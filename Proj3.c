#include <stdio.h>
#include <stdlib.h>

typedef struct no { //Elementos da lista contem Identificador, número que vai andar e opção
  int K, I, O;
  struct no *prox;
} Circ;

int proximo = 0, Iant, Oant, Kant, opcao;
Circ *old = NULL; // Armazenar as variáveis do antigo

Circ *alocar(int i, int k, int o);
Circ *insere(Circ *h, Circ *elemento);
void tiraitem(Circ **atual, Circ **anterior, Circ **h);
void inicia(Circ *h);

int main() {
  int N, i, k, o;
  scanf("%d", &N);

  Circ *head = NULL, *aux, *anterior; // Cabeça e uma lista auxiliar

  for (i = 1; i <= N; i++) {
    scanf("%d", &k);
    scanf("%d", &o);
    aux = alocar(i, k, o);    // Coloco no formato da lista
    head = insere(head, aux); // Preencho a lista com os dados
  }

  proximo = head->K; //Quantos vai percorrer agora
  opcao = head->O; //O que será feito com o próximo item
  inicia(head);

  aux = head;

  while (head != head->prox) { //Enquanto não tiver só um item na lista
    for (i = 1; i < proximo; i++) {
      anterior = aux;
      aux = aux->prox;
    }
    proximo = aux->K;//Vai andar pra qual
    opcao = aux->O;
    if (opcao == 0) {//Retirar item da lista
      if (old != NULL) // Pra não gerar segmentation fault se cair no primeiro caso que old seja vazio
       { free(old);}
      
      tiraitem(&aux, &anterior, &head);
    } else {//Adicionar o valor do que foi retirado anteriormente
      insere(head, old);
      tiraitem(&aux, &anterior, &head);
    }
  }
  printf("%d\n", head->I); //Identificador do item que sobrou
  return 0;
}

Circ *alocar(int i, int k, int o) { //Coloca no formato de lista
  Circ *aux = malloc(sizeof(Circ));
  aux->I = i;
  aux->K = k;
  aux->O = o;
  aux->prox = NULL;

  return aux;
}

Circ *insere(Circ *h, Circ *elemento) {
  Circ *atual, *antes;

  if (!h) // Lista vazia
  {
    h = elemento;
    h->prox = elemento; // Lista Circular
    return h;
  }
  atual = antes = h; // Só tem um elemento agora
  if (h->prox == h) {
    elemento->prox = atual;
    atual->prox = elemento;
    if (elemento->I < atual->I) // Se o identificador for menor -> altera a cabeça, ele será o primeiro
      h = elemento;
    return h;
  }
  while (antes->prox != h && elemento->I > atual->I) // Se tiver outro item além da cabeça já,mas o Id for menor, vai percorrendo
  {
    antes = atual;
    atual = atual->prox;
  }
  if (atual == h && elemento->I < atual->I) {
    antes = atual->prox;
    while (antes->prox != atual) //Enquanto não der uma volta completa
      antes = antes->prox;
    antes->prox = elemento;
    elemento->prox = h;
    h = elemento; // Insere o elemento antes da cabeça, ou seja, elemento passa a ser a nova cabeça
    return h;
  }
  elemento->prox = atual;
  antes->prox = elemento;
  return h;
}

void inicia(Circ *h) // Inicia os valores para as próximas execuções
{
  Iant = h->I;
  Oant = 0;
  Kant = h->K;
}

void tiraitem(Circ **atual, Circ **anterior, Circ **h) // old é o elemento antigo que tava salvo, anterior é elemento anterior ao atual
{
  if (*atual == *h)
    *h = (*h)->prox;
  old = *atual;
  (*anterior)->prox = (*atual)->prox; // Entre parenteses mostrando ser ponteiro de ponteiro
  (*atual) = (*atual)->prox;
  old->prox = NULL;
  old->O = 0; // Zero a opção para não atrapalhar o restante do programa
}
