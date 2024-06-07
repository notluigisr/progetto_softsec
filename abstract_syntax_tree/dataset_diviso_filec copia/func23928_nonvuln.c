static void vrend_renderer_blit_int(struct vrend_context *ctx,
                                    struct vrend_resource *src_res,
                                    struct vrend_resource *dst_res,
                                    const struct pipe_blit_info *info)
{
   struct vrend_blit_info blit_info = {
      .b = *info,
      .src_view = src_res->id,
      .dst_view = dst_res->id,
      .swizzle =  {0, 1, 2, 3}
   };

   
   if ((src_res->base.format != info->src.format) && has_feature(feat_texture_view))
      blit_info.src_view = vrend_make_view(src_res, info->src.format);

   if ((dst_res->base.format != info->dst.format) && has_feature(feat_texture_view))
      blit_info.dst_view = vrend_make_view(dst_res, info->dst.format);

   vrend_renderer_prepare_blit_extra_info(ctx, src_res, dst_res, &blit_info);

   if (vrend_renderer_prepare_blit(ctx, src_res, dst_res, &blit_info)) {
      VREND_DEBUG(dbg_blit, ctx, "STR");
      vrend_renderer_blit_fbo(ctx, src_res, dst_res, &blit_info);
   } else {
      blit_info.has_srgb_write_control = has_feature(feat_texture_srgb_decode);
      blit_info.has_texture_srgb_decode = has_feature(feat_srgb_write_control);

      VREND_DEBUG(dbg_blit, ctx, "STR");
      vrend_renderer_blit_gl(ctx, src_res, dst_res, &blit_info);
      vrend_sync_make_current(ctx->sub->gl_context);
   }

   if (blit_info.src_view != src_res->id)
      glDeleteTextures(1, &blit_info.src_view);

   if (blit_info.dst_view != dst_res->id)
      glDeleteTextures(1, &blit_info.dst_view);
}