void PM_io_parser<PMDEC>::read()
{
  if ( !check_sep("STR") )
    CGAL_error_msg("STR");
  if ( !(check_sep("STR") && (in >> vn)) )
    CGAL_error_msg("STR");
  if ( !(check_sep("STR") && (in >> en) && (en%2==0)) )
    CGAL_error_msg("STR");
  if ( !(check_sep("STR") && (in >> fn)) )
    CGAL_error_msg("STR");

  Vertex_of.resize(vn);
  Halfedge_of.resize(en);
  Face_of.resize(fn);

  for(i=0; i<vn; i++)  Vertex_of[i] =   this->new_vertex();
  for(i=0; i<en; i++)
    if (i%2==0) Halfedge_of[i] = this->new_halfedge_pair_without_vertices();
    else Halfedge_of[i] = twin(Halfedge_of[i-1]);
  for(i=0; i<fn; i++)  Face_of[i] =     this->new_face();

  for(i=0; i<vn; i++) {
    if (!read_vertex(Vertex_of[i]))
      CGAL_error_msg("STR");
  }
  for(i=0; i<en; i++) {
    if (!read_hedge(Halfedge_of[i]))
      CGAL_error_msg("PM_io_parser::read: error in halfedge\
      line");
  }
  for(i=0; i<fn; i++) {
    if (!read_face(Face_of[i]))
      CGAL_error_msg("STR");
  }
}