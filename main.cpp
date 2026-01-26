
#define _USE_MATH_DEFINES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "src/basics.h"
#include <H5Cpp.h>
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
    glm::vec4 col(0.10f,0.10f,0.10f,1.0f);
    glm::vec4 colShade(0.15f,0.49f,0.75f,0.75f);
    Segment segment = Segment(point,1.0f,0.0f,1.0f,col,0.05f);
    LineArea lineA = LineArea(M_PI * 0.0, 0.2f, colShade, 0.025f);
    Line lineB = Line(M_PI * 0.0, 0.2f, colShade, 0.025f);
    H5::H5File file("../test/data/Photo/TestData.h5", H5F_ACC_RDONLY);
    H5::DataSet dataset = file.openDataSet("/Pol1");

    H5::DataSpace dataspace = dataset.getSpace();
    hsize_t dims[2];
    int rank = dataspace.getSimpleExtentDims(dims, NULL);
    hsize_t dataset_size = dims[0] * dims[1];

    // Create a buffer (e.g., std::vector) in memory to hold the data
    std::vector<float> data_out;
    data_out.resize(dataset_size);
    // Read the data from the dataset into the memory buffer
    // The PredType::NATIVE_INT specifies the type in memory (C++ int)
    dataset.read(data_out.data(), H5::PredType::NATIVE_FLOAT);
    std::cout << data_out[0] << std::endl;
 
    glm::mat4 view(1.0f);
    
    Figure fig;
    fig.SetXLabel("Label");
    fig.SetYLabel("Count");
    fig.SetTextScale(0.0006f);
    fig.SetTickScale(0.0006f);
    //fig.Hist(data_out,0, 65535,200);
    fig.SetPlotTranslate(0.0f, 0.0f, 0.0f);
    fig.SetPlotScale(0.0f, 0.0f, 0.0f);
    std::vector<glm::quat>quats{glm::quat(0.0f,0.0f,0.0f,1.0f)};
    fig.PoleFigure(quats,glm::vec3(0.0f,0.0f,-1.0f),0.0f,0.0f);
    
    proj = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    //fig.LineArea();
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
        fig.Draw(proj);
        
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
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
        proj = glm::ortho(0.0f, aspectRatio, 0.0f, 1.0f, 0.0f, 1.0f);
    }else {
        proj = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f / aspectRatio, 0.0f, 1.0f);
    }
    //
    //proj = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
}

