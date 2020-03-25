#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
using namespace std;

/*
 * Do poniższego zadania (gra w kółko i krzyżyk) dodać następujące możliwości:
 *DONE    1. Uwzględnienie remisu (obecnie w przypadku remisu wygrywa ostatni zagrywający -- obecnie kółko).
 *DONE    2. Wybór znaków do grania (zamiast kółka i krzyżyka -- proszę pamiętać, że nie mogą to być dwa identyczne znaki.
 *DONE    3. Zmienna wielkość planszy (wielkość planszy podawana przed kompilacją, w formie stałej globalnej, a więc: const N=wielkość).
 *DONE   4. Gra jednego użytkownika z komputerem (przynajmniej dla ustalonej planszy 3x3).
 *DONE    5. Dodanie poziomów do gry komputera (1. łatwy (losowy), 2. średni (w pewnym procencie losowy), 3. trudny (optymalny)).
 *DONE    6. Dodać możliwość cofnięcia ruchu.
 */



//Wybór wielkości planszy
static const int gameBoardSize = 3;

static const string alphabet = "abcdefghijklmnopqrstuvwxyz";

char previousMove[gameBoardSize][gameBoardSize];



void copyTab(char t1[gameBoardSize][gameBoardSize], char t2[gameBoardSize][gameBoardSize]){
    for (int i = 0; i < gameBoardSize; i++){
        for (int j = 0; j < gameBoardSize; j++){
            t1[i][j] = t2[i][j];
        }
    }
}

void drawExtremeRow(){
    cout<<" ";
    for (int i = 0; i < gameBoardSize*2 + 5; ++i) {
        cout<<"-";
    }
    cout<< " "<<endl;
}

void drawTable(char t[gameBoardSize][gameBoardSize]){

    //pierwszy rząd poziomy
    drawExtremeRow();

    //rząd z nazwami kolumn
    cout<<"|   ";
    for (int i = 0; i < gameBoardSize; ++i) {
    cout<<alphabet[i] << " ";
    }
    cout<<"  |" << endl;

    //wyświetlenie zawartości tablicy
    for (int i = 0; i < gameBoardSize; ++i) {
        cout<<"| " << i + 1 << " ";
        for (int j = 0; j < gameBoardSize; ++j) {
            cout<<t[i][j] << " ";
        }
        cout<<"  |" << endl;
    }

    //ostatni rząd poziomy
    drawExtremeRow();
}

bool getTab(char t[gameBoardSize][gameBoardSize], int & who, char znak1, char znak2){
    char poz[2];
    if(!(who % 2))
        cout<<"Kolko, ";
    else
        cout<<"Krzyzyk, ";
    do{
        cout<<"Podaj pozycje, ktora zaznaczyc (np. a1): "<<endl;
        cin>>poz;

        //cofanie ruchu
        if(poz[0]=='q') {
            copyTab(t, previousMove);
            return true;
        }
    }while((poz[0]<'a' || poz[0]>(char)alphabet[gameBoardSize]) || (poz[1]<'1' || poz[1]>(char)alphabet[gameBoardSize]));

    if(t[poz[1]-'1'][poz[0]-'a']!=' '){
        cout<< endl <<"Pole "<<poz<<" bylo juz uzupelnione."<<endl;
        return getTab(t, who, znak1, znak2);
    }

    if(!(who++ % 2))
        t[poz[1]-'1'][poz[0]-'a']=znak1;
    else
        t[poz[1]-'1'][poz[0]-'a']=znak2;

    return true;
}

bool putInCorner(char t[gameBoardSize][gameBoardSize]){
    bool moveMade = false;
    if(t[0][0] == 'O'){
        if(t[0][2] == ' ' && t[0][1] == ' '){
            t[0][2] = 'O';
            moveMade = true;
        }else if(t[2][0] == ' ' && t[1][0] == ' '){
            t[2][0] = 'O';
            moveMade = true;
        }
    }else if(t[0][2] == 'O'){
        if(t[0][0] == ' ' && t[0][1] == ' '){
            t[0][0] = 'O';
            moveMade = true;
        }else if(t[2][2] == ' ' && t[1][2] == ' '){
            t[2][2] = 'O';
            moveMade = true;
        }
    }else if(t[2][0] == 'O'){
        if(t[0][0] == ' ' && t[1][0] == ' '){
            t[0][0] = 'O';
            moveMade = true;
        }else if(t[2][2] == ' ' && t[2][1] == ' '){
            t[2][2] = 'O';
            moveMade = true;
        }
    }else if(t[2][2] == 'O'){
        if(t[0][2] == ' ' && t[1][2] == ' '){
            t[0][2] = 'O';
            moveMade = true;
        }else if(t[2][0] == ' ' && t[2][1] == ' '){
            t[2][0] = 'O';
            moveMade = true;
        }
    }else if(t[0][0] == 'X' && t[2][0] == 'X' && t[0][2] == 'X' && t[2][2] == 'X'){
        moveMade = false;
    }else{
        while(!moveMade){
            int random = rand() % 4 + 1;
            if(random == 1 && t[0][0] == ' '){
                t[0][0] = 'O';
                moveMade = true;
            }else if(random == 2 && t[0][2] == ' '){
                t[0][gameBoardSize - 1] = 'O';
                moveMade = true;
            }else if(random == 3 && t[2][0] == ' '){
                t[2][0] = 'O';
                moveMade = true;
            }else if(random == 4 && t[2][2] == ' '){
                t[2][2] = 'O';
                moveMade = true;
            }
        }
    }
    return moveMade;
}

