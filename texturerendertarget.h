#ifndef TEXTURERENDERTARGET_H
#define TEXTURERENDERTARGET_H

#include <Qt3DRender/QRenderTarget>
#include <Qt3DRender/QRenderTargetOutput>
#include <Qt3DRender/QTexture>

// Encapsulates a 2D texture that a frame graph can render into.
class TextureRenderTarget : public Qt3DRender::QRenderTarget
{
    Q_OBJECT
public:
    TextureRenderTarget(Qt3DCore::QNode *parent = nullptr, 
                        const QSize &size = QSize(500, 500),
                        Qt3DRender::QRenderTargetOutput::AttachmentPoint attatchmentPoint 
                                                = Qt3DRender::QRenderTargetOutput::Color0);

    void setSize(const QSize &size);
    QSize getSize() { return size; }
    Qt3DRender::QSharedGLTexture* getTexture();

private:
    QSize size;
    Qt3DRender::QRenderTargetOutput *output;
    Qt3DRender::QSharedGLTexture *texture;
    // To enable depth testing
    Qt3DRender::QRenderTargetOutput *depthTextureOutput;
    Qt3DRender::QSharedGLTexture *depthTexture;
};

#endif // TEXTURERENDERTARGET_H
