/*-----------------------------------------------------------------
**
**  Fichero:
**    trafo.h  10/6/2014
**
**    Estructura de Computadores
**    Dpto. de Arquitectura de Computadores y Autom�tica
**    Facultad de Inform�tica. Universidad Complutense de Madrid
**
**  Prop�sito:
**    Contiene las implementaciones de las funciones en C
**    usadas por el programa principal
**
**  Notas de dise�o:
**
**---------------------------------------------------------------*/

#include "trafo.h"
#include "types.h"
#include "imgarm.h"

// COMPLETAR LAS FUNCIONES MARCADAS

/*
unsigned char rgb2gray(pixelRGB* pixel)
{
	return (3483*pixel->R + 11718*pixel->G + 1183*pixel->B) /16384;
}
*/

void RGB2GrayMatrix(pixelRGB orig[], unsigned char dest[], int nfilas, int ncols) {
    int i,j;

    for (i=0;i<nfilas;i++)
        for (j=0; j<ncols; j++)
            dest[i*ncols+j] = rgb2gray(&orig[i*ncols+j]);

}

/*
void apply_gaussian(unsigned char im1[], unsigned char im2[], int width, int height)
{
	// Los argumentos width y height indican respectivamente el numero de columnas y de filas de la imagen.
	int i,j;
	for (i=0 ; i < height; ++i)
		for (j=0 ; j < width; ++j)
			im2[i * width + j] = gaussian(im1, width, height, i, j);
}
*/

void apply_sobel(unsigned char im1[], unsigned char im2[], int width, int height)
{
	// Los argumentos width y height indican respectivamente el numero de columnas y de filas de la imagen.
	int i,j;
	for (i=0 ; i < height; ++i)
		for (j=0 ; j < width; ++j)
			im2[i * width + j] = sobel(im1, width, height, i, j);
}


//***********************************************************************************************************
void computeHistogram(unsigned char imagenGris[], short int histogram[], int N, int M) {

	// Inicializar histograma
	int i, j;
	for (i=0; i < 256; i++) {
		histogram[i]=0;
	}
	// Clasificar pixeles
	for (i=0; i < N; i++) {
		for (j=0; j < M; j++) {
			histogram[ imagenGris[i*M + j] ]++;
		}
	}

}

unsigned char computeThreshold(short int histogram[]) {
	short int max = -1, max2 = -1;
	int max_idx = -1, max2_idx = -1;

	int i;
	for (i=0; i<128; i++) {
		if (histogram[i] > max) {
			max = histogram[i];
			max_idx = i;
		}
	}
	for (i=128; i<255; i++) {
		if (histogram[i] > max2) {
			max2 = histogram[i];
			max2_idx = i;
		}
	}

	return max_idx + (max2_idx - max_idx)/2;
}
/*
void Gray2BinaryMatrix(unsigned char orig[], unsigned char dest[], unsigned char umbral, int nfilas, int ncols) {
	int i,j;

	for (i=0;i<nfilas;i++)
		for (j=0; j<ncols; j++)
			if (orig[i*ncols+j] < umbral)
				dest[i*ncols+j] = 0;
			else
				dest[i*ncols+j] = 255;
}
*/


