/***************************************************************************************************
* windowMan.h
*
* Created on: May 22, 2015, 9:22:53 PM
*     Author: neinome
*
* Synopsis:
*  Offers an interface for communicating with the Window Manager
*
***************************************************************************************************/

#ifndef SRC_WINDOWMAN_H_
#define SRC_WINDOWMAN_H_

// Creates a window with the specified parameters.
//  INPUTS:
//   ProgramHandle: HINSTANCE received at WinMain as the program's handle.
//       xPosition: X position on screen of the window.
//       yPosition: Y position on screen of the window.
//           width: intended width of the window to create.
//          height: intended height of the window to create.
//     windowTitle: string label for the title bar of the window.
//  RETURNS:
//       0: Function terminated normally, window should be showing.
//   NOT 0: Function failed to produce the window (debugging condition only)
int createWindow( void *ProgramHandle,
                  int xPosition,
                  int yPosition,
                  int width,
                  int height,
                  char *windowTitle );

// Destroys the resources associated with the window in preparation to exit
int destroyWindow();

#endif /* SRC_WINDOWMAN_H_ */
