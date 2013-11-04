DELETE FROM `spell_area` WHERE `quest_end` IN (28876, 13621);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65053, 1703, 28876, 28876, 0, 0, 2, 1, 74, 74),
(65053, 1703, 13621, 13621, 0, 0, 2, 1, 74, 74);

DELETE FROM `creature_text` WHERE `entry`=33266;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33266,0,0,'Many thanks, hero!',12,0,100,0,0,0,'Comment'),
(33266,0,1,'For the Horde!',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '62644';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62644, 'spell_apply_salve');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=52385;
UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (33374, 52385, 52212);
UPDATE `creature` SET `position_z` = '120.0', `spawndist` = '20', `MovementType` = '1' WHERE `id` = '52385';

DELETE FROM `spell_area` WHERE `quest_end` IN (13628);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65051, 1703, 13628, 13628, 0, 0, 2, 1, 8, 8);

DELETE FROM `conditions` WHERE `SourceGroup` = '10411';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10411, 0, 0, 0, 9, 0, 13628, 0, 0, 0, 0, 0, '', 'Kadrak - Show gossip only if quest 13628 is active');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10411';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(10411, 'Truun is in need of lumber from Warsong Camp. I need to use Brutusk to haul it.', 1, 1);

DELETE FROM `creature_text` WHERE `entry`=8582;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(8582,0,0,'Very well. But be careful, Brutusk can be very spirited.',12,0,100,0,5,0,'Comment');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '33374';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(33374, 62885, 1);

UPDATE `creature_template` SET `VehicleId`=419, `npcflag`=16777216, `unit_flags`=33554436, `speed_walk`=2.14286, `speed_run`=2.14286 WHERE `entry`=33386;

-- Kadrak
SET @ENTRY := 8582;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10411,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,75,65051,7,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Spell to Invoker"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,56,45051,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Kadrak's Reins");

DELETE FROM `waypoints` WHERE `entry` = '33386';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(33386, 1, 1226.67, -2250.16, 91.75, 'Brutusk WP'),
(33386, 2, 1263.03, -2222.40, 91.95, 'Brutusk WP'),
(33386, 3, 1309.80, -2222.74, 91.67, 'Brutusk WP'),
(33386, 4, 1321.95, -2253.41, 91.60, 'Brutusk WP'),
(33386, 5, 1351.78, -2256.93, 89.96, 'Brutusk WP - Effect Jump'),
(33386, 6, 1416.51, -2258.88, 89.94, 'Brutusk WP'),
(33386, 7, 1503.24, -2381.21, 94.15, 'Brutusk WP'),
(33386, 8, 1569.83, -2443.12, 97.99, 'Brutusk WP'),
(33386, 9, 1584.77, -2485.50, 97.99, 'Brutusk WP'),
(33386, 10, 1607.79, -2501.67, 98.43, 'Brutusk WP'),
(33386, 11, 1574.59, -2542.80, 108.60, 'Brutusk WP');

-- Brutusk
SET @ENTRY := 33386;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,6,27,0,100,0,0,0,0,0,53,1,33386,0,13628,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,2,40,0,100,0,5,0,0,0,97,0,0,0,0,0,0,8,0,0,0,1360.78,-2256.62,89.96,0.04,"On WP Reached - Jump to Pos"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,11,6266,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Stomp"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,54,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - WP Pause"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,9,0,0,0,54,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - WP Pause"),
(@ENTRY,@SOURCETYPE,5,7,61,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Walk"),
(@ENTRY,@SOURCETYPE,6,0,27,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Run"),
(@ENTRY,@SOURCETYPE,7,9,61,0,100,0,0,0,0,0,33,33374,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,8,0,27,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Passive"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,28,62896,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Passenger");

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=33421;

DELETE FROM `spell_script_names` WHERE `spell_id` = '62772';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62772, 'spell_summon_gorat_spirit');

DELETE FROM `spell_area` WHERE `quest_end` IN (28493);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65053, 1703, 28493, 28493, 0, 0, 2, 1, 74, 74);

DELETE FROM `creature_template_addon` WHERE `entry` = '33304';
INSERT INTO `creature_template_addon` (`entry`, `bytes1`, `bytes2`) VALUES
(33304, 3, 257);

DELETE FROM `conditions` WHERE `SourceEntry` = '62792';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 62792, 0, 0, 31, 0, 3, 33336, 0, 0, 0, '', 'Gorat\'s Bowshot - Targeting Invisible Dummy');

