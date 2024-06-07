  static const char* ConvertScalar(PyObject* v, float* out) {
    return ConvertOneFloat<float>(v, out);
  }