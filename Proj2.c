#include <stdio.h>

// Variaveis globais
int tamanho = 0;
int maiorresult = 0;
int resultado[50] = {0};          
int combinacao;                   

// Declarando as funções que serão usadas posteriormente no programa
void decompor(int teste, int *vetor, int *possibilidades, int ind, int M,int tamdecomp,int maiorcomp);
void zerapossib(int *possibilidades, int M);
void salvavetor(int *possibilidades, int num);  
void retiravetor(int *possibilidades);
void troca(int *possibilidades);

int main()
{
  int N, M, i, j, ind = 0;
  scanf ("%d %d", &N, &M);
  int teste[N], vetor[M], possib[M];

  for (i = 0; i < M; i++)
    scanf("%d", &vetor[i]);

  for (i = 0; i < N; i++)
    scanf("%d", &teste[i]);

  for (i = 0; i < N; i++)
  {
    j = 0;
    combinacao = 0;
    zerapossib(possib, M);

    decompor(teste[i], vetor, possib, 0, M,0,0); // Começamos a partir da posição zero do vetor.

    // Resposta
    printf( "%d  ", combinacao);    
    while (resultado[j] != 0)
    {
      printf("%d ", resultado[j]);
      j++;
    }

    printf("\n");
    zerapossib(resultado, 50);
    tamanho = 0;
    maiorresult = 0;
  }

  return 0;
}

// Essa funcao decompoe o numero ate achar a maior solucao
void decompor(int teste, int *vetor, int *possibilidades, int ind, int M, int tamdecomp, int maiorcomp)
{
  int K = ind, anterior = -1;
  if (teste == 0)
  {
    combinacao++;
    if ((tamdecomp > tamanho) || (tamdecomp == tamanho && maiorcomp > maiorresult))
    {
      troca(possibilidades);
      tamanho = tamdecomp;
      maiorresult = maiorcomp;
    }
    tamdecomp = 0; 
    maiorcomp = 0;
  }
  if (teste <= 0)
    return;

  while (K != M)
  {
    if (vetor[K] == anterior)
      continue; //Esse comando para essa possibilidade,mas permite a verificação dos próximos laços
    
    if (vetor[K] > maiorcomp)
      maiorcomp = vetor[K];
      
    salvavetor(possibilidades, vetor[K]);     

    decompor(teste - vetor[K], vetor, possibilidades, K + 1, M,tamdecomp+1,maiorcomp); //Recursão que para fazer até encontrarmos as combinações 
    retiravetor(possibilidades);

    anterior = vetor[K];
    K++;
  }

}

// Essa função inicializa os vetores com zero
void zerapossib(int *possibilidades, int M)
{ 
  int k;
  for (k = 0; k < M; k++)
    possibilidades[k] = 0; 
}

// Essa funcao transforma a penúltima posição em última
void retiravetor(int *possibilidades) 
{
  int k = 0;
  while (possibilidades[k] != 0)
    k++;
  
  possibilidades[k - 1] = 0;
}

// Essa funcao serve para adicionamos no final do vetor o outro número que será usado pra combinar
void salvavetor(int *possibilidades, int num) 
{
  int k = 0;
  while (possibilidades[k] != 0)
    k++;

  possibilidades[k] = num;
}

// Essa função servirá para copiarmos o vetor possibilidades(maior deles) no vetor resultado
void troca(int *possibilidades) 
{
  int k = 0;
  while (possibilidades[k] != 0) 
  {
    resultado[k] = possibilidades[k];
    k++;
  }
}
