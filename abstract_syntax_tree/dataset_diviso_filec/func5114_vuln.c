TEST(CudnnRNNOpsTest, ForwardV2Lstm_ShapeFn) {
  int seq_length = 2;
  int batch_size = 3;
  int num_units = 4;
  int num_layers = 5;
  int dir_count = 1;
  std::vector<int> input_shape = {seq_length, batch_size, num_units};
  std::vector<int> input_h_shape = {num_layers * dir_count, batch_size,
                                    num_units};
  std::vector<int> output_shape = {seq_length, batch_size,
                                   num_units * dir_count};
  auto shape_to_str = [](const std::vector<int>& v) {
    return strings::StrCat("STR");
  };
  string input_shapes_desc = strings::StrCat(
      shape_to_str(input_shape), "STR",
      shape_to_str(input_h_shape), "STR");
  string output_shapes_desc = "STR";

  ShapeInferenceTestOp op("STR");
  TF_ASSERT_OK(NodeDefBuilder("STR")
                   .Input({"STR", 0, DT_FLOAT})
                   .Input({"STR", 0, DT_FLOAT})
                   .Input({"STR", 0, DT_FLOAT})
                   .Input({"STR", 0, DT_FLOAT})
                   .Attr("STR")
                   .Attr("STR")
                   .Attr("STR")
                   .Finalize(&op.node_def));
  INFER_OK(op, input_shapes_desc, output_shapes_desc);
}