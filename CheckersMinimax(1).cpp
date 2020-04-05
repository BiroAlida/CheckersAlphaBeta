#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

typedef struct Piece {
	char player;
	int x, y;
	bool moveBack;
};

typedef struct Board {
	struct Piece* pieces[8][8];
	int score;
	Board* parent;
};

struct Board* initialBoard = new Board{};
vector<Board*> possibleMoves;
vector<Board*> possibleMovesHuman;
unsigned char turn;
unsigned char player1 = 'A';
unsigned char player2 = 'B';
int player1Score = 0;
int player2Score = 0;
int layer = 3;

int calculateScore(Board* board) {
	int countA = 0, countB = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->pieces[i][j]->player == player1) {
				++countA;
			}
			if (board->pieces[i][j]->player == player2) {
				++countB;
			}
		}
	}
	return abs(countB - countA);
}

void initBoard() {
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++) {
			initialBoard->pieces[i][j] = new Piece{' ', i, j, false };
		}
		
	}

	initialBoard->pieces[0][0] = new Piece{ 'B', 0, 0, false }; 
	initialBoard->pieces[0][2] = new Piece{ 'B', 0, 2, false };
	initialBoard->pieces[0][4] = new Piece{ 'B', 0, 4, false };
	initialBoard->pieces[0][6] = new Piece{ 'B', 0, 6, false };
	initialBoard->pieces[1][1] = new Piece{ 'B', 1, 1, false };
	initialBoard->pieces[1][3] = new Piece{ 'B', 1, 3, false };
	initialBoard->pieces[1][5] = new Piece{ 'B', 1, 5, false };
	initialBoard->pieces[1][7] = new Piece{ 'B', 1, 7, false };
	initialBoard->pieces[2][0] = new Piece{ 'B', 2, 0, false };
	initialBoard->pieces[2][2] = new Piece{ 'B', 2, 2, false };
	initialBoard->pieces[2][4] = new Piece{ 'B', 2, 4, false };
	initialBoard->pieces[2][6] = new Piece{ 'B', 2, 6, false };

	initialBoard->pieces[5][1] = new Piece{ 'A', 5, 1, false };
	initialBoard->pieces[5][3] = new Piece{ 'A', 5, 3, false };
	initialBoard->pieces[5][5] = new Piece{ 'A', 5, 5, false };
	initialBoard->pieces[5][7] = new Piece{ 'A', 5, 7, false };
	initialBoard->pieces[6][0] = new Piece{ 'A', 6, 0, false };
	initialBoard->pieces[6][2] = new Piece{ 'A', 6, 2, false };
	initialBoard->pieces[6][4] = new Piece{ 'A', 6, 4, false };
	initialBoard->pieces[6][6] = new Piece{ 'A', 6, 6, false };
	initialBoard->pieces[7][1] = new Piece{ 'A', 7, 1, false };
	initialBoard->pieces[7][3] = new Piece{ 'A', 7, 3, false };
	initialBoard->pieces[7][5] = new Piece{ 'A', 7, 5, false };
	initialBoard->pieces[7][7] = new Piece{ 'A', 7, 7, false };
	
	initialBoard->score = calculateScore(initialBoard);
	initialBoard->parent = NULL;
}

void printBoard(Board* board) {
	int i, j;
	for (i = 0; i < 8; i++)
	{
		cout << i << "| ";
		for (j = 0; j < 8; j++) {
			cout << board->pieces[i][j]->player << "  ";
		}

		cout << endl;
	}

	cout << "   ";
	for (j = 0; j < 8; j++) {
		cout << j << "  ";
	}
	cout << endl;
}

void changeTurn() {
	if (turn == player1) {
		turn = player2;
	}
	else {
		turn = player1;
	}
}

void increaseScore() {
	if (turn == player1) {
		player1Score++;
	}
	else {
		player2Score++;
	}
}

