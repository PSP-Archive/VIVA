/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspsysmem_kernel.h>
#include <psploadexec_kernel.h>
#include <pspreg.h>
#include <pspctrl.h>
#include <psprtc.h>
#include <pspusb.h>
#include <pspusbstor.h>
#include <psppower.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("UMD_KERNEL", 0x1007, 1, 0);

void SetConfFile(int n)
{
	int k1 = pspSdkSetK1(0);
	sctrlSESetBootConfFileIndex(n);
	pspSdkSetK1(k1);
}

void SetUmdFile(char *umdfile)
{
	int k1 = pspSdkSetK1(0);
	sctrlSESetUmdFile(umdfile);
	pspSdkSetK1(k1);
}

int module_start(SceSize args, void *argp)
{
	return 0;
}
