
#define _USE_MATH_DEFINES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/basics.h"

#include <cmath>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

glm::mat4 proj(1.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    std::cout << "Hello" << std::endl;

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    glm::vec3 point(0.0f,0.0f,0.0f );
    glm::vec3 col(0.10f,0.10f,0.10f);
    Segment segment = Segment(point,1.0f,0.0f,1.0f,col,0.05f);
    Line axis = Line(M_PI* 0.0, 0.01f, col, 0.002f);
    axis.AddPoint(glm::vec3(-0.80f, 0.90f, 0.0f));
    axis.AddPoint(glm::vec3(-0.80f, -0.80f, 0.0f));
    axis.AddPoint(glm::vec3(0.85f, -0.80f, 0.0f));
    axis.Build();

    LineArea lineA = LineArea(M_PI* 0.0, 0.2f, col, 0.025f);
    for(int i = 0; i < 100; i++){
        lineA.AddPoint(glm::vec3((i* 2*M_PI/100)/6-0.5,cos(i* 2*M_PI/100),0.0f ));
    }
    lineA.Build();

    TextRender txtRender;

    glm::mat4 view(1.0f);
    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //segment.Draw(proj);
        axis.Draw(proj);
        lineA.Draw(proj);
        txtRender.Draw(proj,glm::vec2(0.0f,0.85f),-M_PI/2,"Count", glm::vec3( 0.3, 0.7f, 0.9f ));
        txtRender.Draw(proj,glm::vec2(0.0f, -0.95f), 0.0f, "Value", glm::vec3(0.3, 0.7f, 0.9f));
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    SCR_WIDTH = width;
    SCR_HEIGHT= height;
    glViewport(0, 0, width, height);
    float aspectRatio = (float)width / (float)height;
    if (aspectRatio >=1) {
        proj = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, 0.0f, 1.0f);
    }
    else {
        proj = glm::ortho(-1.0f, 1.0f, 1.0f/-aspectRatio, 1.0f / aspectRatio, 0.0f, 1.0f);
    }
    //
    //proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
}

