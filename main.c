#include <stdio.h>
#include "image.h"

void print_menu() {
    printf("\nEscolha uma opcao:\n");
    printf("1. Carregar imagem em escala de cinza (Gray)\n");
    printf("2. Carregar imagem RGB\n");
    printf("3. Sair\n");
}

void print_alter() {
    printf("\nEscolha uma opcao:\n");
    printf("1. Aplicar flip horizontal\n");
    printf("2. Aplicar flip vertical\n");
    printf("3. Aplicar transpose\n");
    printf("4. Aplicar CLAHE\n");
    printf("5. Voltar ao menu principal\n");
}

int main() {
    int op;
    int opc;
    char filename_gray[100];
    char filename_rgb[100];
    ImageGray *image_gray = NULL;
    ImageRGB *image_rgb = NULL;
    Lista *lista_gray = criaLista();
    Lista *lista_rgb = criaLista();

    do {
        print_menu();
        printf("\nDigite sua escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("\nDigite o nome do arquivo da imagem em escala de cinza: ");
                scanf("%s", filename_gray);
                image_gray = read_image_gray(filename_gray);
                if (image_gray) {
                    printf("\nDimensoes da imagem em escala de cinza: %d x %d\n", image_gray->dim.largura, image_gray->dim.altura);
                    printf("Valor do primeiro pixel em escala de cinza: %d\n", image_gray->pixels[0].value);
                    create_image_gray(image_gray, lista_gray, filename_gray);
                    do {
                        print_alter();
                        printf("\nDigite sua escolha: ");
                        scanf("%d", &opc);

                        switch (opc) {
                            case 1:
                                if (lista_gray->tam > 0) {
                                    printf("\nFlip horizontal aplicado.\n");
                                    flip_horizontal_gray(image_gray, lista_gray, filename_gray);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip horizontal.\n");
                                }
                                break;
                            case 2:
                                if (lista_gray->tam > 0) {
                                    printf("\nFlip vertical aplicado.\n");
                                    flip_vertical_gray(image_gray, lista_gray, filename_gray);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip vertical.\n");
                                }
                                break;
                            case 3:
                                if (lista_gray->tam > 0) {
                                    printf("\nTranspose aplicado.\n");
                                    transpose_Gray(image_gray, lista_gray, filename_gray);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o Transpose.\n");
                                }
                                break;
                            case 4:
                                if (lista_gray->tam > 0) {
                                    printf("\nCLAHE aplicado.\n");
                                    clahe_gray(image_gray, lista_gray, filename_gray);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o CLAHE.\n");
                                }
                                break;
                            case 5:
                                break;
                            default:
                                printf("Opcao invalida.\n");
                                break;
                        }

                    } while (opc != 5);

                } else {
                    fprintf(stderr, "\nErro ao carregar a imagem em escala de cinza\n");
                }
                break;
            case 2:
                printf("\nDigite o nome do arquivo da imagem RGB: ");
                scanf("%s", filename_rgb);
                image_rgb = read_image_rgb(filename_rgb);
                if (image_rgb) {
                    printf("\nDimensoes da imagem RGB: %d x %d\n", image_rgb->dim.largura, image_rgb->dim.altura);
                    printf("Valor do primeiro pixel: Red %d, Green %d, Blue %d\n", image_rgb->pixels[0].red, image_rgb->pixels[0].green, image_rgb->pixels[0].blue);
                    create_image_rgb(image_rgb, lista_rgb, filename_rgb);
                    do {
                        print_alter();
                        printf("\nDigite sua escolha: ");
                        scanf("%d", &opc);

                        switch (opc) {
                            case 1:
                                if (lista_rgb->tam > 0) {
                                    printf("\nFlip horizontal aplicado.\n");
                                    flip_horizontal_rgb(image_rgb, lista_rgb, filename_rgb);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip horizontal.\n");
                                }
                                break;
                            case 2:
                                if (lista_rgb->tam > 0) {
                                    printf("\nFlip vertical aplicado.\n");
                                    flip_vertical_rgb(image_rgb, lista_rgb, filename_rgb);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip vertical.\n");
                                }
                                break;
                            case 3:
                                if (lista_rgb->tam > 0) {
                                    printf("\nTranspose aplicado.\n");
                                    transpose_RGB(image_rgb, lista_rgb, filename_rgb);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip horizontal.\n");
                                }
                                break;
                            case 4:
                                if (lista_rgb->tam > 0) {
                                    printf("\nCLAHE aplicado.\n");
                                    clahe_rgb(image_rgb, lista_rgb, filename_rgb);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o CLAHE.\n");
                                }
                                break;
                            case 5:
                                if (lista_rgb->tam > 0) {
                                    printf("\nMedian Blur aplicado.\n");
                                    median_blur_rgb(image_rgb, lista_rgb, filename_rgb);
                                } else {
                                    fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o CLAHE.\n");
                                }
                                break;
                            default:
                                printf("\nOpcao invalida! Tente novamente.\n");
                                break;
                        }

                    } while (opc != 6);

                } else {
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

    } while (op != 3);

    return 0;
}
