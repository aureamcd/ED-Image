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

void adicionar_no_lista(Lista *lista, const char *filename)
{
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
    if (!novo)
    {
        fprintf(stderr, "Erro ao alocar memoria para o elemento\n");
        return;
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

void percorrer_lista(Lista *lista){
    Elemento *atual = lista->inicio;
    while (atual != NULL)
    {
        printf("%s\n", atual->filename);
        atual = atual->prox;
    }
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

void create_image_gray(ImageGray *img, Lista *lista)
{
    // Aqui, vai ser chamado toda vez que a imagem for manipulada. Essa função sera chamada ao final,
    // para criar o novo arquivo com os valores novos, e ele tem que estar dentro de uma lista duplamente encadeada

    // chamar a struct (que estara com os novos valores), e preencher o arquivo
    // o arquivo sera criado toda vez que ele for criado, e o nome sera *alteração+num da alteração
    // adicionar ao encadeamento, no final
    

    char filename[50];
    snprintf(filename, sizeof(filename), "alteracao_gray%d.txt", lista->tam + 1);

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
    adicionar_no_lista(lista, filename);
}

void free_image_gray(ImageGray *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

void create_image_rgb(ImageRGB *img, Lista *lista)
{
    // Aqui, vai ser chamado toda vez que a imagem for manipulada. Essa função sera chamada ao final,
    // para criar o novo arquivo com os valores novos, e ele tem que estar dentro de uma lista duplamente encadeada

    // chamar a struct (que estara com os novos valores), e preencher o arquivo
    // o arquivo sera criado toda vez que ele for criado, e o nome sera *alteração+num da alteração
    // adicionar ao encadeamento, no final

    

    char filename[50];
    snprintf(filename, sizeof(filename), "alteracao_rgb%d.txt", lista->tam + 1);

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
            fprintf(file, "%d %d %d,", img->pixels[i * img->dim.largura + j].red,
                                      img->pixels[i * img->dim.largura + j].green,
                                      img->pixels[i * img->dim.largura + j].blue);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    adicionar_no_lista(lista, filename);
}

void free_image_rgb(ImageRGB *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

int write_image_gray(const char *filename, ImageGray *image){
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", filename);
        return 0;
    }

    // Escrever as dimensões da imagem
    fprintf(file, "%d\n%d\n", image->dim.altura, image->dim.largura);

    // Escrever os valores dos pixels
    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            fprintf(file, "%d,", image->pixels[i * image->dim.largura + j].value);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 1; // Sucesso
}

void flip_vertical_gray(Lista *lista)
{
    // Verificar se há pelo menos uma imagem na lista
    if (lista->tam == 0)
    {
        fprintf(stderr, "Nenhuma imagem em escala de cinza carregada para aplicar flip vertical.\n");
        return;
    }

    // Acessar a última imagem em escala de cinza na lista
    Elemento *ultimo_elemento = lista->fim;
    ImageGray *original_img = read_image_gray(ultimo_elemento->filename);
    if (!original_img)
    {
        fprintf(stderr, "Erro ao carregar a última imagem em escala de cinza na lista.\n");
        return;
    }

    // Criar uma nova imagem modificada para armazenar o flip vertical
    ImageGray *modified_img = (ImageGray *)malloc(sizeof(ImageGray));
    if (!modified_img)
    {
        fprintf(stderr, "Erro ao alocar memória para a imagem modificada\n");
        free_image_gray(original_img); // Liberar a imagem original
        return;
    }

    // Copiar as dimensões da imagem original
    modified_img->dim = original_img->dim;

    // Alocar memória para os pixels da imagem modificada
    modified_img->pixels = (PixelGray *)malloc(original_img->dim.largura * original_img->dim.altura * sizeof(PixelGray));
    if (!modified_img->pixels)
    {
        fprintf(stderr, "Erro ao alocar memória para os pixels da imagem modificada\n");
        free_image_gray(original_img); // Liberar a imagem original
        free(modified_img);
        return;
    }

    // Inverter as dimensões da imagem modificada
    modified_img->dim.altura = original_img->dim.altura;
    modified_img->dim.largura = original_img->dim.largura;

    // Copiar os valores dos pixels da imagem original e aplicar o flip vertical
    for (int i = 0; i < original_img->dim.altura; i++)
    {
        for (int j = 0; j < original_img->dim.largura; j++)
        {
            // Atribuir o valor do pixel correspondente da imagem original ao pixel correspondente na imagem modificada,
            // mas invertendo a ordem das linhas para realizar o flip vertical
            modified_img->pixels[i * original_img->dim.largura + j].value = original_img->pixels[(original_img->dim.altura - 1 - i) * original_img->dim.largura + j].value;
        }
    }

    // Criar um novo nome de arquivo para a imagem modificada
    char filename[50];
    snprintf(filename, sizeof(filename), "alteracao_gray%d.txt", lista->tam + 1);

    // Escrever a imagem modificada em um arquivo
    if (write_image_gray(filename, modified_img))
    {
        // Adicionar o nome do arquivo à lista encadeada
        adicionar_no_lista(lista, filename);
        printf("Flip vertical aplicado à última imagem em escala de cinza carregada e salvo em %s.\n", filename);
    }
    else
    {
        fprintf(stderr, "Erro ao salvar a imagem modificada.\n");
    }

    // Liberar a memória alocada
    free_image_gray(original_img);
    free_image_gray(modified_img);
}

void *flip_vertical_rgb(const ImageRGB *image, Lista *lista)
{
    ImageRGB *imgflip = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (!imgflip)
    {
        fprintf(stderr, "Erro ao alocar memoria para a imagem modificada\n");
        return NULL;
    }

    imgflip->dim = image->dim;

    imgflip->pixels = (PixelRGB *)malloc(image->dim.largura * image->dim.altura * sizeof(PixelRGB));
    if (!imgflip->pixels)
    {
        fprintf(stderr, "Erro ao alocar memoria para os pixels da imagem modificada\n");
        free(imgflip);
        return NULL; // Adicionei o retorno de NULL em caso de erro.
    }

    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            // Atribuir o valor do pixel correspondente da imagem original ao pixel correspondente na imagem modificada,
            // mas invertendo a ordem das linhas para realizar o flip vertical
            imgflip->pixels[i * image->dim.largura + j].red = image->pixels[(image->dim.altura - 1 - i) * image->dim.largura + j].red;
            imgflip->pixels[i * image->dim.largura + j].green = image->pixels[(image->dim.altura - 1 - i) * image->dim.largura + j].green;
            imgflip->pixels[i * image->dim.largura + j].blue = image->pixels[(image->dim.altura - 1 - i) * image->dim.largura + j].blue;
        }
    }

    create_image_rgb(imgflip, lista);
    return imgflip;
}