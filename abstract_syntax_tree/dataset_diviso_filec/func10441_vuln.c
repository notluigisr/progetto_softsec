void SparseFillEmptyRowsOpImpl(OpKernelContext* context,
                               AsyncOpKernel::DoneCallback done = nullptr) {
  
  
  if (!done) {
    done = [] {};
  }

  const int kIndicesInput = 0;
  const int kValuesInput = 1;
  const int kDenseShapeInput = 2;
  const int kDefaultValueInput = 3;

  const Tensor& indices_t = context->input(kIndicesInput);
  const Tensor& values_t = context->input(kValuesInput);
  const Tensor& dense_shape_t = context->input(kDenseShapeInput);
  const Tensor& default_value_t = context->input(kDefaultValueInput);

  OP_REQUIRES_ASYNC(
      context, TensorShapeUtils::IsVector(dense_shape_t.shape()),
      errors::InvalidArgument("STR",
                              dense_shape_t.shape().DebugString()),
      done);
  OP_REQUIRES_ASYNC(context, TensorShapeUtils::IsMatrix(indices_t.shape()),
                    errors::InvalidArgument("STR",
                                            indices_t.shape().DebugString()),
                    done);
  OP_REQUIRES_ASYNC(context, TensorShapeUtils::IsVector(values_t.shape()),
                    errors::InvalidArgument("STR",
                                            values_t.shape().DebugString()),
                    done);
  OP_REQUIRES_ASYNC(
      context, TensorShapeUtils::IsScalar(default_value_t.shape()),
      errors::InvalidArgument("STR",
                              default_value_t.shape().DebugString()),
      done);
  
  
  OP_REQUIRES_ASYNC(context, dense_shape_t.NumElements() != 0,
                    errors::InvalidArgument("STR"),
                    done);

  using FunctorType = functor::SparseFillEmptyRows<Device, T, Tindex>;
  OP_REQUIRES_OK_ASYNC(context,
                       FunctorType()(context, default_value_t, indices_t,
                                     values_t, dense_shape_t, done),
                       done);
}