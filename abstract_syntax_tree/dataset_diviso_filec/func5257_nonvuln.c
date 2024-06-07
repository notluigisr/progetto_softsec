  explicit CollectiveReduceOpKernel(OpKernelConstruction* c)
      : CollectiveOpV1Kernel(c) {
    col_params_->instance.type = REDUCTION_COLLECTIVE;
    OP_REQUIRES_OK(c, c->GetAttr("STR", &col_params_->group.group_size));
    OP_REQUIRES(
        c, col_params_->group.group_size > 0,
        errors::InvalidArgument("STR",
                                col_params_->group.group_size));
    OP_REQUIRES_OK(c, c->GetAttr("STR", &col_params_->group.group_key));
    OP_REQUIRES_OK(
        c, c->GetAttr("STR", &col_params_->instance.instance_key));
    OP_REQUIRES_OK(
        c, c->GetAttr("STR",
                      &col_params_->instance.impl_details.subdiv_offsets));
    string merge_op_name;
    OP_REQUIRES_OK(c, c->GetAttr("STR", &merge_op_name));
    if (merge_op_name == "STR") {
      merge_op_name = "STR";
    } else if (merge_op_name == "STR") {
      merge_op_name = "STR";
    }
    string final_op_name;
    OP_REQUIRES_OK(c, c->GetAttr("STR", &final_op_name));
    OP_REQUIRES(c, final_op_name == "STR",
                errors::InvalidArgument(
                    "STR",
                    final_op_name));
    OP_REQUIRES_OK(c, c->GetAttr("STR", &col_params_->instance.data_type));
    OP_REQUIRES_OK(c, c->GetAttr("STR", &dependencies_));
    OP_REQUIRES_OK(
        c, c->GetAttr("STR",
                      &col_params_->instance.impl_details.communication_hint));
    OP_REQUIRES_OK(
        c, c->GetAttr("STR",
                      &col_params_->instance.impl_details.timeout_seconds));
    VLOG(2) << "STR"
            << col_params_->instance.instance_key << "STR"
            << merge_op_name << "STR" << final_op_name
            << "STR"
            << col_params_->instance.impl_details.communication_hint
            << "STR"
            << col_params_->instance.impl_details.timeout_seconds;

    const NodeDef& real_node = c->def();
    col_params_->name = strings::StrCat(real_node.name(), "STR",
                                        merge_op_name, "STR");
    col_params_->group.device_type = c->device_type();

    
    NodeDef sub_node;
    
    sub_node.add_input(real_node.input(0));
    sub_node.add_input(real_node.input(0));
    sub_node.set_device(real_node.device());
    SetAttrValue(col_params_->instance.data_type,
                 &(*sub_node.mutable_attr())["STR"]);
    merge_op_ = BuildOpKernel(c, merge_op_name, &sub_node);
    final_op_ = BuildOpKernel(c, final_op_name, &sub_node);
    col_params_->merge_op = merge_op_.get();
    col_params_->final_op = final_op_.get();
  }