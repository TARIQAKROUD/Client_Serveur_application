#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h> 
#include<stdlib.h> 
#define max 3000

main()
{    

     FILE *FICHIER_cree; 
     int s,a,t;
     char FICHIER[30];
     char msgs[max],msgc[100];

     struct hostent *adr_h;
     struct sockaddr_in serveur;

     
     //Creation_socket,paramétres de serveur et adressage

     s = socket(AF_INET, SOCK_STREAM, 0);
     if(s==-1){
        perror("\n  le socket n'est pas cree \n");
        exit(0);
      }
     printf("\n Socket est bien cree");
     serveur.sin_family=AF_INET;
     serveur.sin_port=htons(2502);
     if((adr_h=gethostbyname("127.0.0.1"))==0) 
	       perror("\nla destination introuvable");
     else bcopy((char *)adr_h->h_addr,(char *)&serveur.sin_addr,adr_h->h_length);

     //vérifié la connexion evec le serveur
     if(connect(s,(struct sockaddr *)&serveur,sizeof(serveur))<0)
            perror("\nEchec de la connexion avec le serveur");
     else { 
            printf("\n=============================================\n");
	     printf("\n la communication avec le serveur avec succé\n");
	      printf("\n=============================================\n");
	     //debut de communication
		   for(;;){
		       printf("entrer le nom de fichier que vous voulez: "); 
           scanf("%s",FICHIER);
           t=send(s,FICHIER,30,0);
           a=recv(s,msgc,100,0); 
           if(msgc[0]=='n'&& msgc[1]=='o'){ 
                 printf("%s\n",msgc);
                 return 0;
               }
           else {
                FICHIER_cree = fopen("Fichier recu","a+");  // Création du fichier à transmettre 
                 if(FICHIER_cree)
                                  printf("\n=============================================\n");
		                 printf("Fichier demander est : \n");        
                                  printf("=============================================\n");
                         
           do{
	             recv(s,msgc,100,0);    // Reception ligne par ligne
               if(msgc[0]=='4'&& msgc[1]=='4') {break;}  // Fin de transmission de fichier

               else{
	                 puts(msgc);
                   fprintf(FICHIER_cree,"%s",msgc);
                 }     
		       } while(1);
 
           fclose(FICHIER_cree);
           printf("Fin \n");
           printf("vous voulez un autre fichier? (y/n)\n");
           scanf("%s",&msgs);
           if(msgs[0]=='y'){ 
               t=send(s,msgs,2,0);
               continue;
             }
           else{
               return 0;
             }            

          }

      }

	}
       close(s);
}
