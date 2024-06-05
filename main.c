#include <stdio.h>
#include "image.h"

void print_menu()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Carregar imagem em escala de cinza (Gray)\n");
    printf("2. Carregar imagem RGB\n");
    printf("3. Aplicar flip vertical em imagem em escala de cinza\n");
    printf("4. Sair\n");
}

int main()
{
    int choice;
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
            }
            else
            {
                fprintf(stderr, "\nErro ao carregar a imagem RGB\n");
            }
            break;
         case 3:
            // Testar a função flip_vertical_gray
            if (lista_gray->tam > 0) {
                printf("\nFlip vertical aplicado.\n");
                flip_vertical_gray(lista_gray);
            } else {
                printf("\nNenhuma imagem em escala de cinza carregada para aplicar flip vertical.\n");
            }
            break;
        case 4:
            // Liberar listas e encerrar o programa
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
