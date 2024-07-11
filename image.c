#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "image.h"

void print_menu()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Carregar txt em escala de cinza (Gray)\n");
    printf("2. Carregar txt RGB\n");
    printf("3. Carregar imagem\n");
    printf("4. Sair\n");
}

void print_menug()
{

    printf("\nEscolha uma opcao:\n");
    printf("1. Adicionar Edicao\n");
    printf("2. Adicionar Edicao Aleatoria\n");
    printf("3. Historico\n");
    printf("4. Voltar\n");
}

void swit_menug(Lista *lista, ImageGray *image_gray, char *filename)
{
    int op;
    do
    {
        print_menug();
        printf("\nDigite sua escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            do
            {
            swit_gray(lista, image_gray, filename);
            } while (op != 6);
            break;
        case 2:
            adicionar_aleatorio_gray(image_gray, lista, filename);
            break;
        case 3:
            swit_hist_gray(lista, image_gray);
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (op != 4);
}

void swit_menur(Lista *lista, ImageRGB *image_rgb, char *filename)
{
    int op;
    do
    {
        print_menug();
        printf("\nDigite sua escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        do{
            swit_rgb(lista, image_rgb, filename);
            break;
            } while (op != 6);
        case 2:
            adicionar_aleatorio_rgb(image_rgb, lista, filename);
            break;
        case 3:
            swit_hist_rgb(lista, image_rgb);
            break;
        case 4:
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (op != 4);
}

void print_alter()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Aplicar flip horizontal\n");
    printf("2. Aplicar flip vertical\n");
    printf("3. Aplicar transpose\n");
    printf("4. Aplicar CLAHE\n");
    printf("5. Aplicar MEDIAN\n");
    printf("6. Voltar \n");
}

void swit_gray(Lista *lista, ImageGray *image_gray, char *filename)
{
    int op;

    print_alter();
    printf("\nDigite sua escolha: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        flip_horizontal_gray(image_gray, lista, filename);
        break;

    case 2:
        flip_vertical_gray(image_gray, lista, filename);
        break;

    case 3:
        transpose_gray(image_gray, lista, filename);
        break;
    case 4:
        clahe_gray(image_gray, lista, filename);
        break;

    case 5:
        median_blur_gray(image_gray, lista, filename);
        break;
    case 6:
        break;
    default:
        printf("Opcao invalida.\n");
        break;
    }
}

void swit_rgb(Lista *lista, ImageRGB *image_rgb, char *filename)
{
    int op;
    

        print_alter();
        printf("\nDigite sua escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            flip_horizontal_rgb(image_rgb, lista, filename);
            break;

        case 2:
            flip_vertical_rgb(image_rgb, lista, filename);
            break;

        case 3:
            transpose_rgb(image_rgb, lista, filename);
            break;

        case 4:
            clahe_rgb(image_rgb, lista, filename);
            break;

        case 5:
            median_blur_rgb(image_rgb, lista, filename);
            break;

        case 6:
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }

   
}

void print_hist()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Imprimir Historico\n");
    printf("2. Adicionar Edicao\n");
    printf("3. Deletar Edicao\n");
    printf("4. Buscar\n");
    printf("5. Desfazer Ultima alteracao\n");
    printf("6. Voltar ao menu principal\n");
}

void swit_hist_gray(Lista *lista, ImageGray *image_gray)
{
    strcpy(lista->inicio->ult_alt, "Original");
    print_hist();
    int op;
    printf("Digite a opcao:");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        imprimir_historico(lista);
        break;
    case 2:
        added_gray(lista, image_gray);
        break;
    case 3:
        deletar_renomear_txt(lista);
        break;
    case 4:
        buscar_e_gerar_imagem(lista);
        break;
    case 5:
        desfazer_alteracaogray(lista);
        break;
    case 6:
        break;
    default:
        printf("Opção invalida.\n");
        break;
    }
}

void swit_hist_rgb(Lista *lista, ImageRGB *image_rgb)
{
        strcpy(lista->inicio->ult_alt, "Original");

    print_hist();
    int op;
    printf("Digite a opcao:");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        imprimir_historico(lista);
        break;
    case 2:
        added_rgb(lista, image_rgb);
    case 3:
        deletar_renomear_txt(lista);
        break;
    case 4:
        buscar_e_gerar_imagem(lista);
        break;
    case 5:
        desfazer_alteracaorgb(lista);
        break;
    case 6:
        break;

    default:
        printf("Opção invalida.\n");
        break;
    }
}

