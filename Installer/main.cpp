/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>

#define _printf pspDebugScreenPrintf

#define SECOND 1*1000*1000

PSP_MODULE_INFO("VIVA Flash Patcher", 0x800, 0, 1);
PSP_HEAP_SIZE_KB(20480);

//[package] [version] [flash] [oFile] [rFile] [nFile] [extention]

typedef struct
{
	char package[256];
	float version;
	int flash;
	char oFile[256];
	char rFile[256];
	char nFile[256];
	char extention[256];
} _patch;

int devAssign(const char *dev1, const char *dev2, const char *dev3)
{
    int status = 0;
    status = sceIoAssign(dev1, dev2, dev3, IOASSIGN_RDWR, NULL, 0);
    return status;
}

int devUnassign(const char *dev)
{
    int status = 0;
    status = sceIoUnassign(dev);
    return status;
}

void getPatchInfo(char* fileName, _patch *info, int num)
{
	//return;
	FILE* patch;
	
	patch = fopen(fileName, "r");
	if(!patch)
	{
		_printf("Error");
		sceKernelSleepThread();
		return;
	}
	
	//fscanf(patch, "%s", &info[num].package);
	fscanf(patch, "%s", info[num].package);
	fscanf(patch, "%f", &info[num].version);
	fscanf(patch, "%i", &info[num].flash);
	fscanf(patch, "%s", info[num].oFile);
	fscanf(patch, "%s", info[num].rFile);
	fscanf(patch, "%s", info[num].nFile);
	fscanf(patch, "%s", info[num].extention);
	
	if(info[num].oFile[0] == '0')
	{
		info[num].oFile[0] = 0;
	}
	if(info[num].rFile[0] == '0')
	{
		info[num].rFile[0] = 0;
	}
	if(info[num].nFile[0] == '0')
	{
		info[num].nFile[0] = 0;
	}
	
	fclose(patch);
}

int writePackage(char *oFileTemp, char *nFileTemp, char *extention, int flash)
{
	char oFile[256];
	char nFile[256];
	
	switch(flash)
	{
		case 0:
			strcpy(nFile, "flash0:/");
			break;
			
		case 1:
			strcpy(nFile, "flash1:/");
			break;
		
		case 2:
			strcpy(nFile, "flash2:/");
			break;
		
		case 3:
			strcpy(nFile, "flash3:/");
			break;	
	}
	
	
	//copy file locations over
	strcpy(oFile, oFileTemp);
	strcat(nFile, nFileTemp);
	
	//append file locations with extention
	strcat(oFile, ".package");
	strcat(nFile, extention);
	
	FILE *newFile;
	FILE *oldFile;
	
	u8* buffer = (u8*)malloc(1*1024*1024); //allocate 1mb off heap
	
	pspDebugScreenPrintf("\n%s", nFile);
	
	SceUID fd;
	fd = sceIoOpen(nFile, PSP_O_WRONLY | PSP_O_CREAT, 0777);
	if(fd < 0)
	{
		pspDebugScreenPrintf("\nError");
	}
	
	sceIoClose(fd);
	
	newFile = fopen(nFile, "wb"); //N.B. Must be binary mode for non-text files
	oldFile = fopen(oFile, "rb"); //N.B. Must be binary mode for non-text files
	
	/*_printf("\nPackage %s\n", oFileTemp);
	_printf("New File %s\n", nFileTemp);
	_printf("New File %s\n", nFile);
	_printf("Old File %s\n", oFile);
	sceKernelSleepThread();*/
	
	if((!newFile) || (!oldFile))
	{
		if(!newFile)
		{
			_printf("\nNew File %s\n", nFile);
		}
		if(!oldFile)
		{
			_printf("Old File %s\n", oFile);
		}
		_printf("Error");
		sceKernelSleepThread();
	}
	
	//_printf("\nWriting file %s\n", oFile);
	
	//sceKernelSleepThread();
	
	size_t len;
	
	len = fread(buffer, 1, 1*1024*1024, oldFile);
	while(1)
	{
		if(len <= 0)
		{
			break;
		}
		fwrite(buffer, 1, len, newFile);
		len = fread(buffer, 1, 1*1024*1024, oldFile);
	}
	
	fclose(oldFile);
	fclose(newFile);
	free(buffer); //close buffer
	return 1;
}

