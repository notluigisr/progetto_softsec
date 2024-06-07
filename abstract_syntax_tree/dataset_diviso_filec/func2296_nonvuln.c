    
    CImg<Tfloat> get_LabtoXYZ(const bool use_D65=true) const {
      return CImg<Tfloat>(*this,false).LabtoXYZ(use_D65);