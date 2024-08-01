#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

namespace MATRIX {

enum class Type { King, Queen, Rook, Bishop, Knight, Pawn };

class Chess_piece {
public:
    Chess_piece(Type type = Type::Pawn) : type(type) {}

    friend std::ostream& operator<<(std::ostream& os, const Chess_piece& piece) {
        switch (piece.type) {
            case Type::King: os << "K"; break;
            case Type::Queen: os << "Q"; break;
            case Type::Rook: os << "R"; break;
            case Type::Bishop: os << "B"; break;
            case Type::Knight: os << "N"; break;
            case Type::Pawn: os << "P"; break;
            default: os << "-";
        }
        return os;
    }

private:
    Type type;
}; // class Chess_piece
} // namespace MATRIX
#endif