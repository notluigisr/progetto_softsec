bool PM_io_parser<PMDEC>::read_hedge(Halfedge_handle e)
{ 
  int n, eo, epr, ene, v, f; bool m;
  if ( !(in >> n) ||
       !check_sep("STR") ||
       !(in >> eo) || !check_sep("STR") ||
       !(in >> epr) || !check_sep("STR") ||
       !(in >> ene) || !check_sep("STR") ||
       !(in >> v) || !check_sep("STR") ||
       !(in >> f) || !check_sep("STR") ||
       !(in >> m) || !check_sep("STR") )
    return false;
  CGAL_assertion_msg
     (eo >= 0 || (std::size_t) eo < en || epr >= 0 || (std::size_t) epr < en || ene >= 0 || (std::size_t) ene < en ||
      v >= 0 || (std::size_t) v < vn || f >= 0 || (std::size_t) f < fn ,
      "STR");

  
  CGAL_assertion(EI[e->opposite()]);
  e->set_prev(Halfedge_of[epr]);
  e->set_next(Halfedge_of[ene]);
  e->set_vertex(Vertex_of[v]);
  e->set_face(Face_of[f]);
  mark(e) = m;
  return true;
}