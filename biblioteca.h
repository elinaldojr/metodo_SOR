#ifndef BIBLIOTECA
#define BIBLIOTECA

double * aloca_vetor(int n){
	double *d = (double *) malloc(n*sizeof(double));
	return d;
}

void inicializa_vetor_d(double *d, int N, int f, int m){
	int i;
	for(i=0; i<N; i++){
		if( i != (N - 1)/2 )
			d[i] = (double) f;
		else
			d[i] = (double) (f-m);
	}
}

void inicializa_vetor_b(double *b, int tam, double D, int NX){
	int i;
	for(i=0; i<tam; i++){
		b[i] = -1/(D*D);
	}
	for(i=NX-1; i<tam; i+=NX){
		b[i] = 0;
	}
}

void inicializa_vetor_c(double *c, int tam, double D){
	int i;
	for(i=0; i<tam; i++){
		c[i] = -1/(D*D);
	}
}

void inicializa_vetor_a(double *a, int N, int NX, double G, double DT, double *b, double *c){
	int i;
	
	//inicializa primeiro e ultimo elemento da diagonal principal
  a[0] = G/DT + fabs(b[0]) + fabs(c[0]);
  a[N-1] = a[0];

	//inicializa NX-ésimo e (N-NX+1)-ésimo elementos da diagonal principal
	a[NX-1] = a[0];
	a[N-NX] = a[0];

  //inicializa da segunda até a (NX-1)-ésima e da (N-NX+2)-ésima até (N-1)-ésima linha da diagonal principal
	for(i=1; i<NX-1; i++){
		a[i] = G/DT + fabs(b[i-1]) + fabs(b[i]) + fabs(c[i]);
		a[N-i-1] = a[i];
	}

  //inicializa os demais elementos da diagonal principal
	for(i=NX; i<N/2+1; i++){
		a[i] += G/DT + fabs(b[i-1])+ fabs(b[i]) + 2*fabs(c[i]);
		a[N-i-1] = a[i];
	}
}

void imprime_vetor(double *d, int N){
	int i;
	for(i=0; i<N; i++){
		printf("%d %lf \n", i, d[i]);
	}
}

#endif