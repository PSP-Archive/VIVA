/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

#ifndef __ICON_H__
#define __ICON_H__

class icon
{
	private:
		float X;
		float Y;
		float Z;
		float xRot;
		float yRot;
		float zRot;
		unsigned int texture;
		unsigned int background;
		unsigned int iconList;
		unsigned int bgList;
		bool iconActive;
		//GLUquadricObj *quadratic;
		
	public:
		~icon();
		void initIcon(char* fileName);
		void loadBackground(char* fileName);
		bool success();
		void drawIcon();
		void drawBackground(int X1 = 0, int X2 = 0);
		bool activateIcon();
		bool deactivateIcon();
		void setXYZ(float x, float y, float z);
		void setRot(float x, float y, float z);
		bool getStatus();
};

extern icon music;
extern icon homebrew;
extern icon umd;
extern icon internet;
extern icon picture;
extern icon about;

#endif
