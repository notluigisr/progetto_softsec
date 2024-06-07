  void Compute(OpKernelContext* context) override {
    
    
    const Tensor& input = context->input(0);

    
    
    const Tensor& filter = context->input(1);

    
    
    OP_REQUIRES(context, input.dims() == 5,
                errors::InvalidArgument("STR"));
    OP_REQUIRES(context, filter.dims() == 5,
                errors::InvalidArgument("STR"));

    const int64 in_depth = GetTensorDim(input, data_format_, 'C');
    const int64 in_batch = GetTensorDim(input, data_format_, 'N');

    const int64 filter_depth = filter.dim_size(3);
    const int64 out_depth = filter.dim_size(4);

    OP_REQUIRES(context, in_depth % filter_depth == 0,
                errors::InvalidArgument(
                    "STR",
                    in_depth, "STR", filter_depth));

    
    std::array<int64, 3> input_size = {
        {GetTensorDim(input, data_format_, '0'),
         GetTensorDim(input, data_format_, '1'),
         GetTensorDim(input, data_format_, '2')}};
    std::array<int64, 3> filter_size = {
        {filter.dim_size(0), filter.dim_size(1), filter.dim_size(2)}};
    std::array<int64, 3> dilations = {
        {GetTensorDim(dilation_, data_format_, '0'),
         GetTensorDim(dilation_, data_format_, '1'),
         GetTensorDim(dilation_, data_format_, '2')}};
    std::array<int64, 3> strides = {{GetTensorDim(stride_, data_format_, '0'),
                                     GetTensorDim(stride_, data_format_, '1'),
                                     GetTensorDim(stride_, data_format_, '2')}};
    std::array<int64, 3> out, padding;

    OP_REQUIRES_OK(
        context, Get3dOutputSizeV2(input_size, filter_size, dilations, strides,
                                   padding_, &out, &padding));
    TensorShape out_shape = ShapeFromFormat(
        data_format_, in_batch, {{out[0], out[1], out[2]}}, out_depth);
    Tensor* output;
    OP_REQUIRES_OK(context, context->allocate_output(0, out_shape, &output));

    
    if (out_shape.num_elements() == 0) return;

    LaunchConvOp<Device, T>::launch(context, cudnn_use_autotune_, input, filter,
                                    dilations, strides, padding_, data_format_,
                                    output);
  }