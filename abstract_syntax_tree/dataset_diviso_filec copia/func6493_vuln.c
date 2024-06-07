initpyfribidi (void)
{
	PyObject *module;

	

	module = Py_InitModule3 ("STR", PyfribidiMethods,
				 _pyfribidi__doc__);

	PyModule_AddIntConstant (module, "STR", (long) FRIBIDI_TYPE_RTL);
	PyModule_AddIntConstant (module, "STR", (long) FRIBIDI_TYPE_LTR);
	PyModule_AddIntConstant (module, "STR", (long) FRIBIDI_TYPE_ON);

	PyModule_AddStringConstant (module, "STR",
				    "STR");
}