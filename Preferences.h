#ifndef _PREFERENCES_H
#define _PREFERENCES_H

#include <cstdlib>
#include <fstream>
using namespace std;

class Preferences
{
    public:
        static void setup();

        static int getScreenWidth();
        static int getScreenHeight();

        static void setScreenWidth(int inWidth);
        static void setScreenHeight(int inHeight);

    private:
        static int mWidth;
        static int mHeight;

        static ofstream prefs;

};

#endif