int copyFile(char *oFileTemp, char *rFileTemp, char *extention, int flash)
{
	char oFile[256];
	char rFile[256];
	
	switch(flash)
	{
		case 0:
			strcpy(oFile, "flash0:/");
			break;
			
		case 1:
			strcpy(oFile, "flash1:/");
			break;
		
		case 2:
			strcpy(oFile, "flash2:/");
			break;
		
		case 3:
			strcpy(oFile, "flash3:/");
			break;	
	}
	
	strcpy(rFile, oFile);
	
	//copy file locations over
	strcat(oFile, oFileTemp);
	strcat(rFile, rFileTemp);
	
	//append file locations with extention
	strcat(oFile, extention);
	strcat(rFile, extention);
	
	FILE *newFile;
	FILE *oldFile;
	
	u8* buffer = (u8*)malloc(1*1024*1024); //allocate 1mb off heap
	
	newFile = fopen(rFile, "wb"); //N.B. Must be binary mode for non-text files
	oldFile = fopen(oFile, "rb"); //N.B. Must be binary mode for non-text files
	
	if((!newFile) || (!oldFile))
	{
		_printf("\nNew File %s\n", rFile);
		_printf("Old File %s\n", oFile);
		_printf("Error");
		sceKernelSleepThread();
		//error
	}
	
	size_t len;
	
	len = fread(buffer, 1, 1*1024*1024, oldFile);
	while(1)
	{
		if(len <= 0)
		{
			break;
		}
		fwrite(buffer, 1, len, newFile);
		len = fread(buffer, 1, 1*1024*1024, oldFile);
	}
	
	fclose(oldFile);
	fclose(newFile);
	free(buffer); //close buffer
	return 1;
}

int deleteFile(const char *path)
{
    int status = 0;
    status = sceIoRemove(path);
    if(status < 0)
	{
		status = sceIoRmdir(path);
	}
    return status;
}

int patchFile(_patch *patch, int num)
{
	//check if there is a file to rename
	int status = 0;
	//char package[256];
	
	_printf("oFile = %i\n", *patch[num].oFile);
	
	if(*patch[num].oFile != 0)
	{
		_printf("Backing up %s to %s...", patch[num].oFile, patch[num].rFile);
		deleteFile(patch[num].rFile);
		status = copyFile(patch[num].oFile, patch[num].rFile, patch[num].extention, patch[num].flash);
		if(status < 0)
		{
			//error
		}
		_printf("Done\n");
	}
	
	_printf("Patching %s%s...\n", patch[num].nFile, patch[num].extention);
	_printf("Writing %s...\n", patch[num].package);
	//sceKernelSleepThread();
	{
		char delPath[256];
		sprintf(delPath, "flash%i:/%s%s", patch[num].flash, patch[num].nFile, patch[num].extention);
		deleteFile(delPath);
	}
	status = writePackage(patch[num].package, patch[num].nFile, patch[num].extention, patch[num].flash);
	if(status < 0)
	{
		//error
	}
	_printf("Done\n");
	return 1;
}

