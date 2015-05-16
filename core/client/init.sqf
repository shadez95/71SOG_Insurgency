//#define DEBUG_MODE_FULL
#include "script_component.hpp"

//#include "script_events.hpp"
#include "script_functions.hpp"
diag_log [diag_frameno, diag_ticktime, time, "Executing CLIENT init.sqf"];

if (hasInterface) then {
	CALLC(PREFIX\COMPONENT\scoreKeeper.sqf);
	CALLC(PREFIX\COMPONENT\TFAR_Required.sqf);
};

diag_log [diag_frameno, diag_ticktime, time, "CLIENT init.sqf processed"];
