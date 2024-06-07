void vrend_launch_grid(struct vrend_context *ctx,
                       UNUSED uint32_t *block,
                       uint32_t *grid,
                       uint32_t indirect_handle,
                       uint32_t indirect_offset)
{
   bool new_program = false;
   struct vrend_resource *indirect_res = NULL;

   if (!has_feature(feat_compute_shader))
      return;

   if (ctx->sub->cs_shader_dirty) {
      struct vrend_linked_shader_program *prog;
      bool cs_dirty;

      ctx->sub->cs_shader_dirty = false;

      if (!ctx->sub->shaders[PIPE_SHADER_COMPUTE]) {
         vrend_printf("STR", ctx->debug_name);
         return;
      }

      vrend_shader_select(ctx, ctx->sub->shaders[PIPE_SHADER_COMPUTE], &cs_dirty);
      if (!ctx->sub->shaders[PIPE_SHADER_COMPUTE]->current) {
         vrend_printf( "STR", ctx->debug_name);
         return;
      }
      if (ctx->sub->shaders[PIPE_SHADER_COMPUTE]->current->id != (GLuint)ctx->sub->prog_ids[PIPE_SHADER_COMPUTE]) {
         prog = lookup_cs_shader_program(ctx, ctx->sub->shaders[PIPE_SHADER_COMPUTE]->current->id);
         if (!prog) {
            prog = add_cs_shader_program(ctx, ctx->sub->shaders[PIPE_SHADER_COMPUTE]->current);
            if (!prog)
               return;
         }
      } else
         prog = ctx->sub->prog;

      if (ctx->sub->prog != prog) {
         new_program = true;
         ctx->sub->prog_ids[PIPE_SHADER_VERTEX] = -1;
         ctx->sub->prog_ids[PIPE_SHADER_COMPUTE] = ctx->sub->shaders[PIPE_SHADER_COMPUTE]->current->id;
         ctx->sub->prog = prog;
         prog->ref_context = ctx->sub;
      }
      ctx->sub->shader_dirty = true;
   }
   vrend_use_program(ctx, ctx->sub->prog->id);

   vrend_draw_bind_ubo_shader(ctx, PIPE_SHADER_COMPUTE, 0);
   vrend_draw_bind_const_shader(ctx, PIPE_SHADER_COMPUTE, new_program);
   vrend_draw_bind_samplers_shader(ctx, PIPE_SHADER_COMPUTE, 0);
   vrend_draw_bind_images_shader(ctx, PIPE_SHADER_COMPUTE);
   vrend_draw_bind_ssbo_shader(ctx, PIPE_SHADER_COMPUTE);
   vrend_draw_bind_abo_shader(ctx);

   if (indirect_handle) {
      indirect_res = vrend_renderer_ctx_res_lookup(ctx, indirect_handle);
      if (!indirect_res) {
         report_context_error(ctx, VIRGL_ERROR_CTX_ILLEGAL_RESOURCE, indirect_handle);
         return;
      }
   }

   if (indirect_res)
      glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, indirect_res->id);
   else
      glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, 0);

   if (indirect_res) {
      glDispatchComputeIndirect(indirect_offset);
   } else {
      glDispatchCompute(grid[0], grid[1], grid[2]);
   }
}