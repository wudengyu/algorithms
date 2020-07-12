#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define NHASH 400000
#define MULT 1337
int postion = 0;
struct wordlist
{
    char word[51];
    struct wordlist *link;
} * hashlist[400000], *f;
struct wrongword
{
    char word[51];
    int pos[2000];
    int time;
} wrongwordlist[25000];
unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = (MULT * h + *p) % NHASH;
    return h;
}
void hashbulid()
{
    char word[51];
    int m;
    FILE *in;
    in = fopen("dictionary.txt", "r");
    while (fscanf(in, "%s", word) != EOF)
    {
        m = hash(word);
        if (hashlist[m] == NULL)
        {
            hashlist[m] = (struct wordlist *)malloc(sizeof(struct wordlist));
            hashlist[m]->link = NULL;
            strcpy(hashlist[m]->word, word);
        }
        else
        {
            f = hashlist[m];
            while (f->link != NULL)
            {
                f = f->link;
            }
            f->link = (struct wordlist *)malloc(sizeof(struct wordlist));
            f = f->link;
            f->link = NULL;
            strcpy(f->word, word);
        }
    }
    fclose(in);
}
int hashfind(char *str)
{
    int m;
    m = hash(str);
    if (hashlist[m] == NULL)
        return 0;
    else
    {
        f = hashlist[m];
        while (f != NULL)
        {
            if (strcmp(str, f->word) == 0)
                return 1;
            else
                f = f->link;
        }
        return 0;
    }
}
int check()
{
    char ch,word[51];
    int inwordposition=0,wrongwordcount=0;
    long articleposition=0,wordstartposition=0;
    FILE *in;
    in = fopen("article.txt", "r");
    while((ch=fgetc(in))!=EOF)
    {
        if(ch>=65&&ch<=90)
            ch+=32;
        if(ch>=97&&ch<=122)
        {
            if(inwordposition==0)
            {
                wordstartposition=articleposition;
            }
            word[inwordposition++]=ch;
        }
        else if(inwordposition!=0)
        {
            word[inwordposition]='\0';
            inwordposition=0;
            if(!hashfind(word))
            {
                int i;
                for(i=0;i<wrongwordcount;i++)
                {
                    if(strcmp(wrongwordlist[i].word,word)==0)
                    break;
                }
                if(i==wrongwordcount)
                {
                    strcpy(wrongwordlist[i].word,word);
                    wrongwordlist[i].time=0;
                    wrongwordcount++;
                }
                wrongwordlist[i].pos[wrongwordlist[i].time++]=wordstartposition;
            }
        }
        if(ch!='\n')
            articleposition++;
    }
    fclose(in);
    return wrongwordcount;
}
void buttlesort(int n)
{
    int i, j;
    struct wrongword temp;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-1-i; j++)
        {
            if (wrongwordlist[j].time < wrongwordlist[j + 1].time)
            {
                temp = wrongwordlist[j];
                wrongwordlist[j] = wrongwordlist[j + 1];
                wrongwordlist[j + 1] = temp;
            }
            else if (wrongwordlist[j].time == wrongwordlist[j + 1].time)
            {
                if (strcmp(wrongwordlist[j].word, wrongwordlist[j + 1].word) > 0)
                {
                    temp = wrongwordlist[j];
                    wrongwordlist[j] = wrongwordlist[j + 1];
                    wrongwordlist[j + 1] = temp;
                }
            }
        }
}
void putout(int n)
{
    FILE *out;
    out = fopen("misspelling.txt", "w");
    int i, j;
    for (i = 0; i < n; i++)
    {
        fprintf(out, "%s %d", wrongwordlist[i].word, wrongwordlist[i].time);
        for (j = 0; j < wrongwordlist[i].time; j++)
        {
            fprintf(out, " %d", wrongwordlist[i].pos[j]);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}
int main()
{
    int n;
    hashbulid();
    n = check();
    buttlesort(n);
    putout(n);
    return 0;
}
