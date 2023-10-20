#include "functions.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void freeList(node *head){
    while(head){
        node *temp=head;
        head=head->next;
        free(temp);
    }
}

void print(node *ans){
    while(ans){
        printf("%d",ans->data);
        ans=ans->next;
    }
    printf("\n");
}

node* reverse(node *curr){
    node *prev=NULL,*forward=NULL;
    while(curr){
        forward=curr->next;
        curr->next=prev;
        prev=curr;
        curr=forward;
    }
    return prev;
}

node *createNode(){
    node *temp=(node *)malloc(sizeof(node));
    temp->next=NULL;
    return temp;
}

void insertAtHead(node **head,int value){
    node *temp=createNode();
    temp->data=value;
    temp->next=*head;
    *head=temp;
}

int getLen(node *head){
    int len=0;
    while(head){
        len++;
        head=head->next;
    }
    return len;
}

int isSmaller(node *dividend,node *divisor){
    int len1=getLen(dividend),len2=getLen(divisor);
    if(len1<len2) return 0;
    else if(len1>len2) return 1;
    else{
        while(dividend){
            if(dividend->data > divisor->data)  return 1;
            else if(dividend->data < divisor->data) return 0;
            dividend=dividend->next;
            divisor=divisor->next;
        }
    }
    return 2;
}

int compare(char *a,char *b){
    int len1=strlen(a),len2=strlen(b);

    if(len1>len2) return 1;
    else if(len2>len1) return 2;
    else{
        //case when length of both strings is same now we need to check which number is greater
        for(int i=0;i<len1;i++){
            if(a[i]>b[i]) return 1;
            else if(a[i]<b[i]) return 2;
        }
    }
    //if we have not return yet then both numbers are equal
    return 0;
}

//simple addition of two linked list

