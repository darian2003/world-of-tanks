#include "lab_m1/Tema2/gui.h"
#include <cmath>

#include <iostream>
#include <random>
#include <map>
#include <string>

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

# define PI 3.14159265358979323846

using namespace m1;

Mesh* gui::CreateMap(const std::string &name, float side, glm::vec3 color1, glm::vec3 color2) {

     std::vector<VertexFormat> vertices =
    {
       VertexFormat(glm::vec3(-side/2,0,-side/2), glm::vec3(0), color1),
       VertexFormat(glm::vec3(side/2,0,-side/2), glm::vec3(0), color1),
       VertexFormat(glm::vec3(side/2,0,side/2), glm::vec3(0), color1),
       VertexFormat(glm::vec3(-side/2,0,side/2), glm::vec3(0), color1),

       VertexFormat(glm::vec3(-side/2,0,-side/2), glm::vec3(0), color2),
       VertexFormat(glm::vec3(side/2,0,-side/2), glm::vec3(0), color2),
       VertexFormat(glm::vec3(side/2,0,side/2), glm::vec3(0), color2),
       VertexFormat(glm::vec3(-side/2,0,side/2), glm::vec3(0), color2),

       VertexFormat(glm::vec3(-side/2,side,-side/2), glm::vec3(0), color2),
       VertexFormat(glm::vec3(side/2,side,-side/2), glm::vec3(0), color2),
       VertexFormat(glm::vec3(side/2,side,side/2), glm::vec3(0), color2),
       VertexFormat(glm::vec3(-side/2,side,side/2), glm::vec3(0), color2),
    };

    Mesh* map = new Mesh(name);
    std::vector<unsigned int> indices = { 
        // LOWERBASE
        0,1,2,
        0,2,3,
    };

    map->InitFromData(vertices, indices);
    return map;
}

Mesh* gui::CreateAdvancedCannonBall(const std::string &name, glm::vec3 color) {

    std::vector<VertexFormat> vertices = {};

    Mesh* cannonBall = new Mesh(name);
    std::vector<unsigned int> indices = {};

    for (int i = 0; i < m1::CannonBall::levels; i++) {
        for (int j = 0; j < m1::CannonBall::pointCount; j++) {
            float x = m1::CannonBall::radius * sin(2 * M_PI * j / m1::CannonBall::pointCount) * sin(2 * M_PI * i / m1::CannonBall::levels);
            float y = m1::CannonBall::radius * cos(2 * M_PI * i / m1::CannonBall::levels);
            float z = m1::CannonBall::radius * cos(2 * M_PI * j / m1::CannonBall::pointCount) * sin(2 * M_PI * i / m1::CannonBall::levels);
            vertices.push_back(VertexFormat(glm::vec3(x, y, z), glm::vec3(0), color));
        }
    }

    for (int i = 0; i < m1::CannonBall::levels; i++) {
        for (int j = 0; j < m1::CannonBall::pointCount; j++) {
            int a = i * m1::CannonBall::pointCount + j;
            int b = i * m1::CannonBall::pointCount + (j + 1) % m1::CannonBall::pointCount;
            int c = (i + 1) * m1::CannonBall::pointCount + j;
            int d = (i + 1) * m1::CannonBall::pointCount + (j + 1) % m1::CannonBall::pointCount;
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);
            indices.push_back(b);
            indices.push_back(c);
            indices.push_back(d);
        }
    }

    cannonBall->InitFromData(vertices, indices);
    return cannonBall;
}

