#include <stdio.h>
#include <stdlib.h>
#include <time.h>//Verificar o tempo de execução
#define N 200000

typedef struct biggo{
    int high;
    int low;
}BigInt;

void insertion(BigInt *vet,int num);
void reverte(BigInt *vet);//Função para voltar o número negativo

int main()
{   clock_t t;//Contador de tempo
    BigInt vet[N];//Valor definido no exercicio
    FILE *fp,*resp;
    int i=0,final;
    double tempo;

    fp = fopen("bigint.dat","r");
    
    if(fp==NULL)
       { printf("Arquivo não encontrado\n");//não tem como fazer
        return 0;//encerra o programa
       }
    for(i=0;i<N;i++)
    {
        fscanf(fp, "%d %d",&vet[i].high,&vet[i].low);
        if(vet[i].high<0)//Se for negativo, para não dar erro ao ordenar eu transformo em positivo
        {
            vet[i].low = -(vet[i].low);
        }
        i++;
    }

    fclose(fp);
    fflush(fp);

    resp = fopen("ins.dat","w");
    final = i;//Saber qual a última posição preenchida
     t = clock();//Contar o tempo do insertion
    insertion(vet, i-1);//Chamo a função para ordenar
    t = clock() - t;
    tempo = ((double)t)/CLOCKS_PER_SEC; //Para ter o tempo que demorou o Quick sort
    printf("%.2lf segundos",tempo);
    reverte(vet);
    for(i=0;i<final-1;i++)
    {
        fprintf(resp,"%d %d\n",vet[i].high,vet[i].low);
    }
    fclose(resp);

 return 0;   
}

void insertion(BigInt *vet,int num)
{
    int i, j;
    BigInt aux;
    
    for (i = 1; i < N; i++) 
	{
        aux = vet[i];
        j = i - 1;
 
        while (j >= 0 && vet[j].high > aux.high) 
		{
			vet[j + 1] = vet[j];
      j--;
			
        }
        vet[j + 1] = aux;
    }

  for(i = 1; i < num; i++)
  {
        aux = vet[i];
        j = i - 1;
 
        while (j >= 0 && (vet[j].high == aux.high && vet[j].low > aux.low)) 
		{
			vet[j + 1] = vet[j];
      j--;
			
        }
        vet[j + 1] = aux;
  }
}

void reverte(BigInt *vet)
{
	int i;
	
	for (i = 0; i < N; i ++) 
	{
		if(vet[i].high < 0) 
		{
			vet[i].low = -(vet[i].low); //se for negativo, fazemos a invers�o novamente para que o n�mero retorne ao inicial
		}
		
	}
}

