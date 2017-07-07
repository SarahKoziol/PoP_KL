#include <iostream>

/*
 * Author: Sarah Koziol, MATRIKELNUMMER
 * Date: 2017-07-07
 * Project: Klausur
 * For: Prozessorientierte Programmierung (Sommersemester 2016)
 */

#include <stdio.h> // zeile 1

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

ecell get(int x, int y) {
    return (labyrinth[x][y]);
}

void setl(int x, int y, ecell val) {
//    labyrinth[x][y] |= val;
    labyrinth[x][y] = (ecell) ((int) labyrinth[x][y] | (int) val);
}

void suche(int x, int y, int breite, int hoehe) {
    if (get(x, y) & KAESE) {
        setl(x, y, CHECK);
        printf("Käse in der Zelle [%d,%d] gefunden\n", x, y);
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
    } else setl(x, y, CHECK);
}

// Aufgabe 2a
void visualisieren() {
    for (int i = 0; i < lheight; i++) {
        for (int j = 0; j < lwidth; j++) {
            char charToOutput;
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
                    break;
                default:
                    break;
            }
            std::cout << charToOutput << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    visualisieren();
    suche(0, 1, lheight, lwidth);
    return 0;
}
