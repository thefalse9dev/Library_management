/*A random comment*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
struct user{
    /*A user has an id, username, passowrd, cart of 5 books maximum, notifcations of 5 notifs max*/
    int id;
    char username[25];
    char password[25];
    int cartsize;
    int notifsize;
    char notifs[10][100];
    char cart[5][100];
};
struct book{
    int bookid;
    char bookname[50];
    char bookauthor[50];
    int heldby;
    int requestedby;
    int duedate;
};
int librarysize=0;
int membersize=0;
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