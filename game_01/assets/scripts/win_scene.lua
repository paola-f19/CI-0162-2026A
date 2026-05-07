
scene = {
  -- Tabla de imagenes y sprites
  sprites = {},

  -- Tabla con la info de las animaciones
  animations = {
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
    {fontId = "press_start_24", filePath = "./assets/fonts/press_start.ttf", fontSize = 24},
    {fontId = "press_start_16", filePath = "./assets/fonts/press_start.ttf", fontSize = 16},
  },

  -- Tabla de acciones y teclas
  keys = {
  },

  -- Tabla de acciones y botones de raton
  buttons = {
    [0] = 
    {name = "mouse_left_button", button = 1},
  },

  -- Tabla de mapa
  maps = {
  },

  -- Tabla de entidades
  entities = {
    [0] =
    -- Win text
    {
      components = {
        text = {
            text = "Level Cleared!",
            fontId = "press_start_24",
            r = 255,
            g = 255,
            b = 255,
            a = 255,
        },
        transform = {
            position = { x = 40.0, y = 80.0 },
            scale = { x = 1.0, y = 1.0},
            rotation = 0.0,
        },
        ui = {},
      },
    },
    -- Restart button
    {
      components = {
        clickable = {},
        script = {
          path = "./assets/scripts/restart.lua",
        },
        text = {
          text = "Replay",
          fontId = "press_start_16",
          r = 60,
          g = 60,
          b = 60,
          a = 255,
        },
        transform = {
          position = { x = 100.0, y = 150.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        ui = {},
        ui_rect = {
          width = 200,
          height = 40,
          color = { r = 100, g = 149, b = 237, a = 255 },
        },
      },
    },
    -- Menu button
    {
      components = {
        clickable = {},
        script = {
          path = "./assets/scripts/menu_button.lua",
        },
        text = {
          text = "Main Menu",
          fontId = "press_start_16",
          r = 60,
          g = 60,
          b = 60,
          a = 255,
        },
        transform = {
          position = { x = 100.0, y = 200.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        ui = {},
        ui_rect = {
          width = 200,
          height = 40,
          color = { r = 100, g = 149, b = 237, a = 255 },
        },
      },
    },
  },
}