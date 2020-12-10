/*
 Este é um esqueleto que deve ser utilzado como base para implementação da Agenda.
	- As funções não tem os parâmetros definidos e os parâmetros caso necessários, devem ser incluídos.
    - Caso seja necessário novas funções podem ser incluídas
 	- Devem ser respeitados os nomes dados mara o métodos e estruturas, porém novas estruturas e funções podem ser criados, caso julgue necessário
	- Faça os includes necessários
	- A organização das funções fica a critério do programador
	- Códigos não identados sofrerão duras penalidades
	- Não serão toleradas variaveis globais
	- Caso seja detectado plágio, os grupos envolvidos receberão nota 0.
*/

#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

//Struct que representa a data.
typedef struct {
	int day;
	int month;
	int year;
} Date;

// Estrutura que contém os campos dos registros da agenda
struct MREC {
     char name[30];
     Date  birth; 
     char email[40];
     char phone[15];
	struct MREC *right;
     struct MREC *left;
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

//Função para deixar a string em lower case
void toLowercase(char *str, int size){
     for(int i = 0; i < size; i++){
          str[i] = tolower(str[i]);
     }
}

// Função responsável por imprimir um contato
void printContact(Contact *contact){
     printf("Nome: %s\n", contact->name);
     printf("Nascimento: %d/%d/%d\n", contact->birth.day, contact->birth.month, contact->birth.year);
     printf("Email: %s\n", contact->email);
     printf("Telefone: %s\n", contact->phone);
     printf("-----------------------------------------------------------------\n");
}

// Apresenta o menu da aplicação e retorna a opção selecionada
int menu()
{
    int op=0;

    printf("-----------------------------------------------------------------\n\n");
    printf("Para Encerrar o programa digite: %d\n", EXIT);     
    printf("Para adicionar um novo contato digite: 1\n");     
    printf("Para deletar um contato digite: 2\n");     
    printf("Para atualizar um contato digite: 3\n");     
    printf("Para buscar um contato digite: 4\n");     
    printf("Para listar os contatos digite: 5\n");     

    printf("\nOpção desejada: ");
    scanf("%d",&op);
     
    return op;
}

int heightThree(Contact *root);
Contact *RR(Contact *root);
Contact *LL(Contact *root);
Contact *LR(Contact *root);
Contact *RL(Contact *root);
int fBalance(Contact *root);
Contact *balanceTree(Contact *root);

//Código com tratamento de recursividade para adicionar um contato na árvore AVL.
Contact *AddContact(Contact *root, Contact *newContact){
     if (root == NULL){
        return newContact;
     } 
     else{
          if(strcmp(tolower(root->name), tolower(newContact->name)) >= 0){
            root->left = AddContact(root->left, newContact);
          }
          else{
            root->right = AddContact(root->right, newContact);
          }
     }
     root = balanceTree(root);
     return root;
}

// Permite o cadastro de um contato
void *insContact(Contact *root)
{    
    Contact *newContact = (Contact *) malloc(sizeof(Contact));
    printf("Insira o nome do contato que deseja adicionar na agenda: ");
    scanf("%s", newContact->name);
    printf("Insira o aniversário do contato: (dia/mes/ano) ");
    scanf("%d/%d/%d", &newContact->birth.day, &newContact->birth.month, &newContact->birth.year);
    printf("Insira o email do contato: ");
    scanf("%s", newContact->email);
    printf("Insira o telefone do contato: ");
    scanf("%s", newContact->phone);
    printContact(newContact);
    root = AddContact(root,newContact);
}

// Permite excluir um contato da agenda
void delContact ()
{
     return;
}

// Lista o conteudo da agenda (todos os campos)
void listContacts ()
{
     return;
}

// Função responsável por buscar na árvore o contato com o nome desejado
Contact* searchContact (Contact *root, char *name)
{
     char contact_name[30];
     strcpy(contact_name, root->name);
     toLowercase(contact_name, sizeof(contact_name));
     toLowercase(name, sizeof(name));

     if(root == NULL){
          return NULL;
     }
     if(strcmp(contact_name, name) == 0){
          return root;
     }
     if(strcmp(contact_name, name) > 0){
          searchContact(root->left, name);
     }
     else{
          searchContact(root->right,name);
    }
}

// Permite consultar um contato da agenda por nome
void queryContact (Contact *root)
{
     char name[30];
     Contact *contact;

     printf("Insira o nome do contato que deseja buscar na agenda: ");
     scanf("%s", name);

     contact = searchContact(root, name);

     if(contact == NULL) {
          printf("O contado não foi encontrado\n");
     } else {
          printContact(contact);
     }
     return;
}

// Permite a atualização dos dados de um contato da agenda
void upContact ()
{
     return;
}

void print2DUtil(Contact *root, int space){ 
     if (root == NULL){
        return; 
     }    
     space += 10; 
  
     print2DUtil(root->right, space); 
  
     printf("\n"); 
     for (int i = 10; i < space; i++) 
        printf(" "); 
     printf("%s\n", root->name); 
   
    print2DUtil(root->left, space); 
}


// Programa principal
int main()
{    
    int op=0;
    Contact *MContact = NULL;

    while (op!=EXIT)
    {
        op=menu();
        switch(op) {
            case 1 : 
                insContact(MContact);
                break;
            case 2 : 
                delContact();
                break;
            case 3 : 
                upContact();
                break;
            case 4 : 
                queryContact(MContact);
                break;
            case 5 : 
                listContacts();
                break;
            default:
                printf("\nOpção não existente\n");
        }
    }
    return 0;
}

int biggestInt(int a, int b){
    return (a > b) ? a : b; 
}

int heightThree(Contact *root){
    int right=0, left=0;
    if (root == NULL){
        return 0;
    }
    else{
        if (root->left == NULL && root->right == NULL){
            return 1;
        }
        else{
            if (root->right != NULL){
                right = (1 + heightThree(root->right));
            }
            if (root->left != NULL){
                left = (1 + heightThree(root->left));
            }
            return biggestInt(right, left);
        }
    }
}

Contact *RR(Contact *root){
    Contact *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

Contact *LL(Contact *root){
    Contact *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

Contact *LR(Contact *root){
    Contact *newRoot = RR(root->left);
    newRoot = LL(root);
    return newRoot;
}

Contact *RL(Contact *root){
    Contact *newRoot = LL(root->right);
    newRoot = RR(root);
    return newRoot;
}

int fBalance(Contact *root){
    int heightLeft = heightThree(root->left), heightRight = heightThree(root->right);
    return (heightLeft-heightRight);
}

Contact *balanceTree(Contact *root){
    int diff = fBalance(root);
    if(diff > 1){
        if(fBalance(root->left) < 0){
            root = LR(root);
        } else{
            root = LL(root);
        }
    }else if(diff < -1){
        if(fBalance(root->right) < 0){
            root = RR(root);
        } else{
            root = RL(root);
        }
    }
    return root;
}