# Bank Project

+ A bank manages a set of accounts of different types: current accounts, savings accounts, etc... The bank must allow its clients to open accounts.
The behaviors and characteristics related to an account are at a highly abstract level, with many similarities: each account has an owner, a balance, a number, and an interest rate. Clients must be able to deposit, withdraw money `if there is enough balance`, and check the balance of their accounts.
+ A client should be able to transfer money from their current account to another of their accounts `current or savings`.
+ A client should also be able to transfer money to the account of another client by paying a transaction fee of 30 DH.
+ Savings accounts earn money: they have an interest rate `tx`, and each deposit of an amount M into a savings account leads to an increase in the balance of that account by `M + M * tx`.


#### The goal of this exercise is to simulate the operation of a Bank class.

## Compte
+ **1-The top of the accounts hierarchy is an abstract class called `Compte`, which will not directly handle deposits (Compte should be an abstract class). Write the code for the Compte class, which should contain two private attributes: 
its `number` and its `balance`, as well as the public methods:**
  - void deposer(double montant); 
  - boolean retirer(double montant);
  - double consulterSolde();
  - ... operator<<(...);

## CompteCourant
+ **2-Code the CompteCourant class, which inherits from the `Compte` class and includes the following public methods:**
  - constructor; 
  - void deposer(double montant);
  - boolean virer(double montant, Compte destinataire);

## CompteEpargne
+ **3-Code the `CompteEpargne` class, which inherits from the `Compte` class and contains one private attribute: its interest rate `tx`, as well as the public methods:**
  - constructor; 
  - void deposer(double montant);
  - ... operator<<(...);

## Client
+ **4-Write the `Client` class, where each client has at least one account. The class must also contain the attributes: `first name` and `last name`, as well as the public methods:** 
  - Constructor; 
  - String getNom();
  - String getPrenom();
  - Compte getCompte(int index);
  - void setCompte(Compte compte);

## Bnaque
+ **5-Write the `Banque` class, which has several clients. The class must also contain the number of its clients, as well as the public methods:**
  - Constructor; 
  - void ajoutetClient(String nom, String prenom);
  - Client getClient(int index);
  - void afficherRapport();

## Menu
+ **6-To ensure an interactive operation of the bank, provide the `Banque` class with a public method called `menu()`. This method should provide a dialogue with the user so that the bank can offer the following services:**
  - Add a client.
  - Perform an operation for a client.
  - Display a general report.