Lista *criaLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if (!lista)
    {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        exit(1);
    }

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
        fprintf(stderr, "Erro ao alocar memória para o elemento.\n");
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
    Elemento *current = lista->inicio;
    Elemento *next;

    while (current != NULL)
    {
        next = current->prox;
        free(current);
        current = next;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
}

void imprimir_historico(Lista *lista)
{
    Elemento *elem = lista->inicio;

    while (elem)
    {
        printf("%s - %s\n", elem->filename, elem->ult_alt);

        elem = elem->prox;
        if (elem)
        {
            printf("\n");
        }
    }
}

void added_gray(Lista *lista, ImageGray *image_gray)
{
    char txt[50];
    imprimir_historico(lista);

    printf("Digite o nome do TXT:");
    scanf("%s", txt);

    Elemento *current = lista->inicio->prox;
    int found = 0;
    while (current != NULL)
    {
        if (strcmp(current->filename, txt) == 0)
        {
            found = 1;
            break;
        }
        current = current->prox;
    }

    if (!found)
    {
        printf("O arquivo %s nao pode ser editado ou nao esta na lista.\n", txt);
        return;
    }

    image_gray = read_image_gray(txt);

    call_python_script("image_utils.py", "image_gray_from_txt", txt, "atual_gray.png");

    char base_name[100];
    strcpy(base_name, txt);
    char *dot = strstr(base_name, ".txt"); 
    if (dot != NULL)
    {
        *dot = '\0'; 
    }
    strcat(base_name, ".txt");

    swit_gray(lista, image_gray, base_name);

    strcat(lista->fim->ult_alt, " -> ");
    strcat(lista->fim->ult_alt, txt);
}

void added_rgb(Lista *lista, ImageRGB *image_rgb)
{
    char txt[50];
    imprimir_historico(lista);

    printf("Digite o nome do TXT:");
    scanf(" %s", txt);

    Elemento *current = lista->inicio->prox;
    int found = 0;
    while (current != NULL)
    {
        if (strcmp(current->filename, txt) == 0)
        {
            found = 1;
            break;
        }
        current = current->prox;
    }

    if (!found)
    {
        printf("O arquivo %s nao pode ser editado ou nao esta na lista.\n", txt);
        return;
    }

    image_rgb = read_image_rgb(txt);

    call_python_script("image_utils.py", "image_rgb_from_txt", txt, "atual_rgb.png");

    char base_name[100];
    strcpy(base_name, txt);
    char *dot = strstr(base_name, ".txt");
    if (dot != NULL)
    {
        *dot = '\0';
    }
    strcat(base_name, ".txt");

    swit_rgb(lista, image_rgb, base_name);

    strcat(lista->fim->ult_alt, " -> ");
    strcat(lista->fim->ult_alt, txt);
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
    char filename[256];
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

    call_python_script("image_utils.py", "image_gray_from_txt", filename, "atual_gray.png");
}

void create_image_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
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

    call_python_script("image_utils.py", "image_rgb_from_txt", filename, "atual_rgb.png");
}

void flip_vertical_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura / 2; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                int temp = image->pixels[i * image->dim.largura + j].value;
                image->pixels[i * image->dim.largura + j].value = image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j].value;
                image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j].value = temp;
            }
        }
        create_image_gray(image, lista, filename_gray);
        printf("\nFlip vertical aplicado.\n");

        strcpy(lista->fim->ult_alt, "Flip Vertical");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip vertical.\n");
    }
}

void flip_horizontal_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura / 2; j++)
            {
                int idx1 = i * image->dim.largura + j;
                int idx2 = i * image->dim.largura + (image->dim.largura - j - 1);
                int temp = image->pixels[idx1].value;
                image->pixels[idx1].value = image->pixels[idx2].value;
                image->pixels[idx2].value = temp;
            }
        }

        create_image_gray(image, lista, filename_gray);
        printf("\nFlip horizontal aplicado.\n");
        strcpy(lista->fim->ult_alt, "Flip Horizontal");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip horizontal.\n");
    }
}

