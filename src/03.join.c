/***************************************************************************************************
* join.c
*
* Created on: Jun 7, 2015, 4:16:32 PM
*     Author: neinome
*
* Synopsis:
*  This program initiates connections between the server and clients. For the server, the clients
*  are stored and information passed to the server is stored and distributed to relevant parties.
*
***************************************************************************************************/

// Standard Headers
#include <stdio.h>
#include <windows.h>
#include <commctrl.h>

// Project Headers
#include "control.h"
#include "res.h"
#include "states.h"

// Macro Definitions
//#define

// File Type Definitions
//typedef unsigned char ui8

// File Functions
static void createGUI();
static inline int nearButtons( int, int );
static void buttonDown( int, int );
static void buttonUp( int, int );
static void command( int, int );
static void ipValidate( HWND );
static void portValidate( HWND );

// File Variables
static HBITMAP img = NULL;
static POINT in = { -1, -1 };
static HWND gui[ 5 ]; // IP gui[ 0 ].gui[ 1 ].gui[ 2 ].gui[ 3 ]:gui[ 4 ]

// Function definitions
void updJoin( short x, short y, int obj, int wprm, int msg )
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
 HWND edit = (( HWND ) obj );

 switch( w )
 {
  case EN_KILLFOCUS:
   if( edit == gui[ 0 ] || edit == gui[ 1 ] ||
       edit == gui[ 2 ] || edit == gui[ 3 ])
    ipValidate( edit );

   else if( edit == gui[ 4 ])
    portValidate( edit );

 }
}

void ipValidate( HWND val )
{
 char buf[ 4 ] = { 0 };
 int num;

 GetWindowText( val, buf, 4 );
 num = atoi( buf );

 if( num > 255 )
  num = 255;

 itoa( num, buf, 10 );
 SetWindowText( val, buf );

}

void portValidate( HWND val )
{
 char buf[ 6 ] = { 0 };
 int num;

 GetWindowText( val, buf, 6 );
 num = atoi( buf );

 if( num < 1024 )
  num = 1024;

 else if( num > 65535 )
  num = 65535;

 itoa( num, buf, 10 );
 SetWindowText( val, buf );

}

void drwJoin( int drw )
{
 if( !img || drw )
 {
  createGUI();
  img = LoadBitmap( hThis, MAKEINTRESOURCE( SPL_JOIN ));

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
 int i,
     xPos[ 5 ] = { 240, 271, 302, 333, 240 },
     yPos[ 5 ] = { 183, 183, 183, 183, 223 },
     len[ 5 ] = { 30, 30, 30, 30, 50 };

 for( i = 0; i < 5; i++ )
 {
  gui[ i ] = CreateWindow( WC_EDIT,
                           "",
                           ES_NUMBER | ES_CENTER | WS_CHILD | WS_VISIBLE | WS_THICKFRAME,
                           xPos[ i ], yPos[ i ], len[ i ], 22,
                           hWin, NULL, hThis, NULL);
  SendMessage( gui[ i ], EM_SETLIMITTEXT, len[ i ]/ 10, 0 );

  if( i < 4 )
   SetWindowText( gui[ i ], "0" );

 }
 SetWindowText( gui[ 4 ], "27274" );

}

void clrJoin()
{
 if( img )
  DeleteObject( img );

}
