  void operator()(OpKernelContext* context, const Tensor& input_tensor,
                  Tensor& output_tensor, int n, bool reverse) {
    const T* input = input_tensor.flat<T>().data();
    T* output = output_tensor.flat<T>().data();

    
    
    const int num_rows = output_tensor.NumElements();
    const int last_dim = input_tensor.dim_size(input_tensor.dims() - 1);

    
    auto SubNthElement = [&, input, output, last_dim, n](int start, int limit) {
      
      std::vector<T> buf(last_dim);

      for (int b = start; b < limit; ++b) {
        
        const T* input_start = input + b * last_dim;
        const T* input_end = input + (b + 1) * last_dim;
        std::copy(input_start, input_end, buf.begin());

        std::nth_element(buf.begin(), buf.begin() + n, buf.end());
        
        
        output[b] = buf[n];
      }
    };

    auto worker_threads = *(context->device()->tensorflow_cpu_worker_threads());
    
    
    
    Shard(worker_threads.num_threads, worker_threads.workers, num_rows,
          20 * last_dim, SubNthElement);
  }