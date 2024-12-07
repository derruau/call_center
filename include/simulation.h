#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "call.h"
#define  nomFichier "registre d'appels.txt" 
#include "../include/call.h" 

typedef struct 
{
   int heure;
   int min;
   int sec;
} Tim;

Tim *Convert_Time(time_t* t);
void start_simulation(Call **clients, int clients_size);
long simulation_max(long *L, int size);
long simulation_min(long *L, int size);
long *simulation_wait(Call **clients, int clients_size);
long *simulation_end(Call **clients, int clients_size);
long *simulation_answer(Call **clients, int clients_size);
float simulation_time_avg(long *L; int size);
