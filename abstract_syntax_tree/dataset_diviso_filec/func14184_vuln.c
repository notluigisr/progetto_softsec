bool SM_io_parser<Decorator_>::read_loop(SHalfloop_handle l)
{ 
  int n, lo, f; bool m; Sphere_circle k;
  if ( !(in >> n) ||
       !check_sep("STR") ||
       !(in >> lo) || !check_sep("STR") ||
       !(in >> f) || !check_sep("STR") ||
       !(in >> m) || !check_sep("STR") ||
       !(in >> k) || !check_sep("STR") )
    return false;
  CGAL_assertion_msg(
    (lo >= 0 && lo < 2 && f >= 0 && f < fn),"STR");

  set_face(l,SFace_of[f]);
  l->mark() = m;
  l->circle() = k;
  return true;
}