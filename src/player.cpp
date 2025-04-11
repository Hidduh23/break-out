#include "player.h"

Matrix Player::GetPivotRotationMatrix(Vector3 pivot, Vector3 rotationAngles)
{
    Matrix translateToOrigin = MatrixTranslate(-pivot.x, -pivot.y, -pivot.z);
    Matrix rotation = MatrixRotateXYZ(rotationAngles);
    Matrix translateBack = MatrixTranslate(pivot.x, pivot.y, pivot.z);

    return MatrixMultiply(MatrixMultiply(translateBack, rotation), translateToOrigin);
}

void Player::StartMove()
{
    if(!m_isMoving)
    {
        m_isMoving = true;
    }
}

bool Player::HasReachedTarget()
{
    return (fabs(m_rot.x) >= m_rotStop || 
            fabs(m_rot.y) >= m_rotStop || 
            fabs(m_rot.z) >= m_rotStop);
}

void Player::Move(const float& deltaTime)
{
    if (m_isMoving)
    {
        // Update rotation
        m_rot += m_direction * m_rotSpeed * deltaTime;

        // Check if the rotation has reached its target
        if (HasReachedTarget())
        {
            m_isMoving = false;
            m_pos += m_displacement;
            m_rot = {0.0f, 0.0f, 0.0f};
        }

        // Update the model's transformation matrix
        m_playerModel.transform = GetPivotRotationMatrix(m_pivotPoint, m_rot);
    }
}

void Player::HandleKeyInput()
{
    if(!m_isMoving)
    {
        if (IsKeyPressed('W'))
        {
            m_pivotPoint = {-0.5f, 0.5f, 0.0f};
            m_direction = {0.0f, 0.0f, -1.0f};
            m_displacement = {1.0f, 0.0f, 0.0f};
            StartMove();
        }
        if (IsKeyPressed('S'))
        {
            m_pivotPoint = {0.5f, 0.5f, 0.0f};
            m_direction = {0.0f, 0.0f, 1.0f};
            m_displacement = {-1.0f, 0.0f, 0.0f};
            StartMove();
        }
        if (IsKeyPressed('A'))
        {
            m_pivotPoint = {0.0f, 0.5f, 0.5f};
            m_direction = {-1.0f, 0.0f, 0.0f};
            m_displacement = {0.0f, 0.0f, -1.0f};
            StartMove();
        }
        if (IsKeyPressed('D'))
        {
            m_pivotPoint = {0.0f, 0.5f, -0.5f};
            m_direction = {1.0f, 0.0f, 0.0f};
            m_displacement = {0.0f, 0.0f, 1.0f};
            StartMove();
        }
        if (IsKeyPressed('Q'))
        {
            m_pivotPoint = {0.0f, 0.0f, 0.0f};
            m_direction = {0.0f, 1.0f, 0.0f};
            m_displacement = {0.0f, 0.0f, 0.0f};
            StartMove();
        }
        if (IsKeyPressed('E'))
        {
            m_pivotPoint = {0.0f, 0.0f, 0.0f};
            m_direction = {0.0f, -1.0f, 0.0f};
            m_displacement = {0.0f, 0.0f, 0.0f};
            StartMove();
        }
    }
}
