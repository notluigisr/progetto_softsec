  py::handle get_device_name() const {
    return GetPyObject(&GetData()->device_name);
  }