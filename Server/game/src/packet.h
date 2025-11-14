//arat - değiştir

typedef struct packet_target
{
	BYTE	header;
	DWORD	dwVID;
	BYTE	bHPPercent;
#ifdef ENABLE_VIEW_TARGET_HP_SP
	BYTE	bSPPercent;
	int		iMinHP;
	int		iMaxHP;
	int		iMinSP;
	int		iMaxSP;
#endif
} TPacketGCTarget;
