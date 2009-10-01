#ifndef _PREFERENCES_H
#define _PREFERENCES_H

#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

#include "SDL_Tools.h"
#include <SDL_mixer.h>

#define NUM_SETTINGS 8

class Preferences
{
    public:
        static void setup();

        static void setScreenWidth(int inWidth);
        static void setScreenHeight(int inHeight);
        static void setColorDepth(int inDepth);
        static void setFullscreen(bool inFullscreen);
        static void setAudioRate(int inRate);
        static void setAudioFormat(Uint16 inFormat);
        static void setAudioChannels(int inChannels);
        static void setAudioBuffers(int inBuffers);

        static void saveSettings();
        static void rewriteSettings();

        //This allows a quick get without having to make a function call
        static const int &cWidth;
        static const int &cHeight;
        static const int &cColorDepth;
        static const bool &cFullscreen;

        static const int &cAudioRate;
        static const Uint16 &cAudioFormat;
        static const int &cAudioChannels;
        static const int &cAudioBuffers;

    private:
        static inline bool setSetting(string inSetting, bool inWrite);
        static int mWidth;
        static int mHeight;
        static int mColorDepth;
        static bool mFullscreen;

        static int mAudioRate;
        static Uint16 mAudioFormat;
        static int mAudioChannels;
        static int mAudioBuffers;

        static ofstream mPrefs;
        static stringstream mNewSettings;

        static string* mSettings;


};

#endif
