Status TF_TensorToPyArray(Safe_TF_TensorPtr tensor, PyObject** out_ndarray) {
  
  
  if (tensor == nullptr) {
    Py_INCREF(Py_None);
    *out_ndarray = Py_None;
    return Status::OK();
  }
  int64 nelems = -1;
  gtl::InlinedVector<npy_intp, 4> dims;
  TF_RETURN_IF_ERROR(
      GetPyArrayDimensionsForTensor(tensor.get(), &dims, &nelems));

  
  TF_Tensor* original = tensor.get();
  TF_Tensor* moved = TF_TensorMaybeMove(tensor.release());
  if (moved != nullptr) {
    if (ArrayFromMemory(
            dims.size(), dims.data(), TF_TensorData(moved),
            static_cast<DataType>(TF_TensorType(moved)),
            [moved] { TF_DeleteTensor(moved); }, out_ndarray)
            .ok()) {
      return Status::OK();
    }
  }
  tensor.reset(original);

  
  PyArray_Descr* descr = nullptr;
  TF_RETURN_IF_ERROR(GetPyArrayDescrForTensor(tensor.get(), &descr));
  Safe_PyObjectPtr safe_out_array =
      tensorflow::make_safe(PyArray_Empty(dims.size(), dims.data(), descr, 0));
  if (!safe_out_array) {
    return errors::Internal("STR");
  }
  PyArrayObject* py_array =
      reinterpret_cast<PyArrayObject*>(safe_out_array.get());
  if (TF_TensorType(tensor.get()) == TF_STRING) {
    Status s = CopyTF_TensorStringsToPyArray(tensor.get(), nelems, py_array);
    if (!s.ok()) {
      return s;
    }
  } else if (static_cast<size_t>(PyArray_NBYTES(py_array)) !=
             TF_TensorByteSize(tensor.get())) {
    return errors::Internal("STR", PyArray_NBYTES(py_array),
                            "STR",
                            TF_TensorByteSize(tensor.get()), "STR");
  } else {
    FastMemcpy(PyArray_DATA(py_array), TF_TensorData(tensor.get()),
               PyArray_NBYTES(py_array));
  }

  *out_ndarray = safe_out_array.release();
  return Status::OK();
}