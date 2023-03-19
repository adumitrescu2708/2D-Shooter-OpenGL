#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

/*
    NAME:	Dumitrescu Alexandra
    GROUP:	333CA
*/

Mesh* object2D::CreateTriangle(const std::string& name, glm::vec3 baseCenter, float length, glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(baseCenter + glm::vec3(0, length, 0), color),
        VertexFormat(baseCenter - glm::vec3(0, length, 0), color),
        VertexFormat(baseCenter + glm::vec3(4 * length, 0, 0), color)
    };

    Mesh* triangle = new Mesh(name);

    std::vector<unsigned int> indices = { 0, 1, 2 };

    triangle->InitFromData(vertices, indices);
    return triangle;
}


Mesh* object2D::CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color)
{
    Mesh* circle = new Mesh(name);

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;


    glm::vec3 startPoint = center - glm::vec3(radius, 0, 0);
    int numberOfPoints = 32;
    float angle = 0.0f, anglef = 6.28f / numberOfPoints;

    for (int i = 0; i < numberOfPoints; i++) {
        vertices.push_back(VertexFormat(glm::vec3(radius * cos(angle) + center[0], radius * sin(angle) + center[1], 0), color));
        angle += anglef;
    }

    vertices.push_back(startPoint);

    for (int i = 0; i < 32; i++) {
        indices.push_back(i);
    }
    indices.push_back(0);
    circle->SetDrawMode(GL_TRIANGLE_FAN);
    circle->InitFromData(vertices, indices);
    return circle;
}


Mesh* object2D::CreateRomb(const std::string& name,
    glm::vec3 center,
    float length,
    float weight,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center - glm::vec3(length/2, 0, 0), color),
        VertexFormat(center - glm::vec3(0, weight / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, 0, 0), color),
        VertexFormat(center + glm::vec3(0, weight / 2, 0), color),
    };

    Mesh* romb = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0};
    romb->InitFromData(vertices, indices);
    return romb;
}

Mesh* object2D::CreateRectangle(const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float weight,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, weight, 0), color),
        VertexFormat(corner + glm::vec3(0, weight, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

