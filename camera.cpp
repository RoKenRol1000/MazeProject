#include "camera.h"

#include <algorithm>

namespace
{
    constexpr float PI = 3.1415f;
    constexpr QVector3D worldUp {0.f, 1.f, 0.f};
}

static float DegreesToRadians(float angle)
{
    return PI / 180 * angle;
}

Camera::Camera(QVector3D pos, float phiAngle, float tettaAngle) noexcept
{}

void Camera::ChangePos(QVector3D pos) noexcept
{
    _pos = std::move(pos);
}
void Camera::SetPitchAngle(float angle) noexcept
{
    _pitchAngle = angle;
    if (_pitchAngle > 89.f)
    {
        _pitchAngle = 89.f;
    }
    if (_pitchAngle < -89.f)
    {
        _pitchAngle = -89.f;
    }
    UpdateVectors();
}
void Camera::SetYawAngle(float angle) noexcept
{
    _yawAngle = angle;
    UpdateVectors();
}

void Camera::UpdateVectors() noexcept
{
    _front.setX(std::cos(DegreesToRadians(_yawAngle)) * std::cos(DegreesToRadians(_pitchAngle)));
    _front.setY(std::sin(DegreesToRadians(_pitchAngle)));
    _front.setZ(std::sin(DegreesToRadians(_yawAngle)) * std::cos(DegreesToRadians(_pitchAngle)));
    _front.normalize();
    _right = QVector3D::crossProduct(_front, worldUp);
    _right.normalize();
    _up = QVector3D::crossProduct(_right, _front);
    _up.normalize();
}

void Camera::MoveForward(float steps) noexcept
{
    _pos += steps * _movementSpeed * QVector3D{_front.x(), 0, _front.z()};
}
void Camera::MoveSideway(float steps) noexcept
{
    _pos += steps * _movementSpeed * QVector3D{_right.x(), 0, _right.z()};
}

QMatrix4x4 Camera::GetViewMatrix() noexcept
{
    UpdateVectors();
    QMatrix4x4 view;
    view.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    view.lookAt(_pos, _pos + _front, _up);
    return view;
}

[[nodiscard]] const QVector3D& Camera::GetPos() const noexcept
{
    return _pos;
}

[[nodiscard]] float Camera::GetPitchAngle() const noexcept
{
    return _pitchAngle;
}

[[nodiscard]] float Camera::GetYawAngle() const noexcept
{
    return _yawAngle;
}
