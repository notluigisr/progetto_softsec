mark_fill_rect16_add_nospots_common_no_alpha_g(int w, int h, uint16_t *gs_restrict dst_ptr, uint16_t *gs_restrict src, int num_comp, int num_spots, int first_blend_spot,
               uint16_t src_alpha, int rowstride, int planestride, bool additive, pdf14_device *pdev, gs_blend_mode_t blend_mode,
               bool overprint, gx_color_index drawn_comps, int tag_off, gs_graphics_type_tag_t curr_tag,
               int alpha_g_off, int shape_off, uint16_t shape)
{
    template_mark_fill_rect16(w, h, dst_ptr, src, num_comp, 0, 0,
               src_alpha, rowstride, planestride, 1, pdev, BLEND_MODE_Normal,
               0, 0, 0, curr_tag,
               0, 0, shape);
}