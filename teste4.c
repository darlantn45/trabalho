
// Libs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAX 500000

// Define uma constante
// Define a constant

// Protótipo da função de ordenação
// Ordination function prototype
void quick_sort(int *a, int left, int right);

// Função main
// Main Function
int main(int argc, char** argv)
{
  //time_t start, end;
  //time(&start);
  FILE*  arq1 = fopen("output.txt","wt");//abr aquivo
  FILE*  arq2 = fopen("input.txt","rt");//abr aquivo
  int i, vet[MAX];
  for (int j = 0; j < MAX; j++) {
    fscanf(arq2, "%i", &vet[j]);
  }


  // Lê MAX ou 10 valores

  // Ordena os valores
  // Order values
  quick_sort(vet, 0, MAX - 1);

  // Imprime os valores ordenados
  // Print values in order ascendant
  printf("\n\nValores ordenados\n");
  for(i = 0; i < MAX; i++)
  {
		fprintf(arq1,"%i\n",vet[i] );
    printf("%d \n", vet[i]);
  }
//  time(&end);
  //double time_take = (end-start);
//  printf("%lf\n",time_take);
printf("Ordenacao feita e salvo no arquivo de saida\n");
  return 0;
}

// Função de Ordenação por Seleção
// Quick sort function
void quick_sort(int *a, int left, int right) {
  int i, j, x, y;

  i = left;
  j = right;
  x = a[(left + right) / 2];

  while(i <= j) {
    while(a[i] < x && i < right) {
      i++;
    }
    while(a[j] > x && j > left) {
      j--;
    }
    if(i <= j) {
      y = a[i];
      a[i] = a[j];
      a[j] = y;
      i++;
      j--;
    }
  }

  if(j > left) {
    quick_sort(a, left, j);
  }
  if(i < right) {
    quick_sort(a, i, right);
  }
}
