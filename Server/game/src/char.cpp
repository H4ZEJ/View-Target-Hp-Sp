//arat - deðiþtir

void CHARACTER::ClearTarget()
{
	if (m_pkChrTarget)
	{
		m_pkChrTarget->m_set_pkChrTargetedBy.erase(this);
		m_pkChrTarget = NULL;
	}

	TPacketGCTarget p;

	p.header = HEADER_GC_TARGET;
	p.dwVID = 0;
	p.bHPPercent = 0;
#ifdef ENABLE_VIEW_TARGET_HP_SP
	p.bSPPercent = 0;
	p.iMinHP = 0;
	p.iMaxHP = 0;
	p.iMinSP = 0;
	p.iMaxSP = 0;
#endif

	CHARACTER_SET::iterator it = m_set_pkChrTargetedBy.begin();

	while (it != m_set_pkChrTargetedBy.end())
	{
		LPCHARACTER pkChr = *(it++);
		pkChr->m_pkChrTarget = NULL;

		if (!pkChr->GetDesc())
		{
			sys_err("%s %p does not have desc", pkChr->GetName(), get_pointer(pkChr));
			abort();
		}

		pkChr->GetDesc()->Packet(p);
	}

	m_set_pkChrTargetedBy.clear();
}

//arat - deðiþtir

void CHARACTER::SetTarget(LPCHARACTER pkChrTarget)
{
	if (m_pkChrTarget == pkChrTarget)
		return;

	if (m_pkChrTarget)
		m_pkChrTarget->m_set_pkChrTargetedBy.erase(this);

	m_pkChrTarget = pkChrTarget;

	TPacketGCTarget p;

	p.header = HEADER_GC_TARGET;

	if (m_pkChrTarget)
	{
		m_pkChrTarget->m_set_pkChrTargetedBy.emplace(this);

		p.dwVID	= m_pkChrTarget->GetVID();

#ifdef ENABLE_VIEW_TARGET_HP_SP
		if ((m_pkChrTarget->GetMaxHP() <= 0))
		{
			p.bHPPercent = 0;
			p.iMinHP = 0;
			p.iMaxHP = 0;
		}
		else if (m_pkChrTarget->IsPC() && !m_pkChrTarget->IsPolymorphed())
		{
			p.bHPPercent = MINMAX(0, (m_pkChrTarget->GetHP() * 100) / m_pkChrTarget->GetMaxHP(), 100);
			p.iMinHP = m_pkChrTarget->GetHP();
			p.iMaxHP = m_pkChrTarget->GetMaxHP();
		}
#else
		if ((m_pkChrTarget->IsPC() && !m_pkChrTarget->IsPolymorphed()) || (m_pkChrTarget->GetMaxHP() <= 0))
		{
			p.bHPPercent = 0;
		}
#endif
		else
		{
			if (m_pkChrTarget->GetRaceNum() == 20101 ||
				m_pkChrTarget->GetRaceNum() == 20102 ||
				m_pkChrTarget->GetRaceNum() == 20103 ||
				m_pkChrTarget->GetRaceNum() == 20104 ||
				m_pkChrTarget->GetRaceNum() == 20105 ||
				m_pkChrTarget->GetRaceNum() == 20106 ||
				m_pkChrTarget->GetRaceNum() == 20107 ||
				m_pkChrTarget->GetRaceNum() == 20108 ||
				m_pkChrTarget->GetRaceNum() == 20109)
			{
				LPCHARACTER owner = m_pkChrTarget->GetVictim();

				if (owner)
				{
					int iHorseHealth = owner->GetHorseHealth();
					int iHorseMaxHealth = owner->GetHorseMaxHealth();

					if (iHorseMaxHealth)
					{
						p.bHPPercent = MINMAX(0, iHorseHealth * 100 / iHorseMaxHealth, 100);
#ifdef ENABLE_VIEW_TARGET_HP_SP
						p.iMinHP = 100;
						p.iMaxHP = 100;
#endif
					}
					else
					{
						p.bHPPercent = 100;
#ifdef ENABLE_VIEW_TARGET_HP_SP
						p.iMinHP = 100;
						p.iMaxHP = 100;
#endif
					}
				}
				else
				{
					p.bHPPercent = 100;
#ifdef ENABLE_VIEW_TARGET_HP_SP
					p.iMinHP = 100;
					p.iMaxHP = 100;
#endif
				}
			}
			else
			{
				if (m_pkChrTarget->GetMaxHP() <= 0) // @fixme136
				{
					p.bHPPercent = 0;
#ifdef ENABLE_VIEW_TARGET_HP_SP
					p.iMinHP = 0;
					p.iMaxHP = 0;
#endif
				}
				else
				{
					p.bHPPercent = MINMAX(0, (m_pkChrTarget->GetHP() * 100) / m_pkChrTarget->GetMaxHP(), 100);
#ifdef ENABLE_VIEW_TARGET_HP_SP
					p.iMinHP = m_pkChrTarget->GetHP();
					p.iMaxHP = m_pkChrTarget->GetMaxHP();
#endif
				}
			}
		}
#ifdef ENABLE_VIEW_TARGET_HP_SP
		if ((m_pkChrTarget->GetMaxSP() <= 0))
		{
			p.bSPPercent = 0;
			p.iMinSP = 0;
			p.iMaxSP = 0;
		}
		else if (m_pkChrTarget->IsPC() && !m_pkChrTarget->IsPolymorphed())
		{
			p.bSPPercent = MINMAX(0, (m_pkChrTarget->GetSP() * 100) / m_pkChrTarget->GetMaxSP(), 100);
			p.iMinSP = m_pkChrTarget->GetSP();
			p.iMaxSP = m_pkChrTarget->GetMaxSP();
		}
		else
		{
			p.bSPPercent = 0;
			p.iMinSP = 0;
			p.iMaxSP = 0;
		}
#endif
	}
	else
	{
		p.dwVID = 0;
		p.bHPPercent = 0;
#ifdef ENABLE_VIEW_TARGET_HP_SP
		p.bSPPercent = 0;
		p.iMinHP = 0;
		p.iMaxHP = 0;
		p.iMinSP = 0;
		p.iMaxSP = 0;
#endif
	}

	GetDesc()->Packet(p);
}

