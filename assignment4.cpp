#include<iostream>
#include<string.h>
#include<stack>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

FILE *fp, *fp2, *fp3, *fp4;

void addLineNumber()
{
    char c, lna[10];
    int ln = 1, x;

    fp = fopen("input.c", "r");
    fp2 = fopen("output.txt", "w");

    if(!fp)
        cout<<"\nFile can't be opened!";
    else
    {
        while((c = fgetc(fp)) != EOF)
        {
            itoa(ln, lna, 10);
            for(x=0; x < strlen(lna); x++)
                fputc(lna[x], fp2);
            fputc(' ', fp2);
            while(c!='\n')
            {
                fputc(c, fp2);
                c = fgetc(fp);
            }
            fputc('\n', fp2);
            ln++;
        }
    }
    fclose(fp);
    fclose(fp2);
    fp2=fopen("output.txt","r");
    cout<<"After Adding Line Numbers, Output: "<<endl;
    while((c=fgetc(fp2))!=EOF)
        printf("%c",c);
    fclose(fp2);
}

void comment_whitespace_remove()
{
    char c,d,e,f;
    int cnt=0;

    fp=fopen("output.txt","r");
    fp2=fopen("output1.txt","w");

    if(!fp)
    {
        cout<<"\nFile can't be opened!";
    }
    else
    {
        while((c=fgetc(fp))!=EOF)
        {
            if(c=='/')
            {
                d=fgetc(fp);
                if(d=='/')
                {
                    while((e=fgetc(fp))!='\n');
                }
                else if(d=='*')
                {
                    while((f=fgetc(fp))!='/');
                }
            }
            else
            {
                if(c==' ')
                {
                    if(cnt==0)
                    {
                        fputc(c, fp2);
                    }
                    cnt++;
                }
                if((c!=' ') && (c!='\t') && (c!='\r'))
                {
                    fputc(c, fp2);
                    cnt=0;
                }
            }

        }
    }
    fclose(fp);
    fclose(fp2);
    fp2=fopen("output1.txt","r");
    cout<<"\nAfter Removing Comments and White Space, Output:"<<endl;
    while((c=fgetc(fp2))!=EOF)
        printf("%c",c);
	fclose(fp2);
}
bool bracket_pair(char start, char last)
{
    if(start=='(' && last==')')
        return true;
    if(start=='{' && last=='}')
        return true;
    if(start=='[' && last==']')
        return true;
    return false;
}
void parentheses_check()
{
    char c,d,e,f;
    stack<char> st;
    int ln=1;
    fp=fopen("output1.txt","r");
    if(!fp)
    {
        cout<<"\nFile can't be opened!";
    }
    else
    {
        while((c=fgetc(fp))!=EOF)
        {
            if(c=='\n')
            {
                ln++;
            }
            if((c=='(')||(c=='{')||(c=='['))
            {
                st.push(c);
            }
            else if((c==')')||(c=='}')||(c==']'))
            {
                if(st.empty()||!bracket_pair(st.top(), c))
                {
                    cout<< "Misplaced parentheses '" << c << "' at line no: " <<ln <<endl;
                }
                else
                {
                    st.pop();
                }
            }
        }
        if(!st.empty())
        {
            cout << "Unbalanced parentheses at line: " << ln-1 <<endl;
        }
    }
}
bool condition_pair(string start, string last)
{
    if(start=="if" && last=="else")
        return true;
    return false;
}
void condition_check()
{
    char c,f,h,d;
    stack<string>  S_if;
    int ln = 1,cnt = 0,k = 1,dup_flag = 0;
    int  s_flag[1000];
    char str[1000];
    string w;

    fp = fopen("output3.txt","r");
    while (fgets(str, sizeof str, fp) != NULL)
    {
        cnt = 0;
        char *p = str;
        char word[sizeof str];
        int n;
        dup_flag = 0;
        while (sscanf(p, "%s%n", word, &n) == 1)
        {
            w = word;
            s_flag[k] = 0;

            if(w == "if")
            {
                S_if.push(word);
            }
            else if(w == "else")
            {

                if(S_if.empty() || !condition_pair(S_if.top(),word))
                {
                    cout << "Unmatched else at line no: " << ln <<endl;

                }

                else
                    S_if.pop();
            }
            if(w == ";")
            {
                s_flag[k] = 1;
                if((cnt > 0)&& (s_flag[k-1] == 1) && (dup_flag == 0))
                {
                    dup_flag = 1;
                    cout <<"Duplicate token '" << w << "' at line no: " <<ln <<endl;
                }
                cnt++;
            }
            p += n;
            k++;
        }
        ln++;
    }
    fclose(fp);
}
void lexeme_separate()
{
    char c,d;
    fp=fopen("output1.txt","r");
    fp2=fopen("output2.txt","w");

    fputc(' ',fp2);
    while((c=fgetc(fp))!=EOF)
    {
        if((!isalnum(c)) && (c!=' ') && (c!='_') && (c!='.') && (c!='\n'))
        {
            fputc(' ', fp2);
        }
        fputc(c,fp2);

        if((c=='=')||(c=='<')||(c=='>')||(c=='!'))
        {
            d=fgetc(fp);
            if(d=='=')
            {
                fputc(d, fp2);
                fputc(' ', fp2);
            }
            else{
                fputc(' ',fp2);
                fputc(d, fp2);
                if((!isalnum(d)) && (d!=' ') && (d!='_') && (d!='.')){
                    fputc(' ', fp2);
                }
            }
        }
        else if((!isalnum(c)) && (c!=' ') && (c!='_') && (c!='.'))
        {
            fputc(' ', fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    fp2=fopen("output2.txt","r");
    cout<<"\nAfter Separating Lexames, Output:"<<endl;
    while((c=fgetc(fp2))!=EOF)
        printf("%c",c);
    fclose(fp2);
}
int keyword(char lex[])
{
    int i, flag=0;
    char keywords[32][20]={"auto","double","int","struct",
                             "break","else","long","switch",
                             "case","enum","register","typedef",
                             "char","extern","return","union",
                             "const","float","short","unsigned",
                             "continue","for","signed","void",
                             "default","goto","sizeof","volatile",
                             "do","if","static","while"};
    for(i=0; i<32; i++)
    {
        if(!strcmp(lex, keywords[i]))
        {
            flag=1;
            break;
        }
    }
    return flag;
}
int identifier(char lex[])
{
    int flag=0, i=0;
    if(isalpha(lex[0])||lex[0]=='_')
    {
        flag=1;
        for(i=1; i<strlen(lex);i++)
        {
            if((!isalnum(lex[i])) && (lex[i] != '_') && (!isalpha(lex[i])))
            {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}
void insert_id()
{
    char c;
    int flag;
    fp=fopen("output2.txt","r");
    fp2=fopen("output3.txt","w");
    char str[1000];
    while(fgets(str, sizeof str, fp)!=NULL){
        char *p=str;
        char word[sizeof str];
        int n;
        while(sscanf(p, "%s%n", word, &n)==1){
            if(keyword(word))
                fputs(word, fp2);
            else if(identifier(word))
            {
                fputs("id ", fp2);
                fputs(word, fp2);
            }
            else
                fputs(word, fp2);
            fputc(' ',fp2);
            p+=n;
        }
        fputc('\n', fp2);
    }
    fclose(fp);
    fclose(fp2);
    fp2=fopen("output3.txt","r");
    cout<<"\nAfter Adding ID, Output:"<<endl;
    while((c=fgetc(fp2))!=EOF)
        printf("%c",c);
    fclose(fp2);
}
int main(void)
{
    addLineNumber();
    comment_whitespace_remove();
    lexeme_separate();
    insert_id();
    parentheses_check();
    condition_check();
    return 0;
}
