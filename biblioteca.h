#ifndef BIBLIOTECA
#define BIBLIOTECA

//recebe a quantidade de elementos do vetor
double * aloca_vetor(int n){
	//aloca dinamicamente um vetor de double de tamanho n
	double *d = (double *) malloc(n*sizeof(double));
	return d;
}

//inicializa o vetor d
//recebe o tamanho do vetor e as variáveis f e m do problema
void inicializa_vetor_d(double *d, int N, int f, int m){
	int i;
	for(i=0; i<N; i++){
		//inicializa as posições do vetor d com o valor de f
		if( i != (N-1)/2 ) 
			d[i] = (double) f;
		//o elemento central do vetor d é inicializado com a diferença entre f e m
		else
			d[i] = (double) (f-m);
	}
}

//inicializa o vetor b
//recebe o tamanho e as variáveis DX e NX
void inicializa_vetor_b(double *b, int tam, double DX, int NX){
	int i;
	//inicializa todas as posições de b
	for(i=0; i<tam; i++){
		//se NÃO estiver na NX-ésima posição de b, inicializa com -1/(DX*DX)
		if( (i+1)%NX != 0 ) 
			b[i] = -1/(DX*DX);
		//se estiver na NX-ésima posição de b, inicializa com 0 (zero)
		else
			b[i] = 0;
	}
}

//inicializa o vetor c
//recebe o tamanho e as variáveis DY e NY
void inicializa_vetor_c(double *c, int tam, double DY){
	int i;
	//inicializa todas as poisções de c com -1/(DY*DY)
	for(i=0; i<tam; i++){
		c[i] = -1/(DY*DY);
	}
}

//inicializa o vetor a
//recebe as variáveis n, G e DT e os vetores b e c
void inicializa_vetor_a(double *a, int n, double G, double DT, double *b, double *c){
	int i, N, NX;
	NX = n;
	N = n*n;
	
	//inicializa o primeiro e o último elemento de a
  a[0] = G/DT + fabs(b[0]) + fabs(c[0]);
  a[N-1] = a[0];

	//inicializa NX-ésimo e (N-NX+1)-ésimo elementos de a
	a[NX-1] = a[0];
	a[N-NX] = a[0];

	for(i=1; i<N/2+1; i++){
		//inicializa a segunda linha até a (NX-1)-ésima e da (N-NX+2)-ésima até (N-1)-ésima linha de a
		if(i < NX-1){
			a[i] = G/DT + fabs(b[i-1]) + fabs(b[i]) + fabs(c[i]);
			a[N-i-1] = a[i];
		}
		//inicializa os demais elementos de a
		else if(i >= NX){
			a[i] = G/DT + fabs(b[i-1])+ fabs(b[i]) + 2*fabs(c[i]);
			a[N-i-1] = a[i];
		}
	}
}

//mostra os elementos de um vetor
//recebe o vetor e o seu tamanho
void imprime_vetor(double *vetor, int N){
	int i;
	for(i=0; i<N; i++){
		printf("%d %lf \n", i, vetor[i]);
	}
}

//escreve solução em um arquivo de saída
void escreve_saida(double *x, int tam, int repeticoes){
	int i;
	FILE *saida;

	saida = fopen("saida.txt", "w");

	if(!saida)
		return;

	fprintf(saida, "%d\n", repeticoes);
	for(i=0; i<tam; i++){
		fprintf(saida, "x[%d] = %lf\n", i, x[i]);
	}

	fclose(saida);
}

//método de Sobre-Relaxação Sucessiva
//recebe os vetores que formam a matriz e a variável n
double * SOR(double *a, double *b, double *c, double *d, int n, int w, double erro){
	int i, k, N, max_repeticoes = 100;
	double *x, max_e, xk, e, R;
	
	N = n*n;
	x = (double *) calloc(N, sizeof(double));

	for(k=0; k<max_repeticoes; k++){
		for(i=0; i<N; i++){
			xk = x[i];

			//começa a calcular o resíduo
			R = d[i] - xk*a[i];

			//primeira condição (c abaixo da diagonal principal)
			if(i >= n){
				R -= c[i-n]*x[i-n];
			}
			//segunda condição (b abaixo da diagonal principal)
			if(i%n != 0){
				R -= b[i-1]*x[i-1];
			}
			//terceira cndição (b acima da diagonal principal)
			if((i+1)%n != 0){
				R -= b[i]*x[i+1];
			}
			//quarta condição (c acima da diagonal principal)
			if(i < N-n){
				R -= c[i]*x[i+n];
			}

			//calcula o x1(k+1) -> x1(k+1) = x(k) + w/aii * R(k)
			x[i] = xk + (w/a[i])*R;

			//calcula o erro da primeira iteração de x(k)
			if(i == 0){
				max_e = fabs(xk - x[0]);
				e = max_e;
			}
			//calcula o erro das próximas iterações de x(k)
			else{
				e = fabs(xk - x[i]);
			}
			
			//verifica qual dos erros de x(k) é o maior
			if(max_e < e)
				max_e = e;
		}
		
		//caso o erro seja atingido para as iterações
		if(max_e <= erro){
			//escreve solução no arquivo de saída
			escreve_saida(x, N, k);
			return x;
		}
	}

	//escreve solução no arquivo de saída
	escreve_saida(x, N, k);
	return x;
}

#endif