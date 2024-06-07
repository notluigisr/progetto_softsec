bool SM_io_parser<Decorator_>::read_edge(SHalfedge_handle e)
{ 
  int n, eo, epr, ene, v, f; bool m; Sphere_circle k;
  if ( !(in >> n) ||
       !check_sep("STR") ||
       !(in >> eo) || !check_sep("STR") ||
       !(in >> epr) || !check_sep("STR") ||
       !(in >> ene) || !check_sep("STR") ||
       !(in >> v) || !check_sep("STR") ||
       !(in >> f) || !check_sep("STR") ||
       !(in >> m) || !check_sep("STR") ||
       !(in >> k) || !check_sep("STR") )
    return false;
  CGAL_assertion_msg
     (eo >= 0 && eo < en && epr >= 0 && epr < en && ene >= 0 && ene < en &&
      v >= 0 && v < vn && f >= 0 && f < fn ,
      "STR");

  
  CGAL_assertion(EI[e->twin()]);
  set_prev(e,Edge_of[epr]);
  set_next(e,Edge_of[ene]);
  set_source(e,SVertex_of[v]);
  set_face(e,SFace_of[f]);
  e->mark() = m;
  e->circle() = k;
  return true;
}