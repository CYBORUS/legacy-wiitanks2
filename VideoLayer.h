#ifndef _VIDEOLAYER_H
#define	_VIDEOLAYER_H

#define PRIORITY_SCREEN     1
#define PRIORITY_BACKGROUND 2
#define PRIORITY_DEFAULT    100
#define PRIORITY_GUI        9000
#define PRIORITY_TEXT       9500
#define PRIORITY_MOUSE      10000

#include "SDL_Tools.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

/** Official Layer Priority List
  *
  * (1) SDL video display
  * (2) primary background (playing field)
  * (9000) GUI
  * (10000) mourse cursor
  */

class VideoLayer
{
    public:
        VideoLayer();
        virtual ~VideoLayer();

        void setLocation(int inX, int inY);

        int priority;
        Surface surface;
        VideoLayer* next;
        SDL_Rect location;
        SDL_Rect* clip;

        static Surface getImage(const char* inFile);
};

#endif
