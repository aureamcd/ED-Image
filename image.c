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
    printf("6. Historico\n");
    printf("7. Desfazer Alteração\n");
    printf("8. Voltar ao menu principal\n");
}

void print_hist()
{
    printf("\nEscolha uma opcao:\n");
    printf("1. Imprimir Historico\n");
    printf("2. Adicionar Edicao\n");
    printf("3. Deletar Edicao\n");
    printf("7. Voltar ao menu principal\n");
}

void swit_gray(Lista *lista, ImageGray *image_gray, char *filename)
{
    int op;
    do
    {
        print_alter();
        printf("\nDigite sua escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            flip_horizontal_gray(image_gray, lista, filename);
            break;

        case 2:
            flip_vertical_gray(image_gray, lista, filename);
            break;

        case 3:
            transpose_gray(image_gray, lista, filename);
            break;
        case 4:
            clahe_gray(image_gray, lista, filename);
            break;

        case 5:
            median_blur_gray(image_gray, lista, filename);
            break;

        case 6:
            print_hist();
            swit_hist_gray(lista, image_gray);
            break;
        case 7:
            desfazer_ultima_alteracaogray(lista, image_gray);
            break;

        case 8:
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (op != 8);
}

void desfazer_ultima_alteracao_rgb(Lista *lista, ImageRGB *imagergb)
{
    if (lista->ultimo_modificado == NULL)
    {
        printf("Nenhuma alteração para desfazer.\n");
        return;
    }

    Elemento *elem = lista->ultimo_modificado;
    if (elem->pilha && elem->pilha->prox)
    {
        // Remover o último elemento da pilha
        Pilha *remover = elem->pilha;
        elem->pilha = remover->prox;
        elem->tam_listap--;
        free(remover);

        // Se a pilha ficar vazia, atualiza o último modificado
        if (elem->pilha == NULL)
        {
            lista->ultimo_modificado = NULL;
        }

        // Atualizar imagergb com o novo topo da pilha, se houver
        if (elem->pilha)
        {
            // Aqui você precisaria implementar a cópia dos pixels de elem->pilha->imagergb para imagergb
            // Suponha que ImageRGB tenha uma função para copiar os pixels
            imagergb = elem->pilha->imagergb;

            // Chamar a função create com o filename do topo da pilha
            create_image_rgb(imagergb, lista, elem->filename); // Supondo que create é a função que você deseja chamar
        }
        else
        {
            printf("Pilha vazia após desfazer a última alteração.\n");
        }
    }
    else
    {
        printf("Não há alterações suficientes para desfazer.\n");
    }
}

void swit_rgb(Lista *lista, ImageRGB *image_rgb, char *filename)
{
    int op;
    do
    {
        print_alter();
        printf("\nDigite sua escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            flip_horizontal_rgb(image_rgb, lista, filename);
            break;

        case 2:
            flip_vertical_rgb(image_rgb, lista, filename);
            break;

        case 3:
            transpose_rgb(image_rgb, lista, filename);
            break;

        case 4:
            clahe_rgb(image_rgb, lista, filename);
            break;

        case 5:
            median_blur_rgb(image_rgb, lista, filename);
            break;

        case 6:
            print_hist();
            swit_hist_rgb(lista, image_rgb);
            break;

        case 7:
            desfazer_ultima_alteracao_rgb(lista, image_rgb);
            break;
        case 8:
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }

    } while (op != 8);
}

void swit_hist_gray(Lista *lista, ImageGray *image_gray)
{
    int op;
    printf("Digite a opcao:");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        imprimir_historico(lista);
        break;
    case 2:

        added_gray(lista, image_gray);
        break;
    default:
        printf("Opção inválida.\n");
        break;
    }
}

void swit_hist_rgb(Lista *lista, ImageRGB *image_rgb)
{
    int op;
    printf("Digite a opcao:");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        imprimir_historico(lista);
        break;
    case 2:

        added_rgb(lista, image_rgb);
        break;
    default:
        printf("Opção inválida.\n");
        break;
    }
}

void delete_temp_files(Lista *lista, const char *base_name)
{
    for (int i = 1; i <= lista->tam; i++)
    {
        char temp_filename[100];
        sprintf(temp_filename, "%s.txt%d", base_name, i);
        if (remove(temp_filename) != 0)
        {
            perror("Erro ao deletar o arquivo temporário");
        }
    }
}

void delete_current_png(const char *base_name)
{
    char png_filename[100];
    snprintf(png_filename, sizeof(png_filename), "atual_%s.png", base_name);
    if (remove(png_filename) != 0)
    {
        perror("Erro ao deletar o arquivo PNG atual");
    }
}

void call_python_script(char *py, char *funcao, char *txt, char *output)
{
    char command[256];
    snprintf(command, sizeof(command), "python %s %s %s %s", py, funcao, txt, output);
    system(command);
}

