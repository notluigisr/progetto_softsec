  Status ValidateInputsGenerateOutputs(
      OpKernelContext* ctx, const Tensor** inputs, const Tensor** seq_len,
      Tensor** log_prob, OpOutputList* decoded_indices,
      OpOutputList* decoded_values, OpOutputList* decoded_shape) const {
    Status status = ctx->input("STR", inputs);
    if (!status.ok()) return status;
    status = ctx->input("STR", seq_len);
    if (!status.ok()) return status;

    const TensorShape& inputs_shape = (*inputs)->shape();

    if (inputs_shape.dims() != 3) {
      return errors::InvalidArgument("STR");
    }

    const int64 max_time = inputs_shape.dim_size(0);
    const int64 batch_size = inputs_shape.dim_size(1);

    if (max_time == 0) {
      return errors::InvalidArgument("STR");
    }
    if (!TensorShapeUtils::IsVector((*seq_len)->shape())) {
      return errors::InvalidArgument("STR");
    }

    if (!(batch_size == (*seq_len)->dim_size(0))) {
      return errors::FailedPrecondition(
          "STR",
          "STR", (*seq_len)->dim_size(0),
          "STR", batch_size);
    }

    auto seq_len_t = (*seq_len)->vec<int32>();

    for (int b = 0; b < batch_size; ++b) {
      if (!(seq_len_t(b) <= max_time)) {
        return errors::FailedPrecondition("STR", b,
                                          "STR", max_time);
      }
    }

    Status s = ctx->allocate_output(
        "STR", TensorShape({batch_size, top_paths_}), log_prob);
    if (!s.ok()) return s;

    s = ctx->output_list("STR", decoded_indices);
    if (!s.ok()) return s;
    s = ctx->output_list("STR", decoded_values);
    if (!s.ok()) return s;
    s = ctx->output_list("STR", decoded_shape);
    if (!s.ok()) return s;

    return Status::OK();
  }