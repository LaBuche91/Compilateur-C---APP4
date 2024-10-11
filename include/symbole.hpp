#ifndef SYMBOLE_H
#define SYMBOLE_H

#include <string>
#include <map>
#include <stack>

using namespace std;

//structure symbole
struct Symbole
{
    NodeType type;
    int position=-1;
};
//pile de map de Symbole
stack<map<string, Symbole>> pileSymboles;

//declaration des fonctions
Symbole *declare(string var);
Symbole *find(string var);
void begin();
void end();

void begin()
{
    //on crée une nouvelle map de Symbole et on la met sur la pile
    map<string, Symbole> m;
    pileSymboles.push(m);
}

void end()
{
    //on enlève la map de Symbole du dessus de la pile
    pileSymboles.pop();
}

Symbole *declare(string var)
{
    //si le Symbole n'existe pas, on le crée dans la map de Symbole
    if (pileSymboles.top().find(var) == pileSymboles.top().end())
    {
        Symbole s;
        pileSymboles.top()[var] = s;
        return &pileSymboles.top()[var];
    }
    else
    {
        cout << "Erreur : variable " << var << " déjà déclaré" << endl;
        exit(1);
    }
}

Symbole *find(string var)
{
    //on cherche dans la stack courante
    if (pileSymboles.top().find(var) != pileSymboles.top().end())
    {
        return &pileSymboles.top()[var];
    }
    else     //sinon on cherche dans la portée supérieure, et ainsi de suite...
    {
        stack<map<string, Symbole>> pileSymbolesTemp = pileSymboles;
        pileSymbolesTemp.pop();
        while (!pileSymbolesTemp.empty())
        {
            if (pileSymbolesTemp.top().find(var) != pileSymbolesTemp.top().end())
            {
                return new Symbole(pileSymbolesTemp.top()[var]);
            }
            pileSymbolesTemp.pop();
        }
    }
    //si on ne trouve pas, on retourne une erreur
    cout << "Erreur : variable " << var << " non déclaré" << endl;
    exit(1);
}

#endif // SYMBOLE_H