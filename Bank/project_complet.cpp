#include <iostream>
#include <string.h>
#include <assert.h>
const float COMMISION_VIREMENT=30;
const float TAUX_EPARGNE=0.025;
const float MIN_MONTANT_OUVERTURE=100;

using namespace std;

//-------------------------------------
//-------------String------------------
//-------------------------------------
class String {
public:
    String(const char* s="");
    String(const String& s);
    String& operator=(const String& s);
    int operator==(const String& s);
    const char& operator[](int i){return chaine[i];}
    ~String(){delete chaine;}
    friend ostream& operator<<(ostream& out,const String& s);
    friend istream& operator>>(istream& out,String& s);
 private:
    char* chaine;
};

//*********** constructeur par défaut ************
String::String(const char* s){
    chaine=new char[strlen(s)+1];
    assert(chaine!=0);
    strcpy(chaine,s);
}

//*********** constructeur par recopie ************
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
//*************** operator>> *******************
istream& operator>>(istream& in,String& s){
    in>>s.chaine;
    return in;
}
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
    ~Compte(){
        numeroComptes--;
    }
    int getNumero(){
        return numero;
    }
    virtual void deposer(double montant)=0;
    virtual bool virer(double montant,Compte& destinataire)
            {return 0;}
    //************** retirer ****************
    bool retirer(double montant){
        if(montant<solde){
            solde-=montant;
            return true;
        }
        else
            return false;
    };
    //************* consulterSolde ****************
    double consulterSolde(){
         return solde;
    }
    virtual void afficher(ostream&);
    friend ostream& operator<<(ostream& out,Compte& compte);
};
int Compte::numeroComptes=0;

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
class CompteCourant: public Compte{
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
    int codeClient;
    int nbComptes;
    static int numeroClients;
public:
    Client(String n="",String p="")
            {nom=n;
            prenom=p;
            numeroClients++;
            codeClient=numeroClients;
            nbComptes=0;
            comptes=0;
            dernier=0;
            }
    ~Client()
            {numeroClients--;
            Noeud *ptr=comptes;
            while (ptr != 0){
                Noeud* temp=ptr;
                ptr = ptr->suivant;
                delete temp;
            }
        }

    String Nom();
    String Prenom();
    int CodeClient(){return codeClient;}
    Compte& getCompte(int numero);
    void setCompte(Compte& compte);
    int getNbCompte();
    void deposer(int numeroCompte,float montant);
    bool retirer(int numeroCompte,float montant);
    bool virer(int numeroCompte,int CompteDest,float montant);
    friend ostream& operator<<(ostream& out,const Client& client);
};
int Client::numeroClients=0;
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
assert(numero>=1&&numero<=nbComptes);
Noeud* ptr=comptes;
for(int i=0;i<nbComptes;i++,ptr=ptr->Suivant())
    if(ptr->Info().getNumero()==numero)return ptr->Info();
}

