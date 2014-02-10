DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27963 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=28512 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27963 AND `SourceId`=0 AND `ElseGroup`=2 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=28582 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27963 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=28581 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

DELETE FROM `creature_loot_template` WHERE `item` = '62809';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5856, 62809, -73.1818, 1, 0, 1, 1);

UPDATE `creature_template` SET `mindmg`=72, `maxdmg`=107, `attackpower`=27 WHERE `entry` IN (47270, 47275, 47276);

DELETE FROM `creature_loot_template` WHERE `item` = '10005';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5833, 10005, -100, 1, 0, 1, 1);

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=47269;

DELETE FROM `creature_loot_template` WHERE `item` = '62805';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5853, 62805, -83.3873, 1, 0, 1, 1);

DELETE FROM `creature_text` WHERE `entry`=47269;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47269,0,0,'Lunk tired of all this killing! Lunk quits!',14,0,100,0,0,0,'Comment'),
(47269,1,0,'Lunk going to find some real adventures!',14,0,100,0,0,0,'Comment');

UPDATE `creature` SET `spawntimesecs`=120 WHERE `id`=5853;
UPDATE `quest_template` SET `PrevQuestId`='27956' WHERE `Id`=27957;
UPDATE `quest_template` SET `PrevQuestId`='27957' WHERE `Id`=27958;

-- Lunk
SET @ENTRY := 47269;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27957,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,47269,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,47269,0,0,26,27957,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Quest Complete");

UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id`=27957;
UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=45, `MovementType`=1 WHERE `id`=47278;

-- Ash Chicken
SET @ENTRY := 47278;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,56,62934,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Ash Chicken - Gossip Hello - Create Item Ash Chicken"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,0,10,0,100,0,1,5,8000,8000,11,59669,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Flee"),
(@ENTRY,@SOURCETYPE,4,0,10,0,5,0,1,6,0,0,11,81773,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Exhausted"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run");

UPDATE `creature_template` SET `IconName`='openhandglow', `npcflag`=1, `flags_extra`=2, `unit_flags`=2 WHERE `entry`=47278;

-- Glassweb Spider
SET @ENTRY := 5856;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4500,16000,20000,11,744,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Poison"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,0,20,8000,9000,11,745,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Web on Close"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,7,27959,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Quest 27959");

DELETE FROM `spell_area` WHERE `spell` = '88166';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(88166, 51, 27959, 27959, 1, 8),
(88166, 1444, 27959, 27959, 1, 8),
(88166, 247, 27959, 27959, 1, 8);

UPDATE `creature_template` SET `minlevel`=50, `maxlevel`=50, `unit_flags`=2, `npcflag`=2 WHERE `entry`=47281;

DELETE FROM `creature_text` WHERE `entry`=47281;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47281,0,0,'You hold still, spider!',14,0,100,0,0,0,'Comment'),
(47281,0,1,'Spider tummy time!',14,0,100,0,0,0,'Comment'),
(47281,0,2,'Lunk will ride you now!',14,0,100,0,0,0,'Comment'),
(47281,0,3,'Look out spider! Here come Lunk!',14,0,100,0,0,0,'Comment'),
(47281,1,0,'Here, I got you this.',12,0,100,0,0,0,'Comment'),
(47281,1,1,'See? No kill spider for venom. Just ride.',12,0,100,0,0,0,'Comment'),
(47281,1,2,'Here, you can scrape venom off Lunk\'s tummy.',12,0,100,0,0,0,'Comment'),
(47281,1,3,'I got some venom for you.',12,0,100,0,0,0,'Comment'),
(47281,2,0,'You stop killing now! Lunk doesn\'t like!',12,0,100,0,0,0,'Comment'),
(47281,2,1,'Please, no kill when Lunk is around.',12,0,100,0,0,0,'Comment'),
(47281,2,2,'No! No kill!',12,0,100,0,0,0,'Comment'),
(47281,2,3,'Why you do that? Why you kill?',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `npcflag`=16777216, `VehicleId`=591 WHERE `entry`=5856;

-- Glassweb Spider
SET @ENTRY := 5856;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4500,16000,20000,11,744,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Poison"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,0,20,8000,9000,11,745,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Web on Close"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,7,27959,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Quest 27959"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,1,50,0,0,45,0,1,0,0,0,0,11,47281,20,0,0.0,0.0,0.0,0.0,"On HP 50% - Set Data 1 to Lunk"),
(@ENTRY,@SOURCETYPE,4,0,27,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,47281,20,0,0.0,0.0,0.0,0.0,"On Death - Set Data 2 to Lunk"),
(@ENTRY,@SOURCETYPE,6,7,60,1,100,0,6000,6000,6000,6000,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (6 seconds) - Remove Passenger"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,6000,6000,6000,6000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,0,27,0,100,0,0,0,0,0,46,45,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Move Forward");

DELETE FROM `creature_involvedrelation` WHERE `id` = '47281';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(47281, 27959);

-- Lunk
SET @ENTRY := 47281;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,5,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,1,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,6,52,0,100,0,1,47281,0,0,11,46598,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Ride Spider"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,6,6,52,0,100,0,1,47281,0,0,11,88154,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Add Aura"),
(@ENTRY,@SOURCETYPE,7,0,20,0,100,0,27959,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Force Despawn");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27959;

DELETE FROM `spell_area` WHERE `spell` = '90161';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`) VALUES
(90161, 1446, 27965, 1, 66);

UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (14634, 14625);
UPDATE `quest_template` SET `Flags`=8 WHERE `Id`=28061;

DELETE FROM `creature_loot_template` WHERE `item` = '62822';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(47309, 62822, -42.4998, 1, 0, 1, 1),
(47310, 62822, -44.7357, 1, 0, 1, 1),
(47311, 62822, -71.8922, 1, 0, 1, 1),
(8419, 62822, -100, 1, 0, 1, 1),
(5860, 62822, -88.6511, 1, 0, 1, 1),
(5861, 62822, -87.4111, 1, 0, 1, 1),
(5862, 62822, -87.1333, 1, 0, 1, 1);

