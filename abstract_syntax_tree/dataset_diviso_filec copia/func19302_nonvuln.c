  bool memcpy_field_possible(const Field *from) const
  {
    return real_type() == from->real_type() &&
           pack_length() == from->pack_length() &&
           is_unsigned() == from->is_unsigned();
  }