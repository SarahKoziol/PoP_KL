/*
 * Author: Sarah Koziol
 * Matrikelnummer: 915642
 * Exam: Wie kommt die Maus zum Käse?
 * For: Prozessorientierte Programmierung (Sommersemester 2016)
 */

#include <stdio.h> // originale zeile 1
#include <iostream>
#include <array>

enum ecell {
    NODATA = 0, WAND = 1, KAESE = 2, GASSE = 4, CHECK = 8
};

const int lheight = 7;
const int lwidth = 6;

ecell labyrinth[lheight][lwidth] = {
        {WAND, GASSE, WAND,  WAND,  WAND,  WAND},
        {WAND, GASSE, GASSE, GASSE, GASSE, WAND},
        {WAND, WAND,  GASSE, WAND,  GASSE, WAND},
        {WAND, GASSE, GASSE, WAND,  GASSE, WAND},
        {WAND, WAND,  GASSE, WAND,  WAND,  WAND},
        {WAND, KAESE, GASSE, GASSE, GASSE, WAND},
        {WAND, WAND,  WAND,  WAND,  WAND,  WAND}
};

int rekursionstiefe = 0;
int strecke = 0;

ecell get(int x, int y) {
    return (labyrinth[x][y]);
}

void setl(int x, int y, ecell val) {
//    labyrinth[x][y] |= val;
    labyrinth[x][y] = (ecell) ((int) labyrinth[x][y] | (int) val);
}

// 2b bspw. std::array<int, 2> statt void, return {x, y} dann
// alternativ bool und return true / false
void suche(int x, int y, int breite, int hoehe) {
    // setl(x, y, CHECK); könnte hier sein und müsste nicht mehrfach unten sein
    if (get(x, y) & KAESE) {
        setl(x, y, CHECK);
        printf("Käse in der Zelle [%d,%d] gefunden\n", x, y); // TODO 2b auskommentieren
        return;
    } else if (get(x, y) & GASSE && !(get(x, y) & CHECK)) {
        setl(x, y, CHECK);

        if (x + 1 < breite) {
            suche(x + 1, y, breite, hoehe);
        }
        if (y + 1 < hoehe) {
            suche(x, y + 1, breite, hoehe);
        }
        if (x - 1 >= 0) {
            suche(x - 1, y, breite, hoehe);
        }
        if (y - 1 >= 0) {
            suche(x, y - 1, breite, hoehe);
        }

        // Aufgabe 2g, diagonalen
        // an dieser stelle diagonal gehen als letzte option
//        if (x + 1 < breite && y + 1 < hoehe) {
//            suche(x + 1, y + 1, breite, hoehe);
//        }
//        if (x - 1 >= 0 && y + 1 < hoehe) {
//            suche(x - 1, y + 1, breite, hoehe);
//        }
//        if (x + 1 < breite && y - 1 >= 0) {
//            suche(x + 1, y - 1, breite, hoehe);
//        }
//        if (x - 1 >= 0 && y - 1 >= 0) {
//            suche(x - 1, y - 1, breite, hoehe);
//        }

        strecke++;
    } else {
        setl(x, y, CHECK);
    }
    // 2b bspw. return false
}

// Aufgabe 2a
void visualisieren() {
    for (int i = 0; i < lheight; i++) {
        for (int j = 0; j < lwidth; j++) {
            char charToOutput = '?';
            switch (get(i, j)) {
                case WAND:
                    charToOutput = '#';
                    break;
                case KAESE:
                    charToOutput = '*';
                    break;
                case GASSE:
                    charToOutput = '.';
                    break;
                case CHECK:
                    // Aufgabe 2d
                    charToOutput = 'x';
                    break;
                default:
                    // scheinbar werden die zellen nicht auf CHECK gesetzt, sondern CHECK addiert
                    // daher modulo CHECK (8), wenn rest überbleibt wurde die zelle modifiziert
                    if (get(i, j) % CHECK > 0) {
                        charToOutput = 'x';
                    }
                    break;
            }
            std::cout << charToOutput << ' ';
        }
        std::cout << std::endl;
    }
}

// Aufgabe 2e
int main() {
    std::cout << "Labyrinth: " << std::endl;
    visualisieren();
    suche(0, 1, lheight, lwidth); // 2b, auf return reagieren
    std::cout << "Untersuchte Zellen: " << std::endl;
    visualisieren(); // Aufgabe 2d
    std::cout << "Rekursionstiefe: " << rekursionstiefe << std::endl;
    std::cout << "Zurückgelegte Strecke: " << strecke << std::endl;
    return 0;
}

// Aufgabe 2f
// Muss ähnlich wie die Methode suche() verlaufen, jedoch ist das Ziel nicht "Käse" sondern "Koordinate"
