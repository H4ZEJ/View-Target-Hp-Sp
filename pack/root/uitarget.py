#arat:
		hpGauge = ui.Gauge()
		hpGauge.SetParent(self)
		hpGauge.MakeGauge(130, "red")
		hpGauge.Hide()

#altına ekle:
		if app.ENABLE_VIEW_TARGET_HP_SP:
			spGauge = ui.Gauge()
			spGauge.SetParent(self)
			spGauge.MakeGauge(130, "blue")
			spGauge.Hide()

			hpDecimal = ui.TextLine()
			hpDecimal.SetParent(hpGauge)
			hpDecimal.SetDefaultFontName()
			hpDecimal.SetPosition(5, 5)
			hpDecimal.SetOutline()
			hpDecimal.Hide()

			spDecimal = ui.TextLine()
			spDecimal.SetParent(spGauge)
			spDecimal.SetDefaultFontName()
			spDecimal.SetPosition(5, 5)
			spDecimal.SetOutline()
			spDecimal.Hide()

#arat:
			hpGauge.SetPosition(175, 17)

#değiştir:
		if app.ENABLE_VIEW_TARGET_HP_SP:
			hpGauge.SetPosition(310, 17)
		else:
			hpGauge.SetPosition(175, 17)

#arat:
		hpGauge.SetWindowHorizontalAlignRight()

altına ekle:
		if app.ENABLE_VIEW_TARGET_HP_SP:
			spGauge.SetPosition(175, 17)
			spGauge.SetWindowHorizontalAlignRight()

#arat:
		self.hpGauge = hpGauge

#altına ekle:
		if app.ENABLE_VIEW_TARGET_HP_SP:
			self.spGauge = spGauge
			self.hpDecimal = hpDecimal
			self.spDecimal = spDecimal

#arat:
		self.hpGauge = None

#altına ekle:
		if app.ENABLE_VIEW_TARGET_HP_SP:
			self.spGauge = None
			self.hpDecimal = None
			self.spDecimal = None

#arat - değiştir:
	if app.ENABLE_VIEW_TARGET_HP_SP:
		def Open(self, vid, name, hpPercentage, spPercentage, iMinHP, iMaxHP, iMinSP, iMaxSP):
			if vid:
				if not constInfo.GET_VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD():
					if not player.IsSameEmpire(vid):
						self.Hide()
						return

				if vid != self.GetTargetVID():
					self.ResetTargetBoard()
					self.SetTargetVID(vid)
					self.SetTargetName(name)

				if player.IsMainCharacterIndex(vid):
					self.__ShowMainCharacterMenu()
				elif chr.INSTANCE_TYPE_BUILDING == chr.GetInstanceType(self.vid):
					self.Hide()
				else:
					self.RefreshButton()
					self.Show()

				if player.GetName() != name:
					if not self.hpGauge.IsShow():
						self.name.SetPosition(33 - (len(name) * 1.5), 13)
						self.name.SetWindowHorizontalAlignLeft()
						self.name.SetHorizontalAlignLeft()
						self.__UpdateHPGaugePosition()
						self.hpGauge.Show()
						self.UpdatePosition()
					self.hpGauge.SetPercentage(hpPercentage, 100)
					if not self.spGauge.IsShow():
						self.name.SetPosition(33 - (len(name) * 1.5), 13)
						self.name.SetWindowHorizontalAlignLeft()
						self.name.SetHorizontalAlignLeft()
						self.spGauge.Show()
						self.UpdatePosition()
					self.spGauge.SetPercentage(spPercentage, 100)

					self.hpDecimal.SetText(localeInfo.DecimalNumber(max(iMinHP, 0)) + " / " + localeInfo.DecimalNumber(iMaxHP))
					(textWidth, textHeight) = self.hpDecimal.GetTextSize()
					self.hpDecimal.SetPosition(130 / 2 - textWidth / 2, -15)

					self.hpDecimal.Show()
					self.spDecimal.SetText(localeInfo.DecimalNumber(max(iMinSP, 0)) + " / " + localeInfo.DecimalNumber(iMaxSP))
					(textWidth, textHeight) = self.spDecimal.GetTextSize()
					self.spDecimal.SetPosition(130 / 2 - textWidth / 2, -15)

					self.spDecimal.Show()
				else:
					self.SetSize(150 + (len(name) * 1.5), 65)
					self.name.SetPosition(0, 13)
					self.name.SetWindowHorizontalAlignCenter()
					self.name.SetHorizontalAlignCenter()
					self.UpdatePosition()
			else:
				self.HideAllButton()
				self.__ShowButton(localeInfo.TARGET_BUTTON_WHISPER)
				self.__ShowButton("VOTE_BLOCK_CHAT")
				self.__ArrangeButtonPosition()
				self.SetTargetName(name)
				self.Show()
	else:
		def Open(self, vid, name):
			if vid:
				if not constInfo.GET_VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD():
					if not player.IsSameEmpire(vid):
						self.Hide()
						return

				if vid != self.GetTargetVID():
					self.ResetTargetBoard()
					self.SetTargetVID(vid)
					self.SetTargetName(name)

				if player.IsMainCharacterIndex(vid):
					self.__ShowMainCharacterMenu()
				elif chr.INSTANCE_TYPE_BUILDING == chr.GetInstanceType(self.vid):
					self.Hide()
				else:
					self.RefreshButton()
					self.Show()
			else:
				self.HideAllButton()
				self.__ShowButton(localeInfo.TARGET_BUTTON_WHISPER)
				self.__ShowButton("VOTE_BLOCK_CHAT")
				self.__ArrangeButtonPosition()
				self.SetTargetName(name)
				self.Show()

