#include "game.h"

//Name: Pranav Saboo, psaboo2
//Group members: Kyle Li (kyleli2), Pranav Saboo (psaboo2), Saud Tahir(saudtt2)

/**
 * Intro Paragraph:
 * First we set the user inputs of rows and columns to the mygame bounds.
 * To start the game we want the board to be clear which is represented
 * by a board filled with "-1"s. This is done in the make game * make_game
 * function.
 *
 * For the remake_game function we do a similar process in which
 * we make the board filled with "-1"s given the rows and cols.
 *
 * The function get_cell is meant to return a pointer to the corresponding
 * cell in the game, given the row and column it is at in what is viewed as
 * a 2D array. Since the cells array is a 1D array, we first apply a conversion
 * to the row and column, make sure that we are not out of bounds, and then
 * return the pointer to the cell from the conversion. This pointer is useful
 * in the move functions, where it is dereferenced to determine the value
 * at each cell.
 *
 * The user can make 4 moves using the keys w, a, s, d. Each key
 * has a similar function but are slightly different in the orientation they
 * move the board. For the w and s functions we iterate through the cols
 * and while the current row is within the row bounds we check to see what
 * the value holds. Similarly in functions a and d we iterate through the rows
 * and while the col is within the col bounds we check to see what value it holds.
 * If the value held is -1, we find the next non -1 number and move it up to the
 * current index. I f the value at the current index is not -1, we find the next
 * non -1 number and see if its value is the same as teh current index. If it is,
 * we double the vlue at the current index and increment our index. If not, we
 * move it to the next index after our current index and increment teh current index.
 * If the current index reaches the bounds of the board or the rest of the values
 * after the current index are all -1, we move to the next row/col depending on
 * whether the function is ws or ad. After iterating through all rows/cols,
 * the function ends.
 *
 * The function legal_move_check is meant to return a 1 if there are more
 * moves available to make, or a 0 if there are no more moves left. Since our
 * move functions return a 1 if there is a move available to make, we first make
 * a deep copy of the board, then apply each function to the copy. If any
 * function returns a 1, we return a 1 in the function.
 *
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/

{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //Initialize all other variables in game struct

    //initialize variables
  	mygame->rows = rows;   //this is the same as (*mygame).rows = rows
  	mygame->cols = cols;
  	mygame->score = 0;
  	int i;

  	//set every cell in mygame to -1
  	for (i=0; i<rows*cols; i++) {
      mygame->cells[i] = -1;
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows; //since _cur_game_ptr is passed by reference, we must dereference it once
  	(*_cur_game_ptr)->cols = new_cols;
  	(*_cur_game_ptr)->score = 0;
  	int i;
  	//set each element to -1
  	for (i=0; i<new_rows*new_cols; i++) {
      (*_cur_game_ptr)->cells[i] = -1;
    }
	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    int index = row * cur_game->cols + col; //going from 2D to 1D

  	// if not in game board bounds then return Null
  	if (row>=(cur_game->rows) || col>=(cur_game->cols) || col<0 || row<0) {
			return NULL;
    }

  	return &cur_game->cells[index]; //dereference to obtain actual value in cell
}


int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
  	int row;
  	int tempIdx;
  	int col;
  	int change = 0;

  	//iterates through columns
  	for (col=0; col<(cur_game->cols); col++) {

  	    //sets current row to 0
  	    row=0;

  	    //while current row is not out of the bounds of the game board
  	    while(row < cur_game->rows) {
  	        //set temporary row index to the index after the current row
            tempIdx = row + 1;

            //while the next non -1 valued index is not found, increment tempIdx
            while (tempIdx < cur_game->rows && *get_cell(cur_game, tempIdx, col) == -1){
                tempIdx++;
            }

            //if tempIdx is out of bounds, move onto next column
            if (tempIdx == cur_game->rows) {
                break;
            }

            //if the current row index holds the value -1, then replace current row index value with value at tempIdx
            if (*get_cell(cur_game, row, col) == -1) {
                *get_cell(cur_game, row, col) = *get_cell(cur_game, tempIdx, col);

                //set value of tempIdx to -1
                *get_cell(cur_game, tempIdx, col) = -1;

                //update change to 1
                change = 1;
            }

            // else, if the current row index's value is not -1
            else{
                // if the current row index holds the same value as the value at tempIdx
                if (*get_cell(cur_game, tempIdx, col) == *get_cell(cur_game, row, col)) {
                    //double current row index value
                    *get_cell(cur_game, row, col) *= 2;

                    //set temp index value to -1
                    *get_cell(cur_game, tempIdx, col) = -1;

                    //update score
                    cur_game->score += *get_cell(cur_game, row, col);


                    //update change to 1
                    change = 1;
                }

                // if current index value is not the same as the value at tempIdx and the next index's value is -1
                else if (*get_cell(cur_game, row + 1, col) == -1) {
                    // set the value of the next row index to the value at tempIdx
                    *get_cell(cur_game, row + 1, col) = *get_cell(cur_game, tempIdx, col);

                    // if tempIdx is not the next index after current row index, update the value at tempIdx to -1
                    if (tempIdx != row + 1){
                        *get_cell(cur_game, tempIdx, col) = -1;
                    }

                     //update change to 1
                    change = 1;
                }

                //increment row
                row++;
            }
  	    }
  	}
  	return change;
}


int move_s(game * cur_game) //slide down
{
  	int row;
  	int tempIdx;
  	int col;
  	int change = 0;

  	//iterates through columns
  	for (col=cur_game->cols-1; col >= 0; col--) {

  	    //sets current row to max row
  	    row=cur_game->rows-1;

  	    //while current row is not out of the bounds of the game board
  	    while(row >= 0) {
  	        //set temporary row index to the index before the current row
            tempIdx = row - 1;

            //while the next non -1 valued index is not found, decrement tempIdx
            while (tempIdx >= 0 && *get_cell(cur_game, tempIdx, col) == -1){
                tempIdx--;
            }

            //if tempIdx is out of bounds, move onto next column
            if (tempIdx == -1) {
                break;
            }

            //if the current row index holds the value -1, then replace current row index value with value at tempIdx
            if (*get_cell(cur_game, row, col) == -1) {
                *get_cell(cur_game, row, col) = *get_cell(cur_game, tempIdx, col);

                //set value of tempIdx to -1
                *get_cell(cur_game, tempIdx, col) = -1;

                //update change to 1
                change = 1;
            }

            // else, if the current row index's value is not -1 and the next index's value is -1
            else {
                // if the current row index holds the same value as the value at tempIdx
                if (*get_cell(cur_game, tempIdx, col) == *get_cell(cur_game, row, col)) {
                    //double current row index value
                    *get_cell(cur_game, row, col) *= 2;

                    //set temp index value to -1
                    *get_cell(cur_game, tempIdx, col) = -1;

                    //update score
                    cur_game->score += *get_cell(cur_game, row, col);

                    //update change to 1
                    change = 1;
                }

                // if current index value is not the same as the value at tempIdx and the next index's value is -1
                else if (*get_cell(cur_game, row - 1, col) == -1) {
                    // set the value of the next row index (row - 1) to the value at tempIdx
                    *get_cell(cur_game, row - 1, col) = *get_cell(cur_game, tempIdx, col);

                    // if tempIdx is not the next index after current row index, update teh value at tempidx to -1
                    if (tempIdx != row - 1){
                        *get_cell(cur_game, tempIdx, col) = -1;
                    }

                    //update change to 1
                    change = 1;
                }

                //decrement row
                row--;
            }
  	    }
  	}
  	return change;
}


int move_a(game * cur_game) //slide left
{
  	int row;
  	int tempIdx;
  	int col;
  	int change = 0;

  	//iterates through rows
  	for (row=0; row<(cur_game->rows); row++) {

  	    //sets current col to 0
  	    col=0;

  	    //while current col is not out of the bounds of the game board
  	    while(col < cur_game->cols) {
  	        //set temporary col index to the index after the current col
            tempIdx = col + 1;

            //while the next non -1 valued index is not found, increment tempIdx
            while (tempIdx < cur_game->cols && *get_cell(cur_game, row, tempIdx) == -1){
                tempIdx++;
            }

            //if tempIdx is out of bounds, move onto next row
            if (tempIdx == cur_game->cols) {
                break;
            }

            //if the current col index holds the value -1, then replace current col index value with value at tempIdx
            if (*get_cell(cur_game, row, col) == -1) {
                *get_cell(cur_game, row, col) = *get_cell(cur_game, row, tempIdx);

                //set value of tempIdx to -1
                *get_cell(cur_game, row, tempIdx) = -1;

                //update change to 1
                change = 1;
            }

            // else, if the current col index's value is not -1 and the next index's value is -1
            else  {
                // if the current col index holds the same value as the value at tempIdx
                if (*get_cell(cur_game, row, tempIdx) == *get_cell(cur_game, row, col)) {
                    //double current col index value
                    *get_cell(cur_game, row, col) *= 2;

                    //set temp index value to -1
                    *get_cell(cur_game, row, tempIdx) = -1;

                    //update score
                    cur_game->score += *get_cell(cur_game, row, col);

                    //update change to 1
                    change = 1;
                }

                // if current index value is not the same as the value at tempIdx and the next index's value is -1
                else if (*get_cell(cur_game, row, col + 1) == -1) {
                    // set the value of the next col index to the value at tempIdx
                    *get_cell(cur_game, row, col + 1) = *get_cell(cur_game, row, tempIdx);

                    // if tempIdx is not the next index after current row index, update teh value at tempidx to -1
                    if (tempIdx != col + 1){
                        *get_cell(cur_game, row, tempIdx) = -1;
                    }

                    //update change to 1
                    change = 1;
                }

                //incrememnt col
                col++;
            }
  	    }
  	}
  	return change;
}


int move_d(game * cur_game){ //slide to the right
  	int row;
  	int tempIdx;
  	int col;
  	int change = 0;

  	//iterates through rows
  	for (row=(cur_game->rows) - 1; row>=0; row--) {

  	    //sets current col to max col
  	    col=(cur_game->cols) - 1;

  	    //while current col is not out of the bounds of the game board
  	    while(col >= 0) {
  	        //set temporary col index to the index before the current col
            tempIdx = col - 1;

            //while the next non -1 valued index is not found, decrement tempIdx
            while (tempIdx >= 0 && *get_cell(cur_game, row, tempIdx) == -1){
                tempIdx--;
            }

            //if tempIdx is out of bounds, move onto next row
            if (tempIdx == -1) {
                break;
            }

            //if the current col index holds the value -1, then replace current col index value with value at tempIdx
            if (*get_cell(cur_game, row, col) == -1) {
                *get_cell(cur_game, row, col) = *get_cell(cur_game, row, tempIdx);

                //set value of tempIdx to -1
                *get_cell(cur_game, row, tempIdx) = -1;

                //update change to 1
                change = 1;
            }

            // else, if the current col index's value is not -1 and the next index's value is -1
            else {
                // if the current col index holds the same value as the value at tempIdx
                if (*get_cell(cur_game, row, tempIdx) == *get_cell(cur_game, row, col)) {
                    //double current col index value
                    *get_cell(cur_game, row, col) *= 2;

                    //set temp index value to -1
                    *get_cell(cur_game, row, tempIdx) = -1;

                    //update score
                    cur_game->score += *get_cell(cur_game, row, col);

                    //update change to 1
                    change = 1;
                }

                // if current index value is not the same as the value at tempIdx and the next index's value is -1
                else if (*get_cell(cur_game, row, col - 1) == -1) {
                    // set the value of the next col index (col - 1) to the value at tempIdx
                    *get_cell(cur_game, row, col - 1) = *get_cell(cur_game, row, tempIdx);

                    // if tempIdx is not the next index after current row index, update teh value at tempidx to -1
                    if (tempIdx != col - 1){
                        *get_cell(cur_game, row, tempIdx) = -1;
                    }

                    //update change to 1
                    change = 1;
                }

                //decrement col
                col--;
            }
  	    }
  	}
  	return change;
}

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    int i;
    //makes a copy of cur_game to apply checks to it
    game * cur_game_copy = malloc(sizeof(game));
    cur_game_copy->cells = malloc((cur_game->rows)*(cur_game->cols)*sizeof(cell));

    //copies cols and rows from cur_game to cur_game_copy
    cur_game_copy->cols = cur_game->cols;
    cur_game_copy->rows = cur_game->rows;

    //copies all cells from cur_game to cur_game_copy_
    for (i=0; i<(cur_game->cols)*(cur_game->rows); i++) {
        cur_game_copy->cells[i] = cur_game->cells[i];
    }

    // checks to see if any moves can be made
    if (move_w(cur_game_copy) || move_a(cur_game_copy) || move_s(cur_game_copy) || move_d(cur_game_copy) == 1) {
        return 1;
    }

    // if no moves can be made, return 0
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
