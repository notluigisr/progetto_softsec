    CImg<Tfloat> get_pow(const double p) const {
      return CImg<Tfloat>(*this,false).pow(p);
    }