#Adventure Game

This project runs a very small "dungeon-crawler-esque" game. The program 
creates a dungeon map by loading in a file that gets stored in as a vector 
of different dungeon rooms, which contain doors, enemies, weapons, and keys 
that the player can interact with.

In order to play the game, simply launch the program through the run 
configuration "start-game," as specified by CMAKE. For whatever reason 
testing is needed, the same applied just with the configuration being 
"test-game."

##The control scheme of the game is as follows:
- Left and Right Arrow Keys shift through the different action button 
  choices accordingly
- The Enter/Return Key selects a button
- The Escape Key exits the sub-panels that can be toggled when selecting a 
  main action button
- The Escape Key also exits the program if the player has not hit enter and 
  selected one of the main action button options
  
##Useful Information
  
The "win condition" of the program is simply to beat the final boss, who is 
named "Dragon."

There are multiple rooms sealed off by locks that can be unlocked using the 
keys picked up around the dungeon. Those areas are completely optional and 
only serve to provide more enemies to fight and special items to collect.

##Closing

Hopefully, this game proves nice to playthrough, even if it is a really 
simple program. Good luck with the dungeon crawling!