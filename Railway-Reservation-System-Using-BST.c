#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void manage();
void can();
void user();
void database();
void res();
void reserve();
void displaypassdetail();
void cancell();
void enquiry();

char f[10]="f";
char s[10]="s";
int addr,ad,flag,f1,d,m,i,amt;
float tamt;

typedef struct login{
  char id[100];
  char pass[100];
  char password[100];
  struct login *next;
} login;

typedef struct llist{
  login *head;
  int number_of_nodes;
} llist;

llist *ll;


void displayid(login* user)
{
  printf("id: ");
  puts(user -> id);
  printf("Password: ");
  puts(user -> pass);
}

login* initlogin()
{
  login *temp = (login *)malloc(sizeof(login));
  temp -> next = NULL;
  return temp;
}

void init_llist()
{
  FILE *fptr;
  ll = (llist *)malloc(sizeof(llist));
  ll -> head = NULL;
  ll -> number_of_nodes = 0;
  fptr = fopen("id.txt","r");
  login *a = initlogin();
  if(fptr == NULL)
    return;
  while(fread(a,sizeof(login),1,fptr))
  {
    a -> next = ll -> head;
    ll -> head = a;
    ll -> number_of_nodes++;
    a = initlogin();
  }
  fclose(fptr);
}

void ll_insert(login *a)
{
  a -> next = ll -> head;
  ll -> head = a;
  ll -> number_of_nodes++;
}

void save_ll(){
  FILE *fptr;
  login *aux = ll -> head;
  fptr = fopen("id.txt","w");
  while(aux)
  {
    fwrite((char *)& *aux,sizeof(login),1,fptr);
    aux = aux -> next;
  }
  fclose(fptr);
}

void getid(login* user)
{
    printf("Enter your id: ");
    fflush(stdin);
    gets(user -> id);
    printf("Enter the password: ");//getpass
    scanf("%s",user -> pass);
    strcpy(user -> password,user -> pass);
}

typedef struct detail{
    int tno;
    char tname[100];
    char bp[100];
    char dest[100];
    int c1,c1fare;
    int c2,c2fare;
    int d,m,y;
    struct detail *left,*right;
} detail;

typedef struct bst{
  detail *root;
  int number_of_nodes;
} bst;

bst *dt;

void dt_insert(detail *a)
{
  detail *aux = dt -> root;
  if(aux == NULL)
  {
    dt -> root = a;
    return;
  }
  while(aux)
  {
    if(a -> tno >= aux -> tno)
    {
        if(aux -> right == NULL)
        {
          aux -> right = a;
          return;
        }
        else
          aux = aux -> right;
    }
    else
    {
        if(aux -> left == NULL)
        {
            aux -> left = a;
            return;
          }
        else
          aux = aux -> left;
    }
  }
}

detail *initdetail()
{
  detail *temp = (detail *)malloc(sizeof(detail));
  temp -> right = temp -> left = NULL;
  return temp;
}


void displaydetail(detail *train)
{
    printf("%d\t%s\t%s\t%s\t",train -> tno,train -> tname,train -> bp,train -> dest);
    printf("%d-%d-%d\n",train -> d,train -> m,train -> y);
}

void dt_initialize()
{
  dt = (bst *)malloc(sizeof(bst));
  FILE *fptr;
  dt -> root = NULL;
  dt -> number_of_nodes = 0;
  fptr = fopen("train.txt","r");
  detail *a = initdetail();
  if(fptr == NULL)
    return;
  while(fread(a,sizeof(detail),1,fptr))
  {
    a -> left = a -> right = NULL;
    dt_insert(a);
    dt -> number_of_nodes++;
    a = initdetail();
  }
  fclose(fptr);
}

detail* search(int tno)
{
  detail *aux = dt -> root;
  while(aux)
  {
    if(tno > aux -> tno)
          aux = aux -> right;
    else if(tno < aux -> tno)
      aux = aux -> left;
    else
      return aux;
    }
    return NULL;
}

void save(detail *root,FILE *fptr)
{
  if(root == NULL)
  return;
  save(root -> left,fptr);
  save(root -> right,fptr);
  fwrite((char *)& *root,sizeof(detail),1,fptr);
}

