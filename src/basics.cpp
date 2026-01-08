#include "basics.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

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


Segment::Segment(std::array<float,3>  _p , float _length,float _angle, float _thickness, std::array<float,3>  _rgb ,float _antiAliasing){
    if(!initalized){
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

        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            std::cout << "Hello" << std::endl;
            // open files
            vShaderFile.open("../shaders/SegmentVertex.vs");
            fShaderFile.open("../shaders/SegmentFragment.fs");
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


        initalized = true;
    }
    point = _p;
    length = _length;
    model[0] = cos(_angle);
    model[1] = sin(_angle);
    model[2] = -sin(_angle);
    model[3] = cos(_angle);
    thickness = _thickness;
    rgb = _rgb;
    antiAliasing = _antiAliasing;
}

//Line::Line(std::array<float,3> p1, std::array<float,3> p2, float thickness, std::array<float,3> rgb,float antiAliasing){
//    float rot =std::acos((p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2])/(std::sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2]*p1[2]) *std::sqrt(p1[0] * p2[0] + p2[1] * p2[1] + p2[2]*p2[2])));
//    float dis = std::sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));
//    Line(p1,dis,rot, thickness,rgb, antiAliasing);
//}

Segment::~Segment(){
    if(initalized){
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);
        glDeleteBuffers(1,&EBO);
        glDeleteProgram(ID);
        initalized = false;
    }
}

void Segment::Draw(unsigned int width, unsigned int height){
    glUseProgram(ID);
    resolution[0] = width;
    resolution[1] = height;
    glUniform2fv(glGetUniformLocation(ID, "resolution"),1,resolution.data());
    glUniform1fv(glGetUniformLocation(ID, "antialias"),1,&antiAliasing);
    glUniform1fv(glGetUniformLocation(ID, "thickness"),1,&thickness);
    glUniform1fv(glGetUniformLocation(ID, "len"),1,&length);
    glUniformMatrix2fv(glGetUniformLocation(ID, "model"),1,false,model.data());
    glUniform2fv(glGetUniformLocation(ID, "point"),1,point.data());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
}


Line::Line(float _angle, float _thickness, std::array<float,3>  _rgb ,float _antiAliasing){
    if(!initalized){

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
            vShaderFile.open("../shaders/LineVertex.vs");
            fShaderFile.open("../shaders/LineFragment.fs");
            gShaderFile.open("../shaders/LineGeometry.gs");
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


        initalized = true;
    }

    model[0] = cos(_angle);
    model[1] = sin(_angle);
    model[2] = -sin(_angle);
    model[3] = cos(_angle);
    thickness = _thickness;
    rgb = _rgb;
    antiAliasing = _antiAliasing;
}

//Line::Line(std::array<float,3> p1, std::array<float,3> p2, float thickness, std::array<float,3> rgb,float antiAliasing){
//    float rot =std::acos((p1[0] * p2[0] + p1[1] * p2[1] + p1[2] * p2[2])/(std::sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2]*p1[2]) *std::sqrt(p1[0] * p2[0] + p2[1] * p2[1] + p2[2]*p2[2])));
//    float dis = std::sqrt((p2[0]-p1[0])*(p2[0]-p1[0]) + (p2[1]-p1[1])*(p2[1]-p1[1]) + (p2[2]-p1[2])*(p2[2]-p1[2]));
//    Line(p1,dis,rot, thickness,rgb, antiAliasing);
//}

Line::~Line(){
    if(initalized){
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);
        //glDeleteBuffers(1,&EBO);
        glDeleteProgram(ID);
        initalized = false;
    }
}

void Line::AddPoint(std::array<float,3> point){
    points.push_back(point);
}

void Line::Build(){
    std::array<float, 3> first = (*points.begin());
    std::array<float, 3> firstN = (*(points.begin()+1));
    std::array<float, 3> firstDir{ first[0] - firstN[0] + first[0], first[1] - firstN[1] + first[1], first[2] - firstN[2] + first[2] };

    std::array<float, 3> last = (*(points.end()-1));
    std::array<float, 3> lastN = (*(points.end() - 2));
    std::array<float, 3> lastDir{ last[0]-lastN[0]+ last[0], last[1] - lastN[1] + last[1], last[2] - lastN[2] + last[2] };

    points.insert(points.begin(), firstDir);
    
    points.insert(points.end(), lastDir);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(std::array<float,3>),points.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void Line::Draw(unsigned int width, unsigned int height){
    glUseProgram(ID);
    resolution[0] = width;
    resolution[1] = height;
    //glUniform2fv(glGetUniformLocation(ID, "resolution"),1,resolution.data());
    glUniform1fv(glGetUniformLocation(ID, "antialias"),1,&antiAliasing);
    glUniform1fv(glGetUniformLocation(ID, "thickness"),1,&thickness);
    glUniformMatrix2fv(glGetUniformLocation(ID, "model"),1,false,model.data());
    glUniform3fv(glGetUniformLocation(ID, "color"), 1, rgb.data());
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, points.size());
}