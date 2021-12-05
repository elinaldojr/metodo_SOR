#include "dependencias.h"
#include "biblioteca.h"

int main(void) {
	FILE *entrada, *matriz_saida;
	double LX, LY, DT, G, DX, DY, w, erro; 
	int NX, NY, n, N, f, m;
	double *d, *a, *b, *c, *x;

	entrada = fopen("entrada.txt", "r");

	//LX LY n DT G w f m
	fscanf(entrada, "%lf %lf %d %lf %lf %lf %d %d %lf", &LX, &LY, &n, &DT, &G, &w, &f, &m, &erro);

	printf("LX: %lf\n", LX); 
	printf("LY: %lf\n", LY);
	printf("n=NX=NY: %d\n", n);
	printf("DT: %lf\n", DT);  
	printf("G: %lf\n", G); 
	printf("w: %lf\n", w);
	printf("f: %d\n", f);
	printf("m: %d\n", m);
	printf("erro: %lf\n", erro);

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

	printf("\n");
	imprime_vetor(x, n);
	
	fclose(entrada);
	free(a);
	free(b);
	free(c);
	free(d);
	free(x);

  return 0;
}