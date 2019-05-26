#include "vector.hpp"
#include <ostream>
#include <cmath>
#include <string>
using namespace std;

Vector::Vector(double ix, double iy) {
  this->x = ix;
  this->y = iy;
}

Vector::Vector() {
  this->x = 0;
  this->y = 0;
}

double Vector::get_x() {
  return this->x;
}
    
double Vector::get_y() {
  return this->y;
}

double Vector::get_magnitude() {
  return sqrt(this->x*this->x + this->y*this->y);
}

Vector Vector::get_normalized() {
  double mag = this->get_magnitude();
  return Vector(this->x/mag, this->y/mag);
}

string Vector::to_string() {
  return std::to_string(this->x) + "," + std::to_string(this->y);
}

void Vector::set_x(double ix) {
  this->x = ix;
}

void Vector::set_y(double iy) {
  this->y = iy;
}

double Vector::distanceTo(Vector next) {
  return sqrt((next.get_x()-this->get_x())*(next.get_x()-this->get_x())+(next.get_y()-this->get_y())*(next.get_y()-this->get_y()));
}

bool Vector::isBetween(Vector v1, Vector v2) {
  if (v1.get_x() > v2.get_x()) 
    if(this->get_x() > v1.get_x() || this->get_x() < v2.get_x()) return false;
  else if (v1.get_x() < v2.get_x()) 
    if (this->get_x() < v1.get_x() || this->get_x() > v2.get_x()) return false;
  else
    if (this->get_x() != v1.get_x()) return false;

  if (v1.get_y() > v2.get_y()) 
    if (this->get_y() > v1.get_y() || this->get_y() < v2.get_y()) return false;
  else if (v1.get_y() < v2.get_y()) 
    if (this->get_y() < v1.get_y() || this->get_y() > v2.get_y()) return false;
  else
    if (this->get_y() != v1.get_y()) return false;

  return true;
}

ostream& operator<<(ostream& os, Vector v) {
  os << v.to_string();
  return os;
}

Vector operator*(double mult, Vector v) {
  Vector out = Vector(v.get_x()*mult, v.get_y()*mult);
  return out;
}

Vector operator*(Vector v, double mult) {
  Vector out = Vector(v.get_x()*mult, v.get_y()*mult);
  return out;
}

Vector operator+(Vector v1, Vector v2) {
  Vector out = Vector(v1.get_x()+v2.get_x(), v1.get_y()+v2.get_y());
  return out;
}

Vector operator-(Vector v1, Vector v2) {
  Vector out = Vector(v1.get_x()-v2.get_x(), v1.get_y()-v2.get_y());
  return out;
}

bool operator==(Vector v1, Vector v2) {
  return v1.get_x()==v2.get_x() && v1.get_y()==v2.get_y();
}

bool operator !=(Vector v1, Vector v2) {
  return !(v1 == v2);
}