UPDATE `creature` SET `spawntimesecs`=120, `spawndist`=35, `MovementType`=1 WHERE `id` IN (5860, 5861);
UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (8419, 47311);
UPDATE `gameobject` SET `phaseMask`=1 WHERE `id`=148506;

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `area` = '1442' AND `quest_start` = '27965';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`) VALUES
(49417, 1442, 27965, 1, 66);

UPDATE `creature_template` SET `mindmg`=54, `maxdmg`=82, `attackpower`=20, `dmg_multiplier`=1.4 WHERE `entry`=47311;
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=27984;
UPDATE `conditions` SET `ConditionValue1`=27984 WHERE  `SourceTypeOrReferenceId`=15 AND `SourceGroup`=1285 AND `SourceEntry`=0 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=9 AND `ConditionTarget`=0 AND `ConditionValue1`=3377 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
UPDATE `gossip_menu_option` SET `action_menu_id`=0 WHERE  `menu_id`=1286 AND `id`=0;

-- Zamael Lunthistle
SET @ENTRY := 8436;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,1286,0,0,0,26,27984,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Select Gossip - Quest Complete"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Close Gossip");

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry`=5840;

DELETE FROM `spell_area` WHERE `spell` = '88291' AND `quest_start` = '27983';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(88291, 5615, 27983, 27983, 1, 10);

UPDATE `creature` SET `spawntimesecs`=120, `spawndist`=50, `MovementType`=1 WHERE `id` IN (5854, 47553);

DELETE FROM `creature_text` WHERE `entry`=47332;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47332,0,0,'You take dwarf\'s things. No need to kill.',12,0,100,0,0,0,'Comment'),
(47332,0,1,'He will be sleepy for a while. Lunk know. Lunk do before.',12,0,100,0,0,0,'Comment'),
(47332,0,2,'Here, I stealed this from little dwarf.',12,0,100,0,0,0,'Comment'),
(47332,0,3,'Sitting easier than killing.',12,0,100,0,0,0,'Comment'),
(47332,1,0,'Why you do that? Why you kill?',12,0,100,0,0,0,'Comment'),
(47332,1,1,'No! No kill!',12,0,100,0,0,0,'Comment'),
(47332,1,2,'You hurt Lunk\'s feelings when you kill.',12,0,100,0,0,0,'Comment'),
(47332,1,3,'Oh no! Why do you kill it?',12,0,100,0,0,0,'Comment'),
(47332,1,4,'Please, no kill when Lunk is around.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=5840;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(5840,0,0,'Ugh! Why are you WET!?',12,0,100,0,0,0,'Comment'),
(5840,0,1,'But... but...',12,0,100,0,0,0,'Comment'),
(5840,0,2,'That\'s... one... giant... keester...',12,0,100,0,0,0,'Comment'),
(5840,0,3,'Why did it have to be... a smelly ogre...',12,0,100,0,0,0,'Comment'),
(5840,0,4,'Where... did... he... come from...',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=50, `maxlevel`=50, `unit_flags`=2 WHERE `entry`=47332;

-- Dark Iron Steamsmith
SET @ENTRY := 5840;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,7000,7000,12000,15000,11,11983,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dark Iron Steamsmith - In Combat - Cast Steam Jet"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,7,27983,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Quest"),
(@ENTRY,@SOURCETYPE,2,0,12,0,100,1,10,50,0,0,45,0,1,0,0,0,0,11,47332,20,0,0.0,0.0,0.0,0.0,"On HP 50% - Set Data 1 to Lunk"),
(@ENTRY,@SOURCETYPE,3,0,12,0,100,1,10,50,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On HP 50% - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,1,3500,3500,3500,3500,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,0,0,5840,0,0,41,30000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,6,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,47332,15,0,0.0,0.0,0.0,0.0,"On Death - Set Data 2 to Lunk");

-- Lunk
SET @ENTRY := 47332;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,5,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Invoker"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,5,6,52,0,100,0,0,47332,0,0,75,56756,0,0,0,0,0,19,5840,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Sleep to Dark Iron Steamsmith"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,33,47381,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,8,0,20,0,100,0,27983,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Force Despawn");

DELETE FROM `creature_involvedrelation` WHERE `id` = '47332';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(47332, 27983);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27983;

DELETE FROM `creature_involvedrelation` WHERE `quest` = '27985';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(8436, 27985);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-100 WHERE `entry`=8566 AND `item`=18960;

DELETE FROM `creature` WHERE `guid` IN (732177, 732269, 732370);
DELETE FROM `creature_addon` WHERE `guid` IN (732177, 732269, 732370);
UPDATE `creature_template` SET `questItem3`=18960 WHERE `entry`=8566;

DELETE FROM `creature_loot_template` WHERE `entry` = '5840' AND `item` = '18960';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5840, 18960, -100, 1, 0, 1, 1);

UPDATE `creature_template` SET `mindmg`=74, `maxdmg`=112, `attackpower`=28 WHERE `entry`=47553;
UPDATE `creature_template` SET `mindmg`=80, `maxdmg`=120, `attackpower`=30 WHERE `entry`=47463;
UPDATE `creature` SET `spawndist`=35, `MovementType`=1, `spawntimesecs`=120 WHERE `id` IN (47463, 5850, 5855);

-- Magma Elemental
SET @ENTRY := 5855;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,8,13600,14500,11,11970,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Fire Nova on Close"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,35000,120000,35000,120000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Force Despawn");

-- Inferno Elemental
SET @ENTRY := 5852;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,9000,16500,22000,11,10733,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Flame Spray"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,35000,120000,35000,120000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Force Despawn");

