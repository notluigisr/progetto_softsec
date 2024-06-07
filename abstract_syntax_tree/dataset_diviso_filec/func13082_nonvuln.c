
    const CImg<T>& _save_cpp(std::FILE *const file, const char *const filename) const {
      if (!file && !filename)
        throw CImgArgumentException(_cimg_instance
                                    "STR",
                                    cimg_instance);
      std::FILE *const nfile = file?file:cimg::fopen(filename,"STR");
      CImg<charT> varname(1024); *varname = 0;
      if (filename) cimg_sscanf(cimg::basename(filename),"STR",varname._data);
      if (!*varname) cimg_snprintf(varname,varname._width,"STR");
      std::fprintf(nfile,
                   "STR"
                   "STR",
                   varname._data,_width,_height,_depth,_spectrum,pixel_type(),pixel_type(),varname._data,
                   is_empty()?"STR");
      if (!is_empty()) for (ulongT off = 0, siz = size() - 1; off<=siz; ++off) {
        std::fprintf(nfile,cimg::type<T>::format(),cimg::type<T>::format((*this)[off]));
        if (off==siz) std::fprintf(nfile,"STR");
        else if (!((off + 1)%16)) std::fprintf(nfile,"STR");
        else std::fprintf(nfile,"STR");
      }
      if (!file) cimg::fclose(nfile);
      return *this;