void transpose_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        PixelGray *transpose_pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelGray));
        if (!transpose_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels transpostos.\n");
            exit(1);
        }
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                transpose_pixels[j * image->dim.altura + i] = image->pixels[i * image->dim.largura + j];
            }
        }
        int temp = image->dim.altura;
        image->dim.altura = image->dim.largura;
        image->dim.largura = temp;

        free(image->pixels);
        image->pixels = transpose_pixels;

        create_image_gray(image, lista, filename_gray);
        printf("\nTranspose aplicado.\n");

        strcpy(lista->fim->ult_alt, "Transpose");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o Transpose.\n");
    }
}

void clahe_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        float clip_limit = 3.0;
        int NUM_BINS = 256;

        int altura_bloco = image->dim.altura;
        int largura_bloco = image->dim.largura;

        int num_blocos_x = (image->dim.largura + largura_bloco - 1) / largura_bloco;
        int num_blocos_y = (image->dim.altura + altura_bloco - 1) / altura_bloco;

        int ***histogramas = (int ***)malloc(num_blocos_y * sizeof(int **));
        if (!histogramas)
        {
            printf("Erro ao alocar memória para os histogramas\n");
            exit(1);
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            histogramas[i] = (int **)malloc(num_blocos_x * sizeof(int *));
            if (!histogramas[i])
            {
                printf("Erro ao alocar memória para os histogramas\n");
                exit(1);
            }
            for (int j = 0; j < num_blocos_x; j++)
            {
                histogramas[i][j] = (int *)calloc(NUM_BINS, sizeof(int));
                if (!histogramas[i][j])
                {
                    printf("Erro ao alocar memória para os histogramas\n");
                    exit(1);
                }
            }
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            for (int j = 0; j < num_blocos_x; j++)
            {
                memset(histogramas[i][j], 0, NUM_BINS * sizeof(int));

                int x_inicio = j * largura_bloco;
                int x_fim = (j + 1) * largura_bloco;
                int y_inicio = i * altura_bloco;
                int y_fim = (i + 1) * altura_bloco;

                if (x_fim > image->dim.largura)
                    x_fim = image->dim.largura;
                if (y_fim > image->dim.altura)
                    y_fim = image->dim.altura;

                for (int y = y_inicio; y < y_fim; y++)
                {
                    for (int x = x_inicio; x < x_fim; x++)
                    {
                        int valor_pixel = image->pixels[y * image->dim.largura + x].value;
                        histogramas[i][j][valor_pixel]++;
                    }
                }

                int limite = (int)(clip_limit * (x_fim - x_inicio) * (y_fim - y_inicio) / NUM_BINS);
                int excesso = 0;

                for (int k = 0; k < NUM_BINS; k++)
                {
                    if (histogramas[i][j][k] > limite)
                    {
                        excesso += histogramas[i][j][k] - limite;
                        histogramas[i][j][k] = limite;
                    }
                }

                int incremento = excesso / NUM_BINS;
                for (int k = 0; k < NUM_BINS; k++)
                {
                    histogramas[i][j][k] += incremento;
                }

                for (int k = 1; k < NUM_BINS; k++)
                {
                    histogramas[i][j][k] += histogramas[i][j][k - 1];
                }
            }
        }

        for (int y = 0; y < image->dim.altura; y++)
        {
            for (int x = 0; x < image->dim.largura; x++)
            {
                int bloco_x = x / largura_bloco;
                int bloco_y = y / altura_bloco;

                int valor_pixel = image->pixels[y * image->dim.largura + x].value;
                int total_pixels_bloco = largura_bloco * altura_bloco;

                if (bloco_x < num_blocos_x && bloco_y < num_blocos_y)
                {
                    int valor_equalizado = (int)(((float)histogramas[bloco_y][bloco_x][valor_pixel] / total_pixels_bloco) * (NUM_BINS - 1));
                    image->pixels[y * image->dim.largura + x].value = (valor_equalizado > 255) ? 255 : valor_equalizado;
                }
            }
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            for (int j = 0; j < num_blocos_x; j++)
            {
                free(histogramas[i][j]);
            }
            free(histogramas[i]);
        }
        free(histogramas);

        create_image_gray(image, lista, filename_gray);
        printf("\nCLAHE aplicado.\n");

        strcpy(lista->fim->ult_alt, "Clahe");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o CLAHE.\n");
    }
}

