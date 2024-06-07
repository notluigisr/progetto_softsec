static const char* ConvertOneFloat(PyObject* v, T* out) {
  if (PyErr_Occurred()) {
    return nullptr;
  }
  if (TF_PREDICT_TRUE(PyFloat_Check(v))) {
    const double as_double = PyFloat_AS_DOUBLE(v);
    *out = static_cast<T>(as_double);
    
    if (TF_PREDICT_FALSE(sizeof(T) < sizeof(double) && std::isinf(*out) &&
                         std::isfinite(as_double))) {
      return ErrorOutOfRangeDouble;
    }
    return nullptr;
  }
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(v)) {
    *out = PyInt_AS_LONG(v);
    return nullptr;
  }
#endif
  if (PyLong_Check(v)) {
    *out = PyLong_AsDouble(v);
    if (PyErr_Occurred()) return ErrorOutOfRangeDouble;
    return nullptr;
  }
  if (PyIsInstance(v, &PyFloatingArrType_Type)) {  
    Safe_PyObjectPtr as_float = make_safe(PyNumber_Float(v));
    if (PyErr_Occurred()) {
      return nullptr;
    }
    return ConvertOneFloat<T>(as_float.get(), out);
  }
  if (PyIsInstance(v, &PyIntegerArrType_Type)) {  
#if PY_MAJOR_VERSION < 3
    Safe_PyObjectPtr as_int = make_safe(PyNumber_Int(v));
#else
    Safe_PyObjectPtr as_int = make_safe(PyNumber_Long(v));
#endif
    if (PyErr_Occurred()) {
      return nullptr;
    }
    return ConvertOneFloat<T>(as_int.get(), out);
  }
  return ErrorMixedTypes;
}