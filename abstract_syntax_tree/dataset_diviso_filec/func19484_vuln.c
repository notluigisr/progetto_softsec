bool PM_io_parser<PMDEC>::read_vertex(Vertex_handle v)
{
  
  
  int n; bool iso; int f; Mark m; Point p;
  if ( !(in >> n) ||
       !check_sep("STR") ||
       !(in >> iso) ||
       !(in >> f) ||
       !check_sep("STR") ||
       !(in >> m) ||
       !check_sep("STR") ||
       !(in >> p) ||
       !check_sep("STR") ) return false;

  if (iso) v->set_face(Face_of[f]);
  else     v->set_halfedge(Halfedge_of[f]);
  mark(v) = m; point(v) = p;
  return true;
}