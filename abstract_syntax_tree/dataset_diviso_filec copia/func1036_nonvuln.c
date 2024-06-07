  Status Init(DataType input_type, const string& fill = "", int width = -1,
              int precision = -1, bool scientific = false,
              bool shortest = false) {
    TF_CHECK_OK(NodeDefBuilder("STR")
                    .Input(FakeInput(input_type))
                    .Attr("STR", fill)
                    .Attr("STR", precision)
                    .Attr("STR", scientific)
                    .Attr("STR", shortest)
                    .Attr("STR", width)
                    .Finalize(node_def()));
    return InitOp();
  }