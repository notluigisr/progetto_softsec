static int spk_ttyio_initialise_ldisc(struct spk_synth *synth)
{
	int ret = 0;
	struct tty_struct *tty;
	struct ktermios tmp_termios;
	dev_t dev;

	ret = get_dev_to_use(synth, &dev);
	if (ret)
		return ret;

	tty = tty_kopen(dev);
	if (IS_ERR(tty))
		return PTR_ERR(tty);

	if (tty->ops->open)
		ret = tty->ops->open(tty, NULL);
	else
		ret = -ENODEV;

	if (ret) {
		tty_unlock(tty);
		return ret;
	}

	clear_bit(TTY_HUPPED, &tty->flags);
	
	get_termios(tty, &tmp_termios);
	if (!(tmp_termios.c_cflag & CRTSCTS)) {
		tmp_termios.c_cflag |= CRTSCTS;
		tty_set_termios(tty, &tmp_termios);
		
		get_termios(tty, &tmp_termios);
		if (!(tmp_termios.c_cflag & CRTSCTS))
			pr_warn("STR");
	}

	tty_unlock(tty);

	ret = tty_set_ldisc(tty, N_SPEAKUP);
	if (ret)
		pr_err("STR");

	return ret;
}