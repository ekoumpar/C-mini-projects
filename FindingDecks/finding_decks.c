#include <stdio.h>
#include <string.h>
#define SIZE 100
/* given the cards of each deck and the number of them this project computes
 how many completed decks we can make and which cards are left out
*/
int main(void)
{
    char s[SIZE];//string used for the input of user
    char const card[][7]={"'A-0'", "'A-1'", "'A-2'", "'A-3'", "'K-0'", "'K-1'", "'K-2'", "'K-3'", "'Q-0'", "'Q-1'", "'Q-2'", "'Q-3'", "'J-0'", "'J-1'", "'J-2'", "'J-3'", "'10-0'",
    "'10-1'","'10-2'", "'10-3'", "'9-0'", "'9-1'", "'9-2'", "'9-3'", "'8-0'", "'8-1'", "'8-2'", "'8-3'", "'7-0'", "'7-1'", "'7-2'", "'7-3'", "'6-0'", "'6-1'", "'6-2'", "'6-3'",
"'5-0'", "'5-1'", "'5-2'", "'5-3'", "'4-0'", "'4-1'", "'4-2'", "'4-3'", "'3-0'", "'3-1'", "'3-2'", "'3-3'", "'2-0'", "'2-1'", "'2-2'", "'2-3'"};
    //initialization of the deck
    int size[7],decks=0,i=0;
    // size of each deck,number of decks,counting variable;
    int number[52]={0},min,n;
    //vector that counts the number of existing cards,least shown card
    char c;
    printf("Give the cards of each deck and the number of them\nFor example ['A-1' 'K-3' '2-3'] 3 ['5-2'] 1 \n");

    while((c=getchar())=='[')//ignores character '['
    {
        while(c!=']')//until reaches character  ']'
        {
            scanf("%5s",&s);//reads each card (containing of 5 characters)
            if(s[1]=='1'&&s[2]=='0')//in case of 10 saves the 6th character
            {
                scanf("%1s",&s[5]);
            }
            for(int d=0; d<52; d++)
            {
                // compares a card of the input to the initialized deck
                // to find out which card it is
                if(strcmp(s,card[d])==0)
                {
                    number[d]++;//increases number of the specific card that is given
                    break;
                }

            }
            c=getchar();
        }
        scanf("%d", &size[i]);//saves size of the deck that is given by the user
        if(size[i]==52)//case of having a complete deck
        {
            for(int j=0; j<52; j++)
            {
                number[j]--;//ignores the cards of the completed deck
            }
            decks=1;
        }
        if((c=getchar())=='\n')
        {
            break;
        };
        i++;

    }
    min=number[0];
    for(int i=0; i<52; i++)
    {
        if(number[i]<=min)//finding the least shown card
        {
             min=number[i];
        }

    }
    decks=decks+min;//total decks will be the completed ones and the number of cards shown the least times

    //prints te number of completed decks and the cards that left
    printf("\n%d,[", decks);
    for(int j=0; j<52; j++)
    {
        if(number[j]>min)
        {
            n=number[j]-min;//number of a specific card that left
            for(int i=0; i<n; i++)
            {
                printf("%s,",card[j]);
            }
        }

    }
    printf("\b]");
    return 0;


}
