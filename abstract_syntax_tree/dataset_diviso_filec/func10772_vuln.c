static TfLiteStatus InitTemporaryTensors(TfLiteContext* context,
                                         TfLiteNode* node) {
  OpData* data = reinterpret_cast<OpData*>(node->user_data);
  
  
  if (data->fft_integer_working_area_id != kTensorNotAllocated &&
      data->fft_double_working_area_id != kTensorNotAllocated) {
    return kTfLiteOk;
  }

  TfLiteIntArrayFree(node->temporaries);
  
  node->temporaries = TfLiteIntArrayCreate(2);
  int first_new_index;
  TF_LITE_ENSURE_STATUS(context->AddTensors(context, 2, &first_new_index));
  node->temporaries->data[kFftIntegerWorkingAreaTensor] = first_new_index;
  data->fft_integer_working_area_id = first_new_index;
  node->temporaries->data[kFftDoubleWorkingAreaTensor] = first_new_index + 1;
  data->fft_double_working_area_id = first_new_index + 1;

  
  TfLiteTensor* fft_integer_working_area =
      GetTemporary(context, node, kFftIntegerWorkingAreaTensor);
  fft_integer_working_area->type = kTfLiteInt32;
  
  
  fft_integer_working_area->allocation_type = kTfLiteArenaRw;

  
  TfLiteTensor* fft_double_working_area =
      GetTemporary(context, node, kFftDoubleWorkingAreaTensor);
  
  
  
  
  
  
  
  fft_double_working_area->type = kTfLiteInt64;
  
  
  fft_double_working_area->allocation_type = kTfLiteArenaRw;

  return kTfLiteOk;
}