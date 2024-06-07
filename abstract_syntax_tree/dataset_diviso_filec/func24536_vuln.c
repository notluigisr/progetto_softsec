  static const char* ConvertScalar(PyObject* v, tstring* out) {
    if (PyBytes_Check(v)) {
      out->assign(PyBytes_AS_STRING(v), PyBytes_GET_SIZE(v));
      return nullptr;
    }
    if (PyUnicode_Check(v)) {
#if PY_MAJOR_VERSION >= 3
      Py_ssize_t size;
      const char* str = PyUnicode_AsUTF8AndSize(v, &size);
      if (str == nullptr) return ErrorConvertingUnicodeString;
      out->assign(str, size);
      return nullptr;
#else
      PyObject* py_str = PyUnicode_AsUTF8String(v);
      if (py_str == nullptr) return ErrorConvertingUnicodeString;
      out->assign(PyBytes_AS_STRING(py_str), PyBytes_GET_SIZE(py_str));
      Py_DECREF(py_str);
      return nullptr;
#endif
    }
    return ErrorMixedTypes;
  }