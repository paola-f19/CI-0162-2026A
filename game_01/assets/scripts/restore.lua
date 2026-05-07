-- VARIABLES GLOBALES
clickable = false
this_layer = 0

-- TODO: collision with non-player entities will set the layer erroneously
function on_collision(other)
  clickable = true
  print("collision happening")

  this_layer = get_layer(this)
end

-- TODO: bug where just calling 'this' gives me the player info instead of object
function on_click()
  if clickable then
    print("restoring dimension "..this_layer.. " !")
    clickable = false;
    play_sound("restore")
    remove_layer(this_layer)
  end
end