Mesh* gui::CreateCannonBall(const std::string &name, glm::vec3 color) {

    std::vector<VertexFormat> vertices = {};

    Mesh* cannonBall = new Mesh(name);
    std::vector<unsigned int> indices = {};

float x, y, z, xy;                              // vertex position
float nx, ny, nz, lengthInv = 1.0f / CannonBall::radius;    // vertex normal
float s, t;                                     // vertex texCoord

float sectorStep = 2 * PI / CannonBall::sectorCount;
float stackStep = PI / CannonBall::stackCount;
float sectorAngle, stackAngle;

for(int i = 0; i <= CannonBall::stackCount; ++i)
{
    stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
    xy = CannonBall::radius * cosf(stackAngle);             // r * cos(u)
    z = CannonBall::radius * sinf(stackAngle);              // r * sin(u)

    // add (sectorCount+1) vertices per stack
    // first and last vertices have same position and normal, but different tex coords
    for(int j = 0; j <= CannonBall::sectorCount; ++j)
    {
        sectorAngle = j * sectorStep;           // starting from 0 to 2pi

        // vertex position (x, y, z)
        x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
        y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
        vertices.push_back(VertexFormat(glm::vec3(x, y, z), glm::vec3(0), color));
    }
}
    // generate CCW index list of sphere triangles
// k1--k1+1
// |  / |
// | /  |
// k2--k2+1
std::vector<int> lineIndices;
int k1, k2;
for(int i = 0; i < CannonBall::stackCount; ++i)
{
    k1 = i * (CannonBall::sectorCount + 1);     // beginning of current stack
    k2 = k1 + CannonBall::sectorCount + 1;      // beginning of next stack

    for(int j = 0; j < CannonBall::sectorCount; ++j, ++k1, ++k2)
    {
        // 2 triangles per sector excluding first and last stacks
        // k1 => k2 => k1+1
        if(i != 0)
        {
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);
        }

        // k1+1 => k2 => k2+1
        if(i != (CannonBall::stackCount-1))
        {
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }

        // store indices for lines
        // vertical lines for all stacks, k1 => k2
        lineIndices.push_back(k1);
        lineIndices.push_back(k2);
        if(i != 0)  // horizontal lines except 1st stack, k1 => k+1
        {
            lineIndices.push_back(k1);
            lineIndices.push_back(k1 + 1);
        }
    }
}


    cannonBall->InitFromData(vertices, indices);
    return cannonBall;
}

std::vector<m1::Building*> gui::generateBuildings(float map_side, float safety_radius, int nr) {
    std::vector<m1::Building*> map;
    for (int i = 0; i < nr; i++) {
        float posx = rand() % (int)map_side - map_side / 2; 
        float posz = rand() % (int)map_side - map_side / 2;
        if (posx <= safety_radius && posx >= -safety_radius && posz <= safety_radius && posz >= -safety_radius) {
            i--;
            continue;
        }
        float posy = 0;
        float x = rand() % ((int)map_side / 10) + 1;
        float y = rand() % ((int)map_side / 10) + 3;
        float z = rand() % ((int)map_side / 10) + 1;
        // if (0,0,0) is in the building, discard building
        if (posx - x / 2 <= 0 && posx + x / 2 >= 0 && posz - z / 2 <= 0 && posz + z / 2 >= 0) {
            i--;
            continue;
        }
        if (posx - x / 2 < -map_side / 2) {
            x = abs(map_side / 2 - abs(posx));
        }
        if (posx + x / 2 > map_side / 2) {
            x = abs(map_side / 2 - abs(posx));
        }
        if (posz - z / 2 < -map_side / 2) {
            z = abs(map_side / 2 - abs(posz));
        }
        if (posz + z / 2 > map_side / 2) {
            z = abs(map_side / 2 - abs(posz));
        }

        float r = (float)rand() / RAND_MAX;
        float g = (float)rand() / RAND_MAX;
        float b = (float)rand() / RAND_MAX;
        map.push_back(new m1::Building(glm::vec3(posx, posy, posz), x, y, z, glm::vec3(r, g, b)));
    }
    return map;
}

