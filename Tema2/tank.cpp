#include <iostream>
#include "lab_m1/Tema2/tank.h"
#include <cmath>

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

float Tank::lowerBaseHeight = 0.1;
float Tank::lowerBaseLength = 1.5;
float Tank::lowerBaseWidth = 1;
float Tank::upperBaseHeight = Tank::lowerBaseHeight * 3;
float Tank::upperBaseLength = Tank::lowerBaseLength * 0.8;
float Tank::upperBaseWidth = Tank::lowerBaseWidth * 0.8;
float Tank::lowerToMiddleOffset = (Tank::middleTrackLength - Tank::lowerTrackLength)/2;


float Tank::trackHeight = 0.13;
float Tank::lowerTrackLength = Tank::lowerBaseLength * 0.95;
float Tank::lowerTrackHeight = Tank::lowerBaseHeight/2;
float Tank::trackWidth = Tank::lowerBaseWidth * 0.2;
float Tank::trackWidthOffset = Tank::lowerBaseWidth * 0.05;
float Tank::middleTrackLength = Tank::lowerBaseLength * 1.1;
float Tank::upperTrackLength = Tank::lowerBaseLength * 0.95;

glm::vec3 Tank::baseColorFriendly = glm::vec3(0,0.1,0);
glm::vec3 Tank::trackColor = glm::vec3(0.9,0.9,0.9);

