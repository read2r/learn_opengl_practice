#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(int argc, char** argv) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /*
    float vertices0[] = {
        // positions        //colors
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    */

   Shader shaderProgram0("./shader/shader.vs", "./shader/shader.fs");
   Shader shaderProgram1("./shader/shader.vs", "./shader/shader2.fs");

    float vertices0[] = {
        // positions
         0.5f,  0.5f, 0.0f,
         0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    float vertices1[] = {
        0.5f,  -0.5f, 0.0f,
        -0.5f,  -0.5f, 0.0f,
        -0.5f,  0.0f, 0.0f,
    };

    unsigned int VAO0, VAO1;
    unsigned int VBO0, VBO1;

    glGenVertexArrays(1, &VAO0);
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO0);
    glGenBuffers(1, &VBO1);

    glBindVertexArray(VAO0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // wire frame mode;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // render loop
    while(!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // rendering commands here
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram0.use();
        glBindVertexArray(VAO0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shaderProgram1.use();

        float timeValue = (float)(glfwGetTime());
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram1.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO0);
    glDeleteBuffers(1, &VBO1);
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        glClearColor(0.3f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}