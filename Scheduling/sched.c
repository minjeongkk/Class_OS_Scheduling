#include <stdio.h>
#include <stdlib.h>
#include "sched_types.h"

// ù��° ���μ���
void process1() {
    p[0].name = 'A';
    p[0].pid = 0;
    p[0].arrival = 0;
    p[0].service = 3;
    p[0].runtime = 0;

    p[1].name = 'B';
    p[1].pid = 1;
    p[1].arrival = 2;
    p[1].service = 6;
    p[1].runtime = 0;

    p[2].name = 'C';
    p[2].pid = 2;
    p[2].arrival = 4;
    p[2].service = 4;
    p[2].runtime = 0;

    p[3].name = 'D';
    p[3].pid = 3;
    p[3].arrival = 6;
    p[3].service = 5;
    p[3].runtime = 0;

    p[4].name = 'E';
    p[4].pid = 4;
    p[4].arrival = 8;
    p[4].service = 2;
    p[4].runtime = 0;


    sortArrival(p);
}

// �ι�° ���μ���
void process2(){
    p[0].name = 'A';
    p[0].arrival = 0;
    p[0].service = 2;
    p[0].runtime = 0;

    p[1].name = 'B';
    p[1].arrival = 3;
    p[1].service = 5;
    p[1].runtime = 0;

    p[2].name = 'C';
    p[2].arrival = 4;
    p[2].service = 3;
    p[2].runtime = 0;

    p[3].name = 'D';
    p[3].arrival = 6;
    p[3].service = 6;
    p[3].runtime = 0;

    p[4].name = 'E';
    p[4].arrival = 8;
    p[4].service = 3;
    p[4].runtime = 0;

    sortArrival(p);
}

// ť �ʱ�ȭ
void initQueue(queue* q) {
    q->rear = NULL;
    q->front = NULL;
    q->cnt = 0;
    q->timeq = 1;
}