node *add2(node *num1,node *num2){
    node *ans=NULL;
    int carry=0,s=0;

    while(num1 && num2){

        s=(num1->data)+(num2->data)+carry;
        num1=num1->next;
        num2=num2->next;
        node *temp=createNode();

        carry=s/10;
        s=s%10;

        temp->data=s;

        temp->next=ans;
        ans=temp;

        s=0;
    }

    while(num1){
        s=num1->data+carry;
        num1=num1->next;
        carry=s/10;
        s=s%10;
        node *temp=createNode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    while(num2){
        s=num2->data+carry;
        num2=num2->next;
        carry=s/10;
        s=s%10;
        node *temp=createNode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    if(carry){
        node *temp=createNode();
        temp->data=carry;
        temp->next=ans;
        ans=temp;
    }

    return ans;    
}

//addition after multiplication

node *add(node *num1,node *num2,int iteration){
    node *ans=NULL;

    //insert first element from num2 in ans then add rest
    for(int i=0;i<iteration;i++){
        node *t=createNode();
        t->data=num2->data;
        num2=num2->next;
        if(!ans) ans=t;
        else{
            t->next=ans;
            ans=t;
        }
    }

    int carry=0,s=0;

    while(num1 && num2){

        s=(num1->data)+(num2->data)+carry;
        num1=num1->next;
        num2=num2->next;
        node *temp=createNode();

        carry=s/10;
        s=s%10;

        temp->data=s;

        temp->next=ans;
        ans=temp;

        s=0;

    }

    while(num1){
        s=num1->data+carry;
        num1=num1->next;
        carry=s/10;
        s=s%10;
        node *temp=createNode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    while(num2){
        s=num2->data+carry;
        num2=num2->next;
        carry=s/10;
        s=s%10;
        node *temp=createNode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    return ans;    
}

//multiply with input Linked list

node* Multiply(node *num1,node *num2){
    //firstly as answer of num1 x num2 == num2 x num1,we should be choosing 
    //second number with least length

    node *head1=NULL,*ans=NULL;

    //these are the nodes which will get added if we have num2 > 2

    int carry=0,prod=0;

    //save original heads as we need them again and again
    node *list1=num1,*list2=num2;

    while(list1){
        prod=(list1->data)*(list2->data)+carry;
            if(prod>9){
                carry=prod/10;
                prod=prod%10;
            }
            else carry=0;
            insertAtHead(&head1,prod);
            list1=list1->next;
        }
        if(carry){
            insertAtHead(&head1,carry);
            carry=0;
        }
        //in case if we have only one digit in num2
        list2=list2->next;
        ans=head1;
        if(!list2){
            return ans;
        }
        ans=reverse(ans);

        int itr=0;

    while(list2){
        itr++;
        //if there are more than one digit
        head1=NULL;
        list1=num1;
        while(list1){
            prod=(list1->data)*(list2->data)+carry;
            if(prod>9){
                carry=prod/10;
                prod=prod%10;
            }
            else carry=0;
            insertAtHead(&head1,prod);
            list1=list1->next;
        }
        if(carry){
            insertAtHead(&head1,carry);
            carry=0;
        }
        //print(ans);
        head1=reverse(head1);
        list2=list2->next;
        ans=add(head1,ans,itr);
        ans=reverse(ans);
    }
    ans=reverse(ans);
    return ans;
}

node* convertToLL(char *str){
    int i=0;
    node *head=NULL;
    while(str[i]!='\0'){
        node *temp=createNode();
        temp->data=str[i]-48;
        temp->next=head;
        head=temp;
        i++;
    }
    head=head->next;
    return head;
}

//Addition

node* AddbigInt(char *a,char *b){
    node *num1=convertToLL(a);
    node *num2=convertToLL(b);

    node *ans=NULL;
    int s=0,carry=0;

    while(num1 && num2){

        s=(num1->data)+(num2->data)+carry;
        num1=num1->next;
        num2=num2->next;
        node *temp=createNode();

        carry=s/10;
        s=s%10;

        temp->data=s;

        temp->next=ans;
        ans=temp;

        s=0;

    }

    while(num1){
        s=num1->data+carry;
        num1=num1->next;
        carry=s/10;
        s=s%10;
        node *temp=createNode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    while(num2){
        s=num2->data+carry;
        num2=num2->next;
        carry=s/10;
        s=s%10;
        node *temp=createNode();

        temp->data=s;
        temp->next=ans;
        ans=temp;

        s=0;
    }

    if(carry){
        node *temp=createNode();
        temp->data=carry;
        temp->next=ans;
        ans=temp;
    }

    return ans;
}

//Subtraction

void borrow(node *num1){
    if(!num1) return;
    else if(num1->data>0){
        (num1->data)--;
        return;
    }
    else{
        borrow(num1->next);
        num1->data=9;
    }
}

node* Subtract_bigInt(char *a,char *b){
    int minus=0;
    //check which number is greater
    int key=compare(a,b);
    if(key==0){
        //as both numbers are equal return node with data 0
        node *temp=createNode();
        temp->data=0;
        temp->next=NULL;
        return temp;
    }
    
    //convert both strings to LL
    node *num1=convertToLL(a);
    node *num2=convertToLL(b);

    if(key==2){
        //in this case as second number is greater ans will be negative
        minus=1;
        //swap
        node *temp=num1;
        num1=num2;
        num2=temp;
    }

    node *ans=NULL;

    while(num1 && num2){
        node *temp=createNode();
        if((num1->data)<(num2->data)){
            //case of borrowing carry
            //firstly we should be modifying our Linked list as we are borrowing
            borrow(num1->next);
            num1->data+=10;
        }
        temp->data=num1->data-num2->data;
        temp->next=ans;
        ans=temp;
        num1=num1->next;
        num2=num2->next;
    }

    while(num1){
        node *temp=num1->next;
        num1->next=ans;
        ans=num1;
        num1=temp;
    }

    while(ans->data==0) ans=ans->next;

    if(minus) ans->data=-(ans->data);

    return ans;
}

//subtract two linked list
node* Subtract_bigLinkedList(node *num1,node *num2){
    node *ans=NULL;

    while(num1 && num2){
        node *temp=createNode();
        if((num1->data)<(num2->data)){
            //case of borrowing carry
            //firstly we should be modifying our Linked list as we are borrowing
            borrow(num1->next);
            num1->data+=10;
        }
        temp->data=num1->data-num2->data;
        temp->next=ans;
        ans=temp;
        num1=num1->next;
        num2=num2->next;
    }

    while(num1){
        node *temp=num1->next;
        num1->next=ans;
        ans=num1;
        num1=temp;
    }

    while(ans->data==0) ans=ans->next;

    return ans;
}

//Multiplication

node* Multiply_bigInt(char *a,char *b){
    //firstly as answer of num1 x num2 == num2 x num1,we should be choosing 
    //second number with least length

    node *num1=convertToLL(a);
    node *num2=convertToLL(b);

    if(strlen(a)<strlen(b)){
        node *temp=num1;
        num1=num2;
        num2=temp;    
    }

    node *head1=NULL,*ans=NULL;

    //these are the nodes which will get added if we have num2 > 2

    int carry=0,prod=0;

    //save original heads as we need them again and again
    node *list1=num1,*list2=num2;

    while(list1){
        prod=(list1->data)*(list2->data)+carry;
            if(prod>9){
                carry=prod/10;
                prod=prod%10;
            }
            else carry=0;
            insertAtHead(&head1,prod);
            list1=list1->next;
        }
        if(carry){
            insertAtHead(&head1,carry);
            carry=0;
        }
        //in case if we have only one digit in num2
        list2=list2->next;
        ans=head1;
        if(!list2){
            return ans;
        }
        ans=reverse(ans);

        int itr=0;

    while(list2){
        itr++;
        //if there are more than one digit
        head1=NULL;
        list1=num1;
        while(list1){
            prod=(list1->data)*(list2->data)+carry;
            if(prod>9){
                carry=prod/10;
                prod=prod%10;
            }
            else carry=0;
            insertAtHead(&head1,prod);
            list1=list1->next;
        }
        if(carry){
            insertAtHead(&head1,carry);
            carry=0;
        }
        //print(ans);
        head1=reverse(head1);
        list2=list2->next;
        ans=add(head1,ans,itr);
        ans=reverse(ans);
    }
    ans=reverse(ans);
    return ans;
}

//Division

node* Divide_bigInt(char *a,char *b,int option){
    int key=compare(a,b);

    node *ans=NULL;

    if(key==0){
        ans=createNode();
        ans->data=1;
        return ans;
    }
    else if(key==2){
        ans=createNode();
        ans->data=0;
        return ans;
    }

    node *num1=convertToLL(a),*num2=convertToLL(b);

    node *factor=createNode();
    factor->data=1;
    node *one=createNode();
    one->data=1;

    num1=reverse(num1);

    int mark=1,sub=0;

    while(mark){
        node *temp=Multiply(factor,num2);
        mark=isSmaller(num1,temp);

        if(mark==1){
            factor=add2(factor,one);
            factor=reverse(factor);
        }
        else if(mark==0){
            factor=Subtract_bigLinkedList(factor,one);
            sub=1;
            if(option==5){
                temp=reverse(temp);
                temp=Subtract_bigLinkedList(temp,num2);
                //num1=reverse(num1);
                node *rem=Subtract_bigLinkedList(num1,temp);
                reverse(rem);
                return rem;
            }
            break;
        }
        else{
            if(option==5){
                node *rem=createNode();
                rem->data=0;
                return rem;
            }
            break;
        }
        freeList(temp);
    }
    if(sub==0) factor=reverse(factor);
    return factor;
}