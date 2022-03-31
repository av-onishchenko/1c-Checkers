#include "Positions.h"

Position::Position(int line, int column): line_(line), column_(column){
    index_ = line*8 + column;
}

std::set<Position> Position::ConnectedCells() {
    std::set<Position> result;

    if (line_ > 1 && column_ > 1){
        result.insert(Position(line_ - 2, column_ - 2));
    }
    if (line_ > 1 && column_ < 6){
        result.insert(Position(line_ - 2, column_ + 2));
    }
    if (line_ < 6 && column_ > 1){
        result.insert(Position(line_ + 2, column_ - 2));
    }
    if (line_ < 6 && column_ < 1){
        result.insert(Position(line_ + 2, column_ + 2));
    }
    return result;
}


Position GetCell(const std::string &num) {
    return Position((num[0] - 65),  + num[1] - 1);
}

Position GetMiddleCell(const Position& from, const Position& to) {
    return Position((from.line_ + to.line_) / 2,(from.column_ + to.column_) / 2);
}
