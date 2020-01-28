# COMP-2501-Project
 platformer-like game in which a player controls a helicopter navigating a constrained environment of some kind, such as a series of underground passages. You can draw inspiration from the action game "Fort Apocalypse"


## Project Requirements
The project has both technical requirements (restrictions on how you do things and requirements for things that must be included) and gameplay requirements (things that you need to incorporate into the game somehow). Note that this list identifies the bare minimum; projects that contain all required elements but remain uninspired or incomplete will not be received well. Here is a rule of thumb: treating the requirements as a checklist, and minimally meeting all of them, will result in an overall grade of D+.  Use the project as a chance to show off your skills and make something creative and interesting.



The project is intended to exercise the various game elements we study in this course (hence the technical requirements) while being a self-contained game (hence the gameplay requirements). The gameplay requirements are quite low, though, giving you plenty of scope for going beyond them.



Note that there are no requirements relating to art or other assets. Use free, existing assets and do not waste valuable developer time in making new ones.



### Technical requirements.

1. Written in C++ using OpenGL to render; readable code with no fatal bugs.

2. All movement handled through transformations.

3. At least one use of physically-based motion (with gravity and momentum-based collisions).

4. Collision detection between game entities and the walls and platforms of the level.

5. At least one instance of hierarchical transformations for a compound object (e.g., a cannon with swiveling barrel).

6. A gameworld larger than the screen, with ability to scroll around and see different parts.

7. At least one enemy that navigates using path planning.

8. At least one game entity that moves using chase, pursuit, flee, or escape behaviours.



9. Finite state machine controlling overall game (e.g., loading screen, pause, break from action between levels).

10. At least two instances of particle systems used.

### Gameplay requirements.

0. Side-scrolling underground action-helicopter game!

1. At least three different enemy types with distinct behaviours.

2. At least three levels with different layouts.

2a. Optionally, different finishing conditions for each level: e.g., clear enemies, destroy key enemy, collect all keys, collect key and reach exit. You can probably think of many others.

3. At least two distinct weapons the player can use.

4. Use of currency for player to buy upgrades. (Or, some clever way to otherwise get the player to make long-term decisions.)

4a. optionally, RPG-style upgrade paths for the player: additional weapons, shields, speed boosters, and more.

5. A HUD showing useful information: current cash, health, other game elements of interest.

6. At least one interesting powerup with a timer.

7. Challenges that reward planning as well as reflexes.

