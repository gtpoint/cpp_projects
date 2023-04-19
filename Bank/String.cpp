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
//*************** operator>> *******************
istream& operator>>(istream& in,String& s){
    in>>s.chaine;
    return in;
}
/*
test string

*/
int main()
{
    String nom,prenom;
    String nom2,prenom2;
    cout<<"Nom:";
    cin>>nom;
    cout<<nom<<endl;
    cout<<"Prenom:";
    cin>>prenom;
    cout<<prenom<<endl;

    cout<<"Nom:";
    cin>>nom2;
    cout<<nom2<<endl;
    cout<<"Prenom:";
    cin>>prenom2;
    cout<<prenom2<<endl;
    cout<<(nom==nom2 && prenom==prenom2);
return 0;
}
