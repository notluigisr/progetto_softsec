  explicit SparseCrossOp(OpKernelConstruction* context) : OpKernel(context) {
    OP_REQUIRES_OK(context, context->GetAttr("STR", &num_buckets_));
    
    
    int64 signed_hash_key_;
    OP_REQUIRES_OK(context, context->GetAttr("STR", &signed_hash_key_));
    hash_key_ = static_cast<uint64>(signed_hash_key_);
  }