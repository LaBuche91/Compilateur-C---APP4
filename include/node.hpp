#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <map>
#include <optional>

using namespace std;

static int nbLabel = 0;
//variable globale pour les labels
static int labelBoucles = 0;

// énumération des type de Node
enum NodeType
{
    Nd_const = 1,
    Nd_not_unaire = 2,
    Nd_moins_unaire = 3,
    Nd_affecter_unaire = 4,
    Nd_plus = 5,
    Nd_mul = 6,
    Nd_div = 7,
    Nd_mod = 8,
    Nd_minus_operation = 9,
    Nd_less_operation = 10,
    Nd_less_or_equal_operation = 11,
    Nd_equal_operation = 12,
    Nd_not_equal_operation = 13,
    Nd_greater_operation = 14,
    Nd_greater_or_equal_operation = 15,
    Nd_and_operation = 16,
    Nd_or_operation = 17,
    Nd_debug = 18,
    Nd_bloc = 19,
    Nd_drop = 20,
    Nd_ref = 21,
    Nd_declaration = 22,
    Nd_int = 23,
    Nd_cond = 24,
    Nd_loop = 25, //execute les instructions à l'infini
    Nd_break = 26,//sort de la loop
    Nd_continue = 27,//continue la loop
    Nd_ancre = 28, //sert revenir a un noeud lors d'un continue dans une boucle
};

map<int, string> NodeNames = {
    {Nd_plus, "add"},
    {Nd_mul, "mul"},
    {Nd_div, "div"},
    {Nd_mod, "mod"},
    {Nd_minus_operation, "sub"},
    {Nd_less_operation, "cmplt"},
    {Nd_less_or_equal_operation, "cmple"},
    {Nd_equal_operation, "cmpeq"},
    {Nd_greater_operation, "cmpgt"},
    {Nd_greater_or_equal_operation, "cmpge"},
    {Nd_not_equal_operation, "cmpne"},
    {Nd_and_operation, "and"},
    {Nd_or_operation, "or"},
    {Nd_bloc, ""},       // car juste enchainement d'instruction
    {Nd_drop, "drop 1"}, // drop 1 pour le moment
    {Nd_debug, "dbg"},
};

enum TokenType
{
    tok_eof = 1,
    tok_ident = 2,
    tok_constante = 3,
    tok_plus = 4,
    tok_moin = 5,
    tok_mult = 6,
    tok_div = 7,
    tok_not = 8,
    tok_and = 9,
    tok_or = 10,
    tok_egal = 11,
    tok_diff = 12,
    tok_inf = 13,
    tok_infeg = 14,
    tok_sup = 15,
    tok_supeg = 16,
    tok_affect = 17,
    tok_pv = 18,
    tok_virg = 19,
    tok_parouv = 20,
    tok_parfer = 21,
    tok_accolouv = 22,
    tok_accolfer = 23,
    tok_mod = 24,
    tok_if = 25,
    tok_else = 26,
    tok_while = 27,
    tok_for = 28,
    tok_do = 29,
    tok_break = 30,
    tok_continue = 31,
    tok_return = 32,
    tok_int = 33,
    tok_char = 34,
    tok_bool = 35,
    tok_string = 36,
    tok_void = 37,
    tok_main = 38,
    tok_cin = 39,
    tok_cout = 40,
    tok_include = 41,
    tok_namespace = 42,
    tok_std = 43,
    tok_using = 44,
    tok_end = 45,
    tok_true = 46,
    tok_false = 47,
    tok_debug = 48
};

// structure ExpressionType
struct ExpressionType
{
    TokenType tokenType;
    int priorite;
    int associativite;
    NodeType NodeOperandes;

    ExpressionType(TokenType tokenType, int priorite, int associativite, NodeType NodeOperandes)
    {
        this->tokenType = tokenType;
        this->priorite = priorite;
        this->associativite = associativite;
        this->NodeOperandes = NodeOperandes;
    }
};

// constantes des ExpressionType
const ExpressionType TOKEN_MUL(tok_mult, 7, 1, Nd_mul);
const ExpressionType TOKEN_DIV(tok_div, 7, 1, Nd_div);
const ExpressionType TOKEN_MODULO(tok_mod, 7, 1, Nd_mod);

