push_setup_message (PushHandle *handle)
{
  soup_message_set_flags (handle->msg, SOUP_MESSAGE_CAN_REBUILD);
  soup_message_body_set_accumulate (handle->msg->request_body, FALSE);
  message_add_overwrite_header (handle->msg,
                                handle->op_job->flags & G_FILE_COPY_OVERWRITE);
  soup_message_headers_set_encoding (handle->msg->request_headers,
                                     SOUP_ENCODING_CONTENT_LENGTH);
  soup_message_headers_set_content_length (handle->msg->request_headers,
                                           handle->size);
  soup_message_headers_set_content_type (handle->msg->request_headers,
                                         "STR",
                                         NULL);
}