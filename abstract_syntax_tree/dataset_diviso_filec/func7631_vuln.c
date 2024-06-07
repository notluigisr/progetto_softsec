  static const char* ConvertScalar(PyObject* v, int64* out) {
#if PY_MAJOR_VERSION < 3
    if (TF_PREDICT_TRUE(PyInt_Check(v))) {
      *out = PyInt_AS_LONG(v);
      return nullptr;
    }
#endif
    if (TF_PREDICT_TRUE(PyLong_Check(v) || IsPyDimension(v))) {
      int overflow = 0;
      
      *out = PyLong_AsLongLongAndOverflow(v, &overflow);
      if (TF_PREDICT_FALSE(overflow)) return ErrorOutOfRange;
      return nullptr;
    }
    if (PyIsInstance(v, &PyIntegerArrType_Type)) {  
#if PY_MAJOR_VERSION < 3
      Safe_PyObjectPtr as_int = make_safe(PyNumber_Int(v));
#else
      Safe_PyObjectPtr as_int = make_safe(PyNumber_Long(v));
#endif
      return ConvertScalar(as_int.get(), out);
    }
    if (IsPyFloat(v)) return ErrorFoundFloat;
    return ErrorMixedTypes;
  }