#ifndef OFFSCREENENGINEDELEGATE_H
#define OFFSCREENENGINEDELEGATE_H

#include "offscreenengine.h"
#include <QLabel>
#include <Qt3DRender/QRenderCaptureReply>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL.h>

// Example class that requests frames from the offscreen engine.
// The engine's framegraph generates the frame, which notifies this delegate.
// Once the frame is set in the provided label, a new frame is requested.
class OffscreenEngineDelegate : public QObject
{
    Q_OBJECT
public:
    OffscreenEngineDelegate(OffscreenEngine *engine, QLabel *label);
    virtual ~OffscreenEngineDelegate();

    GLuint loadTexturewithSDL(const QImage &sourceImage, GLenum texture_format);
    SDL_Surface* QImage_toSDLSurface(const QImage &sourceImage);
    GLuint GLID();

private:
    OffscreenEngine *engine;
    QLabel *label;
    Qt3DRender::QRenderCaptureReply *reply;
    GLuint gluid;

private Q_SLOTS:
    void onImageRendered();

private:
    void requestRenderCapture();
};

#endif // OFFSCREENENGINEDELEGATE_H
