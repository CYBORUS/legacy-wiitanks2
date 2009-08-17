#include "Preferences.h"
#include <iostream>
#include <string>
using namespace std;

//setup all our static variables
int Preferences::mWidth = 800;
int Preferences::mHeight = 600;
ofstream Preferences::prefs;

/*
*   setup()
*
*   Loads all the preferences from a presaved file
*
*   If the file is not found, it creates one and writes the default settings out to it.
*/
void Preferences::setup()
{
    ifstream settings;
    settings.open("settings.dat");

    string next;

    if (settings.fail())
    {
        cerr << "Error opening settings\n";
        ofstream defSet;

        defSet.open("settings.dat");

        if (defSet.fail())
        {
            cerr << "Error creating settings file" << endl;
        }
        else
        {
            defSet << mWidth << endl << mHeight << endl;
        }
    }
    else
    {

        getline(settings, next);

        mWidth = atoi(next.substr(next.find_first_of("0123456789")).c_str());

        getline(settings, next);


        mHeight = atoi(next.substr(next.find_first_of("0123456789")).c_str());


        settings.close();
    }
}

int Preferences::getScreenWidth()
{
    return mWidth;
}

int Preferences::getScreenHeight()
{
    return mHeight;
}

void Preferences::setScreenWidth(int inWidth)
{
    prefs.open("settings.dat");

    if (!prefs.fail())
    {

    }
}

void Preferences::setScreenHeight(int inHeight)
{
}
