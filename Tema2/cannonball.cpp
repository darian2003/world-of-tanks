#include <iostream>
#include "lab_m1/Tema2/cannonball.h"
#include <cmath>

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

float CannonBall::radius = 0.1;
int CannonBall::pointCount = 12;
int CannonBall::levels = 5;
int CannonBall::sectorCount = 10;
int CannonBall::stackCount = 10;