DELETE FROM `creature_involvedrelation` WHERE `quest` = '28061';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(14625, 28061);

DELETE FROM `spell_area` WHERE `spell` = '90161' AND `quest_start` = '27986';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`) VALUES
(90161, 5628, 27986, 1, 66);

DELETE FROM `creature_loot_template` WHERE `item` = '62914';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(9318, 62914, -75.7082, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `entry`= '8338';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8338, 943, 0.0151, 1, 0, 1, 1),
(8338, 1639, 0.0136, 1, 0, 1, 1),
(8338, 1979, 0.0015, 1, 0, 1, 1),
(8338, 2100, 0.0151, 1, 0, 1, 1),
(8338, 2291, 0.0753, 1, 0, 1, 1),
(8338, 3208, 0.1356, 1, 0, 1, 1),
(8338, 3927, 4.6688, 1, 0, 1, 1),
(8338, 3939, 1.5668, 1, 0, 1, 1),
(8338, 4069, 0.003, 1, 0, 1, 1),
(8338, 4089, 0.1657, 1, 0, 1, 1),
(8338, 7517, 0.003, 1, 0, 1, 1),
(8338, 7519, 0.0105, 1, 0, 1, 1),
(8338, 7520, 0.0301, 1, 0, 1, 1),
(8338, 7527, 0.0151, 1, 0, 1, 1),
(8338, 7528, 0.0181, 1, 0, 1, 1),
(8338, 7529, 0.0151, 1, 0, 1, 1),
(8338, 7532, 0.0136, 1, 0, 1, 1),
(8338, 7536, 0.0121, 1, 0, 1, 1),
(8338, 7538, 0.0181, 1, 0, 1, 1),
(8338, 7539, 0.0105, 1, 0, 1, 1),
(8338, 7540, 0.003, 1, 0, 1, 1),
(8338, 7543, 0.0015, 1, 0, 1, 1),
(8338, 7553, 0.0166, 1, 0, 1, 1),
(8338, 7557, 0.0015, 1, 0, 1, 1),
(8338, 7611, 0.0105, 1, 0, 1, 1),
(8338, 7989, 0.0301, 1, 0, 1, 1),
(8338, 7990, 0.0452, 1, 0, 1, 1),
(8338, 8106, 0.0015, 1, 0, 1, 1),
(8338, 8107, 0.0075, 1, 0, 1, 1),
(8338, 8108, 0.003, 1, 0, 1, 1),
(8338, 8110, 0.003, 1, 0, 1, 1),
(8338, 8111, 0.0151, 1, 0, 1, 1),
(8338, 8112, 0.0075, 1, 0, 1, 1),
(8338, 8114, 0.0045, 1, 0, 1, 1),
(8338, 8115, 0.006, 1, 0, 1, 1),
(8338, 8117, 0.0075, 1, 0, 1, 1),
(8338, 8119, 0.0045, 1, 0, 1, 1),
(8338, 8121, 0.0015, 1, 0, 1, 1),
(8338, 8122, 0.0226, 1, 0, 1, 1),
(8338, 8123, 0.0136, 1, 0, 1, 1),
(8338, 8124, 0.0105, 1, 0, 1, 1),
(8338, 8125, 0.0045, 1, 0, 1, 1),
(8338, 8127, 0.0045, 1, 0, 1, 1),
(8338, 8128, 0.0045, 1, 0, 1, 1),
(8338, 8129, 0.006, 1, 0, 1, 1),
(8338, 8130, 0.0105, 1, 0, 1, 1),
(8338, 8131, 0.003, 1, 0, 1, 1),
(8338, 8132, 0.006, 1, 0, 1, 1),
(8338, 8133, 0.0151, 1, 0, 1, 1),
(8338, 8134, 0.0075, 1, 0, 1, 1),
(8338, 8138, 0.0904, 1, 0, 1, 1),
(8338, 8199, 0.009, 1, 0, 1, 1),
(8338, 8246, 0.009, 1, 0, 1, 1),
(8338, 8247, 0.0015, 1, 0, 1, 1),
(8338, 8248, 0.0603, 1, 0, 1, 1),
(8338, 8249, 0.0015, 1, 0, 1, 1),
(8338, 8250, 0.0015, 1, 0, 1, 1),
(8338, 8253, 0.0151, 1, 0, 1, 1),
(8338, 8255, 0.0015, 1, 0, 1, 1),
(8338, 8256, 0.0151, 1, 0, 1, 1),
(8338, 8257, 0.003, 1, 0, 1, 1),
(8338, 8259, 0.003, 1, 0, 1, 1),
(8338, 8260, 0.0015, 1, 0, 1, 1),
(8338, 8264, 0.0045, 1, 0, 1, 1),
(8338, 8276, 0.006, 1, 0, 1, 1),
(8338, 8279, 0.0105, 1, 0, 1, 1),
(8338, 8280, 0.0105, 1, 0, 1, 1),
(8338, 8281, 0.0226, 1, 0, 1, 1),
(8338, 8282, 0.0045, 1, 0, 1, 1),
(8338, 8315, 0.003, 1, 0, 1, 1),
(8338, 8389, 0.0045, 1, 0, 1, 1),
(8338, 8390, 0.0075, 1, 0, 1, 1),
(8338, 9293, 0.0301, 1, 0, 1, 1),
(8338, 9295, 0.006, 1, 0, 1, 1),
(8338, 9298, 0.009, 1, 0, 1, 1),
(8338, 9905, 0.0045, 1, 0, 1, 1),
(8338, 9913, 0.009, 1, 0, 1, 1),
(8338, 9914, 0.0015, 1, 0, 1, 1),
(8338, 9924, 0.009, 1, 0, 1, 1),
(8338, 9936, 0.0121, 1, 0, 1, 1),
(8338, 9937, 0.0075, 1, 0, 1, 1),
(8338, 9938, 0.0301, 1, 0, 1, 1),
(8338, 9939, 0.0075, 1, 0, 1, 1),
(8338, 9940, 0.0015, 1, 0, 1, 1),
(8338, 9941, 0.0105, 1, 0, 1, 1),
(8338, 9942, 0.0603, 1, 0, 1, 1),
(8338, 9945, 0.0045, 1, 0, 1, 1),
(8338, 9947, 0.0045, 1, 0, 1, 1),
(8338, 9948, 0.006, 1, 0, 1, 1),
(8338, 9949, 0.0121, 1, 0, 1, 1),
(8338, 9951, 0.0603, 1, 0, 1, 1),
(8338, 9952, 0.0015, 1, 0, 1, 1),
(8338, 9954, 0.1808, 1, 0, 1, 1),
(8338, 9955, 0.006, 1, 0, 1, 1),
(8338, 9957, 0.0753, 1, 0, 1, 1),
(8338, 9958, 0.003, 1, 0, 1, 1),
(8338, 9960, 0.0603, 1, 0, 1, 1),
(8338, 9961, 0.0151, 1, 0, 1, 1),
(8338, 9962, 0.0136, 1, 0, 1, 1),
(8338, 9963, 0.0015, 1, 0, 1, 1),
(8338, 9964, 0.0226, 1, 0, 1, 1),
(8338, 9965, 0.0753, 1, 0, 1, 1),
(8338, 10058, 0.009, 1, 0, 1, 1),
(8338, 10059, 0.0015, 1, 0, 1, 1),
(8338, 10060, 0.0075, 1, 0, 1, 1),
(8338, 10062, 0.009, 1, 0, 1, 1),
(8338, 10063, 0.003, 1, 0, 1, 1),
(8338, 10066, 0.009, 1, 0, 1, 1),
(8338, 10067, 0.0136, 1, 0, 1, 1),
(8338, 10068, 0.0045, 1, 0, 1, 1),
(8338, 10069, 0.0301, 1, 0, 1, 1),
(8338, 10071, 0.003, 1, 0, 1, 1),
(8338, 10072, 0.003, 1, 0, 1, 1),
(8338, 10075, 0.0452, 1, 0, 1, 1),
(8338, 10076, 0.003, 1, 0, 1, 1),
(8338, 10079, 0.0603, 1, 0, 1, 1),
(8338, 10080, 0.0015, 1, 0, 1, 1),
(8338, 10081, 0.0301, 1, 0, 1, 1),
(8338, 10083, 0.0301, 1, 0, 1, 1),
(8338, 10084, 0.003, 1, 0, 1, 1),
(8338, 10086, 0.0015, 1, 0, 1, 1),
(8338, 10092, 0.009, 1, 0, 1, 1),
(8338, 10093, 0.0015, 1, 0, 1, 1),
(8338, 10127, 0.006, 1, 0, 1, 1),
(8338, 10131, 0.003, 1, 0, 1, 1),
(8338, 10132, 0.003, 1, 0, 1, 1),
(8338, 10134, 0.0015, 1, 0, 1, 1),
(8338, 10174, 0.0452, 1, 0, 1, 1),
(8338, 10180, 0.0015, 1, 0, 1, 1),
(8338, 10190, 0.003, 1, 0, 1, 1),
(8338, 10191, 0.0452, 1, 0, 1, 1),
(8338, 10196, 0.0105, 1, 0, 1, 1),
(8338, 10201, 0.0105, 1, 0, 1, 1),
(8338, 10202, 0.009, 1, 0, 1, 1),
(8338, 10205, 0.006, 1, 0, 1, 1),
(8338, 10206, 0.0151, 1, 0, 1, 1),
(8338, 10207, 0.009, 1, 0, 1, 1),
(8338, 10208, 0.0151, 1, 0, 1, 1),
(8338, 10209, 0.003, 1, 0, 1, 1),
(8338, 10239, 0.0015, 1, 0, 1, 1),
(8338, 10243, 0.0045, 1, 0, 1, 1),
(8338, 10320, 0.009, 1, 0, 1, 1),
(8338, 10603, 0.003, 1, 0, 1, 1),
(8338, 11208, 0.0753, 1, 0, 1, 1),
(8338, 11225, 0.006, 1, 0, 1, 1),
(8338, 11226, 0.003, 1, 0, 1, 1),
(8338, 11975, 0.0136, 1, 0, 1, 1),
(8338, 11976, 0.0015, 1, 0, 1, 1),
(8338, 11988, 0.006, 1, 0, 1, 1),
(8338, 11989, 0.0105, 1, 0, 1, 1),
(8338, 12001, 0.0045, 1, 0, 1, 1),
(8338, 12013, 0.003, 1, 0, 1, 1),
(8338, 12024, 0.003, 1, 0, 1, 1),
(8338, 12032, 0.0045, 1, 0, 1, 1),
(8338, 12043, 0.0015, 1, 0, 1, 1),
(8338, 12691, 0.0045, 1, 0, 1, 1),
(8338, 13018, 0.0015, 1, 0, 1, 1),
(8338, 13021, 0.0151, 1, 0, 1, 1),
(8338, 13043, 0.0151, 1, 0, 1, 1),
(8338, 13076, 0.0301, 1, 0, 1, 1),
(8338, 13085, 0.0151, 1, 0, 1, 1),
(8338, 13089, 0.0151, 1, 0, 1, 1),
(8338, 13102, 0.006, 1, 0, 1, 1),
(8338, 13128, 0.0015, 1, 0, 1, 1),
(8338, 13134, 0.0015, 1, 0, 1, 1),
(8338, 15216, 0.0166, 1, 0, 1, 1),
(8338, 15227, 0.0151, 1, 0, 1, 1),
(8338, 15235, 0.0121, 1, 0, 1, 1),
(8338, 15236, 0.0301, 1, 0, 1, 1),
(8338, 15245, 0.0105, 1, 0, 1, 1),
(8338, 15252, 0.0196, 1, 0, 1, 1),
(8338, 15253, 0.0015, 1, 0, 1, 1),
(8338, 15263, 0.003, 1, 0, 1, 1),
(8338, 15274, 0.003, 1, 0, 1, 1),
(8338, 15279, 0.0347, 1, 0, 1, 1),
(8338, 15291, 0.0603, 1, 0, 1, 1),
(8338, 15323, 0.2862, 1, 0, 1, 1),
(8338, 15937, 0.003, 1, 0, 1, 1),
(8338, 21949, 0.0904, 1, 0, 1, 1),
(8338, 62916, -100, 1, 0, 1, 10);

DELETE FROM `creature_loot_template` WHERE `item`= '62916';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8338, 62916, -100, 1, 0, 3, 10),
(8566, 62916, -77.8105, 1, 0, 3, 10);

UPDATE `quest_template` SET `PrevQuestId`='28052' WHERE `Id` IN (28054, 28055, 28056);
UPDATE `gameobject` SET `phaseMask`=3 WHERE `id` IN (149030, 149025, 149031, 149032);
UPDATE `gameobject` SET `phaseMask`=2 WHERE `id` IN (148996, 149020, 149017, 149019);

-- Tower Fire
SET @ENTRY := 149019;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,1500,1500,23000,23000,44,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 1.5 Secs - Set Game Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,20000,20000,23000,23000,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 20 Secs - Set Phase 2"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,21000,21000,23000,23000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 21 Secs - Set Event Phase 0");

-- Tower Fire
SET @ENTRY := 149017;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,1500,1500,23000,23000,44,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 1.5 Secs - Set Game Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,20000,20000,23000,23000,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 20 Secs - Set Phase 2"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,21000,21000,23000,23000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 21 Secs - Set Event Phase 0");

-- Tower Fire
SET @ENTRY := 148996;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,1500,1500,23000,23000,44,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 1.5 Secs - Set Game Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,20000,20000,23000,23000,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 20 Secs - Set Phase 2"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,21000,21000,23000,23000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 21 Secs - Set Event Phase 0");

-- Tower Fire
SET @ENTRY := 149020;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,1500,1500,23000,23000,44,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 1.5 Secs - Set Game Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,20000,20000,23000,23000,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 20 Secs - Set Phase 2"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,21000,21000,23000,23000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update 21 Secs - Set Event Phase 0");

-- Sentry Brazier
SET @ENTRY := 149031;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,3000,3000,3000,3000,45,0,1,0,0,0,0,15,0,80,0,0.0,0.0,0.0,0.0,"Update (3 seconds) - Set Data 1 to Fire"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,4000,4000,4000,4000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (4 seconds) - Set Phase 0");

-- Sentry Brazier
SET @ENTRY := 149030;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,3000,3000,3000,3000,45,0,1,0,0,0,0,15,0,80,0,0.0,0.0,0.0,0.0,"Update (3 seconds) - Set Data 1 to Fire"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,4000,4000,4000,4000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (4 seconds) - Set Phase 0");

-- Sentry Brazier
SET @ENTRY := 149032;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,3000,3000,3000,3000,45,0,1,0,0,0,0,15,0,80,0,0.0,0.0,0.0,0.0,"Update (3 seconds) - Set Data 1 to Fire"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,4000,4000,4000,4000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (4 seconds) - Set Phase 0");

-- Sentry Brazier
SET @ENTRY := 149025;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,3000,3000,3000,3000,45,0,1,0,0,0,0,15,0,80,0,0.0,0.0,0.0,0.0,"Update (3 seconds) - Set Data 1 to Fire"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,4000,4000,4000,4000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (4 seconds) - Set Phase 0");

SET @OGUID := 400000;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+10;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+0, 149017, 0, 1, 2, -6928.98, -1440.92, 241.454, 1.1915, 0, 0, 0.56113, 0.827728, 300, 0, 1),
(@OGUID+1, 149017, 0, 1, 2, -6921.29, -1429.04, 256.914, 2.48348, 0, 0, 0.946348, 0.323149, 300, 0, 1),
(@OGUID+2, 149017, 0, 1, 2, -6919.26, -1438.44, 253.048, 2.47563, 0, 0, 0.945072, 0.326863, 300, 0, 1),
(@OGUID+3, 149017, 0, 1, 2, -6927.71, -1438.67, 270.841, 1.55279, 0, 0, 0.700711, 0.713445, 300, 0, 1),
(@OGUID+4, 149017, 0, 1, 2, -6938.33, -1432.66, 270.059, 0.0212605, 0, 0, 0.01063, 0.999943, 300, 0, 1),
(@OGUID+5, 149017, 0, 1, 2, -6932.8, -1427.7, 251.91, 2.04999, 0, 0, 0.854713, 0.519101, 300, 0, 1),
(@OGUID+6, 149017, 0, 1, 2, -6917.17, -1432.39, 245.245, 3.08279, 0, 0, 0.999568, 0.0293955, 300, 0, 1),
(@OGUID+7, 149017, 0, 1, 2, -6937.85, -1432.85, 256.215, 0.247503, 0, 0, 0.123436, 0.992353, 300, 0, 1),
(@OGUID+8, 149017, 0, 1, 2, -6932.73, -1423.47, 274.387, 4.37085, 0, 0, 0.816988, -0.576655, 300, 0, 1),
(@OGUID+9, 149017, 0, 1, 2, -6920.14, -1434.54, 270.94, 1.72406, 0, 0, 0.759166, 0.650897, 300, 0, 1),
(@OGUID+10, 149017, 0, 1, 2, -6930.36, -1423.44, 262.909, 1.89292, 0, 0, 0.81135, 0.58456, 300, 0, 1);

DELETE FROM `spell_area` WHERE `spell` = '84481' AND `quest_start` = '28033';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(84481, 5628, 28033, 1, 74, 0);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12265 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12265;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12265, 0, 0, 0, 9, 0, 28034, 0, 0, 0, 0, 0, '', 'Iron Summit Guard - Show gossip only if quest 28034 is active');

-- Iron Summit Guard
SET @ENTRY := 47434;
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
(@ENTRY,@SOURCETYPE,16,0,2,1,100,1,0,15,0,0,22,2,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"At 15% HP - Set Phase 2"),
(@ENTRY,@SOURCETYPE,17,0,2,2,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,18,19,7,2,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,19,0,61,2,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,20,0,2,2,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,21,0,9,1,100,0,0,20,8000,9000,11,12024,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Net on Close"),
(@ENTRY,@SOURCETYPE,22,0,62,0,100,0,12265,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,23,24,62,0,100,0,12265,0,0,0,33,47434,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,24,25,61,0,100,0,0,0,0,0,17,94,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Dance!"),
(@ENTRY,@SOURCETYPE,25,26,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Npc Flag"),
(@ENTRY,@SOURCETYPE,26,0,61,0,100,0,0,0,0,0,41,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=5967 AND `id`=1;

DELETE FROM `conditions` WHERE `SourceGroup`=5967;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 5967, 0, 0, 0, 9, 0, 28052, 0, 0, 0, 0, 0, '', 'Show gossip only if quest 28052 is active');

UPDATE `creature_template` SET `minlevel`=50, `maxlevel`=50, `speed_run`=4.14286, `InhabitType`=4, `VehicleId`=1266 WHERE `entry`=47467;

DELETE FROM `waypoints` WHERE `entry` = '47467';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47467, 1, -6967.83, -1286.47, 295.91, 'Brotherhood Flying Machine WP'),
(47467, 2, -7027.80, -1244.50, 292.14, 'Brotherhood Flying Machine WP'),
(47467, 3, -7018.77, -1195.65, 276.82, 'Brotherhood Flying Machine WP'),
(47467, 4, -6974.21, -1189.64, 246.28, 'Brotherhood Flying Machine WP'),
(47467, 5, -6947.20, -1255.75, 214.54, 'Brotherhood Flying Machine WP'),
(47467, 6, -6914.70, -1418.94, 313.43, 'Brotherhood Flying Machine WP'),
(47467, 7, -6797.26, -1339.93, 324.45, 'Brotherhood Flying Machine WP'),
(47467, 8, -6914.70, -1418.94, 313.43, 'Brotherhood Flying Machine WP'),
(47467, 9, -7059.21, -1275.22, 304.84, 'Brotherhood Flying Machine WP'),
(47467, 10, -7101.00, -1266.31, 270.84, 'Brotherhood Flying Machine WP');

-- Lanie Reed
SET @ENTRY := 2941;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Lanie Reed - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Lanie Reed - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Lanie Reed - On Aggro - Say Line 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,5967,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,5967,1,0,0,85,88498,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Flight Machine"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,5967,1,0,0,75,65141,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Phase");

-- Doug Deepdown
SET @ENTRY := 47927;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Doug Deepdown - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Doug Deepdown - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Doug Deepdown - On Aggro - Say Line 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,5967,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,5967,1,0,0,85,88498,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Flight Machine"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,5967,1,0,0,75,65141,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Phase");

-- Brotherhood Flying Machine
SET @ENTRY := 47467;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,47467,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,9,0,0,0,33,47467,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,10,0,0,0,28,63313,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 10 - Remove Passenger");

UPDATE `creature_template` SET `npcflag`=8193, `gossip_menu_id`=5967 WHERE `entry`=47927;
UPDATE `creature` SET `spawntimesecs`=120, `spawndist`=0, `MovementType`=0, `phaseMask`=2 WHERE `id`=47470;

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '28052';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 246, 28052, 28052, 1, 8);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-63313' AND `spell_effect` = '-65141';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-63313, -65141, 'Remove Phase on Remove Vehicle');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12271 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=5843;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(5843,0,0,'Never! I love work for the Dark Iron!',12,0,100,0,0,0,'Comment'),
(5843,0,1,'Intruder! The intruder is trying to save me!',12,0,100,0,0,0,'Comment'),
(5843,1,0,'Oh, thank you! Thank you!',12,0,100,0,0,0,'Comment'),
(5843,1,1,'It\'s about time! I\'m sick of being a slave.',12,0,100,0,0,0,'Comment'),
(5843,1,2,'I knew the Thorium Brotherhood would come through!',12,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceGroup`=12271;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12271, 0, 0, 0, 9, 0, 28055, 0, 0, 0, 0, 0, '', 'Slave Worker - Show gossip only if quest 28055 is active');

