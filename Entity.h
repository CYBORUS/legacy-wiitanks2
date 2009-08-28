#ifndef _ENTITY_H
#define _ENTITY_H

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        virtual void collide(Entity* inEntity);

    private:
        // private member variables
};

#endif

