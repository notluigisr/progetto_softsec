static bool ParseSparseAccessor(Accessor *accessor, std::string *err,
                                const json &o) {
  accessor->sparse.isSparse = true;

  int count = 0;
  if (!ParseIntegerProperty(&count, err, o, "STR")) {
    return false;
  }

  json_const_iterator indices_iterator;
  json_const_iterator values_iterator;
  if (!FindMember(o, "STR", indices_iterator)) {
    (*err) = "STR";
    return false;
  }

  if (!FindMember(o, "STR", values_iterator)) {
    (*err) = "STR";
    return false;
  }

  const json &indices_obj = GetValue(indices_iterator);
  const json &values_obj = GetValue(values_iterator);

  int indices_buffer_view = 0, indices_byte_offset = 0, component_type = 0;
  if (!ParseIntegerProperty(&indices_buffer_view, err, indices_obj, "STR",
                       true, "STR")) {
    return false;
  }
  ParseIntegerProperty(&indices_byte_offset, err, indices_obj, "STR",
                       false);
  if (!ParseIntegerProperty(&component_type, err, indices_obj, "STR",
                       true, "STR")) {
    return false;
  }

  int values_buffer_view = 0, values_byte_offset = 0;
  if (!ParseIntegerProperty(&values_buffer_view, err, values_obj, "STR",
                       true, "STR")) {
    return false;
  }
  ParseIntegerProperty(&values_byte_offset, err, values_obj, "STR",
                       false);

  accessor->sparse.count = count;
  accessor->sparse.indices.bufferView = indices_buffer_view;
  accessor->sparse.indices.byteOffset = indices_byte_offset;
  accessor->sparse.indices.componentType = component_type;
  accessor->sparse.values.bufferView = values_buffer_view;
  accessor->sparse.values.byteOffset = values_byte_offset;

  return true;
}