UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=38202;

-- Bloodpetal Seed
SET @ENTRY := 38202;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,71349,1,0,0,56,50253,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Credit"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,51,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Kill Self");

DELETE FROM `creature_loot_template` WHERE `item` = '50371';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(6555, 50371, -70.3946, 1, 0, 6, 6),
(6554, 50371, -68.7488, 1, 0, 6, 6),
(6553, 50371, -59.1732, 1, 0, 6, 6),
(6551, 50371, -53.0028, 1, 0, 6, 6),
(6552, 50371, -53.2248, 1, 0, 6, 6);

-- Un'Goro Pit Bunny
SET @ENTRY := 38354;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,33,38355,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Quest Credit");

-- Diemetradon
SET @ENTRY := 9163;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,8000,32000,44000,11,83367,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Diemetradon Howl"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,38354,20,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Pit Trigger");

-- Young Diemetradon
SET @ENTRY := 9162;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,8000,32000,44000,11,83367,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Diemetradon Howl"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3500,22000,25000,11,3604,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Tendon Rip"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,38354,20,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Pit Trigger");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735173;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=38214;
UPDATE `creature_template` SET `mindmg`=89, `maxdmg`=119, `attackpower`=218 WHERE `entry`=38214;
UPDATE `creature_template` SET `modelid2`=8149 WHERE `entry`=38214;

DELETE FROM `gameobject_loot_template` WHERE `item` = '50407';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(27849, 50407, -100, 1, 0, 1, 1);

-- Deletes creature Gorishi Fledgling Colossus (id: 38305, guid: 728413) in zone: 490, area: 540
DELETE FROM `creature` WHERE `guid` = 728413; DELETE FROM creature_addon WHERE guid = 728413;

-- Deletes creature Gorishi Fledgling Colossus (id: 38305, guid: 728406) in zone: 490, area: 540
DELETE FROM `creature` WHERE `guid` = 728406; DELETE FROM creature_addon WHERE guid = 728406;