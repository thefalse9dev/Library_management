/*A random comment*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void librarian(){
    /*a function to display the choice after validating login for a librarian*/
}
void member(){
    /*a function to display the choices for a member after verifying member login*/
}
void welcome(){
    /* the function which creates a screen and provides option to log in*/
    int ch;
    printf("Type 1 to login as member");
    printf("Type 2 to login as librarian");
    scanf("%d",&ch);
    if(ch!=1 || ch!=2)
        printf("invalid choice");
    else if(ch==1)
        member();
    else
        librarian();
    
    
}
int main(){
    void welcome();
}