bool checkGameBoard(char t[gameBoardSize][gameBoardSize]){
    char cross = 'X', circle = 'O';
    int blank = 0;
    for (int i = 0; i < gameBoardSize; ++i) {
        int verticalCross = 0, horizontalCross = 0, diagonalCross = 0;
        int verticalCircle = 0, horizontalCircle = 0, diagonalCircle = 0;
        for (int j = 0; j < gameBoardSize; ++j) {
            if(t[i][j] == cross){
                horizontalCross++;
            }else if(t[i][j] == circle){
                horizontalCircle++;
            }else{
                blank++;
            }

            if(t[j][i] == cross){
                verticalCross++;
            }else if(t[j][i] == circle){
                verticalCircle++;
            }else{
                blank++;
            }
        }
        if(t[i][i] == cross){
            diagonalCross++;
        }else if(t[i][i] == circle) {
            diagonalCircle++;
        }else{
            blank++;
        }


        if(verticalCircle == 3 || horizontalCircle == 3 || diagonalCircle == 3) {
            cout << "Zwyciezca: " << cross << endl;
            return true;
        }else if(verticalCross == 3 || horizontalCross == 3 || diagonalCross == 3){
            cout << "Zwyciezca: " << cross << endl;
        }
    }
    if(blank == 0){
        cout << "Remis. Plansza jest juz pelna" << endl;
        return true;
    }

    return false;
}

bool tryToFinish(char t[gameBoardSize][gameBoardSize], char character){
    int vertical = 0, horizontal = 0, diagonal = 0;
    int blankVertical = 0, blankHorizontal = 0, blankDiagonal = 0;
    int blankVerticalPoz = 0, blankHorizontalPoz = 0, blankDiagonalPoz = 0;
    for (int i = 0; i < gameBoardSize; ++i) {
        for (int j = 0; j < gameBoardSize; ++j) {
            if(t[i][j] == character){
                horizontal++;
            }else if(t[i][j] == ' '){
                blankHorizontal++;
                blankHorizontalPoz = j;
            }

            if(t[j][i] == character){
                vertical++;
            }else if(t[j][i] == character){
                blankVertical++;
                blankVerticalPoz = j;
            }
        }
        if(t[i][i] == character){
            diagonal++;
        }else if(t[i][i] == ' ') {
            blankDiagonal++;
            blankDiagonalPoz = i;
        }


        if(vertical == 2 && blankVertical == 1){
            t[blankVerticalPoz][i] = 'O';
            return true;
        }else if(horizontal == 2 && blankHorizontal == 1){
            t[i][blankHorizontalPoz] = 'O';
            return true;
        }else if(diagonal == 2 && blankDiagonal == 1){
            t[blankDiagonalPoz][blankDiagonalPoz] = 'O';
            return true;
        }

        vertical = 0;
        blankVertical = 0;
        horizontal = 0;
        blankHorizontal = 0;
    }

    return false;
}

void randomMoves(char t[gameBoardSize][gameBoardSize]) {
    bool moveMade = false;
    while(!moveMade){
        int randomX = rand() % gameBoardSize;
        int randomY = rand() % gameBoardSize;

        if(t[randomY][randomX] == ' '){
            t[randomY][randomX] = 'O';
            moveMade = true;
        }
    }

}

void AdvancedAI(char t[gameBoardSize][gameBoardSize], int move){
        if(move < 3){
            putInCorner(t);
        }else{
            if(!tryToFinish(t, 'O'))
                if(!tryToFinish(t, 'X'))
                    if(!putInCorner(t))
                        randomMoves(t);
        }
}

int main(){
    srand(time(NULL));

    char tab[gameBoardSize][gameBoardSize];
    for(int i=0; i<gameBoardSize; i++) for(int j=0; j<gameBoardSize; tab[i][j++]=' ');
    copyTab(previousMove, tab);
    int who = 0;
    int move = 1;
    bool end = false;

    bool singlePlayer = true;
    int difficultyLevel = 0;

    int temp = 0;

    cout << "Wybierz model rozgrywki" << endl;
    cout << "Jeden gracz (1)" << endl;
    cout << "Dwoch graczy (2)" << endl;
    do {
        cout << "Wybor: ";
        cin >> temp;
        if(temp == 1){
            singlePlayer = true;
        }else if(temp == 2){
            singlePlayer = false;
        }
    }while(temp != 1 && temp != 2);

    if(singlePlayer){
        cout << "Wybierz poziom trudnosci: ";
        cin >> difficultyLevel;
    }

    temp = 0;
    int i = 0;
    while(!end) {
        if(singlePlayer){
            if (i % 2 == 0) {
                copyTab(previousMove, tab);
                if (difficultyLevel == 0) {
                    randomMoves(tab);
                } else if (difficultyLevel == 1) {
                    if(temp%2 == 0) {
                        randomMoves(tab);
                    }else {
                        AdvancedAI(tab, move);
                    }
                    temp++;
                } else if (difficultyLevel == 2) {
                    AdvancedAI(tab, move);
                }
                move++;
                who += 1;

                drawTable(tab);
                if(checkGameBoard(tab)) break;
            }
            i++;
        }
        if(singlePlayer){
            if(i%2 == 1){
                //Mozliwość wyboru znaków do gry
                getTab(tab, who, 'O', 'X');
                if(singlePlayer){
                    drawTable(tab);
                    cout << "Ruch komputera (nacisnij dowolny klawisz aby kontynuowac)";
                    getch();
                }
                if(checkGameBoard(tab)) break;
            }
            i++;
        }else{
            getTab(tab, who, 'O', 'X');
            drawTable(tab);
            if(checkGameBoard(tab)) break;
        }
    }
    drawTable(tab);
    return 0;
}