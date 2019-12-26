#include <ctype.h>
#include <math.h>
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
Main function is to roll N numbered dice as many times as the user wants.
There is an option to add players names such that players can track which roll belongs to whom.

Creator: fsport
Last modified: 2019-06-05
*/

#define DICE_SIDES 6

// structs
struct ThePlayers {
    int numberPlayers;
    char playerNames[10][100];
};

struct Histogram {
    int arraySize;
    int histogramArray[10000];
};

struct Options {
    int histogramOn;
};

// function that CAPITALIZES user input
// https://stackoverflow.com/questions/26327812/strupr-and-strlwr-in-string-h-part-are-of-the-ansi-standard/26328095#26328095
char* strupr(char* s) {
    char* tmp = s;

    for (;*tmp;++tmp) {
        *tmp = toupper((unsigned char) *tmp);
    }
    return s;
}

// Initializes program by printing header
void init() {
    srand(time(NULL));

    printf("\n");
    printf(" ==============================================================================\n");
    printf("|                                                                              |\n");
    printf("|                           THE ULTIMATE DICE ROLLER                           |\n");
    printf("|                                                                              |\n");
    printf(" ==============================================================================\n");
}

void printPlayers(struct ThePlayers* players) {
    int i = 0;
    for (i = 0; i < players->numberPlayers; i++) {
        printf("Player %s's Turn!\n", players->playerNames[i]);
    }
}

// Reads N names and stores them in an array
void addPlayers(struct ThePlayers* players) {
    int i = 0;
    char yesNo;
    players->numberPlayers = 0;

    printf(" Do you want to add players to this session? [y/n] ");
    scanf("%c", &yesNo);

    if (yesNo == 'y' || yesNo == 'Y') {
        printf(" How many players? ");

        while (scanf("%d", &players->numberPlayers) != 1) {   // checks if number of players user wants is an integer
            getchar();                                      // discard user input since its not an integer and prompt again
            printf(" That's not a number...think about your life choices and try again.\n");
        }

        // players->playerNames[players->numberPlayers];
        printf(" Enter %d player names in the order of play.\n", players->numberPlayers);
        players->playerNames[players->numberPlayers][100];
        for (i = 0; i < players->numberPlayers; i++) {
            scanf("%s", players->playerNames[i]);
        }
        printf("\n");

        //print out players after user enters names
        printf("  =============================================\n");
        printf("  Player Order:                                \n");
        printf("  ---------------------------------------------\n");
        for (i = 0; i < players->numberPlayers; i++) {
            printf("  Player %d: %s                            \n", i+1, strupr(players->playerNames[i]));
        }
        printf("  =============================================\n");
    }

    else if (yesNo == 'n' || yesNo =='N') {
        //do nothing
    }

    else {
        printf(" User input error...bye.\n");
        exit(-1);
    }
}

void enableHistogram(struct Options* optionSettings) {
    char yesNoHistogram;
    optionSettings->histogramOn = 0;

    printf("\n Show histogram after each roll? [y/n] ");
    while(1) {
        scanf("%c", &yesNoHistogram);
        if (yesNoHistogram == 'n' || yesNoHistogram == 'N') {
            break;
        }
        else if (yesNoHistogram == 'y' || yesNoHistogram == 'Y') {
            optionSettings->histogramOn = 1;
            break;
        }
    }
    printf("\n");
}