//*************** getNbCompte *****************
int  Client::getNbCompte(){
    return nbComptes;
}
//*************** deposer *****************
void Client::deposer(int numeroCompte,float montant)
{
    getCompte(numeroCompte).deposer(montant);
}
//*************** retirer *****************
bool Client::retirer(int numeroCompte,float montant)
{
    return getCompte(numeroCompte).retirer(montant);
}
//*************** virer *****************
bool Client::virer(int numeroCompte,int CompteDest,float montant)
{
    return getCompte(numeroCompte).virer(montant,getCompte(CompteDest));
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

//-------------------------------------
//------------- Banque -----------
//-------------------------------------
class Maillon{
    Client* info;
   // Noeud* suivant;
public:

Maillon* suivant;
    Maillon(Client& c, Maillon*s)
        {info = &c; suivant = s;}
    Client& Info(){return *info;}
    Maillon* Suivant(){return suivant;}
};

class Banque{
    int nombreClients;
    Maillon* clients;
    Maillon* dernier;
public:
    Banque(){
        nombreClients=0;
        clients=0;
        dernier=0;
    }
    ~Banque(){
        Maillon *ptr=clients;
        while (ptr != 0){
            Maillon* temp=ptr;
            ptr = ptr->suivant;
            delete temp;
        }
    }

    void ajouterClient(Client& nouveauClient);
    Client& getClient(int index);
    void afficherRapport(); //affiche le bilan de tous comptes
    void menu();
    void operationClient(Client& client);
    int touverClient(String nom,String prenom);
    bool creationCompte(Client& client);
    void deposer(Client& client);
    bool retirer(Client& client);
    void consulterSolde(Client& client);
    bool virer(Client& client);
};
//*************** ajouterClient *****************
void Banque::ajouterClient(Client& nouveauClient){
    nombreClients++;
    Maillon* ptr;
    ptr=new Maillon(nouveauClient,0);
    if(clients==0)
        clients = ptr;
    else
        dernier->suivant=ptr;
    dernier=ptr;
}
//*************** getClient *****************
Client& Banque::getClient(int index){
    assert(index>=1&&index<=nombreClients);
    for(Maillon* ptr=clients;ptr;ptr=ptr->suivant)
        if(ptr->Info().CodeClient()==index)
            return ptr->Info();
 }

//**************** afficherRapport ********
void Banque::afficherRapport(){
    Maillon* ptr=clients;
    for(int i=1; i<=nombreClients; i++,ptr=ptr->suivant)
        cout<<ptr->Info()<<endl;
}

//**************** menu ********
void Banque::menu(){
    String nom,prenom;
    Client *client;
    int service;
    int index;
    int choix;
    do{
    cout<<"1:ajouterClient\t\t"<<"2:operationClient\t\t"<<"3:afficherRapport\t"<<"4:sortir"<<endl;
    cin>>choix;
    switch(choix)
        {
        case 1: cout<<"Nom:";
                cin>>nom;cout<<nom<<endl;
                cout<<"Prenom:";
                cin>>prenom;cout<<prenom<<endl;
                client=new Client(nom,prenom);
                if(touverClient(nom,prenom)==-1)
                    ajouterClient(*client);
                else
                    {
                    delete client;
                    cout<<"Client ajouter auparavent"<<endl;
                    }
                break;
        case 2: cout<<"Nom:";
                cin>>nom;cout<<nom<<endl;
                cout<<"Prenom:";
                cin>>prenom;cout<<prenom<<endl;
                index=touverClient(nom,prenom);
                if(index!=-1)
                    operationClient(getClient(index));
                else
                    {
                    delete client;
                    cout<<"Client non existant !"<<endl;
                    }

                break;
        case 3: afficherRapport();
                break;
        case 4: exit(0);
        default:break;//***************
        }
    }while(choix>=1&&choix<=3);
}

//**************** OperationClient ************************
void Banque::operationClient(Client& client){
cout <<client<<endl;
int service;
    do{
    cout<<"\n1:creationCompte\t"<<"2:deposer\t"<<"3:retirer\t"  \
            <<"4:consulterSolde\t"<<"5:virer\t"<<"6:sortir"<<endl;
    cin>>service;
    switch(service)
        {
            case 1: if(!creationCompte(client))
                        cout<<endl<<"Creation de compte non effectuee !";
                    break;
            case 2: deposer(client);break;
            case 3: if(!retirer(client))
                        cout<<endl<<"Retrait non effectue !";
                    break;
            case 4: consulterSolde(client);break;
            case 5: if(!virer(client))
                        cout<<endl<<"Virement non effectue !";
                    break;
        default:break;
        }
    }while(service>=1&&service<=5);


}

//**************** touverClient ************************
int Banque::touverClient(String nom,String prenom)
{
   Maillon* ptr=clients;
    for(int i=1; i<=nombreClients; i++,ptr=ptr->suivant)
        if(nom==ptr->Info().Nom() && prenom==ptr->Info().Prenom())
            return ptr->Info().CodeClient();
    return -1;

}

//**************** creationCompte ************************
bool Banque::creationCompte(Client& client){
    CompteCourant* compte;
    CompteEpargne* compteEpargne;
    int typeCompte;
    cout<<"1:Compte Courant \t 2:Compte Epargne:";
    cin>>typeCompte;
    if(typeCompte!=1 && typeCompte!=2) return 0;
    if(typeCompte==1)
        {
        cout<<"Creation Compte Courant:"<<endl;
        compte=new CompteCourant;
        cout<<*compte<<endl;
        client.setCompte(*compte);}
    if(typeCompte==2)
        {
        cout<<"Creation Compte Epargne:"<<endl;
        compteEpargne=new CompteEpargne;
        cout<<*compteEpargne<<endl;
        client.setCompte(*compteEpargne);}
    return 1;
}

//***************** deposer******************************
void Banque::deposer(Client& client){
    int numeroCompte; float montant;
    cout<<client<<endl;
    cout<<"Numero de compte du depot:";
    cin>>numeroCompte;
    cout<<"Montant a deposer:";
    cin>>montant;

    client.deposer(numeroCompte,montant);
}

//***************** retirer ******************************
bool Banque::retirer(Client& client)
{
    int numeroCompte; float montant;
    cout<<client<<endl;
    cout<<"Numero de compte du retrait:";
    cin>>numeroCompte;
    cout<<"Montant a retirer:";
    cin>>montant;

    return client.retirer(numeroCompte,montant);
}

//***************** consulterSolde ******************************
void Banque::consulterSolde(Client& client)
{
    int numeroCompte;
    cout<<client;
    cout<<"Numero de compte a consulter:";
    cin>>numeroCompte;

    cout<<client.getCompte(numeroCompte);
}
//***************** virer ***********************
bool Banque::virer(Client& client)
{
    int numeroCompte,numeroCompteDest;
    float montant;
    cout<<client<<endl;
    cout<<"Numero de compte courant:";
    cin>>numeroCompte;
    cout<<"Montant a virer:";
    cin>>montant;
    cout<<"Numero de compte destinataire:";
    cin>>numeroCompteDest;

    return client.virer(numeroCompte,numeroCompteDest,montant);
}


int main()
{
Banque banque;
banque.menu();
return 0;
}

