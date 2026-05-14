
scene = {
  -- Tabla de imagenes y sprites
  sprites = {},

  -- Tabla con la info de las animaciones
  animations = {
  },

  -- Tabla de efectos de sonido
  sounds = {
  },

  -- Tabla de musica
  music = {
    [0] = 
    {id = "bgMusic", filePath = "./assets/audio/AdventureBegin.ogg"}
  },

  -- Tabla de fuentes
  fonts = {
    [0] =
    {fontId = "press_start_16", filePath = "./assets/fonts/press_start.ttf", fontSize = 16},
    {fontId = "press_start_24", filePath = "./assets/fonts/press_start.ttf", fontSize = 24},
    {fontId = "press_start_32", filePath = "./assets/fonts/press_start.ttf", fontSize = 32},
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
  maps = {},

  -- Tabla de entidades
  entities = {
    [0] =
    {
      components = {
        text = {
          text = "Inderdimensional",
          fontId = "press_start_24",
          r = 255,
          g = 255,
          b = 255,
          a = 255,
        },
        transform = {
          position = { x = 10.0, y = 30.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    {
      components = {
        text = {
          text = "Fixer",
          fontId = "press_start_24",
          r = 255,
          g = 255,
          b = 255,
          a = 255,
        },
        transform = {
          position = { x = 10.0, y = 60.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    -- Level 01 button
    {
      components = {
        clickable = {},
        script = {
          path = "./assets/scripts/menu_button_01.lua",
        },
        text = {
          text = "Level 01",
          fontId = "press_start_16",
          r = 0,
          g = 0,
          b = 0,
          a = 0,
        },
        transform = {
          position = { x = 180.0, y = 120.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        ui = {},
        ui_rect = {
          width = 200,
          height = 40,
          color = { r = 245, g = 245, b = 245, a = 245 },
        },
      },
    },
    -- Level 02 button
    {
      components = {
        clickable = {},
        script = {
          path = "./assets/scripts/menu_button_02.lua",
        },
        text = {
          text = "Level 02",
          fontId = "press_start_16",
          r = 0,
          g = 0,
          b = 0,
          a = 0,
        },
        transform = {
          position = { x = 180.0, y = 180.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        ui = {},
        ui_rect = {
          width = 200,
          height = 40,
          color = { r = 245, g = 245, b = 245, a = 245 },
        },
      },
    },
    -- Level 03 button
    {
      components = {
        clickable = {},
        script = {
          path = "./assets/scripts/menu_button_03.lua",
        },
        text = {
          text = "Level 03",
          fontId = "press_start_16",
          r = 0,
          g = 0,
          b = 0,
          a = 0,
        },
        transform = {
          position = { x = 180.0, y = 240.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        ui = {},
        ui_rect = {
          width = 200,
          height = 40,
          color = { r = 245, g = 245, b = 245, a = 245 },
        },
      },
    },
  },
}