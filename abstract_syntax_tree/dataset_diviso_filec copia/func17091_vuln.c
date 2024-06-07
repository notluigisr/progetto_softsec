inline const TfLiteTensor* GetIntermediates(TfLiteContext* context,
                                            const TfLiteNode* node, int index) {
  return &context->tensors[node->intermediates->data[index]];
}