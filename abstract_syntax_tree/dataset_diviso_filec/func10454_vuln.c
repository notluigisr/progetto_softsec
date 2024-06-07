bool SM_io_parser<Decorator_>::read_face(SFace_handle f)
{ 
  int n, ei, vi, li; Mark m;
  if ( !(in >> n) || !check_sep("STR") ) return false;
  while (in >> ei) {
    CGAL_assertion_msg(ei >= 0 && ei < en,
                           "STR");
    store_sm_boundary_object(Edge_of[ei],f);
  } in.clear();
  if (!check_sep("STR")) { return false; }
  while (in >> vi) {
    CGAL_assertion_msg(vi >= 0 && vi < vn,
                           "STR");
    store_sm_boundary_object(SVertex_of[vi],f);
  } in.clear();
  if (!check_sep("STR")) { return false; }
  while (in >> li) {
    CGAL_assertion_msg(li >= 0 && li < 2,
                           "STR");
    store_sm_boundary_object(Loop_of[li],f);
  } in.clear();
  if (!check_sep("STR") )
    return false;
  f->mark() = m;
  return true;
}