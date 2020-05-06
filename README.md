# War Vessels ReadME

Author: Sruti Kamarajugadda

---


The project, War Vessels, is simply the game Battleship with a twist. Alike certain forms of Battleship, this two player game is set up where you, the user, play against the computer. The game goes as follows: 

* After you, the user, pick where to place your ships, the computer will pick where it places its ships. However, you can customize the the width of the board, the height of the board, the number of ships you would like to place, and your name, shown on the graphics board, in the run.cc class. You can also customize if you play against the easy player strategy or difficult player strategy. 
* -> Easy Player Strategy: You can stack ships; however, the computer cannot. This gives you a much greater advantage. 
* -> Advanced Player Strategy: You can stack ships and so can the computer player strategy. You still do, however, have an advantage, because the computer still shoots randomly, so the computer could potentially shoot over and over in a coordinate point where there are no ships. 

To play the game, simply press run, and when you are ready to move to load the game, press the 1 key on the opening screen. From there on, simply follow the instructions on the bottom left corner to play the game and note that in order to make selections, you must use mouse presses. To adapt the game, it is important to note that logic mostly exists in the src classes, while graphics code and some logic code exists in my_app.cc

In terms of installation, the game runs with cinder graphics on a CMake project in CLion. In order to play this game, you must download Clion and install CMake and cinder. This project also uses the ciAnimatedGif cinder block which can be found here: [GitHub] (https://github.com/cwhitney/ciAnimatedGif)

