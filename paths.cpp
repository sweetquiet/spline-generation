#include "vector.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

/**
 * Resources:
 * https://www.ri.cmu.edu/pub_files/pub3/coulter_r_craig_1992_1/coulter_r_craig_1992_1.pdf
 * https://www.youtube.com/watch?v=8319J1BEHwM
 * https://www.cubic.org/docs/hermite.htm
 */

/**
 * Fit a cubic function given specified starting and ending coordinates and derivatives.
 */
vector<Vector> hermiteCubic(Vector startPos, Vector startTan, Vector endPos, Vector endTan, int steps) {
  vector<Vector> out;

  for(int t=0; t<steps; t++) {
    double s = (double)t/(double)steps;
    double a1 =  2.0*s*s*s - 3.0*s*s + 1.0;
    double a2 = -2.0*s*s*s + 3.0*s*s;
    double a3 =   s*s*s - 2.0*s*s + s;
    double a4 =   s*s*s -  s*s;

    out.push_back(a1*startPos + a2*endPos + a3*startTan + a4*endTan);
  }

  return out;
}

/**
 * Find the next lookahead point given some path, a current coordinate, and a lookahead distance
 */
Vector next_lookahead(Vector current, vector<Vector> path, double lookahead) {
  
}



string vector_string(vector<Vector> v) {
  string out;

  for(int i=0; i<v.size(); i++) {
    out.append(v.at(i).to_string()+"\n");
  }

  return out;
}

int main() {
  cout << vector_string(hermiteCubic(Vector(0,0), Vector(40,0), Vector (30,-10), Vector(10,-10), 30));

  //cout << vector_string(spacePoints(Vector(0,0), Vector(10, 10), 3));
  return 0;
}
