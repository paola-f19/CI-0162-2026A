#include "SceneLoader.hpp" 

#include <glm/glm.hpp>
#include <iostream>

#include "../Components/AnimationComponent.hpp"
#include "../Components/AttackComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/DamageComponent.hpp"
#include "../Components/DirectionComponent.hpp"
#include "../Components/FactionComponent.hpp"
#include "../Components/HealthBarComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/LayerComponent.hpp"
#include "../Components/PatrolComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/WanderComponent.hpp"
#include "../Game/Game.hpp"

SceneLoader::SceneLoader() {
  std::cout << "[SCENELOADER] Se ejecuta constructor" << std::endl;
}

SceneLoader::~SceneLoader() {
  std::cout << "[SCENELOADER] Se ejecuta destructor" << std::endl;
}

void SceneLoader::LoadScene(const std::string& scenePath, sol::state& lua
  , std::unique_ptr<AnimationManager>& animationManager
  , std::unique_ptr<AssetManager>& assetManager
  , std::unique_ptr<ControllerManager>& controllerManager
  , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer) {
  
  sol::load_result script_result = lua.load_file(scenePath);
  if (!script_result.valid()) {
    sol::error err = script_result;
    std::string errMessage = err.what();
    std::cerr << " [SCENELOADER] " << errMessage << std::endl;
    return;
  }

  lua.script_file(scenePath);

  sol::table scene = lua["scene"];

  sol::table sprites = scene["sprites"];
  LoadSprites(renderer, sprites, assetManager);
  std::cout << " [SCENELOADER] loaded sprites" << std::endl;

  sol::table animations = scene["animations"];
  LoadAnimations(animations, animationManager);
  std::cout << " [SCENELOADER] loaded animations" << std::endl;

  sol::table fonts = scene["fonts"];
  LoadFonts(fonts, assetManager);
  std::cout << " [SCENELOADER] loaded fonts" << std::endl;

  sol::table keys = scene["keys"];
  LoadKeys(keys, controllerManager);
  std::cout << " [SCENELOADER] loaded keys" << std::endl;

  sol::table buttons = scene["buttons"];
  LoadButtons(buttons, controllerManager);
  std::cout << " [SCENELOADER] loaded buttons" << std::endl;

  sol::table maps = scene["maps"];
  LoadMap(maps, registry);
  std::cout << " [SCENELOADER] loaded maps" << std::endl;

  sol::table entities = scene["entities"];
  LoadEntities(lua, entities, registry);
  std::cout << " [SCENELOADER] loaded entities" << std::endl;
}

void SceneLoader::LoadSprites(SDL_Renderer* renderer, const sol::table& sprites
  , std::unique_ptr<AssetManager>& assetManager) {
  int index = 0;
  while (true) {
    sol::optional<sol::table> hasSprite = sprites[index];
    if (hasSprite == sol::nullopt) {
      break;
    }

    sol::table sprite = sprites[index];

    std::string assetId = sprite["assetId"];
    std::string filePath = sprite["filePath"];

    assetManager->AddTexture(renderer, assetId, filePath);

    index++;
  }
}

void SceneLoader::LoadAnimations(const sol::table& animations
  , std::unique_ptr<AnimationManager>& animationManager) {
  int index = 0;
  while (true) {
    sol::optional<sol::table> hasAnimation = animations[index];
    if (hasAnimation == sol::nullopt) {
      break;
    }  
    sol::table animation = animations[index];

    std::string animationId = animation["animation_id"];
    std::string textureId = animation["texture_id"];
    int row = animation["row"];
    int width = animation["w"];
    int height = animation["h"];
    int numFrames = animation["num_frames"];
    int speedRate = animation["speed_rate"];
    bool isLoop = animation["is_loop"];

    animationManager->AddAnimation(animationId, textureId, row, width, height
      , numFrames, speedRate, isLoop);

    index++;
  } 
}

void SceneLoader::LoadFonts(const sol::table& fonts
  , std::unique_ptr<AssetManager>& assetManager) {
  int index = 0;
  while (true) {
    sol::optional<sol::table> hasFont = fonts[index];
    if (hasFont == sol::nullopt) {
      break;
    }

    sol::table font = fonts[index];
    std::string fontId = font["fontId"];
    std::string filePath = font["filePath"];
    int size = font["fontSize"];

    assetManager->AddFont(fontId, filePath, size);

    index++;
  }
}

