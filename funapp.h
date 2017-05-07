
// create address struct

struct address 
{
  char name[30];
  char street[30];
  char city[20];
  char state[3];
  char zip[10];
  struct address *next;
  struct address *prior;
} list_entry;


// load variable in struct

struct address *start;
struct address *last;

// create function in type struct

struct address *find(char *);
struct address *store(struct address *, struct address *);


// create function 

void enter() , display() , search() ;
void save()  , load()    , list() , del();
void display(struct address *info, int *row);
int menu_select();






void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}



int menu_select()
{
  char s[5];

  system("clear");
  gotoxy(25, 4);
  printf("1. enter a name ");
  gotoxy(25, 6);
  printf("2. delete a name ");
  gotoxy(25, 8);
  printf("3. list all files ");
  gotoxy(25, 10);
  printf("4. search ");
  gotoxy(25, 12);
  printf("5. save the file  ");
  gotoxy(25, 14);
  printf("6. load the file  ");
  gotoxy(25, 16);
  printf("7. quit ");
      
  do 
  {
   	gotoxy(20, 18);
   	printf("Please Enter Item Number(1-7) :: ");
   	gets(s);
  } while (atoi(s) < 0 || atoi(s) > 7);

  return atoi(s);
}





void enter()
{

  struct address *info;
  int i;
  char ch;

  system("clear");
  gotoxy(3, 2);
  printf("   name        street     city     state    zip");
  gotoxy(3, 3);
  printf(" ------------ -------- ");
  printf("--------   -----  ------- ");

  i = 4;

  for (;;) 
  {
    info = (struct address *)malloc(sizeof(list_entry));

    if(!info) 
    {
   		printf("\n out of memory. press a key ");
   		getchar();
   		return;
    }

    gotoxy(3,i);
    gets(info -> name);

    if(!info -> name[0]) 
    {
   		gotoxy(15, i + 1);
   		printf("press a key to continue");
   		getchar();
   		break;
    }

    gotoxy(18, i);
    gets(info -> street);
    gotoxy(28, i);
    gets(info -> city);
    gotoxy(38, i);
    gets(info -> state);
    gotoxy(45, i);
    gets(info -> zip);

    i++;
    start = store(info, start);

  } 
}




struct address *store(struct address *i, struct address *top)
{
 	struct address *old, *p;

  if(last == NULL) 
  {
   	i -> next = NULL;
   	i -> prior = NULL;
   	start = i;
   	last = i;
   	return i;
  }

  p = top;
  old = NULL;

  while (p != NULL) 
  {
    if(strcmp(p -> name, i -> name) < 0) 
    {
      old = p ;
      p = p -> next ;
    }
    else 
    {
      if (p -> prior) 
      {
    		p -> prior -> next=i;
    		i -> next=p;
    		i -> prior=p -> prior;
    		p -> prior=i;

    		return top;
      }

      i -> next = p;
      i -> prior = NULL;
      p -> prior = i;

      return i;
    }
  }

  old -> next = i ;
  i -> next = NULL ;
  i -> prior = old ;
  last = i ;

  return start ;
}




void del()
{
  struct address *info;
  char name[80];

  gotoxy(20, 20);
  printf(" enter name for delete : ");
  gets(name);

  info = find(name);

  if(info == NULL) 
  {
    gotoxy(10, 20);
    printf(" name not found! press a key to continue.");
    getchar();
  }

  if (info)
  if (start == info)
 	{
   	start = info -> next;

   	if(start)
      start -> prior = NULL;
   	else
      last = NULL;
 	} 
  else  
  {
    info -> prior -> next = info -> next;
    if(info != last)
   		info -> next -> prior = info -> prior;
    else
  		last = info -> prior;
  } 

  free(info);
  gotoxy(10,20);
  printf("name deleted, press a key to continue.");
  getchar();
}





struct address *find(char *name)
{
  struct address *info;
  info = start;

  while(info != NULL) 
  {
 		if(strcmp(name, info -> name) == 0)
    		return info;
 		info = info -> next;
  }
  return NULL;
}





void list()
{
  struct address *info;
  int i;

  info = start;

  system("clear");
  gotoxy(3, 2);
  printf("   name        street     city     state    zip");
  gotoxy(3, 3);
  printf(" ------------ --------  -");
  printf("-------   -----  ------- ");

  i = 4;

  while(info != NULL) 
  {
 		display(info, &i);
 		info = info -> next;
  }

  gotoxy(15, i + 2);
  printf("press a key to continue.");
  getchar();
}




void display(struct address *info, int *row)
{
  gotoxy(3, *row);
  printf("%s", info -> name);
  gotoxy(18, *row);
  printf("%s", info -> street);
  gotoxy(28, *row);
  printf("%s", info -> city);
  gotoxy(38, *row);
  printf(info -> state);
  gotoxy(47, *row);
  printf(info -> zip);

  *row = *row + 1;
}



void search()
{
  char name[40];
  int i;
  struct address *info;

  gotoxy(20, 20);
  printf(" enter name to find : ");
  gets(name);

  info = find(name);

  if(info == NULL) 
  {
   	gotoxy(10, 20);
  	printf(" name not found! press a key to continue.");
   	getchar();
  }
  else  
  {
   	system("clear");
   	gotoxy(3, 2);
   	printf("   name        street   city     state   zip");
   	gotoxy(3, 3);
   	printf(" ------------ -------");
   	printf("-  --------   -----  ------- ");

   	i = 4;

   	display(info ,&i);
   	gotoxy(15, i + 2);
   	printf("press a key to continue.");
   	getchar();
  }
}




void save()
{
  struct address *info;

  FILE *fp;

  if((fp = fopen("l.dat","wb")) == NULL)  
  {
 		printf("\n cannot open file. ") ;
 		getchar();
 		exit(1);
  }

  gotoxy(20, 20);
  printf("<< saving file >>");

  info = start;

  while(info) 
  {
    fwrite(info, sizeof(struct address), 1, fp);
    info = info -> next;
  }

  fclose(fp);
  gotoxy(15, 22);
  printf("file successfuly saved press a key...");
  getchar();
}




void load ()
{
  struct address *info , *temp = NULL;

  FILE *fp;
  fp = fopen("l.dat","rb");

  if(fp == NULL)  
  {
 		printf("\n cannot open file.");
 		getchar();
 		exit(1);
  }

  while(start) 
  {
    info = start -> next;
    free(info);
    start = info;
  }

  gotoxy(20,20);
  printf(" << loading file  >> ");

  start = NULL ;

  while(!feof(fp)) 
  {
   	info = (struct address *)
    malloc(sizeof(struct address));

   	if(1 != fread(info, sizeof(struct address), 1, fp))
    break;

   	if(start == NULL)  
   	{
      temp = start = info;
      info -> prior = NULL;
      info -> next = NULL;
   	}
   	else  
    {
      info -> next = NULL;
      temp -> next = info;
      info -> prior = temp;
      temp = info;
   	}
  }

  last = temp;

  fclose(fp);
  gotoxy(15,22);
  printf("file successfuly loaded press a key ...") ;
  getchar();
}

