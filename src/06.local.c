/***************************************************************************************************
* local.c
*
* Created on: Jun 7, 2015, 4:17:01 PM
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
void updLocal( short x, short y, int obj, int wprm, int msg )
{
 ;

}

void drwLocal( int drw )
{
 ;

}

void clrLocal()
{
 if( img )
  DeleteObject( img );

}
