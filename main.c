#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct s
{
    char symbol;
    struct s *next;
} Stack;

FILE *file = NULL;
Stack *head = NULL;
char *M[7][7];
char a;
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void push(char s)
{
    Stack *nouveau = (Stack*) malloc(sizeof(Stack));

    nouveau->symbol = s;
    nouveau->next = head;

    head = nouveau;
}

void pop()
{
    Stack *tmp;
    if(head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
int nonTerminal(char X)
{
    return (X == 'R' || X == 'A' || X == 'E' || X == 'B' || X == 'T' || X == 'C' || X == 'F')? 1 :0;
}

int returnIndexOf(char c)
{
    switch (c)
    {
    case 'R':
    case '+':
        return 0;
    case 'A':
    case '*':
        return 1;
    case 'E':
    case '(':
        return 2;
    case 'B':
    case ')':
        return 3;
    case 'T':
    case 'a':
        return 4;
    case 'C':
    case 'b':
        return 5;
    case 'F':
    case '$':
        return 6;
    }
    return -1;
}

void aForward()
{
    Color(14,0);
    fscanf(file,"%c",&a);
    printf("\nmove a forward, par %c",a);
    Color(15,0);
}

void popX()
{
    Color(12,0);
    printf("\npopX %c",head->symbol);
    pop();
    Color(15,0);

}

void pushYi(char *exp)
{
    int i;
         printf("\npushYi");
   for ( i = strlen(exp) - 1; i != -1; i--)
    {
        printf("\nY[%d] : %c",i,exp[i]);
        push(exp[i]);
    }
}

void showPile()
{
    Color(15,15);
    printf("\n                                                   ");
    Color(15,0);
    Stack *tmp = head;
    printf("\n=====");
    printf("\nPILE:");
    printf("\n=====");
    while(tmp)
    {
        printf("\n  %c  ",tmp->symbol);
        tmp = tmp->next;
    }
    printf("\n=====");
    Color(15,0);
}

void LLpraser()
{
    char exp[5];
    aForward();
    while(1)
    {
        showPile();
        if(nonTerminal(head->symbol))
        {
            printf("\nX = %c is non-terminal",head->symbol);
            strcpy(exp, M[returnIndexOf(head->symbol)][returnIndexOf(a)]);
            if(strcmp(M[returnIndexOf(head->symbol)][returnIndexOf(a)],""))
            {
                popX();
                if (strcmp(exp, "e"))
                    pushYi(exp);
            }
            else
            {
                Color(12,0);
                printf("\nERROR :Case empty in  LL table, M[%d][%d]\n",returnIndexOf(head->symbol),returnIndexOf(a));
                Color(15,0);
          return;
            }
        }
        else
        {
            printf("\nX = %c is terminal",head->symbol);
            if( head->symbol == '$')
            {
                if( a == '$')
                {
                    Color(2,0);
                    puts("\nACCEPTED");
                    Color(15,0);
                    return;

                }
                else
                {
                    puts("ERROR");
                    return;
                }
            }
            else
            {
                if(head->symbol == a)
                {
                    popX();
                    aForward();
                }
                else
                {
                    puts("ERREUR3");
                    return;
                }
            }
        }
    }
}

int main()
{
    int i=0,j=0;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 7; j++)
            M[i][j] = "";

    M[0][2] = M[0][4] = M[0][5] = "EA";

    M[1][0] = "+EA";
    M[1][3] = M[1][6] = "e";

    M[2][2] = M[2][4] = M[2][5] = "TB";

    M[3][0] = M[3][3] = M[3][6] = "e";
    M[3][2] = M[3][4] = M[3][5] = "TB";

    M[4][2] = M[4][4] = M[4][5] = "FC";

    M[5][1]  = "*C";
    M[5][0] = M[5][2] = M[5][3] = M[5][4] = M[5][5] = M[5][6] = "e";

    M[6][2] = "(R)";
    M[6][4] = "a";
    M[6][5] = "b";

    while(1)
    {
        file = fopen("code.txt","r");
        if(!file)
        {
            printf("FILE NOT FOUND !");
            exit(0);
        }
        Color(14,0);
        puts(" _________________________________________________________________");
        puts("|         CCC   OOO   M M   PPP  IIIII  L    EEEE   RRR        |");
        puts("|        C     O   O M M M  P P    I    L    E___   R R        |");
        puts("|        C     O   O M M M  PPP    I    L    E      RRR        |");
        puts("|         CCC   OOO  M   M  P    IIIII  LLLL EEEE   R  R       |");
        Color(0,15);
        puts("|                                    By : Brahim Ben Addi      |");
        Color(0,14);
        puts("|                                                              |");
        puts("|         LL praser                                            |");
        puts("|   create code.txt file, which has your text such as a+b$     |");
        puts("|                                                              |");
        Color(15,0);
        while(head)
            pop();
        push('$');
        push('R');
        system("PAUSE");
        LLpraser();
        system("PAUSE");
        system("ClS");
        fclose(file);
    }
    return 0;
}
