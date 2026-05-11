
scene = {
  -- Tabla de imagenes y sprites
  sprites = {
    [0] =
    {assetId = "barrier_gem", filePath = "./assets/images/barrier_gem.png"},
    {assetId = "0_red_dungeon", filePath = "./assets/images/red_dungeon.png"},
    {assetId = "0_red_dungeon_props", filePath = "./assets/images/red_dungeon.png"},
    {assetId = "1_grassy", filePath = "./assets/images/na_floors.png"},
    {assetId = "1_grassy_props", filePath = "./assets/images/grassy_props.png"},
    {assetId = "2_dungeon", filePath = "./assets/images/dungeon.png"},
    {assetId = "2_dungeon_props", filePath = "./assets/images/dungeon_props.png"},
    {assetId = "player", filePath = "./assets/images/player.png"},
    {assetId = "dungeon_char", filePath = "./assets/images/dungeon_char.png"},
    {assetId = "cyclope", filePath = "./assets/images/cyclope.png"},
    {assetId = "red_beast", filePath = "./assets/images/red_beast.png"},
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
    {id = "bgMusic", filePath = "./assets/audio/Crypt.ogg"}
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
    map_path = "./assets/maps/level_02.tmx",
    tilesets = {
      [0] =
      {name = "0_red_dungeon", path = "./assets/maps/red_dungeon.tsx"},
      {name = "0_red_dungeon_props", path = "./assets/maps/red_dungeon_props.tsx"},
      {name = "1_grassy", path = "./assets/maps/grassy.tsx"},
      {name = "1_grassy_props", path = "./assets/maps/grassy_props.tsx"},
      {name = "2_dungeon", path = "./assets/maps/dungeon.tsx"},
      {name = "2_dungeon_props", path = "./assets/maps/dungeon_props.tsx"},
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
          position = { x = 780.0, y = 790.0 },
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
          position = { x = 590.0, y = 1080.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      }
    },
    -- Denizen 01 - 1
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
          assetId = "dungeon_char",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 32 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 1360.0, y = 300.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 1360.0, y = 300.0 },
          radius = 300.0,
          speed = 50,
        },
      },
    },
    -- Denizen 01 - 2
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
          assetId = "dungeon_char",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 32 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 240.0, y = 600.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 240.0, y = 600.0 },
          radius = 300.0,
          speed = 50,
        },
      },
    },
    -- Denizen 01 - 3
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
          assetId = "dungeon_char",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 32 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 480.0, y = 700.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 480.0, y = 700.0 },
          radius = 300.0,
          speed = 50,
        },
      },
    },
    -- Denizen 01 - 4
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
          assetId = "dungeon_char",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 32 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Denizen 01",
        },
        transform = {
          position = { x = 900.0, y = 780.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        wander = {
          origin = { x = 900.0, y = 780.0 },
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
          assetId = "cyclope",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 1370.0, y = 880.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 01 - 2
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
          assetId = "cyclope",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 410.0, y = 240.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 01 - 3
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
          assetId = "cyclope",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 1190.0, y = 660.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 01 - 4
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
          assetId = "cyclope",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 01",
        },
        transform = {
          position = { x = 500.0, y = 930.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02 - 1
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
              { x = 420, y = 200 },
              { x = 1000, y = 200 },
              { x = 1000, y = 220 },
              { x = 420, y = 220 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "red_beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 420.0, y = 200.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02 - 2
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
              { x = 540, y = 1140 },
              { x = 960, y = 1140 },
              { x = 960, y = 1190 },
              { x = 540, y = 1190 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "red_beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 540.0, y = 1140.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02 - 3
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
              { x = 600, y = 375 },
              { x = 960, y = 375 },
              { x = 960, y = 410 },
              { x = 600, y = 410 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "red_beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 600.0, y = 375.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Enemy 02 - 4
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
              { x = 670, y = 990 },
              { x = 915, y = 990 },
              { x = 915, y = 1020 },
              { x = 670, y = 1020 },
            },
        },
        rigid_body = {
          is_dynamic = false,
          is_solid = false,
          mass = 1,
        },
        sprite = {
          assetId = "red_beast",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
          offset = { x = 0, y = 0 },
        },
        tag = {
          tag = "Enemy 02",
        },
        transform = {
          position = { x = 670.0, y = 1000.0 },
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
        sanity = {
          maxSanity = 60,
          currentSanity = 60,
          drain = 1,
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
    -- Health bar
    {
      components = {
        bar = {
          width = 100,
          height = 10,
          posX = 10,
          posY = 10,
          fgColor = { r = 0, g = 255, b = 0, a = 255 },
          bgColor = { r = 60, g = 60, b = 60, a = 255 },
          type = "health"
        }, 
      },
    },
    -- Sanity bar
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
      },
    },
  },
}