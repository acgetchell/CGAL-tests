//
// Created by Adam Getchell on 2019-03-08.
//
// https://doc.cgal.org/latest/Triangulation_3/Triangulation_3_2draw_triangulation_3_8cpp-example.html

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/draw_triangulation_3.h>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using DT3 = CGAL::Delaunay_triangulation_3<K>;
using Creator = CGAL::Creator_uniform_3<double, K::Point_3>;

int main()
{
  std::vector<K::Point_3> points;
  CGAL::Random_points_in_sphere_3<K::Point_3, Creator> g(1.0);
  CGAL::cpp11::copy_n(g, 50, std::back_inserter(points));

  DT3 dt3(points.begin(),points.end());

  CGAL::draw(dt3);

  return EXIT_SUCCESS;
}
