

#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <thread>
#include <chrono>


using namespace std;

bool assertop(char);
vector<int> _showmove(char, char, char[3][3]);
void play(char,char,  char[3][3], bool&);
bool _putSymbol(char, char[3][3], vector<int>, char bot);
bool botAi(char, char[3][3], vector<int>, char player);
void displayMatrix(char[3][3]);
bool _iswin(bool&, char[3][3], char , char);

int main()
{
    char tab[3][3] = {
    {'#', '#', '#'},
    {'#', '#', '#'},
    {'#', '#', '#'}
    };


    char player;
    char bot;
    bool isplay = true;


    do {
        cout << "che segno vuoi? X o O\n";
        cin >> player;
    } while (assertop(player));

    

    player == 'X' ? bot = 'O' : bot = 'X';

    while (isplay) {
        play(player, bot, tab, isplay);
        displayMatrix(tab);
        
    }

    return 0;
}

bool assertop(char player) {
    if (player != 'X' && player != 'O') {
        return true;
    }
    else {
        return false;
    }
}

vector<int>  _showmove(char player, char bot, char chart[3][3]) {
    int index = 0;
    int move1;
    int move2;
    cout << "dove vuoi posizionare il tuo " <<  player;
    cout << "\n";
    
    for(int i = 0; i < 3; i++) {
        
        for (int j = 0; j < 3; j++) {
            index++;
            if (chart[i][j] != '#') {
                continue;
            }
            else {
                cout << index << " ";
                cout << i;
                cout << " : ";
                cout << j;
                cout << "\n";

            }
        }
    }
    cin >> move1;
    cin >> move2;
    vector<int> moves = { move1, move2 };
    cout << '\n';
    
    return moves;
}

void  play(char player, char bot, char chart[3][3], bool& playing) {
    vector<int> moves;
    do {
         moves = _showmove(player, bot, chart);
         
    } while (!(_putSymbol(player, chart, moves, bot)));
    
    

    botAi(bot, chart, moves, player);

    _iswin(playing, chart, player, bot);
}

bool _putSymbol(char player, char chart[3][3], vector<int> moves, char bot) {
    if (chart[moves[0]][moves[1]] == '#') {
        chart[moves[0]][moves[1]] = player;
        return true;
    }
    else {
        return false;
    }
}

bool botAi(char bot, char chart[3][3], vector<int> moves, char player) {
    bool isFull = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (chart[i][j] == '#') {
                isFull = false;
                break;
            }
        }
        if (!isFull)
            break;
    }

    if (isFull) {
        
        return false; // Table is full, bot cannot make a move
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 2);

    int randomrow = dist(gen);
    chrono::milliseconds duration(200);
    this_thread::sleep_for(duration);
    int randomcol = dist(gen);
    
    
    if (chart[randomrow][randomcol] == '#') {
        chart[randomrow][randomcol] = bot;
        return true;
    }
    else {
        return botAi(bot, chart, moves, player);
    }
}


void displayMatrix(char matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        cout << '\n';
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << "  ";
        }
    }

    cout << "\n";
}

bool _iswin(bool& playing, char chart[3][3], char player, char bot) {
    // Controllo se il giocatore ha vinto (orizzontalmente, verticalmente o diagonalmente)
    if ((chart[0][0] == player && chart[0][1] == player && chart[0][2] == player) ||
        (chart[1][0] == player && chart[1][1] == player && chart[1][2] == player) ||
        (chart[2][0] == player && chart[2][1] == player && chart[2][2] == player) ||
        (chart[0][0] == player && chart[1][0] == player && chart[2][0] == player) ||
        (chart[0][1] == player && chart[1][1] == player && chart[2][1] == player) ||
        (chart[0][2] == player && chart[1][2] == player && chart[2][2] == player) ||
        (chart[0][0] == player && chart[1][1] == player && chart[2][2] == player) ||
        (chart[0][2] == player && chart[1][1] == player && chart[2][0] == player)) {
        playing = false; // Imposta playing su false per indicare la fine del gioco
        cout << "compimenti hai vinto!";
        return true; // Restituisci true, poiché il giocatore ha vinto
    }

    // Controllo se il bot ha vinto (orizzontalmente, verticalmente o diagonalmente)
    if ((chart[0][0] == bot && chart[0][1] == bot && chart[0][2] == bot) ||
        (chart[1][0] == bot && chart[1][1] == bot && chart[1][2] == bot) ||
        (chart[2][0] == bot && chart[2][1] == bot && chart[2][2] == bot) ||
        (chart[0][0] == bot && chart[1][0] == bot && chart[2][0] == bot) ||
        (chart[0][1] == bot && chart[1][1] == bot && chart[2][1] == bot) ||
        (chart[0][2] == bot && chart[1][2] == bot && chart[2][2] == bot) ||
        (chart[0][0] == bot && chart[1][1] == bot && chart[2][2] == bot) ||
        (chart[0][2] == bot && chart[1][1] == bot && chart[2][0] == bot)) {
        playing = false; // Imposta playing su false per indicare la fine del gioco
        cout << "hai perso :(";
        return true; // Restituisci true, poiché il bot ha vinto
    }

    bool isFull = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (chart[i][j] == '#') {
                isFull = false;
                break;
            }
        }
        if (!isFull)
            break;
    }

    if (isFull) {
        playing = false;
        cout << "pareggio lol";
        return false; // Table is full, bot cannot make a move
    }

    return false; // Nessuno ha ancora vinto
}
