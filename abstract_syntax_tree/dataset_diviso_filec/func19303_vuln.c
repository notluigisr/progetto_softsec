TfLiteStatus Subgraph::AllocateTensors() {
  TFLITE_SCOPED_TAGGED_DEFAULT_PROFILE(profiler_.get(), "STR");
  if (!consistent_) {
    ReportError("STR");
    return kTfLiteError;
  }

  
  TF_LITE_ENSURE_STATUS(RedoAllDelegates());

  
  
  
  if (state_ != kStateUninvokable &&
      !HasDynamicTensorImpl(context_, inputs())) {
    if (memory_planner_ && !memory_planner_->HasNonPersistentMemory()) {
      
      
      
      
      memory_planner_->AcquireNonPersistentMemory();
    }
    return kTfLiteOk;
  }

  next_execution_plan_index_to_prepare_ = 0;
  next_execution_plan_index_to_plan_allocation_ = 0;
  next_original_execution_plan_index_to_prepare_ = 0;
  if (memory_planner_) {
    TF_LITE_ENSURE_STATUS(memory_planner_->ResetAllocations());
  }

  TF_LITE_ENSURE_STATUS(PrepareOpsAndTensors());

  state_ = kStateInvokable;

  
  
  
  
  ResetVariableTensors();

  return kTfLiteOk;
}