DELETE FROM `creature_text` WHERE `entry` IN (33304, 33302);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33304,0,0,'Thank you, friend. I could not rest knowing that my mission had not been completed',12,0,100,0,0,0,'Comment'),
(33304,1,0,'...and that my men\'s sacrifice had not been avenged.',12,0,100,0,0,0,'Comment'),
(33304,2,0,'We must hurry, now. I sense that my time is short.',12,0,100,0,0,0,'Comment'),
(33304,3,0,'Follow me closely, and prepare for battle!',12,0,100,0,0,0,'Comment'),
(33304,4,0,'Captain Elendilad conceals himself on the island ahead, cowardly issuing orders to his underfings.',12,0,100,0,0,0,'Comment'),
(33304,5,0,'He must fall!',12,0,100,0,0,0,'Comment'),
(33304,6,0,'Show yourself elf-coward! Face your death with honor!',14,0,100,0,0,0,'(Yell)'),
(33302,0,0,'How many times must I have you killed, orc?!',14,0,100,0,0,0,'Comment'),
(33302,1,0,'Curse you, orc vermin! This forest belongs to the Kaldorei...',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '33304';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(33304, 1, 1460.44, -2045.64, 93.20, 'Spirit of Gorat WP'),
(33304, 2, 1484.81, -2081.13, 93.51, 'Spirit of Gorat WP'),
(33304, 3, 1501.19, -2087.17, 90.94, 'Spirit of Gorat WP');

-- Spirit of Gorat
SET @ENTRY := 33304;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,60,0,100,1,3500,3500,3500,3500,91,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Update - Remove Bytes (Stand up)"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,33304,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,33304,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,5,52,0,100,0,2,33304,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3 (Next WP)"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,53,0,33304,0,13621,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Start WP"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,1,0,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Talk 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,33304,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,8,0,40,0,100,0,3,0,0,0,1,6,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Talk 6"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,6,33304,0,0,11,62792,4,0,0,0,0,10,177446,33336,0,0.0,0.0,0.0,0.0,"After Talk 6 - Launch Arrow"),
(@ENTRY,@SOURCETYPE,10,0,54,0,100,0,0,0,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Unattackable"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,1,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,12,0,54,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn");

-- Captain Elendilad
SET @ENTRY := 33302;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,5,13600,14500,11,78828,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Bladestorm on Close"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,9000,120000,120000,11,78823,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Commanding Shout"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,3,4,52,0,100,0,0,33302,0,0,11,72204,4,0,0,0,0,11,33304,250,0,0.0,0.0,0.0,0.0,"After Talk 0 - Jump to Gorat"),
(@ENTRY,@SOURCETYPE,4,7,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"Link - Attack Nearest Player"),
(@ENTRY,@SOURCETYPE,5,6,6,0,100,0,0,0,0,0,1,1,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,33304,60,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Spirit of Gorat"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,19,33536,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unit Flags");

-- Gorat's Target Bunny
SET @ENTRY := 33336;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,62792,1,0,0,12,33302,4,60000,0,0,0,8,0,0,0,1514.59,-2143.57,88.53,1.91,"On Spellhit - Summon Elendilad");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10338 AND `id`=0;
DELETE FROM `conditions` WHERE `SourceGroup` = '10338';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10338, 0, 0, 0, 9, 0, 13640, 0, 0, 0, 0, 0, '', 'Demoralized Peon - Show gossip only if quest 13640 is active');

DELETE FROM `gameobject_loot_template` WHERE `item` = '45069';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(26883, 45069, -100);

