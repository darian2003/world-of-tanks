
#include <iostream>
#include "lab_m1/Tema2/turret.h"
#include "lab_m1/Tema2/tank.h"
#include "lab_m1/Tema2/cannon.h"

#include <cmath>

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

// Implement the functions defined in turret.h here

// Example implementation of a member function
void Turret::fire() {
    // Code to fire the turret
}

float Turret::turretLowerBaseHeight = Tank::upperBaseHeight + 0.01;
float Turret::turretLowerBaseLength = Tank::upperBaseLength * 0.5;
float Turret::turretLowerBaseWidth = Tank::upperBaseWidth * 0.75;
float Turret::turretUpperBaseHeight = Turret::turretLowerBaseHeight + 0.1;
float Turret::turretUpperBaseLength = Turret::turretLowerBaseLength * 0.8;
float Turret::turretUpperBaseWidth = Turret::turretLowerBaseWidth * 0.8;
glm::vec3 Turret::turretColorFriendly = glm::vec3(0, 0.25, 0);

Mesh *Turret::CreateTurret(const std::string &name, bool isFriendly) {

    glm::vec3 center = glm::vec3(0,0,0);
    glm::vec3 lowerBaseColor = glm::vec3(0, 0.1, 0);
    glm::vec3 turretColor = glm::vec3(0);
    glm::vec3 *color;
    if (isFriendly) {
        turretColor = Turret::turretColorFriendly;
    } else {
        turretColor = glm::vec3(1, 0, 0);
    }

    Mesh* turret = new Mesh(name);

    std::vector<VertexFormat> vertices =
    {
        // turret lower base
        VertexFormat(glm::vec3(-Turret::turretLowerBaseWidth/2,Turret::turretLowerBaseHeight,-Turret::turretLowerBaseLength/2), glm::vec3(0), turretColor),
        VertexFormat(glm::vec3(Turret::turretLowerBaseWidth/2,Turret::turretLowerBaseHeight,-Turret::turretLowerBaseLength/2), glm::vec3(0), turretColor),
        VertexFormat(glm::vec3(Turret::turretLowerBaseWidth/2,Turret::turretLowerBaseHeight,Turret::turretLowerBaseLength/2), glm::vec3(0), turretColor),
        VertexFormat(glm::vec3(-Turret::turretLowerBaseWidth/2,Turret::turretLowerBaseHeight,Turret::turretLowerBaseLength/2), glm::vec3(0), turretColor),
        // turret upper base
        VertexFormat(glm::vec3(-Turret::turretUpperBaseWidth/2,Turret::turretUpperBaseHeight,-Turret::turretUpperBaseLength/2), glm::vec3(0), turretColor),
        VertexFormat(glm::vec3(Turret::turretUpperBaseWidth/2,Turret::turretUpperBaseHeight,-Turret::turretUpperBaseLength/2), glm::vec3(0), turretColor),
        VertexFormat(glm::vec3(Turret::turretUpperBaseWidth/2,Turret::turretUpperBaseHeight,Turret::turretUpperBaseLength/2), glm::vec3(0), turretColor),
        VertexFormat(glm::vec3(-Turret::turretUpperBaseWidth/2,Turret::turretUpperBaseHeight,Turret::turretUpperBaseLength/2), glm::vec3(0), turretColor),
    };

    std::vector<unsigned int> indices =
    {
        // turret lower base
        0, 1, 2,
        0, 2, 3,
        // turret upper base
        4, 5, 6,
        4, 6, 7,
        // sides
        0, 4, 1,
        4, 5, 1,
        1, 5, 2,
        2, 5, 6,
        2, 6, 3,
        3, 6, 7,
        3, 7, 0,
        0, 7, 4,
    };

    turret->InitFromData(vertices, indices);
    return turret;

}
