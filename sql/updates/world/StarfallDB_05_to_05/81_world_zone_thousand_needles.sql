UPDATE `gossip_menu_option` SET `option_id`=4, `npc_option_npcflag`=8192 WHERE `menu_id`=11304 AND `id`=0;

-- Shyn
SET @ENTRY := 39898;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11304,0,0,0,33,39897,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

UPDATE `creature_template` SET `mindmg`=52, `maxdmg`=78, `attackpower`=19 WHERE `entry` IN
(39947, 48130,48131,48132,47479,47485,47487,47510,47583);

UPDATE `creature_template` SET `mindmg`=250, `maxdmg`=286, `attackpower`=60 WHERE `entry` IN (39895, 39963);

DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=25487 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=25356 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=25487 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=25478 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

-- Seyala Nightwisp
SET @ENTRY := 40367;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dyslix Silvergrub - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,12,9297,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dyslix Silvergrub - On Aggro - Summon Enraged Wyvern"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11372,2,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11372,2,0,0,12,24488,3,300000,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Hippogryph");

UPDATE `creature_template` SET `gossip_menu_id`=11372 WHERE `entry`=40367;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11372' AND `id` = '2';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11372, 2, 'Seyala, I need to get to Westreach Summit!', 1, 1);

UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `speed_walk`=5, `speed_run`=5.14286, `VehicleId`=108, `InhabitType`=4 WHERE `entry`=24488;

DELETE FROM `waypoints` WHERE `entry` = '24488';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(24488, 1, -4997.92, 73.45, 124.36, 'Cenarion War Hippogryph WP'),
(24488, 2, -5073.56, 36.61, 183.46, 'Cenarion War Hippogryph WP'),
(24488, 3, -5076.46, -111.12, 260.28, 'Cenarion War Hippogryph WP'),
(24488, 4, -4954.19, -282.98, 339.76, 'Cenarion War Hippogryph WP'),
(24488, 5, -4597.11, -808.55, 91.36, 'Cenarion War Hippogryph WP'),
(24488, 6, -4342.01, -815.53, 80.31, 'Cenarion War Hippogryph WP'),
(24488, 7, -4451.80, -600.39, 15.28, 'Cenarion War Hippogryph WP'),
(24488, 8, -4463.57, -536.05, 6.50, 'Cenarion War Hippogryph WP');

-- Cenarion War Hippogryph
SET @ENTRY := 24488;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,100,100,0,0,86,46598,0,18,10,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Update - Ride Player"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,24488,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,8,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,8,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,7,0,0,0,33,39897,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"On WP Reached- Quest Complete");

UPDATE `quest_template` SET `PrevQuestId`='0' WHERE `Id` IN (25478, 25356);

-- Motega Firemane
SET @ENTRY := 39963;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,25489,0,0,0,85,50004,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Canoe");

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0, `dynamicflags`=0 WHERE `entry`=39951;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=39947;
UPDATE `creature_template` SET `mindmg`=25, `maxdmg`=44, `attackpower`=11 WHERE `entry`=39951;
UPDATE `spell_target_position` SET `target_position_x`=-4229.58, `target_position_y`=-880.75, `target_position_z`=0.99, `target_orientation`=2.05, `target_map`=1 WHERE `id`=50005 AND `effIndex`=0;

DELETE FROM `waypoints` WHERE `entry` = '27923';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(27923, 1, -4291.73, -830.93, 0.0, 'Canoe WP'),
(27923, 2, -4418.39, -910.13, 0.0, 'Canoe WP'),
(27923, 3, -4779.51, -1188.64, 0.0, 'Canoe WP'),
(27923, 4, -5084.70, -1266.09, 0.0, 'Canoe WP'),
(27923, 5, -5290.75, -1511.80, 0.0, 'Canoe WP'),
(27923, 6, -5330.72, -1705.90, 0.0, 'Canoe WP'),
(27923, 7, -5702.31, -2235.90, 0.0, 'Canoe WP'),
(27923, 8, -5699.25, -2575.25, 0.0, 'Canoe WP'),
(27923, 9, -5553.04, -2797.29, 0.0, 'Canoe WP'),
(27923, 10, -5587.92, -2963.98, 0.0, 'Canoe WP'),
(27923, 11, -5579.43, -3152.47, 0.0, 'Canoe WP'),
(27923, 12, -5647.77, -3434.35, 0.0, 'Canoe WP'),
(27923, 13, -5787.50, -3379.25, 0.0, 'Canoe WP'),
(27923, 14, -6014.20, -3700.12, 0.0, 'Canoe WP'),
(27923, 15, -6256.54, -3767.58, 0.0, 'Canoe WP'),
(27923, 16, -6226.42, -3835.77, 0.0, 'Canoe WP'),
(27923, 17, -6203.85, -3909.83, 0.0, 'Canoe WP');

-- Lou the Cabin Boy
SET @ENTRY := 27923;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,27923,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,17,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passengers");

UPDATE `creature_template` SET `unit_flags`=768, `speed_walk`=3, `speed_run`=3.14286 WHERE `entry`=27923;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (40779, 40776, 40494, 40483, 40777, 40778);
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (40529, 40530);

UPDATE `gossip_menu_option` SET `option_id`=8, `npc_option_npcflag`=65536 WHERE `menu_id`=11435 AND `id`=1;
UPDATE `creature_template` SET `mindmg`=52, `maxdmg`=78, `attackpower`=19, `minrangedmg`=42, `maxrangedmg`=69, `rangedattackpower`=15 WHERE `entry`=40449;
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE  `menu_id`=11435 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry` IN (40529, 40530, 40483, 40494);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40529,0,0,'BAR FIGHT!',42,0,100,0,0,0,'Comment'),
(40530,0,0,'BAR FIGHT!',42,0,100,0,0,0,'Comment'),
(40483,0,0,'BAR FIGHT!',42,0,100,0,0,0,'Comment'),
(40494,0,0,'BAR FIGHT!',42,0,100,0,0,0,'Comment');

-- Goblin Bar Patron
SET @ENTRY := 40494;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,75541,1,50,50,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Creatures"),
(@ENTRY,@SOURCETYPE,2,6,61,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,4000,12500,4500,13000,5,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Drink"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,45000,45000,45000,45000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Evade"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,1,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,10,0,0.0,0.0,0.0,0.0,"Link - Attack Nearest Creature");

-- Gnome Bar Patron
SET @ENTRY := 40483;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,75541,1,50,50,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Creatures"),
(@ENTRY,@SOURCETYPE,2,6,61,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,4000,12500,4500,13000,5,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Drink"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,45000,45000,45000,45000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Evade"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,1,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,10,0,0.0,0.0,0.0,0.0,"Link - Attack Nearest Creature");

-- Goblin Bar Patron
SET @ENTRY := 40530;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,75541,1,50,50,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Creatures"),
(@ENTRY,@SOURCETYPE,2,6,61,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,4000,12500,4500,13000,5,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Drink"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,45000,45000,45000,45000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Evade"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,1,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,10,0,0.0,0.0,0.0,0.0,"Link - Attack Nearest Creature");

-- Gnome Bar Patron
SET @ENTRY := 40529;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,75541,1,50,50,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Creatures"),
(@ENTRY,@SOURCETYPE,2,6,61,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,4000,12500,4500,13000,5,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Drink"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,45000,45000,45000,45000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Evade"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,1,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,10,0,0.0,0.0,0.0,0.0,"Link - Attack Nearest Creature");

DELETE FROM `spell_script_names` WHERE `spell_id` = '75541';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75541, 'spell_bottle_of_grog');

DELETE FROM `spell_area` WHERE `spell` = '6462' AND `area` IN (5049, 5041);
INSERT INTO `spell_area` (`spell`, `area`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(6462, 5049, 1, 0, 0),
(6462, 5041, 1, 0, 0);

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=40599;

DELETE FROM `creature_text` WHERE `entry`=40599;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40599,0,0,'Rugfizzle escapes from the outhouse and gestures wildly up at the speedbarge.',16,0,100,0,14,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '75689';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75689, 'spell_pirates_crowbar');

-- Rugfizzle
SET @ENTRY := 40599;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,40599,0,0,69,0,0,0,0,0,0,8,0,0,0,-6198.04,-3907.3,0.87,0.73,"After Talk 0 - Move to Ground"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

UPDATE `quest_template` SET `Flags`=8 WHERE `Id`=25533;
UPDATE `gameobject` SET `phaseMask`=2 WHERE `id`=203009;

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '25533';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 5041, 25533, 25533, 1, 10);

UPDATE `creature` SET `phaseMask`=6, `position_x`=-6196.72, `position_y`=-3896.82, `position_z`=4.93, `orientation`=5.46 WHERE `guid`=212499;
UPDATE `creature` SET `phaseMask`=7 WHERE `guid`=212407;

DELETE FROM `creature_addon` WHERE `guid` = '212499';
INSERT INTO `creature_addon` (`guid`, `emote`) VALUES
(212499, 431);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11430';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11430, 0, 'Get me into my boat, Griznak.', 1, 1),
(11430, 1, 'Get me into my boat, Griznak.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=11430 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11430, 0, 0, 0, 9, 0, 25533, 0, 0, 0, 0, 0, '', 'Griznak - Show gossip only if quest 25533 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=11430 AND `SourceEntry` = '1';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11430, 1, 0, 0, 9, 0, 25562, 0, 0, 0, 0, 0, '', 'Griznak - Show gossip only if quest 25562 is active');

DELETE FROM `spell_target_position` WHERE `id` IN (75859, 75976);
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(75859, 1, -6193.66, -3922.13, 0.0, 5.61),
(75976, 1, -6218.27, -3918.45, 0.0, 5.51);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '40663';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(40663, 40743, 1, 1, 'Frost Cannon on Riverboat', 8, 0),
(40663, 40727, 0, 1, 'Griznak on Riverboat', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '40658';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(40658, 40745, 1, 1, 'Fire Cannon on Riverboat', 8, 0),
(40658, 40727, 0, 1, 'Griznak on Riverboat', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '40663';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(40663, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '40658';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(40658, 46598, 0);

UPDATE `creature_template` SET `InhabitType`=4, `VehicleId`=770, `spell1`=75833 WHERE `entry`=40663;
UPDATE `creature_template` SET `VehicleId`=775, `spell1`=75833 WHERE `entry`=40743;
UPDATE `quest_template` SET `RequiredSpellCast2`=75833 WHERE `Id`=25533;

UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=40743;

DELETE FROM `creature_involvedrelation` WHERE `id` = '40487' AND `quest` = '25533';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(40487, 25533);

UPDATE `creature` SET `phaseMask`=4 WHERE `id`=40707;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '40707';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(40707, 40702, 0, 1, 'Southsea Rowboat - Southsea Boarder', 8, 0),
(40707, 40705, 1, 1, 'Southsea Rowboat - Southsea Boarder', 8, 0),
(40707, 40705, 2, 1, 'Southsea Rowboat - Southsea Boarder', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '40700';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(40700, 40702, 0, 1, 'Southsea Rowboat - Southsea Boarder', 8, 0),
(40700, 40702, 1, 1, 'Southsea Rowboat - Southsea Boarder', 8, 0),
(40700, 40702, 2, 1, 'Southsea Rowboat - Southsea Boarder', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '40707';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(40707, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '40700';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(40700, 46598, 0);

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (40700, 40707, 40702, 40705);

-- Southsea Rowboat
SET @ENTRY := 40700;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,89,80,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Random Move");

UPDATE `creature_template_addon` SET `auras`='75908' WHERE `entry` IN (40700, 40707);
UPDATE `creature_template` SET `modelid1`=23258, `modelid2`=23258 WHERE `entry` IN (40707, 40700);

DELETE FROM `spell_area` WHERE `spell` = '55858' AND `quest_start` = '25562';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(55858, 400, 25562, 25562, 1, 10);

DELETE FROM `creature_template` WHERE `entry` = '40658';
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(40658, 0, 0, 0, 0, 0, 31160, 0, 0, 0, 'River Boat', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1.14286, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1048576, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75849, 0, 0, 0, 0, 0, 0, 0, 0, 770, 0, 0, '', 0, 4, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 225, 1, 0, 0, '', 15595);

DELETE FROM `waypoints` WHERE `entry` = '40658';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(40658, 1, -6019.00, -3984.63, 0.0, 'RiverBoat Thousand WP'),
(40658, 2, -6009.89, -3876.60, 0.0, 'RiverBoat Thousand WP'),
(40658, 3, -6047.84, -3755.20, 0.0, 'RiverBoat Thousand WP'),
(40658, 4, -6153.51, -3721.85, 0.0, 'RiverBoat Thousand WP'),
(40658, 5, -6238.41, -3781.60, 0.0, 'RiverBoat Thousand WP'),
(40658, 6, -6238.41, -3781.60, 0.0, 'RiverBoat Thousand WP'),
(40658, 7, -6215.56, -3915.09, 0.0, 'RiverBoat Thousand WP');

DELETE FROM `waypoints` WHERE `entry` = '40663';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(40663, 1, -6019.00, -3984.63, 0.0, 'RiverBoat Thousand WP'),
(40663, 2, -6009.89, -3876.60, 0.0, 'RiverBoat Thousand WP'),
(40663, 3, -6047.84, -3755.20, 0.0, 'RiverBoat Thousand WP'),
(40663, 4, -6153.51, -3721.85, 0.0, 'RiverBoat Thousand WP'),
(40663, 5, -6238.41, -3781.60, 0.0, 'RiverBoat Thousand WP'),
(40663, 6, -6238.41, -3781.60, 0.0, 'RiverBoat Thousand WP'),
(40663, 7, -6215.56, -3915.09, 0.0, 'RiverBoat Thousand WP');

-- River Boat
SET @ENTRY := 40658;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,40663,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0");

-- River Boat
SET @ENTRY := 40658;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,40658,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0");

-- Griznak
SET @ENTRY := 40727;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11430,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11430,0,0,0,85,75859,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Riverboat"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,40727,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11430,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,2,62,0,100,0,11430,1,0,0,85,75976,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Riverboat");

-- Southsea Rowboat
SET @ENTRY := 40707;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,66728,1,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,66728,1,0,0,33,40707,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,15000,5000,15000,11,75819,0,0,0,0,0,11,0,300,0,0.0,0.0,0.0,0.0,"OOC - Cast Cannonball");

DELETE FROM `creature_text` WHERE `entry`=40658;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40658,0,0,'Use the Leave Vehicle button to quickly get back onto the Speedbarge.',42,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=40663;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40663,0,0,'Use the Leave Vehicle button to quickly get back onto the Speedbarge.',42,0,100,0,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=40700;

DELETE FROM `creature_template` WHERE `entry` = '144958';
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(144958, 0, 0, 0, 0, 0, 999, 0, 0, 0, 'Speedbarge Cannon Trigger', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1, 1, 0, 1007, 1354, 0, 1571, 1, 2000, 2200, 1, 0, 2048, 8, 0, 0, 0, 0, 758, 1062, 220, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 4, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 15595);

-- Speedbarge Cannon Trigger
SET @ENTRY := 144958;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,8000,21000,8000,21000,11,75819,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Explosion");

SET @CGUID := 401050;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+19;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 144958, 1, 1, 4, 0, 0, -6118.86, -3828.76, 25.6538, 3.42547, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+1, 144958, 1, 1, 4, 0, 0, -6122.99, -3790.09, 25.8759, 3.74355, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+2, 144958, 1, 1, 4, 0, 0, -6029.71, -3916.85, 0.0000924768, 1.61239, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+3, 144958, 1, 1, 4, 0, 0, -6105.12, -3994.14, 0.0000924768, 5.67454, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+4, 144958, 1, 1, 4, 0, 0, -6172.8, -3952, 0.000888725, 5.28719, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+5, 144958, 1, 1, 4, 0, 0, -6140.38, -3807.35, 26.0311, 2.12761, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+6, 144958, 1, 1, 4, 0, 0, -6124.77, -3852.44, 6.17633, 2.06085, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+7, 144958, 1, 1, 4, 0, 0, -6094.23, -3849.84, 6.16837, 4.51915, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+8, 144958, 1, 1, 4, 0, 0, -6159.96, -3767.9, 51.8356, 2.25719, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+9, 144958, 1, 1, 4, 0, 0, -6152.9, -3813.3, 59.8374, 1.99014, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+10, 144958, 1, 1, 4, 0, 0, -6148.61, -3822.28, 36.4802, 2.45353, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+11, 144958, 1, 1, 4, 0, 0, -6153.33, -3820.55, 26.3474, 6.27357, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+12, 144958, 1, 1, 4, 0, 0, -6182.45, -3824, 15.2106, 5.18537, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+13, 144958, 1, 1, 4, 0, 0, -6100.48, -3864.8, 12.5568, 1.67798, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+14, 144958, 1, 1, 4, 0, 0, -6091.37, -3905.38, 11.2168, 5.83997, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+15, 144958, 1, 1, 4, 0, 0, -6162.57, -3892.45, 4.93799, 6.22303, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+16, 144958, 1, 1, 4, 0, 0, -6200.64, -3844.71, 2.45577, 1.02621, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+17, 144958, 1, 1, 4, 0, 0, -6192.01, -3867.86, 2.23442, 1.97011, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+18, 144958, 1, 1, 4, 0, 0, -6181.7, -3894.32, 4.19386, 2.28427, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+19, 40727, 1, 1, 1, 0, 1, -6125.73, -3876.78, 6.24781, 0.645772, 120, 0, 0, 1, 0, 0, 0, 0, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=736649;

DELETE FROM `creature_addon` WHERE `guid` = '736649';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(736649, '49414');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '25526';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5041, 25526, 1, 66, 0);

UPDATE `quest_template` SET `PrevQuestId`='25562' WHERE `Id`=25589;

DELETE FROM `creature_template_addon` WHERE `entry` = '40854';
INSERT INTO `creature_template_addon` (`entry`, `bytes1`) VALUES
(40854, 50397184);

UPDATE `creature_template` SET `InhabitType`=3, `HoverHeight`=2, `speed_walk`=2.4, `speed_run`=2.44286 WHERE `entry`=40854;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=40869;

-- Holdfast Cannon
SET @ENTRY := 40869;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,15000,5000,15000,11,76387,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Cannonball"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Die"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,33,40869,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Killed Monster");

UPDATE `quest_template` SET `PrevQuestId`='25562' WHERE `Id` IN (25596, 25745, 28042);
UPDATE `quest_template` SET `PrevQuestId`='25542' WHERE `Id` IN (25590, 25744, 28031);

-- Den Whomper
SET @ENTRY := 40959;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,25,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,0,5,15000,17000,11,80182,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Uppercut on Close"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,0,0,60,14000,16000,11,4955,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Fist of Stone at 60% HP"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,0,0,30,32000,35000,11,21049,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Bloodlust at 30% HP"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,76488,1,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Friendly"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,76488,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,60000,60000,60000,60000,2,230,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction"),
(@ENTRY,@SOURCETYPE,7,0,8,0,100,0,76488,1,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Flags"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,0,60000,60000,60000,60000,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Flags");

UPDATE `creature_template` SET `unit_flags`=0, `type_flags`=0 WHERE `entry`=40958;

-- Tony Two-Tusk
SET @ENTRY := 40958;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,20000,20000,11,86087,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Burning Blaze"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,86088,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Throw Dynamite"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,8000,8000,11000,11000,11,86073,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flamethrower");

UPDATE `creature_template` SET `mindmg`=58, `maxdmg`=86, `attackpower`=22 WHERE `entry`=40958;

DELETE FROM `spell_area` WHERE `spell` = '76708' AND `quest_start` = '25628';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(76708, 5028, 25628, 25704, 0, 0, 2, 1, 64, 11);

UPDATE `creature_template` SET `minlevel`=44, `maxlevel`=46, `unit_flags`=768 WHERE `entry`=41058;
UPDATE `gameobject_template` SET `data0`=76752 WHERE `entry`=203152;
UPDATE `gameobject_template` SET `data0`=76756 WHERE `entry`=203153;
UPDATE `creature_template` SET `mindmg`=55, `maxdmg`=82, `attackpower`=21 WHERE `entry` IN
(40092,40431,40959,40958,41076,41081,41082,48178,47388,48177,48178, 47389, 47390, 41196, 40063, 40062);
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry` IN (41113, 41103, 41104, 41097, 41100, 41099);

