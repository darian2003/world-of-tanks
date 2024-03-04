#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/Tema2/turret.h"
#include "lab_m1/Tema2/cannon.h"

namespace m1 {

    class Turret;
    class Cannon;

     enum class MovementState
    {
        GoingForward,
        GoingBackward,
        InPlaceRotationLeft,
        InPlaceRotationRight
    };

    enum class RotationState
    {
        GoingLeft,
        GoingRight
    };

    class Tank {

        public: 
            Tank() {}
            ~Tank(){}
            static Mesh *CreateTank(const std::string &name, bool isFriendly);
            static float GetLowerBaseHeight() { return lowerBaseHeight; }
            static float GetLowerBaseLength() { return lowerBaseLength; }
            static float GetLowerBaseWidth() { return lowerBaseWidth; }
            static float GetUpperBaseHeight() { return upperBaseHeight; }
            static float GetUpperBaseLength() { return upperBaseLength; }
            static float GetUpperBaseWidth() { return upperBaseWidth; }
            // constructor
            Tank(float x, float y, float z) {
                Set(x, y, z);
            }
            // setter
            void Set(float x, float y, float z) {
                this->x = x;    
                this->y = y;    
                this->z = z;
                this->state = MovementState::GoingForward;
                this->tankAngle = rand() % 360;
            }

        public:
            Turret *turret;
            Cannon *cannon;
            float x = 0, y = 0, z = 0; 
            float tankAngle = 0, turretAngle = 0, cannonAngle = 0;      
            MovementState state; 
            RotationState rotationState = RotationState::GoingLeft;
            float rotationTimer = 5.f;  
            float reloadTime = 0;
            float timer = 4;
            int hp = 3;
            bool inRange = false;

            static float lowerBaseHeight;
            static float lowerBaseLength;
            static float lowerBaseWidth;
            static float upperBaseHeight;
            static float upperBaseLength;
            static float upperBaseWidth;

            static float trackHeight;
            static float lowerTrackLength;
            static float lowerTrackHeight;
            static float trackWidth;
            static float trackWidthOffset;
            static float middleTrackLength;
            static float upperTrackLength;

            static float lowerToMiddleOffset;

            float cannonLength = lowerBaseLength * 0.8;
            float radius = 0.1;
            int pointCount = 12;

            static glm::vec3 baseColorFriendly;
            static glm::vec3 trackColor;



    };
}