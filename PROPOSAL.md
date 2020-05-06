# War Vessels

Author: Sruti Kamarajugadda

---


The endeavor which I embarked on for this project is ultimately recreating the game Battleship with a twist. The twist that I was able to implement is the ability of the hard player strategy to stack ships. The game of Battleship in its truest essence is simply a two-player game, where players, through luck and a bit of strategy, try to target and sink ships in the positions their opponents have placed them. Players before the start of their game would position a set number of ships, which happened to just be one size, anywhere in a set size coordinate grid; players would then take turns conveying one coordinate point where he or she believes their opponent placed their ship. The game continues until one player is deemed victorious, eventually becoming victor through sinking all of his or her opponent’s ships. In this implementation of Battleship, one player strategy was a human player; however, the other was a programmed player strategy (an advanced or easier strategy the player strategy that the human player can choose to play against).

My inspiration for this game comes from the many very intense rounds of Battleship I use to play in grade-school against my friends. I believe my motivation to complete the implementation of this project is a derivative of my fact that I am honestly so excited to be able to have enough knowledge to both approach and code a game that I have grown up being so elated just to play.

The external library I used is the ciAnimatedGif cinder block extension. Compatible with a mac, I used this external library as a means of reward or punishment, if the user won or lost the game respectively. And a non-strictly structured timeline for this project includes:
* Week 1: Implemented all the logic for the game, including setting up the board object, ship objects, etc., for the game. Wrote test for the helper functions for this logic. Was able to play the game fully on the console. Showed a trivial use for my external library. 

* Week 2: Started working on the graphics of the game. Was able to finish basic graphics. Was able to track user location on cinder graphics screen. In terms of logic, rewrote much code from Week 1 to avoid a circular dependency between my_app.cc and game engine.

* Week 3: Spent the majority of the time on making aesthetics better. Incorporated the external library in a meaningful way. Increased complexity by reworking the player strategies.

Lastly, as I said before in the case I was able to finish this project earlier than the timeline detailed in the PROPOSAL.MD, I would most likely work to make the game’s aesthetics even more analogous to implementations we would see in an online version of Battleship. Ultimately, although I was not able to implement a leader board, I was able to make the graphics as advanced as I would have hoped, rather than the simple graphics I believed I would achieve during week 3, such as having to type into the graphics screen or having to play at least some of the game on the console.

[GitHub] (https://github.com/cwhitney/ciAnimatedGif) - Gif external library




