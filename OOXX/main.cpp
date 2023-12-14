#include <iostream>
#include <vector>

using namespace std;

// 定義遊戲棋盤大小
const int BOARD_SIZE = 3;

// 定義玩家類型
enum class Player { NONE, X, O };

// 定義遊戲類
class TicTacToe {
private:
    vector<vector<Player>> board; // 遊戲棋盤

public:
    TicTacToe() : board(BOARD_SIZE, vector<Player>(BOARD_SIZE, Player::NONE)) {}

    // 顯示遊戲棋盤
    void displayBoard() const {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                switch (board[i][j]) {
                    case Player::X:
                        cout << " X ";
                        break;
                    case Player::O:
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
                cout << "-----------" << endl;
            }
        }
        cout << endl;
    }

    // 玩家進行移動
    bool makeMove(int row, int col, Player currentPlayer) {
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != Player::NONE) {
            // 無效移動
            cout << "無效的移動，請重新選擇位置。" << endl;
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
};

int main() {
    TicTacToe game;
    Player currentPlayer = Player::X;

    while (true) {
        // 顯示當前狀態
        game.displayBoard();

        // 玩家輸入
        int row, col;
        cout << "輪到 " << (currentPlayer == Player::X ? "X" : "O") << " 輸入位置 (行 列): ";
        cin >> row >> col;

        // 玩家進行移動，直到有效移動為止
        while (!game.makeMove(row, col, currentPlayer)) {
            cout << "輸入無效，請重新輸入位置 (行 列): ";
            cin >> row >> col;
        }

        // 檢查是否獲勝
        if (game.checkWin(currentPlayer)) {
            game.displayBoard();
            cout << (currentPlayer == Player::X ? "X" : "O") << " 獲勝！遊戲結束。" << endl;
            break;
        }

        // 檢查是否平局
        if (game.checkDraw()) {
            game.displayBoard();
            cout << "遊戲平局！" << endl;
            break;
        }

        // 切換玩家
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    return 0;
}
