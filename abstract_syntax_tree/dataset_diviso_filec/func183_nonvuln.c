static bool vrend_check_query_locked(struct vrend_query *query)
{
   struct virgl_host_query_state state;
   bool ret;

   state.result_size = vrend_is_timer_query(query->gltype) ? 8 : 4;
   ret = vrend_get_one_query_result(query->id, state.result_size == 8,
         &state.result);
   if (ret == false)
      return false;

   
   if (query->fake_samples_passed) {
      vrend_update_oq_samples_multiplier(vrend_state.current_ctx);
      state.result *=  vrend_state.current_ctx->sub->fake_occlusion_query_samples_passed_multiplier;
   }

   state.query_state = VIRGL_QUERY_STATE_DONE;

   if (query->res->iov) {
      vrend_write_to_iovec(query->res->iov, query->res->num_iovs, 0,
            (const void *) &state, sizeof(state));
   } else {
      *((struct virgl_host_query_state *) query->res->ptr) = state;
   }

   return true;
}