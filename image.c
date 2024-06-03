#include <stdio.h>
#include <stdlib.h>
#include "image.h"

ImageGray *create_image_gray()
{
    FILE *file = fopen("input_image_Gray.txt", "r");

    if (!file)
    {
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return NULL;
    }

   fscanf(file, "%d", &imageGray->dim.altura);
   fscanf(file, "%d", &imageGray->dim.largura);
    

    int **matriz = (int *)malloc(altura * sizeof())

        // Ler as dimensões da imagem
        Dimensoes dim;
    if (fscanf(file, "%d %d", &dim.altura, &dim.largura) != 2)
    {
        fprintf(stderr, "Erro ao ler as dimensões da imagem\n");
        fclose(file);
        return NULL;
    }

    // Alocar memória para a estrutura da imagem
    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image)
    {
        fprintf(stderr, "Erro ao alocar memória para a estrutura da imagem\n");
        fclose(file);
        return NULL;
    }
    image->dim = dim;

    // Alocar memória para os pixels
    image->pixels = (PixelGray *)malloc(dim.largura * dim.altura * sizeof(PixelGray));
    if (!image->pixels)
    {
        fprintf(stderr, "Erro ao alocar memória para os pixels\n");
        free(image);
        fclose(file);
        return NULL;
    }

    // Ler os valores dos pixels
    for (int i = 0; i < dim.largura * dim.altura; i++)
    {
        if (fscanf(file, "%d", &image->pixels[i].value) != 1)
        {
            fprintf(stderr, "Erro ao ler o valor do pixel %d\n", i);
            free(image->pixels);
            free(image);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return image;
}
