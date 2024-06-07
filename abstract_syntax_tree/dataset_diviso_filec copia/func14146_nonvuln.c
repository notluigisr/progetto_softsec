Status CheckPaddingSize(int64_t window_rows, int64_t window_cols,
                        int64_t pad_top, int64_t pad_bottom, int64_t pad_left,
                        int64_t pad_right) {
  if (!FastBoundsCheck(pad_top, window_rows)) {
    return errors::InvalidArgument("STR", pad_top,
                                   "STR"
                                   "STR",
                                   window_rows);
  }
  if (!FastBoundsCheck(pad_bottom, window_rows)) {
    return errors::InvalidArgument("STR", pad_bottom,
                                   "STR"
                                   "STR",
                                   window_rows);
  }
  if (!FastBoundsCheck(pad_left, window_cols)) {
    return errors::InvalidArgument("STR", pad_left,
                                   "STR"
                                   "STR",
                                   window_cols);
  }
  if (!FastBoundsCheck(pad_right, window_cols)) {
    return errors::InvalidArgument("STR", pad_right,
                                   "STR"
                                   "STR",
                                   window_cols);
  }
  return Status::OK();
}