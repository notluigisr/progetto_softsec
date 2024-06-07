  bool has_default_now_unireg_check() const
  {
    return unireg_check == TIMESTAMP_DN_FIELD
        || unireg_check == TIMESTAMP_DNUN_FIELD;
  }