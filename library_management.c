/*
    librarysize to store the actual number of books and records placed to track the
    position where the next book variable has to be stored
    membersize serves the same purpose as above but for the users list
    b_id starts with 1 and b_id++ is executed whenever a new book/order is added to avoid duplicates
    heldby = 0 means library has the book
    heldby !=0 some user of that number as user_id has the book
    reservedby = userid user with that id has reserved it
    reservedby = -1 no one has reserved it
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void search(int);
void reserve_book(int);
struct user{
    /*A user has an id, username, passowrd, cart of 5 books maximum
    , notifcations of 5 notifs max*/
    int id;
    char username[25];
    char password[25];
    int cartsize;
    int notifsize;
    char notifs[10][100];
    char cart[5][100];
};
struct book{
    /*A book has an uniqueid, book_name, author, issue_no, id of the person holding it,
     id of the person who has requested it and its due date to be returned back*/
    int bookid;
    char bookname[50];
    char bookauthor[50];
    int issue;
    int heldby;
    int requestedby;
    int duedate;
};
struct book library[1000];
struct user members[1000];
int librarysize=0;
int membersize=0;
int b_id=1;
void search(int id){
    /*Search for a particular title*/
    int userid =id;
    char title[50];
    int flag=0;
    printf("Enter the book title to be searched : \n");
    scanf("%[^\n]%*c", title);
    for(int i=0;i<librarysize;i++){
        if(strcmp(title,library[i].bookname) == 0){
            flag++;
            printf("Book ID : &d \n",library[i].bookid);
            printf("Title : &s \n",library[i].bookname);
            printf("Author : &s \n",library[i].bookauthor);
            printf("issue number : &d \n",library[i].issue);
        }
    }
    int ch;
    if(flag==0){
        printf("Sorry the book is unavailable, would you like to place an order for the same \n");
        printf("Enter 1 to place an order \n");
        scanf("%d",&ch);
        if(ch==1)
            reserve_book(userid);
    }
    /*Search for a particular book_id*/
    /*Search for by title and author*/
    
}
 void checkout(int id){

    /* After searching the user will be asked to enter the id of the book he wants
    to checkout, if the user doesn't have a book of the same title in his cart and
    library has the book, its held by will be set to user_id and due_date will be 
    generated, will be added to his cart at cart[cartsize] and cartsize++, librarysize -- */
}
  void reserve_book(int id){
    /*A new field will be created in the library with 
    requested_by = user_id,bookname =title[],bookauthor=author[]
    bookid = b_id, b_id++*/
    
}
void delete_reservation(int id){
    /* shift all the books after the book id position to delete the reservation if held_by =-1*/
}
void add_user(){
    /*A librarian only function to add new users to the list at membersize and memebersize++*/
}
void add_book(){
    /*A librarian only function to add books to the library at librarysize abd librarysize ++*/
}
void delete_user(){
    /*a librian only function to remove an user and shift all other users up and usersize--*/
}
void librarian(){
    /*a function to display the choice after validating login for a librarian*/
}
void delete_book(){
    /*A librarian only function similar to delete_user() but for books*/
}
void password_change(){
    /*if login is validated user can reset his/her password*/
}
void inventory(){
    /*a functions that provides data such as number of books, users etc etc*/
}
void member(){
    /*contains the welcome page for the member login and the required functions*/
}
void welcome(){
    /* The function which creates a screen and provides option to log in. */
    printf("hello!\n");
    int ch;
    do{
        printf("Type 1 to login as member \n");
        printf("Type 2 to login as librarian \n");
        printf("Type 3 to  exit\n");
        scanf("%d",&ch);
        if(ch==1)
             member();
        else if(ch==2)
            librarian();
        else if(ch!=3)
            printf("invalid choice!");
    }while(ch!=3);
    
}
int main(){
    search(2);
    welcome();
    return 0;
}
