#define MAX_CHARS_IN_DICTIONARY_WORD 32
#define BIG_BOGGLE 1
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
#define INPUT_NEEDED_TO_CONTINUE 0
#define NUM_GAMES_TO_AVERAGE 1000
#define DEBUG_PRINTING_ON 0
#define AVERAGE_PRINTING_ON 1


