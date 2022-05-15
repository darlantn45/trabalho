#include "scheduler.h"
#include "load_jobs.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int confere(){
	int processo = 0;
	for (int i = 0; i < queueSize; i++) {
		if(tempo[i]<1){
			processo++;
		}
	}
	return processo;
}

int SJF_NP(){

	int menor = 1000;
	int aux;
	for (int i = 0; i < queueSize; i++) {
		if(tempo[i] > 0){
			if(menor > tempo[i]){
				menor = tempo[i];
				aux = i;
			}
		}
	}

return aux;
}

extern void iniciarProcesso(int index);

void scheduler_init(char* jobs, float quantum){

	pidx = 0;
	alterna = 1;
	receive=0;

	loadJobs(jobs);

	print_jobsQueue();
	tempo = (int*) malloc(queueSize*sizeof(int));
	int i;

	for(i = 0; i < queueSize; i++){
	tempo[i] = atoi(argumentos[i]);
			iniciarProcesso(i);

			kill(spid[i], SIGSTOP);
	}
	alterna = -1;


	while(1){
		int processo = confere();//função para conferir quantos processos foram feitos
		if(processo == queueSize){//caso entre, irá finalizar o while.
			kill(spid[alterna], SIGSTOP);//pausa o processo final da fila
			printf("\nSem mais processos na fila, SJF finalizado\n");
			break;//sai do while
		}
		  signal(SIGALRM, alternaTarefa);
		  alarm(quantum);
		  while(!receive)
			pause();
		  receive = 0;

    }


}

void alternaTarefa(int signum){
	UNUSED(signum);

	int aux = alterna;

	receive = 1;

	alterna = SJF_NP(tempo);//recebe o menor processo
	tempo[alterna] = tempo[alterna] - 1;//diminui o tempo do processo
//	printf("%i\n",tempo[alterna] );

	//fica alternaando o processo que está em execução

	if(alterna < queueSize - 1){//tamanho do alterna não pode ser maaior do que a file-1
			if (alterna >= 0){//alterna tem que ser maior que zero
				kill(spid[aux], SIGSTOP);//faz o processo pausar
		}
		}
		kill(spid[alterna], SIGCONT);//retorna um processo pausado pelo sinal SIGSTOP
		// else {
		// 	//pausa o processo, muda o alterna pra zero e retorna o processo pausado
		// 	kill(spid[alterna], SIGSTOP);//faz o processo pausar
		// }

	}
