#ifndef ANDROIDGLINVESTIGATIONS_RENDERER_H // include guard - For prevent multiple definitions
#define ANDROIDGLINVESTIGATIONS_RENDERER_H

#include <EGL/egl.h>
#include <memory>
#include <chrono>

#include "Model.h"
#include "Shader.h"

struct android_app;

// Estrutura para o estado do jogo
struct GameState {
    long long totalDamageDealt = 0;
    long long currentMonsterHealth = 1000;
    long long autoClickDamagePerSecond = 10;
    int clicksPerSecond = 0;
    std::chrono::high_resolution_clock::time_point lastFrameTime;
};

class Renderer {
public:
    /*!
     * @param pApp the android_app this Renderer belongs to, needed to configure GL
     */
    inline Renderer(android_app *pApp) :
            app_(pApp),
            display_(EGL_NO_DISPLAY),
            surface_(EGL_NO_SURFACE),
            context_(EGL_NO_CONTEXT),
            width_(0),
            height_(0),
            shaderNeedsNewProjectionMatrix_(true) {
        initRenderer();
        gameState_.lastFrameTime = std::chrono::high_resolution_clock::now();
    }

    virtual ~Renderer();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();

    /*!
     * Renders all the models in the renderer
     */
    void render();

private:
    /*!
     * Performs necessary OpenGL initialization. Customize this if you want to change your EGL
     * context or application-wide settings.
     */
    void initRenderer();

    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void updateRenderArea();

    /*!
     * Creates the models for this sample. You'd likely load a scene configuration from a file or
     * use some other setup logic in your full game.
     */
    void createModels();

    void updateGameState(float deltaTime);

    android_app *app_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLint width_;
    EGLint height_;

    bool shaderNeedsNewProjectionMatrix_;

    std::unique_ptr<Shader> shader_;
    std::vector<Model> models_;

    GameState gameState_;
};

#endif //ANDROIDGLINVESTIGATIONS_RENDERER_H