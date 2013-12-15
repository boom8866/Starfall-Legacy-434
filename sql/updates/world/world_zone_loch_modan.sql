DELETE FROM `item_loot_template` WHERE `entry` = '60681';
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(60681, 2596, 100, 1, 0, 1, 1),
(60681, 60502, 100, 1, 0, 1, 1),
(60681, 60503, 100, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '82799';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 82799, 0, 0, 31, 0, 3, 44262, 0, 0, 0, '', 'Mosshide Representative');

-- Mosshide Representative
SET @ENTRY := 44262;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,82799,1,0,0,33,44266,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

DELETE FROM `creature_text` WHERE `entry` IN (1379, 2149);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(1379,0,0,'Help! I've only one hand to defend myself with.',12,0,100,0,0,0,'Comment'),
(1379,1,0,'Send them on! I'm not afraid of some scrawny beasts! ',12,0,100,0,0,0,'Comment'),
(1379,2,0,'Ah, here at last! It's going to feel so good to get rid of these barrels. ',12,0,100,0,0,0,'Comment'),
(2149,1,0,'Feel the power of the Dark Iron Dwarves!',12,0,100,0,0,0,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (171, 5375, 5376, 5377);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(171, 'at_ironband_caravan'),
(5375, 'at_ironband_excavation'),
(5376, 'at_ironband_excavation'),
(5377, 'at_ironband_excavation');

-- Miran
SET @ENTRY := 1379;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,1379,0,0,45,0,1,0,0,0,0,11,2149,100,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Raider"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,2,1379,0,0,18,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Remove Pacified");

-- Dark Iron Raider
SET @ENTRY := 2149;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,12,1051,2,120000,0,0,0,8,0,0,0,-5677.07,-3559.59,306.58,2.69,"On Get Data 1 - Summon Dark Iron Dwarf Left"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,12,1051,2,120000,0,0,0,8,0,0,0,-5680.43,-3556.26,305.99,2.74,"On Get Data 1 - Summon Dark Iron Dwarf Right"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,15,309,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,1379,100,0,0.0,0.0,0.0,0.0,"On Death - Set Data 2 to Miran"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,2149,0,0,45,0,1,0,0,0,0,11,1379,100,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Miran");

-- Ol' Sooty
SET @ENTRY := 1225;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,1225,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Leaping Rush"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,18500,5000,18500,11,84867,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sundering Swipe"),
(@ENTRY,@SOURCETYPE,2,0,0,0,5,0,20000,25000,20000,25000,11,84868,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hibernate");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry` IN (33485, 33486, 33487);

DELETE FROM `creature` WHERE `guid`=160935;
DELETE FROM `creature_addon` WHERE `guid`=160935;