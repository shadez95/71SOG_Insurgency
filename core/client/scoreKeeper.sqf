#include "script_component.hpp"
#include "script_functions.hpp"

"WEST_SCORE" addPublicVariableEventHandler {
	_score = _this select 1;
	_value = missionNamespace getVariable "Cache_EventHandlers";
	diag_log format["_value = %1",_value];
	_indexEH = _value select 0;
	_indexMPEH = _value select 1;
	_cache = _value select 2;
	
	_cache removeEventHandler["handleDamage",_indexEH];
	_cache removeEventHandler["MPKilled",_indexMPEH];
	
	_cache call FUNC(cacheKilled);
};

[] spawn {
	while {true} do {
		if (WEST_SCORE == (paramsArray select 1)) then {
			[-2, {CALLC(PREFIX\COMPONENT\blufor_win.sqf);}, "None"] call CBA_fnc_globalExecute;
			sleep 20;
			[-2, {endMission "END1"}, "None"] call CBA_fnc_globalExecute;
		};
		sleep 10;
	};
};