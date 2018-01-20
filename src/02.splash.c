/***************************************************************************************************
* splash.c
*
* Created on: Jun 7, 2015, 7:50:39 PM
*     Author: neinome
*
* Synopsis:
*  Shows title screen for game
*
***************************************************************************************************/

// Standard Headers
#include <stdio.h>
#include <windows.h>

// Project Headers
#include "res.h"
#include "states.h"

// Macro Definitions
//#define

// File Type Definitions
//typedef unsigned char ui8

// File Funtions
static inline int nearButtons( int, int );
static void buttonDown( int, int );
static void buttonUp( int, int );

// File Variables
static HBITMAP img = NULL;
static POINT in = { -1, -1 };

// Function definitions
void updSplash( short x, short y, int obj, int wprm, int msg )
{
 switch( msg )
 {
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
 return ( x > 304 && x < 380 ) && ( y > 528 && y < 598 );

}

void buttonDown( int x, int y )
{
 in.x = x;
 in.y = y;
 drwButton( y, press );

}

void buttonUp( int x, int y )
{
 if( y > 528 && y < 552 && in.y > 528 && in.y < 552 )
  state = INITIATE;

 else if( y < 575 && in.y < 575 )
  state = JOIN;

 else if( y < 598 && in.y < 598 )
  state = QUIT;

}

void drwSplash( int drw )
{
 if( !img || drw )
 {
  img = LoadBitmap( hThis, MAKEINTRESOURCE( SPL_TITLE ));

  SelectObject( src, img );
  BitBlt( dest,
          0, 0, 500, 600,
          src,
          0, 0,
          SRCCOPY );

 }
}

void clrSplash()
{
 if( img )
  DeleteObject( img );

}
