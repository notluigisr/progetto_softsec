scanner_cleanup (parser_context_t *context_p) 
{
  if (context_p->skipped_scanner_info_p != NULL)
  {
    context_p->skipped_scanner_info_end_p->next_p = context_p->next_scanner_info_p;
    context_p->next_scanner_info_p = context_p->skipped_scanner_info_p;
    context_p->skipped_scanner_info_p = NULL;
  }

  scanner_info_t *scanner_info_p = context_p->next_scanner_info_p;

  while (scanner_info_p != NULL)
  {
    scanner_info_t *next_scanner_info_p = scanner_info_p->next_p;

    size_t size = sizeof (scanner_info_t);

    switch (scanner_info_p->type)
    {
      case SCANNER_TYPE_END:
      {
        scanner_info_p = context_p->active_scanner_info_p;
        continue;
      }
      case SCANNER_TYPE_FUNCTION:
      case SCANNER_TYPE_BLOCK:
      {
        size = scanner_get_stream_size (scanner_info_p, sizeof (scanner_info_t));
        break;
      }
      case SCANNER_TYPE_WHILE:
      case SCANNER_TYPE_FOR_IN:
#if JERRY_ESNEXT
      case SCANNER_TYPE_FOR_OF:
#endif 
      case SCANNER_TYPE_CASE:
#if JERRY_ESNEXT
      case SCANNER_TYPE_INITIALIZER:
      case SCANNER_TYPE_CLASS_FIELD_INITIALIZER_END:
#endif 
      {
        size = sizeof (scanner_location_info_t);
        break;
      }
      case SCANNER_TYPE_FOR:
      {
        size = sizeof (scanner_for_info_t);
        break;
      }
      case SCANNER_TYPE_SWITCH:
      {
        scanner_release_switch_cases (((scanner_switch_info_t *) scanner_info_p)->case_p);
        size = sizeof (scanner_switch_info_t);
        break;
      }
      default:
      {
#if JERRY_ESNEXT
        JERRY_ASSERT (scanner_info_p->type == SCANNER_TYPE_END_ARGUMENTS
                      || scanner_info_p->type == SCANNER_TYPE_LITERAL_FLAGS
                      || scanner_info_p->type == SCANNER_TYPE_CLASS_CONSTRUCTOR
                      || scanner_info_p->type == SCANNER_TYPE_LET_EXPRESSION
                      || scanner_info_p->type == SCANNER_TYPE_ERR_REDECLARED
                      || scanner_info_p->type == SCANNER_TYPE_ERR_ASYNC_FUNCTION
                      || scanner_info_p->type == SCANNER_TYPE_EXPORT_MODULE_SPECIFIER);
#else 
        JERRY_ASSERT (scanner_info_p->type == SCANNER_TYPE_END_ARGUMENTS);
#endif 
        break;
      }
    }

    scanner_free (scanner_info_p, size);
    scanner_info_p = next_scanner_info_p;
  }

  context_p->next_scanner_info_p = NULL;
  context_p->active_scanner_info_p = NULL;
} 