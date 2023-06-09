#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera final
{
    QVector3D _pos;
    QVector3D _front {0.f, 0.f, -1.f};
    QVector3D _up {0.f, 1.f, 0.f};
    QVector3D _right {-1.f, 0.f, 0.f};

    float _pitchAngle = 0.f;
    float _yawAngle = 90.f;
    float _movementSpeed = 0.1f;

    void UpdateVectors() noexcept;
public:
    Camera() noexcept = default;;
    Camera(QVector3D pos, float phiAngle, float tettaAngle) noexcept;

    void ChangePos(QVector3D pos) noexcept;
    void SetPitchAngle(float angle) noexcept;
    void SetYawAngle(float angle) noexcept;

    void MoveForward(float steps) noexcept;
    void MoveSideway(float steps) noexcept;

    QMatrix4x4 GetViewMatrix() noexcept;
    [[nodiscard]] const QVector3D& GetPos() const noexcept;
    [[nodiscard]] float GetPitchAngle() const noexcept;
    [[nodiscard]] float GetYawAngle() const noexcept;
};

#endif // CAMERA_H
