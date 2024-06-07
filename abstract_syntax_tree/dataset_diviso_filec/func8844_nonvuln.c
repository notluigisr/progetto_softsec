    **/
    CImg<T>& load_dcraw_external(const char *const filename) {
      if (!filename)
        throw CImgArgumentException(_cimg_instance
                                    "STR",
                                    cimg_instance);
      std::fclose(cimg::fopen(filename,"STR"));            
      CImg<charT> command(1024), filename_tmp(256);
      std::FILE *file = 0;
      const CImg<charT> s_filename = CImg<charT>::string(filename)._system_strescape();
#if cimg_OS==1
      cimg_snprintf(command,command._width,"STR",
                    cimg::dcraw_path(),s_filename.data());
      file = popen(command,"STR");
      if (file) {
        const unsigned int omode = cimg::exception_mode();
        cimg::exception_mode(0);
        try { load_pnm(file); } catch (...) {
          pclose(file);
          cimg::exception_mode(omode);
          throw CImgIOException(_cimg_instance
                                "STR",
                                cimg_instance,
                                filename);
        }
        pclose(file);
        return *this;
      }
#endif
      do {
        cimg_snprintf(filename_tmp,filename_tmp._width,"STR",
                      cimg::temporary_path(),cimg_file_separator,cimg::filenamerand());
        if ((file=std_fopen(filename_tmp,"STR"))!=0) cimg::fclose(file);
      } while (file);
      cimg_snprintf(command,command._width,"STR",
                    cimg::dcraw_path(),s_filename.data(),CImg<charT>::string(filename_tmp)._system_strescape().data());
      cimg::system(command,cimg::dcraw_path());
      if (!(file = std_fopen(filename_tmp,"STR"))) {
        cimg::fclose(cimg::fopen(filename,"STR"));
        throw CImgIOException(_cimg_instance
                              "STR",
                              cimg_instance,
                              filename);

      } else cimg::fclose(file);
      load_pnm(filename_tmp);
      std::remove(filename_tmp);
      return *this;