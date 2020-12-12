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

/*o q falta ajustar:
    - Adicionar dois nomes no insertion.
    - resolver conflito de nomes iguais.
    - Deixar o menu bonitinho
    - arrumar free no del
    - ajustar código (separar em .h e deixar bonito)
    - Pressione enter para mostrar (5 contatos por vez na listagem)
    - LUXO:
        - busca por índice (letra a), aí aparece os nomes q começam com a.
*/

#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

//Struct que representa a data.
typedef struct 
{
	int day;
	int month;
	int year;
} Date;

// Estrutura que contém os campos dos registros da agenda
struct MREC 
{
    char name[30];
    Date  birth; 
    char email[40];
    char phone[15];
	struct MREC *right;
    struct MREC *left;
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

//Instanciamento das funções para tratar ordem de utilização
void printContact(Contact *contact);
int heightThree(Contact *root);
Contact *RR(Contact *root);
Contact *LL(Contact *root);
Contact *LR(Contact *root);
Contact *RL(Contact *root);
int fBalance(Contact *root);
Contact *balanceTree(Contact *root);
Contact *biggestNode(Contact *root);
Contact* searchContact (Contact *root, char *name);
void queryContact (Contact *root);
Contact *AddContact(Contact *root, Contact *newContact);
Contact *insContact(Contact *root);
Contact *delContact (Contact *root);
Contact *removeContact(Contact *root, Contact *contactDel);
void listContacts ();
Contact* upContact ();
void print2DUtil(Contact *root, int space);

// Função responsável por imprimir um contato
void printContact(Contact *contact)
{
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

//Código com tratamento de recursividade para adicionar um contato na árvore AVL.
Contact *AddContact(Contact *root, Contact *newContact)
{
    if (root == NULL){
        return newContact;
    } 
    else{
        if(strcasecmp(root->name,newContact->name) >= 0){
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
Contact *insContact(Contact *root)
{    
    Contact *newContact = (Contact *) malloc(sizeof(Contact));
    printf("\n");
    printf("Insira o nome do contato que deseja adicionar na agenda: ");
    scanf("%s", newContact->name);
    printf("Insira o aniversário do contato: (dia/mes/ano) ");
    scanf("%d/%d/%d", &newContact->birth.day, &newContact->birth.month, &newContact->birth.year);
    printf("Insira o email do contato: ");
    scanf("%s", newContact->email);
    printf("Insira o telefone do contato: ");
    scanf("%s", newContact->phone);
    root = AddContact(root,newContact);
    return root;
}

// Permite excluir um contato da agenda
Contact *delContact (Contact *root)
{   
    char name[30];

    printf("Insira o nome do contato que deseja deletar da agenda: ");
    scanf("%s", name);

    Contact *contact = searchContact(root, name);

    if(contact == NULL) {
        printf("-----------------------------------------------------------------\n\n");
        printf("O contado não foi encontrado\n");
    } else {
        root = removeContact(root,contact);
    }
    return root;
}

//Código com tratamento de recursividade para remover um contato na árvore AVL.
Contact *removeContact(Contact *root, Contact *contactDel)
{
    if (root == NULL){
        return NULL;
    } 
    else{
        if(strcasecmp(root->name,contactDel->name) == 0){
            if(root->left == NULL && root->right == NULL){
                free(root);
                return NULL;
            }
            else if(root->left != NULL && root->right == NULL){
                Contact *newRoot = root->left;
                // free(root); /*Não conseguimos dar free no Root, causa Segmentarion Fault*/
                return newRoot;
            }
            else if(root->left == NULL && root->right != NULL){
                Contact *newRoot = root->right;
                // free(root);
                return newRoot;
            }
            else{
                Contact *newRoot;
                if(root->left->right == NULL){
                    newRoot = root->left;
                    newRoot->right = root->right;
                    // free(root);
                    return newRoot;
                }
                else{
                    newRoot = biggestNode(root->left);
                    newRoot->left = root->left;
                    newRoot->right = root->right;
                    // free(root);
                    return newRoot;
                }
            }
        }
        else if(strcasecmp(root->name,contactDel->name) > 0){
            root->left = removeContact(root->left, contactDel);
        }
        else{
            root->right = removeContact(root->right, contactDel);
        }
    }
    root = balanceTree(root);
    return root;
}

// Lista o conteudo da agenda (todos os campos)
void listContacts (Contact * root)
{
    if (root == NULL){
        return;
    }
    else {
        if(root->left != NULL) {
            listContacts(root->left);
        }
        printContact(root);
        if(root->right != NULL) {
            listContacts(root->right);
        }
    }
}

// Função responsável por buscar na árvore o contato com o nome desejado
Contact* searchContact (Contact *root, char *name)
{
   if(root == NULL){
        return NULL;
    } else {
        int name_compare = strcasecmp(root->name, name);

        if(name_compare == 0){
            return root;
        }
        if(name_compare > 0){
            searchContact(root->left, name);
        }
        else{
            searchContact(root->right, name);
        }
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
        printf("-----------------------------------------------------------------\n\n");
        printf("O contado não foi encontrado\n");
    } else {
        printf("-----------------------------------------------------------------\n\n");
        printf("Contato buscado:\n");
        printContact(contact);
    }
    return;
}

// Permite a atualização dos dados de um contato da agenda
Contact * upContact (Contact *root)
{
    char name[30];
    Contact *contact;
    Contact *editedContact = (Contact *) malloc(sizeof(Contact));

    printf("Insira o nome do contato que deseja atualizar na agenda: ");
    scanf("%s", name);

    contact = searchContact(root, name);

    if (contact != NULL) { // Se o contato foi encontrado
        // faz a leitura dos dados que serão alterados
        printf("\n--------------- Contato encontrado ---------------\n");
        printf("\nInsira o novo nome para o campo, caso deseje manter o valor atual digite -1:\n\n");
        printf("Nome atual: %s\n- Novo nome: ", contact->name);
        scanf("%s", editedContact->name);
        printf("\nNascimento atual: %d/%d/%d\n- Nova data de nascimento: ", contact->birth.day, contact->birth.month, contact->birth.year);
        scanf("%d/%d/%d", &editedContact->birth.day, &editedContact->birth.month, &editedContact->birth.year);
        printf("\nEmail atual: %s\n- Novo email: ", contact->email);
        scanf("%s", editedContact->email);
        printf("\nTelefone atual: %s\n- Novo telefone: ", contact->phone);
        scanf("%s", editedContact->phone);

        // Caso o nome do contato não seja alterado apenas alteramos o valor dos atributos
        if (strcmp(editedContact->name, contact->name) == 0 || strcmp(editedContact->name, "-1") == 0){
            if(strcasecmp(editedContact->email, contact->email) != 0 && strcasecmp(editedContact->email, "-1") != 0)
                strcpy(contact->email, editedContact->email);
            if(strcasecmp(editedContact->phone, contact->phone) != 0 && strcasecmp(editedContact->phone, "-1") != 0)
                strcpy(contact->phone, editedContact->phone);
            if(editedContact->birth.day != contact->birth.day && editedContact->birth.day != -1){
                contact->birth.day = editedContact->birth.day;
                contact->birth.month = editedContact->birth.month;
                contact->birth.year = editedContact->birth.year;
            }
            printf("\nContato alterado com sucesso!\n");
        } else { // Caso o nome do contato seja alterado excluimos o nodo anterior e criamos um novo com os dados atualizados
                    // e o reincerimos na tabela
            if(strcasecmp(editedContact->email, "-1") == 0) 
                strcpy(editedContact->email, contact->email);
            if(strcasecmp(editedContact->phone, "-1") == 0) 
                strcpy(editedContact->phone, contact->phone);
            if(editedContact->birth.day == -1){
                editedContact->birth.day = contact->birth.day;
                editedContact->birth.month = contact->birth.month;
                editedContact->birth.year = contact->birth.year;
            }
            root = removeContact(root, contact);
            root = AddContact(root, editedContact);
            printf("\nContato alterado com sucesso!\n");
        }
    } else {
        printf("Contato não encontrado!\n");
    }
    return root;   
}

// Função criada para testes com print em formato da árvore
void print2DUtil(Contact *root, int space)
{ 
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

// Função para limpar a árvore (Free) após a gravação em arquivo
void cleanAVL(Contact *root)
{
    if (root == NULL){
        return;
    }
    else{
        if(root->left != NULL){
            cleanAVL(root->left);
        }
        if(root->right != NULL){
            cleanAVL(root->right);
        }
        free(root);
    }
}

// Função que lê do arquivo e puxa os contatos para o programa
Contact *fileRead(Contact *root, FILE *file)
{
    Contact *aux = malloc(sizeof(Contact));
    while (fread(aux, sizeof(Contact), 1, file) > 0)
    {
        aux->left=NULL;/* A estrutura é salva com os ponteiros para right e left, precisamos anular para poder usar a recursividade */
        aux->right=NULL;
        root = AddContact(root,aux);
        aux = malloc(sizeof(Contact));
    }
    free(aux);
    return root;
}

// Função que grava os contatos do programa no arquivo, retorna o número de contatos gravados
int fileWrite(Contact *root, FILE *file)
{
    int nContacts = 0;
    if (root == NULL){
        return 0;
    }
    else{
        nContacts += fwrite(root, sizeof(Contact), 1, file);
        if(root->left != NULL){
            nContacts += fileWrite(root->left, file);
        }
        if(root->right != NULL){
            nContacts += fileWrite(root->right, file);
        }
        return nContacts;
    }
}

// Função que percorre a árvore e retorna o número de contatos na estrutura
int numberContacts(Contact *root)
{
    int nContacts = 0;
    if (root == NULL){
        return 0;
    }
    else{
        nContacts++;
        if(root->left != NULL){
            nContacts += numberContacts(root->left);
        }
        if(root->right != NULL){
            nContacts += numberContacts(root->right);
        }
        return nContacts;
    }
}

// Programa principal
int main()
{   
    int op=0, nContacts = 0;
    Contact *MContact = NULL;

    FILE *mainAgenda = fopen("Agenda_DrChapatin.ag","a+b");
    if (mainAgenda == NULL)
    {   
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }
    MContact = fileRead(MContact,mainAgenda);
    fclose(mainAgenda);

    nContacts = numberContacts(MContact);

    while (op!=EXIT)
    {   
        op=menu();
        switch(op) {
            case 1 : 
                MContact = insContact(MContact);
                nContacts++;
                print2DUtil(MContact,0);
                break;
            case 2 : 
                MContact = delContact(MContact);
                nContacts--;
                print2DUtil(MContact,0);
                break;
            case 3 : 
                MContact = upContact(MContact);
                break;
            case 4 : 
                queryContact(MContact);
                break;
            case 5 : 
                printf("\nLista de contatos:\nNúmero de Contatos: %d\n\n", nContacts);
                listContacts(MContact);
                break;
            case 10:
                break;
            default:
                printf("\nOpção não existente\n");
        }
    }
    mainAgenda = fopen("Agenda_DrChapatin.ag","wb");

    int nwrite = fileWrite(MContact,mainAgenda);
    fclose(mainAgenda);
    if(nwrite != nContacts)
    {
        printf("Problema na gravação\n");
        exit(1);
    }

    cleanAVL(MContact);
    return 0;
}

int biggestInt(int a, int b)
{
    return (a > b) ? a : b; 
}

int heightThree(Contact *root)
{
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

Contact *RR(Contact *root)
{
    Contact *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

Contact *LL(Contact *root)
{
    Contact *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

Contact *LR(Contact *root)
{
    root->left = RR(root->left);
    Contact *newRoot = LL(root);
    return newRoot;
}

Contact *RL(Contact *root)
{
    root->right = LL(root->right);
    Contact *newRoot = RR(root);
    return newRoot;
}

int fBalance(Contact *root)
{
    int heightLeft = heightThree(root->left), heightRight = heightThree(root->right);
    return (heightLeft-heightRight);
}

Contact *balanceTree(Contact *root)
{
    int diff = fBalance(root);
    if(diff > 1){
        if(fBalance(root->left) < 0){
            root = LR(root);
        } 
        else{
            root = LL(root);
        }
    }
    else if(diff < -1){
        if(fBalance(root->right) < 0){
            root = RR(root);
        } else{
            root = RL(root);
        }
    }
    return root;
}

Contact *biggestNode(Contact *root)
{
    Contact *father = root;

    if (root == NULL){
        printf("Não pode entrar aqui, se entra tem erro de lógica.\n\n");
    }

    root = root->right;
    while(root->right != NULL){
        father = root;
        root = root->right;
    }
    //aqui o root ja é o maior, não tem filhos a direita.
    father->right = root->left; //tirei o root da árvore
    return root;
}
