#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXTAM 3

typedef struct{
int pag;
int tempo;
}Pagina;

int func(int cont, Pagina *p){
  int maior = -1,aux;
  for (int i = 0; i < MAXTAM; i++) {
    if(maior < p[i].tempo){
      maior = p[i].tempo;
      aux = i;
    }
}
return aux;
}

int main(){

FILE *arq;
int aux,tempo,pag = 0,contador = 0;
char c;

Pagina p[MAXTAM];


arq = fopen("teste.txt","r");

if(arq	==	NULL){
       printf("Ocorreu um erro no arquivo");
       system("pause");
       exit(1);
     }

while( (c=fgetc(arq)) != '\n') {
  if(isdigit(c) != 2048){
    printf("Arquivo invalido!\n");
    exit(1);
  }
}
fseek(arq, 0, SEEK_SET);
for (int i = 0; i < MAXTAM; i++) {
       c = fgetc(arq);
       aux = c -'0';
       p[i].pag =aux;
       p[i].tempo = MAXTAM-i-1;
       pag++;
     }

while( (c=fgetc(arq)) != '\n') {

  for (int i = 0; i < MAXTAM; i++) {

    printf("%i ",p[i].pag );
  }
  printf("\n");
  aux = c - '0';
  for (int i = 0; i < MAXTAM; i++) {
  if(aux != p[i].pag){
    contador++;
  }
}
if(contador == MAXTAM){
  tempo = func(contador,p);
  p[tempo].pag = aux;
  pag++;
  for (int i = 0; i < MAXTAM; i++) {
    p[i].tempo++;
  }
  p[tempo].tempo = 0;

}else{
  for (int i = 0; i < MAXTAM; i++) {
    p[i].tempo++;
    if(aux == p[i].pag){
      p[i].tempo = 0;
    }
  }
}
  contador = 0;
}

printf("Pag%i\n",pag );



  return 0;
}
