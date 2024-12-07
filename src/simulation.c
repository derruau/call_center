#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "call.h"
#define  nomFichier "registre d'appels.txt" 
#define nomFichier2 "données de la simulation.txt"
#include "../include/call.h"
#include "../include/queue.h" 
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
      fprintf(fichier, "%d  ", clients[i]->id);
      fprintf(fichier, "%s  ", clients[i]->tel);
      fprintf(fichier, "%s  ", clients[i]->client_name);
      fprintf(fichier, "%d:%d:%d  ", moment_deb->tm_hour, moment_deb->tm_min, moment_deb->tm_sec );
      fprintf(fichier, "%d:%d:%d  ", moment_fin->tm_hour, moment_fin->tm_min, moment_fin->tm_sec);
      fprintf(fichier, "%d:%d:%d  ", wait->tm_hour, wait->tm_min, wait->tm_sec);


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
	
float simulation_time_avg(long *L; int size)
{
	float avg=0;
	for (int i=0; i<size; i++)
	{
		avg= avg+L[i];
	}
	
	avg=avg/size; 
	return avg; 
}

	

