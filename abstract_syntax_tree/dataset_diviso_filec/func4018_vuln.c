  void CalculateOutputIndexValueRowID(
      const RowPartitionTensor& value_rowids,
      const vector<INDEX_TYPE>& parent_output_index,
      INDEX_TYPE output_index_multiplier, INDEX_TYPE output_size,
      vector<INDEX_TYPE>* result) {
    const INDEX_TYPE index_size = value_rowids.size();
    result->reserve(index_size);
    if (index_size == 0) {
      return;
    }

    INDEX_TYPE current_output_column = 0;
    INDEX_TYPE current_value_rowid = value_rowids(0);
    DCHECK_LT(current_value_rowid, parent_output_index.size());
    INDEX_TYPE current_output_index = parent_output_index[current_value_rowid];
    result->push_back(current_output_index);
    for (INDEX_TYPE i = 1; i < index_size; ++i) {
      INDEX_TYPE next_value_rowid = value_rowids(i);
      if (next_value_rowid == current_value_rowid) {
        if (current_output_index >= 0) {
          ++current_output_column;
          if (current_output_column < output_size) {
            current_output_index += output_index_multiplier;
          } else {
            current_output_index = -1;
          }
        }
      } else {
        current_output_column = 0;
        current_value_rowid = next_value_rowid;
        DCHECK_LT(next_value_rowid, parent_output_index.size());
        current_output_index = parent_output_index[next_value_rowid];
      }
      result->push_back(current_output_index);
    }
    DCHECK_EQ(result->size(), value_rowids.size());
  }