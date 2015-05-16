//#define DEBUG_MODE_FULL
#include "script_component.hpp"

//#include "script_events.hpp"
#include "script_functions.hpp"
diag_log [diag_frameno, diag_ticktime, time, "Executing MAIN init.sqf"];

LOADCP(cache);
LOADCP(client);






//Params from config
/*
if (isNil {missionNamespace getVariable (configName ((missionConfigFile >> "Params") select 0))}) then {
	if (isNil "paramsArray") then {
	    if (isClass (missionConfigFile/"Params")) then {
	        for "_i" from 0 to (count (missionConfigFile/"Params") - 1) do {
	            _paramName = configName ((missionConfigFile >> "Params") select _i);
	            missionNamespace setVariable [_paramName, getNumber (missionConfigFile >> "Params" >> _paramName >> "default")];
	        };
	    };
	} else {
*/
	    /*for "_i" from 0 to (count paramsArray - 1) do {
	        missionNamespace setVariable [configName ((missionConfigFile >> "Params") select _i), paramsArray select _i];
	   };	  */
/*
	};
};
*/

//Default settings when params not in use
/*
{
	_var = _x select 0;
	_val = _x select 1;
	if (isNil _var) then {
			missionNamespace setVariable [_var, _val];
	};
} forEach [["MGO_SrvScript",0], ["MGO_AcreEnabled",1], ["MGO_AcreSlots",1], ["MGO_RepairEnabled",1], ["MGO_RepairFactor",5],
 ["MGO_RestrictEnabled",1], ["MGO_RestrictPilot",1], ["MGO_RestrictAcre",1]];

if (!isNil "MGO_SrvScript") then {
	if (MGO_SrvScript == 1) then {
		if (isServer) then { execVM "\userconfig\mgo_serv\serverfuncs.sqf" };
	};
} else {
	MGO_SrvScript = 0;
};

if (!isDedicated) then {
	["ACE_sys_interaction", "Interaction_Menu", { _this call FUNC(menuopen) }] call CBA_fnc_addKeyHandlerFromConfig;
};
*/
/*
#ifdef MGO_ACRE_ENAB
LOADCP(acre);
#endif
#ifdef MGO_REPAIR_ENAB
LOADCP(repair);
#endif
#ifdef MGO_RESTRICT_ENAB
LOADCP(restrict);
#endif
#ifdef MGO_RANGE_ENAB
LOADCP(range);
#endif
#ifdef MGO_GNRC_ENAB
LOADCP(gnrc);
#endif
#ifdef MGO_ATTACH_ENAB
LOADCP(attach);
#endif
#ifdef MGO_MOTD_ENAB
LOADCP(motd);
#endif
#ifdef MGO_EVENTS_ENAB
LOADCP(events);
#endif
#ifdef MGO_PUNISH_ENAB
LOADCP(punish);
#endif*/
diag_log [diag_frameno, diag_ticktime, time, "MAIN init.sqf processed"];