void SceneLoader::LoadKeys(const sol::table& keys
  , std::unique_ptr<ControllerManager>& controllerManager) {
  int index = 0;
  while (true) {
    sol::optional<sol::table> hasKey = keys[index];
    if (hasKey == sol::nullopt) {
      break;
    }

    sol::table key = keys[index];

    std::string name = key["name"];
    int keyCode = key["key"];

    controllerManager->AddActionKey(name, keyCode);

    index++;
  }
}

void SceneLoader::LoadButtons(const sol::table& buttons
  , std::unique_ptr<ControllerManager>& controllerManager) {
  int index = 0;
  while (true) {
    sol::optional<sol::table> hasButtons = buttons[index];
    if (hasButtons == sol::nullopt) {
      break;
    }

    sol::table button = buttons[index];

    std::string name = button["name"];
    int buttonCode = button["button"];

    controllerManager->AddMouseButton(name, buttonCode);

    index++;
  }
}

void SceneLoader::LoadMap(const sol::table map,
  std::unique_ptr<Registry>& registry) {

  sol::optional<int> hasWidth = map["width"];
  if (hasWidth != sol::nullopt) {
    Game::GetInstance().mapWidth = map["width"];
  }

  sol::optional<int> hasHeight = map["height"];
  if (hasHeight != sol::nullopt) {
    Game::GetInstance().mapHeight = map["height"];
  }

  sol::optional<std::string> hasPath = map["map_path"];
  if (hasPath == sol::nullopt) {
    return;
  }

  std::string mapPath = map["map_path"];

  // Load TMX map
  tinyxml2::XMLDocument xmlmap;
  xmlmap.LoadFile(mapPath.c_str());

  tinyxml2::XMLElement* xmlRoot = xmlmap.RootElement();

  int tWidth, tHeight, mWidth, mHeight;
  xmlRoot->QueryIntAttribute("tilewidth", &tWidth);
  xmlRoot->QueryIntAttribute("tileheight", &tHeight);
  xmlRoot->QueryIntAttribute("width", &mWidth);
  xmlRoot->QueryIntAttribute("height", &mHeight);

  Game::GetInstance().mapWidth = tWidth * mWidth;
  Game::GetInstance().mapHeight = tHeight * mHeight;

  //*  LOAD TILESETS 
  std::vector<TilesetData> tilesets;
  int tilesetIndex = 0;

  tinyxml2::XMLElement* xmlTileset = xmlRoot->FirstChildElement("tileset");

  // loop for every tileset
  while (xmlTileset != nullptr) {
    std::cout << "INSIDE LOOP TO ADD TILESETS" << std::endl;

    int firstGid;
    xmlTileset->QueryIntAttribute("firstgid", &firstGid);

    // Find matching Lua tileset
    sol::table luaTilesets = map["tilesets"];
    
    sol::optional<sol::table> hasTileset = luaTilesets[tilesetIndex];
    if (hasTileset == sol::nullopt) break;

    sol::table luaTileset = luaTilesets[tilesetIndex];

    std::string tilesetName = luaTileset["name"];
    std::string tilesetPath = luaTileset["path"];

    // load TSX
    tinyxml2::XMLDocument xmltilesetDoc;
    xmltilesetDoc.LoadFile(tilesetPath.c_str());

    // Extraer la raiz del documento xml
    tinyxml2::XMLElement* xmlTileSetRoot = xmltilesetDoc.RootElement();

    // Extraer cantidad de columnas del tileset
    int columns;
    xmlTileSetRoot->QueryIntAttribute("columns", &columns);

    TilesetData data;
    data.name = tilesetName;
    data.firstGid = firstGid;
    data.columns = columns;

    tilesets.push_back(data);

    tilesetIndex++;
    xmlTileset = xmlTileset->NextSiblingElement("tileset");
  }

  std::cout << "NUMBER OF TILESETS: " << tilesets.size() << std::endl;

  //*  LOAD LAYERS
  tinyxml2::XMLElement* xmlLayer = xmlRoot->FirstChildElement("layer");
  int tilesetIndexForLoadLayer = 0;

  while (xmlLayer != nullptr) {
    LoadLayer(registry, xmlLayer, tWidth, tHeight, mWidth, tilesets
      , tilesetIndexForLoadLayer);
    xmlLayer = xmlLayer->NextSiblingElement("layer");
    tilesetIndexForLoadLayer++;
  }

  //*  LOAD OBJECTS
  tinyxml2::XMLElement* xmlObjectGroup =
    xmlRoot->FirstChildElement("objectgroup");

  while (xmlObjectGroup != nullptr) {
    const char* objectGroupName;
    xmlObjectGroup->QueryStringAttribute("name", &objectGroupName);

    std::string name = objectGroupName;

    if (name.find("colliders") != std::string::npos) {
      LoadColliders(registry, xmlObjectGroup);
    }

    xmlObjectGroup = xmlObjectGroup->NextSiblingElement("objectgroup");
  }
}

