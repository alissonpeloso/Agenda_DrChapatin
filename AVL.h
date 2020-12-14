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

// Função responsável por imprimir um contato
void printContact(Contact *contact)
{
     printf("Nome: %s\n", contact->name);
     printf("Nascimento: %d/%d/%d\n", contact->birth.day, contact->birth.month, contact->birth.year);
     printf("Email: %s\n", contact->email);
     printf("Telefone: %s\n", contact->phone);
     printf("-----------------------------------------------------------------\n");
}

//Função que compara e retorna o maior inteiro, utilizada na função heighThree.
int biggestInt(int a, int b)
{
    return (a > b) ? a : b; 
}

//Função que percorre a árvore e retorna a altura (int)
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

//Realiza rotação para balancear árvore na situação right right (todos os nodos à direita)
Contact *RR(Contact *root)
{
    Contact *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

//Realiza rotação para balancear árvore na situação left left (todos os nodos à esquerda)
Contact *LL(Contact *root)
{
    Contact *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

//Realiza rotação para balancear árvore na situação left right (nodo à esquerda e depois à direita)
Contact *LR(Contact *root)
{
    root->left = RR(root->left);
    Contact *newRoot = LL(root);
    return newRoot;
}

//Realiza rotação para balancear árvore na situação right left (nodo à direita e depois à esquerda)
Contact *RL(Contact *root)
{
    root->right = LL(root->right);
    Contact *newRoot = RR(root);
    return newRoot;
}

//Função que retorna o diferencial entre altura dos dois filhos do nodo
int fBalance(Contact *root)
{
    int heightLeft = heightThree(root->left), heightRight = heightThree(root->right);
    return (heightLeft-heightRight);
}

//Função que verifica as situação e realiza a operação adequada para equilibrar a árvore
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

//Verifica e retorna qual é o maior nodo (utilizado para deletar um nodo "pai" da árvore)
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