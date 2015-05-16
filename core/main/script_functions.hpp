MGO_PHON = ["Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel",
 "India", "Juliet", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", 
"Romeo","Sierra", "Tango", "Uniform", "Victor", "Whiskey", "Xray", "Yankee", "Zulu"];

FUNC(WarnMsg) = {
	PARAMS_1(_msg);
	DEFAULT_PARAM(1,_beep,true);

	if (_beep) then {
		hint _msg;
	} else {
		hintSilent _msg;
	};

	_msg = _msg call FUNC(RemoveLineBreak);

	[playerSide, "HQ"] sideChat _msg;
};

FUNC(TitleMsg) = {
	PARAMS_1(_msg);
	DEFAULT_PARAM(1,_time,10);
	titleText [_msg, "plain down"];
	titleFadeOut _time;
};

FUNC(RemoveLineBreak) = { // code by Xeno
	private ["_msg", "_msg_chat_a", "_i", "_c"];
	_msg = _this;
	_msg_chat_a = toArray (_msg);
	for "_i" from 0 to (count _msg_chat_a - 2) do {
		_c = _msg_chat_a select _i;
		if (_c == 92) then {
			if ((_msg_chat_a select (_i + 1)) in [78,110]) then {
				_msg_chat_a set [_i, 32];
				_i = _i + 1;
				_msg_chat_a set [_i, -1];
			};
		};
	};
	_msg_chat_a = _msg_chat_a - [-1];
	toString (_msg_chat_a)
};

FUNC(EngineOff) = {
	PARAMS_1(_veh);
	//if (isEngineOn _veh) then {_veh engineOn false}; //CIT #22360
	if (isNil {_veh getVariable QGVAR(org_fuel)}) then {
		_veh setVariable [QGVAR(org_fuel), fuel _veh];
		if (_veh getVariable [QGVAR(org_fuel), 0] > 0) then {
			_veh setFuel 0;
			_veh spawn {
				sleep 1;
				_this setFuel (_this getVariable [QGVAR(org_fuel), 0]);
				_this setVariable [QGVAR(org_fuel), nil];
			};
		};
	};
};

// by Xeno
// get displayname of an object
// parameters: type of object (string), what (0 = CfgVehicles, 1 = CfgWeapons, 2 = CfgMagazines)
// example: _dispname = ["UAZ", 0] call FUNC(GetDisplayName);
FUNC(GetDisplayName) = {
	private ["_obj_name", "_obj_kind", "_cfg", "_drop_dn"];
	PARAMS_2(_obj_name,_obj_kind);
	_cfg = switch (_obj_kind) do {case 0: {"CfgVehicles"};case 1: {"CfgWeapons"};case 2: {"CfgMagazines"};};

	_drop_dn = getText (configFile >> _cfg >> _obj_name >> "displayNameShort");
	if (_drop_dn == "") then {
		_drop_dn = getText (configFile >> _cfg >> _obj_name >> "displayName");
		if (_drop_dn == "") then {
			_drop_dn = _obj_name;
		};
	};

	_drop_dn
};

FUNC(VehicleChat) = {
	PARAMS_2(_veh,_msg);
	if (typeName _veh != "OBJECT") exitWith {};
	if (typeName _msg != "STRING") exitWith {};
	["MTEMCV", [_veh,_msg]] call CBA_fnc_globalEvent;
};

FUNC(returnConfigEntry) = {
	/*
		File: returnConfigEntry.sqf
		Author: Joris-Jan van 't Land

		Description:
		Explores parent classes in the run-time config for the value of a config entry.

		Parameter(s):
		_this select 0: starting config class (Config)
		_this select 1: queried entry name (String)

		Returns:
		Number / String - value of the found entry
	*/
	if (count _this < 2) exitWith {nil};
	private ["_config", "_entryName"];
	PARAMS_2(_config,_entryName);
	if (typeName _config != typeName configFile) exitWith {nil};
	if (typeName _entryName != typeName "") exitWith {nil};
	private ["_entry", "_value"];
	_entry = _config >> _entryName;
	if (configName (_config >> _entryName) == "" && !((configName _config) in ["CfgVehicles", "CfgWeapons", ""])) then {
		[inheritsFrom _config, _entryName] call FUNC(returnConfigEntry);
	} else {
		if (isNumber _entry) then {
			_value = getNumber _entry;
		} else {
			if (isText _entry) then {_value = getText _entry};
		};
	};
	if (isNil "_value") exitWith {nil};
	_value
};

FUNC(menuopen) = {
	_target = cursorTarget;
	if (!isNull _target) then {
		if (isNil QGVAR(menuopen)) then {
			GVAR(menuopen) = true;
			["MGO_OPMEN", [_target]] call CBA_fnc_localEvent;
			0 spawn {
				sleep 10;
				GVAR(menuopen) = nil;
			};
		};
	};
	false
};

