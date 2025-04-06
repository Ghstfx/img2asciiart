#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Missing image file path\n");
        exit(EXIT_SUCCESS);
    }
    int width, height, channels;
    unsigned char *img = stbi_load(argv[1], &width, &height, &channels, 0);
    if(img == NULL) {
        printf("Image loading did not work :/\n");
        exit(EXIT_FAILURE);
    }
    stbi_image_free(img);
    exit(EXIT_SUCCESS);
}