void save_dl(){
  FILE *fptr;
  detail *aux = dt -> root;
  fptr = fopen("train.txt","w");
  save(dt -> root,fptr);
  fclose(fptr);
}

void getdetail(detail* train)
{
  printf("Enter the details as follows\n");
  printf("Train no:");
  scanf("%d",&train -> tno);
  fflush(stdin);
  printf("Train name:");
  gets(train -> tname);
  printf("Boarding point:");
  gets(train -> bp);
  printf("Destination pt:");
  gets(train -> dest);
  printf("No of seats in first class & fare per ticket:");
  scanf("%d\n%d",&train -> c1,&train -> c1fare);
  printf("No of seats in second class & fare per ticket:");
  scanf("%d\n%d",&train -> c2,&train -> c2fare);
  printf("Date of travel (d-m-y): ");
  scanf("%d-%d-%d",&train -> d,&train -> m,&train -> y);
  train -> left = train -> right = NULL;
}



void display(detail *a)
{
  if(a == NULL)
  return;
  display(a -> left);
  displaydetail(a);
  display(a -> right);
}

typedef struct reser{
  int pnr;
  int tno;
  char tname[100];
  char bp[10];
  char dest[100];
  char pname[10][100];
  int age[20];
  char clas[10];
  int nosr;
  int d,m,y;
  int con;
  float amc;
  struct reser *next;
} reser;

typedef struct rlist{
  reser *head;
  int number_of_nodes;
} rlist;

rlist *rl;

reser* initreser()
{
  reser *temp = (reser *)malloc(sizeof(reser));
  temp -> next = NULL;
  return temp;
}

void displayresdet(reser *p)
{
    printf("...............................................\n");
    printf("...............................................\n");
    printf("Pnr no: %d",p -> pnr);
    printf("\nTrain no: %d",p -> tno);
    printf("\nTrain name: ");
    puts(p ->tname);
    printf("Boarding point: ");
    puts(p -> bp);
    printf("Destination pt: ");
    puts(p -> dest);
    printf("No of seats reserved: %d\n",p -> nosr);
    for(i=0; i < p -> nosr; i++)
    {
        printf("Passenger name:");
        puts(p -> pname[i]);
        printf("Passenger age:%d\n", p -> age[i]);
    }
    printf("\nYour class:");
    puts(p -> clas);
    printf("\nDate of reservation: %d-%d-%d",p -> d,p -> m,p -> y);
    printf("\nYour concession category: %d",p -> con);
    printf("\nYou must pay: %f rs\n",p -> amc);
    printf("*\n");
    printf("*\n");
}

void init_rlist()
{
  rl = (rlist *)malloc(sizeof(rlist));
  FILE *fptr;
  rl -> head = NULL;
  rl -> number_of_nodes = 0;
  fptr = fopen("passenger.txt","r");
  reser *b = initreser();
  if(fptr == NULL)
    return;
  while(fread(b,sizeof(reser),1,fptr))
  {
    b -> next = rl -> head;
    rl -> head = b;
    rl -> number_of_nodes++;
    b = initreser();
  }
  fclose(fptr);
}

void rl_insert(reser *a)
{
  a -> next = rl -> head;
  rl -> head = a;
  rl -> number_of_nodes++;
}


void save_rl(){
  FILE *fptr;
  reser *aux = rl -> head;
  fptr = fopen("passenger.txt","w");
  while(aux)
  {
    fwrite((char *)& *aux,sizeof(reser),1,fptr);
    aux = aux -> next;
  }
  fclose(fptr);
}


void getresdet(reser *p)
{
  int i;
  printf("Enter the details as follows\n");
  printf("Train no:");
  scanf("%d",&p -> tno);
  printf("Train name:");
  fflush(stdin);
  gets(p -> tname);
  printf("Boarding point:");
  gets(p ->bp);
  printf("Destination pt:");
  gets(p -> dest);
  printf("No of seats required:");
  scanf("%d",&p -> nosr);
  for(i=0; i < p -> nosr ; i++)
  {
      printf("Passenger name:");
      fflush(stdin);
      gets(p -> pname[i]);
      printf("Passenger age:");
      scanf("%d",&p -> age[i]);
  }
  printf("Enter the class f-first class s-second class:");
  fflush(stdin);
  gets(p -> clas);
  printf("Date of travel:");
  scanf("%d-%d-%d",&p -> d,&p->m,&p->y);
  printf("Enter the concession category\n");
  printf("1.Military\n2.Senior citizen\n");
  printf("3.Children below 5 yrs\n4.None\n");
  fflush(stdin);
  scanf("%d",&p ->con);
  printf("\n............END OF GETTING DETAILS............\n");
}

