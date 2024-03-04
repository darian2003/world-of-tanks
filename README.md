
For a better understanding of the game, I recommend watching the gameplay video.

3D Game Inspired From World Of Tanks implemented using purely C++ with OpenGL and using various libraries such as GLEW & GLUT
- The purpose of the game is to destroy as many enemy tanks before the player's tank gets destroyed
- The game logic is implemented such that enemy tanks point their cannon at the player only if the player is inside their specified range.
- Each tank has a cooldown between each shot
- The map is created by randomly generating buildings inside it
- Collisions with other tanks/buldings is implemented such that two objects cannot pass through each other
- The camera is placed behind the player's tank and is performing the same moves as the tank (rotation, translation, etc)
- Movements of the tank are performed using the keyboard and shooting by using the mouse


