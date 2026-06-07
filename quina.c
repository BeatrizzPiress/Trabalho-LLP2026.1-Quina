/*
	ALunos(a): Ana Beatriz Sousa Pires e Antônio Vinicius de Sousa Martins
	Loteria escolhida: Quina
	Descrição: Jogar 5 números de 01 a 80, gera apostas da Quina, salva os jogos em arquivo,
	lê os jogos gravados e verifica os acertos a partir da sequência
	ganhadora informada pelo usuário.

	Repositório GitHub:
	https://github.com/BeatrizzPiress/Trabalho-LLP2026.1-Quina
*/

#include<stdio.h>
#include<locale.h>
#include<time.h>
#include<stdlib.h>

#define MAX (int)(3e5)

int  sortear(int,int);
void sortear_quina(int*);
void mostrar_quina(int*);
void mostrar_quina_acertos(int*,int* premio);
void ordenar(int*,int);
int eh_repetido(int,int*,int);
int contar_acertos(int*, int*);
int salvar_jogo(int*,FILE*);
int ler_arquivo(int jogos_lidos[][5]);


void sortear_salvar(int n, int jogos[][5], FILE*);
int ler(int jogos[][5]);
void verificar(int quinas[][5]);

int
main() {
	
	int n, escolha, jogos[MAX][5];  // sem usar malloc
	FILE *arq;
	
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));

	puts(
		"[ 1 ] Sortear e Salvar\n"
		"[ 2 ] Ler\n"
		"[ 3 ] Verificar\n"
		"[ 0 ] Sair");
	do {
		printf("--> ");
		scanf("%d", &escolha);
		switch (escolha) {
			case 1: {
				puts("--- Sorteando ---");
				printf("Quantos jogos você quer jogar? \n");
				scanf("%d", &n);
				sortear_salvar(n, jogos, arq);
				break;
			}
			case 2:
				puts("--- Lendo ---");
				n = ler(jogos);
				break;
			case 3:
				puts("--- Verificando ---");
				break;
			case 0:
				break;
			default:
				puts("Desulpa. Não entendi.");
		}
	} while (escolha != 0);

	printf("Peguei N: %d\n", n);
	//exit(0);


    int j,vencedor[5];
    

    printf("\nDigite os 5 numeros da sequencia ganhadora (ex: 01-10-25-35-70): ");

    scanf("%d-%d-%d-%d-%d",
	 &vencedor[0],
	 &vencedor[1],
	 &vencedor[2],
	 &vencedor[3],
	 &vencedor[4]);

    ordenar(vencedor,5);

    printf("Premiado: ");
    mostrar_quina(vencedor);

    for(j = 0; j < n; j++) {
	int acertos;

	/*
	acertos = contar_acertos(jogos_lidos[j], vencedor);

	 printf("Jogo %d: %d acertos | ", j + 1, acertos);
	 mostrar_quina_acertos(jogos_lidos[j], vencedor);

	if(acertos == 5) {
	 	printf(" - PARABÉNS, VC GANHOU A QUINA!");
	}
	*/
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

void
mostrar_quina_acertos(int *lista, int *premio)
{
	const int N=5;
	const char normal[]="\033[m", destaque[]="\033[42;30m";
	int i;
	for (i=0; i < N; ++i)
		printf("%s%02d%s%c", (lista[i] == premio[i]) ? destaque : normal, lista[i], normal, (i != N-1) ? '-' : '\n');
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

int
salvar_jogo(int *jogo, FILE *arq)
{
	const int N=5;
	int i;
	for (i = 0; i < N; ++i)
		fprintf(arq, "%02d%c", jogo[i], (i < N-1) ? '-' : '\n');
	return 0;
}

int
ler_arquivo(int jogos_lidos[][5])
{
	FILE *arq;
	int qtd = 0;

	arq = fopen("dados.txt", "r");

	if(arq == NULL)
	{
		printf("Erro ao abrir arquivo!\n");
		return 0;
	}

	while(fscanf(arq,
		"%d-%d-%d-%d-%d",
		&jogos_lidos[qtd][0],
		&jogos_lidos[qtd][1],
		&jogos_lidos[qtd][2],
		&jogos_lidos[qtd][3],
		&jogos_lidos[qtd][4]) == 5)
	{
		qtd++;
	}

	fclose(arq);

	return qtd;
}


void
sortear_salvar(int n, int jogos[][5], FILE *arq)
{
	int j;

	printf("Estou sorteando = %d jogos!\n", n);

	if (! (arq=fopen("dados.txt", "w")) )
		puts("Error ao abrir arquivo.");

	
	for (j=0; j < n; ++j) {
		sortear_quina(jogos[j]);
		ordenar(jogos[j], 5);
		mostrar_quina(jogos[j]);
		salvar_jogo(jogos[j], arq);
	}
	
	fclose(arq);
}


int ler(int jogos_lidos[][5])
{
    int j, n;

    n = ler_arquivo(jogos_lidos);
    printf("\nJogos lidos do arquivo:\n");

    for(j = 0; j < n; j++)
  {
	 mostrar_quina(jogos_lidos[j]);
  }

  return n;
}

