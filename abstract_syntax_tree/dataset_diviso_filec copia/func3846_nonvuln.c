      static double mp_argmaxabs(_cimg_math_parser& mp) {
        const unsigned int i_end = (unsigned int)mp.opcode[2];
        double val = _mp_arg(3), absval = cimg::abs(val);
        unsigned int argval = 0;
        for (unsigned int i = 4; i<i_end; ++i) {
          const double _val = _mp_arg(i), _absval = cimg::abs(_val);
          if (_absval>absval) { val = _val; absval = _absval; argval = i - 3; }
        }
        return (double)argval;
      }