Mesh* gui::CreateBuilding(Building* building, const std::string &name) {

     std::vector<VertexFormat> vertices =
    {
        // LOWERBASE
        VertexFormat(glm::vec3(-building->x/2,0,-building->z/2), glm::vec3(0), building->color),
        VertexFormat(glm::vec3(building->x/2,0,-building->z/2), glm::vec3(0), building->color),
        VertexFormat(glm::vec3(building->x/2,0,building->z/2), glm::vec3(0), building->color),
        VertexFormat(glm::vec3(-building->x/2,0,building->z/2), glm::vec3(0), building->color),
        // UPPERBASE
        VertexFormat(glm::vec3(-building->x/2,building->y,-building->z/2), glm::vec3(0), building->color),
        VertexFormat(glm::vec3(building->x/2,building->y,-building->z/2), glm::vec3(0), building->color),
        VertexFormat(glm::vec3(building->x/2,building->y,building->z/2), glm::vec3(0), building->color),
        VertexFormat(glm::vec3(-building->x/2,building->y,building->z/2), glm::vec3(0), building->color),
    };

    Mesh* mesh = new Mesh(name);
    std::vector<unsigned int> indices = { 
        // lowerbase
        0, 1, 2,
        0, 2, 3, 
        // upperbase
        4, 5, 6,
        4, 6, 7,
        // sides
        3, 7, 4,
        3, 4, 0,
        0, 4, 5,
        0, 5, 1,
        1, 5, 6,
        1, 6, 2,
        2, 6, 3,
        3, 6, 7
    };

    mesh->InitFromData(vertices, indices);
    return mesh;
}

bool gui::CheckCollisionBullet(CannonBall* cannonBall, std::vector<m1::Building*> buildings) {
    for (auto building : buildings) {
        if (cannonBall->position.x > building->position.x - building->x / 2 && cannonBall->position.x < building->position.x + building->x / 2 &&
            cannonBall->position.z > building->position.z - building->z / 2 && cannonBall->position.z < building->position.z + building->z / 2) {
                return true;
        }
    }
    return false;
}

int gui::GetRandomNumberInRange(const int minInclusive, const int maxInclusive)
{
    static std::random_device randomDevice;
    static std::default_random_engine randomEngine(randomDevice());

    std::uniform_int_distribution<int> uniformDist(minInclusive, maxInclusive);

    return uniformDist(randomEngine);
}

m1::MovementState gui::GetNextMovementState(const m1::MovementState currentState)
{
    int randomChange = gui::GetRandomNumberInRange(0, 1);
    MovementState nextState = currentState;
    
    switch (currentState)
    {
    case m1::MovementState::GoingForward:
    case m1::MovementState::GoingBackward:
        nextState = (randomChange == 1)
            ? m1::MovementState::InPlaceRotationLeft
            : m1::MovementState::InPlaceRotationRight;
        break;

    case m1::MovementState::InPlaceRotationLeft:
    case m1::MovementState::InPlaceRotationRight:
        nextState = (randomChange == 1)
            ? m1::MovementState::GoingForward
            : m1::MovementState::GoingBackward;
        break;
        
    default:
        break;
    }

    return nextState;
}

std::string gui::GetMovementStateName(const m1::MovementState state)
{
    static const std::map<MovementState, std::string> kStateNames
    {
        { m1::MovementState::GoingForward, "GoingForward" },
        { m1::MovementState::GoingBackward, "GoingBackward" },
        { m1::MovementState::InPlaceRotationLeft, "InPlaceRotationLeft" },
        { m1::MovementState::InPlaceRotationRight, "InPlaceRotationRight" },
    };

    std::string s = "";

   if (kStateNames.find(state) != kStateNames.end())
    {
        s = kStateNames.at(state);  
    }

    return s;
}


