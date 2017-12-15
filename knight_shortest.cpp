#include <bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

#define GETX(_x, _n) (_x/n)
#define GETY(_y, _n) (_y%n)
#define SERIALIZE(_x, _y, _n) ((_x)*(_n) + (_y))
#define CHECK(p) (p>=0&&p<n)

typedef enum PATH {
  PATH_START = 0,
  PATH_UL = 1,
  PATH_UR = 2,
  PATH_R = 3,
  PATH_LR = 4,
  PATH_LL = 5,
  PATH_L  = 6,
  PMAX
} PATH;

const char *getPathStr(PATH p)
{
  switch(p) {
  case PATH_UL: return "UL";
  case PATH_UR: return "UR";
  case PATH_R: return "R";
  case PATH_LR: return "LR";
  case PATH_LL: return "LL";
  case PATH_L: return "L";
  default: return "?";
  }
  return "?";
}

int getNext(PATH &prevpath, int n, int i, int j)
{
    if (PATH_L == PMAX) {
        return -1;
    }

    PATH path = (PATH)((int)prevpath + 1);
    prevpath=path;
    switch (path) {
        case PATH_UL:
          if (CHECK(i-2)&&CHECK(j-1)) {
            return SERIALIZE(i-2,j-1,n);
          } else {
            return -1;
          }
        break;
        case PATH_UR:
          if (CHECK(i-2)&&CHECK(j+1)) {
            return SERIALIZE(i-2,j+1,n);
          } else {
            return -1;
          }
        break;
        case PATH_R:
          if (CHECK(i)&&CHECK(j+2)) {
            return SERIALIZE(i,j+2,n);
          } else {
            return -1;
          }
        break;
        case PATH_LR:
          if (CHECK(i+2)&&CHECK(j+1)) {
            return SERIALIZE(i+2,j+1,n);
          } else {
            return -1;
          }
        break;
        case PATH_LL:
          if (CHECK(i+2)&&CHECK(j-1)) {
            return SERIALIZE(i+2,j-1,n);
          } else {
            return -1;
          }
        break;
        case PATH_L:
          if (CHECK(i)&&CHECK(j-2)) {
            return SERIALIZE(i,j-2,n);
          } else {
            return -1;
          }
        break;
        default:
          return -1;
          break;
    }
    return -1;
}

void printShortestPath(int n, int i_start, int j_start, int i_end, int j_end) {
    //  Print the distance along with the sequence of moves.
    queue<int> q;
    vector<int> visited(n*n);
    vector< pair<int,int> > parent(n*n);

    int lmost, mincount=0, done=0;
    int start = SERIALIZE(i_start, j_start, n);
    int end = SERIALIZE(i_end, j_end, n);

    q.push(start);
    visited[start]=1;
    parent[start].first=-1;
    parent[start].second=-1;
    lmost=start;

#ifdef DEBUG
    cout << "Finding shortest path from " << start << " to " << end << endl;
#endif /*DEBUG*/

    while(q.size() and !done) {
      int front=q.front(), child=0;
      q.pop();
      if (lmost==front) {
        lmost=-1;
        mincount++;
      }
      PATH path = PATH_START;
      int i=GETX(front,n),j=GETY(front,n);
      while (PMAX != path)  {
        child=getNext(path, n, i, j);
        if (-1 == child)
          continue;
        if (child==end) {
          visited[end]=1;
          parent[child].first=front;
          parent[child].second=path;
          done=1;
          break;
        }
        if (!visited[child]) {
          parent[child].first=front;
          parent[child].second=path;
#ifdef DEBUG
          cout << "Visiting node " << child << " from " << front
            << " (" <<GETX(child,n) << ", " << GETY(child,n) << ")"<< endl;
#endif /*DEBUG*/
          visited[child]=1;
          if (lmost==-1)
            lmost=child;
          q.push(child);
        }
      }
    }

    if (done) {
      cout << mincount << endl;
      pair<int, int> path=parent[end];
      vector<string> path_str;
      while (path.first!=-1) {
        path_str.push_back(getPathStr((PATH)path.second));
        path=parent[path.first];
      }
      for(int i=path_str.size()-1; i>=0; --i) {
        cout << path_str[i] << " ";
      }
      cout << endl;
    } else {
      cout << "Impossible" << endl;
    }
}

int main() {
    int n;
    cin >> n;
    int i_start;
    int j_start;
    int i_end;
    int j_end;
    cin >> i_start >> j_start >> i_end >> j_end;
    printShortestPath(n, i_start, j_start, i_end, j_end);
    return 0;
}
