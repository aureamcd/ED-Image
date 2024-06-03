#include <stdio.h>
#include "image.h"

int main() {
    ImageGray *imagecinza = create_image_gray();
    if (!imagecinza) {
        fprintf(stderr, "Erro ao criar a imagem\n");
        return 1;
    }

    printf("Dimensões da imagem: %d x %d\n", imagecinza->dim.largura, imagecinza->dim.altura);
    printf("Valor do primeiro pixel: %d\n", imagecinza->pixels[0].value);

    free_image_gray(imagecinza);

    ImageRGB *imagergb = create_image_rgb();
    if (!imagergb) {
        fprintf(stderr, "Erro ao criar a imagem\n");
        return 1;
    }

    printf("Dimensões da imagem: %d x %d\n", imagergb->dim.largura, imagergb->dim.altura);
    printf("Valor do primeiro pixel: %d\n", imagergb->pixels[0].red,imagergb->pixels[0].green,imagergb->pixels[0].blue);

    free_image_gray(imagergb);

    return 0;
}

