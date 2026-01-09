#ifndef PLOTSBASICS
#define PLOTSBASICS

#include <glad/glad.h>
#include <array>
#include <vector>
#include <string>
#include <map>


struct Segment{
    std::array<float,3> point;
    float length;
    std::array<float,4> model;
    float thickness;
    std::array<float,3> rgb;
    std::array<float,2> resolution;
    float antiAliasing;
    //Should this be static? UV don't change
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    bool initalized = false;
    unsigned int ID;

    Segment(std::array<float,3> p , float length,float angle, float thickness = 2,  std::array<float,3> rgb = std::array<float,3>{0.0f,0.0f,0.0f} ,float antiAliasing = 1.0f);
    //Line(std::array<float,3> p1, std::array<float,3> p2, float thickness = 2, std::array<float,3> rgb = std::array<float,3>{0.0f,0.0f,0.0f} ,float antiAliasing = 1.0f);
    ~Segment();
    void Draw(unsigned int width, unsigned int height);
};

struct Line {
    std::vector<std::array<float,3>> points;
    std::array<float, 4> model;
    float thickness;
    std::array<float, 3> rgb;
    std::array<float,2> resolution;
    float antiAliasing;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    bool initalized = false;
    unsigned int ID;

    Line(float angle = 0, float thickness = 2, std::array<float, 3> rgb = std::array<float, 3>{ 0.0f,0.0f,0.0f }, float antiAliasing = 1.0f);
    void AddPoint(std::array<float,3> point);
    void Build();
    ~Line();
    void Draw(unsigned int width, unsigned int height);

};
struct Character {
    unsigned int textureID;
    std::array<unsigned int, 2> size;
    std::array<int, 2> bearing;
    unsigned int advance;
};



struct TextRender {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int ID;
    std::map<char, Character> characters;

    void LoadChar();

    TextRender();
    void Draw(std::string text, std::array<float, 3>_rgb);
};

#endif//PLOTSBASICS