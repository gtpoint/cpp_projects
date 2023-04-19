#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
const float COMMISION_VIREMENT=30;
const float TAUX_EPARGNE=0.025;
const float MIN_MONTANT_OUVERTURE=100;
//-------------------------------------
//-------------Compte------------------
//-------------------------------------
class Compte{
protected:
    int numero;
    double solde;
    static int numeroComptes;
public:
    Compte(){
        numeroComptes++;
        numero=numeroComptes;
        }
    int getNumero(){return numero;}
    virtual void deposer(double montant)=0;
    virtual bool virer(double montant,Compte& destinataire)
            {return 0;}
    bool retirer(double montant);
    double consulterSolde();
    void afficher(ostream&);
};
int Compte::numeroComptes=0;

//************** retirer ****************
bool Compte::retirer(double montant){
        if(montant<solde){
            solde-=montant;
            return 1;
        }
        else
            return 0;
    }
//************* consulterSolde ****************
double Compte::consulterSolde(){
    return solde;
}
//************* afficher ****************
void Compte::afficher(ostream& out)
{
    cout<<"\tNumero: ";
    out<<numero;
    cout<<"\tSolde: ";
    out<<solde;
}


//-------------------------------------
//-------------CompteCourant-----------
//-------------------------------------
class CompteCourant:public Compte{
public:
    CompteCourant(double s=MIN_MONTANT_OUVERTURE):
        Compte(){solde=s;}
    void deposer(double montant);
    bool virer(double montant,Compte& destinataire);
    friend ostream& operator<<(ostream&,CompteCourant&);
};

//*************** deposer *******************
void CompteCourant::deposer(double montant){
    solde+=montant;
}
//*************** virer *******************
bool CompteCourant::virer(double montant,Compte& destinataire){
    if(montant+COMMISION_VIREMENT>solde)return 0;
    solde-=montant+COMMISION_VIREMENT;
    destinataire.deposer(montant);
    return 1;
}
//*************** operator<< *******************
ostream& operator<<(ostream& out,CompteCourant& compte)
{
    cout<<"Compte courant";
    compte.afficher(out);//*************************
    cout<<endl;
    return out;
}
//-------------------------------------
//-------------CompteEparne-----------
//-------------------------------------
class CompteEpargne:public Compte{
private:
    float taux;
public:
    CompteEpargne(double s=MIN_MONTANT_OUVERTURE,float t=TAUX_EPARGNE):
        Compte(){solde=s;taux=t;}
    void deposer(double montant);
    friend ostream& operator<<(ostream&,CompteEpargne&);
};

//*************** deposer *******************
void CompteEpargne::deposer(double montant){
      solde+=montant+montant*taux;
}
//*************** operator<< *******************
ostream& operator<<(ostream& out,CompteEpargne& compte)
{
    cout<<"Compte epargne" ;
    compte.afficher(out);
    cout<<"\tTaux: ";
    out<<compte.taux;
    cout<<endl;
    return out;
}

/**************************
Test des classes comptes
***************************/
int main()
{
    CompteCourant compteCourant1;
    CompteCourant compteCourant2(1000.00);
    CompteEpargne compteEpargne1;
    CompteEpargne compteEpargne2(900.00,3.5);
    cout<<compteCourant1;
    cout<<compteCourant2;
    cout<<compteEpargne1;
    cout<<compteEpargne2;

    compteCourant1.deposer(350);
    cout<<compteCourant1;
    compteEpargne1.deposer(1000);
    cout<<compteEpargne1;

    if(compteCourant2.retirer(2000))
        cout<<"\nRetrait effectuee"<<endl;
    else cout<<"\nRetrait non effectuee"<<endl;
    cout<<compteCourant2;

    if(compteCourant2.retirer(500))
        cout<<"\nRetrait effectuee"<<endl;
    else cout<<"\nRetrait non effectuee"<<endl;
    cout<<compteCourant2;


    CompteCourant compteCourant3(5000.);
    cout<<compteCourant3;
    if(compteCourant3.virer(120,compteCourant2))
        cout<<"\nVirement effectuee"<<endl;
    else cout<<"\nVirement non effectuee"<<endl;
    cout<<compteCourant3;
    cout<<compteCourant2;

    CompteEpargne compteEpargne4;
    cout<<compteEpargne4;
    if(compteCourant3.virer(120,compteEpargne4))
        cout<<"\nVirement effectuee"<<endl;
    else cout<<"\nVirement non effectuee"<<endl;
    cout<<compteCourant3;
    cout<<compteEpargne4;

return 0;
}
