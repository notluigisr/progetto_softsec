void PM_io_parser<PMDEC>::debug() const
{
  out << "STR"
      << "STR"
      << "STR";
  Vertex_iterator vit,vend = this->vertices_end();
  for( vit = this->vertices_begin(); vit != vend; ++vit ) {
    if ( is_isolated(vit) ) continue;
    typename Base::Halfedge_around_vertex_circulator
      hcirc = out_edges(vit), hend = hcirc;
    debug_vertex(vit);
    CGAL_For_all(hcirc,hend) { out << "STR"; debug_hedge(hcirc); }
  }
  out << std::endl;
}