Lista *criaLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if (!lista)
    {
        fprintf(stderr, "Erro ao alocar memória para a lista.\n");
        exit(1);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->ultimo_modificado = NULL;
    lista->tam = 0;
    lista->cont = 0;

    return lista;
}

void liberar_lista(Lista *lista)
{
    Elemento *atual = lista->inicio;
    while (atual)
    {
        Elemento *prox = atual->prox;

        Pilha *pilha_atual = atual->pilha;
        while (pilha_atual)
        {
            Pilha *prox_pilha = pilha_atual->prox;
            free(pilha_atual);
            pilha_atual = prox_pilha;
        }
        free(atual);
        atual = prox;
    }
    free(lista);
}

void adicionar_no_lista(Lista *lista, char *filename)
{
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
    if (!novo)
    {
        fprintf(stderr, "Erro ao alocar memória para o elemento.\n");
        exit(1);
    }

    strncpy(novo->filename, filename, sizeof(novo->filename) - 1);
    novo->filename[sizeof(novo->filename) - 1] = '\0';
    novo->pilha = NULL;
    novo->tam_listap = 0;
    novo->prox = NULL;
    novo->ant = lista->fim;

    if (lista->tam == 0)
    {
        lista->inicio = novo;
    }
    else
    {
        lista->fim->prox = novo;
    }
    lista->fim = novo;
    lista->tam++;
}

void push_pilha_gray(Lista *lista, ImageGray *image_gray, char *filename, char *alteracao)
{
    Elemento *elem = lista->inicio;
    while (elem)
    {
        if (strcmp(elem->filename, filename) == 0)
        {
            Pilha *nova_pilha = (Pilha *)malloc(sizeof(Pilha));
            if (!nova_pilha)
            {
                fprintf(stderr, "Erro ao alocar memória para nova pilha.\n");
                exit(1);
            }

            nova_pilha->imagegray = image_gray;
            nova_pilha->imagergb = NULL; // Assumindo que a pilha para RGB não será usada aqui
            strcpy(nova_pilha->alt, alteracao);
            nova_pilha->prox = elem->pilha;
            elem->pilha = nova_pilha;
            elem->tam_listap++;
            lista->ultimo_modificado = elem;
            return;
        }
        elem = elem->prox;
    }

    // Se não encontrou um elemento com o mesmo filename, cria um novo elemento na lista
    adicionar_no_lista(lista, filename);
    push_pilha_gray(lista, image_gray, filename, alteracao); // Chama novamente para adicionar a pilha
}

void push_pilha_rgb(Lista *lista, ImageRGB *image_rgb, char *filename, char *alteracao)
{
    Elemento *elem = lista->inicio;
    while (elem)
    {
        if (strcmp(elem->filename, filename) == 0)
        {
            Pilha *nova_pilha = (Pilha *)malloc(sizeof(Pilha));
            if (!nova_pilha)
            {
                fprintf(stderr, "Erro ao alocar memória para nova pilha.\n");
                exit(1);
            }

            nova_pilha->imagegray = NULL;
            nova_pilha->imagergb = image_rgb; // Assumindo que a pilha para grayscale não será usada aqui
            strcpy(nova_pilha->alt, alteracao);
            nova_pilha->prox = elem->pilha;
            elem->pilha = nova_pilha;
            elem->tam_listap++;
            lista->ultimo_modificado = elem;
            return;
        }
        elem = elem->prox;
    }

    // Se não encontrou um elemento com o mesmo filename, cria um novo elemento na lista
    adicionar_no_lista(lista, filename);
    push_pilha_rgb(lista, image_rgb, filename, alteracao); // Chama novamente para adicionar a pilha
}

void imprimir_historico(Lista *lista)
{
    Elemento *elem = lista->inicio;

    while (elem)
    {
        printf("Arquivo: %s\n", elem->filename);

        Pilha *pilha = elem->pilha;
        if (pilha)
        {
            printf("- Alteracao: ");
            while (pilha)
            {
                printf("%s", pilha->alt);
                pilha = pilha->prox;
                if (pilha)
                {
                    printf(" - ");
                }
            }
        }

        elem = elem->prox;
        if (elem)
        {
            printf("\n\n"); // Espaço entre arquivos
        }
        else
        {
            printf("\n"); // Fim do último arquivo
        }
    }
}

