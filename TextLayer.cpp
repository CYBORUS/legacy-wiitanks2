#include <iostream>
#include "TextLayer.h"
using namespace std;

TextLayer::TextLayer() : VideoLayer()
{
    mFont = NULL;
    mSize = 0;
}

TextLayer::~TextLayer()
{
}

bool TextLayer::loadFont(const char* inFile, int inSize)
{
    mSize = inSize;
    mFont = TTF_OpenFont(inFile, inSize);
    return mFont != NULL;
}

void TextLayer::setColor(char inRed, char inGreen, char inBlue, char inAlpha)
{
    mColor.r = inRed;
    mColor.g = inGreen;
    mColor.b = inBlue;
    mColor.unused = inAlpha;
}

void TextLayer::setText(const char* inText)
{
    mText = inText;
    SDL_FreeSurface(surface);
    //surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
    surface = TTF_RenderText_Blended(mFont, mText.c_str(), mColor);
}
