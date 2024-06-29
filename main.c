#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

int main()
{
    int op;
    char opc;
    char filename_gray[100];
    char filename_rgb[100];
    ImageGray *image_gray = NULL;
    ImageRGB *image_rgb = NULL;
    Lista *lista_gray = criaLista();
    Lista *lista_rgb = criaLista();
    char nomen[100];
    char nomea[100];

    do
    {

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

                    swit_gray(lista_gray, image_gray, filename_gray);

                    // Após aplicar a edição
                    char base_name[100]; // Declare base_name_gray como array de caracteres
                    strcpy(base_name, filename_gray);
                    char *dot = strrchr(base_name, '.');
                    if (dot != NULL && strcmp(dot, ".txt") == 0)
                    {
                        *dot = '\0';
                    }

                    sprintf(nomea, "%s_%d.txt", base_name, lista_gray->tam);
                    sprintf(nomen, "%s_final.txt", base_name);

                    rename(nomea, nomen);

                    printf("Edicao finalizada!!\n\nTXT final: %s_final.txt\nImagem: %s_final.png",
                           base_name, base_name);

                    printf("\n\nEditar nova imagem? (s/n): ");
                    scanf(" %c", &opc);
                    getchar(); // Captura o caractere newline residual
                }

                liberar_lista(lista_gray);
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

                    swit_rgb(lista_rgb, image_rgb, filename_rgb);

                    // Após aplicar a edição
                    char base_name[100]; // Declare base_name_gray como array de caracteres
                    strcpy(base_name, filename_rgb);
                    char *dot = strrchr(base_name, '.');
                    if (dot != NULL && strcmp(dot, ".txt") == 0)
                    {
                        *dot = '\0';
                    }

                    sprintf(nomea, "%s_%d.txt", base_name, lista_rgb->tam);
                    sprintf(nomen, "%s_final.txt", base_name);

                    rename(nomea, nomen);

                    printf("Edicao finalizada!!\n\nTXT final: %s_final.txt\nImagem: %s_final.png",
                           base_name, base_name);

                    printf("\n\nEditar nova imagem? (s/n): ");
                    scanf(" %c", &opc);
                    getchar(); // Captura o caractere newline residual

                    liberar_lista(lista_rgb);
                    break;
                }

            case 3:
                // Implementar leitura e processamento de imagem semelhante aos casos anteriores
                printf("Opção 3 selecionada - implementar leitura e processamento de imagem.\n");
                break;

            case 4:
                liberar_lista(lista_gray);
                liberar_lista(lista_rgb);
                printf("Programa encerrado.\n");
                return 0;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
            }
        } while (op != 4);
    } while (opc == 's');

return 0;
}