#pragma once

#define QSIZE 20
#define SIZE 50 
#define NUM 5

// 프로세스 구조체
typedef struct Process {
	char name;
	int pid;
	int arrival; //도착시간
	int service; 
	int runtime; //실제 실행시간
}process;
process p[5];

// Node 구조체
typedef struct Node{
	int data;
	struct Node* next;
}Node;

// Queue 구조체
typedef struct Queue {
	Node* front;
	Node* rear;
	int cnt; //큐에 들어있는 요소 개수
	int timeq; //quantum
}queue;

void initQueue(queue* q); // Queue 초기화
int isEmpty(queue* q); // Queue 요소가 비었는지 체크
void enqueue(queue* q, int pid); // Queue 삽입
int dequeue(queue* q); // Queue 삭제
void priority_queue(queue* q, int s_case, int time); //우선순위 큐

void process1(); //첫번째 프로세스
void process2(); // 두번째 프로세스

void sortArrival(process* p); //도착시간 정렬
void sched_print(int print[NUM][SIZE], int n, int time); //그래프 출력함수

void FCFS();
//RR
void SPN();
void HRRN();
//MLFQ (q=1)
//MLFQ (q=2^i)