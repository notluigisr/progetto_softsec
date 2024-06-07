bool SM_io_parser<Decorator_>::read_vertex(SVertex_handle v)
{
  
  
  int n; bool iso; int f; Mark m; Sphere_point p;
  if ( !(in >> n) ||
       !check_sep("STR") ||
       !(in >> iso) ||
       !(in >> f) ||
       !check_sep("STR") ||
       !(in >> m) ||
       !check_sep("STR") ||
       !(in >> p) ||
       !check_sep("STR") ) return false;

  if (iso) set_face(v,SFace_of[f]);
  else     set_first_out_edge(v,Edge_of[f]);
  v->mark() = m; v->point() = p;
  return true;
}