void gui::MoveEnemies(std::vector<Tank*> enemies, float enemy_speed, float enemy_rotation_speed, float deltaTimeSeconds, std::vector<m1::Building*> buildings) {
    MovementState state = MovementState::GoingForward;
    for (auto enemy : enemies) {
        enemy->timer -= deltaTimeSeconds;
        
        if (enemy->timer <= 0) {
           // printf("reset timer\n");
            enemy->timer = 4;
            /*
            *  Instead of using a for-loop, you will be calling these functions
            *  whenever a sum of delta times goes past a certain value (then you
            *  reset that sum to zero and start accumulating again).
            */
            state = GetNextMovementState(state);
         //   printf("state = %s\n", GetMovementStateName(state).c_str());
            enemy->state = state;
        }
        float oldx = enemy->x, oldz = enemy->z;
        if (enemy->state == MovementState::GoingForward) {
            enemy->z -= enemy_speed * deltaTimeSeconds * cos(RADIANS(enemy->tankAngle));
            enemy->x -= enemy_speed * deltaTimeSeconds * sin(RADIANS(enemy->tankAngle));
            if (gui::CheckCollisionTankBuilding(enemy, buildings)) {
                enemy->z = oldz;
                enemy->x = oldx;
                enemy->state = MovementState::GoingBackward;
            } 
        } else if (enemy->state == MovementState::GoingBackward) {
            enemy->z += enemy_speed * deltaTimeSeconds * cos(RADIANS(enemy->tankAngle));
            enemy->x += enemy_speed * deltaTimeSeconds * sin(RADIANS(enemy->tankAngle));
            if (gui::CheckCollisionTankBuilding(enemy, buildings)) {
                enemy->z = oldz;
                enemy->x = oldx;
                enemy->state = MovementState::GoingForward;
            } 
        } else if (enemy->state == MovementState::InPlaceRotationLeft) {
            enemy->tankAngle += enemy_rotation_speed * deltaTimeSeconds;
            if (enemy->inRange)
                enemy->turretAngle -= enemy_rotation_speed * deltaTimeSeconds;
        } else if (enemy->state == MovementState::InPlaceRotationRight) {
            enemy->tankAngle -= enemy_rotation_speed * deltaTimeSeconds;
            if (enemy->inRange)
                enemy->turretAngle += enemy_rotation_speed * deltaTimeSeconds;
        }
    }
}

std::vector<Tank*> gui::GenerateEnemies(float map_side, float safety_radius, int nr, std::vector<Building*> buildings) {
    std::vector<Tank*> enemies;
    for (int i = 0; i < nr; i++) {
        float posx = rand() % (int)map_side - map_side / 2; 
        float posz = rand() % (int)map_side - map_side / 2;
        if (posx < safety_radius && posx > -safety_radius && posz < safety_radius && posz > -safety_radius) {
            i--;
            continue;
        }
        bool ok = true;
        for (auto building : buildings) {
            ok = true;
            if (posx >= building->position.x - building->x / 2 && posx <= building->position.x + building->x / 2 &&
                posz >= building->position.z - building->z / 2 && posz <= building->position.z + building->z / 2) {
                    ok = false;
                    break;
            }
        }
        if (ok)
            enemies.push_back(new Tank(posx, 0, posz));
        else
            i--;
    }
    return enemies;
}

