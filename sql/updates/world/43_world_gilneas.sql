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

-- UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_prince_liam_greymane_intro' WHERE `entry` = 34850;

DELETE FROM `phase_definitions` WHERE `zoneId` = 4755;
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `phaseId`, `terrainswapmap`, `flags`, `comment`) VALUES 
('4755', '1', '0', '0', '638', '1', 'Gilneas City: Default Terrainswap');