static int delete_cb(void *rock, void *data)
{
    struct delete_rock *drock = (struct delete_rock *) rock;
    struct dav_data *ddata = (struct dav_data *) data;
    struct index_record record;
    int r;

    if (!ddata->imap_uid) {
        
        return 0;
    }

    
    r = mailbox_find_index_record(drock->mailbox, ddata->imap_uid, &record);
    if (r) {
        drock->txn->error.desc = error_message(r);
        return HTTP_SERVER_ERROR;
    }

    r = drock->deletep(drock->txn, drock->mailbox, &record, data);

    return r;
}