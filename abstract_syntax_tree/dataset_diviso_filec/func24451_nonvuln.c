Py_ssize_t TensorShapeNumDims(PyObject* value) {
  const auto size = PySequence_Size(value);
  if (size == -1) {
    
    
    
    PyErr_Clear();
  }
  return size;
}