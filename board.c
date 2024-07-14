#include <stdio.h>
#include <stdlib.h>
#include "board.h"

char stateToChar[]={' ','O','X'};

board* createBoard(int dimensions){
    board *board=malloc(sizeof(struct board));
    board->state=0;
    board->dimensions=dimensions;
    board->fields=malloc(9*sizeof(field));
    board->fieldsUsed=0;
    for (int i=0;i<9;i++){
        field *field=malloc(sizeof(struct field));
        field->state=0;
        field->board=NULL;
        field->motherBoard=board;
        if (dimensions>1){
            field->board=createBoard(dimensions-1);
        }
        board->fields[i]=field;
    }
    return board;
}

void destroyBoard(board **pboard){
    board *board = *pboard;
    for (int i=8;i>=0;i--){
        if (board->fields[i]->board!=NULL){
            struct board *newboard=getBoardFromField(board->fields[i]);
            destroyBoard(&newboard);
        }
        free(board->fields[i]);
    }
    free(board->fields);
    free(board);
    *pboard=NULL;
}

int updateBoardState(board *board){
    for (int i=0;i<3;i++){
        if (board->fields[i*3]->state!=0 && board->fields[i*3]->state==board->fields[i*3+1]->state && board->fields[i*3+1]->state==board->fields[i*3+2]->state){
            board->state=board->fields[i*3]->state;
            return board->fields[i*3]->state;
        }
        if (board->fields[i]->state!=0 && board->fields[i]->state==board->fields[i+3]->state && board->fields[i+3]->state==board->fields[i+6]->state){
            board->state=board->fields[i]->state;
            return board->fields[i]->state;
        }
    }
    if (board->fields[0]->state!=0 && board->fields[0]->state==board->fields[4]->state && board->fields[4]->state==board->fields[8]->state){
        board->state=board->fields[0]->state;
        return board->fields[0]->state;
    }
    if (board->fields[2]->state!=0 && board->fields[2]->state==board->fields[4]->state && board->fields[4]->state==board->fields[6]->state){
        board->state=board->fields[2]->state;
        return board->fields[2]->state;
    }
    return 0;
}

void displayBoard(board *board){
    for (int i=0;i<9;i++){
        printf("%c",stateToChar[board->fields[i]->state]);
        if (i%3==2){
            printf("\n");
        } else {
            printf("|");
        }
    }
}

board* getBoardFromField(field *field){
    return field->board;
}

void setFieldState(field *field, int state){
    field->state=state;
    field->motherBoard->fieldsUsed+=1;
}

int updateFieldState(field *field){
    if (field->board!=NULL){
        field->state=updateBoardState(field->board);
    }
    field->motherBoard->fieldsUsed+=1;
    return field->state;
}

field* getFieldFromCoordinates(board *board, int *coordinates, int depth){
    struct board *currentBoard = board;
    if (depth>board->dimensions){
        printf("Too many coordinates (%d), applied only the first %d\n",depth,board->dimensions);
        depth=board->dimensions;
    }
    field *currentField;
    for (int i=0;i<depth;i++){
        currentField=currentBoard->fields[coordinates[i]];
        currentBoard=getBoardFromField(currentField);
    }
    return currentField;
}
