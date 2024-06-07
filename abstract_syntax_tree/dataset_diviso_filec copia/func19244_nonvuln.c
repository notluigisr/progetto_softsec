    
    Tfloat linear_atX_p(const float fx, const int y=0, const int z=0, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "STR",
                                    cimg_instance);

      return _linear_atX_p(fx,y,z,c);