#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2 AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 averageVelocity = Vector2::zero();

    // todo: add your code here to align each boid in a neighborhood

    // hint: iterate over the neighborhood
    for (int i = 0; i < neighborhood.size(); i++)
    {
        averageVelocity.x += neighborhood[i]->getVelocity().x;
        averageVelocity.y += neighborhood[i]->getVelocity().y;
    }
    if (neighborhood.size() > 0) 
    {
        averageVelocity.x /= neighborhood.size();
        averageVelocity.y /= neighborhood.size();
    }


    return Vector2::normalized(averageVelocity);
}