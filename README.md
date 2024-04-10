# UIUC-CS-126-Final-Project
Cinder C++ project that recreates an adventure RPG project from earlier in the semester for CS 126 at UIUC.

This Cinder C++ project was my final submission for the CS 126 final project at UIUC. This assignment was conducted over the course of about a month. For this assignment, I received a grade of 96.92%, which can be seen in the Grade Screenshot as well as my grades for the other stages of the project.

Disclaimer: The final allowable submission date has long passed, so the ability to use this code to submit the assignment for a grade in the semester of Spring 2021 has similarly passed. I do not condone usage of this project for the purposes of cheating if this exact type of project assignment is to be re-used in future iterations of CS 126 at the University of Illinois at Urbana-Champaign.

Below is the original README used when the project was submitted for grading.

# Adventure Game

This project runs a very small "dungeon-crawler-esque" game. The program 
creates a dungeon map by loading in a file that gets stored in as a vector 
of different dungeon rooms, which contain doors, enemies, weapons, and keys 
that the player can interact with.

In order to play the game, simply launch the program through the run 
configuration "start-game," as specified by CMAKE. For whatever reason 
testing is needed, the same applied just with the configuration being 
"test-game."

## The control scheme of the game is as follows:
- Left and Right Arrow Keys shift through the different action button 
  choices accordingly
- The Enter/Return Key selects a button
- The Escape Key exits the sub-panels that can be toggled when selecting a 
  main action button
- The Escape Key also exits the program if the player has not hit enter and 
  selected one of the main action button options
  
## Useful Information
  
The "win condition" of the program is simply to beat the final boss, who is 
named "Dragon."

There are multiple rooms sealed off by locks that can be unlocked using the 
keys picked up around the dungeon. Those areas are completely optional and 
only serve to provide more enemies to fight and special items to collect.

## Closing

Hopefully, this game proves nice to playthrough, even if it is a really 
simple program. Good luck with the dungeon crawling!
