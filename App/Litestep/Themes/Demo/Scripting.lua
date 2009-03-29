require "lsmodule"
require "evar"
--module ("memory", package.seeall)

function bang_Startup()
	bang_ResizeTray();
	local FirstRun = evar.toboolean('FirstRun');
	lslua.exec('!CommandShowText Runbar');
	if FirstRun then
		bang_Tutorial();
	end
end

bang_ToggleDesktop = function()
	--lslua.exec('!alert "testing out LUA!')
	local DesktopEnabled = evar.toboolean('ShowDesk');
	Desktop = lsmodule.clickonic;
	Desktop.version = '1.1.4';
	if DesktopEnabled then
		SetRCVar('ShowDesk', 'false');
		Desktop:unload();
	else
		SetRCVar('ShowDesk', 'true');
		--lslua.exec('!reload');
		Desktop:load();
	end
end

bang_ToggleTaskbar = function()
	local TaskbarEnabled = evar.toboolean('ShowTask');
	Taskbar = lsmodule.xtaskbar;
	Taskbar.version = '2.2'
	if TaskbarEnabled then
		SetRCVar('ShowTask', 'false');
		Taskbar:unload();
	else
		SetRCVar('ShowTask', 'true');
		--lslua.exec('!reload');
		Taskbar:load();
	end
end

bang_ToggleFullscreenWindows = function()
	local FullScreenWindowsEnabled = evar.toboolean('MaxWindowsFullScreen');
	if FullScreenWindowsEnabled then
		SetRCVar('MaxWindowsFullScreen', 'false');
		lslua.exec('!jDeskSetWorkArea 1,26,-1,-25');
	else
		SetRCVar('MaxWindowsFullScreen', 'true');
		lslua.exec('!jDeskSetWorkArea 1,1,-1,-1');
	end
end

function bang_ToggleStats()
	local StatsEnabled = evar.toboolean('ShowStats');
	Stats = lsmodule.xlabel.Stats;
	if StatsEnabled then
		SetRCVar('ShowStats', 'false');
		Stats:destroy();
	else
		SetRCVar('ShowStats', 'true');
		--lslua.exec('!reload');
		Stats:create();
	end
end

function bang_AttemptThemeFix()
	
end

function bang_ResizeLSX()
	--LSX = lsmodule.command;
	Stats = lsmodule.xlabel.stats;
	Expanded = evar.toboolean('LSXExpanded');
	ShowStats = evar.toboolean('ShowStats');
	if Expanded then
		lslua.exec('!CommandResize home 5 5');
		--LSX:resize('home');
		if ShowStats then
			Stats:repositionby(-100, 0, 100, 0, 5, 5);
		end
		lslua.set_evar('LSXExpanded', 'false');
	else
		--lslua.exec('!alert "'..LSX.MaxWidth..'"');
		lslua.exec('!CommandResizeBy 100 0 5 5');
		--LSX:resizeby(LSX.Width, 0, 5, 5);
		if ShowStats then
			Stats:repositionby(100, 0, -100, 0, 5, 5);
		end
		lslua.set_evar('LSXExpanded', 'true');
	end
end

function bang_ResizeTray()
	local StatsEnabled = evar.toboolean('ShowStats');
	xTray = lsmodule.xtray.xtray;
	SysBorder = lsmodule.xlabel.sysbord;
	Time = lsmodule.xlabel.time;
	Stats = lsmodule.xlabel.stats;
	--xTrayWidth = xTray.IconWidth*xTray.IconCount
	--ResX = lslua.get_evar('ResolutionX');
	--!xTrayMove -%#xTrayIconWidth*xTrayCurrentIconCount-TimeX%# 1
	--lslua.exec('!alert "'..xTrayWidth..'\n'..xTray.Width..'"');
	xTray:move(Time.X-xTray.Width, xTray.Y);
	--!LabelResize Sysbord %#xTrayIconWidth*xTrayCurrentIconCount+TimeWidth+2%# $SysbordHeight$
	SysBorder:reposition(
		Time.X-xTray.Width, xTray.Y,
		xTray.Width+Time.Width+2, SysBorder.Height);
	--!LabelMove Sysbord -%#xTrayIconWidth*xTrayCurrentIconCount-TimeX%# 1
	
	if StatsEnabled then
	--!LabelResize Stats %#$StatsWidth$-(xTrayIconWidth*xTrayCurrentIconCount)+$xTrayIconWidth$-1%# $StatsHeight$
		--lslua.exec('!alert '..lslua.get_evar('StatsWidth')-xTray.Width);
		local xTrayOrgWidth = 
		Stats:resize(
			lslua.get_evar('StatsWidth')-(xTray.Width-evar["xTrayWidth"])-1, Stats.Height);
	end
end

function bang_ToggleFullscreenDesktop()
	Desktop = lsmodule.clickonic;
	local DesktopFullScreen = evar.toboolean('DeskFullScreen');
	if DesktopFullScreen then
		SetRCVar('DeskFullScreen', 'false');
		lslua.exec('!ClickonicReposition DeskIcons 0 26 $ResolutionX$ $ResolutionY-52$');
	else
		SetRCVar('DeskFullScreen', 'true');
		lslua.exec('!ClickonicReposition DeskIcons 0 0 $ResolutionX$ $ResolutionY$');
	end
end

function bang_Tutorial()
	--local PortableAppsDir = evar['PA'];
	lslua.exec('$Tutorial$');
end

function bang_EndTutorial()
	SetRCVar('FirstRun', 'false');
end

function SetRCVar(Setting, Value)
	-- Set the evar in memory, then in rc files.
	lslua.set_evar(Setting, Value);
	BasicRC = evarutils.config.Basic;
	BasicRC[Setting] = Value;
end