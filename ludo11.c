#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 28 //N-4 should be Multiple of 8
#define L (N-4)/8
struct node
{
    int data;
    struct node *next;
};
typedef struct node node;
node*head=NULL;
node *startp1,*startp2,*startp3,*startp4;
void createboard(int i)
{
    int c;
    c=0;

    while(c!=i)
    {
        struct node *a,*current;
        a= (struct node *)malloc(sizeof(struct  node));
        a->data=c;
        a->next=NULL;
        if(head==NULL)
        {
            head=a;
            current=a;
        }

        else
        {
            current->next=a;
            current=a;
        }
        if(current->data==0)
            startp1=current;
        else if(current->data==i/4)
            startp2=current;
        else if(current->data==2*(i/4))
            startp3=current;
        else if(current->data==3*(i/4))
            startp4=current;

        c++;
    }

}
typedef struct player
{
    char name[20];
    int start;
    int c1,c2;
    node *startp;
}Player;
void sendthemback(int position,Player *p2,Player *p3,Player *p4)
{
        if(p4->c1<=N-2 && (position==(p4->c1 + p4->start)%N))
        {
            p4->c1=0;
        }
        else if(p4->c2<=N-2 && (position==(p4->c2+p4->start)%N))
        {
            p4->c2=0;
        }
        else if((position==(p2->c1+p2->start)%N) && p2->c1<=N-2)
        {
            p2->c1=0;
        }
        else if(p2->c2<=N-2 && (position==(p2->c2+p2->start)%N))
        {
            p2->c2=0;
        }
        else if(p3->c1<=N-2 && (position==(p3->c1+p3->start)%N))
        {
            p3->c1=0;
        }
        else if(p3->c2<=N-2 && (position==(p3->c2+p3->start)%N))
        {
            p3->c2=0;
        }

}
int move(Player *p,Player *p2,Player *p3,Player *p4)
{
    printf("\n");
    printf("Player %s's turn : \n",p->name);
    printf("Press any key to throw dice..\n");
    getc(stdin);

    int piecechoice=0;
    int m=1+rand()%6;
    printf("Dice shows %d\n",m);
    if(p->c1==0 && p->c2==0)
    {
        if(m==1 || m==6)
            {
                p->c1++;
                printf("1st piece unlocked.");
            }
    }
    else
    {
        if(p->c2==0 && m!=1 && m!=6)
        {
            if(p->c1<=N-2)
            {
                p->c1+=m;
                sendthemback((p->start+p->c1)%N,p2,p3,p4);

            }
            else if(m<=L+N-p->c1-2)
            {
                p->c1+=m;
            }

        }
        else
        {
            printf("Which piece do you want to move?");
            scanf("%d",&piecechoice);
            if(piecechoice!=1 && piecechoice!=2)
            {
                piecechoice=1+rand()%2;
            }

            if(piecechoice==1)
            {
                if(p->c1<N-2)
                {
                    p->c1+=m;
                    sendthemback((p->start+p->c1)%N,p2,p3,p4);
                }
                else
                {
                    if(m<=L+N-p->c1-2)
                        p->c1+=m;
                }
            }
            else if(piecechoice==2)
            {
                if(p->c2==0 &&(m==1 || m==6))
                {
                    p->c2++;
                    printf("2nd piece unlocked.");
                }
                else
                {
                     if(p->c2<N-2)
                     {
                        p->c2+=m;
                        sendthemback((p->start+p->c2)%N,p2,p3,p4);
                     }
                    else if(m<=L+N-p->c2-2)
                    {
                        p->c2+=m;
                    }
                }
            }
        }
    }
    printf("\n");

    if(p->c1>=N  && p->c2>=N)
    {
        return 1;
    }
    return 0;
}
int main(void)
{
    srand(time(NULL));
    Player A,B,C,D;
    int n;
    char tmpname[20];
    A.c1=0;
    B.c1=0;
    C.c1=0;
    D.c1=0;
    A.c2=0;
    B.c2=0;
    C.c2=0;
    D.c2=0;

    A.start=0;
    B.start=N/4;
    C.start=N/2;
    D.start=3*(N/4);

    puts("Enter name of players : ");
    gets(tmpname);
    strcpy(A.name,tmpname);
    fflush(stdin);
    gets(tmpname);
    strcpy(B.name,tmpname);
    fflush(stdin);
    gets(tmpname);
    strcpy(C.name,tmpname);
    fflush(stdin);
    gets(tmpname);
    strcpy(D.name,tmpname);

    int game=1;
    while(game)
    {
        system("cls");
        printf("\n\n");
        printf("%-10s's pieces : %d %d\n",A.name,A.c1,A.c2);
        printf("%-10s's pieces : %d %d\n",B.name,B.c1,B.c2);
        printf("%-10s's pieces : %d %d\n",C.name,C.c1,C.c2);
        printf("%-10s's pieces : %d %d\n",D.name,D.c1,D.c2);
        printf("\n");

        n=move(&A,&B,&C,&D);
        if(n==1)
        {
            puts(A.name);
            game=0;
            break;
        }
        n=move(&B,&A,&C,&D);
        if(n==1)
        {
            puts(B.name);
            game=0;
            break;
        }
        n=move(&C,&A,&B,&D);
        if(n==1)
        {
            puts(C.name);
            game=0;
            break;
        }
        n=move(&D,&A,&B,&C);
        if(n==1)
        {
            puts(D.name);
            game=0;
            break;
        }
        printf("Press any key to Continue...");
        getc(stdin);
    }
    getc(stdin);
    return 0;
}
