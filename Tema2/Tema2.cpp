#include "lab_m1/Tema2/Tema2.h"



#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{

    polygonMode = GL_FILL;
    myTank->turret = new Turret();
    myTank->cannon = new Cannon();

    renderCameraTarget = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 6), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {    
        Mesh* friendly_tank = Tank::CreateTank("friendly_tank", true);
        AddMeshToList(friendly_tank);
    }

    {    
        Mesh* enemy_tank = Tank::CreateTank("enemy_tank", false);
        AddMeshToList(enemy_tank);
    }

    {
        Mesh* turret = Turret::CreateTurret("enemy_turret", false);
        AddMeshToList(turret);
        turret = Turret::CreateTurret("turret", true);
        AddMeshToList(turret);
    }

    {
        Mesh* cannon = Cannon::CreateCannon("cannon", true);
        AddMeshToList(cannon);
    }

    {
        Mesh* advanced_cannonballcannonball = gui::CreateAdvancedCannonBall("advanced_cannonball", glm::vec3(1,0,0));
        AddMeshToList(advanced_cannonballcannonball);
        Mesh* cannonball = gui::CreateCannonBall("cannonball", glm::vec3(0.1,0.1,0.1));
        AddMeshToList(cannonball);
        cannonball = gui::CreateCannonBall("enemy_cannonball", glm::vec3(1,1,0));
        AddMeshToList(cannonball);
    }

    {
        buildings = gui::generateBuildings(map_side, safety_radius, number_of_buildings);
        for (int i = 0; i < buildings.size(); i++) {
            Mesh* building = gui::CreateBuilding(buildings[i], "building"+std::to_string(i));
            AddMeshToList(building);
        }
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *map = gui::CreateMap("map", map_side, glm::vec3(0, 0.3, 0.7), glm::vec3(0, 0.5, 0.5));
        AddMeshToList(map);
    }

    enemies = gui::GenerateEnemies(map_side, safety_radius_enemies, number_of_enemies, buildings);


    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    projectionMatrix = perspective;

}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{

    if (myTank->hp <= 0) {
        deltaTimeSeconds = 0;
        if (!game_ended) {
            printf("GAME OVER\n");
            printf("SCORE: %d\n", score);
            game_ended = true;
        }
    }

    game_time -= deltaTimeSeconds;
    if (game_time <= 0) {
        deltaTimeSeconds = 0;
        if (!game_ended) {
            printf("TIME IS UP\n");
            printf("SCORE: %d\n", score);
            game_ended = true;
        }
    }

    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    if (enemies.size() < number_of_enemies) {
        std::vector<Tank*> new_enemies = gui::GenerateEnemies(map_side, safety_radius_enemies, number_of_enemies - enemies.size(), buildings);
        for (auto enemy : new_enemies) {
            enemies.push_back(enemy);
        }
    }

    myTank->reloadTime -= deltaTimeSeconds;
    gui::MoveEnemies(enemies, enemy_speed, enemy_rotation_speed, deltaTimeSeconds, buildings);
    score += gui::CheckCollisionEnemyBullet2(myCannonBalls, enemies);
    std::vector<Tank*> myTankVector = {myTank};
    gui::CheckCollisionEnemyBullet2(enemyCannonBalls, myTankVector);
    gui::EnemiesShoot(enemies, enemyCannonBalls, myTank, shooting_range, deltaTimeSeconds, rotation_speed);
    for (auto enemy : enemies) {
        gui::TankToTankCollision(myTank, enemy, camera);
    }
    // TO DO for enemy tanks between each other
    for (int i = 0; i < enemies.size(); i++) {
        for (int j = i + 1; j < enemies.size(); j++) {
            gui::TankToTankCollision(enemies[i], enemies[j], NULL);
        }
    }

    gui::CheckCollisionBulletBuilding(myCannonBalls, buildings);
    gui::CheckCollisionBulletBuilding(enemyCannonBalls, buildings);
    for (auto enemy : enemies) {
        gui::CheckCollisionTankBuilding(enemy, buildings);
    }


    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->x, myTank->y, myTank->z));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(myTank->tankAngle), glm::vec3(0,1,0));
        RenderMesh(meshes["friendly_tank"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->x, myTank->y, myTank->z));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(myTank->tankAngle) + RADIANS(myTank->turretAngle), glm::vec3(0,1,0));
        RenderMesh(meshes["turret"], shaders["VertexNormal"], modelMatrix);
        RenderMesh(meshes["cannon"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderMesh(meshes["map"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->x, myTank->y, myTank->z));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(myTank->tankAngle) + RADIANS(myTank->turretAngle) + RADIANS(myTank->cannonAngle), glm::vec3(0,1,0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.5f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["advanced_cannonball"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 4, 0));
        RenderMesh(meshes["cannonball"], shaders["VertexNormal"], modelMatrix);
    }

    // update cannonballs
    for (int i = 0; i < myCannonBalls.size(); i++) {
        myCannonBalls[i]->timeToLive -= deltaTimeSeconds;
        if (myCannonBalls[i]->timeToLive <= 0) {
            myCannonBalls.erase(myCannonBalls.begin() + i);
            continue;
        }

        myCannonBalls[i]->position += myCannonBalls[i]->direction * glm::vec3(deltaTimeSeconds * 10);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myCannonBalls[i]->position[0], myCannonBalls[i]->position[1], myCannonBalls[i]->position[2]));
        RenderMesh(meshes["cannonball"], shaders["VertexNormal"], modelMatrix);
    }

    for (int i = 0; i < enemyCannonBalls.size(); i++) {
        enemyCannonBalls[i]->timeToLive -= deltaTimeSeconds;
        if (enemyCannonBalls[i]->timeToLive <= 0) {
            enemyCannonBalls.erase(enemyCannonBalls.begin() + i);
            continue;
        }

        enemyCannonBalls[i]->position += enemyCannonBalls[i]->direction * glm::vec3(deltaTimeSeconds * 10);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemyCannonBalls[i]->position[0], enemyCannonBalls[i]->position[1], enemyCannonBalls[i]->position[2]));
        RenderMesh(meshes["enemy_cannonball"], shaders["VertexNormal"], modelMatrix);
    }

    // draw buildings
    for (int i = 0; i < buildings.size(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(buildings[i]->position[0], buildings[i]->position[1], buildings[i]->position[2]));
        RenderMesh(meshes["building"+std::to_string(i)], shaders["VertexNormal"], modelMatrix);
    }

    // move enemies
    for (auto enemy : enemies) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemy->x, enemy->y, enemy->z));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(enemy->tankAngle), glm::vec3(0,1,0));
        RenderMesh(meshes["enemy_tank"], shaders["VertexNormal"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemy->x, enemy->y, enemy->z));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(enemy->tankAngle) + RADIANS(enemy->turretAngle), glm::vec3(0,1,0));
        RenderMesh(meshes["enemy_turret"], shaders["VertexNormal"], modelMatrix);
        RenderMesh(meshes["cannon"], shaders["VertexNormal"], modelMatrix);
    }

    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }

}



