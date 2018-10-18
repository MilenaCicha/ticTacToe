#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>



struct TableStruct{

    unsigned tableSize;
    int maxMoves;
    int getMaxMoves() {return tableSize * tableSize;};
    char** table ;
    char** fillTable();
};

char** TableStruct::fillTable(){
    table = new char*[tableSize];
    for (int i=0; i<tableSize; ++i)
        table[i] = new char[tableSize+1];

    for(int rows = 0; rows < tableSize; ++rows){
        for(int cols = 0; cols < tableSize; ++cols){
            table[rows][cols]= ' ';

        }
        table[rows][tableSize] = '\0';
    }

    return table;
}



void showFieldNumbers(int tableSize)
{
    int counter{1};
    for (int i=1; i<=tableSize; ++i)
    {
        if(counter < 10)
            std::cout<<"  "<<counter;
        else
            std::cout <<" "<< counter;
        counter++;

        for (int j=2; j<=tableSize; ++j)
        {
            std::cout <<std::right<< std::setw(4) << counter;
            counter++;
        }
        std::cout << std::endl;
    }
}


void showTable(TableStruct &gameTable){

    for (int rows = 0; rows < gameTable.tableSize; ++rows){
        for(int cols = 0; cols < gameTable.tableSize-1; ++cols){
            std::cout<<" "<<gameTable.table[rows][cols]<<" |";
        }
        std::cout<<" "<<gameTable.table[rows][gameTable.tableSize-1]<<std::endl;
        if(rows < gameTable.tableSize - 1)
            std::cout<< std::string(4*gameTable.tableSize-1,'-')<<"\n";
    }
}

int userPrompt(int tableSize){
    int field;
    do {
        std::cin.clear();
        std::cin.ignore(100,'\n');
        std::cout << "Podaj liczbe od 1 do "<<(tableSize*tableSize)<<"\n";
        showFieldNumbers(tableSize);
    }while (!(std::cin >> field) or field-1 > tableSize*tableSize);
    return field;
}

void move(char letter, TableStruct &gameTable){

    int field = userPrompt(gameTable.tableSize);
    field = field - 1;

    while(gameTable.table[field/gameTable.tableSize][field%gameTable.tableSize] == 'X' or
          gameTable.table[field/gameTable.tableSize][field%gameTable.tableSize] == 'O')
    {
        std::cout<<"Nieprawidlowy ruch. Podaj numer pola na ktorym nie ma zadnego znaku\n";
        field=userPrompt(gameTable.tableSize);
        field = field - 1;
    }

    gameTable.table[field/gameTable.tableSize][field%gameTable.tableSize] = letter;

}

bool winningConditions(char playerLetter, TableStruct &gameTable){

    //SPRAWDZA WARUNKI -->
    for(int row = 0; row <gameTable.tableSize;++row){
        bool allInRowPlayerLetter = gameTable.table[row][0] == playerLetter;
        for(int col = 1; col < gameTable.tableSize && allInRowPlayerLetter; ++col){
            allInRowPlayerLetter = gameTable.table[row][col] == playerLetter;
        }
        if (allInRowPlayerLetter)
            return true;
    }

    //                 ^
    //SPRAWDZA WARUNKI |
    //                 |
    for(int col = 0; col <gameTable.tableSize;++col){
        bool allInColPlayerLetter = gameTable.table[0][col] == playerLetter;
        for(int row = 1; row < gameTable.tableSize && allInColPlayerLetter; ++row){
            allInColPlayerLetter = gameTable.table[row][col] == playerLetter;
        }
        if (allInColPlayerLetter)
            return true;
    }

    //SPRAWDZA SKOSY
    bool allInCrossPlayerLetter = gameTable.table[0][0]== playerLetter;
    for(int indeks = 1; indeks < gameTable.tableSize && allInCrossPlayerLetter; ++indeks)
    {
        allInCrossPlayerLetter = gameTable.table[indeks][indeks]== playerLetter;
    }
    if(allInCrossPlayerLetter)
        return true;

    allInCrossPlayerLetter = gameTable.table[0][gameTable.tableSize-1]== playerLetter;
    for(int row = 1, col = gameTable.tableSize-2; row < gameTable.tableSize && allInCrossPlayerLetter; ++row, --col ){
        allInCrossPlayerLetter = gameTable.table[row][col] == playerLetter;
    }

    return allInCrossPlayerLetter;

}
void game(TableStruct &gameTable,char player1Letter, char player2Letter,int maxMoves){

    for (int i = 1; i <= maxMoves; ++i) {
        if (i % 2 == 1){
            std::cout<<std::endl;
            std::cout<<"Tura Gracza 1\n";
            move(player1Letter, gameTable);
        }
        else{
            std::cout<<std::endl;
            std::cout<<"Tura Gracza 2\n";
            move(player2Letter, gameTable);
        }

        showTable(gameTable);


        if(winningConditions(player1Letter, gameTable)) {
            std::cout << "Wygrywa " << player1Letter << "!\n";
            return;
        }
        if(winningConditions(player2Letter, gameTable)) {
            std::cout << "Wygrywa " << player2Letter << "!\n";
            return;
        }

    }
    if(!winningConditions(player1Letter,gameTable) && !winningConditions(player2Letter,gameTable))
        std::cout<<"Remis!\n";

}
int main(){


    TableStruct gameTable;

    char continueGame = 'Y';
    char player1Letter;
    char player2letter;

    std::cout<<"     ------------------------------------------\n";
    std::cout<<"\t"<<"Witaj w grze w kolko i krzyzyk.\t\n";
    std::cout<<"     ------------------------------------------\n";

    std::cout<<"Podaj rozmiar tablicy, jesli chcesz podac rozmiar np 3 x 3 wpisz 3, jesli 4 x 4, podaj 4, itd.\n";
    std::cin>>gameTable.tableSize;
    gameTable.maxMoves = gameTable.getMaxMoves();

    do {
        gameTable.fillTable();
        do {
            std::cout << "Wybiera Gracz 1. O czy X?\n";
            std::cin >> player1Letter;
            player1Letter = char(toupper(player1Letter));
        } while (player1Letter != 'X' and player1Letter != 'O');

        if (player1Letter == 'X') {
            std::cout << "Wybrales X. Gracz 2 gra O.\n";
            player2letter = 'O';
        } else if (player1Letter == 'O') {
            std::cout << "Wybrales O. Gracz 2 gra X.\n";
            player2letter = 'X';
        }

        game(gameTable,player1Letter,player2letter,gameTable.maxMoves);
        std::cout << "Czy chcesz zagrac ponownie? Y/N\n";
        std::cin >> continueGame;
        continueGame = toupper(continueGame);


    }while(continueGame == 'Y');

    for(int row = 0; row < gameTable.tableSize; ++row){
        delete[] gameTable.table[row];
    }
    delete gameTable.table;

    std::cout<<"Dziekuje za gre!\n";



}
