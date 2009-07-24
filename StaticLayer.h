#ifndef _STATICLAYER_H
#define	_STATICLAYER_H

#include "VideoLayer.h"

class StaticLayer : public VideoLayer
{
    public:
        StaticLayer();
        virtual ~StaticLayer();

        void setLocation(int inX, int inY);
};

#endif
