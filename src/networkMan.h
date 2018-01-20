#ifndef netMan
#define netMan

#define NM_NETWORK 0

HWND hView;
HWND hList;

void startSrvrCon( HWND, unsigned short );
void end();
void procNet( HWND, WORD );

#endif