FUNC(debugMarker) = {
	PARAMS_5(_str,_pos,_shape,_type,_color);
	
	_mkr = createMarker[_str,_pos];
	_mkr setMarkerShape _shape;
	_mkr setMarkerType _type;
	_mkr setMarkerColor _color;
	_str;
};

FUNC(killedText) = {
	hint parseText format["<t align='center' color='#e5b348' size='1.2'><t shadow='1'shadowColor='#000000'>Insurgency</t></t>
	<img color='#ffffff' image='core\Images\img_line_ca.paa' align='center' size='0.79' />
	<t color='#eaeaea'>%1/%2</t><t color='#80FF00'> Ammo Caches</t><t color='#eaeaea'> have been destroyed</t>
	<img color='#ffffff' image='core\Images\img_line_ca.paa' align='center' size='0.79' />", WEST_SCORE,paramsArray select 1]
};

FUNC(pickedUpIntel) = {
	hint parseText format["<t align='center' color='#e5b348' size='1.2'><t shadow='1'shadowColor='#000000'>Insurgency</t></t>
	<img color='#ffffff' image='core\Images\img_line_ca.paa' align='center' size='0.79' />
	<t color='#eaeaea'>New intel received on the location of an ammo cache. A marker has been added to the map.</t>
	<img color='#ffffff' image='core\Images\img_line_ca.paa' align='center' size='0.79' />"]
};

FUNC(cacheKilled) = {
	private ["_pos","_x"];
	
	_cache = _this;
	
	_pos = getPos _cache;
	_x = 0;

	while { _x <= 20 } do {
		"M_Mo_82mm_AT_LG" createVehicle _pos;
		_x = _x + 1 + random 4;
		sleep 1;
	};

	call FUNC(killedText);
	if (count INS_marker_array > 0) then { {deleteMarker _x} forEach INS_marker_array; INS_marker_array = []};
	publicVariable "INS_marker_array";
	westTickets = westTickets + (paramsArray select 3);
	publicVariable "westTickets";
};

FUNC(createIntel) = {
	private ["_i","_sign","_sign2","_radius","_cache","_pos","_mkr","_range","_intelRadius"];

    _cache = _this;
	_intelRadius = 500;
    _i = 0;

	while{ (getMarkerPos format["%1intel%2", _cache, _i] select 0) != 0} do {
		_i = _i + 1;
	};

	_sign = 1;

	if (random 100 > 50) then {
		_sign = -1;
	};

	_sign2 = 1;

	if (random 100 > 50) then {
		_sign2 = -1;
	};

	_radius = _intelRadius - _i * 50;

	if (_radius < 50) then {
		_radius = 50;
	};

	_pos = [(getPosATL _cache select 0) + _sign *(random _radius),(getPosATL _cache select 1) + _sign2*(random _radius)];
	_mkr = createMarker[format["%1intel%2", _cache, _i], _pos];
	_mkr setMarkerType "hd_unknown";
	_range = round sqrt(_radius^2*2);
	_range = _range - (_range % 50);
	_mkr setMarkerText format["%1m", _range];
	_mkr setMarkerColor "ColorRed";
	_mkr setMarkerSize [0.5,0.5];
	_mkr_array = [_mkr];
	INS_marker_array = INS_marker_array + _mkr_array;
};

FUNC(intelPickup) = {
	if (side player == east) exitWith{};
	_intel = _this select 0;
	_used = _this select 1;
	_ID = _this select 2;
	
	_intel removeAction _ID;
	
	_cases = nearestObjects[getPos player, intelItems, 10];

	if (count _cases == 0) exitWith {};

	_case = _cases select 0;

	if (isNull _case) exitWith {};

	deleteVehicle _case;
	player groupChat "You retrieved some INTEL on the general location of an ammo cache";

	_cache = cache;

	if (isNil "_cache") exitWith {
		hint "There is no spawned cache. This is game breaking. Please contact the admin to restart and report this issue";
	};

	[-1, { call FUNC(pickedUpIntel)}, nil] call CBA_fnc_globalExecute;
	[0, { _this call FUNC(createIntel)}, _cache] call CBA_fnc_globalExecute;
	//[nil, "pickedUpIntel", true, false] spawn BIS_fnc_MP;
	//[_cache, "createIntel", false, false] spawn BIS_fnc_MP;
};

FUNC(addActionMP) = {
	private["_object","_screenMsg"];
	PARAMS_2(_object,_screenMsg);

	if(isNull _object) exitWith {};

	_object addaction [_screenMsg,QUOTE(call FUNC(intelPickup))];
};