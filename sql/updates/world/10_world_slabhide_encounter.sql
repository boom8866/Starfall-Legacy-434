REPLACE INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6070, 'at_tsc_slabhide_event');

UPDATE `creature_template` SET `InhabitType`= 5, `HoverHeight`= 11.25 WHERE `entry` IN (43214, 49538);
DELETE FROM `creature_addon` WHERE `guid` IN (222365, 222444);
DELETE FROM `creature` WHERE `guid`= 222444;

DELETE FROM `creature_template_addon` WHERE `entry`= 43214;
UPDATE `creature_template` SET `minlevel`= 84, `maxlevel`= 84, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `scriptname`= 'boss_slabhide' WHERE `entry`= 43214;
UPDATE `creature_template` SET `minlevel`= 87, `maxlevel`= 87, `faction_A`= 16, `faction_H`= 16, `exp`= 3, `unit_flags`= 33587264 WHERE `entry`= 49538;

UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `unit_flags`= 33554432, `scriptname`= 'npc_tsc_stalactit_dummy' WHERE `entry`= 43357;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `unit_flags`= 33554432 WHERE `entry`= 49659;

UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `unit_flags`= 33554432, `InhabitType`= 4, `scriptname`= 'npc_tsc_stalactit' WHERE `entry`= 43159;
UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `unit_flags`= 33554432, `InhabitType`= 4 WHERE `entry`= 49658;

UPDATE `creature_template` SET `minlevel`= 85, `maxlevel`= 85, `faction_A`= 16, `faction_H`= 16, `unit_flags`= 33554432, `scriptname`= 'npc_tsc_lava_fissure' WHERE `entry`= 43242;

REPLACE INTO `creature_template_addon` (`entry`, `auras`) VALUES
(43357, 81027),
(49659, 81027);

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES

(82530, 'spell_tsc_face_random_player'),
(92300, 'spell_tsc_crystal_storm'),
(80654, 'spell_tsc_stalactite_area');

REPLACE INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(49538, 0, 0, 0, 395, 70); -- 5 players heroic