-- Sparkleshell Borer
SET @ENTRY := 41113;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,85,93455,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Sparkleshell Snapper
SET @ENTRY := 41103;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,85,93455,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Sparkleshell Tortoise
SET @ENTRY := 41104;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,85,93455,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Saltstone Basilisk
SET @ENTRY := 41097;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,85,93455,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Scorpid River
SET @ENTRY := 41100;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,85,93455,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Saltstone Crystalhide
SET @ENTRY := 41099;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,85,93455,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `gameobject_template` SET `ScriptName`='go_ajamon_portal_start' WHERE `entry`=207073;
UPDATE `gameobject_template` SET `ScriptName`='go_ajamon_portal_return' WHERE `entry`=207078;

-- "Plucky" Johnson
SET @ENTRY := 41135;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,60000,60000,11,76990,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Soul on Stick"),
(@ENTRY,@SOURCETYPE,1,2,38,0,100,0,0,1,0,0,11,77011,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Resurrection"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,11,76988,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Transform"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,33,41130,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,28,76990,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Soul"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0");

-- Mad Magus Tirth
SET @ENTRY := 41131;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,13901,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,13901,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,9,1,100,0,0,8,13600,14500,11,11975,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Arcane Explosion on Close"),
(@ENTRY,@SOURCETYPE,11,0,2,1,100,0,0,40,33000,35000,11,6742,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Bloodlust at 40% HP"),
(@ENTRY,@SOURCETYPE,12,0,0,1,100,0,5000,7000,18000,20000,11,13747,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Slow"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,0,8000,8000,8000,8000,11,76886,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Fireball Cosmetic"),
(@ENTRY,@SOURCETYPE,14,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Creatures");

DELETE FROM `creature_text` WHERE `entry`=41135;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41135,0,0,'Thank you!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41058;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41058,0,0,'I LIVE!',14,0,100,0,0,0,'Comment'),
(41058,1,0,'I need to get back. I\'m sure we\'ll cross paths again. Next time, I\'ll get to return the favor.',14,0,100,0,0,0,'Comment'),
(41058,2,0,'Bye, mon. See you later tonight.',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41060;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41060,0,0,'No you won\'t Tony. Go away. I\'m busy summoning up a date for later!.',12,0,100,0,0,0,'Comment');

-- Spirit of Tony Two-Tusk
SET @ENTRY := 41058;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,77011,1,0,0,3,0,32215,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Morph"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,77011,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,41058,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,6,8,52,0,100,0,1,41058,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,41058,0,0,45,1,0,0,0,0,0,10,213276,41060,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Ajamon"),
(@ENTRY,@SOURCETYPE,8,9,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-6079.38,-4652.6,93.85,1.36,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Ajamon Ghostcaller
SET @ENTRY := 41060;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,25704,0,0,0,11,77011,0,0,0,0,0,11,41058,60,0,0.0,0.0,0.0,0.0,"On Reward Quest - Cast Resurrection"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0");

UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id`=25704;

DELETE FROM `creature_loot_template` WHERE `item` = '62911';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(47388, 62911, -89.4561, 1, 0, 1, 1),
(48177, 62911, -100, 1, 0, 1, 1),
(48178, 62911, -89.8576, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '88479';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 88479, 0, 0, 31, 0, 3, 31047, 0, 0, 0, '', 'Targeting -> Dead Employee Trigger Tow');

UPDATE `creature_template` SET `IconName`='openhandglow', `npcflag`=1, `InhabitType`=4 WHERE `entry`=47446;

-- Dead Employee
SET @ENTRY := 47446;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,11,88479,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Cast Hook"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,69,88479,0,0,0,0,0,10,211896,31047,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Move To Boat"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,33,47446,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Despawn");

UPDATE `creature_template` SET `lootid`=48177 WHERE `entry`=48177;
UPDATE `creature_template` SET `lootid`=48178 WHERE `entry`=48178;
UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=47389;

DELETE FROM `creature_loot_template` WHERE `entry` IN (48177, 48178);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48177, 866, 0.0186, 1, 0, 1, 1),
(48177, 869, 0.0062, 1, 0, 1, 1),
(48177, 1207, 0.1222, 1, 0, 1, 1),
(48177, 1529, 0.05, 1, 0, 1, 1),
(48177, 1613, 0.1222, 1, 0, 1, 1),
(48177, 1625, 0.0186, 1, 0, 1, 1),
(48177, 1640, 0.0248, 1, 0, 1, 1),
(48177, 1716, 0.0062, 1, 0, 1, 1),
(48177, 1725, 0.2, 1, 0, 1, 1),
(48177, 3778, 0.1, 1, 0, 1, 1),
(48177, 3779, 0.2, 1, 0, 1, 1),
(48177, 3780, 0.1, 1, 0, 1, 1),
(48177, 3781, 0.05, 1, 0, 1, 1),
(48177, 3782, 0.05, 1, 0, 1, 1),
(48177, 3783, 0.1, 1, 0, 1, 1),
(48177, 3784, 0.1, 1, 0, 1, 1),
(48177, 3785, 0.05, 1, 0, 1, 1),
(48177, 3786, 0.05, 1, 0, 1, 1),
(48177, 3787, 0.1, 1, 0, 1, 1),
(48177, 3793, 0.05, 1, 0, 1, 1),
(48177, 3794, 0.1, 1, 0, 1, 1),
(48177, 3796, 0.1, 1, 0, 1, 1),
(48177, 3798, 0.1, 1, 0, 1, 1),
(48177, 3799, 0.05, 1, 0, 1, 1),
(48177, 3800, 0.1, 1, 0, 1, 1),
(48177, 3801, 0.05, 1, 0, 1, 1),
(48177, 3803, 0.1, 1, 0, 1, 1),
(48177, 3804, 0.05, 1, 0, 1, 1),
(48177, 3805, 0.1, 1, 0, 1, 1),
(48177, 3806, 0.05, 1, 0, 1, 1),
(48177, 3808, 0.05, 1, 0, 1, 1),
(48177, 3810, 0.1, 1, 0, 1, 1),
(48177, 3814, 0.05, 1, 0, 1, 1),
(48177, 3816, 0.05, 1, 0, 1, 1),
(48177, 3817, 0.05, 1, 0, 1, 1),
(48177, 3869, 0.0124, 1, 0, 1, 1),
(48177, 3873, 0.0248, 1, 0, 1, 1),
(48177, 3936, 0.05, 1, 0, 1, 1),
(48177, 3937, 0.05, 1, 0, 1, 1),
(48177, 3939, 0.05, 1, 0, 1, 1),
(48177, 3942, 0.05, 1, 0, 1, 1),
(48177, 3943, 0.05, 1, 0, 1, 1),
(48177, 3963, 0.05, 1, 0, 1, 1),
(48177, 3964, 0.05, 1, 0, 1, 1),
(48177, 3967, 0.05, 1, 0, 1, 1),
(48177, 3989, 0.2321, 1, 0, 1, 1),
(48177, 4004, 0.05, 1, 0, 1, 1),
(48177, 4006, 0.05, 1, 0, 1, 1),
(48177, 4007, 0.05, 1, 0, 1, 1),
(48177, 4018, 0.1, 1, 0, 1, 1),
(48177, 4019, 0.05, 1, 0, 1, 1),
(48177, 4022, 0.2, 1, 0, 1, 1),
(48177, 4023, 0.1, 1, 0, 1, 1),
(48177, 4025, 0.1, 1, 0, 1, 1),
(48177, 4026, 0.05, 1, 0, 1, 1),
(48177, 4087, 0.0186, 1, 0, 1, 1),
(48177, 4416, 0.0062, 1, 0, 1, 1),
(48177, 4636, 0.05, 1, 0, 1, 1),
(48177, 4637, 0.05, 1, 0, 1, 1),
(48177, 5215, 0.0744, 1, 0, 1, 1),
(48177, 5974, 0.0062, 1, 0, 1, 1),
(48177, 7084, 0.0062, 1, 0, 1, 1),
(48177, 7453, 0.0372, 1, 0, 1, 1),
(48177, 7909, 0.1, 1, 0, 1, 1),
(48177, 8196, 0.0124, 1, 0, 1, 1),
(48177, 8386, 0.0124, 1, 0, 1, 1),
(48177, 8746, 0.05, 1, 0, 1, 1),
(48177, 8747, 0.1, 1, 0, 1, 1),
(48177, 8748, 0.05, 1, 0, 1, 1),
(48177, 8749, 0.05, 1, 0, 1, 1),
(48177, 8751, 0.1, 1, 0, 1, 1),
(48177, 9293, 0.0062, 1, 0, 1, 1),
(48177, 9434, 0.0186, 1, 0, 1, 1),
(48177, 10300, 0.0062, 1, 0, 1, 1),
(48177, 10302, 0.0062, 1, 0, 1, 1),
(48177, 10603, 0.0062, 1, 0, 1, 1),
(48177, 10606, 0.0248, 1, 0, 1, 1),
(48177, 11225, 0.0122, 1, 0, 1, 1),
(48177, 11972, 0.0124, 1, 0, 1, 1),
(48177, 11986, 0.0186, 1, 0, 1, 1),
(48177, 11987, 0.0062, 1, 0, 1, 1),
(48177, 11998, 0.0124, 1, 0, 1, 1),
(48177, 12011, 0.0124, 1, 0, 1, 1),
(48177, 12022, 0.0372, 1, 0, 1, 1),
(48177, 12042, 0.0062, 1, 0, 1, 1),
(48177, 13199, 0.0248, 1, 0, 1, 1),
(48177, 14216, 0.0186, 1, 0, 1, 1),
(48177, 14220, 0.0062, 1, 0, 1, 1),
(48177, 14224, 0.0124, 1, 0, 1, 1),
(48177, 14228, 0.031, 1, 0, 1, 1),
(48177, 14234, 0.0062, 1, 0, 1, 1),
(48177, 14238, 0.0248, 1, 0, 1, 1),
(48177, 14239, 0.0062, 1, 0, 1, 1),
(48177, 14240, 0.0062, 1, 0, 1, 1),
(48177, 14241, 0.0248, 1, 0, 1, 1),
(48177, 14242, 0.0124, 1, 0, 1, 1),
(48177, 14243, 0.0248, 1, 0, 1, 1),
(48177, 14245, 0.0062, 1, 0, 1, 1),
(48177, 14250, 0.0124, 1, 0, 1, 1),
(48177, 14251, 0.0248, 1, 0, 1, 1),
(48177, 14422, 0.0124, 1, 0, 1, 1),
(48177, 14423, 0.0062, 1, 0, 1, 1),
(48177, 14424, 0.0062, 1, 0, 1, 1),
(48177, 14426, 0.0248, 1, 0, 1, 1),
(48177, 14435, 0.0062, 1, 0, 1, 1),
(48177, 14591, 0.0248, 1, 0, 1, 1),
(48177, 14598, 0.0372, 1, 0, 1, 1),
(48177, 14600, 0.0062, 1, 0, 1, 1),
(48177, 14602, 0.0124, 1, 0, 1, 1),
(48177, 14603, 0.031, 1, 0, 1, 1),
(48177, 14770, 0.0124, 1, 0, 1, 1),
(48177, 14781, 0.0062, 1, 0, 1, 1),
(48177, 14821, 0.0062, 1, 0, 1, 1),
(48177, 14826, 0.0062, 1, 0, 1, 1),
(48177, 14827, 0.0062, 1, 0, 1, 1),
(48177, 14828, 0.0124, 1, 0, 1, 1),
(48177, 14833, 0.0062, 1, 0, 1, 1),
(48177, 14834, 0.0062, 1, 0, 1, 1),
(48177, 14896, 0.0124, 1, 0, 1, 1),
(48177, 14897, 0.0372, 1, 0, 1, 1),
(48177, 14899, 0.0062, 1, 0, 1, 1),
(48177, 14900, 0.0186, 1, 0, 1, 1),
(48177, 14902, 0.0062, 1, 0, 1, 1),
(48177, 14903, 0.031, 1, 0, 1, 1),
(48177, 14940, 0.0062, 1, 0, 1, 1),
(48177, 15152, 0.0062, 1, 0, 1, 1),
(48177, 15155, 0.0062, 1, 0, 1, 1),
(48177, 15157, 0.0496, 1, 0, 1, 1),
(48177, 15158, 0.0124, 1, 0, 1, 1),
(48177, 15159, 0.0124, 1, 0, 1, 1),
(48177, 15163, 0.0062, 1, 0, 1, 1),
(48177, 15165, 0.0248, 1, 0, 1, 1),
(48177, 15214, 0.0372, 1, 0, 1, 1),
(48177, 15233, 0.0248, 1, 0, 1, 1),
(48177, 15234, 0.0122, 1, 0, 1, 1),
(48177, 15251, 0.0186, 1, 0, 1, 1),
(48177, 15261, 0.0122, 1, 0, 1, 1),
(48177, 15322, 0.0248, 1, 0, 1, 1),
(48177, 15359, 0.0186, 1, 0, 1, 1),
(48177, 15363, 0.0062, 1, 0, 1, 1),
(48177, 15366, 0.0062, 1, 0, 1, 1),
(48177, 15368, 0.0062, 1, 0, 1, 1),
(48177, 15369, 0.0062, 1, 0, 1, 1),
(48177, 15371, 0.0124, 1, 0, 1, 1),
(48177, 15374, 0.0124, 1, 0, 1, 1),
(48177, 15375, 0.0062, 1, 0, 1, 1),
(48177, 15377, 0.0062, 1, 0, 1, 1),
(48177, 15567, 0.0062, 1, 0, 1, 1),
(48177, 15569, 0.0062, 1, 0, 1, 1),
(48177, 15572, 0.0186, 1, 0, 1, 1),
(48177, 15574, 0.0124, 1, 0, 1, 1),
(48177, 15580, 0.0186, 1, 0, 1, 1),
(48177, 15582, 0.0186, 1, 0, 1, 1),
(48177, 15583, 0.0186, 1, 0, 1, 1),
(48177, 15584, 0.0186, 1, 0, 1, 1),
(48177, 15589, 0.0062, 1, 0, 1, 1),
(48177, 15592, 0.0062, 1, 0, 1, 1),
(48177, 15596, 0.0062, 1, 0, 1, 1),
(48177, 15597, 0.0496, 1, 0, 1, 1),
(48177, 15606, 0.0062, 1, 0, 1, 1),
(48177, 15612, 0.0062, 1, 0, 1, 1),
(48177, 15977, 0.0062, 1, 0, 1, 1),
(48177, 15979, 0.0186, 1, 0, 1, 1),
(48177, 20498, 31.631, 1, 0, 1, 1),
(48177, 20499, 68.369, 1, 0, 1, 1),
(48177, 21940, 0.0186, 1, 0, 1, 1),
(48177, 56200, 23.9161, 1, 0, 1, 1),
(48177, 56201, 53.1787, 1, 0, 1, 1),
(48177, 56202, 22.8369, 1, 0, 1, 1),
(48177, 62911, -100, 1, 0, 1, 1),
(48178, 866, 0.0146, 1, 0, 1, 1),
(48178, 868, 0.001, 1, 0, 1, 1),
(48178, 869, 0.001, 1, 0, 1, 1),
(48178, 870, 0.001, 1, 0, 1, 1),
(48178, 873, 0.001, 1, 0, 1, 1),
(48178, 936, 0.0019, 1, 0, 1, 1),
(48178, 1204, 0.0019, 1, 0, 1, 1),
(48178, 1207, 0.0781, 1, 0, 1, 1),
(48178, 1265, 0.001, 1, 0, 1, 1),
(48178, 1529, 0.05, 1, 0, 1, 1),
(48178, 1613, 0.05, 1, 0, 1, 1),
(48178, 1625, 0.0272, 1, 0, 1, 1),
(48178, 1640, 0.0126, 1, 0, 1, 1),
(48178, 1716, 0.001, 1, 0, 1, 1),
(48178, 1718, 0.001, 1, 0, 1, 1),
(48178, 1722, 0.0049, 1, 0, 1, 1),
(48178, 1725, 0.2, 1, 0, 1, 1),
(48178, 1980, 0.0019, 1, 0, 1, 1),
(48178, 2825, 0.001, 1, 0, 1, 1),
(48178, 3187, 0.05, 1, 0, 1, 1),
(48178, 3778, 0.05, 1, 0, 1, 1),
(48178, 3779, 0.05, 1, 0, 1, 1),
(48178, 3780, 0.05, 1, 0, 1, 1),
(48178, 3781, 0.1, 1, 0, 1, 1),
(48178, 3782, 0.05, 1, 0, 1, 1),
(48178, 3783, 0.05, 1, 0, 1, 1),
(48178, 3784, 0.1, 1, 0, 1, 1),
(48178, 3785, 0.1, 1, 0, 1, 1),
(48178, 3786, 0.1, 1, 0, 1, 1),
(48178, 3787, 0.05, 1, 0, 1, 1),
(48178, 3792, 0.05, 1, 0, 1, 1),
(48178, 3793, 0.05, 1, 0, 1, 1),
(48178, 3794, 0.1, 1, 0, 1, 1),
(48178, 3795, 0.05, 1, 0, 1, 1),
(48178, 3796, 0.05, 1, 0, 1, 1),
(48178, 3798, 0.05, 1, 0, 1, 1),
(48178, 3799, 0.05, 1, 0, 1, 1),
(48178, 3800, 0.1, 1, 0, 1, 1),
(48178, 3801, 0.05, 1, 0, 1, 1),
(48178, 3802, 0.1, 1, 0, 1, 1),
(48178, 3803, 0.05, 1, 0, 1, 1),
(48178, 3804, 0.05, 1, 0, 1, 1),
(48178, 3805, 0.05, 1, 0, 1, 1),
(48178, 3806, 0.05, 1, 0, 1, 1),
(48178, 3807, 0.05, 1, 0, 1, 1),
(48178, 3808, 0.05, 1, 0, 1, 1),
(48178, 3809, 0.05, 1, 0, 1, 1),
(48178, 3810, 0.05, 1, 0, 1, 1),
(48178, 3811, 0.05, 1, 0, 1, 1),
(48178, 3812, 0.05, 1, 0, 1, 1),
(48178, 3813, 0.05, 1, 0, 1, 1),
(48178, 3814, 0.05, 1, 0, 1, 1),
(48178, 3815, 0.05, 1, 0, 1, 1),
(48178, 3816, 0.05, 1, 0, 1, 1),
(48178, 3817, 0.05, 1, 0, 1, 1),
(48178, 3832, 0.002, 1, 0, 1, 1),
(48178, 3864, 0.1, 1, 0, 1, 1),
(48178, 3873, 0.0586, 1, 0, 1, 1),
(48178, 3874, 0.002, 1, 0, 1, 1),
(48178, 3914, 0.2, 1, 0, 1, 1),
(48178, 3936, 0.05, 1, 0, 1, 1),
(48178, 3937, 0.05, 1, 0, 1, 1),
(48178, 3938, 0.05, 1, 0, 1, 1),
(48178, 3939, 0.05, 1, 0, 1, 1),
(48178, 3940, 0.05, 1, 0, 1, 1),
(48178, 3941, 0.1, 1, 0, 1, 1),
(48178, 3942, 0.05, 1, 0, 1, 1),
(48178, 3943, 0.05, 1, 0, 1, 1),
(48178, 3961, 0.1, 1, 0, 1, 1),
(48178, 3962, 0.05, 1, 0, 1, 1),
(48178, 3963, 0.05, 1, 0, 1, 1),
(48178, 3964, 0.1, 1, 0, 1, 1),
(48178, 3965, 0.05, 1, 0, 1, 1),
(48178, 3966, 0.05, 1, 0, 1, 1),
(48178, 3967, 0.1, 1, 0, 1, 1),
(48178, 3968, 0.05, 1, 0, 1, 1),
(48178, 3986, 0.05, 1, 0, 1, 1),
(48178, 3989, 0.1, 1, 0, 1, 1),
(48178, 4000, 0.05, 1, 0, 1, 1),
(48178, 4001, 0.05, 1, 0, 1, 1),
(48178, 4002, 0.05, 1, 0, 1, 1),
(48178, 4003, 0.05, 1, 0, 1, 1),
(48178, 4004, 0.05, 1, 0, 1, 1),
(48178, 4005, 0.05, 1, 0, 1, 1),
(48178, 4006, 0.05, 1, 0, 1, 1),
(48178, 4007, 0.05, 1, 0, 1, 1),
(48178, 4017, 0.1, 1, 0, 1, 1),
(48178, 4018, 0.1, 1, 0, 1, 1),
(48178, 4019, 0.05, 1, 0, 1, 1),
(48178, 4020, 0.05, 1, 0, 1, 1),
(48178, 4021, 0.1, 1, 0, 1, 1),
(48178, 4022, 0.05, 1, 0, 1, 1),
(48178, 4023, 0.05, 1, 0, 1, 1),
(48178, 4024, 0.05, 1, 0, 1, 1),
(48178, 4025, 0.1, 1, 0, 1, 1),
(48178, 4026, 0.1, 1, 0, 1, 1),
(48178, 4087, 0.0701, 1, 0, 1, 1),
(48178, 4299, 0.05, 1, 0, 1, 1),
(48178, 4300, 0.002, 1, 0, 1, 1),
(48178, 4416, 0.0195, 1, 0, 1, 1),
(48178, 4636, 0.1, 1, 0, 1, 1),
(48178, 4637, 0.05, 1, 0, 1, 1),
(48178, 5011, 0.0097, 1, 0, 1, 1),
(48178, 5215, 0.0253, 1, 0, 1, 1),
(48178, 7084, 0.0391, 1, 0, 1, 1),
(48178, 7450, 0.002, 1, 0, 1, 1),
(48178, 7453, 0.002, 1, 0, 1, 1),
(48178, 7909, 0.05, 1, 0, 1, 1),
(48178, 7910, 0.05, 1, 0, 1, 1),
(48178, 7975, 0.05, 1, 0, 1, 1),
(48178, 7992, 0.002, 1, 0, 1, 1),
(48178, 7993, 0.0391, 1, 0, 1, 1),
(48178, 8029, 0.0195, 1, 0, 1, 1),
(48178, 8194, 0.05, 1, 0, 1, 1),
(48178, 8196, 0.0146, 1, 0, 1, 1),
(48178, 8385, 0.0391, 1, 0, 1, 1),
(48178, 8386, 0.002, 1, 0, 1, 1),
(48178, 8387, 0.05, 1, 0, 1, 1),
(48178, 8746, 0.05, 1, 0, 1, 1),
(48178, 8747, 0.05, 1, 0, 1, 1),
(48178, 8748, 0.05, 1, 0, 1, 1),
(48178, 8749, 0.1, 1, 0, 1, 1),
(48178, 8750, 0.05, 1, 0, 1, 1),
(48178, 8751, 0.05, 1, 0, 1, 1),
(48178, 9434, 0.001, 1, 0, 1, 1),
(48178, 10301, 0.05, 1, 0, 1, 1),
(48178, 10302, 0.0039, 1, 0, 1, 1),
(48178, 10312, 0.0039, 1, 0, 1, 1),
(48178, 10315, 0.05, 1, 0, 1, 1),
(48178, 10606, 0.0586, 1, 0, 1, 1),
(48178, 11972, 0.0058, 1, 0, 1, 1),
(48178, 11973, 0.0029, 1, 0, 1, 1),
(48178, 11986, 0.0078, 1, 0, 1, 1),
(48178, 11987, 0.002, 1, 0, 1, 1),
(48178, 11998, 0.0029, 1, 0, 1, 1),
(48178, 12011, 0.0088, 1, 0, 1, 1),
(48178, 12022, 0.0136, 1, 0, 1, 1),
(48178, 12030, 0.0049, 1, 0, 1, 1),
(48178, 12031, 0.0068, 1, 0, 1, 1),
(48178, 12042, 0.0029, 1, 0, 1, 1),
(48178, 13017, 0.0019, 1, 0, 1, 1),
(48178, 13020, 0.0019, 1, 0, 1, 1),
(48178, 13029, 0.0019, 1, 0, 1, 1),
(48178, 13034, 0.001, 1, 0, 1, 1),
(48178, 13038, 0.001, 1, 0, 1, 1),
(48178, 13042, 0.001, 1, 0, 1, 1),
(48178, 13068, 0.001, 1, 0, 1, 1),
(48178, 13088, 0.0029, 1, 0, 1, 1),
(48178, 13095, 0.001, 1, 0, 1, 1),
(48178, 13103, 0.0039, 1, 0, 1, 1),
(48178, 13119, 0.001, 1, 0, 1, 1),
(48178, 13145, 0.0058, 1, 0, 1, 1),
(48178, 13199, 0.0039, 1, 0, 1, 1),
(48178, 14216, 0.0049, 1, 0, 1, 1),
(48178, 14220, 0.0126, 1, 0, 1, 1),
(48178, 14225, 0.0107, 1, 0, 1, 1),
(48178, 14228, 0.0107, 1, 0, 1, 1),
(48178, 14230, 0.0029, 1, 0, 1, 1),
(48178, 14232, 0.0088, 1, 0, 1, 1),
(48178, 14233, 0.0195, 1, 0, 1, 1),
(48178, 14234, 0.0058, 1, 0, 1, 1),
(48178, 14238, 0.0146, 1, 0, 1, 1),
(48178, 14239, 0.0068, 1, 0, 1, 1),
(48178, 14240, 0.0175, 1, 0, 1, 1),
(48178, 14241, 0.0302, 1, 0, 1, 1),
(48178, 14242, 0.0029, 1, 0, 1, 1),
(48178, 14243, 0.0029, 1, 0, 1, 1),
(48178, 14245, 0.0165, 1, 0, 1, 1),
(48178, 14246, 0.001, 1, 0, 1, 1),
(48178, 14247, 0.0019, 1, 0, 1, 1),
(48178, 14248, 0.0156, 1, 0, 1, 1),
(48178, 14250, 0.0049, 1, 0, 1, 1),
(48178, 14251, 0.0175, 1, 0, 1, 1),
(48178, 14253, 0.0029, 1, 0, 1, 1),
(48178, 14255, 0.0049, 1, 0, 1, 1),
(48178, 14260, 0.0029, 1, 0, 1, 1),
(48178, 14261, 0.0029, 1, 0, 1, 1),
(48178, 14407, 0.0039, 1, 0, 1, 1),
(48178, 14413, 0.0019, 1, 0, 1, 1),
(48178, 14418, 0.0058, 1, 0, 1, 1),
(48178, 14421, 0.0263, 1, 0, 1, 1),
(48178, 14422, 0.0204, 1, 0, 1, 1),
(48178, 14423, 0.0243, 1, 0, 1, 1),
(48178, 14424, 0.0039, 1, 0, 1, 1),
(48178, 14425, 0.0049, 1, 0, 1, 1),
(48178, 14426, 0.0058, 1, 0, 1, 1),
(48178, 14428, 0.001, 1, 0, 1, 1),
(48178, 14429, 0.0039, 1, 0, 1, 1),
(48178, 14430, 0.0049, 1, 0, 1, 1),
(48178, 14431, 0.001, 1, 0, 1, 1),
(48178, 14435, 0.0029, 1, 0, 1, 1),
(48178, 14591, 0.0039, 1, 0, 1, 1),
(48178, 14592, 0.0185, 1, 0, 1, 1),
(48178, 14598, 0.0117, 1, 0, 1, 1),
(48178, 14599, 0.0136, 1, 0, 1, 1),
(48178, 14600, 0.0078, 1, 0, 1, 1),
(48178, 14602, 0.0029, 1, 0, 1, 1),
(48178, 14603, 0.0204, 1, 0, 1, 1),
(48178, 14605, 0.0029, 1, 0, 1, 1),
(48178, 14606, 0.0136, 1, 0, 1, 1),
(48178, 14654, 0.0019, 1, 0, 1, 1),
(48178, 14656, 0.0039, 1, 0, 1, 1),
(48178, 14760, 0.0019, 1, 0, 1, 1),
(48178, 14768, 0.0019, 1, 0, 1, 1),
(48178, 14769, 0.0097, 1, 0, 1, 1),
(48178, 14770, 0.0107, 1, 0, 1, 1),
(48178, 14771, 0.0049, 1, 0, 1, 1),
(48178, 14772, 0.0078, 1, 0, 1, 1),
(48178, 14773, 0.0088, 1, 0, 1, 1),
(48178, 14774, 0.0039, 1, 0, 1, 1),
(48178, 14775, 0.0019, 1, 0, 1, 1),
(48178, 14776, 0.001, 1, 0, 1, 1),
(48178, 14777, 0.0029, 1, 0, 1, 1),
(48178, 14821, 0.001, 1, 0, 1, 1),
(48178, 14826, 0.0039, 1, 0, 1, 1),
(48178, 14827, 0.0068, 1, 0, 1, 1),
(48178, 14828, 0.0019, 1, 0, 1, 1),
(48178, 14829, 0.0029, 1, 0, 1, 1),
(48178, 14830, 0.0039, 1, 0, 1, 1),
(48178, 14831, 0.0049, 1, 0, 1, 1),
(48178, 14832, 0.0049, 1, 0, 1, 1),
(48178, 14834, 0.0019, 1, 0, 1, 1),
(48178, 14838, 0.0049, 1, 0, 1, 1),
(48178, 14839, 0.0049, 1, 0, 1, 1),
(48178, 14841, 0.001, 1, 0, 1, 1),
(48178, 14895, 0.0029, 1, 0, 1, 1),
(48178, 14896, 0.0282, 1, 0, 1, 1),
(48178, 14897, 0.0204, 1, 0, 1, 1),
(48178, 14898, 0.0321, 1, 0, 1, 1),
(48178, 14899, 0.0058, 1, 0, 1, 1),
(48178, 14900, 0.0292, 1, 0, 1, 1),
(48178, 14901, 0.0097, 1, 0, 1, 1),
(48178, 14902, 0.0136, 1, 0, 1, 1),
(48178, 14903, 0.0185, 1, 0, 1, 1),
(48178, 14906, 0.0019, 1, 0, 1, 1),
(48178, 14940, 0.0019, 1, 0, 1, 1),
(48178, 14941, 0.0049, 1, 0, 1, 1),
(48178, 14942, 0.0019, 1, 0, 1, 1),
(48178, 14943, 0.001, 1, 0, 1, 1),
(48178, 14946, 0.001, 1, 0, 1, 1),
(48178, 15146, 0.0049, 1, 0, 1, 1),
(48178, 15152, 0.0068, 1, 0, 1, 1),
(48178, 15155, 0.0029, 1, 0, 1, 1),
(48178, 15157, 0.0107, 1, 0, 1, 1),
(48178, 15158, 0.0175, 1, 0, 1, 1),
(48178, 15159, 0.0136, 1, 0, 1, 1),
(48178, 15160, 0.0049, 1, 0, 1, 1),
(48178, 15161, 0.0029, 1, 0, 1, 1),
(48178, 15163, 0.0029, 1, 0, 1, 1),
(48178, 15165, 0.0117, 1, 0, 1, 1),
(48178, 15169, 0.0019, 1, 0, 1, 1),
(48178, 15214, 0.037, 1, 0, 1, 1),
(48178, 15233, 0.05, 1, 0, 1, 1),
(48178, 15234, 0.0282, 1, 0, 1, 1),
(48178, 15244, 0.0175, 1, 0, 1, 1),
(48178, 15251, 0.0175, 1, 0, 1, 1),
(48178, 15261, 0.0185, 1, 0, 1, 1),
(48178, 15322, 0.0156, 1, 0, 1, 1),
(48178, 15359, 0.0097, 1, 0, 1, 1),
(48178, 15362, 0.0049, 1, 0, 1, 1),
(48178, 15363, 0.0068, 1, 0, 1, 1),
(48178, 15366, 0.0156, 1, 0, 1, 1),
(48178, 15367, 0.0019, 1, 0, 1, 1),
(48178, 15368, 0.0078, 1, 0, 1, 1),
(48178, 15369, 0.0136, 1, 0, 1, 1),
(48178, 15371, 0.0107, 1, 0, 1, 1),
(48178, 15374, 0.0029, 1, 0, 1, 1),
(48178, 15375, 0.0019, 1, 0, 1, 1),
(48178, 15377, 0.0058, 1, 0, 1, 1),
(48178, 15567, 0.0136, 1, 0, 1, 1),
(48178, 15569, 0.0097, 1, 0, 1, 1),
(48178, 15572, 0.0029, 1, 0, 1, 1),
(48178, 15574, 0.0068, 1, 0, 1, 1),
(48178, 15576, 0.0019, 1, 0, 1, 1),
(48178, 15578, 0.0058, 1, 0, 1, 1),
(48178, 15580, 0.0117, 1, 0, 1, 1),
(48178, 15582, 0.0068, 1, 0, 1, 1),
(48178, 15583, 0.0049, 1, 0, 1, 1),
(48178, 15584, 0.0097, 1, 0, 1, 1),
(48178, 15589, 0.0185, 1, 0, 1, 1),
(48178, 15591, 0.0088, 1, 0, 1, 1),
(48178, 15593, 0.0019, 1, 0, 1, 1),
(48178, 15595, 0.0029, 1, 0, 1, 1),
(48178, 15596, 0.0243, 1, 0, 1, 1),
(48178, 15597, 0.0058, 1, 0, 1, 1),
(48178, 15600, 0.0068, 1, 0, 1, 1),
(48178, 15603, 0.0117, 1, 0, 1, 1),
(48178, 15605, 0.0039, 1, 0, 1, 1),
(48178, 15606, 0.0126, 1, 0, 1, 1),
(48178, 15607, 0.001, 1, 0, 1, 1),
(48178, 15608, 0.001, 1, 0, 1, 1),
(48178, 15610, 0.0019, 1, 0, 1, 1),
(48178, 15611, 0.0019, 1, 0, 1, 1),
(48178, 15612, 0.0049, 1, 0, 1, 1),
(48178, 15613, 0.0019, 1, 0, 1, 1),
(48178, 15963, 0.001, 1, 0, 1, 1),
(48178, 15977, 0.0019, 1, 0, 1, 1),
(48178, 15978, 0.0078, 1, 0, 1, 1),
(48178, 15979, 0.0107, 1, 0, 1, 1),
(48178, 15990, 0.001, 1, 0, 1, 1),
(48178, 20498, 38.6512, 1, 0, 1, 1),
(48178, 20499, 61.3488, 1, 0, 1, 1),
(48178, 56200, 24.5213, 1, 0, 1, 1),
(48178, 56201, 52.7623, 1, 0, 1, 1),
(48178, 56202, 22.5451, 1, 0, 1, 1),
(48178, 62911, -89.8576, 1, 0, 1, 1);

UPDATE `creature_template` SET `unit_flags2`=0, `type_flags`=0, `AIName`='', `InhabitType`=5 WHERE `entry`=47389;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=41196;

DELETE FROM `creature_text` WHERE `entry`=41196;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41196,0,0,'Kravel Koalbeard is stunned. Steal the Alliance\'s Proposal now!',42,0,100,0,0,0,'Comment');

UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id`=25757;

-- Kravel Koalbeard
SET @ENTRY := 41196;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,38557,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,38557,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw"),
(@ENTRY,@SOURCETYPE,5,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model"),
(@ENTRY,@SOURCETYPE,6,7,9,1,100,0,30,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Throw Range"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Throw Range"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,0,0,10,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Throw Range"),
(@ENTRY,@SOURCETYPE,9,10,61,1,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model when not in Throw Range"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Throw Range"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,0,11,25,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 25 Yards"),
(@ENTRY,@SOURCETYPE,12,13,61,1,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack at 25 Yards"),
(@ENTRY,@SOURCETYPE,13,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model at 25 Yards"),
(@ENTRY,@SOURCETYPE,14,15,7,1,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,15,0,61,1,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,16,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,17,18,2,0,100,1,0,10,0,0,1,0,5000,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On HP 10% - Talk 0"),
(@ENTRY,@SOURCETYPE,18,19,61,0,100,0,0,0,0,0,11,78320,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Stun"),
(@ENTRY,@SOURCETYPE,19,20,61,0,100,0,0,0,0,0,2,31,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction 31"),
(@ENTRY,@SOURCETYPE,20,0,61,0,100,0,0,0,0,0,41,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,21,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,22,0,64,0,100,0,0,0,0,0,56,55807,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit");

DELETE FROM `conditions` WHERE `SourceEntry` = '25814' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25814, 25797, 0),
(20, 8, 25814, 25799, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25814' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25814, 25797, 0),
(19, 8, 25814, 25799, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25813' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25813, 25796, 0),
(20, 8, 25813, 25798, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25813' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25813, 25796, 0),
(19, 8, 25813, 25798, 0);

UPDATE `quest_template` SET `PrevQuestId`='25791' WHERE `Id`=25797;
UPDATE `quest_template` SET `PrevQuestId`='25790' WHERE `Id`=25796;
UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=2 WHERE `Id` IN (25799, 25798);

SET @CGUID := 401070;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+20;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 25781, 1, 1, 1, 0, 0, -5459.42, -4396.97, 83.7278, 1.38352, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+1, 25781, 1, 1, 1, 0, 0, -5466.65, -4420.51, 83.7276, 0.9954, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+2, 25781, 1, 1, 1, 0, 0, -5481.89, -4444, 83.7276, 0.9954, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+3, 25781, 1, 1, 1, 0, 0, -5493.14, -4461.14, 83.7276, 0.938025, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+4, 25781, 1, 1, 1, 0, 0, -5418.12, -4270.16, 83.853, 0.935987, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+5, 25781, 1, 1, 1, 0, 0, -5427.67, -4284.87, 83.853, 1.25324, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+6, 25781, 1, 1, 1, 0, 0, -5431.34, -4299.27, 83.8581, 1.76286, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+7, 25781, 1, 1, 1, 0, 0, -5429.38, -4313.67, 83.8528, 1.46586, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+8, 25781, 1, 1, 1, 0, 0, -5300.05, -4195.38, 84.7254, 2.64872, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+9, 25781, 1, 1, 1, 0, 0, -5278.13, -4223.1, 84.7254, 5.35778, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+10, 25781, 1, 1, 1, 0, 0, -5293.41, -4213.11, 84.7254, 0.340219, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+11, 25781, 1, 1, 1, 0, 0, -5274.88, -4386.27, 90.4959, 4.4412, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+12, 25781, 1, 1, 1, 0, 0, -5273.6, -4354.92, 90.4959, 4.99582, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+13, 25781, 1, 1, 1, 0, 0, -5274.16, -4330.57, 90.4959, 4.61782, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+14, 25781, 1, 1, 1, 0, 0, -5278.68, -4311.5, 90.499, 4.71232, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+15, 25781, 1, 1, 1, 0, 0, -5322.54, -4437.5, 90.5647, 0.449045, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+16, 25781, 1, 1, 1, 0, 0, -5343.41, -4457.51, 90.5538, 1.05992, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+17, 25781, 1, 1, 1, 0, 0, -5360.55, -4472.19, 90.5546, 0.48392, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+18, 25781, 1, 1, 1, 0, 0, -5405.44, -4163.68, 84.0421, 5.59978, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+19, 25781, 1, 1, 1, 0, 0, -5421.74, -4146.85, 84.0719, 1.2471, 300, 0, 0, 8982, 3155, 0, 0, 0, 0),
(@CGUID+20, 25781, 1, 1, 1, 0, 0, -5426.41, -4173.86, 84.0353, 3.65572, 300, 0, 0, 8982, 3155, 0, 0, 0, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` = '77390';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77390, 'spell_setup_an_oil_drilling_rig');

UPDATE `creature_template` SET `minlevel`=40, `maxlevel`=40, `speed_walk`=0.001, `speed_run`=0.001 WHERE `entry`=41299;
UPDATE `creature_template` SET `mindmg`=52, `maxdmg`=78, `attackpower`=19, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (41302, 41305, 41306);

-- Oil Drilling Rig
SET @ENTRY := 41299;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,10000,10000,30000,30000,11,77385,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Mauler"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,20000,20000,40000,40000,11,77386,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Stormer"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,30000,30000,65000,65000,11,77387,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Wrangler"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,65000,65000,65000,65000,11,77401,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Success!"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,11,77588,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Explode"),
(@ENTRY,@SOURCETYPE,5,0,60,0,100,0,65000,65000,65000,65000,15,25799,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Update - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,60,0,100,0,70000,70000,70000,70000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Force Despawn"),
(@ENTRY,@SOURCETYPE,7,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,8,0,54,0,100,0,0,0,0,0,18,262144,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Stunned"),
(@ENTRY,@SOURCETYPE,9,0,60,0,100,0,65000,65000,65000,65000,15,25798,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Update - Quest Credit");

-- Galak Stormer
SET @ENTRY := 41305;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,12550,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Lightning Shield"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,9532,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Bolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,12500,12500,11,9532,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Cloud"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Player"),
(@ENTRY,@SOURCETYPE,4,0,4,0,50,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

-- Galak Wrangler
SET @ENTRY := 41306;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,3500,3500,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Player"),
(@ENTRY,@SOURCETYPE,2,0,4,0,50,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

-- Galak Mauler
SET @ENTRY := 41302;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,13730,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,12500,12500,11,74720,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Pound"),
(@ENTRY,@SOURCETYPE,2,0,4,0,50,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Player");

DELETE FROM `creature_text` WHERE `entry`=41302;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41302,0,0,'Junk shot that thing!',14,0,100,0,0,0,'Comment'),
(41302,0,1,'Find your black gold somewhere else!',0,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41306;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41306,0,0,'Junk shot that thing!',14,0,100,0,0,0,'Comment'),
(41306,0,1,'Find your black gold somewhere else!',0,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41305;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41305,0,0,'Junk shot that thing!',14,0,100,0,0,0,'Comment'),
(41305,0,1,'Find your black gold somewhere else!',0,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=4 WHERE `entry`=41299;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=41299;

UPDATE `page_text` SET `text`='As you are all well aware, we as an organization make a regular habit of combing the local reaches of the twisting nether for misplaced objects. This has turned up all manner of wayward treasure, from errant magical essences to crackling shards of mystic power to entire suits of armor and powerful weaponry. Increasingly of late, however, we have also begun to turn up garbage and refuse as well.', `next_page`=3470 WHERE `entry`=3469;
DELETE FROM `page_text` WHERE `entry` IN (3470, 3471);
INSERT INTO `page_text` (`entry`, `text`, `next_page`) VALUES
(3470, 'The sheer vastness of the nether is no excuse for using it as a garbage repository! Your Portal and Teleport spells are a great privilege and responsibility, and carelessly casting the waste from your noontime meals into a portal could have GRAVE CONSEQUENCES for all of Azeroth! Please secure all objects when traveling via portal and report any lost objects to the Kirin Tor council at once. Read the latest edition of Thinking with Portals A Memorandum on Proper Portal Usage for all information regarding portal use.', 3471),
(3471, 'If this problem grows any further out of hand, I will be forced to insist that all portal travelers relinquish their weaponry and personal hygiene supplies before embarking. And the next time my lecture notes appear among the rubbish, I will personally transform the heads of all apprentices into dunce caps!\r\n\r\n--Archmage Runeweaver', 0);

UPDATE `gameobject_template` SET `ScriptName`='go_horn_mouthpiece' WHERE `entry`=203248;
UPDATE `creature_template` SET `InhabitType`=4, `mindmg`=54, `maxdmg`=80, `attackpower`=20, `dmg_multiplier`=1.1, `unit_flags`=0, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=41334;

-- Whrrrl
SET @ENTRY := 41334;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,69,0,0,0,0,0,0,10,213015,23837,0,0.0,0.0,0.0,0.0,"On AI Init - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,49,0,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Attack Nearest Player"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,1000,1000,1000,1000,11,77435,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Cast Lightning");

DELETE FROM `spell_script_names` WHERE `spell_id` = '77327';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77327, 'spell_splithoof_brand');

DELETE FROM `creature_text` WHERE `entry`=41236;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41236,0,0,'I know who you are. I\'ll not surrender the Sacred Flame to a filthy meatbag such as yourself!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `mindmg`=58, `maxdmg`=86, `attackpower`=22, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=41236;

-- Aquarian
SET @ENTRY := 41236;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,52,0,100,0,0,41236,0,0,19,33536,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Unit Flag to 0"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-4903.3,-2283.35,70.19,0.1,"Link - Move To Pos");

-- The Ancient Brazier Fire Bunny
SET @ENTRY := 41242;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,60000,60000,60000,60000,28,70415,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Burn");

UPDATE `creature_template` SET `mindmg`=55, `maxdmg`=82, `attackpower`=21 WHERE `entry` IN
(48191, 45907, 41439, 41448, 41447, 41421, 41444, 41431, 45381, 45383, 41458, 45385);
UPDATE `creature_template` SET `lootid`=48191 WHERE `entry`=48191;

DELETE FROM `creature_loot_template` WHERE `entry` = '48191';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48191, 869, 0.011, 1, 0, 1, 1),
(48191, 1207, 0.0147, 1, 0, 1, 1),
(48191, 1265, 0.0183, 1, 0, 1, 1),
(48191, 1625, 0.0183, 1, 0, 1, 1),
(48191, 1640, 0.033, 1, 0, 1, 1),
(48191, 3395, 0.0073, 1, 0, 1, 1),
(48191, 3430, 0.0183, 1, 0, 1, 1),
(48191, 3778, 0.1, 1, 0, 1, 1),
(48191, 3779, 0.1, 1, 0, 1, 1),
(48191, 3780, 0.1, 1, 0, 1, 1),
(48191, 3781, 0.1, 1, 0, 1, 1),
(48191, 3782, 0.2, 1, 0, 1, 1),
(48191, 3783, 0.05, 1, 0, 1, 1),
(48191, 3784, 0.05, 1, 0, 1, 1),
(48191, 3785, 0.05, 1, 0, 1, 1),
(48191, 3786, 0.1, 1, 0, 1, 1),
(48191, 3787, 0.05, 1, 0, 1, 1),
(48191, 3792, 0.1, 1, 0, 1, 1),
(48191, 3793, 0.05, 1, 0, 1, 1),
(48191, 3794, 0.05, 1, 0, 1, 1),
(48191, 3795, 0.05, 1, 0, 1, 1),
(48191, 3796, 0.05, 1, 0, 1, 1),
(48191, 3798, 0.05, 1, 0, 1, 1),
(48191, 3799, 0.05, 1, 0, 1, 1),
(48191, 3800, 0.05, 1, 0, 1, 1),
(48191, 3801, 0.05, 1, 0, 1, 1),
(48191, 3802, 0.1, 1, 0, 1, 1),
(48191, 3804, 0.05, 1, 0, 1, 1),
(48191, 3805, 0.05, 1, 0, 1, 1),
(48191, 3806, 0.05, 1, 0, 1, 1),
(48191, 3807, 0.05, 1, 0, 1, 1),
(48191, 3808, 0.1, 1, 0, 1, 1),
(48191, 3809, 0.05, 1, 0, 1, 1),
(48191, 3810, 0.05, 1, 0, 1, 1),
(48191, 3811, 0.05, 1, 0, 1, 1),
(48191, 3813, 0.1, 1, 0, 1, 1),
(48191, 3815, 0.05, 1, 0, 1, 1),
(48191, 3816, 0.1, 1, 0, 1, 1),
(48191, 3820, 0.0769, 1, 0, 1, 1),
(48191, 3864, 0.05, 1, 0, 1, 1),
(48191, 3914, 0.2, 1, 0, 1, 1),
(48191, 3936, 0.05, 1, 0, 1, 1),
(48191, 3937, 0.05, 1, 0, 1, 1),
(48191, 3938, 0.1, 1, 0, 1, 1),
(48191, 3939, 0.05, 1, 0, 1, 1),
(48191, 3940, 0.05, 1, 0, 1, 1),
(48191, 3941, 0.05, 1, 0, 1, 1),
(48191, 3942, 0.1, 1, 0, 1, 1),
(48191, 3943, 0.05, 1, 0, 1, 1),
(48191, 3961, 0.1, 1, 0, 1, 1),
(48191, 3962, 0.05, 1, 0, 1, 1),
(48191, 3963, 0.05, 1, 0, 1, 1),
(48191, 3964, 0.05, 1, 0, 1, 1),
(48191, 3965, 0.05, 1, 0, 1, 1),
(48191, 3966, 0.1, 1, 0, 1, 1),
(48191, 3986, 0.1, 1, 0, 1, 1),
(48191, 3989, 0.05, 1, 0, 1, 1),
(48191, 4002, 0.05, 1, 0, 1, 1),
(48191, 4003, 0.05, 1, 0, 1, 1),
(48191, 4004, 0.05, 1, 0, 1, 1),
(48191, 4006, 0.05, 1, 0, 1, 1),
(48191, 4007, 0.05, 1, 0, 1, 1),
(48191, 4017, 0.05, 1, 0, 1, 1),
(48191, 4018, 0.05, 1, 0, 1, 1),
(48191, 4019, 0.05, 1, 0, 1, 1),
(48191, 4020, 0.05, 1, 0, 1, 1),
(48191, 4021, 0.05, 1, 0, 1, 1),
(48191, 4022, 0.05, 1, 0, 1, 1),
(48191, 4023, 0.1, 1, 0, 1, 1),
(48191, 4024, 0.05, 1, 0, 1, 1),
(48191, 4025, 0.05, 1, 0, 1, 1),
(48191, 4026, 0.05, 1, 0, 1, 1),
(48191, 4087, 0.0367, 1, 0, 1, 1),
(48191, 4353, 0.0073, 1, 0, 1, 1),
(48191, 4416, 0.0073, 1, 0, 1, 1),
(48191, 4636, 0.1, 1, 0, 1, 1),
(48191, 4637, 0.05, 1, 0, 1, 1),
(48191, 5011, 0.0183, 1, 0, 1, 1),
(48191, 5215, 0.0514, 1, 0, 1, 1),
(48191, 5974, 0.0147, 1, 0, 1, 1),
(48191, 7453, 0.011, 1, 0, 1, 1),
(48191, 7909, 0.05, 1, 0, 1, 1),
(48191, 7992, 0.0073, 1, 0, 1, 1),
(48191, 8169, 1.2712, 1, 0, 1, 1),
(48191, 8194, 0.011, 1, 0, 1, 1),
(48191, 8196, 0.0293, 1, 0, 1, 1),
(48191, 8385, 0.0769, 1, 0, 1, 1),
(48191, 8386, 0.0077, 1, 0, 1, 1),
(48191, 8390, 0.0073, 1, 0, 1, 1),
(48191, 8747, 0.05, 1, 0, 1, 1),
(48191, 8750, 0.05, 1, 0, 1, 1),
(48191, 8751, 0.1, 1, 0, 1, 1),
(48191, 9434, 0.0037, 1, 0, 1, 1),
(48191, 10300, 0.0077, 1, 0, 1, 1),
(48191, 10601, 0.0769, 1, 0, 1, 1),
(48191, 11972, 0.011, 1, 0, 1, 1),
(48191, 11973, 0.0037, 1, 0, 1, 1),
(48191, 11987, 0.011, 1, 0, 1, 1),
(48191, 11998, 0.0037, 1, 0, 1, 1),
(48191, 12011, 0.033, 1, 0, 1, 1),
(48191, 12022, 0.0037, 1, 0, 1, 1),
(48191, 12030, 0.0037, 1, 0, 1, 1),
(48191, 12042, 0.011, 1, 0, 1, 1),
(48191, 13038, 0.0037, 1, 0, 1, 1),
(48191, 13081, 0.0037, 1, 0, 1, 1),
(48191, 13100, 0.0037, 1, 0, 1, 1),
(48191, 13129, 0.011, 1, 0, 1, 1),
(48191, 13138, 0.0073, 1, 0, 1, 1),
(48191, 13145, 0.0073, 1, 0, 1, 1),
(48191, 13199, 0.0183, 1, 0, 1, 1),
(48191, 14216, 0.011, 1, 0, 1, 1),
(48191, 14220, 0.0293, 1, 0, 1, 1),
(48191, 14224, 0.0073, 1, 0, 1, 1),
(48191, 14225, 0.0147, 1, 0, 1, 1),
(48191, 14228, 0.022, 1, 0, 1, 1),
(48191, 14230, 0.0037, 1, 0, 1, 1),
(48191, 14232, 0.0037, 1, 0, 1, 1),
(48191, 14233, 0.033, 1, 0, 1, 1),
(48191, 14238, 0.011, 1, 0, 1, 1),
(48191, 14239, 0.0073, 1, 0, 1, 1),
(48191, 14240, 0.0147, 1, 0, 1, 1),
(48191, 14242, 0.0037, 1, 0, 1, 1),
(48191, 14245, 0.011, 1, 0, 1, 1),
(48191, 14248, 0.033, 1, 0, 1, 1),
(48191, 14250, 0.0037, 1, 0, 1, 1),
(48191, 14251, 0.0147, 1, 0, 1, 1),
(48191, 14255, 0.0037, 1, 0, 1, 1),
(48191, 14407, 0.011, 1, 0, 1, 1),
(48191, 14418, 0.0073, 1, 0, 1, 1),
(48191, 14421, 0.011, 1, 0, 1, 1),
(48191, 14422, 0.011, 1, 0, 1, 1),
(48191, 14423, 0.0147, 1, 0, 1, 1),
(48191, 14424, 0.011, 1, 0, 1, 1),
(48191, 14425, 0.0073, 1, 0, 1, 1),
(48191, 14426, 0.0073, 1, 0, 1, 1),
(48191, 14429, 0.0037, 1, 0, 1, 1),
(48191, 14430, 0.011, 1, 0, 1, 1),
(48191, 14431, 0.0147, 1, 0, 1, 1),
(48191, 14435, 0.0073, 1, 0, 1, 1),
(48191, 14591, 0.0183, 1, 0, 1, 1),
(48191, 14592, 0.0183, 1, 0, 1, 1),
(48191, 14598, 0.0073, 1, 0, 1, 1),
(48191, 14599, 0.0037, 1, 0, 1, 1),
(48191, 14600, 0.0037, 1, 0, 1, 1),
(48191, 14602, 0.0073, 1, 0, 1, 1),
(48191, 14603, 0.011, 1, 0, 1, 1),
(48191, 14606, 0.0073, 1, 0, 1, 1),
(48191, 14654, 0.0037, 1, 0, 1, 1),
(48191, 14656, 0.0073, 1, 0, 1, 1),
(48191, 14770, 0.0073, 1, 0, 1, 1),
(48191, 14771, 0.0037, 1, 0, 1, 1),
(48191, 14772, 0.011, 1, 0, 1, 1),
(48191, 14773, 0.0037, 1, 0, 1, 1),
(48191, 14774, 0.0037, 1, 0, 1, 1),
(48191, 14775, 0.0147, 1, 0, 1, 1),
(48191, 14776, 0.0037, 1, 0, 1, 1),
(48191, 14821, 0.0037, 1, 0, 1, 1),
(48191, 14826, 0.011, 1, 0, 1, 1),
(48191, 14827, 0.0037, 1, 0, 1, 1),
(48191, 14828, 0.011, 1, 0, 1, 1),
(48191, 14829, 0.0037, 1, 0, 1, 1),
(48191, 14830, 0.0037, 1, 0, 1, 1),
(48191, 14832, 0.0257, 1, 0, 1, 1),
(48191, 14834, 0.0037, 1, 0, 1, 1),
(48191, 14839, 0.0037, 1, 0, 1, 1),
(48191, 14896, 0.0183, 1, 0, 1, 1),
(48191, 14897, 0.0147, 1, 0, 1, 1),
(48191, 14898, 0.044, 1, 0, 1, 1),
(48191, 14899, 0.0073, 1, 0, 1, 1),
(48191, 14900, 0.0183, 1, 0, 1, 1),
(48191, 14901, 0.0073, 1, 0, 1, 1),
(48191, 14903, 0.0183, 1, 0, 1, 1),
(48191, 14940, 0.0037, 1, 0, 1, 1),
(48191, 14942, 0.0037, 1, 0, 1, 1),
(48191, 14943, 0.0257, 1, 0, 1, 1),
(48191, 15146, 0.0037, 1, 0, 1, 1),
(48191, 15152, 0.0183, 1, 0, 1, 1),
(48191, 15156, 0.0147, 1, 0, 1, 1),
(48191, 15157, 0.0147, 1, 0, 1, 1),
(48191, 15159, 0.0147, 1, 0, 1, 1),
(48191, 15161, 0.0037, 1, 0, 1, 1),
(48191, 15165, 0.0147, 1, 0, 1, 1),
(48191, 15214, 0.0293, 1, 0, 1, 1),
(48191, 15234, 0.0514, 1, 0, 1, 1),
(48191, 15244, 0.0257, 1, 0, 1, 1),
(48191, 15251, 0.0147, 1, 0, 1, 1),
(48191, 15261, 0.0367, 1, 0, 1, 1),
(48191, 15322, 0.044, 1, 0, 1, 1),
(48191, 15359, 0.0147, 1, 0, 1, 1),
(48191, 15363, 0.0037, 1, 0, 1, 1),
(48191, 15366, 0.0073, 1, 0, 1, 1),
(48191, 15368, 0.0037, 1, 0, 1, 1),
(48191, 15370, 0.0037, 1, 0, 1, 1),
(48191, 15371, 0.011, 1, 0, 1, 1),
(48191, 15372, 0.0037, 1, 0, 1, 1),
(48191, 15377, 0.0073, 1, 0, 1, 1),
(48191, 15567, 0.022, 1, 0, 1, 1),
(48191, 15569, 0.0037, 1, 0, 1, 1),
(48191, 15572, 0.0037, 1, 0, 1, 1),
(48191, 15574, 0.0073, 1, 0, 1, 1),
(48191, 15578, 0.011, 1, 0, 1, 1),
(48191, 15580, 0.0037, 1, 0, 1, 1),
(48191, 15582, 0.022, 1, 0, 1, 1),
(48191, 15583, 0.0037, 1, 0, 1, 1),
(48191, 15584, 0.0073, 1, 0, 1, 1),
(48191, 15589, 0.0073, 1, 0, 1, 1),
(48191, 15592, 0.0037, 1, 0, 1, 1),
(48191, 15593, 0.0037, 1, 0, 1, 1),
(48191, 15596, 0.011, 1, 0, 1, 1),
(48191, 15597, 0.011, 1, 0, 1, 1),
(48191, 15600, 0.0037, 1, 0, 1, 1),
(48191, 15603, 0.011, 1, 0, 1, 1),
(48191, 15605, 0.0037, 1, 0, 1, 1),
(48191, 15606, 0.0147, 1, 0, 1, 1),
(48191, 15613, 0.0073, 1, 0, 1, 1),
(48191, 15978, 0.0073, 1, 0, 1, 1),
(48191, 15979, 0.0037, 1, 0, 1, 1),
(48191, 52976, 18.2486, 1, 0, 1, 2),
(48191, 52982, 12.2881, 1, 0, 1, 1),
(48191, 56051, 48.2009, 1, 0, 1, 1),
(48191, 56052, 25.3604, 1, 0, 1, 1),
(48191, 56053, 26.3434, 1, 0, 1, 1);

UPDATE `creature_template` SET `unit_flags`=256 WHERE `entry` IN (45907, 41439, 41448, 41447, 41421, 41444);

-- ELM General Purpose Bunny (scale x0.01)
SET @ENTRY := 24021;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,10000,10000,11,84990,32,0,0,0,0,10,736598,41460,0,0.0,0.0,0.0,0.0,"Update - Add Chains");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=736598;
UPDATE `creature_template_addon` SET `auras`='77579' WHERE `entry`=41460;

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '25872';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 484, 25872, 25872, 1, 8, 11);

UPDATE `creature_template_addon` SET `auras`='49417' WHERE `entry`=24021;
UPDATE `npc_spellclick_spells` SET `spell_id`=77584 WHERE `npc_entry`=41460 AND `spell_id`=84658;

-- Freewind Brave
SET @ENTRY := 41468;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,3,52,0,100,0,0,41468,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,41468,0,0,69,0,0,0,0,0,0,8,0,0,0,-5429.88,-2378.6,87.72,1.36,"After Talk 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

UPDATE `creature_template` SET `minlevel`=42, `maxlevel`=42, `unit_flags`=512 WHERE `entry`=41468;

DELETE FROM `creature_text` WHERE `entry`=41468;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41468,0,0,'Nechi owachi. Hello and thank you.',12,0,100,0,0,0,'Comment'),
(41468,1,0,'I will join you soon. Together, we will teach these Grimtotem cowards the meaning of fear!',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_area` WHERE `spell` = '84658' AND `quest_start` = '25872';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_end_status`) VALUES
(84658, 2097, 25872, 27330, 1, 11),
(84658, 5675, 25872, 27330, 1, 11);

-- Freewind Brave
SET @ENTRY := 45278;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Rushing Charge"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,5500,5500,11,85625,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,4000,4000,9500,9500,11,79878,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bloodthirst"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,6000,6000,6000,6000,11,81500,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast War Stomp"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,6,8,38,0,100,0,0,10,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,45278,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,28,84658,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Remove Auras From Players");

DELETE FROM `creature_text` WHERE `entry`=45278;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45278,0,0,'Hail.',12,0,100,0,0,0,'Comment'),
(45278,1,0,'Until we meet again.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `mindmg`=74, `maxdmg`=92, `attackpower`=25, `dmg_multiplier`=1.1, `InhabitType`=1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45278;
UPDATE `quest_template` SET `PrevQuestId`='27276' WHERE `Id` IN (27311, 27313, 27315);

-- No Weapons For You! Fire Bunny
SET @ENTRY := 45509;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,70415,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Add Flames"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,20000,20000,20000,20000,28,70415,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Flames");

-- Grimtotem Weapon Rack
SET @ENTRY := 205368;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,45509,5,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger (Flames)");

UPDATE `gameobject_template` SET `data5`=1 WHERE `entry`=205368;
UPDATE `gameobject` SET `spawntimesecs`=60 WHERE `id`=205368;
UPDATE `creature_template` SET `mindmg`=58, `maxdmg`=86, `attackpower`=22, `dmg_multiplier`=2.5 WHERE `entry` IN (45387, 45410, 45418, 45438);

DELETE FROM `creature_text` WHERE `entry`=45387;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45387,0,0,'%s becomes enraged!',16,0,100,0,0,0,'combat Enrage'),
(45387,1,0,'You\'ll soon learn to kneel before the might of the Grimtotem! If I let you live.',14,0,100,0,0,0,'Comment'),
(45387,1,1,'It will be a pleasure cleaving you in half!',14,0,100,0,0,0,'Comment'),
(45387,1,2,'Well, well, well, it looks like you people have a spine after all.',14,0,100,0,0,0,'Comment'),
(45387,2,0,'Earth Mother be merciful!',14,0,100,0,0,0,'Comment');

-- Isha Gloomaxe
SET @ENTRY := 45387;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,17000,19000,11,16856,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Mortal Strike"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,8000,24000,26000,11,85240,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Sundering Cleave"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,30,0,0,11,78943,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Enrage at 30% HP"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 30% HP"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 2");

UPDATE `quest_template` SET `PrevQuestId`='27315' WHERE `Id`=27319;
UPDATE `quest_template` SET `PrevQuestId`='27319' WHERE `Id`=27324;
UPDATE `quest_template` SET `PrevQuestId`='27324' WHERE `Id` IN (27321, 27326, 27328);

UPDATE `conditions` SET `ConditionValue1`=27321 WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27358 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27320 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
UPDATE `conditions` SET `ConditionValue1`=27326 WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27358 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27325 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
UPDATE `conditions` SET `ConditionValue1`=27328 WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27358 AND `SourceId`=0 AND `ElseGroup`=2 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27327 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

DELETE FROM `waypoints` WHERE `entry` = '45468';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45468, 1, -5011.22, -2105.69, 84.01, 'Drums'),
(45468, 2, -5009.31, -2114.35, 83.83, 'Drums'),
(45468, 3, -5002.58, -2114.80, 83.66, 'Drums'),
(45468, 4, -4998.23, -2108.25, 83.95, 'Drums'),
(45468, 5, -5003.46, -2101.57, 84.05, 'Drums');

DELETE FROM `waypoints` WHERE `entry` = '45463';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45463, 1, -5005.73, -2115.01, 83.62, 'Rattle'),
(45463, 2, -4999.11, -2111.23, 83.75, 'Rattle'),
(45463, 3, -5001.31, -2102.81, 84.10, 'Rattle'),
(45463, 4, -5010.59, -2103.84, 83.98, 'Rattle'),
(45463, 5, -5010.10, -2108.44, 83.88, 'Rattle');

DELETE FROM `waypoints` WHERE `entry` = '45466';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45466, 1, -4998.72, -2107.08, 84.00, 'Writ'),
(45466, 2, -5003.57, -2101.81, 84.03, 'Writ'),
(45466, 3, -5010.22, -2103.87, 83.95, 'Writ'),
(45466, 4, -5006.17, -2115.95, 83.62, 'Writ'),
(45466, 5, -5002.01, -2113.74, 83.68, 'Writ');

-- The Rattle of Bones
SET @ENTRY := 45463;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,1,2,37,0,100,0,0,0,0,0,53,1,45463,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,11,84949,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Spell"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,1,20000,20000,20000,20000,12,45446,4,60000,0,0,0,8,0,0,0,-5004.63,-2107.96,83.78,5.02,"Update - Summon Arikara");

-- The Writ of History
SET @ENTRY := 45466;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,1,2,37,0,100,0,0,0,0,0,53,1,45466,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,11,84953,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Spell");

-- The Drums of War
SET @ENTRY := 45468;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,1,2,37,0,100,0,0,0,0,0,53,1,45468,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,11,84954,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Spell");

DELETE FROM `spell_script_names` WHERE `spell_id` = '84925';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84925, 'spell_shuhalo_artifacts');

UPDATE `creature_template` SET `speed_run`=1.60286 WHERE `entry` IN (45468, 45466, 45463);
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=45468;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=45466;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=45463;

UPDATE `creature_template` SET `faction_A`=14, `faction_H`=14, `mindmg`=56, `maxdmg`=84, `attackpower`=21, `dmg_multiplier`=3.5 WHERE `entry`=45446;

-- Arikara
SET @ENTRY := 45446;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,79085,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Bolt"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,33,45447,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete");

DELETE FROM `creature_text` WHERE `entry`=45446;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45446,0,0,'Thank you for the gift. Let us see if you are worthy!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `speed_run`=2.0 WHERE `entry` IN (45468, 45466, 45463);

-- Lakota Windsong
SET @ENTRY := 45442;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27330,0,0,0,45,0,10,0,0,0,0,11,45278,50,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 10 to Freewind Brave"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,27329,0,0,0,45,0,10,0,0,0,0,11,45277,50,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 10 to Feralas Sentinel");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27330;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=47481;

-- Highperch Prideling
SET @ENTRY := 47481;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,85,88527,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Free Prideling"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,85,88532,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Prideling"),
(@ENTRY,@SOURCETYPE,3,4,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,33,47481,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

-- Highperch Prideling
SET @ENTRY := 47483;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,2,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,11,88567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Bubble"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive");

UPDATE `creature_template` SET `unit_flags`=512, `InhabitType`=7 WHERE `entry`=47483;
UPDATE `creature_template` SET `ScriptName`='npc_heartrazor' WHERE `entry`=47486;
UPDATE `creature_template` SET `ScriptName`='npc_twilight_subduer' WHERE `entry`=47487;
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `unit_flags`=512, `InhabitType`=4, `VehicleId`=1271 WHERE `entry`=47504;

DELETE FROM `waypoints` WHERE `entry` = '47504';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47504, 1, -4997.51, -927.93, 26.23, 'Heartrazor WP'),
(47504, 2, -5161.02, -913.01, 96.60, 'Heartrazor WP'),
(47504, 3, -5306.09, -1089.44, 156.96, 'Heartrazor WP'),
(47504, 4, -5305.34, -1149.04, 88.51, 'Heartrazor WP');

-- Heartrazor
SET @ENTRY := 47504;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,27,0,100,0,0,0,0,0,53,1,47504,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,4,0,0,0,28,88590,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run");

UPDATE `creature_template` SET `ScriptName`='npc_heartrazor_wp', `npcflag`=1 WHERE `entry`=47503;
UPDATE `creature_template` SET `speed_run`=2.14286 WHERE `entry`=47504;
UPDATE `creature_template_addon` SET `auras`='49414' WHERE `entry`=47503;
UPDATE `creature` SET `position_z`=6.141 WHERE `guid`=736600;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28088';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_end_status`) VALUES
(49416, 482, 28088, 1, 0);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '28098';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5588, 28098, 1, 2, 9);

DELETE FROM `creature_text` WHERE `entry`=47510;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47510,0,0,'It will be a pleasure shooting your down!',14,0,100,0,0,0,'Comment'),
(47510,1,0,'Useless wind rider! I don\'t need you anyway!',14,0,100,0,0,0,'Comment'),
(47510,2,0,'What\'s this? Shoo!',14,0,100,0,0,0,'Comment'),
(47510,3,0,'No! Get away! Get off of me!',14,0,100,0,0,0,'Comment'),
(47510,4,0,'NOOOOOO!',14,0,100,0,0,0,'Comment');

-- Richtofen's Wind Rider
SET @ENTRY := 47509;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,1,0,0,0,0,0,8,0,0,0,-5327.12,-1348.4,102.02,5.82,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

UPDATE `creature_template` SET `InhabitType`=4, `speed_run`=2.14286 WHERE `entry`=47509;
UPDATE `creature_template_addon` SET `bytes1`=0, `bytes2`=0, `auras`='88602' WHERE `entry`=47510;

-- Twilight Skymaster Richtofen
SET @ENTRY := 47510;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
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
(@ENTRY,@SOURCETYPE,16,0,0,1,100,0,6000,8000,17000,25000,11,79721,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Explosive Shot"),
(@ENTRY,@SOURCETYPE,17,0,2,1,100,1,0,30,0,0,11,80003,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Black Arrow at 30% HP"),
(@ENTRY,@SOURCETYPE,18,0,4,1,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,19,20,2,1,100,1,0,75,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 75% HP - Talk 1"),
(@ENTRY,@SOURCETYPE,20,21,61,1,100,0,0,0,0,0,43,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Mount To Entry"),
(@ENTRY,@SOURCETYPE,21,22,61,1,100,0,0,0,0,0,11,88601,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon WindRider"),
(@ENTRY,@SOURCETYPE,22,0,61,1,100,0,0,0,0,0,28,88602,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Hover"),
(@ENTRY,@SOURCETYPE,23,0,1,0,100,0,1000,1000,10000,10000,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Fly"),
(@ENTRY,@SOURCETYPE,24,25,2,1,100,1,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Talk 2"),
(@ENTRY,@SOURCETYPE,25,26,61,1,100,0,0,0,0,0,12,47511,4,12000,0,0,0,8,0,0,0,-5382.05,-1276.8,87.29,3.82,"Link - Summon Prideling"),
(@ENTRY,@SOURCETYPE,26,27,61,1,100,0,0,0,0,0,12,47511,4,12000,0,0,0,8,0,0,0,-5380.05,-1275.8,87.29,3.82,"Link - Summon Prideling"),
(@ENTRY,@SOURCETYPE,27,28,61,1,100,0,0,0,0,0,12,47511,4,12000,0,0,0,8,0,0,0,-5378.05,-1274.8,87.29,3.82,"Link - Summon Prideling"),
(@ENTRY,@SOURCETYPE,28,29,61,1,100,0,0,0,0,0,0,47511,4,12000,0,0,0,8,0,0,0,-5379.05,-1272.8,87.53,3.82,"Link - Summon Prideling"),
(@ENTRY,@SOURCETYPE,29,0,61,1,100,0,0,0,0,0,0,47511,4,12000,0,0,0,8,0,0,0,-5382.05,-1274.8,87.38,3.82,"Link - Summon Prideling"),
(@ENTRY,@SOURCETYPE,30,0,27,1,100,0,0,0,0,0,11,88598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Cower"),
(@ENTRY,@SOURCETYPE,31,0,27,1,100,1,0,0,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 3"),
(@ENTRY,@SOURCETYPE,32,0,27,1,100,0,0,0,0,0,89,12,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Random Move"),
(@ENTRY,@SOURCETYPE,33,0,27,1,100,0,0,0,0,0,33,47510,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Quest Complete"),
(@ENTRY,@SOURCETYPE,34,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,35,0,7,0,100,0,0,0,0,0,28,88598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Cower"),
(@ENTRY,@SOURCETYPE,36,0,27,1,100,0,0,0,0,0,75,6462,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Disable Attack"),
(@ENTRY,@SOURCETYPE,37,0,52,1,100,0,3,47510,0,0,1,4,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,38,39,52,1,100,0,4,47510,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Run"),
(@ENTRY,@SOURCETYPE,39,0,61,1,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-5340.58,-1361.49,87.21,5.29,"Link - Move Away"),
(@ENTRY,@SOURCETYPE,40,0,34,1,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

-- Highperch Prideling
SET @ENTRY := 47511;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,69,0,0,0,0,0,0,10,210915,47510,0,0.0,0.0,0.0,0.0,"AI Init - Move To Target"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,10,210915,47510,0,0.0,0.0,0.0,0.0,"On Movement Inform - Ride Skymaster");

UPDATE `creature` SET `phaseMask`=1, `position_z`=91.748 WHERE `guid`=736648;
UPDATE `creature_template_addon` SET `auras`='49415' WHERE `entry`=45707;
UPDATE `creature_template` SET `ScriptName`='npc_heartrazor_wp_return' WHERE `entry`=45707;

-- Heartrazor
SET @ENTRY := 47508;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,47508,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,0,0,0,0,28,88590,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger");

UPDATE `creature_template` SET `speed_run`=2.14286, `VehicleId`=1271, `InhabitType`=4 WHERE `entry`=47508;

DELETE FROM `waypoints` WHERE `entry` = '47508';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47508, 1, -5266.91, -1145.38, 103.93, 'Heartrazor Return'),
(47508, 2, -5051.88, -1056.91, 112.09, 'Heartrazor Return'),
(47508, 3, -4988.71, -980.34, 78.12, 'Heartrazor Return'),
(47508, 4, -4967.53, -993.95, 9.04, 'Heartrazor Return');

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=47507;
UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry`=47508;
UPDATE `creature_template_addon` SET `bytes1`=0 WHERE `entry`=47507;
UPDATE `creature_template_addon` SET `bytes1`=0 WHERE `entry`=47503;
UPDATE `quest_template` SET `PrevQuestId`='28124' WHERE `Id` IN (28127, 28125);
UPDATE `gameobject` SET `state`=1 WHERE `id` IN (206743, 206742);
UPDATE `creature` SET `phaseMask`=1 WHERE `id`=47630;
UPDATE `creature_template` SET `mindmg`=66, `maxdmg`=99, `attackpower`=25, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=47630;

-- Twilight Jailer
SET @ENTRY := 47630;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,30,0,500,1000,600000,600000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text OOC"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,4500,12000,13000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,9000,18000,22000,11,11971,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Sunder Armor"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,47621,30,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Prisoner"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,15,206742,30,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Cage"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,15,206743,30,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Cage");

-- Bulwark Prisoner
SET @ENTRY := 47621;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,46,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn");

-- Twilight Cage
SET @ENTRY := 206742;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,9,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Activate");

-- Twilight Cage
SET @ENTRY := 206743;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,9,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Activate");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28139;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12296 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12297 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12298 AND `id`=0;

UPDATE `creature_template` SET `mindmg`=55, `maxdmg`=82, `attackpower`=21, `dmg_multiplier`=42.2 WHERE `entry` IN (47602, 47620, 47619);

DELETE FROM `creature_text` WHERE `entry`=47602;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47602,0,0,'Huh? What?',12,0,100,0,0,0,'Comment');

-- Codemaster Deethuk
SET @ENTRY := 47602;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,67,0,100,0,9000,12000,0,0,11,79862,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Backstub"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,5,30,5000,6000,11,79866,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Deadly Throw on Close"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,30,0,0,11,79864,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shadowstep at 30% HP"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,8000,11000,23000,26500,11,79863,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Hemorrhage"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12296,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12296,0,0,0,33,47602,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,0,12296,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,47602,0,0,11,81311,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Sacrifice");

-- Commander Fastfuse
SET @ENTRY := 47620;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,32064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Battle Shout on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,0,0,40,20000,21000,11,79878,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Bloodthirst at 40% HP"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,4500,16000,17000,11,11977,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Rend"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,8000,9000,22000,28000,11,79881,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Slam"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12298,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12298,0,0,0,1,0,2000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,0,12298,0,0,0,33,47620,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,47620,0,0,11,81311,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Sacrifice");

DELETE FROM `creature_text` WHERE `entry`=47620;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47620,0,0,'Paratroopers?!',12,0,100,0,0,0,'Comment');

-- Commander Fastfuse
SET @ENTRY := 47620;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,32064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Battle Shout on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,0,0,40,20000,21000,11,79878,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Bloodthirst at 40% HP"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,4500,16000,17000,11,11977,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Rend"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,8000,9000,22000,28000,11,79881,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Slam"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12298,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12298,0,0,0,1,0,3000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,0,12298,0,0,0,33,47620,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,47620,0,0,11,81311,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Sacrifice"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,0,12298,0,0,0,66,45,0,0,0,0,0,8,0,0,0,-5551.71,-1748.57,109.93,1.28,"On Gossip Select - Rotate");

DELETE FROM `creature_text` WHERE `entry`=47619;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47619,0,0,'A mirror? How wonderful!',12,0,100,0,0,0,'Comment');

-- Elementalist Starion
SET @ENTRY := 47619;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,79564,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,79564,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,0,1,100,0,5000,7000,12000,14000,11,80117,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Earth Spike"),
(@ENTRY,@SOURCETYPE,11,0,0,1,100,0,9000,12000,24000,27000,11,79886,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Lava Burst"),
(@ENTRY,@SOURCETYPE,12,0,0,1,100,0,4000,17000,25000,36000,11,88771,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Twilight Immolate"),
(@ENTRY,@SOURCETYPE,13,0,62,0,100,0,12297,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,14,0,62,0,100,0,12297,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,0,47619,0,0,11,81311,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Sacrifice"),
(@ENTRY,@SOURCETYPE,16,0,62,0,100,0,12297,0,0,0,33,47619,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,17,0,62,0,100,0,12297,0,0,0,66,45,0,0,0,0,0,8,0,0,0,-5551.74,-1748.29,109.92,1.26,"On Gossip Select - Rotate");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28140;

DELETE FROM `creature_text` WHERE `entry`=47736;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47736,0,0,'I suppose I should thank you for freeing me. We\'ll soon see if you think that was a wise decision.',12,0,100,0,0,0,'Comment'),
(47736,1,0,'Meet me just outside of the Twilight Withering down the path to the east.',12,0,100,0,0,0,'Comment');

-- Magatha Grimtotem
SET @ENTRY := 47736;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,47736,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,47736,0,0,11,52096,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Teleport"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,52096,1,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Force Despawn");

-- Magatha Grimtotem
SET @ENTRY := 47718;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,120000,120000,11,88881,32,0,0,0,0,10,211395,24021,0,0.0,0.0,0.0,0.0,"OOC - Cast Right Bond"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,2000,2000,120000,120000,11,88880,32,0,0,0,0,10,211396,24021,0,0.0,0.0,0.0,0.0,"OOC - Cast Left Bond");

DELETE FROM `spell_target_position` WHERE `id` = '88857';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(88857, 1, -5756.31, -2026.65, 87.28, 0.71);

UPDATE `gameobject_template` SET `data10`=88857 WHERE `entry`=206767;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28140';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5590, 28140, 28140, 1, 8, 11);

DELETE FROM `creature_involvedrelation` WHERE `quest` = '28140';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(47580, 28140);

DELETE FROM `creature_questrelation` WHERE `quest` = '28142';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(47580, 28142);

UPDATE `creature_template` SET `mindmg`=66, `maxdmg`=99, `attackpower`=25, `lootid`=47816 WHERE `entry`=47816;
UPDATE `creature_template` SET `mindmg`=66, `maxdmg`=99, `attackpower`=25, `lootid`=47816 WHERE `entry`=48130;
UPDATE `creature_template` SET `mindmg`=66, `maxdmg`=99, `attackpower`=25, `lootid`=47816 WHERE `entry`=48132;
UPDATE `creature_template` SET `mindmg`=66, `maxdmg`=99, `attackpower`=25, `lootid`=47816 WHERE `entry`=47804;

DELETE FROM `creature_loot_template` WHERE `entry` IN (47816, 48130, 48132, 47804);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(47804, 754, 0.0049, 1, 0, 1, 1),
(47804, 1608, 0.0147, 1, 0, 1, 1),
(47804, 1613, 0.0686, 1, 0, 1, 1),
(47804, 1645, 5.9115, 1, 0, 1, 1),
(47804, 1685, 0.0098, 1, 0, 1, 1),
(47804, 1713, 0.0049, 1, 0, 1, 1),
(47804, 1714, 0.0049, 1, 0, 1, 1),
(47804, 1720, 0.0049, 1, 0, 1, 1),
(47804, 1994, 0.0245, 1, 0, 1, 1),
(47804, 2815, 0.0049, 1, 0, 1, 1),
(47804, 3187, 0.0686, 1, 0, 1, 1),
(47804, 3430, 0.0392, 1, 0, 1, 1),
(47804, 3832, 0.0049, 1, 0, 1, 1),
(47804, 3864, 0.1, 1, 0, 1, 1),
(47804, 3874, 0.0049, 1, 0, 1, 1),
(47804, 3914, 0.2, 1, 0, 1, 1),
(47804, 3927, 11.2347, 1, 0, 1, 1),
(47804, 3928, 3.6714, 1, 0, 1, 1),
(47804, 3936, 0.1667, 1, 0, 1, 1),
(47804, 3937, 1.6909, 1, 0, 1, 1),
(47804, 3938, 0.1716, 1, 0, 1, 1),
(47804, 3939, 0.1716, 1, 0, 1, 1),
(47804, 3940, 0.1, 1, 0, 1, 1),
(47804, 3941, 0.1, 1, 0, 1, 1),
(47804, 3942, 0.2451, 1, 0, 1, 1),
(47804, 3943, 0.1765, 1, 0, 1, 1),
(47804, 3961, 0.1863, 1, 0, 1, 1),
(47804, 3962, 0.1, 1, 0, 1, 1),
(47804, 3963, 0.1293, 1, 0, 1, 1),
(47804, 3964, 0.1, 1, 0, 1, 1),
(47804, 3965, 0.1, 1, 0, 1, 1),
(47804, 3966, 0.1421, 1, 0, 1, 1),
(47804, 3967, 0.1667, 1, 0, 1, 1),
(47804, 3968, 0.1, 1, 0, 1, 1),
(47804, 3986, 0.1667, 1, 0, 1, 1),
(47804, 3989, 0.2549, 1, 0, 1, 1),
(47804, 4000, 0.1765, 1, 0, 1, 1),
(47804, 4001, 0.1765, 1, 0, 1, 1),
(47804, 4002, 0.1, 1, 0, 1, 1),
(47804, 4003, 0.2059, 1, 0, 1, 1),
(47804, 4004, 0.1293, 1, 0, 1, 1),
(47804, 4005, 0.1372, 1, 0, 1, 1),
(47804, 4006, 0.05, 1, 0, 1, 1),
(47804, 4007, 0.1, 1, 0, 1, 1),
(47804, 4017, 0.2353, 1, 0, 1, 1),
(47804, 4018, 0.2696, 1, 0, 1, 1),
(47804, 4019, 0.2794, 1, 0, 1, 1),
(47804, 4020, 0.3284, 1, 0, 1, 1),
(47804, 4021, 0.2, 1, 0, 1, 1),
(47804, 4022, 2.0887, 1, 0, 1, 1),
(47804, 4023, 0.4706, 1, 0, 1, 1),
(47804, 4024, 0.2745, 1, 0, 1, 1),
(47804, 4025, 0.2, 1, 0, 1, 1),
(47804, 4026, 0.3431, 1, 0, 1, 1),
(47804, 4088, 0.0245, 1, 0, 1, 1),
(47804, 4089, 0.0098, 1, 0, 1, 1),
(47804, 4090, 0.0049, 1, 0, 1, 1),
(47804, 4306, 21.6, 1, 0, 1, 2),
(47804, 4338, 56.3992, 1, 0, 1, 1),
(47804, 4601, 1.2821, 1, 0, 1, 1),
(47804, 4602, 5.1282, 1, 0, 1, 1),
(47804, 4637, 0.4019, 1, 0, 1, 1),
(47804, 5216, 0.0637, 1, 0, 1, 1),
(47804, 5432, 57.6923, 1, 0, 1, 1),
(47804, 6149, 1.598, 1, 0, 1, 1),
(47804, 7453, 0.0098, 1, 0, 1, 1),
(47804, 7552, 0.0343, 1, 0, 1, 1),
(47804, 7909, 0.3, 1, 0, 1, 1),
(47804, 7910, 0.05, 1, 0, 1, 1),
(47804, 8194, 0.0343, 1, 0, 1, 1),
(47804, 8196, 0.0294, 1, 0, 1, 1),
(47804, 8199, 0.0147, 1, 0, 1, 1),
(47804, 8385, 0.0343, 1, 0, 1, 1),
(47804, 8386, 0.0196, 1, 0, 1, 1),
(47804, 8387, 0.0099, 1, 0, 1, 1),
(47804, 8749, 0.1691, 1, 0, 1, 1),
(47804, 8750, 0.1, 1, 0, 1, 1),
(47804, 8751, 0.1372, 1, 0, 1, 1),
(47804, 9298, 0.0098, 1, 0, 1, 1),
(47804, 10300, 0.0147, 1, 0, 1, 1),
(47804, 10301, 0.0098, 1, 0, 1, 1),
(47804, 10302, 0.0245, 1, 0, 1, 1),
(47804, 10312, 0.0147, 1, 0, 1, 1),
(47804, 10606, 0.0098, 1, 0, 1, 1),
(47804, 11202, 0.0196, 1, 0, 1, 1),
(47804, 11204, 0.0098, 1, 0, 1, 1),
(47804, 11208, 0.0995, 1, 0, 1, 1),
(47804, 11225, 0.0098, 1, 0, 1, 1),
(47804, 11973, 0.0196, 1, 0, 1, 1),
(47804, 11974, 0.0049, 1, 0, 1, 1),
(47804, 11987, 0.0049, 1, 0, 1, 1),
(47804, 11988, 0.0196, 1, 0, 1, 1),
(47804, 12012, 0.0196, 1, 0, 1, 1),
(47804, 12031, 0.0098, 1, 0, 1, 1),
(47804, 12032, 0.0098, 1, 0, 1, 1),
(47804, 12043, 0.0098, 1, 0, 1, 1),
(47804, 13026, 0.0049, 1, 0, 1, 1),
(47804, 13029, 0.0049, 1, 0, 1, 1),
(47804, 13058, 0.0098, 1, 0, 1, 1),
(47804, 13071, 0.0049, 1, 0, 1, 1),
(47804, 13095, 0.0098, 1, 0, 1, 1),
(47804, 13100, 0.0147, 1, 0, 1, 1),
(47804, 13115, 0.0098, 1, 0, 1, 1),
(47804, 13132, 0.0049, 1, 0, 1, 1),
(47804, 14237, 0.0049, 1, 0, 1, 1),
(47804, 14242, 0.0147, 1, 0, 1, 1),
(47804, 14243, 0.0294, 1, 0, 1, 1),
(47804, 14244, 0.0098, 1, 0, 1, 1),
(47804, 14246, 0.0539, 1, 0, 1, 1),
(47804, 14247, 0.0539, 1, 0, 1, 1),
(47804, 14249, 0.0049, 1, 0, 1, 1),
(47804, 14252, 0.0245, 1, 0, 1, 1),
(47804, 14253, 0.0196, 1, 0, 1, 1),
(47804, 14254, 0.0049, 1, 0, 1, 1),
(47804, 14257, 0.0147, 1, 0, 1, 1),
(47804, 14258, 0.0147, 1, 0, 1, 1),
(47804, 14259, 0.0049, 1, 0, 1, 1),
(47804, 14260, 0.0441, 1, 0, 1, 1),
(47804, 14262, 0.0441, 1, 0, 1, 1),
(47804, 14268, 0.0098, 1, 0, 1, 1),
(47804, 14270, 0.0833, 1, 0, 1, 1),
(47804, 14272, 0.0392, 1, 0, 1, 1),
(47804, 14273, 0.0049, 1, 0, 1, 1),
(47804, 14276, 0.0147, 1, 0, 1, 1),
(47804, 14417, 0.0049, 1, 0, 1, 1),
(47804, 14425, 0.0245, 1, 0, 1, 1),
(47804, 14428, 0.0294, 1, 0, 1, 1),
(47804, 14429, 0.0049, 1, 0, 1, 1),
(47804, 14431, 0.0637, 1, 0, 1, 1),
(47804, 14432, 0.0245, 1, 0, 1, 1),
(47804, 14433, 0.0294, 1, 0, 1, 1),
(47804, 14435, 0.0098, 1, 0, 1, 1),
(47804, 14436, 0.0147, 1, 0, 1, 1),
(47804, 14439, 0.0098, 1, 0, 1, 1),
(47804, 14440, 0.0098, 1, 0, 1, 1),
(47804, 14549, 0.0049, 1, 0, 1, 1),
(47804, 14601, 0.049, 1, 0, 1, 1),
(47804, 14604, 0.0147, 1, 0, 1, 1),
(47804, 14652, 0.0196, 1, 0, 1, 1),
(47804, 14653, 0.0049, 1, 0, 1, 1),
(47804, 14654, 0.0539, 1, 0, 1, 1),
(47804, 14656, 0.0294, 1, 0, 1, 1),
(47804, 14657, 0.0245, 1, 0, 1, 1),
(47804, 14659, 0.0049, 1, 0, 1, 1),
(47804, 14660, 0.0098, 1, 0, 1, 1),
(47804, 14663, 0.0049, 1, 0, 1, 1),
(47804, 14768, 0.0245, 1, 0, 1, 1),
(47804, 14774, 0.0098, 1, 0, 1, 1),
(47804, 14775, 0.0098, 1, 0, 1, 1),
(47804, 14776, 0.0147, 1, 0, 1, 1),
(47804, 14777, 0.0343, 1, 0, 1, 1),
(47804, 14778, 0.0735, 1, 0, 1, 1),
(47804, 14781, 0.0245, 1, 0, 1, 1),
(47804, 14782, 0.0588, 1, 0, 1, 1),
(47804, 14783, 0.0098, 1, 0, 1, 1),
(47804, 14784, 0.0098, 1, 0, 1, 1),
(47804, 14786, 0.0196, 1, 0, 1, 1),
(47804, 14787, 0.0098, 1, 0, 1, 1),
(47804, 14791, 0.0049, 1, 0, 1, 1),
(47804, 14821, 0.0245, 1, 0, 1, 1),
(47804, 14825, 0.0343, 1, 0, 1, 1),
(47804, 14831, 0.0147, 1, 0, 1, 1),
(47804, 14834, 0.0196, 1, 0, 1, 1),
(47804, 14835, 0.0049, 1, 0, 1, 1),
(47804, 14838, 0.0049, 1, 0, 1, 1),
(47804, 14839, 0.0441, 1, 0, 1, 1),
(47804, 14840, 0.0098, 1, 0, 1, 1),
(47804, 14841, 0.0441, 1, 0, 1, 1),
(47804, 14842, 0.0196, 1, 0, 1, 1),
(47804, 14843, 0.0098, 1, 0, 1, 1),
(47804, 14853, 0.0147, 1, 0, 1, 1),
(47804, 14905, 0.0294, 1, 0, 1, 1),
(47804, 14906, 0.0294, 1, 0, 1, 1),
(47804, 14909, 0.0343, 1, 0, 1, 1),
(47804, 14910, 0.0343, 1, 0, 1, 1),
(47804, 14911, 0.0147, 1, 0, 1, 1),
(47804, 14914, 0.0098, 1, 0, 1, 1),
(47804, 14918, 0.0098, 1, 0, 1, 1),
(47804, 14939, 0.0147, 1, 0, 1, 1),
(47804, 14940, 0.0147, 1, 0, 1, 1),
(47804, 14944, 0.0196, 1, 0, 1, 1),
(47804, 14945, 0.0245, 1, 0, 1, 1),
(47804, 14946, 0.0294, 1, 0, 1, 1),
(47804, 14947, 0.0147, 1, 0, 1, 1),
(47804, 14949, 0.0098, 1, 0, 1, 1),
(47804, 14950, 0.0098, 1, 0, 1, 1),
(47804, 14951, 0.0049, 1, 0, 1, 1),
(47804, 14955, 0.0147, 1, 0, 1, 1),
(47804, 14956, 0.049, 1, 0, 1, 1),
(47804, 15156, 0.0098, 1, 0, 1, 1),
(47804, 15161, 0.0049, 1, 0, 1, 1),
(47804, 15162, 0.049, 1, 0, 1, 1),
(47804, 15163, 0.0245, 1, 0, 1, 1),
(47804, 15164, 0.0098, 1, 0, 1, 1),
(47804, 15166, 0.0196, 1, 0, 1, 1),
(47804, 15168, 0.0539, 1, 0, 1, 1),
(47804, 15169, 0.0196, 1, 0, 1, 1),
(47804, 15172, 0.0049, 1, 0, 1, 1),
(47804, 15173, 0.0147, 1, 0, 1, 1),
(47804, 15178, 0.0196, 1, 0, 1, 1),
(47804, 15215, 0.0784, 1, 0, 1, 1),
(47804, 15251, 0.0245, 1, 0, 1, 1),
(47804, 15262, 0.0392, 1, 0, 1, 1),
(47804, 15270, 0.0588, 1, 0, 1, 1),
(47804, 15287, 0.0637, 1, 0, 1, 1),
(47804, 15370, 0.0245, 1, 0, 1, 1),
(47804, 15372, 0.0098, 1, 0, 1, 1),
(47804, 15373, 0.0049, 1, 0, 1, 1),
(47804, 15374, 0.0392, 1, 0, 1, 1),
(47804, 15375, 0.0147, 1, 0, 1, 1),
(47804, 15376, 0.0294, 1, 0, 1, 1),
(47804, 15378, 0.0245, 1, 0, 1, 1),
(47804, 15379, 0.0049, 1, 0, 1, 1),
(47804, 15380, 0.0245, 1, 0, 1, 1),
(47804, 15382, 0.0196, 1, 0, 1, 1),
(47804, 15383, 0.0049, 1, 0, 1, 1),
(47804, 15592, 0.0147, 1, 0, 1, 1),
(47804, 15599, 0.0147, 1, 0, 1, 1),
(47804, 15601, 0.0049, 1, 0, 1, 1),
(47804, 15602, 0.0196, 1, 0, 1, 1),
(47804, 15607, 0.0098, 1, 0, 1, 1),
(47804, 15608, 0.0343, 1, 0, 1, 1),
(47804, 15609, 0.0049, 1, 0, 1, 1),
(47804, 15610, 0.0392, 1, 0, 1, 1),
(47804, 15611, 0.0098, 1, 0, 1, 1),
(47804, 15612, 0.0637, 1, 0, 1, 1),
(47804, 15614, 0.049, 1, 0, 1, 1),
(47804, 15615, 0.0049, 1, 0, 1, 1),
(47804, 15616, 0.0049, 1, 0, 1, 1),
(47804, 15617, 0.0049, 1, 0, 1, 1),
(47804, 15618, 0.0098, 1, 0, 1, 1),
(47804, 15624, 0.0098, 1, 0, 1, 1),
(47804, 15625, 0.0098, 1, 0, 1, 1),
(47804, 15626, 0.0098, 1, 0, 1, 1),
(47804, 15628, 0.0098, 1, 0, 1, 1),
(47804, 15632, 0.0098, 1, 0, 1, 1),
(47804, 15635, 0.0049, 1, 0, 1, 1),
(47804, 15964, 0.0147, 1, 0, 1, 1),
(47804, 15980, 0.0049, 1, 0, 1, 1),
(47804, 15981, 0.0049, 1, 0, 1, 1),
(47804, 21944, 0.0147, 1, 0, 1, 1),
(47816, 1613, 0.0439, 1, 0, 1, 1),
(47816, 1980, 0.0088, 1, 0, 1, 1),
(47816, 1994, 0.1759, 1, 0, 1, 1),
(47816, 3187, 0.0175, 1, 0, 1, 1),
(47816, 3430, 0.0263, 1, 0, 1, 1),
(47816, 3858, 8.1395, 1, 0, 1, 1),
(47816, 3864, 0.05, 1, 0, 1, 1),
(47816, 3914, 0.2, 1, 0, 1, 1),
(47816, 3936, 0.05, 1, 0, 1, 1),
(47816, 3937, 0.05, 1, 0, 1, 1),
(47816, 3938, 0.05, 1, 0, 1, 1),
(47816, 3939, 0.05, 1, 0, 1, 1),
(47816, 3940, 0.1, 1, 0, 1, 1),
(47816, 3941, 0.1, 1, 0, 1, 1),
(47816, 3942, 0.1, 1, 0, 1, 1),
(47816, 3961, 0.05, 1, 0, 1, 1),
(47816, 3962, 0.1759, 1, 0, 1, 1),
(47816, 3963, 0.1759, 1, 0, 1, 1),
(47816, 3964, 0.1407, 1, 0, 1, 1),
(47816, 3965, 0.1, 1, 0, 1, 1),
(47816, 3966, 0.1404, 1, 0, 1, 1),
(47816, 3967, 0.1, 1, 0, 1, 1),
(47816, 3968, 0.1, 1, 0, 1, 1),
(47816, 3986, 0.1, 1, 0, 1, 1),
(47816, 3989, 0.05, 1, 0, 1, 1),
(47816, 4002, 0.05, 1, 0, 1, 1),
(47816, 4003, 0.05, 1, 0, 1, 1),
(47816, 4004, 0.05, 1, 0, 1, 1),
(47816, 4007, 0.05, 1, 0, 1, 1),
(47816, 4017, 0.1, 1, 0, 1, 1),
(47816, 4018, 0.1, 1, 0, 1, 1),
(47816, 4019, 0.05, 1, 0, 1, 1),
(47816, 4020, 0.1, 1, 0, 1, 1),
(47816, 4021, 0.1, 1, 0, 1, 1),
(47816, 4022, 0.2, 1, 0, 1, 1),
(47816, 4023, 0.05, 1, 0, 1, 1),
(47816, 4024, 0.05, 1, 0, 1, 1),
(47816, 4025, 0.05, 1, 0, 1, 1),
(47816, 4026, 0.299, 1, 0, 1, 1),
(47816, 4088, 0.0175, 1, 0, 1, 1),
(47816, 4637, 0.05, 1, 0, 1, 1),
(47816, 7067, 6.3865, 1, 0, 1, 1),
(47816, 7075, 5.3338, 1, 0, 1, 1),
(47816, 7552, 0.0088, 1, 0, 1, 1),
(47816, 7992, 0.0088, 1, 0, 1, 1),
(47816, 8150, 20.9302, 1, 0, 1, 1),
(47816, 8196, 0.0263, 1, 0, 1, 1),
(47816, 8749, 0.05, 1, 0, 1, 1),
(47816, 8750, 0.1231, 1, 0, 1, 1),
(47816, 10312, 0.0088, 1, 0, 1, 1),
(47816, 10603, 0.0088, 1, 0, 1, 1),
(47816, 10604, 0.0175, 1, 0, 1, 1),
(47816, 11202, 0.0175, 1, 0, 1, 1),
(47816, 11225, 0.0088, 1, 0, 1, 1),
(47816, 11988, 0.0088, 1, 0, 1, 1),
(47816, 12012, 0.0088, 1, 0, 1, 1),
(47816, 12031, 0.0088, 1, 0, 1, 1),
(47816, 13051, 0.0088, 1, 0, 1, 1),
(47816, 13071, 0.0088, 1, 0, 1, 1),
(47816, 13100, 0.0175, 1, 0, 1, 1),
(47816, 14243, 0.0088, 1, 0, 1, 1),
(47816, 14246, 0.0175, 1, 0, 1, 1),
(47816, 14247, 0.0439, 1, 0, 1, 1),
(47816, 14252, 0.0088, 1, 0, 1, 1),
(47816, 14253, 0.0088, 1, 0, 1, 1),
(47816, 14257, 0.0088, 1, 0, 1, 1),
(47816, 14258, 0.0263, 1, 0, 1, 1),
(47816, 14260, 0.0351, 1, 0, 1, 1),
(47816, 14262, 0.0175, 1, 0, 1, 1),
(47816, 14268, 0.0088, 1, 0, 1, 1),
(47816, 14270, 0.0088, 1, 0, 1, 1),
(47816, 14425, 0.0175, 1, 0, 1, 1),
(47816, 14428, 0.0088, 1, 0, 1, 1),
(47816, 14431, 0.0439, 1, 0, 1, 1),
(47816, 14432, 0.0439, 1, 0, 1, 1),
(47816, 14436, 0.0088, 1, 0, 1, 1),
(47816, 14601, 0.0088, 1, 0, 1, 1),
(47816, 14604, 0.0175, 1, 0, 1, 1),
(47816, 14654, 0.0263, 1, 0, 1, 1),
(47816, 14656, 0.0263, 1, 0, 1, 1),
(47816, 14660, 0.0088, 1, 0, 1, 1),
(47816, 14768, 0.0439, 1, 0, 1, 1),
(47816, 14776, 0.0088, 1, 0, 1, 1),
(47816, 14777, 0.0175, 1, 0, 1, 1),
(47816, 14784, 0.0175, 1, 0, 1, 1),
(47816, 14821, 0.0088, 1, 0, 1, 1),
(47816, 14833, 0.0088, 1, 0, 1, 1),
(47816, 14839, 0.0439, 1, 0, 1, 1),
(47816, 14840, 0.0088, 1, 0, 1, 1),
(47816, 14910, 0.0175, 1, 0, 1, 1),
(47816, 14944, 0.0175, 1, 0, 1, 1),
(47816, 14945, 0.0088, 1, 0, 1, 1),
(47816, 14956, 0.0263, 1, 0, 1, 1),
(47816, 15161, 0.0088, 1, 0, 1, 1),
(47816, 15162, 0.0088, 1, 0, 1, 1),
(47816, 15166, 0.0088, 1, 0, 1, 1),
(47816, 15168, 0.0088, 1, 0, 1, 1),
(47816, 15169, 0.0088, 1, 0, 1, 1),
(47816, 15173, 0.0088, 1, 0, 1, 1),
(47816, 15215, 0.0526, 1, 0, 1, 1),
(47816, 15251, 0.0175, 1, 0, 1, 1),
(47816, 15262, 0.0176, 1, 0, 1, 1),
(47816, 15270, 0.0439, 1, 0, 1, 1),
(47816, 15287, 0.0351, 1, 0, 1, 1),
(47816, 15370, 0.0088, 1, 0, 1, 1),
(47816, 15372, 0.0088, 1, 0, 1, 1),
(47816, 15373, 0.0088, 1, 0, 1, 1),
(47816, 15382, 0.0088, 1, 0, 1, 1),
(47816, 15386, 0.0088, 1, 0, 1, 1),
(47816, 15599, 0.0088, 1, 0, 1, 1),
(47816, 15602, 0.079, 1, 0, 1, 1),
(47816, 15604, 0.0088, 1, 0, 1, 1),
(47816, 15610, 0.0175, 1, 0, 1, 1),
(47816, 15611, 0.0088, 1, 0, 1, 1),
(47816, 15615, 0.0088, 1, 0, 1, 1),
(47816, 15617, 0.0088, 1, 0, 1, 1),
(47816, 15620, 0.0088, 1, 0, 1, 1),
(47816, 15632, 0.0088, 1, 0, 1, 1),
(47816, 21944, 0.0088, 1, 0, 1, 1),
(47816, 21945, 0.0088, 1, 0, 1, 1),
(47816, 55978, 79.5772, 1, 0, 1, 1),
(47816, 55981, 8.5271, 1, 0, 1, 1),
(47816, 56033, 3.4884, 1, 0, 1, 1),
(47816, 56035, 27.907, 1, 0, 1, 1),
(47816, 56046, 39.5349, 1, 0, 1, 3),
(48130, 866, 0.1318, 1, 0, 1, 1),
(48130, 869, 0.0043, 1, 0, 1, 1),
(48130, 870, 0.0022, 1, 0, 1, 1),
(48130, 1204, 0.0065, 1, 0, 1, 1),
(48130, 1207, 0.1977, 1, 0, 1, 1),
(48130, 1265, 0.0065, 1, 0, 1, 1),
(48130, 1529, 0.05, 1, 0, 1, 1),
(48130, 1613, 0.05, 1, 0, 1, 1),
(48130, 1625, 0.0387, 1, 0, 1, 1),
(48130, 1640, 0.0151, 1, 0, 1, 1),
(48130, 1718, 0.0043, 1, 0, 1, 1),
(48130, 1722, 0.0022, 1, 0, 1, 1),
(48130, 1980, 0.0022, 1, 0, 1, 1),
(48130, 3778, 0.05, 1, 0, 1, 1),
(48130, 3779, 0.1, 1, 0, 1, 1),
(48130, 3780, 0.05, 1, 0, 1, 1),
(48130, 3781, 0.05, 1, 0, 1, 1),
(48130, 3782, 0.05, 1, 0, 1, 1),
(48130, 3783, 0.1, 1, 0, 1, 1),
(48130, 3784, 0.05, 1, 0, 1, 1),
(48130, 3785, 0.1, 1, 0, 1, 1),
(48130, 3786, 0.1, 1, 0, 1, 1),
(48130, 3787, 0.05, 1, 0, 1, 1),
(48130, 3794, 0.1, 1, 0, 1, 1),
(48130, 3795, 0.1, 1, 0, 1, 1),
(48130, 3796, 0.1, 1, 0, 1, 1),
(48130, 3798, 0.05, 1, 0, 1, 1),
(48130, 3799, 0.05, 1, 0, 1, 1),
(48130, 3800, 0.05, 1, 0, 1, 1),
(48130, 3801, 0.05, 1, 0, 1, 1),
(48130, 3802, 0.05, 1, 0, 1, 1),
(48130, 3803, 0.1, 1, 0, 1, 1),
(48130, 3804, 0.05, 1, 0, 1, 1),
(48130, 3805, 0.1, 1, 0, 1, 1),
(48130, 3806, 0.1, 1, 0, 1, 1),
(48130, 3807, 0.05, 1, 0, 1, 1),
(48130, 3808, 0.1, 1, 0, 1, 1),
(48130, 3810, 0.05, 1, 0, 1, 1),
(48130, 3811, 0.05, 1, 0, 1, 1),
(48130, 3813, 0.05, 1, 0, 1, 1),
(48130, 3814, 0.05, 1, 0, 1, 1),
(48130, 3815, 0.05, 1, 0, 1, 1),
(48130, 3816, 0.05, 1, 0, 1, 1),
(48130, 3817, 0.05, 1, 0, 1, 1),
(48130, 3864, 0.05, 1, 0, 1, 1),
(48130, 3914, 0.2, 1, 0, 1, 1),
(48130, 3936, 0.1, 1, 0, 1, 1),
(48130, 3937, 0.05, 1, 0, 1, 1),
(48130, 3938, 0.05, 1, 0, 1, 1),
(48130, 3939, 0.05, 1, 0, 1, 1),
(48130, 3940, 0.05, 1, 0, 1, 1),
(48130, 3942, 0.05, 1, 0, 1, 1),
(48130, 3943, 0.05, 1, 0, 1, 1),
(48130, 3963, 0.05, 1, 0, 1, 1),
(48130, 3964, 0.05, 1, 0, 1, 1),
(48130, 3965, 0.1, 1, 0, 1, 1),
(48130, 3967, 0.05, 1, 0, 1, 1),
(48130, 3968, 0.1, 1, 0, 1, 1),
(48130, 3986, 0.1, 1, 0, 1, 1),
(48130, 3989, 0.05, 1, 0, 1, 1),
(48130, 4000, 0.1, 1, 0, 1, 1),
(48130, 4001, 0.05, 1, 0, 1, 1),
(48130, 4002, 0.05, 1, 0, 1, 1),
(48130, 4003, 0.05, 1, 0, 1, 1),
(48130, 4004, 0.05, 1, 0, 1, 1),
(48130, 4005, 0.05, 1, 0, 1, 1),
(48130, 4006, 0.05, 1, 0, 1, 1),
(48130, 4007, 0.05, 1, 0, 1, 1),
(48130, 4017, 0.1, 1, 0, 1, 1),
(48130, 4018, 0.1, 1, 0, 1, 1),
(48130, 4019, 0.1, 1, 0, 1, 1),
(48130, 4020, 0.05, 1, 0, 1, 1),
(48130, 4021, 0.1, 1, 0, 1, 1),
(48130, 4022, 0.1, 1, 0, 1, 1),
(48130, 4023, 0.05, 1, 0, 1, 1),
(48130, 4024, 0.1, 1, 0, 1, 1),
(48130, 4025, 0.05, 1, 0, 1, 1),
(48130, 4026, 0.1, 1, 0, 1, 1),
(48130, 4087, 0.0215, 1, 0, 1, 1),
(48130, 4353, 0.0086, 1, 0, 1, 1),
(48130, 4415, 0.0043, 1, 0, 1, 1),
(48130, 4636, 0.05, 1, 0, 1, 1),
(48130, 4637, 0.05, 1, 0, 1, 1),
(48130, 4867, 69.954, 1, 0, 1, 1),
(48130, 5011, 0.0022, 1, 0, 1, 1),
(48130, 5215, 0.0301, 1, 0, 1, 1),
(48130, 6045, 0.0659, 1, 0, 1, 1),
(48130, 7909, 0.05, 1, 0, 1, 1),
(48130, 7910, 0.05, 1, 0, 1, 1),
(48130, 7912, 0.0108, 1, 0, 1, 1),
(48130, 7992, 0.0066, 1, 0, 1, 1),
(48130, 8154, 20.6344, 1, 0, 1, 1),
(48130, 8169, 1.0681, 1, 0, 1, 1),
(48130, 8194, 0.0129, 1, 0, 1, 1),
(48130, 8196, 0.0132, 1, 0, 1, 1),
(48130, 8746, 0.05, 1, 0, 1, 1),
(48130, 8747, 0.1, 1, 0, 1, 1),
(48130, 8748, 0.05, 1, 0, 1, 1),
(48130, 8749, 0.1, 1, 0, 1, 1),
(48130, 8750, 0.05, 1, 0, 1, 1),
(48130, 8751, 0.1, 1, 0, 1, 1),
(48130, 8838, 0.0132, 1, 0, 1, 1),
(48130, 9293, 0.0065, 1, 0, 1, 1),
(48130, 9434, 0.0043, 1, 0, 1, 1),
(48130, 10302, 0.0065, 1, 0, 1, 1),
(48130, 10603, 0.0086, 1, 0, 1, 1),
(48130, 11202, 0.0066, 1, 0, 1, 1),
(48130, 11972, 0.0086, 1, 0, 1, 1),
(48130, 11973, 0.0022, 1, 0, 1, 1),
(48130, 11986, 0.0108, 1, 0, 1, 1),
(48130, 11998, 0.0172, 1, 0, 1, 1),
(48130, 12011, 0.0172, 1, 0, 1, 1),
(48130, 12022, 0.0108, 1, 0, 1, 1),
(48130, 12030, 0.0043, 1, 0, 1, 1),
(48130, 12037, 44.5678, 1, 0, 1, 1),
(48130, 12042, 0.0151, 1, 0, 1, 1),
(48130, 13017, 0.0043, 1, 0, 1, 1),
(48130, 13020, 0.0043, 1, 0, 1, 1),
(48130, 13034, 0.0043, 1, 0, 1, 1),
(48130, 13038, 0.0022, 1, 0, 1, 1),
(48130, 13042, 0.0022, 1, 0, 1, 1),
(48130, 13081, 0.0043, 1, 0, 1, 1),
(48130, 13088, 0.0043, 1, 0, 1, 1),
(48130, 13103, 0.0065, 1, 0, 1, 1),
(48130, 13138, 0.0065, 1, 0, 1, 1),
(48130, 13199, 0.0022, 1, 0, 1, 1),
(48130, 14216, 0.0043, 1, 0, 1, 1),
(48130, 14220, 0.0172, 1, 0, 1, 1),
(48130, 14224, 0.0086, 1, 0, 1, 1),
(48130, 14225, 0.0065, 1, 0, 1, 1),
(48130, 14228, 0.0151, 1, 0, 1, 1),
(48130, 14230, 0.0022, 1, 0, 1, 1),
(48130, 14232, 0.0043, 1, 0, 1, 1),
(48130, 14233, 0.0108, 1, 0, 1, 1),
(48130, 14234, 0.0022, 1, 0, 1, 1),
(48130, 14238, 0.0151, 1, 0, 1, 1),
(48130, 14239, 0.0043, 1, 0, 1, 1),
(48130, 14240, 0.0129, 1, 0, 1, 1),
(48130, 14241, 0.0129, 1, 0, 1, 1),
(48130, 14242, 0.0151, 1, 0, 1, 1),
(48130, 14243, 0.0043, 1, 0, 1, 1),
(48130, 14245, 0.0086, 1, 0, 1, 1),
(48130, 14248, 0.0215, 1, 0, 1, 1),
(48130, 14250, 0.0215, 1, 0, 1, 1),
(48130, 14251, 0.0194, 1, 0, 1, 1),
(48130, 14253, 0.0108, 1, 0, 1, 1),
(48130, 14255, 0.0022, 1, 0, 1, 1),
(48130, 14407, 0.0065, 1, 0, 1, 1),
(48130, 14413, 0.0022, 1, 0, 1, 1),
(48130, 14418, 0.0043, 1, 0, 1, 1),
(48130, 14421, 0.0043, 1, 0, 1, 1),
(48130, 14422, 0.0172, 1, 0, 1, 1),
(48130, 14423, 0.0194, 1, 0, 1, 1),
(48130, 14426, 0.0065, 1, 0, 1, 1),
(48130, 14429, 0.0022, 1, 0, 1, 1),
(48130, 14430, 0.0065, 1, 0, 1, 1),
(48130, 14435, 0.0065, 1, 0, 1, 1),
(48130, 14591, 0.0065, 1, 0, 1, 1),
(48130, 14592, 0.0086, 1, 0, 1, 1),
(48130, 14598, 0.0237, 1, 0, 1, 1),
(48130, 14599, 0.0022, 1, 0, 1, 1),
(48130, 14600, 0.0387, 1, 0, 1, 1),
(48130, 14602, 0.0022, 1, 0, 1, 1),
(48130, 14603, 0.0323, 1, 0, 1, 1),
(48130, 14605, 0.0022, 1, 0, 1, 1),
(48130, 14606, 0.0086, 1, 0, 1, 1),
(48130, 14607, 0.0108, 1, 0, 1, 1),
(48130, 14760, 0.0043, 1, 0, 1, 1),
(48130, 14769, 0.0022, 1, 0, 1, 1),
(48130, 14770, 0.0065, 1, 0, 1, 1),
(48130, 14771, 0.0086, 1, 0, 1, 1),
(48130, 14772, 0.0043, 1, 0, 1, 1),
(48130, 14773, 0.0043, 1, 0, 1, 1),
(48130, 14774, 0.0129, 1, 0, 1, 1),
(48130, 14775, 0.0043, 1, 0, 1, 1),
(48130, 14776, 0.0065, 1, 0, 1, 1),
(48130, 14777, 0.0022, 1, 0, 1, 1),
(48130, 14821, 0.0043, 1, 0, 1, 1),
(48130, 14825, 0.0043, 1, 0, 1, 1),
(48130, 14826, 0.0108, 1, 0, 1, 1),
(48130, 14827, 0.0065, 1, 0, 1, 1),
(48130, 14830, 0.0022, 1, 0, 1, 1),
(48130, 14831, 0.0065, 1, 0, 1, 1),
(48130, 14832, 0.0065, 1, 0, 1, 1),
(48130, 14834, 0.0022, 1, 0, 1, 1),
(48130, 14895, 0.0043, 1, 0, 1, 1),
(48130, 14896, 0.0237, 1, 0, 1, 1),
(48130, 14897, 0.0215, 1, 0, 1, 1),
(48130, 14898, 0.028, 1, 0, 1, 1),
(48130, 14899, 0.0065, 1, 0, 1, 1),
(48130, 14900, 0.0215, 1, 0, 1, 1),
(48130, 14901, 0.0086, 1, 0, 1, 1),
(48130, 14902, 0.0022, 1, 0, 1, 1),
(48130, 14903, 0.0387, 1, 0, 1, 1),
(48130, 14910, 0.0043, 1, 0, 1, 1),
(48130, 14941, 0.0065, 1, 0, 1, 1),
(48130, 14946, 0.0043, 1, 0, 1, 1),
(48130, 15146, 0.0108, 1, 0, 1, 1),
(48130, 15152, 0.0344, 1, 0, 1, 1),
(48130, 15155, 0.0258, 1, 0, 1, 1),
(48130, 15156, 0.0022, 1, 0, 1, 1),
(48130, 15157, 0.0086, 1, 0, 1, 1),
(48130, 15158, 0.0108, 1, 0, 1, 1),
(48130, 15159, 0.0086, 1, 0, 1, 1),
(48130, 15160, 0.0022, 1, 0, 1, 1),
(48130, 15161, 0.0129, 1, 0, 1, 1),
(48130, 15163, 0.0043, 1, 0, 1, 1),
(48130, 15165, 0.0129, 1, 0, 1, 1),
(48130, 15214, 0.0301, 1, 0, 1, 1),
(48130, 15233, 0.0409, 1, 0, 1, 1),
(48130, 15234, 0.0215, 1, 0, 1, 1),
(48130, 15244, 0.1318, 1, 0, 1, 1),
(48130, 15261, 0.0581, 1, 0, 1, 1),
(48130, 15359, 0.0194, 1, 0, 1, 1),
(48130, 15362, 0.0043, 1, 0, 1, 1),
(48130, 15363, 0.0065, 1, 0, 1, 1),
(48130, 15366, 0.0108, 1, 0, 1, 1),
(48130, 15368, 0.0108, 1, 0, 1, 1),
(48130, 15369, 0.0065, 1, 0, 1, 1),
(48130, 15370, 0.0043, 1, 0, 1, 1),
(48130, 15371, 0.0086, 1, 0, 1, 1),
(48130, 15372, 0.0043, 1, 0, 1, 1),
(48130, 15375, 0.0022, 1, 0, 1, 1),
(48130, 15567, 0.0237, 1, 0, 1, 1),
(48130, 15569, 0.0043, 1, 0, 1, 1),
(48130, 15574, 0.0086, 1, 0, 1, 1),
(48130, 15576, 0.0065, 1, 0, 1, 1),
(48130, 15578, 0.0086, 1, 0, 1, 1),
(48130, 15580, 0.0065, 1, 0, 1, 1),
(48130, 15582, 0.0108, 1, 0, 1, 1),
(48130, 15583, 0.0022, 1, 0, 1, 1),
(48130, 15584, 0.0065, 1, 0, 1, 1),
(48130, 15589, 0.0151, 1, 0, 1, 1),
(48130, 15591, 0.0043, 1, 0, 1, 1),
(48130, 15595, 0.0086, 1, 0, 1, 1),
(48130, 15596, 0.0043, 1, 0, 1, 1),
(48130, 15597, 0.0129, 1, 0, 1, 1),
(48130, 15600, 0.0065, 1, 0, 1, 1),
(48130, 15603, 0.0086, 1, 0, 1, 1),
(48130, 15606, 0.0022, 1, 0, 1, 1),
(48130, 15607, 0.0065, 1, 0, 1, 1),
(48130, 15610, 0.0065, 1, 0, 1, 1),
(48130, 15611, 0.0022, 1, 0, 1, 1),
(48130, 15612, 0.0022, 1, 0, 1, 1),
(48130, 15613, 0.0065, 1, 0, 1, 1),
(48130, 15963, 0.0022, 1, 0, 1, 1),
(48130, 15964, 0.0022, 1, 0, 1, 1),
(48130, 15978, 0.0043, 1, 0, 1, 1),
(48130, 15979, 0.0065, 1, 0, 1, 1),
(48130, 19933, 5.5075, 1, 0, 1, 1),
(48130, 19937, 15.079, 1, 0, 1, 1),
(48130, 19938, 14.9047, 1, 0, 1, 1),
(48130, 21940, 0.0066, 1, 0, 1, 1),
(48132, 866, 0.022, 1, 0, 1, 1),
(48132, 1613, 0.0441, 1, 0, 1, 1),
(48132, 3802, 0.1764, 1, 0, 1, 1),
(48132, 3805, 0.3, 1, 0, 1, 1),
(48132, 3809, 0.3053, 1, 0, 1, 1),
(48132, 3816, 0.2, 1, 0, 1, 1),
(48132, 3936, 0.1527, 1, 0, 1, 1),
(48132, 3937, 0.2, 1, 0, 1, 1),
(48132, 3963, 0.2, 1, 0, 1, 1),
(48132, 3966, 0.1323, 1, 0, 1, 1),
(48132, 3986, 0.229, 1, 0, 1, 1),
(48132, 4002, 0.1527, 1, 0, 1, 1),
(48132, 4023, 0.2, 1, 0, 1, 1),
(48132, 4026, 0.2, 1, 0, 1, 1),
(48132, 4087, 0.022, 1, 0, 1, 1),
(48132, 4867, 28.9462, 1, 0, 1, 1),
(48132, 5215, 0.022, 1, 0, 1, 1),
(48132, 6444, 38.8668, 1, 0, 1, 1),
(48132, 7910, 0.8397, 1, 0, 1, 1),
(48132, 8154, 20.5042, 1, 0, 1, 1),
(48132, 8169, 0.6723, 1, 0, 1, 1),
(48132, 11167, 0.022, 1, 0, 1, 1),
(48132, 11972, 0.0441, 1, 0, 1, 1),
(48132, 12037, 18.9153, 1, 0, 1, 1),
(48132, 13119, 0.022, 1, 0, 1, 1),
(48132, 14216, 0.0441, 1, 0, 1, 1),
(48132, 14220, 0.022, 1, 0, 1, 1),
(48132, 14228, 0.022, 1, 0, 1, 1),
(48132, 14233, 0.022, 1, 0, 1, 1),
(48132, 14238, 0.022, 1, 0, 1, 1),
(48132, 14242, 0.0441, 1, 0, 1, 1),
(48132, 14250, 0.022, 1, 0, 1, 1),
(48132, 14423, 0.022, 1, 0, 1, 1),
(48132, 14591, 0.0441, 1, 0, 1, 1),
(48132, 14592, 0.022, 1, 0, 1, 1),
(48132, 14605, 0.7055, 1, 0, 1, 1),
(48132, 14770, 0.022, 1, 0, 1, 1),
(48132, 14771, 0.022, 1, 0, 1, 1),
(48132, 14825, 0.0882, 1, 0, 1, 1),
(48132, 14826, 0.022, 1, 0, 1, 1),
(48132, 14827, 0.022, 1, 0, 1, 1),
(48132, 14832, 0.022, 1, 0, 1, 1),
(48132, 14896, 0.0661, 1, 0, 1, 1),
(48132, 14897, 0.0441, 1, 0, 1, 1),
(48132, 14898, 0.022, 1, 0, 1, 1),
(48132, 14903, 0.022, 1, 0, 1, 1),
(48132, 15158, 0.0661, 1, 0, 1, 1),
(48132, 15214, 0.022, 1, 0, 1, 1),
(48132, 15234, 0.0882, 1, 0, 1, 1),
(48132, 15244, 0.022, 1, 0, 1, 1),
(48132, 15261, 0.0661, 1, 0, 1, 1),
(48132, 15359, 0.022, 1, 0, 1, 1),
(48132, 15371, 0.022, 1, 0, 1, 1),
(48132, 15567, 0.022, 1, 0, 1, 1),
(48132, 15578, 0.022, 1, 0, 1, 1),
(48132, 15580, 0.1102, 1, 0, 1, 1),
(48132, 15589, 0.022, 1, 0, 1, 1),
(48132, 15603, 0.022, 1, 0, 1, 1),
(48132, 15606, 0.022, 1, 0, 1, 1),
(48132, 15612, 0.0441, 1, 0, 1, 1),
(48132, 19937, 6.1067, 1, 0, 1, 1),
(48132, 19938, 6.1728, 1, 0, 1, 1),
(48132, 56238, 17.0194, 1, 0, 1, 1),
(48132, 56239, 2.888, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (736646, 736647);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28142';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5589, 28142, 0, 1, 74, 0);

UPDATE `quest_template` SET `PrevQuestId`='28142' WHERE `Id` IN (28158, 28157);
UPDATE `quest_template` SET `PrevQuestId`='28159' WHERE `Id`=28161;

UPDATE `creature_template` SET `mindmg`=61, `maxdmg`=47, `attackpower`=23, `dmg_multiplier`=1.1, `lootid`=47763 WHERE `entry`=47763;
UPDATE `creature_template` SET `mindmg`=61, `maxdmg`=47, `attackpower`=23, `dmg_multiplier`=1.1, `lootid`=47766 WHERE `entry`=47766;

-- Bound Fury
SET @ENTRY := 47763;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,80549,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Gout of Flame"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1500,1500,2500,2500,11,35377,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scorch"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3500,3500,6500,6500,11,11970,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire Nova"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,18500,18500,18500,18500,11,80549,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Gout of Flame");

-- Bound Vortex
SET @ENTRY := 47766;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,83004,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Storm Cloud"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1500,1500,3000,3000,11,57780,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Bolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,15500,15500,15500,15500,11,83004,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Storm Cloud");

UPDATE `creature_template` SET `maxdmg`=66, `dmgschool`=92, `dmg_multiplier`=1.1 WHERE `entry`=47777;

-- Animus
SET @ENTRY := 47777;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,1,100,0,0,0,0,0,11,80066,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Tornado"),
(@ENTRY,@SOURCETYPE,1,0,0,1,100,0,1500,1500,2500,2500,11,32018,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Call Lightning"),
(@ENTRY,@SOURCETYPE,2,0,0,1,100,0,3500,3500,4500,4500,11,79539,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Crashing Wave"),
(@ENTRY,@SOURCETYPE,3,0,0,1,100,0,5500,5500,6500,6500,11,83018,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Magma Wave"),
(@ENTRY,@SOURCETYPE,4,0,0,1,100,0,9500,9500,9500,9500,11,32712,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Nova"),
(@ENTRY,@SOURCETYPE,5,0,0,1,100,0,12500,12500,12500,12500,11,79872,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shockwave"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,88928,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Phase 1"),
(@ENTRY,@SOURCETYPE,7,0,60,1,100,0,8000,8000,0,0,19,33536,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Flags"),
(@ENTRY,@SOURCETYPE,8,0,60,1,100,0,8000,8000,0,0,28,52952,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Shield"),
(@ENTRY,@SOURCETYPE,9,0,60,1,100,0,8000,8000,0,0,49,0,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Update - Attack Player"),
(@ENTRY,@SOURCETYPE,10,0,7,0,100,0,0,0,0,0,18,33536,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Evade - Reset Flags");

UPDATE `creature_template` SET `lootid`=47777 WHERE `entry`=47777;

DELETE FROM `creature_loot_template` WHERE `item` = '63096';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(47777, 63096, -100, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (39972, 39949, 39992);
UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `id` IN (39949, 39972);


-- Caryssia Moonhunter
SET @ENTRY := 39946;
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
(@ENTRY,@SOURCETYPE,16,5,9,1,100,0,0,5,9000,11000,11,40505,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Cleave"),
(@ENTRY,@SOURCETYPE,17,0,0,1,100,0,5000,8000,35000,36000,11,13730,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,18,0,0,1,100,0,6000,9000,120000,125000,11,32064,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,19,0,11,0,100,1,0,0,0,0,11,7165,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Battle Stance on Spawn"),
(@ENTRY,@SOURCETYPE,20,0,4,0,100,0,0,0,0,0,42,99,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0, `dynamicflags`=0 WHERE `entry`=39972;
UPDATE `creature_template` SET `mindmg`=52, `maxdmg`=78, `attackpower`=19 WHERE `entry` IN (39949, 39972);
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (39949, 39972);
UPDATE `creature_template` SET `InhabitType`=1 WHERE `entry`=39992;
UPDATE `creature_template` SET `minrangedmg`=42, `maxrangedmg`=62, `rangedattackpower`=15 WHERE `entry`=39972;

-- Rendow
SET @ENTRY := 39992;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,99,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,25488,0,0,0,85,75326,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Start Boat Event");

DELETE FROM `waypoints` WHERE `entry` = '40408';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(40408, 1, -4418.39, -910.13, 0.0, 'Canoe WP'),
(40408, 2, -4779.51, -1188.64, 0.0, 'Canoe WP'),
(40408, 3, -5084.70, -1266.09, 0.0, 'Canoe WP'),
(40408, 4, -5290.75, -1511.80, 0.0, 'Canoe WP'),
(40408, 5, -5330.72, -1705.90, 0.0, 'Canoe WP'),
(40408, 6, -5702.31, -2235.90, 0.0, 'Canoe WP'),
(40408, 7, -5699.25, -2575.25, 0.0, 'Canoe WP'),
(40408, 8, -5553.04, -2797.29, 0.0, 'Canoe WP'),
(40408, 9, -5587.92, -2963.98, 0.0, 'Canoe WP'),
(40408, 10, -5579.43, -3152.47, 0.0, 'Canoe WP'),
(40408, 11, -5647.77, -3434.35, 0.0, 'Canoe WP'),
(40408, 12, -5787.50, -3379.25, 0.0, 'Canoe WP'),
(40408, 13, -6014.20, -3700.12, 0.0, 'Canoe WP'),
(40408, 14, -6256.54, -3767.58, 0.0, 'Canoe WP'),
(40408, 15, -6226.42, -3835.77, 0.0, 'Canoe WP'),
(40408, 16, -6203.85, -3909.83, 0.0, 'Canoe WP');

UPDATE `creature_template` SET `VehicleId`=740, `speed_walk`=3, `speed_run`=3.14286, `InhabitType`=4 WHERE `entry`=40408;

-- Water Traveler
SET @ENTRY := 40408;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,40408,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,0,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger");

DELETE FROM `spell_target_position` WHERE `id` = '75357';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(75357, 1, -4377.40, -832.16, 0.0, 3.97);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '40408';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(40408, 46598, 0);

UPDATE `creature_template` SET `VehicleId`=740 WHERE `entry`=40390;
UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry`=40408;

DELETE FROM `creature_text` WHERE `entry`=40598;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40598,0,0,'Drag Master Miglen escapes from the outhouse and gestures wildly up at the speedbarge.',16,0,100,0,14,0,'Comment');

-- Drag Master Miglen
SET @ENTRY := 40598;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,40598,0,0,69,0,0,0,0,0,0,8,0,0,0,-6198.04,-3907.3,0.87,0.73,"After Talk 0 - Move to Ground"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=736599;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '25524';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5041, 25524, 1, 66, 0);

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=40591;
UPDATE `quest_template` SET `PrevQuestId`='25561' WHERE `Id`=25588;

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '25532';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 5041, 25532, 25532, 1, 10);

UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=736645;
UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=212321;

DELETE FROM `creature` WHERE `guid` = '212500';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(212500, 40726, 1, 1, 2, 0, 1, -6187.86, -3906.39, 4.93363, 2.39677, 300, 0, 0, 1676, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '212500';
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(212500, 0, 0, 0, 0, 431, NULL);

UPDATE `creature_template` SET `gossip_menu_id`=11428 WHERE `entry`=40726;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11428 AND `id`=0;

-- Mazzer Stripscrew
SET @ENTRY := 40726;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11428,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11428,0,0,0,85,75859,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Riverboat"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,40726,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11428,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,2,62,0,100,0,11428,1,0,0,85,75976,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Riverboat");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11428' AND `id` = '1';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11428, 1, 'Get me into my boat, Mazzer.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=11428 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11428, 0, 0, 0, 9, 0, 25532, 0, 0, 0, 0, 0, '', 'Mazzer - Show gossip only if quest 25532 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=11428 AND `SourceEntry` = '1';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11428, 1, 0, 0, 9, 0, 25561, 0, 0, 0, 0, 0, '', 'Mazzer - Show gossip only if quest 25561 is active');

UPDATE `quest_template` SET `RequiredSpellCast2`=75833 WHERE `Id`=25532;

DELETE FROM `creature_involvedrelation` WHERE `id` = '40475' AND `quest` = '25532';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(40475, 25532);

DELETE FROM `spell_area` WHERE `spell` = '55858' AND `quest_start` = '25561';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(55858, 400, 25561, 25561, 1, 10);

UPDATE `creature` SET `phaseMask`=6 WHERE `guid`=212500;
UPDATE `creature` SET `phaseMask`=7 WHERE `guid`=212321;

UPDATE `quest_template` SET `PrevQuestId`='25561' WHERE `Id`=25590;
UPDATE `quest_template` SET `PrevQuestId`='25561' WHERE `Id`=28031;
UPDATE `quest_template` SET `PrevQuestId`='25561' WHERE `Id`=25744;

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=41199;

DELETE FROM `creature_text` WHERE `entry`=41199;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41199,0,0,'Trackmaster Zherin is stunned. Steal the Horde\'s Proposal now!',42,0,100,0,0,0,'Comment');

-- Trackmaster Zherin
SET @ENTRY := 41199;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
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
(@ENTRY,@SOURCETYPE,16,0,9,1,100,0,0,5,13000,14000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Heroic Strike on Close"),
(@ENTRY,@SOURCETYPE,17,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,18,19,2,0,100,1,0,10,0,0,1,0,5000,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On HP 10% - Talk 0"),
(@ENTRY,@SOURCETYPE,19,20,61,0,100,0,0,0,0,0,11,78320,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Stun"),
(@ENTRY,@SOURCETYPE,20,21,61,0,100,0,0,0,0,0,2,31,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction 31"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,41,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,22,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,23,0,64,0,100,0,0,0,0,0,56,55808,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit");

UPDATE `creature_template` SET `mindmg`=55, `maxdmg`=82, `attackpower`=21 WHERE `entry`=41199;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=213035;

DELETE FROM `spell_area` WHERE `spell` = '76708' AND `quest_start` = '25627';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(76708, 5028, 25627, 25704, 0, 0, 2, 1, 64, 11);

DELETE FROM `creature` WHERE `guid` = '736538';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(736538, 41463, 1, 1, 1, 0, 0, -5438.34, -2423.82, 90.2828, 1.37881, 300, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = '41463';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(41463, 0, 0, 65536, 1, 0, '77578');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '25871';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 484, 25871, 25871, 1, 8, 11);

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=41463;

-- Captured Feralas Sentinel
SET @ENTRY := 41463;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,85,77583,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Sentinel");

DELETE FROM `creature_text` WHERE `entry`=41464;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41464,0,0,'Ishnu-alah. Good fortune to you.',12,0,100,0,0,0,'Comment'),
(41464,1,0,'I will rejoin you soon. We will teach these Grimtotem savages the meaning of honor.',12,0,100,0,0,0,'Comment');

-- Feralas Sentinel
SET @ENTRY := 41464;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,41464,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,41464,0,0,69,0,0,0,0,0,0,8,0,0,0,-5429.78,-2377.51,87.51,1.39,"After Talk 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=41464;

DELETE FROM `spell_area` WHERE `spell` = '84657' AND `quest_start` = '25871';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_end_status`) VALUES
(84657, 2097, 25871, 27329, 1, 11),
(84657, 5675, 25871, 27329, 1, 11);

UPDATE `creature_template` SET `mindmg`=74, `maxdmg`=92, `attackpower`=25, `dmg_multiplier`=1.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45277;

-- Feralas Sentinel
SET @ENTRY := 45277;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,81219,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2500,2500,5000,5000,11,85625,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,6000,6000,11,21008,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mocking Blow"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,12500,12500,12500,12500,11,37683,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Evasion");

DELETE FROM `creature_equip_template` WHERE `entry` = '45277';
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(45277, 1, 17382, 17382, 14118);

DELETE FROM `creature_text` WHERE `entry`=45277;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45277,0,0,'Ishnu-alah.',12,0,100,0,0,0,'Comment'),
(45277,1,0,'Until we meet again.',12,0,100,0,0,0,'Comment');

-- Feralas Sentinel
SET @ENTRY := 45277;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,81219,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2500,2500,5000,5000,11,85625,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,6000,6000,11,21008,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mocking Blow"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,12500,12500,12500,12500,11,37683,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Evasion"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,6,0,4,0,100,0,0,0,0,0,42,99,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,10,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 1"),
(@ENTRY,@SOURCETYPE,8,9,52,0,100,0,1,45277,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,28,84657,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura");

UPDATE `creature_template` SET `InhabitType`=1 WHERE `entry`=45277;
UPDATE `quest_template` SET `PrevQuestId`='27275' WHERE `Id` IN (27310, 27312, 27314);
UPDATE `creature_template` SET `faction_A`=2250, `faction_H`=2250 WHERE `entry`=45277;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN
(211416, 211417, 211474, 211228, 211229, 211166, 211167, 211118, 211119, 211051, 211050, 211095, 211094, 211120, 211121);
UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id`=27329;
UPDATE `quest_template` SET `PrevQuestId`='28159' WHERE `Id`=28160;