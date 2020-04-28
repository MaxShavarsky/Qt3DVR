#include "offscreenenginedelegate.h"
#include <GL/gl.h>

OffscreenEngineDelegate::OffscreenEngineDelegate(OffscreenEngine *engine, QLabel *label) :
    engine(engine),
    label(label),
    reply(nullptr)
{
    // Immediately request a render capture.
    // Every time we receive a reply, we then
    // re-request a new capture.
    requestRenderCapture();
}

OffscreenEngineDelegate::~OffscreenEngineDelegate()
{
    delete reply;
}

void OffscreenEngineDelegate::requestRenderCapture()
{
    delete reply;
    reply = engine->getRenderCapture()->requestCapture();
    connect(reply, SIGNAL(completed()), this, SLOT(onImageRendered()));
}

void OffscreenEngineDelegate::onImageRendered()
{
    // Get the image from the reply and display it in the label.
    label->setPixmap(QPixmap::fromImage(reply->image()));
    reply->image().save("/home/maxshavarsky/Pictures/reply_image.png");
    gluid = loadTexturewithSDL(label->pixmap()->toImage(),GL_RGB8);
    // Request another render capture.
    requestRenderCapture();
}



GLuint OffscreenEngineDelegate::GLID() {
    return gluid;
}

SDL_Surface* OffscreenEngineDelegate::QImage_toSDLSurface(const QImage &sourceImage) {
    // Ensure that the source image is in the correct pixel format
    QImage image = sourceImage;
    if (image.format() != QImage::Format_ARGB32)
        image = image.convertToFormat(QImage::Format_ARGB32);

    // QImage stores each pixel in ARGB format
    // Mask appropriately for the endianness
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 amask = 0x000000ff;
    Uint32 rmask = 0x0000ff00;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0xff000000;
#else
    Uint32 amask = 0xff000000;
    Uint32 rmask = 0x00ff0000;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x000000ff;
#endif

    return SDL_CreateRGBSurfaceFrom((void*)image.constBits(),
                                    image.width(), image.height(), image.depth(), image.bytesPerLine(),
                                    rmask, gmask, bmask, amask);
}

GLuint OffscreenEngineDelegate::loadTexturewithSDL(const QImage &sourceImage, GLenum texture_format)
{
    GLuint texture;         // This is a handle to our texture object
    SDL_Surface *surface;   // This surface will tell us the details of the image
    GLint  nOfColors;


    if ( (surface = QImage_toSDLSurface(sourceImage)) ) {

        // Check that the image's width is a power of 2
        if ( (surface->w & (surface->w - 1)) != 0 ) {
            printf("warning: image's width is not a power of 2\n");
        }

        // Also check if the height is a power of 2
        if ( (surface->h & (surface->h - 1)) != 0 ) {
            printf("warning: image's height is not a power of 2\n");
        }

        // get the number of channels in the SDL surface
        nOfColors = surface->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGBA;
            else
                texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
            if (surface->format->Rmask == 0x000000ff)
                texture_format = GL_RGB;
            else
                texture_format = GL_BGR;
        } else {
            printf("warning: the image is not truecolor..  this will probably break\n");
            // this error should not go unhandled
        }

        // Have OpenGL generate a texture object handle for us
        glGenTextures( 1, &texture );

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, texture );

        // Set the texture's stretching properties
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
    }
    else {
        printf("SDL could not load image %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

// Free the SDL_Surface only if it was successfully created
    if ( surface ) {
        SDL_FreeSurface( surface );
    }
    printf("Return texture");
    return texture;
}