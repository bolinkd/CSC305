#include "simulation.h"

#include "scene.h"

#include "imgui.h"

#include <math.h>

#define FLYTHROUGH_CAMERA_IMPLEMENTATION
#include "flythrough_camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <SDL2/SDL.h>

std::vector<uint32_t> CubeTransformIds;
std::vector<uint32_t> TeapotTransformIds;

void Simulation::Init(Scene* scene)
{
    mScene = scene;

    std::vector<uint32_t> loadedMeshIDs;

    uint32_t CubeId;

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/cube/cube.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        AddMeshInstance(mScene, loadedMeshID, &CubeId);

        // scale up the cube
        uint32_t CubeTransformId = scene->Instances[CubeId].TransformID;
        CubeTransformIds.push_back(CubeTransformId);
        scene->Transforms[CubeTransformId].Translation += glm::vec3(0.0f, 2.0f, 0.0f);
        scene->Transforms[CubeTransformId].Scale = glm::vec3(2.0f);
    }

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/teapot/teapot.obj", &loadedMeshIDs);

    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        // place a teapot on top of the cube
        {
            uint32_t TeapotId;
            AddMeshInstance(mScene, loadedMeshID, &TeapotId);
            uint32_t TeapotTransformId = scene->Instances[TeapotId].TransformID;
            TeapotTransformIds.push_back(TeapotTransformId);
            scene->Instances[TeapotId].ParentID = CubeId;
            scene->Transforms[TeapotTransformId].Translation += glm::vec3(0.0f, 0.0f, 6.0f);
            scene->Transforms[TeapotTransformId].Scale = glm::vec3(0.5f);
            //scene->Transforms[newTransformID].RotationOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
            //glm::mat4 transformxD = glm::rotate(float(M_PI/2), glm::vec3(0.0, 1.0, 0.0));
            //scene->Transforms[newTransformID].Rotation = glm::quat(transformxD);
        }
/*
        // place a teapot on the side
        {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            scene->Instances[newInstanceID].ParentID = CubeId;
            scene->Transforms[newTransformID].Scale = glm::vec3(0.5f);
            scene->Transforms[newTransformID].Translation += glm::vec3(3.0f, 1.0f, 4.0f);
            glm::mat4 transformxD = glm::rotate(float(M_PI) / 2, glm::vec3(1.0, 1.0, 1.0));
            scene->Transforms[newTransformID].Rotation = glm::quat(transformxD);
        }

        // place another teapot on the side
        {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            scene->Transforms[newTransformID].Translation += glm::vec3(3.0f, 1.0f, -4.0f);
        }
*/
    }

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/floor/floor.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        AddMeshInstance(mScene, loadedMeshID, nullptr);
    }

    Camera mainCamera;
    mainCamera.Eye = glm::vec3(5.0f);
    glm::vec3 target = glm::vec3(0.0f);
    mainCamera.Look = normalize(target - mainCamera.Eye);
    mainCamera.Up = glm::vec3(0.0f, 1.0f, 0.0f);
    mainCamera.FovY = glm::radians(70.0f);
    mScene->MainCamera = mainCamera;
}

void Simulation::HandleEvent(const SDL_Event& ev)
{
    if (ev.type == SDL_MOUSEMOTION)
    {
        mDeltaMouseX += ev.motion.xrel;
        mDeltaMouseY += ev.motion.yrel;
    }
}

float totalTime = 0.0f;

void Simulation::Update(float deltaTime)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    totalTime += deltaTime;

    for (uint32_t transformId : TeapotTransformIds )
    {
        glm::mat4 transformxD = glm::rotate(totalTime, glm::vec3(0.0, 1.0, 0.0));
        mScene->Transforms[transformId].Rotation = glm::quat(transformxD);
    }
    int mx, my;
    Uint32 mouse = SDL_GetMouseState(&mx, &my);

    if ((mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0)
    {
        flythrough_camera_update(
            value_ptr(mScene->MainCamera.Eye),
            value_ptr(mScene->MainCamera.Look),
            value_ptr(mScene->MainCamera.Up),
            NULL,
            deltaTime,
            5.0f, // eye_speed
            0.1f, // degrees_per_cursor_move
            80.0f, // max_pitch_rotation_degrees
            mDeltaMouseX, mDeltaMouseY,
            keyboard[SDL_SCANCODE_W], keyboard[SDL_SCANCODE_A], keyboard[SDL_SCANCODE_S], keyboard[SDL_SCANCODE_D],
            keyboard[SDL_SCANCODE_SPACE], keyboard[SDL_SCANCODE_LCTRL],
            0);
    }

    mDeltaMouseX = 0;
    mDeltaMouseY = 0;

    if (ImGui::Begin("Example GUI Window"))
    {
        ImGui::Text("Mouse Pos: (%d, %d)", mx, my);
        ImGui::Text("FPS: (%d)", int(1/deltaTime));
    }
    ImGui::End();
}

void* Simulation::operator new(size_t sz)
{
    // zero out the memory initially, for convenience.
    void* mem = ::operator new(sz);
    memset(mem, 0, sz);
    return mem;
}
    
