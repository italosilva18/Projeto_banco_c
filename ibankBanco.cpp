#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include <conio.h>
#include<string.h>

FILE *arquivoAtual;
FILE *extrato;
FILE *arquivoOutro;

void menu();
void logar();
void saque();
void transferencia();
void credito();
float saldo;
int contaLOG, agenciaLOG,senhaLOG,agencia,conta,senha,indice,escolha;
char szBuffer[1024],szbuff[1024],nome[30];



int main(){
	setlocale(LC_ALL,"");	
    int tentativas = 0;
    int repete;
    
        logar();
            do{
            
           	menu();
           	scanf("%i",&escolha);
			switch(escolha){
                case 1:
                    do{	repete = 0;
                        saque();
                        printf("\nDeseja Realizar outro Saque? Digite 1 se quiser repetir.\n");
                        scanf("%i",&repete);
                    }while(repete == 1);
                    break;
                case 2:
                	arquivoAtual = fopen(szBuffer,"r");
                    fscanf(arquivoAtual, "%s %i %i %f %i",&nome,&conta,&agencia,&saldo,&senha);
					printf("\nSaldo: %.2f\n\n",saldo);
					fclose(arquivoAtual);
                    break;
                case 3:	
                    do{
                        transferencia();
                        printf("\nDeseja Realizar outra Transferencia? Digite 1 se quiser repetir.\n");
                        scanf("%i",&repete);
                    }while(repete == 1);
                    break;
                case 4:
                	char tudo[100];
					extrato = fopen(szbuff,"r");
                	while(fgets(tudo,80,extrato) != NULL){
                		printf("%s",tudo);
                		}
                		fclose(extrato);
                		break;
                		
				case 5: do{
				credito();	
				printf("\nDeseja realizar outro crédito? 1 para sim.\n");
				scanf("%i",&repete);	
				}while(repete == 1);
				break;		
				case 0:
				printf("Obrigado por utilizar nossos serviços.\n");
				exit(0);
                    break;
                default:
                    printf("\nEscolha incorreta!!!");
            }
    		printf("\nDeseja voltar ao menu? Se sim digite 1...\n");
    		scanf("%i",&repete);
        	}while(repete == 1);
       	printf("\nObrigado por usar nossos serviços");
             return 0;
        }
     





void menu(){
	system("cls");
    arquivoAtual = fopen(szBuffer,"r+");
    fscanf(arquivoAtual, "%s %i %i %f %i",&nome,&agencia,&conta,&saldo,&senha);

    printf("\nSeja bem vindo ao IBANK \n");
    printf("O MELHOR DO BRASIL\n");
	printf("\n\ndigite seu usuario e senha para efetuar LOGIN\n\n");

    printf("\nUsuário: %s",nome);
    printf("\nSuas opções:");
    printf("\n1 - Saque");
    printf("\n2 - Saldo");
    printf("\n3 - Transferência");
    printf("\n4 - Extrato");
    printf("\n5 - crédito");
    printf("\n0 - Sair");
    printf("\nEscolha: \n");
    fclose(arquivoAtual);
    fclose(extrato);
  	
}

void logar(){
	
    printf("\nSeja bem vindo ao sistema bancario!\n");
    printf("\nDigite sua agencia:\n");
    scanf("%i",&agenciaLOG);
    printf("\nDigite sua conta:\n");
    scanf("%i",&contaLOG);
    printf("\nDigite sua Senha:\n");
    scanf("%d",&senhaLOG);
    snprintf(szBuffer,sizeof(szBuffer),"%i_%i.txt",agenciaLOG,contaLOG);
    snprintf(szbuff,sizeof(szbuff),"extrato_%d_%d.txt",agenciaLOG,contaLOG);
	arquivoAtual = fopen(szBuffer,"r");
	if(arquivoAtual == NULL){
    	printf("Conta não existe.\n");  
    	system("PAUSE");
    	exit(0);
	}
	fscanf(arquivoAtual,"%s %i %i %f %i",&nome,&agencia,&conta,&saldo,&senha);	   
    if(contaLOG != conta && agenciaLOG != agencia){
	printf("Conta inexistente!");
	exit(0);
	}       
	if(senhaLOG != senha){
		printf("Senha incorreta.");
		system("PAUSE");
		exit(0);
	}		
	extrato = fopen(szbuff,"a+");         
	
	fprintf(extrato,"\nExtrato de sua Conta:\n\n");
	fprintf(extrato,"Nome:%s\nAgencia:%d\nConta:%d\nSaldo:%.2f\n%d\n",nome,agencia,conta,saldo,senha);
	fputs(__DATE__"--"__TIME__"\n\n",extrato);
	
	fclose(extrato);
	fclose(arquivoAtual);
	
	}
	
	

