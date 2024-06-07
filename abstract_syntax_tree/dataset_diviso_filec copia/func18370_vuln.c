void usb_ep_combine_input_packets(USBEndpoint *ep)
{
    USBPacket *p, *u, *next, *prev = NULL, *first = NULL;
    USBPort *port = ep->dev->port;
    int totalsize;

    assert(ep->pipeline);
    assert(ep->pid == USB_TOKEN_IN);

    QTAILQ_FOREACH_SAFE(p, &ep->queue, queue, next) {
        
        if (ep->halted) {
            p->status = USB_RET_REMOVE_FROM_QUEUE;
            port->ops->complete(port, p);
            continue;
        }

        
        if (p->state == USB_PACKET_ASYNC) {
            prev = p;
            continue;
        }
        usb_packet_check_state(p, USB_PACKET_QUEUED);

        
        if (prev && prev->short_not_ok) {
            break;
        }

        if (first) {
            if (first->combined == NULL) {
                USBCombinedPacket *combined = g_new0(USBCombinedPacket, 1);

                combined->first = first;
                QTAILQ_INIT(&combined->packets);
                qemu_iovec_init(&combined->iov, 2);
                usb_combined_packet_add(combined, first);
            }
            usb_combined_packet_add(first->combined, p);
        } else {
            first = p;
        }

        
        totalsize = (p->combined) ? p->combined->iov.size : p->iov.size;
        if ((p->iov.size % ep->max_packet_size) != 0 || !p->short_not_ok ||
                next == NULL ||
                
                (totalsize == (16 * KiB - 36) && p->int_req)) {
            usb_device_handle_data(ep->dev, first);
            assert(first->status == USB_RET_ASYNC);
            if (first->combined) {
                QTAILQ_FOREACH(u, &first->combined->packets, combined_entry) {
                    usb_packet_set_state(u, USB_PACKET_ASYNC);
                }
            } else {
                usb_packet_set_state(first, USB_PACKET_ASYNC);
            }
            first = NULL;
            prev = p;
        }
    }
}