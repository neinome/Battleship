/***************************************************************************************************
* networkMan.c
*
* Created on: Apr 18, 2013, 2:01:XX PM
*     Author: neinome
*
* Synopsis:
*  This program initiates connections between the server and clients. For the server, the clients
*  are stored and information passed to the server is stored and distributed to relevant parties.
*
***************************************************************************************************/

/* Standard headers */
#include <stdio.h>
#include <winsock2.h>

/* Project headers */
#include "control.h"
#include "networkMan.h"

/* Function prototype */
void acceptClnt();
void killCon( int );
void recvData();
void sendData();
void updateClients();

/* File variables */
#define MAX_CLNTS 7

typedef struct sockaddr sockaddr;

typedef union
{
 SOCKADDR_IN sinAddr;
 sockaddr    saddr;

} sAddr;

typedef struct
{
 WORD sockVer;
 WSADATA data;
 SOCKET sock[ MAX_CLNTS ], lstn;
 HOSTENT *host;
 sAddr addr;

} Sock;

char sbuf[ 50 ];
char gbuf[ MAX_CLNTS ][ 50 ];
int clients;
HANDLE hRun;
HANDLE hSys;
Sock sock;

/* File functions */
void startSrvrCon( HWND hWnd, ushrt port )
{
 memset( sbuf, 0, 50 );
 memset( gbuf, 0, MAX_CLNTS * 50 );

 sock.sockVer = MAKEWORD( 2, 0 );
 WSAStartup( sock.sockVer, &sock.data );
 sock.addr.sinAddr.sin_addr.s_addr = INADDR_ANY;
 sock.addr.sinAddr.sin_family = AF_INET;
 sock.addr.sinAddr.sin_port   = htons( port );
 sock.lstn = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

 bind( sock.lstn, &sock.addr.saddr, sizeof( sockaddr ));
 WSAAsyncSelect( sock.lstn, hWnd, NM_NETWORK, 9 );
 listen( sock.lstn, MAX_CLNTS );
 SendMessage( hView,
              EM_REPLACESEL,
              0,
              (( LPARAM ) "Waiting for clients...\r\n" ));

}

void end()
{
 int i;

 for( i = clients; clients > 0; i--, clients-- )
  closesocket( sock.sock[ clients ]);

 WSACleanup();

}

void procNet( HWND hWnd, WORD msg )
{
 switch( msg )
 {
  case FD_ACCEPT:
   acceptClnt();

  break;

  case FD_READ:
   recvData();

  break;

 }
}

void acceptClnt()
{
 if( clients < MAX_CLNTS )
 {
  sock.sock[ clients ] = accept( sock.lstn, NULL, NULL );
  clients++;

 }
}

void recvData()
{
 int i, bts;

 for( i = 0; i < clients; i++ )
 {
  bts = recv( sock.sock[ i ], gbuf[ i ], 50, 0 );

  if( gbuf[ i ][ 0 ] == 0x1A &&
      gbuf[ i ][ 1 ] == 0x04 &&
      gbuf[ i ][ 2 ] == 0x1A )
   killCon( i );

  else if( bts > 0 )
   sendData();

  memset( gbuf[ i ], 0, 50 );

 }
}

void sendData()
{
 int i;

 for( i = 0; i < clients; i++ )
 {
  if( send( sock.sock[ i ], sbuf, 50, 0 ) < 0 )
  {
   if( WSAGetLastError() != WSAEWOULDBLOCK )
    killCon( i-- );

  }
 }

 memset( sbuf, 0, 50 );

}

void killCon( int index )
{
 SOCKET temp = sock.sock[ index ];

 clients--;

 sock.sock[ index ] = sock.sock[ clients ];
 sock.sock[ clients ] = 0;

 shutdown( temp, SD_BOTH );
 closesocket( temp );

}

/*
0x03 - END OF TEXT                 EX
0x04 - END OF TRANSMISSION         ET
0x06 - ACKNOWLEDGE                 AK
0x0A - LINE FEED                   LF
0x0C - FORM FEED                   FF
0x0D - CARRIAGE RETURN             CR
0x10 - DATA LINK ESCAPE            DS
0x17 - END OF TRANSMISSION BLOCK   EB
0x19 - END OF MEDIUM               EM
0x1B - ESCAPE                      ES
0x1C - FILE SEPARATOR              FS
0x1D - GROUP SEPARATOR             GS
0x1E - RECORD SEPARATOR            RS
0x1F - UNIT SEPARATOR              US
*/
