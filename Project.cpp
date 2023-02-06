#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define N 1000000

typedef struct table table;

struct table
{
    int id;
    char name[100], iT[100], dT[100], sc[100], val[100];
} tabVal[100];

char check[100], cur[100], dType[100][50], scope[100][50];
int cnt, iType, topD, topS, elseCnt, lineNum;
 int isKeyword(char buffer[]);
//void srcCode();
void step1();
void step2();
void step3();
void step4();
void finalPrint();




void stepOne();
void stepTwo();

void tabInsert();
void tabSearch();
void scopeVal();

int main(void)
{
    //  srcCode();
    step1();
    step2();
    step3();
    step4();
    finalPrint();

    return 0;
}

void srcCode()
{
    int cnt = 0;
    char ch[N];
    FILE *codeFile, *finOut, *header, *key;
    codeFile = fopen("input.c", "w");
    finOut = fopen("180104138.txt", "w");
    header = fopen("header.txt", "w");
    key = fopen("key.txt", "w");

    fprintf(finOut, "Source code with line number:\n");
    while(gets(ch))
    {
        if(!strcmp(ch, "Compile"))
            break;
        ++cnt;
        fprintf(finOut, "%d %s\n", cnt, ch);
        fprintf(codeFile, "%s\n", ch);
    }
    fprintf(finOut, "\n\nErrors:\n");
    fclose(codeFile);
    fclose(finOut);
    fclose(header);
    fclose(key);
}

void step1()
{
    FILE *fp1,*fp2;
    char c,f,h,s,d,e;
    int count =0;

    fp1 = fopen("input.c","r");
    fp2 = fopen("step1.txt","w");

    if(!fp1)
    {
        printf("File not found!");
    }
    else
    {
        while((c = fgetc(fp1)) != EOF)
        {
            if(c == '/')
            {
                //Single comment
                f = fgetc(fp1);
                if(f  == '/')
                {
                    while((h = fgetc(fp1)) != '\n');

                }
                //Multiline comment
                else if(f == '*')
                {
                    while((d = fgetc(fp1)) != '/');
                }

            }
            else
            {
                //int main and printf handling
                if(c == ' ')
                {
                    e = fgetc(fp1);

                    if(e != '\0' && e != '(')
                    {
                        fputc(c,fp2);

                    }
                    fputc(e,fp2);

                }
                //Space after every new line
                if(c == '\n')
                {
                    fputc(' ',fp2);
                }
                //whitespace, newline,tabs,carriage return removal
                if((c != ' ') && (c != '\n') && (c != '\t') && (c != '\r'))
                {
                    fputc(c,fp2);
                }

            }


        }
    }

    fclose(fp1);
    fclose(fp2);

    fp2 = fopen("step1.txt","r");
    while((c = fgetc(fp2)) != EOF)
    {
        printf("%c",c);

    }

    fclose(fp2);
}

