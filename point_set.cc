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
    }
}

