mark_fill_rect(int w, int h, byte *gs_restrict dst_ptr, byte *gs_restrict src, int num_comp, int num_spots, int first_blend_spot,
               byte src_alpha, int rowstride, int planestride, bool additive, pdf14_device *pdev, gs_blend_mode_t blend_mode,
               bool overprint, gx_color_index drawn_comps, int tag_off, gs_graphics_type_tag_t curr_tag,
               int alpha_g_off, int shape_off, byte shape, bool isolated)
{
    template_mark_fill_rect(w, h, dst_ptr, src, num_comp, num_spots, first_blend_spot,
               src_alpha, rowstride, planestride, additive, pdev, blend_mode,
               overprint, drawn_comps, tag_off, curr_tag,
               alpha_g_off, shape_off, shape, isolated);
}