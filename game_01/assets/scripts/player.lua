-- VARIABLES GLOBALES
player_states = {
  idle = 1,
  run_side = 2,
  run_up = 3,
  run_down = 4,
  attack = 5
}
player_state = player_states["idle"]
last_direction = "down"

player_velocity = 150
fixed_player_velocity = math.sqrt((player_velocity * player_velocity) / 2)

is_attacking = false
attack_timer = 0
attack_duration = 0.15

function update(dt)
  if is_attacking then
    attack_timer = attack_timer - dt

    if attack_timer <= 0 then
      is_attacking = false
      update_animation_state()
    end
  end

  set_velocity(this, 0, 0);
  local vel_x = 0
  local vel_y = 0

  if is_action_activated("up") then
    vel_y = vel_y + -1
    last_direction = "up"
    set_direction(this, 0, -1)
  end
  if is_action_activated("left") then
    vel_x = vel_x + -1
    last_direction = "left"
    set_direction(this, -1, 0)
  end
  if is_action_activated("down") then
    vel_y = vel_y + 1
    last_direction = "down"
    set_direction(this, 0, 1)
  end
  if is_action_activated("right") then
    vel_x = vel_x + 1
    last_direction = "right"
    set_direction(this, 1, 0)
  end

  if vel_x ~= 0 and vel_y ~= 0 then
    vel_x = vel_x * fixed_player_velocity
    vel_y = vel_y * fixed_player_velocity
  else
    vel_x = vel_x * player_velocity
    vel_y = vel_y * player_velocity
  end

  set_velocity(this, vel_x, vel_y)
  update_animation_state()
end

function update_animation_state()

  -- attack animation overrides movement animation
  if is_attacking then
    return
  end
  
  local vel_x, vel_y = get_velocity(this)

  -- jugador no se mueve
   if math.abs(vel_x) < 0.001 and math.abs(vel_y) < 0.001 then
    if player_state ~= player_states["idle"] then
      player_state = player_states["idle"]
      if last_direction == "down" then
        change_animation(this, "player_idle_front")
      elseif last_direction == "right" then
        flip_sprite(this, false)
        change_animation(this, "player_idle_side")
      elseif last_direction == "left" then
        flip_sprite(this, true)
        change_animation(this, "player_idle_side")
      elseif last_direction == "up" then
        change_animation(this, "player_idle_back")
      end
    end
    return
  end

  -- jugador se mueve hacia la derecha
  if vel_x >= 0.001 then
    flip_sprite(this, false)
    if player_state ~= player_states["run"] then
      player_state = player_states["run"]
      change_animation(this, "player_run_side")
    end
    return
  end

  -- jugador se mueve hacia la izquierda
  if vel_x <= -0.001 then
    flip_sprite(this, true)
    if player_state ~= player_states["run"] then
      player_state = player_states["run"]
      change_animation(this, "player_run_side")
    end
    return
  end

  -- jugador se mueve hacia arriba
  if vel_y <= -0.001 then
    if player_state ~= player_states["run_up"] then
      player_state = player_states["run_up"]
      change_animation(this, "player_run_up")
    end
    return
  end

  -- jugador se mueve hacia abajo
  if vel_y >= 0.001 then
    if player_state ~= player_states["run_down"] then
      player_state = player_states["run_down"]
      change_animation(this, "player_run_down")
    end
    return
  end
end

function start_attack()
  is_attacking = true
  attack_timer = attack_duration
  player_state = player_states["attack"]

  print("[LUASCRIPT] player started attack!")

  if last_direction == "right" then
    flip_sprite(this, false)
    change_animation(this, "player_attack_side")

  elseif last_direction == "left" then
    flip_sprite(this, true)
    change_animation(this, "player_attack_side")

  elseif last_direction == "up" then
    change_animation(this, "player_attack_up")

  elseif last_direction == "down" then
    change_animation(this, "player_attack_down")
  end
end