DELETE FROM `spell_script_names` WHERE `spell_id` IN (79200, 79196, 79251, 79249, 79332, 86862, 86863, 79015);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79200, 'spell_summon_wave_south'),
(79196, 'spell_summon_wave_west'),
(79251, 'spell_gravity_well_damage_nearby'),
(79249, 'spell_gravity_well_damage'),
(79332, 'spell_gravity_well_pull'),
(86862, 'spell_seismic_shard_prepare'),
(86863, 'spell_seismic_shard_change_seat'),
(79015, 'spell_seismic_shard');

-- Set UNIT_FLAG_NOT_SELECTABLE to Gravity Well and Seismic Shard.
UPDATE `creature_template` SET `unit_flags` = 33554432 WHERE `entry` IN (42499, 42355);

DELETE FROM `spell_target_position` WHERE `id` IN (79193, 79199, 86860, 86858, 86856);
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(79193, 0, 725, 1260, 960, 205.443756, 0),
(79199, 0, 725, 1280, 1050, 210.383057, 0),
(86860, 0, 725, 1350.75, 919.133, 194.769, 0),
(86858, 0, 725, 1341.19, 913.399, 197.092, 0),
(86856, 0, 725, 1361.89, 920.219, 196.308, 0);

-- High Priestess Azil loot
UPDATE `creature_template` SET `lootid` = 42333 WHERE `entry` = 42333;
UPDATE `creature_template` SET `lootid` = 49624 WHERE `entry` = 49624;

DELETE FROM `creature_loot_template` WHERE `Entry` IN (42333, 49624);
INSERT INTO `creature_loot_template` (`Entry`, `Item`, `ChanceOrQuestChance`, `LootMode`, `GroupId`, `MinCountOrRef`, `MaxCount`) VALUES
(42333, 1, 100, 1, 0, -43406, 1),
(49624, 1, 100, 1, 0, -43407, 1),
(49624, 52078, 100, 1, 0, 1, 1);

DELETE FROM `reference_loot_template` WHERE `Entry` IN (43406, 43407);
INSERT INTO `reference_loot_template` (`Entry`, `Item`, `ChanceOrQuestChance`, `LootMode`, `GroupId`, `MinCountOrRef`, `MaxCount`) VALUES
(43406, 55812, 0, 1, 1, 1, 1),
(43406, 55813, 0, 1, 1, 1, 1),
(43406, 55814, 0, 1, 1, 1, 1),
(43406, 55815, 0, 1, 1, 1, 1),
(43406, 55816, 0, 1, 1, 1, 1),
(43406, 55817, 0, 1, 1, 1, 1),
(43406, 55818, 0, 1, 1, 1, 1),
(43406, 55819, 0, 1, 1, 1, 1),
(43406, 55820, 0, 1, 1, 1, 1),
(43406, 55821, 0, 1, 1, 1, 1),
(43407, 56343, 0, 1, 1, 1, 1),
(43407, 56344, 0, 1, 1, 1, 1),
(43407, 56345, 0, 1, 1, 1, 1),
(43407, 56346, 0, 1, 1, 1, 1),
(43407, 56347, 0, 1, 1, 1, 1),
(43407, 56348, 0, 1, 1, 1, 1),
(43407, 56349, 0, 1, 1, 1, 1),
(43407, 56350, 0, 1, 1, 1, 1),
(43407, 56351, 0, 1, 1, 1, 1),
(43407, 56352, 0, 1, 1, 1, 1);

-- Heroic template of High Priestess Azil
UPDATE `creature_template` SET `difficulty_entry_1` = 49624 WHERE `entry` = 42333;

-- Script names
UPDATE `creature_template` SET `ScriptName` = 'boss_high_priestess_azil' WHERE `entry` = 42333;
UPDATE `creature_template` SET `ScriptName` = 'npc_devout_follower' WHERE `entry` = 42428;
UPDATE `creature_template` SET `ScriptName` = 'npc_gravity_well' WHERE `entry` = 42499;
UPDATE `creature_template` SET `ScriptName` = 'npc_seismic_shard' WHERE `entry` = 42355;

DELETE FROM `creature_text` WHERE `entry`=42333;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42333,0,0,'The world will be reborn in flames!',14,0,100,0,0,21634,'Comment'),
(42333,1,0,'Witness the power bestowed upon me by Deathwing! Feel the fury of earth!',14,0,100,0,0,21628,'Comment'),
(42333,2,0,'A sacrifice for you, master.',14,0,100,0,0,21635,'Comment'),
(42333,3,0,'For my death, countless more will fall. The burden is now yours to bear.',14,0,100,0,0,21633,'Comment');

UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry` IN (42355, 49657);
UPDATE `quest_template` SET `PrevQuestId`='28815' WHERE `Id`=28814;
UPDATE `quest_template` SET `Flags`=8 WHERE `Id`=28815;