  Status FillCollectiveParams(CollectiveParams* col_params,
                              CollectiveType collective_type,
                              const Tensor& group_size, const Tensor& group_key,
                              const Tensor& instance_key) {
    if (group_size.dims() > 0) {
      return errors::Internal("STR",
                              group_size.shape().DebugString());
    }
    if (group_key.dims() > 0) {
      return errors::Internal("STR",
                              group_key.shape().DebugString());
    }
    if (instance_key.dims() > 0) {
      return errors::Internal(
          "STR",
          instance_key.shape().DebugString());
    }
    col_params->name = name_;
    col_params->group.device_type = device_type_;
    col_params->group.group_size = group_size.unaligned_flat<int32>()(0);
    if (col_params->group.group_size <= 0) {
      return errors::InvalidArgument(
          "STR",
          col_params->group.group_size);
    }
    col_params->group.group_key = group_key.unaligned_flat<int32>()(0);
    col_params->instance.type = collective_type;
    col_params->instance.instance_key = instance_key.unaligned_flat<int32>()(0);
    col_params->instance.data_type = data_type_;
    col_params->instance.impl_details.communication_hint = communication_hint_;
    col_params->instance.impl_details.timeout_seconds = timeout_seconds_;
    return Status::OK();
  }