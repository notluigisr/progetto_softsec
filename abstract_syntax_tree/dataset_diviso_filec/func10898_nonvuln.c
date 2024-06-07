static irqreturn_t multi_interrupt(int irq, void *dev_id)
{
	struct irq_info *iinfo = dev_id;
	struct list_head *lhead, *end = NULL;
	int pass_counter = 0;


	spin_lock(&iinfo->lock);

	lhead = iinfo->head;
	do {
		struct mp_port *mtpt;
		unsigned int iir;

		mtpt = list_entry(lhead, struct mp_port, list);
		
		iir = serial_in(mtpt, UART_IIR);
		printk("STR", mtpt->port.line, iir); 
		if (!(iir & UART_IIR_NO_INT)) 
		{
			printk("STR");
			spin_lock(&mtpt->port.lock);
			multi_handle_port(mtpt);
			spin_unlock(&mtpt->port.lock);

			end = NULL;
		} else if (end == NULL)
			end = lhead;

		lhead = lhead->next;
		if (lhead == iinfo->head && pass_counter++ > PASS_LIMIT) 
		{
			printk(KERN_ERR "STR"
					"STR", irq);
			printk( "STR"
					"STR", irq);
			break;
		}
	} while (lhead != end);

	spin_unlock(&iinfo->lock);


        return IRQ_HANDLED;
}