void desfazer_ultima_alteracaogray(Lista *lista, ImageGray *imagegray)
{
    if (lista->ultimo_modificado == NULL)
    {
        printf("Nenhuma alteração para desfazer.\n");
        return;
    }

    // Copiar o filename do último modificado
    char filename[50];
    strcpy(filename, lista->ultimo_modificado->filename);

    // Procurar o elemento correspondente ao filename
    Elemento *elem = lista->inicio;
     while (elem != NULL && strcmp(elem->filename, filename) != 0)
    {
        elem = elem->prox;
    }

    if (elem == NULL)
    {
        printf("Elemento não encontrado.\n");
        return;
    }
    
    if (elem->pilha)
    {
        // Remover o último elemento da pilha
        Pilha *remover = elem->pilha;
        elem->pilha = remover->prox;
        elem->tam_listap--;
        free(remover);

        // Verificar se a pilha está vazia após a remoção
        if (elem->pilha == NULL)
        {
            // Remover o elemento da lista, pois não há mais alterações
            if (elem->ant)
            {
                elem->ant->prox = elem->prox;
            }
            else
            {
                lista->inicio = elem->prox;
            }
            if (elem->prox)
            {
                elem->prox->ant = elem->ant;
            }
            else
            {
                lista->fim = elem->ant;
            }

            // Excluir o arquivo TXT associado ao elemento removido
            remove(elem->filename);

            free(elem);
            lista->ultimo_modificado = NULL;
            printf("Arquivo e pilha removidos, pois não há mais alterações.\n");
        }
        else
        {
            // Atualizar o último modificado para o novo topo da pilha
            lista->ultimo_modificado = elem;
            printf("%s", lista->fim->pilha->alt);
            // Atualizar imagegray com o novo topo da pilha
            *imagegray = *(lista->fim->pilha->imagegray);

            // Chamar a função create_image_gray com o filename do elemento original
            create_image_gray(imagegray, lista, lista->fim->filename); // Supondo que create_image_gray é a função que você deseja chamar
        }
    }
    else
    {
        printf("Não há alterações suficientes para desfazer.\n");
    }
}

void added_gray(Lista *lista, ImageGray *image_gray)
{
    char txt[50];
    imprimir_historico(lista);

    printf("Digite o nome do TXT:");
    scanf("%s", txt);

    image_gray = read_image_gray(txt);

    call_python_script("image_utils.py", "image_gray_from_txt", txt, "atual_gray.png");
    lista->cont = 0;
    swit_gray(lista, image_gray, txt);
}

void added_rgb(Lista *lista, ImageRGB *image_rgb)
{
    char txt[50];
    imprimir_historico(lista);

    printf("Digite o nome do TXT:");
    scanf(" %s", txt);

    image_rgb = read_image_rgb(txt);

    call_python_script("image_utils.py", "image_rgb_from_txt", txt, "atual_rgb.png");
    lista->cont = 0;
    swit_rgb(lista, image_rgb, txt);
}

ImageGray *read_image_gray(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.largura) != 1 || fscanf(file, "%d", &dim.altura) != 1)
    {
        printf("Erro ao ler as dimensoes da imagem\n");
        fclose(file);
        exit(1);
    }

    ImageGray *image = (ImageGray *)malloc(sizeof(ImageGray));
    if (!image)
    {
        printf("Erro ao alocar memoria para a imagem\n");
        fclose(file);
        exit(1);
    }

    image->dim = dim;
    image->pixels = (PixelGray *)malloc(dim.largura * dim.altura * sizeof(PixelGray));
    if (!image->pixels)
    {
        printf("Erro ao alocar memoria para os pixels\n");
        free(image);
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < dim.largura * dim.altura; i++)
    {
        int pixel_value;
        if (fscanf(file, "%d,", &pixel_value) != 1)
        {
            printf("Erro ao ler o valor do pixel no indice %d\n", i);
            free(image->pixels);
            free(image);
            fclose(file);
            exit(1);
        }
        image->pixels[i].value = pixel_value;
    }

    fclose(file);
    return image;
}

ImageRGB *read_image_rgb(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    Dimensoes dim;
    if (fscanf(file, "%d", &dim.altura) != 1 || fscanf(file, "%d", &dim.largura) != 1)
    {
        printf("Erro ao ler as dimensoes da imagem\n");
        fclose(file);
        exit(1);
    }

    ImageRGB *image = (ImageRGB *)malloc(sizeof(ImageRGB));
    if (!image)
    {
        printf("Erro ao alocar memoria para a imagem\n");
        fclose(file);
        exit(1);
    }

    image->dim = dim;
    image->pixels = (PixelRGB *)malloc(dim.largura * dim.altura * sizeof(PixelRGB));
    if (!image->pixels)
    {
        printf("Erro ao alocar memoria para os pixels\n");
        free(image);
        fclose(file);
        exit(1);
    }

    for (int i = 0; i < dim.largura * dim.altura; i++)
    {
        int red, green, blue;
        if (fscanf(file, "%d %d %d,", &red, &green, &blue) != 3)
        {
            printf("Erro ao ler os valores dos canais de cor RGB no indice %d\n", i);
            free(image->pixels);
            free(image);
            fclose(file);
            exit(1);
        }
        image->pixels[i].red = red;
        image->pixels[i].green = green;
        image->pixels[i].blue = blue;
    }

    fclose(file);
    return image;
}

