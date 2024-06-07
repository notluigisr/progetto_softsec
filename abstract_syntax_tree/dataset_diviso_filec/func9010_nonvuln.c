  void ComputeAsync(OpKernelContext* context, DoneCallback done) override {
    
    const Tensor& grads = context->input(0);
    
    const Tensor& boxes = context->input(2);
    
    const Tensor& box_index = context->input(3);
    
    const Tensor& image = context->input(1);

    
    OP_REQUIRES_ASYNC(context, grads.dims() == 4,
                      errors::InvalidArgument("STR",
                                              grads.shape().DebugString()),
                      done);
    const int crop_height = grads.dim_size(1);
    const int crop_width = grads.dim_size(2);
    const int depth = grads.dim_size(3);
    OP_REQUIRES_ASYNC(
        context, crop_height > 0 && crop_width > 0,
        errors::InvalidArgument("STR"), done);

    OP_REQUIRES_ASYNC(context, image.dims() == 4,
                      errors::InvalidArgument("STR",
                                              image.shape().DebugString()),
                      done);
    const int batch_size = image.dim_size(0);
    const int image_height = image.dim_size(1);
    const int image_width = image.dim_size(2);
    OP_REQUIRES_ASYNC(
        context, image_height > 0 && image_width > 0,
        errors::InvalidArgument("STR"), done);
    OP_REQUIRES_ASYNC(context, image.dim_size(3) == depth,
                      errors::InvalidArgument("STR"),
                      done);

    int num_boxes = 0;
    OP_REQUIRES_OK_ASYNC(
        context, ParseAndCheckBoxSizes(boxes, box_index, &num_boxes), done);

    OP_REQUIRES_ASYNC(
        context, grads.dim_size(0) == num_boxes,
        errors::InvalidArgument("STR"),
        done);

    
    Tensor* output = nullptr;
    OP_REQUIRES_OK_ASYNC(
        context,
        context->allocate_output(0, TensorShape({num_boxes, 4}), &output),
        done);

    auto compute_callback = [context, output]() {
      const Tensor& grads = context->input(0);
      const Tensor& image = context->input(1);
      const Tensor& boxes = context->input(2);
      const Tensor& box_index = context->input(3);
      const bool status = functor::CropAndResizeBackpropBoxes<Device, T>()(
          context->eigen_device<Device>(), grads.tensor<float, 4>(),
          image.tensor<T, 4>(), boxes.tensor<float, 2>(),
          box_index.tensor<int32, 1>(), output->tensor<float, 2>());
      if (!status) {
        context->SetStatus(errors::Internal(
            "STR"));
      }
    };

    RunIfBoxIndexIsValid<Device>(context, box_index.tensor<int32, 1>(),
                                 batch_size, std::move(compute_callback),
                                 std::move(done));
  }