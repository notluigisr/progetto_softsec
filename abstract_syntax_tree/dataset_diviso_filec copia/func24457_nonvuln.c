inline void ShapeFromDims(const tflite::Dims<4>& dims, RuntimeShape* shape) {
  shape->BuildFrom(
      {dims.sizes[3], dims.sizes[2], dims.sizes[1], dims.sizes[0]});
}