// made by cop
void gui::EnemiesShoot(std::vector<Tank*> enemies, std::vector<CannonBall*> &enemyCannonBalls, Tank *myTank, float range, float deltaTimeSeconds, float rotation_speed) { 
    for (auto enemy : enemies) {
        float distance = gui::getDistace(glm::vec3(myTank->x, myTank->y, myTank->z), glm::vec3(enemy->x, enemy->y, enemy->z));
         if (distance > range) {
          //  enemy->reloadTime = 3;  
            if (enemy->rotationState == m1::RotationState::GoingLeft) {
                enemy->turretAngle += rotation_speed * deltaTimeSeconds;
            } else if (enemy->rotationState == RotationState::GoingRight) {
                enemy->turretAngle -= rotation_speed * deltaTimeSeconds;
            }
            enemy->rotationTimer -= deltaTimeSeconds;
            if (enemy->rotationTimer <= 0) {
                enemy->rotationTimer = rand() % 5 + 1;
                
                if (enemy->rotationState == RotationState::GoingLeft) {
                    enemy->rotationState = RotationState::GoingRight;
                } else if (enemy->rotationState == RotationState::GoingRight) {
                    enemy->rotationState = RotationState::GoingLeft;
                }
            }
                continue;
        }
        // we are in their range
        enemy->inRange = true;
        enemy->reloadTime -= deltaTimeSeconds;
        glm::vec3 dir = glm::normalize(glm::vec3(myTank->x - enemy->x, 0, myTank->z - enemy->z));
        // calculate the angle between dir and OZ
        float angle = angleBetweenAxes(dir.x, dir.y, dir.z, 0, 0, 1);
        enemy->turretAngle = angle - enemy->tankAngle;
        if (dir[0] > 0) {
            enemy->turretAngle -= 180;
        } else {
            enemy->turretAngle -= 2 * angle + 180;
        }
        angle = enemy->tankAngle + enemy->turretAngle;
        if (enemy->reloadTime <= 0) {
            enemy->reloadTime = 3;
            dir = glm::rotate(glm::mat4(1.0f), RADIANS(angle), glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
            dir[1] = 0;
            CannonBall *cannonBall = new CannonBall(glm::vec3(enemy->x - Cannon::cannonLength * sin(RADIANS(angle)), 0.36, enemy->z - Cannon::cannonLength * cos(RADIANS(angle))), glm::vec3(dir));
            enemyCannonBalls.push_back(cannonBall);
        }
    }
}

// if enemy is immobile
void gui::CheckCollisionEnemyBullet(std::vector<CannonBall*> &enemyCannonBalls, std::vector<Tank*> &enemies) {
    for (auto enemy : enemies) {
        for (auto it = enemyCannonBalls.begin(); it != enemyCannonBalls.end(); /* no increment here */) {
            auto cannonBall = *it;
            float distance = gui::getDistace(glm::vec3(cannonBall->position[0], cannonBall->position[1], cannonBall->position[2]), glm::vec3(enemy->x, enemy->y, enemy->z));

            if (distance < CannonBall::radius + Tank::lowerBaseLength) {
                enemy->hp--;

                // erase cannonball
                it = enemyCannonBalls.erase(it);
            } else {
                // Move to the next cannonball if no collision
                ++it;
            }
        }
    }
}


// if enemy disappears
int gui::CheckCollisionEnemyBullet2(std::vector<CannonBall*> &enemyCannonBalls, std::vector<Tank*> &enemies) {
    int score = 0;
    for (auto itEnemy = enemies.begin(); itEnemy != enemies.end(); /* no increment here */) {
        auto enemy = *itEnemy;

        for (auto itCannonBall = enemyCannonBalls.begin(); itCannonBall != enemyCannonBalls.end(); /* no increment here */) {
            auto cannonBall = *itCannonBall;
            float distance = gui::getDistace(glm::vec3(cannonBall->position[0], cannonBall->position[1], cannonBall->position[2]), glm::vec3(enemy->x, enemy->y, enemy->z));

            if (distance < CannonBall::radius + Tank::lowerBaseLength) {
                enemy->hp--;

                // erase cannonball
                itCannonBall = enemyCannonBalls.erase(itCannonBall);
            } else {
                // Move to the next cannonball if no collision
                ++itCannonBall;
            }
        }

        if (enemy->hp <= 0) {
            // erase enemy
            itEnemy = enemies.erase(itEnemy);
            score++;
        } else {
            // Move to the next enemy if not removed
            ++itEnemy;
        }
    }
    return score;
}

float gui::getDistace(glm::vec3 a, glm::vec3 b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.z - b.z, 2));
}

void gui::CheckCollisionBulletBuilding(std::vector<CannonBall*> &myCannonBalls, std::vector<Building*> buildings) {
    for (auto itBuilding = buildings.begin(); itBuilding != buildings.end(); /* no increment here */) {
        auto building = *itBuilding;

        for (auto itCannonBall = myCannonBalls.begin(); itCannonBall != myCannonBalls.end(); /* no increment here */) {
            auto cannonBall = *itCannonBall;
            float distance = gui::getDistace(glm::vec3(cannonBall->position[0], cannonBall->position[1], cannonBall->position[2]), glm::vec3(building->position.x, building->position.y, building->position.z));
            float x1 = cannonBall->position[0];
            float z1 = cannonBall->position[2];
            float x2 = building->position.x;
            float z2 = building->position.z;
            if (x1 > x2 - building->x / 2 && x1 < x2 + building->x / 2 && z1 > z2 - building->z / 2 && z1 < z2 + building->z / 2) {
                // erase cannonball
                itCannonBall = myCannonBalls.erase(itCannonBall);
            } else {
                // Move to the next cannonball if no collision
                ++itCannonBall;
            }
        }

        // Move to the next building if not removed
        ++itBuilding;
    }
}

