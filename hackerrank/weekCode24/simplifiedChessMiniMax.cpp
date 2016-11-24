#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cstring>
using namespace std;

const int NMAX = 4;
const int INF = 0x3f3f3f3f;

int Q, W, B, M;

struct Direction {
    int dx, dy;
};

enum PieceType {
    QUEEN, ROOK, BISHOP, KNIGHT
};

vector<Direction> QUEEN_DIRS {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
vector<Direction> ROOK_DIRS {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
vector<Direction> BISHOP_DIRS {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
vector<Direction> KNIGHT_DIRS {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

struct Piece {
    bool isWhite;

    Piece(bool _isWhite) : isWhite(_isWhite) {}

    virtual vector<Direction> getDirections() = 0;

    virtual PieceType getType() = 0;

    virtual int maxMovesInDirection() {
        return INF;
    }

    virtual ~Piece() {}
};

struct Queen : public Piece {
    Queen(bool isWhite) : Piece(isWhite) { }

    vector<Direction> getDirections() {
        return QUEEN_DIRS;
    }

    PieceType getType() {
        return QUEEN;
    }
};

struct Rook : public Piece {
    Rook(bool isWhite) : Piece(isWhite) { }

    vector<Direction> getDirections() {
        return ROOK_DIRS;
    }

    PieceType getType() {
        return ROOK;
    }
};

struct Bishop : public Piece {
    Bishop(bool isWhite) : Piece(isWhite) {}

    vector<Direction> getDirections() {
        return BISHOP_DIRS;
    }

    PieceType getType() {
        return BISHOP;
    }
};

struct Knight : public Piece {
    Knight(bool isWhite) : Piece(isWhite) {}

    vector<Direction> getDirections() {
        return KNIGHT_DIRS;
    }

    PieceType getType() {
        return KNIGHT;
    }

    int maxMovesInDirection() {
        return 1;
    }
};

struct PiecePosition {
    Piece* piece;
    int row, col;

    PiecePosition(Piece* _piece, int _row, int _col) {
        piece = _piece;
        row = _row;
        col = _col;
    }
};

Piece* getPiece(char pieceType, bool isWhite) {
    switch (pieceType) {
        case 'Q':
            return new Queen(isWhite);
        case 'N':
            return new Knight(isWhite);
        case 'B':
            return new Bishop(isWhite);
        case 'R':
            return new Rook(isWhite);
    }

    return NULL;
}

enum WinState {
    BLACK_WON, NO_WINNER, WHITE_WON
};

struct Board {
    Piece* board[NMAX][NMAX];

    Board(vector<PiecePosition>& pieces) {
        memset(board, 0, sizeof(board));
        for (auto& pieceEntry: pieces) {
            board[pieceEntry.row][pieceEntry.col] = pieceEntry.piece;
        }
    }

    Board(Piece* otherBoard[NMAX][NMAX], int rowFrom, int colFrom, int rowTo, int colTo) {
        memcpy(board, otherBoard, sizeof(board));
        board[rowFrom][colFrom] = 0;
        board[rowTo][colTo] = otherBoard[rowFrom][colFrom];
    }

    ~Board() {
        for (int r = 0; r < NMAX; r++) {
            for (int c = 0; c < NMAX; c++) {
                if (board[r][c]) {
                    delete board[r][c];
                }
            }
        }
    }

    WinState currState() {
        bool whiteQueenExists = false, blackQueenExists = false;
        for (int r = 0; r < NMAX; r++) {
            for (int c = 0; c < NMAX; c++) {
                if (board[r][c] && board[r][c] -> getType() == QUEEN) {
                    whiteQueenExists |= board[r][c] -> isWhite;
                    blackQueenExists |= !(board[r][c] -> isWhite);
                }
            }
        }

        if (!whiteQueenExists) {
            return BLACK_WON;
        } else if (!blackQueenExists) {
            return WHITE_WON;
        }
        return NO_WINNER;
    }

    inline bool validPos(int r, int c) {
        return validPos(r) && validPos(c);
    }

    inline bool validPos(int coord) {
        return 0 <= coord && coord < NMAX;
    }

    void getPossibleMoves(vector<Board*>& moves, bool isWhiteTurn) {
        for (int r = 0; r < NMAX; r++) {
            for (int c = 0; c < NMAX; c++) {
                if (board[r][c] && board[r][c] -> isWhite == isWhiteTurn) {
                    int currR, currC, remMoves;
                    for (auto& dir: board[r][c] -> getDirections()) {
                        currR = r + dir.dx, currC = c + dir.dy, remMoves = board[r][c] -> maxMovesInDirection();
                        while (remMoves && validPos(currR, currC)) {
                            // check if piece already exists there
                            if (board[currR][currC]) {
                                // check if piece is not of the same type
                                if (board[currR][currC] -> isWhite != isWhiteTurn) {
                                    moves.push_back(new Board(board, r, c, currR, currC));
                                }
                                break ;
                            }
                            moves.push_back(new Board(board, r, c, currR, currC));

                            remMoves--; currR += dir.dx; currC += dir.dy;
                        }
                    }
                }
            }
        }
    }
};

Board* initialBoard;

WinState minimax(Board* currNode, int depth, bool isWhiteTurn) {
    WinState currState = currNode -> currState();
    // no more moves or terminal node
    if (!depth || currState != NO_WINNER) {
        return currState;
    }

    vector<Board*> possibleMoves;
    // populate array of moves
    currNode -> getPossibleMoves(possibleMoves, isWhiteTurn);
    if (isWhiteTurn) {
        WinState bestValue = BLACK_WON;
        for (auto& move: possibleMoves) {
            WinState candValue = minimax(move, depth - 1, false);
            bestValue = max(bestValue, candValue);
        }

        return bestValue;
    }

    WinState bestValue = WHITE_WON;
    for (auto& move: possibleMoves) {
        WinState candValue = minimax(move, depth - 1, true);
        bestValue = min(bestValue, candValue);
    }

    return bestValue;
}

void read() {
    scanf("%d%d%d\n", &W, &B, &M);
    char pieceType, col;
    int row;

    vector<PiecePosition> pieces; 
    for (int i = 1; i <= W; i++) {
        scanf("%c %c %d\n", &pieceType, &col, &row);
        pieces.push_back(PiecePosition(getPiece(pieceType, true), row - 1, col - 'A'));
    }
    for (int i = 1; i <= B; i++) {
        scanf("%c %c %d\n", &pieceType, &col, &row);
        pieces.push_back(PiecePosition(getPiece(pieceType, false), row - 1, col - 'A'));
    }

    initialBoard = new Board(pieces);
    /*for (auto& pieceEntry: pieces) {
        printf("%d %d -> colour: %d, type: %d\n", pieceEntry.row, pieceEntry.col, pieceEntry.piece -> isWhite,
            pieceEntry.piece -> getType());
    }*/
}

int main() {
    freopen("simplifiedChess.in", "r", stdin);

    scanf("%d\n", &Q);
    while (Q--) {
        read();
        M -= 1 - (M & 1);
        WinState result = minimax(initialBoard, M, true);
        if (result == WHITE_WON) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
