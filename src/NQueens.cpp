#include <iostream>
#include <string.h>
#include "SearchAlgorithms.h"

/**
From Wikipedia:
The eight queens puzzle is the problem of placing eight chess queens on an 8×8
chessboard so that no two queens threaten each other. Thus, a solution requires
that no two queens share the same row, column, or diagonal. The eight queens
puzzle is an example of the more general n queens problem of placing n
non-attacking queens on an n×n chessboard, for which solutions exist for all
natural numbers n with the exception of n=2 and n=3
**/
/**
x-->
y 0|2|0|3|1
| 1| |Q| | |
| 3| | | |Q|
| 0|Q| | | |
v 2| | |Q| |
**/

class NQueens : public State{
  public:
    NQueens(int n);
    NQueens(NQueens * F,int X,int Y);
    bool equals(State*);
    virtual ~NQueens();

    void printBoard();
  protected:
    void GenerateChildrens();
    bool isObjective();

  private:
    /**
    x: there is a entry in x for every column. x[k]!=-1 means there is a queen
    on the k'th column
    y: similar to x but this one describe the rows
    d1: there are 2*(2*n -1) diagonals on a nXn board, d1 represent the ones
    that are parallel to the main diagonal. d1[2n-1]!=1 means tha there is
    a queen on the main diagonal
    d2: like d2, but works for de diagonals parallel to the antidiagonal
    **/
    int *x,*y,*d1,*d2,n,queensPlaced;
};

NQueens::~NQueens(){
  delete[] x;
  delete[] y;
  delete[] d1;
  delete[] d2;
}

void NQueens::printBoard(){
  for(int i=0;i<n;i++){
    for(int j =0;j<n;j++){
      if(x[j]==i)
        std::cout<<"Q";
      else
        std::cout<<"#";
    }
    std::cout<<"\n";
  }
}


bool NQueens::equals(State* table){
  NQueens* comp = (NQueens*) table;

  if(queensPlaced != comp->queensPlaced){
    return false;
  }
  //if there are the same ammount of queens, we need to verify their positions
  for(int i=0;i<n;i++){
    if(x[i] != comp->x[i] || y[i] != comp->y[i])
      return false;
  }
  return true;
}

bool NQueens::isObjective(){
  return queensPlaced==n;
}
//constructor for the initial state
NQueens::NQueens(int n):State(0){
  int diagonalSize =  2*n-1;
  x = new int[n];
  y = new int[n];
  d1 = new int[diagonalSize];
  d2 = new int[diagonalSize];
  memset(x,-1,sizeof(int)*n);
  memset(y,-1,sizeof(int)*n);
  memset(d1,-1,sizeof(int)*diagonalSize);
  memset(d2,-1,sizeof(int)*diagonalSize);
  queensPlaced = 0;
  this->n = n;
}

//makes a copy of F and a add queen at (X,Y)
NQueens::NQueens(NQueens * F,int X,int Y):State(F){
   n = F->n;
   int diagonalSize = 2*F->n - 1;
   x = new int[F->n];
   y = new int[F->n];
   d1 = new int[diagonalSize];
   d2 = new int[diagonalSize];

   memcpy(x,F->x,sizeof(int)*F->n);
   memcpy(y,F->y,sizeof(int)*F->n);
   memcpy(d1,F->d1,sizeof(int)*diagonalSize);
   memcpy(d2,F->d2,sizeof(int)*diagonalSize);

   x[X]=Y;
   y[Y]=X;
   d1[X-Y+diagonalSize/2]=1;
   d2[(n-X-1)-Y+diagonalSize/2]=1;
   queensPlaced= F->queensPlaced;
   queensPlaced++;
}

//Iterate through the whole board and generate a child for each cell where is
//possible to place a queen
void NQueens::GenerateChildrens(){
  int slide = (2*n -1)/2;
  for(int i = 0; i< n;i++){
    for(int j = 0; j< n; j++){
       //is there a queen atacking cell (i,j)?
       if(x[i] == -1 && y[j] == -1 && d1[i-j+slide] == -1 && d2[(n - i-1)-j+ slide] == -1 ){
         //if not ...
         addChildren(new NQueens(this,i,j));
       }
    }
  }
}

int main(int argc, char* argv[]){
  if(argc !=2)
    return -1;

  NQueens * Q = new NQueens(atoi(argv[1]));
  Path* p = SearchAlgorithms::DFS(Q);

  if(p){
    NQueens* q = (NQueens*) p->getObjective();
    q->printBoard();
  }

  
}
