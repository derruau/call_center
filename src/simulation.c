#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "call.h"
#define  nomFichier "registre d'appels.txt" 
#define nomFichier2 "données de la simulation.txt"
#include "../include/call.h"
#include "../include/queue.h" 
#include "../include/helper.h"
/*
#define lambda 1
#define minsrv 2 // debut du service 
#define maxsrv 5 // fin du service 
#define op_number 5*/
typedef struct 
{
   int heure;
   int min;
   int sec;
} Tim;



struct tm* convert_time(time_t* t)
{
   struct tm *T;
   T=localtime(t);
   
   return T;
}


		
	


void simulation_register(Call **clients, int clients_size)
{
   FILE*  fichier= fopen(nomFichier, "w+" ) ;
   /*fprintf(fichier, "ID client  ");
   fprintf(fichier, "Nom  ");
   fprintf(fichier,"Heure d'arrivée  ");
   fprintf(fichier, "Durée d'attente  ");
   fprintf(fichier, "Heure de début de service  ");
   fprintf(fichier, "Heure de fin de service  ");*/
   struct tm *moment_deb;
   struct tm *moment_fin;
   struct tm *wait; 
   for (int i=0; i<clients_size; i++ )
   {
      moment_deb= convert_time(&clients[i]->call_start);
      moment_fin= convert_time(&clients[i]->call_end );  
      wait = convert_time(&clients[i]->wait_time);   
      fprintf(fichier, "\n");
      fprintf(fichier, "ID client: %d  ", clients[i]->id);
      fprintf(fichier, "Nom: %s  ", clients[i]->tel);
      fprintf(fichier, "Prénom: %s  ", clients[i]->client_name);
      fprintf(fichier, "Heure d'arrivée: %s ", ctime(&clients[i]->call_start));
      fprintf(fichier, "Heure de fin de service: %s ", ctime(&clients[i]->call_end));
      fprintf(fichier, "Durée d'attente: %ld  ",clients[i]->wait_time);


   }
   fclose(fichier);
}

long simulation_max(long *L, int size)
{
	long max=L[0];
	for (int i=0; i<size; i++)
	{
		if (max<=L[i])
		{
			max=L[i];
		}
	}
	return max;
}

long simulation_min(long *L, int size)
{
	long min=L[0];
	for (int i=0; i<size; i++)
	{
		if ( min>=L[i])
		{
			min=L[i];
		}
	}
	return min;
}
			

long *simulation_wait(Call **clients, int clients_size)
{
	long *wait_list;
	wait_list=(long*) malloc(sizeof(long)*clients_size);
	for (int i=0; i<clients_size; i++)
	{
		wait_list[i]=clients[i]->wait_time;
	}
	return wait_list; 
}	

long *simulation_end(Call **clients, int clients_size)
{
	long *end_list;
	end_list=(long*) malloc(sizeof(long)*clients_size);
	for (int i=0; i<clients_size; i++)
	{
		end_list[i]=clients[i]->call_end;
	}
	return end_list;
}

long *simulation_start(Call **clients, int clients_size)
{
	long *start_list;
	start_list=(long*) malloc(sizeof(long)*clients_size);
	for (int i=0; i<clients_size; i++)
	{
		start_list[i]=clients[i]->call_start;
	}
	return start_list;
}

long *simulation_answer(Call **clients, int clients_size)
{
	long *answer_list;
	answer_list= (long*) malloc(sizeof(long)*clients_size);
	for (int i=0; i<clients_size; i++)
	{
		answer_list[i]=clients[i]->call_end - clients[i]->call_end; 
	}
	return answer_list;
}
	
float simulation_time_avg(long *L, int size)
{
	float avg=0;
	for (int i=0; i<size; i++)
	{
		avg= avg+L[i];
	}
	
	avg=avg/size; 
	return avg; 
}

void simulation_queue(Queue *q, Call **clients, int clients_size)
{
	long *start=simulation_start(clients, clients_size);
	long min= start[0];
	int k=0;
	Call *c;
	for (int i=0; i<clients_size; i++)  //classement des clients par ordre d'arrivée
		for (int j=i; j<clients_size; j++)
		{
			if (min>=start[j])
			{
				min=start[j];
				k=j;
			}
			start[k] =start[i];
			start[i]=min;
			c=clients[i];
			clients[i]=clients[k];
			clients[k]=c;
		}
	
	
	for (int i=clients_size-1; i>0; i--)
	{
		queue_enqueue(q, clients[i]);
	}		
	
}


void simulation_running(Queue *q, int operators, Call **clients)
{
	Call *ops[operators];
	time_t t0= clients[0]->call_start;
	time_t t1= time(NULL); 
	int k=0; 
	time_t t2;
	time_t t3;
	double running_time;
	running_time=-difftime(t1,t2); 
	for (int i=0; i<operators; i++)
		{
			t2=time(NULL);
			running_time=difftime(t1,t2); 
			ops[i]= queue_dequeue(q);
			ops[i]->wait_time= -helper_add_seconds(ops[i]->wait_time,running_time); 
			ops[i]->call_end=ops[i]->call_end+ops[i]->wait_time;
			clients[k]->wait_time=ops[i]->wait_time;
			clients[k]->call_end=ops[i]->call_end;
			k++;
			
		}	
	while(!queue_is_empty(q))
	{
		for (int i=0; i<operators; i++)
		{
			t2=time(NULL);
			running_time=difftime(t1,t2);
			t3=t1+running_time;  
			if (t3==ops[i]->call_end)
			{
				ops[i]= queue_dequeue(q); 
				ops[i]->wait_time=-helper_add_seconds(ops[i]->wait_time,running_time); 
				ops[i]->call_end=ops[i]->call_end+ops[i]->wait_time;
				clients[k]->wait_time=ops[i]->wait_time;
				clients[k]->call_end=ops[i]->call_end;
				k++;
				
			}
		}	
	}
}
	
void simulation_stat(Call **clients, int clients_size)
{
	FILE*fichier= fopen(nomFichier2, "w+");
	long* wait_list=simulation_wait(clients,clients_size);
	long wait_avg=simulation_time_avg(wait_list, clients_size); 
	long wait_max=simulation_max(wait_list,  clients_size); 
	long wait_min=simulation_min(wait_list, clients_size);
	long *start_list= simulation_start(clients,clients_size);
	long *end_list=simulation_start(clients, clients_size); 
	long *answer_list= simulation_answer(clients, clients_size); 
	long answer_avg= simulation_time_avg(answer_list, clients_size);
	long end_simulation= simulation_max(end_list, clients_size);
	float call_debit= clients_size/24.0;
	fprintf(fichier,"temps min d'attente:");
	fprintf(fichier,"%ld ", wait_min);
	fprintf(fichier,"\n");
	fprintf(fichier,"temps moyen d'attente:");
	fprintf(fichier," %ld", wait_avg);
	fprintf(fichier,"\n");
	fprintf(fichier,"temps max d'attente:");
	fprintf(fichier," %ld", wait_max);
	fprintf(fichier,"\n");
	fprintf(fichier,"debit journalier d'appels:");
	fprintf(fichier," %f", call_debit);
	fprintf(fichier,"\n");
	fprintf(fichier,"temps de reponse moyen: ");
	fprintf(fichier,"%ld", answer_avg);
	fprintf(fichier,"\n");
	fprintf(fichier,"heure de fin de dernier service: ");
	fprintf(fichier,"%ld", end_simulation);
	fprintf(fichier,"\n");
	fclose(fichier);
}
