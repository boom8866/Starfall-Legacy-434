UPDATE `quest_template` SET `PrevQuestId`=14071 WHERE  `Id`=26711;
UPDATE `quest_template` SET `PrevQuestId`=24502 WHERE  `Id`=28414;
UPDATE `creature_template` SET `gossip_menu_id`=10622 WHERE  `entry`=35128;
UPDATE `gossip_menu_option` SET `npc_option_npcflag`=1 WHERE  `menu_id`=10622 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1 WHERE  `menu_id`=10622 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE  `menu_id`=10624 AND `id`=0;
UPDATE `gossip_menu_option` SET `action_menu_id`=10621 WHERE  `menu_id`=10622 AND `id`=0;
UPDATE `creature_template` SET `VehicleId`='448' WHERE (`entry`='34840');
-- Szabo
SET @ENTRY := 35128;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10622,0,0,0,56,47046,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Gossip Select - Add Item 47046");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=10623 WHERE  `menu_id`=10624 AND `id`=0;

-- Missa Spekkies
SET @ENTRY := 35130;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10624,0,0,0,56,47047,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Gossip Select - Add Item 47047");

UPDATE `creature_template` SET `gossip_menu_id`=10620 WHERE  `entry`=35126;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=10619 WHERE  `menu_id`=10620 AND `id`=0;

-- Gappy Silberzahn
SET @ENTRY := 35126;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10620,0,0,0,56,47045,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Gossip Select - Add Item 47045");

UPDATE `creature_template` SET `modelid1`=29630, `modelid2`=29632 WHERE  `entry`=35236;
UPDATE `creature_template` SET `modelid1`=29631, `modelid2`=29633 WHERE  `entry`=35202;
UPDATE `creature_template` SET `modelid1`=29631, `modelid2`=29633 WHERE  `entry`=35238;
UPDATE `creature_template` SET `modelid1`=29630, `modelid2`=29632 WHERE  `entry`=35235;

DELETE FROM `phase_definitions` WHERE `zoneId` = 4737 AND `entry` IN (1, 2, 3, 4, 5, 6, 7);
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `phaseId`, `terrainswapmap`, `flags`, `comment`) VALUES 
(4737, 1, 3, 0, 0, 0, 'Kezan: Add Phase 3 After Take OR Complete Quest: 14153 and 14113'),
(4737, 2, 5, 0, 0, 0, 'Kezan: Add Phase 5 After Take OR Complete Quest: 14115'),
(4737, 3, 9, 0, 0, 0, 'Kezan: Add Phase 9 After Take OR Complete OR reward Quest: 14116'),
(4737, 4, 1024, 0, 0, 1, 'Kezan: SET Phase 1024 After Take OR Complete Or reward Quest:14120'),
(4737, 5, 4096, 0, 0, 1, 'Kezan: SET Phase 4096 After reward Quest: 14120'),
(4737, 6, 8192, 0, 0, 1, 'Kezan: SET Phase 8192 After Complete Or reward Quest: 14125'),
(4737, 7, 24576, 0, 0, 1, 'Kezan: SET Phase 24576 After taken or Complete Quest: 14126');

SET @ZONE := 4737;
SET @ENTRY := 1;
SET @QUEST := 14153;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 1;
SET @QUEST := 14113;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 3, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 4, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 2;
SET @QUEST := 14115;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 3;
SET @QUEST := 14116;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 3, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 4;
SET @QUEST := 14120;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 3, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 5;
SET @QUEST := 14122;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 5;
SET @QUEST := 14121;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 5;
SET @QUEST := 14124;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');


SET @ZONE := 4737;
SET @ENTRY := 5;
SET @QUEST := 14123;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 6;
SET @QUEST := 14125;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

SET @ZONE := 4737;
SET @ENTRY := 7;
SET @QUEST := 14126;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 1, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 2, 28, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL'),
(25, @ZONE, @ENTRY, 0, 3, 9, 0, @QUEST, 0, 0, 0, 0, 0, '', 'NULL');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 34830;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES (34830, 66306, 1);

UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=34830;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 48526 AND `spell_id` = 70015;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (48526, 70015, 3, 0);

UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=48526;
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (37179, 0, 0, 0, 0, 0, 26559, 0, 0, 0, 'Bilgewater Buccaneer', '', '', 0, 1, 1, 0, 0, 2204, 2204, 0, 1, 0.992063, 1, 0, 1, 2, 0, 0, 1, 2000, 2000, 1, 4, 67584, 0, 0, 0, 0, 0, 1, 2, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 69992, 0, 0, 0, 0, 0, 0, 0, 0, 582, 0, 0, '', 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 16384, 0, '', 15595);

DELETE FROM `spell_target_position` WHERE `id` = 74100;
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES (74100, 0, 648, 534.42, 3272.82, 0.227959, 4.77141);
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES (74100, 1, 648, 534.42, 3272.82, 0.227959, 4.77141);

DELETE FROM `creature_questrelation` WHERE `id` = 35053;
DELETE FROM `creature_questrelation` WHERE `id` = 35054;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES (35053, 26712);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES (35053, 14113);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES (35054, 14153);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES (35054, 26711);

DELETE FROM `spell_area` WHERE `spell` = 80818 AND `area` = 4822;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_status`) VALUES (80818, 4822, 24567, 66);

DELETE FROM `spell_target_position` WHERE `id` IN (69971, 69976, 69977, 69978, 69979, 69980, 69981, 69982);
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES 
(69971, 0, 648, -8288.62, 1479.97, 43.97413, 0.1134),
(69976, 0, 648, -8273.75, 1484.46, 43.02283, 6.2744),
(69977, 0, 648, -8288.08, 1487.72, 43.92963, 6.19029),
(69978, 0, 648, -8281.04, 1477.49, 43.38793, 0.22149),
(69979, 0, 648, -8281.33, 1490.41, 43.55893, 6.08339),
(69980, 0, 648, -8295.10, 1484.91, 44.40643, 6.26849),
(69981, 0, 648, -8294.66, 1474.68, 44.37793, 0.21589),
(69982, 0, 648, -8294.61, 1493.67, 44.70723, 6.07089);

DELETE FROM `creature_questrelation` WHERE  `id`=35175 AND `quest`=14153;
DELETE FROM `creature_questrelation` WHERE  `id`=35175 AND `quest`=26711;

DELETE FROM `spell_area` WHERE `spell` IN (66928, 66908, 66927) AND `area` = 4765;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES 
(66908, 4765, 14113, 14113, 0, 0, 2, 1, 10, 11),
(66928, 4765, 14113, 14113, 0, 0, 2, 1, 10, 11),
(66927, 4765, 14153, 14153, 0, 0, 2, 1, 10, 11),
(66908, 4765, 14153, 14153, 0, 0, 2, 1, 10, 11);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (66912, 66909, 66911, 66913);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES 
(66912, 66917, 0),
(66912, 66918, 0),
(66912, 66919, 0),
(66909, 75122, 0),
(66911, 75123, 0),
(66913, 75124, 0);

UPDATE `quest_template` SET `PrevQuestId`='14138' WHERE  `Id`=14075;
UPDATE `quest_template` SET `ExclusiveGroup`=-14069 WHERE  `Id`=14069;
UPDATE `quest_template` SET `ExclusiveGroup`=-14069 WHERE  `Id`=14075;
UPDATE `creature_template` SET `ScriptName`='' WHERE  `entry`=34830;
UPDATE `quest_template` SET `PrevQuestId`='14071' WHERE  `Id`=26712;
UPDATE `quest_template` SET `PrevQuestId`='14071' WHERE  `Id`=26711;

DELETE FROM `spell_area` WHERE `spell` = 67435 AND `area` = 4768;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`) VALUES (67435, 4768, 14123, 1, 10);
UPDATE `gameobject_template` SET `data0`=92633 WHERE  `entry`=207355;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `SourceEntry` IN(14113, 14153);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES 
(19, 14113, 1, 8, 14011),
(19, 14113, 1, 8, 14109),
(19, 14113, 1, 8, 24520),
(19, 14113, 1, 8, 14070),
(19, 14113, 2, 8, 14012),
(19, 14113, 2, 8, 14109),
(19, 14113, 2, 8, 24520),
(19, 14113, 2, 8, 14070),
(19, 14113, 3, 8, 14013),
(19, 14113, 3, 8, 14109),
(19, 14113, 3, 8, 24520),
(19, 14113, 3, 8, 14070),
(19, 14113, 4, 8, 14007),
(19, 14113, 4, 8, 14109),
(19, 14113, 4, 8, 24520),
(19, 14113, 4, 8, 14070),
(19, 14113, 5, 8, 14010),
(19, 14113, 5, 8, 14109),
(19, 14113, 5, 8, 24520),
(19, 14113, 5, 8, 14070),
(19, 14113, 6, 8, 14009),
(19, 14113, 6, 8, 14109),
(19, 14113, 6, 8, 24520),
(19, 14113, 6, 8, 14070),
(19, 14113, 7, 8, 14008),
(19, 14113, 7, 8, 14109),
(19, 14113, 7, 8, 24520),
(19, 14113, 7, 8, 14070),
(19, 14153, 1, 8, 14011),
(19, 14153, 1, 8, 14110),
(19, 14153, 1, 8, 24520),
(19, 14153, 1, 8, 14070),
(19, 14153, 2, 8, 14012),
(19, 14153, 2, 8, 14110),
(19, 14153, 2, 8, 24520),
(19, 14153, 2, 8, 14070),
(19, 14153, 3, 8, 14013),
(19, 14153, 3, 8, 14110),
(19, 14153, 3, 8, 24520),
(19, 14153, 3, 8, 14070),
(19, 14153, 4, 8, 14007),
(19, 14153, 4, 8, 14110),
(19, 14153, 4, 8, 24520),
(19, 14153, 4, 8, 14070),
(19, 14153, 5, 8, 14010),
(19, 14153, 5, 8, 14110),
(19, 14153, 5, 8, 24520),
(19, 14153, 5, 8, 14070),
(19, 14153, 6, 8, 14009),
(19, 14153, 6, 8, 14110),
(19, 14153, 6, 8, 24520),
(19, 14153, 6, 8, 14070),
(19, 14153, 7, 8, 14008),
(19, 14153, 7, 8, 14110),
(19, 14153, 7, 8, 24520),
(19, 14153, 7, 8, 14070);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 19 AND `SourceEntry` IN(26712, 26711);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES (19, 26712, 20, 0);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES (19, 26711, 20, 1);

