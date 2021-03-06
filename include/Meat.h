#ifndef MEAT_H
#define MEAT_H

#include <iostream>

#include "Position.h"
#include "MovableObject.h"

class Meat : public MovableObject
{
    private:

    public:
        Meat(float x=0.f, float y=0.f);
        virtual ~Meat();
        Meat(const Meat& other);
        Meat& operator=(const Meat& other);

        //Methods
        const std::string str() const;
        Meat* clone() const;
};

#endif // MEAT_H