int main()
{
	FILE* list;
	//FILE* patch;
	bool done = false;
	bool unPatch = false;
	char filePath[10][256];
	_patch patch[10];
	int item = 0;
	int itemMax = 0;
	
	_printf("Developed by Auraomega");
	
	list = fopen("list.txt", "r");
	if(!list)
	{
		_printf("Error");
		sceKernelSleepThread();
		//error
	}
	
	while(!feof(list))
	{
		fscanf(list, "%s", filePath[itemMax]);
		itemMax++;
	}
	
	for(int loop = 0; loop < itemMax; loop++)
	{
		getPatchInfo(filePath[loop], patch, loop);
	}
	
	fclose(list);
	
	if(itemMax == 0)
	{
		//error
	}
	
	pspDebugScreenInit();
	
	int status = 0;
	
	status = devUnassign("flash0:");
	if(status < 0)
	{
		pspDebugScreenPrintf("Error");
		sceKernelSleepThread();
	}
	status = devAssign("flash0:", "lflash0:0,0", "flashfat0:");
	if(status < 0)
	{
		pspDebugScreenPrintf("Error");
		sceKernelSleepThread();
	}
	
	status = devUnassign("flash2:");
	if(status < 0)
	{
		pspDebugScreenPrintf("Error 2");
		sceKernelSleepThread();
	}
    status = devAssign("flash2:", "lflash0:0,2", "flashfat2:");
	if(status < 0)
	{
		pspDebugScreenPrintf("Error 2.1");
		sceKernelSleepThread();
	}
	
    /*status = devUnassign("flash3:");
	if(status < 0)
	{
		pspDebugScreenPrintf("Error 3");
		sceKernelSleepThread();
	}
    status = devAssign("flash3:", "lflash0:0,3", "flashfat3:");
	if(status < 0)
	{
		pspDebugScreenPrintf("Error 3.1");
		sceKernelSleepThread();
	}*/
	
	SceCtrlData pad;
	
	while(!done)
	{
		pspDebugScreenSetTextColor(0x000000FF);
		
		if(unPatch == false)
		{
			_printf("*****UNPATCH MODE OFF*****\n\n\n");
		}
		
		if(unPatch == true)
		{
			_printf("*****UNPATCH MODE ON******\n\n\n");
		}
		
		_printf("Flash Patcher developer for VIVA by ...?\n\n");
		_printf("List contains %i objects\n", itemMax);
		_printf("Patch Files available:\n");
		
		for(int loop = 0; loop < itemMax; loop++)
		{
			if(loop == item)
			{
				pspDebugScreenSetTextColor(0xFF00FF00);
			}
			else
			{
				pspDebugScreenSetTextColor(0x00FF00FF);
			}
			_printf(" %s\n", filePath[loop]);
		}
		
		pspDebugScreenSetTextColor(0x000000FF);
		pspDebugScreenSetXY(10, 10);	
		
		_printf("%s content:\n\n", filePath[item]);
		getPatchInfo(filePath[item], patch, 0);
		
		_printf("Package Name: %s\n", patch[item].package);
		if(patch[item].version < 0.1)
		{
			_printf("Version: %0.2f *Warning, Experimental Build*\n", patch[item].version);
		}
		else if(patch[item].version < 1)
		{
			_printf("Version: %0.2f *Warning, Beta Build*\n", patch[item].version);
		}
		else if(patch[item].version >= 1)
		{
			_printf("Version: %0.2f\n", patch[item].version);
		}
		_printf("Writing to flash%i\n", patch[item].flash);
		if(patch[item].oFile[0] != 0)
		{
			_printf("Backing up file %s%s to %s%s\n", patch[item].oFile, patch[item].extention, patch[item].rFile, patch[item].extention);
		}
		_printf("File to be flashed as %s%s\n", patch[item].nFile, patch[item].extention);
		
		sceKernelDelayThread(SECOND/5); // 1/2s / 0.2s / 200ms
		while(1)
		{
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				item++;
				if(item > itemMax - 1)
				{
					item = 0;
				}
				break;
			}
			if(pad.Buttons & PSP_CTRL_UP)
			{
				item--;
				if(item < 0)
				{
					item = itemMax - 1;
				}
				break;
			}
			if(pad.Buttons & PSP_CTRL_RTRIGGER)
			{
				unPatch = true;
				break;
			}
			if(pad.Buttons & PSP_CTRL_LTRIGGER)
			{
				unPatch = false;
				break;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(unPatch == false)
				{
					pspDebugScreenClear();
					_printf("Patching file %s...\n", filePath[item]);
					patchFile(patch, item);
					_printf("Patching file %s complete\n", filePath[item]);
					_printf("Returning to menu in 2 seconds");
					sceKernelDelayThread(2*SECOND);
					break;
				}
				if(unPatch == true)
				{
					pspDebugScreenClear();
					
					char delPath[256];
					int status;
					
					sprintf(delPath, "flash%i:/%s%s", patch[item].flash, patch[item].nFile, patch[item].extention);
					_printf("Deleting file at %s...", delPath);
					deleteFile(delPath);
					
					printf("Patching file %s...\n", filePath[item]);
					status = copyFile(patch[item].rFile, patch[item].nFile, patch[item].extention, patch[item].flash);
					if(status < 0)
					{
						_printf("Error");
						sceKernelSleepThread();
					}
					
					_printf("Unpatching file %s complete\n", filePath[item]);
					_printf("Returning to menu in 2 seconds");
					sceKernelDelayThread(2*SECOND);
					break;
				}
			}
		}
		pspDebugScreenClear();
	}
}
