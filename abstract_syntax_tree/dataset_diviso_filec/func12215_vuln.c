Status CompressElement(const std::vector<Tensor>& element,
                       CompressedElement* out) {
  
  
  std::vector<TensorProto> non_memcpy_components;
  int64 total_size = 0;
  for (auto& component : element) {
    if (DataTypeCanUseMemcpy(component.dtype())) {
      
      
      total_size += DMAHelper::buffer(&component)->size();
    } else {
      non_memcpy_components.emplace_back();
      component.AsProtoTensorContent(&non_memcpy_components.back());
      total_size += non_memcpy_components.back().ByteSizeLong();
    }
  }

  
  
  tstring uncompressed;
  uncompressed.resize_uninitialized(total_size);
  
  char* position = uncompressed.mdata();
  int non_memcpy_component_index = 0;
  for (auto& component : element) {
    CompressedComponentMetadata* metadata =
        out->mutable_component_metadata()->Add();
    metadata->set_dtype(component.dtype());
    component.shape().AsProto(metadata->mutable_tensor_shape());
    if (DataTypeCanUseMemcpy(component.dtype())) {
      const TensorBuffer* buffer = DMAHelper::buffer(&component);
      memcpy(position, buffer->data(), buffer->size());
      metadata->set_tensor_size_bytes(buffer->size());
    } else {
      TensorProto& proto = non_memcpy_components[non_memcpy_component_index++];
      proto.SerializeToArray(position, proto.ByteSizeLong());
      metadata->set_tensor_size_bytes(proto.ByteSizeLong());
    }
    position += metadata->tensor_size_bytes();
  }
  DCHECK_EQ(position, uncompressed.mdata() + total_size);

  if (!port::Snappy_Compress(uncompressed.mdata(), total_size,
                             out->mutable_data())) {
    return errors::Internal("STR");
  }
  VLOG(3) << "STR"
          << out->data().size() << "STR";
  return Status::OK();
}