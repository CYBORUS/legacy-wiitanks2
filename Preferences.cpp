#include "Preferences.h"
#include <iostream>
#include <string>
using namespace std;

//setup all our static variables
int Preferences::mWidth = 800;
int Preferences::mHeight = 600;
bool Preferences::mFullscreen = false;
ofstream Preferences::prefs;

const int &Preferences::cWidth = mWidth;
const int &Preferences::cHeight = mHeight;
const bool &Preferences::cFullscreen = mFullscreen;


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
        saveSettings();

        settings.open("settings.dat");


    }

    getline(settings, next);


    while (((next[0] == '#') || (next.find_first_of("Width") == string::npos)) && !settings.eof())
    {
        getline(settings, next);
    }

    if (!settings.eof())
    {
        mWidth = atoi(next.substr(next.find_first_of("0123456789")).c_str());
    }
    else
    {
        saveSettings();
        settings.clear();
    }

    prefs.seekp(0);

    getline(settings, next);

    while (((next[0] == '#') || (next.find_first_of("Height") == string::npos)) && !settings.eof())
    {
        getline(settings, next);
    }

    if (!settings.eof())
    {
        mHeight = atoi(next.substr(next.find_first_of("0123456789")).c_str());
    }
    else
    {
        saveSettings();
        settings.clear();
    }

    prefs.seekp(0);

    getline(settings, next);

    while (((next[0] == '#') || (next.find_first_of("Fullscreen") == string::npos)) && !settings.eof())
    {
        getline(settings, next);
    }

    if (!settings.eof())
    {
        mFullscreen = (bool)atoi(next.substr(next.find_first_of("0123456789")).c_str());
    }
    else
    {
        saveSettings();
        settings.clear();
    }

    settings.close();

}

void Preferences::saveSettings()
{
    prefs.open("settings.dat", fstream::trunc);

    if (!prefs.fail())
    {
        prefs << "Width: " << mWidth << endl << "Height: " << mHeight << endl << "Fullscreen: " << mFullscreen << endl;
    }
    else
    {
        cerr << "Error creating settings file" << endl;
        exit(5);
    }
    prefs.close();
}

void Preferences::setScreenWidth(int inWidth)
{
    mWidth = inWidth;
}

void Preferences::setScreenHeight(int inHeight)
{
    mHeight = inHeight;
}
