#include "player.h"

Matrix Player::GetPivotRotationMatrix(Vector3 pivot, Vector3 rotationAngles)
{
    // Step 1: Translate the cuboid so the pivot point is at the origin
    Matrix translateToOrigin = MatrixTranslate(-pivot.x, -pivot.y, -pivot.z);

    // Step 2: Apply the rotation
    Matrix rotation = MatrixRotateXYZ(rotationAngles);

    // Step 3: Translate the cuboid back to its original position
    Matrix translateBack = MatrixTranslate(pivot.x, pivot.y, pivot.z);

    // Combine the transformations: translateBack * rotation * translateToOrigin
    return MatrixMultiply(MatrixMultiply(translateBack, rotation), translateToOrigin);
}

void Player::StartMove(Vector3 direction)
{
    if(!m_isMoving)
    {
        m_isMoving = true;
        m_direction = direction;
        m_pivotPoint = {direction.x * 0.5f, direction.y * 0.5f, direction.z * 0.5f};
    }
}

bool Player::HasReachedTarget()
{
    return (fabs(m_rot.x) >= halfPi || 
            fabs(m_rot.y) >= halfPi || 
            fabs(m_rot.z) >= halfPi);
}

void Player::Move(const float& deltaTime)
{
    if(m_isMoving)
    {
        m_rot.x += m_direction.x * m_rotSpeed * deltaTime;
        m_rot.y += m_direction.y * m_rotSpeed * deltaTime;
        m_rot.z += m_direction.z * m_rotSpeed * deltaTime;

        m_playerModel.transform = GetPivotRotationMatrix(m_pivotPoint, m_rot);

        if (HasReachedTarget()) // Implement this function if needed
        {
            m_isMoving = false;
        }
    }
}

void Player::HandleKeyInput()
{
    if (IsKeyPressed('W'))
    {
        StartMove({0.0f, 1.0f, 0.0f}); // Move North
    }
    if (IsKeyPressed('S'))
    {
        StartMove({0.0f, -1.0f, 0.0f}); // Move South
    }
    if (IsKeyPressed('A'))
    {
        StartMove({-1.0f, 0.0f, 0.0f}); // Move West
    }
    if (IsKeyPressed('D'))
    {
        StartMove({1.0f, 0.0f, 0.0f}); // Move East
    }
}
