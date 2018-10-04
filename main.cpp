#include <iostream>
#include <string>

#include "fonctions_motMystere.h"

using namespace std;

enum reponse
{
    motTrouve,
    motCherche,
    abandon
};


int main(int argc, char **argv)
{
    bool arret(0);



    cout << endl << "<------------------------------- Mot Mystere ------------------------------->" << endl << endl;

    cout << "Le but du jeu est de retrouver le mot dont les lettres ont ete melangees. Le nombre de coups est compte." << endl << "Moins il y a de coups, mieux c'est !" << endl << endl;

    //réinitialisation des statistiques
        int garderScores(0);
        garderScores = demandeGarderScores();

        system("cls"); //effacer la console

    do
    {
        cout << endl << "<------------------------------- Mot Mystere ------------------------------->" << endl << endl;

        cout << "Le but du jeu est de retrouver le mot dont les lettres ont ete melangees. Le nombre de coups est compte." << endl << "Moins il y a de coups, mieux c'est !" << endl << endl;

        int const nombreCoupsMax(4);

    //saisie du niveau
        int niveauChoisi;
        niveauChoisi = saisieNiveau();

    //instructions à l'utilisateur
        cout << endl << "Il y a " << nombreCoupsMax << " essais possibles." << endl << "Pour abandonner, saisir x (en minuscule). Cela donnera " << nombreCoupsMax+1 << " points." << endl;

    //contrôle de la saisie du mot + MAJUSCULES
        string motMystere("mystere");

        motMystere = renvoiMotMystere(niveauChoisi);
        motMystere = mettreEnMajuscules(motMystere);
        //cout << "mot Mystere : " << motMystere << endl;

    //jeu
        reponse reponseJoueur(motCherche);
        string motPropose("0"), motMelange("0");
        int nombreCoups(1);

        do
        {
            motMelange = melangerMot(motMystere);
            motPropose = saisieMotPropose(motMelange);

            if (motPropose==motMystere)
            {
                reponseJoueur = motTrouve;
                cout << "Bravo ! Le mot mystere est bien : " << motMystere << endl;
                enregistrerScore(nombreCoups,garderScores);
                    //cout << "Nombre de coups : " << nombreCoups; //controle
            }
            else if (motPropose=="x" || nombreCoups>nombreCoupsMax)
            {
                reponseJoueur = abandon;
                cout << "Dommage ! Le mot mystere etait : " << motMystere << endl;
                enregistrerScore(nombreCoupsMax+1,garderScores);
            }

            nombreCoups++;

        }while(reponseJoueur==motCherche);

    //demande de rejouer

        cout << endl << "Voulez-vous rejouer (0) ou arreter (1) ? ";
        cin >> arret;

        if (!arret)
        {
            system("cls"); //effacer la console
        }
        else
        {
            system("cls"); //effacer la console
            cout << endl << "<------------------------------- Mot Mystere ------------------------------->" << endl << endl;
            cout << "Le but du jeu est de retrouver le mot dont les lettres ont ete melangees. Le nombre de coups est compte." << endl << "Moins il y a de coups, mieux c'est !" << endl << endl;

        }

    }while(!arret);


    demandeAffichageScore();
    demandeAffichageMoyenne();

    cout << endl << endl <<  "----------------------------------------------------------------------------" << endl;
    cout << "                  Taper sur une touche pour fermer le jeu." << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    return 0;
}
