#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
	// time_t start, end;
  // time(&start);
  long int a,b,c;
  int n=70,cont;
  double r;


    a = 1;
    b = 1;
    cont = 2;

    while(cont < n) {
      c = a + b;
      r = c;
      r = r/b;
      a = b;
      b = c;
      cont = cont + 1;
      //eh a mesma coisa: cont++;
    }
		printf("O septuagésimo numero da sequencia de fibonace eh: %ld\n", c);

	// time(&end);
	// double time_take = (end-start);
	// printf("%lf\n",time_take);

  return 0;
}
