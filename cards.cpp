//cards.cpp
//Ziqi Fu, Kenny Zhang 3/13/2018
//Implementation of the classes defined in cards.h

#include "cards.h"

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

//constructor
Cards::Cards():root(0) { }

// destructor deletes all nodes
Cards::~Cards() {
    clear(root);
}

// recursive helper for destructor
void Cards::clear(Card* n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}
/*
//destructor clears all cards in a stack (recursive)
Cards::~Cards(){

  delete root;
}

Cards::Card::~Card(){
 if(left!=0)
   {delete (left);}
 if(right!=0)
   {delete (right);}

}

*/
//print all the cards in a stack
void Cards::decode_s(Card *n){
    int i=n->suit;
    switch(i){
    case 1: cout<< "c ";
    case 2: cout<< "d ";
    case 3: cout<< "s ";
    case 4: cout<< "h ";
    }

}
void Cards::decode_n(Card *n){
    int i=n->num;
    switch(i){
    case 11: cout<< "j"<<endl;
    case 12: cout<< "q"<<endl;
    case 13: cout<< "k"<<endl;
    default: cout<< n->num<<endl;
  
    }      

}
void Cards::print() {
    Card *n = root;
    int j=root->suit;
    int k=root->num;
    while (n!=findPre(n,k,j)){
        n=findPre(n,k,j);
        k=n->num;
        j=n->suit;
    }
    while (n!=findSuc(n,k,j)){
      decode_s(n);
      decode_n(n);
        n=findSuc(n,k,j);
        k=n->num;
        j=n->suit;
    }
}

//add a card to the end
void Cards::append(char s, char k){
    int sig=0;
    int u=0;
    switch(s){
        case 'c': sig=1;
        case 'd': sig=2;
        case 's': sig=3;
        case 'h': sig=4;
    }
    switch(k){
        case 'j': u=11;
        case 'q': u=12;
        case 'k': u=13;
    default: u=k-'0';
    }
 

  
    if (root == 0) { // empty list
        root = new Card;
        root->suit = sig;
        root->num = u;
    }
    else {
        Card *n = root;
        while (n->left!=0 && n->right!=0){
            if((sig<(n->suit)|| (sig==n->suit && (u<n->num || u==n->num))) && (n->left!=0) ){
                n=n->left;
            }
            else{
                n=n->right;
            }
        }
        if(sig<(n->suit)|| (sig==n->suit && (u<n->num || u==n->num))){
        n->left = new Card;
        n->left->suit = sig;
        n->left->num = u;
        }
        else{        
        n->right = new Card;
        n->right->suit = sig;
        n->right->num = u;}
    }
}
Card* Cards::findPre(Card* root, int num, int suit){
    if (root == NULL)  return 0;
    Card* pre;
    // If key is present at root
    if (root->num == num && root->suit==suit)
    {
        // the maximum value in left subtree is predecessor
        if (root->left != NULL)
        {
            Card* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
        return pre;
    }
    if (root->suit < suit || root->num <=num)
    {
        pre = root ;
        findPre(root->right, num, suit ) ;
    }
 
}
Card* Cards::findSuc(Card* root, int num, int suit){
    if (root == NULL)  return 0;
    Card* suc;
    // If key is present at root
    if (root->num == num && root->suit==suit)
    {
        // the maximum value in left subtree is predecessor
        if (root->right != NULL)
        {
            Card* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        return suc;
    }
    if (root->suit < suit || root->num <=num)
    {
         suc = root ;
        findSuc(root->left, num, suit ) ;
    }
 
}
Card* Cards::deleteNode(Card* root, int suit, int num)
{
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (suit < root->suit )
        root->left = deleteNode(root->left, suit,num);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (suit > root->suit || (suit== root->suit && num<root->num))
        root->right = deleteNode(root->right, suit,num);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            Card *temp = root->right;
            clear(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Card *temp = root->left;
            clear(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)

        Card* temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->suit = temp->suit;
        root->num = temp->num;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->suit,temp->num);
    }
    return root;
}

Card* Cards::minValueNode(Card* s)
{
    Card* current = s;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

//remove a card from a stack
void Cards::remove(int suit, int k){

    root=deleteNode(root,suit,k);
}

//returns true if match is found
bool Cards::matchFound(int suit, int k){
    Card *n = root;
    int j=root->suit;
    int m=root->num;
    while (n){
        n=findPre(n,m,j);
        k=n->num;
        j=n->suit;
    }
    while (n){
        if (n->suit == suit && n->num == k )
            return true;
        n=findSuc(n,m,j);
        k=n->num;
        j=n->suit;
    }
    return false;
}
//count the number of cards in the class
int Cards::count()  {
    int result = 0;
    Card *n = root;
    int j=root->suit;
    int k=root->num;
    while (n){
        n=findPre(n,k,j);
        k=n->num;
        j=n->suit;
    }
    while (n){
        ++result;
        n=findSuc(n,k,j);
        k=n->num;
        j=n->suit;
    }
    return result;
}
//Play the game and return the string of output
string Cards::process_A(Cards & target){
    string result = "";
    Card * n = root;
    int j=root->suit;
    int k=root->num;
    while (n){
        n=findPre(n,k,j);
        k=n->num;
        j=n->suit;
    }
    while (n){
        if (target.matchFound(n->suit,n->num)){
            result += n->suit;
            result += " ";
            result += n->num;
            target.remove(n->suit,n->num);
            this->remove(n->suit,n->num);
            break;
        }         
        n=findSuc(n,k,j);
        k=n->num;
        j=n->suit;
    } 
    return result;
}
string Cards::process_B(Cards & target){
    string result = "";
    Card * n = root;
    int j=root->suit;
    int k=root->num;
    while (n){
        n=findSuc(n,k,j);
        k=n->num;
        j=n->suit;
    }
    while (n){
        if (target.matchFound(n->suit,n->num)){
            result += n->suit;
            result += " ";
            result += n->num;
            target.remove(n->suit,n->num);
            this->remove(n->suit,n->num);
            break;
        }         
        n=findPre(n,k,j);
        k=n->num;
        j=n->suit;
    } 
    return result;
}