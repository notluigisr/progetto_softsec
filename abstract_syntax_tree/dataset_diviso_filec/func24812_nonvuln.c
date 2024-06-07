bool SM_io_parser<Decorator_>::read_face(SFace_handle f)
{ 
  int n, ei, vi, li; Mark m;
  if ( !(in >> n) || !check_sep("STR") ) return false;
  while (in >> ei) {
    if(!(ei >= 0 && ei < en))
    {
      std::cerr<<"STR"<<std::endl;
      in.clear(std::ios_base::badbit);
      return false;
    }
    this->store_sm_boundary_object(Edge_of[ei],f);
  } in.clear();
  if (!check_sep("STR")) { return false; }
  while (in >> vi) {
    if(!(vi >= 0 && vi < vn))
    {
      std::cerr<<"STR"<<std::endl;
      in.clear(std::ios_base::badbit);
      return false;
    }
    this->store_sm_boundary_object(SVertex_of[vi],f);
  } in.clear();
  if (!check_sep("STR")) { return false; }
  while (in >> li) {
    if(!(li >= 0 && li < 2))
    {
      std::cerr<<"STR"<<std::endl;
      in.clear(std::ios_base::badbit);
      return false;
    }
    this->store_sm_boundary_object(Loop_of[li],f);
  } in.clear();
  if (!check_sep("STR") )
    return false;
  f->mark() = m;
  return true;
}