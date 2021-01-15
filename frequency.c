#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_LETTERS (int)26
#define END_OF_WORD (char)'$'
#define HEAD_LETTER (char)'*'


typedef struct _Node{
    char letter;
    long unsigned int frequency;
    struct _Node *next[NUM_OF_LETTERS+1];
} Node;

char check_mode(int argc, char **argv)
{
    if(argc > 1)
    {
        char *str = argv[1];
        if(strlen(str) == 1 && str[0] == 'r')
        {
            return 1;
        }
    }
    return 0;
}

int char_to_int(char c)
{
    return c - 'a';
}

char capslock_off(char c)
{
    if('a' <= c && c <= 'z')
    {
        return c;
    }
    else if('A' <= c && c <= 'z')
    {
         return c + 32;
    }
    return 0;
}

Node* new_node(char c)
{
    Node *nodeptr = (Node*)malloc(sizeof(Node));
    if(nodeptr == NULL)
    {
        return NULL;
    }
    nodeptr->letter = c;
    nodeptr->frequency = 1;
    for(int i = 0; i<NUM_OF_LETTERS+1; i++)
    {
        nodeptr->next[i] = NULL;
    }
    return nodeptr;
}


Node new_trie()
{
    Node new_tri;
    new_tri.frequency = 0;
    new_tri.letter = HEAD_LETTER;
    for(int i = 0; i<NUM_OF_LETTERS+1; i++)
    {
        new_tri.next[i] = NULL;
    }
    return new_tri;
}

void build_trie(Node *trie)
{
    char c = '\0';
    Node *curr = trie;
    while(scanf("%c",&c)!=EOF)
    {
        char ch = capslock_off(c);
        if(ch)
        {
            int i = char_to_int(ch);
            if(curr->next[i] == NULL)
            {
                curr->next[i] = new_node(ch);
                if(curr->next[i] == NULL)
                {
                    printf("Error allocating memory\n");
                    break;
                }
            }
            else
            {
                curr->next[i]->frequency++;
            }
            curr = curr->next[i];
        }
        else if(curr != trie)
        {
            if(curr->next[NUM_OF_LETTERS] == NULL)
            {
                curr->next[NUM_OF_LETTERS] = new_node(END_OF_WORD);
            }
            else
            {
                curr->next[NUM_OF_LETTERS]->frequency++;
            }
            curr = trie;
        } 
    }
}

long unsigned int print_word(Node *n, char mode)
{
    long unsigned int f = 0;
    if(n->letter == END_OF_WORD)
    {
        f = n ->frequency;
        printf(" %ld\n", f);
        free(n);
        return f;
    }
    printf("%c",n->letter);
    if(!mode && n->next[NUM_OF_LETTERS] != NULL)
    {
        f = print_word(n->next[NUM_OF_LETTERS], mode);
        n->next[NUM_OF_LETTERS] = NULL;
    }
    else
    {
        int i = 0;
        if(mode)
        {
            i = NUM_OF_LETTERS-1;
        }
        while (n->next[i] == NULL && i < NUM_OF_LETTERS +1 && i > -2)
        {
            if(mode)
            {
                i--;
            }
            else
            {
                i++;
            }
        }
        if(i == -1)
        {
            f = print_word(n->next[NUM_OF_LETTERS], mode);
            n->next[NUM_OF_LETTERS] = NULL;
        }
        else
        {
            long unsigned int fd = n->next[i]->frequency;
            f = print_word(n->next[i], mode);
            if(fd == f)
            {
                n->next[i] = NULL;
            }
        }
    }
    n->frequency-=f;
    if(n->frequency == 0)
    {
        free(n);
    }
    return f;
}

void print_trie(Node* node, char mode)
{
    if(mode)
    {
        for(int i = NUM_OF_LETTERS; i > -1 ; i--)
    {
        while (node->next[i] != NULL)
        {
            long unsigned int f = node->next[i]->frequency;
            long unsigned int fd = print_word(node->next[i], mode);
            if(fd == f)
            {
                node->next[i] = NULL;
            }
        }
    }
    }
    else
    {
        for(int i = 0; i < NUM_OF_LETTERS; i++)
        {
            while (node->next[i] != NULL)
            {
                long unsigned int f = node->next[i]->frequency;
                long unsigned int fd = print_word(node->next[i], mode);
                if(fd == f)
                {
                    node->next[i] = NULL;
                }
            }
        }   
    }
}

int main(int argc,char**argv)
{
    char mode = check_mode(argc, argv);
    Node trie = new_trie();
    build_trie(&trie);
    print_trie(&trie, mode);
    return 0;
}