/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Computabilidad y Algoritmia 2023-2024
  *
  * @author Rubén Díaz Marrero 
  * @date 04/12/2023
  * @brief Este programa obtiene el Euclidean minimum spanning tree (EMST)
  *  de un conjunto de puntos en dos dimensiones (2D)
  */


#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "point_set.h"



CyA::point_set::point_set(const std::vector<CyA::point> &points) : point_vector(points) {
  quickHull();
}


CyA::point_set::~point_set(void) {
  hull_.clear();
}


double CyA::point_set::distance(const CyA::line &l, const CyA::point &p) const {
  double A = l.second.second - l.first.second;
  double B = l.first.first - l.second.first;
  double C = A * l.first.first + B * l.first.second;

  double distance = A * p.first + B * p.second - C;

  return distance < 0.0 ? -distance : distance;
}


int CyA::point_set::find_side(const CyA::line &l, const CyA::point &p) const {
  double A = l.second.second - l.first.second;
  double B = l.first.first - l.second.first;
  double C = A * l.first.first + B * l.first.second;

  double distance = A * p.first + B * p.second - C;

  return distance < 0.0 ? -1 : distance > 0.0 ? 1 : 0;
}


void CyA::point_set::x_bounds(CyA::point &min_x, CyA::point &max_x) const {
  min_x = max_x = *this->begin();

  for (const CyA::point &p : *this) {
    if (p.first < min_x.first) {
      min_x = p;
    } else if (p.first > max_x.first) {
      max_x = p;
    }
  }
}


double CyA::point_set::point_2_line(const CyA::line &l, const CyA::point &p) const {
  double A = l.second.second - l.first.second;
  double B = l.first.first - l.second.first;
  double C = A * l.first.first + B * l.first.second;

  double distance = A * p.first + B * p.second - C;

  return distance;
}


bool CyA::point_set::farthest_point(const CyA::line &l, int side, CyA::point &farthest) const {
  double max_distance = 0.0;
  bool found = false;

  for (const CyA::point &p : *this) {
    double distancia = distance(l, p);

    if (find_side(l, p) == side && distancia > max_distance) {
      max_distance = distancia;
      farthest = p;
      found = true;
    }
  }

  return found;
}



void CyA::point_set::quickHull(void) {
  hull_.clear();

  CyA::point min_x_point; 
  CyA::point max_x_point;

  x_bounds(min_x_point, max_x_point);

  quickHull(CyA::line(min_x_point, max_x_point), side::LEFT);
  quickHull(CyA::line(min_x_point, max_x_point), side::RIGHT);

  // Remove duplicates
  std::sort(hull_.begin(), hull_.end());
  hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
}


void CyA::point_set::quickHull(const CyA::line &l, int side) {
  CyA::point farthest;

  if (farthest_point(l, side, farthest)) {
    quickHull(CyA::line(l.first, farthest), -find_side(CyA::line(l.first, farthest), l.second));
    quickHull(CyA::line(farthest, l.second), -find_side(CyA::line(farthest, l.second), l.first));
  } else {
      hull_.push_back(l.first);
      hull_.push_back(l.second);
      lines_.push_back(l);
    }
}



/**
 * @brief Imprime los puntos del conjunto
 * @param os Flujo de salida
 */

void CyA::point_set::write_hull(std::ostream &os) const {
  os << hull_.size() << std::endl;

  for (const CyA::point &p : hull_) {
    os << p << std::endl;
  }
}



/**
 * @brief Imprime los puntos en formato .dot
*/
void CyA::point_set::write(std::ostream &os) const {
  CyA::point_vector points = get_points();

  os << "graph{ " << std::endl << std::endl;

  for (int i = 0; i < size(); i++) {
    os << " " << i << " [pos = \"" << (*this)[i].first << "," << (*this)[i].second << "!\"]" << std::endl;
  }

  os << std::endl;

  // Imprimir líneas
  for (const CyA::line &l : lines_) {
    int i, j;
    point_find(l.first, i);
    point_find(l.second, j);

    os << " " << i << " -- " << j << std::endl;
  }


  os << "}" << std::endl;
}


void CyA::point_set::point_find(const CyA::point &p, int &i) const {
  i = 0;
  for (const CyA::point &p_i : *this) {
    if (p_i == p) {
      return;
    }
    i++;
  }
  i = -1;
}

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps)
{
    os << ps.size() << std::endl;

    for (const CyA::point &p : ps)
    {
        os << p << std::endl;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const CyA::point& p)
{
    os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.first << "\t" << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << p.second;

    return os;
}


std::istream& operator>>(std::istream& is, CyA::point_vector& ps)
{
    int n;
    is >> n;

    ps.clear();

    for (int i = 0; i < n; ++i)
    {
        CyA::point p;
        is >> p;

        ps.push_back(p);
    }

    return is;
}

std::istream& operator>>(std::istream& is, CyA::point& p)
{
    is >> p.first >> p.second;

    return is;
}