void saque(){
	system("cls");
	float valor_sq;
    printf("\nDigite o Valor que deseja sacar:\n");
    scanf("%f", &valor_sq);
	arquivoAtual = fopen(szBuffer,"w+");
	extrato = fopen(szbuff,"a");
    fscanf(arquivoAtual, "%s %i %i %f %i",&nome,&conta,&agencia,&saldo,&senha);
    if(valor_sq > saldo){
        printf("\nSeu Saldo é insuficiente!!!\n Tente outros valores.\n");
    }else{
        saldo = saldo - valor_sq;
        printf("Saque efetuado com sucesso!");
        fprintf(arquivoAtual,"%s\n%i\n%i\n%.2f\n%i ",nome,agencia,conta,saldo,senha);
        fprintf(extrato,"\nSaque efetuado no valor de: %.2f\nSaldo atual: %.2f\n",valor_sq,saldo);
        fputs(__DATE__"--"__TIME__"\n\n",extrato);
    }
    fclose(arquivoAtual);
	fclose(extrato);	
}
 
void transferencia(){
	system("cls");
	
	char bufferoutro[1024],nomeoutro[30];	
	float valor_tr = 0,saldooutro;
    int conta_tr, agencia_tr,agenciaoutro,contaoutro,senhaoutro;
    int erro = 0;
    extrato = fopen(szbuff,"a");
 	arquivoAtual = fopen(szBuffer,"w+");
    fscanf(arquivoAtual,"%s %i %i %f %i",&nome,&conta,&agencia,&saldo,&senha);
    do{
    printf("\nDigite a Agencia destino:");
    scanf("%d",&agencia_tr);
    printf("\nDigite a Conta destino:");
    scanf("%d",&conta_tr);
    printf("\nDigite o Valor:");
    scanf("%f",&valor_tr);
    snprintf(bufferoutro,sizeof(bufferoutro),"%d_%d.txt",agencia_tr,conta_tr);
    arquivoOutro = fopen(bufferoutro,"r");
	if(arquivoOutro == NULL){
    	printf("Conta não existe.");
    	exit(0);
	}
	else if(conta == conta_tr){
        printf("Conta do próprio usuário, por favor digite a ag e conta de outrem...");
        erro += 1;
    	}
		if(erro>=3){
    	printf("Deixe de ser burro!!!");
    	exit(0);
		}        	
	}while(conta == conta_tr);    
	if(valor_tr > saldo){
        printf("\nSeu Saldo é insuficiente!!!");
        exit(0);
    }	
    	fscanf(arquivoOutro,"%s %i %i %f %i",&nomeoutro,&contaoutro,&agenciaoutro,&saldooutro,&senhaoutro);
        saldo = saldo - valor_tr;
        saldooutro = saldooutro + valor_tr;
		fclose(arquivoOutro);
		arquivoOutro = fopen(bufferoutro,"w"); 
		printf("\nTransferencia realizada com Sucesso!");
        printf("\nFavorecido: %s",nomeoutro);
        printf("\nNo valor de R$ %.2f",valor_tr);
        	
		fprintf(arquivoAtual,"%s\n%d\n%d\n%.2f\n%i",nome,agencia,conta,saldo,senha);
		fprintf(arquivoOutro,"%s\n%d\n%d\n%.2f\n%i",nomeoutro,agenciaoutro,contaoutro,saldooutro,senhaoutro);
		fprintf(extrato,"\nTransferencia realizada no valor de: %.2f\n",valor_tr);
		fputs(__DATE__"--"__TIME__"\n\n",extrato);
		fclose(arquivoAtual);
		fclose(arquivoOutro);
		fclose(extrato);		        
}
   
void credito(){
	float credv;
	system("cls");
	printf("\nDigite o valor que deseja creditar: \n");
	scanf("%f",&credv);
	arquivoAtual = fopen(szBuffer,"w+");
	extrato = fopen(szbuff,"w");
	fscanf(arquivoAtual,"%s %i %i %f %i",&nome,&agencia,&conta,&saldo,&senha);
	saldo += credv;
	printf("Crédito efetuado com sucesso!");
	fprintf(arquivoAtual,"%s\n%i\n%i\n%.2f\n%i",nome,agencia,conta,saldo,senha);
	fprintf(extrato,"Houve um crédito na sua conta no valor de: %.2f\n",credv);
	fputs(__DATE__"--"__TIME__"\n\n",extrato);
	fclose(arquivoAtual);
	fclose(extrato);	
}    
    
    
    
    
    
    
    
    
    
    
    
    
