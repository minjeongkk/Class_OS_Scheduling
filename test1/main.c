#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define NUM 5

typedef struct Process {
    char name;
    int arrival; //도착시간
    int service;
    int runtime; //실제 실행시간
}process;

void sched_print(int print[][SIZE], int n, int time) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < time; j++) {
            if (print[i][j] == 1)
                printf("■");
            else
                printf("□");
        }
        printf("\n");
    }
}

int main() {

    process p[NUM];

    int time, total, pselect;

    p[0].name = 'A';
    p[0].arrival = 0;
    p[0].service = 3;
    p[0].runtime = 0;

    p[1].name = 'B';
    p[1].arrival = 2;
    p[1].service = 6;
    p[1].runtime = 0;

    p[2].name = 'C';
    p[2].arrival = 4;
    p[2].service = 4;
    p[2].runtime = 0;

    p[3].name = 'D';
    p[3].arrival = 6;
    p[3].service = 5;
    p[3].runtime = 0;

    p[4].name = 'E';
    p[4].arrival = 8;
    p[4].service = 2;
    p[4].runtime = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = i+1; j < 5; j++) {
            if (p[i].arrival > p[j].arrival) {
                process tmp;
                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
    
    int print[NUM][SIZE] = { 0 };

    time = 0;
    total = p[0].service + p[1].service + p[2].service + p[3].service + p[4].service;
    pselect = 0;
    
    while (total != 0) {
        if (p[pselect].arrival > time) {
            print[pselect][time] = 0;
            time += 1;
        }
        
        for (int i = 0; i < p[pselect].service; i++) {
            total--;
            p[pselect].runtime++;
            print[pselect][time] = 1;
            time+=1;
        }
        pselect += 1;

    }

    sched_print(print, NUM, time);


}

