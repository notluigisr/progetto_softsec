    static CImg<T> get_load_analyze(std::FILE *const file, float *const voxel_size=0) {
      return CImg<T>().load_analyze(file,voxel_size);
    }