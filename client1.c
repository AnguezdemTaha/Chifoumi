#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>


#include <signal.h>

#include <stdlib.h>
#include <stdio.h>

//la fonction d'alarm 
void alarm_handler(int a){
printf("Vous avez dépassé le temps\n");
//write(sd,demande,sizeof(demande));
//alarm(20);
exit(0);
//close(sd);

}


int main (int argc,char *argv[]){
int sd1;
struct sockaddr_in serveraddr;

char response[256];
char request[256];

//variable pour les scores
int score1=0;
int score2=0;

//variable indique est-ce-que ce jouer veut repeter le jeu
char repeter[256]="oui";

//variable a lire qui indique est-ce-que l'autre jouer veut repeter le jeu
char repeter2[256];

//association d'alarm avec la fonction decrier dans le haut
signal(SIGALRM,alarm_handler);

//conexion+... (sockets)
sd1=socket(AF_INET, SOCK_STREAM,0);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=1500;
serveraddr.sin_addr.s_addr=INADDR_ANY;
 if(connect(sd1,(struct sockaddr *)&serveraddr, sizeof(serveraddr))<0) exit(0);

//debut de jeu
while(strcmp(repeter,"oui")==0){


printf("\n Choisissez entre : c(Ciseaux), p(Pierre), f(Feuille) :\n");
//si le jouer passer beucoup de temps sans saisir on va exit 
alarm(30);
scanf("%s",&request);
printf("...Veillez attendre le choix de l'autre joueur... \n");
//envoie du choix de jouer
write(sd1,request, sizeof(request));
//lecture de l'etat(win or lose) d'apres le server
read(sd1,response, sizeof(response));
//au cas le server nous a repondu par "n" ca signifier que l'autre jouer n'a pas choisi dans le temps desirer
if(strcmp(response,"n")==0){
printf("L'autre joueur n'a pas choisi dans le temps permis");
close(sd1);
}
//else
//cas gagner incriment son score
if(strcmp(response,"Gagné!!!")==0){
++score1;
}
//cas lose incriment le score de l'autre jouer
if(strcmp(response,"Perdu!!!")==0){
++score2;

}
printf("%s\n",response);

//affichage de scores
printf("Score: \nVous:%d \nEnemy: %d",score1,score2);
alarm(30);
printf("\nSouhaitez-vous rejouer?    Veuillez répondre par oui ou non \n");
scanf("%s",&repeter);
//envoyer au server que je veut repeter ou non
write(sd1,repeter, sizeof(repeter));
//lecture d'apres le server est-ce-que l'autre jouer veut repeter
read(sd1,repeter2, sizeof(repeter2));
//si non on va afecter non au repeter et come ca la bocle va stoper
if(strcmp(repeter2,"oui")!=0){
strcpy(repeter,"non");}
}
close(sd1);

}


