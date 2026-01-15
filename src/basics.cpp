#define _USE_MATH_DEFINES
#include "basics.h"


#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  


float uvs[] = {
    0.0,  1.0f,  // top right
    0.0f, 0.0f,  // bottom right
    1.0f, 1.0f,  // bottom left
    1.0f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    0, 2, 3   // second Triangle
};




//unsigned int Line::VAO = 0;
//unsigned int Line::VBO = 0;
//unsigned int Line::EBO = 0;
//bool Line::initalized = false;
//unsigned int Line::shader = 0;

void checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}




Shader::Shader(){
}


void Shader::Load(std::string vertexPath, std::string fragmentPath, std::string geometryPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        std::cout << "Hello" << std::endl;
        // open files
        vShaderFile.open(vertexPath.c_str());
        fShaderFile.open(fragmentPath.c_str());
        gShaderFile.open(geometryPath.c_str());
        
        std::stringstream vShaderStream, fShaderStream, gShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        gShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        geometryCode = gShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    const char * gShaderCode = geometryCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment, geometry;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    checkCompileErrors(geometry, "GEOMETRY");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, geometry);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);
    std::cout << "Create Full Shader: " << ID << std::endl;
}

void Shader::Load(std::string vertexPath, std::string fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath.c_str());
        fShaderFile.open(fragmentPath.c_str());
        //fShaderFile.open("../shaders/SegmentFragment.fs");
        //vShaderFile.open("../shaders/SegmentVertex.vs");
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    std::cout << "Create Part Shader: " << ID << std::endl;
}

Shader::~Shader(){
    std::cout << "ID: "<< ID << " Removed !" << std::endl;
    glDeleteProgram(ID);
}


bool Segment::initalized = false;
Shader Segment::shader = Shader();
Segment::Segment(glm::vec3 _p , float _length,float _angle, float _thickness, glm::vec4 _rgba ,float _antiAliasing){
    if(!Segment::initalized){
        Segment::shader.Load("../shaders/SegmentVertex.vs","../shaders/SegmentFragment.fs");
        Segment::initalized = true;
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs),uvs,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 2 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    point = _p;
    length = _length;
    model = glm::mat4(1.0f);
    model[0][0] = cos(_angle);
    model[0][1] = sin(_angle);
    model[1][0] = -sin(_angle);
    model[1][1] = cos(_angle);
    model[2][2] = 1.0f;
    model[3][3] = 1.0f;
    thickness = _thickness;
    rgba = _rgba;
    antiAliasing = _antiAliasing;
}

//Line::Line(std::array<float,3> p1, std::array<float,3> p2, float thickness, std::array<float,3> rgb,float antiAliasing){
//    float rot =std::acos((p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2])/(std::sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2]*p1[2]) *std::sqrt(p1[0] * p2[0] + p2[1] * p2[1] + p2[2]*p2[2])));
//    float dis = std::sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));
//    Line(p1,dis,rot, thickness,rgb, antiAliasing);
//}

Segment::~Segment(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}

