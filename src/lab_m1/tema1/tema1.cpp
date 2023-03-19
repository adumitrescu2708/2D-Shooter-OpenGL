#include "lab_m1/tema1/object2D.h"
#include "lab_m1/tema1/tema1.h"
#include "lab_m1/tema1/vis2D.h"
#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/animations.h"

#include <vector>
#include <iostream>



using namespace std;
using namespace m1;


tema1::tema1()
{

}


tema1::~tema1()
{
}


void tema1::Init()
{
        auto camera = GetSceneCamera();
        camera->SetPosition(glm::vec3(0, 0, 50));
        camera->SetRotation(glm::vec3(0, 0, 0));
        camera->Update();
        GetCameraInput()->SetActive(false);

        /* Create required 2D meshes */

        /* Meshes for duck */
        Mesh* triangle = object2D::CreateTriangle("duck_body", glm::vec3(0, 1, 0), 2, glm::vec3(0.35, 0.23, 0.15));
        AddMeshToList(triangle);

        Mesh* triangle2 = object2D::CreateTriangle("duck_mouth", glm::vec3(0, 4.5, 0), 2, glm::vec3(0.91, 0.80, 0.22));
        AddMeshToList(triangle2);

        Mesh* circle = object2D::CreateCircle("duck_head", glm::vec3(0, 1, 0), 1, glm::vec3(0.19, 0.34, 0.22));
        AddMeshToList(circle);

        Mesh* circle2 = object2D::CreateCircle("cloud", glm::vec3(0, 0, 0), 2, glm::vec3(0.68, 0.78, 0.81));
        AddMeshToList(circle2);

        Mesh* cloud = object2D::CreateRectangle("cloudBody", glm::vec3(0, 0, 0), 8, 5, glm::vec3(0.68, 0.78, 0.81), true);
        AddMeshToList(cloud);

        /* Meses for score */
        Mesh* point = object2D::CreateCircle("point", glm::vec3(0, 0, 0), 0.7, glm::vec3(0.54, 0.23, 0.23));
        AddMeshToList(point);

        Mesh* bullet = object2D::CreateRectangle("bullet", glm::vec3(0, 0, 0), 2, 0.7, glm::vec3(0.31, 0.37, 0.31), true);
        AddMeshToList(bullet);

        Mesh* scoreRectangle = object2D::CreateRectangle("scoreRectangle", glm::vec3(0, 0, 0), 24, 2, glm::vec3(1, 0.89, 0.71));
        AddMeshToList(scoreRectangle);

        Mesh* score = object2D::CreateRectangle("score", glm::vec3(0, 0, 0), 1, 2, glm::vec3(1, 0.7, 0.28), true);
        AddMeshToList(score);

        Mesh* killingSpree = object2D::CreateRomb("KillingSpree", glm::vec3(0, 0, 0), 2, 5, glm::vec3(0.69, 0.61, 0.85));
        AddMeshToList(killingSpree);

        /* Meshes for background view */
        Mesh* grass1 = object2D::CreateCircle("grass", glm::vec3(0, 0, 0), 30, glm::vec3(0.32, 0.38, 0.30));
        AddMeshToList(grass1);

        Mesh* grass2 = object2D::CreateCircle("grass2", glm::vec3(0, 0, 0), 15, glm::vec3(0.22, 0.27, 0.21));
        AddMeshToList(grass2);

        Mesh* grass3 = object2D::CreateCircle("grass3", glm::vec3(0, 0, 0), 15, glm::vec3(0.16, 0.20, 0.15));
        AddMeshToList(grass3);

        Mesh* grass4 = object2D::CreateCircle("grass4", glm::vec3(0, 0, 0), 15, glm::vec3(0.12, 0.15, 0.11));
        AddMeshToList(grass4);

        Mesh* sun1 = object2D::CreateCircle("sun", glm::vec3(0, 0, 0), 5, glm::vec3(0.66, 0.36, 0.16));
        AddMeshToList(sun1);

        Mesh* sun2 = object2D::CreateCircle("sun2", glm::vec3(0, 0, 0), 5, glm::vec3(0.79, 0.36, 0.05));
        AddMeshToList(sun2);

        Mesh* sun3 = object2D::CreateCircle("sun3", glm::vec3(0, 0, 0), 5, glm::vec3(0.83, 0.61, 0.04));
        AddMeshToList(sun3);

        Mesh* sun4 = object2D::CreateCircle("sun4", glm::vec3(0, 0, 0), 5, glm::vec3(0.98, 0.77, 0.25));
        AddMeshToList(sun4);

        /* Compute Logic space */
        logicSpace.x = 0;
        logicSpace.y = 0;
        logicSpace.width = 100;
        logicSpace.height = 50;

        /* Initialise Duck */
        animations::GenerateEntryDirection(directionAngle, currentPositionX, currentPositionY);

        wingAngle = 0.2;
        wingIncrease = true;

        lifesNumber = bulletsNumber = 3;
        ducksCounter = 0;

        duck.initialSpeed = speed = 10;
        duck.Init(speed);

        duck.lives = 3;
        duck.duckIndex = duck.score = duck.killingSpree = 0;
        duck.lenght = 10;
        duck.width = 10;
        duck.killingSpreeActivated = false;

        bonusAngle = 0;
        skyMovementX = skyMovementX2 = 0;
}

void tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0, 400);
    GetSceneCamera()->Update();
}

glm::mat3 tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
 
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void tema1::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);

    /* Based on the score compute color of the sky */
    glm::vec3 skyColor = glm::vec3(0, 0, 0);
    if (duck.score < 4) {
        skyColor = glm::vec3(0.15, 0.23, 0.26);
    }
    else if (duck.score >= 4 && duck.score < 8) {
        skyColor = glm::vec3(0.23, 0.36, 0.40);
    }
    else if (duck.score >= 8 && duck.score < 12) {
        skyColor = glm::vec3(0.29, 0.43, 0.49);
    }
    else if ((duck.score >= 12 && duck.score < 16)) {
        skyColor = glm::vec3(0.36, 0.53, 0.60);
    }
    else if ((duck.score >= 16 && duck.score <= 20)) {
        skyColor = glm::vec3(0.36, 0.53, 0.60);
    }
    else if ((duck.score > 20)) {
        skyColor = glm::vec3(0.57, 0.70, 0.75);
    }
    SetViewportArea(viewSpace, skyColor, true);

    /* Draw lifes, bullets, score */
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    visMatrix *= transform2D::Translate(5, 45);
    DrawGamePlayInfo(visMatrix, deltaTimeSeconds);

    /* Draw and update Duck */
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    animations::MoveDuck(&duck, deltaTimeSeconds, logicSpace.width, logicSpace.height, &visMatrix);
    DrawScene(visMatrix, deltaTimeSeconds);

    /* Draw background, sun and moving clouds */
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawBackground(visMatrix);
    DrawMovingSky(visMatrix, deltaTimeSeconds);
}

void tema1::DrawMovingSky(glm::mat3 visMatrix, float deltaTimeSeconds) {

    skyMovementX += deltaTimeSeconds * 0.5;
    glm::mat3 visMatrix2 = visMatrix * transform2D::Translate(skyMovementX, 0);

    /* Regenerate clouds positions if out of screen */
    if (skyMovementX > 50) {
        skyMovementX = -50;
    }

    if (skyMovementX2 > 70) {
        skyMovementX2 = -30;
    }

    /* Draw clouds */
    float angle = 0;
    float factor = (double)3.14 / (double)4;
    for (int i = 1; i < 6; i++) {
        modelMatrix = visMatrix2 * transform2D::Translate(50, 40);
        modelMatrix *= transform2D::Translate(4, 0);
        modelMatrix *= transform2D::Rotate(angle);
        angle -= factor;
        modelMatrix *= transform2D::Translate(-4, 0);
        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    }
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix2 * transform2D::Translate(50, 38);
    RenderMesh2D(meshes["cloudBody"], shaders["VertexColor"], modelMatrix);

    angle = 0;
    factor = (double)3.14 / (double)4;
    for (int i = 1; i < 6; i++) {
        modelMatrix = visMatrix2 * transform2D::Scale(0.5, 0.5) * transform2D::Translate(30, 25);
        modelMatrix *= transform2D::Translate(4, 0);
        modelMatrix *= transform2D::Rotate(angle);
        angle -= factor;
        modelMatrix *= transform2D::Translate(-4, 0);
        RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    }
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix2 *transform2D::Scale(0.5, 0.5) * transform2D::Translate(30, 23);
    RenderMesh2D(meshes["cloudBody"], shaders["VertexColor"], modelMatrix);

    /* Depending on the score, draw the sun on different positions with different colors */
    if (duck.score >= 4 && duck.score < 8) {
        modelMatrix = visMatrix * transform2D::Translate(65, 5);
        RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);
    }
    else if (duck.score >= 8 && duck.score < 12) {
        modelMatrix = visMatrix * transform2D::Translate(65, 15);
        RenderMesh2D(meshes["sun2"], shaders["VertexColor"], modelMatrix);
    }
    else if ((duck.score >= 12 && duck.score < 16)) {
        modelMatrix = visMatrix * transform2D::Translate(65, 25);
        RenderMesh2D(meshes["sun3"], shaders["VertexColor"], modelMatrix);
    }
    else if ((duck.score >= 16)) {
        modelMatrix = visMatrix * transform2D::Translate(65, 35);
        RenderMesh2D(meshes["sun4"], shaders["VertexColor"], modelMatrix);
    }

}

