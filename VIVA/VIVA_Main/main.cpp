/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

#define __PC__ //PC testing enabled load dud functions

//#include <windows.h>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/**START: PSP Specific**/
#include <pspctrl.h>
#include <pspdebug.h>
#include <psprtc.h>
#include <pspsdk.h>
#include <pspumd.h>
#include <pspkernel.h>
#include <pspvshbridge.h>

int window;

PSP_MODULE_INFO("VIVA", 0x0800, 0, 1);
//PSP_HEAP_SIZE_KB(20*1024);
PSP_HEAP_SIZE_KB(512);
/**END: PSP Specific**/

#include "icon.h"
#include "GL.h"
#include "framerate.h"

#include "common.h"

extern "C"
{
	#include <systemctrl_se.h>
	#include <systemctrl.h>
	#include "../VIVA_Modules/ISOLoader/k/k.h"
	#include "../VIVA_Modules/ISOLoader/isoloader.h"
};

char location[3][100];

int fps = 0; // for calculating the frames per second
char fpsDisplay[100];
u32 tickResolution;
u64 fpsTickNow;
u64 fpsTickLast;

float rotation = 0;
//float lastrot = 1;

unsigned int background;

void FPS(void)
{
	fps++;
	sceRtcGetCurrentTick(&fpsTickNow);
	
	if( ((fpsTickNow - fpsTickLast) / ((float)tickResolution)) >= 1.0f )
	{
		fpsTickLast = fpsTickNow;
		sprintf(fpsDisplay, "FPS: %d", fps);
		fps = 0;
	}
	pspDebugScreenSetXY(0, 0);
	pspDebugScreenPrintf(fpsDisplay);
 
}

enum _icon
{
	ICON_ERROR = -1,
	MUSIC = 0,
	HOMEBREW,
	UMD,
	INTERNET,
	PICTURE,
	ABOUT,
	ICON_MAX
};

