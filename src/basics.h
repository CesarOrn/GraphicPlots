#ifndef PLOTSBASICS
#define PLOTSBASICS

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glad/glad.h>
#include <array>
#include <vector>
#include <string>
#include <map>

/*
* 
*/

// https://towardsdatascience.com/kernel-density-estimator-for-multidimensional-data-3e78c9779ed8/
struct KDE{
    std::vector<glm::vec2> points;
    void PushPoint(glm::vec2 point);
    float F(float x, float y);
};

struct Shader {
    unsigned int ID;
    Shader();
    void Load(std::string vertexPath, std::string fragmentPath, std::string geometryPath);
    void Load(std::string vertexPath, std::string fragmentPath);
    ~Shader();
};

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
    static bool initalized;
    static Shader shader;

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
    static bool initalized;
    static Shader shader;

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
    static bool initalized;
    static Shader shader;

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
    glm::mat4 model; 
    glm::mat4 proj;
    std::map<char, Character> characters;
    int maxWidth;
    int maxHeight;
    static bool initalized;
    static Shader shader;

    void LoadChar();

    TextRender();
    void Draw(glm::mat4 viewProj, glm::vec2 pos, float rotation, float scale, std::string text, glm::vec4 rgba);
};


struct Ticks {
    std::string text;
    glm::vec3 position;
};

enum class PlotsType : unsigned int {
    NO_PLOT,
    LINE_SEGMENTS,
    LINE,
    LINE_AREA,
    HISTOGRAM,
    HEAT_MAP
};

/*
* Still need to add axis to make subplots possible;
* Most plots are just point in 3d space with diffrent interpertaions.
* Heat 
*/
struct Figure {

    static bool initalized;
    static Shader shader;

    TextRender txtRender;

    std::string xLabel;
    std::string yLabel;
    std::string zLabel;
    std::string title;

    std::vector<Ticks> xTicks;
    std::vector<Ticks> yTicks;
    std::vector<Ticks> zTicks;

    glm::vec4 boarderColor;
    glm::vec4 backGroundColor;

    //Line axis;
    glm::vec4 axisColor;
    Line axis;
    float axisThickness;
    float axisAntiAliasing;

    glm::vec3 point;
    float length;
    glm::mat4 model;
    float thickness;
    glm::vec4 rgba;
    glm::vec2 resolution;
    float antiAliasing;
    unsigned int textureID;
    //Should this be static? UV don't change

    float thicknessCorrection;
    float antiAliasingCorrection;

    int drawCount;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    //Data stats for scaling points
    float dataMaxZ;
    float dataMinZ;
    float dataMaxY;
    float dataMinY;
    float dataMaxX;
    float dataMinX;
    glm::mat4 correctionPlotMat;
    glm::mat4 correctionAxisMat;

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
    float xTickScale;
    float yTickScale;
    float zTickScale;

    PlotsType plotType;

    Figure();
    ~Figure();

    void SetTitle(std::string title);
    void SetXLabel(std::string xLabel);
    void SetYLabel(std::string yLabel);
    void SetZLabel(std::string zLabel);
    void SetTextScale(float scale);
    void SetTickScale(float scale);
    void SetAxisScale(float scale);

    void SetPlotScale(float xScale, float yScale, float zScale);
    void SetPlotTranslate(float xTrans, float yTrans, float zTrans);
    //void SetPlotScaleY(float yScale);
    //void SetPlotScaleZ(float zScale);
    //void SetPlotTranslationX(float transX);
    //void SetPlotTranslationY(float transY);
    //void SetPlotTranslationZ(float transZ);

    void Hist(std::vector<float> data, float binStart, float binEnd,int binCount);
    void Plot(std::vector<glm::vec3> points);
    void PlotArea(std::vector<glm::vec3> points);
    void PoleFigure(std::vector<glm::quat> quats, glm::vec3 ref, float theta, float phi);

    //void CalculateFitTransform(std::vector<glm::vec3> points);
    void CalculateTicks();
    void CalculatePlotTransforms();
    void Draw(glm::mat4 proj);


};

#endif//PLOTSBASICS