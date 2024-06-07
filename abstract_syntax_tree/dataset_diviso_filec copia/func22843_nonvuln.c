static bool rbd_image_format_valid(u32 image_format)
{
	return image_format == 1 || image_format == 2;
}