DELETE FROM `creature_text` WHERE `entry`=33440;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33440,0,0,'Hmm, you don\'t look very though... but okey.',12,0,100,0,0,0,'Comment'),
(33440,0,1,'I\'m trusting you... Don't let me die!',12,0,100,0,0,0,'Comment'),
(33440,0,2,'You not gunna let me die, huh? Okay, then...',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `id`=33440;
UPDATE `creature` SET `phaseMask` = '1' WHERE `id` IN (33458, 33569);
UPDATE `creature_template` SET `unit_flags`=0, `dynamicflags`=0, `flags_extra`=0 WHERE `entry` IN (33569, 33458, 33280);

-- Demoralized Peon
SET @ENTRY := 33440;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10338,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,13,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,3,52,0,100,0,0,33440,0,0,69,0,0,0,0,0,0,19,33446,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Move To"),
(@ENTRY,@SOURCETYPE,3,5,34,0,100,0,0,0,0,0,17,234,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Movement Inform 0 - Set Emote Work"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,10338,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Npc Flag"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,6,7,60,1,100,0,8000,8000,8000,8000,11,63043,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - Spawn Wood"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,1,0,0,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Evade"),
(@ENTRY,@SOURCETYPE,8,0,7,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset NPC Flag"),
(@ENTRY,@SOURCETYPE,9,12,7,0,100,0,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Emote"),
(@ENTRY,@SOURCETYPE,10,0,60,1,65,0,2000,2000,2000,2000,45,0,1,0,0,0,0,19,33458,0,0,0.0,0.0,0.0,0.0,"Phase 1 - Update (65% chance - Set Data 1 to Ashenvale Stalker)"),
(@ENTRY,@SOURCETYPE,11,0,60,1,65,0,2000,2000,2000,2000,45,0,1,0,0,0,0,19,33569,0,0,0.0,0.0,0.0,0.0,"Phase 1 - Update (65% chance - Set Data 1 to Ashenvale Assailant)"),
(@ENTRY,@SOURCETYPE,12,0,61,0,100,0,0,0,0,0,1,1,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Passive");

-- Ashenvale Assailant
SET @ENTRY := 33569;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Invisible"),
(@ENTRY,@SOURCETYPE,1,2,38,0,100,0,0,1,0,0,47,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Visible"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,33440,0,0,0.0,0.0,0.0,0.0,"Link - Attack Peon"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,11,72204,2,0,0,0,0,19,33440,0,0,0.0,0.0,0.0,0.0,"Link - Jump to Peon");

-- Ashenvale Stalker
SET @ENTRY := 33458;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Invisible"),
(@ENTRY,@SOURCETYPE,1,2,38,0,100,0,0,1,0,0,47,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Visible"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,33440,0,0,0.0,0.0,0.0,0.0,"Link - Attack Peon"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,11,72204,2,0,0,0,0,19,33440,0,0,0.0,0.0,0.0,0.0,"Link - Jump to Peon");

DELETE FROM `creature_text` WHERE `entry` IN (33458, 33569);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33458,0,0,'No longer shall we tolerate your presence here, orc!',12,0,100,0,0,0,'Comment'),
(33569,0,0,'No longer shall we tolerate your presence here, orc!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_loot_template` WHERE `item` = '45071';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(3928, 45071, -100);

UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=19021;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10342 AND `id`=0;
DELETE FROM `conditions` WHERE `SourceGroup` = '10342';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10342, 0, 0, 0, 9, 0, 13653, 0, 0, 0, 0, 0, '', 'Gorka - Show gossip only if quest 13653 is active');

UPDATE `creature_template` SET `speed_walk`=2.14286, `speed_run`=2.14286, `VehicleId`=1155 WHERE `entry`=33509;

DELETE FROM `spell_script_names` WHERE `spell_id` = '63162';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(63162, 'spell_summon_brutusk_2');

DELETE FROM `creature_text` WHERE `entry`=33507;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33507,0,0,'Follow me, $n! Hurry!',12,0,100,0,0,0,'Comment'),
(33507,1,0,'To Mor\'shan!!',12,0,100,0,0,0,'Comment'),
(33507,2,0,'Out of our way, fools!',14,0,100,0,0,0,'Comment'),
(33507,3,0,'Unghh!!',12,0,100,0,0,0,'Comment'),
(33507,4,0,'Hurry, Brutusk, I\'m wounded!',12,0,100,0,0,0,'Comment'),
(33507,5,0,'I am... finished...',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` IN (33509, 33421);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(33421, 1, 1580.26, -2482.74, 97.99, 'Gorka WP'),
(33509, 1, 1580.88, -2476.6, 98, 'Brutusk II WP'),
(33509, 2, 1568.30, -2440.05, 97.99, 'Brutusk II WP 2'),
(33509, 3, 1477.08, -2344.80, 91.46, 'Brutusk II WP 2 - Break'),
(33509, 4, 1407.79, -2255.14, 89.91, 'Brutusk II WP 2'),
(33509, 5, 1322.84, -2255.92, 91.54, 'Brutusk II WP 2'),
(33509, 6, 1290.82, -2221.56, 91.69, 'Brutusk II WP 2'),
(33509, 7, 1253.11, -2225.13, 92.43, 'Brutusk II WP 2'),
(33509, 8, 1218.09, -2254.94, 91.78, 'Brutusk II WP 2');

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=33458;
UPDATE `creature_template` SET `unit_flags`=2 WHERE `entry`=33509;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=33569;

DELETE FROM `conditions` WHERE `SourceEntry` = '63306';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 63306, 0, 0, 31, 0, 3, 33569, 0, 0, 0, '', 'Gorka\'s Multishot - Targeting Assailant');

-- Brutusk
SET @ENTRY := 33509;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,54,0,100,0,0,0,0,0,53,0,33509,0,13653,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,3,40,0,100,0,1,0,0,0,54,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Pause"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,86,63209,0,19,33507,6,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cross Cast on Gorka"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,86,56687,0,21,10,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cross Cast on Player"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,33507,0,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Gorka"),
(@ENTRY,@SOURCETYPE,7,8,40,0,100,0,3,33509,0,0,54,17000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 of 2 - WP Pause"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,45,0,4,0,0,0,0,10,738393,33569,0,0.0,0.0,0.0,0.0,"Link - Set Data 4 to Assailant"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,4,0,0,0,45,0,20,0,0,0,0,11,33507,15,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Set Data 20 to Gorka"),
(@ENTRY,@SOURCETYPE,10,0,40,0,100,0,5,0,0,0,45,0,19,0,0,0,0,11,33569,400,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Set Data 18 to Assailant"),
(@ENTRY,@SOURCETYPE,11,13,40,0,100,0,8,0,0,0,28,63209,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - Remove Passenger 1"),
(@ENTRY,@SOURCETYPE,12,14,40,0,100,0,8,0,0,0,28,56687,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - Remove Passenger 2"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,0,0,0,0,0,45,0,30,0,0,0,0,11,33507,15,0,0.0,0.0,0.0,0.0,"Link - Set Data 30 to Gorka"),
(@ENTRY,@SOURCETYPE,14,15,61,0,100,0,0,0,0,0,33,33507,0,0,0,0,0,18,30,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,15,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Gorka
SET @ENTRY := 33507;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,2,54,0,100,0,0,0,0,0,53,1,33421,0,13653,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,1,0,0,0,11,63162,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Call Brutusk II"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,1,1,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,10,0,0,1,2,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,45,0,12,0,0,0,0,11,33569,100,0,0.0,0.0,0.0,0.0,"Link - Set Data 12 to Assailant"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,2,33507,0,0,45,0,13,0,0,0,0,10,738393,33569,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 13 to Assailant commander"),
(@ENTRY,@SOURCETYPE,8,9,38,0,100,0,0,14,0,0,1,3,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 14 - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,11,63306,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Multishot"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,20,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 20 - Talk 4"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,30,0,0,1,5,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 30 - Talk 5"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,5,33507,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Die");

-- Ashenvale Assailant
SET @ENTRY := 33569;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Invisible"),
(@ENTRY,@SOURCETYPE,1,2,38,0,100,0,0,1,0,0,47,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Visible"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,33440,0,0,0.0,0.0,0.0,0.0,"Link - Attack Peon"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,11,72204,2,0,0,0,0,19,33440,0,0,0.0,0.0,0.0,0.0,"Link - Jump to Peon"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,4,0,0,47,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Set Visible"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set React Passive"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,1,1,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,1,33569,0,0,45,0,10,0,0,0,0,11,33507,100,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 10 to Gorka"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,12,0,0,47,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 12 - Set Visible"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,13,0,0,1,2,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 13 - Talk 2"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,2,33569,0,0,1,3,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,3,33569,0,0,45,0,14,0,0,0,0,11,33507,80,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 14 to Gorka"),
(@ENTRY,@SOURCETYPE,13,0,8,0,100,0,63306,1,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,18,0,0,70,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 18 - Respawn");

-- Gorka
SET @ENTRY := 33421;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10342,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,86,63155,2,7,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Self");

UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=194612;
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `id`=194464;
UPDATE `gameobject` SET `phasemask`=1 WHERE `id`=194612;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10411' AND `id` IN (1, 2);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(10411, 1, 'I will check back with you shortly, Kadrak.', 1, 1),
(10411, 2, 'This seems urgent, Kadrak. There must be another way!.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup` = '10411' AND `SourceEntry` IN (1, 2);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10411, 1, 0, 0, 9, 0, 13712, 0, 0, 0, 0, 0, '', 'Kadrak - Show gossip only if quest 13712 is active'),
(15, 10411, 2, 0, 0, 9, 0, 13712, 0, 0, 0, 0, 0, '', 'Kadrak - Show gossip only if quest 13712 is active');

DELETE FROM `npc_text` WHERE `ID` = '85820';
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`, `WDBVerified`) VALUES
(85820, 'Brutusk is out watering the bushes right now.\r\n\r\nStay close though, $n. He should be ready for our ride to Splintertree Very soon.', NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 1);

DELETE FROM `gossip_menu` WHERE `text_id` = '85820';
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(8582, 85820);

DELETE FROM `conditions` WHERE `SourceGroup` = '8582' AND `SourceEntry` ='85820';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(14, 8582, 85820, 0, 0, 9, 0, 13712, 0, 0, 0, 0, 0, '', 'Kadrak - Show text only if quest 13712 is active');

DELETE FROM `creature_text` WHERE `entry`=33569;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33569,0,0,'No longer shall we tolerate your presence here, orc!',12,0,100,0,0,0,'Comment'),
(33569,1,0,'That\'s far enough, orc! Dismount and submit or die!',14,0,100,0,0,0,'Comment'),
(33569,2,0,'Shoot!',14,0,100,0,0,0,'Comment'),
(33569,3,0,'Kill her!',14,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '96925';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(96925, 'spell_summon_burning_blade_flyer');

UPDATE `creature_template` SET `HoverHeight`=10, `speed_run`=1.50864 WHERE `entry`=52385;

DELETE FROM `waypoints` WHERE `entry` = '52385';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(52385, 1, 1256.37, -2246.40, 234.05, 'Burning Blade Flyer WP'),
(52385, 2, 1585.97, -2353.93, 280.95, 'Burning Blade Flyer WP'),
(52385, 3, 2082.65, -2414.54, 439.11, 'Burning Blade Flyer WP'),
(52385, 4, 2313.41, -2529.04, 105.80, 'Burning Blade Flyer WP');

-- Burning Blade Flyer
SET @ENTRY := 52385;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,10,734271,8582,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move To Kadrak"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,0,0,0,0,86,46598,0,18,10,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Grab Player"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,53,1,52385,0,13712,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,4,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,33,34007,0,0,0,0,0,18,40,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,41,2500,0,0,0,0,0,1,40,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Kadrak
SET @ENTRY := 8582;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10411,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,75,65051,7,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Spell to Invoker"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,56,45051,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Kadrak's Reins"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,10411,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,6,62,0,100,0,10411,2,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,0,0,0,0,11,96925,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Burning Blade Flyer"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,1,1,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=8582;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(8582,0,0,'Very well. But be careful, Brutusk can be very spirited.',12,0,100,0,5,0,'Comment'),
(8582,1,0,'Very well, $n, I\'ll meet you there.',12,0,100,0,0,0,'Comment');

-- Burning Blade Flyer
SET @ENTRY := 52385;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,10,734271,8582,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move To Kadrak"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,0,0,0,0,86,46598,0,18,10,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Grab Player"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,53,1,52385,0,13712,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,4,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,33,34007,0,0,0,0,0,18,40,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,41,2500,0,0,0,0,0,1,40,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738386;
DELETE FROM `spell_area` WHERE `quest_end` IN (13712);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65053, 1703, 28493, 28493, 0, 0, 2, 1, 74, 74);

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=33837;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10396';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(10396, 'I have not finished yet my job. Durak, can you give me the disguise again please?', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup` = '10396';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10396, 0, 0, 0, 9, 0, 13798, 0, 0, 0, 0, 0, '', 'Durak - Show gossip only if quest 13798 is active');

UPDATE `quest_template` SET `SourceSpellId`=63704 WHERE `Id`=13798;
UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=33697;
UPDATE `creature_template` SET `scale`=2, `InhabitType`=3, `flags_extra`=128 WHERE `entry`=33965;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (33945, 33912, 33914); 

DELETE FROM `spell_script_names` WHERE `spell_id` IN (64118, 64074);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(64118, 'spell_cancel_imp_disguise'),
(64074, 'spell_throw_accursed_ore');

-- Felfire Projectile Bunny
SET @ENTRY := 33965;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,45779,16,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Fel Explosion"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,11,39429,16,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Fel Flamestrike");

-- Ashenvale Bowman
SET @ENTRY := 33914;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,33965,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Death - Give Credit");

-- Raging Ancient
SET @ENTRY := 33912;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,33969,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Death - Give Credit");

-- Ashenvale Assailant
SET @ENTRY := 33945;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,33965,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Death - Give Credit");

DELETE FROM `spell_script_names` WHERE `spell_id` = '63797';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(63797, 'spell_throw_blood');

DELETE FROM `conditions` WHERE `SourceEntry` = '63797';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 63797, 0, 0, 31, 0, 3, 33847, 0, 0, 0, '', 'Throw Blood - Forest Heart target');

-- Forest Heart Bunny (Horde)
SET @ENTRY := 33847;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,63797,1,0,0,33,33847,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Complete");

DELETE FROM `spell_script_names` WHERE `spell_id` = '63829';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(63829, 'spell_throw_signal_powder');

DELETE FROM `conditions` WHERE `SourceEntry` = '63829';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 63829, 0, 0, 31, 0, 3, 33859, 0, 0, 0, '', 'Throw Signal Powder - Target Smoldering Brazier');

-- Smoldering Brazier Bunny
SET @ENTRY := 33859;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,63829,1,0,0,12,33889,8,90000,0,0,0,8,0,0,0,2582.01,-3065.85,150.57,0.44,"On Spellhit - Summon Krok");

