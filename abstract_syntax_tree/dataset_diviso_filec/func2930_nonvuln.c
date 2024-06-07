static int vrend_draw_bind_samplers_shader(struct vrend_context *ctx,
                                           int shader_type,
                                           int next_sampler_id)
{
   int index = 0;

   uint32_t dirty = ctx->sub->sampler_views_dirty[shader_type];

   uint32_t mask = ctx->sub->prog->samplers_used_mask[shader_type];
   while (mask) {
      int i = u_bit_scan(&mask);

      struct vrend_sampler_view *tview = ctx->sub->views[shader_type].views[i];
      if (dirty & (1 << i) && tview) {
         if (ctx->sub->prog->shadow_samp_mask[shader_type] & (1 << i)) {
            glUniform4f(ctx->sub->prog->shadow_samp_mask_locs[shader_type][index],
                        (tview->gl_swizzle_r == GL_ZERO || tview->gl_swizzle_r == GL_ONE) ? 0.0 : 1.0,
                        (tview->gl_swizzle_g == GL_ZERO || tview->gl_swizzle_g == GL_ONE) ? 0.0 : 1.0,
                        (tview->gl_swizzle_b == GL_ZERO || tview->gl_swizzle_b == GL_ONE) ? 0.0 : 1.0,
                        (tview->gl_swizzle_a == GL_ZERO || tview->gl_swizzle_a == GL_ONE) ? 0.0 : 1.0);
            glUniform4f(ctx->sub->prog->shadow_samp_add_locs[shader_type][index],
                        tview->gl_swizzle_r == GL_ONE ? 1.0 : 0.0,
                        tview->gl_swizzle_g == GL_ONE ? 1.0 : 0.0,
                        tview->gl_swizzle_b == GL_ONE ? 1.0 : 0.0,
                        tview->gl_swizzle_a == GL_ONE ? 1.0 : 0.0);
         }

         if (tview->texture) {
            GLuint id;
            struct vrend_resource *texture = tview->texture;
            GLenum target = tview->target;

            debug_texture(__func__, tview->texture);

            if (texture->storage == VREND_RESOURCE_STORAGE_BUFFER) {
               id = texture->tbo_tex_id;
               target = GL_TEXTURE_BUFFER;
            } else
               id = tview->id;

            glActiveTexture(GL_TEXTURE0 + next_sampler_id);
            glBindTexture(target, id);

            if (ctx->sub->views[shader_type].old_ids[i] != id ||
                ctx->sub->sampler_views_dirty[shader_type] & (1 << i)) {
               vrend_apply_sampler_state(ctx, texture, shader_type, i,
                                         next_sampler_id, tview);
               ctx->sub->views[shader_type].old_ids[i] = id;
            }
            dirty &= ~(1 << i);
         }
      }
      next_sampler_id++;
      index++;
   }
   ctx->sub->sampler_views_dirty[shader_type] = dirty;

   return next_sampler_id;
}