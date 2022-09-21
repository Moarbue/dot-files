package.path = package.path .. ";" .. os.getenv("HOME") .. "/.config/luastatus/colorscheme/color.lua"
local color = require("color")

widget = luastatus.require_plugin('cpu-usage-linux').widget{
    cb = function(usage)
        if usage ~= nil then
		return string.format('%s^c#282828^^b#fb4934^  ^c#fb4934^^b#282828^%5.1f%% ', color.sep, usage * 100)
        end
    end,
}