#arat:
		self.name.SetWindowHorizontalAlignCenter()
		self.hpGauge.Hide()

#altına ekle:
		if app.ENABLE_VIEW_TARGET_HP_SP:
			self.spGauge.Hide()
			self.hpDecimal.Hide()
			self.spDecimal.Hide()

#arat-değiştir:
	if app.ENABLE_VIEW_TARGET_HP_SP:
		def SetHP(self, hpPercentage, iMinHP, iMaxHP):
			if not self.hpGauge.IsShow():
				self.SetSize(200 + 7 * self.nameLength, self.GetHeight())
				self.name.SetPosition(23, 13)
				self.name.SetWindowHorizontalAlignLeft()
				self.name.SetHorizontalAlignLeft()
				self.__UpdateHPGaugePosition()
				self.hpGauge.Show()
				self.UpdatePosition()
			self.hpGauge.SetPercentage(hpPercentage, 100)

			if self.spGauge.IsShow():
				self.spGauge.Hide()

			self.hpDecimal.SetText(localeInfo.DecimalNumber(max(iMinHP, 0)) + " / " + localeInfo.DecimalNumber(iMaxHP))
			(textWidth, textHeight) = self.hpDecimal.GetTextSize()
			self.hpDecimal.SetPosition(130 / 2 - textWidth / 2, -15)

			self.hpDecimal.Show()

			self.spDecimal.Hide()
	else:
		def SetHP(self, hpPercentage):
			if not self.hpGauge.IsShow():
				self.SetSize(200 + 7 * self.nameLength, self.GetHeight())

				self.name.SetPosition(23, 13)
				self.name.SetWindowHorizontalAlignLeft()
				self.name.SetHorizontalAlignLeft()
				self.hpGauge.Show()
				self.UpdatePosition()

			self.hpGauge.SetPercentage(hpPercentage, 100)

#arat:
		self.SetSize(max(150, showingButtonCount * 75), 65)

#değiştir:
		if app.ENABLE_VIEW_TARGET_HP_SP:
			if showingButtonCount <= 3:
				self.SetSize(max(150, 4 * 75), 65)
			else:
				self.SetSize(max(150, showingButtonCount * 75), 65)
		else:
			self.SetSize(max(150, showingButtonCount * 75), 65)

#en alta ekle:
	if app.ENABLE_VIEW_TARGET_HP_SP:
		def __UpdateHPGaugePosition(self):
			if nonplayer.GetLevelByVID(self.vid) != -1:
				self.hpGauge.SetPosition(175, 17)
			else:
				self.hpGauge.SetPosition(310, 17)