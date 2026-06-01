/*
	ALunos(a): Ana Beatriz Sousa Pires e Antônio Vinicius de Sousa Martins
	Loteria escolhida: Quina
	Descrição: Jogar 5 números de 01 a 80. 
*/

#include<stdio.h>
#include<locale.h>
#include<time.h>
#include<stdlib.h>


int  sortear(int,int);
void sortear_quina(int*);
void mostrar_quina(int*);
void ordenar(int*,int);
int eh_repetido(int,int*,int);
int contar_acertos(int*, int*);


int
main() {
	
	int n;
	
	setlocale(LC_ALL, "Portuguese");
	printf("Quantos jogos você quer jogar? \n");
	scanf("%d", &n);
	
	printf("Estou sorteando = %d jogos!\n", n);

	srand(time(NULL));

	int j, jogos[n][5]={};
	
	for (j=0; j < n; ++j) {
		sortear_quina(jogos[j]);
		ordenar(jogos[j], 5);
		mostrar_quina(jogos[j]);
	}

	int vencedor[5];

   sortear_quina(vencedor);
   ordenar(vencedor,5);

   for(j = 0; j < n; j++) {
	int acertos;

	acertos = contar_acertos(jogos[j], vencedor);

	printf("Jogo %d: %d acertos\n", j + 1, acertos);

	if(acertos == 5) {
		printf(" - PARABÉNS, VC GANHOU  A QUINA!");
	}

	printf("\n");
}
	return 0;
}


/*	Sortea número de A a B */
int
sortear(int a, int b) {
  const int range = b - a + 1;
  int n;

	do {
		n = rand();
	} while (n >= (RAND_MAX - RAND_MAX % range));
	
	return n % range + a;
}


void
sortear_quina(int* jogo) {
	const int N = 5;
	int i;
	for (i=0; i < N; ++i)
		do jogo[i] = sortear(1,80);
		while ( eh_repetido(jogo[i], jogo, i) );
}


void
ordenar(int *lista, int n)
{
	int j, i, i_min=0, aux;

	for (j=0; j < n; ++j) {
		i_min = j;
		
		for (i=j; i < n; ++i) {
			if (lista[i] < lista[i_min])
				i_min = i;
		}
		
		aux = lista[j];
		lista[j] = lista[i_min];
		lista[i_min] = aux;
	}
}


void
mostrar_quina(int *lista)
{
	const int N=5;
	int i;
	for (i=0; i < N; ++i)
		printf("%02d%c", lista[i], (i != N-1) ? '-' : '\n');
}

int
eh_repetido(int n, int *lista, int index)
{
	int i;
	for (i=0; i < index; ++i)
		if (n == lista[i])
			return 1;
	return 0;
}

int
contar_acertos(int *jogo, int *ganhador) // func p contar acertos 
{
	int i, j;
	int acertos = 0;
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			if(jogo[i] == ganhador[j])
			{
				acertos++;
			}
		}
	}
	return acertos;
}