UPDATE `quest_template` SET `PrevQuestId`='24502' WHERE  `Id`=28414;
UPDATE `quest_template` SET `ExclusiveGroup`=24503 WHERE  `Id`=28414;
UPDATE `quest_template` SET `ExclusiveGroup`=24503 WHERE  `Id`=24503;
UPDATE `creature_template_addon` SET `auras`='0' WHERE  `entry`=37602;
UPDATE `creature_template` SET `InhabitType`=7 WHERE  `entry`=37804;
UPDATE `creature` SET `phasemask` = 15364 WHERE `guid` = 787870;
UPDATE `creature` SET `phasemask` = 15364 WHERE `guid` = 787870;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES (91847, 74100, 'Kezan Teleport Lost Isle');
UPDATE `creature_template` SET `ScriptName`='npc_defiant_troll' WHERE  `entry`=34830;
UPDATE `gameobject` SET `phaseMask` = 1 WHERE `id` = 195489;
UPDATE `creature_template_addon` SET `auras`='' WHERE  `entry`=35186;
UPDATE `creature_template` SET `ScriptName`='npc_kezan_partygoer' WHERE  `entry`=35186;
UPDATE `creature_template` SET `ScriptName`='npc_kezan_partygoer' WHERE  `entry`=35175;
UPDATE `gameobject` SET `phaseMask` = 15360 WHERE `id` = 202593;
UPDATE `gameobject_template` SET `ScriptName`='go_kajamitedeposit' WHERE  `entry`=202593;
UPDATE `gameobject` SET `spawntimesecs` = 120 WHERE `id` = 202593;
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (35486, 0, 0, 0, 0, 0, 29827, 0, 0, 0, 'First Bank of Kezan Vault', '', '', 0, 1, 1, 0, 0, 35, 35, 2, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 67526, 67508, 67524, 67525, 67522, 0, 0, 0, 0, 476, 0, 0, '', 0, 3, 1, 1, 0.833333, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 'npc_first_bank_of_kezan_vault', 15595);

