#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* ! ! ! DOLEZITE ! ! !
 *
 *
 * Program ma na riadkoch 75 - 109 dve rozdielne semi-grafiky, defaultne je zapnuta ta lepsia, ktora vyuziva
 * ascii tabulkove znaky, no bohuzial online kompilatori nerozoznavaju tieto znaky, takze ak uvidite otaznikove znaky
 * vsade v na okrajoch tabulky, tak je potrebne zakomentovat lepsiu semi-grafiku a odkomentovat horsiu semi-grafiku...
 * Jedine otazniky co su povolene su lodicky v horsej semi-grafike...
 *
 * Takto ma vyzerat lepsia semi-grafika: https://imgur.com/a/ZYhe5Gd
 * Takto ma vyzerat horsia semi-grafika: https://imgur.com/a/7VUGosk
 *
 * testovane a funkcne v:
 * [ LEPSIA SEMI-GRAFIKA ] clion - externa konzola
 * [ LEPSIA SEMI-GRAFIKA ] devcpp
 * [ HORSIA SEMI-GRAFIKA ] replit
 * [ HORSIA SEMI-GRAFIKA ] onlinegdb
 *
 * ! ! ! DOLEZITE ! ! ! */

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define color_DEFAULT 0
#define color_CYAN    1
#define color_GREEN   2
#define color_YELLOW  3
#define color_RED     4
#define color_WHITE   5
#define color_BLACK   6
#define color_MAGENTA 7

#define BOARD_SIZE    10
#define SHIP_TILE     254
#define WATER_TILE    126
#define INVALID_TILE  35
#define VOID_TILE     ' '
#define HIT_TILE      64
#define SHIP_COUNT    5
#define INPUT_LEN     30
#define NAME_LEN      30
#define TRUE          1
#define FALSE         0

#define INIT_GAME     1
#define SHOW_HELP     2
#define SHOW_MENU     3
#define EXIT_GAME     4
#define START_GAME    5

#define SHIP_COUNT    5
#define SHIP_1_LEN    5
#define SHIP_2_LEN    4
#define SHIP_3_LEN    3
#define SHIP_4_LEN    3
#define SHIP_5_LEN    2

#define MENU_TYPE_MAIN        1
#define MENU_TYPE_CHOOSE_SHIP 2
#define MENU_TYPE_PLACE_SHIP  3
#define MENU_TYPE_ROTATE_SHIP 4
#define MENU_TYPE_COMMANDS    5
#define MENU_TYPE_ATTACK      6

#define MENU_OPTION_COUNT   3
#define MENU_HINTS_COUNT    6

/* * * * * * * * * * * *
 * LEPSIA SEMI-GRAFIKA *
 * * * * * * * * * * * */

#define TABLE_TL            218
#define TABLE_TR            191
#define TABLE_BL            192
#define TABLE_BR            217
#define TABLE_VERTICAL      179
#define TABLE_HORIZONZAL    196
#define TABLE_LC            195
#define TABLE_RC            180
#define TABLE_MC            197
#define TABLE_TC            194
#define TABLE_BC            193
#define TABLE_WD            42


/* * * * * * * * * * * *
 * HORSIA SEMI-GRAFIKA *
 * * * * * * * * * * * */
/*
#define TABLE_TL            '+'
#define TABLE_TR            '+'
#define TABLE_BL            '+'
#define TABLE_BR            '+'
#define TABLE_VERTICAL      '|'
#define TABLE_HORIZONZAL    '-'
#define TABLE_LC            '|'
#define TABLE_RC            '|'
#define TABLE_MC            '+'
#define TABLE_TC            '-'
#define TABLE_BC            '-'
#define TABLE_WD            42
*/

struct _player {
    char name[NAME_LEN];
    int health;
};

/* * * * * * * * * * *
 * UTILITY FUNCTIONS *
 * * * * * * * * * * */
void changeColor(int color);
void repeatCharacter(char character, int length, char endingCharacter);
void addStringTerminator(char *string);
void errorMessage(char *string, char *reason);

/* * * * * * * * * * * * * *
 * GAME / BOARD  FUNCTIONS *
 * * * * * * * * * * * * * */
void fillArray(char *array, int length, char character);
void fillArray2D(char array[BOARD_SIZE][BOARD_SIZE], int length, char character);

int initGame(
        struct _player *p1,
        struct _player *p2,
        char p1_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p1_attackBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_attackBoard[BOARD_SIZE][BOARD_SIZE]
        );

int startGame(
        struct _player *p1,
        struct _player *p2,
        char p1_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p1_attackBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_attackBoard[BOARD_SIZE][BOARD_SIZE]
        );

void printBoard(char array[BOARD_SIZE][BOARD_SIZE]);
void printDoubleBoard(char array[BOARD_SIZE][BOARD_SIZE], char array2[BOARD_SIZE][BOARD_SIZE]);
void showTurn(struct _player *p, int method);
void infoScreen(char *title, char *text, struct _player *p1);
int showCommands(int restriction, struct _player *p);

/* * * * * * * * * *
 * MENU  FUNCTIONS *
 * * * * * * * * * */
void showMenu(char *title, char strings[][30], int arrayLength);
void menu_borderLine(char character, int length, char borderLeft, char borderRight);
void menu_textLine(char *string, int length, int tableColor, int textColor, int method);
void menu_blankLine();

/* * * * * * * * * *
 * INPUT FUNCTIONS *
 * * * * * * * * * */
int inputHandler(int menu, char *array, int restriction);
int processInput(int menu, char input[INPUT_LEN]);
int inputHandlerCoords(
        int method,
        char array[BOARD_SIZE][BOARD_SIZE],
        char copy[BOARD_SIZE][BOARD_SIZE],
        int length,
        int rotation,
        struct _player *p
        );

int processInputCoords(char input[INPUT_LEN], int *coordX, int *coordY);
int processInputRotation(char input[INPUT_LEN]);
void inputScreen(char *string);

/* * * * * * * * * *
 * SHIP  FUNCTIONS *
 * * * * * * * * * */