DELETE FROM `creature_text` WHERE `entry`=33889;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33889,0,0,'When this is over, you may want to brush up on your secrecy skills....',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_template_addon` WHERE `entry` = '33889';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(33889, '91218');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10481';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(10481, 0, 0, 'Kadrak, I lost my Secret Signal Powder. Do you have another? ', 1, 1, 0, 0, 0, 0, NULL);

DELETE FROM `conditions` WHERE `SourceGroup` = '10481';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(8, 10481, 0, 0, 0, 9, 0, 13808, 0, 0, 0, 0, 0, '', 'Kadrak - Show gossip only if quest 13808 is rewarded');

-- Kadrak
SET @ENTRY := 33837;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10481,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,56,45710,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Secret Signal Powder");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10396' AND `id` = '1';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(10396, 1, 0, 'This is terrible, Durak! Hellscream is convinced there\'s a demon behind our work here! What can we do?! ', 1, 1, 0, 0, 0, 0, NULL);

DELETE FROM `conditions` WHERE `SourceGroup` = '10396' AND `SourceEntry` = '1';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10396, 1, 0, 0, 9, 0, 13842, 0, 0, 0, 0, 0, '', 'Durak - Show gossip only if quest 13842 is active');

DELETE FROM `creature_text` WHERE `entry`=33760;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33760,0,0,'Hellscream\'s involved, you say?',12,0,100,0,0,0,'Comment'),
(33760,1,0,'Well then there is only one thing left to be done...',12,0,100,0,0,0,'Comment'),
(33760,2,0,'This is all happening sooner than I would have liked.',12,0,100,0,0,0,'Comment'),
(33760,3,0,'I am afraid that you, $n, have outgrown your usefulness...',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=177756;
UPDATE `creature_template` SET `lootid`=33760, `questItem1`=60638 WHERE `entry`=33760;

-- Durak
SET @ENTRY := 33760;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10396,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,10396,0,0,0,75,63704,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Imp Disguise"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,10396,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,10396,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,4,5,52,0,100,0,0,33760,0,0,69,0,0,0,0,0,0,8,0,0,0,2489.44,-2466.38,109.04,3.14,"After Talk 0 - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,1,33760,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,2,33760,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,9,52,0,100,0,3,33760,0,0,11,82969,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Cast Transform"),
(@ENTRY,@SOURCETYPE,9,10,61,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction 14"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,11,0,6,0,100,0,0,0,0,0,78,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Call script reset");

DELETE FROM `creature_loot_template` WHERE `item` = '60638';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(33760, 60638, -100);

UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60 WHERE `id`=34167;
UPDATE `creature_template` SET `unit_flags`=2 WHERE `entry`=34167;

DELETE FROM `conditions` WHERE `SourceEntry` = '64605';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 64605, 0, 0, 31, 0, 3, 34167, 0, 0, 0, '', 'Chop Tree - Target Ashenvale Oak');

DELETE FROM `spell_script_names` WHERE `spell_id` = '64605';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(64605, 'spell_chop_tree');

UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60 WHERE `guid`=738616;

DELETE FROM `creature_loot_template` WHERE `item` = '5490';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3711, 5490, -100, 1, 0, 1, 1),
(3712, 5490, -100, 1, 0, 1, 1),
(3713, 5490, -100, 1, 0, 1, 1),
(3715, 5490, -100, 1, 0, 1, 1),
(3717, 5490, -100, 1, 0, 1, 1),
(3944, 5490, -100, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=34603;
UPDATE `creature_template_addon` SET `auras`='65726' WHERE `entry`=34603;

DELETE FROM `creature_loot_template` WHERE `item` = '46741';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3745, 46741, -89.212, 1, 0, 1, 1),
(3743, 46741, -89.65, 1, 0, 1, 1),
(3750, 46741, -89.5858, 1, 0, 1, 1);

DELETE FROM `areatrigger_involvedrelation` WHERE `id`=2926;
-- Tideress
SET @ENTRY := 12759;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;

UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5600,8500,14500,22200,11,9672,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Tideress - In Combat - Cast Frostbolt"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,0,5,15400,21800,11,6873,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Tideress - At 0 - 5 Range - Cast Foul Chill"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,26,25,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Complete Event");

DELETE FROM `creature` WHERE `id`=12921;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=722171;

-- Chief Murgut
SET @ENTRY := 12918;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,6,0,100,1,0,0,0,0,11,20818,3,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Summon Foulweald Totem Basket on Death"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,1,0,0,0,0,1,1,3,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Text on Death"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,2232.9,-1550.3,93.24,5.09,"On Just Summoned - Move To Pos");

-- Foulweald Warrior
SET @ENTRY := 3743;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,11,0,100,1,0,0,0,0,11,6821,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Warrior - On Respawn - Cast Corrupted Strength Passive"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Warrior - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,2232.9,-1550.3,93.24,5.19,"On Just Summoned - Move To");

-- Foulweald Ursa
SET @ENTRY := 3749;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,11,0,100,1,0,0,0,0,11,6821,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Ursa - On Respawn - Cast Corrupted Strength Passive"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,1,0,0,0,0,11,7165,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Ursa - On Aggro - Cast Battle Stance"),
(@ENTRY,@SOURCETYPE,2,0,9,0,100,0,0,5,12600,24800,11,9080,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Ursa - At 0 - 5 Range - Cast Hamstring"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Ursa - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,2232.9,-1550.3,93.24,5.09,"On Just Summoned - Move To Pos");

-- Foulweald Totemic
SET @ENTRY := 3750;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,11,0,100,1,0,0,0,0,11,6823,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Totemic - On Respawn - Cast Corrupted Intellect Passive"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Foulweald Totemic - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,2232.9,-1550.3,93.24,5.09,"On Just Summoned - Move To Pos");

DELETE FROM `creature_template_addon` WHERE `entry` = '43242';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(43242, '80798');

DELETE FROM `conditions` WHERE `SourceEntry` = '65132';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 65132, 0, 0, 31, 0, 3, 43242, 0, 0, 0, '', 'Gift of the Earth - Targeting Lava Fissure');

UPDATE `quest_template` SET `RequiredNpcOrGo1`=43242 WHERE  `Id`=13880;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (65132, 65115);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(65132, 'spell_gift_of_the_earth_second'),
(65115, 'spell_gift_of_the_earth');

-- Lava Fissure
SET @ENTRY := 195002;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,120000,120000,12,43242,4,120000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Lava Fissure");

UPDATE `creature_template` SET `unit_class`=8 WHERE `entry`=34317;
UPDATE `quest_template` SET `SourceSpellId`=65171 WHERE `Id`=13884;

DELETE FROM `conditions` WHERE `SourceGroup` = '10493';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10493, 0, 0, 0, 9, 0, 13884, 0, 0, 0, 0, 0, '', 'Arctanus - Show gossip only if quest 13884 is active');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10493';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(10493, 0, 0, 'Arctanus, I lost my Freezing Surger. Can I have another?', 1, 1, 0, 0, 0, 0, NULL);

-- Arctanus
SET @ENTRY := 34292;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10493,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,10493,0,0,0,86,65171,0,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Elemental");

-- Freezing Surger
SET @ENTRY := 34317;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,2500,2500,11,65172,4,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC Cast Frostbolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,15000,15000,11,65173,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC Cast Chains of Ice"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Force Despawn (2 minutes)");

UPDATE `creature_template` SET `spell1`=65231, `spell2`=65216, `spell3`=65232, `spell4`=0, `spell5`=65233, `VehicleId`=690, `InhabitType`=4, `npcflag`=16777216 WHERE `entry`=34322;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10494 AND `id`=0;
DELETE FROM `conditions` WHERE `SourceGroup` = '10494';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10494, 2, 0, 0, 9, 0, 13888, 0, 0, 0, 0, 0, '', 'The Vortex - Show gossip only if quest 13888 is active');

-- The Vortex
SET @ENTRY := 34289;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10494,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,10494,0,0,0,86,65186,0,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Vortex");

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '34322';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(34322, 46598, 1);

DELETE FROM `waypoints` WHERE `entry` = '34322';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(34322, 1, 3086.77, -1073.75, 530.66, 'The Vortex WP');

DELETE FROM `creature` WHERE `guid`=728774;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=710107;

-- Whirling Vortex
SET @ENTRY := 34322;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,2000,2000,2000,2000,86,46598,0,7,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,53,1,34322,0,13888,120000,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP");

-- Lord Magmathar
SET @ENTRY := 34295;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,10000,20000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text OOC"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,15000,18000,75,65214,0,0,0,0,0,11,34322,200,0,0.0,0.0,0.0,0.0,"Cast Lordly Immolate"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,4000,5000,17000,20000,11,65215,2,0,0,0,0,4,0,0,0,0.0,0.0,0.0,0.0,"Cast Infernal Conflagration"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,33,34333,0,0,0,0,0,18,300,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete");

DELETE FROM `spell_script_names` WHERE `spell_id` = '65233';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(65233, 'spell_return_to_the_vortex');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=736329;

DELETE FROM `spell_area` WHERE `quest_end` IN (13879, 13888);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65176, 4690, 13879, 13879, 0, 0, 2, 1, 74, 74),
(65176, 4690, 13888, 13888, 0, 0, 2, 1, 74, 74);

DELETE FROM `conditions` WHERE `SourceEntry` = '65433';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 65433, 0, 0, 31, 0, 3, 34424, 0, 0, 0, '', 'Throw Explosive - Broken Wagon Bunny');

DELETE FROM `creature_template_addon` WHERE  `entry`=34424;

-- Broken-down Wagon Bunny
SET @ENTRY := 34424;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,65433,1,0,0,33,34424,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Complete"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,75,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Add fire"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,11,65550,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Explosion");

DELETE FROM `script_waypoint` WHERE `entry` = '12717';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(12717, 0, 3458.80, 1072.33, 2.05, 'Muglash WP'),
(12717, 1, 3516.57, 1081.86, 0.20, 'Muglash WP'),
(12717, 2, 3548.84, 1092.60, 0.43, 'Muglash WP'),
(12717, 3, 3592.83, 1118.46, 0.50, 'Muglash WP'),
(12717, 4, 3609.27, 1138.38, 7.99, 'Muglash WP'),
(12717, 5, 3618.14, 1139.66, 7.99, 'Muglash WP');

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=176758;

DELETE FROM `creature_loot_template` WHERE `item` = '46365';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3721, 46365, 89.9418, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '65203';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 65203, 0, 0, 31, 0, 3, 34329, 0, 0, 0, '', 'Throw Oil - Targeting Lightouse Bunny');

UPDATE `gameobject_template` SET `data0`=65203 WHERE `entry`=195024;
UPDATE `creature_template` SET `InhabitType`=7, `HoverHeight`=2, `flags_extra`=0 WHERE `entry`=34329;

DELETE FROM `creature_loot_template` WHERE `item` = '46392';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3816, 46392, -30.9739, 1, 0, 1, 1);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10510' AND `id` = '1';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(10510, 1, 'I am to bomb Astranaar! Captain Goggath\'s orders.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup` = '10510' AND `SourceEntry` = '1';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10510, 1, 0, 0, 9, 0, 13947, 0, 0, 0, 0, 0, '', 'Thraka - Show gossip only if quest 13947 is active');

