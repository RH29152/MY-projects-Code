#include<iostream>
#include<string>
using namespace std;

class TicTacToe{
    int Game_board[3][3];
    public:
    TicTacToe(){// default constrcuter
       clearBoard();
    }

    void clearBoard(){  // this function initializes board to all zeros 
         for(int i=0;i<3;i++){
             for(int j=0;j<3;j++){
            Game_board[i][j]=0; }
            }
                     }


    void Board(){// this function prints whole gameBoard

 for(int i=0;i<3;i++){
     for(int j=0;j<3;j++){
            if(j==2)cout<<" "<<Game_board[i][j];
            else cout<<" "<<Game_board[i][j]<<" |";
        }
         cout<<endl;
        cout<<"----------"<<endl; }
}


     bool move(int player, int row, int col){  // This function make moves of game 
     bool isDone=false;
    if(gameStatus()!=3 && Game_board[row][col]==0){ // gamestatus returns 3 if whole board is full 
        Game_board[row][col]=player;
                    return true;
         
         }

    else {cout<<"Invalid Move. Try Again...."<<endl;
    return false; }
    
    }

       


 int count1=0,count2=0,count3=0;

        int gameStatus(){ // this whole functions gives game status whether game is over (lost,win,drawn) or 0

// here we are checking after everymove players wining status

            for(int i=0;i<3;i++){
                count1=0,count2=0,count3=0;
             for(int j=0;j<3;j++){
            if(Game_board[i][0]!=0 && Game_board[i][0]==Game_board[i][j])count1++;  // this checks rows if anyone wining or not
             if(Game_board[i][0]!=0 && Game_board[0][i]==Game_board[j][i])count2++; // this checks columns if anyone wining or not
              if(Game_board[i][0]!=0 && Game_board[i][0]==Game_board[j][j])count3++;// this checks primary diagonals if anyone wining or not
} 
    if(count1==3) return Game_board[i][0];
        if(count2==3) return Game_board[0][i];
        if(count3==3) return Game_board[i][0];
        if(Game_board[0][2]==Game_board[1][1]&&Game_board[0][2]==Game_board[2][0])return Game_board[0][2];// this checks secondary diagonals if anyone wining or not
 }

// here below we are checking that if the game Board full or not 

        bool isFull=true;
for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
           if(Game_board[i][j]==0){ isFull=false; break;}
        }
        if(!isFull)break;
        }
        if(isFull){return 3;} // if game is drawn no one of players won

      return 0;  // if game is'nt over 

        }


   ////********** Tic Tac Toe AI ***********************************************************************************





   // Returns true if the game is over
bool isGameOver() {
    int status = gameStatus();
    return status == 1 || status == 2 || status == 3;
}

// Returns the value of the board from the perspective of the AI player
int evaluateBoard() {
    int status = gameStatus();
    if (status == 1) return -1;  // AI loses
    if (status == 2) return 1;   // AI wins
    return 0;  // Draw or game not over
}

// Implements the Minimax algorithm to find the best move
int minimax(int depth, bool isMaximizingPlayer) {
    int score = evaluateBoard();

    // If the game is over, return the score
    if (isGameOver()) return score;

    if (isMaximizingPlayer) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (Game_board[i][j] == 0) {
                    // Make the move
                    Game_board[i][j] = 2;
                    // Call minimax recursively
                    int currentScore = minimax(depth + 1, false);
                    // Undo the move
                    Game_board[i][j] = 0;
                    // Update the best score
                    bestScore = max(bestScore, currentScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (Game_board[i][j] == 0) {
                    // Make the move
                    Game_board[i][j] = 1;
                    // Call minimax recursively
                    int currentScore = minimax(depth + 1, true);
                    // Undo the move
                    Game_board[i][j] = 0;
                    // Update the best score
                    bestScore = min(bestScore, currentScore);
                }
            }
        }
        return bestScore;
    }
}

// Finds the best move for the AI player
pair<int, int> findBestMove() {
    int bestScore = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if cell is empty
            if (Game_board[i][j] == 0) {
                // Make the move
                Game_board[i][j] = 2;
                // Compute the score of this move
                int moveScore = minimax(0, false);
                // Undo the move
                Game_board[i][j] = 0;
                // If this move is better than the current best, update the best move
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = {i, j};
                }
            }
        }
    }

    return bestMove;
}     
        

};

int main() {
    cout<<"Welcome to Tic-Tac-Toe! \n"<<endl;
    TicTacToe game;
    int player;
    int move=2;
    while(true){
        if(move%2==0) player=1;  else player =2;

        game.Board();

        int row, col;
        if (player == 1) {
            cout<<"Your move: Enter row(0-2) and col(0-2)"<<endl;
            cin>>row>>col;
        } else {
            cout<<"****************AI move done.*********************"<<endl;
            pair<int, int> bestMove = game.findBestMove();
            row = bestMove.first;
            col = bestMove.second;
        }

        if(game.move(player,row,col)) move++;

        if(game.gameStatus()==1){game.Board(); cout<<"Player 1 wins!"<<endl;break;} 
        if(game.gameStatus()==2){ game.Board(); cout<<"Player 2 wins!"<<endl; break;}
        if(game.gameStatus()==3){game.Board(); cout<<"The game is drawn. Try Again."<<endl; break;}
    }
    return 0;
}
