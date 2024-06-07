void TensorSliceReader::LoadShard(int shard) const {
  CHECK_LT(shard, sss_.size());
  if (sss_[shard] || !status_.ok()) {
    return;  
  }
  string value;
  SavedTensorSlices sts;
  const string fname = fnames_[shard];
  VLOG(1) << "STR";
  Table* table;
  Status s = open_function_(fname, &table);
  if (!s.ok()) {
    status_ = errors::DataLoss("STR",
                               s.ToString());
    return;
  }
  sss_[shard].reset(table);
  if (!(table->Get(kSavedTensorSlicesKey, &value) &&
        ParseProtoUnlimited(&sts, value))) {
    status_ = errors::Internal(
        "STR"
        "STR",
        fname);
    return;
  }
  status_ = CheckVersions(sts.meta().versions(), TF_CHECKPOINT_VERSION,
                          TF_CHECKPOINT_VERSION_MIN_PRODUCER, "STR",
                          "STR");
  if (!status_.ok()) return;
  for (const SavedSliceMeta& ssm : sts.meta().tensor()) {
    TensorShape ssm_shape(ssm.shape());
    for (const TensorSliceProto& tsp : ssm.slice()) {
      TensorSlice ss_slice(tsp);
      status_ = RegisterTensorSlice(ssm.name(), ssm_shape, ssm.type(), fname,
                                    ss_slice, &tensors_);
      if (!status_.ok()) return;
    }
  }
}