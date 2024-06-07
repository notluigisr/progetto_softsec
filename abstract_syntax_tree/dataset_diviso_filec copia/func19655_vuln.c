TfLiteStatus InitializeTemporaries(TfLiteContext* context, TfLiteNode* node,
                                   OpContext* op_context) {
  
  OpData* op_data = reinterpret_cast<OpData*>(node->user_data);
  TfLiteIntArrayFree(node->temporaries);
  node->temporaries = TfLiteIntArrayCreate(3);
  node->temporaries->data[0] = op_data->scratch_tensor_index;
  TfLiteTensor* scratch_tensor = GetTemporary(context, node, 0);
  scratch_tensor->type = kTfLiteInt32;
  scratch_tensor->allocation_type = kTfLiteArenaRw;
  TfLiteIntArray* index_size = TfLiteIntArrayCreate(1);
  index_size->data[0] = NumDimensions(op_context->input);
  TF_LITE_ENSURE_OK(context,
                    context->ResizeTensor(context, scratch_tensor, index_size));

  
  node->temporaries->data[1] = op_data->scratch_tensor_index + 1;
  TfLiteTensor* resolved_axis = GetTemporary(context, node, 1);
  resolved_axis->type = kTfLiteInt32;
  
  node->temporaries->data[2] = op_data->scratch_tensor_index + 2;
  TfLiteTensor* temp_sum = GetTemporary(context, node, 2);
  switch (op_context->input->type) {
    case kTfLiteFloat32:
      temp_sum->type = kTfLiteFloat32;
      break;
    case kTfLiteInt32:
      temp_sum->type = kTfLiteInt64;
      break;
    case kTfLiteInt64:
      temp_sum->type = kTfLiteInt64;
      break;
    case kTfLiteUInt8:
    case kTfLiteInt8:
    case kTfLiteInt16:
      temp_sum->type = kTfLiteInt32;
      break;
    case kTfLiteBool:
      temp_sum->type = kTfLiteBool;
      break;
    default:
      return kTfLiteError;
  }
  return kTfLiteOk;
}