PHP_FUNCTION(imagejpeg)
{
#ifdef USE_GD_IOCTX
	_php_image_output_ctx(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GDIMG_TYPE_JPG, "STR", gdImageJpegCtx);
#else
	_php_image_output(INTERNAL_FUNCTION_PARAM_PASSTHRU, PHP_GDIMG_TYPE_JPG, "STR", gdImageJpeg);
#endif
}