void gui::TankToTankCollision(Tank *tank1, Tank *tank2, implemented::Camera *camera) {

    float distance = gui::getDistace(glm::vec3(tank1->x, tank1->y, tank1->z), glm::vec3(tank2->x, tank2->y, tank2->z));

    if (distance < Tank::lowerBaseLength) {
        glm::vec3 dif = glm::vec3(tank2->x, tank2->y, tank2->z) - glm::vec3(tank1->x, tank1->y, tank1->z);
        float modp = Tank::lowerBaseLength - distance;
        glm::vec3 p = glm::normalize(dif) * modp;
        tank1->x -= p.x * 0.5;
        tank1->z -= p.z * 0.5; 
        tank2->x += p.x * 0.5;
        tank2->z += p.z * 0.5;
        if (camera != NULL) {
            camera->MoveCollision(-p * glm::vec3(0.5));
        }
    }
}


bool gui::CheckCollisionTankBuilding(Tank *tank, std::vector<Building*> buildings) {
    for (int i = 0 ; i < 8; i++) {
        float x1 = tank->x + Tank::lowerBaseLength / 2 * sin(RADIANS(tank->tankAngle + i * 45));
        float z1 = tank->z + Tank::lowerBaseLength / 2 * cos(RADIANS(tank->tankAngle + i * 45));
        for (auto building : buildings) {
            if (x1 > building->position.x - building->x / 2 && x1 < building->position.x + building->x / 2 &&
                z1 > building->position.z - building->z / 2 && z1 < building->position.z + building->z / 2) {
                    return true;
            }
        }
        // the center of the tank should not go outside the map
        if (tank->x < -25 || tank->x > 25 || tank->z < -25 || tank->z > 25)
            return true;
    }
    return false;
}

// Function to calculate the dot product of two vectors
float gui::dotProduct(float x1, float y1, float z1, float x2, float y2, float z2) {
    return x1 * x2 + y1 * y2 + z1 * z2;
}

// Function to calculate the magnitude of a vector
float gui::magnitude(float x, float y, float z) {
    return std::sqrt(x * x + y * y + z * z);
}

// Function to calculate the angle in degrees between two vectors
float gui::angleBetweenAxes(float x1, float y1, float z1, float x2, float y2, float z2) {
     float dot = dotProduct(x1, y1, z1, x2, y2, z2);
    float mag1 = magnitude(x1, y1, z1);
    float mag2 = magnitude(x2, y2, z2);

    // Calculate the angle in radians using the dot product and magnitudes
    float radians = std::acos(dot / (mag1 * mag2));

    // Convert radians to degrees
    float degrees = radians * (180.0f / M_PI);

    // Ensure the angle is within the range [0, 360)
    degrees = fmod(degrees, 360.0f);

    if (degrees < 0.0f) {
        degrees += 360.0f;
    }

    return degrees;
}

float gui::angleBetweenVectors(float x1, float y1, float z1, float x2, float y2, float z2) {
    float dot = dotProduct(x1, y1, z1, x2, y2, z2);
    float mag1 = magnitude(x1, y1, z1);
    float mag2 = magnitude(x2, y2, z2);

    // Ensure denominators are not zero
    if (mag1 == 0.0f || mag2 == 0.0f) {
        std::cerr << "Error: One of the vectors has zero magnitude." << std::endl;
        return 0.0f;
    }

    // Calculate the angle in radians using the dot product and magnitudes
    float radians = std::acos(dot / (mag1 * mag2));

    // Convert radians to degrees
    float degrees = radians * (180.0f / M_PI);

    return degrees;
}