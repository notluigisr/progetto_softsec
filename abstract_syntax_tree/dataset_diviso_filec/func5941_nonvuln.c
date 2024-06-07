uint32_t ssh_buffer_get_data(struct ssh_buffer_struct *buffer, void *data, uint32_t len)
{
    int rc;

    
    rc = ssh_buffer_validate_length(buffer, len);
    if (rc != SSH_OK) {
        return 0;
    }
    memcpy(data,buffer->data+buffer->pos,len);
    buffer->pos+=len;
    return len;   
}