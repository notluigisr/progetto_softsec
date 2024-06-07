pdf14_mark_fill_rectangle(gx_device * dev, int x, int y, int w, int h,
                          gx_color_index color, const gx_device_color *pdc,
                          bool devn)
{
    pdf14_device *pdev = (pdf14_device *)dev;
    pdf14_buf *buf = pdev->ctx->stack;

    if (buf->deep)
        return do_mark_fill_rectangle16(dev, x, y, w, h, color, pdc, devn);
    else
        return do_mark_fill_rectangle(dev, x, y, w, h, color, pdc, devn);
}