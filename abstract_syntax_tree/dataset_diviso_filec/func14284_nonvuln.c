std::string Magick::Image::directory(void) const
{
  if (constImage()->directory)
    return(std::string(constImage()->directory));

  if (!quiet())
    throwExceptionExplicit(MagickCore::CorruptImageWarning,
      "STR");

  return(std::string());
}