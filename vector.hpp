#ifndef _vector_h_
#define _vector_h_
#include <ostream>

using namespace std;

class Vector {
  public:
    Vector();
    Vector(double ix, double iy);
    double get_x();
    double get_y();
    void set_x(double ix);
    void set_y(double iy);
    double get_magnitude();
    string to_string();
    Vector get_normalized();
  private:
    double x;
    double y;
};

std::ostream& operator<<(std::ostream& os, Vector v);
Vector operator*(double mult, Vector v);
Vector operator*(Vector v, double mult);
Vector operator+(Vector v1, Vector v2);
Vector operator-(Vector v1, Vector v2);

#endif // _vector_h_