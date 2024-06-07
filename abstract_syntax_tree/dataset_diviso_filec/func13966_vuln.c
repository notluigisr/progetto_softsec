  static const char* ConvertScalar(PyObject* v, Eigen::half* out) {
    
    
    Safe_PyObjectPtr as_float = make_safe(PyNumber_Float(v));
    double v_double = PyFloat_AS_DOUBLE(as_float.get());
    *out = Eigen::half(v_double);

    return nullptr;
  }