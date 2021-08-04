/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

//#include <SDL/SDL.h>
//#include <SDL/SDL_opengl.h>

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

#include <pspdebug.h>

//#include <GL/glext.h>

#include "imageload.h"

#include "common.h"

//#include "common/SDL.h"

int nextPower(int power)
{
	int rValue = 1;
	
	while(rValue < power)
	{
		rValue *= 2;
	}
	
	return rValue;
}

int loadBMP(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	//return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	//return 0;
    }
	pspDebugScreenPrintf("Width of %s: %lu\n", filename, image->sizeX);
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	//return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	//return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	//return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	//return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
	printf("Error allocating memory for color-corrected image data");
	//return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	//return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = image->data[i];
	image->data[i] = image->data[i+2];
	image->data[i+2] = temp;
    }
    
    // we're done.
    return 1;
}

#include <png.h>
#include <malloc.h>

void loadTexBMP(char* fileName, unsigned int* texture)
{
	Image* tempImage;
	tempImage = (Image*) malloc(sizeof(Image));
	if(tempImage == 0)
	{
		exit(0);
	}
	
	if(loadBMP(fileName, tempImage))
	//loadBMP(fileName, tempImage);
	{	
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		/*if((tempImage->sizeX != 128) && (tempImage->sizeX != 256) && (tempImage->sizeX != 512) && (tempImage->sizeY != 128) && (tempImage->sizeY != 256) && (tempImage->sizeY != 512))
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tempImage->sizeX, tempImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, tempImage->data);
		}*/
		//else
		//{
			glTexImage2D(GL_TEXTURE_2D, 0, 3, tempImage->sizeX, tempImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, tempImage->data);
		//}
	}
	else
	{
		exit(0);
	}
}

void loadTex(char* fileName, unsigned int* texture)
{
	loadTexBMP(fileName, texture);
}

void enableBlend()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void disableBlend()
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

int initGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	//enableBlend();
    glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 1.0f, 1);
	
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 100);
	glMatrixMode(GL_MODELVIEW);
	return true;
}

int resizeWindow(int width, int height)
{
	//return 1;
    GLfloat ratio;
 
    if (height == 0)
	{
		height = 1;
	}

    ratio = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    return true;
}

void draw2D()
{
	glClearColor(0, 0, 0, 0);

	//Set projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);

	//Initialize modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
