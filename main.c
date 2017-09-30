#include <stdio.h>
#include "trafo.h"
#include "types.h"
#include "time.h"
#include "lena512color.h"

// Comentar esta linea para NO usar como entrada

// la imagen de LENA
#define LENA

#ifdef LENA
#define N 512
#define M 512
pixelRGB* imagenRGB;
#else
#define N 512
#define M 512
pixelRGB imagenRGB[N*M];
#endif

unsigned char imagenGris[N*M];
unsigned char imagenGauss[N*M];
unsigned char imagenSobel[N*M];

unsigned char imagenBinaria[N*M]; //*

#ifndef LENA
void initRGB(int nfilas, int ncols)
{
    int i,j;

    for (i=0;i<nfilas;i++)
        for (j=0; j<ncols; j++) {
        	imagenRGB[i*ncols+j].R = (i+j)%256;
        	imagenRGB[i*ncols+j].G = (i+j)%256;
        	imagenRGB[i*ncols+j].B = (i+j)%256;
        }
}
#else
void initRGB(int nfilas, int ncols)
{
    imagenRGB = (pixelRGB*) imageLena512;
}
#endif

typedef struct _maximo_t {
	int columna;
	unsigned char valor;
} maximo;
maximo imagenMax[N];

int main() {
	// short int histograma[256]; //*

	short int time = 0;
    timer_init();
    initRGB(N,M);
    timer_start();
    RGB2GrayMatrix(imagenRGB, imagenGris,N,M);
    apply_gaussian(imagenGris, imagenGauss, N, M);
    apply_sobel(imagenGauss, imagenSobel, N, M);

    // Parte avanzada
    MaximoGris(imagenGris,N,M,imagenMax);

    //* Pasa la imagen gris a binaria
    // computeHistogram(imagenGris,histograma,N,M);
    // unsigned char threshold = computeThreshold(histograma);
    // Gray2BinaryMatrix(imagenGris,imagenBinaria,threshold,N,M);
    //* Pasa la imagen gris a binaria con un umbral predefinido
    Gray2BinaryMatrix(imagenGris,imagenBinaria,127,N,M);


    time = timer_stop();
    return 0;
}
