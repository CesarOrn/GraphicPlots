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
    glm::vec3 rgb;
    glm::vec2 resolution;
    float antiAliasing;
    //Should this be static? UV don't change
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    bool initalized = false;
    unsigned int ID;

    Segment(glm::vec3 p , float length,float angle, float thickness = 2, glm::vec3 rgb = glm::vec3(0.0f,0.0f,0.0f) ,float antiAliasing = 1.0f);
    //Line(std::array<float,3> p1, std::array<float,3> p2, float thickness = 2, std::array<float,3> rgb = std::array<float,3>{0.0f,0.0f,0.0f} ,float antiAliasing = 1.0f);
    ~Segment();
    void Draw(unsigned int width, unsigned int height);
};

struct Line {
    std::vector<glm::vec3> points;
    glm::mat4 model;
    float thickness;
    glm::vec3 rgb;
    glm::vec2 resolution;
    float antiAliasing;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    bool initalized = false;
    unsigned int ID;

    Line(float angle = 0, float thickness = 2, glm::vec3 rgb = glm::vec3( 0.0f,0.0f,0.0f ), float antiAliasing = 1.0f);
    void AddPoint(glm::vec3 point);
    void Build();
    ~Line();
    void Draw(unsigned int width, unsigned int height);

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
    void Draw(glm::vec2 pos, float rotation, std::string text, glm::vec3 rgb);
};

#endif//PLOTSBASICS