typedef struct canc
{
  int pnr;
  int tno;
  char tname[100];
  char bp[10];
  char dest[100];
  char pname[10][100];
  int age[20];
  int i;
  char clas[10];
  int nosc;
  int d,m,y;
  float amr;
} canc;

canc* initcanc()
{
  canc *temp = (canc *)malloc(sizeof(canc));
  return temp;
}

void getcancdet(canc* p)
{
    printf("Enter the details as follows\n");
    printf("Pnr no:");
    scanf("%d",&p->pnr);
    printf("Date of cancellation: ");
    scanf("%d-%d-%d",&p->d,&p->m,&p->y);
    printf("...........END OF GETTING DETAILS...........\n");
}

void displaycancdet(canc *p)
{
    printf("...........................................\n");
    printf("...........................................\n");
    printf("Pnr no: %d",p -> pnr);
    printf("\nTrain no: %d",p -> tno);
    printf("\nTrain name:");
    puts(p -> tname);
    printf("Boarding point:");
    puts(p -> bp);

    printf("Destination pt:");
    puts(p -> dest);
    printf("\nYour class:");
    puts(p -> clas);
    printf("no of seats to be cancelled: %d",p -> nosc);
    for(i=0; i<p -> nosc; i++)
    {
        printf("Passenger name:");
        puts(p -> pname[i]);
        printf("\tpassenger age: %d",p -> age[i]);
    }
    printf("\nDate of cancellation: %d-%d-%d",p->d,p->m,p->y);
    printf("\nYou can collect:%f rs\n",p -> amr);
    printf("*\n");
    printf(".........END OF CANCELLATION.............\n");
    printf("*\n");
}

void database()
{
    char *password;
    char *pass="insecurities";
    printf("Enter the admininistrator password:");//getpass
    scanf("%s",password);
    detail *a = initdetail();
    int ch;
    char c;
    if(strcmp(pass,password)!=0)
    {
        printf("Enter the password correctly \n");
        printf("You are not permitted to login this mode\n");
        return;
    }
    if(strcmp(pass,password)==0)
    {
        char c;
        do
        {
            printf("\n\n...........ADMINISTRATOR MENU...........\n");
            printf("1.Create detail data base\n2.Add details\n");
            printf("3.Display details\n4.User management\n");
            printf("5.Display passenger details\n6.Return to main menu\n");
            printf("Enter your choice:");
            scanf("%d",&ch);
            printf("\n");
            switch(ch)
            {
            case 1:
                do
                {
                    a = initdetail();
                    getdetail(a);
                    dt_insert(a);
                    printf("Do you want to add one more record?\n");
                    printf("y-for Yes\nn-for No\n");
                    fflush(stdin);
                    scanf("%c",&c);
                }
                while(c=='y');
                break;
            case 2:
                a = initdetail();
                getdetail(a);
                dt_insert(a);
                break;
            case 3:
                display(dt -> root);
                break;
            case 4:
                manage();
                break;
            case 5:
                displaypassdetail();
                break;
            }
        }
        while(ch<=5);
    }
}

