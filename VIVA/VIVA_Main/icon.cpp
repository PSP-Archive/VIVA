/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

/*#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>*/

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<GL/glext.h>

#include "icon.h"
#include "GL.h"

#include "common.h"

icon music;
icon homebrew;
icon umd;
icon internet;
icon picture;
icon about;

icon::~icon()
{
	delete[] &texture;
	delete[] &background;
}

void icon::initIcon(char* fileName)
{
	texture = 0;
	
	iconActive = false;
	X = 0;
	Y = 0;
	Z = 0;
	xRot = 0;
	yRot = 0;
	zRot = 0;
	
	loadTex(fileName, &texture);
	
	iconList = glGenLists(1);
	
	glNewList(iconList, GL_COMPILE);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	//gluSphere(quadratic, 2, 32, 32);
	glBegin(GL_QUADS);
		//front face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1, -1, 1);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1, -1, 1);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 1, 1, 1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1, 1, 1);
	glEnd();
	
	glBegin(GL_QUADS);
		//back face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1, -1, -1);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1, -1, -1);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 1, 1, -1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1, 1, -1);
	glEnd();
		
	glBegin(GL_QUADS);
		//left face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1, -1, -1);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1, -1,  1);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1, 1,   1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1, 1,  -1);
	glEnd();
		
	glBegin(GL_QUADS);
		//right face
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1, -1, -1);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1, -1,  1);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1, 1,   1);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1, 1,  -1);
	glEnd();
	
	glEndList();
	
	
	/*quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);*/
}

bool icon::success()
{
	if(!texture)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void icon::loadBackground(char* fileName)
{
	loadTex(fileName, &background);
}

void icon::drawIcon()
{
	if(iconActive)
	{
		yRot += 1;
	}
	
	//move and rotate as required
	glTranslatef(X, Y, Z);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glRotatef(zRot, 0, 0, 1);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glCallList(iconList);
	
	//move and rotate back to original position
	glRotatef(-xRot, 1, 0, 0);
	glRotatef(-yRot, 0, 1, 0);
	glRotatef(-zRot, 0, 0, 1);
	glTranslatef(-X, -Y, -Z);
}

void icon::drawBackground(int X1, int Y1)
{
	draw2D();
	glLoadIdentity();
	glTranslatef(0, 0, -1);	
	
	glBindTexture(GL_TEXTURE_2D, background);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(X1,  SCREEN_HEIGHT, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(SCREEN_WIDTH,  SCREEN_HEIGHT, 0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(SCREEN_WIDTH, Y1, 0);
	glEnd();
	
	resizeWindow(480, 272);
}

bool icon::activateIcon()
{
	iconActive = true;
	return iconActive;
}

bool icon::deactivateIcon()
{
	iconActive = false;
	return iconActive;
}

void icon::setXYZ(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

void icon::setRot(float x, float y, float z)
{
	xRot = x;
	yRot = y;
	zRot = z;
}

bool icon::getStatus()
{
	return iconActive;
}
