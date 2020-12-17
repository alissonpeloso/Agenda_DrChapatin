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
#include "AVL.h"

#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

//Structs foram transferidas para AVL.h, para melhor organização :)

//Pré-instanciamento para atender uso da função nas demais funções
Contact* searchContact (Contact *root, char *name);

// Apresenta o menu da aplicação e retorna a opção selecionada
int menu()
{
    int op=0;
    printf("\nSelecione a opção desejada abaixo:\n");
    printf("================================== MENU ==================================\n");
    printf("1 - Criar novo contato | 2 - Deletar um Contato | 3 - Atualizar um contato \n4 - Buscar um Contato  | 5 - Listar Contatos    | 10 - Encerrar\n");   
    printf("==========================================================================\n");
    
    printf("\nOpção desejada: ");
    scanf("%d",&op);
            
    return op;
}

//Código com tratamento de recursividade para adicionar um contato na árvore AVL.
Contact *AddContact(Contact *root, Contact *newContact)
{
    newContact->right = NULL;
    newContact->left = NULL;
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
    printf("- Insira o nome do contato que deseja adicionar na agenda: ");
    getchar();
    scanf("%[^\n]s", newContact->name);
    Contact *aux = searchContact(root,newContact->name);
    if(aux != NULL){
        printf("\n");
        printf("ERRO: Esse contato já existe!\n");
        return root;
    }
    printf("- Insira o aniversário do contato (dia/mes/ano): ");
    scanf("%d/%d/%d", &newContact->birth.day, &newContact->birth.month, &newContact->birth.year);
    while(newContact->birth.day > 31 || newContact->birth.day < 1 || newContact->birth.month < 1 || newContact->birth.month > 12 || newContact->birth.year < 1000 || newContact->birth.year > 2020){
        printf("*ERRO*: Insira uma data válida (dia/mes/ano): ");
        scanf("%d/%d/%d", &newContact->birth.day, &newContact->birth.month, &newContact->birth.year);
    }
    printf("- Insira o email do contato (example@example.com): ");
    scanf("%s", newContact->email);
    printf("- Insira o telefone do contato ((99)99999-9999): ");
    getchar();
    scanf("%[^\n]s", newContact->phone);
    root = AddContact(root,newContact);
    printf("\n\t**Contato inserido com sucesso!**\n");
    return root;
}

//Código com tratamento de recursividade para remover um contato na árvore AVL.
Contact *removeContact(Contact *root, Contact *contactDel)
{
    if (root == NULL){
        return NULL;
    } 
    else{
        Contact *newRoot;
        if(strcasecmp(root->name,contactDel->name) == 0){
            if(root->left == NULL && root->right == NULL){
                return NULL;
            }
            else if(root->left != NULL && root->right == NULL){
                newRoot = root->left;
            }
            else if(root->left == NULL && root->right != NULL){
                newRoot = root->right;
            }
            else{
                if(root->left->right == NULL){
                    newRoot = root->left;
                    newRoot->right = root->right;
                }
                else{
                    newRoot = biggestNode(root->left);
                    newRoot->left = root->left;
                    newRoot->right = root->right;
                }
            }
            free(root);
            newRoot = balanceTree(newRoot);
            return newRoot;
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

// Permite excluir um contato da agenda
Contact *delContact (Contact *root)
{   
    char name[30];

    printf("- Insira o nome do contato que deseja deletar da agenda: ");
    getchar();
    scanf("%[^\n]s", name);

    Contact *contact = searchContact(root, name);

    if(contact == NULL) {
        printf("-----------------------------------------------------------------\n\n");
        printf("*ERRO*: O contado não foi encontrado\n");
    } else {
        root = removeContact(root,contact);
        printf("\n\t**Contato removido com sucesso!**\n");
    }
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

    printf("- Insira o nome do contato que deseja buscar na agenda: ");
    getchar();
    scanf("%[^\n]s", name);

    contact = searchContact(root, name);

    if(contact == NULL) {
        printf("-----------------------------------------------------------------\n\n");
        printf("*ERRO*: O contado não foi encontrado\n");
    } else {
        printf("-----------------------------------------------------------------\n\n");
        printf("**Contato buscado:**\n\n");
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

    printf("- Insira o nome do contato que deseja atualizar na agenda: ");
    getchar();
    scanf("%[^\n]s", name);

    contact = searchContact(root, name);

    if (contact != NULL) { // Se o contato foi encontrado
        // faz a leitura dos dados que serão alterados
        printf("\n--------------- Contato encontrado ---------------\n");
        printf("\n*Insira o novo nome para o campo, caso deseje manter o valor atual digite -1*\n\n");
        printf("Nome atual: %s\n- Novo nome: ", contact->name);
        getchar();
        scanf("%[^\n]s", editedContact->name);
        printf("\nNascimento atual: %d/%d/%d\n- Nova data de nascimento (dia/mes/ano): ", contact->birth.day, contact->birth.month, contact->birth.year);
        scanf("%d/%d/%d", &editedContact->birth.day, &editedContact->birth.month, &editedContact->birth.year);
        while(editedContact->birth.day > 31 || editedContact->birth.day < 1 || editedContact->birth.month < 1 || editedContact->birth.month > 12 || editedContact->birth.year < 1000 || editedContact->birth.year > 2020){
            printf("ERRO: Insira uma data válida (dia/mes/ano): ");
            scanf("%d/%d/%d", &editedContact->birth.day, &editedContact->birth.month, &editedContact->birth.year);
        }              
        printf("\nEmail atual: %s\n- Novo email (example@example.com): ", contact->email);
        scanf("%s", editedContact->email);
        printf("\nTelefone atual: %s\n- Novo telefone ((99)99999-9999): ", contact->phone);
        getchar();
        scanf("%[^\n]s", editedContact->phone);

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
            printf("\n\t**Contato alterado com sucesso!**\n");
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
            printf("\n\t**Contato alterado com sucesso!**\n");
        }
    } else {
        printf("*ERRO*: Contato não encontrado!\n");
    }
    return root;   
}

// Função que lê do arquivo e puxa os contatos para o programa
Contact *fileRead(Contact *root, FILE *file)
{
    Contact *aux = malloc(sizeof(Contact));
    while (fread(aux, sizeof(Contact), 1, file) > 0)
    {
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

    printf("\n###########################################################################\n");
    printf("#                       [ Bem-vindo Dr. Chapatin ]                        #\n");
    printf("###########################################################################\n");

    while (op!=EXIT)
    {   
        op=menu();
        switch(op) {
            case 1 : 
                MContact = insContact(MContact);
                nContacts++;
                break;
            case 2 : 
                MContact = delContact(MContact);
                nContacts--;
                break;
            case 3 : 
                MContact = upContact(MContact);
                break;
            case 4 : 
                queryContact(MContact);
                break;
            case 5 : 
                printf("\n***Lista de contatos***\nNúmero de Contatos: %d\n\n", nContacts);
                listContacts(MContact);
                break;
            case 10:
                system("exit");
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