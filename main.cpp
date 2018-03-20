#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

//void game(Cards a, Cards b);

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }
    
    Cards a,b; //two stacks
    
  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
      
     // cout<<"CHECK "<<line.at(2)<<" Length = "<<line.length()<< "TF "<<cardFile1.eof()<<endl;
      if (line.at(2)=='1'){
         // cout<<"***"<<endl;
          a.append(line.at(0),'l');
      }
      
      else {
              a.append(line.at(0),line.at(2));
          //cout<<"11"<<endl;
          //a.print();
//          cout<<endl;
      }
   //   else {
          //cout<<line.at(0)<<" "<<10<<endl;
     //     a.append(line.at(0),10);
          //cout<<"11"<<endl;
          //a.print();
          //cout<<endl;
    //  }
  }
  cardFile1.close();

    //cout<<"CHECK POINT"<<endl;

    
  while (getline (cardFile2, line) && (line.length() > 0)){
      //cout<<"CHECK "<<line.at(2)<<" Length = "<<line.length()<< "TF "<<cardFile2.eof()<<endl;
      
      if (line.at(2)=='1' ){
          //cout<<"***"<<endl;
          b.append(line.at(0),'l');
      }
      
      else {
//          cout<<line.at(0)<<" "<<line.at(2)<<endl;
          
              b.append(line.at(0),line.at(2));
//          cout<<"22"<<endl;
          //b.print();
          //cout<<endl;
      }
      //else {
//          cout<<line.at(0)<<" "<<10<<endl;
   //       b.append(line.at(0), 10);
//          cout<<"22"<<endl;
//          b.print();
          //cout<<endl;
    //  }
  }
  cardFile2.close();
    
//    cout<<"Alice's cards:"<<endl;
//    a.print();
//    cout<<endl<<"Bob's cards:"<<endl;
//    b.print();
//    //cout<<"GAME START CHECK POINT"<<endl;
//    cout<<endl;
    game(a,b);
    
//    a.print();
//    b.print();
    //store the number of cards each stack has]
    
/*
    int acount = a.count();
    int bcount = b.count();
    
//    cout<<endl<<acount<<" "<<bcount<<endl;
    
//    cout<<"checkpoint"<<endl;
    
    //marks who takes turn
    int turn = 1;
    string matchCard = "";
    while (true){
        if (turn == 1){
            matchCard = a.process_A(b);
            if (matchCard.length()!= 0)
                cout<<"Alice picked matching card "<<matchCard<<endl;
            turn = 2; //switch turn
        }
        
        if (turn == 2){
            matchCard = b.process_B(a);
            if (matchCard.length()!= 0)
                cout<<"Bob picked matching card "<<matchCard<<endl;
            turn = 1; //switch turn
        }

        //if no match is found, then exit
        if (a.count()==acount && b.count() == bcount)
            break;
        else{
            acount = a.count();
            bcount = b.count();
        }
    }
 */


  return 0;
}
