# Aim and Shoot

## Description
This is a simple 3D game implemented in C++ using openGL.
As a player, you are in a shooting training room, with some targets, and some trajectories. You are practicing on types of trajectories, which are:
- Bullet.
- Grenade.
- Shuriken (ninja star).

## Animations
Each model animates as follows:
- Bullet:
    - Rotates continually around its direction axis.
    - Travels along the room in a straight line.
- Grenade:
    - Rotates continually around a diagonal axis between its direction and horizontal axis’s.
    - Travels along the room in a normal projectile motion as per the side view.
       
- Shuriken:
    - Rotates continually around its vertical axis (as its first image is a top view).
    - Travels along the room in a Frisbee motion as per the top view. The room traveling motions include testing if the shot hit a target or the room border; also it is not affected by any power factor.

## Camera Control
At the aiming phase, the player can turn left or right (using the mouse), changing both the camera view alongside the initial shooting direction. Turnings up and down are not allowed (to simplify the room traversal of the trajectories).
At the replay mode, the camera is attached to the trajectory (as the trajectory is visible with its view), and the camera follows the object till it stops.

## Gameplay
There is only one target in the middle of the room. The player can move this target (left, right, near, or far) with the keyboard.
The player also can change the trajectory with the number keys. After firing, the trajectory travels the room till it stops hitting something (the target, or a wall), 
then the replay mode starts showing where did the shot land. This practice mode is repeated as many times as the player wants.

## Controls
- Use the mouse to move the camera
- a: move the target to the left
- s: move the target away from you
- d: move the target to the right
- w: move the target closer to you
- f: fire weapon
- 0: change weapon
- 1: change trajectory of firing to the right
- 2: change trajectory of firing to the left
- ESC: exit game
