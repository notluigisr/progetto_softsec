void vrend_fb_bind_texture(struct vrend_resource *res,
                           int idx,
                           uint32_t level, uint32_t layer)
{
   vrend_fb_bind_texture_id(res, res->id, idx, level, layer);
}