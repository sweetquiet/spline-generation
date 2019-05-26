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

  for (int t=0; t<steps; t++) {
    double s = (double)t/(double)steps;
    double a1 =  2.0*s*s*s - 3.0*s*s + 1.0;
    double a2 = -2.0*s*s*s + 3.0*s*s;
    double a3 =   s*s*s - 2.0*s*s + s;
    double a4 =   s*s*s -  s*s;

    out.push_back(a1*startPos + a2*endPos + a3*startTan + a4*endTan);
  }

  return out;
}

double slope(Vector start, Vector end) {
  return (end.get_y() - start.get_y())/(end.get_x() - start.get_x());
}

double lookahead_discriminant(Vector current, Vector line, double m, double l) {
  return l * l * (1 + m * m)-
    (m*current.get_x()-m*line.get_x()-current.get_y()+line.get_y()) * 
    (m*current.get_x()-m*line.get_x()-current.get_y()+line.get_y());
}

double round_hundredths(double input) {
  return (double) round(input * 100.0) / 100.0;
}

/**
 * Find the next lookahead point given some path, a current coordinate, and a lookahead distance
 */
Vector next_lookahead(Vector current, vector<Vector> path, double l) {
  int i = path.size()-1;
  double m;
  double x0;
  double y0;
  double x1;
  double y1;
  double sol1_x;
  double sol1_y;
  double sol2_x;
  double sol2_y;
  Vector sol1;
  Vector sol2;

  while (i >= 1) {
    
    m = slope(path.at(i-1), path.at(i));
    x0 = current.get_x();
    y0 = current.get_y();
    x1 = path.at(i).get_x();
    y1 = path.at(i).get_y();

    if (lookahead_discriminant(current, path.at(i), m, l) >= 0) {
      sol1_x = (x0 + m*(m*x1+y0-y1) - sqrt(lookahead_discriminant(current, path.at(i), m, l))) / (1 + m*m);
      sol2_x = (x0 + m*(m*x1+y0-y1) + sqrt(lookahead_discriminant(current, path.at(i), m, l))) / (1 + m*m);
      sol1_y = (y1 + m*(x0-x1+m*y0 - sqrt(lookahead_discriminant(current, path.at(i), m, l)))) / (1 + m*m);
      sol2_y = (y1 + m*(x0-x1+m*y0 + sqrt(lookahead_discriminant(current, path.at(i), m, l)))) / (1 + m*m);

      sol1 = Vector(sol1_x, sol1_y);
      sol2 = Vector(sol2_x, sol2_y);

      if (sol1 == sol2) {
        if (sol1.isBetween(path.at(i), path.at(i-1))) return sol1;
      }
      else {
        if (sol1.isBetween(path.at(i), path.at(i-1))) {
          if (sol2.isBetween(path.at(i), path.at(i-1))) {
            if (sol1.distanceTo(path.at(i)) < sol2.distanceTo(path.at(i))) return sol1;
            else return sol2;
          }
          else {
            return sol1;
          }
        }
        else if (sol2.isBetween(path.at(i), path.at(i-1))) return sol2;
      }
    }
    
    i--;
  }
}

string vector_string(vector<Vector> v) {
  string out;

  for (int i=0; i<v.size(); i++) {
    out.append(v.at(i).to_string()+"\n");
  }

  return out;
}

int main() {
  vector<Vector> path = hermiteCubic(Vector(0,0), Vector(40,0), Vector (30,-10), Vector(10,-10), 30);
  cout << vector_string(path) << "\n\n";
  cout << next_lookahead(Vector(0,0), path, 2);
  return 0;
}
