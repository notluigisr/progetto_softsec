static struct getout *new_getout(struct Configurable *config)
{
  struct getout *node =malloc(sizeof(struct getout));
  struct getout *last= config->url_last;
  if(node) {
    
    memset(node, 0, sizeof(struct getout));

    
    if(last)
      last->next = node;
    else
      config->url_list = node; 

    
    config->url_last = node;
  }
  return node;
}