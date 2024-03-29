// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QWindow>
#include <QOpenGLFunctions>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

//! [1]
class OpenGLWindow : public QWindow, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = nullptr);
    virtual ~OpenGLWindow() override;

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override;

private:
    bool m_animating = false;

    QOpenGLContext *m_context = nullptr;
    QOpenGLPaintDevice *m_device = nullptr;
};
//! [1]