char *initPlayerName(char *input, char *string);
void initShips(char *name, char playingBoard[BOARD_SIZE][BOARD_SIZE]);
void showShips(char *name, char *array);
int showRotations(char array[BOARD_SIZE][BOARD_SIZE]);
int rotateShip(int rotation, char array[BOARD_SIZE][BOARD_SIZE], int coordX, int coordY, int length);
int placeShip(char array[BOARD_SIZE][BOARD_SIZE], int coordX, int coordY, int length);
int scan3x3(char array[BOARD_SIZE][BOARD_SIZE], int coordX, int coordY, int exception, int rotation);

int main() {
    char choice, result = -1;

    struct _player p1, p2;
    char p1_shipBoard[BOARD_SIZE][BOARD_SIZE], p1_attackBoard[BOARD_SIZE][BOARD_SIZE],
            p2_shipBoard[BOARD_SIZE][BOARD_SIZE], p2_attackBoard[BOARD_SIZE][BOARD_SIZE];

    char strings[MENU_OPTION_COUNT][30] = {
            "[ 1 ] / Start",
            "[ 2 ] / Help",
            "[ 3 ] / Exit"
    };

    system(CLEAR);

    showMenu("BATTLE - SHIPS", strings, MENU_OPTION_COUNT);

    choice = (char)inputHandler(MENU_TYPE_MAIN, NULL, 0);


    if (choice == INIT_GAME)
        choice = (char)initGame(&p1, &p2, p1_shipBoard, p1_attackBoard, p2_shipBoard, p2_attackBoard);

    if (choice == START_GAME) {
        result = (char)startGame(&p1, &p2, p1_shipBoard, p1_attackBoard, p2_shipBoard, p2_attackBoard);
        printf("%d", result);
    }

    if (result == 0)
        infoScreen("PLAYER LOST ALL SHIPS", "Winner:", &p1);

    else if (result == 1)
        infoScreen("PLAYER LOST ALL SHIPS", "Winner:", &p2);

    else if (result == 3 || result == 4)
        infoScreen("PLAYER HAS SURRENDERED", "Winner:", result == 4 ? &p1 : &p2);

    system("Pause");
    return 0;
}

/* * * * * * * * * * *
 * UTILITY FUNCTIONS *
 * * * * * * * * * * */
void changeColor(int color) {
    /*
     * Funkcia zmeni farbu vypisanim prislusneho escape-sequence characterom a stringom
     * color: farba na ktoru sa ma text zafarbit
     */
    switch (color) {
        case color_DEFAULT:
            printf("\033[0m");
            break;
        case color_CYAN:
            printf("\033[36m");
            break;
        case color_GREEN:
            printf("\033[32m");
            break;
        case color_YELLOW:
            printf("\033[33m");
            break;
        case color_RED:
            printf("\033[91m");
            break;
        case color_WHITE:
            printf("\033[37m");
            break;
        case color_BLACK:
            printf("\033[90m");
            break;
        case color_MAGENTA:
            printf("\033[35m");
            break;
        default:
            break;
    }
}

void repeatCharacter(char character, int length, char endingCharacter) {
    /*
     * Funkcia vytlaci znak X-krat na obrazovku
     * character: znak, ktory bude vytlaceny
     * length: pocet, kolko krat bude znak vytlaceny
     * endingCharacter: (optional) znak bude vytlaceny uplne na konci jeden-krat
     */
    for(int i=0; i<length; i++)
        printf("%c", character);

    if (endingCharacter != 0)
        printf("%c", endingCharacter);
}

void addStringTerminator(char *string) {
    /*
     * Funkcia addStringTerminator nahradi \n za \0
     * string: string v ktorom sa zmena vykona
     */
    string[strlen(string)-1] = '\0';
}

void errorMessage(char *string, char *reason) {
    /*
     * Funkcia zmeni farbu textu a vypise string
     * string: chybova sprava
     * error: (optional) spresnenie chyby
     */
    changeColor(color_RED);

    printf("\n%s", string);

    if (reason != NULL)
        printf(" [ %s ]", reason);

    printf("\n");

    changeColor(color_DEFAULT);
}

/* * * * * * * * * * * * * *
 * GAME / BOARD  FUNCTIONS *
 * * * * * * * * * * * * * */
void fillArray(char *array, int length, char character) {
    /*
     * Funkcia naplni cele pole jednym znakom
     * array: pole
     * length: pocet prvkov pola
     * character: znak, ktorym je pole naplnane
     */
    for (int i=0; i<length; i++)
        array[i] = character;
}

void fillArray2D(char array[BOARD_SIZE][BOARD_SIZE], int length, char character) {
    /*
     * Funkcia naplni cele pole jednym znakom
     * array: pole
     * length: pocet prvkov pola
     * character: znak, ktorym je pole naplnane
     */
    for (int i=0; i<length; i++)
        for (int j=0; j<length; j++)
            array[i][j] = character;
}

int initGame(
        struct _player *p1,
        struct _player *p2,
        char p1_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p1_attackBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_attackBoard[BOARD_SIZE][BOARD_SIZE]
) {
    /*
     * Funkcia nastavuje vsetky premenne a polia pred zacatim hry
     * p1: hrac 1
     * p2: hrac 2
     * p1_shipBoard: plocha s lodickami hraca 1
     * p1_attackBoard plocha na ktoru hrac 1 utoci
     * p2_shipBoard plocha s lodickami hraca 2
     * p2_attackBoard plocha na ktoru hrac 2 utoci
     */
    char input[NAME_LEN];

    fillArray2D(p1_shipBoard, BOARD_SIZE, WATER_TILE);
    fillArray2D(p1_attackBoard, BOARD_SIZE, WATER_TILE);
    fillArray2D(p2_shipBoard, BOARD_SIZE, WATER_TILE);
    fillArray2D(p2_attackBoard, BOARD_SIZE, WATER_TILE);

    p1->health = SHIP_1_LEN + SHIP_2_LEN + SHIP_3_LEN + SHIP_4_LEN + SHIP_5_LEN;
    p2->health = SHIP_1_LEN + SHIP_2_LEN + SHIP_3_LEN + SHIP_4_LEN + SHIP_5_LEN;

    initPlayerName(input, "Enter name for Player 1");
    strcpy(p1->name, input);

    initPlayerName(input, "Enter name for Player 2");
    strcpy(p2->name, input);

    initShips(p1->name, p1_shipBoard);
    infoScreen("SHIP PLACEMENT DONE", "Next turn:", p2);
    initShips(p2->name, p2_shipBoard);
    infoScreen("SHIP PLACEMENT DONE", "Next turn:", p1);

    return START_GAME;
}

