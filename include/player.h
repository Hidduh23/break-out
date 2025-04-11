#include "raylib.h"
#include "raymath.h"

class Player
{
public:
    Player() = default;

    void HandleKeyInput();
    void Move(const float& deltaTime);

    inline const Model& GetModel() const{
        return m_playerModel;
    }

    inline const Vector3& GetPos() const{
        return m_pos;
    }

    inline const Vector3& GetRot() const{
        return m_rot;
    }

private:

    Matrix GetPivotRotationMatrix(Vector3 pivot, Vector3 rotationAngles);
    void StartMove();
    bool HasReachedTarget();

    Vector3   m_pos = { 0.0f, 0.5f, 0.0f };
    Vector3   m_rot = { 0.0f, 0.0f, 0.0f };

    bool      m_isMoving = false;

    Vector3   m_direction = { 0.0f, 0.0f, 0.0f };
    Vector3   m_pivotPoint = { 0.0f, 0.0f, 0.0f };
    Vector3   m_displacement = { 0.0f, 0.0f, 0.0f };

    Mesh      m_playerMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model     m_playerModel = LoadModelFromMesh(m_playerMesh);
    float     m_rotSpeed = PI;
    // Check if the absolute rotation in any direction (x, y, or z) has reached π/2
    const float m_rotStop = PI / 2.0f;
};