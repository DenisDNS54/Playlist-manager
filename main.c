#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
typedef struct
{
    char autor[30];
    char nume[30];
}melodii;
melodii v[100];
typedef struct {
    char name[30];
    melodii v[100];
    float rating;
}playlist;
playlist play[100];

int limitaplaylist()
{
    for (int i = 0; i < 100; i++)
        if (strcmp(play[i].name,"")==0)
        {
            return i;
        }
}
int limita_melodii(int indx)
{
    for (int i = 0; i < 100; i++)
        if (strcmp(play[indx].v[i].nume,"")==0)
        {
            return i;
        }
}

int adaugarePlaylist(char name[30],float rating)
{
    for (int i = 0; i < 100; i++)
        if (strcmp(play[i].name,"")==0)
        {
            strcpy(play[i].name,name);
            play[i].rating=rating;
            return i;
        }
}
void adaugare_melodii(char titlu[30],char autor[30],int index,int index2)
{

    strcpy(play[index].v[index2].autor,autor);
    strcpy(play[index].v[index2].nume,titlu);
}


void sterge_melodie(int index,int indexp)
{
    for(int i=index; i < 100; i++)
    {
        strcpy(play[indexp].v[i].autor,play[indexp].v[i+1].autor);
        strcpy(play[indexp].v[i].nume,play[indexp].v[i+1].nume);
    }
    int ultim=limita_melodii(indexp);
    strcpy(play[indexp].v[ultim].autor,"");
    strcpy(play[indexp].v[ultim].nume,"");
}

void sterge_playlist(int index)
{
    int limit=limitaplaylist(play);
    for(int i=index; i < limit; i++)
    {
        play[i]=play[i+1];
    }
    //int ultim=limitaplaylist(play);
    //strcpy(play[ultim].name,"");
}

void citire()
{

    char numeplaylist[30],numef[30],autorf[30],str[30];
    int i=0,i2=0,ok=0;
    float ratingf=0;
    FILE* fp = fopen("Playlist.txt","r");
    while(!feof(fp))
    {
        if(ok==0)
        {
        fgets(numeplaylist, 30, fp);
        numeplaylist[strlen(numeplaylist)-1]=NULL;
        strcpy(play[i].name,numeplaylist);
        //printf("Playlist");printf("%s",play[i].name);
            ok=1;//printf("%d\n",ok);
            i2=0;
        }
        fgets(numef, 30, fp);
        //printf("%s",numef);
        ratingf=atof(numef);
        if(ratingf>0)
            {
                //printf("intra aici");
                strcpy(str, numef);
                ratingf = atof(str);
                play[i].rating=ratingf;
                //printf("Raiting");printf("%.2f\n",play[i].rating);
                i++;
                ok=0;//printf("%d\n",ok);
                ratingf=0;
            }
        else
        {
            fgets(autorf, 30, fp);
            numef[strlen(numef)-1]=NULL;
            strcpy(play[i].v[i2].nume,numef);
            //printf("Nume");printf("%s",play[i].v[i2].nume);
            autorf[strlen(autorf)-1]=NULL;
            strcpy(play[i].v[i2].autor,autorf);
            //printf("autor");printf("%s",play[i].v[i2].autor);
            i2++;
        }


    }
    fclose(fp);
    sterge_playlist(i-1);
}

void scriere()
{
    FILE* fp=fopen("Playlist.txt","w");
    int limplay=limitaplaylist();
    for(int i=0;i<limplay;i++)
    {
        fprintf(fp, "%s\n", play[i].name);
        int limmel=limita_melodii(i);
        for(int j=0;j<limmel;j++)
        {

            fprintf(fp, "%s\n",play[i].v[j].nume);
            fprintf(fp, "%s\n",play[i].v[j].autor);
        }
        fprintf(fp, "%.2f\n",play[i].rating);
    }
    fclose(fp);

}
void sortare()
{
    playlist aux[10];
    int limit = limitaplaylist(play);
    for(int i=0;i<limit;i++)
    {
        if(play[i].rating<play[i+1].rating)
        {
            aux[0]=play[i];
            play[i]=play[i+1];
            play[i+1]=aux[0];
        }
    }
}