// ť�� ����ִ��� Ȯ��, ������� 1 ���, �Ⱥ������ 0 ���
int isEmpty(queue* q) {
    if (q->cnt == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

// ť ����
void enqueue(queue* q, int pid) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = pid;
    newNode->next = NULL;

    if (isEmpty(q)==1){    // ť�� ������� ��
        q->front = newNode;
    }
    else {    // ť�� ������� ���� ��
        q->rear->next = newNode; //�� ���� ������ newNode
    }
    q->rear = newNode;    //�� �� newNode�� ����   
    q->cnt++;    //ť���� ��� ������ 1 ����

}

// ť pop
int dequeue(queue* q) {
    int tmp;
    Node* point;
    if (isEmpty(q)) {
        return -1;
    }
    point = q->front;
    tmp = point->data;
    q->front = point->next;
    q->cnt--;
    free(point);

    return tmp;
}

// ����ð��� ª�� ������� ����
void priority_queue(queue* q, int s_case, int time) {
    int tmp=0;
    int cnt = q->cnt;
    int* proc = malloc(sizeof(int) * cnt);
    double res1, res2;

    for (int i = 0; i < cnt; i++) {
        proc[i] = dequeue(q); //q�� ���� �޾Ƽ� proc �迭�� ����
    }
    //SPN�� ���: ����ð��� ª�� ������� ����
    if (s_case == 1) {
        for (int i = 0; i < cnt; i++) {
            for (int j = i; j < cnt; j++) {
                // ª�� ���� ������ �迭���� ��ġ �ٲ�
                if (p[proc[i]].service >= p[proc[j]].service) {
                    tmp = proc[i];
                    proc[i] = proc[j];
                    proc[j] = tmp;
                }
            }
        }
    }
    //HRRN�� ���: ������� ���� ������� ����
    else if (s_case == 2) {
        for (int i = 0; i < cnt; i++) {
            res1 =((time - p[proc[i]].arrival) + p[proc[i]].service) / p[proc[i]].service; //�����
            for (int j = i; j < cnt; j++) {
                res2 = ((time - p[proc[j]].arrival) + p[proc[j]].service) / p[proc[j]].service; //�����
                // ����� ū ���� ������ �迭 �������� ������
                if (res1 < res2) {
                    tmp = proc[i];
                    proc[i] = proc[j];
                    proc[j] = tmp;
                }
            }
        }
    }

    // ���ĵ� ������� ť�� ����
    for (int i = 0; i < cnt; i++) {
        enqueue(q, proc[i]);
    }

}

// �����ð� ����
void sortArrival(process* p) {
    for (int i = 0; i < NUM; i++) {
        for (int j = i + 1; j < NUM; j++) {
            if (p[i].arrival > p[j].arrival) {
                process tmp;
                int tmp_pid;
                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;

                tmp_pid = p[i].pid;
                p[i].pid = p[j].pid;
                p[j].pid = tmp_pid;
            }
        }
    }
}

// ���
void sched_print(int print[NUM][SIZE], int n, int time) {
    for (int i = 0; i < n; i++) {
        printf("%c ", p[i].name);
        for (int j = 0; j < time; j++) {
            if (print[i][j] == 1)
                printf(" ��");
            else
                printf(" ��");
        }
        printf("\n");
    }
}

//FCFS
void FCFS() {
    int time = 0;
    int total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service;// �� ���� �ð�
    int pselect = 0;
    int be_pselect = 0;
    int printarr[NUM][SIZE] = { 0 };
    queue cpu_q;

    initQueue(&cpu_q);

    enqueue(&cpu_q, p[pselect].pid);

    while (total != 0) {
        pselect = dequeue(&cpu_q);

        // ť�κ��� ���μ����� ����� �ҷ��� ���
        if (pselect >= 0) {
            for (int i = 0; i < p[pselect].service; i++) {
                if (p[pselect].runtime == p[pselect].service) { //������ runtime�� service�� ������ break
                    break;
                }
                total--; // ��ü ���� �ð� ����
                p[pselect].runtime++; // �ش� ���μ��� runtime 1 ����
                printarr[pselect][time] = 1; // ����ǥ�� ���
                time += 1; // �ð� 1 ����
                be_pselect = pselect; // ������ pselect ����
                
                // ����ð� ���� ������ ���μ����� ������ ť�� ����
                for (int j = pselect+1; j < NUM; j++) {
                    if (time >= p[j].arrival) {
                        enqueue(&cpu_q, p[j].pid);
                    }
                }
            }
        }
        // ť�� �ƹ��͵� ���� ���μ����� �ҷ����� ���� ���
        else {
            // 1 ������ �ð����� ������ ���� ������ ť�� ����
            for (int j = be_pselect+1; j < NUM; j++) {
                if (time >= p[j].arrival) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
        }
        // total �ð��� 0�� �Ǹ� ����
        if (total == 0) {
            break;
        }
        // ������ ���μ����� ���� ��, ������ ����ϰ� �ð��� 1 ����
        if (isEmpty(&cpu_q) == 1 ) {
            if (pselect >= 0) { //pselect�� 0�̻��� �� �׷����� ����
                printarr[pselect][time] = 0;
            }
            time += 1;
            continue;
        }

    }
    // ���
    sched_print(printarr, NUM, time);
}

//RR
void RR() {
    int time = 0;
    int timeslice = 0;
    int total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service; //�� ���� �ð�
    int pselect = 0;
    int be_pselect = 0;
    int printarr[NUM][SIZE] = { 0 };
    queue cpu_q;

    initQueue(&cpu_q);

    enqueue(&cpu_q, p[pselect].pid);

    while (total != 0) {
        pselect = dequeue(&cpu_q);
        // ť�κ��� ���μ����� ����� �ҷ��� ���
        if (pselect >= 0) {
            // �Ϸ�Ȱ��� ť�� ���������� �ٸ� ���μ����� ����
            if (p[pselect].runtime == p[pselect].service) {
                pselect = dequeue(&cpu_q);
            }

            // time quantum ����
            if (cpu_q.timeq > (p[pselect].service - p[pselect].runtime)) {
                timeslice = (p[pselect].service - p[pselect].runtime);
            }
            else {
                timeslice = cpu_q.timeq;
            }

            // timeslice��ŭ ����
            for (int j = 0; j < timeslice; j++) {

                total--; // ��ü ���� �ð� ����
                p[pselect].runtime++; // �ش� ���μ��� runtime 1 ����
                printarr[pselect][time] = 1; // ����ǥ�� ���
                time += 1; // �ð� 1 ����

                // ����ð����� ���� ť�� ������ ť�� ����
                for (int k = 0; k < NUM; k++) {
                    if (time == p[k].arrival && pselect != k && p[k].runtime != p[k].service) {
                        enqueue(&cpu_q, p[k].pid);
                    }
                }
                be_pselect = pselect;
            }
            // �������� ���μ����� ������ �ʾ����� �ٽ� ť�� ����
            if (p[pselect].runtime != p[pselect].service) {
                enqueue(&cpu_q, p[pselect].pid);
            }



        }
        // ť�� �ƹ��͵� ���� ���μ����� �ҷ����� ���� ���
        else {
            // 1 ������ �ð����� ������ ���� ������ ť�� ����
            for (int j = 0; j < NUM; j++) {
                if (time == p[j].arrival && p[j].runtime != p[j].service) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
        }
        if (total == 0) {
            break;
        }
        // ������ ���μ����� ���� ��, ������ ����ϰ� �ð��� 1 ����
        if (isEmpty(&cpu_q) == 1) {
            if (pselect >= 0) { //pselect�� 0�̻��� �� �׷����� ����
                printarr[pselect][time] = 0;
            }
            time += 1;
            continue;
        }

    }
    sched_print(printarr, NUM, time);
}

// SPN
void SPN() {
    int time = 0;
    int total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service; // �� ���� �ð�
    int pselect = 0;
    int printarr[NUM][SIZE] = { 0 };
    queue cpu_q;
    int be_pselect=0;

    initQueue(&cpu_q);

    enqueue(&cpu_q, p[0].pid); //���� ó���� �ֱ� 

    while (total != 0) {
        pselect = dequeue(&cpu_q);

        // ť�κ��� ���μ����� ����� �ҷ��� ���
        if (pselect >= 0) {
            for (int i = p[pselect].runtime; i < p[pselect].service; i++) {
                total--; // ��ü ���� �ð� ����
                p[pselect].runtime++; // �ش� ���μ��� runtime 1 ����
                printarr[pselect][time] = 1; // ����ǥ�� ���
                time += 1; // �ð� 1 ����
                be_pselect = pselect;

                // ����ð����� ������ ���μ����� ������ ť�� ����
                for (int j = pselect + 1; j < NUM; j++) {
                    if (time >= p[j].arrival) {
                        enqueue(&cpu_q, p[j].pid);
                    }
                }
                priority_queue(&cpu_q, 1, time); //�켱������ ����
            }
        }

        // ť�� �ƹ��͵� ���� ���μ����� �ҷ����� ���� ���
        else {
            // 1 ������ �ð����� ������ ���� ������ ť�� ����
            for (int j = be_pselect + 1; j < NUM; j++) {
                if (time >= p[j].arrival) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
            priority_queue(&cpu_q, 1, time); //�켱������ ����
        }
        if (total == 0) {
            break;
        }
        // ������ ���μ����� ���� ��, ������ ����ϰ� �ð��� 1 ����
        if (isEmpty(&cpu_q) == 1) {
            if (pselect >= 0) { //pselect�� 0�̻��� �� �׷����� ����
                printarr[pselect][time] = 0;
            }
            time += 1;
            continue;
        }

    }
    //���
    sched_print(printarr, NUM, time);
}

void HRRN() {
    int time = 0;
    int total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service;
    int pselect = 0;
    int printarr[NUM][SIZE] = { 0 };
    queue cpu_q;
    int be_pselect = 0;

    initQueue(&cpu_q);

    enqueue(&cpu_q, p[0].pid); //���� ó���� �ֱ� 

    while (total != 0) {
        pselect = dequeue(&cpu_q);
        // ť�κ��� ���μ����� ����� �ҷ��� ���
        if (pselect >= 0) {
            for (int i = p[pselect].runtime; i < p[pselect].service; i++) {
                total--; // ��ü ���� �ð� ����
                p[pselect].runtime++; // �ش� ���μ��� runtime 1 ����
                printarr[pselect][time] = 1; // ����ǥ�� ���
                time += 1; // �ð� 1 ����
                be_pselect = pselect;
                // ����ð����� ������ ���μ����� ������ ť�� ����
                for (int j = pselect + 1; j < NUM; j++) {
                    if (time >= p[j].arrival) {
                        enqueue(&cpu_q, p[j].pid);
                    }
                }
                priority_queue(&cpu_q, 2, time); //�켱������ ����
            }
        }
        // ť�� �ƹ��͵� ���� ���μ����� �ҷ����� ���� ���
        else {
            // 1 ������ �ð����� ������ ���� ������ ť�� ����
            for (int j = be_pselect + 1; j < NUM; j++) {
                if (time >= p[j].arrival) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
            priority_queue(&cpu_q, 2, time); //�켱������ ����
        }
        if (total == 0) {
            break;
        }
        // ������ ���μ����� ���� ��, ������ ����ϰ� �ð��� 1 ����
        if (isEmpty(&cpu_q) == 1) {
            if (pselect >= 0) { //pselect�� 0�̻��� �� �׷����� ����
                printarr[pselect][time] = 0;
            }
            time += 1;
            continue;
        }

    }
    //���
    sched_print(printarr, NUM, time);
}


void lottery() {
    // ��ü : 0~99 => A: 75 (0~74), B: 25 (75~99)
    int ticket[2][20] = { 0 };
    int lotto[20];
    for (int i = 0; i < 20; i++) {
        lotto[i] = rand() % 100; //0~99 ������ ��ȣ 20���� �迭�� ����

        if (lotto[i] < 75) { //0~74�̸� ���� 0�� �迭�� 1�Է�
            ticket[0][i] = 1;
        }
        else { //0~74�̸� ���� 1�� �迭�� 1�Է�
            ticket[1][i] = 1;
        }
    }

    // �����ٷ� ���� ��� ���
    printf("Here is output of a lottery schedulers's winning tickets:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", lotto[i]);
    }
    printf("\n\n");
    printf("Here is the resulting schedule:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 20; j++) {
            if (ticket[i][j] == 1) {
                printf("%c  ", 'A' + i);
            }
            else {
                printf("   ");
            }
        }
        printf("\n");
    }

}