void SceneLoader::LoadLayer(std::unique_ptr<Registry>& registry,
  tinyxml2::XMLElement* layer,
  int tWidth, int tHeight, int mWidth,
  const std::vector<TilesetData>& tilesets, int tilesetIndex) {

  tinyxml2::XMLElement* xmldata = layer->FirstChildElement("data");

  const char* data = xmldata->GetText();

  std::stringstream tmpNumber;
  int pos = 0;
  int tileNumber = 0;

  while (true) {
    if (data[pos] == '\0') {
      break;
    }
    if (isdigit(data[pos])) {
      tmpNumber << data[pos];
    } else if (!isdigit(data[pos]) && tmpNumber.str().length() != 0) {
      int tileId = std::stoi(tmpNumber.str());
      if (tileId > 0) {
        
        Entity tile = registry->CreateEntity();
        // std::cout << "CREATED TILE " << tileId << " THAT USES " << tilesetIndex << std::endl;
        tile.AddComponent<TransformComponent>(
          glm::vec2(
            (tileNumber % mWidth) * tWidth,
            (tileNumber / mWidth) * tHeight
          )
        );
        int localId = tileId - tilesets[tilesetIndex].firstGid;

        tile.AddComponent<SpriteComponent>(
          tilesets[tilesetIndex].name,
          tWidth,
          tHeight,
          ((localId) % tilesets[tilesetIndex].columns) * tWidth,
          ((localId) / tilesets[tilesetIndex].columns) * tHeight
        );

        tile.AddComponent<LayerComponent>(
          std::stoi(std::string(1, tilesets[tilesetIndex].name.at(0)))
        );
      }

      tileNumber++;
      tmpNumber.str("");
    }
    pos++;
  }
}

void SceneLoader::LoadColliders(std::unique_ptr<Registry>& registry
  , tinyxml2::XMLElement* objectGroup) {
  // get collider layer
  const char* objectGroupName;
  objectGroup->QueryStringAttribute("name", &objectGroupName);
  int layer = std::stoi(std::string(1, objectGroupName[0]));

  // Cargar el primer collider
  tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");

  while (object != nullptr) {
    // Declarar variables
    const char* name;
    std::string tag;
    int x, y, w, h;

    // Obtener el tag del objeto
    object->QueryStringAttribute("name", &name);
    tag = name;

    // Obtener la posicion
    object->QueryIntAttribute("x", &x);
    object->QueryIntAttribute("y", &y);

    // Obtener medidas
    object->QueryIntAttribute("width", &w);
    object->QueryIntAttribute("height", &h);

    // Crear entidad
    Entity collider = registry->CreateEntity();
    collider.AddComponent<TagComponent>(tag);
    collider.AddComponent<TransformComponent>(glm::vec2(x, y));
    collider.AddComponent<BoxColliderComponent>(w, h);
    collider.AddComponent<RigidBodyComponent>(false, true, 9999999999.0f);
    collider.AddComponent<LayerComponent>(layer);

    object = object->NextSiblingElement("object");
  }
}

