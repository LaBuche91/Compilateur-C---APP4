#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

struct Token {
	int type;
	int ligne=1;
	int valeurConst; // pour les constante
    string valeurStr; // pour les chaine de caractère
};

#endif // TOKEN_H