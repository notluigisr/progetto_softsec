void SRC_Finalise(void)
{
  LCL_RemoveParameterChangeHandler(slew_sources, NULL);
  LCL_RemoveDispersionNotifyHandler(add_dispersion, NULL);

  Free(sources);
  Free(sort_list);
  Free(sel_sources);

  initialised = 0;
}