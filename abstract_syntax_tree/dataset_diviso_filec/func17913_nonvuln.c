TensorShape PoolParameters::forward_output_shape() {
  if (depth_window == 1) {
    
    return ShapeFromFormat(data_format, tensor_in_batch, out_height, out_width,
                           depth);
  } else {
    
    return TensorShape(
        {tensor_in_batch, tensor_in_rows, tensor_in_cols, out_depth});
  }
}