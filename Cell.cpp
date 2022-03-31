#include "Cell.h"

Figure::Figure(const std::string& color): color_(color){};

void Figure::Clear(){
    color_ = "empty";
    have_to_eat_ = false;
    is_damn_ = false;
}

Cell::Cell(int line_, int column_, const std::string& color) : figure_(color){
    pos_ = Position(line_, column_);
    connected_cells_ = pos_.ConnectedCells();
}

void Cell::UpdateWhite(){
    figure_.have_to_eat_ = false;
    for (auto& it: connected_cells_){
        Cell* another = &(*field_)[it.index_];
        if ((*another).figure_.color_ != "empty"){
            continue;
        }
        if ((*field_)[GetMiddleCell(pos_, (*another).pos_).index_].figure_.color_ != "black"){
            continue;
        }
        if (!figure_.is_damn_ && pos_.line_ > it.line_){
            continue;
        }
        figure_.have_to_eat_ = true;
    }
}


void Cell::UpdateAnother(){
    eages_front_.clear();
    eages_back_.clear();
    for (auto& it: connected_cells_){
        Cell* another = &(*field_)[it.index_];
        if ((*another).figure_.color_ != "empty"){
            continue;
        }
        if ((*field_)[GetMiddleCell(pos_, (*another).pos_).index_].figure_.color_ != "white"){
            continue;
        }
        if (pos_.index_ < it.index_){
            eages_front_.insert(it);
        }
        eages_back_.insert(it);
    }
}

void Cell::Update(){
    if (figure_.color_ == "white"){
        UpdateWhite();
        return;
    }
    UpdateAnother();
}