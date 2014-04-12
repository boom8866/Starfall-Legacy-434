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
(75859, 1, -6218.27, -3918.45, 0.0, 5.51),
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
UPDATE `quest_template` SET `RequiredSpellCast2`=75823 WHERE `Id`=25533;

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

DELETE FROM `spell_area` WHERE `spell` = '49416';
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
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,60000,60000,60000,60000,2,230,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction");

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
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_end_status`) VALUES
(76708, 5028, 25628, 25704, 1, 11);

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
(@ENTRY,@SOURCETYPE,8,0,54,0,100,0,0,0,0,0,18,262144,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Stunned");

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
(3470, 'The sheer vastness of the nether is no excuse for using it as a garbage repository! Your Portal and Teleport spells are a great privilege and responsibility, and carelessly casting the waste from your noontime meals into a portal could have GRAVE CONSEQUENCES for all of Azeroth! Please secure all objects when traveling via portal and report any lost objects to the Kirin Tor council at once. Read the latest edition of “Thinking with Portals – A Memorandum on Proper Portal Usage” for all information regarding portal use.', 3471),
(3471, 'If this problem grows any further out of hand, I will be forced to insist that all portal travelers relinquish their weaponry and personal hygiene supplies before embarking. And the next time my lecture notes appear among the rubbish, I will personally transform the heads of all apprentices into dunce caps!\r\n\r\n--Archmage Runeweaver', 0);