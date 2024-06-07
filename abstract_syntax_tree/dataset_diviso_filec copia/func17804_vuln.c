  static const char* ConvertScalar(PyObject* v, complex128* out) {
    if (PyComplex_Check(v)) {
      *out = complex128(PyComplex_RealAsDouble(v), PyComplex_ImagAsDouble(v));
      return nullptr;
    } else if (PyIsInstance(v, &PyComplexFloatingArrType_Type)) {  
      auto as_complex = PyComplex_AsCComplex(v);
      *out = complex128(as_complex.real, as_complex.imag);
      return nullptr;
    }
    return ErrorMixedTypes;
  }