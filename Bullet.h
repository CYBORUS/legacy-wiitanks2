#include <cmath>
using namespace std;

#include "VideoLayer.h"

struct Coor
{
    double x;
    double y;
};

class Bullet
{
    public:
        Bullet(double inVX, double inVY, double inPX, double inPY, double inMagnitude);
        //virtual ~Bullet();

         void onUpdate();
         VideoLayer* getLayer();




    private:
        Coor mVector;
        Coor mPos;

        VideoLayer* mBullet;
};
