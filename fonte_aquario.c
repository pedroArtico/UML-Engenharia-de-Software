#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int login (int x, int y);
void bloquear_cartao ();
int escolher_conta ();
int escolher_operacao ();
void extrato ();
void deposito (int indice_conta, float x, int nro_conta);
int saque (int conta, float x);
int transferencia (int origem, int destino, float x);

int tipo_conta;
int CONTA;
int a=0;
FILE *ex;

struct usuario {
	int conta;
	int senha;
	float saldoC;
	float saldoP;
	char nome[50]; 
};
struct usuario pessoa[4];
	
int main() 
{
	int a, b, c, i, k, f, s, d=0, y, n, e;
	int dest=(-1);
	float j;
	
	pessoa[0].conta=873982;
	pessoa[1].conta=223912;
	pessoa[2].conta=173234;
	pessoa[3].conta=185514;
	pessoa[0].senha=171204;
	pessoa[1].senha=172356;
	pessoa[2].senha=177455;
	pessoa[3].senha=182787;
	pessoa[0].saldoC=1200;
	pessoa[1].saldoC=4890;
	pessoa[2].saldoC=7367;
	pessoa[3].saldoC=2365;
	pessoa[0].saldoP=3256;
	pessoa[1].saldoP=300;
	pessoa[2].saldoP=0;
	pessoa[3].saldoP=2960;
	strcpy(pessoa[0].nome,"Felipe Silva do Nascimento");
	strcpy(pessoa[1].nome,"Gabriel Paulo Turato");
	strcpy(pessoa[2].nome,"Kaique Chiovetto Siqueira");
	strcpy(pessoa[3].nome,"Lucca Di Bastiani do Amaral");
	int agencia =1234;
	
	ex = fopen("ex.txt", "w");
		if(ex == NULL){
       		printf("erro");
        	exit(0);
    	}
    	rewind(ex);
    	fclose(ex);	
    l:	
	printf ("Entre com o numero da sua agencia\n");
	scanf ("%d", &a);
	if (a != 1234) {
		printf("Agencia invalida.\n");
		goto l;
	}
	novamente:
	printf ("Entre com o numero da sua conta\n");
	scanf ("%d", &b);
	printf ("Entre com sua senha\n");
	scanf (" %d", &c);
    CONTA = login (b, c);
     if((CONTA > (-3)) && (CONTA < 0)){
     	goto novamente;
	 }
	 if(CONTA == (-3)){
	 	bloquear_cartao ();
	 }
	escolha_operacao:
	tipo_conta = escolher_conta();
	i=escolher_operacao ();
	if(i==1) {
		escolher_deposito:
		printf ("Digite o numero da conta de destino: \n");
		scanf("%d", &a);
		valor_deposito:
		printf ("Digite o valor a ser depositado.\n");
		scanf("%f", &j);
		if (j<=0) {
			printf("Entre com um valor valido para deposito.\n");
			goto valor_deposito;
		}
		for (c=0;c<4;c++) {
			if ((pessoa[c].conta) != a) {
				d++;
			}
		}
		if (d==4) {
			printf("Conta invalida, favor digitar uma conta valida.\n\n");
			goto escolher_deposito;
			d=0;
		}
		else {
		for (c=0;c<4;c++) {
			if (pessoa[c].conta == a) {
				f=c;
			}
		}
		deposito (f, j, a);
		}
	}
	if(i==2) {
		printf ("Digite o valor a ser sacado.\n");
		scanf("%f", &j);
		s=saque (CONTA, j);
		if (s==-1){
			printf("Saldo insuficiente para realizar esta operacao.\n");
	    }
	    if (s==1) {
		   printf("Operacao realizada com sucesso !\n");
	   }
	}
	if (i==3) {
		conta:
		printf("Digite a conta de destino: \n");
		scanf("%d" ,&a);
		
		for (y=0;y<4;y++) {
		  if(a == pessoa[y].conta)  {
			dest = y;
		  }
	   }
	    if(dest == -1){
           printf("Conta de destino invalida.\n");
           goto conta;
		}
				
		printf("Digite o valor a ser transferido.\n");
		scanf("%f", &j);
		k=transferencia (CONTA, dest, j);
		if(k<0) {
			printf("Saldo insuficiente para realizar essa operacao.\n");
		}
		if(k==1){
		 printf("Operacao realizada com sucesso !\n");
		}
	}
	if(i==4) {
		extrato ();
	}
	escolher_tarefa:
	printf("Se deseja realizar outra operacao digite 1, caso contrario digite 2.\n");
	scanf("%d",&n);

	if(n==1 || n==2) {
		if(n==1){
	 	 goto escolha_operacao;
		}
		if(n==2) {
			return 0;
		}
	}
	else {
		printf("Opcao invalida, digite novamente.\n\n");
    	goto escolher_tarefa;
    }

	if(n==1){
		system ("cls");
		goto escolha_operacao;
	}
	else {
    	system ("pause");
	}
}

