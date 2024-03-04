#pragma once

#include "components/simple_scene.h"
#include "lab_m1/lab5/lab_camera.h"
#include "lab_m1/Tema2/tank.h"
#include "lab_m1/Tema2/turret.h"
#include "lab_m1/Tema2/cannon.h"
#include "lab_m1/Tema2/gui.h"
#include "lab_m1/Tema2/building.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     public:
        implemented::Camera *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        GLenum cullFace;
        GLenum polygonMode;
        float cannonHeight = (Turret::turretLowerBaseHeight + Turret::turretUpperBaseHeight)/2;
        
        float map_side = 50.f;
        float safety_radius = 3.f;
        float safety_radius_enemies = 10.f;
        float rotation_speed = 110;
        float tank_speed = 8;
        float enemy_speed = 2.5f;
        float enemy_rotation_speed = 50.f;
        float number_of_enemies = 7;
        float shooting_range = 15;
        int number_of_buildings = 25;
        float game_time = 40.f;
        int score = 0;
        bool game_ended = false;

        Tank *myTank = new Tank();
        std::vector<CannonBall*> myCannonBalls;
        std::vector<CannonBall*> enemyCannonBalls;
        std::vector<Building*> buildings;
        std::vector<Tank*> enemies;

        float t = 0;
      

        // TODO(student): If you need any other class variables, define them here.
        float fov = 60.f;
        float left = -5.f, right = 5.f, top = 5.f, bottom = -5.f;
        glm::mat4 ortho = glm::ortho(left, right, bottom, top, 0.01f, 200.0f); 
        glm::mat4 perspective = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);

    };
}   // namespace m1
