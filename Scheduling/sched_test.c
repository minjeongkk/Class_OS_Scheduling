#include <stdio.h>
#include <stdlib.h>
#include "sched_types.h"

int main() {
	process1();
	printf("==================FIFO(1)==================\n");
	FCFS();
	printf("\n");
	printf("===================SPN(1)===================\n");
	process1();
	SPN();
	printf("\n");

	process2();
	printf("==================FIFO(2)==================\n");
	FCFS();
	printf("\n");
	printf("===================SPN(2)===================\n");
	process2();
	SPN();
	printf("\n");

}