//arat - deðiþtir

void CHARACTER::BroadcastTargetPacket()
{
	if (m_set_pkChrTargetedBy.empty())
		return;

	TPacketGCTarget p;

	p.header = HEADER_GC_TARGET;
	p.dwVID = GetVID();

	if (GetMaxHP() <= 0)
	{
		p.bHPPercent = 0;
#ifdef ENABLE_VIEW_TARGET_HP_SP
		p.iMinHP = 0;
		p.iMaxHP = 0;
#endif
	}
	else
	{
#ifdef ENABLE_VIEW_TARGET_HP_SP
		p.bHPPercent = MINMAX(0, (GetHP() * 100) / GetMaxHP(), 100);
		p.iMinHP = GetHP();
		p.iMaxHP = GetMaxHP();
#else
		if (IsPC())
		{
			p.bHPPercent = 0;
		}
		else
		{
			p.bHPPercent = MINMAX(0, (GetHP() * 100) / GetMaxHP(), 100);
		}
#endif
	}

#ifdef ENABLE_VIEW_TARGET_HP_SP
	if (GetMaxSP() <= 0)
	{
		p.bSPPercent = 0;
		p.iMinSP = 0;
		p.iMaxSP = 0;
	}
	else if (IsPC() && !IsPolymorphed())
	{
		p.bSPPercent = MINMAX(0, (GetSP() * 100) / GetMaxSP(), 100);
		p.iMinSP = GetSP();
		p.iMaxSP = GetMaxSP();
	}
	else
	{
		p.bSPPercent = 0;
		p.iMinSP = 0;
		p.iMaxSP = 0;
	}
#endif

	CHARACTER_SET::iterator it = m_set_pkChrTargetedBy.begin();

	while (it != m_set_pkChrTargetedBy.end())
	{
		LPCHARACTER pkChr = *it++;

		if (!pkChr->GetDesc())
		{
			sys_err("%s %p does not have desc", pkChr->GetName(), get_pointer(pkChr));
			abort();
		}

		pkChr->GetDesc()->Packet(p);
	}
}

//arat:

		val = GetSP();

//altýna ekle:
#ifdef ENABLE_VIEW_TARGET_HP_SP
		BroadcastTargetPacket();
#endif
