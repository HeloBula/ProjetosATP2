#include <stdio.h>
#include <stdlib.h>
#include <time.h>//Verificar o tempo de execução
#define N 200000

typedef struct biggo{
    int high;
    int low;
}BigInt;

void troca(BigInt *vet,BigInt *vetor);
void quicksort(BigInt *vet,int inicio, int ultimo);

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
    while(!feof(fp))
    {
        fscanf(fp, "%d %d",&vet[i].high,&vet[i].low);
        i++;
    }
    
    fclose(fp);
    fflush(fp);

    resp = fopen("quick.dat","w");

    final = i;//Saber qual a última posição preenchida
    t = clock();
    quicksort(vet,0,final-2);//Chamo a função para ordenar
    t = clock() - t;
    tempo = ((double)t)/CLOCKS_PER_SEC; //Para ter o tempo que demorou o Quick sort
    printf("%.2lf segundos",tempo);
    for(i=0;i<final-1;i++)
    {
        fprintf(resp,"%d %d\n",vet[i].high,vet[i].low);
    }
    fclose(resp);

 return 0;   
}

void quicksort(BigInt *vet,int inicio, int ultimo)//Diferente do normal-ALTERAR
{
    int i,pivo,bigger;

    if(inicio<ultimo)
    {
        pivo = ultimo;
        bigger = inicio;
        for(i=bigger;i<ultimo;i++)
        {
            if(vet[i].high < vet[pivo].high)
            {
                troca(&vet[i],&vet[bigger]);
                bigger++;
            }
            else if(vet[i].high==vet[pivo].high &&vet[i].high>0&&vet[i].low<vet[pivo].low)//Se forem igual essa parte, eu comparo a outra
            { 
                troca(&vet[i],&vet[bigger]);
                bigger++;
            }
            else if(vet[i].high==vet[pivo].high && vet[i].high<0 && vet[i].low>vet[pivo].low)//Se um deles for negativo, o outro também será, uma vez que são iguais.E como são negativos,vejo qual é maior
            { 
                troca(&vet[i],&vet[bigger]);
                bigger++;
            }
        }
        troca(&vet[bigger],&vet[pivo]);//Com isso eu deixo os menores de um lado e maiores do outro
        quicksort(vet,inicio,bigger-1);//Ordeno dentro da parte esquerda, ajeitando nas posições certas com vetores cada vez menores
        quicksort(vet,bigger+1,ultimo);//Idem ao de cima só que para o lado direito
    }
}

void troca(BigInt *vet,BigInt *vetor)
{
    BigInt aux;

    aux = *vetor;//pega o ultimo
    *vetor = *vet;
    *vet = aux;//recebe o que tava no ultimo
}