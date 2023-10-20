typedef struct node{
    int data;
    struct node *next;
}node;

node* AddbigInt(char *a,char *b);
node* Subtract_bigInt(char *a,char *b);
node* Multiply_bigInt(char *a,char *b);
node* Divide_bigInt(char *a,char *b,int option);
node* Mod_bigInt(char *a,char *b);

node* convertToLL(char *str);
void print(node *head);