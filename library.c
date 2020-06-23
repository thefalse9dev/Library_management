#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
struct book{
    /*A book has an bookid is the index of the given book in the array , book_name, author, issue_no, id of the person holding it,
     id of the person who has requested it and its due date to be returned back*/
    char bookname[50];
    char bookauthor[50];
    int issue;
    int heldby;
    int requestedby;
    int duedate;
};
struct user{
/*A user has an id = index in the array of users, username, passowrd, cart of 5 books maximum
    , notifcations of 5 notifs max*/
    char username[25];
    char password[25];
    int cartsize;
    int notifsize;
    char notifs[10][100];
    struct book cart_book[5];
    int book_id[5];
};
struct book library[1000];
struct user members[1000];
int bookid=1;
int memberid=1;
int get_space(){
    /*Returns the location of the first empty book else returns -1*/
    for(int i=1;i<bookid;i++){
        if(strcmp(library[i].bookauthor,"") == 0 && strcmp(library[i].bookname,"") == 0 && library[i].issue==-1 && library[i].heldby==-1 && library[i].requestedby == -1 && library[i].duedate == -1){
            return i;
        }
    }
    return -1;
}
void delete(int bkid){
    /*Deletes the book by resetting the values to defaults ie int = -1 string = "" */
    library[bkid].issue=-1;
    library[bkid].heldby=-1;
    library[bkid].requestedby=-1;
    library[bkid].duedate=-1;
    strcpy(library[bkid].bookauthor,"");
    strcpy(library[bkid].bookname,"");
}
int get_reserve(char t[],char a[],int iss){
    /*Gets the location of the top most valid reservation, if not present gives -1 and also notifies all the user's who have resreved for the book
    and deletes their reservations*/
     int flag=0;
     int loc=-1;
     for(int i=1;i<bookid;i++){
        if(strcmp(library[i].bookauthor,a) == 0 && strcmp(library[i].bookname,t) == 0 && library[i].issue==iss && library[i].heldby==-1 && library[i].requestedby != -1){
            strcpy(members[library[i].requestedby].notifs[members[library[i].requestedby].notifsize]," has arrived.\nCheckout soon, before it goes out of stock again");
            members[library[i].requestedby].notifsize++;
            library[i].requestedby=-1;
            if(flag==0){
                loc=i;
                flag++;
            }
        }
    }
    return loc;
}
void send_notif(char t[],char a[],int iss){
    /* Sends notifications to all matching records with the Requested IDs */
    char message[100];
    for(int i=1;i<bookid;i++){
        if(strcmp(library[i].bookauthor,a) == 0 && strcmp(library[i].bookname,t) == 0 && library[i].issue==iss  && library[i].requestedby != -1){
            strcpy(message,"Your book ");
            strcat(message,library[i].bookname);
            strcat(message," is now back in stock!, checkout soon before it goes out of stock");
            strcpy(members[library[i].requestedby].notifs[members[library[i].requestedby].notifsize],message);
            members[library[i].requestedby].notifsize++;
            library[i].requestedby=-1;
        }
    }    
}
void add_book(){
    char t[50];
    char a[50];
    int iss;
    int loc=get_space();
    printf("Enter the Book Title : ");
    scanf(" %[^\n]%*c", t);;
    printf("Enter the Author's Name : ");
    scanf(" %[^\n]%*c", a);
    printf("Enter the Issue ID : ");
    scanf(" %d",&iss);
    int l=get_reserve(t,a,iss);
    printf("%d",l);
    /*If reservation is placed add the book to that place*/
    if(l!=-1){
        strcpy(library[l].bookauthor,a);
        strcpy(library[l].bookname,t);
        library[l].issue=iss;
        library[l].heldby=0;
        printf("Book added, it's Book ID is %d \n",l);
    }    
    else{
    /*if it's not placed add in the end and do bookid++*/   
        if(loc==-1){
            strcpy(library[bookid].bookauthor,a);
            strcpy(library[bookid].bookname,t);
            library[bookid].issue=iss;
            library[bookid].heldby=0;
            library[bookid].requestedby=-1;
            library[bookid].duedate=-1;
            printf("Book added, it's Book ID is %d \n",bookid);
            bookid++; 
        }
        else{
            strcpy(library[loc].bookauthor,a);
            strcpy(library[loc].bookname,t);
            library[loc].issue=iss;
            library[loc].heldby=0;
            library[loc].requestedby=-1;
            library[loc].duedate=-1;
            printf("Book added, it's Book ID is %d \n",loc);
        }
    }
}
int get_id(char t[],char a[],int iss){
    /*Returns the id of a book if book is not present gives -1*/
    for(int i =1;i<bookid;i++){
        if(strcmp(library[i].bookauthor,a) == 0 && strcmp(library[i].bookname,t) == 0 && library[i].issue==iss && library[i].heldby==0 ){
            return i;
        }
    }
    return -1;
}
void add_reservation(int id){
    char t[50];
    char a[50];
    int iss;
    printf("Enter the Book Title : ");
    scanf(" %[^\n]%*c", t);
    printf("Enter the Author's Name : ");
    scanf(" %[^\n]%*c", a);
    printf("Enter the Issue ID : ");
    scanf(" %d",&iss);
    int loc = get_space();
    if(loc==-1){
        /*We are adding the reservation in the end ie bookid and bookid++*/
        strcpy(library[bookid].bookauthor,a);
        strcpy(library[bookid].bookname,t);
        library[bookid].issue=iss;
        library[bookid].heldby=-1;
        library[bookid].requestedby=id;
        library[bookid].duedate=-1;
        printf("Reservation added, it's Reservation ID is %d \nThis will be the Book ID once the book is available",bookid);
        bookid++;
    }
    else{
        /*Adding it in a blankspace in the middle*/
        strcpy(library[loc].bookauthor,a);
        strcpy(library[loc].bookname,t);
        library[loc].issue=iss;
        library[loc].heldby=-1;
        library[loc].requestedby=id;
        library[loc].duedate=-1;
        printf("Reservation added, it's Reservation ID is %d \nThis will be the Book ID once the book is available",loc);
    }
}
void delete_res(int id, int r_id){
    if(library[r_id].requestedby==id && library[r_id].heldby==-1){
        delete(r_id);
    }
    else{
        printf("No such Reservation found\n");
    }
}
void delete_book(int b_id){
    if(library[b_id].heldby==0){
        delete(b_id);
    }
    else{
        printf("Book not present!\n");
    }
}
int cartloc(int id){
    /*Gets the first free location in the cart else gives -1*/
    int loc=-1;
    for(int i=0;i<5;i++){
        if(members[id].book_id[i]==-1){
            return i;
        }
    }
    return loc;
}
void initialize_user(int id){
    for(int i=0;i<5;i++){
        members[id].book_id[i]=-1;
        strcpy(members[id].notifs[i],"");
    }
}
int get_user_space(){
    /*Finds the first blank space in the Userlist*/
    for(int i=1;i<memberid;i++){
        if(strcmp(members[i].username,"") == 0 && strcmp(members[i].password,"") == 0 && members[i].cartsize==-1 && members[i].notifsize==-1 ){
            return i;
        }
    }
    return -1;
}
void add_user(){
    char n[50]="";
    printf("Enter the User's Name : ");
    scanf(" %[^\n]%*c", n); 
    int l = get_user_space();
    if(l==-1){
        /*Create new user at the memberid pos as no blanks found*/
        strcpy(members[memberid].username,n);
         strcpy(members[memberid].password,(n));
        members[memberid].cartsize=0;
        members[memberid].notifsize=0;
        initialize_user(memberid);
         printf("User Created with User ID %d \n",memberid);
        printf("and Passwrod %s \n",members[memberid].password);
        memberid++;
    }
    else{
        /*Adding the user at the blank location found by get_user_space*/
        strcpy(members[l].username,n);
        strcpy(members[l].password,(n));
        members[l].cartsize=0;
        members[l].notifsize=0;
        initialize_user(l);
        printf("User Created with User ID %d \n",l);
        printf("and Passwrod %s \n",members[l].password);
    }
}
void delete_user(){
    int id;
    printf("Enter the User's id : ");
    scanf("%d",&id);
    char p[50]="";
    printf("Enter the User's Password : ");
    scanf(" %[^\n]%*c", p); 
    if(strcmp(members[id].password,p)==0){
        strcpy(members[id].username,"");
        strcpy(members[id].password,"");
        members[id].cartsize=-1;
        members[id].notifsize=-1;
    }
    else{
        printf("Wrong credentials");
    }
}
int get_loc(int id){
    if(library[id].heldby==0){
        return id;
    }
    return -1;
}
void checkout(int bkid,int u_id){
    /*If book present in the library and not present in the cart allow checkout*/
    int l = cartloc(u_id);
    int loc = get_loc(bkid);
    if(loc!=-1 && members[u_id].cartsize<5){
        /*Book present in the Library*/
        members[u_id].cart_book[l]=library[bkid];
        members[u_id].book_id[l]=bkid;
        members[u_id].cartsize++;
        library[bkid].heldby=u_id;
        printf("Book succesfully checked out");
    }
    else if(loc!=-1 && members[u_id].cartsize>5){
        printf("Cart Full!");
    }
    else
    {
        printf("Book is not present");
    }
    
}
void checkin(int bkid,int u_id){
    /*User decides to return the book*/
    int b=-1;
    for(int i =0;i<5;i++){
        if(members[u_id].book_id[i]==bkid){
            /*User has the book, now clear that entry and change the library held by to 0 and cartsize--*/
            send_notif(members[u_id].cart_book[i].bookname,members[u_id].cart_book[i].bookauthor,members[u_id].cart_book[i].issue);
            strcpy(members[u_id].cart_book[i].bookauthor,"");
            strcpy(members[u_id].cart_book[i].bookname,"");
            members[u_id].cart_book[i].heldby=-1;
            members[u_id].cart_book[i].requestedby=-1;
            members[u_id].cart_book[i].issue=-1;
            members[u_id].book_id[i]=-1;
            library[bkid].heldby=0;
            b=0;
        }
    }
    if(b==0){
        printf("Book Succesfully returned");
    }
    else{
        printf("Cart does not contain the book");
    }

}
void change_password(int id){
    char n[50];
    char p[50];
    printf("Enter the username : ");
    scanf(" %[^\n]%*c", n);
    printf("Enter the password : ");
    scanf(" %[^\n]%*c", p);
    char np[50];
    if(strcmp(members[id].username,n) == 0 && strcmp(members[id].password,p)==0){
        printf("Enter the new password");
        scanf(" %[^\n]%*c", np);
        strcpy(members[id].password,np);
    }
    else{
        printf("Wrong Username and/or Password");
    }
}
int main(){
    
}