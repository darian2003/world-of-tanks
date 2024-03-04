#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {
    class Building {
        public:
            Building() {}
            ~Building(){}

            Building(const glm::vec3& position, float x, float y, float z, glm::vec3 color) {
                Set(position, x, y, z, color);
            }

            void Set(const glm::vec3& position, float x, float y, float z, glm::vec3 color) {
                this->position = position;
                this->x = x;    
                this->y = y;    
                this->z = z;
                this->color = color;
            }

        public:
            glm::vec3 position;
            float x, y, z;
            glm::vec3 color;
    };
    
}