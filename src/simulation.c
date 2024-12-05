#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "call.h"
#define  nomFichier "registre d'appels.txt" 
#include "../include/call.h" 
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

void start_simulation(Call **clients, int clients_size)
{
   FILE*  fichier= fopen(nomFichier, "w" ) ;
  /* fprintf(fichier, "ID client  ");
   fprintf(fichier, "Nom  ");
   fprintf(fichier,"Heure d'arrivée  ");
   fprintf(fichier, "Durée d'attente  ");
   fprintf(fichier, "Heure de début de service  ");
   fprintf(fichier, "Heure de fin de service  ");*/
   struct tm *moment_deb;
   struct tm *moment_fin;
   for (int i=0; i<clients_size; i++ )
   {
      moment_deb= convert_time(&clients[i]->call_start);
      moment_fin= convert_time(&clients[i]->call_start);     
      fprintf(fichier, "\n");
      fprintf(fichier, "%d", clients[i]->id);
      fprintf(fichier, "%s", clients[i]->client_name);
      fprintf(fichier, "%d:%d:%d", moment_deb->tm_hour, moment_deb->tm_min, moment_deb->tm_sec );
      fprintf(fichier, "%d", clients[i]->wait_time);
      fprintf(fichier, "%d:%d:%d", moment_fin->tm_hour, moment_fin->tm_min, moment_fin->tm_sec);; 
      


   }
   fclose(fichier);
}

