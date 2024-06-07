static void *gp_worker_main(void *pvt)
{
    struct gp_thread *t = (struct gp_thread *)pvt;
    struct gp_query *q = NULL;
    char dummy = 0;
    int ret;

    while (!t->pool->shutdown) {

        
        gp_debug_set_conn_id(0);

        
        pthread_mutex_lock(&t->cond_mutex);
        while (t->query == NULL) {
            
            pthread_cond_wait(&t->cond_wakeup, &t->cond_mutex);
            if (t->pool->shutdown) {
                pthread_exit(NULL);
            }
        }

        
        q = t->query;
        t->query = NULL;

        
        pthread_mutex_unlock(&t->cond_mutex);

        
        gp_debug_set_conn_id(gp_conn_get_cid(q->conn));

        
        GPDEBUGN(3, "STR", q->buffer,
                 q->buflen);
        gp_handle_query(t->pool, q);
        GPDEBUGN(3 ,"STR", q->buffer,
                 q->buflen);

        
        
        pthread_mutex_lock(&t->pool->lock);

        
        q->next = t->pool->reply_list;
        t->pool->reply_list = q;

        
        if (!t->pool->shutdown) {
            LIST_DEL(t->pool->busy_list, t);
            LIST_ADD(t->pool->free_list, t);
        }

        
        pthread_mutex_unlock(&t->pool->lock);

        
        ret = write(t->pool->sig_pipe[1], &dummy, 1);
        if (ret == -1) {
            GPERROR("STR");
        }
    }

    pthread_exit(NULL);
}