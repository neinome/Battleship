/***************************************************************************************************
* control.c
*
* Created on: May 10, 2015, 9:15:49 PM
*     Author: neinome
*
* Synopsis:
*  Does stuff.
*  Function pointers make doing things easy.
*  Seriously trivial section of the code when done correctly.
*  Seriously MESSY code when done poorly.
*
***************************************************************************************************/

// Standard Headers
#include <time.h>
#include <windows.h>
#include <stdio.h> // for debugging

// Project Headers
#include "control.h"
#include "res.h"
#include "states.h"

// Macro Definitions
//#define foo bar

// File Type Definitions
// typedef unsigned int uint;

// File Functions
extern int destroyWindow( BOOL );

// File Variables
static void ( *update[ NUM_STATES ])( short, short, int, int, int ) = { &updSplash,
                                                                        &updInit,
                                                                        &updJoin,
                                                                        &updPlace,
                                                                        &updLocal,
                                                                        &updRemote,
                                                                        &updCPU,
                                                                        &updEnd };
static void ( *draw[ NUM_STATES ])( int ) = { &drwSplash,
                                              &drwInit,
                                              &drwJoin,
                                              &drwPlace,
                                              &drwLocal,
                                              &drwRemote,
                                              &drwCPU,
                                              &drwEnd };

gameState state = SPLASH;

// Function definitions
void run()
{
 MSG msg;

 int st = clock(), clk, cpf = CLOCKS_PER_SEC / 60;

 while( state != QUIT )
 {
  clk = clock();

  if( clk - st >= cpf )
  {
   st += cpf;
   draw[ state ]( 0 );

  }

  if( PeekMessage( &msg, NULL, 0, 0, 1 ))
  {
   TranslateMessage( &msg );
   DispatchMessage( &msg );

  }
 }
}

LRESULT controlProc( HWND hThs, UINT msg, WPARAM w, LPARAM l )
{
 LRESULT toRet = 0;
 short *xy = (( short* ) &l );

 if( state == CPU || state == REMOTE )
 {
  update[ state ]( xy[ 0 ], xy[ 1 ], l, HIWORD( w ), msg );
  if( msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_RBUTTONUP )
   msg = WM_MOUSEWHEEL;

 }

 switch( msg )
 {
  case WM_CLOSE:
   state = QUIT;

  break;
  case WM_LBUTTONDOWN:
  case WM_RBUTTONDOWN:
  case WM_LBUTTONUP:
  case WM_RBUTTONUP:
  case WM_MOUSEMOVE:
  case WM_COMMAND:
   update[ state ]( xy[ 0 ], xy[ 1 ], l, HIWORD( w ), msg );

  break;
  default:
   toRet = DefWindowProc( hThs, msg, w, l );

 }

 return toRet;

}
/*
   doMouseClick( msg, l );

  break;
  case WM_COMMAND:
   if( HIWORD( w ) == CBN_SELCHANGE )
   {
    if( l == (( long long ) gui[ 0 ]))
      enablePlayers();

    if( l == (( long long ) gui[ 1 ]) ||
        l == (( long long ) gui[ 2 ]) ||
        l == (( long long ) gui[ 3 ]) ||
        l == (( long long ) gui[ 4 ]) ||
        l == (( long long ) gui[ 5 ]) ||
        l == (( long long ) gui[ 6 ]) ||
        l == (( long long ) gui[ 7 ]) ||
        l == (( long long ) gui[ 8 ]))
    {
      setupPlayers();
      enableColors();

    }

    if( l == (( long long ) gui[  9 ]) ||
        l == (( long long ) gui[ 10 ]) ||
        l == (( long long ) gui[ 11 ]) ||
        l == (( long long ) gui[ 12 ]) ||
        l == (( long long ) gui[ 13 ]) ||
        l == (( long long ) gui[ 14 ]) ||
        l == (( long long ) gui[ 15 ]) ||
        l == (( long long ) gui[ 16 ]))
      validateColors(( HWND ) l );

  }
  break;
  default:
   toRet = DefWindowProc( hThs, msg, w, l );

 }

 return toRet;

}

void doMouseClick( UINT msg, LPARAM l )
{
 if( msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP )
  update[ state ]( l & 0x0000FFFF, l >> 16 );

 else if(( msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP ) && state == PLACE )
  rotate();

}
*/
