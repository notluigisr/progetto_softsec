    
    T atNX(const int pos, const int x, const int y, const int z, const int c, const T& out_value) const {
      return (pos<0 || pos>=width())?out_value:_data[pos].atX(x,y,z,c,out_value);