int startGame(
        struct _player *p1,
        struct _player *p2,
        char p1_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p1_attackBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_shipBoard[BOARD_SIZE][BOARD_SIZE],
        char p2_attackBoard[BOARD_SIZE][BOARD_SIZE]
) {
    /*
     * Funkcia obsluhuje beh celej hry, striada hracov v cykloch po ich tahoch a vracia hodnoty aby sa v maine vedela
     * hra ukoncit
     * p1: hrac 1
     * p2: hrac 2
     * p1_shipBoard: plocha s lodickami hraca 1
     * p1_attackBoard plocha na ktoru hrac 1 utoci
     * p2_shipBoard plocha s lodickami hraca 2
     * p2_attackBoard plocha na ktoru hrac 2 utoci
     */
    int turn = 0, choice, restriction;
    while (TRUE) {
        restriction = 0;
        choice = 0;
        while (choice != 2) {
            system(CLEAR);
            showTurn(turn % 2 == 0 ? p1 : p2, 2);

            if (turn % 2 == 0)
                printDoubleBoard(p1_shipBoard, p1_attackBoard);

            else
                printDoubleBoard(p2_shipBoard, p2_attackBoard);

            showCommands(restriction, turn % 2 == 0 ? p1 : p2);
            choice = inputHandler(MENU_TYPE_COMMANDS, NULL, restriction);

            if (choice == 1) {
                restriction = 1;

                system(CLEAR);
                showTurn(turn % 2 == 0 ? p1 : p2, 2);

                if (turn % 2 == 0)
                    printDoubleBoard(p1_shipBoard, p1_attackBoard);

                else
                    printDoubleBoard(p2_shipBoard, p2_attackBoard);

                inputScreen("Enter coordinates");

                if (turn % 2 == 0)
                    inputHandlerCoords(
                            MENU_TYPE_ATTACK,
                            p1_attackBoard,
                            p2_shipBoard,
                            0,
                            0,
                            p2
                            );

                else
                    inputHandlerCoords(
                            MENU_TYPE_ATTACK,
                            p2_attackBoard,
                            p1_shipBoard,
                            0,
                            0,
                            p1
                            );


            } else if (choice == 3) {
                return turn % 2 == 0 ? 3 : 4;
            }
        }

        if (p1->health == 0)
            return 1;

        if (p2->health == 0)
            return 0;

        turn++;
        infoScreen("END OF TURN", "Next turn:", turn % 2 == 0 ? p1 : p2);
    }

    return 0;
}

void printBoard(char array[BOARD_SIZE][BOARD_SIZE]) {
    /*
     * Funkcia vytlaci celu tabulku na obrazovku
     * array: hracia plocha ktora je vytlacena
     */
    printf("    ");
    for (int i = 0; i < BOARD_SIZE; i++)
        printf(" %c  ", i+'A');

    changeColor(color_BLACK);
    printf("\n   %c", TABLE_TL);
    for (int j = 0; j < BOARD_SIZE-1; j++)
        repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_TC);

    repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_TR);
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++){
        changeColor(color_DEFAULT);
        printf("%2d", i);
        changeColor(color_BLACK);
        printf(" %c", TABLE_VERTICAL);

        for (int j = 0; j < BOARD_SIZE; j++) {
            if (array[i][j] == WATER_TILE)
                changeColor(color_CYAN);
            else if (array[i][j] == INVALID_TILE)
                changeColor(color_MAGENTA);
            else
                changeColor(color_WHITE);
            printf(" %c ", array[i][j]);
            changeColor(color_BLACK);
            printf("%c", TABLE_VERTICAL);
        }
        printf("\n   %c", i == BOARD_SIZE-1 ? TABLE_BL : TABLE_LC);
        changeColor(color_BLACK);
        for (int j = 0; j < BOARD_SIZE-1; j++)
            if (i == BOARD_SIZE-1)
                repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_BC);
            else
                repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_MC);

        repeatCharacter((char)TABLE_HORIZONZAL, 3, 0);
        printf("%c\n", i == BOARD_SIZE-1 ? TABLE_BR : TABLE_RC);
    }

    changeColor(color_DEFAULT);
}

void printDoubleBoard(char array[BOARD_SIZE][BOARD_SIZE], char array2[BOARD_SIZE][BOARD_SIZE]) {
    /*
     * Funkcia vytlaci 2 hracie plochy vedla seba na obrazovku
     * array: prva hracia plocha (obsahuje hracove lode)
     * array2: druha hracia plocha (hrac na tuto plochu utoci)
     */
    for (int k = 0; k < 2; k++) {
        printf("    ");
        for (int i = 0; i < BOARD_SIZE; i++)
            printf(" %c  ", i+'A');
        repeatCharacter(' ', 5, 0);
    }

    changeColor(color_BLACK);
    printf("\n");
    for (int k = 0; k < 2; k++) {
        printf("   %c", TABLE_TL);
        for (int j = 0; j < BOARD_SIZE - 1; j++)
            repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_TC);
        repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_TR);
        repeatCharacter(' ', 5, 0);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++){
        for (int k = 0; k < 2; k++) {
            changeColor(color_DEFAULT);
            printf("%2d", i);
            changeColor(color_BLACK);
            printf(" %c", TABLE_VERTICAL);

            for (int j = 0; j < BOARD_SIZE; j++) {
                if (k==0) {
                    if (array[i][j] == WATER_TILE)
                        changeColor(color_CYAN);
                    else if (array[i][j] == HIT_TILE)
                        changeColor(color_RED);
                    else
                        changeColor(color_WHITE);
                } else {
                    if (array2[i][j] == WATER_TILE)
                        changeColor(color_CYAN);
                    else if (array2[i][j] == HIT_TILE)
                        changeColor(color_RED);
                    else
                        changeColor(color_WHITE);
                }
                printf(" %c ", k==0 ? array[i][j] : array2[i][j]);
                changeColor(color_BLACK);
                printf("%c", TABLE_VERTICAL);
            }
            repeatCharacter(' ', 5, 0);
        }
        printf("\n");
        for (int k = 0; k < 2; k++) {
            printf("   %c", i == BOARD_SIZE - 1 ? TABLE_BL : TABLE_LC);
            changeColor(color_BLACK);
            for (int j = 0; j < BOARD_SIZE - 1; j++)
                if (i == BOARD_SIZE - 1)
                    repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_BC);
                else
                    repeatCharacter((char)TABLE_HORIZONZAL, 3, (char)TABLE_MC);

            repeatCharacter((char)TABLE_HORIZONZAL, 3, 0);
            printf("%c", i == BOARD_SIZE - 1 ? TABLE_BR : TABLE_RC);
            repeatCharacter(' ', 5, 0);
        }
        printf("\n");
    }

    changeColor(color_DEFAULT);
}