void menu(){
    citire();
    sortare();
    scriere();
    system("cls");
    int pozitie = 1;
    int keyPressed = 0;
    #define MAX 2
    #define MIN 1

    //while(keyPressed !=)
    while(1){

        system("cls");

        printf("[===  MENIU PRINCIPAL  ===]\n");
        navigare(1,pozitie); printf("Creaza un nou playlist\n");
        navigare(2,pozitie); printf("Vizioneaza playlist existent\n");

        keyPressed = getch();

        if(keyPressed == 80 && pozitie != MAX){
            pozitie++;
                                        }

        else if(keyPressed == 72 && pozitie !=MIN){
                pozitie--;
                                            }
            else{
                pozitie = pozitie;
                }


       if(pozitie == 1 && keyPressed == 13)
{
    system("cls");
    char a[30],rating[30],b[30],name[30]=" ";
    int index=0,indexp,index2=0;
    printf("Nume playlist:");
    scanf("%s", &name);
    float rating1=0;
                //system("cls");
                printf("introduceti rating:");
                scanf("%s",&rating);
                rating1=atof(rating);
    index=adaugarePlaylist(name,rating1);
    fflush(stdin);
        int poz2=1;
    while (1)
    {
        system("cls");
        printf("Nume playlist:");
        printf("%s\n",play[index].name);
        navigare(1,poz2);printf("Adauga\n");
        if(strcmp(play[index].v[0].nume,"")!=0)
        {navigare(2,poz2);printf("Terminat\n");}

        keyPressed=getch();
        if(keyPressed == 80 && poz2 != MAX)
            {
                poz2++;
            }

        else
            if(keyPressed == 72 && poz2 != MIN)
            {
                poz2--;
            }
        if(poz2 == 1 && keyPressed == 13)
        {
            system("cls");
            printf("----");
            printf("%s",&name);
            printf("----\n");
            printf("Nume:");
            gets(a);
            fflush(stdin);
            //scanf("%s",a);
            printf("\n");
            printf("Autor:");
            gets(b);
            fflush(stdin);
            //scanf("%s",b);
            adaugare_melodii(a,b,index,index2);
            index2++;

        }
        if(poz2 == 2 && keyPressed == 13)
            {
                break;
            }

    }
}
sortare();
scriere();
#define MAX 6
#define MIN 1


        if(pozitie == 2 && keyPressed == 13){
            int delplay;
            int poz3=1;
            int j;
                while(1){
            system("cls");
            printf("---Playlist-uri---\n");
            int limita=limitaplaylist(play);
                    for(j=0;j<limita;j++)
                        {
                            navigare(j+1,poz3);printf("%d",j+1);printf("%s",play[j].name);
                            printf(" *");printf("%.2f",play[j].rating);printf("*\n");
                        }


                    navigare(j+1,poz3); printf("sterge playlist\n");
                    navigare(j+2,poz3); printf("Terminat\n");
                    #define MAX j+2
                    keyPressed = getch();

                if(keyPressed == 80 && poz3 != MAX){
                    poz3++;
                                        }

                else if(keyPressed == 72 && poz3 != MIN){
                    poz3--;
                    //break;
                                            }
                else{
                    poz3 = poz3;
                    }
                if(poz3==MAX-1 && keyPressed==13)
                {
                    poz3++;
                    int ok=1;
                    while(ok==1){
                    printf("Introdu playlist-ul pe care doriti sa il stergeti:");
                    scanf("%d",&delplay);
                        if(delplay>0 && delplay<=j+1)
                            ok=0;
                    }
                    //printf("Ajunge");
                    //printf("%d",delplay);
                    delplay=delplay-1;
                    sterge_playlist(delplay);
                }
                if(poz3>=MIN && poz3<=MAX-2 && keyPressed==13)
                {
                    //keyPressed==0;
                    int k=0;
                    int pozm=1;
                    while(1)
                    {
                    system("cls");
                    printf("---");
                    printf("%s",play[poz3-1].name);printf("---");
                    printf(" *");printf("%.2f",play[poz3-1].rating);printf("*\n");
                    int limita2=limita_melodii(poz3-1);
                    for(k=0;k<limita2;k++)
                    {
                        navigare(k+1,pozm);printf("%d",k+1);  printf("%s",play[poz3-1].v[k].nume);
                                             printf("-");
                                             printf("%s\n",play[poz3-1].v[k].autor);
                    }
                        navigare(k+1,pozm); printf("Adauga melodie\n");
                        navigare(k+2,pozm); printf("Sterge melodie\n");
                        navigare(k+3,pozm); printf("Terminat\n");

                     keyPressed = getch();
                    if(keyPressed == 80 && pozm != k+3){
                            pozm++;
                                        }

                    else if(keyPressed == 72 && pozm != 1){
                            pozm--;
                                            }
                    if(pozm==k+1 && keyPressed==13)
                    {
                        char a1[30],b1[30];
                        system("cls");
                        printf("----");
                        printf("%s",play[poz3-1].name);
                        printf("----\n");
                        printf("Nume:");
                        gets(a1);
                        //scanf("%s",&a);
                        fflush(stdin);
                        printf("\n");
                        printf("Autor:");
                        gets(b1);
                        //scanf("%s",&b);
                        fflush(stdin);
                        int var1,var2;
                        var1=poz3-1;
                        var2=k;
                        adaugare_melodii(a1,b1,var1,var2);
                        k++;
                    }
                    if(pozm==k+3 && keyPressed==13)
                        break;
                    if(pozm==k+2 && keyPressed==13)
                    {
                       int ok=1;
                    do{
                    printf("Introdu melodia pe care doriti sa il stergeti:");
                    scanf("%d",&delplay);
                        if(delplay>0 && delplay<=k)
                            ok=0;
                    }while(ok);
                    delplay=delplay-1;
                    sterge_melodie(delplay,poz3-1);
                    }

                    }
                }


                if(poz3 == MAX && keyPressed == 13)
                    break;

                }
                }

        }
        sortare();
        scriere();
}

void navigare(int CurentPoz,int arrowPoz){
    if(CurentPoz == arrowPoz){
        printf(">>");
    }
    else{
        printf("  ");
    }
}

int main()
{
    menu();
    return 0;
 }
