#ifndef _PREFERENCES_H
#define _PREFERENCES_H

#include <cstdlib>
#include <fstream>
using namespace std;

class Preferences
{
    public:
        static void setup();

        static void setScreenWidth(int inWidth);
        static void setScreenHeight(int inHeight);

        static void saveSettings();

        //This allows a quick get without having to make a function call
        static const int &cWidth;
        static const int &cHeight;
        static const bool &cFullscreen;

    private:
        static int mWidth;
        static int mHeight;

        static bool mFullscreen;

        static ofstream prefs;

};

#endif
