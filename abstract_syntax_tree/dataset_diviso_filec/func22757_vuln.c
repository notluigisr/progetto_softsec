Status PyArrayDescr_to_TF_DataType(PyArray_Descr* descr,
                                   TF_DataType* out_tf_datatype) {
  PyObject* key;
  PyObject* value;
  Py_ssize_t pos = 0;
  if (PyDict_Next(descr->fields, &pos, &key, &value)) {
    
    
    const char* key_string =
        PyBytes_Check(key) ? PyBytes_AsString(key)
                           : PyBytes_AsString(PyUnicode_AsASCIIString(key));
    if (!key_string) {
      return errors::Internal("STR");
    }
    tensorflow::string key = key_string;
    
    
    
    
    if (key == "STR") {
      *out_tf_datatype = TF_QUINT8;
    } else if (key == "STR") {
      *out_tf_datatype = TF_QINT8;
    } else if (key == "STR") {
      *out_tf_datatype = TF_QINT16;
    } else if (key == "STR") {
      *out_tf_datatype = TF_QUINT16;
    } else if (key == "STR") {
      *out_tf_datatype = TF_QINT32;
    } else if (key == "STR") {
      *out_tf_datatype = TF_RESOURCE;
    } else {
      return errors::Internal("STR");
    }
    return Status::OK();
  }
  return errors::Internal("STR");
}