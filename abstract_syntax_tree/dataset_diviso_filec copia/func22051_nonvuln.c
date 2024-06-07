static void vrend_draw_bind_images_shader(struct vrend_sub_context *sub_ctx, int shader_type)
{
   GLenum access;
   GLboolean layered;
   struct vrend_image_view *iview;
   uint32_t mask, tex_id, level, first_layer;


   if (!sub_ctx->images_used_mask[shader_type])
      return;

   if (!sub_ctx->prog->img_locs[shader_type])
      return;

   if (!has_feature(feat_images))
      return;

   mask = sub_ctx->images_used_mask[shader_type];
   while (mask) {
      unsigned i = u_bit_scan(&mask);

      if (!(sub_ctx->prog->images_used_mask[shader_type] & (1 << i)))
          continue;
      iview = &sub_ctx->image_views[shader_type][i];
      tex_id = iview->texture->id;
      if (has_bit(iview->texture->storage_bits, VREND_STORAGE_GL_BUFFER)) {
         if (!iview->texture->tbo_tex_id)
            glGenTextures(1, &iview->texture->tbo_tex_id);

         
         uint32_t format = (iview->format == GL_RGBA8_SNORM) ? GL_RGBA8UI : iview->format;

         glBindBufferARB(GL_TEXTURE_BUFFER, iview->texture->id);
         glBindTexture(GL_TEXTURE_BUFFER, iview->texture->tbo_tex_id);

         if (has_feature(feat_arb_or_gles_ext_texture_buffer))
            glTexBuffer(GL_TEXTURE_BUFFER, format, iview->texture->id);

         tex_id = iview->texture->tbo_tex_id;
         level = first_layer = 0;
         layered = GL_TRUE;
      } else {
         level = iview->u.tex.level;
         first_layer = iview->u.tex.first_layer;
         layered = !((iview->texture->base.array_size > 1 ||
                      iview->texture->base.depth0 > 1) && (iview->u.tex.first_layer == iview->u.tex.last_layer));
      }

      if (!vrend_state.use_gles)
         glUniform1i(sub_ctx->prog->img_locs[shader_type][i], i);

      switch (iview->access) {
      case PIPE_IMAGE_ACCESS_READ:
         access = GL_READ_ONLY;
         break;
      case PIPE_IMAGE_ACCESS_WRITE:
         access = GL_WRITE_ONLY;
         break;
      case PIPE_IMAGE_ACCESS_READ_WRITE:
         access = GL_READ_WRITE;
         break;
      default:
         vrend_printf( "STR");
         return;
      }

      glBindImageTexture(i, tex_id, level, layered, first_layer, access, iview->format);
   }
}