bool isValidMove(Board* board, int x, int y, int xInput, int yInput) {
	if (xInput < 0 || xInput > 7 || yInput < 0 || yInput > 7 || yInput == y) {
		return false;
	}

	if (board->pieces[xInput][yInput]->player == turn) {
		return false;
	}

	if (turn == player1) {
		if (board->pieces[x][y]->moveBack != true) {
			if (xInput != x - 1 && (yInput != y - 1 || yInput != y + 1)) {
				return false;
			}
		}
		else {
			if (xInput != x + 1 && (yInput != y - 1 || yInput != y + 1)) {
				return false;
			}
		}
	}

	if (turn == player2) {
		if (board->pieces[x][y]->moveBack != true) {
			if (xInput != x + 1 && (yInput != y - 1 || yInput != y + 1)) {
				return false;
			}
		}
		else {
			if (xInput != x - 1 && (yInput != y - 1 || yInput != y + 1)) {
				return false;
			}
		}
	}

	return true;
}

void checkIfLastRow(Board* board, int x, int y) {
	if ((turn == player1 && x == 0) || (turn == player2 && x == 7)) {
		board->pieces[x][y]->moveBack = true;
	}
}

void removeEnemy(Board* board, int x, int y, int xInput, int yInput) {
	if (turn == player1) {
		if (yInput < y) {
			if (board->pieces[xInput - 1][yInput - 1]->player == ' ') {
				board->pieces[xInput][yInput]->player = ' ';
				board->pieces[xInput - 1][yInput - 1]->player = turn;

				checkIfLastRow(board, xInput - 1, yInput - 1);
				increaseScore();
				changeTurn();
				return;
			}
		}
		if (yInput > y) {
			if (board->pieces[xInput - 1][yInput + 1]->player == ' ') {
				board->pieces[xInput][yInput]->player = ' ';
				board->pieces[xInput - 1][yInput + 1]->player = turn;

				checkIfLastRow(board,xInput - 1, yInput + 1);
				increaseScore();
				changeTurn();
				return;
			}
		}
	}

	if (turn == player2) {
		if (yInput < y) {
			if (board->pieces[xInput + 1][yInput - 1]->player == ' ') {
				board->pieces[xInput][yInput]->player = ' ';
				board->pieces[xInput + 1][yInput - 1]->player = turn;

				checkIfLastRow(board,xInput + 1, yInput - 1);
				increaseScore();
				changeTurn();
				return;
			}
		}
		if (yInput > y) {
			if (board->pieces[xInput + 1][yInput + 1]->player == ' ') {
				board->pieces[xInput][yInput]->player = ' ';
				board->pieces[xInput + 1][yInput + 1]->player = turn;

				checkIfLastRow(board, xInput + 1, yInput + 1);
				increaseScore();
				changeTurn();
				return;
			}
		}
	}

}

void printScore() {
	if (turn == player1) {
		cout << player1Score << endl;
	}
	else {
		cout << player2Score << endl;
	}
}

bool checkWinner() {
	if (player1Score == 12) {
		cout << player1 << " winner!" << endl;
		return true;
	} 

	if (player2Score == 12) {
		cout << player2 << " winner!" << endl;
		return true;
	}

	return false;
}

void makeMoveHuman(Board* board) {
	int x, y, xInput, yInput;
	cout << turn << " "; printScore();
	cout << "Adja meg a babu koordinatait: " << endl;
	cout << "y koordinata: "; cin >> x;
	cout << "x koordinata: "; cin >> y;

	if (board->pieces[x][y]->player == turn) {
		cout << "Adja meg a koordinatakat: " << endl;
		cout << "x: "; cin >> xInput;
		cout << "y: "; cin >> yInput;

		if (isValidMove(board, x,y,xInput, yInput)) {
			if (board->pieces[xInput][yInput]->player != turn && board->pieces[xInput][yInput]->player != ' ') {
				removeEnemy(board, x, y, xInput, yInput);
				board->pieces[x][y]->player = ' ';
			}
			else {
				board->pieces[xInput][yInput]->player = board->pieces[x][y]->player;
				board->pieces[x][y]->player = ' ';
			}
			checkIfLastRow(board, xInput, yInput);

			system("CLS");
			printBoard(board);
 		}
		else {
			cout << "Nem joo lepes!" << endl;
		}
	}
	else {
		cout << "Nem megfelelo babu!" << endl;
	}

}

