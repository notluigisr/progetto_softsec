    CImg<T>& fill(const char *const expression, const bool repeat_values, const bool allow_formula=true,
                  CImgList<T> *const list_images=0) {
      return _fill(expression,repeat_values,allow_formula?1:0,list_images,"STR",0);
    }