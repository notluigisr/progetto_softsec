      static double mp_complex_tan(_cimg_math_parser& mp) {
        const double real = _mp_arg(2), imag = _mp_arg(3), denom = std::cos(2*real) + std::cosh(2*imag);
        double *ptrd = &_mp_arg(1) + 1;
        ptrd[0] = std::sin(2*real)/denom;
        ptrd[1] = std::sinh(2*imag)/denom;
        return cimg::type<double>::nan();
      }