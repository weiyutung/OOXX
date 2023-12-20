12/20
// 411262271 魏羽彤
// 411262673 蔡詠淇
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BOARD_SIZE = 3;                       // 定義遊戲棋盤大小

enum class Player { NONE, PLAYER1, PLAYER2 };   // 定義玩家類型

class TicTacToe {                               // 定義遊戲類
private:
    vector<vector<Player>> board;               // 遊戲棋盤
    vector<string> players;                     // 玩家名稱
    size_t currentPlayerIndex;                  // 目前玩家的索引
public:
    size_t player1Wins;                         // 紀錄玩家1贏的回合數
    size_t player2Wins;                         // 紀錄玩家2贏的回合數
 TicTacToe() : board(BOARD_SIZE, vector<Player>(BOARD_SIZE, Player::NONE)), currentPlayerIndex(0), player1Wins(0), player2Wins(0) {}

    void addPlayer(const string& playerName){   // 新增玩家
        players.push_back(playerName);
    }

    string getCurrentPlayerName() const {       // 取得目前玩家名稱
        return players[currentPlayerIndex];
    }

    void displayBoard() const{                  // 顯示遊戲棋盤

        cout << "   ";
        for (int col = 0; col < BOARD_SIZE; ++col) {       // 印 col
            cout << "" << col << "   ";
        }
        cout << endl;

        for (int i = 0; i < BOARD_SIZE; ++i) {            // 印 row 和 board
            cout << i << " ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                switch (board[i][j]) {
                    case Player::PLAYER1:
                        cout << " X ";
                        break;
                    case Player::PLAYER2:
                        cout << " O ";
                        break;
                    default:
                        cout << "   ";
                        break;
                }
                if (j < BOARD_SIZE - 1)
                    cout << "|";
            }
            cout << endl;
            if (i < BOARD_SIZE - 1) {
                cout << "  ";
                for (int k = 0; k < BOARD_SIZE; ++k) {
                    cout << "---";
                    if (k < BOARD_SIZE - 1)
                        cout << "+";
                }
                cout << endl;
            }
        }
        cout << endl;
    }

    bool makeMove(int row, int col, Player currentPlayer) {                     // 玩家進行移動
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != Player::NONE) {
            cout << "Invalid move, please choose a different position." << endl;                // 無效移動
            return false;
        }
        board[row][col] = currentPlayer;                    // 更新棋盤
        return true;
    }

    bool checkWin(Player currentPlayer) const {       // 檢查是否有玩家獲勝
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
                return true;                          // 檢查行
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
                return true;                          // 檢查列
        }
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)           // 檢查對角線
            return true;
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
            return true;
        return false;
    }

    bool checkDraw() const {                            // 檢查是否平局
        for (const auto& row : board) {
            for (const auto& cell : row) {
                if (cell == Player::NONE)
                    return false;                       // 存在空格，遊戲繼續
            }
        }
        return true;                                    // 所有格子都滿了，平局
    }

    void drawNextPlayer() {                             // 抽籤選擇下一位玩家
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
    size_t getPlayer1Wins() const {                    // 獲取玩家1贏得的回合數
        return player1Wins;
    }

    size_t getPlayer2Wins() const {                    // 獲取玩家2贏得的回合數
        return player2Wins;
    }

    void displayOverallResults() const {               // 顯示整體結果
        if(getPlayer1Wins() == 1 || getPlayer1Wins() == 0)
            cout << players[0] << " wins: " << getPlayer1Wins() << " round" << endl;
        else
            cout << players[0] << " wins: " << getPlayer1Wins() << " rounds" << endl;
        if(getPlayer2Wins() == 1 || getPlayer2Wins() == 0)
            cout << players[1] << " wins: " << getPlayer2Wins() << " round" << endl;
        else
            cout << players[1] << " wins: " << getPlayer2Wins() << " rounds" << endl;

    }

    void resetBoard() {                                // 重置棋盤
        board = vector<vector<Player>>(BOARD_SIZE, vector<Player>(BOARD_SIZE, Player::NONE));
        currentPlayerIndex = 0;
    }
};
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    TicTacToe game;

    string playerName1, playerName2;
    cout << "Enter Player 1's name: ";
    cin >> playerName1;
    game.addPlayer(playerName1);

    cout << "Enter Player 2's name: ";
    cin >> playerName2;
    game.addPlayer(playerName2);

    bool playAgain = true;
    while (playAgain) {
        game.resetBoard();                             // 重置棋盤
        Player currentPlayer = (rand() % 2 == 0) ? Player::PLAYER1 : Player::PLAYER2;  // 隨機決定先手玩家
        cout << endl;
        cout << (currentPlayer == Player::PLAYER1 ? playerName1 : playerName2) << " goes first!" << endl;
        cout << endl;
        bool gameIsOver = false;                      // 新增變數來標記遊戲是否已經結束
        while (!gameIsOver) {
            game.displayBoard();                      // 顯示當前狀態
            int row, col;
            cout << "It's " << (currentPlayer == Player::PLAYER1 ? playerName1 : playerName2) << " turn" << endl;;
            cout << "Please enter row : ";
            cin >> row ;
            cout << "Please enter col : ";
            cin >> col;
            cout << endl;

            while (!game.makeMove(row, col, currentPlayer)) {                 // 玩家進行移動，直到有效移動為止
                cout << "Please enter row : ";
                cin >> row ;
                cout << "Please enter col : ";
                cin >> col;
                cout << endl;
            }

            if (game.checkWin(currentPlayer)) {                               // 檢查是否獲勝
                game.displayBoard();
                cout << (currentPlayer == Player::PLAYER1 ? playerName1 : playerName2) << " Win! Game Over." << endl;
                gameIsOver = true;
                if (currentPlayer == Player::PLAYER1) {
                    game.player1Wins++;
                } else if (currentPlayer == Player::PLAYER2) {
                    game.player2Wins++;
                }
                break;
            }

            if (game.checkDraw()) {                                            // 檢查是否平局
                game.displayBoard();
                cout << "It's a tie!" << endl;
                gameIsOver = true;
                break;
            }

            game.drawNextPlayer();                                             // 抽籤選擇下一位玩家
            currentPlayer = (currentPlayer == Player::PLAYER1) ? Player::PLAYER2 : Player::PLAYER1;
        }

        char response;                  // 詢問是否進行下一輪
        cout << "Do you want to play again? (y/n): ";
        cin >> response;
        if (response != 'y' && response != 'Y')
            playAgain = false;
    }
    cout << endl;
    game.displayOverallResults();
    cout << "Goodbye!" << endl;
    return 0;
}
