#include <stdio.h>
#include "image.h"

void print_menu()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Carregar imagem em escala de cinza (Gray)\n");
    printf("2. Carregar imagem RGB\n");
    printf("3. Sair\n");
}

void print_flip_menu()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Aplicar flip horizontal\n");
    printf("2. Aplicar flip vertical\n");
    printf("3. Aplicar transpose\n");
    printf("4. Voltar ao menu principal\n");
}

int main()
{
    int choice;
    int flip_choice;
    char filename_gray[100];
    char filename_rgb[100];
    ImageGray *image_gray = NULL;
    ImageRGB *image_rgb = NULL;
    Lista *lista_gray = criaLista();
    Lista *lista_rgb = criaLista();

    while (1)
    {
        print_menu();
        printf("\nDigite sua escolha: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nDigite o nome do arquivo da imagem em escala de cinza: ");
            scanf("%s", filename_gray);
            image_gray = read_image_gray(filename_gray);
            if (image_gray)
            {
                printf("\nDimensoes da imagem em escala de cinza: %d x %d\n", image_gray->dim.largura, image_gray->dim.altura);
                printf("Valor do primeiro pixel em escala de cinza: %d\n", image_gray->pixels[0].value);
                create_image_gray(image_gray, lista_gray);
                while (1)
                {
                    print_flip_menu();
                    printf("\nDigite sua escolha: ");
                    scanf("%d", &flip_choice);

                    switch (flip_choice)
                    {
                    case 1:
                        if (lista_gray->tam > 0)
                        {
                            printf("\nFlip horizontal aplicado.\n");
                            flip_horizontal_gray(lista_gray,image_gray);
                        }
                        else
                        {
                            printf("\nNenhuma imagem em escala de cinza carregada para aplicar flip horizontal.\n");
                        }
                        break;
                    case 2:
                        if (lista_gray->tam > 0)
                        {
                            printf("\nFlip vertical aplicado.\n");
                            flip_vertical_gray(lista_gray,image_gray);
                        }
                        else
                        {
                            printf("\nNenhuma imagem em escala de cinza carregada para aplicar flip vertical.\n");
                        }
                        break;
                   
                    case 3:
                        if (lista_gray->tam > 0)
                        {
                            printf("\nTranspose aplicado.\n");
                           transpose_Gray(lista_gray, image_gray);
                        }
                        else
                        {
                            printf("\nNenhuma imagem em escala de cinza carregada para aplicar flip horizontal.\n");
                        }
                        break;
                    case 4:
                        break;
                    default:
                        printf("\nOpcao invalida! Tente novamente.\n");
                        break;
                    }

                    if (flip_choice == 4)
                    {
                        break;
                    }
                }
            }
            else
            {
                fprintf(stderr, "\nErro ao carregar a imagem em escala de cinza\n");
            }
            break;
        case 2:
            printf("\nDigite o nome do arquivo da imagem RGB: ");
            scanf("%s", filename_rgb);
            image_rgb = read_image_rgb(filename_rgb);
            if (image_rgb)
            {
                printf("\nDimensoes da imagem RGB: %d x %d\n", image_rgb->dim.largura, image_rgb->dim.altura);
                printf("Valor do primeiro pixel: Red %d, Green %d, Blue %d\n", image_rgb->pixels[0].red, image_rgb->pixels[0].green, image_rgb->pixels[0].blue);
                create_image_rgb(image_rgb, lista_rgb);
                while (1)
                {
                    print_flip_menu();
                    printf("\nDigite sua escolha: ");
                    scanf("%d", &flip_choice);

                    switch (flip_choice)
                    {
                    case 1:
                        if (lista_rgb->tam > 0)
                        {
                            printf("\nFlip vertical aplicado.\n");
                            flip_vertical_rgb(lista_rgb,image_rgb);
                        }
                        else
                        {
                            printf("\nNenhuma imagem RGB carregada para aplicar flip vertical.\n");
                        }
                        break;
                    case 2:
                        if (lista_rgb->tam > 0)
                        {
                            printf("\nFlip horizontal aplicado.\n");
                            // Implemente a função flip_horizontal_rgb(lista_rgb);
                        }
                        else
                        {
                            printf("\nNenhuma imagem RGB carregada para aplicar flip horizontal.\n");
                        }
                        break;
                    case 3:
                        break;
                    default:
                        printf("\nOpcao invalida! Tente novamente.\n");
                        break;
                    }

                    if (flip_choice == 3)
                    {
                        break;
                    }
                }
            }
            else
            {
                fprintf(stderr, "\nErro ao carregar a imagem RGB\n");
            }
            break;
        case 3:
            liberar_lista(lista_gray);
            liberar_lista(lista_rgb);
            return 0;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }
    }

    return 0;
}
