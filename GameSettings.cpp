#include "GameSettings.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

GameSettings::GameSettings()
{
    ifstream settings;
    settings.open("settings.dat");

    string next;

    if (settings.fail())
    {
        cerr << "Error opening settings\n";
        exit(5);
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

GameSettings::~GameSettings()
{
}
