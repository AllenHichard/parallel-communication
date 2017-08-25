#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h> // Biblioteca necessária para o carregamento da inpout32.dll
/*Inpout32*/
//Declaração dos ponteiros para função.
typedef short _stdcall (*PtrInp)(short EndPorta);
typedef void _stdcall (*PtrOut)(short EndPorta, short datum);
HINSTANCE hLib; //Instância para a DLL inpout32.dll.
PtrInp inportB;     //Instância para a função Imp32().
PtrOut outportB;  //Instância para a função Out32().
/*Inpout32*/


void Enviar_Byte(int decimal);
int Receber_Byte();
int Menu();
void Controle(int opcao);

void Conversor_linha(int binario[4], int linha);
void Conversor_Coluna(int binary[4],char coluna);
int Conversor_Decimal(int vetor[8]);
void Conversor_Unidade(int vetor[8], int binario[4], int binary[4]);

main(){
   int i,num, binario[4],binary[4], vetor[8], valorEnviado, opcao;
   char coluna;
   
    /*Inpout32*/
   //Carrega a DLL na memória.
   hLib = LoadLibrary("inpoutx64.dll");
   if(hLib == NULL)
   {
      printf("\n\aErro. O arquivo inpout32.DLL nao foi encontrado.\nO programa vai terminar apos digitar qualquer tecla.");
      getch();
   }
   else 
   {
   //Todo o programa só será executado apenas se a dll for carregada.
   //Obtém o endereço da função Inp32 contida na DLL.
      inportB = (PtrInp) GetProcAddress(hLib, "Inp32");
      if(inportB == NULL)
      {
         printf("\n\aErro. Erro ao endereçar a função Inp32.");
      }
      //Obtém o endereço da função Out32 contida na DLL.
      outportB = (PtrOut) GetProcAddress(hLib, "Out32");
      if(outportB == NULL)
      { 
         printf("\n\aErro. Erro ao endereçar a função Out32.");

      }
   /*Inpout32*/
  }
  opcao = Menu();
  if(opcao == 2){
  	printf("informe a Linha\n");
    scanf("%d", &num);
    printf("informe a colunass\n");
    scanf(" %c", &coluna);
    Conversor_linha(binario,num);
    Conversor_Coluna(binary,coluna);
    Conversor_Unidade(vetor, binario, binary);
    valorEnviado = Conversor_Decimal(vetor);
    Enviar_Byte(valorEnviado);
  }
  
}

void Conversor_linha(int binario[4], int linha){
	int i;
   for(i=3; i>=0; i--){
      binario[i] = linha % 2;
      linha = linha / 2;
   }
}

void Conversor_Coluna(int binary[4], char coluna){
	int valor;
	if(coluna == 'a')
	   valor = 10;
	   else if(coluna == 'b')
	   valor = 11;
	   else if(coluna == 'c')
	   valor = 12;
	   else if(coluna == 'd')
	   valor = 13;
	   else if(coluna == 'e')
	   valor = 14;
	   else if(coluna == 'f')
	   valor = 15;
   Conversor_linha(binary,valor);
}


void Conversor_Unidade(int vetor[8], int binario[4], int binary[4]){
	 int i;
	 for(i=0; i<4; i++){
     vetor[i]= binario[i];
     vetor[i+4]= binary[i];
   }
	
}

int Conversor_Decimal(int vetor[8]){
  int i, j=0, dec = 0;
  
  for(i=7; i>=0; i--){
  	if(vetor[i]==1){
  		dec = dec + pow(2,j);
	  }
	  j++;
  }
  return dec;
}


int Menu(){
	int opcao;
	printf("Início de Programa\n");
	printf("Escolha Uma das Opcoes abaixo\n");
	printf("Deseja Receber o Byte da porta paralela --- 1\n");
	printf("Deseja Informar o Byte para ser enviado --- 2\n");
	scanf("%d", &opcao);
	return opcao;
}


void Controle(int Opcao){
	if(Opcao==1){
		int byte = Receber_Byte();
	}
	else if(Opcao ==2){
		int decimal;
   		printf("\n\aInforme o numero decimal que irá enviar para a Porta paralela");
   		scanf("%d", &decimal);
   		Enviar_Byte(decimal);
	}
	
}

void Enviar_Byte(int decimal){
	char teclado=' ';
    teclado=getch();
    while(teclado!='p')
    {
    	outportB(0x378,decimal); 
    }
  outportB(0x378,0);
}


int Receber_Byte(){
	return inportB(0x379);	
}




	


