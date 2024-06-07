  epoch_t get_up_epoch() const {
    epoch_t ret;
    retrieve_epochs(NULL, &ret, NULL);
    return ret;
  }