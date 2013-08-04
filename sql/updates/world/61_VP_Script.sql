-- Script Texts
DELETE FROM `creature_text` WHERE `entry` = 43875;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(43875, 0, 0, 'YOU tread upon the sacrosanct! Mortals have no place amidst the clouds.', 14, 0, 100, 0, 0, 20867, 'Asaad'),
(43875, 1, 0, 'Al\'Akir, your servant calls for aid!', 14, 0, 100, 0, 0, 20869, 'Asaad - Aggro'),
(43875, 2, 0, '%s conjure a temporary grounding field!', 41, 0, 100, 0, 0, 20869, 'Asaad - Grounding Field'),
(43875, 3, 0, 'The winds take me!', 14, 0, 100, 0, 0, 20870, 'Asaad - Death'),
(43875, 4, 0, 'BACK to the earth with you!', 14, 0, 100, 0, 0, 20868, 'Asaad - Say Slay');

DELETE FROM `conditions` WHERE `SourceEntry` IN(87517,86911);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
('13', '7', '87517', '0', '0', '31', '0', '3', '47085', '0', '0', '0', '0', '', 'Grounding Field Visual Beams - target World Trigger'),
('13', '7', '86911', '0', '0', '31', '0', '3', '46492', '0', '0', '0', '0', '', 'Unstable Grounding Field - target World Trigger');

-- Grounding Field
UPDATE `creature_template` SET `HoverHeight`='1', `flags_extra`='130',`faction_A`='14', `faction_H`='14', `npcflag`='256', `InhabitType` = 4 WHERE `entry`='47085';
-- Unstable Grounding Field
UPDATE `creature_template` SET `HoverHeight`='1', `flags_extra`='130',`faction_A`='114',`VehicleId`='192' , `faction_H`='114', `npcflag`='256', `InhabitType` = 4, `ScriptName`='npc_field_walker' WHERE `entry`='46492';
-- Assad
UPDATE `creature_template` SET `HoverHeight`='10', `flags_extra`='1', `InhabitType` = 4,`ScriptName`='boss_asaad' WHERE `entry`='43875';

-- Slipstream
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_slipstream' WHERE `entry` = 45455;

-- Spell Script Names
DELETE FROM `spell_script_names` WHERE `spell_id` IN (85063, 87726, 87474, 87553, 93994, 88201, 87618);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('85063', 'spell_slipstream'),
('87726', 'spell_grounding_field_pulse'),
('87474', 'spell_grounding_field_pulse'),
('87553', 'spell_supremacy_of_the_storm_damage'),
('93994', 'spell_supremacy_of_the_storm_damage'),
('88201', 'spell_healing_well'),
('87618', 'spell_vp_static_energize');

REPLACE INTO `creature_template_addon` (`entry`, `Auras`) VALUES
(47085, 87725);

-- Grand Vizier Ertan Boss Loot (missing)
DELETE FROM `creature_loot_template` WHERE `entry`= 43878 AND `item`=65660;
DELETE FROM `creature_loot_template` WHERE `entry`= 43878 AND `item`=71715;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('43878', '65660', '-100', '1', '0', '1', '1'),
('43878', '71715', '0.3682', '1', '0', '1', '1');

-- Cleanup first
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (45477,45912,45915,45917,47238,45924,45919,45926,45930,45935,45932);
-- Gust Soldier
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_vp_gust_soldier', `flags_extra`='1' WHERE `entry` = 45477;
-- Wild Vortex
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_vp_wild_vortex', `flags_extra`='1' WHERE `entry` = 45912;
-- Armored Mistral
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_vp_armored_mistral', `flags_extra`='1' WHERE `entry` = 45915;
-- Cloud Prince
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_vp_cloud_prince', `flags_extra`='1' WHERE `entry` = 45917;
-- Whipping Wind
UPDATE `creature_template` SET `minlevel`='82', `maxlevel`='84', `exp`='3', `faction_A`='16', `faction_H`='16' WHERE `entry`=47238;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_vp_whipping_wind', `flags_extra`='1' WHERE `entry` = 47238;
-- Turbulent Sqall
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_vp_turbulent_squall', `flags_extra`='1' WHERE `entry` = 45924;
-- Young Storm Dragon
UPDATE `creature_template` SET `AIName` = '',`HoverHeight`='2', `InhabitType` = 4, `ScriptName` = 'npc_vp_young_storm_dragon', `flags_extra`='1' WHERE `entry` = 45919;
-- Empyrean Assassin
UPDATE `creature_template` SET `AIName` = '',`ScriptName` = 'npc_vp_empyrean_assassin', `flags_extra`='1' WHERE `entry` = 45922;
-- Servent of Asaad
UPDATE `creature_template` SET `AIName` = '',`ScriptName` = 'npc_vp_servent_of_asaad', `flags_extra`='1' WHERE `entry` = 45926;
-- Minister Air
UPDATE `creature_template` SET `AIName` = '',`ScriptName` = 'npc_vp_minister_air', `flags_extra`='1' WHERE `entry` = 45930;
-- Temple Adept
UPDATE `creature_template` SET `AIName` = '',`ScriptName` = 'npc_vp_temple_adept', `flags_extra`='1' WHERE `entry` = 45935;
-- Skyfall Star
UPDATE `creature_template` SET `AIName` = '',`ScriptName` = 'npc_vp_skyfall_star', `flags_extra`='1' WHERE `entry` = 45932;
-- Zephyr
UPDATE `creature_template` SET `speed_walk`='1.7', `speed_run`='1.7' WHERE `entry`='45991';

-- Altairus
UPDATE `creature_template` SET `AIName` = '',`HoverHeight`='4', `InhabitType` = 4,`flags_extra`='1' WHERE `entry` = 43873;
UPDATE `creature_text` SET `text`='The wind abruptly shifts direction at %s\' command!' WHERE `entry`='43873' AND `groupid`='0' AND `id`='0';
