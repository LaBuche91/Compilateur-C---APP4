#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include "node.h"
#include "token.h"
#include "symbole.h"

using namespace std;

// variables globales
Token T;
Token L;
string code;
int position = 0;
Node *A;
static int cptVariables = 0;

// mots clés du langage
vector<string> mots_cles = {"if", "else", "while", "for", "do", "break", "continue", "return", "int", "char", "bool", "string", "void", "main", "cin", "cout", "include", "namespace", "std", "using", "end", "true", "false", "debug"};

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

//-----------------------------ANALYSE LEXICALE--------------------------------
// ' ', '\t', '\n', '\r', '\0', '+', '-', '*', '/', '!', '&', '|', '=', '<', '>', ';', ',', '(', ')', '%', '{', '}'
Token lireToken()
{
    char c;
    c = code[position++];
    // on remet le token T à zéro
    T.valeurConst = 0;
    T.valeurStr = "";
    while (c == ' ' || c == '\t' || c == '\n' || c == '\r')
    {
        if (c == '\n')
            T.ligne++;
        c = code[position++];
    }
    if (c == '\0')
    {
        T.type = tok_eof;
        return T;
    }
    switch (c)
    {
    case '+':
        T.type = tok_plus;
        break;
    case '-':
        T.type = tok_moin;
        break;
    case '*':
        T.type = tok_mult;
        break;
    case '/':
        T.type = tok_div;
        break;
    case '!':
        T.type = tok_not;
        if (code[position] == '=')
        {
            T.type = tok_diff;
            position++;
        }
        break;
    case '&':
        T.type = tok_and;
        if (code[position] == '&')
        {
            T.type = tok_and;
            position++;
        }
        break;
    case '|':
        T.type = tok_or;
        if (code[position] == '|')
        {
            T.type = tok_or;
            position++;
        }
        break;
    case '=':
        T.type = tok_affect;
        if (code[position] == '=')
        {
            T.type = tok_egal;
            position++;
        }
        break;
    case '<':
        T.type = tok_inf;
        if (code[position] == '=')
        {
            T.type = tok_infeg;
            position++;
        }
        break;
    case '>':
        T.type = tok_sup;
        if (code[position] == '=')
        {
            T.type = tok_supeg;
            position++;
        }
        break;
    case ';':
        T.type = tok_pv;
        break;
    case ',':
        T.type = tok_virg;
        break;
    case '(':
        T.type = tok_parouv;
        break;
    case ')':
        T.type = tok_parfer;
        break;
    case '%':
        T.type = tok_mod;
        break;
    case '{':
        T.type = tok_accolouv;
        break;
    case '}':
        T.type = tok_accolfer;
        break;
    }
    if (c >= '0' && c <= '9')
    {
        T.type = tok_constante;
        T.valeurConst = c - '0';
        while (code[position] >= '0' && code[position] <= '9')
        {
            T.valeurConst = T.valeurConst * 10 + code[position] - '0'; // conversion de char en int
            position++;
        }
    }
    if (c >= 'a' && c <= 'z')
    {
        T.type = tok_ident;
        T.valeurStr = c;
        while ((code[position] >= 'a' && code[position] <= 'z') || (code[position] >= '0' && code[position] <= '9'))
        {
            T.valeurStr += code[position];
            position++;
        }
        for (int i = 0; i < mots_cles.size(); i++)
        {
            if (T.valeurStr == mots_cles[i])
            {
                T.type = tok_if + i;
                T.valeurStr = mots_cles[i];
                break;
            }
        }
    }
    return T;
};

//OK
void next()
{
    L = T;
    T = lireToken();
    //cout << "Token : "<<T.type <<":"<<get_token_name(T.type) << " valStr:" << T.valeurStr << " valConst:" << T.valeurConst << " ligne:" << T.ligne << endl;
};

bool check(int type)
{
    if (T.type != type)
        return false;
    next();
    return true;
};

void accept(int type)
{
    if (T.type != type)
    {
        cout << "Erreur de syntaxe à la ligne" << T.ligne << endl;
        cout<< "attendu : "<<get_token_name(type)<<" reçu : "<<get_token_name(T.type)<<endl;
        exit(1);
    }
    next();
};

void analex(string fileName)
{
    ifstream file(fileName);
    if (file)
    {
        // on extraie le code du fichier
        code = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        // code ="(3+1) * 2 - 10 / 5 % 2 + (4 && 1) || (!0) ==1 != 2 < 3 <=4 > 5 >= 6";
        file.close();
        next();
    }
    else
    {
        cout << "Erreur lors de l'ouverture du fichier" << endl;
        exit(1);
    }
};

