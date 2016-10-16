#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;

void printboard(int x, int y, int ** array){
	// for printing the array
	int i = 0;
	cout << " ";
 	for(i = 0 ; i < y ; i++){
		cout <<"_" <<  i;
	}
	cout <<"_" << endl; 
	for( i = 0; i < x ; i++){
		cout << i << "|"; 
		for(int j = 0 ; j < y ; j++){
					
		 	cout << array[i][j] << "|";
		}
		cout << endl;
	}
	
}

// For creating the number of bombs. Same postions for the bombs may repeat. Need to fix it
void createBombs(int **dupBoard, int numberOfBombs, int size_x,int size_y){
	srand(time(NULL));
	int x_cor, y_cor;
	for(int i = 0 ; i < numberOfBombs; i++){
	
		x_cor = rand() % size_x;
		y_cor = rand() % size_y;
		dupBoard[x_cor][y_cor] = '*'; 		
	}
	
}

// Playing the game
void playGame(int** dupBoard, int** origBoard, int x, int y){
	
	int xCor, yCor, iterator;
	bool game = true;
	while(game){
		cout << "Enter the value of X-Coordinate: " << endl;
		cin >> xCor;
		cout << "Enter the value of Y-Coordinate: " << endl;
		cin >> yCor;
		if(dupBoard[xCor][yCor] == '*'){
			origBoard[xCor][yCor] = '*';
			cout << "You lost" << endl;
			game = false;
		}
		else{
			iterator = 0;
			if(dupBoard[xCor - 1] [yCor] == '*'){
				iterator++;
			}
			if(dupBoard[xCor + 1] [yCor] == '*'){
				iterator++;
			}
			if(dupBoard[xCor - 1] [yCor - 1] == '*'){
				iterator++;
			}
			if(dupBoard[xCor - 1] [yCor + 1] == '*'){
				iterator++;
			}
			if(dupBoard[xCor + 1] [yCor + 1] == '*'){
				iterator++;
			}

			if(dupBoard[xCor + 1] [yCor - 1] == '*'){
				iterator++;
			}

			if(dupBoard[xCor] [yCor + 1] == '*'){
				iterator++;
			}

			if(dupBoard[xCor] [yCor - 1] == '*'){
				iterator++;
			}
				
			origBoard[xCor][yCor] = iterator;

	
		} 

	printboard(x,y,origBoard);
	}
}

int main(){
	
	int size_x, size_y;
	int numBombs , sizeBombs;
	cout << "Enter the size of the board you want to play: " <<  endl;
	cin >> size_x >> size_y;
	int **board = (int**)malloc((size_x + 1) * sizeof(int*));
	for(int i = 0; i < size_x; i++){
	
		board[i] = (int*)malloc((size_y + 1) * sizeof(int));
	}
	
	// Fill the board with '_' first
	
	for(int j = 0 ; j < size_x ; j++){

		for(int k = 0; k < size_y ; k++ ){
		
			board[j][k] = '_';
		}
	}
	
	printboard(size_x, size_y, board);

	//duplicate board to play the game

	int **duplicate_board = (int**)malloc((size_x + 1) * sizeof(int*));
	for(int i = 0; i < size_x; i++){
	
		duplicate_board[i] = (int*)malloc((size_y + 1) * sizeof(int));
	}

	// populate the values in the duplicate board
	for(int j = 0 ; j < size_x; j++){
		for(int k = 0 ; k < size_y ; k++){

			duplicate_board[j][k] = '_';
		}
	}
	
	sizeBombs = size_x * size_y / 4;
	cout << "Enter Number of bombs you want to have on your board(should be less than " << sizeBombs << ") quater size of the board"  << endl;
	cin >> numBombs;
	
	while((numBombs > sizeBombs) || (numBombs < 1)){
		cout << "You have entered an invalid number. Enter number less than or equal to " << sizeBombs << endl;
		cin >> numBombs;
	}

	createBombs(duplicate_board, numBombs, size_x, size_y);
	printboard(size_x, size_y, duplicate_board);
	
	playGame(duplicate_board, board, size_x, size_y);


// free the stuff that was allocated
	for(int j = 0 ; j < size_x; j++){
		free(duplicate_board[j]);
	}
	free(duplicate_board);
	
	for(int i = 0 ; i < size_x; i++){

		free(board[i]);
	}

	free(board);
	return 0;
}
