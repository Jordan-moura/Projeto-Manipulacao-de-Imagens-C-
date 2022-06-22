#include <stdio.h>
#include <stdlib.h>
// Struct
typedef struct info_s
{
    char tipo[3];
    int num_col;
    int num_lin;
    int num_MAX;
    int *mat_img;
}info;
// Prototipos
void limiarizacao(info Imagem);
void negativasso(info Imagem);
void histograma(info Imagem);
// Principal
int main()
{   ////////// Criando uma imagem principal
    FILE *img_pri;
    info Imagem;
    img_pri = fopen("macaco.pgm", "r");
    //////////  Verificando se abriu o codigo
    if(img_pri == NULL)
        printf("Nao acessado o pricipal.");

    /////////  Lendo os valores no arquivo principal
    fscanf(img_pri, " %s %d %d %d", &Imagem.tipo, &Imagem.num_lin, &Imagem.num_col, &Imagem.num_MAX);
    Imagem.mat_img = (int*)(malloc(Imagem.num_lin * Imagem.num_col * sizeof(Imagem.mat_img)));
    for(int i=0; i<Imagem.num_lin * Imagem.num_col; i++)
        fscanf(img_pri, "%d ", &Imagem.mat_img[i]);
    //////// Chamando todas as funçoes
    limiarizacao(Imagem);
    negativasso(Imagem);
    histograma(Imagem);
    free(Imagem.mat_img);
    return 0;
}
// Funçoes
// LIMIARIZAÇAO
void limiarizacao(info Imagem)
{
    FILE *limi;
    //// Abrindo o arquivo para escrever dentro
    limi = fopen("Limiarizacao.pgm", "w");
    if(limi == NULL)
        printf("Nao acessado o de limi");

    fprintf(limi, "%s\n", Imagem.tipo);
    fprintf(limi, "%d ", Imagem.num_col);
    fprintf(limi, "%d\n", Imagem.num_lin);
    fprintf(limi, "%d\n", Imagem.num_MAX);
    for(int i=0; i<Imagem.num_lin; i++)
    {
        for(int j=0; j<Imagem.num_col; j++)
        {
            if(Imagem.mat_img[i*Imagem.num_col + j] >= 150)
                fprintf(limi, "%d ", 255);
            else
                fprintf(limi, "%d ", 0);
        }
        fprintf(limi, "\n");
    }
    fclose(limi);
}
// NEGATIVO
void negativasso(info Imagem)
{
    FILE *neg;
    neg = fopen("negativo.pgm", "w");

    if(neg == NULL)
        printf("Nao acessado o de negativo");

    fprintf(neg, "%s\n", Imagem.tipo);
    fprintf(neg, "%d ", Imagem.num_col);
    fprintf(neg, "%d\n", Imagem.num_lin);
    fprintf(neg, "%d\n", Imagem.num_MAX);
    for(int i=0; i<Imagem.num_lin; i++)
    {
        for(int j=0; j<Imagem.num_col; j++)
            fprintf(neg, "%d ", 255 - Imagem.mat_img[i*Imagem.num_col + j]);
        fprintf(neg, "\n");
    }
    fclose(neg);
}
// HISTOGRAMA
void histograma(info Imagem)
{
    FILE *hist;
    hist = fopen("histograma.txt", "w");
    int tons[255] = {0};

    if(hist == NULL)
    printf("Nao acessado o de histograma");

    for(int i=0; i<Imagem.num_lin; i++)
    {
        for(int j=0; j<Imagem.num_col; j++)
            tons[Imagem.mat_img[i*Imagem.num_col + j]]+=1;
    }

    for(int i=0; i<=255; i++)
        fprintf(hist, "Tonalidade nivel %d: %d\n", i, tons[i]);

    fclose(hist);
}

