#include <iostream>
#include "lab_m1/Tema2/turret.h"
#include "lab_m1/Tema2/tank.h"
#include "lab_m1/Tema2/cannon.h"


#include <cmath>

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

glm::vec3 Cannon::cannonColor = glm::vec3(0.9,0.9,0.9);
int Cannon::pointCount = 12;
float Cannon::radius = 0.05;
float Cannon::cannonHeight = (Turret::turretLowerBaseHeight + Turret::turretUpperBaseHeight);
float Cannon::cannonLength = Tank::lowerBaseLength / 1.4;


Mesh* Cannon::CreateCannon(const std::string &name, bool isFriendly) {

    Mesh* cannon = new Mesh(name);

    std::vector<VertexFormat> vertices = {};
    std::vector<unsigned int> indices = {};
    float cannonHeight = (Turret::turretLowerBaseHeight + Turret::turretUpperBaseHeight)/2;

    float angle = 360.0f / Cannon::pointCount;
    // First Circle
    for (int i = 0; i < Cannon::pointCount; i++)
    {
        float currentAngle = angle * i;
        float x = Cannon::radius * cos(glm::radians(currentAngle));
        float y = cannonHeight + Cannon::radius * sin(glm::radians(currentAngle));
        float z = 0.0f;

        vertices.push_back(VertexFormat(glm::vec3(x,y,z), glm::vec3(0), Cannon::cannonColor));
    }

    printf("cannon height = %f\n", cannonHeight);
    printf("cannon length = %f\n", Cannon::cannonLength);

    // Second Circle
    for (int i = 0; i < Cannon::pointCount; i++)
    {
        float currentAngle = angle * i;
        float x = Cannon::radius * cos(glm::radians(currentAngle));
        float y = cannonHeight + Cannon::radius * sin(glm::radians(currentAngle));
        float z = -Cannon::cannonLength;

        vertices.push_back(VertexFormat(glm::vec3(x,y,z), glm::vec3(0), Cannon::cannonColor));
    }

    for (int i = 0; i < Cannon::pointCount - 1; i++) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + Cannon::pointCount);

        indices.push_back(i + 1);
        indices.push_back(i + Cannon::pointCount);
        indices.push_back(i + Cannon::pointCount + 1);
    }
    indices.push_back(0);
    indices.push_back(Cannon::pointCount-1);
    indices.push_back(Cannon::pointCount + Cannon::pointCount - 1);

    indices.push_back(0);
    indices.push_back(Cannon::pointCount + Cannon::pointCount - 1);
    indices.push_back(Cannon::pointCount);


    cannon->InitFromData(vertices, indices);
    return cannon;

}