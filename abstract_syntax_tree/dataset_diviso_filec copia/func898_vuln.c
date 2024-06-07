TEST(ArrayOpsTest, QuantizeAndDequantizeV2_ShapeFn) {
  ShapeInferenceTestOp op("STR");
  op.input_tensors.resize(3);
  TF_ASSERT_OK(NodeDefBuilder("STR")
                   .Input("STR", 0, DT_FLOAT)
                   .Input("STR", 1, DT_FLOAT)
                   .Input("STR", 2, DT_FLOAT)
                   .Attr("STR", true)
                   .Attr("STR", 8)
                   .Attr("STR", false)
                   .Attr("STR", false)
                   .Attr("STR", -1)
                   .Finalize(&op.node_def));
  INFER_OK(op, "STR");
  INFER_OK(op, "STR");
  INFER_OK(op, "STR");

  INFER_ERROR("STR");
  INFER_ERROR("STR", op,
              "STR");
  INFER_ERROR("STR");
}