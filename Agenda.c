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

// Apresenta o menu da aplicação e retorna a opção selecionada
int menu()
{
    int op=0;
    while (op!=EXIT || op!=1)
    {
        printf("%d Finaliza",EXIT);
        printf("\n: ");
        scanf("%d",&op);
     }    
    return op;
}

// Permite o cadastro de um contato
void *insContact(Contact *root)
{    
     Contact *newContact = (Contact *)malloc(sizeof(Contact));
     printf("Insira o nome do contato que deseja adicionar na agenda: ");
     scanf("%s", &newContact->name);
     printf("Insira o aniversário do contato: (dia/mes/ano) ");
     scanf("%d/%d/%d", &newContact->birth.day, &newContact->birth.month, &newContact->birth.year);
     printf("Insira o email do contato: ");
     scanf("%s", &newContact->email);
     printf("Insira o telefone do contato: ");
     scanf("%s", &newContact->phone);
     return;
}

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

// Função responsável por buscar na árvore o contato com o nome desejado
Contact* searchContact (Contact *root, char *name)
{
     if(root == NULL){
          return NULL;
     }
     if(strcmp(tolower(root->name), tolower(name)) == 0){
          return root;
     }
     if(strcmp(tolower(root->name), tolower(name)) > 0){
          searchContact(root->left, name);
     }
     else{
          searchContact(root->right,name);
     }
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
          switch(op)
          {
               case 1 : insContact(MContact);
               case 2 : delContact();
               case 3 : upContact();
               case 4 : queryContact(MContact);
               case 5 : listContacts();
          }
    }
    return 0;
}
