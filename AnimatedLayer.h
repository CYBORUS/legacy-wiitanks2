#ifndef _ANIMATEDLAYER_H
#define	_ANIMATEDLAYER_H

#include "VideoLayer.h"

class AnimatedLayer : public VideoLayer
{
    public:
        AnimatedLayer();
        virtual ~AnimatedLayer();

        void loadSheet(const char* inFile, int inFrameSize, int inFrameCount);
        void oscillate(bool inOscillate);
        void update();
    private:
        bool mOscillate;
        int mCurrentFrame;
        int mFrameSize;
        int mFrameOffset;
        int mFrameCount;
        Surface mSheet;
};

#endif
