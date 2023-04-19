#include <iostream>
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
    friend Complexe operator-(const Complexe&,const Complexe&);

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
Complexe operator-(const Complexe&z1,const Complexe&z2)
{
    return z1-z2;
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
    Complexe sommet();
    friend ostream& operator<<(ostream&,const Pile&);
private:
    Complexe pile[MAX_PILE];
    Complexe memoire;
};
//************ sommet *******
Complexe Pile::sommet()
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
    for(int i=MAX_PILE-1;i>=0;i--)
        pile[i]=pile[i-1];
}

//************ operator<< ********************
ostream& operator<<(ostream& out,const Pile& p)
{
    for(int i=MAX_PILE-1;i>=0;i--)
        out<<p.pile[i]<<endl;
    return out;

}

//-------- main---------
int main()
{
Complexe z1;
Pile pile;
for(int i=MAX_PILE-1;i>=0;i--){
    cin>>z1;
    cout<<"z1="<<z1<<endl;
    pile.empiler(z1);
}
cout<<"pile:"<<endl;
cout<<pile;
return 0;
}
