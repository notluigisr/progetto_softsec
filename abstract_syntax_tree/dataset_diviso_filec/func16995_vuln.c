TfLiteStatus EvalGatherNd(TfLiteContext* context,
                          const TfLiteEvalTensor* params,
                          const TfLiteEvalTensor* indices,
                          TfLiteEvalTensor* output) {
  switch (params->type) {
    case kTfLiteFloat32:
      return GatherNd<float, IndicesT>(params, indices, output);
      break;
    case kTfLiteInt8:
      return GatherNd<int8_t, IndicesT>(params, indices, output);
      break;
    default:
      TF_LITE_KERNEL_LOG(context,
                         "STR",
                         TfLiteTypeGetName(params->type));
      return kTfLiteError;
  }
}