void CairoOutputDev::drawImageMask(GfxState *state, Object *ref, Stream *str,
				   int width, int height, GBool invert,
				   GBool interpolate, GBool inlineImg) {

  
  cairo_set_source (cairo, fill_pattern);

  
  if (width == 1 && height == 1) {
    ImageStream *imgStr;
    Guchar pix;
    int invert_bit;

    imgStr = new ImageStream(str, width, 1, 1);
    imgStr->reset();
    imgStr->getPixel(&pix);
    imgStr->close();
    delete imgStr;

    invert_bit = invert ? 1 : 0;
    if (pix ^ invert_bit)
      return;

    cairo_save (cairo);
    cairo_rectangle (cairo, 0., 0., width, height);
    cairo_fill (cairo);
    cairo_restore (cairo);
    if (cairo_shape) {
      cairo_save (cairo_shape);
      cairo_rectangle (cairo_shape, 0., 0., width, height);
      cairo_fill (cairo_shape);
      cairo_restore (cairo_shape);
    }
    return;
  }

  if (state->getFillColorSpace()->getMode() == csPattern)
    cairo_push_group_with_content (cairo, CAIRO_CONTENT_ALPHA);

  

  cairo_matrix_t matrix;
  cairo_get_matrix (cairo, &matrix);
  
  
  if (!printing && prescaleImages && matrix.xy == 0.0 && matrix.yx == 0.0) {
    drawImageMaskPrescaled(state, ref, str, width, height, invert, interpolate, inlineImg);
  } else {
    drawImageMaskRegular(state, ref, str, width, height, invert, interpolate, inlineImg);
  }

  if (state->getFillColorSpace()->getMode() == csPattern) {
    if (mask)
      cairo_pattern_destroy (mask);
    mask = cairo_pop_group (cairo);
  }
}