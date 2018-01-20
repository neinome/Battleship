/***************************************************************************************************
* windowMan.c
*
* Created on: May 22, 2015, 9:31:14 PM
*     Author: neinome
*
* Synopsis:
*  Manages the program's window.
*
***************************************************************************************************/

// Standard Headers
#include <windows.h>
#include <stdio.h> // debugging

// Project Headers
#include "control.h"
#include "res.h"
#include "states.h"
#include "windowMan.h"

// Macro Definitions
//#define SOME_VALUE_XYZ

// File Type Definitions
//typedef unsigned char ui8;

// File Funtions
extern LRESULT controlProc( HWND, UINT, WPARAM, LPARAM );

// File Variables
static WNDCLASSEX winClass;

HINSTANCE hThis = NULL;
HWND hWin = NULL;
HDC src, dest;

HICON press, unprs;

// Function definitions
int createWindow( void *hThs, int x, int y, int w, int h, char *title )
{
 int toRet = 0;

 hThis = hThs;
 ZeroMemory( &winClass, sizeof( winClass ));
 winClass.cbSize        = sizeof( winClass );
 winClass.hbrBackground = (( HBRUSH ) COLOR_WINDOW + 1 );
 winClass.hCursor       = LoadCursor( NULL, IDC_ARROW );
 winClass.hIcon         = LoadIcon( hThis, MAKEINTRESOURCE( BTTL_ICO ));
 winClass.hInstance     = hThis;
 winClass.lpfnWndProc   = controlProc;
 winClass.lpszClassName = title;
 winClass.style         = CS_HREDRAW | CS_VREDRAW;

 if(( toRet = RegisterClassEx( &winClass )))
 {
  if(!( hWin = CreateWindow( title,
                             title,
                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
                             x, y,
                             w + 6, h + 25,
                             NULL,
                             NULL,
                             winClass.hInstance,
                             NULL )))
  {
   UnregisterClass( title, hThis );
   toRet = 0;

  }

  else
  {
   dest = GetDC( hWin );
   src = CreateCompatibleDC( dest );
   press = (( HICON ) LoadImage( hThis, MAKEINTRESOURCE( BTN_PRESS ), IMAGE_ICON, 75, 23, 0 ));
   unprs = (( HICON ) LoadImage( hThis, MAKEINTRESOURCE( BTN_UNPRS ), IMAGE_ICON, 75, 23, 0 ));

  }
 }

 return toRet;

}

int destroyWindow()
{
 int toRet = 0;

 clrSplash();
 clrInit();
 clrJoin();
 clrLocal();
 clrEnd();

 DeleteObject( press );

 toRet = DeleteDC( dest );
 toRet |= ReleaseDC( hWin, src );

 ShowWindow( hWin, 0 );
 toRet |= DestroyWindow( hWin );
 toRet |= UnregisterClass( winClass.lpszClassName, hThis );

 return toRet;

}

void drwButton( int y, HICON btn )
{
 if( y > 528 && y < 552 )
  y = 529;

 else if( y < 575 )
  y = 552;

 else if( y < 598 )
  y = 575;

 DrawIconEx( src, 305, y, btn, 75, 23, 0, NULL, DI_NORMAL );
 BitBlt( dest,
         0, 0, 500, 600,
         src,
         0, 0,
         SRCCOPY );

}
