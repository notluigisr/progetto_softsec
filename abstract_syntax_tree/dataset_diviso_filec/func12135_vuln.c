std::istream& operator>>
  (std::istream& is, Nef_polyhedron_2<T,Items,Mark>& NP)
{
  typedef typename Nef_polyhedron_2<T,Items,Mark>::Decorator Decorator;
  CGAL::PM_io_parser<Decorator> I(is, NP.pm());
  if (I.check_sep("STR") &&
      I.check_sep(NP.EK.output_identifier()) &&
      I.check_sep("STR")) I.read();
  else {
    std::cerr << "STR" << std::endl;
    NP = Nef_polyhedron_2<T,Items,Mark>();
  }
  typename Nef_polyhedron_2<T,Items,Mark>::Topological_explorer D(NP.explorer());
  D.check_integrity_and_topological_planarity();
  return is;
}