#include <stdio.h>
#include <stdlib.h>
#include "image.h"

ImageGray *create_image_gray() {
    printf("oi");
    const char *filename = "C:\\Users\\luisl\\OneDrive\\Documentos\\GitHub\\ED-Image\\utils\\input_image_example_Gray.txt";
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    // Ler as dimensões da imagem
    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1) {
        fprintf(stderr, "Erro ao ler as dimensões da imagem\n");
        fclose(file);
        return NULL;
    }

    // Alocar memória para a estrutura da imagem
    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image) {
        fprintf(stderr, "Erro ao alocar memória para a imagem\n");
        fclose(file);
        return NULL;
    }
    image->dim = dim;

    // Alocar memória para os pixels
    image->pixels = (PixelGray *)malloc(dim.largura * dim.altura * sizeof(PixelGray));
    if (!image->pixels) {
        fprintf(stderr, "Erro ao alocar memória para os pixels\n");
        free(image);
        fclose(file);
        return NULL;
    }

    // Ler os valores dos pixels
    for (int i = 0; i < dim.largura * dim.altura; i++) {
        int pixel_value;
    if (fscanf(file, "%d", &pixel_value) != 1) {
        fprintf(stderr, "Erro ao ler o valor do pixel\n");
        free(image->pixels);
        free(image);
        fclose(file);
    return NULL;
    }
    image->pixels[i].value = pixel_value;
    }
    fclose(file);
    return image;
}