void copyPiece(Piece* p1, Piece* p2) {
	p1->moveBack = p2->moveBack;
	p1->player = p2->player;
	p1->x = p2->x;
	p1->y = p2->y;
}

void copyStruct(Board* b1, Board* b2) {
	b1->parent = b2->parent;
	b1->score = b2->score;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			b1->pieces[i][j] = new Piece{};
			copyPiece(b1->pieces[i][j], b2->pieces[i][j]);
		}
	}
}

void findMoves(Board* board, int player, vector<Board*> &possibleMoves) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->pieces[i][j]->player == player) {
				if (isValidMove(board, i, j, i + 1, j + 1)) {
					Board* tempBoard = new Board{};
					copyStruct(tempBoard, board);

					tempBoard->pieces[i][j]->player = ' ';
					tempBoard->pieces[i + 1][j + 1]->player = player;
					tempBoard->score = calculateScore(tempBoard);
					tempBoard->parent = board;
					possibleMoves.push_back(tempBoard);
				}
				if (isValidMove(board, i, j, i + 1, j - 1)) {
					Board* tempBoard = new Board{};
					copyStruct(tempBoard, board);

					tempBoard->pieces[i][j]->player = ' ';
					tempBoard->pieces[i + 1][j - 1]->player = player;
					tempBoard->score = calculateScore(tempBoard);
					tempBoard->parent = board;
					possibleMoves.push_back(tempBoard);
				}
				if (isValidMove(board, i, j, i - 1, j + 1)) {
					Board* tempBoard = new Board{};
					copyStruct(tempBoard, board);

					tempBoard->pieces[i][j]->player = ' ';
					tempBoard->pieces[i - 1][j + 1]->player = player;
					tempBoard->score = calculateScore(tempBoard);
					tempBoard->parent = board;
					possibleMoves.push_back(tempBoard);
				}
				if (isValidMove(board, i, j, i - 1, j - 1)) {
					Board* tempBoard = new Board{};
					copyStruct(tempBoard, board);

					tempBoard->pieces[i][j]->player = ' ';
					tempBoard->pieces[i - 1][j - 1]->player = player;
					tempBoard->score = calculateScore(tempBoard);
					tempBoard->parent = board;
					possibleMoves.push_back(tempBoard);
				}
			}
		}
	}
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

int alphaBetaPruning(Board* board, int alpha, int beta) {
	if (layer == 0) {return board->score; }

	possibleMoves.clear();
	possibleMovesHuman.clear();

	if (layer % 2 > 0) {
		//max
		findMoves(board, player2, possibleMoves);
		layer--;
		for (int i = 0; i < possibleMoves.size(); i++) {
			alpha = max(alpha, alphaBetaPruning(possibleMoves[i], alpha, beta));
			if (alpha >= beta) {
				return alpha;
			}
			return alpha;
		}
	}
	else {
		//min
		findMoves(board, player1, possibleMovesHuman);
		layer--;
		for (int i = 0; i < possibleMovesHuman.size(); i++) {
			beta = min(beta, alphaBetaPruning(possibleMovesHuman[i], alpha, beta));
			if (beta >= alpha) {
				return beta;
			}
			return beta;
		}
	}
}

int main()
{
	initBoard();
	printBoard(initialBoard);
	turn = player1;

	while (!checkWinner()) {
		if (turn == player1) {
			makeMoveHuman(initialBoard);
		}
		else {
			int alpha = alphaBetaPruning(initialBoard, INFINITY, -INFINITY);
			possibleMoves.clear();
			findMoves(initialBoard, player2, possibleMoves);
			
			for (int i = 0; i < possibleMoves.size(); i++) {
				if (possibleMoves[i]->score == alpha) {
					copyStruct(initialBoard, possibleMoves[i]);

					system("CLS");
					printBoard(initialBoard);
					break;
				}
			}
		}
		changeTurn();
	}
	
	return 0;
}

