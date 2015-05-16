//#define DEBUG_MODE_FULL
#include "script_component.hpp"
/*
#ifdef DEBUG_MODE_FULL
	#define cache_debug true
#else
	#define cache_debug false
#endif*/

cache_debug = true;

//#include "script_events.hpp"
#include "script_functions.hpp"
diag_log [diag_frameno, diag_ticktime, time, "Executing CACHE init.sqf"];

private["_cache"];

cacheMarkerArray = [];
publicVariable "cacheMarkerArray";
WEST_SCORE = 0;
publicVariable "WEST_SCORE";

//cache creation
if (isServer) then {
	_cache = CALLC(PREFIX\COMPONENT\createCache.sqf);
};









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
diag_log [diag_frameno, diag_ticktime, time, "CACHE init.sqf processed"];
