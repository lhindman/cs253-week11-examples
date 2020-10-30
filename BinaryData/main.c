#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define BOARD_DIM 8
#define MAX_NAME_LENGTH 40

struct game_state {
   char playerName[MAX_NAME_LENGTH];
   int numMoves;
   int gameBoard[BOARD_DIM][BOARD_DIM];
};
typedef struct game_state GameState;

void printGameState(GameState gs) {
   fprintf(stdout,"-----------------------\n");
   fprintf(stdout," Player Name: %s\n", gs.playerName);
   fprintf(stdout," Moves Made: %d\n", gs.numMoves);
   fprintf(stdout,"----- Game Board ------\n");

   for (int i = 0; i < BOARD_DIM; i++) {
      for (int j = 0; j < BOARD_DIM; j++) {
         fprintf(stdout,"%2d ",gs.gameBoard[i][j]);
      }
      fprintf(stdout,"\n");
   }
}


int main(void) {

   srand(time(0));
   FILE * savedGameState;

   /* Setup a GameState struct for a fake game */
   GameState theGame;
   strncpy(theGame.playerName,"The Rock",MAX_NAME_LENGTH);
   theGame.numMoves = rand() % 256;

   for (int i = 0; i < BOARD_DIM; i++) {
      for (int j = 0; j < BOARD_DIM; j++) {
         theGame.gameBoard[i][j] = rand() % 2;
      }
   }

   printGameState(theGame);

   /* Similar to how we can use the stdin, stdout and stderr FILE streams
    *   to read from and write to the console, we can also create our
    *   own FILE streams to fread from and write to files.
    */

   errno = 0;
   savedGameState = fopen("gamesave.dat", "w");

   if(savedGameState == NULL) {
      fprintf(stderr,"fopen: errno set to %d\n", errno);
      perror("fopen");
      exit(1);
   }

   /* Write the current GameState to file */
   size_t itemCount = 0;
   itemCount = fwrite(&theGame,sizeof(GameState),1,savedGameState);
   fflush(savedGameState);
   fclose(savedGameState);
   if(itemCount == 1) {
      fprintf(stdout,"The GameState was successfully saved to disk\n");
   } else {
      fprintf(stderr,"ERROR: An error occurred while saving GameState to disk!\n");
   }


   /*------------------------------ Restore Game State -------------------------------*/
   errno = 0;
   savedGameState = fopen("gamesave.dat", "r");

   if(savedGameState == NULL) {
      fprintf(stderr,"fopen: errno set to %d\n", errno);
      perror("fopen");
      exit(1);
   }

   GameState restoredGame;
   itemCount = 0;
   itemCount = fread(&restoredGame, sizeof(GameState), 1, savedGameState);

   if (itemCount == 1) {
      fprintf(stdout,"The GameState was successfully restored from disk\n");
      printGameState(restoredGame);
   } else {
      fprintf(stderr,"ERROR: An error occurred while restoring GameState from disk!\n");
   }

   


   return 0;
}
