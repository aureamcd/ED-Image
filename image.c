#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

Lista *criaLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return lista;
}

void adicionar_no_lista(Lista *lista, char *filename)
{
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
    if (!novo)
    {
        printf("Erro ao alocar memoria para o elemento\n");
        exit(1);
    }
    strncpy(novo->filename, filename, sizeof(novo->filename) - 1);
    novo->filename[sizeof(novo->filename) - 1] = '\0';
    novo->prox = NULL;
    novo->ant = lista->fim;

    if (lista->tam == 0)
    {
        lista->inicio = novo;
    }
    else
    {
        lista->fim->prox = novo;
    }
    lista->fim = novo;
    lista->tam++;
}

void liberar_lista(Lista *lista)
{
    Elemento *atual = lista->inicio;
    while (atual)
    {
        Elemento *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

void percorrer_lista(Lista *lista)
{
    Elemento *atual = lista->inicio;
    while (atual != NULL)
    {
        printf("%s\n", atual->filename);
        atual = atual->prox;
    }
}

ImageGray *read_image_gray(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1)
    {
        printf("Erro ao ler as dimensoes da imagem\n");
        fclose(file);
        exit(1);
    }

    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image)
    {
        printf("Erro ao alocar memoria para a imagem\n");
        fclose(file);
        exit(1);
    }

    image->dim = dim;
    image->pixels = (PixelGray *)malloc(dim.largura * dim.altura * sizeof(PixelGray));
    if (!image->pixels)
    {
        printf("Erro ao alocar memoria para os pixels\n");
        free(image);
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < dim.largura * dim.altura; i++)
    {
        int pixel_value;
        if (fscanf(file, "%d,", &pixel_value) != 1)
        {
            printf("Erro ao ler o valor do pixel no indice %d\n", i);
            free(image->pixels);
            free(image);
            fclose(file);
            exit(1);
        }
        image->pixels[i].value = pixel_value;
    }

    fclose(file);
    return image;
}

ImageRGB *read_image_rgb(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1)
    {
        printf("Erro ao ler as dimensoes da imagem\n");
        fclose(file);
        exit(1);
    }

    ImageRGB *image = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (!image)
    {
        printf("Erro ao alocar memoria para a imagem\n");
        fclose(file);
        exit(1);
    }

    image->dim = dim;
    image->pixels = (PixelRGB *)malloc(dim.largura * dim.altura * sizeof(PixelRGB));
    if (!image->pixels)
    {
        printf("Erro ao alocar memoria para os pixels\n");
        free(image);
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < dim.largura * dim.altura; i++)
    {
        int red, green, blue;
        if (fscanf(file, "%d %d %d,", &red, &green, &blue) != 3)
        {
            printf("Erro ao ler os valores dos canais de cor RGB no indice %d\n", i);
            free(image->pixels);
            free(image);
            fclose(file);
            exit(1);
        }
        image->pixels[i].red = red;
        image->pixels[i].green = green;
        image->pixels[i].blue = blue;
    }

    fclose(file);
    return image;
}

ImageGray *create_image_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    // Aqui, vai ser chamado toda vez que a imagem for manipulada. Essa função sera chamada ao final,
    // para criar o novo arquivo com os valores novos, e ele tem que estar dentro de uma lista duplamente encadeada

    // chamar a struct (que estara com os novos valores), e preencher o arquivo
    // o arquivo sera criado toda vez que ele for criado, e o nome sera *alteração+num da alteração
    // adicionar ao encadeamento, no final

    char filename[50];
    snprintf(filename, sizeof(filename), "%s%d", filename_gray, lista->tam + 1);

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Erro ao criar o arquivo %s\n", filename);
        exit(1);
    }

    fprintf(file, "%d\n%d\n", image->dim.altura, image->dim.largura);
    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            fprintf(file, "%d,", image->pixels[i * image->dim.largura + j].value);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    adicionar_no_lista(lista, filename);

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

