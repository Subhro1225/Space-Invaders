# Space-Invaders
Space Invaders is a console based game, which is developed by only using C language. 
The project is inspired by an old arcade game which was published by Taito in Japan, in April 1978.
<br>
This is a fixed shooter single player game in which the user contols a spaceship (Left and Right) which is loaded with a cannons which is used 
to shoot a number of aliens overhead. The user needs to destroy all the aliens in order to win the game before the aliens reach the ground. the aliens move both horizontally and vertically.
Each alien consist 10 points and the score is showed in the top right corner of the screen. 
<br>
<h2>Controls</h2>
a to move the spaceship left.<br>
b to move the spaceship right.<br>
" " to shoot a bullet.<br>
q to quit the game.<br>
<h2>logic</h2>
It is a text based console appilcaition so every character is desplayed as a symbol. <br>
'^' is used for the spaceship.<br>
'0' is used for the aliens.<br>
'|' is used for the bullets.<br>

1. The main function runs a main gameloop till the condition is true.<br>
2. In the game loop is board is rapidly initilized.
3. The board is updated according to the user's input and initilized again in the next itteration.
4. The game runs till the condition becomes false that is when the player presses 'q' or the aliens reaches to the bottom or if the player clears all the aliens.