void median_blur_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        int tamanho_kernel = 5; 
        int largura = image->dim.largura;
        int altura = image->dim.altura;
        PixelGray *pixels = image->pixels;

        int half_kernel = tamanho_kernel / 2;
        PixelGray *temp_pixels = (PixelGray *)malloc(tamanho_kernel * tamanho_kernel * sizeof(PixelGray));

        if (!temp_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels temporários.\n");
            return;
        }

        
        for (int y = 0; y < altura; y++)
        {
            for (int x = 0; x < largura; x++)
            {
                int contador = 0;

                for (int ky = -half_kernel; ky <= half_kernel; ky++)
                {
                    for (int kx = -half_kernel; kx <= half_kernel; kx++)
                    {
                        int novo_x = x + kx;
                        int novo_y = y + ky;

                        if (novo_x >= 0 && novo_x < largura && novo_y >= 0 && novo_y < altura)
                        {
                            int indice = novo_y * largura + novo_x;
                            temp_pixels[contador++] = pixels[indice];
                        }
                    }
                }

                
                qsort(temp_pixels, contador, sizeof(PixelGray), compararg);

               
                int indice = y * largura + x;
                pixels[indice] = temp_pixels[contador / 2];
            }
        }

        free(temp_pixels);

      
        create_image_gray(image, lista, filename_gray);
        printf("\nMedian Blur aplicado.\n");
        strcpy(lista->fim->ult_alt, "Median Blur");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o Median Blur.\n");
    }
}

void adicionar_aleatorio_gray(ImageGray *image, Lista *lista, char *filename_gray)
{

    srand(time(NULL));

    int random_case = rand() % 5 + 1;

    switch (random_case)
    {
    case 1:
        flip_horizontal_gray(image, lista, filename_gray);
        break;

    case 2:
        flip_vertical_gray(image, lista, filename_gray);
        break;

    case 3:
        transpose_gray(image, lista, filename_gray);
        break;

    case 4:
        clahe_gray(image, lista, filename_gray);
        break;

    case 5:
        median_blur_gray(image, lista, filename_gray);
        break;
    }
}

void desfazer_alteracaogray(Lista *lista)
{
    char op;

    if (lista->tam == 1)
    {
        printf("Não há alterações para desfazer.\n");
        return;
    }
    else
    {
        
        Elemento *ultimo = lista->fim;

        printf("\nApagar %s (s/n)? ", ultimo->filename);
        fflush(stdout); 
        fflush(stdin);  
        scanf(" %c", &op); 

        if (op == 's')
        {
            if (remove(ultimo->filename) == 0)
            {
                printf("Arquivo %s removido com sucesso.\n", ultimo->filename);
            }
            else
            {
                perror("Erro ao remover o arquivo");
            }

            
            remover_ultimo_lista(lista);

            
            ultimo = lista->fim;

            
            if (ultimo != NULL)
            {
                printf("Restaurando a partir de %s\n", ultimo->filename); 

              
                read_image_gray(ultimo->filename);
                call_python_script("image_utils.py", "image_gray_from_txt", ultimo->filename, "atual_gray.png");
                printf("Alteração desfeita e imagem restaurada a partir de %s\n", ultimo->filename);
            }
            else
            {
                printf("Lista está vazia após desfazer a última alteração.\n");
            }
        }
        else
        {
            printf("Alteração não desfeita.\n");
        }
    }
}


void flip_vertical_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura / 2; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                PixelRGB temp = image->pixels[i * image->dim.largura + j];
                image->pixels[i * image->dim.largura + j] = image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j];
                image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j] = temp;
            }
        }
        create_image_rgb(image, lista, filename_rgb);
        printf("\nFlip vertical aplicado.\n");

        strcpy(lista->fim->ult_alt, "Flip Vertical");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip vertical.\n");
    }
}

void flip_horizontal_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura / 2; j++)
            {
                int idx1 = i * image->dim.largura + j;
                int idx2 = i * image->dim.largura + (image->dim.largura - j - 1);
                PixelRGB temp = image->pixels[idx1];
                image->pixels[idx1] = image->pixels[idx2];
                image->pixels[idx2] = temp;
            }
        }
        create_image_rgb(image, lista, filename_rgb);
        printf("\nFlip horizontal aplicado.\n");
        strcpy(lista->fim->ult_alt, "Flip Horizontal");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip horizontal.\n");
    }
}

