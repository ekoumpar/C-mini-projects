#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 20
#define TRUE 1
#define FALSE 0


void open(FILE **fp, char *s);  //opens an existing or a new file

void correctname(char *s); //makes a valid filename

void removechar(char *s); //removes character "\0" from a string

void realread(FILE **fp); //prints properly filenames from "names.txt"

void print(FILE **fp);//prints a string from file

void deletes(FILE **fp, char *s); //marks a deleted file

void count(FILE **fp, int *m, int *n); //counts the number of raws and columns of a matrix

int main() {
    char name[SIZE],name1[SIZE],name2[SIZE];
    char str1[SIZE],str2[SIZE]; // strings for saving filenames

    int choice,d,check;
    int m=0,n=0,k=0,pos=0;
    int m1,n1,m2,n2;
    int pin[SIZE][SIZE];
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    FILE *fp,*fp1;




    while(1) {

        fflush(stdin);
        printf("\n\t\tOPTIONS\n");
        printf("\t1. New matrix\n\t2. Load an existing matrix\n\t3. Show available matrices\n\t4. Delete a matrix\n\t5. Vector operations \n\t6. Matrix operations\n\t7. Exit\n");
        printf("\nPlease select by typing the number of an option:  ");
        scanf("%d", &choice);
        printf("\n");
        switch(choice)
        {
            case 1:
                // creation new string from user
                fflush(stdin);
                printf("Name of the matrix:  ");
                fgets( name, sizeof(name), stdin);
                //writes filename on file "names.txt"
                open(&fp1,"names.txt");
                fseek(fp1,0,SEEK_END);
                fprintf(fp1,"%s",name);
                //creating a valid string
                correctname(name);
                open(&fp,name);
                label:
                printf("Number of dimensions:  ");
                scanf("%d", &choice);
                if(choice==1)
                {
                    printf("Length of the vector:  ");
                    scanf("%d", &m);
                }
                else if(choice==2)
                {
                    printf("Number of raws:  ");
                    scanf("%d", &m);
                    printf("Number of culomns:  ");
                    scanf("%d", &n);
                }
                else if(choice>2)
                {
                    printf("More than 2 dimensions are not available!!\n");
                    goto label;
                }
                printf("\n\t1. Values from user\n\t2.Random values\n");
                printf("\nChoose an option by typing the number of it:  ");
                scanf("%d", &choice);
                switch(choice)
                {
                    case 1:
                        for(int i=0; i<m; i++)
                        {
                            if(n==0)
                            {
                                printf("Give the value of element %d: ", i+1);
                                scanf("%d", &pin[i][0]);
                                fprintf(fp,"%5d* ",pin[i][0]);
                            }
                            else
                            {
                                for(int j=0; j<n; j++)
                                {
                                    printf("Give a value of element %d,%d: ", i+1, j+1);
                                    scanf("%d", &pin[i][j]);
                                    fprintf(fp,"%5d* ",pin[i][j]);
                                }
                            }
                            fprintf(fp,"\n");

                        }
                        printf("\n\n--------------------------------------------------\n\n");
                        continue;
                    case 2:
                        //initializing with random values
                        srand(time(NULL));
                        for(int i=0; i<m; i++)
                        {
                            if(n==0)
                            {
                                pin[i][0]= rand()%100;
                                fprintf(fp,"%5d* ",pin[i][0]);
                            }
                            else
                            {
                                for(int j=0; j<n; j++)
                                {
                                    pin[i][j]=rand()%100;
                                    fprintf(fp,"%5d* ",pin[i][j]);
                                }
                            }
                            fprintf(fp,"\n");
                        }
                        _fcloseall();
                        printf("\n\n--------------------------------------------------\n\n");
                        continue;
                }
            case 2:
                open(&fp,name);
                rewind(fp);
                print(&fp);
                _fcloseall();
                printf("\n\n--------------------------------------------------\n\n");
                continue;

            case 3:
                open(&fp1,"names.txt");
                realread(&fp1);
                printf("Write the name of the matrix you want to see:  ");
                fflush(stdin);
                fgets(name, sizeof(name), stdin);
                correctname(name);
                open(&fp,name);
                rewind(fp);
                print(&fp);
                _fcloseall();
                printf("\n\n--------------------------------------------------\n\n");
                continue;

            case 4:
                open(&fp1,"names.txt");
                realread(&fp1);
                printf("Write the name of the matrix you want to delete:  ");
                fflush(stdin);
                fgets(name, sizeof(name), stdin);
                deletes(&fp1,name);
                correctname(name);
                check=remove(name);
                if(check==0)
                    printf("\nFile has been deleted\n");
                else printf("\nError by deleting the file\n");
                fclose(fp1);
                printf("\n\n--------------------------------------------------\n\n");
                continue;



            case 5:
                open(&fp1,"names.txt");
                realread(&fp1);
                fclose(fp1);
                printf("Write the name of the vectors to operate \n");
                do
                {
                    fflush(stdin);
                    printf("Vector 1:  ");
                    fgets(name1, sizeof(name1), stdin);
                    strcpy(str1,name1);
                    (str1)[strcspn(str1, "\n")]='\0';
                    correctname(name1);
                    open(&fp,name1);
                    count(&fp,&m1,&n1);
                    print(&fp);
                    rewind(fp);
                    //Reading string from file
                     for(int i=0; i<m1; i++)
                    {

                        for(int j=0; j<n1; j++)
                        {
                            fseek(fp,pos,SEEK_SET);
                            fscanf(fp,"%d",&d);
                            k=ftell(fp);
                            A[i][j]=d;
                            pos=k+2;
                        }
                    }
                    if(m1!=1 && n1!=1)
                        printf("The matrix you chose is not a vector!!\n");
                    pos=k=0;

                }while(m1!=1 && n1!=1);
                do
                {
                    printf("Vector 2:  ");
                    fflush(stdin);
                    fgets(name2, sizeof(name2), stdin);
                    strcpy(str2,name2);
                    (str2)[strcspn(str2, "\n")]='\0';
                    correctname(name2);
                    open(&fp1,name2);
                    count(&fp1,&m2,&n2);
                    print(&fp1);
                    rewind(fp1);
                    for(int i=0; i<m2; i++)
                    {

                        for(int j=0; j<n2; j++)
                        {
                            fseek(fp1,pos,SEEK_SET);
                            fscanf(fp1,"%d",&d);
                            k=ftell(fp1);
                            B[i][j]=d;
                            pos=k+2;
                        }
                    }
                    if(m2!=1 && n2!=1)
                        printf("The matrix you chose is not a vector!\n");
                    pos=k=0;
                }while(m2!=1 && n2!=1);
                _fcloseall();
                printf("Operations\n\t1. Addition\n\t2. Multiplication\n\t3. Transposition\n");
                printf("Choose an operation by typing the number of it:  ");
                scanf("%d", &choice);
                switch(choice)
                {
                    case 1:
                        if(m1!=m2 || n1!=n2)
                        {
                            printf("\nAddition between vectors of different dimension is not allowed !!\n\n");
                            _fcloseall();
                            printf("\n\n--------------------------------------------------\n\n");
                            continue;
                        }
                        m=m1;
                        n=n1;
                        //Changes the name into "str1+str2"
                        strcat(str1,"+");
                        strcat(str1,str2);
                        open(&fp1,"names.txt");
                        fseek(fp1,0,SEEK_END);
                        fprintf(fp1,"%s\n",str1);
                        correctname(str1);
                        open(&fp,str1);
                        //Addition
                        for(int i=0; i<m; i++)
                        {
                            for(int j=0; j<n; j++)
                            {
                                C[i][j] = A[i][j]+B[i][j];
                                fprintf(fp,"%5d* ", C[i][j]);
                            }
                            fprintf(fp,"\n");

                        }
                        printf("\tMatrix C: \n\n");
                        rewind(fp);
                        print(&fp);
                        _fcloseall();
                        printf("\n\n--------------------------------------------------\n\n");
                        continue;
                    case 2:
                        if(n1!=m2)
                        {
                            printf("\nThis operation is not allowed!\n");
                            _fcloseall();
                            printf("\n\n--------------------------------------------------\n\n");
                            continue;
                        }
                        strcat(str1,"x");
                        strcat(str1,str2);
                        open(&fp1,"names.txt");
                        fseek(fp1,0,SEEK_END);
                        fprintf(fp1,"%s\n",str1);
                        correctname(str1);
                        open(&fp,str1);
                        //Multiplication
                        for(int i=0; i<m1; i++)
                        {
                            for(int j=0; j<n2; j++)
                            {
                                C[i][j]=0;
                                for(int k=0; k<n1; k++)
                                {
                                    C[i][j] += A[i][k] * B[k][j];

                                }

                            fprintf(fp,"%5d* ", C[i][j]);
                            }
                            fprintf(fp,"\n");
                        }
                        printf("\Vector C: \n\n");
                        rewind(fp);
                        print(&fp);
                        _fcloseall();
                        printf("\n\n--------------------------------------------------\n\n");
                        continue;
                    case 3:
                        printf("Choose which one you want: 1 or 2\n");
                        scanf("%d",&d);
                        if(d==1)
                        {
                            strcat(str1,"T");
                            open(&fp1,"names.txt");
                            fseek(fp1,0,SEEK_END);
                            fprintf(fp1,"%s\n",str1);
                            correctname(str1);
                            open(&fp,str1);
                            //Transposition
                            for(int i=0; i<n1; i++)
                            {
                                for(int j=0; j<m1; j++)
                                {
                                    C[i][j]=A[j][i];
                                    fprintf(fp,"%5d* ", C[i][j]);
                                }
                                fprintf(fp,"\n");
                            }
                        }
                        else if(d==2)
                        {
                            strcat(str2,"T");
                            open(&fp1,"names.txt");
                            fseek(fp1,0,SEEK_END);
                            fprintf(fp1,"%s\n",str2);
                            correctname(str2);
                            open(&fp,str2);
                            for(int i=0; i<n2; i++)
                            {
                                for(int j=0; j<m2; j++)
                                {
                                    C[i][j]=B[j][i];
                                    fprintf(fp,"%5d* ", C[i][j]);
                                }
                                fprintf(fp,"\n");
                            }
                        }
                        printf("\tVector C: \n\n");
                        rewind(fp);
                        print(&fp);
                        _fcloseall();
                printf("\n\n--------------------------------------------------\n\n");
                continue;
                }





            case 6:
                open(&fp1,"names.txt");
                realread(&fp1);
                fclose(fp1);
                printf("Write the names of the matrices to operate\n");
                pos=k=0;
                fflush(stdin);
                printf("Matrix A:  ");
                fgets(name1, sizeof(name1), stdin);
                strcpy(str1,name1);
                (str1)[strcspn(str1, "\n")]='\0';
                correctname(name1);
                open(&fp,name1);
                count(&fp,&m1,&n1);
                print(&fp);
                printf("\n");
                rewind(fp);
                for(int i=0; i<m1; i++)
                {
                    for(int j=0; j<n1; j++)
                    {
                        fseek(fp,pos,SEEK_SET);
                        fscanf(fp,"%d",&d);
                        k=ftell(fp);
                        A[i][j]=d;
                        pos=k+2;
                    }
                }
                pos=k=0;
                printf("Matrix B:  ");
                fflush(stdin);
                fgets(name2, sizeof(name2), stdin);
                strcpy(str2,name2);
                (str2)[strcspn(str2, "\n")]='\0';
                correctname(name2);
                open(&fp1,name2);
                count(&fp1,&m2,&n2);
                print(&fp1);
                printf("\n");
                rewind(fp1);
                pos=k=0;
                for(int i=0; i<m2; i++)
                {
                    for(int j=0; j<n2; j++)
                    {
                        fseek(fp1,pos,SEEK_SET);
                        fscanf(fp1,"%d",&d);
                        k=ftell(fp1);
                        B[i][j]=d;
                        pos=k+2;
                    }
                }
                pos=k=0;
                _fcloseall();
                printf("Operations\n\t1. Addition\n\t2. Multiplication\n\t3. Transposition\n");
                printf("Choose an operation by typing the number of it:  ");
                scanf("%d", &choice);
                switch(choice)
                {
                    case 1:
                        if(m1!=m2 || n1!=n2)
                        {
                            printf("Additon between matrices of different dimension is not allowed!!\n\n");
                            _fcloseall();
                            printf("\n\n--------------------------------------------------\n\n");
                            continue;
                        }
                        m=m1;
                        n=n1;
                        strcat(str1,"+");
                        strcat(str1,str2);
                        open(&fp1,"names.txt");
                        fseek(fp1,0,SEEK_END);
                        fprintf(fp1,"%s\n",str1);
                        correctname(str1);
                        open(&fp,str1);
                        for(int i=0; i<m; i++)
                        {
                            for(int j=0; j<n; j++)
                            {
                                C[i][j] = A[i][j]+B[i][j];
                                fprintf(fp,"%5d* ", C[i][j]);
                            }
                            fprintf(fp,"\n");

                        }
                        printf("\tMatrix C: \n");
                        rewind(fp);
                        print(&fp);
                        _fcloseall();
                        printf("\n\n--------------------------------------------------\n\n");
                        continue;
                    case 2:
                        if(n1!=m2)
                        {
                            printf("This operation is not allowed!");
                            _fcloseall();
                            printf("\n\n--------------------------------------------------\n\n");
                            continue;
                        }
                        strcat(str1,"x");
                        strcat(str1,str2);
                        open(&fp1,"names.txt");
                        fseek(fp1,0,SEEK_END);
                        fprintf(fp1,"%s\n",str1);
                        correctname(str1);
                        open(&fp,str1);
                         for(int i=0; i<m1; i++)
                        {
                            for(int j=0; j<n2; j++)
                            {
                                C[i][j]=0;
                                for(int k=0; k<n1; k++)
                                {
                                    C[i][j] += A[i][k] * B[k][j];

                                }

                            fprintf(fp,"%5d* ", C[i][j]);
                            }
                            fprintf(fp,"\n");
                        }
                        printf("\tMatrix C: \n");
                        rewind(fp);
                        print(&fp);
                        _fcloseall();
                        printf("\n\n--------------------------------------------------\n\n");
                        continue;
                    case 3:
                        printf("Choose which matrix you want: 1 or 2\n");
                        scanf("%d",&d);
                        if(d==1)
                        {
                            strcat(str1,"T");
                            open(&fp1,"names.txt");
                            fseek(fp1,0,SEEK_END);
                            fprintf(fp1,"%s\n",str1);
                            correctname(str1);
                            open(&fp,str1);
                            for(int i=0; i<n1; i++)
                            {
                                for(int j=0; j<m1; j++)
                                {
                                    C[i][j]=A[j][i];
                                    fprintf(fp,"%5d* ", C[i][j]);
                                }
                                fprintf(fp,"\n");
                            }
                        }
                        else if(d==2)
                        {
                            strcat(str2,"T");
                            open(&fp1,"names.txt");
                            fseek(fp1,0,SEEK_END);
                            fprintf(fp1,"%s\n",str2);
                            correctname(str2);
                            open(&fp,str2);
                            for(int i=0; i<n2; i++)
                            {
                                for(int j=0; j<m2; j++)
                                {
                                    C[i][j]=B[j][i];
                                    fprintf(fp,"%5d* ", C[i][j]);
                                }
                                fprintf(fp,"\n");
                            }
                        }
                        printf("\t\tMatrix C: \n\n");
                        rewind(fp);
                        print(&fp);
                        _fcloseall();
                printf("\n\n--------------------------------------------------\n\n");
                continue;
                }

            case 7:
                _fcloseall();
                exit(0);


            default : printf("There is not such option!\n\n");
        }
}

    return 0;


    }

    void open(FILE **fp, char *s)
    {
        /*Parameters
        pointer on an opening file pointer, string of filename
        */
        char c=TRUE;
        (*fp) = fopen(s, "r+");
        //If it does not exist,it is created
        if((*fp)==NULL)
        {
            (*fp)=fopen(s, "w");
            if((*fp)==NULL)
                c=FALSE;
            fclose(*fp);
            (*fp)=fopen(s,"r+");
            if((*fp)==NULL)
                c=FALSE;
        }
        if(c==FALSE)
        {
            printf("Error by opening the file");
            exit(0);
        }
    }
    void correctname(char *s)//string of the name of a matrix
    {

        (s)[strcspn(s, "\n")]='\0';//remove "\n"
        strcat(s, ".txt");//ads suffix ".txt"
        removechar(s);//removes "\0"
    }
    void removechar(char *s)//string of the name of a matrix
    {

    int i, j;
    int len = strlen(s);
    for(i=0; i<len; i++)
    {
        if(s[i] == '\0')
        {
            for(j=i; j<len; j++)
            {
                s[j] = s[j+1];
            }
            len--;
            i--;
        }
    }

  }
  void realread(FILE **fp)//pointer to pointer of a file
  {
      char c='0';
      rewind(*fp);
      do
      {
          //ignores strings that start with symbol "#"
          //prints the rest file
        c=fgetc(*fp);
        while(c!=EOF && c!='#')
        {
            printf("%c",c);
            c=fgetc(*fp);

        }
        while(c!=EOF && c!='\n')
        {
            c=fgetc(*fp);
        }
        }while(c!=EOF);
        printf("\n\n");
  }
  void print(FILE **fp)//pointer to a pointer of a file
  {
      //ignores character "*"
      //prints the rest file
      int c;
      rewind(*fp);
      while(!feof(*fp))
      {
          c=fgetc(*fp);
          if(c!='*')
            printf("%c",c);
      }


}

  void deletes(FILE **fp, char *s)
  {
      /*Parameters
        pointer on an opening file pointer, string of filename
        */
      int len, i=0, check=0;
      char c='0';
      char p='#';
      len=strlen(s);
      rewind(*fp);
      while(c!=EOF)
      {
          c=fgetc(*fp);
          //if only all following characters are equal
          if(c==s[i])
          {
              i++;
              check++;
              if(check==len)//detects the string
              {
                fseek(*fp,(-len-1),SEEK_CUR);
                fputc(p,(*fp));//prints the start of a string
                break;
                }

          }
          //if all characters are not equal initializes counting on zero
          else if(c!=s[i])
            {
                check=0;
                i=0;
            }
      }

  }
  void count(FILE **fp, int *m, int *n)
  {
      /*Parameters:
      pointer to pointer of a file,
      pointer to the number of raws ,
      pointer to the number of culomns */
      char c='0';
      (*m)=0;
      (*n)=0;
      while(c!=EOF)
      {
          c=getc(*fp);
          if(c=='\n')//each character "\n" represents each line
            (*m)++;
          else if(c=='*' && (*m)==0 )//each character "*" represents each column
            (*n)++;


      }

  }