const ExpressionType TOKEN_PLUS(tok_plus, 6, 1, Nd_plus);
const ExpressionType TOKEN_MOINS(tok_moin, 6, 1, Nd_minus_operation);

const ExpressionType TOKEN_LESS(tok_inf, 5, 1, Nd_less_operation);
const ExpressionType TOKEN_LESS_OR_EQUAL(tok_infeg, 5, 1, Nd_less_or_equal_operation);
const ExpressionType TOKEN_GREATER(tok_sup, 5, 1, Nd_greater_operation);
const ExpressionType TOKEN_GREATER_OR_EQUAL(tok_supeg, 5, 1, Nd_greater_or_equal_operation);

const ExpressionType TOKEN_EQUAL(tok_egal, 4, 1, Nd_equal_operation);
const ExpressionType TOKEN_NOT_EQUAL(tok_diff, 4, 1, Nd_not_equal_operation);

const ExpressionType TOKEN_AND(tok_and, 3, 1, Nd_and_operation);

const ExpressionType TOKEN_OR(tok_or, 2, 1, Nd_or_operation);

const ExpressionType TOKEN_AFFECT(tok_affect, 1, 1, Nd_affecter_unaire);

struct Node
{
    int type;
    string valeur;
    int position = -1;
    int Nenfants = 0; // si pas initialisé, le tout marche pas ???????
    vector<Node *> enfants;
};

// déclaration des fonctions Atom, suffix, prefix, Expression, Instruction, Fonction, AnaSyntaxique
Node *Atom();
Node *suffix();
Node *prefix();
Node *Expression();
Node *Expression2(int priorite);
Node *Instruction();
Node *Fonction();
Node *AnaSyntaxique();
Node *AnaSemantique(Node *N);
void genCode(Node *N);

// déclaration des fonctions CreerNode, AjouterEnfant
Node *CreerNode(int type);
Node *CreerNode(int type, string valeur);
Node *CreerNode(int type, string valeur, Node *enfant);
Node *CreerNode(int type, Node *enfant, Node *enfant2);
Node *CreerNode(int type, string valeur, Node *enfant, Node *enfant2);
Node *CreerNode(int type, string valeur, Node *enfant, Node *enfant2, Node *enfant3);
Node *CreerNode(int type, string valeur, Node *enfant, Node *enfant2, Node *enfant3, Node *enfant4);
void AjouterEnfant(Node *N, Node *enfant);

// trouver le type de l'expression selon le token
optional<ExpressionType> findByType(int tokenType)
{
    switch (tokenType)
    {
    case tok_mult:
        return TOKEN_MUL;
    case tok_div:
        return TOKEN_DIV;
    case tok_mod:
        return TOKEN_MODULO;
    case tok_plus:
        return TOKEN_PLUS;
    case tok_moin:
        return TOKEN_MOINS;
    case tok_inf:
        return TOKEN_LESS;
    case tok_infeg:
        return TOKEN_LESS_OR_EQUAL;
    case tok_sup:
        return TOKEN_GREATER;
    case tok_supeg:
        return TOKEN_GREATER_OR_EQUAL;
    case tok_egal:
        return TOKEN_EQUAL;
    case tok_diff:
        return TOKEN_NOT_EQUAL;
    case tok_and:
        return TOKEN_AND;
    case tok_or:
        return TOKEN_OR;
    case tok_affect:
        return TOKEN_AFFECT;
    default:
        return nullopt;
    }
};

Node *CreerNode(int type)
{
    Node *N = new Node;
    N->type = type;
    N->Nenfants = 0;
    return N;
};

Node *CreerNode(int type, string valeur)
{
    Node *N = new Node;
    N->type = type;
    N->valeur = valeur;
    N->Nenfants = 0;
    return N;
};

Node *CreerNode(int type, Node *enfant)
{
    Node *N = new Node;
    N->type = type;
    AjouterEnfant(N, enfant);
    return N;
};

Node *CreerNode(int type, string valeur, Node *enfant)
{
    Node *N = new Node;
    N->valeur = valeur;
    N->type = type;
    AjouterEnfant(N, enfant);
    return N;
};

