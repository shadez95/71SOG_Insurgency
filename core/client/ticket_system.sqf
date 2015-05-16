/**********************************************************************************************
*      /\__  _\
*      \/_/\ \/     ___     ____  __  __  _ __    __      __    ___     ___   __  __
*  _______\ \ \   /' _ `\  /',__\/\ \/\ \/\`'__\/'_ `\  /'__`\/' _ `\  /'___\/\ \/\ \  _______
* /\______\\_\ \__/\ \/\ \/\__, `\ \ \_\ \ \ \//\ \L\ \/\  __//\ \/\ \/\ \__/\ \ \_\ \/\______\
* \/______//\_____\ \_\ \_\/\____/\ \____/\ \_\\ \____ \ \____\ \_\ \_\ \____\\/`____ \/______/
*          \/_____/\/_/\/_/\/___/  \/___/  \/_/ \/___L\ \/____/\/_/\/_/\/____/ `/___/> \
*                                                 /\____/                         /\___/
*                                                 \_/__/                          \/__/
**********************************************************************************************
*                             __    ____
*    /'\_/`\                 /\ \__/\  _`\
*   /\      \     __     __  \ \ ,_\ \ \L\ \     __       __     ____
*   \ \ \__\ \  /'__`\ /'__`\ \ \ \/\ \  _ <'  /'__`\   /'_ `\  /',__\
*    \ \ \_/\ \/\  __//\ \L\.\_\ \ \_\ \ \L\ \/\ \L\.\_/\ \L\ \/\__, `\
*     \ \_\\ \_\ \____\ \__/.\_\\ \__\\ \____/\ \__/.\_\ \____ \/\____/
*      \/_/ \/_/\/____/\/__/\/_/ \/__/ \/___/  \/__/\/_/\/___L\ \/___/
*                                                         /\____/
*                                                         \_/__/
*
*********************************************************************************************
* Insurgency ALiVE
* MeatBags.org
**************************/

//Modify these values to change the ticket count.
waitUntil {typeName (paramsArray select 2) == "SCALAR"};
TICKETS_WEST = paramsArray select 2;
publicVariable "TICKETS_WEST";

if (!isDedicated) then {
  waitUntil {!isNull player};
  sleep 1;

  if (side player == WEST) then {
      player addEventHandler["killed", { ["playedKilled",["None"]] call cba_fnc_globalEvent}];
  };
};

if (isServer) then {
  westTickets = TICKETS_WEST;
  publicVariable "westTickets";

  ["playedKilled", {
    westTickets = westTickets - 1;
    publicVariable "westTickets";
    true spawn ticket_sys_tickets;

    if (westTickets < 1) then {
      true spawn ticket_sys_opfor_win;
    };
  }] call cba_fnc_addEventHandler;
};

ticket_sys_opfor_win = {
  [-2, {[] execVM "opfor_win.sqf"}, "None"] call CBA_fnc_globalExecute;
  sleep 20;
  [-2, {endMission "END1"}, "None"] call CBA_fnc_globalExecute;
};

ticket_sys_tickets = {
[-2, {hint parseText format["<t align='center' color='#e5b348' size='1.2'><t shadow='1'shadowColor='#000000'>Insurgency</t></t>
  <img color='#ffffff' image='core\Images\img_line_ca.paa' align='center' size='0.79' />
  <t color='#eaeaea' align='center'>Blufor Reinforcements:</t> <t color='#80FF00' align='center'>%1</t>
  <img color='#ffffff' image='core\Images\img_line_ca.paa' align='center' size='0.79' />",westTickets]}, "None"] call CBA_fnc_globalExecute;

};