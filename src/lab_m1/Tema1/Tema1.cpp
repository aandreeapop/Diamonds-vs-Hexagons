#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/enemy.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "lab_m1/Tema1/figure.h"
#include "lab_m1/Tema1/transformFigure.h"
#include "colors.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
    diamond1.row = 1;
    diamond1.column = 1;
    diamond1.translateX = x1Diamond;
    diamond1.translateY = y1Diamond;

    diamond2.row = 1;
    diamond2.column = 2;
    diamond2.translateX = x2Diamond;
    diamond2.translateY = y1Diamond;

    diamond3.row = 1;
    diamond3.column = 3;
    diamond3.translateX = x3Diamond;
    diamond3.translateY = y1Diamond;

    diamond4.row = 2;
    diamond4.column = 1;
    diamond4.translateX = x1Diamond;
    diamond4.translateY = y2Diamond;

    diamond5.row = 2;
    diamond5.column = 2;
    diamond5.translateX = x2Diamond;
    diamond5.translateY = y2Diamond;

    diamond6.row = 2;
    diamond6.column = 3;
    diamond6.translateX = x3Diamond;
    diamond6.translateY = y2Diamond;

    diamond7.row = 3;
    diamond7.column = 1;
    diamond7.translateX = x1Diamond;
    diamond7.translateY = y3Diamond;

    diamond8.row = 3;
    diamond8.column = 2;
    diamond8.translateX = x2Diamond;
    diamond8.translateY = y3Diamond;

    diamond9.row = 3;
    diamond9.column = 3;
    diamond9.translateX = x3Diamond;
    diamond9.translateY = y3Diamond;
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    resolutionX = (float)resolution.x;

    squareSide = 100;
    diamondLength = 30;
    hexagonsLength = 10;
    starLength = 10;
    lifeSide = 70;

    enemies.push_back(enemy1);
    enemies.push_back(enemy2); 
    enemies.push_back(enemy3);

    enemies.at(0).translateX = resolutionX + 10;
    enemies.at(1).translateX = resolutionX + 10;
    enemies.at(2).translateX = resolutionX + 10;

    //squares

    Mesh* rectangle = figure::CreateSquare("rectangle", glm::vec3(0, 0, 0), squareSide, red, true);
    AddMeshToList(rectangle);

    Mesh* square = figure::CreateSquare("square", glm::vec3(0, 0, 0), squareSide, gray, true);
    AddMeshToList(square);

    Mesh* squareUp = figure::CreateSquare("squareUp", glm::vec3(0, 0, 0), squareSide, gray, false);
    AddMeshToList(squareUp);

    //enemies

    Mesh* yellowHexagon = figure::CreateHexagons("yellowHexagon", glm::vec3(0, 0, 0), hexagonsLength, yellow, blueGray);
    AddMeshToList(yellowHexagon);

    Mesh* turquoiseHexagon = figure::CreateHexagons("turquoiseHexagon", glm::vec3(0, 0, 0), hexagonsLength, turquoise, blueGray);
    AddMeshToList(turquoiseHexagon);

    Mesh* purpleHexagon = figure::CreateHexagons("purpleHexagon", glm::vec3(0, 0, 0), hexagonsLength, purple, blueGray);
    AddMeshToList(purpleHexagon);

    Mesh* pinkHexagon = figure::CreateHexagons("pinkHexagon", glm::vec3(0, 0, 0), hexagonsLength, pink, blueGray);
    AddMeshToList(pinkHexagon);

    //projectiles

    Mesh* yellowStar = figure::CreateStar("yellowStar", glm::vec3(0, 0, 0), starLength, yellow);
    AddMeshToList(yellowStar);

    Mesh* turquoiseStar = figure::CreateStar("turquoiseStar", glm::vec3(0, 0, 0), starLength, turquoise);
    AddMeshToList(turquoiseStar);

    Mesh* purpleStar = figure::CreateStar("purpleStar", glm::vec3(0, 0, 0), starLength, purple);
    AddMeshToList(purpleStar);

    Mesh* pinkStar = figure::CreateStar("pinkStar", glm::vec3(0, 0, 0), starLength, pink);
    AddMeshToList(pinkStar);

    //diamonds

    Mesh* yellowDiamond = figure::CreateDiamond("yellowDiamond", glm::vec3(0, 0, 0), diamondLength, yellow);
    AddMeshToList(yellowDiamond);

    Mesh* turquoiseDiamond = figure::CreateDiamond("turquoiseDiamond", glm::vec3(0, 0, 0), diamondLength, turquoise);
    AddMeshToList(turquoiseDiamond);

    Mesh* purpleDiamond = figure::CreateDiamond("purpleDiamond", glm::vec3(0, 0, 0), diamondLength, purple);
    AddMeshToList(purpleDiamond);

    Mesh* pinkDiamond = figure::CreateDiamond("pinkDiamond", glm::vec3(0, 0, 0), diamondLength, pink);
    AddMeshToList(pinkDiamond);

    Mesh* life = figure::CreateSquare("life", glm::vec3(0, 0, 0), lifeSide, red, true);
    AddMeshToList(life);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
    if (!gameOver) {
        DrawScene();
        RandomEnemies();

        PutEnemy(enemies.at(0), deltaTimeSeconds);
        PutEnemy(enemies.at(1), deltaTimeSeconds);
        PutEnemy(enemies.at(2), deltaTimeSeconds);

        if (newYellowDiamond) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformFigure::Translate(xMouse, yMouse);
            RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);
        }

        if (newTurquoiseDiamond) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformFigure::Translate(xMouse, yMouse);
            RenderMesh2D(meshes["turquoiseDiamond"], shaders["VertexColor"], modelMatrix);
        }

        if (newPurpleDiamond) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformFigure::Translate(xMouse, yMouse);
            RenderMesh2D(meshes["purpleDiamond"], shaders["VertexColor"], modelMatrix);
        }

        if (newPinkDiamond) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformFigure::Translate(xMouse, yMouse);
            RenderMesh2D(meshes["pinkDiamond"], shaders["VertexColor"], modelMatrix);
        }

        DrawDiamond(diamond1, deltaTimeSeconds);
        DrawDiamond(diamond2, deltaTimeSeconds);
        DrawDiamond(diamond3, deltaTimeSeconds);
        DrawDiamond(diamond4, deltaTimeSeconds);
        DrawDiamond(diamond5, deltaTimeSeconds);
        DrawDiamond(diamond6, deltaTimeSeconds);
        DrawDiamond(diamond7, deltaTimeSeconds);
        DrawDiamond(diamond8, deltaTimeSeconds);
        DrawDiamond(diamond9, deltaTimeSeconds);
    }
}

