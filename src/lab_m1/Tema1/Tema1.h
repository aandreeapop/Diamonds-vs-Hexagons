#pragma once

#include "components/simple_scene.h"
#include "enemy.h"
#include "projectile.h"
#include "diamond.h"
#include <vector>

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

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

        void DrawScene();
        void PutEnemy(Enemy& enemy, float deltaTimeSeconds);
        void RandomEnemies();
        void ShootProjectile(Projectile& projectile, float deltaTimeSeconds);
        void StartShooting(Diamond& diamond, float deltaTimeSeconds);
        void FadeEnemy(Enemy& enemy, float deltaTimeSeconds);
        void FadeDiamond(Diamond& diamond, float deltaTimeSeconds);
        void DrawDiamond(Diamond& diamond, float deltaTimeSeconds);
        void SetDiamondColor(Diamond& diamond);

    protected:
        glm::mat3 modelMatrix;
        float squareSide;
        float diamondLength;
        float hexagonsLength;
        float starLength;
        float lifeSide;
        float resolutionX;

        int randomRow;
        float randomY;
        int randomColor;

        float x1Diamond = 152.5f;
        float x2Diamond = 307.5f;
        float x3Diamond = 462.5f;
        float y1Diamond = 382.5f;
        float y2Diamond = 227.5f;
        float y3Diamond = 72.5f;
        
        Diamond diamond1;
        Diamond diamond2;
        Diamond diamond3;
        Diamond diamond4;
        Diamond diamond5;
        Diamond diamond6;
        Diamond diamond7;
        Diamond diamond8;
        Diamond diamond9;

        bool firstEverEnemy = true;
        Enemy enemy1;
        Enemy enemy2;
        Enemy enemy3;
        std::vector<Enemy> enemies;

        float lastSpawnTime = 0;
        float spawnInterval = 0;

        int numberOfEnemies = 0;

        bool newYellowDiamond = false;
        bool newTurquoiseDiamond = false;
        bool newPurpleDiamond = false;
        bool newPinkDiamond = false;

        int xMouse = -1;
        int yMouse = -1;

        int numberOfLives = 3;
        bool gameOver = false;
    };
}   // namespace m1