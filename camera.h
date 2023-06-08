#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>

class Camera final
{
    QVector3D _pos;
    float _phiAngle = 0.f;
    float _tettaAnggle = 0.f;
public:
    Camera() noexcept = default;;
    Camera(QVector3D pos, float phiAngle, float tettaAngle) noexcept;

    void ChangePos(QVector3D pos);
    void SetPhiAngle(float angle);
    void SetTettaAngle(float angle);

    [[nodiscard]] const QVector3D& GetPos() const noexcept;
    [[nodiscard]] float GetPhiAngle() const noexcept;
    [[nodiscard]] float GetTettaAngle() const noexcept;
};

#endif // CAMERA_H
