static inline bool vrend_format_can_scanout(enum virgl_formats format)
{
#ifdef ENABLE_GBM_ALLOCATION
   uint32_t gbm_format = 0;
   if (virgl_gbm_convert_format(&format, &gbm_format))
      return false;

   if (!gbm || !gbm->device || !gbm_format)
      return false;

   return gbm_device_is_format_supported(gbm->device, gbm_format, GBM_BO_USE_SCANOUT);
#else
   (void)format;
   return true;
#endif
}