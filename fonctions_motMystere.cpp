#include "fonctions_motMystere.h"

using namespace std;


/*int demandeGarderScores()
demande à l'utilisateur s'il veut garder ses scores ou non.

renvoie un int : 0 si oui, 1 sinon
*/
int demandeGarderScores()
{
    string garder("0");
    int compteur(0);

    do
    {
        if (compteur==0)
        {
            cout << "Voulez-vous garder vos scores (1) ou les effacer (0) ? ";
            cin >> garder;
        }
        else
        {
            cout << "Il faut saisir 1 ou 0 : ";
            cin >> garder;
        }
        compteur++;
    }while(garder!="0" && garder!="1");

    int garderScore(0);
    garderScore = atoi(garder.c_str());

    return garderScore;
}


/* controleSaisie(string &mot, etape niveauEtape)
vérifie si le mot saisi (variable mot) est correct selon l'étape (variable niveauEtape) :
étape motMystere_1 : uniquement des lettres non accenutées, min ou MAJ
étape motPropose_2 : uniquement des lettres non accentuées, MAJ uniquement

renvoie un booléen :
TRUE si la saisie est correcte, FALSE sinon
*/
bool controleSaisie(string &mot, etape niveauEtape)
{
    bool saisieCorrecte(true);
    size_t i(0);

    if (niveauEtape==motMystere_1)
    {
        while (saisieCorrecte==true && i<mot.size())
        {
            if(!isalpha(mot[i]))
            {
                saisieCorrecte = false;
            }
            else
            {
                i++;
            }
        }
    }
    else if (niveauEtape==motPropose_2)
    {
        if (mot!="x")
        {
            while (saisieCorrecte==true && i<mot.size())
            {
                if(mot[i]>64 && mot[i]<91) //lettres MAJ
                {
                    i++;
                }
                else
                {
                    saisieCorrecte = false;
                }
            }
        }

    }

    return saisieCorrecte;
}

/*saisieMotPropose(string motMystereMelange)
- propose un anagramme du mot mystere (variable motMystereMelange) à l'utilisateur et lui demande une réponse
    -1ère demande : juste une demande
    -demande(s) suivante(s) : demande + remarque sur ce qu'il faut saisir
- contrôle la réponse (fonction controleSaisie ou "x" pour arrêter la partie)

renvoie un string : le mot proposé (et contrôlé)
*/
string saisieMotPropose(string motMystereMelange)
{
    bool saisieCorrecte(false);
    size_t i(0);
    string motPropose;

    do
    {
        if(i==0)//proposition de l'anagramme
        {
            //demande
            cout << endl << "Quel est le mot mystere ? " << motMystereMelange << endl;
            cin >> motPropose;
        }
        else
        {
            //demande + remarques
            cout << endl << "Le  mot saisi est incorrect : il ne faut saisir que des lettres majuscules non accentuees." << endl <<"Saisir un mot : " << "Quel est le mot mystere ? " << motMystereMelange << endl;
            cin >> motPropose;
        }

        saisieCorrecte = controleSaisie(motPropose, motPropose_2);//contrôle du mot proposé

        i++;
    }while(!saisieCorrecte || motPropose=="X");

    return motPropose;
}

/*mettreEnMajuscules(string &mot)
transforme un mot en min/MAJ (variable mot) en MAJ

renvoie un string : le mot en majuscule
*/
string mettreEnMajuscules(string &mot)
{
    string motMAJ("");

    for(size_t i(0); i<mot.size(); i++)
    {
        motMAJ += toupper(mot[i]);
    }

    return motMAJ;
}

/*saisieNiveau()
demande à l'utilisateur le niveau de jeu

renvoie un entier : le niveau choisi
*/
int saisieNiveau()
{
    int compteurSaisie(0), niveauChoisi(0);
    int const niveauMax(4);
    string niveauSaisi("0");

    do
    {
        if (compteurSaisie==0)
        {
            cout << "Choisir un niveau :" << endl << "1. facile" << endl << "2. moyen" << endl << "3. difficile" << endl << "4. expert" << endl;
            cin >> niveauSaisi;
            niveauChoisi = atoi(niveauSaisi.c_str());
            compteurSaisie++;
        }
        else
        {
            cout << "Choisir un niveau (entre 1 et 4) : ";
            cin >> niveauSaisi;
            niveauChoisi = atoi(niveauSaisi.c_str());
            compteurSaisie++;
        }
    }while(niveauChoisi<1 || niveauChoisi>niveauMax);

    return niveauChoisi;
}

/*melangerMot(string motDepart)
fait un anagramme du mot (variable motDepart)

renvoie un string : l'anagramme
*/
string melangerMot(string motDepart)
{
    string anagramme("");
    int position(0);

    while (motDepart!="")
    {
        srand(time(0));
        position = rand() % motDepart.size();

        anagramme.push_back(motDepart[position]);
        motDepart.erase(position,1);
    }

    return anagramme;
}

