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

	if(alterna < queueSize - 1){
		if (alterna >= 0){
		kill(spid[alterna], SIGSTOP);
	}
		alterna++;
	}
	else {
		kill(spid[alterna], SIGSTOP);
		alterna = 0;
	}

	kill(spid[alterna], SIGCONT);
}
