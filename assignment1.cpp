#include<stdio.h>
#include<string.h>

int main(void)
{

    FILE *fp1,*fp2;
    char c,f,h,s,d,e;
    int count =0;

    fp1 = fopen("input.c","r");
    fp2 = fopen("output1.txt","w");

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

    fp2 = fopen("output1.txt","r");
    while((c = fgetc(fp2)) != EOF)
    {
        printf("%c",c);

    }

    fclose(fp2);
    return 0;
}


