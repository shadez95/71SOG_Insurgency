//#define DEBUG_MODE_FULL
#include "script_component.hpp"
#include "script_functions.hpp"

private["_cache","_indexEH","_indexMPEH"];
_cache = _this;

_indexEH = _cache addEventHandler ["handleDamage", {
	if ((_this select 4) == "SatchelCharge_Remote_Mag") then {
		_cache setDamage 1;
	} else {
		if ((_this select 4) == "DemoCharge_Remote_Mag") then {
			_cache setDamage 1;
		} else {_cache setDamage 0;};
	};
}];

_indexMPEH = _cache addMPEventHandler["MPKilled", {
	_this CALLC(PREFIX\COMPONENT\createCache.sqf);
	WEST_SCORE = WEST_SCORE + 1;
	publicVariable "WEST_SCORE";
}];

missionNamespace setVariable ["Cache_EventHandlers",[_indexEH,_indexMPEH,_cache]];