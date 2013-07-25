-- Gilneas intro

-- Setup scriptnames
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_panicked_citizen_gate' WHERE `entry` = 44086;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gilneas_city_guard_gate' WHERE `entry` = 34864;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gilnean_crow' WHERE `entry` = 50260;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_prince_liam_greymane_intro' WHERE `entry` = 34850;

-- QUEST - 14099 - Royal Orders
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_prince_liam_greymane_phase_1' WHERE `entry` = 34913;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_rampaging_worgen' WHERE `entry` in (34884,35118,35505,35627,50471);
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gilneas_city_guard' WHERE `entry` in (34916,35232,36057,41015,50474);

-- QUEST - 14098 - Evacuate the Merchant Square
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_qems_citizen' WHERE `entry` in(34981,35836);
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_qems_worgen' WHERE `entry` = 35660;

-- Quest - 14157 - Old Divisions
UPDATE `creature_text` SET `sound`='19633' WHERE `entry`='35115' AND `groupid`='0';
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_king_genn_greymane_qod' WHERE `entry` = 35112;

-- Quest By the Skin of His Teeth 14154
UPDATE `creature_template` SET `AIName` = '', `faction_A`='2179', `faction_H`='2179', `ScriptName` = 'npc_worgen_attacker' WHERE `entry` in(35167,35170,35188,35456);
UPDATE `creature_template` SET `AIName` = '',`faction_A`='2203', `faction_H`='2203', `ScriptName` = 'npc_lord_darius_crowley' WHERE `entry` = 35077;
UPDATE `creature_template_addon` SET `bytes2`='1', `emote`='27', `auras`='67503' WHERE `entry`='35077';

-- QUEST - 14159 - The Rebel Lord's Arsenal
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_josiah_avery_worgen', `mindmg`='4', `baseattacktime`='2000', `rangeattacktime`='2000', `minrangedmg`='3', `maxrangedmg`='4', `rangedattackpower`='1' WHERE `entry` = 35370;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_josiah_avery_human' WHERE `entry` = 35369;


-- QUEST - 14204 - From the Shadows
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_lorna_crowley_qfs' WHERE `entry` = 35378;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gilnean_mastiff' WHERE `entry` = 35631;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_bloodfang_lurker' WHERE `entry` = 35463;
-- Respawn time on lurkers
UPDATE `creature` SET `spawntimesecs`='12' WHERE `id`='35463';

DELETE FROM `spell_script_names` WHERE `spell_id` = 67805;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
('67805', 'spell_attack_lurker');

-- QUEST - 14293 - Save Krennan Aranas
DELETE FROM `creature_text` WHERE `entry` in (35753, 35907);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
('35753', '0', '0', 'Help!  Up here!', '14', '0', '0', '1', '0', '20921', 'Krennan Aranas In Tree'),
('35907', '0', '0', 'Thank you! I owe you my life.', '12', '0', '0', '1', '0', '20922', 'Saved Krennan Aranas');
UPDATE `creature_text` SET `sound`='19710' WHERE (`entry`='35550') AND (`groupid`='1') AND (`id`='0');
UPDATE `creature_text` SET `sound`='19709' WHERE (`entry`='35550') AND (`groupid`='1') AND (`id`='1');
UPDATE `creature_text` SET `sound`='19712' WHERE (`entry`='35550') AND (`groupid`='1') AND (`id`='2');
UPDATE `creature_template` SET `InhabitType`='4' WHERE `entry`='35753';

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=35905;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES 
('35905', '63151', '1', '0');

UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_king_genn_greymane' WHERE `entry` = 35550;
-- Short note: for camera spells with summon creature please add the right vehicle value in order to make it work this camera cannon will not work without this vehicle id
-- this was used by spell 93522 on effect summon
UPDATE `creature_template` SET `AIName` = '',`VehicleId`='1418', `ScriptName` = 'npc_cannon_camera' WHERE `entry` = 50420;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_vehicle_genn_horse' WHERE `entry` = 35905;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_saved_aranas' WHERE `entry` = 35907;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_lord_godfery_p4_8' WHERE `entry` = 35906;

-- cleanup for Save Krennan Aranas Waypoints
DELETE FROM script_waypoint WHERE entry=35905;
DELETE FROM creature WHERE id = 35753;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
('35753', '654', '1', '4', '0', '1', '-1673.33', '1344.85', '19.404', '0.24798', '10', '0', '0', '69', '79', '0', '0', '0', '0');

DELETE FROM creature_template_addon WHERE entry = 35753;
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
('35753', '1', '78037');

-- QUEST - 14294 - Time to Regroup
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_king_genn_greymane_qtr' WHERE `entry` = 35911;

-- QUEST - 14212 - Sacrifices
DELETE FROM `creature` WHERE `guid` = 777248;
UPDATE `creature_template` SET `AIName` = '', `spell1`='67063', `VehicleId`='463', `ScriptName` = 'npc_crowley_horse' WHERE `entry` = 44427;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_lord_darius_crowley_c2' WHERE `entry` = 35552;

DELETE FROM script_waypoint WHERE entry=44427;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`) VALUES
(44427, 1, -1733.16, 1657.12, 20.487, 0),
(44427, 2, -1708.57, 1668.38, 20.603, 0),
(44427, 3, -1672.35, 1654.15, 20.4894, 0),
(44427, 4, -1667.97, 1621.56, 20.4894, 0),
(44427, 5, -1695.44, 1613.45, 20.4894, 0),
(44427, 6, -1706.51, 1635.75, 20.4894, 0),
(44427, 7, -1695.11, 1672.98, 20.6713, 0),
(44427, 8, -1672.25, 1704.1, 20.4989, 0),
(44427, 9, -1647.89, 1709.19, 20.4978, 0),
(44427, 10,-1610.74, 1711.23, 22.6819, 0),
(44427, 11, -1559.29, 1707.9, 20.4853, 0),
(44427, 12, -1541.24, 1635.49, 21.23, 0),
(44427, 13, -1516.68, 1622.81, 20.4866, 0),
(44427, 14, -1441.73, 1629.45, 20.4866, 0),
(44427, 15, -1423.11, 1603.72, 20.4866, 0),
(44427, 16, -1416.55, 1583.68, 20.485, 0),
(44427, 17, -1447.75, 1538.23, 20.4857, 0),
(44427, 18, -1465.08, 1533.48, 20.4857, 0),
(44427, 19, -1500.87, 1564.68, 20.4867, 0),
(44427, 20,-1536.46, 1579.09, 27.7734, 0),
(44427, 21, -1542.2, 1573.9, 29.2055, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 35317;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES 
('35317', '66245', '1', '0');
-- General Phase def declarations
DELETE FROM `phase_definitions` WHERE `zoneId` = 4755;
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `phaseId`, `terrainswapmap`, `flags`, `comment`) VALUES 
('4755', '1', '0', '0', '638', '1', 'Gilneas City: Default Terrainswap');