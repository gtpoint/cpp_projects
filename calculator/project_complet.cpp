#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

//-------------Complexe------------------
class Complexe{
public:
    Complexe(float x=0.,float y=0.)
        {re=x;im=y;}
    Complexe(const Complexe& z)
        {re=z.re;im=z.im;}
    void operator+=(const Complexe&);
    void operator*=(const Complexe&);
    void multipierParI();
    Complexe operator-();
    friend Complexe operator+(const Complexe&,const Complexe&);
    friend Complexe operator*(const Complexe&,const Complexe&);
    friend Complexe operator-(Complexe&,Complexe&);

    Complexe conj();
    double   abs();
    Complexe inverser();
    friend Complexe operator/(Complexe&,Complexe&);

    friend istream& operator>>(istream&,Complexe&);
    friend ostream& operator<<(ostream&,const Complexe&);
private:
    float re,im;
};
//************ operator+= ********************
void Complexe::operator+=(const Complexe& z)
{
    re+=z.re;
    im+=z.im;
}

//************ opposer ********************
Complexe Complexe::operator-()
{   Complexe z(-re,-im);
    return z;
}

//************ operator- ********************
Complexe operator-(Complexe&z1,Complexe&z2)
{   Complexe z=-z2;
    return z1+z;
}

//************ conjugé ********************
Complexe Complexe::conj()
{   Complexe z(re,-im);
    return z;
}

//************ module ********************
double Complexe::abs()
{
    return sqrt(re*re+im*im);
}

//************ inverser ********************
Complexe Complexe::inverser()
{   Complexe z(conj());
    double d=abs()*abs();
    z*=1/d;
    return z;
}

//************ operator+ ********************
Complexe operator/(Complexe&z1, Complexe&z2)
{
    Complexe z;
    z=z2.inverser();
    z*=z1;
    return z;
}
//************ operator*= ********************
void Complexe::operator*=(const Complexe& z)
{
    re=re*z.re-im*z.im;
    im=re*z.im+im*z.re;
}
//************ multipierParI ********************
void Complexe::multipierParI()
{
    float temp=re;
    re=-im;
    im=temp;
}
//************ operator+ ********************
Complexe operator+(const Complexe&z1,const Complexe&z2)
{
    Complexe z(z1.re+z2.re,z1.im+z2.im);
    return z;
}
//************ operator* ********************
Complexe operator*(const Complexe&z1,const Complexe&z2)
{
    Complexe z=z1;
    z*=z2;
    return z;
}
//************ operator>> ********************
istream& operator>>(istream& in,Complexe&z)
{
    cout<<"saisir la partie reelle:";
    in>>z.re;
    cout<<"saisir la partie imaginaire:";
    in>>z.im;
    return in;
}

//************ operator<< ********************
ostream& operator<<(ostream& out,const Complexe&z)
{
    if(z.re==0 && z.im==0)return out<<z.re;
    else{
    if(z.re!=0 )out<<z.re;
    if(z.im>0) out<<"+i"<<z.im;
    if(z.im<0) out<<"-i"<<abs(z.im);
    return out;
    }

}

//---------Pile-------------
const int MAX_PILE=4;
class Pile{
public:
    void empiler(Complexe);
    void depiler();
    Complexe& sommet();
    friend ostream& operator<<(ostream&,const Pile&);
private:
    Complexe pile[MAX_PILE];
};
//************ sommet *******
Complexe& Pile::sommet()
{
    return pile[MAX_PILE-1];
}
//************ empiler *******
void  Pile::empiler(Complexe z)
{
    for(int i=0;i<MAX_PILE-1;i++)
        pile[i]=pile[i+1];
    pile[MAX_PILE-1]=z;
}
//************ depiler *******
void Pile::depiler()
{
    for(int i=MAX_PILE-1;i>0;i--)
        pile[i]=pile[i-1];
}

//************ operator<< ********************
ostream& operator<<(ostream& out,const Pile& p)
{
    for(int i=MAX_PILE-1;i>=0;i--)
        out<<p.pile[i]<<endl;
    return out;

}


//---------Calculatrice-------------

class Calculatrice{
public:
    void entrerReel(Complexe);
    void multipierParI();
    void addition();
    void soustraction();
    void multiplication();
    void division();
    void memoriser();
    void rappeler();
    void rst();
    friend ostream& operator<<(ostream&,Calculatrice&);
    friend istream& operator>>(istream&,Calculatrice&);
private:
    Pile pile;
    Complexe memoire;
};
//************ entrerReel ********************
void Calculatrice::entrerReel(Complexe z)
{
 pile.empiler(z);
}
//************ operator>> ********************
istream& operator>>(istream& in,Calculatrice& c)
{
    float r;
    cout<<"Entrer un reel:";
    in>>r;
    c.entrerReel(r);
    return in;
}
//************ operator<< ********************
ostream& operator<<(ostream& out,Calculatrice& c)
{
    out<<c.pile.sommet();
    return out;
}
//************ multipierParI ********************
void Calculatrice::multipierParI()
{
    pile.sommet().multipierParI();
}
//************ addition ********************
void Calculatrice::addition()
{
    Complexe z2=pile.sommet();
    pile.depiler();
    Complexe z1=pile.sommet();
    pile.depiler();
    pile.empiler(z1+z2);
}
//************ soustraction ********************
void Calculatrice::soustraction()
{
    Complexe z2=pile.sommet();
    pile.depiler();
    Complexe z1=pile.sommet();
    pile.depiler();
    pile.empiler(z1-z2);
}
//************ multiplication ********************
void Calculatrice::multiplication()
{
    Complexe z2=pile.sommet();
    pile.depiler();
    Complexe z1=pile.sommet();
    pile.depiler();
    pile.empiler(z1*z2);
}
//************ division ********************
void Calculatrice::division()
{
    Complexe z2=pile.sommet();
    pile.depiler();
    Complexe z1=pile.sommet();
    pile.depiler();
    pile.empiler(z1/z2);
}
//************ rappeler  ***********
void Calculatrice::rappeler()
{
    pile.empiler(memoire);
}
//************ memoriser  ***********
void Calculatrice::memoriser()
{
    memoire=pile.sommet();
}
//************ rst  ***********
void Calculatrice::rst()
{
    system("cls");
    cout<<*this<<endl;
}
//-------- Menu---------
class Menu{
public:
    void executer();
    void afficher();
    int choix();
private:
    Calculatrice calc;
};
//************ choix ********************
int Menu::choix()
{
int choix;
cin>>choix;
return choix;
}
//************ afficher ********************
void Menu::afficher()
{
    cout<<"1:Num\t";
    cout<<"2:*I\t";
    cout<<"3:+\t";
    cout<<"4:-\t";
    cout<<"5:*\t";
    cout<<"6:/\t";
    cout<<"7:M+\t";
    cout<<"8:MR\t";
    cout<<"9:Enree\t";
    cout<<endl;
}
//************ executer ***********
void Menu::executer()
{
    int c;
    do{
    afficher();
    c=choix();
    switch(c)
        {
        case 1: cin>>calc;calc.rst();break;
        case 2: calc.multipierParI();calc.rst();break;
        case 3: calc.addition();calc.rst();break;
        case 4: calc.soustraction();calc.rst();break;
        case 5: calc.multiplication();calc.rst();break;
        case 6: calc.division();calc.rst();break;
        case 7: calc.memoriser();break;
        case 8: calc.rappeler();break;
        case 9: calc.rst();break;
         default:break;
        }
    }while(c>=1&&c<=9);

}
//-------- main---------
int main()
{
Menu mn;
mn.executer();
return 0;
}
