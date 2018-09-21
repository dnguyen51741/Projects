#ifndef FINDPATH_H
#define FINDPATH_H
#include <string>
#include <iostream>

using namespace std;
class findPath
{
private:
    int mat[500][500];
    int numpaths = 0;
    int distances[1];
    int initial;
    string paths[1];
    string pathwq;
    string path2;
    string completepaths[90000];
    int numcompletepaths=0;
    int lengthsofpaths[90000];
    int initialx;
    int initialy;
    int xfinal;
    int yfinal;

public:
    findPath(int x, int y);
    void path(int x, int y , string array[],int num,int xstart,int ystart );
};

#endif // FINDPATH_H
