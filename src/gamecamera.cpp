#include <cmath>
#include "gamecamera.h"

GameCamera::GameCamera()
{
    m_camera.position = defaultPos;           // Camera position
    m_camera.target = defaultTarget;          // Camera looking at point
    m_camera.up = defaultUp;                  // Camera up vector (rotation towards target)
    m_camera.fovy = defaultFovy;              // Camera field-of-view Y
    m_camera.projection = CAMERA_PERSPECTIVE; // Camera projection type
}

const void GameCamera::Update(float mouseWheelMove, Vector2 mouseDelta)
{
    m_camera.fovy -= mouseWheelMove;
    m_angle += mouseDelta.x * 0.005f;
    m_camera.position.x = m_radius * cos(m_angle);
    m_camera.position.z = m_radius * sin(m_angle);

    UpdateCamera(&m_camera, CAMERA_CUSTOM);
}

const void GameCamera::Reset()
{
    m_angle = 0.0f;
    m_radius = defaultRadius; 
    m_camera.fovy = defaultFovy;
    m_camera.position = defaultPos;
    UpdateCamera(&m_camera, CAMERA_CUSTOM);
}