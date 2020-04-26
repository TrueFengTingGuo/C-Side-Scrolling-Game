# Side Scrolling Game(C++ , OpenGL)

# Project Description
 This game uses C++ and OpenGL language. In this project, all display is direactly handled by vertex shdaers and fragment shader without using any third party editor. It features sprite rendering ,basic game physcis and particle system.

---

# Game Description
 The player is a secret agent who must steal a helicopter from a secret underground base and escape. The player must find their way through the base and cave systems while avoiding enemy helicopters who are chasing him/her down, dodge falling rocks and defeating different stages of a killer UFO created by scientists in the secret base. 

---

# Explanation of the game

## Basic Control	

Use WSAD to control your character to move around the map. Player can press space bar to fire. Press Q to cycle through weapons. Use mouse to aim. P to pause the game.

## Enemies

There are four enemies in this game. Enemy helicopter can chase player down. As player gets in a certain range, it will fire immediately. Turret has more hp but stay stationary. Rock falls and does damage when it has enough speed. Boss has two ability: dodge bullet and It can continually fire in a certain amount of time. Boss can’t dodge bullets if it is shooting.
 
## Dodge Mechanics	

The core gameplay is to dodge all bullets. Most of the enemies will sign before they are about to fire. The sign is shown as <img src="https://github.com/TrueFengTingGuo/C-Side-Scrolling-Game/blob/master/screenshot/dodgingmark.png" width="20" height="30" border="10" />    in the game. 

<img src="https://github.com/TrueFengTingGuo/C-Side-Scrolling-Game/blob/master/screenshot/dodgingscreenshot.png" width="420" height="250" border="10" /> 

Here is an example where the enemy on the top right corner is ready to shoot. In this case, player should be alerted and ready to dodge the bullet. 

## Boost Speed	

Sometime player may get into a sticky situation where there is not enough speed to dodge to the bullet. To counter this problem, player can press left mouse click to boost velocity. This ability has one second cooldown. Notice that player can only boost himself to a certain speed. This means if current speed is 0.1, then it will boost harder, but if current speed is 1, then it will not boost too much.

## Bottom left UI

<img src="https://github.com/TrueFengTingGuo/C-Side-Scrolling-Game/blob/master/screenshot/currency.png" width="300" height="250" border="10" /> 

Ammo is shown on the top, Currency is shown on the bottom


## Top right UI (store)

<img src="https://github.com/TrueFengTingGuo/C-Side-Scrolling-Game/blob/master/screenshot/store.png" width="300" height="250" border="10" /> 

We have store system in the game. When player has enough currency, player can press right mouse bottom on the corresponding weapon to buy a weapon. The weapon icon should stretch and shrink when player put his mouse on the icon. If player has already owned the weapon, it will buy ammo instead. There are two weapons: SMG (low damage, high fire rate), Rifle (high damage, low fire rate).

## Power Zone

<img src="https://github.com/TrueFengTingGuo/C-Side-Scrolling-Game/blob/master/screenshot/Powerup.png" width="300" height="250" border="10" /> 

When character touches the green area  on the map, this zone will temporally grant player’s massive attack speed and reduced recoil. Under this effect, character will have a visual effect like example on the right.


## Particle System

Particles are mainly used on powerup and collision handling


