#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int Ident;
    int tempchegada;
    int carga;
    struct no *prox;
}Fila;

//Struct normal
typedef struct parametro{
    int tempo;
    int ocupado;//Verifica se o caixa ta livre - 0 é que tá livre, 1 está ocupado
}Atendente;

Fila *alocar(int I,int O, int C);
void insere(Fila **h,Fila *F);
Fila *remover(Fila *h);
int verifica(int M, Atendente *centro);//Vê se o atendente ta livre
int regulatempo(int M,Atendente *centro);//Vê se tem tempo entre um atendimento e outro
void resetar(int M, Atendente *centro);//Uso essa pra liberar o caixa depois do tempo
void funcionamento(Fila *h,int M, Atendente *centro);


int TempPassado=0;//Vai ser usado em algumas funções,começa zerado

int main(){

int N,M; //Elementos na fila, e numero de atendentes
int i;
int I,O,C;
Fila *h = NULL, *F;


scanf("%d %d",&N,&M);

Atendente centro[M]; //Quantos centros tem
Fila *aux; //Recebe o item da fila que será entregue para o atendimento

for(i=0;i<N;i++)
{  scanf("%d %d %d",&I,&O,&C); 
   F = alocar(I,O,C); //Montando a fila
   insere(&h,F); 
}
  for(i=0;i<M;i++)
  {
    centro[i].ocupado = 0; //Inicio os atendentes
    centro[i].tempo = 0;
  } 

    funcionamento(h,M,centro);//Funcionamento do caixa, explicado mais para baixo

return 0;
}

Fila *alocar(int I,int O, int C){ //Coloco no formato de ila, passando o Identificador, Tempo de chegada e Carga
    Fila *aux;
    aux = malloc(sizeof(Fila));
    aux->Ident = I;
    aux->tempchegada = O;
    aux->carga = C;
    aux->prox = NULL;
return aux;
}

void insere(Fila **h,Fila *F){
    Fila *aux ,*prev;//prev caminha atrás de aux
    aux = prev = (*h);
 if(!(*h))
 {
    (*h) = F;
    return;
 }

while(aux && aux->tempchegada < F->tempchegada){ //Só entra nele se o tempo for menor
    prev = aux;
    aux = aux->prox;
}
while(aux && aux->tempchegada == F->tempchegada && F->Ident > aux->Ident){//Se chegou ao mesmo tempo, verifica até achar o menor identificador
    prev = aux;
    aux = aux->prox;
}
if(aux!=(*h))//Tem que mudar a cabeça pro elemento novo
{
prev->prox = F;
F->prox = aux;
return ;
}
else
    F->prox = aux;
    (*h) = F;
    return;
}

Fila *remover(Fila *h) //Tira o primeiro e retorna a nova cabeça
{
   Fila *aux;
   aux = h;

  if(aux == NULL)
  {
    return h;
  }
  else
    {
        h = aux->prox;
        free(aux);
        return h;
    }

}

int verifica(int M,Atendente *centro){
    int i, Minimo, disponivel ,ind = 0;
    Minimo = 10000, disponivel = 0;//minimo começa com 10000 pois é o limite que está no exercicio

    for(i=0;i<M;i++)
    {
        if(centro[i].ocupado == 0)
            disponivel += 1;//Aumento o contador
    }
   if(disponivel == 0)//Nenhum disponivel
    return -1;
   else if(disponivel == 1)//Se só tiver 1 disponivel
    {
        for(i=0;i<M;i++)
        {
            if(centro[i].ocupado == 0)
                ind = i;
        }
        return ind;
    }
    else //Tiver mais de um caixa livre
      {
        for(i=0;i<M;i++)
        {
            if(centro[i].ocupado == 0)
            {
                if(centro[i].tempo < Minimo) // devolve o que vai sair mais cedo 
                {
                    Minimo = centro[i].tempo;
                    ind = i;
                }
            }
        }
    return ind;
      } 
}

int regulatempo(int M,Atendente *centro)//Quando tiver que esperar pelo outro cliente
{
    int i, menor = centro[0].tempo;
    int disponivel;

    for(i=0;i<M;i++)
    {
        if(centro[i].tempo<menor)//Vou comparando pra ver qual vai ser atendido primeiro
         {
            menor = centro[i].tempo;
            disponivel = i;
         }
    }
    return disponivel;
    // retorna o que vai atender primeiro
}

void resetar(int M, Atendente *centro)
{
    int i;

    for(i=0;i<M;i++){
        if(TempPassado > centro[i].tempo)//Se já passou o tempo que ele ficava ocupado, libera
         {
            centro[i].ocupado = 0;
         }
    }
return;
}

void funcionamento(Fila *h,int M, Atendente *centro)
{

    Fila *aux;
    int i =0, j;

    aux = h;
   while(aux != NULL)//Enquanto tiver alguém na fila
   {
    TempPassado = aux->tempchegada;
    resetar(M,centro);//Libero o caixa quando passar o tempo
    i = verifica(M,centro);//acho caixas livres

    if(i == -1)//Ninguém ta disponivel
    {
        j = regulatempo(M,centro);//qual vai estar disponivel primeiro
        if(aux->tempchegada > centro[j].tempo)
            centro[j].tempo = aux->tempchegada + aux->carga; //O tempo do que fica livre primeiro vai ser o de chegada do próximo a ser atendido mais sua carga
        else
            centro[j].tempo = centro[j].tempo + aux->carga;

        aux = remover(aux); //removo da fila  o que foi atendido   
    }
    else //Se tiver algum livre
    {

        centro[i].ocupado = -1;//mudo pra ocupado
        if(aux->tempchegada > centro[i].tempo)//vejo se chegou quando o caixa já estava livre
            centro[i].tempo = aux->tempchegada + aux->carga;
        else
           centro[i].tempo = centro[i].tempo + aux->carga;

        aux = remover(aux);
    }
   } 

   for(j=0;j<M;j++)//Imprimir a resposta final com o tempo de cada um dos centros
   {
      printf("%d ",centro[j].tempo);  
   }
}
