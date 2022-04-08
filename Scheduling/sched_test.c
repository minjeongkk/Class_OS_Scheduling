#include <stdio.h>
#include <stdlib.h>
#include "sched_types.h"

int main() {
	process1();
	printf("===========================FIFO(1)===========================\n");
	FCFS();
	printf("\n");

	process1();
	printf("===========================RR(1)===========================\n");
	RR();
	printf("\n");
	
	printf("===========================SPN(1)===========================\n");
	process1();
	SPN();
	printf("\n");
	
	printf("===========================HRRN(1)===========================\n");
	process1();
	HRRN();
	printf("\n\n");


	process2();
	printf("===========================FIFO(2)===========================\n");
	FCFS();
	printf("\n");

	process2();
	printf("===========================RR(2)===========================\n");
	RR();
	printf("\n");

	process2();
	printf("===========================SPN(2)===========================\n");
	SPN();
	printf("\n");

	process2();
	printf("===========================HRRN(2)===========================\n");
	HRRN();
	printf("\n");

	printf("===========================lottery===========================\n");
	lottery();
	printf("\n");
}