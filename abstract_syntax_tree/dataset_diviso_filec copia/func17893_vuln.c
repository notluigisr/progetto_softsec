static int dtls1_process_buffered_records(SSL *s)
{
    pitem *item;
    SSL3_BUFFER *rb;

    item = pqueue_peek(s->d1->unprocessed_rcds.q);
    if (item) {
        
        if (s->d1->unprocessed_rcds.epoch != s->d1->r_epoch)
            return (1);         

        rb = &s->s3->rbuf;

        if (rb->left > 0) {
            
            return 1;
        }


        
        while (pqueue_peek(s->d1->unprocessed_rcds.q)) {
            dtls1_get_unprocessed_record(s);
            if (!dtls1_process_record(s))
                return (0);
            if (dtls1_buffer_record(s, &(s->d1->processed_rcds),
                                    s->s3->rrec.seq_num) < 0)
                return -1;
        }
    }

    
    s->d1->processed_rcds.epoch = s->d1->r_epoch;
    s->d1->unprocessed_rcds.epoch = s->d1->r_epoch + 1;

    return (1);
}