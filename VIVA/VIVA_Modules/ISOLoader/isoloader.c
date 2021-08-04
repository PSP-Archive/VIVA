/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

#include <pspkernel.h>
#include <pspsdk.h>
#include <pspumd.h>
#include <string.h>
#include <stdio.h>

#include "k/k.h"

#include "../include/systemctrl_se.h"
#include "../include/systemctrl.h"

PSP_MODULE_INFO("ISO-Loader", 0x0002, 1, 0);

int loadUMD()
{	
	struct SceKernelLoadExecVSHParam param;
	char location[256];
	
	sprintf(location, "disc0:/PSP_GAME/SYSDIR/EBOOT.BIN");
	
	memset(&param, 0, sizeof(param));
	param.size = sizeof(param);
	param.args = strlen(location) + 1;
	param.argp = location;
	param.key = "game";
	
	sctrlKernelLoadExecVSHWithApitype(0x120, location, &param); //0x120 = UMD
	return 1;
}

int loadISO(char *fileName)
{
	SEConfig config;
	
	SetUmdFile(fileName);
	sctrlSEGetConfigEx(&config, sizeof(config));
	
	if(config.umdmode == MODE_MARCH33)
	{
		SetConfFile(1);
	}
	else if(config.umdmode == MODE_NP9660)
	{
		SetConfFile(2);
	}
	else
	{
		SetConfFile(0);
	}
	loadUMD();
	
	return 1;
}

int module_start(SceSize args, void *argp)
{
	int status = 0;
	/*status = pspSdkLoadStartModule("umd_k.prx", PSP_MEMORY_PARTITION_KERNEL);
	if(status > 0)
	{
		status = -1;
	}*/
	return status;
}

int module_stop(void)
{
	return 0;
}