void step2()
{
{

 int isKeyword(char buffer[]);

    {
        if(strcmp(buffer,"auto")!=1||strcmp(buffer,"break")!=1||strcmp(buffer,"case")!=1
                ||strcmp(buffer,"char")!=1||strcmp(buffer,"const")!=1||strcmp(buffer,"continue")!=1
                ||strcmp(buffer,"default")!=1||strcmp(buffer,"do")!=1||strcmp(buffer,"double")!=1
                ||strcmp(buffer,"else")!=1||strcmp(buffer,"enum")!=1||strcmp(buffer,"extern")!=1
                ||strcmp(buffer,"float")!=1||strcmp(buffer,"for")!=1||strcmp(buffer,"goto")!=1
                ||strcmp(buffer,"if")!=1||strcmp(buffer,"int")!=1||strcmp(buffer,"long")!=1
                ||strcmp(buffer,"register")!=1||strcmp(buffer,"return")!=1||strcmp(buffer,"short")!=1
                ||strcmp(buffer,"signed")!=1||strcmp(buffer,"sizeof")!=1||strcmp(buffer,"static")!=1
                ||strcmp(buffer,"struct")!=1||strcmp(buffer,"switch")!=1||strcmp(buffer,"typedef")!=1
                ||strcmp(buffer,"union")!=1||strcmp(buffer,"unsigned")!=1||strcmp(buffer,"void")!=1
                ||strcmp(buffer,"volatile")!=1||strcmp(buffer,"while")!=1);
            return 1;
        return 0;
    }

    int isInteger(char* ch)
    {
        if(strlen(ch)==0)
            return 0;
        for(int i=0; i<strlen(ch); i++)
        {
            if(ch[i]!='0' && ch[i]!='1' && ch[i]!='2'
                    && ch[i]!='3' && ch[i]!='4' && ch[i]!='5'
                    && ch[i]!='6' && ch[i]!='7' && ch[i]!='8'
                    && ch[i]!='9' || (ch[i]!='-' && i>0))
                return 0;
        }
        return 1;
    }

    int isFloat(char buffer[])
    {
        int flag=0;
        for(int i=0; i<strlen(buffer); i++)
        {
            if(buffer[i]!='0' && buffer[i]!='1' && buffer[i]!='2'
                    && buffer[i]!='3' && buffer[i]!='4' && buffer[i]!='5'
                    && buffer[i]!='6' && buffer[i]!='7' && buffer[i]!='8'
                    && buffer[i]!='9' && buffer[i]!='.' || (buffer[i]!='-' && i>0))
                return 0;
            if(buffer[i]=='.')
                flag=1;
        }
        return flag;
    }

    int isIdentifier(char* ch)
    {
        if(ch[0]=='0'||ch[0]=='1'||ch[0]=='2'
                ||ch[0]=='3'||ch[0]=='4'||ch[0]=='5'
                ||ch[0]=='6'||ch[0]=='7'||ch[0]=='8'
                ||ch[0]=='9')
            return 0;
        return 1;
    }

    int isOperator(char ch)
    {
        if(ch=='+'||ch=='-'||ch=='*'
                ||ch=='/'||ch=='%'||ch=='='
                ||ch=='<'||ch=='>')
            return 1;
        return 0;
    }

    int isParenthesis(char ch)
    {
        if(ch=='{'||ch=='('||ch=='['||
                ch=='}'||ch==')'||ch==']')
            return 1;
        return 0;
    }

    char ch, buffer[20], quotation[]="''";
    FILE *p1, *p2;
    int i, j=0, k=0;

    p1= fopen("step1.txt","r");
    p2= fopen("step2.txt","w");

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        while((ch=fgetc(p1))!=EOF)
        {
            if(isalnum(ch))
                buffer[j++]=ch;
            else if(ch=='_'||ch=='.')
                buffer[j++]=ch;
            if((ch==' '||ch==','||ch=='('||ch==')'
                    ||ch=='='||ch=='+'||ch=='-'||ch=='*'
                    ||ch=='<'||ch=='>'||ch=='\n'||ch==';'
                    ||ch==quotation[0]||ch=='/') && (j!=0))
            {
                buffer[j]='\0';
                j=0;

                if(isKeyword(buffer)==1)
                {
                    printf("[kw %s] ", buffer);
                    fprintf(p2,"[kw ");
                    for(i=0; i<strlen(buffer); i++)
                    {
                        fprintf(p2,"%s", buffer);
                        break;
                    }
                    fprintf(p2,"] ");
                }
                else
                {
                    if(isFloat(buffer)==1)
                    {
                        printf("[num %s] ", buffer);
                        fprintf(p2,"[num ");
                        for(i=0; i<strlen(buffer); i++)
                        {
                            fprintf(p2,"%s", buffer);
                            break;
                        }
                        fprintf(p2,"] ");
                    }
                    else if(isInteger(buffer)==1)
                    {
                        printf("[num %s] ", buffer);
                        fprintf(p2,"[num ");
                        for(i=0; i<strlen(buffer); i++)
                        {
                            fprintf(p2,"%s", buffer);
                            break;
                        }
                        fprintf(p2,"] ");
                    }
                    else if(isIdentifier(buffer)==1)
                    {
                        printf("[id %s] ", buffer);
                        fprintf(p2,"[id ");
                        for(i=0; i<strlen(buffer); i++)
                        {
                            fprintf(p2,"%s",buffer);
                            break;
                        }
                        fprintf(p2,"] ");
                    }
                    else
                    {
                        printf("[unkn %s] ", buffer);
                        fprintf(p2,"[unkn ");
                        for(i=0; i<strlen(buffer); i++)
                        {
                            fprintf(p2,"%s", buffer);
                            break;
                        }
                        fprintf(p2,"] ");
                    }
                }
            }
            for(k=0; k<6; ++k)
            {
                if(isParenthesis(ch)==1)
                {
                    printf("[par %c] ",ch);
                    fprintf(p2,"[par %c] ",ch);
                    break;
                }
            }
            for(i=0; i<8; i++)
            {
                if(isOperator(ch)==1)
                {
                    printf("[op %c] ",ch);
                    fprintf(p2,"[op %c] ",ch);
                    break;
                }
            }
            if(ch==';'||ch==','||ch==quotation[0])
            {
                printf("[sep %c] ",ch);
                fprintf(p2,"[sep %c] ",ch);
            }
        }
        fclose(p1);
        fclose(p2);
    }
}
}
void step3()
{
    {
        struct node
        {
            char name[1000], type[1000], dtype[1000], scope[1000];
            int del;
        };
        node store[1000];

        char scope1[1000];
        char str[10000];
        char all[1000][1000];
        int allrow = 1, rowNum = 1;

        void identifierSep()
        {
            FILE *p1, *p2;
            p1=fopen("step2.txt","r");
            p2=fopen("step3.txt","w");
            char ch;
            int cnt=0;
            while((ch=fgetc(p1)) !=EOF)
            {
                if(ch=='[')
                {
                    fputc(ch, p2);
                    str[cnt++]=ch;
                    char tmp[1000];
                    int indx = 0;
                    while((ch=fgetc(p1))!=EOF)
                    {
                        if(ch==' ')
                        {
                            tmp[indx] = '\0';
                            if(strcmp(tmp,"id")==0)
                            {
                                fputc('i', p2);
                                fputc('d', p2);
                                fputc(' ', p2);
                                str[cnt++] = 'i';
                                str[cnt++] = 'd';
                                str[cnt++] = ' ';
                            }
                            break;
                        }
                        else
                        {
                            tmp[indx++] = ch;
                        }
                    }
                    while((ch = fgetc(p1)) != EOF)
                    {
                        if(ch==' ')
                        {
                            break;
                        }
                        fputc(ch, p2);
                        str[cnt++] = ch;
                    }
                }
            }
            str[cnt] = '\0';
            fclose(p1);
            fclose(p2);
        }

        void storeAll()
        {
            int len = strlen(str);
            int i = 0;
            while(i<len)
            {
                if(str[i]=='[')
                {
                    char tmp[1000];
                    int indx = 0;
                    i++;
                    while(str[i] != ']')
                    {
                        tmp[indx++] = str[i++];
                    }
                    tmp[indx] = '\0';
                    strcpy(all[allrow++], tmp);
                }
                i++;
            }
        }

        bool dataType(char *s)
        {
            return ((!strcmp(s, "int")) || (!strcmp(s, "float")) || (!strcmp(s, "long")) || (!strcmp(s, "long long")) || (!strcmp(s, "double")) || (!strcmp(s, "char")));
        }
        char scopeDet[1000][1000];
        void scopeDetect()
        {
            int i=0;
            char sc[1000];
            strcpy(sc, "global");
            while(i<allrow)
            {
                char temp[100];
                strcpy(temp, all[i]);
                if(dataType(temp))
                {
                    i++;
                    char temp2[100];
                    strcpy(temp2, all[i]);
                    char temp4[100];
                    int indx1=0;
                    int j=3;
                    while(temp2[j]!='\0')
                    {
                        temp4[indx1++]= temp2[j++];
                    }
                    temp4[indx1] = '\0';
                    i++;
                    char temp3[100];
                    strcpy(temp3, all[i]);
                    if(strcmp(temp3, "(")==0)
                    {
                        strcpy(scopeDet[i-1], "global");
                        strcpy(sc, temp4);
                    }
                    else
                    {
                        strcpy(scopeDet[i-1],sc);
                    }
                }
                else if (strlen(temp)>2 && temp[0]=='i' && temp[1]=='d')
                {
                    strcpy(scopeDet[i], sc);
                }
                i++;
            }
        }

        void symbolTableGenerate()
        {
            int i = 1;
            while (i < allrow)
            {
                char temp[100];
                strcpy(temp, all[i]);
                if(strlen(temp)>2 && temp[0]=='i' && temp[1]=='d')
                {
                    char name2[100];
                    int j = 3, indx2=0;
                    while(temp[j]!='\0')
                    {
                        name2[indx2++] = temp[j++];
                    }
                    name2[indx2] = '\0';
                    bool found = 0;
                    for(int in=1; in<rowNum; ++in)
                    {
                        if(strcmp(store[in].name, name2)==0 && strcmp(store[in].scope, scopeDet[i])==0)
                        {
                            found = 1;
                            break;
                        }
                    }
                    if(!found)
                    {
                        strcpy(store[rowNum].name, name2);
                        strcpy(store[rowNum].scope, scopeDet[i]);
                        store[rowNum].del=0;
                        char dt[100];
                        strcpy(dt, all[i-1]);
                        if(dataType(dt))
                        {
                            strcpy(store[rowNum].dtype, dt);
                        }
                        else
                        {
                            char ty[100];
                            bool found = 0;
                            for (int in = rowNum-1; in>=1; --in)
                            {
                                if(strcmp(store[in].name, name2)==0)
                                {
                                    found = 1;
                                    strcpy(ty, store[in].dtype);
                                    break;
                                }
                            }
                            if(found)
                            {
                                strcpy(store[rowNum].dtype, ty);
                            }
                        }
                        i++;
                        if(strcmp(all[i], "("))
                        {
                            strcpy(store[rowNum].type, "var");
                        }
                        else
                        {
                            strcpy(store[rowNum].type, "func");
                        }
                        rowNum++;
                    }
                }
                i++;
            }
        }

        void insert()
        {
            char name1[100], type1[100], dtype1[100], scope1[100];
            printf("Name: ");
            scanf("%s", &name1);
            printf("Type: ");
            scanf("%s",&type1);
            printf("Data Type: ");
            scanf("%s", &dtype1);
            printf("Scope: ");
            scanf("%s",&scope1);
            strcpy(store[rowNum].name, name1);
            strcpy(store[rowNum].type, type1);
            strcpy(store[rowNum].dtype, dtype1);
            strcpy(store[rowNum].scope, scope1);
            store[rowNum].del = 0;
            rowNum++;
        }

        void remove()
        {
            int de;
            printf("Enter Row Number: ");
            scanf("%d",&de);
            int org=1;
            for(int i=0; i<rowNum; ++i)
            {
                if(store[i].del==1)
                    continue;
                if(org == de)
                {
                    store[i].del=1;
                    break;
                }
                org++;
            }
        }
        void display()
        {
            int org=1;
            printf("---------------------------------------------------------------------------------------\n");
            printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\n");
            for (int i=1; i<rowNum; ++i)
            {
                if(store[i].del==1)
                    continue;
                printf("---------------------------------------------------------------------------------------\n");
                printf("%10d\t|",org);
                printf("%10s\t|",store[i].name);
                printf("%10s\t|",store[i].type);
                printf("%10s\t|",store[i].dtype);
                printf("%10s\n",store[i].scope);
                org++;
            }
            printf("---------------------------------------------------------------------------------------");


        }
        strcpy(scope1, "global");
        identifierSep();
        storeAll();
        scopeDetect();
        symbolTableGenerate();
        while (true)
        {
            printf("1.Insert\n2.Delete\n3.Display\n4.Exit\n");
            printf("Select Operation: ");
            int op;
            scanf("%d", &op);
            if(op==1)
                insert(), printf("\n");
            else if(op==2)
                remove(), printf("\n");
            else if(op==3)
                display(), printf("\n");
            else if(op==4)
                break;
            else
                printf("Invalid Option");
        }

        void step4()
        {
            {
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
                            else
                            {
                                fputc(' ',fp2);
                                fputc(d, fp2);
                                if((!isalnum(d)) && (d!=' ') && (d!='_') && (d!='.'))
                                {
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
                    char keywords[32][20]= {"auto","double","int","struct",
                                            "break","else","long","switch",
                                            "case","enum","register","typedef",
                                            "char","extern","return","union",
                                            "const","float","short","unsigned",
                                            "continue","for","signed","void",
                                            "default","goto","sizeof","volatile",
                                            "do","if","static","while"
                                           };
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
                        for(i=1; i<strlen(lex); i++)
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
                    while(fgets(str, sizeof str, fp)!=NULL)
                    {
                        char *p=str;
                        char word[sizeof str];
                        int n;
                        while(sscanf(p, "%s%n", word, &n)==1)
                        {
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
                addLineNumber();
                comment_whitespace_remove();
                lexeme_separate();
                insert_id();
                parentheses_check();
                condition_check();
            }

            int main()
            {

                step1();
                step2();
                step3();
                step4();

                return 0;

            }
