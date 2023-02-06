#include<stdio.h>
#include<ctype.h>
#include<string.h>

struct node{
    char name[1000], type[1000], dtype[1000], scope[1000];
    int del;
};
node store[1000];

char scope1[1000];
char str[10000];
char all[1000][1000];
int allrow = 1, rowNum = 1;

void identifierSep(){
    FILE *p1, *p2;
    p1=fopen("output2.txt","r");
    p2=fopen("output3.txt","w");
    char ch;
    int cnt=0;
    while((ch=fgetc(p1)) !=EOF){
        if(ch=='['){
            fputc(ch, p2);
            str[cnt++]=ch;
            char tmp[1000];
            int indx = 0;
            while((ch=fgetc(p1))!=EOF){
                if(ch==' '){
                    tmp[indx] = '\0';
                    if(strcmp(tmp,"id")==0){
                        fputc('i', p2);
                        fputc('d', p2);
                        fputc(' ', p2);
                        str[cnt++] = 'i';
                        str[cnt++] = 'd';
                        str[cnt++] = ' ';
                    }
                    break;
                }
                else{
                    tmp[indx++] = ch;
                }
            }
            while((ch = fgetc(p1)) != EOF){
                if(ch==' '){
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

void storeAll(){
    int len = strlen(str);
    int i = 0;
    while(i<len){
        if(str[i]=='['){
            char tmp[1000];
            int indx = 0;
            i++;
            while(str[i] != ']'){
                tmp[indx++] = str[i++];
            }
            tmp[indx] = '\0';
            strcpy(all[allrow++], tmp);
        }
        i++;
    }
}

bool dataType(char *s){
    return ((!strcmp(s, "int")) || (!strcmp(s, "float")) || (!strcmp(s, "long")) || (!strcmp(s, "long long")) || (!strcmp(s, "double")) || (!strcmp(s, "char")));
}
char scopeDet[1000][1000];
void scopeDetect(){
    int i=0;
    char sc[1000];
    strcpy(sc, "global");
    while(i<allrow){
        char temp[100];
        strcpy(temp, all[i]);
        if(dataType(temp)){
            i++;
            char temp2[100];
            strcpy(temp2, all[i]);
            char temp4[100];
            int indx1=0;
            int j=3;
            while(temp2[j]!='\0'){
                temp4[indx1++]= temp2[j++];
            }
            temp4[indx1] = '\0';
            i++;
            char temp3[100];
            strcpy(temp3, all[i]);
            if(strcmp(temp3, "(")==0){
                strcpy(scopeDet[i-1], "global");
                strcpy(sc, temp4);
            } else{
                strcpy(scopeDet[i-1],sc);
            }
        } else if (strlen(temp)>2 && temp[0]=='i' && temp[1]=='d'){
            strcpy(scopeDet[i], sc);
        }
        i++;
    }
}

void symbolTableGenerate(){
    int i = 1;
    while (i < allrow)
    {
        char temp[100];
        strcpy(temp, all[i]);
        if(strlen(temp)>2 && temp[0]=='i' && temp[1]=='d'){
            char name2[100];
            int j = 3, indx2=0;
            while(temp[j]!='\0'){
                name2[indx2++] = temp[j++];
            }
            name2[indx2] = '\0';
            bool found = 0;
            for(int in=1;in<rowNum;++in){
                if(strcmp(store[in].name, name2)==0 && strcmp(store[in].scope, scopeDet[i])==0){
                    found = 1;
                    break;
                }
            }
            if(!found){
                strcpy(store[rowNum].name, name2);
                strcpy(store[rowNum].scope, scopeDet[i]);
                store[rowNum].del=0;
                char dt[100];
                strcpy(dt, all[i-1]);
                if(dataType(dt)){
                    strcpy(store[rowNum].dtype, dt);
                } else{
                    char ty[100];
                    bool found = 0;
                    for (int in = rowNum-1; in>=1; --in){
                        if(strcmp(store[in].name, name2)==0){
                            found = 1;
                            strcpy(ty, store[in].dtype);
                            break;
                        }
                    }
                    if(found){
                        strcpy(store[rowNum].dtype, ty);
                    }
                }
                i++;
                if(strcmp(all[i], "(")){
                    strcpy(store[rowNum].type, "var");
                } else{
                    strcpy(store[rowNum].type, "func");
                }
                rowNum++;
            }
        }
        i++;
    }
}

void insert(){
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

void remove(){
    int de;
    printf("Enter Row Number: ");
    scanf("%d",&de);
    int org=1;
    for(int i=0; i<rowNum; ++i){
        if(store[i].del==1) continue;
        if(org == de){
            store[i].del=1;
            break;
        }
        org++;
    }
}
void display(){
    int org=1;
    printf("---------------------------------------------------------------------------------------\n");
    printf("SI No.\t\t|Name\t\t|Type\t\t|Data Type\t|Scope\n");
    for (int i=1; i<rowNum; ++i){
        if(store[i].del==1) continue;
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
int main(){
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
        if(op==1) insert(), printf("\n");
        else if(op==2) remove(), printf("\n");
        else if(op==3) display(), printf("\n");
        else if(op==4) break;
        else printf("Invalid Option");
    }
    return 0;
}
