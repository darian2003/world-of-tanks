#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/Tema2/tank.h"

namespace m1 {

    class Tank;

    class Turret {

        public:
            Turret(){}  // Constructor
            ~Turret(){} // Destructor

            void fire(); // Function to fire the turret
            void rotate(); // Function to rotate the turret
            void aim(); // Function to aim the turret
            static Mesh *CreateTurret(const std::string &name, bool isFriendly);


        public:
            float angle;
            bool isFiring;
            static float turretLowerBaseHeight;
            static float turretLowerBaseLength;
            static float turretLowerBaseWidth;
            static float turretUpperBaseHeight;
            static float turretUpperBaseLength;
            static float turretUpperBaseWidth;
            static glm::vec3 turretColorFriendly;
    };
}