void SceneLoader::LoadEntities(sol::state& lua, const sol::table& entities
  , std::unique_ptr<Registry>& registry) {
  int index = 0;
  std::cout << "  [LOAD ENTITIES] entered load entities" << std::endl;
  while (true) {
    sol::optional<sol::table> hasEntity = entities[index];
    if (hasEntity == sol::nullopt) {
      break;
    }

    sol::table entity = entities[index];

    Entity newEntity = registry->CreateEntity();
    std::cout << "  [LOAD ENTITIES] created entity" << std::endl;

    sol::optional<sol::table> hasComponents = entity["components"];
    if (hasComponents != sol::nullopt) {
      sol::table components = entity["components"];
      std::cout << "  [LOAD ENTITIES] got components" << std::endl;

      //* AnimationComponent
      sol::optional<sol::table> hasAnimation = components["animation"];
      if (hasAnimation != sol::nullopt) {
        std::string id = components["animation"]["id"];
        newEntity.AddComponent<AnimationComponent>(id);
      }
      std::cout << "  [LOAD ENTITIES] loaded animation" << std::endl;

      //* AttackComponent
      sol::optional<sol::table> hasAttack = components["attack"];
      if (hasAttack != sol::nullopt) {
        newEntity.AddComponent<AttackComponent>(
          components["attack"]["damage"],
          components["attack"]["range"],
          components["attack"]["duration"],
          components["attack"]["cooldown"]
        );
      }

      //* BoxColliderComponent
      sol::optional<sol::table> hasBoxCollider = components["box_collider"];
      if (hasBoxCollider != sol::nullopt) {
        newEntity.AddComponent<BoxColliderComponent>(
          components["box_collider"]["width"],
          components["box_collider"]["height"],
          glm::vec2(
            components["box_collider"]["offset"]["x"],
            components["box_collider"]["offset"]["y"]
          )
        );
      }
      std::cout << "  [LOAD ENTITIES] loaded boxcollider" << std::endl;

      //* CameraFollowComponent
      sol::optional<sol::table> hasCameraFollow = components["camera_follow"];
      if (hasCameraFollow != sol::nullopt) {
        newEntity.AddComponent<CameraFollowComponent>();
      }
      std::cout << "  [LOAD ENTITIES] loaded camera movement" << std::endl;

      //* CircleColliderComponent
      sol::optional<sol::table> hasCircleCollider =
        components["circle_collider"];
      if (hasCircleCollider != sol::nullopt) {
        newEntity.AddComponent<CircleColliderComponent>(
          components["circle_collider"]["radius"],
          components["circle_collider"]["width"],
          components["circle_collider"]["height"]
        );
      }
      std::cout << "  [LOAD ENTITIES] loaded circle collider" << std::endl;

      //* ClickableComponent
      sol::optional<sol::table> hasClickable = components["clickable"];
      if (hasClickable != sol::nullopt) {
        newEntity.AddComponent<ClickableComponent>();
      }
      std::cout << "  [LOAD ENTITIES] loaded clickable" << std::endl;

      //* DamageComponent
      sol::optional<sol::table> hasDamage = components["damage"];
      if (hasDamage != sol::nullopt) {
        int damage = components["damage"]["damage"];
        newEntity.AddComponent<DamageComponent>(damage);
      }

      //* DirectionComponent
      sol::optional<sol::table> hasDirection = components["direction"];
      if (hasDirection != sol::nullopt) {
        newEntity.AddComponent<DirectionComponent>();
      }

      //* FactionComponent
      sol::optional<sol::table> hasFaction = components["faction"];
      if (hasFaction != sol::nullopt) {
        std::string faction = components["faction"]["faction"];
        newEntity.AddComponent<FactionComponent>(faction);
      }

      //* HealthBarComponent
      sol::optional<sol::table> hasHealthBar = components["healthbar"];
      if (hasHealthBar != sol::nullopt) {
        SDL_Color fg = {components["healthbar"]["fgColor"]["r"]
          , components["healthbar"]["fgColor"]["g"]
          , components["healthbar"]["fgColor"]["b"]
          , components["healthbar"]["fgColor"]["a"]
        };
        SDL_Color bg = {components["healthbar"]["bgColor"]["r"]
          , components["healthbar"]["bgColor"]["g"]
          , components["healthbar"]["bgColor"]["b"]
          , components["healthbar"]["bgColor"]["a"]
        };
        newEntity.AddComponent<HealthBarComponent>(
          components["healthbar"]["width"],
          components["healthbar"]["height"],
          fg, bg
        );
      }

      //* HealthComponent
      sol::optional<sol::table> hasHealth = components["health"];
      if (hasHealth != sol::nullopt) {
        newEntity.AddComponent<HealthComponent>(
          components["health"]["maxHealth"],
          components["health"]["currentHealth"]
        );
      }

      //* LayerComponent
      sol::optional<sol::table> hasLayer = components["layer"];
      if (hasLayer != sol::nullopt) {
        int layer = components["layer"]["layer"];
        newEntity.AddComponent<LayerComponent>(layer);
      }
      std::cout << "  [LOAD ENTITIES] loaded layer" << std::endl;

      //* PatrolComponent
      sol::optional<sol::table> hasPatrol = components["patrol"];
      if (hasPatrol != sol::nullopt) {
        std::vector<glm::vec2> points;

        int index = 0;
        while (true) {
          sol::optional<sol::table> hasWaypoint = components["patrol"]["waypoints"][index];
          if (hasWaypoint == sol::nullopt) {
            break;
          }

          sol::table point = components["patrol"]["waypoints"][index];
          points.emplace_back(point["x"], point["y"]);

          index++;
        }

        newEntity.AddComponent<PatrolComponent>(
            points,
            0,
            components["patrol"]["speed"]
        );
      }

      //* RigidBodyComponent
      sol::optional<sol::table> hasRigidBody = components["rigid_body"];
      if (hasRigidBody != sol::nullopt) {
        newEntity.AddComponent<RigidBodyComponent>(
          components["rigid_body"]["is_dynamic"],
          components["rigid_body"]["is_solid"],
          components["rigid_body"]["mass"]
        );
      }
      std::cout << "  [LOAD ENTITIES] loaded rigidbody" << std::endl;

      //* SpriteComponent
      sol::optional<sol::table> hasSprite = components["sprite"];
      if (hasSprite != sol::nullopt) {
        newEntity.AddComponent<SpriteComponent>(
          components["sprite"]["assetId"],
          components["sprite"]["width"],
          components["sprite"]["height"],
          components["sprite"]["src_rect"]["x"],
          components["sprite"]["src_rect"]["y"],
          glm::vec2(
            components["sprite"]["offset"]["x"],
            components["sprite"]["offset"]["y"]
          )
        );
      }
      std::cout << "  [LOAD ENTITIES] loaded sprite" << std::endl;

      //* TextComponent
      sol::optional<sol::table> hasText = components["text"];
      if (hasText != sol::nullopt) {
        newEntity.AddComponent<TextComponent>(
          components["text"]["text"],
          components["text"]["fontId"],
          components["text"]["r"],
          components["text"]["g"],
          components["text"]["b"],
          components["text"]["a"]
        );
      }
      std::cout << "  [LOAD ENTITIES] loaded text" << std::endl;

      //* TagComponent
      sol::optional<sol::table> hasTag = components["tag"];
      if (hasTag != sol::nullopt) {
        std::string tag = components["tag"]["tag"];
        newEntity.AddComponent<TagComponent>(tag);
      }
      std::cout << "  [LOAD ENTITIES] loaded tag" << std::endl;

      //* TransformComponent
      sol::optional<sol::table> hasTransform = components["transform"];
      if (hasTransform != sol::nullopt) {
        newEntity.AddComponent<TransformComponent>(
          glm::vec2(
            components["transform"]["position"]["x"],
            components["transform"]["position"]["y"]
          ),
          glm::vec2(
            components["transform"]["scale"]["x"],
            components["transform"]["scale"]["y"]
          ),
          components["transform"]["rotation"]
        );
      }
      std::cout << "  [LOAD ENTITIES] loaded transform" << std::endl;

      //* WanderComponent
      sol::optional<sol::table> hasWander = components["wander"];
      if (hasWander != sol::nullopt) {
        newEntity.AddComponent<WanderComponent>(
          glm::vec2(
            components["wander"]["origin"]["x"],
            components["wander"]["origin"]["y"]
          ),
          components["wander"]["radius"],
          components["wander"]["speed"]
        );
      }

      //* ScriptComponent
      sol::optional<sol::table> hasScript = components["script"];
      if (hasScript != sol::nullopt) {
        lua["on_awake"] = sol::nil;
        lua["on_collision"] = sol::nil;
        lua["on_click"] = sol::nil;
        lua["update"] = sol::nil;

        std::string path = components["script"]["path"];
        lua.script_file(path);

        sol::optional<sol::function> hasOnAwake = lua["on_awake"];
        if (hasOnAwake != sol::nullopt) {
          lua["this"] = newEntity;
          sol::function OnAwake = lua["on_awake"];
          OnAwake();
        }

        sol::optional<sol::function> hasOnCollision = lua["on_collision"];
        sol::function onCollision = sol::nil;
        if (hasOnCollision != sol::nullopt) {
          onCollision = lua["on_collision"];
        }

        sol::optional<sol::function> hasOnClick = lua["on_click"];
        sol::function onClick = sol::nil;
        if (hasOnClick != sol::nullopt) {
          onClick = lua["on_click"];
        }

        sol::optional<sol::function> hasUpdate = lua["update"];
        sol::function update = sol::nil;
        if (hasUpdate != sol::nullopt) {
          update = lua["update"];
        }

        sol::optional<sol::function> hasAttack = lua["start_attack"];
        sol::function startAttack = sol::nil;
        if (hasAttack != sol::nullopt) {
          startAttack = lua["start_attack"];
        }
        std::cout << "  [LOAD ENTITIES] loaded script" << std::endl;

        newEntity.AddComponent<ScriptComponent>(onCollision, onClick, update, startAttack);
      }
    }

    index++;
  }
}