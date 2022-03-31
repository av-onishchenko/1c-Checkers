#include "Checkers.h"

Checkers::Checkers(int level): level_(level){
    field_.resize(64);
    int current = 0;
    for (int i = 0; i < 16; ++i){
        field_[i] = Cell(current/8, current%8, "white");
        current += 2;
    }
    current = 40;
    for (int i = 0; i < 16; ++i){
        field_[i] = Cell(current/8, current%8, "black");
        current += 2;
    }
}

std::string Checkers::PlayerMove(const std::string &from, const std::string &to) {
    Position from_cell = GetCell(from);
    Position to_cell = GetCell(to);
    MoveResult result = WhiteMove(from_cell, to_cell);
    switch (result) {
        case incorrect : return "Your move is incorrect! Please, try again";
        case completed : return "Your move is completed. Now it's my tern";
        case one_more : return "Your have to make one more move";
        case win : return "You are wining! Congratulations!";
    }
}

std::string GetStep(const Position& position){
    char first_symbol = char(position.line_ + 65);
    return first_symbol + std::to_string(position.column_);
}


std::string Checkers::MyMove() {
    ResultWay max_way(-1);
    int position = -1;
    for (int i = 0; i < field_.size(); ++i){
        if (field_[i].figure_.color_ != "black"){
            continue;
        }
        ResultWay current_max = MaxWay(field_[i].figure_.is_damn_, i, -1);
        if (current_max.len_ > max_way.len_){
            max_way = current_max;
            position = i;
        }
    }
    if (max_way.len_ == -1){
        return "You are wining! Congratulations!";
    }
    MakeMyMove(max_way.way_);
    return GetStep(field_[position].pos_);
}

std::string Checkers::CurrentScore() const {
    return "Current score is: white - " + std::to_string(white_score_) + ", black - " +
    std::to_string(black_score_);
}

bool Checkers::HaveToEat(const std::string& color){
    for (int i = 0; i < field_.size(); ++i){
        if (field_[i].figure_.color_ == color && field_[i].figure_.have_to_eat_){
            return true;
        }
    }
    return false;
}


void Checkers::UpdateCells(const std::set<Position>& cells){
    for (auto it: cells){
        field_[it.index_].Update();
    }
}


ResultWay Checkers::MaxWay(bool is_damn, int pos, int parent){
    ResultWay result(0);
    for (auto i: field_[pos].connected_cells_){
        if (i.index_ == parent){
            continue;
        }
        if (!is_damn && i.line_ > field_[pos].pos_.line_){
            continue;
        }
        auto current = MaxWay(is_damn, i.index_, pos);
        if (current.len_ + 1 > result.len_){
           result = current;
        }
    }
    result.way_.push_back(pos);
    return result;
}


void Checkers::Move(const Position& from, const Position& to, bool is_hard){
    std::set<Position> connected_cells;
    field_[from.index_].figure_.color_ = "empty";
    field_[to.index_].figure_.color_ = "white";
    if (to.line_ == 7){
        field_[to.index_].figure_.is_damn_ = true;
    }
    for (auto& it: field_[from.index_].connected_cells_){
        connected_cells.insert(it);
    }
    for (auto& it: field_[to.index_].connected_cells_){
        connected_cells.insert(it);
    }
    if (is_hard){
        Position middle = GetMiddleCell(from, to);
        field_[middle.index_].figure_.color_ = "empty";
        for (auto& it: field_[middle.index_].connected_cells_){
            connected_cells.insert(it);
        }
    }
    UpdateCells(connected_cells);
}

void Checkers::MakeMyMove(const std::vector<int>& way){
    bool is_damn = false;
    for (int i = way.size() - 1; i > 0; --i){
        Position middle = GetMiddleCell(field_[way[i]].pos_, field_[way[i - 1]].pos_);
        ++black_score_;
        field_[middle.index_].figure_.Clear();
        if (field_[way[i-1]].pos_.line_ == 1){
            is_damn = true;
        }
    }
    field_[way[0]].figure_.color_ =  "black";
    field_[way[0]].figure_.is_damn_ |= is_damn;
}

Checkers::MoveResult Checkers::HaveToEatCase(const Position& from, const Position& to) {
    if (abs(from.line_ - to.line_) != 2) {
        return incorrect;
    }
    if (abs(from.column_ - to.column_) != 2) {
        return incorrect;
    }
    ++white_score_;
    if (white_score_ == 16){
        return win;
    }
    Move(from, to, true);
    if (HaveToEat("white")) {
        return one_more;
    }
    return completed;
}

Checkers::MoveResult Checkers::HaveNotEatCase(const Position& from, const Position& to) {
    if (abs(from.line_ - to.line_) != 1) {
        return incorrect;
    }
    Move(from, to, false);
    if (abs(from.column_ - to.column_) != 1) {
        return incorrect;
    }
    return completed;
}

Checkers::MoveResult Checkers::WhiteMove(const Position& from, const Position& to) {
    if (field_[from.index_].figure_.color_ != "white" || field_[to.index_].figure_.color_ != "empty") {
        return incorrect;
    }
    if (from.line_ == to.line_) {
        return incorrect;
    }
    if (!field_[from.index_].figure_.is_damn_ && from.line_ > to.line_) {
        return incorrect;
    }
    if (HaveToEat("white")) {
        return HaveToEatCase(from, to);
    }
    return HaveNotEatCase(from, to);
}