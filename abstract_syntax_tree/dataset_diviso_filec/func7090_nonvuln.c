    CImg<Tfloat> get_RGBtosRGB() const {
      return CImg<Tfloat>(*this,false).RGBtosRGB();
    }