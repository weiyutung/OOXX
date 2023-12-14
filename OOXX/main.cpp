#include <iostream>
#include <vector>
#include <cstdlib>  // 包含cstdlib頭文件以使用rand函數
#include <ctime>    // 包含ctime頭文件以使用time函數

using namespace std;

// 定義遊戲棋盤大小
const int BOARD_SIZE = 3;

// 定義玩家類型
enum class Player { NONE, PLAYER1, PLAYER2 };


// 定義遊戲類
class TicTacToe {
private:
    vector<vector<Player>> board; // 遊戲棋盤
    vector<string> players;       // 玩家名稱
    size_t currentPlayerIndex;    // 目前玩家的索引
    size_t player1Wins;  // 紀錄玩家1贏的回合數
    size_t player2Wins;  // 紀錄玩家2贏的回合數

public:
 TicTacToe() : board(BOARD_SIZE, vector<Player>(BOARD_SIZE, Player::NONE)), currentPlayerIndex(0), player1Wins(0), player2Wins(0) {}
    // 新增玩家
    void addPlayer(const string& playerName) {
        players.push_back(playerName);
    }

    // 取得目前玩家名稱
    string getCurrentPlayerName() const {
        return players[currentPlayerIndex];
    }

    // 顯示遊戲棋盤
    void displayBoard() const {
        // 打印列号
        cout << "   ";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            cout << "" << col << "   ";
        }
        cout << endl;

        // 打印行号和棋盘内容
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << i << " "; // 打印行号

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

    // 玩家進行移動
    bool makeMove(int row, int col, Player currentPlayer) {
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != Player::NONE) {
            // 無效移動
            cout << "Invalid move, please choose a different position." << endl;
            return false;
        }

        // 更新棋盤
        board[row][col] = currentPlayer;

        return true;
    }

    // 檢查是否有玩家獲勝
    bool checkWin(Player currentPlayer) const {
        // 檢查行和列
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
                return true; // 檢查行
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
                return true; // 檢查列
        }

        // 檢查對角線
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
            return true;
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
            return true;

        return false;
    }

    // 檢查是否平局
    bool checkDraw() const {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                if (cell == Player::NONE)
                    return false; // 存在空格，遊戲繼續
            }
        }
        return true; // 所有格子都滿了，平局
    }

    // 抽籤選擇下一位玩家
    void drawNextPlayer() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
    size_t getPlayer1Wins() const {
        return player1Wins;
    }
    // 獲取玩家2贏得的回合數
    size_t getPlayer2Wins() const {
        return player2Wins;
    }
    // 顯示整體結果
    void displayOverallResults() const {
        cout << "Overall Results:" << endl;
        cout << players[0] << " (Player 1) wins: " << getPlayer1Wins() << " rounds" << endl;
        cout << players[1] << " (Player 2) wins: " << getPlayer2Wins() << " rounds" << endl;
    }
    // 重置棋盤
    void resetBoard() {
        board = vector<vector<Player>>(BOARD_SIZE, vector<Player>(BOARD_SIZE, Player::NONE));
        currentPlayerIndex = 0;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    TicTacToe game;

    // 新增玩家
    string playerName1, playerName2;
    cout << "Enter Player 1's name: ";
    cin >> playerName1;
    game.addPlayer(playerName1);

    cout << "Enter Player 2's name: ";
    cin >> playerName2;
    game.addPlayer(playerName2);
    cout << endl;

    bool playAgain = true;

    while (playAgain) {
        game.resetBoard();  // 重置棋盤
        Player currentPlayer = (rand() % 2 == 0) ? Player::PLAYER1 : Player::PLAYER2;  // 隨機決定先手玩家
        cout << (currentPlayer == Player::PLAYER1 ? playerName1 : playerName2) << " goes first!" << endl;
        cout << endl;
        bool gameIsOver = false;  // 新增變數來標記遊戲是否已經結束

        while (!gameIsOver) {
            // 顯示當前狀態
            game.displayBoard();

            // 玩家輸入
            int row, col;
            cout << "It's " << (currentPlayer == Player::PLAYER1 ? playerName1 : playerName2) << " turn, please enter (row,col): ";
            cin >> row >> col;
            cout << endl;


            // 玩家進行移動，直到有效移動為止
            while (!game.makeMove(row, col, currentPlayer)) {
                //cout << "Invalid move, please choose a different position." << endl;
                cout << "Please enter (row, col): ";
                cin >> row >> col;
            }

            // 檢查是否獲勝
            if (game.checkWin(currentPlayer)) {
                game.displayBoard();
                cout << (currentPlayer == Player::PLAYER1 ? playerName1 : playerName2) << " You win! Game Over." << endl;
                gameIsOver = true;
                break;
            }

            // 檢查是否平局
            if (game.checkDraw()) {
                game.displayBoard();
                cout << "It's a tie!" << endl;
                gameIsOver = true;
                break;
            }

            // 抽籤選擇下一位玩家
            game.drawNextPlayer();
            currentPlayer = (currentPlayer == Player::PLAYER1) ? Player::PLAYER2 : Player::PLAYER1;
        }
         // 問詢是否進行下一輪
        char response;
        cout << "Do you want to play again? (y/n): ";
        cin >> response;

        if (response != 'y' && response != 'Y')
            playAgain = false;

    }
    cout << "Goodbye!" << endl;
    return 0;
}
