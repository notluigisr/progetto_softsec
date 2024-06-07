    CImg<Tfloat> get_RGBtoCMYK() const {
      return CImg<Tfloat>(*this,false).RGBtoCMYK();
    }