/***************************************************************************************************
* states.h
*
* Created on: Jun 7, 2015, 4:19:42 PM
*     Author: neinome
*
* Synopsis:
*  Gives a clean interface to the updating functionality and drawing instructions for the game
*  states. All updates require the x and y coordinates of the mouse to be passed to them in order
*  to proceed.
*
***************************************************************************************************/

#ifndef SRC_STATES_H_
#define SRC_STATES_H_

// Game state information
typedef enum
{
 QUIT     = -1,
 SPLASH   =  0,
 INITIATE =  1,
 JOIN     =  2,
 CONNECT  =  3,
 PLACE    =  4,
 LOCAL    =  5,
 REMOTE   =  6,
 CPU      =  7,
 END      =  8

} gameState;

typedef struct
{
 int playr;             // player number
 int color;             // player's color code
 int update;            // update function pointer index
 char *ppi[ 10 ][ 10 ]; // boards of the other players
 char flt[ 10 ][ 10 ];  // owned fleet

} Player;

#define NUM_STATES 9

extern gameState state;

extern HINSTANCE hThis;
extern HWND hWin;
extern HDC src, dest;
extern HICON press, unprs;

extern int nPLyr;
extern Player *plyr;

// TODO: ADD NETMAN EXTERN VARIABLES
//extern

// Helper function that draws buttons
void drwButton( int, HICON );

// Update and draw functions for the title portion of the game.
void updSplash( short x, short y, int obj, int wprm, int msg );
void drwSplash( int forceDraw );
void clrSplash();

// Update and draw functions for creation phase.
void updInit( short x, short y, int obj, int wprm, int msg );
void drwInit( int forceDraw );
void clrInit();

// Update and draw functions for join phase.
void updJoin( short x, short y, int obj, int wprm, int msg );
void drwJoin( int forceDraw );
void clrJoin();

// Update and draw functions for connection phase.
void updCnct( short x, short y, int obj, int wprm, int msg );
void drwCnct( int forceDraw );
void clrCnct();

// Update and draw functions for the placement portion of the game.
void updPlace( short x, short y, int obj, int wprm, int msg );
void drwPlace( int forceDraw );
void clrPlace();

// Update and draw functions for the local player's turn of the game.
void updLocal( short x, short y, int obj, int wprm, int msg );
void drwLocal( int forceDraw );
void clrLocal();

// Update and draw functions for a network player's turn during the game.
void updRemote( short x, short y, int obj, int wprm, int msg );
void drwRemote( int forceDraw );

// Update and draw functions for the CPU's turn during the game.
void updCPU( short x, short y, int obj, int wprm, int msg );
void drwCPU( int forceDraw );

// Update and draw functions for the end portion of the game.
void updEnd( short x, short y, int obj, int wprm, int msg );
void drwEnd( int forceDraw );
void clrEnd();

#endif /* SRC_STATES_H_ */
