
#include "GameTable.h"
#include <iostream>
#include <string>

namespace GameTable{

    GameTable::GameTable(unsigned new_tableSize)
    :tableSize{new_tableSize}{
            getMaxMoves();
    }

    GameTable::~GameTable(){
        for(int row = 0; row < returnTableSize(); ++row){
            delete[] table[row];
        }
        delete table;
    }

int GameTable::getMaxMoves(){
    maxMoves=tableSize*tableSize;
    return maxMoves;
}
void GameTable::fillTable(){
    table = new char*[tableSize];
    for (int i=0; i<tableSize; ++i)
        table[i] = new char[tableSize+1];

    for(int rows = 0; rows < tableSize; ++rows){
        for(int cols = 0; cols < tableSize; ++cols){
            table[rows][cols]= ' ';

        }
        table[rows][tableSize] = '\0';
    }

}



void GameTable::showTable(){

    for (int rows = 0; rows < tableSize; ++rows){
        for(int cols = 0; cols < tableSize-1; ++cols){
            std::cout<<" "<<table[rows][cols]<<" |";
        }
        std::cout<<" "<<table[rows][tableSize-1]<<std::endl;
        if(rows < tableSize - 1)
            std::cout<< std::string(4*tableSize-1,'-')<<"\n";
    }
}
bool GameTable::validMove(int& field){

    return table[field/tableSize][field%tableSize] != 'X' and
        table[field/tableSize][field%tableSize] != 'O';
}

bool GameTable::winningConditions(const char& playerLetter){

    //SPRAWDZA WARUNKI -->
    for(int row = 0; row <tableSize;++row){
        bool allInRowPlayerLetter = table[row][0] == playerLetter;
        for(int col = 1; col < tableSize && allInRowPlayerLetter; ++col){
            allInRowPlayerLetter = table[row][col] == playerLetter;
        }
        if (allInRowPlayerLetter)
            return true;
    }

    //                 ^
    //SPRAWDZA WARUNKI |
    //                 |
    for(int col = 0; col <tableSize;++col){
        bool allInColPlayerLetter = table[0][col] == playerLetter;
        for(int row = 1; row < tableSize && allInColPlayerLetter; ++row){
            allInColPlayerLetter = table[row][col] == playerLetter;
        }
        if (allInColPlayerLetter)
            return true;
    }

    //SPRAWDZA SKOSY
    bool allInCrossPlayerLetter = table[0][0]== playerLetter;
    for(int index = 1; index < tableSize && allInCrossPlayerLetter; ++index)
    {
        allInCrossPlayerLetter = table[index][index]== playerLetter;
    }
    if(allInCrossPlayerLetter)
        return true;

    allInCrossPlayerLetter = table[0][tableSize-1]== playerLetter;
    for(int row = 1, col = tableSize-2; row < tableSize && allInCrossPlayerLetter; ++row, --col ){
        allInCrossPlayerLetter = table[row][col] == playerLetter;
    }

    return allInCrossPlayerLetter;

}




}