void showTurn(struct _player *p, int method) {
    /*
     * Funkcia zobrazuje kto je na tahu
     * p: hrac, ktory je na tahu
     * method: premenna, ktora drzi v sebe hodnotu podla ktorej sa zobrazuje text
     */
    changeColor(color_YELLOW);
    repeatCharacter((char)TABLE_HORIZONZAL, 3, 0);
    printf("[");
    changeColor(color_CYAN);
    printf(" %s", p->name);
    changeColor(color_DEFAULT);
    printf("'s TURN ");
    changeColor(color_YELLOW);
    printf("]");
    repeatCharacter((char)TABLE_HORIZONZAL, 80 - strlen(p->name), '\n');
    changeColor(color_DEFAULT);
    printf("\n");

    for (int i = 0; i < method; i++){
        changeColor(i == 0 ? color_GREEN : color_RED);
        repeatCharacter(' ', 3, 0);
        printf("[");
        changeColor(color_DEFAULT);
        i == 0 ? printf(" YOUR SHIPS ") : printf(" ENEMY SHIPS ");
        changeColor(i == 0 ? color_GREEN : color_RED);
        printf("]");
        repeatCharacter(' ', 32, 0);
    }
    printf("\n\n");

    changeColor(color_DEFAULT);
}

void infoScreen(char *title, char *text, struct _player *p) {
    /*
     * Funkcia zobrazuje informacnu tabulku pre hracov a caka na stlacenie tlacidla
     * title: nazov tabulky
     * text: text v tabulke
     * p: hrac
     */
    system(CLEAR);
    changeColor(color_YELLOW);

    menu_borderLine((char)TABLE_HORIZONZAL, TABLE_WD, (char)TABLE_TL, (char)TABLE_TR);

    menu_blankLine();
    menu_blankLine();

    printf("%c", TABLE_VERTICAL);
    changeColor(color_DEFAULT);
    printf("%*c%s%*c", (TABLE_WD-strlen(title)+1)/2 , ' ', title, (TABLE_WD-strlen(title))/2 , ' ');
    changeColor(color_YELLOW);
    printf("%c\n", TABLE_VERTICAL);

    menu_blankLine();
    menu_blankLine();

    menu_textLine(text, strlen(text), color_YELLOW, color_DEFAULT, 1);
    menu_textLine(p->name, strlen(p->name), color_YELLOW, color_CYAN, 1);
    menu_blankLine();

    menu_blankLine();
    menu_borderLine((char)TABLE_HORIZONZAL, TABLE_WD, (char)TABLE_BL, (char)TABLE_BR);

    changeColor(color_DEFAULT);
    system("Pause");
}

int showCommands(int restriction, struct _player *p) {
    /*
     * Funkcia zobrazuje tabulku s instrukciami pri hrani hry
     * restriction: premenna drziaca hodnou podla ktorej sa odomknu tlacitka
     * p: hrac
     */
    changeColor(color_YELLOW);
    printf("\n%c", TABLE_TL);
    repeatCharacter((char)TABLE_HORIZONZAL, 2, '[');
    changeColor(color_DEFAULT);
    printf(" Choose action from the menu ");
    changeColor(color_YELLOW);
    printf("]");
    repeatCharacter((char)TABLE_HORIZONZAL, 10, '\n');
    printf("%c\n%c ", TABLE_VERTICAL, TABLE_VERTICAL);
    restriction == 0 ? changeColor(color_GREEN) : changeColor(color_RED);
    printf("[ 1 ] / Fire\n");
    changeColor(color_YELLOW);
    printf("%c ", TABLE_VERTICAL);
    restriction == 0 ? changeColor(color_RED) : changeColor(color_GREEN);
    printf("[ 2 ] / Next turn\n");
    changeColor(color_YELLOW);
    printf("%c ", TABLE_VERTICAL);
    changeColor(color_GREEN);
    printf("[ 3 ] / Surrender\n");
    changeColor(color_YELLOW);
    printf("%c\n%c", TABLE_VERTICAL, TABLE_BL);
    repeatCharacter((char)TABLE_HORIZONZAL, 43, '\n');

    changeColor(color_DEFAULT);

    return restriction;
}

/* * * * * * * * * *
 * MENU  FUNCTIONS *
 * * * * * * * * * */
void showMenu(char *title, char strings[][30], int arrayLength) {
    /*
     * Funkcia vytlaci cele menu na konzolu
     * title: Nazov menu
     * strings: Pole stringov reprezentujuce mozne volby v menu
     * arrayLength: Pocet prvkov pola strings
     */
    system(CLEAR);

    int len = strlen(strings[0]);

    for (int i = 0; i < arrayLength; i++)
        if (strlen(strings[i]) > len)
            len = strlen(strings[i]);

    changeColor(color_YELLOW);

    menu_borderLine((char)TABLE_HORIZONZAL, TABLE_WD, (char)TABLE_TL, (char)TABLE_TR);

    menu_blankLine();
    menu_blankLine();

    printf("%c", TABLE_VERTICAL);
    changeColor(color_DEFAULT);
    printf("%*c%s%*c", (TABLE_WD-strlen(title)+1)/2 , ' ', title, (TABLE_WD-strlen(title))/2 , ' ');
    changeColor(color_YELLOW);
    printf("%c\n", TABLE_VERTICAL);

    menu_blankLine();
    menu_blankLine();

    for (int i=0; i < arrayLength; i++) {
        menu_textLine(strings[i], len, color_YELLOW, color_DEFAULT, 0);
        menu_blankLine();
    }

    menu_blankLine();
    menu_borderLine((char)TABLE_HORIZONZAL, TABLE_WD, (char)TABLE_BL, (char)TABLE_BR);

    changeColor(color_DEFAULT);
}

