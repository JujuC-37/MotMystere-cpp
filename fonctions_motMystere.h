#ifndef FONCTIONS_MOTMYSTERE_H_INCLUDED
#define FONCTIONS_MOTMYSTERE_H_INCLUDED

#include <string>
#include <iostream>
#include <ctype.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

enum etape
{
    motMystere_1=1,
    motPropose_2
};

int demandeGarderScores();
bool controleSaisie(string &mot, etape &niveauEtape);
string saisieMotPropose(string motMystereMelange);
string mettreEnMajuscules(string &mot);
int saisieNiveau();
string melangerMot(string motDepart);
string renvoiMotMystere(int niveauChoisi);
void enregistrerScore(int nombreCoups, int reinitialiser);
void afficherDerniersScores();
void demandeAffichageScore();
double calculMoyenne();
void demandeAffichageMoyenne();

#endif // FONCTIONS_MOTMYSTERE_H_INCLUDED
