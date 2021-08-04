/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

#include <pspkernel.h>
#include <stdio.h>
#include <string.h>

//#include "depack.h"

PSP_MODULE_INFO("PBP_DEPACK", 0x0, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

void getOffsets(FILE *pbp, int position, long int *pointerStart, long int *pointerEnd)
{
	char buffer[4] = { '\0' };
	int a, b, c, d;
	
	a = b = c = d = 0;
		
	fseek(pbp, position, SEEK_SET);
	fgets(buffer, 4, pbp);
	a = buffer[0];
	b = buffer[1];
	c = buffer[2];
	d = buffer[3];
		
	*pointerStart += a;
	*pointerStart += (b+1)*256;
	*pointerStart += (unsigned long int)c*256*256;
	*pointerStart += (unsigned long int)d*256*256*256;
	
	a = b = c = d = 0;
		
	fseek(pbp, position+4, SEEK_SET);
	fgets(buffer, 4, pbp);
	a = buffer[0];
	b = buffer[1];
	c = buffer[2];
	d = buffer[3];
		
	*pointerEnd += a;
	*pointerEnd += (b+1)*256;
	*pointerEnd += (unsigned long int)c*256*256;
	*pointerEnd += (unsigned long int)d*256*256*256;
}

int module_start(SceSize args, void *argp)
{
	return 0;
}

int module_stop(void)
{
	return 0;
}