void menu_borderLine(char character, int length, char borderLeft, char borderRight) {
    /*
     * Funkcia vytlaci na obrazovku riadok tabulky podla zadanych znakov
     * character: znak ktory bude X-krat vytlaceny
     * length: pocet, kolko krat bude znak vytlaceny
     * borderLeft: znak laveho okraju tabulky
     * borderRight: znak praveho okraju tabulky
     */
    printf("%c", borderLeft);
    repeatCharacter(character, length, 0);
    printf("%c\n", borderRight);
}

void menu_textLine(char *string, int length, int tableColor, int textColor, int method) {
    /*
     * Funkcia vytlaci na konzolu jeden riadok ohraniceny zvislymi ciarami a moznostou volby
     * string: text volby
     * length: dlzka najvacsieho retazca volby z menu
     * tableColor: farba tabulky v menu
     * textColor: farba textu v menu
     * method: premenna ktora drzi v sebe hodnotu, podla ktorej sa zobrazuje pocet medzier
     */
    printf("%c", TABLE_VERTICAL);
    changeColor(textColor);

    if (method == 0)
        printf("%*c%s%*c", (TABLE_WD-length)/2 , ' ', string, TABLE_WD-(TABLE_WD-length)
        /2-strlen(string) , ' ');
    if (method == 1)
        printf("%*c%s%*c", ((TABLE_WD-length)/2)-2 , ' ', string, (TABLE_WD-(TABLE_WD-length)
        /2-strlen(string))+2 , ' ');

    changeColor(tableColor);
    printf("%c\n", TABLE_VERTICAL);
}

void menu_blankLine() {
    /*
     * Funkcia vytlaci na konzolu jeden prazdny riadok ohraniceny zvislymi ciarami
     */
    printf("%c", TABLE_VERTICAL);
    repeatCharacter(' ', TABLE_WD, 0);
    printf("%c\n", TABLE_VERTICAL);
}

/* * * * * * * * * *
 * INPUT FUNCTIONS *
 * * * * * * * * * */
int inputHandler(int menu, char *array, int restriction) {
    /*
     * Funkcia caka na vyber hraca prvej volby (z menu)
     * menu: Menu z ktoreho ocakavame vstup
     * array: hracia plocha
     * restriction: premenna drziaca hodnou podla ktorej sa odomknu tlacitka
     */
    char input[INPUT_LEN];
    int choice;
    int commandNotRecognized = FALSE;

    while (TRUE) {
        if (commandNotRecognized == TRUE) {
            if (menu == MENU_TYPE_MAIN || menu == MENU_TYPE_COMMANDS)
                errorMessage("command not recognized", input);

            else if (menu == MENU_TYPE_CHOOSE_SHIP)
                errorMessage("invalid ship", input);

            else if (menu == MENU_TYPE_PLACE_SHIP)
                errorMessage("invalid position", input);

            commandNotRecognized = FALSE;
        }

        printf("\n");
        inputScreen("Select an option");

        fgets(input, INPUT_LEN, stdin);

        addStringTerminator(input);

        if (menu == MENU_TYPE_MAIN) {
            choice = processInput(MENU_TYPE_MAIN, input);

            if (choice == SHOW_HELP) {
                char strings[MENU_HINTS_COUNT][30] = {
                        "\"Help\" opens this menu",
                        "\"Back\" navrat do menu",
                        "Either use character in []",
                        "or string after /",
                        "Coords works both ways a5=5a",
                        "Commands are case insensitive"
                };

                showMenu("HELP - MENU", strings, MENU_HINTS_COUNT);
            }

            else if (choice == SHOW_MENU) {
                char strings[MENU_OPTION_COUNT][30] = {
                        "[ 1 ] / Start",
                        "[ 2 ] / Help",
                        "[ 3 ] / Exit"
                };

                showMenu("BATTLE - SHIPS", strings, MENU_OPTION_COUNT);
            }

            else if (choice == EXIT_GAME)
                return EXIT_GAME;

            else if (choice == INIT_GAME)
                return INIT_GAME;

            else
                commandNotRecognized = TRUE;

        } else if (menu == MENU_TYPE_CHOOSE_SHIP) {
            choice = processInput(MENU_TYPE_CHOOSE_SHIP, input);

            if (choice > 0 && choice < 6)
                if (array[choice-1] == '0')
                    commandNotRecognized = TRUE;
                else
                    return choice;

            else
                commandNotRecognized = TRUE;
        } else if (menu == MENU_TYPE_COMMANDS) {
            choice = processInput(MENU_TYPE_COMMANDS, input);

            if (choice > 0 && choice < 4)
                if ((choice == 1 && restriction == 1) || (choice == 2 && restriction == 0))
                    commandNotRecognized = TRUE;
                else
                    return choice;

            else
                commandNotRecognized = TRUE;
        }
    }
}

int processInput(int menu, char input[INPUT_LEN]) {
    /*
     * Funkcia pozera na to co bolo zadane z klavesnice a podla toho vrati prislusnu hodnotu
     * menu: Menu z ktoreho sa berie input
     * input: String zadany z klavesnice
     */
    char string[INPUT_LEN];
    char character;

    if (strlen(input) != 1) {
        for (int i = 0; i < strlen(input)+1; i++) {
            character = isalpha(input[i]) ? tolower(input[i]) : input[i];
            string[i] = character;
        }
    }

    if (menu == MENU_TYPE_MAIN) {
        if (strcmp(input, "1") == 0 || strcmp(string, "start") == 0)
            return INIT_GAME;

        if (strcmp(input, "2") == 0 || strcmp(string, "help") == 0)
            return SHOW_HELP;

        if (strcmp(input, "3") == 0 || strcmp(string, "exit") == 0)
            return EXIT_GAME;

        if (strcmp(string, "back") == 0)
            return SHOW_MENU;

    } else if (menu == MENU_TYPE_CHOOSE_SHIP) {
        if (strcmp(input, "1") == 0 || strcmp(string, "carrier") == 0)
            return 1;

        if (strcmp(input, "2") == 0 || strcmp(string, "battleship") == 0)
            return 2;

        if (strcmp(input, "3") == 0 || strcmp(string, "cruiser") == 0)
            return 3;

        if (strcmp(input, "4") == 0 || strcmp(string, "submarine") == 0)
            return 4;

        if (strcmp(input, "5") == 0 || strcmp(string, "destroyer") == 0)
            return 5;

    } else if (menu == MENU_TYPE_COMMANDS) {
        if (strcmp(input, "1") == 0 || strcmp(string, "fire") == 0)
            return 1;

        if (strcmp(input, "2") == 0 || strcmp(string, "next turn") == 0)
            return 2;

        if (strcmp(input, "3") == 0 || strcmp(string, "surrender") == 0)
            return 3;
    }

    return 0;
}