void Segment::Draw(glm::mat4 viewProj){
    glUseProgram(Segment::shader.ID);
    glUniformMatrix4fv(glGetUniformLocation(Segment::shader.ID, "mvp"),1,false, &viewProj[0][0]);
    glUniform1fv(glGetUniformLocation(Segment::shader.ID, "antialias"),1,&antiAliasing);
    glUniform1fv(glGetUniformLocation(Segment::shader.ID, "thickness"),1,&thickness);
    glUniform1fv(glGetUniformLocation(Segment::shader.ID, "len"),1,&length);
    glUniformMatrix2fv(glGetUniformLocation(Segment::shader.ID, "model"),1,false, &model[0][0]);
    glUniform2fv(glGetUniformLocation(Segment::shader.ID, "point"),1,&point[0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



bool Line::initalized = false;
Shader Line::shader = Shader();
Line::Line(float _angle, float _thickness, glm::vec4 _rgba ,float _antiAliasing){
    if(!Line::initalized){
        std::cout << "Line Not INIT"<< std::endl;
        Line::shader.Load("../shaders/LineVertex.vs","../shaders/LineFragment.fs","../shaders/LineGeometry.gs");
        Line::initalized = true;
    }
    model = glm::mat4(1.0f);
    model[0][0] = cos(_angle);
    model[0][1] = sin(_angle);
    model[1][0] = -sin(_angle);
    model[1][1] = cos(_angle);
    model[2][2] = 1.0f;
    model[3][3] = 1.0f;
    thickness = _thickness;
    rgba = _rgba;
    antiAliasing = _antiAliasing;
}

//Line::Line(std::array<float,3> p1, std::array<float,3> p2, float thickness, std::array<float,3> rgb,float antiAliasing){
//    float rot =std::acos((p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2])/(std::sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2]*p1[2]) *std::sqrt(p1[0] * p2[0] + p2[1] * p2[1] + p2[2]*p2[2])));
//    float dis = std::sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));
//    Line(p1,dis,rot, thickness,rgb, antiAliasing);
//}

Line::~Line(){
    
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    //glDeleteBuffers(1,&EBO);
    
}

void Line::AddPoint(glm::vec3 point){
    points.push_back(point);
}

void Line::Build(){
    glm::vec3 first = (*points.begin());
    glm::vec3 firstN = (*(points.begin()+1));
    glm::vec3 firstDir{ first[0] - firstN[0] + first[0], first[1] - firstN[1] + first[1], first[2] - firstN[2] + first[2] };

    glm::vec3 last = (*(points.end()-1));
    glm::vec3 lastN = (*(points.end() - 2));
    glm::vec3 lastDir{ last[0]-lastN[0]+ last[0], last[1] - lastN[1] + last[1], last[2] - lastN[2] + last[2] };

    points.insert(points.begin(), firstDir);
    
    points.insert(points.end(), lastDir);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(glm::vec3),points.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void Line::Draw(glm::mat4 viewProj){

    glm::mat4 mvp = viewProj * model;

    glUseProgram(Line::shader.ID);
    glUniformMatrix4fv(glGetUniformLocation(Line::shader.ID, "mvp"), 1, false, &mvp[0][0]);
    glUniform1fv(glGetUniformLocation(Line::shader.ID, "antialias"),1,&antiAliasing);
    glUniform1fv(glGetUniformLocation(Line::shader.ID, "thickness"),1,&thickness);
    glUniform4fv(glGetUniformLocation(Line::shader.ID, "color"), 1, &rgba[0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, points.size());
    glBindVertexArray(0);
}

bool LineArea::initalized = false;
Shader LineArea::shader = Shader();
LineArea::LineArea(float _angle, float _thickness, glm::vec4 _rgba ,float _antiAliasing){
    if(!initalized){
        shader.Load("../shaders/AreaVertex.vs","../shaders/AreaFragment.fs","../shaders/AreaGeometry.gs");
        initalized = true;
    }
    model = glm::mat4(1.0f);
    model[0][0] = cos(_angle);
    model[0][1] = sin(_angle);
    model[1][0] = -sin(_angle);
    model[1][1] = cos(_angle);
    model[2][2] = 1.0f;
    model[3][3] = 1.0f;
    thickness = _thickness;
    rgba = _rgba;
    antiAliasing = _antiAliasing;
}

//Line::Line(std::array<float,3> p1, std::array<float,3> p2, float thickness, std::array<float,3> rgb,float antiAliasing){
//    float rot =std::acos((p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2])/(std::sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2]*p1[2]) *std::sqrt(p1[0] * p2[0] + p2[1] * p2[1] + p2[2]*p2[2])));
//    float dis = std::sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));
//    Line(p1,dis,rot, thickness,rgb, antiAliasing);
//}

LineArea::~LineArea(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    //glDeleteBuffers(1,&EBO);
}

void LineArea::AddPoint(glm::vec3 point){
    points.push_back(point);
}

void LineArea::Build(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(glm::vec3),points.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void LineArea::Draw(glm::mat4 viewProj){
    glUseProgram(LineArea::shader.ID);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mvp"), 1, false, &viewProj[0][0]);
    glUniform1fv(glGetUniformLocation(shader.ID, "antialias"),1,&antiAliasing);
    glUniform1fv(glGetUniformLocation(shader.ID, "thickness"),1,&thickness);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"),1,false,&model[0][0]);
    glUniform4fv(glGetUniformLocation(shader.ID, "color"), 1, &rgba[0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, points.size());
    glBindVertexArray(0);
}

bool TextRender::initalized = false;
Shader TextRender::shader = Shader();
void TextRender::LoadChar(){
    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    // find path to font
    std::string font_name("../resources/fonts/static/Antonio-Bold.ttf");
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 64);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character;
            character.textureID = texture;
            character.size = glm::ivec2{int(face->glyph->bitmap.width), int(face->glyph->bitmap.rows)};
            character.bearing = glm::ivec2{face->glyph->bitmap_left, face->glyph->bitmap_top};
            character.advance = static_cast<unsigned int>(face->glyph->advance.x);
            characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    std::cout << "Hell22o" << std::endl;
}

TextRender::TextRender() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    if(!initalized){
        shader.Load("../shaders/text.vs","../shaders/text.fs");
        initalized = true;
    }
    LoadChar();

    proj = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

}
void TextRender::Draw(glm::mat4 viewProj,glm::vec2 pos, float rotation, float scale, std::string _text, glm::vec4 _rgba) {
    float textCenter = 0.0f;
    float x = 0.0f;
    float y = 0.0f;

    std::string::const_iterator c;
    for (c = _text.begin(); c != _text.end(); c++)
    {
        Character ch = characters[*c];
        textCenter = textCenter + (float((ch.advance >> 6)) * scale)/4.0f;
    }

    x = x - textCenter;

    model = glm::translate(glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, -1)), glm::vec3(pos.x - textCenter, pos.y, 0));
    glm::mat4 mvp = viewProj * model;
    glUseProgram(shader.ID);
    glUniform4f(glGetUniformLocation(shader.ID, "textColor"), _rgba.r, _rgba.g, _rgba.b,_rgba.a);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "mvp"),1,false,&mvp[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    
    // iterate through all characters
    //std::string::const_iterator c;
    for (c = _text.begin(); c != _text.end(); c++)
    {
        Character ch = characters[*c];
        float xpos = x + ch.bearing[0] * scale;
        float ypos = y - (ch.size[1] - ch.bearing[1]) * scale;

        float w = ch.size[0] * scale;
        float h = ch.size[1] * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


Figure::Figure(){
    TextRender txtRender = TextRender();
    xLabelScale = 0.003f;
    yLabelScale = 0.003f;
    zLabelScale = 0.003f;
    axisColor = glm::vec4(0.10f, 0.10f, 0.10f, 1.0f);
    axis = Line(M_PI * 0.0, 0.008f, axisColor, 0.003f);
    axis.AddPoint(glm::vec3(0.0f, 1.0f, 0.0f));
    axis.AddPoint(glm::vec3(0.0f, 0.0f, 0.0f));
    axis.AddPoint(glm::vec3(1.0f, 0.0f, 0.0f));
    axis.Build();

    model = glm::mat4(1.0f);
    rgba = glm::vec4(0.15f, 0.49f, 0.75f, 0.75f);
    thickness = 0.005;
    antiAliasing = 0.002f;

}

Figure::~Figure(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Figure::SetTitle(std::string title){

}

void Figure::SetXLabel(std::string _xLabel){
    xLabel = _xLabel;
}

void Figure::SetYLabel(std::string _yLabel){
    yLabel = _yLabel;
}

void Figure::SetZLabel(std::string _zLabel){
    zLabel = _zLabel;
}

void Figure::SetTextScale(float scale){
    xLabelScale = scale;
    yLabelScale = scale;
    zLabelScale = scale;
}

void Figure::SetPlotScale(float xScale, float yScale, float zScale) {
    model = glm::scale(model,glm::vec3(xScale, yScale, zScale));
}

void Figure::SetPlotTranslate(float xTrans, float yTrans, float zTrans) {
    model = glm::translate(model, glm::vec3(xTrans, yTrans, zTrans));
}

void Figure::PlotArea(std::vector<glm::vec3> points){
    //Delete a older plot.
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    drawCount = points.size();
}

void Figure::Hist(std::vector<float> data, float binStart, float binEnd, int binCount){
    float binWidth = (binEnd - binStart) / binCount;
    std::vector<int> count;
    count.resize(binCount);
    for (auto i = data.begin(); i != data.end(); i++) {
        if (*i < binStart) {
            count[0]++;
            continue;
        }
        if (*i > binEnd) {
            count[data.size() - 1]++;
            continue;
        }
        for (int j = 0; j < count.size(); j++) {
            if (*i <= (binWidth*j + binStart)) {
                count[j] = count[j] + 1;
                break;
            }
        }
    }
    std::vector<glm::vec3> hist;
    for (int i =0; i != count.size(); i++) {
        hist.push_back(glm::vec3(binStart + binWidth * (float(i)), count[i], 0.0f));
    }

    PlotArea(hist);
    return;
}

void Figure::Draw(glm::mat4 proj){
    glm::mat4 correctionMat = glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(0.08f,0.08f,0.0f)),glm::vec3(0.85f,0.85f,1.0f));
    glm::mat4 mvp = proj * correctionMat;

    //Draw Text
    txtRender.Draw(mvp,glm::vec2(0.5f,0.0f),-M_PI/2,yLabelScale,yLabel, glm::vec4( 0.10f, 0.10f, 0.10f,1.0f));
    txtRender.Draw(mvp,glm::vec2(0.5f,-0.085f), 0.0f,xLabelScale,xLabel, glm::vec4(0.10f, 0.10f, 0.10f,1.0f));
    //Draw Axis Lines;
    axis.Draw(mvp);
    //Draw Data
    glm::mat4 correctionPlotMat = glm::scale(glm::mat4(1.0f),glm::vec3((1.0f) / (9.0f), 1.0f/4.0f,1.0f));
    mvp = proj * correctionMat * correctionPlotMat;
    unsigned int ID = LineArea::shader.ID;
    glUseProgram(ID);
    glUniformMatrix4fv(glGetUniformLocation(ID, "mvp"), 1, false, &mvp[0][0]);
    glUniform1fv(glGetUniformLocation(ID, "antialias"), 1, &antiAliasing);
    glUniform1fv(glGetUniformLocation(ID, "thickness"), 1, &thickness);
    glUniformMatrix4fv(glGetUniformLocation(ID, "model"), 1, false, &model[0][0]);
    glUniform4fv(glGetUniformLocation(ID, "color"), 1, &rgba[0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, drawCount);
    glBindVertexArray(0);
}
