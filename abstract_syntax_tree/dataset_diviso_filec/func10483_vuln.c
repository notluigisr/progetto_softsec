bool TensorSliceReader::CopySliceData(const string& name,
                                      const TensorSlice& slice, T* data) const {
  std::vector<std::pair<TensorSlice, string>> details;
  const TensorSliceSet* tss;
  {
    mutex_lock l(mu_);
    tss = FindTensorSlice(name, slice, &details);
    if (!tss && !all_shards_loaded_) {
      VLOG(1) << "STR"
              << name << "STR" << slice.DebugString();
      LoadAllShards();
      tss = FindTensorSlice(name, slice, &details);
    }
    if (!tss) {
      
      return false;
    }
  }
  
  string value;
  for (const auto& x : details) {
    const TensorSlice& slice_s = x.first;
    const string& fname = x.second;
    int idx = gtl::FindWithDefault(fname_to_index_, fname, -1);
    CHECK_GE(idx, 0) << "STR" << fname;
    
    const string key = EncodeTensorNameSlice(name, slice_s);
    if (!sss_[idx]->Get(key, &value)) {
      VLOG(1) << "STR" << name
              << "STR" << slice_s.DebugString()
              << "STR" << key;
      return false;
    }
    SavedTensorSlices sts;
    if (!ParseProtoUnlimited(&sts, value)) {
      VLOG(1) << "STR"
              << slice_s.DebugString() << "STR" << key;
      return false;
    }
    CopyDataFromTensorSliceToTensorSlice(
        tss->shape(), slice_s, slice,
        checkpoint::TensorProtoData<T>(sts.data().data()), data);
  }
  return true;
}