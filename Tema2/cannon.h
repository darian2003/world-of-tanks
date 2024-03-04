#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/Tema2/tank.h"
#include "lab_m1/Tema2/turret.h"

namespace m1 {

    class Turret;
    class Tank;

    class Cannon {
        public:
            Cannon(){}  // Constructor
            ~Cannon(){} // Destructor

            static Mesh* CreateCannon(const std::string &name, bool isFriendly);

        public:
            static glm::vec3 cannonColor;
            static int pointCount;
            static float radius;
            static float cannonHeight;
            static float cannonLength;

    };
}