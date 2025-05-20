#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

uint8_t luminosity(char red, char green, char blue) {
    return 0.3 * (uint8_t)red + 0.59 * (uint8_t)green + 0.11 * (uint8_t)blue;
}

void grayscale2ascii(unsigned char* gray_img, int width, int height, int gray_channels) {
    char s[width+1];
    s[width] = '\n';
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            uint8_t gray_val = (uint8_t)*(gray_img+gray_channels*((i*width)+j));
            if(gray_val < 25) {
                s[j] = '@';
            } else if(gray_val < 50) {
                s[j] = '%';
            } else if(gray_val < 75) {
                s[j] = '#';
            } else if(gray_val < 100) {
                s[j] = '*';
            } else if(gray_val < 125) {
                s[j] = '+';
            } else if(gray_val < 150) {
                s[j] = '=';
            } else if(gray_val < 175) {
                s[j] = '-';
            } else if(gray_val < 200) {
                s[j] = ':';
            } else if(gray_val < 225) {
                s[j] = '.';
            } else {
                s[j] = ' ';
            }
        }
        printf("%s", s);
    }
    return;
}

void grayscale(unsigned char* img, int width, int height, int channels, const char* output_name) {    
    size_t image_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;
    unsigned char* gray_img = malloc(gray_img_size);
    if(gray_img == NULL) {
        printf("Memory allocation failed :/\n");
        exit(EXIT_FAILURE);
    }
    for(unsigned char* ptr = img, *gray_ptr = gray_img; ptr != img + image_size; ptr += channels, gray_ptr += gray_channels) {
        *gray_ptr = luminosity(*ptr, *(ptr+1), *(ptr+2));
        if(channels == 4) {
            *(gray_ptr + 1) = *(ptr+3);
        }
    }
    stbi_write_png(output_name, width, height, gray_channels, gray_img, width * gray_channels);
    grayscale2ascii(gray_img, width, height, gray_channels);
    free(gray_img);
    return;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Missing image file path\n");
        printf("Usage:\n-f <target> -o <output_name>\n");
        exit(EXIT_SUCCESS);
    }
    int width, height, channels;
    unsigned char* img = stbi_load(argv[1], &width, &height, &channels, 0);
    if(img == NULL) {
        printf("Image loading did not work :/\n");
        exit(EXIT_FAILURE);
    }
    grayscale(img, width, height, channels, "/home/ge92xul/privProjects/img2asciiart/images/kita_gray.png");
    stbi_image_free(img);
    exit(EXIT_SUCCESS);
}