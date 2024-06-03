#include <stdio.h>
#include "image.h"

int main() {
    ImageGray *image = create_image_gray();
    if (!image) {
        fprintf(stderr, "Erro ao criar a imagem\n");
        return 1;
    }

    printf("Dimensões da imagem: %d x %d\n", image->dim.largura, image->dim.altura);
    printf("Valor do primeiro pixel: %d\n", image->pixels[0].value);

    free_image_gray(image);

    return 0;
}