/*renvoiMotMystere()
prends le fichier correspondant au niveau
compte le nombre de mots dans le fichier (1 mot/ligne)
choisit aléatoirement un mot dans le fichier

renvoie un string : mot choisi
*/
string renvoiMotMystere(int niveauChoisi)
{
    string fichier("listeMots_facile.txt");

    switch (niveauChoisi)
    {
        case 1 :    fichier = "listeMots_facile.txt";
                    break;

        case 2 :    fichier = "listeMots_moyen.txt";
                    break;

        case 3 :    fichier = "listeMots_difficile.txt";
                    break;

        case 4 :    fichier = "listeMots_expert.txt";
                    break;
    }



    ifstream fluxLecture(fichier.c_str());

    if(fluxLecture)
    {
    //calcul du nombre de mots disponibles
        int nbMots(0);
        while (!fluxLecture.eof())
        {
            string temp;
            getline(fluxLecture, temp);
            nbMots++;
        }

            //cout << "Nombre de mots : " << nbMots << endl << endl;//controle

    //choix aléatoire du mot
        int numLigne(1);
        string motMystere;

        srand(time(0));

        numLigne = rand() % nbMots;

        fluxLecture.seekg(0);

        int i(0);
        while (i<numLigne)
        {
            getline(fluxLecture, motMystere);
            i++;
        }

        return motMystere;
    }

    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        return "";
    }
}

/*enregistrerScore(int nombreCoups, bool garder)
enregistre le nombre de coups (variable nombreCoups) joues par l'utilisateur dans un fichier existant ou nouveau selon le souhait (variable garder)
*/
void enregistrerScore(int nombreCoups, int garder)
{
    if (garder==0)
    {
        ofstream fluxEnregistrerScore("Scores/scores.txt");

        if(fluxEnregistrerScore)
        {
            fluxEnregistrerScore << nombreCoups << endl;
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde." << endl;
            cout << "Les scores ne seront pas sauvegarder..." << endl;
        }
    }
    else
    {
        ofstream fluxEnregistrerScore("Scores/scores.txt", ios::app);

        if(fluxEnregistrerScore)
        {
            fluxEnregistrerScore << nombreCoups << endl;
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde." << endl;
            cout << "Les scores ne seront pas sauvegardeS..." << endl;
        }
    }

}

/*afficherDerniersScores()
affiche les 5 derniers scores (ou moins si il y en pas assez) enregistrés dans le fichier scores.txt
*/
void afficherDerniersScores()
{
    string fichier("Scores/scores.txt");

    ifstream fluxLecture(fichier.c_str());

    if (fluxLecture)
    {

    //mettre dans un tableau
        string score("0");
        int scoreInt(0), nbLignes(0);
        vector<int> scoreTableau;

        while (getline(fluxLecture, score))
        {
            scoreInt = atoi(score.c_str());
            scoreTableau.push_back(scoreInt);
            nbLignes++;
        }

    //determiner le nombre de scores à afficher
        int nbAffichage(5);

        if(nbLignes<5)
        {
            nbAffichage = nbLignes;
        }

    //afficher les scores
        for (int i(0); i<nbAffichage; i++)
        {
            cout << "Score " << nbLignes-nbAffichage+i+1 << " :\t" << scoreTableau[nbLignes-nbAffichage+i] << endl;
        }


    }
    else
    {
         cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

}

/*void demandeAffichageScore()
demande à l'utilisateur s'il veut afficher ses derniers scores.
En cas de reponse positive, la fonction fait appelle à l'autre fonction afficherDerniersScores().
*/
void demandeAffichageScore()
{
    string reponse("0");
    int compteur(0);

    do
    {
        if (compteur==0)
        {
            cout << "Voulez-vous voir vos derniers scores (1) ou non (0) ? ";
            cin >> reponse;
        }
        else
        {
            cout << "Il faut saisir 1 ou 0 : ";
            cin >> reponse;
        }
        compteur++;
    }while (reponse!="0" && reponse!="1");

    if (reponse=="1")
    {
        afficherDerniersScores();
    }

}

/*double calculMoyenne()
calcule la moyenne des scores enregistrés dans le fichier scores.txt
*/
double calculMoyenne()
{
    string fichier("Scores/scores.txt");

    ifstream fluxLecture(fichier.c_str());

    double moyenne(0);

    if (fluxLecture)
    {
    //mettre dans un tableau
        string score("0");
        int scoreInt(0), nbLignes(0);
        vector<int> scoreTableau;

        while (getline(fluxLecture, score))
        {
            scoreInt = atoi(score.c_str());
            scoreTableau.push_back(scoreInt);
            nbLignes++;
        }

    //calcul moyenne

        if (scoreTableau.size()>0)
        {
            for (size_t i(0); i<scoreTableau.size(); i++)
            {
                moyenne += scoreTableau[i];
            }
            moyenne = moyenne/nbLignes;
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }

    return moyenne;
}

/*void demandeAffichageMoyenne()
demande à l'utilisateur s'il veut voir sa moyenne
en cas de réponse positive, la fonction fait appelle à la fonction calculMoyenne() et affiche la moyenne.
*/
void demandeAffichageMoyenne()
{
    string reponse("0");
    int compteur(0);

    do
    {
        if (compteur==0)
        {
            cout << endl << "Voulez-vous voir votre moyenne (1) ou non (0) ? ";
            cin >> reponse;

        }
        else
        {
            cout << "Il faut saisir 1 ou 0 : ";
            cin >> reponse;
        }
        compteur++;
    }while (reponse!="0" && reponse!="1");


    if (reponse=="1")
    {
        double moyenne;
        moyenne=calculMoyenne();
        cout << "Votre moyenne est : " << moyenne << endl;
    }
}
