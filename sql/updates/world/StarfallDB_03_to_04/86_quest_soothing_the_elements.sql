DELETE FROM `gameobject_template` WHERE `entry` = '301012';
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES
(301012, 8, 299, 'Flamestone at the Blazing Strand', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 1610, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 1);

DELETE FROM `gameobject` WHERE `guid` = '71529';
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(71529, 301012, 1, 1, 65535, 5533.17, 447.457, 35.6064, 2.07625, 0, 0, 0.861453, 0.507838, 300, 0, 1);

DELETE FROM `creature_text` WHERE `entry`=34367;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34367,0,0,'The ritual of summoning has begun. Defend the totem at all costs!',41,0,100,0,0,0,'Comment');

-- Energized Soothing Totem
SET @ENTRY := 34367;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,50000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,6000,6000,9000,9000,12,34368,8,60000,0,0,0,8,0,0,0,5547.04,470.84,28.53,4.07,"Update - 10 Secs (Summon Fire Elemental Remnant)"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,11000,11000,14000,14000,12,34368,8,60000,0,0,0,8,0,0,0,5535.51,468.01,30.06,5.06,"Update - 13 Secs (Summon Other Fire Elemental Remnant)"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,34367,0,0,12,34370,8,60000,0,0,0,8,0,0,0,5545.95,466.99,28.98,4.1,"Update - 1 Minutes (Summon Fire Elemental Rager)"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,41,75000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn (75 secs)");

-- Fire Elemental Remnant
SET @ENTRY := 34368;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,34367,100,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Totem");

-- Fire Elemental Rager
SET @ENTRY := 34370;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,34367,100,0,0.0,0.0,0.0,0.0,"Just Summoned - Attack Totem"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,33,34371,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"Death - Quest Complete");



