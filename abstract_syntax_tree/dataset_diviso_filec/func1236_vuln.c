  friend bool operator==(const TensorKey& t1, const TensorKey& t2) {
    if (t1.dtype() != t2.dtype() || t1.shape() != t2.shape()) {
      return false;
    }
    if (DataTypeCanUseMemcpy(t1.dtype())) {
      return t1.tensor_data() == t2.tensor_data();
    }
    if (t1.dtype() == DT_STRING) {
      const auto s1 = t1.unaligned_flat<tstring>();
      const auto s2 = t2.unaligned_flat<tstring>();
      for (int64_t i = 0, n = t1.NumElements(); i < n; ++i) {
        if (TF_PREDICT_FALSE(s1(i) != s2(i))) {
          return false;
        }
      }
      return true;
    }
    return false;
  }