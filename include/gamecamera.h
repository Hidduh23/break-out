#include "raylib.h"

constexpr Vector3 defaultPos = { 10.0f, 10.0f, 10.0f };
constexpr Vector3 defaultTarget = { 0.0f, 0.0f, 0.0f };
constexpr Vector3 defaultUp = { 0.0f, 1.0f, 0.0f };
constexpr float defaultFovy = 45.0f;
constexpr float defaultRadius= -20.0f;

class GameCamera
{
public:
    GameCamera();

    const void Update(float mouseWheelMove, Vector2 mouseDelta);
    const void Reset();
    inline const Camera& Get(){
        return m_camera;
    }

private:
    Camera3D m_camera = { 0 };
    float m_angle     = 0.0f;
    float m_radius    = defaultRadius;
};