struct field{
    int state;
    struct board *board;
    struct board *motherBoard;
};
typedef struct field field;

struct board{
    int state;
    int dimensions;
    field **fields;
    int fieldsUsed;
};
typedef struct board board;

board* createBoard(int dimensions); //done
void destroyBoard(board **board); //done
int updateBoardState(board *board); //done
void displayBoard(board *board); //done

board* getBoardFromField(field *field); //done
int updateFieldState(field *field); //done
void setFieldState(field *field, int state); //done
field* getFieldFromCoordinates(board *board, int *coordinates, int depth); //done