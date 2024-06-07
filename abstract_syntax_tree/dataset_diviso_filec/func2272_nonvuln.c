    
    CImg<Tfloat> get_invert(const bool use_LU=true) const {
      return CImg<Tfloat>(*this,false).invert(use_LU);