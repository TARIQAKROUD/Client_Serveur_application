#include<stdio.h>

#include<sys/socket.h>

#include<sys/types.h>

#include<netinet/in.h>

#include<netdb.h>

#include<string.h>

#define max 3000



main(){

  	FILE *P_FICHIER;

   	char FICHIER[30]={"\0"};

   	int s,a,b,c,r,longueur,t;

   	struct sockaddr_in serveur,client;

   	char msgs[max],msgc[20];

   	struct hostent *adr_h;

//Creation_Socket et affectation d'adresse+numero de port
printf("---------------------------------------------\n");
    printf("Initialisation du serveur \n");
printf("_____________________________________________\n");

	s = socket(AF_INET, SOCK_STREAM, 0);

  if( s == -1 ){
    perror("\n Erreur lors de la création du socket \n");
    exit(0);
  }

 	else {
printf("---------------------------------------------\n");printf("Socket est bien cree \n ");
printf("_____________________________________________\n");}


 //Structure_serveur

    serveur.sin_family=AF_INET;

    serveur.sin_addr.s_addr=INADDR_ANY;

    serveur.sin_port=htons(2502);

    if((b=bind(s,(struct sockaddr*)&serveur,sizeof(serveur)))==-1) {
                printf("---------------------------------------------\n");

	       perror("le socket n'est pas asscocié à aucune adresse:\n  ");
             printf("_____________________________________________\n");}

    else  {
            printf("---------------------------------------------\n");

  printf("l'affecation d'adresse au socket est bien reussi\n ");
printf("---------------------------------------------\n");
}


printf("---------------------------------------------\n");
	printf("*******Serveur de transfert de fichier realisé par TARIQ AKROUD  *******\n");
	printf("_____________________________________________\n");



//le serveur ecoute les client avec un maximum de clients=20
    if( listen(s, 20) == -1 ){
    perror("\n Erreur listen \n");
    exit(0);
    }
    printf("\n\n welcome to our data base \n ");

    longueur=sizeof(client);

    c = accept(s, (struct sockaddr_in *)&client, &longueur);

    if( c == -1 ){
    perror("\n echec de connexion \n");
    exit(0);
      }
     printf("_____________________________________________\n");
    printf(" Connexion réussie\n");
    printf("_____________________________________________\n");

	 printf("\nConnexion reussie avec le client\n");    
         printf("_____________________________________________\n");
    	

//commencer la communication avec le client

    for(;;){	  

	 	recv(c,FICHIER,30,0);

        P_FICHIER=fopen(FICHIER,"r");  // Creation du fichier a transmettre	



        if(!P_FICHIER) { 
                printf("*****************************************************\n");            

        	printf("Fichier introuvable!\n");
                printf("*****************************************************\n");            

            send(c,"non",strlen("non"),0);

              }

        else {

    		while (fgets(msgc,100,P_FICHIER)){   // Transmission ligne par ligne

       			t=send(c,msgc,100,0);

       			printf("%s\n",msgc);    

     		}

    

            fclose(P_FICHIER);// Fin du fichier

		        t=send(c,"444",4,0);// Envoi du code 444 pour indiquer la fin du transfert de fichier 

            a=recv(c,msgs,max,0);

            if(msgs[0]=='y')continue;

            else {
     printf("Merci pour l'utilisation de notre application\n");
    printf("Réalisé par:\n");
    printf("TARIQ AKROUD \n");
    printf("*************************Ecole Mohammadia d'ingenieurs**************************");
             break;}

   }

    printf("Merci pour l'utilisation de notre application\n");
    printf("Réalisé par:\n");
    printf("TARIQ AKROUD \n");
    printf("*************************Ecole Mohammadia d'ingenieurs**************************");
    return 0; 



  	  }

	

    close(c);   

    close(s);

}

