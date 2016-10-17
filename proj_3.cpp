#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;

void printboard(int x, int y, char ** array){
	// for printing the array
	int i = 0;
	cout << " ";
 		for(i = 0 ; i < y ; i++){
			cout <<"_" <<  i;
		}

	cout <<"_" << endl; 

	for( i = 0; i < x ; i++){
		cout << " " << "|"; 
		for(int j = 0 ; j < y ; j++){
			if(j < 10){		
		 		cout << array[i][j] << "|";
			}
			else{
				
				cout << " "<< array[i][j] << "|";
			}
		}
		cout << i ;
		cout << endl;
	}
	
}

// For creating the number of bombs. Same postions for the bombs may repeat. Need to fix it
void createBombs(char **dupBoard, int numberOfBombs, int size_x,int size_y){
	srand(time(NULL)); 
	int iter = 0;
	int x_cor, y_cor;
	while(iter < numberOfBombs){
	
		x_cor = rand() % size_x;
		y_cor = rand() % size_y;
		if(dupBoard[x_cor][y_cor] != '*'){
			dupBoard[x_cor][y_cor] = '*';
			iter++;
		} 		
	}
	
}

// For revealing if the possible surrounding values are 0's
void revealFunc(char **original, char** duplicate, int size_x, int size_y, int X_Cor, int Y_Cor ){
	int iter1;
	//the initials two for loops are for covering the eight blocks surrounding the middle block
	for(int i1 = X_Cor - 1; i1 <= X_Cor + 1 ; i1++){
		for(int j1 = Y_Cor - 1; j1 <= Y_Cor + 1; j1++ ){

			// Enter only if the bounday conditions  satisfy
			if( i1>=0 && i1< size_x && j1 >=0 && j1 < size_y){
				if(duplicate[i1][j1] == '_'){

					iter1 = 0;
					for(int i2 = i1 -1; i2 <= i1+1; i2++){
						for(int j2 = j1 -1; j2 <= j1+1; j2++){
							if(j2 >= 0 && j2 < size_y && i2 >= 0 && i2 < size_x){
								if(duplicate[i2][j2] == '*'){
									iter1++;
								}
							}
						}
					}
					original[i1][j1] = 48 + iter1;
					duplicate[i1][j1] = 48 + iter1;
					if(iter1 == 0){
						revealFunc(original, duplicate, size_x, size_y, i1, j1);
					}
					
				}
					
			}
		}
	}

}

// Playing the game
void playGame(char** dupBoard, char** origBoard, int x, int y){
	
	int xCor, yCor, iterator;
	bool game = true;
	while(game){
		cout << "Enter the value of X-Coordinate: " << endl;
		cin >> xCor;
		while((xCor >= x || xCor < 0)){
		
			cout << "Enter valid Cor for X: " << endl;
			cin >> xCor;
		}

		cout << "Enter the value of Y-Coordinate: " << endl;
		cin >> yCor;
		while(yCor >= y || yCor < 0){

			cout << "Enter the valid Cor for Y: " << endl;
			cin >> yCor;	
		}
		if(dupBoard[xCor][yCor] == '*'){
			origBoard[xCor][yCor] = '*';
			cout << "You lost (!_!)" << endl;
			game = false;
		}
		else{
			iterator = 0;
			
			for(int i = xCor - 1; i <= xCor + 1 ; i++){
				for(int j = yCor - 1; j <= yCor + 1; j++ ){
					if( i>=0 && i< x && j >=0 && j <y ){
						if(dupBoard[i][j] == '*')
							iterator++;
					}
				}
			}
				
			origBoard[xCor][yCor] = 48 + iterator;
			dupBoard[xCor][yCor] = 48 + iterator;

		} 
		if(iterator == 0){
			
			revealFunc(origBoard, dupBoard, x, y, xCor, yCor);
		}

		printboard(x,y,origBoard);

		int count = 0;
		for(int i = 0; i < x; i++){
			for(int j =0; j < y; j++){
				if(dupBoard[i][j] != '_'){
					count++;
				}
			}
		}
		if(count == (x*y)){
			cout << "You are the champion my friend!!!!!! You kept on fighting till the end!! " << endl;
			cout << "\\m/(-_-)\\m/" << endl;
			cout << "\\m/(-_-)\\m/" << endl;
			
			game = false;
		}
	}
}


int main(){
	
	int size_x, size_y;
	int numBombs , sizeBombs;
	cout << "Enter the width and height of the board you want to play: " <<  endl;
	cin >> size_x >> size_y;
	char **board = (char**)malloc((size_x + 1) * sizeof(char*));
	for(int i = 0; i < size_x; i++){
	
		board[i] = (char*)malloc((size_y + 1) * sizeof(char));
	}
	    if (board == NULL) {
        		cout << "Memory allocation failed" << endl;
        		return 1; //abort program
   		 }
	// Fill the board with '_' first
	
	for(int j = 0 ; j < size_x ; j++){

		for(int k = 0; k < size_y ; k++ ){
		
			board[j][k] = '_';
		}
	}
	

	//duplicate board to play the game

	char **duplicate_board = (char**)malloc((size_x + 1) * sizeof(char*));
	for(int i = 0; i < size_x; i++){
	
		duplicate_board[i] = (char*)malloc((size_y + 1) * sizeof(char));
	}
 	if (duplicate_board == NULL) {
        		cout << "Memory allocation failed" << endl;
        		return 1; //abort program
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
//	printboard(size_x, size_y, duplicate_board);
	printboard(size_x, size_y, board);	
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
