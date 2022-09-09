#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce;
    float extraMag = 0;
    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    Vector2 centerOfMass;
    for (int i = 0; i < neighborhood.size(); i++) 
    {
        centerOfMass += neighborhood[i]->getPosition();
    }
    if (neighborhood.size() > 0)
    {
        centerOfMass /= neighborhood.size();
    }
    cohesionForce = centerOfMass - boid->getPosition();
    Vector2 normalizedForce = Vector2::normalized(cohesionForce);
    Vector2 extraVelocity = cohesionForce - normalizedForce;
    Vector2 addedMag = normalizedForce + Vector2(log(extraVelocity.x + 1), log(extraVelocity.y + 1));
    cohesionForce = addedMag;
    return cohesionForce;
}