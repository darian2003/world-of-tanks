#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {
    class CannonBall {
        public:
            CannonBall() {}
            ~CannonBall(){}

            CannonBall(const glm::vec3& position, const glm::vec3& direction) {
                Set(position, direction);
            }

            void Set(const glm::vec3& position, const glm::vec3& direction) {
                this->direction = glm::normalize(direction);
                this->position = position;
            }

        public:
            glm::vec3 position;
            glm::vec3 direction; // normalized forward vector
            float speed = 0.5;
            float gravity = 0.01;
            float time = 0;
            float maxTime = 100;
            float timeToLive = 6;

            static glm::vec3 color;
            static int pointCount;
            static float radius;
            static int levels;
            static int sectorCount;
            static int stackCount;

    };
}