Mesh *Tank::CreateTank(const std::string &name, bool isFriendly) {

    glm::vec3 center = glm::vec3(0,0,0);
    glm::vec3 lowerBaseColor = glm::vec3(0, 0.1, 0);
    glm::vec3 turretColor = glm::vec3(0);
    if (isFriendly) {
        lowerBaseColor = Tank::baseColorFriendly;
    } else {
        lowerBaseColor = glm::vec3(0.3, 0, 0);
    }

    // left bottom corner of lowerbase left track
    glm::vec3 leftTrackCorner = glm::vec3(-Tank::lowerBaseWidth/2+Tank::trackWidthOffset,0,-Tank::lowerTrackLength/2);
    float lowerToMiddleOffset = (Tank::middleTrackLength - Tank::lowerTrackLength)/2;
    // left bottom corner of lowerbase right track
    glm::vec3 rightTrackCorner = glm::vec3(Tank::lowerBaseWidth/2-Tank::trackWidth-Tank::trackWidthOffset,0,-Tank::lowerTrackLength/2);


    std::vector<VertexFormat> vertices =
    {
        // lowerbase 
        VertexFormat(glm::vec3(-Tank::lowerBaseWidth/2,Tank::lowerBaseHeight,-Tank::lowerBaseLength/2), glm::vec3(0), lowerBaseColor),
        VertexFormat(glm::vec3(Tank::lowerBaseWidth/2,Tank::lowerBaseHeight,-Tank::lowerBaseLength/2), glm::vec3(0), lowerBaseColor),
        VertexFormat(glm::vec3(Tank::lowerBaseWidth/2,Tank::lowerBaseHeight,Tank::lowerBaseLength/2), glm::vec3(0), lowerBaseColor),
        VertexFormat(glm::vec3(-Tank::lowerBaseWidth/2,Tank::lowerBaseHeight,Tank::lowerBaseLength/2), glm::vec3(0), lowerBaseColor),
        // upperbase 
        VertexFormat(glm::vec3(-Tank::upperBaseWidth/2,Tank::upperBaseHeight,-Tank::upperBaseLength/2), glm::vec3(0), lowerBaseColor),
        VertexFormat(glm::vec3(Tank::upperBaseWidth/2,Tank::upperBaseHeight,-Tank::upperBaseLength/2), glm::vec3(0), lowerBaseColor),
        VertexFormat(glm::vec3(Tank::upperBaseWidth/2,Tank::upperBaseHeight,Tank::upperBaseLength/2), glm::vec3(0), lowerBaseColor),
        VertexFormat(glm::vec3(-Tank::upperBaseWidth/2,Tank::upperBaseHeight,Tank::upperBaseLength/2), glm::vec3(0), lowerBaseColor),
        // left track
        // lower part. Starting from 8
        VertexFormat(leftTrackCorner, glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner + glm::vec3(Tank::trackWidth,0,0), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner +glm::vec3(Tank::trackWidth,0,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner +glm::vec3(0,0,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
        // middle part. From 12
        VertexFormat(leftTrackCorner+glm::vec3(0,Tank::trackHeight/2,-lowerToMiddleOffset), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner+glm::vec3(Tank::trackWidth,Tank::trackHeight/2,-lowerToMiddleOffset), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner+glm::vec3(Tank::trackWidth,Tank::trackHeight/2,-lowerToMiddleOffset+Tank::middleTrackLength), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner+glm::vec3(0,Tank::trackHeight/2,-lowerToMiddleOffset+Tank::middleTrackLength), glm::vec3(0), Tank::trackColor),
        // upper part. From 16
        VertexFormat(leftTrackCorner+glm::vec3(0,Tank::trackHeight,0), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner + glm::vec3(Tank::trackWidth,Tank::trackHeight,0), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner +glm::vec3(Tank::trackWidth,Tank::trackHeight,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
        VertexFormat(leftTrackCorner +glm::vec3(0,Tank::trackHeight,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
        // right track
        // lower part. Starting from 20
        VertexFormat(rightTrackCorner, glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner + glm::vec3(Tank::trackWidth,0,0), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner +glm::vec3(Tank::trackWidth,0,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner +glm::vec3(0,0,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
        // middle part. From 24
        VertexFormat(rightTrackCorner+glm::vec3(0,Tank::trackHeight/2,-lowerToMiddleOffset), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner+glm::vec3(Tank::trackWidth,Tank::trackHeight/2,-lowerToMiddleOffset), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner+glm::vec3(Tank::trackWidth,Tank::trackHeight/2,-lowerToMiddleOffset+Tank::middleTrackLength), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner+glm::vec3(0,Tank::trackHeight/2,-lowerToMiddleOffset+Tank::middleTrackLength), glm::vec3(0), Tank::trackColor),
        // upper part. From 28
        VertexFormat(rightTrackCorner+glm::vec3(0,Tank::trackHeight,0), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner+glm::vec3(Tank::trackWidth,Tank::trackHeight,0), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner+glm::vec3(Tank::trackWidth,Tank::trackHeight,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
        VertexFormat(rightTrackCorner+glm::vec3(0,Tank::trackHeight,Tank::lowerTrackLength), glm::vec3(0), Tank::trackColor),
    };

    printf("%f %f %f\n", lowerBaseColor[0], lowerBaseColor[1], lowerBaseColor[2]);

    Mesh* tank = new Mesh(name);
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
        3, 6, 7,
        // LEFT TRACK
        // lower track layer
        8,9,10,
        8,10,11,
        // middle track layer
        12,13,14,
        12,14,15,
        // upper track layer
        16,17,18,
        16,18,19,
        // RIGHT TRACK
        // lower track layer
        20,21,22,
        20,22,23,
        // middle track layer
        24,25,26,
        24,26,27,
        // upper track layer
        28,29,30,
        28,30,31,
        // low-middle track left
        8,9,12,
        12,9,13,
        10,11,14,
        14,11,15,
        8,11,12,
        11,12,15,
        9,10,13,
        10,13,14,
        // middle-high track left
        12,13,16,
        16,13,17,
        14,15,18,
        18,15,19,
        12,15,16,
        15,16,19,
        13,14,17,
        14,17,18,
        // low middle right
        20,21,24,
        24,21,25,
        22,23,26,
        26,23,27,
        20,23,24,
        23,24,27,
        21,22,25,
        22,25,26,
        // middle-high right
        24,25,28,
        28,25,29,
        26,27,30,
        30,27,31,
        24,27,28,
        27,28,31,
        25,26,29,
        26,29,30,
    };

    tank->InitFromData(vertices, indices);
    return tank;
}