//----------------------------ANALYSE SYNTAXIQUE--------------------------------
Node *Atom()
{
    if (check(tok_constante))
    {
        cout << "ATOM1 => constante : " << L.valeurConst << endl;
        A = CreerNode(Nd_const, to_string(L.valeurConst));
        return A;
    }
    else if (check(tok_parouv))
    {
        A = Expression();
        accept(tok_parfer);
        return A;
    }
    else if (check(tok_ident))
    {
        cout << "ATOM3 => ident : " << L.valeurStr << endl;
        A = CreerNode(Nd_ref, L.valeurStr);
        return A;
    }
    else
    {
        cout << "Erreur de syntaxe à la ligne " << T.ligne << endl;
        exit(1);
    }
}

Node *suffix()
{
    A = Atom();
    return A;
};

Node *prefix()
{
    if (check(tok_plus))
    {
        A = prefix();
        return A;
    }
    else if (check(tok_moin))
    {
        A = prefix();
        return CreerNode(Nd_moins_unaire, A->valeur, A);
    }
    else if (check(tok_not))
    {
        A = prefix();
        return CreerNode(Nd_not_unaire, A->valeur, A);
    }
    else
    {
        A = suffix();
        return A;
    }
};

Node *Expression()
{
    return Expression2(0);
};

Node *Expression2(int prioriteMinimal)
{
    Node *A1 = prefix();
    while (T.type != tok_eof)
    {
        optional<ExpressionType> op = findByType(T.type);
        if (!op || op->priorite < prioriteMinimal)
        { // op == NULL || op.priorite < prioriteMinimal comment gérer le cas où op est NULL ???
            return A1;
        }
        next();
        Node *A2 = Expression2(op->priorite + op->associativite);
        A1 = CreerNode(op->NodeOperandes, A1, A2);
    }
    return A1;
}

Node *Instruction()
{
    if (check(tok_debug))
    {
        Node *R = Expression();
        accept(tok_pv);
        return CreerNode(Nd_debug, R->valeur, R);
    }
    else if (check(tok_accolouv))
    {
        Node *R = CreerNode(Nd_bloc);
        while (!check(tok_accolfer))
        {
            AjouterEnfant(R, Instruction());
        }
        return R;
    }
    else if (check(tok_int))
    {
        accept(tok_ident);
        Node *R = CreerNode(Nd_declaration, L.valeurStr);
        accept(tok_pv);
        return R;
    }
    else
    {
        Node *R = Expression();
        accept(tok_pv);
        return CreerNode(Nd_drop, R);
    }
};

Node *Fonction()
{
    return Instruction();
};

Node *AnaSyntaxique()
{
    return Fonction();
};

Node *AnaSemantique(Node *N)
{
    switch (N->type)
    {
    case Nd_bloc:
        begin();
        for (int i = 0; i < N->Nenfants; i++)
        {
            AnaSemantique(N->enfants[i]);
        }
        end();
        break;
    case Nd_ref:
    {
        Symbole *s = find(N->valeur);
        if (s->type != Nd_int)
        {
            cout << "Erreur : variable " << N->valeur << " doit être un entier, type actuel : " << s->type << endl;
            exit(1);
        }
        N->position = s->position;
        break;
    }
    case Nd_declaration:
    {
        Symbole *s = declare(N->valeur);
        s->type = Nd_int;
        s->position = cptVariables++;
        break;
    }
    case Nd_affecter_unaire:
        if (N->enfants[0]->type != Nd_ref)
        {
            cout << "Erreur sémentique : il faut une variable à gauche de l'affectation" << endl;
            exit(1);
        }
        for (int i = 0; i < N->Nenfants; i++)
        {
            AnaSemantique(N->enfants[i]);
        }
    default:
        if (N->Nenfants > 0)
        {
            for (int i = 0; i < N->Nenfants; i++)
            {
                AnaSemantique(N->enfants[i]);
            }
        }
        break;
    }
    return N;
};

int main(int argc, char *argv[])
{
    cout << ".start" << endl;
    for (int i = 1; i < argc; i++)
    {
        analex(argv[i]);
        while (T.type != tok_eof)
        {
            Node *N = AnaSyntaxique();
            AnaSemantique(N);
            // N = Optim(N);
            cout<<"resn "<<cptVariables<<endl;
            genCode(N);
            cout<<"drop "<<cptVariables<<endl;
        }
    }
    // cout<<"dbg"<<endl;
    cout << "halt" << endl;
}
