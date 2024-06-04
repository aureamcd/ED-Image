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
void adicionar_no_lista(Lista *lista, const char *filename);
void liberar_lista(Lista *lista);

// Funções de leitura de arquivo
ImageGray *read_image_gray(const char *filename);
ImageRGB *read_image_rgb(const char *filename);

// Funções de criação e liberação
void create_image_gray(ImageGray *img, Lista *lista);
void free_image_gray(ImageGray *image);

ImageRGB *create_image_rgb();
void free_image_rgb(ImageRGB *image);

// Operações para ImageGray
ImageGray *flip_vertical_gray(ImageGray *image);
ImageGray *flip_horizontal_gray(ImageGray *image);
ImageGray *transpose_Gray(const ImageGray *image);

// Operações para ImageRGB
ImageRGB *flip_vertical_rgb(const ImageRGB *image);
ImageRGB *flip_horizontal_rgb(const ImageRGB *image);
ImageRGB *transpose_RGB(const ImageRGB *image);

// Manipulação por pixel para ImageGray
ImageGray *clahe_gray(const ImageGray *image, int tile_width, int tile_height);
ImageGray *median_blur_gray(const ImageGray *image, int kernel_size);

// Manipulação por pixel para ImageRGB
ImageRGB *clahe_rgb(const ImageRGB *image, int tile_width, int tile_height);
ImageRGB *median_blur_rgb(const ImageRGB *image, int kernel_size);

#endif // IMAGE_H
