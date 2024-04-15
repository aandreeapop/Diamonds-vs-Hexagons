#include "figure.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* figure::CreateSquare(
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
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* figure::CreateDiamond(
    const std::string& name,
    glm::vec3 middle,
    float length,
    glm::vec3 color)
{
    glm::vec3 corner = middle;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, length * 2, 1), color),
        VertexFormat(corner + glm::vec3(-length, 0, 1), color),
        VertexFormat(corner + glm::vec3(0, -length * 2, 1), color),
        VertexFormat(corner + glm::vec3(length, length * 0.5, 1), color),
        VertexFormat(corner + glm::vec3(length, -length * 0.5, 1), color),
        VertexFormat(corner + glm::vec3(length * 2, -length * 0.5, 1), color),
        VertexFormat(corner + glm::vec3(length * 2, length * 0.5, 1), color)
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 3,
        3, 1, 4,
        1, 2, 4,
        3, 4, 5,
        3, 5, 6
    };

    diamond->InitFromData(vertices, indices);
    return diamond;
}

Mesh* figure::CreateHexagons(
    const std::string& name,
    glm::vec3 middle,
    float length,
    glm::vec3 color,
    glm::vec3 color2)
{
    glm::vec3 corner = middle;

    std::vector<VertexFormat> vertices =
    {
        // big hexagon
        VertexFormat(corner + glm::vec3(length * 4, 0, 1), color),
        VertexFormat(corner + glm::vec3(length * 2, length * 3.5, 1), color),
        VertexFormat(corner + glm::vec3(-length * 2, length * 3.5, 1), color),
        VertexFormat(corner + glm::vec3(-length * 4, 0, 0), color),
        VertexFormat(corner + glm::vec3(-length * 2, -length * 3.5, 1), color),
        VertexFormat(corner + glm::vec3(length * 2, -length * 3.5, 1), color),

        // center
        VertexFormat(corner + glm::vec3(0, 0, 1), color2),

        // small hexagon
        VertexFormat(corner + glm::vec3(length * 3, 0, 2), color2),
        VertexFormat(corner + glm::vec3(length * 1.5, length * 2.625, 2), color2),
        VertexFormat(corner + glm::vec3(-length * 1.5, length * 2.625, 2), color2),
        VertexFormat(corner + glm::vec3(-length * 3, 0, 2), color2),
        VertexFormat(corner + glm::vec3(-length * 1.5, -length * 2.625, 2), color2),
        VertexFormat(corner + glm::vec3(length * 1.5, -length * 2.625, 2), color2)

    };

    Mesh* hexagons = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        // big hexagon
        0, 1, 6,
        1, 2, 6,
        2, 3, 6,
        3, 4, 6,
        4, 5, 6,
        5, 0, 6,

        // small hexagon
        7, 8, 6,
        8, 9, 6,
        9, 10, 6,
        10, 11, 6,
        11, 12, 6,
        12, 7, 6
    };

    hexagons->InitFromData(vertices, indices);
    return hexagons;
}

Mesh* figure::CreateStar(
    const std::string& name,
    glm::vec3 middle,
    float length,
    glm::vec3 color)
{
    glm::vec3 corner = middle;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 1), color),

        VertexFormat(corner + glm::vec3(0, length * 3.522f, 3), color),
        VertexFormat(corner + glm::vec3(-length * 2.537f, -length * 3.177f, 3), color),
        VertexFormat(corner + glm::vec3(length * 3.642f, length * 1.042f, 3), color),
        VertexFormat(corner + glm::vec3(-length * 3.357f, length * 1.102f, 3), color),
        VertexFormat(corner + glm::vec3(length * 2.332f, -length * 3.217f, 3), color),

        VertexFormat(corner + glm::vec3(-length * 0.922f, length * 1.081f, 3), color),
        VertexFormat(corner + glm::vec3(length * 0.851f, length * 1.066f, 3), color),
        VertexFormat(corner + glm::vec3(length * 1.391f, -length * 0.494f, 3), color),
        VertexFormat(corner + glm::vec3(0, -length * 1.445f, 3), color),
        VertexFormat(corner + glm::vec3(-length * 1.46f, -length * 0.3337f, 3), color),
    };

    Mesh* star = new Mesh(name);

    std::vector<unsigned int> indices =
    {
        1, 6, 7,
        2, 9, 10,
        3, 7, 8,
        4, 6, 10,
        5, 8, 9,
        0, 6, 7,
        0, 7, 8,
        0, 8, 9,
        0, 9, 10,
        0, 10, 6
    };

    star->InitFromData(vertices, indices);
    return star;
}