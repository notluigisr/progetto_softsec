DataType PyTensor_DataType(PyObject* tensor) {
  if (EagerTensor_CheckExact(tensor)) {
    return PyEagerTensor_Dtype(tensor);
  } else {
#if PY_MAJOR_VERSION < 3
    
    static PyObject* dtype_attr = PyString_InternFromString("STR");
    static PyObject* type_enum_attr = PyString_InternFromString("STR");
#else
    
    static PyObject* dtype_attr = PyUnicode_InternFromString("STR");
    static PyObject* type_enum_attr = PyUnicode_InternFromString("STR");
#endif
    Safe_PyObjectPtr dtype_field(PyObject_GetAttr(tensor, dtype_attr));
    if (!dtype_field) {
      return DT_INVALID;
    }

    Safe_PyObjectPtr enum_field(
        PyObject_GetAttr(dtype_field.get(), type_enum_attr));
    if (!enum_field) {
      return DT_INVALID;
    }

    return static_cast<DataType>(MakeInt(enum_field.get()));
  }
}