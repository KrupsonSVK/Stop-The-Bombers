// - Controls: LEFT, RIGHT, UP, DOWN, "R" to reset, SPACE to fire

#include <iostream>
#include <vector>
#include <map>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "camera.h"
#include "generator.h"
#include "player.h"
#include "space.h"

static const GLFWvidmode* WINDOW_MODE;
Scene scene;

auto terminate(){

    std::cerr << "Game (un)expectly crashed!" << std::endl;

    glfwTerminate();
    return EXIT_FAILURE;
}


void InitializeScene() {
    scene.objects.clear();

    auto camera = CameraPtr(new Camera{ 80.0f, 1.0f, 0.1f, 100.0f});
    camera->position.z = -15.0f;
    scene.camera = camera;

    auto space = SpacePtr(new Space{WINDOW_MODE->width,WINDOW_MODE->height});
    scene.objects.push_back(space);

    auto generator = GeneratorPtr(new Generator{});
    generator->position.x = -20.0f;
    scene.objects.push_back(generator);

    auto player = PlayerPtr(new Player{});
    player->position.x = 10.f;
    scene.objects.push_back(PlayerPtr(player));
}


void OnKeyPress(GLFWwindow* /*w*/, int key, int /*c*/, int action, int /*m*/) {

    scene.keyboard[key] = action;

    if (key == GLFW_KEY_R && action == GLFW_PRESS){
        InitializeScene();
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwTerminate();
    }
}


void OnMouseMove(GLFWwindow* /* window */, double xpos, double ypos) {

    scene.mouse.x = xpos;
    scene.mouse.y = ypos;
}


void setupOpenGL(){

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


GLFWwindow* setupWindow(){

    WINDOW_MODE = glfwGetVideoMode(glfwGetPrimaryMonitor());
    auto window = glfwCreateWindow(WINDOW_MODE->width-400, WINDOW_MODE->height-300, "Chickens The Game", nullptr, nullptr);///**/glfwGetPrimaryMonitor(), nullptr);

    if (!window){
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    if (!glewIsSupported("GL_VERSION_3_3")){
        return NULL;
    }
    return window;
}


void bindKeyboardHandlers(GLFWwindow* window){

    glfwSetKeyCallback(window, OnKeyPress);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}


void initOpenGL(){

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}


void clrscr(){

    glClearColor(.5f,.5f,.5f,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(void) {

    if (!glfwInit()){
        return EXIT_FAILURE;
    }
    setupOpenGL();

    auto window = setupWindow();
    if (!window){
        return terminate();
    }
    initOpenGL();

    bindKeyboardHandlers(window);

    InitializeScene();

    auto gameOver = false;
    auto time = (GLfloat)glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        auto dt = (GLfloat)glfwGetTime() - time;
        time = (GLfloat)glfwGetTime();

        clrscr();
        //        if(!gameOver){
        //        if(!scene.Update(dt))
        //          gameOver = true;
        scene.Update(dt);
        scene.Render();
        //}

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return EXIT_SUCCESS;
}
