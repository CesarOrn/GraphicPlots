#ifndef PLOTSBASICS
#define PLOTSBASICS

#include <glad/glad.h>
#include <array>
#include <vector>

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

#endif//PLOTSBASICS