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
	int aux,fila;
	if(modo == 1)
		fila = np;
	else
		fila = queueSize;
	for (int i = 0; i < fila; i++) {
		if(tempo[i] > 0){
			if(menor > tempo[i]){
				menor = tempo[i];
				aux = i;
			}
		}
	}
	if(np != queueSize)
		np++;

return aux;
}

extern void iniciarProcesso(int index);

void scheduler_init(char* jobs, float quantum){

	pidx = 0;
	alterna = 1;
	receive=0;
	np = 1;
	printf("Digite qual escalonador de processo deseja\n1 -SJF preemptivo\n2 -SJF Nao-preemptivo\n");
	scanf("%i",&modo );

	loadJobs(jobs);

	print_jobsQueue();
	tempo = (int*) malloc(queueSize*sizeof(int));
	int i;

	for(i = 0; i < queueSize; i++){
	tempo[i] = atoi(argumentos[i]);
			iniciarProcesso(i);

			kill(spid[i], SIGSTOP);
	}
	alterna = 0;


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

	int stop = alterna;

	receive = 1;

	if(modo == 2){
	if(tempo[alterna] == 0){
		alterna = SJF_NP();//recebe o menor processo
	}
}else{
	alterna = SJF_NP();
}

	tempo[alterna] = tempo[alterna] - 1;//diminui o tempo do processo

	kill(spid[stop], SIGSTOP);//faz o processo pausar
	kill(spid[alterna], SIGCONT);//retorna um processo pausado pelo sinal SIGSTOP

	}
