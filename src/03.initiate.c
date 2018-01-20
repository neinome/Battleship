/***************************************************************************************************
* initiate.c
*
* Created on: Jun 7, 2015, 4:15:42 PM
*     Author: neinome
*
* Synopsis:
*  TODO: Write SYNOPSIS
*
***************************************************************************************************/

// Standard Headers
#include <stdio.h>
#include <windows.h>
#include <commctrl.h>

// Project Headers
#include "res.h"
#include "states.h"

// Macro Definitions
//#define

// File Type Definitions
// typedef unsigned char ui8

// File Functions
static void createGUI();
static inline int nearButtons( int, int );
static void buttonDown( int, int );
static void buttonUp( int, int );
static void command( int, int );
static void plrCount();

// File Variables
static HBITMAP img = NULL;
static POINT in = { -1, -1 };
static HWND gui[ 3 ]; // 0 - numHumans, 1 - numComps, 2 - compLevel

int nPlyr;
Player *plyr = NULL;

// Function definitions
void updInit( short x, short y, int obj, int wprm, int msg )
{
 switch( msg )
 {
  case WM_COMMAND:
   command( obj, wprm );

  break;
  case WM_LBUTTONDOWN:
   if( nearButtons( x, y ))
    buttonDown( x, y );

  break;
  case WM_LBUTTONUP:
   if( in.x != -1 )
   {
    if( nearButtons( x, y ))
     buttonUp( x, y );

    drwButton( in.y, unprs );
    in.x = in.y = -1;

   }
 }
}

inline int nearButtons( int x, int y )
{
 return ( x > 304 && x < 380 ) && ( y > 551 && y < 598 );

}

void buttonDown( int x, int y )
{
 in.x = x;
 in.y = y;
 drwButton( y, press );

}

void buttonUp( int x, int y )
{
 if( y > 551 && y < 575 && in.y > 551 && in.y < 575 )
  ;

 else if( y > 574 && y < 598 && in.y > 574 && in.y < 598 )
  state = QUIT;

}

void command( int obj, int w )
{
 HWND combo = (( HWND ) obj );
 switch( w )
 {
  case CBN_SELCHANGE:
   if( combo == gui[ 0 ] || combo == gui[ 1 ])
    plrCount();

   else if( combo == gui[ 2 ]) // NOT SURE THAT THIS NEEDS ATTENTION
    ;

 }
}

void plrCount()
{
 int plr = (( int ) SendMessage( gui[ 0 ], CB_GETCURSEL, 0, 0 )),
     ai  = (( int ) SendMessage( gui[ 1 ], CB_GETCURSEL, 0, 0 )),
     maxAI = 8 - plr;

 if( ai > maxAI )
 {
  SendMessage( gui[ 1 ], CB_SETCURSEL, maxAI, 0 );
  ai = maxAI;

 }

 nPlyr = plr + ai;
 EnableWindow( gui[ 2 ], ai );
 EnableWindow( gui[ 1 ], 8 - plr );

}

void drwInit( int drw )
{
 if( !img || drw )
 {
  createGUI();
  img = LoadBitmap( hThis, MAKEINTRESOURCE( SPL_INIT ));

  SelectObject( src, img );
  BitBlt( dest,
          0, 0, 500, 600,
          src,
          0, 0,
          SRCCOPY );

 }
}

void createGUI()
{
 int i, j,
     yPos[ 3 ] = { 144, 222, 300 },
     len[ 3 ] = { 9, 9, 5 },
     str[ 3 ] = { 7, 4, 14 };
 char hum[ 9 ][ 7 ] = { "Humans", "1", "2", "3", "4", "5", "6", "7", "8" },
      ai[ 9 ][ 4 ] = { "AIs", "1", "2", "3", "4", "5", "6", "7", "8" },
      diff[ 5 ][ 14 ] = { "AI Difficulty", "Stupid", "Average", "Intelligent", "Omnipotent" },
      *lib[ 3 ] = {(( char* ) &hum ), (( char* ) &ai ), (( char* ) &diff )};

 for( i = 0; i < 3; i++ )
 {
  gui[ i ] = CreateWindow( WC_COMBOBOX,
                           "",
                           CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                           383, yPos[ i ], 100, 200,
                           hWin, NULL, hThis, NULL);

  for( j = 0; j < len[ i ]; j++ )
   SendMessage( gui[ i ], CB_ADDSTRING, 0, ( LPARAM )((( char* ) lib[ i ]) + ( j * str[ i ])));

  SendMessage( gui[ i ], CB_SETCURSEL, 0, 0 );

 }
 EnableWindow( gui[ 2 ], FALSE );

}

void clrInit()
{
 if( img )
  DeleteObject( img );

}
