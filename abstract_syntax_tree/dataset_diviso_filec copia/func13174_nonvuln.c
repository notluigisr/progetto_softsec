int readDataDim(struct READER *reader, struct DATAOBJECT *da,
                struct DATATYPE *dt, struct DATASPACE *ds, int dim) {
  int i, err;

  if (dim >= sizeof(ds->dimension_size) / sizeof(ds->dimension_size[0]))
    return MYSOFA_UNSUPPORTED_FORMAT; 

  for (i = 0; i < ds->dimension_size[dim]; i++) {
    if (dim + 1 < ds->dimensionality) {
      if (!!(err = readDataDim(reader, da, dt, ds, dim + 1))) {
        return err; 
      }
    } else {
      if (!!(err = readDataVar(reader, da, dt, ds))) {
        return err; 
      }
    }
  }
  return MYSOFA_OK;
}