UPDATE `creature_template` SET `spell1`=65489, `spell6`=65481, `VehicleId`=494, `npcflag`=16777216, `InhabitType`=7, `speed_walk`=2.14286, `speed_run`=2.14286 WHERE `entry`=34433;
UPDATE `creature` SET `spawndist`=50, `MovementType`=1 WHERE `id`=34160;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '34433';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(34433, 65461, 1);

DELETE FROM `waypoints` WHERE `entry` = '34433';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(34433, 0, 2849.03, -527.65, 205.80, 'Furious Windrider WP'),
(34433, 1, 2771.85, -546.69, 148.29, 'Furious Windrider WP'),
(34433, 2, 2628.70, -463.76, 124.39, 'Furious Windrider WP'),
(34433, 3, 2620.80, -379.25, 122.31, 'Furious Windrider WP'),
(34433, 4, 2662.57, -274.74, 122.38, 'Furious Windrider WP'),
(34433, 5, 2755.07, -237.50, 125.98, 'Furious Windrider WP'),
(34433, 6, 2802.54, -285.17, 128.68, 'Furious Windrider WP'),
(34433, 7, 2642.53, -473.83, 137.83, 'Furious Windrider WP'),
(34433, 8, 2726.99, -561.95, 180.95, 'Furious Windrider WP');