void drawBackground()
{
	draw2D();
	glLoadIdentity();
	glTranslatef(0, 0, -1);
	
	glBindTexture(GL_TEXTURE_2D, background);
	
	int X1, Y1;
	
	X1 = Y1 = 0;
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(X1,  SCREEN_HEIGHT, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(SCREEN_WIDTH,  SCREEN_HEIGHT, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(SCREEN_WIDTH, Y1, 0);
	glEnd();
	
	resizeWindow(480, 272);
}

int getCurrentIcon()
{
	if(music.getStatus())
	{
		return MUSIC;
	}
	else if(homebrew.getStatus())
	{
		return HOMEBREW;
	}
	else if(umd.getStatus())
	{
		return UMD;
	}
	else if(internet.getStatus())
	{
		return INTERNET;
	}
	else if(picture.getStatus())
	{
		return PICTURE;
	}
	else if(about.getStatus())
	{
		return ABOUT;
	}
	else
	{
		return ICON_ERROR;
	}
}

void centreRotate(float angle = static_cast<float> (360/ICON_MAX))
{
	//go to centre of icons
	glTranslatef(0, 0, -50);
	//rotate by angle
	glRotatef(angle, 0, 1, 0);
	//return to original position
	glTranslatef(0, 0, 50);
}

void drawScene(int cIcon, float y = 0.0f)
{
	//initGL();
	glLoadIdentity();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawBackground();
	
	//lastrot = rotation;
	
	centreRotate(rotation);
	
	//rotate the icons to compensate for SDLs loading upside down
	//glRotatef(180, 0, 0, 1);
	
	music.setXYZ(0, y, -10);
	music.drawIcon();
	
	centreRotate();
	
	homebrew.setXYZ(0, y, -10);
	homebrew.drawIcon();
	
	centreRotate();
	
	umd.setXYZ(0, y, -10);
	umd.drawIcon();
	
	centreRotate();
	
	internet.setXYZ(0, y, -10);
	internet.drawIcon();
	
	centreRotate();
	
	picture.setXYZ(0, y, -10);
	picture.drawIcon();
	
	centreRotate();
	
	about.setXYZ(0, y, -10);
	about.drawIcon();
	
	//SDL_GL_SwapBuffers();
	glutSwapBuffers();
	//FPS();
	regulateFramerate();
}

void transition(int cIcon)
{
	for(float y = 0; y < 16; y += 0.5f)
	{	
		drawScene(cIcon, y);
	}
}

/**
  *
  * Code here specific to PSP will
  * be loaded. These functions are
  * duds in order to compile
  * without issues for testing
  * purposes only. To be removed
  * upon porting to the PSP system
  *
  **/

#ifdef __PC__ 
void loadMusicPlayer(){};
//void loadUMD(){};
void loadInternet(){};
void openFileBrowser(char *location){};
#endif

/*int loadUMD()
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
}*/

int updown = 0;

void loadOption(int cIcon)
{
	switch(cIcon)
	{
		case MUSIC:
			transition(cIcon);
			loadMusicPlayer();
			break;
		
		case UMD:
			transition(cIcon);
			if(updown == 0)
			{
				int status = loadUMD();
				if(status < 0)
				{
					char string[256];
					sprintf(string, "0x%08X", status);
					sceIoWrite(1, string, sizeof(string));
					//write to PSPLink if error
				}
			}
			else if(updown > 0)
			{
				pspDebugScreenClear();
				loadISO(location[updown]);
				sceKernelSleepThread();
			}
			break;
			
		case INTERNET:
			transition(cIcon);
			loadInternet();
			break;
			
		case HOMEBREW:
			transition(cIcon);
			openFileBrowser("ms0:/PSP/GAME");
			//currently a dud function
			break;
			
		default:
			//error occured
			break;
	}
}

void cleanCode()
{
	//SDL_Quit();
}

/*void checkFile()
{
	struct SceKernelLoadExecVSHParam param;
	memset(&param, 0, sizeof(param));
	param.size = sizeof(param)+strlen("ms0:/VIVA/dev_made_an_error.PBP")+1;
	param.argp = NULL;
	param.args = 0;
	param.key  = "game";
	
	sctrlKernelLoadExecVSHMs2("ms0:/VIVA/dev_made_an_error.PBP", &param);
}*/

int loadXMB()
{
	SceUID mod;
	mod = vshKernelLoadModuleVSH("flash0:/vsh/module/XMB.prx", 0, NULL);
	sceKernelStartModule(mod, 0, 0, 0, NULL);
	return 1;
}

int main(int argc, char** args)
{
	pspDebugScreenPrintf("Developed by Auraomega - Live. Love. Be. Believe.");
	setFramerate(60);
	bool done = false;
	SceCtrlData pad;
	
	//void checkFile();
	
	sprintf(location[0], "UMD");
	sprintf(location[1], "ms0:/test.iso");
	sprintf(location[2], "ms0:/test.cso");
	
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("XMB Replacement Design Concept");
	
	pspDebugScreenInit();
	
	/*
	music.initIcon("music.bmp");
	homebrew.initIcon("homebrew.bmp");
	umd.initIcon("umd.bmp");
	internet.initIcon("internet.bmp");
	picture.initIcon("picture.bmp");
	about.initIcon("about.bmp");
	
	loadTex("background.bmp", &background);
	//*/
	
	//*
	music.initIcon("flash2:/VIVA/music.bmp");
	homebrew.initIcon("flash2:/VIVA/homebrew.bmp");
	umd.initIcon("flash2:/VIVA/umd.bmp");
	internet.initIcon("flash2:/VIVA/internet.bmp");
	picture.initIcon("flash2:/VIVA/picture.bmp");
	about.initIcon("flash2:/VIVA/about.bmp");
	
	loadTex("flash2:/VIVA/background.bmp", &background);
	//*/
	
	/**/
	sceRtcGetCurrentTick( &fpsTickLast );
	tickResolution = sceRtcGetTickResolution();
	/**/
	
	//sceKernelExitGame();
	
	if(!initGL())
	{
		//cleanCode();
		return 0;
	}
	
	resizeWindow(480, 272);
	
	music.activateIcon();
	
	SceUID status;
	
	status = pspSdkLoadStartModule("flash1:/isoloader.prx", PSP_MEMORY_PARTITION_USER);
	if(status < 0)
	{
		pspDebugScreenPrintf("0x%08X : Error starting module", status);
		sceKernelSleepThread();
	}
	
	status = pspSdkLoadStartModule("flash1:/umd_k.prx", PSP_MEMORY_PARTITION_KERNEL);
	if(status < 0)
	{
		pspDebugScreenPrintf("0x%08X : Error starting module", status);
		sceKernelSleepThread();
	}
	
	//add info on which modules have thrown errors
	
	while(!done)
	{
		int cIcon = ICON_ERROR;
		
		cIcon = getCurrentIcon();
		drawScene(cIcon);
		
		sceCtrlReadBufferPositive(&pad, 1);
		if(pad.Buttons & PSP_CTRL_LEFT)
		{
			music.deactivateIcon();
			homebrew.deactivateIcon();
			umd.deactivateIcon();
			internet.deactivateIcon();
			picture.deactivateIcon();
			about.deactivateIcon();
			
			cIcon--;
			
			if(cIcon == ICON_ERROR)
			{
				cIcon = ICON_MAX - 1;
			}
			
			switch(cIcon) //draw main
			{
				case MUSIC:
					music.activateIcon();
					break;
					
				case HOMEBREW:
					homebrew.activateIcon();
					break;
					
				case UMD:
					umd.activateIcon();
					break;
					
				case INTERNET:
					internet.activateIcon();
					break;
					
				case PICTURE:
					picture.activateIcon();
					break;
					
				case ABOUT:
					about.activateIcon();
					break;
					
				default:
					//error occured
					break;
			}
			for(int loop = 0; loop < (360/ICON_MAX)/2; loop++) //rotation graphics
			{
				rotation += 2;
				drawScene(cIcon);
			}
		}
		
		if(pad.Buttons & PSP_CTRL_RIGHT)
		{
			music.deactivateIcon();
			homebrew.deactivateIcon();
			umd.deactivateIcon();
			internet.deactivateIcon();
			picture.deactivateIcon();
			about.deactivateIcon();
			
			cIcon++;
			
			if(cIcon == ICON_MAX)
			{
				cIcon = 0;
			}
			
			switch(cIcon) //draw main
			{
				case MUSIC:
					music.activateIcon();
					break;
					
				case HOMEBREW:
					homebrew.activateIcon();
					break;
					
				case UMD:
					umd.activateIcon();
					break;
					
				case INTERNET:
					internet.activateIcon();
					break;
					
				case PICTURE:
					picture.activateIcon();
					break;
					
				case ABOUT:
					about.activateIcon();
					break;
					
				default:
					//error occured
					break;
			}
			for(int loop = 0; loop < (360/ICON_MAX)/2; loop++) //rotation graphics
			{
				rotation -= 2;
				drawScene(cIcon);
			}
		}
		
		if(pad.Buttons & PSP_CTRL_CROSS)
		{
			loadOption(cIcon);
		}
		
		if(pad.Buttons & PSP_CTRL_START)
		{
			done = true;
		}
		
		if(pad.Buttons & PSP_CTRL_LTRIGGER)
		{
			transition(cIcon);
		}
		
		/**START: Removable once file browser complete**/
		if(pad.Buttons & PSP_CTRL_DOWN)
		{
			updown++;
			if(updown > 2)
			{
				updown = 0;
			}
			sceKernelDelayThread(200*1000);
		}
		/**END: Removable once file browser complete **/
		
		pspDebugScreenSetXY(0, 0);
		pspDebugScreenPrintf("%s", location[updown]);
	}
	cleanCode();
	//unload modules
	loadXMB();
	sceKernelExitGame();
	return 0;
}
