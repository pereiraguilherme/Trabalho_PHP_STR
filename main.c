// Arquivo: php.c
// Autor: Roland Teodorowitsch
// Data: 28 ago. 2018

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RESOURCES 5
#define MAX_TASKS     26
#define MAX_STEPS     20
#define MAX_TIME      1000

#define RUN    0
#define LOCK   1
#define UNLOCK 2

typedef struct {
  int p; //prioridade
  int a; //tempo de chegada
  int ns; //numero de computaçoes
  int s[MAX_STEPS][2]; //steps [run, lock, unlock]
  char name;
  // ...
} TASK;

int main() {
  int  num_resources, num_tasks, i, j, value;
  TASK tasks[MAX_TASKS], orderedTaks[MAX_TASKS];
  char word[20];
  char result[MAX_RESOURCES+1][MAX_TIME];
  int  sim_time = -1;
  char* provisorio;
  int runs;
  while (1) {

     // LEITURA
     //num_resources numero de coisas que podem ser usadas pelas taks
     //num_tasks é numero de tasks que vao ter de ser escalonadas
     scanf("%d %d", &num_resources, &num_tasks);
     if (num_tasks == 0)
        break;
     for (i=0; i<num_tasks; ++i) {
         //prioridade   --- tempo de chegada  --- numero de computações
         scanf("%d %d %d", &(tasks[i].p), &(tasks[i].a), &(tasks[i].ns) );
         for (j=0; j<tasks[i].ns; ++j) {
             //word é pra
             scanf("%s %d", word, &value);
             if (strcmp(word,"run")==0 || strcmp(word,"RUN")==0)
                tasks[i].s[j][0] = RUN;
             else if (strcmp(word,"lock")==0 || strcmp(word,"LOCK")==0)
                tasks[i].s[j][0] = LOCK;
             else if (strcmp(word,"unlock")==0 || strcmp(word,"UNLOCK")==0)
                tasks[i].s[j][0] = UNLOCK;
             else
                exit(1);
             tasks[i].s[j][1] = value;
         }
     }

    //Ordena por tempo de chegada as tasks
    memcpy(orderedTaks, reorderTasks(tasks, num_tasks), sizeof(tasks));

    //Nomeia de alfabeticamente as tasks 
    for(i=0;i<sizeof(tasks); i++){
        tasks[i].name = 'A' + i;
    }
    //Começa simulação sem os a atribuição de requisitos
    for(i=0;i<num_tasks; i++){
        if(sim_time < orderedTaks[i].a){
            for(j=0; j<orderedTaks[i].ns; j++){
                if(orderedTaks[i].s[j][0] == "RUN"){
                    for(runs =0; runs<orderedTaks[i].s[j][1];runs++){
                        provisorio = orderedTaks[i].name;
                        sim_time++;
                    }
                } 
            }
        }
    }
    
    //  // provisorio:
    //  sim_time = 20;
    //  for (i=0; i<num_resources+1; ++i) {
    //      for (j=0; j<sim_time; ++j) {
    //          result[i][j] = '.';
    //      }
    //  }
    //  // fim do provisorio.

     // MOSTRAR RESULTADOS
     for (i=0; i<num_resources+1; ++i) {
         for (j=0; j<sim_time; ++j) {
             putchar(result[i][j]);
         }
         putchar('\n');
     }
     putchar('\n');

  }
  return 0;
}

TASK * setTasksName(TASK tasks[]){
    int i;
    for(i=0;i<sizeof(tasks); i++){
        tasks[i].name = 'A' + i;
    }
    return tasks;
}
TASK * reorderTasks(TASK tasks[], int numTasks){
    int i =0;
    TASK orderedTasks[numTasks];

    for(i=0; i<numTasks; i++){
        if(sizeof(orderedTasks)==0){
            orderedTasks[i] = tasks[i];
        }
        if(tasks[i].a < orderedTasks[i].a){
            orderedTasks[i+1] = orderedTasks[i];
            orderedTasks[i] = tasks[i];
        }
        else orderedTasks[i] = tasks[i];
    }
    return orderedTasks;
}
