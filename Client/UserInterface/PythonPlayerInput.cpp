//arat:
	PyCallClassMemberFunc(m_ppyGameWindow, "SetPCTargetBoard", Py_BuildValue("(is)", pkInstTarget->GetVirtualID(), pkInstTarget->GetNameString()));

//değiştir:
#ifdef ENABLE_VIEW_TARGET_HP_SP
	DWORD vid = pkInstTarget->GetVirtualID();
#else
	PyCallClassMemberFunc(m_ppyGameWindow, "SetPCTargetBoard", Py_BuildValue("(is)", pkInstTarget->GetVirtualID(), pkInstTarget->GetNameString()));
#endif