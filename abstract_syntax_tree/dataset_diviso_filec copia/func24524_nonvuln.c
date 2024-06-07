    Tfloat linear_atXY_p(const float fx, const float fy, const int z=0, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "STR",
                                    cimg_instance);

      return _linear_atXY_p(fx,fy,z,c);
    }