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

void percorrer_lista(Lista *lista){
    Elemento *atual = lista->inicio;
    while (atual != NULL)
    {
        printf("%s\n", atual->filename);
        atual = atual->prox;
    }
}

void imprimir_historico(Lista *lista) {
    if (lista->tam == 0) {
        printf("Lista vazia.\n");
        return;
    }

    printf("\nHistorico de alteracoes:\n");
    Elemento *atual = lista->inicio;
    while (atual != NULL) {
        printf("%s - %s\n", atual->filename, atual->alt);
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
    if (fscanf(file, "%d", &dim.largura) != 1 || fscanf(file, "%d", &dim.altura) != 1)
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

void create_image_gray(ImageGray *image, Lista *lista, char *filename_gray)
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

    fprintf(file, "%d\n%d\n", image->dim.largura, image->dim.altura);
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
}

void free_image_gray(ImageGray *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

void create_image_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
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
}

void free_image_rgb(ImageRGB *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

void flip_vertical_gray(ImageGray *image, Lista *lista, char *filename_gray)
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
}

void flip_horizontal_gray(ImageGray *image, Lista *lista, char *filename_gray)
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
}

void transpose_Gray(ImageGray *image, Lista *lista, char *filename_gray)
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
}

void flip_vertical_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
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
}

void flip_horizontal_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
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
}

void transpose_RGB(ImageRGB *image, Lista *lista, char *filename_rgb)
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
}

void clahe_gray(ImageGray *image, Lista *lista, char *filename_gray) {
    float clip_limit= 3.0;
    int NUM_BINS = 256;

    int altura_bloco=image->dim.altura;
    int largura_bloco=image->dim.largura;

    int num_blocos_x = (image->dim.largura + largura_bloco - 1) / largura_bloco;
    int num_blocos_y = (image->dim.altura + altura_bloco - 1) / altura_bloco;

    int ***histogramas = (int ***)malloc(num_blocos_y * sizeof(int **));
    if (!histogramas) {
        printf("Erro ao alocar memória para os histogramas\n");
        exit(1);
    }

    for (int i = 0; i < num_blocos_y; i++) {
        histogramas[i] = (int **)malloc(num_blocos_x * sizeof(int *));
        if (!histogramas[i]) {
            printf("Erro ao alocar memória para os histogramas\n");
            exit(1);
        }
        for (int j = 0; j < num_blocos_x; j++) {
            histogramas[i][j] = (int *)calloc(NUM_BINS, sizeof(int));
            if (!histogramas[i][j]) {
                printf("Erro ao alocar memória para os histogramas\n");
                exit(1);
            }
        }
    }

    for (int i = 0; i < num_blocos_y; i++) {
        for (int j = 0; j < num_blocos_x; j++) {
            memset(histogramas[i][j], 0, NUM_BINS * sizeof(int));

            int x_inicio = j * largura_bloco;
            int x_fim = (j + 1) * largura_bloco;
            int y_inicio = i * altura_bloco;
            int y_fim = (i + 1) * altura_bloco;

            if (x_fim > image->dim.largura)
                x_fim = image->dim.largura;
            if (y_fim > image->dim.altura)
                y_fim = image->dim.altura;

            for (int y = y_inicio; y < y_fim; y++) {
                for (int x = x_inicio; x < x_fim; x++) {
                    int valor_pixel = image->pixels[y * image->dim.largura + x].value;
                    histogramas[i][j][valor_pixel]++;
                }
            }

            int limite = (int)(clip_limit * (x_fim - x_inicio) * (y_fim - y_inicio) / NUM_BINS);
            int excesso = 0;

            for (int k = 0; k < NUM_BINS; k++) {
                if (histogramas[i][j][k] > limite) {
                    excesso += histogramas[i][j][k] - limite;
                    histogramas[i][j][k] = limite;
                }
            }

            int incremento = excesso / NUM_BINS;
            for (int k = 0; k < NUM_BINS; k++) {
                histogramas[i][j][k] += incremento;
            }

            for (int k = 1; k < NUM_BINS; k++) {
                histogramas[i][j][k] += histogramas[i][j][k - 1];
            }
        }
    }

    for (int y = 0; y < image->dim.altura; y++) {
        for (int x = 0; x < image->dim.largura; x++) {
            int bloco_x = x / largura_bloco;
            int bloco_y = y / altura_bloco;

            int valor_pixel = image->pixels[y * image->dim.largura + x].value;
            int total_pixels_bloco = largura_bloco * altura_bloco;

            if (bloco_x < num_blocos_x && bloco_y < num_blocos_y) {
                int valor_equalizado = (int)(((float)histogramas[bloco_y][bloco_x][valor_pixel] / total_pixels_bloco) * (NUM_BINS - 1));
                image->pixels[y * image->dim.largura + x].value = (valor_equalizado > 255) ? 255 : valor_equalizado;
            }
        }
    }

    for (int i = 0; i < num_blocos_y; i++) {
        for (int j = 0; j < num_blocos_x; j++) {
            free(histogramas[i][j]);
        }
        free(histogramas[i]);
    }
    free(histogramas);

    create_image_gray(image, lista, filename_gray);
}

