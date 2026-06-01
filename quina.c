/*
	ALunos(a): Ana Beatriz Sousa Pires e Antônio Vinicius de Sousa Martins
	Loteria escolhida: Quina
	Descrição: Jogar 5 números de 01 a 80. 
*/

#include<stdio.h>
#include<locale.h>

main() {
	
	int n;
	
	setlocale(LC_ALL, "Portuguese");
	printf("Quantos jogos você quer jogar? \n");
	scanf("%d", &n);
	
	printf("Estou sorteando = %d jogos! ", n);
}
