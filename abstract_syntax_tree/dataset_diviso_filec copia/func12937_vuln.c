  static const char* ConvertScalar(PyObject* v, int32* out) {
    int64 i;
#if PY_MAJOR_VERSION < 3
    if (TF_PREDICT_TRUE(PyInt_Check(v))) {
      i = PyInt_AS_LONG(v);
    } else
#endif
        if (PyLong_Check(v) || IsPyDimension(v)) {
      int overflow = 0;
      
      i = PyLong_AsLongLongAndOverflow(v, &overflow);
      if (TF_PREDICT_FALSE(overflow)) return ErrorOutOfRange;
    } else if (PyIsInstance(v, &PyIntegerArrType_Type)) {  
#if PY_MAJOR_VERSION < 3
      Safe_PyObjectPtr as_int = make_safe(PyNumber_Int(v));
#else
      Safe_PyObjectPtr as_int = make_safe(PyNumber_Long(v));
#endif
      return ConvertScalar(as_int.get(), out);
    } else if (IsPyFloat(v)) {
      return ErrorFoundFloat;
    } else {
      return ErrorMixedTypes;
    }
    *out = static_cast<uint32>(static_cast<uint64>(i));
    
    if (TF_PREDICT_FALSE(i != *out)) return ErrorFoundInt64;
    return nullptr;
  }