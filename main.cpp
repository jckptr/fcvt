



#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char * argv[])
{
    
    int expdtab = 0;
    int term = 'w';


    if (argc < 2)
    {
        printf("no argument\n");
        return 0;
    }

    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'w')
                term = 'w';
            else if (argv[i][1] == 'u')
                term = 'u';
            else if (argv[i][1] == 'm')
                term = 'm';

            if (argv[i][1] == 'e')
                expdtab = 1;
        }
    }


    char * fname = argv[argc - 1];

    if (strlen(fname) > 240)
    {
        printf("Filename too long\n");
        return 0;
    }

    char  newfn[256] = "__old__\0";

    strcat(newfn, fname);


    printf("src file: %s\n", fname);
    printf("src file duplicated into: %s\n", newfn);

/*
    char fname[] = "test.txt";
    char newfn[] = "test_modi.txt";
*/


    FILE *fp;
    FILE *nfp;
    char c;

    fp = fopen(fname, "rb");
    nfp = fopen(newfn, "wb");

    if (fp == NULL || nfp == NULL)
    {
        if (fp != NULL)
            fclose(fp);
        if (nfp != NULL)
            fclose(nfp);
    
        printf("File open failed\n");
        return 0;
    }



    // File duplicated
    while ((c = fgetc(fp)) != EOF)
    {
        fputc(c, nfp);
    }

    fclose(fp);
    fclose(nfp);




    // File write back and apply format translate
    fp = fopen(newfn, "rb");
    if (fp == NULL)
    {
        printf("File open failed\n");
        return 0;
    }

    nfp = fopen(fname, "wb");

    if (nfp == NULL)
    {
        fclose(fp);

        printf("File open failed\n");
        printf("Source file may be modified inappropriate.\n");
        printf("If it be, Try to recover data from file: %s\n", newfn);
        return 0;
    }


    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\t')
        {
            if (expdtab) 
            {
                fputc(' ', nfp);
                fputc(' ', nfp);
                fputc(' ', nfp);
                fputc(' ', nfp);
            }
            else
            {
                fputc('\t', nfp);
            }
        }
        else if (c == '\n' || c == '\r')
        {
            if (c == '\r')
            {
                char n = fgetc(fp);
                if (n != '\n')
                {
                    fseek(fp, -1, SEEK_CUR);
                }
            }

            if (term == 'w')
            {
                fputc('\r', nfp);
                fputc('\n', nfp);
            }
            else if (term == 'u')
            {
                
                fputc('\n', nfp);
            }
            else if (term == 'm')
            {
                fputc('\r', nfp);
            }
            else
            {
                fputc(c, nfp);
            }
        }
        else 
        {
            fputc(c, nfp);
        }
    }


    fclose(fp);
    fclose(nfp);

    printf("completed\n");

    return 0;
}