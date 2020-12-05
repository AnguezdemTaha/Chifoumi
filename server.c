#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>

#include <signal.h>

void alarm_handler(int a){
//printf("vous avez deppaser le temps");
//write(sd,demande,sizeof(demande));
//alarm(20);
//exit(0);
}
int main (int argc ,char *argv[]){
int sd, ns, nb,ns2,sd2;

char etat1[256]="n",etat2[256]="n";
//variable qui enregistre les score des jouers: n'est pas utilisé 
int score1=0;
int score2=0;
char score11[50];
char score22[50];
//
char request[256];
char response[256];

int repeter=1;
char repeter1[256],repeter2[256];

char request2[256];
char response2[256];

signal(SIGALRM,alarm_handler);

//socket pour server et client1
struct sockaddr_in serveraddr;
sd=socket(AF_INET, SOCK_STREAM,0);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=1500;
serveraddr.sin_addr.s_addr=INADDR_ANY;
bind(sd,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
listen(sd,2);
ns=accept(sd,0,0);

//socket pour server et client2
struct sockaddr_in serveraddr2;
sd2=socket(AF_INET, SOCK_STREAM,0);
serveraddr2.sin_family=AF_INET;
serveraddr2.sin_port=1501;
serveraddr2.sin_addr.s_addr=INADDR_ANY;
bind(sd2,(struct sockaddr *)&serveraddr2, sizeof(serveraddr2));
listen(sd2,2);
ns2=accept(sd2,0,0);

//dans le jeu
while(repeter==1){
read(ns, request, sizeof(request));
read(ns2, request2, sizeof(request2));
//fonction a remplire apres
if((strcmp(request,"c")==0 && strcmp(request2,"f")==0) || (strcmp(request,"p")==0 && strcmp(request2,"c")==0) || (strcmp(request,"f")==0 && strcmp(request2,"p")==0)){
strcpy(etat1,"Gagné!!!");
strcpy(etat2,"Perdu!!!");
++score1;
}




else{
if((strcmp(request,"f")==0 && strcmp(request2,"c")==0) || (strcmp(request,"c")==0 && strcmp(request2,"p")==0) || (strcmp(request,"p")==0 && strcmp(request2,"f")==0)){
strcpy(etat1,"Perdu!!!");
strcpy(etat2,"Gagné!!!");
}
else{
if((strcmp(request,"f")==0 && strcmp(request2,"f")==0) || (strcmp(request,"c")==0 && strcmp(request2,"c")==0) || (strcmp(request,"p")==0 && strcmp(request2,"p")==0)){
strcpy(etat1,"Egalité");
strcpy(etat2,"Egalité");
}
else{
strcpy(etat1,"Mauvais choix");
strcpy(etat2,"Mauvais choix");}}
}


//printf("reception d'un neuveux message : %s",request);
//printf("\n reception d'un neuveux message2 : %s",request2);
//printf("\n votre msg :");
//scanf("%s",&response);

//envoyer l'etat de jour au chaque jouer(win or lose)
write(ns,etat1,sizeof(etat1));
write(ns2,etat2 ,sizeof(etat2));

//printf("waiting");

//lecture estceque les jouer vont repeter
read(ns, repeter1, sizeof(repeter1));
read(ns2, repeter2, sizeof(repeter2));

//printf("test %s %s",repeter1,repeter2);

//envoyer au chauqe jouer est-ce-que son enemy veut jouer again
write(ns,repeter2,sizeof(repeter2));
write(ns2,repeter1 ,sizeof(repeter1));

}
close(ns);
close(sd);
}


