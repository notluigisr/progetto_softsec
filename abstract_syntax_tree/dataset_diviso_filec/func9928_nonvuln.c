rsvg_pixbuf_to_cairo (guint8 * pixels, int rowstride, int height)
{
    int row;
    
    for (row = 0; row < height; row++) {
        guint8 *row_data = (pixels + (row * rowstride));
        int i;

        for (i = 0; i < rowstride; i += 4) {
            guint32 *b = (guint32 *) & row_data[i];
            guint8 pixel[4];
            int alpha;

            memcpy (&pixel, b, sizeof (guint32));
            alpha = pixel[3];
            if (alpha == 0)
                *b = 0;
            else
                *b = alpha << 24 |
                    (int) pixel[0] * alpha / 255 << 16 |
                    (int) pixel[1] * alpha / 255 << 8 | (int) pixel[2] * alpha / 255;
        }
    }
}