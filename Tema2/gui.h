#pragma once

#include <string>
#include <iostream>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/Tema2/cannonball.h"
#include "lab_m1/Tema2/building.h"
#include "lab_m1/Tema2/tank.h"
#include "lab_m1/lab5/lab_camera.h"
#include <cstdlib>

namespace gui {
    Mesh *CreateTank(const std::string &name, bool isFriendly);
    Mesh *CreateMap(const std::string &name, float side, glm::vec3 color1, glm::vec3 color2);
    Mesh *CreateAdvancedCannonBall(const std::string &name, glm::vec3 color);
    Mesh *CreateCannonBall(const std::string &name, glm::vec3 color);
    std::vector<m1::Building*> generateBuildings(float map_side, float safety_radius, int nr);
    Mesh *CreateBuilding(m1::Building* building, const std::string &name);
    bool CheckCollisionBullet(m1::CannonBall* cannonBall, std::vector<m1::Building*> buildings);
    void MoveEnemies(std::vector<m1::Tank*> enemies, float enemy_speed, float enemy_rotation_speed, float deltaTimeSeconds, std::vector<m1::Building *> buildings);
    std::vector<m1::Tank*> GenerateEnemies(float map_side, float safety_radius, int nr, std::vector<m1::Building*> buildings);
    void EnemiesShoot(std::vector<m1::Tank*> enemies, std::vector<m1::CannonBall*> &enemyCannonBalls, m1::Tank *myTank, float range, float deltaTimeSeconds, float rotation_speed);
    void CheckCollisionEnemyBullet(std::vector<m1::CannonBall*> &enemyCannonBalls, std::vector<m1::Tank*> &enemies);
    void TankToTankCollision(m1::Tank *tank1, m1::Tank *tank2, implemented::Camera *camera);
    int CheckCollisionEnemyBullet2(std::vector<m1::CannonBall*> &enemyCannonBalls, std::vector<m1::Tank*> &enemies);
    float getDistace(glm::vec3 a, glm::vec3 b);
    void CheckCollisionBulletBuilding(std::vector<m1::CannonBall*> &myCannonBalls, std::vector<m1::Building*> buildings);
    bool CheckCollisionTankBuilding(m1::Tank *tank, std::vector<m1::Building*> buildings);
    float angleBetweenAxes(float x1, float y1, float z1, float x2, float y2, float z2);
    float magnitude(float x, float y, float z);
    float dotProduct(float x1, float y1, float z1, float x2, float y2, float z2);
    float angleBetweenVectors(float x1, float y1, float z1, float x2, float y2, float z2);


    int GetRandomNumberInRange(const int minInclusive, const int maxInclusive);
    std::string GetMovementStateName(const m1::MovementState state);
    m1::MovementState GetNextMovementState(const m1::MovementState currentState);

}