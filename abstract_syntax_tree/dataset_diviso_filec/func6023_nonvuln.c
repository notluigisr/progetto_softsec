      
      void check_matrix_square(const unsigned int arg, const unsigned int n_arg,
                               char *const ss, char *const se, const char saved_char) {
        _cimg_mp_check_type(arg,n_arg,2,0);
        const unsigned int
          siz = _cimg_mp_size(arg),
          n = (unsigned int)cimg::round(std::sqrt((float)siz));
        if (n*n!=siz) {
          const char *s_arg;
          if (*s_op!='F') s_arg = !n_arg?"STR";
          else s_arg = !n_arg?"STR";
          *se = saved_char;
          char *const s0 = ss - 4>expr._data?ss - 4:expr._data;
          cimg::strellipsize(s0,64);
          throw CImgArgumentException("STR"
                                      "STR"
                                      "STR",
                                      pixel_type(),_cimg_mp_calling_function,s_op,*s_op?"STR",
                                      s_arg,*s_op=='F'?(*s_arg?"STR"),
                                      s_type(arg)._data,
                                      s0!=expr._data?"STR");
        }