void clahe_rgb(ImageRGB *image, Lista *lista, char *filename_rgb) {
    float clip_limit = 3.0;
    int NUM_BINS = 256;

    int largura_bloco = image->dim.altura;// Tamanho do bloco
    int altura_bloco = image->dim.largura; // Tamanho do bloco

    int num_blocos_x = (image->dim.largura + largura_bloco - 1) / largura_bloco;
    int num_blocos_y = (image->dim.altura + altura_bloco - 1) / altura_bloco;

    int ***histogramas = (int ***)malloc(num_blocos_y * sizeof(int **));
    if (!histogramas) {
        printf("Erro ao alocar memória para os histogramas\n");
        exit(1);
    }

    for (int i = 0; i < num_blocos_y; i++) {
        histogramas[i] = (int **)malloc(num_blocos_x * sizeof(int *));
        if (!histogramas[i]) {
            printf("Erro ao alocar memória para os histogramas\n");
            exit(1);
        }
        for (int j = 0; j < num_blocos_x; j++) {
            histogramas[i][j] = (int *)calloc(NUM_BINS, sizeof(int));
            if (!histogramas[i][j]) {
                printf("Erro ao alocar memória para os histogramas\n");
                exit(1);
            }
        }
    }

    for (int canal = 0; canal < 3; canal++) { // Loop por cada canal de cor (0: Red, 1: Green, 2: Blue)
        for (int i = 0; i < num_blocos_y; i++) {
            for (int j = 0; j < num_blocos_x; j++) {
                memset(histogramas[i][j], 0, NUM_BINS * sizeof(int));

                int x_inicio = j * largura_bloco;
                int x_fim = (j + 1) * largura_bloco;
                int y_inicio = i * altura_bloco;
                int y_fim = (i + 1) * altura_bloco;

                if (x_fim > image->dim.largura)
                    x_fim = image->dim.largura;
                if (y_fim > image->dim.altura)
                    y_fim = image->dim.altura;

                for (int y = y_inicio; y < y_fim; y++) {
                    for (int x = x_inicio; x < x_fim; x++) {
                        int valor_pixel;
                        if (canal == 0) {
                            valor_pixel = image->pixels[y * image->dim.largura + x].red;
                        } else if (canal == 1) {
                            valor_pixel = image->pixels[y * image->dim.largura + x].green;
                        } else {
                            valor_pixel = image->pixels[y * image->dim.largura + x].blue;
                        }
                        histogramas[i][j][valor_pixel]++;
                    }
                }

                int limite = (int)(clip_limit * (x_fim - x_inicio) * (y_fim - y_inicio) / NUM_BINS);
                int excesso = 0;

                for (int k = 0; k < NUM_BINS; k++) {
                    if (histogramas[i][j][k] > limite) {
                        excesso += histogramas[i][j][k] - limite;
                        histogramas[i][j][k] = limite;
                    }
                }

                int incremento = excesso / NUM_BINS;
                for (int k = 0; k < NUM_BINS; k++) {
                    histogramas[i][j][k] += incremento;
                }

                for (int k = 1; k < NUM_BINS; k++) {
                    histogramas[i][j][k] += histogramas[i][j][k - 1];
                }
            }
        }

        for (int y = 0; y < image->dim.altura; y++) {
            for (int x = 0; x < image->dim.largura; x++) {
                int bloco_x = x / largura_bloco;
                int bloco_y = y / altura_bloco;

                int valor_pixel;
                if (canal == 0) {
                    valor_pixel = image->pixels[y * image->dim.largura + x].red;
                } else if (canal == 1) {
                    valor_pixel = image->pixels[y * image->dim.largura + x].green;
                } else {
                    valor_pixel = image->pixels[y * image->dim.largura + x].blue;
                }

                if (bloco_x < num_blocos_x && bloco_y < num_blocos_y) {
                    int valor_equalizado = (int)(((float)histogramas[bloco_y][bloco_x][valor_pixel] / histogramas[bloco_y][bloco_x][NUM_BINS - 1]) * (NUM_BINS - 1));
                    valor_equalizado = (valor_equalizado > 255) ? 255 : valor_equalizado;

                    if (canal == 0) {
                        image->pixels[y * image->dim.largura + x].red = valor_equalizado;
                    } else if (canal == 1) {
                        image->pixels[y * image->dim.largura + x].green = valor_equalizado;
                    } else {
                        image->pixels[y * image->dim.largura + x].blue = valor_equalizado;
                    }
                }
            }
        }
    }

    for (int i = 0; i < num_blocos_y; i++) {
        for (int j = 0; j < num_blocos_x; j++) {
            free(histogramas[i][j]);
        }
        free(histogramas[i]);
    }
    free(histogramas);

    create_image_rgb(image, lista, filename_rgb);
}


