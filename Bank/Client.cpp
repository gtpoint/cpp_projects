#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

class String
{
public:
    String(const char* s="");
    String(const String& s);
    String& operator=(const String& s);
    int operator==(const String& s);
    const char& operator[](int i){return chaine[i];}
    ~String(){delete chaine;}
    friend ostream& operator<<(ostream& out,const String& s);
 private:
    char* chaine;
};

//*********** constructeur par défaut ************
String::String(const char* s){
    chaine=new char[strlen(s)+1];
    assert(chaine!=0);
    strcpy(chaine,s);
}

//*********** constructeur ppar recopie ************
String::String(const String& s){
    chaine=new char[strlen(s.chaine)+1];
    assert(chaine!=0);
    strcpy(chaine,s.chaine);
}
//*************** operator= ********************
String& String::operator=(const String& s){
    if(this == &s) return *this;
    delete chaine;
    chaine=new char[strlen(s.chaine)+1];
    assert(chaine!=0);
    strcpy(chaine,s.chaine);
    return *this;
}
//*************** operator== *******************
int String::operator==(const String& s){
    if(this == &s) return 1;
    return !strcmp(chaine,s.chaine);
}
//*************** operator<< *******************
ostream& operator<<(ostream& out,const String& s){
    out<<s.chaine;
    return out;
}


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
    virtual void afficher(ostream&);
    friend ostream& operator<<(ostream& out,Compte& compte);
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
//*************** operator<< *******************
ostream& operator<<(ostream& out,Compte& compte)
{
    compte.afficher(out);
    return out;

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
    void afficher(ostream&);
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
//************* afficher ****************
void CompteCourant::afficher(ostream& out)
{
    cout<<"Compte courant";
    Compte::afficher(out);
    cout<<endl;
}

//*************** operator<< *******************
ostream& operator<<(ostream& out,CompteCourant& compte)
{
    compte.afficher(out);
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
    void afficher(ostream&);
    friend ostream& operator<<(ostream&,CompteEpargne&);
};

//*************** deposer *******************
void CompteEpargne::deposer(double montant){
      solde+=montant+montant*taux;
}
//************* afficher ****************
void CompteEpargne::afficher(ostream& out)
{
    cout<<"Compte epargne" ;
    Compte::afficher(out);
    cout<<"\tTaux: ";
    out<<taux;
    cout<<endl;

}
//*************** operator<< *******************
ostream& operator<<(ostream& out,CompteEpargne& compte)
{
    compte.afficher(out);
    return out;
}

//-------------------------------------
//------------- Client ----------------
//-------------------------------------
class Noeud{
    Compte* info;
   // Noeud* suivant;
public:

Noeud* suivant;
    Noeud(Compte& c, Noeud*s)
        {info = &c; suivant = s;}
    Compte& Info(){return *info;}
    Noeud* Suivant(){return suivant;}
};

class Client{
    String nom;
    String prenom;
    Noeud* comptes;
    Noeud* dernier;
    int nbComptes;
public:
    Client(String n="",String p="")
            {nom=n;
            prenom=p;
            nbComptes=0;
            comptes=0;
            dernier=0;
    }
    ~Client(){
            Noeud *ptr=comptes;
            while (ptr != 0){
                Noeud* temp=ptr;
                ptr = ptr->suivant;
                delete temp;
            }
    }

    String Nom();
    String Prenom();
    Compte& getCompte(int numero);
    void setCompte(Compte& compte);
    int getNbCompte();
    friend ostream& operator<<(ostream& out,const Client& client);
};
//*************** getNom *******************
String Client::Nom(){
    return nom;
}
//*************** getPrenom ****************
String Client::Prenom(){
    return prenom;
}

//*************** setCompte *****************
void Client::setCompte(Compte& compte){
    Noeud* ptr;
    ptr=new Noeud(compte,0);
    if(comptes==0)
        comptes = ptr;
    else
        dernier->suivant=ptr;
    dernier=ptr;

    nbComptes++;
}

//*************** getCompte *****************
Compte& Client::getCompte(int numero){
assert(numero>=0&&numero<nbComptes);
Noeud* ptr=comptes;
for(int i=0;i<nbComptes;i++,ptr=ptr->Suivant())
    if(ptr->Info().getNumero()==numero)return ptr->Info();
}

//*************** getNbCompte *****************
int  Client::getNbCompte(){
    return nbComptes;
}
//************* operator<< ****************
ostream& operator<<(ostream& out,const Client& client)
{
    cout<<"Le client: ";
    out<<client.nom;
    cout<<"\t";
    out<<client.prenom;
    cout<<endl;
    int nb=client.nbComptes;
    Noeud* ptr=client.comptes;
    for(int i=0;i<nb;i++)
        {
        out<<ptr->Info();
        ptr=ptr->Suivant();
        }
    return out;
}

/*************************************
        Test de la classe Client
*************************************/
int main()
{
    Client client1("SOUHAR","Abdelghani");
    CompteCourant compteCourant1;
    CompteCourant compteCourant2(1000.00);
    CompteEpargne compteEpargne1;
    CompteEpargne compteEpargne2(900.00,3.5);
    client1.setCompte(compteCourant1);
    client1.setCompte(compteCourant2);
    client1.setCompte(compteEpargne1);
    client1.setCompte(compteEpargne2);
    cout<<client1;
    cout<<endl;
    cout<<client1.getCompte(3);

return 0;
}