Node *CreerNode(int type, Node *enfant, Node *enfant2)
{
    Node *N = new Node;
    N->type = type;
    AjouterEnfant(N, enfant);
    AjouterEnfant(N, enfant2);
    return N;
};

Node *CreerNode(int type, string valeur, Node *enfant, Node *enfant2)
{
    Node *N = new Node;
    N->type = type;
    N->valeur = valeur;
    AjouterEnfant(N, enfant);
    AjouterEnfant(N, enfant2);
    return N;
};

Node *CreerNode(int type, string valeur, Node *enfant, Node *enfant2, Node *enfant3)
{
    Node *N = new Node;
    N->type = type;
    N->valeur = valeur;
    AjouterEnfant(N, enfant);
    AjouterEnfant(N, enfant2);
    AjouterEnfant(N, enfant3);
    return N;
};

Node *CreerNode(int type, string valeur, Node *enfant, Node *enfant2, Node *enfant3, Node *enfant4)
{
    Node *N = new Node;
    N->type = type;
    N->valeur = valeur;
    AjouterEnfant(N, enfant);
    AjouterEnfant(N, enfant2);
    AjouterEnfant(N, enfant3);
    AjouterEnfant(N, enfant4);
    return N;
};

void AjouterEnfant(Node *N, Node *enfant)
{
    N->enfants.push_back(enfant);
    N->Nenfants++;
};

void genCode(Node *N)
{
    if (N->type == Nd_plus || N->type == Nd_mul || N->type == Nd_div || N->type == Nd_mod || N->type == Nd_minus_operation || N->type == Nd_less_operation || N->type == Nd_less_or_equal_operation || N->type == Nd_equal_operation || N->type == Nd_not_equal_operation || N->type == Nd_greater_operation || N->type == Nd_greater_or_equal_operation || N->type == Nd_and_operation || N->type == Nd_or_operation || N->type == Nd_bloc || N->type == Nd_drop || N->type == Nd_debug)
    {
        for (int i = 0; i < N->Nenfants; i++) // Use N->Nenfants instead of N->enfants.size()
        {
            genCode(N->enfants[i]);
        }
        if (NodeNames[N->type] != "")
        {
            cout << "  " << NodeNames[N->type] << endl;
        }
    }
    else
    {
        switch (N->type)
        {
        case Nd_declaration:
            break;
        case Nd_ref:
            cout << "  get " << N->position << endl;
            break;
        case Nd_affecter_unaire:
            genCode(N->enfants[1]);
            cout << "  dup" << endl;
            cout << "  set " << N->enfants[0]->position << endl;
            break;
        case Nd_const:
            cout << "  push " << N->valeur << endl;
            break;
        case Nd_not_unaire:
            genCode(N->enfants[0]);
            cout << "  not" << endl;
            break;
        case Nd_moins_unaire:
            cout << "  push 0" << endl;
            genCode(N->enfants[0]);
            cout << "  sub" << endl;
            break;
        case Nd_cond:
        {
            int tmp = nbLabel++;
            genCode(N->enfants[0]);
            cout << "  jumpf l1_"<<tmp << endl;
            genCode(N->enfants[1]);
            int tmp2 = nbLabel++;
            cout << "  jump l2_"<<tmp2 << endl;
            cout << ".l1_"<<tmp << endl;
            if(N->Nenfants >= 3) genCode(N->enfants[2]);//problème ici
            cout << ".l2_"<<tmp2<< endl; 
            break;
        }
        case Nd_loop:
        {
            int l = nbLabel++;
            int tmp = labelBoucles;
            labelBoucles = l;
            cout << ".l1_"<<l<< endl;
            for (int i = 0; i < N->Nenfants; i++)
            {
                genCode(N->enfants[i]);
            }
            cout << "  jump l1_"<<l << endl;
            cout<<".l2_"<<l<<endl;
            labelBoucles = tmp;
            break;
        }
        case Nd_break:
            cout << "  jump l2_"<<labelBoucles<< endl;
            break;
        case Nd_ancre:
            cout << ".l3_"<<labelBoucles<< endl;
            break;
        case Nd_continue:
            cout << "  jump l3_"<<labelBoucles<< endl;
            break;
        default:
            break;
        }
    }
};
#endif // NODE_H