void create_image_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    // Aqui, vai ser chamado toda vez que a imagem for manipulada. Essa função sera chamada ao final,
    // para criar o novo arquivo com os valores novos, e ele tem que estar dentro de uma lista duplamente encadeada

    // chamar a struct (que estara com os novos valores), e preencher o arquivo
    // o arquivo sera criado toda vez que ele for criado, e o nome sera *alteração+num da alteração
    // adicionar ao encadeamento, no final
    char filename[50];
    strcpy(filename, filename_gray);

    if (lista->cont > 0)
    {

        snprintf(filename, sizeof(filename), "%s%d", filename_gray, lista->tam + 1);
    }

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Erro ao criar o arquivo %s\n", filename);
        exit(1);
    }

    fprintf(file, "%d\n%d\n", image->dim.largura, image->dim.altura);
    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            fprintf(file, "%d,", image->pixels[i * image->dim.largura + j].value);
        }

        fprintf(file, "\n");
    }

    fclose(file);
    if (lista->cont > 0)
    {
        adicionar_no_lista(lista, filename);
    }

    call_python_script("image_utils.py", "image_gray_from_txt", filename, "atual_gray.png");
}

void free_image_gray(ImageGray *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

void create_image_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    // Aqui, vai ser chamado toda vez que a imagem for manipulada. Essa função sera chamada ao final,
    // para criar o novo arquivo com os valores novos, e ele tem que estar dentro de uma lista duplamente encadeada

    // chamar a struct (que estara com os novos valores), e preencher o arquivo
    // o arquivo sera criado toda vez que ele for criado, e o nome sera *alteração+num da alteração
    // adicionar ao encadeamento, no final

    char filename[50];

    strcpy(filename, filename_rgb);
    if (lista->cont > 0)
    {
        snprintf(filename, sizeof(filename), "%s%d", filename_rgb, lista->tam + 1);
    }
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Erro ao criar o arquivo %s\n", filename);
        exit(1);
    }

    fprintf(file, "%d\n%d\n", image->dim.altura, image->dim.largura);
    for (int i = 0; i < image->dim.altura; i++)
    {
        for (int j = 0; j < image->dim.largura; j++)
        {
            fprintf(file, "%d %d %d,", image->pixels[i * image->dim.largura + j].red,
                    image->pixels[i * image->dim.largura + j].green,
                    image->pixels[i * image->dim.largura + j].blue);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    if (lista->cont > 0)
    {
        adicionar_no_lista(lista, filename);
    }

    call_python_script("image_utils.py", "image_rgb_from_txt", filename, "atual_rgb.png");
}

void free_image_rgb(ImageRGB *image)
{
    if (image)
    {
        free(image->pixels);
        free(image);
    }
}

void flip_vertical_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura / 2; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                int temp = image->pixels[i * image->dim.largura + j].value;
                image->pixels[i * image->dim.largura + j].value = image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j].value;
                image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j].value = temp;
            }
        }
        create_image_gray(image, lista, filename_gray);
        printf("\nFlip vertical aplicado.\n");

        char filename[50];
        strcpy(filename, filename_gray);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_gray, lista->tam);
        }

        push_pilha_gray(lista, image, filename, "Aplicacao Flip Vertical");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip vertical.\n");
    }
}

void flip_horizontal_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura / 2; j++)
            {
                int idx1 = i * image->dim.largura + j;
                int idx2 = i * image->dim.largura + (image->dim.largura - j - 1);
                int temp = image->pixels[idx1].value;
                image->pixels[idx1].value = image->pixels[idx2].value;
                image->pixels[idx2].value = temp;
            }
        }
        create_image_gray(image, lista, filename_gray);
        printf("\nFlip horizontal aplicado.\n");

        char filename[50];
        strcpy(filename, filename_gray);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_gray, lista->tam);
        }

        push_pilha_gray(lista, image, filename, "Aplicacao Flip Horizontal");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar flip horizontal.\n");
    }
}
void transpose_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        PixelGray *transpose_pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelGray));
        if (!transpose_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels transpostos.\n");
            exit(1);
        }
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                transpose_pixels[j * image->dim.altura + i] = image->pixels[i * image->dim.largura + j];
            }
        }
        int temp = image->dim.altura;
        image->dim.altura = image->dim.largura;
        image->dim.largura = temp;

        free(image->pixels);
        image->pixels = transpose_pixels;

        create_image_gray(image, lista, filename_gray);
        printf("\nTranspose aplicado.\n");

        char filename[50];
        strcpy(filename, filename_gray);

        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_gray, lista->tam);
        }

        push_pilha_gray(lista, image, filename, "Aplicacao Transpose");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o Transpose.\n");
    }
}

