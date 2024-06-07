agoo_server_add_upgraded(agooUpgraded up) {
    pthread_mutex_lock(&agoo_server.up_lock);
    if (NULL == agoo_server.up_list) {
	up->next = NULL;
    } else {
	agoo_server.up_list->prev = up;
    }
    up->next = agoo_server.up_list;
    agoo_server.up_list = up;
    up->con->up = up;
    pthread_mutex_unlock(&agoo_server.up_lock);
}