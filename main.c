#include "dependencias.h"
#include "biblioteca.h"

int main(void) {
	FILE *entrada, *matriz_saida;
	double LX, LY, DT, G, DX, DY, erro; 
	int NX, NY, n, N, w, f, m;
	double *d, *a, *b, *c, *x;

	entrada = fopen("entrada.txt", "r");

	//LX LY n DT G w f m
	fscanf(entrada, "%lf %lf %d %lf %lf %d %d %d %lf", &LX, &LY, &n, &DT, &G, &w, &f, &m, &erro);
	NX = NY = n;
	N = NX*NY; //quantidade de linhas da matriz quadrada

	DX = LX/NX;
	DY = LY/NY;

	d = aloca_vetor(N); 
	inicializa_vetor_d(d, N, f, m);
	
	b = aloca_vetor(N-1);
	inicializa_vetor_b(b, N-1, DX, NX); 

	c = aloca_vetor(N-NY);
	inicializa_vetor_c(c, N-NY, DY); 
	
	a = aloca_vetor(N); 
	inicializa_vetor_a(a, n, G, DT, b, c);

	x = SOR(a, b, c, d, n, w, erro);

  return 0;
}