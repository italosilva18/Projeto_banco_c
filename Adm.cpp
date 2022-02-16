#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include<string.h>



int menu();
void logar();
void adcionar();
int  code = 1234;

int main(){
	setlocale(LC_ALL,"");
	int recurso,i;
	logar();
	
	do{
	
	switch(menu()){
		case 1: 
		do{
		adcionar();
		printf("\nQuer criar mais uma conta?\n1 para sim...\n");
		scanf("%d",&recurso);
		}while(recurso == 1);
		break;
		case 2:
			printf("Saindo...");
			exit(0);
			break;
		default:printf("Nenhuma opção selecionada\n");
	
		
	}	
	printf("Deseja realizar mais operações?\n Digite 1 para sim ou outra tecla pra sair\n");
	scanf("%d",&recurso);
	}	while(recurso == 1);
		return 0;
}

int menu(){ 
	char select; 
	printf("\n\nUsuário:\nAdmin\n");
	printf("Suas opções: \n");
	printf("1 - Adcionar novo cliente\n");
	printf("2 - sair\n");
	printf("Qual sua escolha?\n");
	select = getch();
	return atoi(&select);
	
}

void logar(){
	int password;
	printf("\nSeja bem vindo ao IBANK \n");
    printf("O MELHOR DO BRASIL\n");
	printf("\n\ndigite senha para efetuar LOGIN\n\n");
	
	scanf("%d",&password);
	for(int i=0;i<5;i++){
	if(password != code){
	printf("conta não encontrada");
	exit(0);
		}
	}
				
}

void adcionar(){
	FILE *fileArquivo;

 char szBuffer[1024];


 char nome[500]; 
 int agencia;
 int conta;
 int senha;
 float saldo;
 
 printf("Programa de cadastro de pessoas \n");
 printf("Digite o nome :");
 scanf("%s",&nome);
 printf("Digite a agencia :");
 scanf("%d",&agencia);
 printf("Digite a conta :");
 scanf("%d",&conta);
 printf("Digite a senha :");
 scanf("%d",&senha);
 printf("Digite o saldo :");
 scanf("%f",&saldo);

	snprintf(szBuffer, sizeof (szBuffer),"%d_%d.txt",agencia,conta);
	fileArquivo = fopen(szBuffer,"w");
	if(fileArquivo == NULL){
		printf("Erro no arquivo\n\n");
		exit(0);
	}
	
	fprintf(fileArquivo,"%s\n%i\n%i\n%.2f\n%i",nome,agencia,conta,saldo,senha);
	fclose(fileArquivo);
}








