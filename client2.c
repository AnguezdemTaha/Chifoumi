#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>

#include <signal.h>

#include <stdlib.h>
#include <stdio.h>

void alarm_handler(int a){
printf("Vous avez dépassé le temps\n");
exit(0);
}
int main (int argc,char *argv[]){
int sd1;
struct sockaddr_in serveraddr;
char response[256];
char request[256];

int score1=0;
int score2=0;

char repeter[256]="oui";char repeter1[256];

signal(SIGALRM,alarm_handler);

sd1=socket(AF_INET, SOCK_STREAM,0);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=1501;
serveraddr.sin_addr.s_addr=INADDR_ANY;
 if(connect(sd1,(struct sockaddr *)&serveraddr, sizeof(serveraddr))<0) exit(0);

while(strcmp(repeter,"oui")==0){
printf("\n Choisissez entre : c(Ciseaux), p(Pierre), f(Feuille) :\n");
alarm(30);
scanf("%s",&request);
printf("...Veillez attendre le choix de l'autre joueur... \n");
write(sd1,request, sizeof(request));
read(sd1,response, sizeof(response));
if(strcmp(response,"n")==0){
printf("L'autre joueur n'a pas choisi dans le temps permis");
close(sd1);

}
if(strcmp(response,"Gagné!!!")==0){
++score1;

}
if(strcmp(response,"Perdu!!!")==0){
++score2;

}
printf("%s\n",response);
printf("Score: \nVous:%d \nEnemy: %d",score1,score2);
alarm(30);
printf("\nSouhaitez-vous rejouer?    Veuillez répondre par oui ou non \n");
scanf("%s",&repeter);
write(sd1,repeter, sizeof(repeter));
read(sd1,repeter1, sizeof(repeter1));
if(strcmp(repeter1,"oui")!=0){
strcpy(repeter,"non");}
}
close(sd1);

}



