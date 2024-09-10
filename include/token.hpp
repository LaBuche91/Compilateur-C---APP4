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

const char *token_names[] = {
    "", "tok_eof", "tok_ident", "tok_constante", "tok_plus", "tok_moin", "tok_mult", "tok_div",
    "tok_not", "tok_and", "tok_or", "tok_egal", "tok_diff", "tok_inf", "tok_infeg", "tok_sup",
    "tok_supeg", "tok_affect", "tok_pv", "tok_virg", "tok_parouv", "tok_parfer", "tok_accolouv",
    "tok_accolfer", "tok_mod", "tok_if", "tok_else", "tok_while", "tok_for", "tok_do",
    "tok_break", "tok_continue", "tok_return", "tok_int", "tok_char", "tok_bool",
    "tok_string", "tok_void", "tok_main", "tok_cin", "tok_cout", "tok_include",
    "tok_namespace", "tok_std", "tok_using", "tok_end", "tok_true", "tok_false", "tok_debug"};

const char *get_token_name(int token)
{
    if (token >= 1 && token <= 47)
    {
        return token_names[token];
    }
    else
    {
        return "Unknown token";
    }
};

#endif // TOKEN_H