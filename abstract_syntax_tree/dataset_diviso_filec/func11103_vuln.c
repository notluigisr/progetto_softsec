Status GraphConstructor::MakeEdge(Node* src, int output_index, Node* dst,
                                  int input_index) {
  DataType src_out = src->output_type(output_index);
  DataType dst_in = dst->input_type(input_index);
  if (!TypesCompatible(dst_in, src_out)) {
    return errors::InvalidArgument(
        "STR",
        DataTypeString(src_out), "STR", output_index,
        "STR");
  }
  g_->AddEdge(src, output_index, dst, input_index);
  return Status::OK();
}