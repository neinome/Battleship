/***************************************************************************************************
* main.c
*
* Created on: May 10, 2015, 9:13:28 PM
*     Author: neinome
*
* Synopsis:
*  Battleship game project.
*  Started in 2004, still not completed.
*  Fifth attempt to complete.
*  Let's see how far it goes this time. >_>;
*
***************************************************************************************************/

// Standard Headers
#include <windows.h>

// Project Headers
#include "control.h"
#include "windowMan.h"

// Macro Definitions
//#define

// File Type Definitions
//typedef unsigned char ui8

// File Funtions
//static int foo( char );

// File Variables
// static int bar;

// Function definitions
int WinMain( HINSTANCE hThis,
             HINSTANCE hNull,
             LPSTR cmdArgs,
             int show )
{
 if( createWindow( hThis, CW_USEDEFAULT, CW_USEDEFAULT, 500, 600, "Battleship" ))
  run();

 destroyWindow();

 return 0;

}
