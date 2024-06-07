  Status CalculateOutputIndex(OpKernelContext* context, int dimension,
                              const vector<INDEX_TYPE>& parent_output_index,
                              INDEX_TYPE output_index_multiplier,
                              INDEX_TYPE output_size,
                              vector<INDEX_TYPE>* result) {
    const RowPartitionTensor row_partition_tensor =
        GetRowPartitionTensor(context, dimension);
    auto partition_type = GetRowPartitionTypeByDimension(dimension);
    switch (partition_type) {
      case RowPartitionType::VALUE_ROWIDS:
        CalculateOutputIndexValueRowID(
            context, row_partition_tensor, parent_output_index,
            output_index_multiplier, output_size, result);
        return tensorflow::Status::OK();
      case RowPartitionType::ROW_SPLITS:
        if (row_partition_tensor.size() - 1 > parent_output_index.size()) {
          return errors::InvalidArgument(
              "STR",
              row_partition_tensor.size() - 1, "STR",
              parent_output_index.size());
        }
        CalculateOutputIndexRowSplit(
            context, row_partition_tensor, parent_output_index,
            output_index_multiplier, output_size, result);
        return tensorflow::Status::OK();
      default:
        return errors::InvalidArgument(
            "STR",
            RowPartitionTypeToString(partition_type));
    }
  }