require "lsmodule"
require "evar"
--module ("memory", package.seeall)

bang_ToggleDesktop = function()
	--lslua.exec('!alert "testing out LUA!')
	local DesktopEnabled = evar.toboolean('ShowDesk');
	Desktop = lsmodule.clickonic;
	Desktop.version = '1.1.4';
	if DesktopEnabled then
		lslua.set_evar('ShowDesk', 'false');
		SetRCVar('ShowDesk', 'false');
		Desktop:unload();
	else
		lslua.set_evar('ShowDesk', 'true');
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
		lslua.set_evar('ShowTask', 'false');
		SetRCVar('ShowTask', 'false');
		Taskbar:unload();
	else
		lslua.set_evar('ShowTask', 'true');
		SetRCVar('ShowTask', 'true');
		--lslua.exec('!reload');
		Taskbar:load();
	end
end

bang_ToggleFullscreenWindows = function()
	local FullScreenWindowsEnabled = evar.toboolean('MaxWindowsFullScreen');
	if FullScreenWindowsEnabled then
		lslua.set_evar('MaxWindowsFullScreen', 'false');
		SetRCVar('MaxWindowsFullScreen', 'false');
		lslua.exec('!jDeskSetWorkArea 1,26,-1,-25');
	else
		lslua.set_evar('MaxWindowsFullScreen', 'true');
		SetRCVar('MaxWindowsFullScreen', 'true');
		lslua.exec('!jDeskSetWorkArea 1,1,-1,-1');
	end
end

function bang_ToggleStats()
	local StatsEnabled = evar.toboolean('ShowStats');
	Stats = lsmodule.xlabel.Stats;
	if StatsEnabled then
		lslua.set_evar('ShowStats', 'false');
		SetRCVar('ShowStats', 'false');
		Stats:destroy();
	else
		lslua.set_evar('ShowStats', 'true');
		SetRCVar('ShowStats', 'true');
		--lslua.exec('!reload');
		Stats:create();
	end
end

function bang_AttemptThemeFix()
	
end

function bang_ResizeTray()
	local StatsEnabled = evar.toboolean('ShowStats');
	xTray = lsmodule.xtray.xtray;
	--!ParseEvars !xTrayMove -%#xTrayIconWidth*xTrayCurrentIconCount-TimeX%# 1]
	--xTray:moveby(
	if StatsEnabled then
		
	else
		
	end
end

function bang_ToggleFullscreenDesktop()
	Desktop = lsmodule.clickonic;
	local DesktopFullScreen = evar.toboolean('DeskFullScreen');
	if DesktopFullScreen then
		lslua.set_evar('DeskFullScreen', 'false');
		SetRCVar('DeskFullScreen', 'false');
		lslua.exec('!ClickonicReposition DeskIcons 0 26 $ResolutionX$ $ResolutionY-52$');
	else
		lslua.set_evar('DeskFullScreen', 'true');
		SetRCVar('DeskFullScreen', 'true');
		lslua.exec('!ClickonicReposition DeskIcons 0 0 $ResolutionX$ $ResolutionY$');
	end
end

function bang_Tutorial()
	--local PortableAppsDir = evar['PA'];
	lslua.exec('$PA$LitestepPortable\\App\\Litestep\\Tutorial\\Tutorial.exe');
end

function SetRCVar(Setting, Value)
	BasicRC = evarutils.config.Basic;
	BasicRC[Setting] = Value;
end