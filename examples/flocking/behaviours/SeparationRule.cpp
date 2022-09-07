#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include <cmath>
Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2 position = boid->getPosition();
        Vector2 difference = Vector2::zero();
        int countCloseFlockmates = 0;
        //yikers I should probably do something faster than this but... whatever. 
        for (int i = 0; i < neighborhood.size(); i++) 
        {
            float distance = Vector2::getDistance(position, neighborhood[i]->getPosition());
            if (distance < desiredMinimalDistance && distance > 0.01) 
            {
                difference = position - neighborhood[i]->getPosition();
                float inverseMag = 1 / difference.getMagnitude();
                difference = difference.normalized();
                difference *= inverseMag;
                separatingForce += difference;
                countCloseFlockmates++;
            }
        }
        if (countCloseFlockmates > 0) 
        {
            separatingForce /= countCloseFlockmates;
        }
    }
    separatingForce = Vector2::normalized(separatingForce);
    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
