TfLiteStatus Eval(TfLiteContext* context, TfLiteNode* node) {
  const TfLiteTensor* value = GetInput(context, node, kValueTensor);

  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);

  if (IsDynamicTensor(output)) {
    const TfLiteTensor* dims = GetInput(context, node, kDimsTensor);
    TF_LITE_ENSURE_OK(context, ResizeOutput(context, dims, output));
  }

  reference_ops::Fill(GetTensorShape(value), GetTensorData<data_type>(value), \
                      GetTensorShape(output),                                 \
                      GetTensorData<data_type>(output))
  switch (output->type) {
    case kTfLiteInt32:
      TF_LITE_FILL(int32_t);
      break;
    case kTfLiteInt64:
      TF_LITE_FILL(int64_t);
      break;
    case kTfLiteFloat32:
      TF_LITE_FILL(float);
      break;
    case kTfLiteBool:
      TF_LITE_FILL(bool);
      break;
    case kTfLiteString:
      FillString(value, output);
      break;
    default:
      context->ReportError(
          context,
          "STR"
          "STR",
          value->type);
      return kTfLiteError;
  }
#undef TF_LITE_FILL
  return kTfLiteOk;
}