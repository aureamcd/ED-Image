#include <stdio.h>
#include <stdlib.h>
#include "image.h"




ImageGray *read_image_gray() {
    const char *filename = "input_image_example_Gray.txt";
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1) {
        fprintf(stderr, "Erro ao ler as dimensões da imagem\n");
        fclose(file);
        return NULL;
    }

    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image) {
        fprintf(stderr, "Erro ao alocar memória para a imagem\n");
        fclose(file);
        return NULL;
    }

    image->dim = dim;
    image->pixels = (PixelGray *)malloc(dim.largura * dim.altura * sizeof(PixelGray));
    if (!image->pixels) {
        fprintf(stderr, "Erro ao alocar memória para os pixels\n");
        free(image);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < dim.largura * dim.altura; i++) {
        int pixel_value;
        if (fscanf(file, "%d,", &pixel_value) != 1) {
            fprintf(stderr, "Erro ao ler o valor do pixel no índice %d\n", i);
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

ImageRGB *read_image_rgb() {
    const char *filename = "input_image_example_RGB.txt";
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1) {
        fprintf(stderr, "Erro ao ler as dimensões da imagem\n");
        fclose(file);
        return NULL;
    }

    ImageRGB *image = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (!image) {
        fprintf(stderr, "Erro ao alocar memória para a imagem\n");
        fclose(file);
        return NULL;
    }

    image->dim = dim;
    image->pixels = (PixelRGB *)malloc(dim.largura * dim.altura * sizeof(PixelRGB));
    if (!image->pixels) {
        fprintf(stderr, "Erro ao alocar memória para os pixels\n");
        free(image);
        fclose(file);
        return NULL;
    }

    // Agora, leia os valores RGB para cada pixel da imagem
    for (int i = 0; i < dim.largura * dim.altura; i++) {
        int red, green, blue;
        if (fscanf(file, "%d %d %d,", &red, &green, &blue) != 3) {
            fprintf(stderr, "Erro ao ler os valores dos canais de cor RGB no índice %d\n", i);
            free(image->pixels);
            free(image);
            fclose(file);
            return NULL;
        }
        image->pixels[i].red = red;
        image->pixels[i].green = green;
        image->pixels[i].blue = blue;
    }

    fclose(file);
    return image;
}

void free_image_gray(ImageGray *image) {
    if (image) {
        printf("Liberando memória da imagem em escala de cinza...\n");
        free(image->pixels);
        free(image);
        printf("Memória liberada com sucesso!\n");
    }
}

void free_image_rgb(ImageRGB *image) {
    if (image) {
        printf("Liberando memória da imagem RGB...\n");
        free(image->pixels);
        free(image);
        printf("Memória liberada com sucesso!\n");
    }
}


