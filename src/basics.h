#ifndef PLOTSBASICS
#define PLOTSBASICS

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <array>
#include <vector>
#include <string>
#include <map>


struct Segment{
    glm::vec3 point;
    float length;
    glm::mat4 model;
    float thickness;
    glm::vec4 rgba;
    glm::vec2 resolution;
    float antiAliasing;
    //Should this be static? UV don't change
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    bool initalized = false;
    unsigned int ID;

    Segment(glm::vec3 p , float length,float angle, float thickness = 2, glm::vec4 rgba = glm::vec4(0.0f,0.0f,0.0f,1.0f) ,float antiAliasing = 1.0f);
    //Line(std::array<float,3> p1, std::array<float,3> p2, float thickness = 2, std::array<float,3> rgb = std::array<float,3>{0.0f,0.0f,0.0f} ,float antiAliasing = 1.0f);
    ~Segment();
    void Draw(glm::mat4 viewProj);
};

struct Line {
    std::vector<glm::vec3> points;
    glm::mat4 model;
    float thickness;
    glm::vec4 rgba;
    glm::vec2 resolution;
    float antiAliasing;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    bool initalized = false;
    unsigned int ID;

    Line(float angle = 0, float thickness = 2, glm::vec4 rgba = glm::vec4( 0.0f,0.0f,0.0f,1.0f ), float antiAliasing = 1.0f);
    void AddPoint(glm::vec3 point);
    void Build();
    ~Line();
    void Draw(glm::mat4 viewProj);
};

/*
*
*/
struct LineArea{
    std::vector<glm::vec3> points;
    glm::mat4 model;
    float thickness;
    glm::vec4 rgba;
    glm::vec2 resolution;
    float antiAliasing;
    unsigned int VAO;
    unsigned int VBO;
    bool initalized = false;
    unsigned int ID;

    LineArea(float angle = 0, float thickness = 2, glm::vec4 rgba = glm::vec4( 0.0f,0.0f,0.0f,1.0f), float antiAliasing = 1.0f);
    void AddPoint(glm::vec3 point);
    void Build();
    ~LineArea();
    void Draw(glm::mat4 viewProj);
};

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};



struct TextRender {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int ID;
    glm::mat4 model; 
    glm::mat4 proj;
    std::map<char, Character> characters;

    void LoadChar();

    TextRender();
    void Draw(glm::mat4 viewProj, glm::vec2 pos, float rotation, float scale, std::string text, glm::vec4 rgba);
};

/*
* Still need to add axis to make subplots possible;
*/
struct Figure {
    TextRender txtRender;

    std::string xLabel;
    std::string yLabel;
    std::string zLabel;
    std::string title;

    std::vector<float> xTics;
    std::vector<float> yTics;
    std::vector<float> zTics;

    glm::vec4 boarderColor;
    glm::vec4 backGroundColor;

    //Line axis;

    unsigned int VAO;
    unsigned int VBO;

    //Scale of plots
    float minX;
    float minY;
    float minZ;

    float maxX;
    float maxY;
    float maxZ;

    float xLabelScale;
    float yLabelScale;
    float zLabelScale;

    Figure();
    ~Figure();

    void SetTitle(std::string title);
    void SetXLabel(std::string xLabel);
    void SetYLabel(std::string yLabel);
    void SetZLabel(std::string zLabel);
    void SetTextScale(float scale);

    void Hist();
    void LineArea(std::vector<glm::vec2> points);
    void Draw(glm::mat4 proj);


};

#endif//PLOTSBASICS