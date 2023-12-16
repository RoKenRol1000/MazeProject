#include "camera.h"
#include <QDir>
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

void Camera::SetMoveCoff(float coff) noexcept
{
    _movementCoff = coff;
}
Camera::Camera(QVector3D pos, float yawAngle, float pitchAngle) noexcept:_pos(pos), _yawAngle(yawAngle), _pitchAngle(pitchAngle)
{
    UpdateVectors();
}

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
    _counter += 10.f*std::abs(steps);
    QVector3D front;
    front.setX(std::cos(DegreesToRadians(_yawAngle)));
    front.setZ(std::sin(DegreesToRadians(_yawAngle)));
    front.normalize();
    _pos += steps * _movementCoff * _movementSpeed * front;
}
void Camera::MoveSideway(float steps) noexcept
{
    _pos += steps * _movementCoff * _movementSpeed * QVector3D{_right.x(), 0, _right.z()};
}


QMatrix4x4 Camera::GetViewMatrix() noexcept
{
    UpdateVectors();
    QVector3D shake = 0.1 * std::sin(_counter * _movementCoff/1.5) * _right + 0.1 * std::abs(std::sin(_counter * _movementCoff/1.5)) * _up;
    QMatrix4x4 view;
    view.lookAt(_pos + shake, _pos + shake + _front, _up);

    //qDebug()<<_counter<<' '<<(_counter/1.5 >= 2 * PI);
    if (_counter/1.5 >= 2 * PI)
    {
        _counter = 0.f;
    }
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

[[nodiscard]] const QVector3D& Camera::GetFrontVector() const noexcept
{
    return _front;
}

[[nodiscard]]const QVector3D& Camera::GetRightVector() const noexcept
{
    return _right;
}

[[nodiscard]]const QVector3D& Camera::GetUpVector() const noexcept
{
    return _up;
}
