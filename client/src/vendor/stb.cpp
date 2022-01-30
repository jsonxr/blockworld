#ifndef BLOCK_WORLD_STB_H
#define BLOCK_WORLD_STB_H

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_JPEG
//#define STBI_NO_PNG
#define STBI_NO_BMP
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define STBI_WRITE_NO_STDIO // stdio version of functions
#include <stb_image_write.h>
#undef STB_IMAGE_WRITE_IMPLEMENTATION

#endif  // BLOCK_WORLD_STB_H
