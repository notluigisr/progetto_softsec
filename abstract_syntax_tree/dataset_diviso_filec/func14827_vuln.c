Status TensorSliceReader::GetTensor(
    const string& name, std::unique_ptr<tensorflow::Tensor>* out_tensor) const {
  DataType type;
  TensorShape shape;
  TensorSlice slice;
  {
    mutex_lock l(mu_);
    const TensorSliceSet* tss = gtl::FindPtrOrNull(tensors_, name);
    if (tss == nullptr) {
      return errors::NotFound(name, "STR");
    }

    if (tss->Slices().size() > 1) {
      
      return errors::Unimplemented("STR");
    }

    type = tss->type();
    shape = tss->shape();
    slice = tss->Slices().begin()->second.slice;
  }

  std::unique_ptr<tensorflow::Tensor> t(new tensorflow::Tensor(type, shape));
  bool success = false;


  case dt:                                                               \
    success = CopySliceData(name, slice,                                 \
                            t->flat<EnumToDataType<dt>::Type>().data()); \
    break;

  switch (type) {
    READER_COPY(DT_FLOAT);
    READER_COPY(DT_DOUBLE);
    READER_COPY(DT_INT32);
    READER_COPY(DT_UINT8);
    READER_COPY(DT_INT16);
    READER_COPY(DT_INT8);
    READER_COPY(DT_INT64);
    READER_COPY(DT_STRING);
    default:
      return errors::Unimplemented("STR");
  }
#undef READER_COPY

  if (!success) {
    return errors::NotFound(name, "STR");
  }
  std::swap(*out_tensor, t);

  return Status::OK();
}