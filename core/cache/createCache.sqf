//#define DEBUG_MODE_FULL
#include "script_component.hpp"
#include "script_functions.hpp"

private["_cacheTown","_targetBuilding","_cachePositions","_cachePosition"];

_cities = call FUNC(UrbanAreas);
_cacheTown = _cities select floor random count _cities;
//diag_log format["CACHE - _cacheTown = %1",_cacheTown];
_cacheBuildings = [(_cacheTown select 1), (_cacheTown select 2)] call FUNC(findBuildings);
//diag_log format["CACHE - _cacheBuildings = %1", _cacheBuildings];
_targetBuilding = _cacheBuildings select floor random count _cacheBuildings;
//diag_log format["CACHE - _targetBuilding = %1", _targetBuilding];
_cachePositions = _targetBuilding call FUNC(buildingPositions);
//diag_log format["CACHE - _cachePositions = %1",_cachePositions];
if (_cachePositions isEqualTo []) then {
	_cachePosition = getPosATL _targetBuilding;
} else {
	_cachePosition = _cachePositions select floor random count _cachePositions;
};

//diag_log format["CACHE - _cachePosition = %1",_cachePosition];

if (typeName _cachePosition != "ARRAY") exitWith { CALLC(PREFIX\COMPONENT\createCache.sqf); }; //Checks if there is a building position

private["_cache"];

_cache = createVehicle ["Box_East_WpsSpecial_F", [-10,-10,0], [], 0, "NONE"];
_cache allowDamage false;
clearWeaponCargoGlobal _cache;
clearMagazineCargoGlobal _cache;
clearItemCargoGlobal _cache;

_cache setPos _cachePosition;
_cache allowDamage true;
cache = _cache;
publicVariable "cache";

if (cache_debug) then { [format["box%1",random 1000],getPosATL _cache,"ICON","hd_dot","ColorRed"] call FUNC(debugMarker); };

_cache CALLC(PREFIX\COMPONENT\cacheHandler.sqf);
_cache;