  void CalculateOutputIndexRowSplit(
      OpKernelContext* context, const RowPartitionTensor& row_split,
      const vector<INDEX_TYPE>& parent_output_index,
      INDEX_TYPE output_index_multiplier, INDEX_TYPE output_size,
      vector<INDEX_TYPE>* result) {
    INDEX_TYPE row_split_size = row_split.size();
    if (row_split_size > 0) {
      result->reserve(row_split(row_split_size - 1));
    }
    for (INDEX_TYPE i = 0; i < row_split_size - 1; ++i) {
      INDEX_TYPE row_length = row_split(i + 1) - row_split(i);
      INDEX_TYPE real_length = std::min(output_size, row_length);
      INDEX_TYPE parent_output_index_current = parent_output_index[i];

      if (parent_output_index_current == -1) {
        real_length = 0;
      }
      for (INDEX_TYPE j = 0; j < real_length; ++j) {
        result->push_back(parent_output_index_current);
        parent_output_index_current += output_index_multiplier;
      }
      for (INDEX_TYPE j = 0; j < row_length - real_length; ++j) {
        result->push_back(-1);
      }
    }
    if (row_split_size > 0) {
      OP_REQUIRES(context, result->size() == row_split(row_split_size - 1),
                  errors::InvalidArgument("STR"));
    }
  }