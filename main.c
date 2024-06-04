#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {    

    ImageGray *image_gray = read_image_gray();
    if (!image_gray) {
        fprintf(stderr, "Erro ao criar a imagem em escala de cinza\n");
        return 1;
    }

    printf("Dimensões da imagem em escala de cinza: %d x %d\n", image_gray->dim.largura, image_gray->dim.altura);
    printf("Valor do primeiro pixel em escala de cinza: %d\n", image_gray->pixels[0].value);

    // Liberar imagem em escala de cinza
    free_image_gray(image_gray);

    ImageRGB *image_rgb = read_image_rgb();
    if (!image_rgb) {
        fprintf(stderr, "Erro ao criar a imagem RGB\n");
        return 1;
    }

    printf("Dimensões da imagem RGB: %d x %d\n", image_rgb->dim.largura, image_rgb->dim.altura);
    printf("Valor do primeiro pixel: Red %d, Green %d, Blue %d.\n", image_rgb->pixels[0].red, image_rgb->pixels[0].green, image_rgb->pixels[0].blue);

    free_image_rgb(image_rgb);

    return 0;
}
