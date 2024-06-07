process_acl(construction_context_t *ctx,
            const authz_acl_t *acl,
            node_t *root,
            const char *repository,
            const char *user,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  path_access_t path_access;
  int i;
  node_t *node;

  
  if (!svn_authz__get_acl_access(&path_access.rights, acl, user, repository))
    return;

  
  path_access.sequence_number = acl->sequence_number;

  
  node = root;
  for (i = 0; i < ctx->path->nelts; ++i)
    {
      const node_segment_pair_t *step
        = &APR_ARRAY_IDX(ctx->path, i, const node_segment_pair_t);

      
      if (   !step->node
          || i >= acl->rule.len
          || step->segment->kind != acl->rule.path[i].kind
          || step->segment->pattern.data != acl->rule.path[i].pattern.data)
        {
          ctx->path->nelts = i;
          break;
        }
      else
        {
          node = step->node;
        }
    }

  
  insert_path(ctx, node, &path_access,
              acl->rule.len - i, acl->rule.path + i,
              result_pool, scratch_pool);
}