#define MAX_CHARS_IN_DICTIONARY_WORD 32
#define BIG_BOGGLE 1										//Change this to 0, if we want a 4 x 4 boggle board.
#define SIDES_IN_DICE 6
#define START_CHAR 'A'
#define END_CHAR 'Z'
#define MAX_CHARS_IN_A_WORD 4

#if BIG_BOGGLE
#define NUM_ROWS 5
#define NUM_COLS 5
#else
#define NUM_ROWS 4
#define NUM_COLS 4
#endif
#define NUM_DICE (NUM_ROWS * NUM_COLS)
#define MAX_WORDS_FOUND 300

#define FILENAME_DICTIONARY "../AppData/Dictionary.txt"
#define INPUT_NEEDED_TO_CONTINUE 1							//If this is set to 1, then the program will print Random boggle boards, search for the words present in that board and print them. The program will Exit after the user enters 'q'
#define NUM_GAMES_TO_AVERAGE 1000							//For this to work, set INPUT_NEEDED_TO_CONTINUE = 0, DEBUG_PRINTING_ON = 0 and AVERAGE_PRINTING_ON = 1. The program will now print the average search time for searching words in the 'NUM_GAMES_TO_AVERAGE' random boggle boards.
#define DEBUG_PRINTING_ON 1									//If this is set to 1, then the program will print the Boggle board and the searched words.
#define AVERAGE_PRINTING_ON 1								//If this is set to 1, then the program prints the average search time for searching words in the 'NUM_GAMES_TO_AVERAGE' random boggle boards.