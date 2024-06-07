void EvalHybrid(TfLiteContext* context, TfLiteNode* node,
                TfLiteConvParams* params, OpData* data,
                const TfLiteTensor* input, const TfLiteTensor* filter,
                const TfLiteTensor* bias, TfLiteTensor* im2col,
                TfLiteTensor* accum_scratch, TfLiteTensor* output) {
  float output_activation_min, output_activation_max;
  CalculateActivationRange(params->activation, &output_activation_min,
                           &output_activation_max);

  const int input_size = NumElements(input) / SizeOfDimension(input, 0);
  const int batch_size = SizeOfDimension(input, 0);

  const float* input_ptr = GetTensorData<float>(input);
  int8_t* quantized_input_ptr_batch = GetTensorData<int8_t>(
      GetTemporary(context, node, data->input_quantized_index));
  float* scaling_factors_ptr = GetTensorData<float>(
      GetTemporary(context, node, data->scaling_factors_index));

  
  {
    ruy::profiler::ScopeLabel label("STR");
    for (int b = 0; b < batch_size; ++b) {
      float unused_min, unused_max;
      const int offset = b * input_size;
      tensor_utils::SymmetricQuantizeFloats(
          input_ptr + offset, input_size, quantized_input_ptr_batch + offset,
          &unused_min, &unused_max, &scaling_factors_ptr[b]);
      scaling_factors_ptr[b] *= filter->params.scale;
    }
  }

  switch (kernel_type) {
    case kReference:
    case kGenericOptimized:
    case kMultithreadOptimized:
    case kCblasOptimized: {
      
      ConvParams op_params;
      op_params.padding_type = PaddingType::kSame;
      op_params.padding_values.width = data->padding.width;
      op_params.padding_values.height = data->padding.height;
      op_params.stride_width = params->stride_width;
      op_params.stride_height = params->stride_height;
      op_params.dilation_width_factor = 1;
      op_params.dilation_height_factor = 1;
      op_params.float_activation_min = output_activation_min;
      op_params.float_activation_max = output_activation_max;
      optimized_ops::HybridConv(
          op_params, scaling_factors_ptr, GetTensorShape(input),
          quantized_input_ptr_batch, GetTensorShape(filter),
          GetTensorData<int8_t>(filter), GetTensorShape(bias),
          GetTensorData<float>(bias), GetTensorShape(accum_scratch),
          GetTensorData<int32_t>(accum_scratch), GetTensorShape(output),
          GetTensorData<float>(output), GetTensorShape(im2col),
          GetTensorData<int8_t>(im2col),
          CpuBackendContext::GetFromContext(context));
      break;
    }
  }
}