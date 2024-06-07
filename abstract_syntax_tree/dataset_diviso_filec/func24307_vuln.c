  void Compute(OpKernelContext* context) override {
    
    const Tensor& boxes = context->input(0);
    
    const Tensor& scores = context->input(1);
    
    const Tensor& max_output_size = context->input(2);
    OP_REQUIRES(
        context, TensorShapeUtils::IsScalar(max_output_size.shape()),
        errors::InvalidArgument("STR",
                                max_output_size.shape().DebugString()));
    
    const Tensor& iou_threshold = context->input(3);
    OP_REQUIRES(context, TensorShapeUtils::IsScalar(iou_threshold.shape()),
                errors::InvalidArgument("STR",
                                        iou_threshold.shape().DebugString()));
    const T iou_threshold_val = iou_threshold.scalar<T>()();
    OP_REQUIRES(context,
                iou_threshold_val >= static_cast<T>(0.0) &&
                    iou_threshold_val <= static_cast<T>(1.0),
                errors::InvalidArgument("STR"));
    
    const Tensor& score_threshold = context->input(4);
    OP_REQUIRES(
        context, TensorShapeUtils::IsScalar(score_threshold.shape()),
        errors::InvalidArgument("STR",
                                score_threshold.shape().DebugString()));
    const T score_threshold_val = score_threshold.scalar<T>()();

    
    const Tensor& soft_nms_sigma = context->input(5);
    OP_REQUIRES(
        context, TensorShapeUtils::IsScalar(soft_nms_sigma.shape()),
        errors::InvalidArgument("STR",
                                soft_nms_sigma.shape().DebugString()));
    const T soft_nms_sigma_val = soft_nms_sigma.scalar<T>()();
    OP_REQUIRES(context, soft_nms_sigma_val >= static_cast<T>(0.0),
                errors::InvalidArgument("STR"));

    int num_boxes = 0;
    ParseAndCheckBoxSizes(context, boxes, &num_boxes);
    CheckScoreSizes(context, num_boxes, scores);
    if (!context->status().ok()) {
      return;
    }

    auto similarity_fn = CreateIOUSimilarityFn<T>(boxes);
    int num_valid_outputs;

    
    
    const bool return_scores_tensor_ = true;
    DoNonMaxSuppressionOp<T>(
        context, scores, num_boxes, max_output_size, iou_threshold_val,
        score_threshold_val, soft_nms_sigma_val, similarity_fn,
        return_scores_tensor_, pad_to_max_output_size_, &num_valid_outputs);

    
    Tensor* num_outputs_t = nullptr;
    OP_REQUIRES_OK(context, context->allocate_output(
                                2, tensorflow::TensorShape{}, &num_outputs_t));
    num_outputs_t->scalar<int32>().setConstant(num_valid_outputs);
  }