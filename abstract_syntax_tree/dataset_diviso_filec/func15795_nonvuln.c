    
    CImg<T> get_fill(const char *const expression, const bool repeat_values, const bool allow_formula=true,
                     const CImgList<T> *const list_inputs=0, CImgList<T> *const list_outputs=0) const {
      return (+*this).fill(expression,repeat_values,allow_formula?1:0,list_inputs,list_outputs);