int inputHandlerCoords(
        int method,
        char array[BOARD_SIZE][BOARD_SIZE],
        char copy[BOARD_SIZE][BOARD_SIZE],
        int length,
        int rotation,
        struct _player *p
) {
    /*
     * Funkcia caka na vyber hraca volby (z menu)
     * menu: Menu z ktoreho ocakavame vstup
     * array: hracia plocha
     * copy: kopia hracej plochy
     * length: dlzka lode
     * rotation: smer otocenia lode
     * p: hrac
     */
    char input[INPUT_LEN];
    int choice, commandNotRecognized = FALSE, coordX, coordY, restriction;

    while (TRUE) {
        if (method == MENU_TYPE_PLACE_SHIP) {
            if (commandNotRecognized == TRUE) {
                errorMessage("invalid position", input);
                commandNotRecognized = FALSE;
            }

            inputScreen("Choose position for the ship");

        } else if (method == MENU_TYPE_ROTATE_SHIP) {
            system(CLEAR);
            printBoard(array);

            if (commandNotRecognized == TRUE) {
                if (restriction == 1)
                    errorMessage("ship placement obstructed", input);
                else
                    errorMessage("command not recognized", input);
                printf("\n");
                commandNotRecognized = FALSE;
            }

            restriction = showRotations(array);

        } else if (method == MENU_TYPE_ATTACK) {
            if (commandNotRecognized == TRUE) {
                errorMessage("invalid coordinates", input);
                inputScreen("Enter coordinates");
                commandNotRecognized = FALSE;
            }
        }

        fgets(input, INPUT_LEN, stdin);

        addStringTerminator(input);

        if (method == MENU_TYPE_PLACE_SHIP) {
            if (processInputCoords(input, &coordX, &coordY) == 1) {
                if (array[coordY][coordX] != WATER_TILE) {
                    commandNotRecognized = TRUE;
                    continue;
                }

                rotation = placeShip(array, coordX, coordY, length);
                return rotation;
            }

            else
                commandNotRecognized = TRUE;

        }
        else if (method == MENU_TYPE_ROTATE_SHIP) {
            choice = processInputRotation(input);

            if (choice == 1) {
                rotation++;
                memcpy(array, copy, BOARD_SIZE*BOARD_SIZE);

                rotation = rotateShip(rotation, array, coordX, coordY, length);

            } else if (choice == 2) {
                if (restriction == 1)
                    commandNotRecognized = TRUE;
                else
                    return 0;
            } else if (choice == 3) {
                memcpy(array, copy, BOARD_SIZE*BOARD_SIZE);
                return 1;
            }

            else
                commandNotRecognized = TRUE;

        } else if (method == MENU_TYPE_ATTACK) {
            if (processInputCoords(input, &coordX, &coordY) == 1) {
                if (array[coordY][coordX] != WATER_TILE) {
                    commandNotRecognized = TRUE;
                    continue;
                }

                if (copy[coordY][coordX] == (char)SHIP_TILE) {
                    copy[coordY][coordX] = HIT_TILE;
                    array[coordY][coordX] = HIT_TILE;
                    p->health--;
                    return 1;
                }

                if (copy[coordY][coordX] == WATER_TILE) {
                    copy[coordY][coordX] = VOID_TILE;
                    array[coordY][coordX] = VOID_TILE;
                    return 1;
                }
            }

            else
                commandNotRecognized = TRUE;
        }

    }
}

int processInputCoords(char input[INPUT_LEN], int *coordX, int *coordY) {
    /*
     * Funkcia spracuva vstup a overuje ako bol zadany plus vracia X a Y suradnice
     * input: vstup
     * coordX: suradnica X
     * coordY: suradnica Y
     */
    if (strlen(input) != 2)
        return 0;

    if (isalpha(input[0])) {
        if (tolower(input[0]) < 'a' || tolower(input[0]) > 'z')
            return 0;
        if (input[1] < '0' || input[1] > '9')
            return 0;

        *coordX = tolower(input[0]) - 'a';
        *coordY = input[1]-48;

    } else if (isdigit(input[0])) {
        if (tolower(input[1]) < 'a' && tolower(input[1]) > 'z')
            return 0;
        if (input[0] < '0' || input[0] > '9')
            return 0;

        *coordX = tolower(input[1]) - 'a';
        *coordY = input[0]-48;
    }

    return 1;
}

int processInputRotation(char input[INPUT_LEN]) {
    /*
     * Funkcia spracuva vstup a rotuje lod
     * input: vstup
     */
    char string[INPUT_LEN];
    char character;

    if (strlen(input) != 1) {
        for (int i = 0; i < strlen(input)+1; i++) {
            character = isalpha(input[i]) ? tolower(input[i]) : input[i];
            string[i] = character;
        }
    }

    if (strcmp(input, "r") == 0 || strcmp(string, "rotate") == 0)
        return 1;

    if (strcmp(input, "c") == 0 || strcmp(string, "confirm") == 0)
        return 2;

    if (strcmp(input, "x") == 0 || strcmp(string, "cancel") == 0)
        return 3;

    return 0;
}

void inputScreen(char *string) {
    /*
     * Funkcia vytlaci tabulku pre vstup
     */
    changeColor(color_YELLOW);
    printf("\n%c", TABLE_TL);
    repeatCharacter((char)TABLE_HORIZONZAL, 2, '[');
    changeColor(color_DEFAULT);
    printf(" %s ", string);
    changeColor(color_YELLOW);
    printf("]");
    repeatCharacter((char)TABLE_HORIZONZAL, 37 - strlen(string), '\n');
    printf("%c\n%c", TABLE_VERTICAL, TABLE_BL);
    repeatCharacter((char)TABLE_HORIZONZAL, 2, (char)TABLE_RC);
    printf(" ");

    changeColor(color_DEFAULT);
}

