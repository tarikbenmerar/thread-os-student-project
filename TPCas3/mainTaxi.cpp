 #include <sys/types.h>
 #include <sys/socket.h>
 #include <stdio.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <unistd.h>
 #include <pthread.h>
 #include "taxis.h"

 int main()
 {

   int server_sockfd, client_sockfd;
   int server_len;socklen_t client_len;
   struct sockaddr_in server_address;
   struct sockaddr_in client_address;
   client clt; 
     
  //1- Créer le serveur Taxi 
     printf("[Taxi]: Lancement du serveur de Taxi \n");
     server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
     server_address.sin_family = AF_INET;
     server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
     server_address.sin_port = 9734;
     server_len = sizeof(server_address);
     bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
 
 
  //2- Attendre la connexion du verificateur 
     printf("[Taxi]: En attente de la connexion du verificateur \n");
     listen(server_sockfd, 5);
     client_len = sizeof(client_address);
     client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
 
  //3- Créer la classe Taxis
     printf("[Taxi]: Lancement des taxis\n");
     Taxis taxis(client_sockfd);
  
  //4- Lancer les Taxis
     taxis.lancer_taxi();
  
  //5- Envoyer au verificateur la fin de la simulation
      write(client_sockfd, &clt, sizeof(client)); 
      printf("[Taxi]: Fin de la simulation\n");
     
  //6- Fermer la connexion avec le verificateur
     close(client_sockfd);
  


 }

