void reserve()
{
    int ch;
    do
    {
        printf("1.Reserve\n2.Return to the main menu\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        printf("\n");
        switch(ch)
        {
        case 1:
            res();
            break;
        }
    }
    while(ch==1);
}

void res()
{
    detail *a = initdetail(),*aux = dt -> root;
    reser *b = initreser();
    time_t t;
    int ch;
    getresdet(b);
    a = search(b -> tno);
    if(a != NULL)
    {
        if(strcmp(b -> clas,f) == 0)
        {
            if(a -> c1 >= b -> nosr)

            {
                amt = a -> c1fare;
                ad = sizeof(a -> c1);
                a -> c1 = a -> c1 - b -> nosr;
                if(b -> con==1)
                {
                    printf("Concession category:MILITARY PERSONNEL\n");

                    b -> amc = b -> nosr * ((amt*50)/100);
                }
                else if(b -> con==2)
                {
                    printf("Concession category:SENIOR CITIZEN\n");
                    b -> amc=b -> nosr*((amt*60)/100);
                }
                else if(b -> con==3)
                {
                    printf("Concession category:CHILDERN BELOW FIVE\n");
                    b -> amc=0.0;
                }
                else if(b -> con==4)
                {
                    printf("You cannot get any concession\n");
                    b -> amc=b -> nosr*amt;
                }
                srand((unsigned) time(&t));
                b -> pnr=rand();
                rl_insert(b);
                displayresdet(b);
                printf("\n------------------------------------------------------\n");
                printf("--------------Your ticket is reserved-----------\n");
                printf("-----------------End of reservation menu-------\n");
            }
            else
            {
                printf("*Sorry req seats not available*\n");

            }
        }
        else if(strcmp(b -> clas,s)==0)
        {
            if(a -> c2>=b -> nosr)
            {
                amt = a -> c2fare;
                ad = sizeof(a -> c2);
                a -> c2 = a -> c2 - b -> nosr;
                if(b -> con==1)
                {
                    printf("Concession category:MILITARY PRESONNEL\n");
                    b -> amc=b -> nosr*((amt*50)/100);
                }
                else if(b -> con==2)
                {
                    printf("Concession category:SENIOR CITIZEN\n");
                    b -> amc=b -> nosr*((amt*60)/100);
                }
                else if(b -> con==3)
                {
                    printf("Concession category:CHILDERN BELOW FIVE\n");
                    b -> amc=0.0;
                }
                else if(b -> con==4)
                {
                    printf("You cannot get any concession\n");
                    b -> amc=b -> nosr*amt;
                }
                srand((unsigned) time(&t));
                b -> pnr=rand();
                rl_insert(b);
                displayresdet(b);
                printf("---------------------------------------\n");
                printf("--------Your ticket is reserved--------\n");
                printf("------------End of reservation---------\n");
            }
            else
            {
                printf("*Sorry req no of seats not available\n");
            }
        }
    }
    else
    {
        printf("............Wrong train no......................\n");
        printf("......Enter the train no from the data base.....\n");
    }
}

void cancell()
{
    detail *a;
    reser *b = rl ->head,*p = NULL;
    canc *c = initcanc();
    printf( "*CANCELLATION MENU\n");
    getcancdet(c);
    while(b)
    {
        if(b -> pnr==c -> pnr)
        {
            c -> tno=b -> tno;
            strcpy(c -> tname,b -> tname);
            strcpy(c -> bp,b -> bp);
            strcpy(c -> dest,b -> dest);
            c -> nosc=b -> nosr;
        int j;
for (j = 0; j < c->nosc; j++) {
    // code
}

            {
                strcpy(c -> pname[j],b -> pname[j]);
                c -> age[j]=b -> age[j];
            }
            strcpy(c -> clas,b -> clas);
            a = search(c->tno);
            if(strcmp(c -> clas,f)==0)
            {
                  a ->  c1 = a ->  c1 + c -> nosc;
                  d = a ->  d;
                  m = a ->  m;
                  tamt = b -> amc;
                  if((c -> d==d)&&(c -> m==m))
                  {
                      printf( "You are cancelling at the date of departure\n");
                      c -> amr=tamt-((tamt*60)/100);
                  }
                  else if(c -> m==m)
                  {
                      printf( "You are cancelling at the month of departure\n");
                      c -> amr=tamt-((tamt*50)/100);
                  }
                  else if(m>c -> m)
                  {
                      printf( "You are cancelling one month before the date of departure\n");
                      c -> amr=tamt-((tamt*20)/100);
                  }
                  else
                  {
                      printf( "Cancelling after the departure\n");
                      printf( "Your request cannot be completed\n");
                  }
                  displaycancdet(c);
            }
            else if(strcmp(c -> clas,s)==0)
            {
                  a ->  c2 = a ->  c2 + c -> nosc;
                  d = a ->  d;
                  m = a ->  m;
                  tamt = b -> amc;
                  if((c -> d==d)&&(c -> m==m))
                  {
                      printf( "You are cancelling at the date of departure\n");
                      c -> amr=tamt-((tamt*60)/100);
                  }
                  else if(c -> m==m)
                  {
                      printf( "You are cancelling at the month of departure\n");
                      c -> amr=tamt-((tamt*50)/100);
                  }
                  else if(m>c -> m)
                  {
                      printf( "You are cancelling one month before the date of departure\n");
                      c -> amr=tamt-((tamt*20)/100);
                  }
                  else
                  {
                      printf( "Cancelling after the departure\n");
                      printf( "Your request cannot be completed\n");
                  }
                  displaycancdet(c);
            }
            if(p == NULL)
            {
              rl -> head = b -> next;
              free(b);
              return;
            }
            p -> next = b -> next;
            free(b);
            return;

        }
        p = b;
        b = b -> next;
    }
    printf( "Enter the correct pnr no\n");

}
void can()
{
    int ch;
    do
    {
        printf( ".................CANCELLATION MENU.........\n");
        printf( "1.Cancell\n2.Return to the main menu\n");
        printf( "Enter your choice:");
        fflush(stdin);
        scanf("%d",&ch);
        printf("\n");
        switch(ch)
        {
        case 1:
            cancell();
            break;
        }
    }
    while(ch==1);
}

void displaypassdetail()
{
  reser *aux = rl -> head;
    while(aux)
    {
      displayresdet(aux);
     aux = aux -> next;
   }

}

void enquiry()
{

    display(dt -> root);
}

void user()
{
    login *aux = ll -> head;
    int ch;
    printf("*\n");
    printf("WELCOME TO THE USER MENU*\n");
    printf("\n");
    char *password;
    char id[100];
    puts("Enter your id:");
    fflush(stdin);
    gets(id);
    printf("Enter your password:");//getpass
    scanf("%s",password);
    while(aux)
    {
        if((strcmp(aux -> id,id)==0)&&(strcmp(aux -> pass,password)==0))
        {
            do
            {
                printf("1.Reserve\n2.Cancell\n3.Enquiry\n4.Return to the main menu\n");
                printf("Enter your choice:");
                scanf("%d",&ch);
                printf("\n");
                switch(ch)
                {
                case 1:
                    reserve();
                    break;
                case 2:
                    can();
                    break;
                case 3:
                    enquiry();
                    break;
                }
            }
            while(ch<=3);
            return;
        }
        aux = aux -> next;
    }
    printf("Enter your user id and password correctly\n");
}
void manage()
{
    int ch;
    char c;
    login *a = initlogin(),*aux;
    printf(".........WELCOME TO THE USER MANAGEMENT MENU........\n");
    do
    {
        printf("1.Create id data base\n2.Add details\n");
        printf("3.Display details\n4.Return to the main menu\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        printf("\n");
        switch(ch)
        {
        case 1:
            do
            {
                a = initlogin();
                getid(a);
                ll_insert(a);
                printf("Do you want to add one more record\n");
                printf("y-Yes\nn-No\n");
                fflush(stdin);
                scanf("%c",&c);
            }
            while(c=='y');
            break;
        case 2:
            a = initlogin();
            getid(a);
            ll_insert(a);
            break;
        case 3:
            aux = ll -> head;
            while(aux)
            {
                displayid(aux);
                aux = aux -> next;
            }
            break;
        }
    }
    while(ch<=3);
}

void main()
{
    int ch;
    init_llist();
    init_rlist();
    dt_initialize();
    printf("\n");
    printf(".......WELCOME TO RAILWAY RESERVATION SYSTEM..........\n");
    printf("\n");
    do
    {
        printf("^^^^^^^^^^^^^^^^^^^^^^MAIN MENU^^^^^^^^^^^^^^^^^^^^\n");
        printf("1.Admin mode\n2.User mode\n3.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        printf("\n");
        switch(ch)
        {
        case 1:
            database();
            break;
        case 2:
            user();
            break;
        case 3:
         save_ll();
         save_dl();
         save_rl();
         exit(0);

        }
    }
    while(ch<=3);
    save_ll();
    save_dl();
    save_rl();
}
