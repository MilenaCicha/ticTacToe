#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>


constexpr int tableSize{3};
char player1letter;
char player2letter;


void showTable(char table[tableSize][tableSize]){

    for (int i = 0; i < tableSize; ++i){
        for(int j =0; j < tableSize; ++j){
            std::cout<<table[i][j]<<" ";
        }
        std::cout<<std::endl;

    }
}


void move(int letter, char table[tableSize][tableSize]){


        int field;
        std::cout<<"Podaj numer od 1 do 9, gdzie chcesz umiescic swoj znak\n";
        std::cin>>field;
        field = field - 1;


        while(table[field/3][field%3] == 'X' or table[field/3][field%3] == 'O'){
            std::cout<<"Nieprawidlowy ruch. Podaj numer pola na ktorym nie ma zadnego znaku\n";
            std::cin>>field;
            field = field - 1;
        }
        if(table[field/3][field%3] != 'X' and table[field/3][field%3] != 'O'){

        table[field/3][field%3] = letter;
    }

}

char winningConditions(char table[tableSize][tableSize]){
    if(table[0][0] == player1letter and table[0][1] == player1letter and table[0][2] == player1letter)
        return player1letter;
    if(table[1][0] == player1letter and table[1][1] == player1letter and table[1][2] == player1letter)
        return player1letter;
    if(table[2][0] == player1letter and table[2][1] == player1letter and table[2][2] == player1letter)
        return player1letter;
    if(table[0][0] == player1letter and table[1][0] == player1letter and table[2][0] == player1letter)
        return player1letter;
    if(table[0][1] == player1letter and table[1][1] == player1letter and table[2][1] == player1letter)
        return player1letter;
    if(table[0][2] == player1letter and table[1][2] == player1letter and table[2][2] == player1letter)
        return player1letter;
    if(table[0][0] == player1letter and table[1][1] == player1letter and table[2][2] == player1letter)
        return player1letter;
    if(table[0][2] == player1letter and table[1][1] == player1letter and table[2][0] == player1letter)
        return player1letter;

    if(table[0][0] == player2letter and table[0][1] == player2letter and table[0][2] == player2letter)
        return player2letter;
    if(table[1][0] == player2letter and table[1][1] == player2letter and table[1][2] == player2letter)
        return player2letter;
    if(table[2][0] == player2letter and table[2][1] == player2letter and table[2][2] == player2letter)
        return player2letter;
    if(table[0][0] == player2letter and table[1][0] == player2letter and table[2][0] == player2letter)
        return player2letter;
    if(table[0][1] == player2letter and table[1][1] == player2letter and table[2][1] == player2letter)
        return player2letter;
    if(table[0][2] == player2letter and table[1][2] == player2letter and table[2][2] == player2letter)
        return player2letter;
    if(table[0][0] == player2letter and table[1][1] == player2letter and table[2][2] == player2letter)
        return player2letter;
    if(table[0][2] == player2letter and table[1][1] == player2letter and table[2][0] == player2letter)
        return player2letter;
    else
        return '=';

}
void game(char table[tableSize][tableSize]){
    int maxMoves = 9;

    for (int i = 1; i <= maxMoves; ++i) {
        if(winningConditions(table) == player1letter) {
            std::cout << "Wygrywa " << player1letter << "!\n";
            break;
        }
        if(winningConditions(table) == player2letter) {
            std::cout << "Wygrywa " << player2letter << "!\n";
            break;
        }
        showTable(table);
        if (i % 2 == 1){
            std::cout<<std::endl;
            std::cout<<"Tura Gracza 1\n";
            move(player1letter, table);
        }
        else{
            std::cout<<std::endl;
            std::cout<<"Tura Gracza 2\n";
            move(player2letter, table);
        }

    }
    if(winningConditions(table) == '=')
        std::cout<<"remis\n";

}
int main(){
    char table[tableSize][tableSize] = {'1','2','3','4','5','6','7','8','9'};
    char continueGame = 'Y';
    std::cout<<"     ------------------------------------------\n";
    std::cout<<"\t"<<"Witaj w grze w kolko i krzyzyk.\t\n";
    std::cout<<"     ------------------------------------------\n";

    while(continueGame == 'Y') {

        do {
            std::cout << "Wybiera Gracz 1. O czy X?\n";
            std::cin >> player1letter;
            player1letter = char(toupper(player1letter));
        } while (player1letter != 'X' and player1letter != 'O');

        if (player1letter == 'X') {
            std::cout << "Wybrales X. Gracz 2 gra O.\n";
            player2letter = 'O';
        } else if (player1letter == 'O') {
            std::cout << "Wybrales O. Gracz 2 gra X.\n";
            player2letter = 'X';
        }

        game(table);
        std::cout<<"Czy chcesz zagrac ponownie? Y/N\n";
        std::cin>> continueGame;
        continueGame = toupper(continueGame);




    }
    std::cout<<"Dziekuje za gre!\n";



    }
















