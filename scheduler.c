#include "scheduler.h"
#include "load_jobs.h"
#include <unistd.h>
#include <signal.h>

extern void iniciarProcesso(int index);

void scheduler_init(char* jobs, float quantum){

	pidx = 0;
	alterna = 1;
	receive=0;

	loadJobs(jobs);

	print_jobsQueue();

	int i;

	for(i = 0; i < queueSize; i++){
			iniciarProcesso(i);
			kill(spid[i], SIGSTOP);
	}
	alterna = -1;


	while(1){
		  signal(SIGALRM, alternaTarefa);
		  alarm(quantum);
		  while(!receive)
			pause();
		  receive = 0;

    }


}

void alternaTarefa(int signum){
	UNUSED(signum);

	receive = 1;

	//fica alternaando o processo que está em execução

	if(alterna < queueSize - 1){//tamanho do alterna não pode ser maaior do que a file-1
		if (alterna >= 0){//alterna tem que ser maior que zero
		kill(spid[alterna], SIGSTOP);//faz o processo pausar
	}
		alterna++;
	}
	else {
		//pausa o processo, muda o alterna pra zero e retorna o processo pausado
		kill(spid[alterna], SIGSTOP);//faz o processo pausar
		alterna = 0;
	}

	kill(spid[alterna], SIGCONT);//retorna um processo pausado pelo sinal SIGSTOP
}