-- Slave Worker
SET @ENTRY := 5843;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,11000,12000,11,11971,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Sunder Armor"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12271,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,3,62,0,50,0,12271,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 1 (Flee)"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-6602.14,-1194.68,185.4,3.14,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,10,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (5 seconds)"),
(@ENTRY,@SOURCETYPE,6,7,62,0,75,0,12271,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0 (Fight)"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Aggressive"),
(@ENTRY,@SOURCETYPE,8,9,61,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction Hostile"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,49,14,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,33,5843,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60 WHERE `id` IN (8417, 8402, 8400, 8391);
UPDATE `gameobject` SET `phaseMask`=1, `spawntimesecs`=60 WHERE `guid`=727423;

DELETE FROM `conditions` WHERE `SourceGroup`=1282;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 1282, 0, 0, 0, 9, 0, 28056, 0, 0, 0, 0, 0, '', 'Altar of Suntara - Show gossip only if quest 28056 is active');

-- Lathoric the Black
SET @ENTRY := 8391;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corruption"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,20000,20000,20000,20000,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Corruption"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,4000,4000,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,8391,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,8391,0,0,45,0,1,0,0,0,0,10,763321,8400,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Obsidion"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,1,8391,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Hostile"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,8391,0,0,49,14,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Attack Player"),
(@ENTRY,@SOURCETYPE,8,0,7,0,100,0,0,0,0,0,70,0,0,0,0,0,0,11,0,150,0,0.0,0.0,0.0,0.0,"On Evade - Respawn All"),
(@ENTRY,@SOURCETYPE,9,0,7,0,100,0,0,0,0,0,70,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Respawn Self"),
(@ENTRY,@SOURCETYPE,10,0,7,0,100,0,0,0,0,0,2,120,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Faction");

-- Altar of Suntara
SET @ENTRY := 148498;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,1282,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,1282,0,0,0,45,0,1,0,0,0,0,10,774016,8391,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Data 1 to Lathoric the Black");

-- Obsidion
SET @ENTRY := 8400;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,8000,18000,20000,11,84165,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Flame Blast"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,19,67109120,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Unit Flag"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,91,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Byte 7"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,11,24171,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Resurrect"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,49,0,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Attack Players"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,45,0,1,0,0,0,0,11,8402,50,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Data 5 to Archaeologist"),
(@ENTRY,@SOURCETYPE,6,0,7,0,100,0,0,0,0,0,18,67109120,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Unit Flag");

-- Enslaved Archaeologist
SET @ENTRY := 8402;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,69,1,0,0,0,0,0,8,0,0,0,-6526.59,-1234.76,181.58,2.78,"On Get Data 1 - Move Away"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn");

UPDATE `quest_template` SET `PrevQuestId`='28060' WHERE `Id`=28061;
UPDATE `creature_addon` SET `auras`='82343' WHERE `guid` IN
(763324,763325,763326,763327,763328,763331,763333,763334,763335,763336,763337,763338,763339,763340,763341,763342,763321,774016);

DELETE FROM `creature_addon` WHERE `guid` = '763321';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(763321, '82343');

UPDATE `creature_addon` SET `bytes1`=7, `bytes2`=1 WHERE `guid`=763321;

DELETE FROM `spell_area` WHERE `spell` = '90161' AND `quest_start` = '28056';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(90161, 1443, 28056, 0, 1, 74);

UPDATE `creature` SET `spawndist`=35, `MovementType`=1 WHERE `id` IN (47535, 47533);
DELETE FROM `creature` WHERE `guid` IN (732334, 732152, 732154, 732155, 732156, 732157, 732158, 732159, 732160, 732161, 732153);
DELETE FROM `creature_addon` WHERE `guid` IN (732334, 732152, 732154, 732155, 732156, 732157, 732158, 732159, 732160, 732161, 732153);
DELETE FROM `gameobject` WHERE  `guid`=718294;

DELETE FROM `waypoints` WHERE `entry` = '14636';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(14636, 1, -6511.37, -1352.39, 208.94, 'Chambermaid WP'),
(14636, 2, -6535.73, -1347.52, 208.86, 'Chambermaid WP'),
(14636, 3, -6552.09, -1338.07, 208.96, 'Chambermaid WP'),
(14636, 4, -6568.10, -1310.18, 208.76, 'Chambermaid WP'),
(14636, 5, -6560.65, -1328.93, 208.84, 'Chambermaid WP'),
(14636, 6, -6549.35, -1339.57, 208.91, 'Chambermaid WP');

-- Chambermaid Pillaclencher
SET @ENTRY := 14636;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,0,14636,1,0,0,2,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,11,0,100,0,0,0,0,0,53,0,14636,1,0,0,2,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - WP Start"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,23416,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Pillow Fight"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,35000,65000,35000,65000,11,23417,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Smother"),
(@ENTRY,@SOURCETYPE,4,0,60,0,100,0,35000,65000,35000,65000,11,8064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Sleepy!"),
(@ENTRY,@SOURCETYPE,5,0,7,0,100,0,0,0,0,0,53,0,14636,1,0,0,2,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - WP Start"),
(@ENTRY,@SOURCETYPE,6,0,6,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Set Friendly"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,50,179832,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon Pillaclencher");

-- Dark Iron Pillow
SET @ENTRY := 179828;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,5000,10000,5000,10000,12,14635,4,60000,0,0,0,8,0,0,0,-6562.97,-1310.58,208.9,5.24,"Update - Summon Sleepy Worker"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,5000,10000,5000,10000,12,14635,4,60000,0,0,0,8,0,0,0,-6562.97,-1310.58,208.9,5.24,"Update - Summon Sleepy Worker"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,1,5000,10000,5000,10000,12,14635,4,60000,0,0,0,8,0,0,0,-6568.89,-1313.31,208.76,5.16,"Update - Summon Sleepy Worker"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,1,5000,10000,5000,10000,12,14635,4,60000,0,0,0,8,0,0,0,-6569.86,-1318.88,208.76,5.2,"Update - Summon Sleepy Worker"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,1,5000,10000,5000,10000,12,14635,4,60000,0,0,0,8,0,0,0,-6563.63,-1316.12,208.88,5.33,"Update - Summon Sleepy Worker"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,1,5000,10000,5000,10000,12,14635,4,60000,0,0,0,8,0,0,0,-6569.15,-1326.93,208.74,5.51,"Update - Summon Sleepy Worker");

-- Sleepy Dark Iron Worker
SET @ENTRY := 14635;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,89,80,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Random Move"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,12500,45000,45000,45000,11,8064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Sleepy!"),
(@ENTRY,@SOURCETYPE,2,0,6,0,5,0,0,0,0,0,12,14636,4,120000,0,0,0,8,0,0,0,-6570.14,-1308.5,208.7,5.2,"On Death - Summon Chambermaid"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Walk");

-- Pillaclencher's Ornate Pillow
SET @ENTRY := 179832;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Friendly");

UPDATE `creature_template` SET `speed_walk`=0.9, `speed_run`=0.9 WHERE `entry`=14635;

DELETE FROM `gameobject_loot_template` WHERE `item` = '62933';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(16841, 62933, 100, 1, 0, 1, 1);

DELETE FROM `creature` WHERE `guid` IN (732156, 732157, 732158, 732159);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(732157, 14626, 0, 1, 1, 0, 1, -6614.44, -1266.47, 208.744, 4.75389, 300, 0, 0, 3420, 0, 0, 0, 0, 0),
(732156, 14628, 0, 1, 1, 0, 1, -6527.52, -1301.17, 200.926, 0.619415, 300, 0, 0, 3094, 0, 0, 0, 0, 0),
(732159, 14627, 0, 1, 1, 0, 1, -6617.92, -1267.51, 208.744, 5.18601, 300, 0, 0, 3312, 0, 0, 0, 0, 0),
(732158, 14625, 0, 1, 1, 0, 1, -6611.75, -1268.7, 208.744, 3.99592, 300, 0, 0, 4120, 0, 0, 0, 0, 0);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=5963 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=5963;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 5963, 0, 0, 0, 9, 0, 28060, 0, 0, 0, 0, 0, '', 'Hansel Heavyhands - Show gossip only if quest 28060 is active');

DELETE FROM `creature` WHERE `guid`=732301;
DELETE FROM `creature_addon` WHERE `guid`=732301;

-- Twilight-Lord Arkkus
SET @ENTRY := 47460;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,3000,12000,13000,11,80561,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Flame Edge"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,1,0,0,0,0,11,18968,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Fire Shield on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,49,0,0,0,0,0,0,11,14627,200,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Attack Start");

-- Overseer Maltorius
SET @ENTRY := 14621;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,0,1,100,0,6000,9000,25000,28000,11,13323,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Cast Polymorph"),
(@ENTRY,@SOURCETYPE,11,0,0,1,100,0,4000,12000,16000,22000,11,11639,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shadow Word: Pain"),
(@ENTRY,@SOURCETYPE,12,0,2,1,100,1,0,30,0,0,11,11974,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Power Word: Shield at 30% HP"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,14627,20,0,0.0,0.0,0.0,0.0,"OOC - Attack Hansel");

-- Hansel Heavyhands
SET @ENTRY := 14627;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,5963,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,5963,0,0,0,49,0,0,0,0,0,0,11,47460,200,0,0.0,0.0,0.0,0.0,"On Gossip Select - Attack"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3500,3500,3500,3500,11,90140,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Threat"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3500,3500,3500,3500,11,90140,0,0,0,0,0,11,14621,50,0,0.0,0.0,0.0,0.0,"IC - Cast Threat"),
(@ENTRY,@SOURCETYPE,4,0,7,0,100,0,0,0,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset NPC Flag"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,5963,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove NPC Flag");

UPDATE `creature_template` SET `faction_A`=1891, `faction_H`=1891, `unit_flags`=0, `flags_extra`=0, `dmg_multiplier`=1 WHERE `entry`=14627;
UPDATE `creature_template` SET `unit_flags`=0, `type_flags`=0 WHERE `entry`=14621;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid` IN (731979, 731980);

DELETE FROM `creature` WHERE `guid` IN (732376,732371,732272,732257,732066,732062,731543,731541);
DELETE FROM `creature_addon` WHERE `guid` IN (732376,732371,732272,732257,732066,732062,731543,731541);

DELETE FROM `creature_text` WHERE `entry`=47462;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47462,0,0,'Archduke Calcinder is weakened! Banish him now!',42,0,100,0,0,0,'Comment'),
(47462,1,0,'Fools! You cannot defeat me! I will only return again...',14,0,100,0,0,0,'Comment'),
(47462,2,0,'NOOOOOO! THIS CANNOT BE! I... AM... IMMORTAL...!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template_addon` SET `auras`='88221' WHERE `entry`=47462;

DELETE FROM `conditions` WHERE `SourceEntry` = '88547';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 88547, 0, 0, 31, 0, 3, 47462, 0, 0, 0, '', 'Consecrated Tripetricine - Targeting Archduke Calcinder');

-- Archduke Calcinder
SET @ENTRY := 47462;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,8,13600,14500,11,11970,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Fire Nova on Close"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,9000,22000,26000,11,80549,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Gout of Flame"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,12000,14000,33000,35000,11,75068,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Lava Burst"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,2000,4000,13000,16000,11,35377,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Scorch"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,40,50,0,0,1,0,5000,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Health 50% - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,40,50,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Invincible"),
(@ENTRY,@SOURCETYPE,6,7,8,0,100,0,88547,1,0,0,75,88545,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Banish Effect"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,1,2,9000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 2"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,2,47462,0,0,33,47462,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Quest Credit"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,2,47462,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Force Despawn"),
(@ENTRY,@SOURCETYPE,10,0,7,0,100,0,0,0,0,0,70,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Respawn Self"),
(@ENTRY,@SOURCETYPE,11,0,2,0,100,1,5,10,0,0,1,1,5000,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Health 5%/10% - Talk 1"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,1,1,47462,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Force Despawn");

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=732047;

DELETE FROM `spell_script_names` WHERE `spell_id` = '88547';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88547, 'spell_consecrated_tripetricine');

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=47434;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28062;

DELETE FROM `creature_involvedrelation` WHERE `quest` = '28062';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(14625, 28062);

DELETE FROM `creature_questrelation` WHERE `quest` = '28064';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(14625, 28064);

-- Overseer Oilfist
SET @ENTRY := 14625;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,28064,0,0,0,85,91202,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Blackout");