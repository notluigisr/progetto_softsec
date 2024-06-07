TfLiteStatus SelectEval(TfLiteContext* context, TfLiteNode* node) {
  OpData* data = reinterpret_cast<OpData*>(node->user_data);
  const TfLiteTensor* input_condition =
      GetInput(context, node, kInputTensorCondition);
  const TfLiteTensor* input_x = GetInput(context, node, kInputTensorX);
  const TfLiteTensor* input_y = GetInput(context, node, kInputTensorY);
  TfLiteTensor* output = GetOutput(context, node, kOutputTensor);


  reference_ops::op(GetTensorShape(input_condition),                       \
                    GetTensorData<bool>(input_condition),                  \
                    GetTensorShape(input_x), GetTensorData<type>(input_x), \
                    GetTensorShape(input_y), GetTensorData<type>(input_y), \
                    GetTensorShape(output), GetTensorData<type>(output));


  switch (type) {                                                              \
    break;                                                                     \
    case kTfLiteBool:                                                          \
      TF_LITE_SELECT(bool, op);                                                \
      break;                                                                   \
    case kTfLiteFloat32:                                                       \
      TF_LITE_SELECT(float, op);                                               \
      break;                                                                   \
    case kTfLiteUInt8:                                                         \
      TF_LITE_SELECT(uint8_t, op);                                             \
      break;                                                                   \
    case kTfLiteInt8:                                                          \
      TF_LITE_SELECT(int8_t, op);                                              \
      break;                                                                   \
    case kTfLiteInt16:                                                         \
      TF_LITE_SELECT(int16_t, op);                                             \
      break;                                                                   \
    case kTfLiteInt32:                                                         \
      TF_LITE_SELECT(int32_t, op);                                             \
      break;                                                                   \
    case kTfLiteInt64:                                                         \
      TF_LITE_SELECT(int64_t, op);                                             \
      break;                                                                   \
    default:                                                                   \
      context->ReportError(context,                                            \
                           "STR" \
                           "STR",                                           \
                           type);                                              \
      return kTfLiteError;                                                     \
  }

  if (data->has_low_rank_input_condition) {
    TF_LITE_SWITCH(input_x->type, RankOneSelect);
  } else if (data->requires_broadcast) {
    TF_LITE_SWITCH(input_x->type, BroadcastSelect4DSlow);
  } else {
    TF_LITE_SWITCH(input_x->type, Select);
  }

#undef TF_LITE_SELECT
#undef TF_LITE_SWITCH
  return kTfLiteOk;
}