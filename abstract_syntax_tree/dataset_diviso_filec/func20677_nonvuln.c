    **/
    T& atNXYZC(const int pos, const int x, const int y, const int z, const int c, const T& out_value) {
      return (pos<0 || pos>=width())?(cimg::temporary(out_value)=out_value):_data[pos].atXYZC(x,y,z,c,out_value);