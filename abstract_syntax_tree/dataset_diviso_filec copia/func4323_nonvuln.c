inline void FullyConnectedAsGEMV(
    const RuntimeShape& input_shape, const uint8* input_data,
    int32 input_offset, const RuntimeShape& filter_shape,
    const uint8* filter_data, int32 filter_offset,
    const RuntimeShape& bias_shape, const int32* bias_data, int32 output_offset,
    int32 output_multiplier, int output_shift, int32 output_activation_min,
    int32 output_activation_max, const RuntimeShape& output_shape,
    uint8* output_data, gemmlowp::GemmContext* gemmlowp_context) {
  const int output_dim_count = output_shape.DimensionsCount();
  const int batches = FlatSizeSkipDim(output_shape, output_dim_count - 1);
  const int output_rows = output_shape.Dims(output_dim_count - 1);
  const int input_size = FlatSizeSkipDim(input_shape, 0);
  static constexpr int kKernelRows = 4;
  const int thread_count = gemmlowp::HowManyThreads<kKernelRows>(
      gemmlowp_context->max_num_threads(), output_rows, batches, input_size);
  if (thread_count == 1) {
    
    
    LegacyFullyConnectedAsGEMVWorkerImpl(
        input_shape, input_data, input_offset, filter_shape, filter_data,
        filter_offset, bias_shape, bias_data, output_offset, output_multiplier,
        output_shift, output_activation_min, output_activation_max,
        output_shape, output_data, 0, output_rows);
    return;
  }

  
  TFLITE_DCHECK_GT(thread_count, 1);
  std::vector<gemmlowp::Task*> tasks(thread_count);
  const int kRowsPerWorker = gemmlowp::RoundUp<kKernelRows>(
      gemmlowp::CeilQuotient(output_rows, thread_count));
  int row_start = 0;
  for (int i = 0; i < thread_count; ++i) {
    int row_end = std::min(output_rows, row_start + kRowsPerWorker);
    tasks[i] = new LegacyFullyConnectedAsGEMVWorkerTask(
        input_shape, input_data, input_offset, filter_shape, filter_data,
        filter_offset, bias_shape, bias_data, output_offset, output_multiplier,
        output_shift, output_activation_min, output_activation_max,
        output_shape, output_data, row_start, row_end);
    row_start = row_end;
  }
  TFLITE_DCHECK_EQ(row_start, output_rows);
  gemmlowp_context->workers_pool()->LegacyExecuteAndDestroyTasks(tasks);
}