void transpose_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        PixelRGB *transpose_pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelRGB));
        if (!transpose_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels transpostos.\n");
            exit(1);
        }
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                transpose_pixels[j * image->dim.altura + i] = image->pixels[i * image->dim.largura + j];
            }
        }
        int temp = image->dim.altura;
        image->dim.altura = image->dim.largura;
        image->dim.largura = temp;

        free(image->pixels);
        image->pixels = transpose_pixels;

        create_image_rgb(image, lista, filename_rgb);
        printf("\nTranspose aplicado.\n");

        strcpy(lista->fim->ult_alt, "Flip Transpose");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o Transpose.\n");
    }
}

void clahe_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        float clip_limit = 3.0;
        int NUM_BINS = 256;

        int largura_bloco = image->dim.altura;
        int altura_bloco = image->dim.largura;

        int num_blocos_x = (image->dim.largura + largura_bloco - 1) / largura_bloco;
        int num_blocos_y = (image->dim.altura + altura_bloco - 1) / altura_bloco;

        int ***histogramas = (int ***)malloc(num_blocos_y * sizeof(int **));
        if (!histogramas)
        {
            printf("Erro ao alocar memória para os histogramas\n");
            exit(1);
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            histogramas[i] = (int **)malloc(num_blocos_x * sizeof(int *));
            if (!histogramas[i])
            {
                printf("Erro ao alocar memória para os histogramas\n");
                exit(1);
            }
            for (int j = 0; j < num_blocos_x; j++)
            {
                histogramas[i][j] = (int *)calloc(NUM_BINS, sizeof(int));
                if (!histogramas[i][j])
                {
                    printf("Erro ao alocar memória para os histogramas\n");
                    exit(1);
                }
            }
        }

        for (int canal = 0; canal < 3; canal++)
        {
            for (int i = 0; i < num_blocos_y; i++)
            {
                for (int j = 0; j < num_blocos_x; j++)
                {
                    memset(histogramas[i][j], 0, NUM_BINS * sizeof(int));

                    int x_inicio = j * largura_bloco;
                    int x_fim = (j + 1) * largura_bloco;
                    int y_inicio = i * altura_bloco;
                    int y_fim = (i + 1) * altura_bloco;

                    if (x_fim > image->dim.largura)
                        x_fim = image->dim.largura;
                    if (y_fim > image->dim.altura)
                        y_fim = image->dim.altura;

                    for (int y = y_inicio; y < y_fim; y++)
                    {
                        for (int x = x_inicio; x < x_fim; x++)
                        {
                            int valor_pixel;
                            if (canal == 0)
                            {
                                valor_pixel = image->pixels[y * image->dim.largura + x].red;
                            }
                            else if (canal == 1)
                            {
                                valor_pixel = image->pixels[y * image->dim.largura + x].green;
                            }
                            else
                            {
                                valor_pixel = image->pixels[y * image->dim.largura + x].blue;
                            }
                            histogramas[i][j][valor_pixel]++;
                        }
                    }

                    int limite = (int)(clip_limit * (x_fim - x_inicio) * (y_fim - y_inicio) / NUM_BINS);
                    int excesso = 0;

                    for (int k = 0; k < NUM_BINS; k++)
                    {
                        if (histogramas[i][j][k] > limite)
                        {
                            excesso += histogramas[i][j][k] - limite;
                            histogramas[i][j][k] = limite;
                        }
                    }

                    int incremento = excesso / NUM_BINS;
                    for (int k = 0; k < NUM_BINS; k++)
                    {
                        histogramas[i][j][k] += incremento;
                    }

                    for (int k = 1; k < NUM_BINS; k++)
                    {
                        histogramas[i][j][k] += histogramas[i][j][k - 1];
                    }
                }
            }

            for (int y = 0; y < image->dim.altura; y++)
            {
                for (int x = 0; x < image->dim.largura; x++)
                {
                    int bloco_x = x / largura_bloco;
                    int bloco_y = y / altura_bloco;

                    int valor_pixel;
                    if (canal == 0)
                    {
                        valor_pixel = image->pixels[y * image->dim.largura + x].red;
                    }
                    else if (canal == 1)
                    {
                        valor_pixel = image->pixels[y * image->dim.largura + x].green;
                    }
                    else
                    {
                        valor_pixel = image->pixels[y * image->dim.largura + x].blue;
                    }

                    if (bloco_x < num_blocos_x && bloco_y < num_blocos_y)
                    {
                        int valor_equalizado = (int)(((float)histogramas[bloco_y][bloco_x][valor_pixel] / histogramas[bloco_y][bloco_x][NUM_BINS - 1]) * (NUM_BINS - 1));
                        valor_equalizado = (valor_equalizado > 255) ? 255 : valor_equalizado;

                        if (canal == 0)
                        {
                            image->pixels[y * image->dim.largura + x].red = valor_equalizado;
                        }
                        else if (canal == 1)
                        {
                            image->pixels[y * image->dim.largura + x].green = valor_equalizado;
                        }
                        else
                        {
                            image->pixels[y * image->dim.largura + x].blue = valor_equalizado;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            for (int j = 0; j < num_blocos_x; j++)
            {
                free(histogramas[i][j]);
            }
            free(histogramas[i]);
        }
        free(histogramas);

        create_image_rgb(image, lista, filename_rgb);

        printf("\nCLAHE aplicado.\n");

        strcpy(lista->fim->ult_alt, "Clahe");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o CLAHE.\n");
    }
}

void median_blur_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        int tamanho_kernel = 5; 
        int largura = image->dim.largura;
        int altura = image->dim.altura;
        PixelRGB *pixels = image->pixels;

        int half_kernel = tamanho_kernel / 2;
        PixelRGB *temp_pixels = (PixelRGB *)malloc(tamanho_kernel * tamanho_kernel * sizeof(PixelRGB));

        if (!temp_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels temporários.\n");
            return;
        }

       
        for (int y = 0; y < altura; y++)
        {
            for (int x = 0; x < largura; x++)
            {
                int contador = 0;

                for (int ky = -half_kernel; ky <= half_kernel; ky++)
                {
                    for (int kx = -half_kernel; kx <= half_kernel; kx++)
                    {
                        int novo_x = x + kx;
                        int novo_y = y + ky;

                        if (novo_x >= 0 && novo_x < largura && novo_y >= 0 && novo_y < altura)
                        {
                            int indice = novo_y * largura + novo_x;
                            temp_pixels[contador++] = pixels[indice];
                        }
                    }
                }

              
                qsort(temp_pixels, contador, sizeof(PixelRGB), comparar);

                
                int indice = y * largura + x;
                pixels[indice] = temp_pixels[contador / 2];
            }
        }

        free(temp_pixels);

        
        create_image_rgb(image, lista, filename_rgb);
        printf("\nMedian Blur aplicado.\n");
        strcpy(lista->fim->ult_alt, "Median Blur");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o Median Blur.\n");
    }
}