ImageRGB *create_image_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    // Aqui, vai ser chamado toda vez que a imagem for manipulada. Essa função sera chamada ao final,
    // para criar o novo arquivo com os valores novos, e ele tem que estar dentro de uma lista duplamente encadeada

    // chamar a struct (que estara com os novos valores), e preencher o arquivo
    // o arquivo sera criado toda vez que ele for criado, e o nome sera *alteração+num da alteração
    // adicionar ao encadeamento, no final

    char filename[50];
    snprintf(filename, sizeof(filename), "%s%d", filename_rgb, lista->tam + 1);

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Erro ao criar o arquivo %s\n", filename);
        exit(1);
    }

    fprintf(file, "%d\n%d\n", image->dim.altura, image->dim.largura);
    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            fprintf(file, "%d %d %d,", image->pixels[i * image->dim.largura + j].red,
                    image->pixels[i * image->dim.largura + j].green,
                    image->pixels[i * image->dim.largura + j].blue);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    adicionar_no_lista(lista, filename);

    return image;
}

void free_image_rgb(ImageRGB *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

ImageGray *flip_vertical_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    // Aplicar o flip vertical na própria imagem
    for (int i = 0; i < image->dim.altura / 2; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            // Trocar os pixels entre as linhas i e altura-i-1
            int temp = image->pixels[i * image->dim.largura + j].value;
            image->pixels[i * image->dim.largura + j].value = image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j].value;
            image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j].value = temp;
        }
    }

    // Atualizar a imagem na lista
    create_image_gray(image, lista, filename_gray);
    return image;
}

ImageGray *flip_horizontal_gray(ImageGray *image, Lista *lista, char *filename_gray)
{

    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura / 2; j++)
        {
            // Calcular os índices dos pixels a serem trocados
            int idx1 = i * image->dim.largura + j;
            int idx2 = i * image->dim.largura + (image->dim.largura - j - 1);

            // Trocar os pixels entre as colunas j e largura-j-1
            int temp = image->pixels[idx1].value;
            image->pixels[idx1].value = image->pixels[idx2].value;
            image->pixels[idx2].value = temp;
        }
    }

    // Atualizar a imagem na lista
    create_image_gray(image, lista, filename_gray);
    return image;
}

ImageGray *transpose_Gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    // Aplicar o transpose na própria imagem

    PixelGray *transpose_pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelGray));

    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            transpose_pixels[j * image->dim.altura + i] = image->pixels[i * image->dim.largura + j];
        }
    }

    image->dim.altura = image->dim.altura ^ image->dim.largura;
    image->dim.largura = image->dim.altura ^ image->dim.largura;
    image->dim.altura = image->dim.altura ^ image->dim.largura;

    image->pixels = transpose_pixels;

    // Atualizar a imagem na lista
    create_image_gray(image, lista, filename_gray);
    return image;
}

ImageRGB *flip_vertical_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    // Aplicar o flip vertical na própria imagem
    for (int i = 0; i < image->dim.altura / 2; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            // Trocar os pixels entre as linhas i e altura-i-1
            PixelRGB temp = image->pixels[i * image->dim.largura + j];
            image->pixels[i * image->dim.largura + j] = image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j];
            image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j] = temp;
        }
    }

    // Atualizar a imagem na lista
    create_image_rgb(image, lista, filename_rgb);

    return image;
}

ImageRGB *flip_horizontal_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{

    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura / 2; j++)
        {
            // Calcular os índices dos pixels a serem trocados
            int idx1 = i * image->dim.largura + j;
            int idx2 = i * image->dim.largura + (image->dim.largura - j - 1);

            // Trocar os pixels entre as colunas j e largura-j-1
            PixelRGB temp = image->pixels[idx1];
            image->pixels[idx1] = image->pixels[idx2];
            image->pixels[idx2] = temp;
        }
    }

    // Atualizar a imagem na lista
    create_image_rgb(image, lista, filename_rgb);
    return image;
}

ImageRGB *transpose_RGB(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    // Aplicar o transpose na própria imagem

    PixelRGB *transpose_pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelRGB));

    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            transpose_pixels[j * image->dim.altura + i] = image->pixels[i * image->dim.largura + j];
        }
    }

    image->dim.altura = image->dim.altura ^ image->dim.largura;
    image->dim.largura = image->dim.altura ^ image->dim.largura;
    image->dim.altura = image->dim.altura ^ image->dim.largura;

    image->pixels = transpose_pixels;

    // Atualizar a imagem na lista
    create_image_rgb(image, lista, filename_rgb);
    return image;
}