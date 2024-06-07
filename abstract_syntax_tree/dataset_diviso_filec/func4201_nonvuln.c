int vrend_renderer_transfer_pipe(struct pipe_resource *pres,
                                 const struct vrend_transfer_info *info,
                                 int transfer_mode)
{
   struct vrend_resource *res = (struct vrend_resource *)pres;
   if (!check_transfer_iovec(res, info))
      return EINVAL;

   return vrend_renderer_transfer_internal(vrend_state.ctx0, res, info,
                                           transfer_mode);
}