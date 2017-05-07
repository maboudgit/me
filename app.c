#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "funapp.h"



int main()
{
  
  start = last = NULL;

  for(;;) 
  {
    switch(menu_select()) 
    {
        case 1:  enter();  
        break;
        case 2 : del();    
        break;
        case 3:  list();  
        break ;
        case 4:  search(); 
        break;
        case 5:  save();   
        break ;
        case 6:  load();   
        break ;
        case 7:  exit(0);
    }     
  }
}





