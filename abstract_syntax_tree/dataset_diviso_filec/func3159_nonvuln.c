tstring KeyedDenseTensorColumn<tstring>::Feature(int64 batch, int64 n,
                                                 bool strong_hash) const {
  if (DT_STRING == tensor_.dtype()) return tensor_.matrix<tstring>()(batch, n);
  return std::to_string(tensor_.matrix<int64>()(batch, n));
}