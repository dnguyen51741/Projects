#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include "findpath.h"

using namespace std;
//string beenx[100000];
//string beeny[100000];

//class been{
//public:
 //   int x[10000];
 //   int y[10000];
//};
//int beenx1[100000];
//int beeny1[100000];
//been beenarray[10000];

findPath::findPath(int x, int y) {

    //char five = '5';
   // int fiveint = int(five)-48;
   // cout<<fiveint<<'\n';

//int four=4;
  //  char fourchar=char(four)+48;
  //  cout<<fourchar<<'\n';

    string array[500];

    string line;
    int i = 0;
    ifstream myfile("../map9.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            array[i] = line;
            i++;
        }
        myfile.close();
    } else cout << "Unable to open file";
    /*
    cout<<"Enter x coordinate ";
    cin>>x;
    cout<<'\n';
    cout<<"Enter y coordinate ";
    cin>>y;
    cout<<'\n';

    cout<<"Enter x destination coordinate ";
    cin>>xfinal;
    cout<<'\n';
    cout<<"Enter y destination coordinate ";
    cin>>yfinal;
    cout<<'\n';
    */

    initialx=x;
    initialy=y;

path(x,y,array,numpaths,x,y);



    int y2=0;
while(completepaths[y2]!=""){

    y2++;

}
    cout<<"\n";
    cout << "number of paths is "<<y2;
    int smallest = 0;
    cout<<"\n";
    int d =0;
    smallest =0;

    while(d<y2){
        if (lengthsofpaths[d]<lengthsofpaths[smallest])
        {
         smallest = d;
        }
        d++;
                }

    cout<<"\n"<<"smallest is "<<lengthsofpaths[smallest];
    cout<<"\n";
    cout<<completepaths[smallest];
    cout<<"\n";
   // cout<<beenx[smallest];

}

void findPath::path(int x, int y , string array[],int num,int xstart,int ystart ){

    //beenx[num] = beenx[num-1];
    //beeny[num] = beeny[num-1];
    initial = 0;
    paths[num] = paths[num-1];
   // beenx[num] = beenx[num-1];
   // beeny[num] = beeny[num-1];
   // beenarray[num] = beenarray[num-1];


    int tempx = x;
    int tempy = y;

   /// int u =0;
   // int f = beenx[num].length();


    while(1){

      //  f = beenx[num].length();
      //  u =0;
        //int f = beenx[num].length();
      //  while(u<f){

     //       if(beenx[num][u]==char(char(x)+48) and beeny[num][u]==char(char(y)+48)){
     //           break;
      //      }

     //   u++;
     //   }

        if(x==xstart and y==ystart and initial!=0 ){
            break;
        }

       mat[x][y]=mat[x][y]+1;

        if (initialx==x&&initialy==y) {
            if (initial != 0) {
             break;
        }
        }

        initial++;


        int lengthcheck=0;
        while(paths[num][lengthcheck]==('>')or paths[num][lengthcheck]==('+') or paths[num][lengthcheck]==('|') or paths[num][lengthcheck]==('<')or paths[num][lengthcheck]==('$')or paths[num][lengthcheck]==('^') or paths[num][lengthcheck]==('Q') or paths[num][lengthcheck]==('&') or paths[num][lengthcheck]==('%') or paths[num][lengthcheck]==('!') or paths[num][lengthcheck]==('A') or paths[num][lengthcheck]==('O')){
        //while(paths[num][lengthcheck]!=' '){
            lengthcheck++;
        }
        if (paths[num].length()>350){
            break;
        }





        paths[num] = paths[num] + array[y][x];
      //  beenx[num] = beenx[num]+char(char(x)+48);
       // beeny[num] = beeny[num]+char(char(y)+48);

       // cout<<array[y][x];
        distances[0] = distances[0]+1;


        if (x==xfinal and y==yfinal){

            //distances[0] = initial;

            int length=0;
            while(paths[num][length]==('>')or paths[num][length]==('+') or paths[num][length]==('|') or paths[num][length]==('<')or paths[num][length]==('$')or paths[num][length]==('^') or paths[num][length]==('Q')  or paths[num][length]==('&')or paths[num][length]==('%') or paths[num][lengthcheck]==('!') or paths[num][lengthcheck]==('A')or paths[num][lengthcheck]==('O')){
                length++;
            }
            lengthsofpaths[numcompletepaths] = paths[num].length();
            completepaths[numcompletepaths] = paths[num];
            numcompletepaths++;
            break;
        }

        else if (array[y][x]=='+'){
           // numpaths = numpaths+2;
            num++;
            path(x+1,y,array,num,x,y);
           // numpaths = numpaths+1;
            path(x,y+1,array,num,x,y);
           // numpaths = numpaths+1;
            path(x,y-1,array,num,x,y);
            break;
        }
        else if (array[y][x]=='$'){
            num++;
            path(x+1,y,array,num,x,y);
            path(x,y+1,array,num,x,y);
            break;
        }
        else if (array[y][x]=='W'){
            num++;
            path(x,y-1,array,num,x,y);
            path(x+1,y,array,num,x,y);
            break;
        }
        else if (array[y][x]=='Z'){
            num++;
            path(x+1,y,array,num,x,y);
            path(x-1,y,array,num,x,y);
            break;

        }
        else if (array[y][x]=='O'){
            num++;
            path(x,y+1,array,num,x,y);
            path(x-1,y,array,num,x,y);
            break;

        }
        else if (array[y][x]=='A'){
            num++;
            path(x,y+1,array,num,x,y);
            path(x+1,y,array,num,x,y);
            break;
        }
        else if (array[y][x]=='!'){
            num++;
            path(x-1,y,array,num,x,y);
            path(x,y-1,array,num,x,y);
            break;
        }
        else if (array[y][x]=='@'){
            num++;
            path(x,y-1,array,num,x,y);
            path(x+1,y,array,num,x,y);
            break;
        }
          //  /*
        else if (array[y][x]=='&'){
            num++;
            path(x,y+1,array,num,x,y);
            path(x-1,y,array,num,x,y);
            break;
        }
        else if (array[y][x]=='%'){
            num++;
            path(x,y-1,array,num,x,y);
            path(x-1,y,array,num,x,y);
            break;
        }
        else if (array[y][x]=='Q'){
            num++;
            path(x-1,y,array,num,x,y);
            path(x,y+1,array,num,x,y);
            break;
        }
            // */
        else if (array[y][x]=='>'){
            x++;
        }
        else if (array[y][x]=='<'){
            x--;
        }
        else if (array[y][x]=='^'){
            y--;
        }
        else if (array[y][x]=='|'){
            y++;
        }
        else if (array[y][x]=='*'){

            //distances[0] = initial;

            int length=0;
            while(paths[num][length]==('>')or paths[num][length]==('+') or paths[num][length]==('|') or paths[num][length]==('<')or paths[num][length]==('$')or paths[num][length]==('^') or paths[num][length]==('Q')  or paths[num][length]==('&')or paths[num][length]==('%') or paths[num][lengthcheck]==('!') or paths[num][lengthcheck]==('A')or paths[num][lengthcheck]==('O')){
               length++;
            }
            lengthsofpaths[numcompletepaths] = paths[num].length();
            completepaths[numcompletepaths] = paths[num];
            numcompletepaths++;

            break;
        }

    if (tempx==x&&tempy==y){
        break;
    }
        if (mat[x][y]>200000){
            break;
        }
    }
}
