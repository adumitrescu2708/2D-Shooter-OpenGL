#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/duck.h"


namespace m1
{
    class tema1 : public gfxc::SimpleScene
    {
     public:
         tema1();
        ~tema1();

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };
        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;


        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds);
        void DrawGamePlayInfo(glm::mat3 visMatrix, float deltaTimeSeconds);
        void DrawBackground(glm::mat3 visMatrix);
        void DrawMovingSky(glm::mat3 visMatrix, float deltaTimeSeconds);

        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;

        float currentPositionX;
        float currentPositionY;

        float directionAngle;

        float wingAngle;
        bool wingIncrease;

        int lifesNumber;
        int bulletsNumber;
        int ducksCounter;
        float speed;

        float skyMovementX, skyMovementX2;

        duck::Duck duck;
        float bonusAngle;

    };
}   // namespace m1
