#include "Library/loadpng.h"
#include "Library/process_image.h"
#include "Library/gl_texture.h"


unsigned int load_and_bind_texture(const char* filename)
{
    Image img;
    img.img = NULL; 
    img.w = 0;
    img.h = 0;
    Load_Texture_Swap(&img, filename);

    unsigned int tex_handle = 0;
    glGenTextures(1, &tex_handle); 

    glBindTexture(GL_TEXTURE_2D, tex_handle);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.img);

    glBindTexture(GL_TEXTURE_2D, 0);

    free(img.img);

    return tex_handle;
}