void tema1::DrawBackground(glm::mat3 visMatrix)
{
    /* Draw grass and fields */
    modelMatrix = visMatrix * transform2D::Translate(25, -5) * transform2D::Scale(2, 1);
    RenderMesh2D(meshes["grass2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(45, -5) * transform2D::Scale(2, 1);
    RenderMesh2D(meshes["grass3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(85, -5) * transform2D::Scale(2, 1);
    RenderMesh2D(meshes["grass3"], shaders["VertexColor"], modelMatrix);

}

void tema1::DrawGamePlayInfo(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    /* Draw lives */
    for (int i = 0; i < duck.lives; i++) {
        modelMatrix = visMatrix
            * transform2D::Translate(i * 3, 0);
        RenderMesh2D(meshes["point"], shaders["VertexColor"], modelMatrix);
    }

    /* Draw bullets */
    for (int i = 0; i < duck.bullets; i++) {
        modelMatrix = visMatrix
            * transform2D::Translate(i * 3 - 1, -3);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    /* Draw score */
    modelMatrix = visMatrix * transform2D::Translate(-1.5, -7);
    RenderMesh2D(meshes["scoreRectangle"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix * transform2D::Translate(-1.5, -7);
    if (duck.score > 24) {
        duck.score = 24;
    }
    for (int i = 0; i < duck.score; i++) {
        glm::mat3 modelMatrix2 = modelMatrix * transform2D::Translate(i, 0);
        RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix2);
    }

    modelMatrix = visMatrix * transform2D::Translate(45, -70) * transform2D::Scale(3, 1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    /* Treat killing spree */
    if (duck.killingSpreeActivated == true) {
        bonusAngle += deltaTimeSeconds * 10;
        modelMatrix = visMatrix * transform2D::Translate(90, 0) * transform2D::Rotate(bonusAngle);
        RenderMesh2D(meshes["KillingSpree"], shaders["VertexColor"], modelMatrix);
    }
}

void tema1::DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    /* Continously move duck's wings */
    if (duck.status != duck::movement::SHOT) {
        if (wingIncrease == true) {
            wingAngle += 5 * deltaTimeSeconds;
            if (wingAngle > 0.6) {
                wingIncrease = false;
                wingAngle = 0.6;
            }
        }
        else {
            wingAngle -= 5 * deltaTimeSeconds;
            if (wingAngle < 0.2) {
                wingAngle = 0.2;
                wingIncrease = true;
            }
        }
    }

    /* Draw duck */
    modelMatrix = visMatrix
                * transform2D::Translate(8, 0);
    RenderMesh2D(meshes["duck_head"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix
                * transform2D::Translate(9, 0)
                * transform2D::Scale(0.2f, 0.2f);
    RenderMesh2D(meshes["duck_mouth"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix 
                * transform2D::Translate(0, 0);
    RenderMesh2D(meshes["duck_body"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix
                * transform2D::Translate(4, 1.5)
                * transform2D::Rotate(1.57)
                * transform2D::Scale(0.5f, 0.5f)
                * transform2D::Rotate(wingAngle);             
    RenderMesh2D(meshes["duck_body"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix 
                * transform2D::Translate(3.1, 0.7) 
                * transform2D::Rotate(-1.57) 
                * transform2D::Scale(0.5f, 0.5f) 
                * transform2D::Rotate(-wingAngle);
    RenderMesh2D(meshes["duck_body"], shaders["VertexColor"], modelMatrix);
}


void tema1::FrameEnd()
{
}


void tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void tema1::OnKeyPress(int key, int mods)
{
}


void tema1::OnKeyRelease(int key, int mods)
{
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    double shootOX, shootOY;
    glm::ivec2 position = window->GetCursorPosition();

    glm::mat3 matrix = VisualizationTransf2DUnif(logicSpace, viewSpace);
    matrix = glm::inverse(matrix);

    glm::vec3 vector = glm::vec3(0);
    vector[0] = position[0];
    vector[1] = position[1];
    vector[2] = 1;
    
    glm::vec3 result;
    result = matrix * vector;
    position[0] = result[0];
    position[1] = 50 - result[1];

    duck.Shoot(position[0], position[1]);
}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void tema1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
