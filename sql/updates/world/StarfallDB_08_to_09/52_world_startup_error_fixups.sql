UPDATE `creature_template` SET `dmgschool`= 0 WHERE `dmgschool` IN (78, 36, 82, 28, 92, 27);
UPDATE `creature_template` SET `Spell1`= 0 WHERE `entry` IN (30337, 144959);
UPDATE `creature_template` SET `VehicleId`= 0 WHERE `entry` IN (33166, 42294);

UPDATE `creature_template` SET `unit_class`= 1 WHERE `entry` IN (46094);

UPDATE `creature_template` SET `unit_class`= 1 WHERE `entry` IN (3875, 4958, 48942, 48963, 46950, 49174, 52019);
UPDATE `creature_template` SET `scriptname`= '' WHERE `entry` IN (53813, 53814, 53815);
UPDATE `creature_template` SET `type`= 0 WHERE `entry`= 144952;

UPDATE `creature_template_addon` SET `auras`= '' WHERE `entry` IN (37602, 39731);
UPDATE `creature` SET `MovementType`= 1 WHERE `id` IN (48512, 42837, 42871, 42871);
UPDATE `creature` SET `equipment_id`= 0 WHERE `id` IN (32856, 34390, 1109, 462, 44894, 547, 689, 687, 32856, 505);

UPDATE `creature` SET `MovementType`= 0 WHERE `guid`= 400924;

UPDATE `creature` SET `spawnMask`= 1 WHERE `guid` IN (198685, 196349, 195606, 195896, 195897, 195549, 195900);
UPDATE `creature` SET `phaseMask`= 1 WHERE `guid` IN (775045, 775046, 775047);

DELETE FROM `creature` WHERE `id` NOT IN (SELECT `entry` FROM `creature_template`);
DELETE FROM `creature_addon` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);

UPDATE `creature` SET `MovementType`= 0 WHERE `guid` IN (837476, 837475, 837490, 837489, 837488, 837487, 837486, 837485, 837484, 837483, 837482, 837481, 837480, 837479, 837478, 837477);
UPDATE `creature` SET `MovementType`= 1 WHERE `guid`= 221938;

UPDATE `creature_template` SET `difficulty_entry_1`= 0, `difficulty_entry_2`= 0, `difficulty_entry_3`= 0 WHERE `entry` IN (53813, 53814, 53815, 47120, 42499);

UPDATE `creature_addon` SET `auras`= '88184' WHERE `guid` IN (778170, 778174, 778175,778176, 778177, 778183, 778184);
UPDATE `creature_addon` SET `auras`= '' WHERE `guid` IN (835953, 835954);
UPDATE `creature_template` SET `difficulty_entry_1`= 0 WHERE `entry`= 51350;
UPDATE `creature_template` SET `difficulty_entry_1`= 51350 WHERE `entry`= 47120;
UPDATE `creature_template` SET `difficulty_entry_1`= 0, `scriptname`= '' WHERE `entry`= 40620;
UPDATE `creature_template` SET `npcflag`= 1 WHERE `entry` IN (46224, 46225, 46226);
UPDATE `creature_template` SET `MovementType`= 0 WHERE `entry`= 45003;

UPDATE `quest_template` SET `PrevQuestId`= 0 WHERE `prevQuestId` < 0;
UPDATE `quest_template` SET `NextQuestId`= 0 WHERE `NextQuestId` < 0;

