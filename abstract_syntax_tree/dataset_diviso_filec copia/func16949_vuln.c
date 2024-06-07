  static const char* ConvertScalar(PyObject* v, bool* out) {
    if (v == Py_True) {
      *out = true;
    } else if (v == Py_False) {
      *out = false;
    } else if (PyIsInstance(v, &PyBoolArrType_Type)) {  
      *out = PyObject_IsTrue(v);
    } else {
      return ErrorMixedTypes;
    }
    return nullptr;
  }