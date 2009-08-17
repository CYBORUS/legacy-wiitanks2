#ifndef _SCREENLAYER_H
#define _SCREENLAYER_H

#include "VideoLayer.h"
#include "Preferences.h"

class ScreenLayer : public VideoLayer
{
    public:
        ScreenLayer();
        virtual ~ScreenLayer();

        bool setVideoMode();
        int mHeight;
        int mWidth;

    private:
};

#endif