/* * * * * * * * * *
 * SHIP  FUNCTIONS *
 * * * * * * * * * */
char *initPlayerName(char *input, char *string) {
    /*
     * Funkcia vyziada meno po hracovi
     * input: vstup
     * string: text ktory sa zobrazi v tabulke
     */
    system(CLEAR);

    inputScreen(string);

    fgets(input, NAME_LEN, stdin);

    addStringTerminator(input);

    return input;
}

void initShips(char *name, char playingBoard[BOARD_SIZE][BOARD_SIZE]) {
    /*
     * Funkcia postupne uklada lode na plochu tak ako hrac zadava
     * name: meno hraca
     * playingBoard: hracia plocha
     */
    int shipLengths[SHIP_COUNT] = {SHIP_1_LEN, SHIP_2_LEN, SHIP_3_LEN, SHIP_4_LEN, SHIP_5_LEN};
    int placedShips = 0;
    char availableShips[5], choiceShip, choicePosition, choiceRotation, boardCopy[BOARD_SIZE][BOARD_SIZE];
    fillArray(availableShips, 5, '1');

    while (placedShips < SHIP_COUNT) {
        memcpy(boardCopy, playingBoard, BOARD_SIZE*BOARD_SIZE);
        system(CLEAR);
        showTurn(name, 1);
        printBoard(playingBoard);

        showShips(name, availableShips);
        choiceShip = inputHandler(MENU_TYPE_CHOOSE_SHIP, availableShips, 0);

        system(CLEAR);
        printBoard(playingBoard);

        choicePosition = inputHandlerCoords(
                MENU_TYPE_PLACE_SHIP,
                playingBoard,
                boardCopy,
                shipLengths[choiceShip-1],
                0,
                NULL
                );

        choiceRotation = inputHandlerCoords(
                MENU_TYPE_ROTATE_SHIP,
                playingBoard,
                boardCopy,
                shipLengths[choiceShip-1],
                choicePosition,
                NULL
                );

        if(choiceRotation == 0) {
            placedShips++;
            availableShips[choiceShip-1] = '0';
        }
    }
}

void showShips(char *name, char *array) {
    /*
     * Funkcia ukaze mozne volitelne lode
     * name: meno hraca
     * array: stav lode (ci uz je na ploche alebo nie je)
     */
    changeColor(color_YELLOW);
    printf("\n%c", TABLE_TL);
    repeatCharacter((char)TABLE_HORIZONZAL, 2, '[');
    changeColor(color_DEFAULT);
    printf(" Select one from these ships ");
    changeColor(color_YELLOW);
    printf("]");
    repeatCharacter((char)TABLE_HORIZONZAL, 10, '\n');
    printf("%c\n%c ", TABLE_VERTICAL, TABLE_VERTICAL);
    array[0] == '1' ? changeColor(color_GREEN) : changeColor(color_RED);
    printf("[ 1 ] / Carrier :");
    repeatCharacter(' ', 4, 0);
    for(int i = 0; i < 5; i++)
        printf("%c ",SHIP_TILE);
    changeColor(color_YELLOW);
    printf("\n%c ", TABLE_VERTICAL);

    array[1] == '1' ? changeColor(color_GREEN) : changeColor(color_RED);
    printf("[ 2 ] / Battleship :");
    repeatCharacter(' ', 1, 0);
    for(int i = 0; i < 4; i++)
        printf("%c ",SHIP_TILE);
    changeColor(color_YELLOW);
    printf("\n%c ", TABLE_VERTICAL);

    array[2] == '1' ? changeColor(color_GREEN) : changeColor(color_RED);
    printf("[ 3 ] / Cruiser :");
    repeatCharacter(' ', 4, 0);
    for(int i = 0; i < 3; i++)
        printf("%c ",SHIP_TILE);
    changeColor(color_YELLOW);
    printf("\n%c ", TABLE_VERTICAL);

    array[3] == '1' ? changeColor(color_GREEN) : changeColor(color_RED);
    printf("[ 4 ] / Submarine :");
    repeatCharacter(' ', 2, 0);
    for(int i = 0; i < 3; i++)
        printf("%c ",SHIP_TILE);
    changeColor(color_YELLOW);
    printf("\n%c ", TABLE_VERTICAL);

    array[4] == '1' ? changeColor(color_GREEN) : changeColor(color_RED);
    printf("[ 5 ] / Destroyer :");
    repeatCharacter(' ', 2, 0);
    for(int i = 0; i < 2; i++)
        printf("%c ",SHIP_TILE);
    changeColor(color_YELLOW);
    printf("\n%c\n%c", TABLE_VERTICAL, TABLE_BL);
    repeatCharacter((char)TABLE_HORIZONZAL, 43, '\n');

    changeColor(color_DEFAULT);
}

int showRotations(char array[BOARD_SIZE][BOARD_SIZE]) {
    /*
     * Funkcia zobrazuje menu instrukcii pre pokladanie lode
     * array: hracia plocha
     */
    int restriction = FALSE;

    changeColor(color_YELLOW);
    printf("\n%c", TABLE_TL);
    repeatCharacter((char)TABLE_HORIZONZAL, 2, '[');
    changeColor(color_DEFAULT);
    printf(" Choose rotation for the ship ");
    changeColor(color_YELLOW);
    printf("]");
    repeatCharacter((char)TABLE_HORIZONZAL, 10, '\n');
    printf("%c\n%c ", TABLE_VERTICAL, TABLE_VERTICAL);
    changeColor(color_GREEN);
    printf("[ R ] / Rotate\n");
    changeColor(color_YELLOW);
    printf("%c ", TABLE_VERTICAL);

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (array[i][j] == INVALID_TILE)
                restriction = TRUE;

    restriction ? changeColor(color_RED) : changeColor(color_GREEN);
    printf("[ C ] / Confirm\n");
    changeColor(color_YELLOW);
    printf("%c ", TABLE_VERTICAL);
    changeColor(color_GREEN);
    printf("[ X ] / Cancel\n");
    changeColor(color_YELLOW);
    printf("%c\n%c", TABLE_VERTICAL, TABLE_BL);
    repeatCharacter((char)TABLE_HORIZONZAL, 43, '\n');

    changeColor(color_DEFAULT);

    return restriction;
}

