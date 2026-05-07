
scene = {
  -- Tabla de imagenes y sprites
  sprites = {
    [0] =
    {assetId = "barrier_gem", filePath = "./assets/images/barrier_gem.png"},
    {assetId = "0_grass", filePath = "./assets/images/Grass.png"},
    {assetId = "0_water", filePath = "./assets/images/Water.png"},
    {assetId = "0_nature", filePath = "./assets/images/nature.png"},
    {assetId = "1_city", filePath = "./assets/images/nz_city.png"},
    {assetId = "1_city_props", filePath = "./assets/images/nz_props.png"},
    {assetId = "2_desert", filePath = "./assets/images/na_floors.png"},
    {assetId = "2_desert_props", filePath = "./assets/images/desert_props.png"},
    {assetId = "player", filePath = "./assets/images/player.png"},
    {assetId = "cat", filePath = "./assets/images/cat.png"},
    {assetId = "skull", filePath = "./assets/images/skull.png"},
    {assetId = "beast", filePath = "./assets/images/beast.png"},
    {assetId = "settings", filePath = "./assets/images/Settings.png"},
  },

  -- Tabla con la info de las animaciones
  animations = {
    [0] = 
    {
      animation_id = "player_idle_front",
      texture_id = "player",
      row = 0,
      w = 48,
      h = 48,
      num_frames = 6,
      speed_rate = 15,
      is_loop = true,
    },
    {
      animation_id = "player_idle_side",
      texture_id = "player",
      row = 1,
      w = 48,
      h = 48,
      num_frames = 6,
      speed_rate = 15,
      is_loop = true,
    },
        {
      animation_id = "player_idle_back",
      texture_id = "player",
      row = 2,
      w = 48,
      h = 48,
      num_frames = 6,
      speed_rate = 15,
      is_loop = true,
    },
    {
      animation_id = "player_run_side",
      texture_id = "player",
      row = 4,
      w = 48,
      h = 48,
      num_frames = 6,
      speed_rate = 15,
      is_loop = true,
    },
    {
      animation_id = "player_run_up",
      texture_id = "player",
      row = 5,
      w = 48,
      h = 48,
      num_frames = 6,
      speed_rate = 15,
      is_loop = true,
    },
    {
      animation_id = "player_run_down",
      texture_id = "player",
      row = 3,
      w = 48,
      h = 48,
      num_frames = 6,
      speed_rate = 15,
      is_loop = true,
    },
    -- attacks
    {
      animation_id = "player_attack_side",
      texture_id = "player",
      row = 7,
      w = 48,
      h = 48,
      num_frames = 4,
      speed_rate = 15,
      is_loop = false,
    },
    {
      animation_id = "player_attack_up",
      texture_id = "player",
      row = 8,
      w = 48,
      h = 48,
      num_frames = 4,
      speed_rate = 15,
      is_loop = false,
    },
    {
      animation_id = "player_attack_down",
      texture_id = "player",
      row = 6,
      w = 48,
      h = 48,
      num_frames = 4,
      speed_rate = 15,
      is_loop = false,
    },
  },

  -- Tabla de efectos de sonido
  sounds = {
    [0] =
    {id = "slash", filePath = "./assets/audio/Slash.wav"},
    {id = "hurt", filePath = "./assets/audio/Impact2.wav"},
    {id = "restore", filePath = "./assets/audio/Strange.wav"},
  },

  -- Tabla de musica
  music = {
    [0] = 
    {id = "bgMusic", filePath = "./assets/audio/CalmVillage.ogg"}
  },

  -- Tabla de fuentes
  fonts = {
    [0] =
    {fontId = "press_start_12", filePath = "./assets/fonts/press_start.ttf", fontSize = 20},
  },

  -- Tabla de acciones y teclas
  keys = {
    [0] = 
    {name = "up", key = 119},
    {name = "left", key = 97},
    {name = "down", key = 115},
    {name = "right", key = 100},
  },

  -- Tabla de acciones y botones de raton
  buttons = {
    [0] = 
    {name = "mouse_left_button", button = 1},
  },

  -- Tabla de mapa
  maps = {
    map_path = "./assets/maps/level_01.tmx",
    tilesets = {
      [0] =
      {name = "0_water", path = "./assets/maps/water.tsx"},
      {name = "0_grass", path = "./assets/maps/grass.tsx"},
      {name = "0_nature", path = "./assets/maps/nature.tsx"},
      {name = "1_city", path = "./assets/maps/city.tsx"},
      {name = "1_city_props", path = "./assets/maps/city_props.tsx"},
      {name = "2_desert", path = "./assets/maps/desert.tsx"},
      {name = "2_desert_props", path = "./assets/maps/desert_props.tsx"},
    },
  },

  -- Tabla de entidades
  entities = {
    [0] =
    -- Pause button
    {
      components = {
        clickable = {},
        sprite = {
          assetId = "settings",
          width = 20,
          height = 20,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        script = {
          path = "./assets/scripts/pause.lua",
        },
        transform = {
          position = { x = 375.0, y = 5.0 }, -- TODO: game renders this at x2
          scale = { x = 0.80, y = 0.80 },
          rotation = 0.0,
        },
        ui = {},
      },
    },
    -- Click object to remove tiles - layer 1
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        clickable = {},
        layer = {
          layer = 1;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = true,
          mass = 9999999999,
        },
        script = {
          path = "./assets/scripts/restore.lua",
        },
        sprite = {
          assetId = "barrier_gem",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "1_button",
        },
        transform = {
          position = { x = 1280.0, y = 770.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      }
    },
        -- Click object to remove tiles - layer 2
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        clickable = {},
        layer = {
          layer = 2;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = true,
          mass = 9999999999,
        },
        script = {
          path = "./assets/scripts/restore.lua",
        },
        sprite = {
          assetId = "barrier_gem",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "2_button",
        },
        transform = {
          position = { x = 310.0, y = 1002.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      }
    },
    -- Denizen 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "cat",
          width = 16,
          height = 16,
          src_rect = { x = 16, y = 16 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 200.0, y = 330.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 230.0, y = 330.0 },
          radius = 300.0,
          speed = 50,
        },
      },
    },
    -- Denizen 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "cat",
          width = 16,
          height = 16,
          src_rect = { x = 16, y = 16 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 850.0, y = 580.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 850.0, y = 580.0 },
          radius = 300.0,
          speed = 50,
        },
      },
    },
    -- Denizen 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "cat",
          width = 16,
          height = 16,
          src_rect = { x = 16, y = 16 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 775.0, y = 775.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 985.0, y = 775.0 },
          radius = 300.0,
          speed = 50,
        },
      },
    },
    -- Denizen 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "cat",
          width = 16,
          height = 16,
          src_rect = { x = 16, y = 16 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 345.0, y = 715.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 345.0, y = 715.0 },
          radius = 300.0,
          speed = 50,
        },
      },
    },
    -- Enemy 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        follow = {
          speed = 50,
          detection_radius = 100,
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "skull",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 280.0, y = 425.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        follow = {
          speed = 50,
          detection_radius = 100,
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "skull",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 1045.0, y = 570.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        follow = {
          speed = 50,
          detection_radius = 100,
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "skull",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 1060.0, y = 920.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 01
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        follow = {
          speed = 50,
          detection_radius = 100,
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "skull",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 480.0, y = 1000.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        patrol = {
            speed = 50,
            waypoints = {
              [0] =
              { x = 850, y = 300 },
              { x = 1050, y = 300 },
              { x = 1050, y = 400 },
              { x = 850, y = 400 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 850.0, y = 300.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        patrol = {
            speed = 50,
            waypoints = {
              [0] =
              { x = 840, y = 830 },
              { x = 950, y = 830 },
              { x = 950, y = 920 },
              { x = 840, y = 920 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 840.0, y = 830.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        patrol = {
            speed = 50,
            waypoints = {
              [0] =
              { x = 1220, y = 700 },
              { x = 1370, y = 700 },
              { x = 1370, y = 750 },
              { x = 1220, y = 750 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 1220.0, y = 700.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02
    {
      components = {
        box_collider = {
          width = 16,
          height = 16,
          offset = { x = 0, y = 0 },
        },
        damage = {
          damage = 10,
        },
        faction = {
          faction = "enemy",
        },
        health = {
          maxHealth = 30;
          currentHealth = 30;
        },
        patrol = {
            speed = 50,
            waypoints = {
              [0] =
              { x = 450, y = 700 },
              { x = 650, y = 700 },
              { x = 650, y = 750 },
              { x = 450, y = 750 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 450.0, y = 700.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Player
    -- last on the list so it renders on top of all other entities
    {
      components = {
        animation = {
          id = "player_idle_front",
        },
        attack = {
          damage = 10,
          range = 16.0,
          duration = 0.12,
          cooldown = 0.40,
        },
        camera_follow = {},
        box_collider = {
          width = 8,
          height = 10,
          offset = { x = 4, y = 12 },
        },
        bar = {
          width = 100,
          height = 10,
          posX = 10,
          posY = 10,
          fgColor = { r = 0, g = 255, b = 0, a = 255 },
          bgColor = { r = 60, g = 60, b = 60, a = 255 },
          type = "health"
        }, 
        health = {
          maxHealth = 100,
          currentHealth = 100,
        },
        direction = {},
        faction = {
          faction = "player",
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = true,
          mass = 10,
        },
        script = {
          path = "./assets/scripts/player.lua",
        },
        sprite = {
          assetId = "player",
          width = 48,
          height = 48,
          src_rect = { x = 16, y = 16 }, -- TODO: overriden by animation
          offset = { x = -16, y = -16 },
        },
        tag = {
          tag = "player",
        },
        transform = {
          position = { x = 200.0, y = 200.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    {
      components = {
        bar = {
          width = 100,
          height = 10,
          posX = 10,
          posY = 25,
          fgColor = { r = 100, g = 149, b = 237, a = 255 },
          bgColor = { r = 60, g = 60, b = 60, a = 255 },
          type = "sanity"
        }, 
        sanity = {
          maxSanity = 60,
          currentSanity = 60,
          drain = 1,
        },
      }
    },
  },
}