void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
  
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;
    float oldx = myTank->x, oldz = myTank->z;

    if (window->KeyHold(GLFW_KEY_Q)) {
        camera->TranslateForward(deltaTime * 10);
        camera->ComputeDistanceToTarget(myTank->x, myTank->y, myTank->z);   
    }
    if (window->KeyHold(GLFW_KEY_E)) {
        camera->TranslateBackward(deltaTime * 10);
        camera->ComputeDistanceToTarget(myTank->x, myTank->y, myTank->z);
    }  

    if (game_ended) {
        deltaTime = 0;
    } 

    if (window->KeyHold(GLFW_KEY_W)) {
        myTank->z -= tank_speed * deltaTime * cos(RADIANS(myTank->tankAngle));
        myTank->x -= tank_speed * deltaTime * sin(RADIANS(myTank->tankAngle));
        if (gui::CheckCollisionTankBuilding(myTank, buildings)) {
            myTank->z = oldz;
            myTank->x = oldx;
        } else {
            camera->MoveForwardTank(-tank_speed * deltaTime, myTank->tankAngle);
        }
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        myTank->tankAngle += deltaTime * rotation_speed;
        camera->RotateTankThirdPerson_OY(RADIANS(deltaTime * rotation_speed));
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        myTank->z += tank_speed * deltaTime * cos(RADIANS(myTank->tankAngle));
        myTank->x += tank_speed * deltaTime * sin(RADIANS(myTank->tankAngle));
        if (gui::CheckCollisionTankBuilding(myTank, buildings)) {
            myTank->z = oldz;
            myTank->x = oldx;
        } else {
            camera->MoveForwardTank(tank_speed * deltaTime, myTank->tankAngle);
        }
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        myTank->tankAngle -= deltaTime * rotation_speed;
        camera->RotateTankThirdPerson_OY(RADIANS(-deltaTime * rotation_speed));
    }

}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (window->GetSpecialKeyState() == 0) {
            camera->RotateTankThirdPerson_OX(RADIANS(-deltaY/5));
            camera->RotateTankThirdPerson_OY(RADIANS(-deltaX/5));
        }
    } else {
        myTank->turretAngle -= deltaX/3.5f;
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
     if (button == 1) {
        if (myTank->reloadTime > 0) {
            return;
        }
        float angle = myTank->tankAngle + myTank->turretAngle;
        glm::vec3 dir = glm::rotate(glm::mat4(1.0f), RADIANS(angle), glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
        dir[1] = 0;
        CannonBall *cannonBall = new CannonBall(glm::vec3(myTank->x - Cannon::cannonLength * sin(RADIANS(angle)), cannonHeight, myTank->z - Cannon::cannonLength * cos(RADIANS(angle))), glm::vec3(dir));
        myCannonBalls.push_back(cannonBall);
        myTank->reloadTime = 0.5;
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
