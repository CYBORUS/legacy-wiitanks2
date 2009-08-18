#include "Preferences.h"
#include <iostream>
#include <string>
using namespace std;

//setup all our static variables
int Preferences::mWidth = 800;
int Preferences::mHeight = 600;
bool Preferences::mFullscreen = false;

ofstream Preferences::mPrefs;
stringstream Preferences::mNewSettings;

int Preferences::mAudioRate = 22050;
Uint16 Preferences::mAudioFormat = MIX_DEFAULT_FORMAT;
int Preferences::mAudioChannels = 2;
int Preferences::mAudioBuffers = 256;

string* Preferences::mSettings;

const int &Preferences::cWidth = mWidth;
const int &Preferences::cHeight = mHeight;
const bool &Preferences::cFullscreen = mFullscreen;

const int &Preferences::cAudioRate = mAudioRate;
const Uint16 &Preferences::cAudioFormat = mAudioFormat;
const int &Preferences::cAudioChannels = mAudioChannels;
const int &Preferences::cAudioBuffers = mAudioBuffers;



/*
*   setup()
*
*   Loads all the preferences from a presaved file
*
*   If the file is not found, it creates one and writes the default settings out to it.
*/
void Preferences::setup()
{

    mSettings = new string[NUM_SETTINGS];

    mSettings[0] = "width";
    mSettings[1] = "height";
    mSettings[2] = "fullscreen";
    mSettings[3] = "rate";
    mSettings[4] = "format";
    mSettings[5] = "channels";
    mSettings[6] = "buffers";

    ifstream settings;
    settings.open("settings.dat");

    string next;

    if (settings.fail())
    {
        cerr << "Error opening settings\n";
        rewriteSettings();

        settings.clear();
        settings.open("settings.dat");


    }

    cerr << "done writing settings" << endl;

    getline(settings, next);


    while (!settings.eof())
    {

        if ((next[0] != '#') && (next.length() > 1))
        {
            if (!setSetting(next, false))
            {
                //The setting wasn't found, something is wrong with the settings file
                //need to rewrite it
                rewriteSettings();
                break;
            }
        }
        getline(settings, next);
    }

    settings.close();

    //rewriteSettings();

    //saveSettings();

}


/*
*   rewriteSettings()
*
*   Rewrites the settings file with the default comments
*   using the current game settings.
*   This should only be called if the settings file is missing
*   or somehow been messed up
*/
void Preferences::rewriteSettings()
{
    cerr << "rewriting" << endl;
    mPrefs.open("settings.dat", fstream::trunc);

    mNewSettings << "# This is a comment\n# Rewriting file\n\n";

    if (!mPrefs.fail())
    {
        int i = 0;
        mNewSettings << "# Video\n";
        for (; i < 3; i++)
        {
            setSetting(mSettings[i], true);
        }

        mNewSettings << "\n\n# Audio\n";

        for (; i < NUM_SETTINGS; i++)
        {
            setSetting(mSettings[i], true);
        }

    }
    else
    {
        cerr << "Error creating settings file" << endl;
        exit(5);
    }

    mPrefs << mNewSettings.str();

    mNewSettings.str("");
    mPrefs.close();
}


/*
*   saveSettings()
*
*   Saves all the current settings to the settings file
*   without removing any extra comments that the player
*   may have added to the file.
*/
void Preferences::saveSettings()
{
    ifstream settings;

    settings.open("settings.dat", fstream::in);

    string next;

    if (!settings.fail())
    {
        getline(settings, next);

        while (!settings.eof())
        {
            if ((next[0] == '#') || (next.length() <= 1))
            {
                mNewSettings << next << endl;
            }
            else
            {
                setSetting(next, true);
            }
            getline(settings, next);
        }
    }
    else
    {
        cerr << "Error writing settings" << endl;
        exit(5);
    }

    settings.close();

    mPrefs.open("settings.dat", fstream::trunc);

    mPrefs << mNewSettings.str();

    mPrefs.close();

    mNewSettings.str("");
}


/*
*   setSetting()
*
*   Searches for a setting within a given string and either writes that
*   setting to a stringstream object (save the setting to the file)
*   or changes it in the program (read it in from the file)
*
*   string inSetting: String that contains the setting
*
*   bool inWrite: if true, write it to the stringstream, if false, set the
*       appropriate variable
*/
inline bool Preferences::setSetting(string inSetting, bool inWrite)
{
    bool found = false;

    string name = inSetting.substr(0, inSetting.find_first_of(":"));

    for (int i = 0; i < NUM_SETTINGS && !found; i++)
    {
        if (name == mSettings[i])
        {

            switch(i)
            {
                case 0:
                {
                    found = true;
                    if (inWrite)
                    {
                        mNewSettings << mSettings[i] << ": " << mWidth << endl;
                    }
                    else
                    {
                        mWidth = atoi(inSetting.substr(inSetting.find_first_of("0123456789")).c_str());
                    }
                    break;
                }
                case 1:
                {
                    found = true;
                    if (inWrite)
                    {
                        mNewSettings << mSettings[i] << ": " << mHeight << endl;
                    }
                    else
                    {
                        mHeight = atoi(inSetting.substr(inSetting.find_first_of("0123456789")).c_str());
                    }
                    break;
                }
                case 2:
                {
                    found = true;
                    if (inWrite)
                    {
                        mNewSettings << mSettings[i] << ": " << mFullscreen << endl;
                    }
                    else
                    {
                        mFullscreen = (bool)atoi(inSetting.substr(inSetting.find_first_of("0123456789")).c_str());
                    }
                    break;
                }
                case 3:
                {
                    found = true;
                    if (inWrite)
                    {
                        mNewSettings << mSettings[i] << ": " << mAudioRate << endl;
                    }
                    else
                    {
                        mAudioRate = (bool)atoi(inSetting.substr(inSetting.find_first_of("0123456789")).c_str());
                    }
                    break;
                }
                case 4:
                {
                    found = true;
                    if (inWrite)
                    {
                        mNewSettings << mSettings[i] << ": " << mAudioFormat << endl;
                    }
                    else
                    {
                        mAudioFormat = (bool)atoi(inSetting.substr(inSetting.find_first_of("0123456789")).c_str());
                    }
                    break;
                }
                case 5:
                {
                    found = true;
                    if (inWrite)
                    {
                        mNewSettings << mSettings[i] << ": " << mAudioChannels << endl;
                    }
                    else
                    {
                        mAudioChannels = (bool)atoi(inSetting.substr(inSetting.find_first_of("0123456789")).c_str());
                    }
                    break;
                }
                case 6:
                {
                    found = true;
                    if (inWrite)
                    {
                        mNewSettings << mSettings[i] << ": " << mAudioBuffers << endl;
                    }
                    else
                    {
                        mAudioBuffers = (bool)atoi(inSetting.substr(inSetting.find_first_of("0123456789")).c_str());
                    }
                    break;
                }
            }
        }
    }

    return found;
}


void Preferences::setAudioRate(int inRate)
{
    mAudioRate = inRate;
}

void Preferences::setAudioFormat(Uint16 inFormat)
{
    mAudioFormat = inFormat;
}

void Preferences::setAudioChannels(int inChannels)
{
    mAudioChannels = inChannels;
}

void Preferences::setAudioBuffers(int inBuffers)
{
    mAudioBuffers = inBuffers;
}

void Preferences::setScreenWidth(int inWidth)
{
    mWidth = inWidth;
}

void Preferences::setScreenHeight(int inHeight)
{
    mHeight = inHeight;
}
