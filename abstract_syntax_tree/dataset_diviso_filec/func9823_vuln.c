  void Compute(OpKernelContext* context) override {
    const Tensor& input = context->input(0);
    const TensorShape& input_shape = input.shape();

    const Tensor& out_backprop = context->input(2);
    const TensorShape& out_backprop_shape = out_backprop.shape();

    TensorShape filter_shape;
    if (takes_shape_) {
      const Tensor& filter_sizes = context->input(1);
      OP_REQUIRES_OK(context, TensorShapeUtils::MakeShape(
                                  filter_sizes.vec<int32>(), &filter_shape));
    } else {
      filter_shape = context->input(1).shape();
    }

    ConvBackpropDimensions dims;
    OP_REQUIRES_OK(context,
                   ConvBackpropComputeDimensions(
                       "STR", 3,
                       input_shape, filter_shape, out_backprop_shape, stride_,
                       padding_, data_format_, &dims));

    Tensor* filter_backprop;
    OP_REQUIRES_OK(context,
                   context->allocate_output(0, filter_shape, &filter_backprop));

    if (input_shape.num_elements() == 0) {
      filter_backprop->template flat<T>().setZero();
      return;
    }

    functor::CuboidConvolutionBackwardFilter<Device, T>()(
        context->eigen_device<Device>(),
        filter_backprop->tensor<T, 5>(),                 
        input.tensor<T, 5>(),                            
        out_backprop.tensor<T, 5>(),                     
        static_cast<int>(dims.spatial_dims[0].stride),   
        static_cast<int>(dims.spatial_dims[1].stride),   
        static_cast<int>(dims.spatial_dims[2].stride));  
  }