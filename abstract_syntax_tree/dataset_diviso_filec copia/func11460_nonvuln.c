_XimSaveIMValues(
    Xim			 im,
    XIMArg		*arg)
{
    register XIMArg	*p;
    register int	 n;
    XrmQuark		*quark_list;
    XrmQuark		*tmp;
    XrmQuark		 quark;
    int			 num_quark;

    if (quark_list = im->private.proto.saved_imvalues) {
	num_quark = im->private.proto.num_saved_imvalues;
	for (p = arg; p && p->name; p++) {
	    quark = XrmStringToQuark(p->name);
	    if (_XimCheckIMQuarkList(quark_list, num_quark, quark)) {
		continue;
	    }
	    if (!(tmp = Xrealloc(quark_list,
				(sizeof(XrmQuark) * (num_quark + 1))))) {
		im->private.proto.saved_imvalues = quark_list;
		im->private.proto.num_saved_imvalues = num_quark;
		return False;
	    }
	    num_quark++;
	    quark_list = tmp;
	    quark_list[num_quark] = quark;
	}
	im->private.proto.saved_imvalues = quark_list;
	im->private.proto.num_saved_imvalues = num_quark;
	return True;
    }

    for (p = arg, n = 0; p && p->name; p++, n++);

    if (!(quark_list = Xmalloc(sizeof(XrmQuark) * n))) {
	return False;
    }

    im->private.proto.saved_imvalues = quark_list;
    im->private.proto.num_saved_imvalues = n;
    for (p = arg; p && p->name; p++, quark_list++) {
	*quark_list = XrmStringToQuark(p->name);
    }

    return True;
}