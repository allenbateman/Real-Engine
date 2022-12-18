#include "PickingTexture.h"
#include "Renderer.h"

PickingTexture::PickingTexture()
{
}

PickingTexture::~PickingTexture()
{
}

void PickingTexture::Init(int widowWidth, int windowHeight)
{
//    //Create the FBO
//    glBindFramebuffer(GL_FRAMEBUFFER, app->renderer->editorBuffer.FBO);
//
//
//    //Create the texture object for the primitive information buffer
//    glGenTextures(1, &m_pickingTexture);
//    glBindTexture(GL_TEXTURE_2D, m_pickingTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, widowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pickingTexture, 0);
//
//    //Create the texture object for the depth buffer
//    glGenTextures(1, &m_depthTexture);
//    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, widowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
//
//    //Verify that the FBO is correct
//    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//
//    if (Status != GL_FRAMEBUFFER_COMPLETE)
//    {
//        std::cout << "FB error, status: " << Status << std::endl;
//        
//    }
//
//    //Restore default framebuffer
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PickingTexture::EnableWriting()
{
   // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, app->renderer->editorBuffer.FBO);
}

void PickingTexture::DisableWriting()
{
    //Bind back the default framebuffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

}

PixelInfo PickingTexture::ReadPixel(int x, int y)
{
    PixelInfo Pixel;
  /*  glBindFramebuffer(GL_READ_FRAMEBUFFER, app->renderer->editorBuffer.FBO);

    glReadBuffer(GL_COLOR_ATTACHMENT0);

    
    glReadPixels(x, y, 1, 1, GL_RGB_INTEGER, GL_INT, &Pixel);

    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    std::cout << "DrawId: " << Pixel.DrawId << " ObjectId: " << Pixel.ObjectId <<" PrimId: "<< Pixel.PrimId <<" X: "<<x<<" Y: "<<y << std::endl;
    */
    return Pixel;
}