void flip_vertical_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura / 2; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                PixelRGB temp = image->pixels[i * image->dim.largura + j];
                image->pixels[i * image->dim.largura + j] = image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j];
                image->pixels[(image->dim.altura - i - 1) * image->dim.largura + j] = temp;
            }
        }
        create_image_rgb(image, lista, filename_rgb);
        printf("\nFlip vertical aplicado.\n");
        char filename[50];
        strcpy(filename, filename_rgb);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_rgb, lista->tam);
        }

        push_pilha_rgb(lista, image, filename, "Aplicacao Flip Vertical");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip vertical.\n");
    }
}

void flip_horizontal_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura / 2; j++)
            {
                int idx1 = i * image->dim.largura + j;
                int idx2 = i * image->dim.largura + (image->dim.largura - j - 1);
                PixelRGB temp = image->pixels[idx1];
                image->pixels[idx1] = image->pixels[idx2];
                image->pixels[idx2] = temp;
            }
        }
        create_image_rgb(image, lista, filename_rgb);
        printf("\nFlip horizontal aplicado.\n");

        char filename[50];
        strcpy(filename, filename_rgb);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_rgb, lista->tam);
        }

        push_pilha_rgb(lista, image, filename, "Aplicacao Flip Horizontal");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar flip horizontal.\n");
    }
}

void transpose_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        PixelRGB *transpose_pixels = malloc(image->dim.altura * image->dim.largura * sizeof(PixelRGB));
        if (!transpose_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels transpostos.\n");
            exit(1);
        }
        for (int i = 0; i < image->dim.altura; i++)
        {
            for (int j = 0; j < image->dim.largura; j++)
            {
                transpose_pixels[j * image->dim.altura + i] = image->pixels[i * image->dim.largura + j];
            }
        }
        int temp = image->dim.altura;
        image->dim.altura = image->dim.largura;
        image->dim.largura = temp;

        free(image->pixels);
        image->pixels = transpose_pixels;

        create_image_rgb(image, lista, filename_rgb);
        printf("\nTranspose aplicado.\n");

        char filename[50];
        strcpy(filename, filename_rgb);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_rgb, lista->tam);
        }

        push_pilha_rgb(lista, image, filename, "Aplicacao Transpose");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o Transpose.\n");
    }
}

void clahe_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        float clip_limit = 3.0;
        int NUM_BINS = 256;

        int altura_bloco = image->dim.altura;
        int largura_bloco = image->dim.largura;

        int num_blocos_x = (image->dim.largura + largura_bloco - 1) / largura_bloco;
        int num_blocos_y = (image->dim.altura + altura_bloco - 1) / altura_bloco;

        int ***histogramas = (int ***)malloc(num_blocos_y * sizeof(int **));
        if (!histogramas)
        {
            printf("Erro ao alocar memória para os histogramas\n");
            exit(1);
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            histogramas[i] = (int **)malloc(num_blocos_x * sizeof(int *));
            if (!histogramas[i])
            {
                printf("Erro ao alocar memória para os histogramas\n");
                exit(1);
            }
            for (int j = 0; j < num_blocos_x; j++)
            {
                histogramas[i][j] = (int *)calloc(NUM_BINS, sizeof(int));
                if (!histogramas[i][j])
                {
                    printf("Erro ao alocar memória para os histogramas\n");
                    exit(1);
                }
            }
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            for (int j = 0; j < num_blocos_x; j++)
            {
                memset(histogramas[i][j], 0, NUM_BINS * sizeof(int));

                int x_inicio = j * largura_bloco;
                int x_fim = (j + 1) * largura_bloco;
                int y_inicio = i * altura_bloco;
                int y_fim = (i + 1) * altura_bloco;

                if (x_fim > image->dim.largura)
                    x_fim = image->dim.largura;
                if (y_fim > image->dim.altura)
                    y_fim = image->dim.altura;

                for (int y = y_inicio; y < y_fim; y++)
                {
                    for (int x = x_inicio; x < x_fim; x++)
                    {
                        int valor_pixel = image->pixels[y * image->dim.largura + x].value;
                        histogramas[i][j][valor_pixel]++;
                    }
                }

                int limite = (int)(clip_limit * (x_fim - x_inicio) * (y_fim - y_inicio) / NUM_BINS);
                int excesso = 0;

                for (int k = 0; k < NUM_BINS; k++)
                {
                    if (histogramas[i][j][k] > limite)
                    {
                        excesso += histogramas[i][j][k] - limite;
                        histogramas[i][j][k] = limite;
                    }
                }

                int incremento = excesso / NUM_BINS;
                for (int k = 0; k < NUM_BINS; k++)
                {
                    histogramas[i][j][k] += incremento;
                }

                for (int k = 1; k < NUM_BINS; k++)
                {
                    histogramas[i][j][k] += histogramas[i][j][k - 1];
                }
            }
        }

        for (int y = 0; y < image->dim.altura; y++)
        {
            for (int x = 0; x < image->dim.largura; x++)
            {
                int bloco_x = x / largura_bloco;
                int bloco_y = y / altura_bloco;

                int valor_pixel = image->pixels[y * image->dim.largura + x].value;
                int total_pixels_bloco = largura_bloco * altura_bloco;

                if (bloco_x < num_blocos_x && bloco_y < num_blocos_y)
                {
                    int valor_equalizado = (int)(((float)histogramas[bloco_y][bloco_x][valor_pixel] / total_pixels_bloco) * (NUM_BINS - 1));
                    image->pixels[y * image->dim.largura + x].value = (valor_equalizado > 255) ? 255 : valor_equalizado;
                }
            }
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            for (int j = 0; j < num_blocos_x; j++)
            {
                free(histogramas[i][j]);
            }
            free(histogramas[i]);
        }
        free(histogramas);

        create_image_gray(image, lista, filename_gray);
        printf("\nCLAHE aplicado.\n");

        char filename[50];
        strcpy(filename, filename_gray);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_gray, lista->tam);
        }

        push_pilha_gray(lista, image, filename, "Aplicacao CLAHE");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o CLAHE.\n");
    }
}

