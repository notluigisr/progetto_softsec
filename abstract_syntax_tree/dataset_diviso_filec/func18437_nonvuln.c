    CImg<T>& draw_image(const int x0, const int y0, const int z0, const int c0,
                        const CImg<T>& sprite, const float opacity=1) {
      if (is_empty() || !sprite) return *this;
      if (is_overlapped(sprite)) return draw_image(x0,y0,z0,c0,+sprite,opacity);
      if (x0==0 && y0==0 && z0==0 && c0==0 && is_sameXYZC(sprite) && opacity>=1 && !is_shared())
        return assign(sprite,false);
      const bool bx = x0<0, by = y0<0, bz = z0<0, bc = c0<0;
      const int
        dx0 = bx?0:x0, dy0 = by?0:y0, dz0 = bz?0:z0, dc0 = bc?0:c0,
        sx0 = dx0 - x0,  sy0 = dy0 - y0, sz0 = dz0 - z0, sc0 = dc0 - c0,
        lx = sprite.width() - sx0 - (x0 + sprite.width()>width()?x0 + sprite.width() - width():0),
        ly = sprite.height() - sy0 - (y0 + sprite.height()>height()?y0 + sprite.height() - height():0),
        lz = sprite.depth() - sz0 - (z0 + sprite.depth()>depth()?z0 + sprite.depth() - depth():0),
        lc = sprite.spectrum() - sc0 - (c0 + sprite.spectrum()>spectrum()?c0 + sprite.spectrum() - spectrum():0);
      const ulongT slx = lx*sizeof(T);

      const float nopacity = cimg::abs(opacity), copacity = 1 - std::max(opacity,0.f);
      if (lx>0 && ly>0 && lz>0 && lc>0) {
        for (int c = 0; c<lc; ++c)
          for (int z = 0; z<lz; ++z)
            for (int y = 0; y<ly; ++y) {
              T *ptrd = data(dx0,dy0 + y,dz0 + z,dc0 + c);
              const T *ptrs = sprite.data(sx0,sy0 + y,sz0 + z,sc0 + c);
              if (opacity>=1) std::memcpy(ptrd,ptrs,slx);
              else for (int x = 0; x<lx; ++x) { *ptrd = (T)(nopacity*(*(ptrs++)) + *ptrd*copacity); ++ptrd; }
            }
      }
      return *this;
    }