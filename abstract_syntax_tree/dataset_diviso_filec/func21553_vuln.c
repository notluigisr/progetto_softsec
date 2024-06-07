  void Compute(OpKernelContext* context) override {
    const Tensor& filter = context->input(1);
    const TensorShape& filter_shape = filter.shape();

    const Tensor& out_backprop = context->input(2);
    const TensorShape& out_backprop_shape = out_backprop.shape();

    TensorShape input_shape;
    if (takes_shape_) {
      const Tensor& input_sizes = context->input(0);
      
      
      OP_REQUIRES_OK(context, tensor::MakeShape(input_sizes, &input_shape));
    } else {
      input_shape = context->input(0).shape();
    }

    OP_REQUIRES(
        context, input_shape.dim_size(4) == filter_shape.dim_size(3),
        errors::InvalidArgument("STR"
                                "STR",
                                input_shape.dim_size(4), "STR",
                                filter_shape.dim_size(3), "STR"));
    OP_REQUIRES(
        context, out_backprop_shape.dim_size(4) == filter_shape.dim_size(4),
        errors::InvalidArgument("STR"
                                "STR",
                                out_backprop_shape.dim_size(4),
                                "STR",
                                filter_shape.dim_size(4), "STR"));

    ConvBackpropDimensions dims;
    OP_REQUIRES_OK(context, ConvBackpropComputeDimensions(
                                "STR", 3,
                                input_shape, filter_shape, out_backprop_shape,
                                stride_, padding_, data_format_, &dims));

    Tensor* in_backprop;
    OP_REQUIRES_OK(context,
                   context->allocate_output(0, input_shape, &in_backprop));

    functor::CuboidConvolutionBackwardInput<Device, T>()(
        context->eigen_device<Device>(),
        in_backprop->tensor<T, 5>(),                     
        filter.tensor<T, 5>(),                           
        out_backprop.tensor<T, 5>(),                     
        static_cast<int>(dims.spatial_dims[0].stride),   
        static_cast<int>(dims.spatial_dims[1].stride),   
        static_cast<int>(dims.spatial_dims[2].stride));  
  }