void clahe_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        float clip_limit = 3.0;
        int NUM_BINS = 256;

        int largura_bloco = image->dim.altura; // Tamanho do bloco
        int altura_bloco = image->dim.largura; // Tamanho do bloco

        int num_blocos_x = (image->dim.largura + largura_bloco - 1) / largura_bloco;
        int num_blocos_y = (image->dim.altura + altura_bloco - 1) / altura_bloco;

        int ***histogramas = (int ***)malloc(num_blocos_y * sizeof(int **));
        if (!histogramas)
        {
            printf("Erro ao alocar memória para os histogramas\n");
            exit(1);
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            histogramas[i] = (int **)malloc(num_blocos_x * sizeof(int *));
            if (!histogramas[i])
            {
                printf("Erro ao alocar memória para os histogramas\n");
                exit(1);
            }
            for (int j = 0; j < num_blocos_x; j++)
            {
                histogramas[i][j] = (int *)calloc(NUM_BINS, sizeof(int));
                if (!histogramas[i][j])
                {
                    printf("Erro ao alocar memória para os histogramas\n");
                    exit(1);
                }
            }
        }

        for (int canal = 0; canal < 3; canal++)
        { // Loop por cada canal de cor (0: Red, 1: Green, 2: Blue)
            for (int i = 0; i < num_blocos_y; i++)
            {
                for (int j = 0; j < num_blocos_x; j++)
                {
                    memset(histogramas[i][j], 0, NUM_BINS * sizeof(int));

                    int x_inicio = j * largura_bloco;
                    int x_fim = (j + 1) * largura_bloco;
                    int y_inicio = i * altura_bloco;
                    int y_fim = (i + 1) * altura_bloco;

                    if (x_fim > image->dim.largura)
                        x_fim = image->dim.largura;
                    if (y_fim > image->dim.altura)
                        y_fim = image->dim.altura;

                    for (int y = y_inicio; y < y_fim; y++)
                    {
                        for (int x = x_inicio; x < x_fim; x++)
                        {
                            int valor_pixel;
                            if (canal == 0)
                            {
                                valor_pixel = image->pixels[y * image->dim.largura + x].red;
                            }
                            else if (canal == 1)
                            {
                                valor_pixel = image->pixels[y * image->dim.largura + x].green;
                            }
                            else
                            {
                                valor_pixel = image->pixels[y * image->dim.largura + x].blue;
                            }
                            histogramas[i][j][valor_pixel]++;
                        }
                    }

                    int limite = (int)(clip_limit * (x_fim - x_inicio) * (y_fim - y_inicio) / NUM_BINS);
                    int excesso = 0;

                    for (int k = 0; k < NUM_BINS; k++)
                    {
                        if (histogramas[i][j][k] > limite)
                        {
                            excesso += histogramas[i][j][k] - limite;
                            histogramas[i][j][k] = limite;
                        }
                    }

                    int incremento = excesso / NUM_BINS;
                    for (int k = 0; k < NUM_BINS; k++)
                    {
                        histogramas[i][j][k] += incremento;
                    }

                    for (int k = 1; k < NUM_BINS; k++)
                    {
                        histogramas[i][j][k] += histogramas[i][j][k - 1];
                    }
                }
            }

            for (int y = 0; y < image->dim.altura; y++)
            {
                for (int x = 0; x < image->dim.largura; x++)
                {
                    int bloco_x = x / largura_bloco;
                    int bloco_y = y / altura_bloco;

                    int valor_pixel;
                    if (canal == 0)
                    {
                        valor_pixel = image->pixels[y * image->dim.largura + x].red;
                    }
                    else if (canal == 1)
                    {
                        valor_pixel = image->pixels[y * image->dim.largura + x].green;
                    }
                    else
                    {
                        valor_pixel = image->pixels[y * image->dim.largura + x].blue;
                    }

                    if (bloco_x < num_blocos_x && bloco_y < num_blocos_y)
                    {
                        int valor_equalizado = (int)(((float)histogramas[bloco_y][bloco_x][valor_pixel] / histogramas[bloco_y][bloco_x][NUM_BINS - 1]) * (NUM_BINS - 1));
                        valor_equalizado = (valor_equalizado > 255) ? 255 : valor_equalizado;

                        if (canal == 0)
                        {
                            image->pixels[y * image->dim.largura + x].red = valor_equalizado;
                        }
                        else if (canal == 1)
                        {
                            image->pixels[y * image->dim.largura + x].green = valor_equalizado;
                        }
                        else
                        {
                            image->pixels[y * image->dim.largura + x].blue = valor_equalizado;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < num_blocos_y; i++)
        {
            for (int j = 0; j < num_blocos_x; j++)
            {
                free(histogramas[i][j]);
            }
            free(histogramas[i]);
        }
        free(histogramas);

        create_image_rgb(image, lista, filename_rgb);

        printf("\nCLAHE aplicado.\n");

        char filename[50];
        strcpy(filename, filename_rgb);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_rgb, lista->tam);
        }
        push_pilha_rgb(lista, image, filename, "Aplicacao CLAHE");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o CLAHE.\n");
    }
}

