void SetAttrValue(const gtl::ArraySlice<TensorShape> value, AttrValue* out) {
  out->mutable_list()->Clear();  
  for (const auto& v : value) {
    v.AsProto(out->mutable_list()->add_shape());
  }
}