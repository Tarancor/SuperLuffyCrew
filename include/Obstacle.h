#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>

#include "Position.h"
#include "MovableObject.h"

class Obstacle : public MovableObject
{
    private:


    public:
        Obstacle(float x=0.f, float y=0.f);
        virtual ~Obstacle();
        Obstacle(const Obstacle& other);
        Obstacle& operator=(const Obstacle& other);

        //Methods
        const std::string str() const;
        Obstacle* clone() const;
};

#endif // OBSTACLE_H
