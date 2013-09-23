--[[
rem Remote Controll
rem

@title L:Remote Controll
@param a Shoot
@default a 10

@param s do/until Sleep x10
@default s 0
]]

-- better human readable parameter names
loopWait = s*10

print("ready for KAP! :-)")

repeat
	repeat
		power = get_usb_power()
	until power > 0

	shoot()
until is_key("set") == true
