#include <stdio.h>
#include "image.h"

void print_menu()
{
    printf("Escolha uma opcao:\n");
    printf("1. Carregar imagem em escala de cinza (Gray)\n");
    printf("2. Carregar imagem RGB\n");
    printf("3. Sair\n");
}

int main()
{
    int choice;
    char filename[100];
    ImageGray *image_gray = NULL;
    ImageRGB *image_rgb = NULL;
    Lista *lista = criaLista();

    while (1)
    {
        print_menu();
        printf("Digite sua escolha: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Digite o nome do arquivo da imagem em escala de cinza: ");
            scanf("%s", filename);
            image_gray = read_image_gray(filename);
            if (image_gray)
            {
                printf("Dimensoes da imagem em escala de cinza: %d x %d\n", image_gray->dim.largura, image_gray->dim.altura);
                printf("Valor do primeiro pixel em escala de cinza: %d\n", image_gray->pixels[0].value);
                create_image_gray(image_gray, lista);
            }
            else
            {
                fprintf(stderr, "Erro ao carregar a imagem em escala de cinza\n");
            }
            break;
        case 2:
            printf("Digite o nome do arquivo da imagem RGB: ");
            scanf("%s", filename);
            image_rgb = read_image_rgb(filename);
            if (image_rgb)
            {
                printf("Dimensoes da imagem RGB: %d x %d\n", image_rgb->dim.largura, image_rgb->dim.altura);
                printf("Valor do primeiro pixel: Red %d, Green %d, Blue %d\n", image_rgb->pixels[0].red, image_rgb->pixels[0].green, image_rgb->pixels[0].blue);
                free_image_rgb(image_rgb); // Adicionado para liberar a memória da imagem RGB
            }
            else
            {
                fprintf(stderr, "Erro ao carregar a imagem RGB\n");
            }
            break;
        case 3:
            liberar_lista(lista);
            return 0;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    }

    liberar_lista(lista);
    return 0;
}