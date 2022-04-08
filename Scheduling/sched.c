#include <stdio.h>
#include <stdlib.h>
#include "sched_types.h"

// 첫번째 프로세스
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

// 두번째 프로세스
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

// 큐 초기화
void initQueue(queue* q) {
    q->rear = NULL;
    q->front = NULL;
    q->cnt = 0;
    q->timeq = 1;
}

// 큐가 비어있는지 확인, 비었으면 1 출력, 안비었으면 0 출력
int isEmpty(queue* q) {
    if (q->cnt == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

// 큐 삽입
void enqueue(queue* q, int pid) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = pid;
    newNode->next = NULL;

    if (isEmpty(q)==1){    // 큐가 비어있을 때
        q->front = newNode;
    }
    else {    // 큐가 비어있지 않을 때
        q->rear->next = newNode; //맨 뒤의 다음이 newNode
    }
    q->rear = newNode;    //맨 뒤 newNode로 설정   
    q->cnt++;    //큐안의 요소 개수를 1 증가

}

// 큐 pop
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

// 실행시간이 짧은 순서대로 정렬
void priority_queue(queue* q, int s_case, int time) {
    int tmp=0;
    int cnt = q->cnt;
    int* proc = malloc(sizeof(int) * cnt);
    double res1, res2;

    for (int i = 0; i < cnt; i++) {
        proc[i] = dequeue(q); //q에 것을 받아서 proc 배열에 넣음
    }
    //SPN인 경우: 실행시간이 짧은 순서대로 정렬
    if (s_case == 1) {
        for (int i = 0; i < cnt; i++) {
            for (int j = i; j < cnt; j++) {
                // 짧은 것이 있으면 배열에서 위치 바꿈
                if (p[proc[i]].service >= p[proc[j]].service) {
                    tmp = proc[i];
                    proc[i] = proc[j];
                    proc[j] = tmp;
                }
            }
        }
    }
    //HRRN인 경우: 응답률이 높은 순서대로 정렬
    else if (s_case == 2) {
        for (int i = 0; i < cnt; i++) {
            res1 =((time - p[proc[i]].arrival) + p[proc[i]].service) / p[proc[i]].service; //응답률
            for (int j = i; j < cnt; j++) {
                res2 = ((time - p[proc[j]].arrival) + p[proc[j]].service) / p[proc[j]].service; //응답률
                // 응답률 큰 것이 있으면 배열 앞쪽으로 보내줌
                if (res1 < res2) {
                    tmp = proc[i];
                    proc[i] = proc[j];
                    proc[j] = tmp;
                }
            }
        }
    }

    // 정렬된 순서대로 큐에 넣음
    for (int i = 0; i < cnt; i++) {
        enqueue(q, proc[i]);
    }

}

// 도착시간 정렬
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

// 출력
void sched_print(int print[NUM][SIZE], int n, int time) {
    for (int i = 0; i < n; i++) {
        printf("%c ", p[i].name);
        for (int j = 0; j < time; j++) {
            if (print[i][j] == 1)
                printf(" ■");
            else
                printf(" □");
        }
        printf("\n");
    }
}

//FCFS
void FCFS() {
    int time = 0;
    int total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service;// 총 서비스 시간
    int pselect = 0;
    int be_pselect = 0;
    int printarr[NUM][SIZE] = { 0 };
    queue cpu_q;

    initQueue(&cpu_q);

    enqueue(&cpu_q, p[pselect].pid);

    while (total != 0) {
        pselect = dequeue(&cpu_q);

        // 큐로부터 프로세스를 제대로 불러온 경우
        if (pselect >= 0) {
            for (int i = 0; i < p[pselect].service; i++) {
                if (p[pselect].runtime == p[pselect].service) { //선택한 runtime과 service가 같으면 break
                    break;
                }
                total--; // 전체 서비스 시간 감소
                p[pselect].runtime++; // 해당 프로세스 runtime 1 증가
                printarr[pselect][time] = 1; // 실행표시 출력
                time += 1; // 시간 1 증가
                be_pselect = pselect; // 수행한 pselect 저장
                
                // 실행시간 동안 도착한 프로세스가 있으면 큐에 넣음
                for (int j = pselect+1; j < NUM; j++) {
                    if (time >= p[j].arrival) {
                        enqueue(&cpu_q, p[j].pid);
                    }
                }
            }
        }
        // 큐에 아무것도 없어 프로세스를 불러오지 못한 경우
        else {
            // 1 증가된 시간에서 도착한 것이 있으면 큐에 넣음
            for (int j = be_pselect+1; j < NUM; j++) {
                if (time >= p[j].arrival) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
        }
        // total 시간이 0이 되면 종료
        if (total == 0) {
            break;
        }
        // 실행할 프로세스가 없을 때, 공백을 출력하고 시간을 1 증가
        if (isEmpty(&cpu_q) == 1 ) {
            if (pselect >= 0) { //pselect가 0이상일 때 그래프에 넣음
                printarr[pselect][time] = 0;
            }
            time += 1;
            continue;
        }

    }
    // 출력
    sched_print(printarr, NUM, time);
}

//RR
void RR() {
    int time = 0;
    int timeslice = 0;
    int total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service; //총 서비스 시간
    int pselect = 0;
    int be_pselect = 0;
    int printarr[NUM][SIZE] = { 0 };
    queue cpu_q;

    initQueue(&cpu_q);

    enqueue(&cpu_q, p[pselect].pid);

    while (total != 0) {
        pselect = dequeue(&cpu_q);
        // 큐로부터 프로세스를 제대로 불러온 경우
        if (pselect >= 0) {
            // 완료된것이 큐에 들어와있으면 다른 프로세스로 변경
            if (p[pselect].runtime == p[pselect].service) {
                pselect = dequeue(&cpu_q);
            }

            // time quantum 설정
            if (cpu_q.timeq > (p[pselect].service - p[pselect].runtime)) {
                timeslice = (p[pselect].service - p[pselect].runtime);
            }
            else {
                timeslice = cpu_q.timeq;
            }

            // timeslice만큼 실행
            for (int j = 0; j < timeslice; j++) {

                total--; // 전체 서비스 시간 감소
                p[pselect].runtime++; // 해당 프로세스 runtime 1 증가
                printarr[pselect][time] = 1; // 실행표시 출력
                time += 1; // 시간 1 증가

                // 실행시간동안 들어온 큐가 있으면 큐에 넣음
                for (int k = 0; k < NUM; k++) {
                    if (time == p[k].arrival && pselect != k && p[k].runtime != p[k].service) {
                        enqueue(&cpu_q, p[k].pid);
                    }
                }
                be_pselect = pselect;
            }
            // 실행중인 프로세스가 끝나지 않았으면 다시 큐에 넣음
            if (p[pselect].runtime != p[pselect].service) {
                enqueue(&cpu_q, p[pselect].pid);
            }



        }
        // 큐에 아무것도 없어 프로세스를 불러오지 못한 경우
        else {
            // 1 증가된 시간에서 도착한 것이 있으면 큐에 넣음
            for (int j = 0; j < NUM; j++) {
                if (time == p[j].arrival && p[j].runtime != p[j].service) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
        }
        if (total == 0) {
            break;
        }
        // 실행할 프로세스가 없을 때, 공백을 출력하고 시간을 1 증가
        if (isEmpty(&cpu_q) == 1) {
            if (pselect >= 0) { //pselect가 0이상일 때 그래프에 넣음
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
    int total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service; // 총 서비스 시간
    int pselect = 0;
    int printarr[NUM][SIZE] = { 0 };
    queue cpu_q;
    int be_pselect=0;

    initQueue(&cpu_q);

    enqueue(&cpu_q, p[0].pid); //제일 처음거 넣기 

    while (total != 0) {
        pselect = dequeue(&cpu_q);

        // 큐로부터 프로세스를 제대로 불러온 경우
        if (pselect >= 0) {
            for (int i = p[pselect].runtime; i < p[pselect].service; i++) {
                total--; // 전체 서비스 시간 감소
                p[pselect].runtime++; // 해당 프로세스 runtime 1 증가
                printarr[pselect][time] = 1; // 실행표시 출력
                time += 1; // 시간 1 증가
                be_pselect = pselect;

                // 실행시간동안 도착한 프로세스가 있으면 큐에 넣음
                for (int j = pselect + 1; j < NUM; j++) {
                    if (time >= p[j].arrival) {
                        enqueue(&cpu_q, p[j].pid);
                    }
                }
                priority_queue(&cpu_q, 1, time); //우선순위로 정렬
            }
        }

        // 큐에 아무것도 없어 프로세스를 불러오지 못한 경우
        else {
            // 1 증가된 시간에서 도착한 것이 있으면 큐에 넣음
            for (int j = be_pselect + 1; j < NUM; j++) {
                if (time >= p[j].arrival) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
            priority_queue(&cpu_q, 1, time); //우선순위로 정렬
        }
        if (total == 0) {
            break;
        }
        // 실행할 프로세스가 없을 때, 공백을 출력하고 시간을 1 증가
        if (isEmpty(&cpu_q) == 1) {
            if (pselect >= 0) { //pselect가 0이상일 때 그래프에 넣음
                printarr[pselect][time] = 0;
            }
            time += 1;
            continue;
        }

    }
    //출력
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

    enqueue(&cpu_q, p[0].pid); //제일 처음거 넣기 

    while (total != 0) {
        pselect = dequeue(&cpu_q);
        // 큐로부터 프로세스를 제대로 불러온 경우
        if (pselect >= 0) {
            for (int i = p[pselect].runtime; i < p[pselect].service; i++) {
                total--; // 전체 서비스 시간 감소
                p[pselect].runtime++; // 해당 프로세스 runtime 1 증가
                printarr[pselect][time] = 1; // 실행표시 출력
                time += 1; // 시간 1 증가
                be_pselect = pselect;
                // 실행시간동안 도착한 프로세스가 있으면 큐에 넣음
                for (int j = pselect + 1; j < NUM; j++) {
                    if (time >= p[j].arrival) {
                        enqueue(&cpu_q, p[j].pid);
                    }
                }
                priority_queue(&cpu_q, 2, time); //우선순위로 정렬
            }
        }
        // 큐에 아무것도 없어 프로세스를 불러오지 못한 경우
        else {
            // 1 증가된 시간에서 도착한 것이 있으면 큐에 넣음
            for (int j = be_pselect + 1; j < NUM; j++) {
                if (time >= p[j].arrival) {
                    enqueue(&cpu_q, p[j].pid);
                }
            }
            priority_queue(&cpu_q, 2, time); //우선순위로 정렬
        }
        if (total == 0) {
            break;
        }
        // 실행할 프로세스가 없을 때, 공백을 출력하고 시간을 1 증가
        if (isEmpty(&cpu_q) == 1) {
            if (pselect >= 0) { //pselect가 0이상일 때 그래프에 넣음
                printarr[pselect][time] = 0;
            }
            time += 1;
            continue;
        }

    }
    //출력
    sched_print(printarr, NUM, time);
}


void lottery() {
    // 전체 : 0~99 => A: 75 (0~74), B: 25 (75~99)
    int ticket[2][20] = { 0 };
    int lotto[20];
    for (int i = 0; i < 20; i++) {
        lotto[i] = rand() % 100; //0~99 사이의 번호 20개를 배열에 받음

        if (lotto[i] < 75) { //0~74이면 행이 0인 배열에 1입력
            ticket[0][i] = 1;
        }
        else { //0~74이면 행이 1인 배열에 1입력
            ticket[1][i] = 1;
        }
    }

    // 스케줄러 실행 결과 출력
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