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

typedef struct elemento
{
    char filename[50];
    char ult_alt[50];   
    struct elemento *prox;
    struct elemento *ant;
} Elemento;

typedef struct lista
{
    Elemento *inicio;
    Elemento *fim;    
    int tam;    
} Lista;

void print_menu();

void print_menug();
void swit_menug(Lista *lista, ImageGray *image_gray, char *filename);
void swit_menur(Lista *lista, ImageRGB *image_rgb, char *filename);

void print_alter();
void swit_gray(Lista *lista, ImageGray *image_gray, char *filename);
void swit_rgb(Lista *lista, ImageRGB *image_rgb, char *filename);

void print_hist();
void swit_hist_gray(Lista *lista, ImageGray *image_gray);
void swit_hist_rgb(Lista *lista, ImageRGB *image_rgb);

Lista *criaLista();
void adicionar_no_lista(Lista *lista, char *filename);
void liberar_lista(Lista *lista);
void remover_ultimo_lista(Lista *lista);
void buscar_e_gerar_imagem(Lista *lista);
void deletar_renomear_txt(Lista *lista);


void imprimir_historico(Lista *lista);

void added_gray(Lista *lista, ImageGray *image_gray);
void added_rgb(Lista *lista, ImageRGB *image_rgb);

// Funções de leitura de arquivo
ImageGray *read_image_gray(char *filename);
ImageRGB *read_image_rgb(char *filename);

// Funções de criação
void create_image_gray(ImageGray *image, Lista *lista, char *filename_gray);
void create_image_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);

// Operações para ImageGray
void flip_vertical_gray(ImageGray *image, Lista *lista, char *filename_gray);
void flip_horizontal_gray(ImageGray *image, Lista *lista, char *filename_gray);
void transpose_gray(ImageGray *image, Lista *lista, char *filename_gray);
void clahe_gray(ImageGray *image, Lista *lista, char *filename_gray);
void median_blur_gray(ImageGray *image, Lista *lista, char *filename_rgb);
void adicionar_aleatorio_gray(ImageGray *image, Lista *lista, char *filename_gray);
void desfazer_alteracaogray(Lista *lista);


// Operações para ImageRGB
void flip_vertical_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void flip_horizontal_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void transpose_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void clahe_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void median_blur_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void adicionar_aleatorio_rgb(ImageRGB *image, Lista *lista, char *filename_rgb);
void desfazer_alteracaorgb(Lista *lista);


void delete_temp_files(Lista *lista, const char *base_name);
void delete_current_png(const char *base_name);

void call_python_script(char *py, char *funcao, char *txt, char *output);
int compararg(const void *a, const void *b);
int comparar(const void *a, const void *b);


#endif // IMAGE_H
