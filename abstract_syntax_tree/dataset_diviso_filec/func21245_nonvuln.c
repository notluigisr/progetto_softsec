TEST(ArrayOpsTest, UnravelIndex_ShapeFn) {
  ShapeInferenceTestOp op("STR");

  INFER_OK(op, "STR");

  INFER_OK(op, "STR");

  INFER_OK(op, "STR");
  INFER_OK(op, "STR");
  INFER_OK(op, "STR");
  INFER_OK(op, "STR");

  INFER_ERROR("STR");
}