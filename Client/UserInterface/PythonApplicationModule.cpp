//ekle:

#ifdef ENABLE_VIEW_TARGET_HP_SP
	PyModule_AddIntConstant(poModule, "ENABLE_VIEW_TARGET_HP_SP", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_VIEW_TARGET_HP_SP", 0);
#endif