// Função auxiliar para comparar pixels (utilizada na ordenação)
int comparar(const void *a, const void *b)
{
    return (*(PixelRGB *)a).red - (*(PixelRGB *)b).red;
}

void median_blur_rgb(ImageRGB *image, Lista *lista, char *filename_rgb)
{
    if (lista->tam > 0)
    {
        int tamanho_kernel = 5; // Define o tamanho do kernel do median blur
        int largura = image->dim.largura;
        int altura = image->dim.altura;
        PixelRGB *pixels = image->pixels;

        int half_kernel = tamanho_kernel / 2;
        PixelRGB *temp_pixels = (PixelRGB *)malloc(tamanho_kernel * tamanho_kernel * sizeof(PixelRGB));

        if (!temp_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels temporários.\n");
            return;
        }

        // Aplica o filtro de median blur
        for (int y = 0; y < altura; y++)
        {
            for (int x = 0; x < largura; x++)
            {
                int contador = 0;

                for (int ky = -half_kernel; ky <= half_kernel; ky++)
                {
                    for (int kx = -half_kernel; kx <= half_kernel; kx++)
                    {
                        int novo_x = x + kx;
                        int novo_y = y + ky;

                        if (novo_x >= 0 && novo_x < largura && novo_y >= 0 && novo_y < altura)
                        {
                            int indice = novo_y * largura + novo_x;
                            temp_pixels[contador++] = pixels[indice];
                        }
                    }
                }

                // Ordena os pixels temporários para encontrar o valor mediano
                qsort(temp_pixels, contador, sizeof(PixelRGB), comparar);

                // Atribui o valor mediano ao pixel atual
                int indice = y * largura + x;
                pixels[indice] = temp_pixels[contador / 2];
            }
        }

        free(temp_pixels);

        // Salva a nova imagem e atualiza a lista
        create_image_rgb(image, lista, filename_rgb);
        printf("\nMedian Blur aplicado.\n");

        char filename[50];
        strcpy(filename, filename_rgb);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_rgb, lista->tam);
        }

        push_pilha_rgb(lista, image, filename, "Aplicacao MEDIAN");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem RGB carregada para aplicar o Median Blur.\n");
    }
}

int compararg(const void *a, const void *b)
{
    return *(unsigned char *)a - *(unsigned char *)b;
}

