#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include "include/node.hpp"
#include "include/token.hpp"
#include "include/symbole.hpp"

using namespace std;

// variables globales
Token T;
Token L;
string code;
int position = 0;
Node *A;
static int cptVariables = 0;

// mots clés du langage
vector<string> mots_cles = {"if", "else", "while", "for", "do", "break", "continue", "return", "int", "char", "bool", "string", "void", "cin", "cout", "include", "namespace", "std", "using", "end", "true", "false", "debug", "recv", "send"};
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
        //cout << "EOF" << endl;
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
    //NEW
    case '[':
        T.type = tok_crochetouv;
        break;
    case ']':
        T.type = tok_crochetfer;
        break;
    //END NEW
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
        //cout << "mot clé : " << T.valeurStr << endl;
    }
    //cout << "Token : " << T.type << ":" << get_token_name(T.type) << " valStr:" << T.valeurStr << " valConst:" << T.valeurConst << " ligne:" << T.ligne << endl;
    return T;
};

// OK
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
        cout << "attendu : " << get_token_name(type) << " reçu : " << get_token_name(T.type) << endl;
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
        // cout << "ATOM1 => constante : " << L.valeurConst << endl;
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
        // cout << "ATOM3 => ident : " << L.valeurStr << endl;
        A = CreerNode(Nd_ref, L.valeurStr);
        return A;
    }
    else if(check(tok_recv)){
        A = CreerNode(Nd_recv);
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
    if(check(tok_parouv))
    {
        Node *appel = CreerNode(Nd_appel, A);
        while (!check(tok_parfer))
        {
            Node *E = Expression();
            AjouterEnfant(appel, E);
            check(tok_virg);
        }
        return appel;
    // NEW
    } else if(check(tok_crochetouv)){ //LBracket
        //cout << "LBracket" << endl;
        Node *plus = CreerNode(Nd_plus, A);
        Node *E = Expression();
        AjouterEnfant(plus, E);
        A = CreerNode(Nd_indirection, plus);
        accept(tok_crochetfer);
        check(tok_virg);
    }
    // END NEW
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
    //NEW
    else if(check(tok_and)) //si c'est un pointeur (adresse)
    {
        A = prefix();
        return CreerNode(Nd_adresse, A->valeur, A);
    }
    else if(check(tok_mult)) //si c'est un pointeur (indirection)
    {
        A = prefix();
        return CreerNode(Nd_indirection, A->valeur, A);
    }
    //END NEW
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
        //NEW
        while (check(tok_mult)){}
        //END NEW
        accept(tok_ident);        
        Node *R = CreerNode(Nd_declaration, L.valeurStr);
        accept(tok_pv);
        return R;
    }
    else if (check(tok_if))
    {
        accept(tok_parouv);
        Node *R = Expression();
        accept(tok_parfer);
        Node *R1 = Instruction();
        if (check(tok_else))
        {
            Node *R2 = Instruction();
            return CreerNode(Nd_cond, R->valeur, R, R1, R2);
        }
        return CreerNode(Nd_cond, R->valeur, R, R1);
    }
    else if (check(tok_while))
    {
        accept(tok_parouv);
        Node *E = Expression();
        accept(tok_parfer);
        Node *I = Instruction();
        Node *loop = CreerNode(Nd_loop);
        Node *condition = CreerNode(Nd_cond);
        Node *b = CreerNode(Nd_break);
        Node *ancre = CreerNode(Nd_ancre);
        AjouterEnfant(condition, E);
        AjouterEnfant(condition, I);
        AjouterEnfant(condition, b);
        AjouterEnfant(loop, ancre);
        AjouterEnfant(loop, condition);
        return loop;
    }
    else if (check(tok_do))
    {
        Node *R1 = Instruction();
        accept(tok_while);
        accept(tok_parouv);
        Node *R2 = Expression();
        accept(tok_parfer);
        accept(tok_pv);
        Node *loop = CreerNode(Nd_loop);
        Node *ancre = CreerNode(Nd_ancre);
        Node *condition = CreerNode(Nd_cond);
        Node *b = CreerNode(Nd_break);
        Node *n = CreerNode(Nd_not_unaire);
        AjouterEnfant(n, R2);
        AjouterEnfant(condition, n);
        AjouterEnfant(condition, b);
        AjouterEnfant(loop, ancre);
        AjouterEnfant(loop, R1);
        AjouterEnfant(loop, condition);
        return loop;
    }
    else if (check(tok_for))
    {
        accept(tok_parouv);
        Node *E1 = Expression();
        accept(tok_pv);
        Node *E2 = Expression();
        accept(tok_pv);
        Node *E3 = Expression();
        accept(tok_parfer);
        Node *I = Instruction();
        Node *ancre = CreerNode(Nd_ancre);
        Node *b = CreerNode(Nd_break);
        Node *cond = CreerNode(Nd_cond, E2->valeur, E2, I, b);
        Node *loop=  CreerNode(Nd_loop, E1->valeur,cond, ancre , E3);
        //cout << "loop : " << loop<< endl;
        return CreerNode(Nd_seq, E1, loop);
    }
    else if (check(tok_break))
    {
        accept(tok_pv);
        return CreerNode(Nd_break);
    }
    else if (check(tok_continue))
    {
        accept(tok_pv);
        return CreerNode(Nd_continue);
    }
    else if (check(tok_return))
    {
        Node *R = Expression();
        accept(tok_pv);
        return CreerNode(Nd_ret, R);
    }
    else if(check (tok_recv)){
        Node *R = Expression();
        accept(tok_pv);
        return CreerNode(Nd_recv, R);
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
    // fonction
    accept(tok_int);
    while (check(tok_mult)){}
    accept(tok_ident);
    //cout<<"nom fonction : "<<L.valeurStr<<endl;
    Node *R = CreerNode(Nd_fonction, L.valeurStr);
    accept(tok_parouv);
    while (!check(tok_parfer))
    {
        accept(tok_int);
        while (check(tok_mult)){}
        accept(tok_ident);
        Node *R2 = CreerNode(Nd_declaration, L.valeurStr);
        AjouterEnfant(R, R2);
        check(tok_virg);
    }
    Node *I = Instruction();
    AjouterEnfant(R, I);
    return R;
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
        //cout << "bloc" << endl;
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
    {
        if (N->enfants[0]->type != Nd_ref && N->enfants[0]->type != Nd_indirection)
        {
            cout << "Erreur sémentique : il faut une variable à gauche de l'affectation" << endl;
            exit(1);
        }
        for (int i = 0; i < N->Nenfants; i++)
        {
            AnaSemantique(N->enfants[i]);
        }
        break;
    }
    case Nd_fonction:
    {
        //cout << "fonction : " << N->valeur << endl; //debug
        Symbole *s = declare(N->valeur); 
        //cout<<"la"<<endl;
        s->type = Nd_fonction;
        begin();
        cptVariables = 0;
        for (int i = 0; i < N->enfants.size(); i++)
        {
            //cout<<"anaSemantique"<<endl;
            AnaSemantique(N->enfants[i]);
        }
        end();
        //cout<<"end"<<endl;
        N->position = cptVariables - (N->enfants.size() - 1);
        break;
    }
    case Nd_appel:
    {
        if (N->enfants[0]->type != Nd_ref)
        {
            cout << "Erreur sémentique : il faut une fonction à appeler" << endl;
            exit(1);
        }
        Symbole *s = find(N->enfants[0]->valeur);
        if (s->type != Nd_fonction)
        {
            cout << "Erreur sémentique : " << N->enfants[0]->valeur << " n'est pas une fonction" << endl;
            exit(1);
        }
        for (int i = 1; i < N->enfants.size(); i++)
        {
            AnaSemantique(N->enfants[i]);
        }
        break;
    }
    //NEW
    case Nd_adresse:
        if(N->enfants[0]->type != Nd_ref)
        {
            cout << "Erreur sémentique : il faut une variable à prendre l'adresse" << endl;
            exit(1);
        }
        AnaSemantique(N->enfants[0]);
        break;
    //END NEW
    default:
        if (N->enfants.size() > 0)
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
    cout << "  prep main" << endl;
    cout << "  call 0" << endl;
    cout << "  halt" << endl;
    //begin ici pour les bibliothèque standard
    begin();
    for (int i = 1; i < argc; i++)
    {
        position = 0;
        analex(argv[i]);
        while (T.type != tok_eof)
        {
            Node *N = AnaSyntaxique();
            cptVariables = 0;
            T.ligne = 1; // on remet la ligne à 1
            //cout << "anaSyntaxique" << endl;
            AnaSemantique(N); 
            N = Optimisation(N);
            genCode(N);
        }
    }
    end(); //end pour bibliothèque standard
}