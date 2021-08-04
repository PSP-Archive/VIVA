/**
*
 * This work is licensed under the Creative Commons Attribution-Share Alike 3.0 License.
 * See LICENSE for more details.
 *
 **/

//#include <psprtc.h>

//#include <SDL/SDL.h>

int FPS = 60;

class timer
{
	private:
		int startTicks;
		int ticks;
		
	public:
		int getTicks();
		void setTicks();
};

int timer::getTicks()
{
	//ticks = SDL_GetTicks();
	return ticks - startTicks;
}

void timer::setTicks()
{
	//startTicks = SDL_GetTicks();
}

timer frameTimer;

void regulateFramerate()
{
	if(!FPS)
	{
		return;
	}
	else if(frameTimer.getTicks() < 1000/FPS)
	{
//		SDL_Delay(1000/FPS - frameTimer.getTicks());
	}
	frameTimer.setTicks();
}

int setFramerate(int newFps)
{
	int oldFps = 0;
	
	oldFps = FPS;
	FPS = newFps;
	
	return oldFps;
}
