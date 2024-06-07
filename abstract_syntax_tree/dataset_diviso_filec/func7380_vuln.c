static irqreturn_t sunkbd_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct sunkbd *sunkbd = serio_get_drvdata(serio);

	if (sunkbd->reset <= -1) {
		
		sunkbd->reset = data;
		wake_up_interruptible(&sunkbd->wait);
		goto out;
	}

	if (sunkbd->layout == -1) {
		sunkbd->layout = data;
		wake_up_interruptible(&sunkbd->wait);
		goto out;
	}

	switch (data) {

	case SUNKBD_RET_RESET:
		schedule_work(&sunkbd->tq);
		sunkbd->reset = -1;
		break;

	case SUNKBD_RET_LAYOUT:
		sunkbd->layout = -1;
		break;

	case SUNKBD_RET_ALLUP: 
		break;

	default:
		if (!sunkbd->enabled)
			break;

		if (sunkbd->keycode[data & SUNKBD_KEY]) {
			input_report_key(sunkbd->dev,
					 sunkbd->keycode[data & SUNKBD_KEY],
					 !(data & SUNKBD_RELEASE));
			input_sync(sunkbd->dev);
		} else {
			printk(KERN_WARNING
				"STR",
				data & SUNKBD_KEY,
				data & SUNKBD_RELEASE ? "STR");
		}
	}
out:
	return IRQ_HANDLED;
}