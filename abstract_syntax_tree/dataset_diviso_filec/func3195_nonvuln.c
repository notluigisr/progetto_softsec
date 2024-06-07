  void Fill(OpKernelContext* context, random::PhiloxRandom random,
            Tensor* output) override {
    typedef typename Distribution::ResultElementType T;
    auto flat = output->flat<T>();
    
    functor::FillPhiloxRandom<Device, Distribution>()(
        context, context->eigen_device<Device>(), nullptr,
        nullptr, random, flat.data(), flat.size(), Distribution());
  }