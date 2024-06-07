static GLuint vrend_make_view(struct vrend_resource *res, enum virgl_formats format)
{
   GLuint view_id;

   GLenum tex_ifmt = tex_conv_table[res->base.format].internalformat;
   GLenum view_ifmt = tex_conv_table[format].internalformat;

   if (tex_ifmt == view_ifmt)
      return res->id;

   
   if (!has_bit(res->storage_bits, VREND_STORAGE_GL_IMMUTABLE))
      return res->id;

   VREND_DEBUG(dbg_blit, NULL, "STR",
               util_format_name(res->base.format),
               util_format_name(format));

   if (vrend_state.use_gles) {
      assert(res->target != GL_TEXTURE_RECTANGLE_NV);
      assert(res->target != GL_TEXTURE_1D);
      assert(res->target != GL_TEXTURE_1D_ARRAY);
   }

   glGenTextures(1, &view_id);
   glTextureView(view_id, res->target, res->id, view_ifmt, 0, res->base.last_level + 1,
                 0, res->base.array_size);
   return view_id;
}