// Função auxiliar para comparar pixels (utilizada na ordenação)
int comparar(const void *a, const void *b) {
    return (*(PixelRGB *)a).red - (*(PixelRGB *)b).red;
}

void median_blur_rgb(ImageRGB *image, Lista* lista, char *filename_rgb){
    int tamanho_kernel = 5; // Define o tamanho do kernel do median blur
    int largura = image->dim.largura;
    int altura = image->dim.altura;
    PixelRGB *pixels = image->pixels;

    int half_kernel = tamanho_kernel / 2;
    PixelRGB *temp_pixels = (PixelRGB *)malloc(tamanho_kernel * tamanho_kernel * sizeof(PixelRGB));

    if (!temp_pixels) {
        fprintf(stderr, "Erro ao alocar memória para pixels temporários.\n");
        return;
    }

    // Aplica o filtro de median blur
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int contador = 0;

            for (int ky = -half_kernel; ky <= half_kernel; ky++) {
                for (int kx = -half_kernel; kx <= half_kernel; kx++) {
                    int novo_x = x + kx;
                    int novo_y = y + ky;

                    if (novo_x >= 0 && novo_x < largura && novo_y >= 0 && novo_y < altura) {
                        int indice = novo_y * largura + novo_x;
                        temp_pixels[contador++] = pixels[indice];
                    }
                }
            }

            // Ordena os pixels temporários para encontrar o valor mediano
            qsort(temp_pixels, contador, sizeof(PixelRGB), comparar);

            // Atribui o valor mediano ao pixel atual
            int indice = y * largura + x;
            pixels[indice] = temp_pixels[contador / 2];
        }
    }

    free(temp_pixels);

    // Salva a nova imagem e atualiza a lista
    create_image_rgb(image, lista, filename_rgb);
}

int compararg(const void *a, const void *b) {
    return *(unsigned char *)a - *(unsigned char *)b;
}

void median_blur_gray(ImageGray *image, Lista *lista, char *filename_gray) {
    int tamanho_kernel = 5; // Define o tamanho do kernel do median blur
    int largura = image->dim.largura;
    int altura = image->dim.altura;
    PixelGray *pixels = image->pixels;

    int half_kernel = tamanho_kernel / 2;
    PixelGray *temp_pixels = (PixelGray *)malloc(tamanho_kernel * tamanho_kernel * sizeof(PixelGray));

    if (!temp_pixels) {
        fprintf(stderr, "Erro ao alocar memória para pixels temporários.\n");
        return;
    }

    // Aplica o filtro de median blur
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int contador = 0;

            for (int ky = -half_kernel; ky <= half_kernel; ky++) {
                for (int kx = -half_kernel; kx <= half_kernel; kx++) {
                    int novo_x = x + kx;
                    int novo_y = y + ky;

                    if (novo_x >= 0 && novo_x < largura && novo_y >= 0 && novo_y < altura) {
                        int indice = novo_y * largura + novo_x;
                        temp_pixels[contador++] = pixels[indice];
                    }
                }
            }

            // Ordena os pixels temporários para encontrar o valor mediano
            qsort(temp_pixels, contador, sizeof(PixelGray), compararg);

            // Atribui o valor mediano ao pixel atual
            int indice = y * largura + x;
            pixels[indice] = temp_pixels[contador / 2];
        }
    }

    free(temp_pixels);

    // Atualiza a lista com a nova imagem
    create_image_gray(image, lista, filename_gray);
}