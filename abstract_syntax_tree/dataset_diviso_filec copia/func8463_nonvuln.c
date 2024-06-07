void GetBeginAndSizeVectors(int dimensions, const TfLiteTensor* begin,
                            const TfLiteTensor* size, std::vector<int>* begins,
                            std::vector<int>* sizes) {
  for (int idx = 0; idx < dimensions; ++idx) {
    begins->push_back(GetTensorData<T>(begin)[idx]);
    sizes->push_back(GetTensorData<T>(size)[idx]);
  }
}