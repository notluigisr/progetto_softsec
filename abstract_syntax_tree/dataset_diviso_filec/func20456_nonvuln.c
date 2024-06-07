       (this requires 'cimg_use_zlib' been enabled).
       \param header_size Reserve empty bytes as a starting header.
    **/
    CImg<ucharT> get_serialize(const bool is_compressed=false, const unsigned int header_size=0) const {
#ifndef cimg_use_zlib
      if (is_compressed)
        cimg::warn(_cimglist_instance
                   "STR"
                   "STR",
                   cimglist_instance);
#endif
      CImgList<ucharT> stream;
      if (header_size) CImg<ucharT>(1,header_size,1,1,0).move_to(stream);
      CImg<charT> tmpstr(128);
      const char *const ptype = pixel_type(), *const etype = cimg::endianness()?"STR";
      if (std::strstr(ptype,"STR")==ptype)
        cimg_snprintf(tmpstr,tmpstr._width,"STR",_width,ptype + 9,etype);
      else
        cimg_snprintf(tmpstr,tmpstr._width,"STR",_width,ptype,etype);
      CImg<ucharT>::string(tmpstr,false).move_to(stream);
      cimglist_for(*this,l) {
        const CImg<T>& img = _data[l];
        cimg_snprintf(tmpstr,tmpstr._width,"STR",img._width,img._height,img._depth,img._spectrum);
        CImg<ucharT>::string(tmpstr,false).move_to(stream);
        if (img._data) {
          CImg<T> tmp;
          if (cimg::endianness()) { tmp = img; cimg::invert_endianness(tmp._data,tmp.size()); }
          const CImg<T>& ref = cimg::endianness()?tmp:img;
          bool failed_to_compress = true;
          if (is_compressed) {
#ifdef cimg_use_zlib
            const ulongT siz = sizeof(T)*ref.size();
            uLongf csiz = (ulongT)compressBound(siz);
            Bytef *const cbuf = new Bytef[csiz];
            if (compress(cbuf,&csiz,(Bytef*)ref._data,siz))
              cimg::warn(_cimglist_instance
                         "STR",
                         cimglist_instance);
            else {
              cimg_snprintf(tmpstr,tmpstr._width,"STR",csiz);
              CImg<ucharT>::string(tmpstr,false).move_to(stream);
              CImg<ucharT>(cbuf,csiz).move_to(stream);
              delete[] cbuf;
              failed_to_compress = false;
            }
#endif
          }
          if (failed_to_compress) { 
            CImg<charT>::string("STR",false).move_to(stream);
            stream.insert(1);
            stream.back().
              assign((unsigned char*)ref._data,ref._width,ref._height,ref._depth,ref._spectrum*sizeof(T),true);
          }
        } else CImg<charT>::string("STR",false).move_to(stream);
      }

      
      ulongT siz = 0;
      cimglist_for(stream,l) siz+=stream[l].size();
      const ulongT max_siz = (ulongT)cimg::type<int>::max();
      const unsigned int
        nw = (unsigned int)(siz/max_siz + ((siz%max_siz)?1:0)),
        nh = (unsigned int)(siz/nw + (siz%nw?1:0));
      CImg<ucharT> res(nw,nh,1,1,0);
      unsigned char *ptr = res.data();