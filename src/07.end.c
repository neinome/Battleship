/***************************************************************************************************
* end.c
*
* Created on: Jun 7, 2015, 4:18:11 PM
*     Author: neinome
*
* Synopsis:
*  TODO: Write SYNOPSIS
*
***************************************************************************************************/

// Standard Headers
#include <windows.h>

// Project Headers
#include "states.h"

// Macro Definitions
//#define

// File Type Definitions
//typedef unsigned char ui8

// File Funtions
//static int foo( char );

// File Variables
static HBITMAP img = NULL;

// Function definitions
void updEnd( short x, short y, int obj, int wprm, int msg )
{
 ;

}

void drwEnd( int drw )
{
 ;

}

void clrEnd()
{
 if( img )
  DeleteObject( img );

}
