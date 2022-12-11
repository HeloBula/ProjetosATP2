#include <stdio.h>
#include <math.h> //Inclusão das bibliotecas que serão usadas

int main(){
 /*Declaração de variáveis usadas durante o programa*/   
    FILE *cod;
    FILE *palav; /*Ponteiros de arquivo, os dois primeiros relacionados aos arquivos de entrada e o último ao arquivo de saída*/
    FILE *linha;
    int N,i,count_espaco, count_palavra; /*Variáveis que servirão de contadores*/
    char pp[100],caracter;/*Vetor que receberá a palavra e o que receberá o caracter para comparar*/

/*Abrindo os arquivos que eu havia criado para testar o código*/
    cod=fopen("codigos.dat","r");
    palav=fopen("palavras.dat","r");
/*Com o próximo comando eu faço com que o S.O crie um novo arquivo*/    
    linha=fopen("linhas.dat","w");  
/*Lemos e armazenamos cada número e cada palavra dos arquivos,repetimos essa ação até o final do arquivo "codigo.dat" ou do arquivo "palavras.dat"*/      
    while(!feof(cod)&&!feof(palav))
    {
        fscanf(cod,"%d",&N); //Número de palavras que serão escritas na linha
       if(N>0) //O número é maior que zero
       {
        for(i=0;i<N;i++)
        {
         fscanf(palav,"%s",pp); //Armazeno as palavras do arquivo palavras.dat
         fprintf(linha,"%s ",pp);//Escrevo-as no arquivo de saída
        }
        fprintf(linha,"\n");
       }
       else if(N==0) //Caso o Número for 0
       {
        fprintf(linha,"0\n");// Escrevemos uma linha com um zero
       }
       else //Se N for negativo
       {count_espaco=0;//Inicializando o contador que nos informará quantas palavras voltou, ao contar os espaços
        while(count_espaco<fabs(N))
        {
          fseek(palav,-1,SEEK_CUR); //Enquanto o número de espaço for menor que N,o ponteiro vai voltando um caracter por vez
          caracter=fgetc(palav); //Esse comando parecido com o fgets, pega só um char ao invés de uma string
          if(caracter==' ')
          {
            count_espaco += 1; //Quando o ponteiro encontra um espaço a variável contadora recebe mais 1
          }
          //Para que o ponteiro não retorne no mesmo ponto na próxima repetição,uma vez que leu um caracter,faremos ele retornar uma vez mais
         fseek(palav,-1,SEEK_CUR);
        }
        for(i=0;i<fabs(N);i++) //Coloquei um Módulo no N para que ele vire um número positivo.
        {
         fscanf(palav,"%s",pp);
         fprintf(linha,"%s ",pp); //Imprimindo as palavras
        }
        fprintf(linha,"\n");
       }
    } 
    while(!feof(cod)) //Usei outro laço para percorrer o "codigos.dat", caso esse possua mais números do que existam palavras no "palavras.dat"
    {
      fscanf(cod,"%d",&N);
      fprintf(linha,"%d ",N);  
    }
    count_palavra=0; //Contador que auxiliará na impressão das palavras restantes
    while(!feof(palav))//Esse laço vai ser usado até encontrar o final do arquivo "palavras.dat"
    {
      fscanf(palav,"%s",pp);
      fprintf(linha,"%s ",pp);
      count_palavra+=1; //Quando eu imprimo uma palavra eu aumento o contador
      if(count_palavra%5==0)//dividimos o número do contador em cada repetição por 5,verificando se em alguma o resto será zero
      {
       fprintf(linha,"\n"); //Se isso ocorrer o programa pula a linha e volta a escrever as palavras na debaixo
      }  
    }
    fclose(cod);
    fclose(palav); //Fechamento dos Arquivos
    fclose(linha);

    return 0; //Fim do Programa
    }






