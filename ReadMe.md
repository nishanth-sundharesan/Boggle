# Boggle

### Description:  

The basic rules of the Boggle game can be understood from the video https://www.youtube.com/watch?v=4TsvAfukeS8  

The program creates a Boggle game board randomly out of the dices present in the file "Dice.h". The game can have a 4x4 or a 5x5 board, switchable by the "#define BIG_BOGGLE" present in the file "Boggle.h". 
The position of the dice as well as the letter facing up on the die are randomized. After creating the Boggle board, the program then finds all the words present in the board. An exhaustive list of the approved words is present in the file "Dictionary.txt" which is present in the folder "Boggle\AppData". 
The minimum word length is 4. All the words shorter than 4 letters in length are not considered. Also, the letter 'Q' is treated as 'Qu'.  

This was part of the assignment at FIEA.

The program currently displays the randomly generated board, words found in that board and the time it took to search for those words.

To print the average time the program took to search the words for 'n' number of boards/games.  

1. Set the #define "INPUT_NEEDED_TO_CONTINUE" to 0.  
2. Set the number of games in the #define "NUM_GAMES_TO_AVERAGE".  
3. Set the #define "DEBUG_PRINTING_ON" to 0.  
4. Set the #define "AVERAGE_PRINTING_ON" to 1.  

All these #defines are present in the file "Boggle.h"