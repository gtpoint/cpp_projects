#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;


class T{
  int val ;

  public :
    T(int n ):val(n){};
    T():val(0){};

    friend T operator+(const T& , const T&);
    friend ostream& operator<<(ostream& , T&);
    friend istream& operator>>(istream&  , T&);
};

T operator+(const T& obj1 , const T& obj2){
        return T(obj1.val + obj2.val) ;
}

ostream& operator<<(ostream& out , T& obj){
   out << obj.val ;
   return out ;
}

istream& operator>>(istream& in , T& obj){
   cout << "donner la valeur: " ;
   in >> obj.val ;

}



class Td{
double *tab ;
int taille ;
public :
    Td(double *Array = NULL , int tal = 0){
       taille = tal ;
       if(tal != 0){
           tab = new double[tal];
           for(int i = 0 ; i<tal ; i++){
             tab[i] = Array[i] ;
           }
       }
    }

    Td(const Td& obj){
      tab = obj.tab ;
      taille = obj.taille ;
    }

    ~Td(){ delete tab ; }
    double* getTab(){
       return tab ;
    }

    int getTaille(){
       return taille ;
    }



    Td& operator=(Td& obj ){
        tab = obj.tab ;
        return *this ;
    }

    double& operator[](int pos){
        if(pos >= taille){
            cout << "out of order !" <<  endl ;
            cout << "this array have " << taille << " only" << endl ;
            exit(0);
        }
       return tab[pos] ;
    }
    int Taille(){
      return taille ;
    }
    friend ostream& operator<<(ostream&  , Td&);
};

ostream& operator<<(ostream& out , Td& obj){
  for(int i = 0 ; i<obj.taille ; i++){
    out << obj.tab[i] << "\t" ;
  }
return out ;
}


class poly{
Td coeff ;
int degre ;
public :
    poly(Td coef , int degree){
       degre = degree ;
       for(int i=0 ; i< degree ; i++ ){
          coeff.tab[i] = coef.tab[i];
       }
    }
    poly(const poly& obj){
      coeff = obj.coeff ;
      degre = obj.degre ;
    }

    friend ostream& operator<<(ostream& , poly&) ;
};

ostream& operator<<(ostream& out , poly& obj){

    for(int i = 0 ; i<= obj.degre ; i++){
        if(obj.coeff.tab[i] > 0){
           out << " + " obj.coeff.tab[i] << " X(" << i << ")" ;
        }else {
          out << " - " obj.coeff.tab[i] << " X(" << i << ")" ;
        }
    }
   return out ;
}


int main()
{

  T t[5] ;
/*
  for(int k = 0 ; k<5 ; k++){
    cin >> t[k] ;
  }

  int i , j ;
  for(i = 0 ; i<5 ; i++){
    for(j = 0 ; j<=i ;j++){
        T v = t[i] + i + j ;
        cout << v << "\t" ;
        v = 0 ;
    }
    cout << endl ;
  }
*/

  double a[] = {1 , 4 , 3 , 5} ;
   Td obj1( a , 4);

   poly polynome1( obj1 , 4);
   cout << polynome1 << endl ;



return 0;
}