int rotateShip(int rotation, char array[BOARD_SIZE][BOARD_SIZE], int coordX, int coordY, int length) {
    /*
     * Funkcia otaca lod a testuje ci sa lod moze otocit do daneho smeru
     * array: hracia plocha
     * coordX: suradnica X
     * coordY: suradnica Y
     * length: dlzka lode
     */
    if (rotation == 0) {
        for (int j = 0; j < length; j++)
            if (coordY + j > 9) {
                rotation++;
                break;
            }
    }
    if (rotation == 1) {
        for (int j = 0; j < length; j++)
            if (coordX + j > 9) {
                rotation++;
                break;
            }
    }
    if (rotation == 2) {
        for (int j = 0; j < length; j++)
            if (coordY - j < 0) {
                rotation++;
                break;
            }
    }
    if (rotation == 3) {
        for (int j = 0; j < length; j++)
            if (coordX - j < 0) {
                rotation++;
                break;
            }
    }
    if (rotation == 4) {
        for (int j = 0; j < length; j++)
            if (coordY + j > 9) {
                rotation = rotateShip(rotation-3, array, coordX,coordY, length);
                return rotation;
            }
    }

    if (rotation == 1) {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX+i, coordY, i==0 ? 0 : 1, rotation) == 1)
                array[coordY][coordX+i] = INVALID_TILE;
            else
                array[coordY][coordX+i] = (char)SHIP_TILE;
        }
    } else if (rotation == 2) {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX, coordY-i, i==0 ? 0 : 1, rotation) == 1)
                array[coordY-i][coordX] = INVALID_TILE;
            else
                array[coordY-i][coordX] = (char)SHIP_TILE;
        }
    } else if (rotation == 3) {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX-i, coordY, i==0 ? 0 : 1, rotation) == 1)
                array[coordY][coordX-i] = INVALID_TILE;
            else
                array[coordY][coordX-i] = (char)SHIP_TILE;
        }
    } else {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX, coordY+i, i==0 ? 0 : 1, rotation) == 1)
                array[coordY+i][coordX] = INVALID_TILE;
            else
                array[coordY+i][coordX] = (char)SHIP_TILE;
        }

        rotation = 0;
    }
    system(CLEAR);
    printBoard(array);

    return rotation;
}

int placeShip(char array[BOARD_SIZE][BOARD_SIZE], int coordX, int coordY, int length) {
    /*
     * Funkcia poklada lod na plochu a testuje ci sa lod moze polozit
     * array: hracia plocha
     * coordX: suradnica X
     * coordY: suradnica Y
     * length: dlzka lode
     */
    int rotation = 0;

    if (rotation == 0) {
        for (int j = 0; j < length; j++)
            if (coordY+j > 9) {
                rotation++;
                break;
            }
    } if (rotation == 1) {
        for (int j = 0; j < length; j++)
            if (coordX+j > 9) {
                rotation++;
                break;
            }
    } if (rotation == 2) {
        for (int j = 0; j < length; j++)
            if (coordY-j < 0) {
                rotation++;
                break;
            }
    } if (rotation == 3) {
        for (int j = 0; j < length; j++)
            if (coordX-j < 0) {
                rotation++;
                break;
            }
    } if (rotation == 4)
            return 0;

    if (rotation == 1) {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX+i, coordY, i==0 ? 0 : 1, rotation) == 1)
                array[coordY][coordX+i] = INVALID_TILE;
            else
                array[coordY][coordX+i] = (char)SHIP_TILE;
        }
    } else if (rotation == 2) {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX, coordY-i, i==0 ? 0 : 1, rotation) == 1)
                array[coordY-i][coordX] = INVALID_TILE;
            else
                array[coordY-i][coordX] = (char)SHIP_TILE;
        }
    } else if (rotation == 3) {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX-i, coordY, i==0 ? 0 : 1, rotation) == 1)
                array[coordY][coordX-i] = INVALID_TILE;
            else
                array[coordY][coordX-i] = (char)SHIP_TILE;
        }
    } else  {
        for (int i = 0; i < length; i++) {
            if (scan3x3(array, coordX, coordY+i, i==0 ? 0 : 1, rotation) == 1)
                array[coordY+i][coordX] = INVALID_TILE;
            else
                array[coordY+i][coordX] = (char)SHIP_TILE;
        }

    }
    system(CLEAR);
    printBoard(array);

    return rotation;
}

int scan3x3(char array[BOARD_SIZE][BOARD_SIZE], int coordX, int coordY, int exception, int rotation) {
    /*
     * Funkcia pozera ci sa v rozmedzi 3x3 nenachadza ina lod pri pokladani
     * array: hracia plocha
     * coordX: suradnica X
     * coordY: suradnica Y
     * exception: vynimka, pozicia na ktorej je predosla kocka pri pokladani lode na plochu
     * rotation: smer otocenia lode
     */
    int offsetX, offsetY;

    for (int i = 0; coordX-1+i < coordX-1+3; i++) {
        if (coordX-1+i < 0 || coordX-1+i > 9)
            continue;

        for (int j = 0; coordY-1+j < coordY-1+3; j++) {
            if (coordY-1+j < 0 || coordY-1+j > 9)
                continue;

            if (coordY-1+j == coordY && coordX-1+i == coordX)
                continue;

            if (exception == 1) {
                if (rotation == 1) {
                    offsetX = coordX - 1;
                    offsetY = coordY;
                } else if (rotation == 2) {
                    offsetX = coordX;
                    offsetY = coordY + 1;
                } else if (rotation == 3) {
                    offsetX = coordX + 1;
                    offsetY = coordY;
                } else {
                    offsetX = coordX;
                    offsetY = coordY - 1;
                }

                if (coordY - 1 + j == offsetY && coordX - 1 + i == offsetX)
                    continue;
            }

            if (array[coordY-1+j][coordX-1+i] != WATER_TILE) {
                return 1;
            }
        }
    }

    return 0;
}