int login (int x, int y) { //arrumar pro caso da pessoa acertar na 3ª tentativa
	int j, m=0, k;
	for (j=0;j<4;j++) {
		if ((x==pessoa[j].conta) && (y==pessoa[j].senha)) {
			k=j;
			m = 1;
		}
	}
	if (m==1) {
		return k;
	}
	else {
		 a += (-1);
		 return a;
		}
}

void bloquear_cartao () { //arrumar
	printf ("Sua conta foi bloqueada por exceder o limite de tentativas de login, favor entrar em contato com o banco.\n");
	//sistem("pause");
}

int escolher_conta () {
	int x;
	again:
	printf("Digite 1 para conta corrente e 2 para conta poupanca.\n");
	scanf("%d", &x);
	if(x==1 || x==2) {
		if(x==1) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else {
		printf("Opcao invalida.\n");
		goto again;
	}
}

int escolher_operacao () {
	int x;
	novamente:
	printf("Escolha a operacao a ser realizada:\n1.Deposito\n2.Saque\n3.Transferencia\n4.Extrato\n\n");
	scanf("%d", &x);
	if((x==1) || (x==2) || (x==3) || (x==4) ){
		return x;
	}
	else{
	  printf("Opcao invalida, escolha novamente a operaca a ser realizada: \n");
	  goto novamente;
	}
}

void deposito (int indice_conta, float x, int nro_conta) { //funcionando
	if(tipo_conta==1) {
		(pessoa[indice_conta].saldoC) += x;
		printf("Operacao Realizado com sucesso!\n");
		ex = fopen("ex.txt", "a");
		if(ex == NULL){
       		printf("erro");
        	exit(0);
    	}
    	rewind(ex);
    	fprintf (ex, "Deposito no valor de: %.2f na conta corrente %d \n", x, nro_conta);
    	fclose(ex);
	}
   
	else {
		(pessoa[indice_conta].saldoP) += x;
		printf("Operacao Realizado com sucesso!\n");
		ex = fopen("ex.txt", "a");
			if(ex == NULL){
       			printf("erro");
        		exit(0);
    		}
    		rewind(ex);
    	fprintf (ex, "Deposito no valor de: %.2f na conta poupanca %d \n", x, nro_conta);
    	fclose(ex);
   }
}

int saque (int conta, float x) {  //funcionando
	if(tipo_conta==1) {
		if ((pessoa[conta].saldoC)-x < -1000) {
			return -1;
		}
		else {
			pessoa[conta].saldoC -= x;

			printf("Saque na conta corrente no valor de: %.2f\n", pessoa[conta].saldoC);

			printf("Seu saldo atual e de %.2f\n", pessoa[conta].saldoC);

			ex = fopen("ex.txt", "a");
			if(ex == NULL){
       			printf("erro");
        		exit(0);
    		}
    		rewind(ex);
    		fprintf (ex, "Saque na conta corrente no valor de: %.2f\n", x);
    		fclose(ex); 
			return 1;
		}
	}
	if(tipo_conta==2) {
		if ((pessoa[conta].saldoP)-x < 0) {
			return -1;
		}
		else {
			pessoa[conta].saldoP -= x;
			printf("%.2f\n", pessoa[conta].saldoP);
			ex = fopen("ex.txt", "a");
			if(ex == NULL){
       			printf("erro");
        		exit(0);
    		}
    		rewind(ex);
    		fprintf (ex, "Saque na conta poupanca no valor de: %.2f\n", x);
    		fclose(ex); 
    		return 1;
 		}
	}
}

int transferencia (int origem, int destino, float x) {
	if(tipo_conta==1) {
		if ((pessoa[origem].saldoC)-x < -1000) {
			return -1;
		}
		else {
			(pessoa[origem].saldoC) -= x;
			(pessoa[destino].saldoC) += x;	
			ex = fopen("ex.txt", "a");
			if(ex == NULL){
       			printf("erro");
        		exit(0);
    		}
    		rewind(ex);
    		fprintf (ex, "Transferencia da conta corrente no valor de: %.2f na conta %d\n", x, destino);
    		fclose(ex); 
			
			return 1;
		}
	}
	else {
		if ((pessoa[origem].saldoP)-x < 0) {
			return -1;
		}
		else {
			(pessoa[origem].saldoP) -= x;
			(pessoa[destino].saldoC) += x;
			ex = fopen("ex.txt", "a");
			if(ex == NULL){
       			printf("erro");
        		exit(0);
    		}
    		rewind(ex);
    		fprintf (ex, "Tranferencia da conta poupanca no valor de: %.2f na conta %d\n", x, destino);
    		fclose(ex); 
			return 1;
		}
	}
}

void extrato () {
	char ler[1000];
	printf("\nSaldo da conta corrente:");
	printf("%.2f\n", pessoa[CONTA].saldoC);
	printf("\nSaldo da conta poupanca:");
	printf("%.2f\n", pessoa[CONTA].saldoP);
	 ex = fopen("ex.txt", "rt");
     if(ex == NULL){
     printf("erro");
     exit(0);
    }
     rewind(ex);           
     while(fgets(ler, 100,ex ) != NULL){
          printf("%s\n", ler);
    }
     fclose(ex); 
}
