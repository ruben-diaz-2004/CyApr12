/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 18/12/2023
  * @brief Este programa obtiene el conjunto convexo de un conjunto de puntos en dos dimensiones (2D)
  */


#include <iostream>
#include <vector>

#define MAX_SZ 3
#define MAX_PREC 0

#pragma once

namespace CyA {
  typedef std::pair<double,double> point;
  typedef std::pair<point, point> line;
  typedef std::vector<point> point_vector;
  typedef std::vector<line> line_vector;
 
  enum side {
    LEFT = -1,
    CENTER = 0,
    RIGHT = 1
    
  };
 
  class point_set : public point_vector {
    private:
      point_vector hull_;
      line_vector lines_;
 
    public:
      point_set(const vector<point> &points);
      ~point_set(void);
 
      void quickHull(void);
 
      void write_hull(std::ostream &os) const;
      void write(std::ostream &os) const;
 
      inline const point_vector& get_hull(void) const { return hull_; }
      inline const point_vector& get_points(void) const { return *this; }
      void point_find(const CyA::point &p, int &i) const;
    private:
      void quickHull(const line &l, int side);
 
      double distance(const line &l, const point &p) const;
      int find_side(const line &l, const point &p) const;
      void x_bounds(point &min_x, point &max_x) const;
      double point_2_line(const line &l, const point &p) const;
      bool farthest_point(const line &l, int side, point &farthest) const;
  };
}

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);
std::ostream& operator<<(std::ostream& os, const CyA::point& ps);

std::istream& operator>>(std::istream& is, CyA::point_vector& ps);
std::istream& operator>>(std::istream& is, CyA::point& ps);