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
void search_author(int);
void search_title(int);
void search_id(int);
void reserve_book(int);
void welcome();

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
struct user{
    /*A user has an id, username, passowrd, cart of 5 books maximum
    , notifcations of 5 notifs max*/
    int id;
    char username[25];
    char password[25];
    int cartsize;
    int notifsize;
    char notifs[10][100];
    struct book cart_book[5];
};
struct book library[1000];
struct user members[1000];
int librarysize=0;
int removesize=0;
int membersize=0;
int b_id=1;
int m_id=1;
void search_title(int id){
    char title[50];
    int userid = id;
    int flag =0;
    int r_ch;
    printf("Enter the book title to be searched : \n");
    scanf(" %[^\n]%*c", title);
    for(int i=0;i<librarysize;i++){
        if(strcmp(title,library[i].bookname) == 0){
            flag++;
            printf("Book ID : &d \n",library[i].bookid);
            printf("Title : &s \n",library[i].bookname);
            printf("Author : &s \n",library[i].bookauthor);
            printf("issue number : &d \n",library[i].issue);
        }
    }
    if(flag==0){
        printf("Sorry the book is unavailable, would you like to place an order for the same \n");
        printf("Enter 1 to place an order \n");
        scanf("%d",&r_ch);
        if(r_ch==1)
            reserve_book(userid);
    }
}
void search_author(int id){
    char author[50];
    int userid = id;
    int flag=0;
    int r_ch;
    printf("Enter the author name to be view all the books written by them : \n");
    scanf(" %[^\n]%*c", author);
    for(int i=0;i<librarysize;i++){
        if(strcmp(author,library[i].bookauthor) == 0){
            flag++;
            printf("Book ID : &d \n",library[i].bookid);
            printf("Title : &s \n",library[i].bookname);
            printf("Author : &s \n",library[i].bookauthor);
            printf("issue number : &d \n",library[i].issue);
        }
    }
    if(flag==0){
        printf("Sorry the book is unavailable, would you like to place an order for the same \n");
        printf("Enter 1 to place an order \n");
        scanf("%d",&r_ch);
        if(r_ch==1)
            reserve_book(userid);
    }
}
void search_id(int id){
    int userid =id;
    int bkid;
    int flag=0;
    int r_ch;
    printf("Enter the book id to be searched : \n");
    scanf("%d", &bkid);
    for(int i=0;i<librarysize;i++){
        if(bkid==library[i].bookid){
            flag++;
            printf("Book ID : &d \n",library[i].bookid);
            printf("Title : &s \n",library[i].bookname);
            printf("Author : &s \n",library[i].bookauthor);
            printf("issue number : &d \n",library[i].issue);
        }
    }
    if(flag==0){
        printf("Sorry the book id %d is unavailable, would you like to place an order for the same \n",bkid);
        printf("Enter 1 to place an order \n");
        scanf("%d",&r_ch);
        if(r_ch==1)
            reserve_book(userid);
    }
}
void search(int id){
    int userid = id;
    int ch =0;
    do{
    printf("Enter 1 to search for book by Title\n");
    printf("Enter 2 to search for book by Author\n");
    printf("Enter 3 to search for book by Book ID\n");
    printf("Enter 0 to exit for book by title\n");
    scanf("%d",&ch);
        switch(ch){
        case 0: return;
        case 1: search_title(userid);
                break;
        case 2: search_author(userid);     
                break;
        case 3: search_id(userid);
                break;
        default : printf("Wrong Choice!, try again");                
    }
    }while(ch!=0);
    /*Search for a particular title*/
    
    /*Search for a particular book_id*/
    
    /*Search for by title and author*/
    
}
 void checkout(int id){
    /* After searching the user will be asked to enter the id of the book he wants
    to checkout, if the user doesn't have a book of the same title in his cart and
    library has the book, its held by will be set to user_id and due_date will be 
    generated, will be added to his cart at cart[cartsize] and cartsize++, librarysize -- */
    int bkid=0;
    int userid = id;
    int exit=0;
    printf("Please enter the ID of the book, you want to check out : ");
    scanf("%d",&bkid);
    int flag=0;
    int size = librarysize+removesize;
    int loc =0;
    /*This loop serves the purpose of getting the location of the given book and to change the flag value to 1 if the book is present
    flag remains 0 if the book is not present*/
    for(int i =0;i<size;i++){
        if(library[i].bookid==bkid){
            flag=1;
            loc=i;
            break;
        }
    }  
    /*This loops is used to check if the users' cart has the book already and to prevent duplicates*/
    int flag1=0; 
    for(int i =0;i<members[userid].cartsize;i++){
        if(members[userid].cart_book[i].bookid==library[loc].bookid){
            flag1=1;
        }
    } 
    if(flag==0&&flag1==0){
        printf("Book not present, make sure you enter the correct book ID\n");
        exit=1;
    }
    else if(flag==1&&flag1==0){
        printf("Book present, you have already borrowed %d books and can hold only 5 book at any given time.\n",members[userid].cartsize);
        library[loc].heldby = userid;
        members[userid].cart_book[members[userid].cartsize]=library[loc];
        librarysize--;   
        members[userid].cartsize++;
    }
    else if(members[userid].cartsize==5){
        printf("You cannot borrow more than 5 books at once, please return a book to borrow this books\n");
    }
    else{
        printf("You seem to have the same book in your cart, please return the book to borrow it again\n");
    }
}
void reserve_book(int id){
    /* A new field will be created in the library with 
    requested_by = user_id,bookname =title[],bookauthor=author[]
    bookid = b_id, b_id++*/
    char t[50];
    char a[50];
    int iss;
    printf("Enter the Title of the book");
    scanf(" %[^\n]%*c", t);
    printf("Enter the Author's name");
    scanf(" %[^\n]%*c", a);
    printf(" Enter the issue number");
    scanf("%d", &iss);
    int size = librarysize+removesize;
    /* Updating the Library */
    library[size].bookid = b_id;
    b_id++;
    strcpy(library[size].bookname,t);
    strcpy(library[size].bookauthor,a);
    library[size].heldby = -1;
    library[size].issue = iss;
    library[size].requestedby = id;
    printf("The reservation id is %d, it will be the book id once the book is available",library[size].bookid);
    printf("This id will be required to cancel reservations");
}
void delete_reservation(int id){
    
    /* shift all the books after the book id position to delete the reservation if held_by =-1 */
    int r_id;
    printf("Enter the reservation ID of the reservation that you want to cancel");
    scanf("%d",&r_id);
    int size = librarysize+removesize;
    int flag=0;
    for(int i =0;i<size;i++){
        if(library[i].bookid==r_id&&library[i].requestedby==id){
            strcpy(library[i].bookname,"");
            strcpy(library[i].bookauthor,"");
            library[i].heldby=-1;
            library[i].requestedby=-1;
            flag=1;
            break;
        }
    if(flag==0){
        printf("No such reservation placed with the library!");
    }    
    else{
        printf("Reservations succesfully cancelled!");
    }
    }
 }
void add_user(){
    /* A librarian only function to add new users to the list at membersize and memebersize++ */
    int loc = membersize;
    char name[50];
    printf("Enter the Username");
    scanf(" %[^\n]%*c", name);
    members[membersize].id=m_id;
    strcpy(members[membersize].username,name);
    strcpy(members[membersize].password,toupper(name));
    /*The deafault password is username in upper case, the member is advised to change his/her password after login*/
    members[membersize].cartsize=0;
    members[membersize].notifsize=0;
    for(int i =0;i<5;i++){
        strcpy(members[membersize].cart_book[i].bookauthor,"");
        strcpy(members[membersize].cart_book[i].bookname,"");
        members[membersize].cart_book[i].bookid=0;
        members[membersize].cart_book[i].issue=0;
        members[membersize].cart_book[i].heldby=-1;
        members[membersize].cart_book[i].requestedby=0;
        members[membersize].cart_book[i].bookid=0;
        strcpy(members[membersize].notifs[i],"");
    }
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
    checkout(2);
    return 0;
}