void remover_ultimo_lista(Lista *lista)
{
    if (lista->tam == 0)
    {
        printf("Lista vazia, não há elementos para remover.\n");
        return;
    }

    Elemento *ultimo = lista->fim;
    Elemento *anterior = ultimo->ant;

    if (anterior != NULL)
    {
        anterior->prox = NULL;
        lista->fim = anterior;
    }
    else
    {
        
        lista->inicio = NULL;
        lista->fim = NULL;
    }

    free(ultimo);
    lista->tam--;
}

void buscar_e_gerar_imagem(Lista *lista)
{
    char filename[50];
    char nome[50];
    printf("Digite o nome do TXT: ");
    scanf("%s", filename);

    char base_name[100];
    strcpy(base_name, filename);
    char *dot = strstr(base_name, ".txt"); 
    if (dot != NULL)
    {
        *dot = '\0'; 
    }
    sprintf(nome, "atual_%s.png", base_name);

    Elemento *elem = lista->inicio; 

    while (elem != NULL)
    {
        if (strcmp(elem->filename, filename) == 0)
        {
            call_python_script("image_utils.py", "image_gray_from_txt", filename, nome);

            break;
        }

        elem = elem->prox;
    }
    printf("Arquivo nao existente na lista");
}

void deletar_renomear_txt(Lista *lista)
{
    char filename[50];
    printf("Digite o nome do TXT a ser deletado: ");
    scanf("%s", filename);

    Elemento *elem = lista->inicio;
    Elemento *prev = NULL;

    
    if (elem == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }

    
    prev = elem;
    elem = elem->prox;

    
    while (elem != NULL)
    {
        if (strcmp(elem->filename, filename) == 0)
        {
           
            if (remove(filename) == 0)
            {
                printf("Arquivo %s deletado com sucesso.\n", filename);

                
                prev->prox = elem->prox;
                if (elem->prox != NULL)
                {
                    elem->prox->ant = prev;
                }
                lista->tam--;

                
                Elemento *temp = elem->prox;
                int index = 2; 

                while (temp != NULL)
                {
                    char nomea[50];
                    char nomen[50];

                    strcpy(nomea, temp->filename);

                    char base_name[100];
                    strcpy(base_name, nomea);
                    char *dot = strstr(base_name, ".txt");
                    if (dot != NULL)
                    {
                        *dot = '\0';
                    }

                    snprintf(nomen, sizeof(nomen), "%s.txt%d", base_name, index);
                    index++;

                    if (rename(nomea, nomen) == 0)
                    {
                        printf("Arquivo %s renomeado para %s com sucesso.\n", nomea, nomen);
                        strcpy(temp->filename, nomen); 
                    }
                    else
                    {
                        printf("Erro ao renomear o arquivo %s.\n", nomea);
                    }

                    temp = temp->prox;
                }

                free(elem);
                return;
            }
            else
            {
                printf("Erro ao deletar o arquivo %s.\n", filename);
            }
        }

        prev = elem;
        elem = elem->prox;
    }

    printf("Arquivo não existente na lista ou é o primeiro elemento.\n");
}