void Tema1::DrawDiamond(Diamond& diamond, float deltaTimeSeconds)
{
    if (diamond.inScene && diamond.collision == false) {
        if (diamond.lastShotTime == 0) {
            diamond.lastShotTime = Engine::GetElapsedTime() - 1;
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformFigure::Translate(diamond.translateX, diamond.translateY);
        switch (diamond.color) {
            case 1:
                RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            case 2:
                RenderMesh2D(meshes["turquoiseDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            case 3:
                RenderMesh2D(meshes["purpleDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            case 4:
                RenderMesh2D(meshes["pinkDiamond"], shaders["VertexColor"], modelMatrix);
                break;
        }

        diamond.star.color = diamond.color;
        
        StartShooting(diamond, deltaTimeSeconds);
       
        for (auto & element : diamond.enemiesOnRow) {
            if (glm::distance(glm::vec2(diamond.translateX, diamond.translateY),
                glm::vec2(enemies.at(element).translateX, enemies.at(element).translateY)) < diamond.radius + enemies.at(element).radius) {
                    diamond.collision = true;
                    diamond.lastShotTime = 0;
            }
        }
        
    } else if (diamond.inScene) {
        FadeDiamond(diamond, deltaTimeSeconds);
    } else {
        if (diamond.star.hasStartedMoving) {
            StartShooting(diamond, deltaTimeSeconds);
        }
    }
    diamond.enemiesOnRow.clear();

    if (diamond.star.collision == false && diamond.star.translateX == diamond.translateX + 50) {
        diamond.lastShotTime = Engine::GetElapsedTime();
    }
    ShootProjectile(diamond.star, deltaTimeSeconds);
   
}

void Tema1::SetDiamondColor(Diamond& diamond) {
    diamond.inScene = true;
    if (newYellowDiamond) {
        diamond.color = 1;
    }

    if (newTurquoiseDiamond) {
        diamond.color = 2;
    }

    if (newPurpleDiamond) {
        diamond.color = 3;
    }

    if (newPinkDiamond) {
        diamond.color = 4;
    }
}

void Tema1::DrawScene()
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(10, 10);
    modelMatrix *= transformFigure::Scale(0.5, 4.35);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(90, 10);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(90, 165);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(90, 320);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(245, 10);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(245, 165);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(245, 320);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(400, 10);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(400, 165);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(400, 320);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    //GUI

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(50, 550);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["squareUp"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(225, 550);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["squareUp"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(400, 550);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["squareUp"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(575, 550);
    modelMatrix *= transformFigure::Scale(1.25, 1.25);
    RenderMesh2D(meshes["squareUp"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(112.5, 612.5);
    RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(287.5, 612.5);
    RenderMesh2D(meshes["turquoiseDiamond"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(462.5, 612.5);
    RenderMesh2D(meshes["purpleDiamond"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformFigure::Translate(637.5, 612.5);
    RenderMesh2D(meshes["pinkDiamond"], shaders["VertexColor"], modelMatrix);

    if (numberOfLives > 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformFigure::Translate(950, 600);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);

        if (numberOfLives > 1) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformFigure::Translate(1040, 600);
            RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);

            if (numberOfLives == 3) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transformFigure::Translate(1130, 600);
                RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
            }
        }
    } else {
        gameOver = true;
    }
}


void Tema1::PutEnemy(Enemy& enemy, float deltaTimeSeconds)
{
    if (enemy.notInScene == false) {
        if (enemy.translateX > 35 && enemy.collision == false) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transformFigure::Translate(enemy.translateX, enemy.translateY);
            enemy.translateX -= deltaTimeSeconds * 75;

            switch (enemy.color) {
            case 1:
                RenderMesh2D(meshes["yellowHexagon"], shaders["VertexColor"], modelMatrix);
                break;
            case 2:
                RenderMesh2D(meshes["turquoiseHexagon"], shaders["VertexColor"], modelMatrix);
                break;
            case 3:
                RenderMesh2D(meshes["purpleHexagon"], shaders["VertexColor"], modelMatrix);
                break;
            case 4:
                RenderMesh2D(meshes["pinkHexagon"], shaders["VertexColor"], modelMatrix);
                break;
            }
        }
        else {
            FadeEnemy(enemy, deltaTimeSeconds);
        }
    }
}


void Tema1::RandomEnemies()
{
    float currentTime = Engine::GetElapsedTime();
    float elapsedTime = currentTime - lastSpawnTime;

    if ((enemies.at(0).notInScene || enemies.at(1).notInScene || enemies.at(2).notInScene) && elapsedTime >= spawnInterval) {
        randomRow = rand() % 3 + 1;

        switch (randomRow) {
        case 1:
            randomY = 382.5f;
            break;
        case 2:
            randomY = 227.5f;
            break;
        case 3:
            randomY = 72.5f;
            break;
        }

        randomColor = rand() % 4 + 1;

        lastSpawnTime = currentTime;
        spawnInterval = rand() % 5 + 2;

        if (numberOfEnemies == 0) {
            enemies.at(0).notInScene = false;
            enemies.at(0).translateX = resolutionX;
            enemies.at(0).translateY = randomY;
            enemies.at(0).row = randomRow;
            enemies.at(0).color = randomColor;
            enemies.at(0).numberOfCollisions = 0;
            numberOfEnemies++;
        }
        else if (numberOfEnemies == 1) {
            enemies.at(1).notInScene = false;
            enemies.at(1).translateX = resolutionX;
            enemies.at(1).translateY = randomY;
            enemies.at(1).row = randomRow;
            enemies.at(1).color = randomColor;
            enemies.at(1).numberOfCollisions = 0;
            numberOfEnemies++;
        }
        else {
            enemies.at(2).notInScene = false;
            enemies.at(2).translateX = resolutionX;
            enemies.at(2).translateY = randomY;
            enemies.at(2).row = randomRow;
            enemies.at(2).color = randomColor;
            enemies.at(2).numberOfCollisions = 0;
            numberOfEnemies = 0;
        }
    }
}

void Tema1::ShootProjectile(Projectile& projectile, float deltaTimeSeconds) {
    if (projectile.collision == false && projectile.translateX < resolutionX) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformFigure::Translate(projectile.translateX, projectile.translateY);
        projectile.translateX += deltaTimeSeconds * 300;
        modelMatrix *= transformFigure::Rotate(-projectile.angularStep);
        projectile.angularStep += deltaTimeSeconds * 5;

        switch (projectile.color) {
        case 1:
            RenderMesh2D(meshes["yellowStar"], shaders["VertexColor"], modelMatrix);
            break;
        case 2:
            RenderMesh2D(meshes["turquoiseStar"], shaders["VertexColor"], modelMatrix);
            break;
        case 3:
            RenderMesh2D(meshes["purpleStar"], shaders["VertexColor"], modelMatrix);
            break;
        case 4:
            RenderMesh2D(meshes["pinkStar"], shaders["VertexColor"], modelMatrix);
            break;
        }
    }
    else {
        projectile.hasStartedMoving = false;
    }
    
}

void Tema1::StartShooting(Diamond& diamond, float deltaTimeSeconds) {
    if (enemies.at(0).row == diamond.row) {
        diamond.enemiesOnRow.push_back(0);
    }
    if (enemies.at(1).row == diamond.row) {
        diamond.enemiesOnRow.push_back(1);
    }
    if (enemies.at(2).row == diamond.row) {
        diamond.enemiesOnRow.push_back(2);
    }

    float elapsedTime = Engine::GetElapsedTime() - diamond.lastShotTime;

    if (elapsedTime >= 2) {
        for (auto& element : diamond.enemiesOnRow) {
            if (enemies.at(element).color == diamond.color) {
                diamond.startShooting = true;
            }
        }


        if (!diamond.enemiesOnRow.empty() && !diamond.star.hasStartedMoving && diamond.startShooting) {
            diamond.star.translateX = diamond.translateX + 50;
            diamond.star.translateY = diamond.translateY;
            diamond.star.angularStep = 0;
            diamond.star.hasStartedMoving = true;
            diamond.star.collision = false;
        }
        diamond.startShooting = false;
    }

    if (!diamond.enemiesOnRow.empty() && diamond.star.hasStartedMoving) {
        for (auto& element : diamond.enemiesOnRow) {
            if (glm::distance(diamond.star.translateX, enemies.at(element).translateX) <= diamond.star.radius + enemies.at(element).radius &&
                enemies.at(element).scaleX == 1 && enemies.at(element).color == diamond.color) {
                if (enemies.at(element).numberOfCollisions == 2) {
                    enemies.at(element).collision = true;
                    enemies.at(element).row = -1;
                    diamond.star.collision = true;
                    diamond.star.hasStartedMoving = false;
                    enemies.at(element).numberOfCollisions = 0;
                }   else {
                    diamond.star.collision = true;
                    diamond.star.hasStartedMoving = false;
                    enemies.at(element).numberOfCollisions++;
                }
               
            }

        }
    }
    
}

void Tema1::FadeEnemy(Enemy& enemy, float deltaTimeSeconds) 
{
    if (enemy.scaleX == 1 && enemy.translateX <= 35) {
        numberOfLives--;
    }

    if (enemy.scaleX > 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformFigure::Translate(enemy.translateX, enemy.translateY);
        modelMatrix *= transformFigure::Scale(enemy.scaleX, enemy.scaleY);
        enemy.scaleX -= deltaTimeSeconds * 0.7;
        enemy.scaleY -= deltaTimeSeconds * 0.7;

        switch (enemy.color) {
        case 1:
            RenderMesh2D(meshes["yellowHexagon"], shaders["VertexColor"], modelMatrix);
            break;
        case 2:
            RenderMesh2D(meshes["turquoiseHexagon"], shaders["VertexColor"], modelMatrix);
            break;
        case 3:
            RenderMesh2D(meshes["purpleHexagon"], shaders["VertexColor"], modelMatrix);
            break;
        case 4:
            RenderMesh2D(meshes["pinkHexagon"], shaders["VertexColor"], modelMatrix);
            break;
        }
    }
    else {
        enemy.notInScene = true;
        enemy.scaleX = 1;
        enemy.scaleY = 1;
        enemy.collision = false;
    }
}

void Tema1::FadeDiamond(Diamond& diamond, float deltaTimeSeconds) {
    if (diamond.scaleX > 0) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformFigure::Translate(diamond.translateX, diamond.translateY);
        modelMatrix *= transformFigure::Scale(diamond.scaleX, diamond.scaleY);
        diamond.scaleX -= deltaTimeSeconds * 0.7;
        diamond.scaleY -= deltaTimeSeconds * 0.7;
        switch (diamond.color) {
        case 1:
            RenderMesh2D(meshes["yellowDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        case 2:
            RenderMesh2D(meshes["turquoiseDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        case 3:
            RenderMesh2D(meshes["purpleDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        case 4:
            RenderMesh2D(meshes["pinkDiamond"], shaders["VertexColor"], modelMatrix);
            break;
        }
    }
    else {
        diamond.scaleX = 1;
        diamond.scaleY = 1;
        diamond.inScene = false;
        diamond.collision = false;
    }
}

void Tema1::FrameEnd() 
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods) 
{
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (newYellowDiamond || newTurquoiseDiamond || newPurpleDiamond || newPinkDiamond) {
        xMouse = mouseX + deltaX;
        yMouse = (720 - mouseY) + deltaY;
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
   if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if ((720 - mouseY) >= 550 && (720 - mouseY) <= 675) {
            if ((mouseX >= 50) && (mouseX <= 175)) {
                newYellowDiamond = true;
                xMouse = mouseX;
                yMouse = 720 - mouseY;
            }

            if ((mouseX >= 225) && (mouseX <= 350)) {
                newTurquoiseDiamond = true;
                xMouse = mouseX;
                yMouse = 720 - mouseY;
            }

            if ((mouseX >= 400) && (mouseX <= 525)) {
                newPurpleDiamond = true;
                xMouse = mouseX;
                yMouse = 720 - mouseY;
            }

            if ((mouseX >= 575) && (mouseX <= 700)) {
                newPinkDiamond = true;
                xMouse = mouseX;
                yMouse = 720 - mouseY;
            }
        }

    }

    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        if ((mouseX >= 90) && (mouseX <= 215)) {
            if (((720 - mouseY) >= 320) && ((720 - mouseY) <= 445)) {
                diamond1.inScene = false;
            }

            if (((720 - mouseY) >= 165) && ((720 - mouseY) <= 290)) {
                diamond4.inScene = false;
            }

            if (((720 - mouseY) >= 10) && ((720 - mouseY) <= 135)) {
                diamond7.inScene = false;
            }
        }

        if ((mouseX >= 245) && (mouseX <= 370)) {
            if (((720 - mouseY) >= 320) && ((720 - mouseY) <= 445)) {
                diamond2.inScene = false;
            }

            if (((720 - mouseY) >= 165) && ((720 - mouseY) <= 290)) {
                diamond5.inScene = false;
            }

            if (((720 - mouseY) >= 10) && ((720 - mouseY) <= 135)) {
                diamond8.inScene = false;
            }
        }

        if ((mouseX >= 400) && (mouseX <= 525)) {
            if (((720 - mouseY) >= 320) && ((720 - mouseY) <= 445)) {
                diamond3.inScene = false;
            }

            if (((720 - mouseY) >= 165) && ((720 - mouseY) <= 290)) {
                diamond6.inScene = false;
            }

            if (((720 - mouseY) >= 10) && ((720 - mouseY) <= 135)) {
                diamond9.inScene = false;
            }
        }
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (newYellowDiamond || newTurquoiseDiamond || newPurpleDiamond || newPinkDiamond) {
            if ((mouseX >= 90) && (mouseX <= 215)) {
                if (((720 - mouseY) >= 320) && ((720 - mouseY) <= 445) && !diamond1.inScene) {
                    SetDiamondColor(diamond1);
                }

                if (((720 - mouseY) >= 165) && ((720 - mouseY) <= 290)  && !diamond4.inScene) {
                    SetDiamondColor(diamond4);
                }

                if (((720 - mouseY) >= 10) && ((720 - mouseY) <= 135) && !diamond7.inScene) {
                    SetDiamondColor(diamond7);
                }
            }

            if ((mouseX >= 245) && (mouseX <= 370)) {
                if (((720 - mouseY) >= 320) && ((720 - mouseY) <= 445) && !diamond2.inScene) {
                    SetDiamondColor(diamond2);
                }

                if (((720 - mouseY) >= 165) && ((720 - mouseY) <= 290) && !diamond5.inScene) {
                    SetDiamondColor(diamond5);
                }

                if (((720 - mouseY) >= 10) && ((720 - mouseY) <= 135) && !diamond8.inScene) {
                    SetDiamondColor(diamond8);
                }
            }

            if ((mouseX >= 400) && (mouseX <= 525)) {
                if (((720 - mouseY) >= 320) && ((720 - mouseY) <= 445) && !diamond3.inScene) {
                    SetDiamondColor(diamond3);
                }

                if (((720 - mouseY) >= 165) && ((720 - mouseY) <= 290) && !diamond6.inScene) {
                    SetDiamondColor(diamond6);
                }

                if (((720 - mouseY) >= 10) && ((720 - mouseY) <= 135) && !diamond9.inScene) {
                    SetDiamondColor(diamond9);
                }
            }

            newYellowDiamond = false;
            newTurquoiseDiamond = false;
            newPurpleDiamond = false;
            newPinkDiamond = false;

        }
      
    }
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

