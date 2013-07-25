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

-- General Phase def declarations
DELETE FROM `phase_definitions` WHERE `zoneId` = 4755;
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `phaseId`, `terrainswapmap`, `flags`, `comment`) VALUES 
('4755', '1', '0', '0', '638', '1', 'Gilneas City: Default Terrainswap');