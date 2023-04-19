#include <iostream>
#include <math.h>

using namespace std;

class Complexe{
public:
    Complexe(float x=0.,float y=0.)
        {re=x;im=y;}
    Complexe(const Complexe& z)
        {re=z.re;im=z.im;}
    void operator+=(const Complexe&);
    void operator*=(const Complexe&);
    void multipierParI();

    friend Complexe operator+(const Complexe&,const Complexe&);
    friend Complexe operator*(const Complexe&,const Complexe&);

    Complexe conj();
    double   abs();
    Complexe inverse();
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

//************ inverse ********************
Complexe Complexe::inverse()
{   Complexe z(conj());
    double d=abs()*abs();
    z*=1/d;
    return z;
}

//************ operator+ ********************
Complexe operator/(Complexe&z1, Complexe&z2)
{
    Complexe z;
    z=z2.inverse();
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

//-------- main---------
int main()
{
Complexe z1,z2;
cin>>z1;
cout<<"z1="<<z1<<endl;
/*cout<<"module="<<z1.abs()<<endl;
cout<<"conjuge="<<z1.conj()<<endl;
cout<<"inverse="<<z1.inverse()<<endl;*/
cin>>z2;
cout<<"z2="<<z2<<endl;
cout <<"\nz1*z2="<<z1*z2;
return 0;
}
