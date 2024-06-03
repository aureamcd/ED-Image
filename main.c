#include <stdio.h>
#include "image.h"

int main() {
    // Criar a imagem em tons de cinza
    ImageGray *gray_image = create_image_gray();
    if (!gray_image) {
        fprintf(stderr, "Erro ao criar a imagem em tons de cinza\n");
        return 1;
    }

    // Exibir as dimensões da imagem
    printf("Dimensões da imagem em tons de cinza:\n");
    printf("Altura: %d\n", gray_image->dim.altura);
    printf("Largura: %d\n", gray_image->dim.largura);

    // Exibir os valores dos primeiros pixels
    printf("\nValores dos primeiros pixels:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", gray_image->pixels[i].value);
    }
    printf("\n");

    // Liberar a memória alocada para a imagem
    free_image_gray(gray_image);

    return 0;
}
