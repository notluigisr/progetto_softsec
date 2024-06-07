KEY_Finalise(void)
{
  free_keys();
  ARR_DestroyInstance(keys);
}