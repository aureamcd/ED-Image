#ifndef IMAGE_H
#define IMAGE_H

typedef struct dimensoes {
    int altura, largura;
} Dimensoes;

typedef struct pixelRGB {
    int red, blue, green;
} PixelRGB;

typedef struct pixelGray {
    int value;
} PixelGray;

typedef struct imageGray {
    Dimensoes dim;
    PixelGray *pixels;
} ImageGray;

typedef struct imageRGB {
    Dimensoes dim;
    PixelRGB *pixels;
} ImageRGB;

typedef struct elemento {
    char filename[50];
    struct elemento *prox;
    struct elemento *ant;
} Elemento;

typedef struct lista {
    Elemento *inicio;
    Elemento *fim;
    int tam;    
} Lista;


Lista *criaLista();
void adicionar_no_lista(Lista *lista, char *filename);
void liberar_lista(Lista *lista);
void percorrer_lista(Lista *lista);

// Funções de leitura de arquivo
ImageGray *read_image_gray(char *filename);
ImageRGB *read_image_rgb(char *filename);

// Funções de criação e liberação
ImageGray *create_image_gray(ImageGray *image, Lista *lista, char *filename_gray);
void free_image_gray(ImageGray *image);

ImageRGB *create_image_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void free_image_rgb(ImageRGB *image);

// Operações para ImageGray
ImageGray *flip_vertical_gray(ImageGray *image, Lista *lista, char *filename_gray);
ImageGray *flip_horizontal_gray(ImageGray *image, Lista *lista, char *filename_gray);
ImageGray *transpose_Gray(ImageGray *image, Lista *lista, char *filename_gray);

// Operações para ImageRGB
ImageRGB *flip_vertical_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
ImageRGB *flip_horizontal_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
ImageRGB *transpose_RGB(ImageRGB *image, Lista *lista, char *filename_rgb);

// Manipulação por pixel para ImageGray
ImageGray *clahe_gray(ImageGray *image, int tile_width, int tile_height);
ImageGray *median_blur_gray(ImageGray *image, int kernel_size);

// Manipulação por pixel para ImageRGB
ImageRGB *clahe_rgb(ImageRGB *image, int tile_width, int tile_height);
ImageRGB *median_blur_rgb(ImageRGB *image, int kernel_size);

#endif // IMAGE_H
