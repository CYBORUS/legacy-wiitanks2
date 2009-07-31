#include "AnimatedLayer.h"

AnimatedLayer::AnimatedLayer() : VideoLayer()
{
    mOscillate = false;
    mSheet = NULL;
    mFrameSize = 0;
    mFrameOffset = 1;
    mFrameCount = 0;
    mCurrentFrame = -1;
    clip = new SDL_Rect();
    clip->x = 0;
}

AnimatedLayer::~AnimatedLayer()
{
    SDL_FreeSurface(surface);
    surface = NULL;
}

void AnimatedLayer::oscillate(bool inOscillate)
{
    mOscillate = inOscillate;
}

void AnimatedLayer::loadSheet(const char* inFile, int inFrameSize, int inFrameCount)
{
    mFrameSize = inFrameSize;
    clip->w = mFrameSize;
    clip->h = mFrameSize;
    mFrameCount = inFrameCount;
    mSheet = VideoLayer::getImage(inFile);
    surface = mSheet;
}

void AnimatedLayer::update()
{
    mCurrentFrame += mFrameOffset;
    if (mCurrentFrame >= mFrameCount)
    {
        if (mOscillate)
        {
            mFrameOffset = -1;
            mCurrentFrame = mFrameCount - 2;
        }
        else
        {
            mCurrentFrame = 0;
        }
    }
    else if (mCurrentFrame < 0)
    {
        mCurrentFrame = 1;
        mFrameOffset = 1;
    }

    clip->y = mCurrentFrame * mFrameSize;
}
