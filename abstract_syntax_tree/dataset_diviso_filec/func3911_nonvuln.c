      static double mp_lerp(_cimg_math_parser& mp) {
        const double t = _mp_arg(4);
        return _mp_arg(2)*(1-t) + _mp_arg(3)*t;
      }