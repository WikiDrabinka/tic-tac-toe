#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

int main(){
    int dimensions;
    printf("Welcome to the game!\nYou already know the rules ;)\nControls:\nview {coordinates}\nplay {coordinates [usually just 1]}\nEnter the number of dimensions: ");
    scanf("%d",&dimensions);
    board *mainBoard = createBoard(dimensions);
    displayBoard(mainBoard);
    int turn=1;
    while (updateBoardState(mainBoard)==0 && mainBoard->fieldsUsed<9){
        int task=0;
        int *coordinates=malloc(sizeof(int));
        int i=0;
        char input[10];
        field *field;
        printf("Player %d's turn\n",turn);
        while (task==0){
            scanf("%s",input);
            while (strcmp(input,"view")!=0 && strcmp(input,"play")!=0){
                printf("Incorrect command. Try again\n");
                scanf("%s",input);
            }
            if (strcmp("play",input)==0){
                task=1;
            }
            int coord;
            char temp;
            while (scanf("%d%c",&coord,&temp)>0){
                coordinates=realloc(coordinates,(i+1)*sizeof(int));
                coordinates[i]=coord;
                i++;
                if (temp=='\n'){
                    break;
                }
            }
            field=getFieldFromCoordinates(mainBoard,coordinates,i);
            if (task==0){
                if (field->board!=NULL){
                    displayBoard(field->board);
                } else {
                    printf("Chosen field does not contain a board. Try using less coordinates\n");
                }
                coordinates=realloc(coordinates,sizeof(int));
                i=0;
            }
        }
        setFieldState(field,turn);
        displayBoard(mainBoard);
        turn=3-turn;
        free(coordinates);
    }
}