  SoftmaxWorkerTask(const SoftmaxParams& params,
                    const RuntimeShape& input_shape, const float* input_data,
                    const RuntimeShape& output_shape, float* output_data,
                    int start_batch, int end_batch)
      : params(params),
        input_shape(input_shape),
        input_data(input_data),
        output_shape(output_shape),
        output_data(output_data),
        start_batch(start_batch),
        end_batch(end_batch) {}