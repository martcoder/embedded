// Declarations
#define BUFFSIZE 128
void blockSine(short *buf, int len);
// Global Variables
static short gBuffer[BUFFSIZE];
// ======== main ========
// Simple function which calls blockSine
void main()
{
	blockSine(gBuffer, BUFFSIZE); // Fill buffer with sine data
return;
}
