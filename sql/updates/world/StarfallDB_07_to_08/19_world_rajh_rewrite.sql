DELETE FROM `creature_template_addon` WHERE `entry` IN (47922, 39635, 39634, 47040);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(47922, '89131'),
(39635, '74109'),
(47040, '87645');
 
-- Model Correction
UPDATE `creature_template` SET `modelid1`= 1126, `modelid2`= 11686 WHERE `entry` IN (39634, 39635, 47922);
UPDATE `creature_template` SET `modelid1`= 1126, `modelid2`= 31379 WHERE `entry`= 40835;
UPDATE `creature_template` SET `modelid1`= 1126, `modelid2`= 21072 WHERE `entry`= 47040;

-- Rajh
UPDATE `creature_template` SET `mechanic_immune_mask`= 0 | 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256 | 512 | 1024 | 2048 | 4096 | 8192 | 65536 | 524288 | 4194304 | 8388608 | 67108864 WHERE `entry` IN (39378, 48815);

-- Solar Winds
UPDATE `creature_template` SET `unit_flags`= 33554496, `faction_A`= 16, `faction_H`= 16, `minlevel`= 85, `maxlevel`= 85, `mechanic_immune_mask`= 0, `flags_extra`= 128, `scriptname`= 'npc_solar_winds' WHERE `entry`= 39635;
UPDATE `creature_template` SET `unit_flags`= 33554496, `faction_A`= 35, `faction_H`= 35, `minlevel`= 85, `maxlevel`= 85, `flags_extra`= 128, `scriptname`='' WHERE `entry`= 39634;
-- Solar Fire
UPDATE `creature_template` SET `unit_flags`= 33554496, `faction_A`= 16, `faction_H`= 16, `minlevel`= 85, `maxlevel`= 85, `flags_extra`= 128 WHERE `entry`= 47922;
-- Orb of the Sun
UPDATE `creature_template` SET `unit_flags`= 33554496, `faction_A`= 16, `faction_H`= 16, `minlevel`= 85, `maxlevel`= 85, `flags_extra`= 128, `InhabitType`= 4, `scriptname`= 'npc_orb_of_the_sun' WHERE `entry`= 40835;
UPDATE `creature_template` SET `unit_flags`= 33554496, `faction_A`= 16, `faction_H`= 16, `minlevel`= 85, `maxlevel`= 85, `flags_extra`= 128, `scriptname`= 'npc_inferno_leap' WHERE `entry`= 47040;

DELETE FROM `achievement_criteria_data` WHERE `criteria_id`= 15990;
REPLACE INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`, `ScriptName`) VALUES
(15990, 11, 0, 0, 'achievement_sun_of_a');
