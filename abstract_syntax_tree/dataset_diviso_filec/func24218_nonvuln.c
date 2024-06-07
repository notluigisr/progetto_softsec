pub_queue_ready_read(agooReady ready, void *ctx) {
    agooConLoop	loop = (agooConLoop)ctx;
    agooPub	pub;

    agoo_queue_release(&loop->pub_queue);
    while (NULL != (pub = (agooPub)agoo_queue_pop(&loop->pub_queue, 0.0))) {
	process_pub_con(pub, loop);
    }
    return true;
}