DELETE FROM `creature_text` WHERE `entry` = 35486;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(35486, 0, 0, 'You are breaking into your vault to retrieve your Personal Riches!', 41, 0, 100, 0, 0, 0, 'NULL'),
(35486, 1, 0, 'Use what is called for in your Goblin All-In-1-Der Belt below to crack open the vault!$B|TInterface\\Icons\\INV_Misc_EngGizmos_20.blp:64|t |TInterface\\Icons\\INV_Misc_Bomb_07.blp:64|t |TInterface\\Icons\\INV_Misc_Ear_NightElf_02.blp:64|t |TInterface\\Icons\\INV_Misc_EngGizmos_swissArmy.blp:64|t |TInterface\\Icons\\INV_Weapon_ShortBlade_21.blp:64|t', 41, 0, 100, 0, 0, 0, 'NULL'),
(35486, 2, 0, 'The vault will be cracked open once the |cFFFF2222Vault Breaking progress bar reaches 100 percent!|r$B|TInterface\\Icons\\INV_Misc_coin_02.blp:64|t$BDoing the wrong thing at the wrong time will reduce the progress of the bar.', 41, 0, 100, 0, 0, 0, 'NULL'),
(35486, 3, 0, 'Good luck!', 41, 0, 100, 0, 0, 0, 'NULL'),
(35486, 4, 0, 'Use your |cFFFF2222Kaja\'mite Drill|r!$B|TInterface\\Icons\\INV_Weapon_ShortBlade_21.blp:64|t', 41, 0, 100, 0, 2, 0, 'NULL'),
(35486, 5, 0, 'Correct!', 41, 0, 100, 0, 0, 11595, 'NULL'),
(35486, 6, 0, 'Use your |cFFFF2222Amazing G-Ray|r!$B|TInterface\\Icons\\INV_Misc_EngGizmos_20.blp:64|t', 41, 0, 100, 0, 2, 0, 'NULL'),
(35486, 7, 0, 'Use your |cFFFF2222Infinifold Lockpick|r$B|TInterface\\Icons\\INV_Misc_EngGizmos_swissArmy.blp:64|t', 41, 0, 100, 0, 2, 0, 'NULL'),
(35486, 8, 0, 'Use your |cFFFF2222Blastcrackers|r$B|TInterface\\Icons\\INV_Misc_Bomb_07.blp:64|t', 41, 0, 100, 0, 2, 0, 'NULL'),
(35486, 9, 0, 'Use your |cFFFF2222Ear-O-Scope|r!$B|TInterface\\Icons\\INV_Misc_Ear_NightElf_02.blp:64|t', 41, 0, 100, 0, 2, 0, 'NULL'),
(35486, 10, 0, 'Incorrect!', 41, 0, 100, 0, 0, 847, ''),
(35486, 11, 0, 'Success! You have your Personal Riches!$B$B|TInterface\\Icons\\INV_Misc_coin_02.blp:64|t', 41, 0, 100, 0, 0, 11595, 'NULL');

UPDATE `gameobject_template` SET `ScriptName`='go_gasbot_control_panel' WHERE  `entry`=201736;
UPDATE `creature_template` SET `ScriptName`='npc_gasbot' WHERE  `entry`=37598;
UPDATE `gameobject` SET `spawntimesecs`=30 WHERE  `guid`=778723;
UPDATE `creature_template` SET `VehicleId`=590 WHERE  `entry`=37598;
UPDATE `creature_template` SET `gossip_menu_id`=10624 WHERE  `entry`=35130;