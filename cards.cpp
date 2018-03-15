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
void Cards::decode_s(Card *n) const{
    int i=n->suit;
        if (i==1) cout<< "c ";
        else if (i==2) cout<< "d ";
        else if (i==3) cout<< "s ";
        else cout<< "h ";
}

void Cards::decode_n(Card *n) const{
    int i=n->num;
    if (i==1)  cout<< "a"<<endl;
    else if (i==11) cout<< "j"<<endl;
    else if (i==12) cout<< "q"<<endl;
    else if (i==13) cout<< "k"<<endl;
    else cout<< n->num<<endl;
}

//add a card to the end
bool Cards::append(char s, char k){
    int sig=0;
    int u=0;
    //cout << "s: " << s << endl;
    
    if (s=='c') sig =1;
    else if (s=='d') sig =2;
    else if (s== 's') sig =3;
    else  sig =4;
    
    if (k=='a') u = 1;
    else if ( k=='j') u=11;
    else if (k=='q') u=12;
    else if (k== 'k') u=13;
    else if (k==10) u=10;
    else u = k-'0';
    
    if (!root){
        root = new Card;
        root -> suit = sig;
        root -> num = u;
        root -> left = NULL;
        root -> right = NULL;
        return true;
    }
    return append(sig, u, root);
}

bool Cards::append(int s, int k, Card* n){
    int sig = s;
    int u = k;
    //cout << "sig: " << sig << endl;
    //cout << "num: " << k << endl;
    if (sig == n->suit){
        if (u == n->num){
            return false;
        }else if (u < n -> num){
            if (n->left)
                return append(s,k,n->left);
            else {
                n -> left = new Card;
                n -> left -> suit = sig;
                n -> left -> num = u;
                n -> left -> left = NULL;
                n -> left -> right = NULL;
                return true;
            }
        }else {
            if (!n->right){
                n->right = new Card;
                n->right->suit = sig;
                n->right->num = u;
                n->right->left = NULL;
                n->right->left = NULL;
                return true;
            }else{
                return append(s,k,n->right);
            }
        }
    }else if (sig>n->suit){
        if (!n->right){
            n->right = new Card;
            n->right->suit = sig;
            n->right->num = u;
            n->right->left= NULL;
            n->right->right = NULL;
            return true;
        }
        else
            return append(s,k,n->right);
    }else{
        if (!n->left){
            n->left = new Card;
            n->left->suit = sig;
            n->left->num = u;
            n->left->left= NULL;
            n->left->right= NULL;
            return true;
        }else
            return append(s,k,n->left);
    }return false;
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

int Cards::count() const{
    return count(root);
}


int Cards::count(Card*n) const{
    if(!n) {
        return 0;
    } else {
        return count(n->left) + count(n->right) + 1;
    }
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


void Cards::print() const{
    print(root);
}

void Cards::print(Card* n) const{
    if(n){
        print(n->left);
        //decode_s(n);
        decode_n(n);
        print(n->right);
    }
}






