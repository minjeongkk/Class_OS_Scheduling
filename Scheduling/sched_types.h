#pragma once

#define QSIZE 20
#define SIZE 50 
#define NUM 5

// ���μ��� ����ü
typedef struct Process {
	char name;
	int pid;
	int arrival; //�����ð�
	int service; 
	int runtime; //���� ����ð�
}process;
process p[5];

// Node ����ü
typedef struct Node{
	int data;
	struct Node* next;
}Node;

// Queue ����ü
typedef struct Queue {
	Node* front;
	Node* rear;
	int cnt; //ť�� ����ִ� ��� ����
	int timeq; //quantum
}queue;

void initQueue(queue* q); // Queue �ʱ�ȭ
int isEmpty(queue* q); // Queue ��Ұ� ������� üũ
void enqueue(queue* q, int pid); // Queue ����
int dequeue(queue* q); // Queue ����
void priority_queue(queue* q, int s_case, int time); //�켱���� ť

void process1(); //ù��° ���μ���
void process2(); // �ι�° ���μ���

void sortArrival(process* p); //�����ð� ����
void sched_print(int print[NUM][SIZE], int n, int time); //�׷��� ����Լ�

void FCFS();
//RR
void SPN();
void HRRN();
//MLFQ (q=1)
//MLFQ (q=2^i)