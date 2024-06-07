      static double mp_vkth(_cimg_math_parser& mp) {
        _cimg_mp_vfunc(res = vec.get_shared_points(1,vec.width() - 1).
                       kth_smallest((ulongT)cimg::cut((longT)*vec - 1,(longT)0,(longT)vec.width() - 2)));
      }