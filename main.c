#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {
    
    ImageRGB *image_rgb = create_image_rgb();
    if (!image_rgb) {
        fprintf(stderr, "Erro ao criar a imagem RGB\n");
        return 1;
    }

    printf("Dimensões da imagem RGB: %d x %d\n", image_rgb->dim.largura, image_rgb->dim.altura);
    printf("Valor do primeiro pixel: Red %d, Green %d, Blue %d.\n", image_rgb->pixels[0].red, image_rgb->pixels[0].green, image_rgb->pixels[0].blue);

    free_image_rgb(image_rgb);

    return 0;
}
