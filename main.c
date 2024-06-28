#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

void print_menu()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Carregar txt em escala de cinza (Gray)\n");
    printf("2. Carregar txt RGB\n");
    printf("3. Carregar imagem\n");
    printf("4. Sair\n");
}


void print_alter()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Aplicar flip horizontal\n");
    printf("2. Aplicar flip vertical\n");
    printf("3. Aplicar transpose\n");
    printf("4. Aplicar CLAHE\n");
    printf("5. Aplicar MEDIAN\n");
    printf("6. Imprimir historico\n");
    printf("7. Voltar ao menu principal\n");
}

void call_python_script(const char *script_name, const char *function, const char *txt_file, const char *output_image)
{
    char command[256];
    snprintf(command, sizeof(command), "python %s %s %s %s", script_name, function, txt_file, output_image);
    system(command);
}

int main()
{
    int op;
    int opc;
    char filename_gray[100];
    char filename_rgb[100];
    ImageGray *image_gray = NULL;
    ImageRGB *image_rgb = NULL;
    Lista *lista_gray = criaLista();
    Lista *lista_rgb = criaLista();

    // Inicializa o nó inicial da lista_gray
    lista_gray->inicio = (Elemento *)malloc(sizeof(Elemento));
    if (lista_gray->inicio == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria para o nó inicial da lista_gray\n");
        return 1;
    }
    strcpy(lista_gray->inicio->alt, "Original");

    // Inicializa o nó inicial da lista_rgb
    lista_rgb->inicio = (Elemento *)malloc(sizeof(Elemento));
    if (lista_rgb->inicio == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria para o nó inicial da lista_rgb\n");
        return 1;
    }
    strcpy(lista_rgb->inicio->alt, "Original");

    printf("%s", lista_gray->inicio->alt);

    do
    {
        print_menu();
        printf("\nDigite sua escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\nDigite o nome do arquivo txt da imagem em escala de cinza: ");
            scanf("%s", filename_gray);
            image_gray = read_image_gray(filename_gray);

            if (image_gray)
            {
                printf("\nDimensoes da imagem em escala de cinza: %d x %d\n", image_gray->dim.largura, image_gray->dim.altura);
                printf("Valor do primeiro pixel em escala de cinza: %d\n", image_gray->pixels[0].value);
                create_image_gray(image_gray, lista_gray, filename_gray);

                char altered_filename_gray[100];
                snprintf(altered_filename_gray, sizeof(altered_filename_gray), "gray.txt%d", lista_gray->tam);
                call_python_script("image_utils.py", "image_gray_from_txt", altered_filename_gray, "atual_gray.png");

                do
                {
                    print_alter();
                    printf("\nDigite sua escolha: ");
                    scanf("%d", &opc);

                    switch (opc)
                    {
                    case 1:
                        strcpy(lista_gray->inicio->prox->alt, "Aplicacao Flip Horizontal");
                            printf("%s", lista_gray->inicio->alt);

                        if (lista_gray->tam > 0)
                        {
                            printf("\nFlip horizontal aplicado.\n");
                            flip_horizontal_gray(image_gray, lista_gray, filename_gray);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip horizontal.\n");
                        }
                        break;
                    case 2:
                        strcpy(lista_gray->fim->alt, "Aplicacao Flip Vertical");

                        if (lista_gray->tam > 0)
                        {
                            printf("\nFlip vertical aplicado.\n");
                            flip_vertical_gray(image_gray, lista_gray, filename_gray);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip vertical.\n");
                        }
                        break;
                    case 3:
                        strcpy(lista_gray->fim->alt, "Aplicacao Transpose");

                        if (lista_gray->tam > 0)
                        {
                            printf("\nTranspose aplicado.\n");
                            transpose_Gray(image_gray, lista_gray, filename_gray);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o Transpose.\n");
                        }
                        break;
                    case 4:
                        strcpy(lista_gray->fim->alt, "Aplicacao CLAHE");

                        if (lista_gray->tam > 0)
                        {
                            printf("\nCLAHE aplicado.\n");
                            clahe_gray(image_gray, lista_gray, filename_gray);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o CLAHE.\n");
                        }
                        break;
                    case 5:
                        strcpy(lista_gray->fim->alt, "Aplicacao Median Blur");

                        if (lista_gray->tam > 0)
                        {
                            printf("\nMedian Blur aplicado.\n");
                            median_blur_gray(image_gray, lista_gray, filename_gray);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o Median Blur.\n");
                        }
                        break;
                    case 6:
                        imprimir_historico(lista_gray);
                        break;
                    case 7:
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                    }

                    // Gera a nova imagem após a alteração
                    if (opc >= 1 && opc <= 5)
                    {
                        char altered_filename_gray[100];
                        snprintf(altered_filename_gray, sizeof(altered_filename_gray), "gray.txt%d", lista_gray->tam);
                        call_python_script("image_utils.py", "image_gray_from_txt", altered_filename_gray, "atual_gray.png");
                    }

                } while (opc != 7);
            }
            else
            {
                fprintf(stderr, "\nErro ao carregar a imagem em escala de cinza\n");
            }
            break;
        case 2:
            printf("\nDigite o nome do arquivo txt da imagem RGB: ");
            scanf("%s", filename_rgb);
            image_rgb = read_image_rgb(filename_rgb);
            if (image_rgb)
            {
                printf("\nDimensoes da imagem RGB: %d x %d\n", image_rgb->dim.largura, image_rgb->dim.altura);
                printf("Valor do primeiro pixel: Red %d, Green %d, Blue %d\n", image_rgb->pixels[0].red, image_rgb->pixels[0].green, image_rgb->pixels[0].blue);
                create_image_rgb(image_rgb, lista_rgb, filename_rgb);

                char altered_filename_rgb[100];
                snprintf(altered_filename_rgb, sizeof(altered_filename_rgb), "rgb.txt%d", lista_rgb->tam);
                call_python_script("image_utils.py", "image_rgb_from_txt", altered_filename_rgb, "atual_rgb.png");

                do
                {
                    print_alter();
                    printf("\nDigite sua escolha: ");
                    scanf("%d", &opc);

                    switch (opc)
                    {
                    case 1:
                        strcpy(lista_rgb->fim->alt, "Aplicacao Flip Horizontal");

                        if (lista_rgb->tam > 0)
                        {
                            printf("\nFlip horizontal aplicado.\n");
                            flip_horizontal_rgb(image_rgb, lista_rgb, filename_rgb);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip horizontal.\n");
                        }
                        break;
                    case 2:
                        strcpy(lista_rgb->fim->alt, "Aplicacao Flip Vertical");

                        if (lista_rgb->tam > 0)
                        {
                            printf("\nFlip vertical aplicado.\n");
                            flip_vertical_rgb(image_rgb, lista_rgb, filename_rgb);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip vertical.\n");
                        }
                        break;
                    case 3:
                        strcpy(lista_rgb->fim->alt, "Aplicacao Transpose");

                        if (lista_rgb->tam > 0)
                        {
                            printf("\nTranspose aplicado.\n");
                            transpose_RGB(image_rgb, lista_rgb, filename_rgb);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o Transpose.\n");
                        }
                        break;
                    case 4:
                        strcpy(lista_rgb->fim->alt, "Aplicacao CLAHE");

                        if (lista_rgb->tam > 0)
                        {
                            printf("\nCLAHE aplicado.\n");
                            clahe_rgb(image_rgb, lista_rgb, filename_rgb);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o CLAHE.\n");
                        }
                        break;
                    case 5:
                        strcpy(lista_rgb->fim->alt, "Aplicacao Median Blur");

                        if (lista_rgb->tam > 0)
                        {
                            printf("\nMedian Blur aplicado.\n");
                            median_blur_rgb(image_rgb, lista_rgb, filename_rgb);
                        }
                        else
                        {
                            fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o Median Blur.\n");
                        }
                        break;
                    case 6:
                        imprimir_historico(lista_rgb);
                        break;
                    case 7:
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                    }

                    // Gera a nova imagem após a alteração
                    if (opc >= 1 && opc <= 5)
                    {
                        char altered_filename_rgb[100];
                        snprintf(altered_filename_rgb, sizeof(altered_filename_rgb), "rgb.txt%d", lista_rgb->tam);
                        call_python_script("image_utils.py", "image_rgb_from_txt", altered_filename_rgb, "atual_rgb.png");
                    }

                } while (opc != 7);
            }
            else
            {
                fprintf(stderr, "\nErro ao carregar a imagem RGB\n");
            }
            break;
        case 3:
            // Implementar leitura e processamento de imagem semelhante aos casos anteriores
            break;
        case 4:
            liberar_lista(lista_gray);
            liberar_lista(lista_rgb);
            return 0;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

    } while (op != 4);

    return 0;
}
