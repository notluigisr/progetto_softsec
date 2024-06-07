    
    CImg<Tuchar> get_CMYtoRGB() const {
      return CImg<Tuchar>(*this,false).CMYtoRGB();