void adicionar_aleatorio_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{

    srand(time(NULL));

    int random_case = rand() % 7 + 1;

    switch (random_case)
    {
    case 1:
        flip_horizontal_rgb(image, lista, filename_rgb);
        break;

    case 2:
        flip_vertical_rgb(image, lista, filename_rgb);
        break;

    case 3:
        transpose_rgb(image, lista, filename_rgb);
        break;

    case 4:
        clahe_rgb(image, lista, filename_rgb);
        break;

    case 5:
        median_blur_rgb(image, lista, filename_rgb);
        break;
    
    }
}

void desfazer_alteracaorgb(Lista *lista)
{
    char op;
    if (lista->tam == 1)
    {
        printf("Não há alterações para desfazer.\n");
        return;
    }
    else
    {

       
        Elemento *ultimo = lista->fim;

        printf("\nApagar %s (s/n)?", ultimo->filename);
         fflush(stdout); 
        fflush(stdin); 
        scanf("%c", &op);
        if (op == 's')
        {
            if (remove(ultimo->filename) == 0)
            {
                printf("Arquivo %s removido com sucesso.\n", ultimo->filename);
            }
            else
            {
                perror("Erro ao remover o arquivo");
            }
            remover_ultimo_lista(lista);
            ultimo = lista->fim;
            if (ultimo != NULL)
            {
                printf("Restaurando a partir de %s\n", ultimo->filename); 

               
                read_image_gray(ultimo->filename);
                call_python_script("image_utils.py", "image_rgb_from_txt", ultimo->filename, "atual_rgb.png");
                printf("Alteração desfeita e imagem restaurada a partir de %s\n", ultimo->filename);
            }
            else
            {
                printf("Lista está vazia após desfazer a última alteração.\n");
            }
        }
        else
        {
            printf("Alteração não desfeita.\n");
        }
    }
}

void delete_temp_files(Lista *lista, const char *base_name)
{
    for (int i = 1; i <= lista->tam; i++)
    {
        char temp_filename[100];
        sprintf(temp_filename, "%s.txt%d", base_name, i);
        if (remove(temp_filename) != 0)
        {
            perror("Erro ao deletar o arquivo temporário");
        }
    }
}

void delete_current_png(const char *base_name)
{
    char png_filename[100];
    snprintf(png_filename, sizeof(png_filename), "atual_%s.png", base_name);
    if (remove(png_filename) != 0)
    {
        perror("Erro ao deletar o arquivo PNG atual");
    }
}

void call_python_script(char *py, char *funcao, char *txt, char *output)
{
    char command[256];
    snprintf(command, sizeof(command), "python %s %s %s %s", py, funcao, txt, output);
    system(command);
}

int compararg(const void *a, const void *b)

{
    return *(unsigned char *)a - *(unsigned char *)b;
}

int comparar(const void *a, const void *b)
{
    return (*(PixelRGB *)a).red - (*(PixelRGB *)b).red;
}

