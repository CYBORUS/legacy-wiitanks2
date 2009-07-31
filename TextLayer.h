#ifndef _TEXTLAYER_H
#define	_TEXTLAYER_H

#include <string>
#include "VideoLayer.h"

class TextLayer : public VideoLayer
{
    public:
        TextLayer();
        virtual ~TextLayer();

        bool loadFont(const char* inFile, int inSize);
        void setColor(char inRed, char inGreen, char inBlue, char inAlpha);
        void setText(const char* inText);
    protected:
        SDL_Color mColor;
        TTF_Font* mFont;
        int mSize;
        std::string mText;
};

#endif
