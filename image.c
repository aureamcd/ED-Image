#include <stdio.h>
#include <stdlib.h>
#include "image.h"

Lista *criaLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return lista;
}

void adicionar_no_lista(Lista *lista, ImageGray *image)
{
    Elemento *novo_no = (Elemento *)malloc(sizeof(Elemento));
    novo_no->image = image;
    novo_no->prox = NULL;
    novo_no->ant = lista->fim;

    if (lista->fim)
    {
        lista->fim->prox = novo_no;
    }
    else
    {
        lista->inicio = novo_no;
    }

    lista->fim = novo_no;
    lista->tam++;
}

void liberar_lista(Lista *lista)
{
    Elemento *atual = lista->inicio;
    while (atual)
    {
        Elemento *proximo = atual->prox;
        free_image_gray(atual->image);
        free(atual);
        atual = proximo;
    }
    free(lista);
}

void create_image_gray(ImageGray *img, Lista *lista)
{
    // Aqui, vai ser chamado toda vez que a imagem for manipulada. Essa função sera chamada ao final,
    // para criar o novo arquivo com os valores novos, e ele tem que estar dentro de uma lista duplamente encadeada

    // chamar a struct (que estara com os novos valores), e preencher o arquivo
    // o arquivo sera criado toda vez que ele for criado, e o nome sera *alteração+num da alteração
    // adicionar ao encadeamento, no final
    char filename[50];
    snprintf(filename, sizeof(filename), "alteracao%d.txt", lista->tam + 1);

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "Erro ao criar o arquivo %s\n", filename);
        return;
    }

    fprintf(file, "%d\n%d\n", img->dim.altura, img->dim.largura);
    for (int i = 0; i < img->dim.altura; i++)
    {
        for (int j = 0; j < img->dim.largura; j++)
        {
            fprintf(file, "%d,", img->pixels[i * img->dim.largura + j].value);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    // Adiciona a imagem à lista
    ImageGray *nova_imagem = (ImageGray *)malloc(sizeof(ImageGray));
    *nova_imagem = *img;
    nova_imagem->pixels = (PixelGray *)malloc(img->dim.altura * img->dim.largura * sizeof(PixelGray));
    for (int i = 0; i < img->dim.altura * img->dim.largura; i++)
    {
        nova_imagem->pixels[i] = img->pixels[i];
    }

    adicionar_no_lista(lista, nova_imagem);
}

ImageGray *read_image_gray(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1)
    {
        fprintf(stderr, "Erro ao ler as dimensoes da imagem\n");
        fclose(file);
        return NULL;
    }

    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image)
    {
        fprintf(stderr, "Erro ao alocar memoria para a imagem\n");
        fclose(file);
        return NULL;
    }

    image->dim = dim;
    image->pixels = (PixelGray *)malloc(dim.largura * dim.altura * sizeof(PixelGray));
    if (!image->pixels)
    {
        fprintf(stderr, "Erro ao alocar memoria para os pixels\n");
        free(image);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < dim.largura * dim.altura; i++)
    {
        int pixel_value;
        if (fscanf(file, "%d,", &pixel_value) != 1)
        {
            fprintf(stderr, "Erro ao ler o valor do pixel no indice %d\n", i);
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

ImageRGB *read_image_rgb(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1)
    {
        fprintf(stderr, "Erro ao ler as dimensoes da imagem\n");
        fclose(file);
        return NULL;
    }

    ImageRGB *image = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (!image)
    {
        fprintf(stderr, "Erro ao alocar memoria para a imagem\n");
        fclose(file);
        return NULL;
    }

    image->dim = dim;
    image->pixels = (PixelRGB *)malloc(dim.largura * dim.altura * sizeof(PixelRGB));
    if (!image->pixels)
    {
        fprintf(stderr, "Erro ao alocar memoria para os pixels\n");
        free(image);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < dim.largura * dim.altura; i++)
    {
        int red, green, blue;
        if (fscanf(file, "%d %d %d,", &red, &green, &blue) != 3)
        {
            fprintf(stderr, "Erro ao ler os valores dos canais de cor RGB no indice %d\n", i);
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

void free_image_gray(ImageGray *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

void free_image_rgb(ImageRGB *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}
