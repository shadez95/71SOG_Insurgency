FUNC(UrbanAreas) = {
	private ["_locations","_cityTypes","_randomLoc","_x","_i","_cities"];
	_i = 0;
	_cities = [];

	_locations = configfile >> "CfgWorlds" >> worldName >> "Names";
	_cityTypes = ["NameVillage","NameCity","NameCityCapital","CityCenter"];

	for "_x" from 0 to (count _locations - 1) do {
		_randomLoc = _locations select _x;
		// get city info
		private["_cityName","_cityPos","_cityRadA","_cityRadB","_cityType","_cityAngle"];
		_cityName = getText(_randomLoc >> "name");
		_cityPos = getArray(_randomLoc >> "position");
		_cityRadA = getNumber(_randomLoc >> "radiusA");
		_cityRadB = getNumber(_randomLoc >> "radiusB");
		_cityType = getText(_randomLoc >> "type");
		_cityAngle = getNumber(_randomLoc >> "angle");
		if (_cityType in _cityTypes && (_cityName != "Jaza" && _cityName != "LoyManara" && _cityName != "Stratis Air Base") ) then {
			_cities set [_i,[_cityName, _cityPos, _cityRadA, _cityRadB, _cityType, _cityAngle]];
			_i = _i + 1;
		};
	};
	_cities;
};

FUNC(findBuildings) = {
	private ["_center","_radius","_buildings"];
	PARAMS_2(_center,_radius);
	//_cacheHouses = ["Land_House_L_1_EP1","Land_House_L_3_EP1","Land_House_L_4_EP1","Land_House_L_6_EP1","Land_House_L_7_EP1","Land_House_L_8_EP1","Land_House_L_9_EP1","Land_House_K_1_EP1","Land_House_K_3_EP1","Land_House_K_5_EP1","Land_House_K_6_EP1","Land_House_K_7_EP1","Land_House_K_8_EP1","Land_House_C_1_EP1","Land_House_C_1_v2_EP1","Land_House_C_2_EP1","Land_House_C_3_EP1","Land_House_C_4_EP1","Land_House_C_5_EP1","Land_House_C_5_V1_EP1","Land_House_C_5_V2_EP1","Land_House_C_5_V3_EP1","Land_House_C_9_EP1","Land_House_C_10_EP1","Land_House_C_11_EP1","Land_House_C_12_EP1","Land_A_Villa_EP1","Land_A_Mosque_small_1_EP1","Land_A_Mosque_small_2_EP1","Land_Ind_FuelStation_Build_EP1","Land_Ind_FuelStation_Shed_EP1","Land_Ind_Garage01_EP1"];
	_buildingTypes = ["Church","Land_BellTower_01_V1_F","Land_BellTower_01_V2_F","Land_Calvary_01_V1_F","Land_Calvary_02_V1_F","Land_Calvary_02_V2_F","Land_Lighthouse_small_F","Land_u_Addon_01_V1_F","Land_d_Addon_02_V1_F","Land_u_Addon_02_V1_F","Land_i_Addon_03_V1_F","Land_i_Addon_03mid_V1_F","Land_i_Addon_04_V1_F","Land_i_Garage_V1_F","Land_Metal_Shed_F","Land_i_House_Small_02_V1_F","Land_d_House_Small_02_V1_F","Land_cargo_addon01_V1_F","Land_cargo_addon01_V2_F","Land_cargo_addon02_V1_F","Land_cargo_addon02_V2_F","Land_cargo_house_slum_F","Land_Slum_House01_F","Land_Slum_House02_F","Land_i_Stone_Shed_V1_F","Land_Factory_Conv1_10_F","Land_Factory_Conv1_End_F","Land_FuelStation_Build_F","Land_fs_feed_F","Land_TTowerSmall_1_F","Land_TTowerSmall_2_F","Cargo_House_base_F","Land_Radar_Small_F","Land_Research_house_V1_F","Land_Offices_01_V1_F","Land_Amphitheater_F","Land_Castle_01_tower_F","Land_Cstle_01_house_ruin_F","Land_Castle_01_church_a_ruin_F","Land_Castle_church_b_ruin_F","Land_Castle_01_church_ruin_F","Land_Hospital_main_F","Land_Hospital_side1_F","Land_Hospital_side2_F","Land_LightHouse_F","Land_i_House_Big_01_V2_F","Land_i_House_Big_01_V3_F","Land_d_House_Big_01_V1_F","Land_i_House_Big_02_V2_F","Land_i_House_Big_02_V3_F","Land_d_House_Big_02_V1_F","Land_i_Shop_01_V1_F","Land_d_Shop_01_V1_F","Land_i_Shop_02_V1_F","Land_d_Shop_02_V1_F","Land_i_House_Small_01_V1_F","Land_d_House_Small_01_V1_F","Land_i_House_Small_03_V1_F","Land_i_Stone_HouseBig_V1_F","Land_d_Stone_HouseBig_V1_F","Land_i_Stone_HouseSmall_V1_F","Land_d_Stone_HouseSmall_V1_F","Land_Unfinished_Building_01_F","Land_Unfinished_Building_02_F","Land_Airport_center_F","Land_Airport_Tower_F","Land_LandMark_F","Land_CarService_F","Land_cmp_Hopper_F","Land_cmp_Shed_F","Land_cmp_Shed_dam_F","Land_cmp_Tower_F","Land_dp_mainFactory_F","Land_dp_smallFactory_F","Land_Factory_Conv1_Main_F","Land_Factory_Conv2_F","Land_Factory_Hopper_F","Land_Factory_Main_F","Land_Factory_Tunnel_F","Land_FuelStation_Shed_F","Land_Shed_Big_F","Land_Shed_Small_F","Land_i_Shed_Ind_F","Land_u_Shed_Ind_F","Land_spp_Panel_F","Land_spp_Tower_F","Land_TTowerBig_1_F","Land_TTowerBig_2_F","Land_i_Barracks_V1_F","Land_Bunker_F","Cargo_HQ_base_F","Cargo_Patrol_base_F","Cargo_Tower_base_F","Land_MilOffices_V1_F"];
    if (_radius < 400) then {_radius = 650;};
    _buildings = nearestObjects [_center, _buildingTypes, _radius];
    
	if (cache_debug) then {
		{
			_mkr = createMarker [format ["box%1",random 1000],position _x];
			_mkr setMarkerShape "ICON";
			_mkr setMarkerType "hd_dot";
			_mkr setMarkerColor "ColorBlack";
		} forEach _buildings;
	};
	_buildings;
};

FUNC(buildingPositions) = {
	private ["_building","_positions"];
	_building = _this;

	_positions = [_building] call BIS_fnc_buildingPositions;
    _positions;
};

FUNC(debugMarker) = {
	PARAMS_5(_str,_pos,_shape,_type,_color);
	
	_mkr = createMarker[_str,_pos];
	_mkr setMarkerShape _shape;
	_mkr setMarkerType _type;
	_mkr setMarkerColor _color;
	_str;
};