-- Astranaar Sentinel
SET @ENTRY := 6087;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,95826,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,95826,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
(@ENTRY,@SOURCETYPE,5,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model"),
(@ENTRY,@SOURCETYPE,6,7,9,1,100,0,30,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,0,0,10,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,9,10,61,1,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,0,11,25,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 25 Yards"),
(@ENTRY,@SOURCETYPE,12,13,61,1,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack at 25 Yards"),
(@ENTRY,@SOURCETYPE,13,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model at 25 Yards"),
(@ENTRY,@SOURCETYPE,14,15,7,1,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,15,0,61,1,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,16,0,8,0,100,0,28888,1,0,0,33,34494,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Killed Monster");

-- Astranaar Thrower
SET @ENTRY := 34132;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,28888,1,0,0,33,34492,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Killed Monster");

-- Thraka
SET @ENTRY := 34429;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10510,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,12,34433,8,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Furious Windrider");

-- Furious Wind Rider
SET @ENTRY := 34433;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,18,5,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cross Cast On Player"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,34433,1,13947,180000,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,86,64572,0,18,5,0,0,18,5,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cross Cast On Player"),
(@ENTRY,@SOURCETYPE,3,0,28,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn (2 secs)");

DELETE FROM `spell_script_names` WHERE `spell_id` = '65481';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(65481, 'spell_return_to_base');