void numberOfDiceToRoll(struct Histogram* hist, struct ThePlayers* players, struct Options* optionSettings) {
    int i = 0, j = 0, k = 0, m = 0;
    int sum = 0, 
        rollResult = 0,
        sumCounter = 0, 
        playerCounter = 0, 
        whoseTurn = 0,
        numberOfDiceToRoll = 0, 
        keypress = 0;

    printf(" How many dice do you want to roll? ");
    
    while (scanf("%d", &numberOfDiceToRoll) != 1) {       // checks if number of dice user wants to roll is an integer
        getchar();                                      // discard user input since its not an integer and prompt again
        printf(" That's not a number...try again.\n");
    }
    printf("\n");

    hist->arraySize = DICE_SIDES*numberOfDiceToRoll;
    hist->histogramArray[hist->arraySize];

    for (i = 0; i < hist->arraySize; i++) {
        hist->histogramArray[i] = 0;                    // set all elements in new histogram to zero
    }

    getchar(); // throw previous enter after number of dice is entered
    printf(" Press ENTER to roll %d dice.\n", numberOfDiceToRoll);
    char input = scanf("%lc", &keypress);

    while (input != EOF) {
        if (keypress == '\n' || keypress == ' ') { // can also use getchar()
            printf(" ---------------------------------------------\n");

            for (j = 0; j < numberOfDiceToRoll; j++) {
                rollResult = rand()%DICE_SIDES+1;
                printf("   Dice %d:\n", j+1);

                printf("    _____\n");
                printf("   |     |\n");
                printf("   |  %d  |\n", rollResult);
                printf("   |_____|\n\n");
                sum += rollResult;
            }
            printf(" #############################################\n");

            if (players->numberPlayers != 0) {
                whoseTurn = playerCounter % players->numberPlayers;
                printf(" ROUND %d                      Player: %s\n", (int)floor(playerCounter/players->numberPlayers)+1, strupr(players->playerNames[whoseTurn]));
/*
                // For testing purposes only
                // printf("playercounter: %d\n", playerCounter);
                // printf("mod calc: %d\n", whoseTurn);
                // printf("player array size: %d\n", players->numberPlayers);
                // players->playerNames[whoseTurn] = toupper(players->playerNames[whoseTurn]);
                // printf("          %s's turn:\n", strupr(players->playerNames[whoseTurn]));
*/                
                printf(" =============================================\n");
                playerCounter++;
            }

            printf("                Roll total: %d    \n", sum);
            printf(" #############################################\n");

            //add sum to histogram array
            sumCounter = sum;
            hist->histogramArray[sumCounter-1]++;   // minus 1 since if 2 dice, index = 0 to 11
            sum = 0;
            printf("\n");

            // print histogram after each roll if histogramOn is enabled
            if (optionSettings->histogramOn == 1) {
                for (k = 0; k < hist->arraySize; k++) {
                    printf("        [%2d]: \t", k+1);

                    for (m = 0; m < hist->histogramArray[k]; m++) {
                        printf("#");
                    }
                    printf("\n");
                }
            }
        }

        // exit program if user types "exit" and hits enter
        else if (keypress == 'Q') {    // '033' is ascii for esc, try k = 27
            break;
        }

        printf("\n Press ENTER to roll %d dice again.\n", numberOfDiceToRoll);
        printf(" (Q To END GAME)\n");

        input = scanf("%lc", &keypress);
    }
}

void printHistogram(struct Histogram* hist) {
    int i = 0, total = 0, longestResult = 100;
    double percentage = 0;

    printf("\n ------------------GAME OVER------------------\n");
    printf("\n =============================================\n");
    printf("          Mathifying some statistics...\n");
    printf(" =============================================\n");
    printf("\n");
    sleep(1);

    // calculates total number of rolls made this session
    for (i = 0; i < hist->arraySize; i++) {
        total += hist->histogramArray[i];
    }

    // Shows number of times each result has been rolled over entire game.
    for (i = 0; i < hist->arraySize; i++) {
        // total += hist->histogramArray[i];
        percentage = ((double)hist->histogramArray[i]/(double)total)*100;
        printf("     Number of [%2d]'s rolled = %3d  (%4.1f%%) \n", i+1, hist->histogramArray[i], percentage);
    }

/*  
    // This section was used to print hashes (#) at the end of program to display an
    // end game histrogram. Decided to show number of each roll result instead.

    for (i = 0; i < hist->arraySize; i++) {
        total += hist->histogramArray[i];
    }
    
    for(int j = 1; j < hist->arraySize; j++){
        printf("             Number of [%d]: \t", j+1);

        for (int k = 0; k < hist->histogramArray[j]; k++){
            printf("#");
        }
        printf("\n");

        // Prints histogram based on ratio instead of one hash for each roll result
        // for (int k = 0; k < (longestResult*hist->histogramArray[j])/total; k++){
        //     printf("#");
        // }
        // printf("\n");
    }
*/

    printf("\n         Total rolls this game: %d\n", total);
    printf("\n =============================================\n");
}

int exitProg(int exitCondition) {
    char lastInput, lastPress;
    while(1) {
        printf(" Press 'R' to restart or 'Q' to exit program\n");
        scanf("%c", &lastPress);
        if (lastPress == 'R') {
            getchar();
            break;
        }
        else if (lastPress == 'Q') {
            exitCondition = false;
            getchar();
            return 0;
        }
    }
    return 1;
}

int main() {
    struct ThePlayers   players;
    struct Options      optionSettings;
    struct Histogram    hist;

    int exitCondition = true;                   // enables program to run indefinately until func call exitProg and user quits

    while(exitCondition) {
        // Initialize srand and start program
        init();

        // Ask for if players should be added
        addPlayers(&players);

        // Ask if histogram after roll should be enabled
        enableHistogram(&optionSettings);

        // Ask for number of dice to roll
        numberOfDiceToRoll(&hist, &players, &optionSettings);

        // Ending program: When Q is pressed in numberOfDiceToRoll()
        printHistogram(&hist);
   
        getchar();                              // throw away last input so it doesn't affect the next input request

        if (exitProg(exitCondition) == 0) {      // exitProg returns 0 means exitCondition changed to false so program exits successfully
            break;
        }
    }
    return 0;
}

