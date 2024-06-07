static int ehci_execute(EHCIPacket *p, const char *action)
{
    USBEndpoint *ep;
    int endp;
    bool spd;

    assert(p->async == EHCI_ASYNC_NONE ||
           p->async == EHCI_ASYNC_INITIALIZED);

    if (!(p->qtd.token & QTD_TOKEN_ACTIVE)) {
        fprintf(stderr, "STR");
        return -1;
    }

    if (get_field(p->qtd.token, QTD_TOKEN_TBYTES) > BUFF_SIZE) {
        ehci_trace_guest_bug(p->queue->ehci,
                             "STR");
        return -1;
    }

    if (!ehci_verify_pid(p->queue, &p->qtd)) {
        ehci_queue_stopped(p->queue); 
    }
    p->pid = ehci_get_pid(&p->qtd);
    p->queue->last_pid = p->pid;
    endp = get_field(p->queue->qh.epchar, QH_EPCHAR_EP);
    ep = usb_ep_get(p->queue->dev, p->pid, endp);

    if (p->async == EHCI_ASYNC_NONE) {
        if (ehci_init_transfer(p) != 0) {
            return -1;
        }

        spd = (p->pid == USB_TOKEN_IN && NLPTR_TBIT(p->qtd.altnext) == 0);
        usb_packet_setup(&p->packet, p->pid, ep, 0, p->qtdaddr, spd,
                         (p->qtd.token & QTD_TOKEN_IOC) != 0);
        usb_packet_map(&p->packet, &p->sgl);
        p->async = EHCI_ASYNC_INITIALIZED;
    }

    trace_usb_ehci_packet_action(p->queue, p, action);
    usb_handle_packet(p->queue->dev, &p->packet);
    DPRINTF("STR"
            "STR", p->queue->qhaddr, p->qtd.next,
            p->qtdaddr, p->pid, p->packet.iov.size, endp, p->packet.status,
            p->packet.actual_length);

    if (p->packet.actual_length > BUFF_SIZE) {
        fprintf(stderr, "STR");
        return -1;
    }

    return 1;
}