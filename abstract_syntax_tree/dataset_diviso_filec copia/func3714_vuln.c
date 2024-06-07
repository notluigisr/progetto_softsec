  static Status Compute(OpKernelContext* context,
                        const typename TTypes<T, 1>::ConstTensor& values,
                        const typename TTypes<T, 1>::ConstTensor& value_range,
                        int32_t nbins, typename TTypes<Tout, 1>::Tensor& out) {
    const CPUDevice& d = context->eigen_device<CPUDevice>();

    Tensor index_to_bin_tensor;

    TF_RETURN_IF_ERROR(context->forward_input_or_allocate_temp(
        {0}, DataTypeToEnum<int32>::value, TensorShape({values.size()}),
        &index_to_bin_tensor));
    auto index_to_bin = index_to_bin_tensor.flat<int32>();

    const double step = static_cast<double>(value_range(1) - value_range(0)) /
                        static_cast<double>(nbins);
    const double nbins_minus_1 = static_cast<double>(nbins - 1);

    
    
    
    
    

    
    
    index_to_bin.device(d) =
        ((values.cwiseMax(value_range(0)) - values.constant(value_range(0)))
             .template cast<double>() /
         step)
            .cwiseMin(nbins_minus_1)
            .template cast<int32>();

    out.setZero();
    for (int32_t i = 0; i < index_to_bin.size(); i++) {
      out(index_to_bin(i)) += Tout(1);
    }
    return Status::OK();
  }