void median_blur_gray(ImageGray *image, Lista *lista, char *filename_gray)
{
    if (lista->tam > 0)
    {
        int tamanho_kernel = 5; // Define o tamanho do kernel do median blur
        int largura = image->dim.largura;
        int altura = image->dim.altura;
        PixelGray *pixels = image->pixels;

        int half_kernel = tamanho_kernel / 2;
        PixelGray *temp_pixels = (PixelGray *)malloc(tamanho_kernel * tamanho_kernel * sizeof(PixelGray));

        if (!temp_pixels)
        {
            fprintf(stderr, "Erro ao alocar memória para pixels temporários.\n");
            return;
        }

        // Aplica o filtro de median blur
        for (int y = 0; y < altura; y++)
        {
            for (int x = 0; x < largura; x++)
            {
                int contador = 0;

                for (int ky = -half_kernel; ky <= half_kernel; ky++)
                {
                    for (int kx = -half_kernel; kx <= half_kernel; kx++)
                    {
                        int novo_x = x + kx;
                        int novo_y = y + ky;

                        if (novo_x >= 0 && novo_x < largura && novo_y >= 0 && novo_y < altura)
                        {
                            int indice = novo_y * largura + novo_x;
                            temp_pixels[contador++] = pixels[indice];
                        }
                    }
                }

                // Ordena os pixels temporários para encontrar o valor mediano
                qsort(temp_pixels, contador, sizeof(PixelGray), compararg);

                // Atribui o valor mediano ao pixel atual
                int indice = y * largura + x;
                pixels[indice] = temp_pixels[contador / 2];
            }
        }

        free(temp_pixels);

        // Atualiza a lista com a nova imagem
        create_image_gray(image, lista, filename_gray);
        printf("\nMedian Blur aplicado.\n");

        char filename[50];
        strcpy(filename, filename_gray);
        if (lista->cont > 0)
        {

            snprintf(filename, sizeof(filename), "%s%d", filename_gray, lista->tam);
        }

        push_pilha_gray(lista, image, filename, "Aplicacao MEDIAN");
    }
    else
    {
        fprintf(stderr, "\nNenhuma imagem em escala de cinza carregada para aplicar o Median Blur.\n");
    }
}

// Função para deletar arquivos temporários de texto

void remover_ultimo_lista(Lista *lista)
{
    if (lista->tam == 0)
    {
        printf("Lista vazia, não há elementos para remover.\n");
        return;
    }

    Elemento *ultimo = lista->fim;
    Elemento *anterior = ultimo->ant;

    if (anterior != NULL)
    {
        anterior->prox = NULL;
        lista->fim = anterior;
    }
    else
    {
        // Isso significa que estamos removendo o único elemento da lista
        lista->inicio = NULL;
        lista->fim = NULL;
    }

    free(ultimo);
    lista->tam--;
}

// void desfazer_alteracaogray(Lista *lista)
// {
//     char op;
//     Pilha *p = (Pilha *)malloc(sizeof(Pilha));
//     Elemento *atual = (Elemento *)malloc(sizeof(Elemento));

//     if (lista->tam > 1)
//     {
//         Pilha *aux = p;
//         p = p->prox;

//         // comparar os primeiros 100 pixels pra enconstrar o da pilha

//         printf("\nApagar %s (s/n)?", aux.->filename);
//         scanf("%c", &op);
//         getchar();
//         printf("Elemento %d do topo removido\n", aux->info);
//         free(aux);
//     }

//     // Obter o último elemento da lista de alterações
//     Elemento *ultimo = lista->fim;

//     printf("\nApagar %s (s/n)?", ultimo->filename);
//     scanf("%c", &op);
//     if (op == 's')
//     {
//         if (remove(ultimo->filename) == 0)
//         {
//             printf("Arquivo %s removido com sucesso.\n", ultimo->filename);
//         }
//         else
//         {
//             perror("Erro ao remover o arquivo");
//         }
//         remover_ultimo_lista(lista);
//         read_image_rgb(ultimo->filename);
//         call_python_script("image_utils.py", "image_gray_from_txt", ultimo->filename, "atual_gray.png");
//         printf("Alteração desfeita e imagem restaurada a partir de %s\n", ultimo->filename);
//     }
// }
// }

// void desfazer_alteracaorgb(Lista *lista)
// {
//     char op;
//     if (lista->tam == 1)
//     {
//         printf("Não há alterações para desfazer.\n");
//         return;
//     }
//     else
//     {

//         // Obter o último elemento da lista de alterações
//         Elemento *ultimo = lista->fim;

//         printf("\nApagar %s (s/n)?", ultimo->filename);
//         scanf("%c", &op);
//         if (op == 's')
//         {
//             if (remove(ultimo->filename) == 0)
//             {
//                 printf("Arquivo %s removido com sucesso.\n", ultimo->filename);
//             }
//             else
//             {
//                 perror("Erro ao remover o arquivo");
//             }
//             remover_ultimo_lista(lista);
//             read_image_rgb(ultimo->filename);
//             call_python_script("image_utils.py", "image_rgb_from_txt", ultimo->filename, "atual_rgb.png");
//             printf("Alteração desfeita e imagem restaurada a partir de %s\n", ultimo->filename);
//         }
//     }
// }

// Elemento *encontrar_elemento(Lista *lista, char *filename)
// {
//     if (lista->tam == 0)
//     {
//         printf("Lista vazia, não há elementos para encontrar.\n");
//         return NULL;
//     }

//     Elemento *atual = lista->inicio;

//     // Busca pelo nó com o filename especificado
//     while (atual != NULL && strcmp(atual->filename, filename) != 0)
//     {
//         atual = atual->prox;
//     }

//     if (atual == NULL)
//     {
//         printf("Elemento com filename '%s' não encontrado na lista.\n", filename);
//         return NULL;
//     }

//     // Retorna o ponteiro para o elemento encontrado
//     return atual;
// }
