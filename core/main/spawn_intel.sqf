//#define DEBUG_MODE_FULL
#include "script_component.hpp"
#include "script_functions.hpp"

if (isServer) then {
	_object = _this select 0;
	
	if (side _object == EAST or side _object == resistance) then {

		_object addEventHandler ['killed',{
			_object = _this select 0;
			//Gives 100% chance of spawning intel on opfor players
			if (isPlayer _object) then {
				_scase = createVehicle ["Land_Suitcase_F",getpos (_this select 0), [], 0, "None"];
				//[[_scase,"<t color='#FF0000'>Pickup Intel</t>"],"addactionMP", true, true] spawn BIS_fnc_MP;
				[-1, {[_this,"<t color='#FF0000'>Pickup Intel</t>"] call FUNC(addActionMP);}, _scase] call CBA_fnc_globalExecute;
			} else {
			//Gives 10% chance of spawning intel on AI units
			if (20 > random 100) then {
				_scase = createVehicle ["Land_Suitcase_F",getpos (_this select 0), [], 0, "None"];
				//[[_scase,"<t color='#FF0000'>Pickup Intel</t>"],"addactionMP", true, true] spawn BIS_fnc_MP;
				[-1, {[_this,"<t color='#FF0000'>Pickup Intel</t>"] call FUNC(addActionMP);}, _scase] call CBA_fnc_globalExecute;
			};
			};
		} ];
		/*_object addEventHandler ["Hit",{
			_unit = _this select 0;
			_unit setDamage ((_this select 2) * 5);
		} ];*/
	};

};