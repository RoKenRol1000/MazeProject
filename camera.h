#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QtMultimedia/QSoundEffect>

class Camera final
{
    QSoundEffect _player;
    QVector3D _pos;
    QVector3D _front;
    QVector3D _up;
    QVector3D _right;

    float _pitchAngle = 0.f;
    float _yawAngle = -90.f;
    float _movementSpeed = 2.f;
    float _counter = 0.f;
    float _movementCoff = 1;

    void UpdateVectors() noexcept;
public:
    Camera(QVector3D pos = {}, float yawAngle = -90, float pitchAngle = 0) noexcept;

    void ChangePos(QVector3D pos) noexcept;
    void SetPitchAngle(float angle) noexcept;
    void SetYawAngle(float angle) noexcept;
    void SetMoveCoff(float coff) noexcept;

    void MoveForward(float steps) noexcept;
    void MoveSideway(float steps) noexcept;

    QMatrix4x4 GetViewMatrix() noexcept;
    [[nodiscard]] const QVector3D& GetFrontVector() const noexcept;
    [[nodiscard]] const QVector3D& GetRightVector() const noexcept;
    [[nodiscard]] const QVector3D& GetUpVector() const noexcept;

    [[nodiscard]] const QVector3D& GetPos() const noexcept;
    [[nodiscard]] float GetPitchAngle() const noexcept;
    [[nodiscard]] float GetYawAngle() const noexcept;
};

#endif // CAMERA_H
