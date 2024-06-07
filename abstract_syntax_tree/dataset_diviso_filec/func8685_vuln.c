void UncompressElementOp::Compute(OpKernelContext* ctx) {
  Tensor tensor = ctx->input(0);
  const Variant& variant = tensor.scalar<Variant>()();
  const CompressedElement* compressed = variant.get<CompressedElement>();

  std::vector<Tensor> components;
  OP_REQUIRES_OK(ctx, UncompressElement(*compressed, &components));
  OP_REQUIRES(ctx, components.size() == output_types_.size(),
              errors::FailedPrecondition("STR", output_types_.size(),
                                         "STR",
                                         components.size()));
  for (int i = 0; i < components.size(); ++i) {
    OP_REQUIRES(
        ctx, components[i].dtype() == output_types_[i],
        errors::FailedPrecondition("STR",
                                   DataTypeString(output_types_[i]),
                                   "STR",
                                   DataTypeString(components[i].dtype())));
    ctx->set_output(i, components[i]);
  }
}