    CImgList<T>& assign(const CImg<t1>& img1, const CImg<t2>& img2, const CImg<t3>& img3, const CImg<t4>& img4,
                        const CImg<t5>& img5, const CImg<t6>& img6, const CImg<t7>& img7, const bool is_shared=false) {
      assign(7);
      _data[0].assign(img1,is_shared); _data[1].assign(img2,is_shared); _data[2].assign(img3,is_shared);
      _data[3].assign(img4,is_shared); _data[4].assign(img5,is_shared); _data[5].assign(img6,is_shared);
      _data[6].assign(img7,is_shared);
      return *this;
    }