#ifndef IMAGE_H
#define IMAGE_H

typedef struct dimensoes
{
    int altura, largura;
} Dimensoes;

typedef struct pixelRGB
{
    int red, blue, green;
} PixelRGB;

typedef struct pixelGray
{
    int value;
} PixelGray;

typedef struct imageGray
{
    Dimensoes dim;
    PixelGray *pixels;    
    int tam;
} ImageGray;

typedef struct imageRGB
{
    Dimensoes dim;
    PixelRGB *pixels;    
    int tam;
} ImageRGB;

typedef struct pilha
{
    ImageGray *imagegray;
    ImageRGB *imagergb;
    struct pilha *prox;    
    char alt[50];
} Pilha;

typedef struct elemento
{
    char filename[50];
    Pilha *pilha;
    int tam_listap;
    struct elemento *prox;
    struct elemento *ant;
} Elemento;

typedef struct lista
{
    Elemento *inicio;
    Elemento *fim;
    Elemento *ultimo_modificado;
    int tam;
    int cont;
} Lista;


void print_menu();
void print_alter();
void print_hist();

void swit_gray(Lista *lista, ImageGray *image_gray, char *filename);
void swit_rgb(Lista *lista, ImageRGB *image_rgb, char *filename);

void swit_hist_gray(Lista *lista, ImageGray *image_gray);
void swit_hist_rgb(Lista *lista, ImageRGB *image_rgb);

void delete_temp_files(Lista *lista, const char *base_name);
void delete_current_png(const char *base_name);

void call_python_script(char *py, char *funcao, char *txt, char *output);

Lista *criaLista();
void adicionar_no_lista(Lista *lista, char *filename);
void liberar_lista(Lista *lista);
void percorrer_lista(Lista *lista);

void push_pilha_gray(Lista *lista, ImageGray *image_gray, char *filename, char *alteracao);
Pilha *pop_pilha(Lista *lista);
void desfazer_ultima_alteracaogray(Lista *lista, ImageGray *image_gray);
void desfazer_ultima_alteracaorgb(Lista *lista, ImageRGB *image_rgb);


void imprimir_historico(Lista *lista);
void added_gray(Lista *lista, ImageGray *image_gray);
void added_rgb(Lista *lista, ImageRGB *image_rgb);

// Funções de leitura de arquivo
ImageGray *read_image_gray(char *filename);
ImageRGB *read_image_rgb(char *filename);

// Funções de criação e liberação
void create_image_gray(ImageGray *image, Lista *lista, char *filename_gray);
void free_image_gray(ImageGray *image);

void create_image_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void free_image_rgb(ImageRGB *image);

// Operações para ImageGray
void flip_vertical_gray(ImageGray *image, Lista *lista, char *filename_gray);
void flip_horizontal_gray(ImageGray *image, Lista *lista, char *filename_gray);
void transpose_gray(ImageGray *image, Lista *lista, char *filename_gray);

// Operações para ImageRGB
void flip_vertical_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void flip_horizontal_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void transpose_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);

// Manipulação por pixel para ImageGray
void clahe_gray(ImageGray *image, Lista *lista, char *filename_gray);
void median_blur_gray(ImageGray *image, Lista *lista, char *filename_rgb);

// Manipulação por pixel para ImageRGB
void clahe_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void median_blur_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);

void remover_ultimo_lista(Lista *lista);
void desfazer_alteracaogray(Lista *lista);

void desfazer_alteracaorgb(Lista *lista);

void adicionar_aleatorio_gray(ImageGray *image, Lista *lista, char *filename_gray);
void adicionar_aleatorio_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);



#endif // IMAGE_H
