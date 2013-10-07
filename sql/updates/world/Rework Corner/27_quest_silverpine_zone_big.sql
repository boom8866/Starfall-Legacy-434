UPDATE `quest_template` SET `PrevQuestId` = 27096, `Flags` = 0 WHERE `Id` = 27097;
UPDATE `quest_template` SET `PrevQuestId` = 26965 WHERE `Id` = 26992;
UPDATE `quest_template` SET `PrevQuestId` = 26965 WHERE `Id` = 26989;
UPDATE `quest_template` SET `PrevQuestId` = 26998 WHERE `Id` = 27039;
UPDATE `quest_template` SET `PrevQuestId` = 27098 WHERE `Id` = 27180;
UPDATE `quest_template` SET `PrevQuestId` = 27195 WHERE `Id` = 27290;
UPDATE `quest_template` SET `PrevQuestId` = 26965 WHERE `Id` = 26995;
UPDATE `quest_template` SET `PrevQuestId` = 0 WHERE `Id` = 28089;
UPDATE `quest_template` SET `PrevQuestId` = 27065 WHERE `Id` = 27073;
UPDATE `quest_template` SET `PrevQuestId` = 27069 WHERE `Id` = 27095;
UPDATE `quest_template` SET `PrevQuestId` = 27180 WHERE `Id` = 27226;
UPDATE `quest_template` SET `PrevQuestId` = 27180 WHERE `Id` = 27231;
UPDATE `quest_template` SET `PrevQuestId` = 27194 WHERE `Id` = 27195;
UPDATE `quest_template` SET `PrevQuestId` = 27290 WHERE `Id` = 27333;

UPDATE `creature_template` SET `InhabitType`=3 WHERE  `entry`=1545;
UPDATE `creature_template` SET `InhabitType`=3 WHERE  `entry`=1541;
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27349', '8', '27342');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27349', '8', '27333');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27349', '8', '27345');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27349', '8', '27342');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27349', '8', '27333');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27349', '8', '27345');	
UPDATE `quest_template` SET `PrevQuestId` = 27350 WHERE `Id` = 27364;
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27401', '8', '27360');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27401', '8', '27364');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27401', '8', '27360');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27401', '8', '27364');
UPDATE `quest_template` SET `PrevQuestId` = 27405 WHERE `Id` = 27423;
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27438', '8', '27406');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27438', '8', '27423');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27438', '8', '27406');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27438', '8', '27423');
UPDATE `quest_template` SET `PrevQuestId` = 27438 WHERE `Id` = 27472;
UPDATE `quest_template` SET `PrevQuestId` = 27472 WHERE `Id` = 27474;
UPDATE `quest_template` SET `PrevQuestId` = 27472 WHERE `Id` = 27475;
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27476', '8', '27474');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('19', '27476', '8', '27475');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27476', '8', '27474');
REPLACE INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('20', '27476', '8', '27475');	
UPDATE `quest_template` SET `PrevQuestId` = 27594 WHERE `Id` = 27601;

-- delete orgrimmar portal
DELETE FROM `creature` WHERE `id`=44630;
-- delete Hellscream's Elite
DELETE FROM `creature` WHERE `id`=44636;

-- delete High Warlord Cromush
SET @CGUID:= 786737;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+1;
DELETE FROM `creature` WHERE `id` IN (44640, 6739);
INSERT INTO `creature` (`guid`, `id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(@CGUID+0, 44640, 0, 1, 1, 34009, 0, 515.936, 1567.05, 129.833, 3.25311, 300, 0, 0, 387450, 0, 2, 0, 0, 0),
(@CGUID+1, 6739, 0, 1, 1, 7633, 0, 471.135, 1500.55, 135.605, 1.0821, 500, 0, 0, 1003, 0, 0, 0, 0, 0);

-- delete Garrosh Hellscream
DELETE FROM `creature` WHERE `id`=44629;
DELETE FROM `creature` WHERE `id`=1978;

UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` = 44608;
UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` = 44609;
UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` = 44610;

-- Grand Executor Mortuus
SET @ENTRY := 44615;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,26965,0,0,0,80,4461500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on quest accept do actionlist");

-- Grand Executor Mortuus
SET @ENTRY := 4461500;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44365,100,0,0.0,0.0,0.0,0.0,"on update send data 1 to Sylvanas"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,0,0,12,44630,3,180000,0,0,0,8,0,0,0,1358.62,1054.72,53.12,0.0,"Summon portal avec 5 sec despawn after 3 min"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,0,0,0,12,44630,3,180000,0,0,0,8,0,0,0,1393.27,1021.2,53.2225,0.0,"Summon portal avec 5 sec despawn after 3 min"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,0,0,0,0,12,44630,3,180000,0,0,0,8,0,0,0,1404.71,1063.73,60.5617,0.0,"Summon portal avec 5 sec despawn after 3 min"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,3000,3000,0,0,12,44636,3,170000,0,0,0,8,0,0,0,0.9,1029.71,53.2185,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1389.79,1024.51,53.2083,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1388.05,1026.91,53.2083,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1388.16,1020.88,53.2552,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1385.79,1025.99,53.2259,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1386.69,1023.26,53.2439,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1384.33,1022.04,53.2812,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,11,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1391.1,1027.73,53.2048,2.82743,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,12,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1359.1,1046.55,52.9705,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,13,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1360.89,1051.81,53.1979,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,14,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1360.75,1048.84,53.1289,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,15,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1364.43,1053.62,53.2934,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,16,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1363.08,1048.15,53.2222,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,17,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1364.08,1050.84,53.2916,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,18,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1366.69,1050.31,53.342,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,19,0,0,0,100,0,0,0,0,0,12,44636,3,170000,0,0,0,8,0,0,0,1357.85,1050.12,52.9982,5.25344,"Summon Hellscream''s Elite"),
(@ENTRY,@SOURCETYPE,20,0,0,0,100,0,0,0,0,0,12,44629,3,170000,0,0,0,8,0,0,0,1402.45,1061.62,60.5617,3.92699,"Summon Hellscream''s Garrosh"),
(@ENTRY,@SOURCETYPE,21,0,0,0,100,0,0,0,0,0,12,44640,3,170000,0,0,0,8,0,0,0,1402.15,1067.26,60.5478,1.12756,"Summon Hellscream''s Crommur");

-- Portal from Orgrimmar
SET @ENTRY := 44630;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,55761,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On summoned cast 55761 on self");

-- Hellscream's Elite
SET @ENTRY := 44636;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,12980,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast 12980 on self at summoned"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,169000,169000,169000,169000,11,12980,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast 12980 on self after 169000 ms");

DELETE FROM creature_text WHERE entry in (44365,44640,44629);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44365, 0, 0, 'Where is that ogre-headed buffoon?', 12, 1, 100, 6, 0, 20459, 'Sylvanas'),
(44365, 1, 0, 'Ah, speak of the devil...', 12, 1, 100, 1, 0, 20460, 'Sylvanas'),
(44365, 2, 0, 'Warchief, so glad you could make it.', 12, 1, 100, 1, 0, 20461, 'Sylvanas'),
(44365, 3, 0, 'With the death of the Lich King, many of the more intelligent Scourge became... unemployed. Those ''fiends,'' as you so delicately put it, are called val''kyr. They are under my command now...', 12, 1, 100, 0, 0, 20462, 'Sylvanas'),
(44365, 4, 0, '...and they are part of the reason that I asked to see you.', 12, 1, 100, 1, 0, 20463, 'Sylvanas'),
(44365, 5, 0, 'Very well, Warchief. I have solved the plight of the Forsaken!', 12, 1, 100, 5, 0, 20464, 'Sylvanas'),
(44365, 6, 0, 'As a race, we Forsaken are unable to procreate', 12, 1, 100, 274, 0, 20465, 'Sylvanas'),
(44365, 7, 0, 'With the aid of the val''kyr, we are now able to take the corpses of the fallen and create new Forsaken.', 12, 1, 100, 0, 0, 20466, 'Sylvanas'),
(44365, 8, 0, 'Agatha, show the Warchief!', 12, 1, 100, 22, 0, 20467, 'Sylvanas'),
(44365, 9, 0, 'Warchief, without these new Forsaken my people would die out... Our hold upon Gilneas and northern Lordaeron would crumble.', 12, 1, 100, 0, 0, 20468, 'Sylvanas'),
(44365, 10, 0, 'Isn''t it obvious, Warchief? I serve the Horde.', 12, 1, 100, 66, 0, 20469, 'Sylvanas'),
(44640, 0, 0, 'ABBERATION!', 12, 1, 100, 5, 0, 0, '????????? ?????????? ??????'),
(44640, 1, 0, 'As you command, Warchief!', 12, 1, 100, 66, 0, 0, '????????? ?????????? ??????'),
(44629, 0, 0, 'This better be important, Sylvanas. You know how I detest this place and its foul stench. Why have you called for me?', 12, 1, 100, 0, 0, 20496, 'Garosh'),
(44629, 1, 0, 'And more importantly, what are those Scourge fiends doing here?', 12, 1, 100, 25, 0, 20497, 'Garosh'),
(44629, 2, 0, 'Get on with it, Sylvanas.', 12, 1, 100, 1, 0, 20498, 'Garosh'),
(44629, 3, 0, 'What you have done here, Sylvanas... it goes against the laws of nature. Disgusting is the only word I have to describe it.', 12, 1, 100, 0, 0, 20499, 'Garosh'),
(44629, 4, 0, 'Have you given any thought to what this means, Sylvanas?', 12, 1, 100, 6, 0, 20500, 'Garosh'),
(44629, 5, 0, 'What difference is there between you and the Lich King now?', 12, 1, 100, 6, 0, 20501, 'Garosh'),
(44629, 6, 0, 'Watch your clever mouth, bitch.', 12, 1, 100, 397, 0, 20502, 'Garosh'),
(44629, 7, 0, 'Cromush, you stay behind and make sure the Banshee Queen is well "guarded." I will be expecting a full report when next we meet.', 12, 1, 100, 0, 0, 20503, 'Garosh'),
(44629, 8, 0, 'Remember, Sylvanas, eventually we all have to stand before our maker and face judgment. Your day may come sooner than others...', 12, 1, 100, 0, 0, 20504, 'Garosh');

-- High Warlord Cromush
SET @ENTRY := 44640;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,4464000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on summoned do action");

DELETE FROM waypoints WHERE entry=4464000;
INSERT INTO waypoints(entry, pointid, position_x, position_y, position_z) VALUES
(4464000, 1, 1376.83, 1044.94, 53.3534);

-- High Warlord Cromush
SET @ENTRY := 4464000;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,53,1,4464000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"do wp on summoned"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,93000,93000,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,60000,60000,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 1");

-- Lady Sylvanas Windrunner
SET @ENTRY := 44365;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,80,4436500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on data set 1 do action");

-- Lady Sylvanas Windrunner
SET @ENTRY := 4436500;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,7000,7000,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 1"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,25000,25000,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 2"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,4000,4000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 3"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,16000,16000,0,0,1,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 4 "),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,8000,8000,8000,8000,1,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 5"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,6000,6000,0,0,1,6,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 6"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,5000,5000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 7"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,10000,10000,0,0,1,8,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 8 1min21"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,11,44608,50,0,0.0,0.0,0.0,0.0,"send data 1 to valkir 1min24"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,32000,32000,0,0,1,9,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 9"),
(@ENTRY,@SOURCETYPE,11,0,0,0,100,0,20000,20000,0,0,1,10,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 10"),
(@ENTRY,@SOURCETYPE,12,0,0,0,100,0,37000,37000,0,0,33,44629,0,0,0,0,0,17,0,100,0,0.0,0.0,0.0,0.0,"give credit to player");

-- Garrosh Hellscream
SET @ENTRY := 44629;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,4462900,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on summoned call time action");

-- Garrosh Hellscream
SET @ENTRY := 4462900;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,0,0,97,16,16,0,0,0,0,8,0,0,0,1379.52,1044.37,54.19,5.38,"jump to pos"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,13000,13000,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 1"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,30000,30000,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 2"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,47000,47000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 3"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,22000,22000,0,0,1,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 4"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,5500,5500,0,0,1,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 5"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,12000,12000,0,0,1,6,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 6"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,5000,5000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 7"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,16000,16000,0,0,1,8,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 8"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,11000,11000,0,0,69,0,0,0,0,0,0,8,0,0,0,1351.29,1045.22,52.292,0.0,"move to pos");

REPLACE INTO conditions(SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES
(13, 1, 83173, 0, 0, 31, 0, 3, 44592, 0, 0, 0, 0, '', null),
(13, 1, 83173, 0, 1, 31, 0, 3, 44593, 0, 0, 0, 0, '', null);

-- Agatha
SET @ENTRY := 44608;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,80,4460800,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on data set 1 do action");

-- Agatha
SET @ENTRY := 4460800;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,1363.66,1028.2,64.706,0.686,"move to pos 1"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,3000,3000,69,0,0,0,0,0,0,8,0,0,0,1370.7,1033.03,59.019,0.667,"move to pos 2"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1500,1500,0,0,11,83173,0,0,0,0,0,9,44592,0,100,0.0,0.0,0.0,0.0,"cast on creature range"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,9000,9000,0,0,69,0,0,0,0,0,0,8,0,0,0,1364.02,1028.54,55.99,0.855,"move to home"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0.0,0.0,0.0,0.855,"set orientation");

-- Fallen Human
SET @ENTRY := 44592;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,83173,0,0,0,80,4459200,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on spellhit do action");

-- Fallen Human
SET @ENTRY := 4459200;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,19,144951,15,0,0.0,0.0,0.0,0.0,"move to nearest trigger"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,0,0,69,0,0,0,0,0,0,19,144953,15,0,0.0,0.0,0.0,0.0,"move to nearest trigger"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,0,0,12,44596,3,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"summon 44596 on self"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"force despawn self");

-- Fallen Human
SET @ENTRY := 44593;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,83173,0,0,0,80,4459300,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on spellhit do action");

-- Fallen Human
SET @ENTRY := 4459300;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,19,144951,15,0,0.0,0.0,0.0,0.0,"move to nearest trigger"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,0,0,69,0,0,0,0,0,0,19,144953,15,0,0.0,0.0,0.0,0.0,"move to nearest trigger"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,0,0,12,44597,3,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"summon 44596 on self"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"force despawn self");

-- triger
DELETE FROM `creature_template` WHERE (`entry`=144951);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (144951, 0, 0, 0, 0, 0, 16480, 16480, 16480, 16480, 'Invisible Trigger One', '', '', 0, 1, 1, 0, 35, 35, 0, 1, 1, 1, 0, 1007, 1354, 0, 1571, 1, 2000, 2200, 1, 0, 2048, 8, 0, 0, 0, 0, 758, 1062, 220, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340);

SET @CGUID := 786739;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+29;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(@CGUID+0, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+1, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+2, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+3, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+4, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+5, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+6, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+7, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+8, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+9, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+10, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+11, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+12, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+13, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+14, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+15, 144953, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 50.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+16, 144953, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 51.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+17, 144953, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 50.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+18, 144953, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 50.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+19, 144953, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 51.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+20, 144953, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 51.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+21, 144953, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 50.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+22, 144953, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 50.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+23, 144953, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 50.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+24, 144953, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 51.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+25, 144953, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 51.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+26, 144953, 0, 1, 1, 33984, 0, 1376, 1029.61, 50.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+27, 144953, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 51.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+28, 144953, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 51.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+29, 144953, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 50.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `modelid2` = 0, `modelid3` = 0, `modelid4` = 0 WHERE `entry` = 144951;
DELETE FROM `creature_template` WHERE (`entry`=144953);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`,
`questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (144953, 0, 0, 0, 0, 0, 16480, 0, 0, 0, 'Invisible Trigger One', '', '', 0, 1, 1, 0, 35, 35, 0, 1, 1, 1, 0, 1007, 1354, 0, 1571, 1, 2000, 2200, 1, 0, 2048, 8, 0, 0, 0, 0, 758, 1062, 220, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340);

-- Forsaken Trooper
SET @ENTRY := 44596;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,83149,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast on self 83149");

-- Forsaken Trooper
SET @ENTRY := 44597;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,83149,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast on self 83149");

UPDATE `creature_template` SET `InhabitType` = 7 WHERE `entry` = 44592;
UPDATE `creature_template` SET `InhabitType` = 7 WHERE `entry` = 44593;
DELETE FROM `creature_template_addon` WHERE (`entry`=44608);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (44608, 0, 0, 50397184, 1, 0, '');
DELETE FROM `creature_addon` WHERE (`guid`=59236);
    
-- Data mined from www.wowhead.com
-- Generated by Loot.php November 29, 2012 by Maibenrai
--  http://www.wowhead.com/npc=1778
DELETE FROM `creature_loot_template` WHERE `entry` = 1778;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(1778, 60743, 85.8485, 1, 0, 1, 1), -- 7Diseased Beast Guts
(1778, 60742, -43.219, 1, 0, 1, 1), -- 
(1778, 3173, 41.1490, 1, 0, 1, 1), -- 6Bear Meat
(1778, 4865, 35.5553, 1, 0, 1, 1), -- 7Ruined Pelt
(1778, 7074, 35.5491, 1, 0, 1, 1), -- 7Chipped Claw
(1778, 3169, 13.9499, 1, 0, 1, 1), -- 7Chipped Bear Tooth
(1778, 3170, 13.8624, 1, 0, 1, 1), -- 7Large Bear Tooth
(1778, 3253, -0.4815, 1, 0, 1, 1), -- 6Grizzled Bear Heart
(1778, 774, 0.4301, 1, 0, 1, 1), -- 5Malachite
(1778, 818, 0.2819, 1, 0, 1, 1), -- 5Tigerseye
(1778, 1414, 0.1749, 1, 0, 1, 1), -- 7Cracked Sledge
(1778, 727, 0.1718, 1, 0, 1, 1), -- 5Notched Shortsword
(1778, 6513, 0.1718, 1, 0, 1, 1), -- 6Disciple's Sash
(1778, 4562, 0.1687, 1, 0, 1, 1), -- 5Severing Axe
(1778, 8178, 0.1636, 1, 0, 1, 1), -- 5Training Sword
(1778, 7350, 0.1636, 1, 0, 1, 1), -- 6Disciple's Bracers
(1778, 1411, 0.1533, 1, 0, 1, 1), -- 7Withered Staff
(1778, 2138, 0.1451, 1, 0, 1, 1), -- 7Sharpened Letter Opener
(1778, 8180, 0.1440, 1, 0, 1, 1), -- 5Hunting Bow
(1778, 1416, 0.1379, 1, 0, 1, 1), -- 7Rusty Hatchet
(1778, 1512, 0.1368, 1, 0, 1, 1), -- 7Crude Battle Axe
(1778, 1513, 0.1358, 1, 0, 1, 1), -- 7Old Greatsword
(1778, 1514, 0.1358, 1, 0, 1, 1), -- 7Rusty Warhammer
(1778, 1417, 0.1337, 1, 0, 1, 1), -- 7Beaten Battle Axe
(1778, 1430, 0.1317, 1, 0, 1, 1), -- 7Patchwork Gloves
(1778, 1510, 0.1317, 1, 0, 1, 1), -- 7Heavy Hammer
(1778, 1413, 0.1307, 1, 0, 1, 1), -- 7Feeble Sword
(1778, 2763, 0.1307, 1, 0, 1, 1), -- 7Fisherman Knife
(1778, 4561, 0.1296, 1, 0, 1, 1), -- 5Scalping Tomahawk
(1778, 1503, 0.1276, 1, 0, 1, 1), -- 7Warped Leather Boots
(1778, 3370, 0.1265, 1, 0, 1, 1), -- 7Patchwork Belt
(1778, 6518, 0.1245, 1, 0, 1, 1), -- 6Pioneer Boots
(1778, 2774, 0.1204, 1, 0, 1, 1), -- 7Rust-Covered Blunderbuss
(1778, 2958, 0.1183, 1, 0, 1, 1), -- 5Journeyman's Pants
(1778, 1431, 0.1183, 1, 0, 1, 1), -- 7Patchwork Pants
(1778, 2773, 0.1173, 1, 0, 1, 1), -- 7Cracked Shortbow
(1778, 2777, 0.1173, 1, 0, 1, 1), -- 7Feeble Shortbow
(1778, 1415, 0.1163, 1, 0, 1, 1), -- 7Carpenter's Mallet
(1778, 6514, 0.1142, 1, 0, 1, 1), -- 6Disciple's Cloak
(1778, 1433, 0.1132, 1, 0, 1, 1), -- 7Patchwork Armor
(1778, 2140, 0.1121, 1, 0, 1, 1), -- 5Carving Knife
(1778, 3373, 0.1091, 1, 0, 1, 1), -- 7Patchwork Bracers
(1778, 2778, 0.1091, 1, 0, 1, 1), -- 7Cheap Blunderbuss
(1778, 1418, 0.1080, 1, 0, 1, 1), -- 7Worn Leather Belt
(1778, 1516, 0.1080, 1, 0, 1, 1), -- 7Worn Hatchet
(1778, 1497, 0.1070, 1, 0, 1, 1), -- 7Calico Cloak
(1778, 1507, 0.1060, 1, 0, 1, 1), -- 7Warped Leather Pants
(1778, 1420, 0.1049, 1, 0, 1, 1), -- 7Worn Leather Bracers
(1778, 1511, 0.1049, 1, 0, 1, 1), -- 7Commoner's Sword
(1778, 1412, 0.1039, 1, 0, 1, 1), -- 7Crude Bastard Sword
(1778, 1425, 0.1039, 1, 0, 1, 1), -- 7Worn Leather Vest
(1778, 6515, 0.1029, 1, 0, 1, 1), -- 6Disciple's Gloves
(1778, 2214, 0.1029, 1, 0, 1, 1), -- 7Wooden Buckler
(1778, 2645, 0.1019, 1, 0, 1, 1), -- 7Loose Chain Gloves
(1778, 1499, 0.1019, 1, 0, 1, 1), -- 7Calico Pants
(1778, 1515, 0.1019, 1, 0, 1, 1), -- 7Rough Wooden Staff
(1778, 2212, 0.1008, 1, 0, 1, 1), -- 7Cracked Buckler
(1778, 1502, 0.1008, 1, 0, 1, 1), -- 7Warped Leather Belt
(1778, 2642, 0.0998, 1, 0, 1, 1), -- 7Loose Chain Boots
(1778, 1504, 0.0998, 1, 0, 1, 1), -- 7Warped Leather Bracers
(1778, 1501, 0.0998, 1, 0, 1, 1), -- 7Calico Tunic
(1778, 2959, 0.0988, 1, 0, 1, 1), -- 6Journeyman's Boots
(1778, 1427, 0.0988, 1, 0, 1, 1), -- 7Patchwork Shoes
(1778, 2962, 0.0977, 1, 0, 1, 1), -- 5Burnt Leather Breeches
(1778, 1509, 0.0977, 1, 0, 1, 1), -- 7Warped Leather Vest
(1778, 1730, 0.0977, 1, 0, 1, 1), -- 7Worn Mail Belt
(1778, 1419, 0.0967, 1, 0, 1, 1), -- 7Worn Leather Boots
(1778, 6507, 0.0947, 1, 0, 1, 1), -- 6Infantry Bracers
(1778, 2213, 0.0947, 1, 0, 1, 1), -- 7Worn Large Shield
(1778, 2964, 0.0936, 1, 0, 1, 1), -- 6Burnt Leather Gloves
(1778, 6509, 0.0936, 1, 0, 1, 1), -- 6Infantry Belt
(1778, 2967, 0.0926, 1, 0, 1, 1), -- 6Warrior's Boots
(1778, 1734, 0.0926, 1, 0, 1, 1), -- 7Worn Mail Gloves
(1778, 7351, 0.0916, 1, 0, 1, 1), -- 6Disciple's Boots
(1778, 9745, 0.0916, 1, 0, 1, 1), -- 6Simple Cape
(1778, 1498, 0.0916, 1, 0, 1, 1), -- 7Calico Gloves
(1778, 1422, 0.0905, 1, 0, 1, 1), -- 7Worn Leather Gloves
(1778, 6519, 0.0895, 1, 0, 1, 1), -- 6Pioneer Bracers
(1778, 1423, 0.0895, 1, 0, 1, 1), -- 7Worn Leather Pants
(1778, 6521, 0.0885, 1, 0, 1, 1), -- 6Pioneer Gloves
(1778, 1732, 0.0885, 1, 0, 1, 1), -- 7Worn Mail Bracers
(1778, 9754, 0.0875, 1, 0, 1, 1), -- 6Gypsy Cloak
(1778, 1429, 0.0875, 1, 0, 1, 1), -- 7Patchwork Cloak
(1778, 2643, 0.0875, 1, 0, 1, 1), -- 7Loose Chain Bracers
(1778, 1495, 0.0875, 1, 0, 1, 1), -- 7Calico Shoes
(1778, 3375, 0.0864, 1, 0, 1, 1), -- 7Calico Bracers
(1778, 1506, 0.0864, 1, 0, 1, 1), -- 7Warped Leather Gloves
(1778, 4663, 0.0854, 1, 0, 1, 1), -- 6Journeyman's Belt
(1778, 2215, 0.0844, 1, 0, 1, 1), -- 7Wooden Shield
(1778, 6517, 0.0813, 1, 0, 1, 1), -- 6Pioneer Belt
(1778, 3192, 0.0802, 1, 0, 1, 1), -- 5Short Bastard Sword
(1778, 3374, 0.0792, 1, 0, 1, 1), -- 7Calico Belt
(1778, 2966, 0.0782, 1, 0, 1, 1), -- 5Warrior's Pants
(1778, 2940, 0.0782, 1, 0, 1, 1), -- 7Bloody Bear Paw
(1778, 2635, 0.0782, 1, 0, 1, 1), -- 7Loose Chain Belt
(1778, 2646, 0.0782, 1, 0, 1, 1), -- 7Loose Chain Pants
(1778, 1737, 0.0772, 1, 0, 1, 1), -- 7Worn Mail Vest
(1778, 2961, 0.0741, 1, 0, 1, 1), -- 5Burnt Leather Vest
(1778, 6506, 0.0741, 1, 0, 1, 1), -- 6Infantry Boots
(1778, 1735, 0.0741, 1, 0, 1, 1), -- 7Worn Mail Pants
(1778, 1731, 0.0730, 1, 0, 1, 1), -- 7Worn Mail Boots
(1778, 6510, 0.0720, 1, 0, 1, 1), -- 6Infantry Gauntlets
(1778, 4577, 0.0700, 1, 0, 1, 1), -- 5Compact Shotgun
(1778, 3214, 0.0700, 1, 0, 1, 1), -- 6Warrior's Bracers
(1778, 8181, 0.0689, 1, 0, 1, 1), -- 6Hunting Rifle
(1778, 3609, 0.0679, 1, 0, 1, 1), -- 5Plans: Copper Chain Vest
(1778, 2965, 0.0669, 1, 0, 1, 1), -- 5Warrior's Tunic
(1778, 2648, 0.0669, 1, 0, 1, 1), -- 7Loose Chain Vest
(1778, 1210, 0.0658, 1, 0, 1, 1), -- 5Shadowgem
(1778, 2963, 0.0648, 1, 0, 1, 1), -- 6Burnt Leather Boots
(1778, 4563, 0.0648, 1, 0, 1, 1), -- 6Billy Club
(1778, 5069, 0.0638, 1, 0, 1, 1), -- 5Fire Wand
(1778, 9753, 0.0638, 1, 0, 1, 1), -- 5Gypsy Buckler
(1778, 9761, 0.0638, 1, 0, 1, 1), -- 6Cadet Cloak
(1778, 9742, 0.0628, 1, 0, 1, 1), -- 6Simple Cord
(1778, 7108, 0.0617, 1, 0, 1, 1), -- 5Infantry Shield
(1778, 15925, 0.0586, 1, 0, 1, 1), -- 5Journeyman's Stave
(1778, 11406, 0.0586, 1, 0, 1, 1), -- 7Rotting Bear Carcass
(1778, 2598, 0.0556, 1, 0, 1, 1), -- 5Pattern: Red Linen Robe
(1778, 6337, 0.0556, 1, 0, 1, 1), -- 5Infantry Leggings
(1778, 2960, 0.0556, 1, 0, 1, 1), -- 6Journeyman's Gloves
(1778, 15932, 0.0535, 1, 0, 1, 1), -- 5Disciple's Stein
(1778, 768, 0.0535, 1, 0, 1, 1), -- 6Lumberjack Axe
(1778, 4666, 0.0525, 1, 0, 1, 1), -- 6Burnt Leather Belt
(1778, 6508, 0.0525, 1, 0, 1, 1), -- 6Infantry Cloak
(1778, 2075, 0.0494, 1, 0, 1, 1), -- 5Heavy Mace
(1778, 2968, 0.0494, 1, 0, 1, 1), -- 6Warrior's Gloves
(1778, 6520, 0.0484, 1, 0, 1, 1), -- 6Pioneer Cloak
(1778, 4677, 0.0473, 1, 0, 1, 1), -- 6Veteran Cloak
(1778, 9750, 0.0473, 1, 0, 1, 1), -- 6Gypsy Sash
(1778, 2957, 0.0453, 1, 0, 1, 1), -- 5Journeyman's Vest
(1778, 9743, 0.0442, 1, 0, 1, 1), -- 6Simple Shoes
(1778, 6267, 0.0432, 1, 0, 1, 1), -- 5Disciple's Pants
(1778, 4566, 0.0432, 1, 0, 1, 1), -- 5Sturdy Quarterstaff
(1778, 5571, 0.0422, 1, 0, 1, 1), -- 6Small Black Pouch
(1778, 9752, 0.0422, 1, 0, 1, 1), -- 6Gypsy Bands
(1778, 9758, 0.0412, 1, 0, 1, 1), -- 6Cadet Belt
(1778, 4684, 0.0412, 1, 0, 1, 1), -- 6Spellbinder Belt
(1778, 9751, 0.0401, 1, 0, 1, 1), -- 6Gypsy Sandals
(1778, 6269, 0.0391, 1, 0, 1, 1), -- 5Pioneer Trousers
(1778, 9762, 0.0381, 1, 0, 1, 1), -- 6Cadet Gauntlets
(1778, 6511, 0.0370, 1, 0, 1, 1), -- 5Journeyman's Robe
(1778, 9744, 0.0370, 1, 0, 1, 1), -- 6Simple Bands
(1778, 3213, 0.0370, 1, 0, 1, 1), -- 6Veteran Bracers
(1778, 4564, 0.0360, 1, 0, 1, 1), -- 5Spiked Club
(1778, 5572, 0.0360, 1, 0, 1, 1), -- 6Small Green Pouch
(1778, 4690, 0.0350, 1, 0, 1, 1), -- 6Hunting Belt
(1778, 828, 0.0329, 1, 0, 1, 1), -- 6Small Blue Pouch
(1778, 9760, 0.0329, 1, 0, 1, 1), -- 6Cadet Bracers
(1778, 4683, 0.0329, 1, 0, 1, 1), -- 6Spellbinder Cloak
(1778, 6268, 0.0319, 1, 0, 1, 1), -- 5Pioneer Tunic
(1778, 9747, 0.0319, 1, 0, 1, 1), -- 5Simple Britches
(1778, 9759, 0.0319, 1, 0, 1, 1), -- 6Cadet Boots
(1778, 4689, 0.0298, 1, 0, 1, 1), -- 6Hunting Cloak
(1778, 9746, 0.0288, 1, 0, 1, 1), -- 6Simple Gloves
(1778, 3610, 0.0278, 1, 0, 1, 1), -- 5Plans: Gemmed Copper Gauntlets
(1778, 805, 0.0247, 1, 0, 1, 1), -- 6Small Red Pouch
(1778, 5635, 0.0237, 1, 0, 1, 1), -- 6Sharp Claw
(1778, 6336, 0.0216, 1, 0, 1, 1), -- 5Infantry Tunic
(1778, 5071, 0.0216, 1, 0, 1, 1), -- 5Shadow Wand
(1778, 9755, 0.0216, 1, 0, 1, 1), -- 6Gypsy Gloves
(1778, 5573, 0.0216, 1, 0, 1, 1), -- 6Green Leather Bag
(1778, 6512, 0.0195, 1, 0, 1, 1), -- 5Disciple's Robe
(1778, 6266, 0.0185, 1, 0, 1, 1), -- 5Disciple's Vest
(1778, 2555, 0.0185, 1, 0, 1, 1), -- 5Recipe: Swiftness Potion
(1778, 4496, 0.0185, 1, 0, 1, 1), -- 6Small Brown Pouch
(1778, 2855, -0.0165, 1, 0, 1, 1), -- 6Putrid Claw
(1778, 1438, 0.0165, 1, 0, 1, 1), -- 6Warrior's Shield
(1778, 2632, 0.0154, 1, 0, 1, 1), -- 5Curved Dagger
(1778, 2589, 0.0154, 1, 0, 1, 1), -- 6Linen Cloth
(1778, 15895, 0.0154, 1, 0, 1, 1), -- 6Burnt Buckler
(1778, 7109, 0.0154, 1, 0, 1, 1), -- 6Pioneer Buckler
(1778, 2971, 0.0144, 1, 0, 1, 1), -- 6Spellbinder Boots
(1778, 3643, 0.0144, 1, 0, 1, 1), -- 6Spellbinder Bracers
(1778, 62328, 0.0144, 1, 0, 1, 1), -- 7Shed Fur
(1778, 6342, 0.0134, 1, 0, 1, 1), -- 5Formula: Enchant Chest - Minor Mana
(1778, 3651, 0.0134, 1, 0, 1, 1), -- 5Veteran Shield
(1778, 6555, 0.0123, 1, 0, 1, 1), -- 6Bard's Cloak
(1778, 2553, 0.0113, 1, 0, 1, 1), -- 5Recipe: Elixir of Minor Agility
(1778, 3652, 0.0113, 1, 0, 1, 1), -- 5Hunting Buckler
(1778, 2975, 0.0113, 1, 0, 1, 1), -- 6Hunting Boots
(1778, 4678, 0.0113, 1, 0, 1, 1), -- 6Veteran Girdle
(1778, 4569, 0.0103, 1, 0, 1, 1), -- 5Staunch Hammer
(1778, 15933, 0.0103, 1, 0, 1, 1), -- 5Simple Branch
(1778, 7288, 0.0093, 1, 0, 1, 1), -- 5Pattern: Rugged Leather Pants
(1778, 2406, 0.0093, 1, 0, 1, 1), -- 5Pattern: Fine Leather Boots
(1778, 21808, -0.0093, 1, 0, 1, 1), -- 6Arcane Core
(1778, 5574, 0.0093, 1, 0, 1, 1), -- 6White Leather Bag
(1778, 2407, 0.0082, 1, 0, 1, 1), -- 5Pattern: White Leather Jerkin
(1778, 9764, 0.0082, 1, 0, 1, 1), -- 5Cadet Shield
(1778, 2657, 0.0082, 1, 0, 1, 1), -- 6Red Leather Bag
(1778, 9756, 0.0072, 1, 0, 1, 1), -- 5Gypsy Trousers
(1778, 2972, 0.0072, 1, 0, 1, 1), -- 6Spellbinder Gloves
(1778, 2979, 0.0072, 1, 0, 1, 1), -- 6Veteran Boots
(1778, 9763, 0.0062, 1, 0, 1, 1), -- 5Cadet Leggings
(1778, 2408, 0.0062, 1, 0, 1, 1), -- 5Pattern: Fine Leather Gloves
(1778, 2834, -0.0062, 1, 0, 1, 1), -- 6Embalming Ichor
(1778, 3207, 0.0062, 1, 0, 1, 1), -- 6Hunting Bracers
(1778, 6549, 0.0062, 1, 0, 1, 1), -- 6Soldier's Cloak
(1778, 4408, 0.0041, 1, 0, 1, 1), -- 5Schematic: Mechanical Squirrel Box
(1778, 2876, -0.0041, 1, 0, 1, 1), -- 6Duskbat Pelt
(1778, 20797, -0.0041, 1, 0, 1, 1), -- 6Lynx Collar
(1778, 856, 0.0041, 1, 0, 1, 1), -- 6Blue Leather Bag
(1778, 2859, -0.0031, 1, 0, 1, 1), -- 6Vile Fin Scale
(1778, 20482, -0.0031, 1, 0, 1, 1), -- 6Arcane Sliver
(1778, 12223, 0.0031, 1, 0, 1, 1), -- 6Meaty Bat Wing
(1778, 6271, 0.0021, 1, 0, 1, 1), -- 5Pattern: Red Linen Vest
(1778, 4292, 0.0021, 1, 0, 1, 1), -- 5Pattern: Green Woolen Bag
(1778, 2409, 0.0021, 1, 0, 1, 1), -- 5Pattern: Dark Leather Tunic
(1778, 2070, 0.0021, 1, 0, 1, 1), -- 6Darnassian Bleu
(1778, 20764, -0.0021, 1, 0, 1, 1), -- 6Prospector Anvilward's Head
(1778, 20772, -0.0021, 1, 0, 1, 1), -- 6Springpaw Pelt
(1778, 23334, 0.0021, 1, 0, 1, 1), -- 6Cracked Power Core
(1778, 52077, 0.0021, 1, 0, 1, 1), -- 6Urgent Scarlet Memorandum
(1778, 60615, -0.0021, 1, 0, 1, 1), -- 6Durotar Crocolisk Tooth
(1778, 5523, 0.0021, 1, 0, 1, 1), -- 6Small Barnacled Clam
(1778, 20848, 0.0021, 1, 0, 1, 1), -- 7Sparkling Dust
(1778, 2881, 0.0010, 1, 0, 1, 1), -- 5Plans: Runed Copper Breastplate
(1778, 4293, 0.0010, 1, 0, 1, 1), -- 5Pattern: Hillman's Leather Vest
(1778, 4346, 0.0010, 1, 0, 1, 1), -- 5Pattern: Heavy Woolen Cloak
(1778, 4409, 0.0010, 1, 0, 1, 1), -- 5Schematic: Small Seaforium Charge
(1778, 6348, 0.0010, 1, 0, 1, 1), -- 5Formula: Enchant Weapon - Minor Beastslayer
(1778, 159, 0.0010, 1, 0, 1, 1), -- 6Refreshing Spring Water
(1778, 2858, -0.001, 1, 0, 1, 1), -- 6Darkhound Blood
(1778, 3162, -0.001, 1, 0, 1, 1), -- 6Notched Rib
(1778, 4751, -0.001, 1, 0, 1, 1), -- 6Windfury Talon
(1778, 4769, -0.001, 1, 0, 1, 1), -- 6Trophy Swoop Quill
(1778, 4888, -0.001, 1, 0, 1, 1), -- 6Crawler Mucus
(1778, 20799, -0.001, 1, 0, 1, 1), -- 6Felendren's Head
(1778, 27668, 0.0010, 1, 0, 1, 1), -- 6Lynx Meat
(1778, 52079, 0.0010, 1, 0, 1, 1), -- 6A Scarlet Letter
(1778, 4560, 0.0010, 1, 0, 1, 1), -- 6Fine Scimitar
(1778, 766, 0.0010, 1, 0, 1, 1), -- 6Flanged Mace
(1778, 5469, 0.0010, 1, 0, 1, 1), -- 6Strider Meat
(1778, 2452, 0.0010, 1, 0, 1, 1), -- 6Swiftthistle
(1778, 1468, 0.0010, 1, 0, 1, 1), -- 6Murloc Fin
(1778, 20812, 0.0010, 1, 0, 1, 1), -- 7Tattered Pelt
(1778, 20845, 0.0010, 1, 0, 1, 1), -- 7Torn Wyrm Scale
(1778, 20847, 0.0010, 1, 0, 1, 1), -- 7Wraith Fragment
(1778, 62391, 0.0010, 1, 0, 1, 1), -- 7Cat Hair
(1778, 21006, 0.0010, 1, 0, 1, 1), -- 7Unkempt Pants
(1778, 21005, 0.0010, 1, 0, 1, 1), -- 7Unkempt Gloves
(1778, 21010, 0.0010, 1, 0, 1, 1), -- 7Scraggy Leather Boots
(1778, 21007, 0.0010, 1, 0, 1, 1); -- 7Unkempt Robe
    
-- Data mined from www.wowhead.com
-- Generated by Loot.php November 29, 2012 by Maibenrai
--  http://www.wowhead.com/npc=1765
DELETE FROM `creature_loot_template` WHERE `entry` = 1765;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(1765, 62328, 85.4053, 1, 0, 1, 1), -- 7Shed Fur
(1765, 60743, 84.4924, 1, 0, 1, 1), -- 7Diseased Beast Guts
(1765, 2672, 83.5304, 1, 0, 1, 1), -- 6Stringy Wolf Meat
(1765, 60742, -41.9314, 1, 0, 1, 1), -- 
(1765, 3299, 13.8183, 1, 0, 1, 1), -- 7Fractured Canine
(1765, 774, 0.7875, 1, 0, 1, 1), -- 5Malachite
(1765, 1416, 0.3157, 1, 0, 1, 1), -- 7Rusty Hatchet
(1765, 1414, 0.2897, 1, 0, 1, 1), -- 7Cracked Sledge
(1765, 1413, 0.2814, 1, 0, 1, 1), -- 7Feeble Sword
(1765, 2773, 0.2786, 1, 0, 1, 1), -- 7Cracked Shortbow
(1765, 1411, 0.2749, 1, 0, 1, 1), -- 7Withered Staff
(1765, 1415, 0.2582, 1, 0, 1, 1), -- 7Carpenter's Mallet
(1765, 1419, 0.2554, 1, 0, 1, 1), -- 7Worn Leather Boots
(1765, 8181, 0.2545, 1, 0, 1, 1), -- 6Hunting Rifle
(1765, 2774, 0.2433, 1, 0, 1, 1), -- 7Rust-Covered Blunderbuss
(1765, 2138, 0.2387, 1, 0, 1, 1), -- 7Sharpened Letter Opener
(1765, 1412, 0.2294, 1, 0, 1, 1), -- 7Crude Bastard Sword
(1765, 818, 0.2284, 1, 0, 1, 1), -- 5Tigerseye
(1765, 1417, 0.2266, 1, 0, 1, 1), -- 7Beaten Battle Axe
(1765, 2959, 0.2257, 1, 0, 1, 1), -- 6Journeyman's Boots
(1765, 4666, 0.2219, 1, 0, 1, 1), -- 6Burnt Leather Belt
(1765, 1429, 0.2210, 1, 0, 1, 1), -- 7Patchwork Cloak
(1765, 1433, 0.2182, 1, 0, 1, 1), -- 7Patchwork Armor
(1765, 1418, 0.2145, 1, 0, 1, 1), -- 7Worn Leather Belt
(1765, 2648, 0.2136, 1, 0, 1, 1), -- 7Loose Chain Vest
(1765, 4663, 0.2099, 1, 0, 1, 1), -- 6Journeyman's Belt
(1765, 3370, 0.2062, 1, 0, 1, 1), -- 7Patchwork Belt
(1765, 1423, 0.2043, 1, 0, 1, 1), -- 7Worn Leather Pants
(1765, 1422, 0.1987, 1, 0, 1, 1), -- 7Worn Leather Gloves
(1765, 1420, 0.1969, 1, 0, 1, 1), -- 7Worn Leather Bracers
(1765, 768, 0.1959, 1, 0, 1, 1), -- 6Lumberjack Axe
(1765, 1431, 0.1941, 1, 0, 1, 1), -- 7Patchwork Pants
(1765, 2960, 0.1913, 1, 0, 1, 1), -- 6Journeyman's Gloves
(1765, 1430, 0.1913, 1, 0, 1, 1), -- 7Patchwork Gloves
(1765, 4563, 0.1848, 1, 0, 1, 1), -- 6Billy Club
(1765, 3373, 0.1839, 1, 0, 1, 1), -- 7Patchwork Bracers
(1765, 1427, 0.1839, 1, 0, 1, 1), -- 7Patchwork Shoes
(1765, 2645, 0.1811, 1, 0, 1, 1), -- 7Loose Chain Gloves
(1765, 2642, 0.1774, 1, 0, 1, 1), -- 7Loose Chain Boots
(1765, 6520, 0.1755, 1, 0, 1, 1), -- 6Pioneer Cloak
(1765, 8178, 0.1737, 1, 0, 1, 1), -- 5Training Sword
(1765, 2646, 0.1727, 1, 0, 1, 1), -- 7Loose Chain Pants
(1765, 4562, 0.1681, 1, 0, 1, 1), -- 5Severing Axe
(1765, 2212, 0.1653, 1, 0, 1, 1), -- 7Cracked Buckler
(1765, 2968, 0.1597, 1, 0, 1, 1), -- 6Warrior's Gloves
(1765, 6514, 0.1588, 1, 0, 1, 1), -- 6Disciple's Cloak
(1765, 2213, 0.1588, 1, 0, 1, 1), -- 7Worn Large Shield
(1765, 1425, 0.1560, 1, 0, 1, 1), -- 7Worn Leather Vest
(1765, 2643, 0.1560, 1, 0, 1, 1), -- 7Loose Chain Bracers
(1765, 2963, 0.1514, 1, 0, 1, 1), -- 6Burnt Leather Boots
(1765, 727, 0.1495, 1, 0, 1, 1), -- 5Notched Shortsword
(1765, 6513, 0.1449, 1, 0, 1, 1), -- 6Disciple's Sash
(1765, 3164, 0.1365, 1, 0, 1, 1), -- 6Discolored Worg Heart
(1765, 6508, 0.1337, 1, 0, 1, 1), -- 6Infantry Cloak
(1765, 2962, 0.1328, 1, 0, 1, 1), -- 5Burnt Leather Breeches
(1765, 2635, 0.1272, 1, 0, 1, 1), -- 7Loose Chain Belt
(1765, 2958, 0.1226, 1, 0, 1, 1), -- 5Journeyman's Pants
(1765, 2966, 0.1161, 1, 0, 1, 1), -- 5Warrior's Pants
(1765, 3214, 0.1142, 1, 0, 1, 1), -- 6Warrior's Bracers
(1765, 6517, 0.1142, 1, 0, 1, 1), -- 6Pioneer Belt
(1765, 6519, 0.1124, 1, 0, 1, 1), -- 6Pioneer Bracers
(1765, 3200, 0.1114, 1, 0, 1, 1), -- 6Burnt Leather Bracers
(1765, 4662, 0.1114, 1, 0, 1, 1), -- 6Journeyman's Cloak
(1765, 7350, 0.1059, 1, 0, 1, 1), -- 6Disciple's Bracers
(1765, 6337, 0.1012, 1, 0, 1, 1), -- 5Infantry Leggings
(1765, 8180, 0.0919, 1, 0, 1, 1), -- 5Hunting Bow
(1765, 4658, 0.0919, 1, 0, 1, 1), -- 6Warrior's Cloak
(1765, 4659, 0.0873, 1, 0, 1, 1), -- 6Warrior's Girdle
(1765, 3189, 0.0864, 1, 0, 1, 1), -- 6Wood Chopper
(1765, 4665, 0.0854, 1, 0, 1, 1), -- 6Burnt Cloak
(1765, 2964, 0.0854, 1, 0, 1, 1), -- 6Burnt Leather Gloves
(1765, 3641, 0.0836, 1, 0, 1, 1), -- 6Journeyman's Bracers
(1765, 6509, 0.0836, 1, 0, 1, 1), -- 6Infantry Belt
(1765, 2140, 0.0817, 1, 0, 1, 1), -- 5Carving Knife
(1765, 2967, 0.0789, 1, 0, 1, 1), -- 6Warrior's Boots
(1765, 6507, 0.0761, 1, 0, 1, 1), -- 6Infantry Bracers
(1765, 2598, 0.0752, 1, 0, 1, 1), -- 5Pattern: Red Linen Robe
(1765, 4561, 0.0715, 1, 0, 1, 1), -- 5Scalping Tomahawk
(1765, 5069, 0.0669, 1, 0, 1, 1), -- 5Fire Wand
(1765, 767, 0.0650, 1, 0, 1, 1), -- 6Long Bo Staff
(1765, 3190, 0.0650, 1, 0, 1, 1), -- 6Beatstick
(1765, 15895, 0.0650, 1, 0, 1, 1), -- 6Burnt Buckler
(1765, 7351, 0.0650, 1, 0, 1, 1), -- 6Disciple's Boots
(1765, 9744, 0.0650, 1, 0, 1, 1), -- 6Simple Bands
(1765, 828, 0.0641, 1, 0, 1, 1), -- 6Small Blue Pouch
(1765, 9745, 0.0631, 1, 0, 1, 1), -- 6Simple Cape
(1765, 5572, 0.0585, 1, 0, 1, 1), -- 6Small Green Pouch
(1765, 7109, 0.0585, 1, 0, 1, 1), -- 6Pioneer Buckler
(1765, 9753, 0.0576, 1, 0, 1, 1), -- 5Gypsy Buckler
(1765, 6518, 0.0576, 1, 0, 1, 1), -- 6Pioneer Boots
(1765, 2075, 0.0566, 1, 0, 1, 1), -- 5Heavy Mace
(1765, 4677, 0.0566, 1, 0, 1, 1), -- 6Veteran Cloak
(1765, 3192, 0.0548, 1, 0, 1, 1), -- 5Short Bastard Sword
(1765, 15925, 0.0529, 1, 0, 1, 1), -- 5Journeyman's Stave
(1765, 3609, 0.0520, 1, 0, 1, 1), -- 5Plans: Copper Chain Vest
(1765, 4496, 0.0520, 1, 0, 1, 1), -- 6Small Brown Pouch
(1765, 15932, 0.0511, 1, 0, 1, 1), -- 5Disciple's Stein
(1765, 1438, 0.0492, 1, 0, 1, 1), -- 6Warrior's Shield
(1765, 9751, 0.0492, 1, 0, 1, 1), -- 6Gypsy Sandals
(1765, 9742, 0.0474, 1, 0, 1, 1), -- 6Simple Cord
(1765, 6515, 0.0464, 1, 0, 1, 1), -- 6Disciple's Gloves
(1765, 7108, 0.0446, 1, 0, 1, 1), -- 5Infantry Shield
(1765, 9752, 0.0436, 1, 0, 1, 1), -- 6Gypsy Bands
(1765, 9754, 0.0427, 1, 0, 1, 1), -- 6Gypsy Cloak
(1765, 9761, 0.0399, 1, 0, 1, 1), -- 6Cadet Cloak
(1765, 2957, 0.0390, 1, 0, 1, 1), -- 5Journeyman's Vest
(1765, 2961, 0.0390, 1, 0, 1, 1), -- 5Burnt Leather Vest
(1765, 2965, 0.0390, 1, 0, 1, 1), -- 5Warrior's Tunic
(1765, 9743, 0.0381, 1, 0, 1, 1), -- 6Simple Shoes
(1765, 5571, 0.0371, 1, 0, 1, 1), -- 6Small Black Pouch
(1765, 6506, 0.0371, 1, 0, 1, 1), -- 6Infantry Boots
(1765, 6511, 0.0362, 1, 0, 1, 1), -- 5Journeyman's Robe
(1765, 805, 0.0362, 1, 0, 1, 1), -- 6Small Red Pouch
(1765, 9750, 0.0353, 1, 0, 1, 1), -- 6Gypsy Sash
(1765, 6521, 0.0334, 1, 0, 1, 1), -- 6Pioneer Gloves
(1765, 9758, 0.0316, 1, 0, 1, 1), -- 6Cadet Belt
(1765, 6510, 0.0297, 1, 0, 1, 1), -- 6Infantry Gauntlets
(1765, 6267, 0.0288, 1, 0, 1, 1), -- 5Disciple's Pants
(1765, 4566, 0.0279, 1, 0, 1, 1), -- 5Sturdy Quarterstaff
(1765, 6269, 0.0260, 1, 0, 1, 1), -- 5Pioneer Trousers
(1765, 9746, 0.0241, 1, 0, 1, 1), -- 6Simple Gloves
(1765, 4577, 0.0204, 1, 0, 1, 1), -- 5Compact Shotgun
(1765, 9760, 0.0195, 1, 0, 1, 1), -- 6Cadet Bracers
(1765, 4683, 0.0186, 1, 0, 1, 1), -- 6Spellbinder Cloak
(1765, 9762, 0.0186, 1, 0, 1, 1), -- 6Cadet Gauntlets
(1765, 4684, 0.0167, 1, 0, 1, 1), -- 6Spellbinder Belt
(1765, 6336, 0.0158, 1, 0, 1, 1), -- 5Infantry Tunic
(1765, 4689, 0.0158, 1, 0, 1, 1), -- 6Hunting Cloak
(1765, 6512, 0.0149, 1, 0, 1, 1), -- 5Disciple's Robe
(1765, 4564, 0.0139, 1, 0, 1, 1), -- 5Spiked Club
(1765, 9759, 0.0130, 1, 0, 1, 1), -- 6Cadet Boots
(1765, 6268, 0.0111, 1, 0, 1, 1), -- 5Pioneer Tunic
(1765, 3213, 0.0111, 1, 0, 1, 1), -- 6Veteran Bracers
(1765, 6271, 0.0102, 1, 0, 1, 1), -- 5Pattern: Red Linen Vest
(1765, 2555, 0.0102, 1, 0, 1, 1), -- 5Recipe: Swiftness Potion
(1765, 4408, 0.0102, 1, 0, 1, 1), -- 5Schematic: Mechanical Squirrel Box
(1765, 5635, 0.0093, 1, 0, 1, 1), -- 6Sharp Claw
(1765, 4690, 0.0084, 1, 0, 1, 1), -- 6Hunting Belt
(1765, 7288, 0.0074, 1, 0, 1, 1), -- 5Pattern: Rugged Leather Pants
(1765, 2406, 0.0074, 1, 0, 1, 1), -- 5Pattern: Fine Leather Boots
(1765, 9755, 0.0074, 1, 0, 1, 1), -- 6Gypsy Gloves
(1765, 6342, 0.0065, 1, 0, 1, 1), -- 5Formula: Enchant Chest - Minor Mana
(1765, 6266, 0.0065, 1, 0, 1, 1), -- 5Disciple's Vest
(1765, 2408, 0.0065, 1, 0, 1, 1), -- 5Pattern: Fine Leather Gloves
(1765, 3610, 0.0065, 1, 0, 1, 1), -- 5Plans: Gemmed Copper Gauntlets
(1765, 3651, 0.0065, 1, 0, 1, 1), -- 5Veteran Shield
(1765, 21808, -0.0065, 1, 0, 1, 1), -- 6Arcane Core
(1765, 2589, 0.0065, 1, 0, 1, 1), -- 6Linen Cloth
(1765, 3300, 0.0056, 1, 0, 1, 1), -- 7Rabbit's Foot
(1765, 2876, -0.0046, 1, 0, 1, 1), -- 6Duskbat Pelt
(1765, 2553, 0.0028, 1, 0, 1, 1), -- 5Recipe: Elixir of Minor Agility
(1765, 9764, 0.0028, 1, 0, 1, 1), -- 5Cadet Shield
(1765, 3652, 0.0028, 1, 0, 1, 1), -- 5Hunting Buckler
(1765, 2070, 0.0028, 1, 0, 1, 1), -- 6Darnassian Bleu
(1765, 52077, 0.0028, 1, 0, 1, 1), -- 6Urgent Scarlet Memorandum
(1765, 7074, 0.0028, 1, 0, 1, 1), -- 7Chipped Claw
(1765, 2407, 0.0019, 1, 0, 1, 1), -- 5Pattern: White Leather Jerkin
(1765, 15933, 0.0019, 1, 0, 1, 1), -- 5Simple Branch
(1765, 2834, -0.0019, 1, 0, 1, 1), -- 6Embalming Ichor
(1765, 20482, -0.0019, 1, 0, 1, 1), -- 6Arcane Sliver
(1765, 20772, -0.0019, 1, 0, 1, 1), -- 6Springpaw Pelt
(1765, 52564, 0.0019, 1, 0, 1, 1), -- 6Burning Blade Spellscroll
(1765, 2674, 0.0019, 1, 0, 1, 1), -- 6Crawler Meat
(1765, 7101, 0.0019, 1, 0, 1, 1), -- 7Bug Eye
(1765, 68194, 0.0009, 1, 0, 1, 1), -- 4Oggleflint's Inspirer
(1765, 3314, 0.0009, 1, 0, 1, 1), -- 5Ceremonial Leather Gloves
(1765, 2855, -0.0009, 1, 0, 1, 1), -- 6Putrid Claw
(1765, 2859, -0.0009, 1, 0, 1, 1), -- 6Vile Fin Scale
(1765, 3162, -0.0009, 1, 0, 1, 1), -- 6Notched Rib
(1765, 3635, -0.0009, 1, 0, 1, 1), -- 6Maggot Eye's Paw
(1765, 20797, -0.0009, 1, 0, 1, 1), -- 6Lynx Collar
(1765, 21776, -0.0009, 1, 0, 1, 1), -- 6Captain Kelisendra's Lost Rutters
(1765, 21781, -0.0009, 1, 0, 1, 1), -- 6Thaelis' Head
(1765, 52080, -0.0009, 1, 0, 1, 1), -- 6Fresh Crawler Meat
(1765, 118, 0.0009, 1, 0, 1, 1), -- 6Minor Healing Potion
(1765, 4560, 0.0009, 1, 0, 1, 1), -- 6Fine Scimitar
(1765, 5466, 0.0009, 1, 0, 1, 1), -- 6Scorpid Stinger
(1765, 4339, 0.0009, 1, 0, 1, 1), -- 6Bolt of Mageweave
(1765, 4874, 0.0009, 1, 0, 1, 1), -- 7Clean Fishbones
(1765, 23333, 0.0009, 1, 0, 1, 1), -- 7Shattered Power Core
(1765, 67391, 0.0009, 1, 0, 1, 1), -- 7Polished Skull
(1765, 21007, 0.0009, 1, 0, 1, 1), -- 7Unkempt Robe
(1765, 1510, 0.0009, 1, 0, 1, 1); -- 7Heavy Hammer

UPDATE `creature_template` SET `questItem2` = 60742 WHERE `entry` = 1778;
UPDATE `creature_template` SET `questItem1` = 60742 WHERE `entry` = 1765;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44825, 0, 0, 'You better bring that bat back in one piece, $N!', 12, 0, 100, 25, 0, 0, '???????????? ????????? ?????????'),
(44821, 0, 0, 'Eliminate all murlocs by using the Blight Concoction!$B$B|r|TInterface\Icons\INV_ALCHEMY_POTION_05.BLP:24|t', 42, 1, 100, 0, 0, 0, '???????? ??????????'),
(44821, 1, 0, 'Returning to Forsaken High Command!$B$B|r|TInterface\Icons\ACHIEVEMENT_ZONE_SILVERPINE_01.BLP:24|t', 42, 1, 100, 0, 0, 0, '???????? ??????????');


UPDATE `creature_template` SET `gossip_menu_id` = 11892 WHERE `entry` = 44825;
UPDATE `gossip_menu_option` SET `option_id`='1', `npc_option_npcflag`='8195' WHERE (`menu_id`='11892') AND (`id`='1');
UPDATE `gossip_menu_option` SET `option_id`='1', `npc_option_npcflag`='8195' WHERE (`menu_id`='11892') AND (`id`='0');
UPDATE `gossip_menu_option` SET `option_icon`='2' WHERE (`menu_id`='11892') AND (`id`='1');
UPDATE `gossip_menu_option` SET `option_id`='4' WHERE (`menu_id`='11892') AND (`id`='1');

UPDATE `creature_template` SET `minlevel` = 11, `maxlevel` = 11, `faction_A` = 1610, `faction_H` = 1610, `npcflag` = 16777224, `VehicleId` = 1051 WHERE `entry` = 44821;
DELETE FROM `creature_template_addon` WHERE (`entry`=44821);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (44821, 0, 0, 50331648, 0, 0, '');
-- Bat Handler Maggotbreath
SET @ENTRY := 44825;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,11892,0,0,0,86,83584,0,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"on gossip select "),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"close gossip");
UPDATE `creature_template` SET `spell1` = 83573 WHERE `entry` = 44821;


-- Forsaken Bat
SET @ENTRY := 44821;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,23,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"player enter vehicle"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,1,0,0,0,0,53,1,4482100,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"wp start "),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,33,44825,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"give credit to player"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,3,4482100,0,0,1,0,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,20,4482100,0,0,1,1,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"talk 1"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,21,4482100,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"despawn");

UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` = 44821;
REPLACE INTO waypoints(entry, pointid, position_x, position_y, position_z) VALUES
 (4482100, 1, 1349.3, 1020.34, 72.8816),
 (4482100, 2, 1194.8, 983.654, 60.1593),
 (4482100, 3, 1213.23, 433.797, 78.5396),
 (4482100, 4, 1225.53, 346.395, 74.7502),
 (4482100, 5, 1192.51, 278.76, 69.3665),
 (4482100, 6, 1148.45, 215.764, 70.6388),
 (4482100, 7, 1051.38, 154.551, 54.9989),
 (4482100, 8, 954.518, 112.691, 51.1877),
 (4482100, 9, 905.487, 82.7673, 53.5746),
 (4482100, 10, 831.469, 43.6282, 52.2309),
 (4482100, 11, 778.553, 60.0191, 50.8719),
 (4482100, 12, 744.348, 135.963, 49.2458),
 (4482100, 13, 721.343, 174.492, 50.9795),
 (4482100, 14, 686.726, 228.547, 51.1728),
 (4482100, 15, 695.595, 313.278, 48.0281),
 (4482100, 16, 748.613, 319.992, 48.1748),
 (4482100, 17, 860.879, 263.353, 54.5126),
 (4482100, 18, 988.018, 303.05, 51.6042),
 (4482100, 19, 1050.98, 348.021, 51.4449),
 (4482100, 20, 1124.67, 405.132, 51.8656),
 (4482100, 21, 1421.07, 1017.94, 56.7301);
 UPDATE `creature_template` SET `speed_walk` = 2, `speed_run` = 3 WHERE `entry` = 44821;
 DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15  AND SourceGroup=11892;
 INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('15', '11892', '9', '26998');
 
 
 DELETE FROM `creature` WHERE `id`=1951;
DELETE FROM `creature` WHERE `id`=1950;

UPDATE `creature_template` SET `unit_flags` = 33536, `unit_flags2` = 2048 WHERE `entry` = 44899;
DELETE FROM `creature` WHERE `id`=44899;

#UPDATE `creature_template` SET `equipment_id` = 44899 WHERE `entry` = 44899; Rimosso
UPDATE `creature_template` SET `unit_flags` = 537166592, `unit_flags2` = 2049 WHERE `entry` = 44899;
UPDATE `quest_template` SET `SourceSpellId` = 83751 WHERE `Id` = 27045;

UPDATE `creature_template` SET `minlevel` = 15, `maxlevel` = 15, `faction_A` = 5, `faction_H` = 5, `npcflag` = 2, `unit_flags` = 32776 WHERE `entry` = 44882;
DELETE FROM `creature_template_addon` WHERE (`entry`=44882);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (44882, 0, 0, 0, 1, 0, '');
UPDATE `creature_template` SET `unit_flags` = 537166596 WHERE `entry` = 39086;
UPDATE `creature_template` SET `unit_flags` = 537166592 WHERE `entry` = 39087;
REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44882, 0, 0, 'We haven''t got much time. Crowly will be arriving shortly.', 12, 0, 100, 5, 0, 0, '????? ?????? ??? ?????'),
(44882, 1, 0, 'THERE! Hide in the armoire! I''ll hide in the shadow next to you.', 12, 0, 100, 0, 0, 0, '????? ?????? ??? ????? to ????? ???? ???? ???????? ????'),
(44882, 2, 0, 'I live... and die... for the Banshee Queen.', 12, 0, 100, 0, 0, 0, '????? ?????? ??? ????? to ????? ???? ???? ???????? ????');


-- Deathstalker Rane Yorick
SET @ENTRY := 44882;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,4488200,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on summoned call timeaction"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,80,4488201,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on data set 1 do action list");

-- Deathstalker Rane Yorick
SET @ENTRY := 4488200;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,53,0,4488200,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Move to pos"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,35000,35000,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk1"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,500,500,0,0,11,34189,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast 34189 on self"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,2000,2000,0,0,66,0,0,0,0,0,0,8,0,0,0,0.0,0.0,0.0,4.65,"set orientation"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,2000,2000,2000,2000,12,44883,3,180000,0,0,0,8,0,0,0,1299.36,1206.64,58.57063,0.0,"after 2 sec summon crowley"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,0,0,0,0,12,44884,3,180000,0,0,0,8,0,0,0,1296.2,1210.54,58.55333,0.0,"summon Ivar");


-- Deathstalker Rane Yorick
SET @ENTRY := 4488201;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,44884,15,0,0.0,0.0,0.0,0.0,"enter vehicle"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,7000,7000,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 2"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,6000,0,0,33,44882,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"give credit to player"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,0,0,0,0,97,15,15,0,0,0,0,8,0,0,0,1296.29,1206.47,58.5,0.0,"jump"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1000,1000,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"die self");

-- Lord Darius Crowley
SET @ENTRY := 44883;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,4488300,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"call time action on summoned");

-- Lord Darius Crowley
SET @ENTRY := 4488300;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,1313.48,1206.09,58.5119,0.0,"move to pos"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,8000,8000,8000,66,0,0,0,0,0,0,11,44884,30,0,0.0,0.0,0.0,0.0,"set orientation after 8 sec"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,5000,5000,5000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,19000,19000,19000,19000,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 1"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,8000,8000,8000,8000,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 2"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,29000,29000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 3"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,52000,52000,0,0,69,0,0,0,0,0,0,8,0,0,0,1297.23,1212.63,58.58,0.0,"after 52 sec move"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,4000,4000,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"force despawn self");

-- Packleader Ivar Bloodfang
SET @ENTRY := 44884;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,4488400,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"CALL TIME ACTION");


-- Packleader Ivar Bloodfang
SET @ENTRY := 4488400;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,1308.4,1206.28,58.5109,0.0,"move to pos"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15500,15500,15500,15500,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,31000,31000,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"TALK 1"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,11000,11000,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"TALK 2"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,2000,2000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"TALK 3"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,17000,17000,0,0,1,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"TALK 4"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,2000,2000,0,0,69,0,0,0,0,0,0,8,0,0,0,1312.2,1208.56,58.51,0.0,"move"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,2000,2000,0,0,1,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 5"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,5000,5000,0,0,1,6,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 6"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,5000,5000,0,0,69,0,0,0,0,0,0,8,0,0,0,1313.58,1210.62,58.51,0.0,"move"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,3000,3000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 7"),
(@ENTRY,@SOURCETYPE,11,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,11,44882,10,0,0.0,0.0,0.0,0.0,"set data 1 to yorrick"),
(@ENTRY,@SOURCETYPE,12,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,1309.41,1206.23,58.51,0.0,"move"),
(@ENTRY,@SOURCETYPE,13,0,0,0,100,0,3000,3000,0,0,1,8,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 8"),
(@ENTRY,@SOURCETYPE,14,0,0,0,100,0,10000,10000,0,0,1,9,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"text 9"),
(@ENTRY,@SOURCETYPE,15,0,0,0,100,0,0,0,0,0,11,80743,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast 80743 self eject passenger"),
(@ENTRY,@SOURCETYPE,16,0,0,0,100,0,3000,3000,0,0,66,0,0,0,0,0,0,11,44883,30,0,0.0,0.0,0.0,0.0,"orientation crowley"),
(@ENTRY,@SOURCETYPE,17,0,0,0,100,0,1000,1000,0,0,1,10,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 10"),
(@ENTRY,@SOURCETYPE,18,0,0,0,100,0,7000,7000,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"set run self"),
(@ENTRY,@SOURCETYPE,19,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,1297.07,1212.5,58.49,0.0,"move to pos"),
(@ENTRY,@SOURCETYPE,20,0,0,0,100,0,3000,3000,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"force despawn");

UPDATE `creature_template` SET `minlevel` = 20, `maxlevel` = 20, `faction_A` = 2173, `faction_H` = 2173, `unit_flags` = 33536 WHERE `entry` = 44883;
UPDATE `creature_template` SET `unit_flags` = 33536 WHERE `entry` = 44884;

REPLACE INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44883, 0, 0, 'Have you given any more thought to my proposal, Ivar?', 12, 0, 100, 6, 0, 0, '???? ????? ??????'),
(44883, 1, 0, 'If we''re to win this war we will need your help. Our packs must unite! The Forsaken will destroy us otherwise.', 12, 0, 100, 396, 0, 0, '???? ????? ?????? to ????? ???? ???? ???????? ????'),
(44883, 2, 0, 'You are the alpha mate, Ivar. The rest of the ferals in Silverpine will do as you command.', 12, 0, 100, 397, 0, 0, '???? ????? ?????? to ????? ???? ???? ???????? ????'),
(44883, 3, 0, 'So will you help?', 12, 0, 100, 6, 0, 0, '???? ????? ?????? to ????? ???? ???? ???????? ????'),
(44884, 0, 0, 'Why trust you now, Crowley? You abandoned us. Left us to die.', 12, 0, 100, 6, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 1, 0, 'I don''t care about your war, Crowley.', 12, 0, 100, 274, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 2, 0, 'But...', 12, 0, 100, 1, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 3, 0, 'I have seen firsthand what the Forsaken of capable of doing. It is true. They hunt us... slaughter the defenseless.', 12, 0, 100, 1, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 4, 0, 'Aye, I will gather my pack... we...', 12, 0, 100, 1, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 5, 0, '%s sniffs the air.', 16, 0, 100, 479, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 6, 0, 'It would appear that we are being watched, Crowley. You have grown soft... Likely Greymane''s fault.', 12, 0, 100, 1, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 7, 0, 'Treacherous little pup!', 12, 0, 100, 15, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 8, 0, 'What say you now, spy?', 12, 0, 100, 0, 0, 0, '????? ???? ???? ???????? ???? to ???? ????? ??????'),
(44884, 9, 0, 'I was hoping you''d say that...', 12, 0, 100, 0, 0, 0, '????? ???? ???? ???????? ???? to ????? ?????? ??? ?????'),
(44884, 10, 0, 'I will prepare the pack. It will take some time to gather them all, but we will join... for now.', 12, 0, 100, 1, 0, 0, '????? ???? ???? ???????? ???? to ????? ?????? ??? ?????');

REPLACE INTO waypoints(entry, pointid, position_x, position_y, position_z) VALUES
(4488200, 1, 1290.64, 1199.6, 52.6067),
(4488200, 2, 1290.97, 1207.31, 52.6957),
(4488200, 3, 1304.15, 1207.26, 53.7452),
(4488200, 4, 1305.02, 1221.21, 53.7452),
(4488200, 5, 1298.04, 1221.44, 53.7452),
(4488200, 6, 1296.98, 1205.85, 58.4962),
(4488200, 7, 1307.24, 1206.27, 58.5102),
(4488200, 8, 1312.84, 1209.18, 58.5116),
(4488200, 9, 1313.81, 1211.76, 58.5015);


UPDATE `creature_template` SET `minlevel` = 20, `maxlevel` = 20, `faction_A` = 2173, `faction_H` = 2173, `VehicleId` = 1059 WHERE `entry` = 44884;
UPDATE `creature_template` SET `minlevel` = 12, `maxlevel` = 12, `faction_A` = 5, `faction_H` = 5, `unit_flags` = 8, `VehicleId` = 1055 WHERE `entry` = 44893;

DELETE FROM `creature` WHERE `id`=44893;
SET @CGUID := 786768;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+0;
INSERT INTO `creature` (`guid`, `id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(@CGUID+0, 44893, 0, 1, 1, 34165, 0, 1315.06, 1211.81, 58.5562, 62.2251, 500, 0, 0, 42, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `npcflag` = 16777216 WHERE `entry` = 44894;
UPDATE `creature_template` SET `unit_flags` = 33554440 WHERE `entry` = 44893;

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 44894;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44894 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(44894, 0, 0, 0, 64, 0, 100, 0, 0, 0, 0, 0, 86, 83788, 0, 7, 0, 0, 0, 19, 44893, 10, 0, 0, 0, 0, 0, "Test");


DELETE FROM `creature_addon` WHERE (`guid`=59001);
DELETE FROM `creature_addon` WHERE (`guid`=59122);
DELETE FROM `creature_template_addon` WHERE (`entry`=44916);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (44916, 0, 0, 65536, 0, 0, 83847);
DELETE FROM `creature_template_addon` WHERE (`entry`=44917);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (44917, 0, 0, 65536, 1, 0, '');
-- Quest chain for starting quest #27082: Playing Dirty
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27082;
UPDATE `quest_template` SET `PrevQuestId` = 27082, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27088;


DELETE FROM `creature_template_addon` WHERE (`entry`=45228);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (45228, 0, 0, 0, 257, 0, '');
DELETE FROM `creature_template_addon` WHERE (`entry`=45225);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (45225, 0, 0, 0, 1, 0, '');

INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(44365, 0, 1, 1, 500.622, 1564.54, 128.3453, 4.29351, 120, 0, 0); -- 44365 (Area: 228)
-- Quest chain for starting quest #27333: Losing Ground
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 27349, `ExclusiveGroup` = 0 WHERE `Id` = 27333;
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 27349, `ExclusiveGroup` = 0 WHERE `Id` = 27345;
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27349;
UPDATE `quest_template` SET `PrevQuestId` = 27349, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27350;
UPDATE `quest_template` SET `PrevQuestId` = 27350, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27360;

-- Quest chain for starting quest #27364: On Whose Orders?
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27364;
UPDATE `quest_template` SET `PrevQuestId` = 27364, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27401;
UPDATE `quest_template` SET `PrevQuestId` = 27401, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27405;
UPDATE `quest_template` SET `PrevQuestId` = 27405, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27406;

-- Quest chain for starting quest #27548: Lessons in Fear
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27548;
UPDATE `quest_template` SET `PrevQuestId` = 27548, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27577;

-- Quest chain for starting quest #27550: Pyrewood's Fall
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27550;
UPDATE `quest_template` SET `PrevQuestId` = 27550, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27580;
UPDATE `quest_template` SET `PrevQuestId` = 27580, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 27594;


-- Quest chain for starting quest #28089: Warchief's Command: Hillsbrad Foothills!
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 28096, `ExclusiveGroup` = 0 WHERE `Id` = 28089;
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 28096, `ExclusiveGroup` = 0 WHERE `Id` = 28571;
UPDATE `quest_template` SET `PrevQuestId` = 0, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 28096;
UPDATE `quest_template` SET `PrevQuestId` = 28096, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 28111;
UPDATE `quest_template` SET `PrevQuestId` = 28111, `NextQuestId` = 0, `ExclusiveGroup` = 0 WHERE `Id` = 28138;

DELETE FROM `creature` WHERE `id`=44915;

UPDATE `quest_template` SET `SourceSpellId` = 83839 WHERE `Id` = 27069;
UPDATE `creature_template` SET `minlevel` = 9, `maxlevel` = 9, `faction_A` = 5, `faction_H` = 5, `unit_flags` = 33288, `VehicleId` = 1060, `HoverHeight` = 1 WHERE `entry` = 44914;
DELETE FROM `creature_text` WHERE `entry`=44914;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44914, 0, 0, 'Dis not so bad. Maybe little heavy, but me ok.', 12, 0, 100, 66, 0, 0, '???-????'),
(44914, 0, 1, 'Maybe captain carry one box too?', 12, 1, 100, 0, 0, 0, '???-???? to ?????? ????'),
(44914, 0, 2, 'Ugh.. dese boxes too heavy. Dey might fall!', 12, 1, 100, 0, 0, 0, '???-???? to ?????? ????'),
(44914, 0, 3, 'CAN NO SEE! WHERE TO GO!? WHAT DOING?!', 12, 1, 100, 0, 0, 0, '???-???? to ?????? ????'),
(44914, 0, 4, '?Dis hurt so bad. Like da time poop came out sideways.!', 12, 1, 100, 0, 0, 0, '???-???? to ?????? ????'),
(44914, 1, 0, 'Where to put? Dey falling! HELP!', 12, 1, 100, 0, 0, 0, '???-???? to ?????? ????'),
(44914, 2, 0, 'OOF!', 12, 1, 100, 0, 0, 0, '???-????');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND SourceEntry=83838;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`) VALUES ('13', '1', '83838', '31', '3', '44914');

-- Orc Sea Pup
SET @ENTRY := 44914;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,83838,0,0,0,80,4491400,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on spellhit call event"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,0,0,5000,5000,29,0,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"on update follow owner"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,83865,0,0,0,80,4491401,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on spellhit"),
(@ENTRY,@SOURCETYPE,3,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Run");

-- Orc Sea Pup
SET @ENTRY := 4491400;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,11,83835,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast 83835 on self"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,0,0,33,44915,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"give credit to player"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0");


-- Orc Crate
SET @ENTRY := 44915;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,500,500,0,0,11,46598,0,0,0,0,0,11,44914,10,0,0.0,0.0,0.0,0.0,"on summon cast 46598 to owner");

DELETE FROM `creature` WHERE `id`=44367;
SET @CGUID := 786769
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+1;
INSERT INTO `creature` (`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(@CGUID+0, 44367, 0, 1, 1, 33949, 819.152, 1735.18, 22.5499, 4.78279, 7200, 10, 0, 819, 0, 1, 0, 0, 0),
(@CGUID+1, 44367, 0, 1, 1, 33949, 860.453, 1547.99, 33.4494, 4.66367, 7200, 10, 0, 819, 0, 1, 0, 0, 0);

-- Orc Sea Pup
SET @ENTRY := 4491401;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 1 self"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,0,0,11,68576,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast 68576"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,0,0,0,11,35356,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"cast self"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,2000,2000,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 2"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,3000,3000,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"force despawn"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,0,0,0,0,51,0,0,0,0,0,0,11,44915,30,0,0.0,0.0,0.0,0.0,"kill 44915"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,0,0,0,0,28,83839,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"remove 83839 from player");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND  SourceEntry=83865;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`) VALUES ('13', '1', '83865', '31', '3', '44914');

UPDATE `creature_template` SET `unit_flags` = 33280 WHERE `entry` = 44916;

UPDATE `quest_template` SET `Flags` = 0 WHERE `Id` = 27095;
UPDATE `quest_template` SET `PrevQuestId` = 27073 WHERE `Id` = 27095;

-- Data mined from www.wowhead.com
-- Generated by Loot.php November 29, 2012 by Maibenrai
--  http://www.wowhead.com/npc=35245
DELETE FROM `creature_loot_template` WHERE `entry` = 35245;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(35245, 62340, 77.1639, 1, 0, 1, 1), -- 7Flaky Basilisk Scale
(35245, 62341, 22.6504, 1, 0, 1, 1), -- 7Gluey Basilisk Tear
(35245, 818, 0.3708, 1, 0, 1, 1), -- 5Tigerseye
(35245, 1514, 0.3018, 1, 0, 1, 1), -- 7Rusty Warhammer
(35245, 1510, 0.2861, 1, 0, 1, 1), -- 7Heavy Hammer
(35245, 1515, 0.2798, 1, 0, 1, 1), -- 7Rough Wooden Staff
(35245, 1511, 0.2791, 1, 0, 1, 1), -- 7Commoner's Sword
(35245, 1516, 0.2581, 1, 0, 1, 1), -- 7Worn Hatchet
(35245, 2777, 0.2531, 1, 0, 1, 1), -- 7Feeble Shortbow
(35245, 1512, 0.2524, 1, 0, 1, 1), -- 7Crude Battle Axe
(35245, 2763, 0.2441, 1, 0, 1, 1), -- 7Fisherman Knife
(35245, 2778, 0.2298, 1, 0, 1, 1), -- 7Cheap Blunderbuss
(35245, 1513, 0.2294, 1, 0, 1, 1), -- 7Old Greatsword
(35245, 1506, 0.2278, 1, 0, 1, 1), -- 7Warped Leather Gloves
(35245, 1509, 0.2217, 1, 0, 1, 1), -- 7Warped Leather Vest
(35245, 3374, 0.2207, 1, 0, 1, 1), -- 7Calico Belt
(35245, 1499, 0.2157, 1, 0, 1, 1), -- 7Calico Pants
(35245, 1504, 0.2147, 1, 0, 1, 1), -- 7Warped Leather Bracers
(35245, 1498, 0.2134, 1, 0, 1, 1), -- 7Calico Gloves
(35245, 1497, 0.2021, 1, 0, 1, 1), -- 7Calico Cloak
(35245, 1507, 0.1947, 1, 0, 1, 1), -- 7Warped Leather Pants
(35245, 1502, 0.1934, 1, 0, 1, 1), -- 7Warped Leather Belt
(35245, 1503, 0.1914, 1, 0, 1, 1), -- 7Warped Leather Boots
(35245, 1732, 0.1897, 1, 0, 1, 1), -- 7Worn Mail Bracers
(35245, 1495, 0.1884, 1, 0, 1, 1), -- 7Calico Shoes
(35245, 1501, 0.1871, 1, 0, 1, 1), -- 7Calico Tunic
(35245, 1734, 0.1867, 1, 0, 1, 1), -- 7Worn Mail Gloves
(35245, 3375, 0.1867, 1, 0, 1, 1), -- 7Calico Bracers
(35245, 2215, 0.1647, 1, 0, 1, 1), -- 7Wooden Shield
(35245, 1730, 0.1634, 1, 0, 1, 1), -- 7Worn Mail Belt
(35245, 1737, 0.1571, 1, 0, 1, 1), -- 7Worn Mail Vest
(35245, 2214, 0.1557, 1, 0, 1, 1), -- 7Wooden Buckler
(35245, 1735, 0.1547, 1, 0, 1, 1), -- 7Worn Mail Pants
(35245, 1731, 0.1517, 1, 0, 1, 1), -- 7Worn Mail Boots
(35245, 8180, 0.1471, 1, 0, 1, 1), -- 5Hunting Bow
(35245, 3192, 0.1414, 1, 0, 1, 1), -- 5Short Bastard Sword
(35245, 2140, 0.1407, 1, 0, 1, 1), -- 5Carving Knife
(35245, 4561, 0.1397, 1, 0, 1, 1), -- 5Scalping Tomahawk
(35245, 5069, 0.1381, 1, 0, 1, 1), -- 5Fire Wand
(35245, 1210, 0.1207, 1, 0, 1, 1), -- 5Shadowgem
(35245, 14090, 0.1160, 1, 0, 1, 1), -- 5Beaded Britches
(35245, 2075, 0.1150, 1, 0, 1, 1), -- 5Heavy Mace
(35245, 774, 0.1117, 1, 0, 1, 1), -- 5Malachite
(35245, 3644, 0.1027, 1, 0, 1, 1), -- 6Barbaric Cloth Bracers
(35245, 4686, 0.0974, 1, 0, 1, 1), -- 6Barbaric Cloth Cloak
(35245, 14099, 0.0970, 1, 0, 1, 1), -- 6Native Sash
(35245, 15010, 0.0954, 1, 0, 1, 1), -- 5Primal Wraps
(35245, 15297, 0.0950, 1, 0, 1, 1), -- 6Grizzly Bracers
(35245, 3290, 0.0947, 1, 0, 1, 1), -- 6Ancestral Gloves
(35245, 15479, 0.0924, 1, 0, 1, 1), -- 5Charger's Armor
(35245, 3289, 0.0924, 1, 0, 1, 1), -- 6Ancestral Boots
(35245, 14095, 0.0894, 1, 0, 1, 1), -- 6Native Bands
(35245, 15009, 0.0850, 1, 0, 1, 1), -- 5Primal Leggings
(35245, 15302, 0.0847, 1, 0, 1, 1), -- 6Grizzly Belt
(35245, 3287, 0.0830, 1, 0, 1, 1), -- 5Tribal Pants
(35245, 3286, 0.0800, 1, 0, 1, 1), -- 6Tribal Gloves
(35245, 3284, 0.0784, 1, 0, 1, 1), -- 6Tribal Boots
(35245, 3281, 0.0757, 1, 0, 1, 1), -- 6Battle Chain Gloves
(35245, 15477, 0.0744, 1, 0, 1, 1), -- 5Charger's Pants
(35245, 15484, 0.0720, 1, 0, 1, 1), -- 6War Torn Handgrips
(35245, 4577, 0.0704, 1, 0, 1, 1), -- 5Compact Shotgun
(35245, 4692, 0.0690, 1, 0, 1, 1), -- 6Ceremonial Cloak
(35245, 3303, 0.0680, 1, 0, 1, 1), -- 6Brackwater Bracers
(35245, 3282, 0.0670, 1, 0, 1, 1), -- 5Battle Chain Pants
(35245, 4566, 0.0637, 1, 0, 1, 1), -- 5Sturdy Quarterstaff
(35245, 15482, 0.0637, 1, 0, 1, 1), -- 6War Torn Bands
(35245, 3279, 0.0627, 1, 0, 1, 1), -- 6Battle Chain Boots
(35245, 4564, 0.0617, 1, 0, 1, 1), -- 5Spiked Club
(35245, 15486, 0.0574, 1, 0, 1, 1), -- 5War Torn Shield
(35245, 14094, 0.0557, 1, 0, 1, 1), -- 5Beaded Wraps
(35245, 15969, 0.0544, 1, 0, 1, 1), -- 5Beaded Orb
(35245, 3649, 0.0544, 1, 0, 1, 1), -- 6Tribal Buckler
(35245, 2632, 0.0524, 1, 0, 1, 1), -- 5Curved Dagger
(35245, 14091, 0.0510, 1, 0, 1, 1), -- 5Beaded Robe
(35245, 15015, 0.0490, 1, 0, 1, 1), -- 6Lupine Cloak
(35245, 14110, 0.0487, 1, 0, 1, 1), -- 6Native Sandals
(35245, 4680, 0.0467, 1, 0, 1, 1), -- 6Brackwater Cloak
(35245, 727, 0.0460, 1, 0, 1, 1), -- 5Notched Shortsword
(35245, 4562, 0.0457, 1, 0, 1, 1), -- 5Severing Axe
(35245, 4672, 0.0454, 1, 0, 1, 1), -- 6Ancestral Belt
(35245, 15944, 0.0447, 1, 0, 1, 1), -- 5Ancestral Orb
(35245, 14089, 0.0437, 1, 0, 1, 1), -- 6Beaded Gloves
(35245, 15480, 0.0427, 1, 0, 1, 1), -- 6War Torn Girdle
(35245, 14098, 0.0420, 1, 0, 1, 1), -- 6Native Cloak
(35245, 5071, 0.0407, 1, 0, 1, 1), -- 5Shadow Wand
(35245, 4569, 0.0387, 1, 0, 1, 1), -- 5Staunch Hammer
(35245, 15299, 0.0383, 1, 0, 1, 1), -- 6Grizzly Cape
(35245, 14102, 0.0377, 1, 0, 1, 1), -- 6Native Handwraps
(35245, 14116, 0.0377, 1, 0, 1, 1), -- 6Aboriginal Cape
(35245, 3312, 0.0373, 1, 0, 1, 1), -- 6Ceremonial Leather Bracers
(35245, 3288, 0.0370, 1, 0, 1, 1), -- 5Tribal Vest
(35245, 15481, 0.0367, 1, 0, 1, 1), -- 6War Torn Greaves
(35245, 8178, 0.0353, 1, 0, 1, 1), -- 5Training Sword
(35245, 3291, 0.0350, 1, 0, 1, 1), -- 5Ancestral Woollies
(35245, 14097, 0.0347, 1, 0, 1, 1), -- 5Native Pants
(35245, 3285, 0.0327, 1, 0, 1, 1), -- 6Tribal Bracers
(35245, 4693, 0.0323, 1, 0, 1, 1), -- 6Ceremonial Leather Belt
(35245, 15301, 0.0320, 1, 0, 1, 1), -- 6Grizzly Slippers
(35245, 14115, 0.0317, 1, 0, 1, 1), -- 6Aboriginal Bands
(35245, 14086, 0.0310, 1, 0, 1, 1), -- 6Beaded Sandals
(35245, 15303, 0.0303, 1, 0, 1, 1), -- 5Grizzly Pants
(35245, 4669, 0.0293, 1, 0, 1, 1), -- 6Battle Chain Girdle
(35245, 15008, 0.0290, 1, 0, 1, 1), -- 6Primal Mitts
(35245, 4687, 0.0290, 1, 0, 1, 1), -- 6Barbaric Cloth Belt
(35245, 4681, 0.0280, 1, 0, 1, 1), -- 6Brackwater Girdle
(35245, 4675, 0.0273, 1, 0, 1, 1), -- 6Tribal Belt
(35245, 15473, 0.0273, 1, 0, 1, 1), -- 6Charger's Boots
(35245, 15476, 0.0273, 1, 0, 1, 1), -- 6Charger's Handwraps
(35245, 2589, 0.0270, 1, 0, 1, 1), -- 6Linen Cloth
(35245, 15013, 0.0267, 1, 0, 1, 1), -- 6Lupine Cuffs
(35245, 15483, 0.0260, 1, 0, 1, 1), -- 6War Torn Cape
(35245, 15300, 0.0243, 1, 0, 1, 1), -- 6Grizzly Gloves
(35245, 15485, 0.0240, 1, 0, 1, 1), -- 5War Torn Pants
(35245, 3609, 0.0237, 1, 0, 1, 1), -- 5Plans: Copper Chain Vest
(35245, 2657, 0.0237, 1, 0, 1, 1), -- 6Red Leather Bag
(35245, 3653, 0.0233, 1, 0, 1, 1), -- 5Ceremonial Buckler
(35245, 15298, 0.0230, 1, 0, 1, 1), -- 5Grizzly Buckler
(35245, 15490, 0.0227, 1, 0, 1, 1), -- 6Bloodspattered Cloak
(35245, 3283, 0.0223, 1, 0, 1, 1), -- 5Battle Chain Tunic
(35245, 14365, 0.0217, 1, 0, 1, 1), -- 5Mystic's Cape
(35245, 3292, 0.0210, 1, 0, 1, 1), -- 5Ancestral Tunic
(35245, 6527, 0.0210, 1, 0, 1, 1), -- 5Ancestral Robe
(35245, 3036, 0.0210, 1, 0, 1, 1), -- 5Heavy Shortbow
(35245, 15970, 0.0210, 1, 0, 1, 1), -- 5Native Branch
(35245, 856, 0.0210, 1, 0, 1, 1), -- 6Blue Leather Bag
(35245, 2598, 0.0197, 1, 0, 1, 1), -- 5Pattern: Red Linen Robe
(35245, 48128, -0.0197, 1, 0, 1, 1), -- 6Mountainfoot Iron
(35245, 3304, 0.0197, 1, 0, 1, 1), -- 6Brackwater Gauntlets
(35245, 5574, 0.0197, 1, 0, 1, 1), -- 6White Leather Bag
(35245, 3654, 0.0187, 1, 0, 1, 1), -- 5Brackwater Shield
(35245, 4570, 0.0180, 1, 0, 1, 1), -- 5Birchwood Maul
(35245, 2407, 0.0170, 1, 0, 1, 1), -- 5Pattern: White Leather Jerkin
(35245, 2073, 0.0170, 1, 0, 1, 1), -- 5Dwarven Hatchet
(35245, 5573, 0.0170, 1, 0, 1, 1), -- 6Green Leather Bag
(35245, 6342, 0.0163, 1, 0, 1, 1), -- 5Formula: Enchant Chest - Minor Mana
(35245, 6271, 0.0160, 1, 0, 1, 1), -- 5Pattern: Red Linen Vest
(35245, 15011, 0.0143, 1, 0, 1, 1), -- 5Lupine Cord
(35245, 3314, 0.0137, 1, 0, 1, 1), -- 5Ceremonial Leather Gloves
(35245, 14113, 0.0137, 1, 0, 1, 1), -- 5Aboriginal Sash
(35245, 3308, 0.0130, 1, 0, 1, 1), -- 5Barbaric Cloth Gloves
(35245, 15492, 0.0130, 1, 0, 1, 1), -- 5Bloodspattered Sash
(35245, 3311, 0.0130, 1, 0, 1, 1), -- 6Ceremonial Leather Ankleguards
(35245, 2555, 0.0127, 1, 0, 1, 1), -- 5Recipe: Swiftness Potion
(35245, 7288, 0.0123, 1, 0, 1, 1), -- 5Pattern: Rugged Leather Pants
(35245, 3307, 0.0117, 1, 0, 1, 1), -- 5Barbaric Cloth Boots
(35245, 15309, 0.0107, 1, 0, 1, 1), -- 5Feral Cloak
(35245, 2406, 0.0100, 1, 0, 1, 1), -- 5Pattern: Fine Leather Boots
(35245, 4408, 0.0100, 1, 0, 1, 1), -- 5Schematic: Mechanical Squirrel Box
(35245, 15491, 0.0100, 1, 0, 1, 1), -- 5Bloodspattered Gloves
(35245, 2408, 0.0093, 1, 0, 1, 1), -- 5Pattern: Fine Leather Gloves
(35245, 3302, 0.0083, 1, 0, 1, 1), -- 5Brackwater Boots
(35245, 3610, 0.0083, 1, 0, 1, 1), -- 5Plans: Gemmed Copper Gauntlets
(35245, 2553, 0.0077, 1, 0, 1, 1), -- 5Recipe: Elixir of Minor Agility
(35245, 15495, 0.0073, 1, 0, 1, 1), -- 5Bloodspattered Wristbands
(35245, 6347, 0.0070, 1, 0, 1, 1), -- 5Formula: Enchant Bracer - Minor Strength
(35245, 5466, 0.0063, 1, 0, 1, 1), -- 6Scorpid Stinger
(35245, 2409, 0.0057, 1, 0, 1, 1), -- 5Pattern: Dark Leather Tunic
(35245, 769, 0.0057, 1, 0, 1, 1), -- 6Chunk of Boar Meat
(35245, 4409, 0.0053, 1, 0, 1, 1), -- 5Schematic: Small Seaforium Charge
(35245, 4757, 0.0053, 1, 0, 1, 1), -- 7Cracked Egg Shells
(35245, 4292, 0.0033, 1, 0, 1, 1), -- 5Pattern: Green Woolen Bag
(35245, 6348, 0.0033, 1, 0, 1, 1), -- 5Formula: Enchant Weapon - Minor Beastslayer
(35245, 52564, 0.0033, 1, 0, 1, 1), -- 6Burning Blade Spellscroll
(35245, 6344, 0.0030, 1, 0, 1, 1), -- 5Formula: Enchant Bracer - Minor Spirit
(35245, 6716, 0.0030, 1, 0, 1, 1), -- 5Schematic: EZ-Thro Dynamite
(35245, 4345, 0.0027, 1, 0, 1, 1), -- 5Pattern: Red Woolen Boots
(35245, 4293, 0.0027, 1, 0, 1, 1), -- 5Pattern: Hillman's Leather Vest
(35245, 20772, -0.0027, 1, 0, 1, 1), -- 6Springpaw Pelt
(35245, 2070, 0.0023, 1, 0, 1, 1), -- 6Darnassian Bleu
(35245, 4888, -0.0023, 1, 0, 1, 1), -- 6Crawler Mucus
(35245, 56968, 0.0023, 1, 0, 1, 1), -- 7Bug Juice
(35245, 2881, 0.0020, 1, 0, 1, 1), -- 5Plans: Runed Copper Breastplate
(35245, 4346, 0.0020, 1, 0, 1, 1), -- 5Pattern: Heavy Woolen Cloak
(35245, 117, 0.0020, 1, 0, 1, 1), -- 6Tough Jerky
(35245, 4751, -0.002, 1, 0, 1, 1), -- 6Windfury Talon
(35245, 56151, 0.0020, 1, 0, 1, 1), -- 7Broken Hoof Piece
(35245, 17056, 0.0017, 1, 0, 1, 1), -- 6Light Feather
(35245, 47038, -0.0017, 1, 0, 1, 1), -- 6Slab of Venison
(35245, 60793, -0.0017, 1, 0, 1, 1), -- 6Diseased Organ
(35245, 779, 0.0017, 1, 0, 1, 1), -- 7Shiny Seashell
(35245, 62328, 0.0017, 1, 0, 1, 1), -- 7Shed Fur
(35245, 1414, 0.0017, 1, 0, 1, 1), -- 7Cracked Sledge
(35245, 159, 0.0013, 1, 0, 1, 1), -- 6Refreshing Spring Water
(35245, 4540, 0.0013, 1, 0, 1, 1), -- 6Tough Hunk of Bread
(35245, 4769, -0.0013, 1, 0, 1, 1), -- 6Trophy Swoop Quill
(35245, 20764, -0.0013, 1, 0, 1, 1), -- 6Prospector Anvilward's Head
(35245, 21757, -0.0013, 1, 0, 1, 1), -- 6Grimscale Murloc Head
(35245, 21776, -0.0013, 1, 0, 1, 1), -- 6Captain Kelisendra's Lost Rutters
(35245, 60615, -0.0013, 1, 0, 1, 1), -- 6Durotar Crocolisk Tooth
(35245, 47039, -0.0013, 1, 0, 1, 1), -- 6Scout's Orders
(35245, 3173, 0.0013, 1, 0, 1, 1), -- 6Bear Meat
(35245, 67229, 0.0013, 1, 0, 1, 1), -- 6Stag Flank
(35245, 3685, 0.0013, 1, 0, 1, 1), -- 6Raptor Egg
(35245, 4752, -0.001, 1, 0, 1, 1), -- 6Azure Feather
(35245, 4802, -0.001, 1, 0, 1, 1), -- 6Cougar Claws
(35245, 21808, -0.001, 1, 0, 1, 1), -- 6Arcane Core
(35245, 3299, 0.0010, 1, 0, 1, 1), -- 7Fractured Canine
(35245, 23333, 0.0010, 1, 0, 1, 1), -- 7Shattered Power Core
(35245, 56150, 0.0010, 1, 0, 1, 1), -- 7Glue Material
(35245, 1417, 0.0010, 1, 0, 1, 1), -- 7Beaten Battle Axe
(35245, 2958, 0.0007, 1, 0, 1, 1), -- 5Journeyman's Pants
(35245, 3635, -0.0007, 1, 0, 1, 1), -- 6Maggot Eye's Paw
(35245, 4536, 0.0007, 1, 0, 1, 1), -- 6Shiny Red Apple
(35245, 4753, -0.0007, 1, 0, 1, 1), -- 6Bronze Feather
(35245, 4819, -0.0007, 1, 0, 1, 1), -- 6Fizsprocket's Clipboard
(35245, 4862, -0.0007, 1, 0, 1, 1), -- 6Scorpid Worker Tail
(35245, 5085, -0.0007, 1, 0, 1, 1), -- 6Quilboar Tusk
(35245, 5086, -0.0007, 1, 0, 1, 1), -- 6Zhevra Hooves
(35245, 7097, 0.0007, 1, 0, 1, 1), -- 6Leg Meat
(35245, 20765, -0.0007, 1, 0, 1, 1), -- 6Incriminating Documents
(35245, 828, 0.0007, 1, 0, 1, 1), -- 6Small Blue Pouch
(35245, 5465, 0.0007, 1, 0, 1, 1), -- 6Small Spider Leg
(35245, 6303, 0.0007, 1, 0, 1, 1), -- 6Raw Slitherskin Mackerel
(35245, 27668, 0.0007, 1, 0, 1, 1), -- 6Lynx Meat
(35245, 5523, 0.0007, 1, 0, 1, 1), -- 6Small Barnacled Clam
(35245, 2675, 0.0007, 1, 0, 1, 1), -- 6Crawler Claw
(35245, 4813, 0.0007, 1, 0, 1, 1), -- 7Small Leather Collar
(35245, 7074, 0.0007, 1, 0, 1, 1), -- 7Chipped Claw
(35245, 7096, 0.0007, 1, 0, 1, 1), -- 7Plucked Feather
(35245, 7101, 0.0007, 1, 0, 1, 1), -- 7Bug Eye
(35245, 60743, 0.0007, 1, 0, 1, 1), -- 7Diseased Beast Guts
(35245, 1429, 0.0007, 1, 0, 1, 1), -- 7Patchwork Cloak
(35245, 1433, 0.0007, 1, 0, 1, 1), -- 7Patchwork Armor
(35245, 2773, 0.0007, 1, 0, 1, 1), -- 7Cracked Shortbow
(35245, 3370, 0.0007, 1, 0, 1, 1), -- 7Patchwork Belt
(35245, 1415, 0.0007, 1, 0, 1, 1), -- 7Carpenter's Mallet
(35245, 9753, 0.0003, 1, 0, 1, 1), -- 5Gypsy Buckler
(35245, 6556, 0.0003, 1, 0, 1, 1), -- 5Bard's Bracers
(35245, 2828, -0.0003, 1, 0, 1, 1), -- 6Nissa's Remains
(35245, 2829, -0.0003, 1, 0, 1, 1), -- 6Gregor's Remains
(35245, 2855, -0.0003, 1, 0, 1, 1), -- 6Putrid Claw
(35245, 2859, -0.0003, 1, 0, 1, 1), -- 6Vile Fin Scale
(35245, 3162, -0.0003, 1, 0, 1, 1), -- 6Notched Rib
(35245, 3264, -0.0003, 1, 0, 1, 1), -- 6Duskbat Wing
(35245, 3265, -0.0003, 1, 0, 1, 1), -- 6Scavenger Paw
(35245, 4604, 0.0003, 1, 0, 1, 1), -- 6Forest Mushroom Cap
(35245, 4871, -0.0003, 1, 0, 1, 1), -- 6Searing Collar
(35245, 4905, -0.0003, 1, 0, 1, 1), -- 6Sarkoth's Mangled Claw
(35245, 5203, -0.0003, 1, 0, 1, 1), -- 6Flatland Prowler Claw
(35245, 22487, -0.0003, 1, 0, 1, 1), -- 6Aldaron's Head
(35245, 22567, -0.0003, 1, 0, 1, 1), -- 6Gargoyle Fragment
(35245, 805, 0.0003, 1, 0, 1, 1), -- 6Small Red Pouch
(35245, 2287, 0.0003, 1, 0, 1, 1), -- 6Haunch of Meat
(35245, 4496, 0.0003, 1, 0, 1, 1), -- 6Small Brown Pouch
(35245, 4537, 0.0003, 1, 0, 1, 1), -- 6Tel'Abim Banana
(35245, 8179, 0.0003, 1, 0, 1, 1), -- 6Cadet's Bow
(35245, 766, 0.0003, 1, 0, 1, 1), -- 6Flanged Mace
(35245, 8177, 0.0003, 1, 0, 1, 1), -- 6Practice Sword
(35245, 767, 0.0003, 1, 0, 1, 1), -- 6Long Bo Staff
(35245, 768, 0.0003, 1, 0, 1, 1), -- 6Lumberjack Axe
(35245, 4563, 0.0003, 1, 0, 1, 1), -- 6Billy Club
(35245, 8181, 0.0003, 1, 0, 1, 1), -- 6Hunting Rifle
(35245, 15004, 0.0003, 1, 0, 1, 1), -- 6Primal Boots
(35245, 15472, 0.0003, 1, 0, 1, 1), -- 6Charger's Belt
(35245, 2674, 0.0003, 1, 0, 1, 1), -- 6Crawler Meat
(35245, 2924, 0.0003, 1, 0, 1, 1), -- 6Crocolisk Meat
(35245, 22644, 0.0003, 1, 0, 1, 1), -- 6Crunchy Spider Leg
(35245, 4865, 0.0003, 1, 0, 1, 1), -- 7Ruined Pelt
(35245, 4872, 0.0003, 1, 0, 1, 1), -- 7Dry Scorpid Eye
(35245, 20847, 0.0003, 1, 0, 1, 1), -- 7Wraith Fragment
(35245, 20848, 0.0003, 1, 0, 1, 1), -- 7Sparkling Dust
(35245, 55983, 0.0003, 1, 0, 1, 1), -- 7Inert Elemental Scintilla
(35245, 62514, 0.0003, 1, 0, 1, 1), -- 7Cracked Pincer
(35245, 21006, 0.0003, 1, 0, 1, 1), -- 7Unkempt Pants
(35245, 21011, 0.0003, 1, 0, 1, 1), -- 7Scraggy Leather Bracers
(35245, 21019, 0.0003, 1, 0, 1, 1), -- 7Shoddy Chain Bracers
(35245, 1412, 0.0003, 1, 0, 1, 1), -- 7Crude Bastard Sword
(35245, 1418, 0.0003, 1, 0, 1, 1), -- 7Worn Leather Belt
(35245, 1423, 0.0003, 1, 0, 1, 1), -- 7Worn Leather Pants
(35245, 2774, 0.0003, 1, 0, 1, 1), -- 7Rust-Covered Blunderbuss
(35245, 1411, 0.0003, 1, 0, 1, 1), -- 7Withered Staff
(35245, 1419, 0.0003, 1, 0, 1, 1), -- 7Worn Leather Boots
(35245, 1420, 0.0003, 1, 0, 1, 1); -- 7Worn Leather Bracers
UPDATE `creature_template` SET `lootid` = 35245 WHERE `entry` = 35245;

--  http://www.wowhead.com/npc=1504
DELETE FROM `creature_loot_template` WHERE `entry` = 1504;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(1504, 62530, 74.2609, 1, 0, 1, 1), -- 7Spider Hair
(1504, 1476, 24.6941, 1, 0, 1, 1), -- 7Snapped Spider Limb
(1504, 7101, 0.6681, 1, 0, 1, 1), -- 7Bug Eye
(1504, 7100, 0.6597, 1, 0, 1, 1), -- 7Sticky Ichor
(1504, 805, 0.1069, 1, 0, 1, 1), -- 6Small Red Pouch
(1504, 828, 0.1041, 1, 0, 1, 1), -- 6Small Blue Pouch
(1504, 4496, 0.0970, 1, 0, 1, 1), -- 6Small Brown Pouch
(1504, 5572, 0.0942, 1, 0, 1, 1), -- 6Small Green Pouch
(1504, 5571, 0.0731, 1, 0, 1, 1), -- 6Small Black Pouch
(1504, 3264, -0.0605, 1, 0, 1, 1), -- 6Duskbat Wing
(1504, 1372, 0.0436, 1, 0, 1, 1), -- 7Ragged Cloak
(1504, 1376, 0.0436, 1, 0, 1, 1), -- 7Frayed Cloak
(1504, 3265, -0.0366, 1, 0, 1, 1), -- 6Scavenger Paw
(1504, 1370, 0.0352, 1, 0, 1, 1), -- 7Ragged Leather Bracers
(1504, 3363, 0.0338, 1, 0, 1, 1), -- 7Frayed Belt
(1504, 1374, 0.0323, 1, 0, 1, 1), -- 7Frayed Shoes
(1504, 1369, 0.0323, 1, 0, 1, 1), -- 7Ragged Leather Belt
(1504, 2649, 0.0267, 1, 0, 1, 1), -- 7Flimsy Chain Belt
(1504, 1380, 0.0253, 1, 0, 1, 1), -- 7Frayed Robe
(1504, 3365, 0.0253, 1, 0, 1, 1), -- 7Frayed Bracers
(1504, 2654, 0.0239, 1, 0, 1, 1), -- 7Flimsy Chain Pants
(1504, 1378, 0.0225, 1, 0, 1, 1), -- 7Frayed Pants
(1504, 2589, 0.0211, 1, 0, 1, 1), -- 6Linen Cloth
(1504, 2650, 0.0211, 1, 0, 1, 1), -- 7Flimsy Chain Boots
(1504, 2651, 0.0183, 1, 0, 1, 1), -- 7Flimsy Chain Bracers
(1504, 2211, 0.0169, 1, 0, 1, 1), -- 7Bent Large Shield
(1504, 2653, 0.0169, 1, 0, 1, 1), -- 7Flimsy Chain Gloves
(1504, 1364, 0.0169, 1, 0, 1, 1), -- 7Ragged Leather Vest
(1504, 2210, 0.0155, 1, 0, 1, 1), -- 7Battered Buckler
(1504, 2652, 0.0141, 1, 0, 1, 1), -- 7Flimsy Chain Cloak
(1504, 1368, 0.0113, 1, 0, 1, 1), -- 7Ragged Leather Gloves
(1504, 1366, 0.0098, 1, 0, 1, 1), -- 7Ragged Leather Pants
(1504, 62328, 0.0070, 1, 0, 1, 1), -- 7Shed Fur
(1504, 1367, 0.0070, 1, 0, 1, 1), -- 7Ragged Leather Boots
(1504, 1377, 0.0070, 1, 0, 1, 1), -- 7Frayed Gloves
(1504, 772, -0.0056, 1, 0, 1, 1), -- 6Large Candle
(1504, 2855, -0.0056, 1, 0, 1, 1), -- 6Putrid Claw
(1504, 2656, 0.0056, 1, 0, 1, 1), -- 7Flimsy Chain Vest
(1504, 773, -0.0042, 1, 0, 1, 1), -- 6Gold Dust
(1504, 4604, 0.0042, 1, 0, 1, 1), -- 6Forest Mushroom Cap
(1504, 21757, -0.0042, 1, 0, 1, 1), -- 6Grimscale Murloc Head
(1504, 12223, 0.0042, 1, 0, 1, 1), -- 6Meaty Bat Wing
(1504, 5466, 0.0042, 1, 0, 1, 1), -- 6Scorpid Stinger
(1504, 1430, 0.0042, 1, 0, 1, 1), -- 7Patchwork Gloves
(1504, 159, 0.0028, 1, 0, 1, 1), -- 6Refreshing Spring Water
(1504, 49535, -0.0028, 1, 0, 1, 1), -- 6Stolen Rifle
(1504, 52080, -0.0028, 1, 0, 1, 1), -- 6Fresh Crawler Meat
(1504, 62505, -0.0028, 1, 0, 1, 1), -- 6Bat Eye
(1504, 20847, 0.0028, 1, 0, 1, 1), -- 7Wraith Fragment
(1504, 20848, 0.0028, 1, 0, 1, 1), -- 7Sparkling Dust
(1504, 56968, 0.0028, 1, 0, 1, 1), -- 7Bug Juice
(1504, 21006, 0.0028, 1, 0, 1, 1), -- 7Unkempt Pants
(1504, 3300, 0.0028, 1, 0, 1, 1), -- 7Rabbit's Foot
(1504, 2834, -0.0014, 1, 0, 1, 1), -- 6Embalming Ichor
(1504, 2858, -0.0014, 1, 0, 1, 1), -- 6Darkhound Blood
(1504, 2859, -0.0014, 1, 0, 1, 1), -- 6Vile Fin Scale
(1504, 4862, -0.0014, 1, 0, 1, 1), -- 6Scorpid Worker Tail
(1504, 4905, -0.0014, 1, 0, 1, 1), -- 6Sarkoth's Mangled Claw
(1504, 20799, -0.0014, 1, 0, 1, 1), -- 6Felendren's Head
(1504, 49424, -0.0014, 1, 0, 1, 1), -- 6Gyrochoppa Keys
(1504, 60793, -0.0014, 1, 0, 1, 1), -- 6Diseased Organ
(1504, 769, 0.0014, 1, 0, 1, 1), -- 6Chunk of Boar Meat
(1504, 5179, -0.0014, 1, 0, 1, 1), -- 6Moss-Twined Heart
(1504, 5465, 0.0014, 1, 0, 1, 1), -- 6Small Spider Leg
(1504, 8182, 0.0014, 1, 0, 1, 1), -- 6Pellet Rifle
(1504, 3189, 0.0014, 1, 0, 1, 1), -- 6Wood Chopper
(1504, 3190, 0.0014, 1, 0, 1, 1), -- 6Beatstick
(1504, 5523, 0.0014, 1, 0, 1, 1), -- 6Small Barnacled Clam
(1504, 2675, 0.0014, 1, 0, 1, 1), -- 6Crawler Claw
(1504, 1468, 0.0014, 1, 0, 1, 1), -- 6Murloc Fin
(1504, 3299, 0.0014, 1, 0, 1, 1), -- 7Fractured Canine
(1504, 6296, 0.0014, 1, 0, 1, 1), -- 7Patch of Bat Hair
(1504, 21015, 0.0014, 1, 0, 1, 1), -- 7Shoddy Chain Belt
(1504, 21022, 0.0014, 1, 0, 1, 1), -- 7Weather Beaten Buckler
(1504, 21014, 0.0014, 1, 0, 1, 1), -- 7Scraggy Leather Vest
(1504, 1429, 0.0014, 1, 0, 1, 1), -- 7Patchwork Cloak
(1504, 1431, 0.0014, 1, 0, 1, 1), -- 7Patchwork Pants
(1504, 1416, 0.0014, 1, 0, 1, 1); -- 7Rusty Hatchet
UPDATE `creature_template` SET `lootid` = 1504 WHERE `entry` = 1504;


--  http://www.wowhead.com/npc=1797
DELETE FROM `creature_loot_template` WHERE `entry` = 1797;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(1797, 4865, 70.9613, 1, 0, 1, 1), -- 7Ruined Pelt
(1797, 60793, -48.2654, 1, 0, 1, 1), -- 6Diseased Organ
(1797, 3173, 41.3530, 1, 0, 1, 1), -- 6Bear Meat
(1797, 3170, 28.0905, 1, 0, 1, 1), -- 7Large Bear Tooth
(1797, 818, 0.3704, 1, 0, 1, 1), -- 5Tigerseye
(1797, 1511, 0.3405, 1, 0, 1, 1), -- 7Commoner's Sword
(1797, 1516, 0.3034, 1, 0, 1, 1), -- 7Worn Hatchet
(1797, 1513, 0.2897, 1, 0, 1, 1), -- 7Old Greatsword
(1797, 3253, -0.2832, 1, 0, 1, 1), -- 6Grizzled Bear Heart
(1797, 1515, 0.2695, 1, 0, 1, 1), -- 7Rough Wooden Staff
(1797, 2763, 0.2606, 1, 0, 1, 1), -- 7Fisherman Knife
(1797, 1512, 0.2582, 1, 0, 1, 1), -- 7Crude Battle Axe
(1797, 2777, 0.2526, 1, 0, 1, 1), -- 7Feeble Shortbow
(1797, 1510, 0.2518, 1, 0, 1, 1), -- 7Heavy Hammer
(1797, 1514, 0.2445, 1, 0, 1, 1), -- 7Rusty Warhammer
(1797, 2778, 0.2372, 1, 0, 1, 1), -- 7Cheap Blunderbuss
(1797, 1504, 0.2284, 1, 0, 1, 1), -- 7Warped Leather Bracers
(1797, 1497, 0.2155, 1, 0, 1, 1), -- 7Calico Cloak
(1797, 1506, 0.2106, 1, 0, 1, 1), -- 7Warped Leather Gloves
(1797, 3374, 0.2074, 1, 0, 1, 1), -- 7Calico Belt
(1797, 1509, 0.2042, 1, 0, 1, 1), -- 7Warped Leather Vest
(1797, 1498, 0.2034, 1, 0, 1, 1), -- 7Calico Gloves
(1797, 1499, 0.2001, 1, 0, 1, 1), -- 7Calico Pants
(1797, 1502, 0.1993, 1, 0, 1, 1), -- 7Warped Leather Belt
(1797, 1501, 0.1985, 1, 0, 1, 1), -- 7Calico Tunic
(1797, 1507, 0.1929, 1, 0, 1, 1), -- 7Warped Leather Pants
(1797, 3375, 0.1896, 1, 0, 1, 1), -- 7Calico Bracers
(1797, 2215, 0.1856, 1, 0, 1, 1), -- 7Wooden Shield
(1797, 1734, 0.1824, 1, 0, 1, 1), -- 7Worn Mail Gloves
(1797, 2214, 0.1816, 1, 0, 1, 1), -- 7Wooden Buckler
(1797, 1732, 0.1751, 1, 0, 1, 1), -- 7Worn Mail Bracers
(1797, 1735, 0.1703, 1, 0, 1, 1), -- 7Worn Mail Pants
(1797, 1495, 0.1670, 1, 0, 1, 1), -- 7Calico Shoes
(1797, 1503, 0.1654, 1, 0, 1, 1), -- 7Warped Leather Boots
(1797, 1731, 0.1566, 1, 0, 1, 1), -- 7Worn Mail Boots
(1797, 1737, 0.1541, 1, 0, 1, 1), -- 7Worn Mail Vest
(1797, 3169, 0.1501, 1, 0, 1, 1), -- 7Chipped Bear Tooth
(1797, 8180, 0.1453, 1, 0, 1, 1), -- 5Hunting Bow
(1797, 9754, 0.1453, 1, 0, 1, 1), -- 6Gypsy Cloak
(1797, 1730, 0.1396, 1, 0, 1, 1), -- 7Worn Mail Belt
(1797, 2140, 0.1315, 1, 0, 1, 1), -- 5Carving Knife
(1797, 4561, 0.1299, 1, 0, 1, 1), -- 5Scalping Tomahawk
(1797, 1210, 0.1267, 1, 0, 1, 1), -- 5Shadowgem
(1797, 9742, 0.1219, 1, 0, 1, 1), -- 6Simple Cord
(1797, 3192, 0.1194, 1, 0, 1, 1), -- 5Short Bastard Sword
(1797, 6267, 0.1122, 1, 0, 1, 1), -- 5Disciple's Pants
(1797, 2075, 0.1097, 1, 0, 1, 1), -- 5Heavy Mace
(1797, 4577, 0.1049, 1, 0, 1, 1), -- 5Compact Shotgun
(1797, 6515, 0.1049, 1, 0, 1, 1), -- 6Disciple's Gloves
(1797, 774, 0.1025, 1, 0, 1, 1), -- 5Malachite
(1797, 5069, 0.1009, 1, 0, 1, 1), -- 5Fire Wand
(1797, 9745, 0.0984, 1, 0, 1, 1), -- 6Simple Cape
(1797, 9744, 0.0952, 1, 0, 1, 1), -- 6Simple Bands
(1797, 7351, 0.0936, 1, 0, 1, 1), -- 6Disciple's Boots
(1797, 9750, 0.0936, 1, 0, 1, 1), -- 6Gypsy Sash
(1797, 9761, 0.0928, 1, 0, 1, 1), -- 6Cadet Cloak
(1797, 2965, 0.0888, 1, 0, 1, 1), -- 5Warrior's Tunic
(1797, 6521, 0.0872, 1, 0, 1, 1), -- 6Pioneer Gloves
(1797, 9751, 0.0839, 1, 0, 1, 1), -- 6Gypsy Sandals
(1797, 6337, 0.0807, 1, 0, 1, 1), -- 5Infantry Leggings
(1797, 9743, 0.0807, 1, 0, 1, 1), -- 6Simple Shoes
(1797, 9758, 0.0807, 1, 0, 1, 1), -- 6Cadet Belt
(1797, 9753, 0.0799, 1, 0, 1, 1), -- 5Gypsy Buckler
(1797, 9760, 0.0791, 1, 0, 1, 1), -- 6Cadet Bracers
(1797, 2961, 0.0734, 1, 0, 1, 1), -- 5Burnt Leather Vest
(1797, 6518, 0.0718, 1, 0, 1, 1), -- 6Pioneer Boots
(1797, 6269, 0.0702, 1, 0, 1, 1), -- 5Pioneer Trousers
(1797, 4566, 0.0662, 1, 0, 1, 1), -- 5Sturdy Quarterstaff
(1797, 6510, 0.0654, 1, 0, 1, 1), -- 6Infantry Gauntlets
(1797, 9752, 0.0654, 1, 0, 1, 1), -- 6Gypsy Bands
(1797, 2957, 0.0621, 1, 0, 1, 1), -- 5Journeyman's Vest
(1797, 7350, 0.0621, 1, 0, 1, 1), -- 6Disciple's Bracers
(1797, 6506, 0.0621, 1, 0, 1, 1), -- 6Infantry Boots
(1797, 4677, 0.0621, 1, 0, 1, 1), -- 6Veteran Cloak
(1797, 4684, 0.0605, 1, 0, 1, 1), -- 6Spellbinder Belt
(1797, 4569, 0.0597, 1, 0, 1, 1), -- 5Staunch Hammer
(1797, 727, 0.0565, 1, 0, 1, 1), -- 5Notched Shortsword
(1797, 4562, 0.0525, 1, 0, 1, 1), -- 5Severing Axe
(1797, 4678, 0.0516, 1, 0, 1, 1), -- 6Veteran Girdle
(1797, 2958, 0.0508, 1, 0, 1, 1), -- 5Journeyman's Pants
(1797, 2632, 0.0508, 1, 0, 1, 1), -- 5Curved Dagger
(1797, 2940, 0.0508, 1, 0, 1, 1), -- 7Bloody Bear Paw
(1797, 4564, 0.0500, 1, 0, 1, 1), -- 5Spiked Club
(1797, 7108, 0.0476, 1, 0, 1, 1), -- 5Infantry Shield
(1797, 4683, 0.0476, 1, 0, 1, 1), -- 6Spellbinder Cloak
(1797, 4690, 0.0468, 1, 0, 1, 1), -- 6Hunting Belt
(1797, 15925, 0.0460, 1, 0, 1, 1), -- 5Journeyman's Stave
(1797, 2964, 0.0460, 1, 0, 1, 1), -- 6Burnt Leather Gloves
(1797, 11406, 0.0460, 1, 0, 1, 1), -- 7Rotting Bear Carcass
(1797, 6336, 0.0444, 1, 0, 1, 1), -- 5Infantry Tunic
(1797, 6511, 0.0436, 1, 0, 1, 1), -- 5Journeyman's Robe
(1797, 15932, 0.0436, 1, 0, 1, 1), -- 5Disciple's Stein
(1797, 3213, 0.0436, 1, 0, 1, 1), -- 6Veteran Bracers
(1797, 2972, 0.0420, 1, 0, 1, 1), -- 6Spellbinder Gloves
(1797, 6268, 0.0412, 1, 0, 1, 1), -- 5Pioneer Tunic
(1797, 8178, 0.0403, 1, 0, 1, 1), -- 5Training Sword
(1797, 6514, 0.0395, 1, 0, 1, 1), -- 6Disciple's Cloak
(1797, 6513, 0.0387, 1, 0, 1, 1), -- 6Disciple's Sash
(1797, 3643, 0.0387, 1, 0, 1, 1), -- 6Spellbinder Bracers
(1797, 4689, 0.0379, 1, 0, 1, 1), -- 6Hunting Cloak
(1797, 5071, 0.0371, 1, 0, 1, 1), -- 5Shadow Wand
(1797, 3207, 0.0371, 1, 0, 1, 1), -- 6Hunting Bracers
(1797, 2962, 0.0363, 1, 0, 1, 1), -- 5Burnt Leather Breeches
(1797, 9756, 0.0363, 1, 0, 1, 1), -- 5Gypsy Trousers
(1797, 9746, 0.0355, 1, 0, 1, 1), -- 6Simple Gloves
(1797, 2971, 0.0339, 1, 0, 1, 1), -- 6Spellbinder Boots
(1797, 6509, 0.0315, 1, 0, 1, 1), -- 6Infantry Belt
(1797, 6519, 0.0315, 1, 0, 1, 1), -- 6Pioneer Bracers
(1797, 9759, 0.0315, 1, 0, 1, 1), -- 6Cadet Boots
(1797, 2975, 0.0291, 1, 0, 1, 1), -- 6Hunting Boots
(1797, 9762, 0.0282, 1, 0, 1, 1), -- 6Cadet Gauntlets
(1797, 2073, 0.0274, 1, 0, 1, 1), -- 5Dwarven Hatchet
(1797, 2407, 0.0266, 1, 0, 1, 1), -- 5Pattern: White Leather Jerkin
(1797, 3651, 0.0258, 1, 0, 1, 1), -- 5Veteran Shield
(1797, 9755, 0.0258, 1, 0, 1, 1), -- 6Gypsy Gloves
(1797, 6517, 0.0242, 1, 0, 1, 1), -- 6Pioneer Belt
(1797, 6512, 0.0234, 1, 0, 1, 1), -- 5Disciple's Robe
(1797, 6555, 0.0234, 1, 0, 1, 1), -- 6Bard's Cloak
(1797, 2966, 0.0226, 1, 0, 1, 1), -- 5Warrior's Pants
(1797, 6266, 0.0218, 1, 0, 1, 1), -- 5Disciple's Vest
(1797, 9747, 0.0218, 1, 0, 1, 1), -- 5Simple Britches
(1797, 2967, 0.0218, 1, 0, 1, 1), -- 6Warrior's Boots
(1797, 6549, 0.0218, 1, 0, 1, 1), -- 6Soldier's Cloak
(1797, 2657, 0.0218, 1, 0, 1, 1), -- 6Red Leather Bag
(1797, 6507, 0.0210, 1, 0, 1, 1), -- 6Infantry Bracers
(1797, 9763, 0.0202, 1, 0, 1, 1), -- 5Cadet Leggings
(1797, 5574, 0.0202, 1, 0, 1, 1), -- 6White Leather Bag
(1797, 856, 0.0194, 1, 0, 1, 1), -- 6Blue Leather Bag
(1797, 9764, 0.0186, 1, 0, 1, 1), -- 5Cadet Shield
(1797, 2976, 0.0178, 1, 0, 1, 1), -- 5Hunting Gloves
(1797, 3652, 0.0169, 1, 0, 1, 1), -- 5Hunting Buckler
(1797, 15933, 0.0169, 1, 0, 1, 1), -- 5Simple Branch
(1797, 2553, 0.0153, 1, 0, 1, 1), -- 5Recipe: Elixir of Minor Agility
(1797, 3610, 0.0153, 1, 0, 1, 1), -- 5Plans: Gemmed Copper Gauntlets
(1797, 3609, 0.0145, 1, 0, 1, 1), -- 5Plans: Copper Chain Vest
(1797, 3036, 0.0145, 1, 0, 1, 1), -- 5Heavy Shortbow
(1797, 5573, 0.0145, 1, 0, 1, 1), -- 6Green Leather Bag
(1797, 9757, 0.0137, 1, 0, 1, 1), -- 5Gypsy Tunic
(1797, 2979, 0.0129, 1, 0, 1, 1), -- 6Veteran Boots
(1797, 62328, 0.0129, 1, 0, 1, 1), -- 7Shed Fur
(1797, 6271, 0.0121, 1, 0, 1, 1), -- 5Pattern: Red Linen Vest
(1797, 2555, 0.0121, 1, 0, 1, 1), -- 5Recipe: Swiftness Potion
(1797, 2589, 0.0121, 1, 0, 1, 1), -- 6Linen Cloth
(1797, 2980, 0.0113, 1, 0, 1, 1), -- 5Veteran Gloves
(1797, 4408, 0.0113, 1, 0, 1, 1), -- 5Schematic: Mechanical Squirrel Box
(1797, 4570, 0.0113, 1, 0, 1, 1), -- 5Birchwood Maul
(1797, 6542, 0.0113, 1, 0, 1, 1), -- 5Willow Cape
(1797, 6342, 0.0105, 1, 0, 1, 1), -- 5Formula: Enchant Chest - Minor Mana
(1797, 6537, 0.0105, 1, 0, 1, 1), -- 5Willow Boots
(1797, 5635, 0.0105, 1, 0, 1, 1), -- 6Sharp Claw
(1797, 2598, 0.0097, 1, 0, 1, 1), -- 5Pattern: Red Linen Robe
(1797, 2978, 0.0097, 1, 0, 1, 1), -- 5Veteran Leggings
(1797, 6543, 0.0097, 1, 0, 1, 1), -- 5Willow Bracers
(1797, 9749, 0.0097, 1, 0, 1, 1), -- 5Simple Blouse
(1797, 6556, 0.0089, 1, 0, 1, 1), -- 5Bard's Bracers
(1797, 7288, 0.0081, 1, 0, 1, 1), -- 5Pattern: Rugged Leather Pants
(1797, 2406, 0.0081, 1, 0, 1, 1), -- 5Pattern: Fine Leather Boots
(1797, 6550, 0.0081, 1, 0, 1, 1), -- 5Soldier's Wristguards
(1797, 2408, 0.0073, 1, 0, 1, 1), -- 5Pattern: Fine Leather Gloves
(1797, 6558, 0.0065, 1, 0, 1, 1), -- 5Bard's Belt
(1797, 9765, 0.0065, 1, 0, 1, 1), -- 5Cadet Vest
(1797, 4345, 0.0056, 1, 0, 1, 1), -- 5Pattern: Red Woolen Boots
(1797, 2855, -0.0048, 1, 0, 1, 1), -- 6Putrid Claw
(1797, 5571, 0.0048, 1, 0, 1, 1), -- 6Small Black Pouch
(1797, 12223, 0.0048, 1, 0, 1, 1), -- 6Meaty Bat Wing
(1797, 4757, 0.0048, 1, 0, 1, 1), -- 7Cracked Egg Shells
(1797, 9748, 0.0040, 1, 0, 1, 1), -- 5Simple Robe
(1797, 6344, 0.0040, 1, 0, 1, 1), -- 5Formula: Enchant Bracer - Minor Spirit
(1797, 4292, 0.0040, 1, 0, 1, 1), -- 5Pattern: Green Woolen Bag
(1797, 4346, 0.0040, 1, 0, 1, 1), -- 5Pattern: Heavy Woolen Cloak
(1797, 4409, 0.0040, 1, 0, 1, 1), -- 5Schematic: Small Seaforium Charge
(1797, 4751, -0.004, 1, 0, 1, 1), -- 6Windfury Talon
(1797, 7074, 0.0040, 1, 0, 1, 1), -- 7Chipped Claw
(1797, 2876, -0.0032, 1, 0, 1, 1), -- 6Duskbat Pelt
(1797, 21808, -0.0032, 1, 0, 1, 1), -- 6Arcane Core
(1797, 118, 0.0032, 1, 0, 1, 1), -- 6Minor Healing Potion
(1797, 2774, 0.0032, 1, 0, 1, 1), -- 7Rust-Covered Blunderbuss
(1797, 6347, 0.0024, 1, 0, 1, 1), -- 5Formula: Enchant Bracer - Minor Strength
(1797, 4293, 0.0024, 1, 0, 1, 1), -- 5Pattern: Hillman's Leather Vest
(1797, 6348, 0.0024, 1, 0, 1, 1), -- 5Formula: Enchant Weapon - Minor Beastslayer
(1797, 2859, -0.0024, 1, 0, 1, 1), -- 6Vile Fin Scale
(1797, 20797, -0.0024, 1, 0, 1, 1), -- 6Lynx Collar
(1797, 2881, 0.0016, 1, 0, 1, 1), -- 5Plans: Runed Copper Breastplate
(1797, 2409, 0.0016, 1, 0, 1, 1), -- 5Pattern: Dark Leather Tunic
(1797, 6716, 0.0016, 1, 0, 1, 1), -- 5Schematic: EZ-Thro Dynamite
(1797, 52564, 0.0016, 1, 0, 1, 1), -- 6Burning Blade Spellscroll
(1797, 5466, 0.0016, 1, 0, 1, 1), -- 6Scorpid Stinger
(1797, 2452, 0.0016, 1, 0, 1, 1), -- 6Swiftthistle
(1797, 6149, 0.0016, 1, 0, 1, 1), -- 6Greater Mana Potion
(1797, 2642, 0.0016, 1, 0, 1, 1), -- 7Loose Chain Boots
(1797, 68762, 0.0008, 1, 0, 1, 1), -- 5Imbued Cadet Cloak
(1797, 15210, 0.0008, 1, 0, 1, 1), -- 5Raider Shortsword
(1797, 117, 0.0008, 1, 0, 1, 1), -- 6Tough Jerky
(1797, 2070, 0.0008, 1, 0, 1, 1), -- 6Darnassian Bleu
(1797, 2830, -0.0008, 1, 0, 1, 1), -- 6Thurman's Remains
(1797, 3163, -0.0008, 1, 0, 1, 1), -- 6Blackened Skull
(1797, 3635, -0.0008, 1, 0, 1, 1), -- 6Maggot Eye's Paw
(1797, 4802, -0.0008, 1, 0, 1, 1), -- 6Cougar Claws
(1797, 21770, -0.0008, 1, 0, 1, 1), -- 6Ring of Mmmrrrggglll
(1797, 52077, 0.0008, 1, 0, 1, 1), -- 6Urgent Scarlet Memorandum
(1797, 828, 0.0008, 1, 0, 1, 1), -- 6Small Blue Pouch
(1797, 4496, 0.0008, 1, 0, 1, 1), -- 6Small Brown Pouch
(1797, 4537, 0.0008, 1, 0, 1, 1), -- 6Tel'Abim Banana
(1797, 6303, 0.0008, 1, 0, 1, 1), -- 6Raw Slitherskin Mackerel
(1797, 27668, 0.0008, 1, 0, 1, 1), -- 6Lynx Meat
(1797, 52079, 0.0008, 1, 0, 1, 1), -- 6A Scarlet Letter
(1797, 2960, 0.0008, 1, 0, 1, 1), -- 6Journeyman's Gloves
(1797, 1468, 0.0008, 1, 0, 1, 1), -- 6Murloc Fin
(1797, 4339, 0.0008, 1, 0, 1, 1), -- 6Bolt of Mageweave
(1797, 779, 0.0008, 1, 0, 1, 1), -- 7Shiny Seashell
(1797, 1423, 0.0008, 1, 0, 1, 1), -- 7Worn Leather Pants
(1797, 1417, 0.0008, 1, 0, 1, 1), -- 7Beaten Battle Axe
(1797, 1431, 0.0008, 1, 0, 1, 1), -- 7Patchwork Pants
(1797, 2773, 0.0008, 1, 0, 1, 1), -- 7Cracked Shortbow
(1797, 3370, 0.0008, 1, 0, 1, 1), -- 7Patchwork Belt
(1797, 1427, 0.0008, 1, 0, 1, 1); -- 7Patchwork Shoes
UPDATE `creature_template` SET `lootid` = 1797 WHERE `entry` = 1797;

--  http://www.wowhead.com/npc=1766
DELETE FROM `creature_loot_template` WHERE `entry` = 1766;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(1766, 7074, 85.0962, 1, 0, 1, 1), -- 7Chipped Claw
(1766, 2672, 83.4398, 1, 0, 1, 1), -- 6Stringy Wolf Meat
(1766, 60793, -41.889, 1, 0, 1, 1), -- 6Diseased Organ
(1766, 3301, 12.4787, 1, 0, 1, 1), -- 7Sharp Canine
(1766, 3164, 0.7866, 1, 0, 1, 1), -- 6Discolored Worg Heart
(1766, 3299, 0.4134, 1, 0, 1, 1), -- 7Fractured Canine
(1766, 818, 0.3660, 1, 0, 1, 1), -- 5Tigerseye
(1766, 1516, 0.2971, 1, 0, 1, 1), -- 7Worn Hatchet
(1766, 1510, 0.2846, 1, 0, 1, 1), -- 7Heavy Hammer
(1766, 1511, 0.2658, 1, 0, 1, 1), -- 7Commoner's Sword
(1766, 1514, 0.2649, 1, 0, 1, 1), -- 7Rusty Warhammer
(1766, 1515, 0.2541, 1, 0, 1, 1), -- 7Rough Wooden Staff
(1766, 1512, 0.2452, 1, 0, 1, 1), -- 7Crude Battle Axe
(1766, 2777, 0.2371, 1, 0, 1, 1), -- 7Feeble Shortbow
(1766, 1513, 0.2318, 1, 0, 1, 1), -- 7Old Greatsword
(1766, 3375, 0.2255, 1, 0, 1, 1), -- 7Calico Bracers
(1766, 2778, 0.2210, 1, 0, 1, 1), -- 7Cheap Blunderbuss
(1766, 1503, 0.2157, 1, 0, 1, 1), -- 7Warped Leather Boots
(1766, 2763, 0.2148, 1, 0, 1, 1), -- 7Fisherman Knife
(1766, 1509, 0.2130, 1, 0, 1, 1), -- 7Warped Leather Vest
(1766, 1499, 0.2076, 1, 0, 1, 1), -- 7Calico Pants
(1766, 1504, 0.2076, 1, 0, 1, 1), -- 7Warped Leather Bracers
(1766, 1507, 0.2058, 1, 0, 1, 1), -- 7Warped Leather Pants
(1766, 1506, 0.2022, 1, 0, 1, 1), -- 7Warped Leather Gloves
(1766, 1502, 0.1996, 1, 0, 1, 1), -- 7Warped Leather Belt
(1766, 1497, 0.1987, 1, 0, 1, 1), -- 7Calico Cloak
(1766, 3374, 0.1987, 1, 0, 1, 1), -- 7Calico Belt
(1766, 1495, 0.1906, 1, 0, 1, 1), -- 7Calico Shoes
(1766, 3300, 0.1879, 1, 0, 1, 1), -- 7Rabbit's Foot
(1766, 1501, 0.1852, 1, 0, 1, 1), -- 7Calico Tunic
(1766, 2214, 0.1826, 1, 0, 1, 1), -- 7Wooden Buckler
(1766, 1498, 0.1754, 1, 0, 1, 1), -- 7Calico Gloves
(1766, 1731, 0.1664, 1, 0, 1, 1), -- 7Worn Mail Boots
(1766, 9745, 0.1647, 1, 0, 1, 1), -- 6Simple Cape
(1766, 8180, 0.1602, 1, 0, 1, 1), -- 5Hunting Bow
(1766, 1732, 0.1584, 1, 0, 1, 1), -- 7Worn Mail Bracers
(1766, 1734, 0.1557, 1, 0, 1, 1), -- 7Worn Mail Gloves
(1766, 1737, 0.1557, 1, 0, 1, 1), -- 7Worn Mail Vest
(1766, 1730, 0.1512, 1, 0, 1, 1), -- 7Worn Mail Belt
(1766, 2140, 0.1468, 1, 0, 1, 1), -- 5Carving Knife
(1766, 2215, 0.1450, 1, 0, 1, 1), -- 7Wooden Shield
(1766, 4561, 0.1441, 1, 0, 1, 1), -- 5Scalping Tomahawk
(1766, 1735, 0.1423, 1, 0, 1, 1), -- 7Worn Mail Pants
(1766, 7351, 0.1333, 1, 0, 1, 1), -- 6Disciple's Boots
(1766, 774, 0.1199, 1, 0, 1, 1), -- 5Malachite
(1766, 4562, 0.1154, 1, 0, 1, 1), -- 5Severing Axe
(1766, 6510, 0.1154, 1, 0, 1, 1), -- 6Infantry Gauntlets
(1766, 9754, 0.1154, 1, 0, 1, 1), -- 6Gypsy Cloak
(1766, 6518, 0.1083, 1, 0, 1, 1), -- 6Pioneer Boots
(1766, 6515, 0.1038, 1, 0, 1, 1), -- 6Disciple's Gloves
(1766, 727, 0.1020, 1, 0, 1, 1), -- 5Notched Shortsword
(1766, 6506, 0.1011, 1, 0, 1, 1), -- 6Infantry Boots
(1766, 2961, 0.0984, 1, 0, 1, 1), -- 5Burnt Leather Vest
(1766, 1210, 0.0949, 1, 0, 1, 1), -- 5Shadowgem
(1766, 2965, 0.0850, 1, 0, 1, 1), -- 5Warrior's Tunic
(1766, 6521, 0.0850, 1, 0, 1, 1), -- 6Pioneer Gloves
(1766, 8178, 0.0832, 1, 0, 1, 1), -- 5Training Sword
(1766, 9761, 0.0832, 1, 0, 1, 1), -- 6Cadet Cloak
(1766, 6513, 0.0814, 1, 0, 1, 1), -- 6Disciple's Sash
(1766, 2957, 0.0796, 1, 0, 1, 1), -- 5Journeyman's Vest
(1766, 6514, 0.0796, 1, 0, 1, 1), -- 6Disciple's Cloak
(1766, 2958, 0.0779, 1, 0, 1, 1), -- 5Journeyman's Pants
(1766, 2964, 0.0779, 1, 0, 1, 1), -- 6Burnt Leather Gloves
(1766, 3192, 0.0770, 1, 0, 1, 1), -- 5Short Bastard Sword
(1766, 5069, 0.0770, 1, 0, 1, 1), -- 5Fire Wand
(1766, 6519, 0.0698, 1, 0, 1, 1), -- 6Pioneer Bracers
(1766, 6517, 0.0662, 1, 0, 1, 1), -- 6Pioneer Belt
(1766, 6511, 0.0653, 1, 0, 1, 1), -- 5Journeyman's Robe
(1766, 7350, 0.0653, 1, 0, 1, 1), -- 6Disciple's Bracers
(1766, 9742, 0.0635, 1, 0, 1, 1), -- 6Simple Cord
(1766, 9743, 0.0635, 1, 0, 1, 1), -- 6Simple Shoes
(1766, 2962, 0.0626, 1, 0, 1, 1), -- 5Burnt Leather Breeches
(1766, 9753, 0.0600, 1, 0, 1, 1), -- 5Gypsy Buckler
(1766, 7108, 0.0582, 1, 0, 1, 1), -- 5Infantry Shield
(1766, 15925, 0.0573, 1, 0, 1, 1), -- 5Journeyman's Stave
(1766, 2075, 0.0564, 1, 0, 1, 1), -- 5Heavy Mace
(1766, 4677, 0.0564, 1, 0, 1, 1), -- 6Veteran Cloak
(1766, 15932, 0.0555, 1, 0, 1, 1), -- 5Disciple's Stein
(1766, 4566, 0.0546, 1, 0, 1, 1), -- 5Sturdy Quarterstaff
(1766, 6507, 0.0546, 1, 0, 1, 1), -- 6Infantry Bracers
(1766, 4577, 0.0537, 1, 0, 1, 1), -- 5Compact Shotgun
(1766, 6267, 0.0501, 1, 0, 1, 1), -- 5Disciple's Pants
(1766, 9744, 0.0501, 1, 0, 1, 1), -- 6Simple Bands
(1766, 9751, 0.0501, 1, 0, 1, 1), -- 6Gypsy Sandals
(1766, 9760, 0.0483, 1, 0, 1, 1), -- 6Cadet Bracers
(1766, 4683, 0.0465, 1, 0, 1, 1), -- 6Spellbinder Cloak
(1766, 9752, 0.0456, 1, 0, 1, 1), -- 6Gypsy Bands
(1766, 2966, 0.0447, 1, 0, 1, 1), -- 5Warrior's Pants
(1766, 4684, 0.0421, 1, 0, 1, 1), -- 6Spellbinder Belt
(1766, 2967, 0.0412, 1, 0, 1, 1), -- 6Warrior's Boots
(1766, 2971, 0.0412, 1, 0, 1, 1), -- 6Spellbinder Boots
(1766, 6269, 0.0403, 1, 0, 1, 1), -- 5Pioneer Trousers
(1766, 4690, 0.0403, 1, 0, 1, 1), -- 6Hunting Belt
(1766, 4564, 0.0394, 1, 0, 1, 1), -- 5Spiked Club
(1766, 6268, 0.0394, 1, 0, 1, 1), -- 5Pioneer Tunic
(1766, 4689, 0.0394, 1, 0, 1, 1), -- 6Hunting Cloak
(1766, 6337, 0.0385, 1, 0, 1, 1), -- 5Infantry Leggings
(1766, 9750, 0.0376, 1, 0, 1, 1), -- 6Gypsy Sash
(1766, 6509, 0.0367, 1, 0, 1, 1), -- 6Infantry Belt
(1766, 6555, 0.0349, 1, 0, 1, 1), -- 6Bard's Cloak
(1766, 9746, 0.0340, 1, 0, 1, 1), -- 6Simple Gloves
(1766, 2632, 0.0322, 1, 0, 1, 1), -- 5Curved Dagger
(1766, 9758, 0.0322, 1, 0, 1, 1), -- 6Cadet Belt
(1766, 5071, 0.0313, 1, 0, 1, 1), -- 5Shadow Wand
(1766, 9755, 0.0313, 1, 0, 1, 1), -- 6Gypsy Gloves
(1766, 9764, 0.0286, 1, 0, 1, 1), -- 5Cadet Shield
(1766, 4569, 0.0286, 1, 0, 1, 1), -- 5Staunch Hammer
(1766, 3643, 0.0286, 1, 0, 1, 1), -- 6Spellbinder Bracers
(1766, 2972, 0.0277, 1, 0, 1, 1), -- 6Spellbinder Gloves
(1766, 9762, 0.0268, 1, 0, 1, 1), -- 6Cadet Gauntlets
(1766, 9759, 0.0260, 1, 0, 1, 1), -- 6Cadet Boots
(1766, 9747, 0.0233, 1, 0, 1, 1), -- 5Simple Britches
(1766, 2553, 0.0224, 1, 0, 1, 1), -- 5Recipe: Elixir of Minor Agility
(1766, 6336, 0.0215, 1, 0, 1, 1), -- 5Infantry Tunic
(1766, 6512, 0.0215, 1, 0, 1, 1), -- 5Disciple's Robe
(1766, 4408, 0.0215, 1, 0, 1, 1), -- 5Schematic: Mechanical Squirrel Box
(1766, 5573, 0.0215, 1, 0, 1, 1), -- 6Green Leather Bag
(1766, 6266, 0.0206, 1, 0, 1, 1), -- 5Disciple's Vest
(1766, 3213, 0.0206, 1, 0, 1, 1), -- 6Veteran Bracers
(1766, 5574, 0.0206, 1, 0, 1, 1), -- 6White Leather Bag
(1766, 9756, 0.0188, 1, 0, 1, 1), -- 5Gypsy Trousers
(1766, 2979, 0.0179, 1, 0, 1, 1), -- 6Veteran Boots
(1766, 856, 0.0179, 1, 0, 1, 1), -- 6Blue Leather Bag
(1766, 6342, 0.0161, 1, 0, 1, 1), -- 5Formula: Enchant Chest - Minor Mana
(1766, 6549, 0.0161, 1, 0, 1, 1), -- 6Soldier's Cloak
(1766, 2657, 0.0161, 1, 0, 1, 1), -- 6Red Leather Bag
(1766, 3207, 0.0152, 1, 0, 1, 1), -- 6Hunting Bracers
(1766, 4678, 0.0152, 1, 0, 1, 1), -- 6Veteran Girdle
(1766, 5635, 0.0152, 1, 0, 1, 1), -- 6Sharp Claw
(1766, 3651, 0.0143, 1, 0, 1, 1), -- 5Veteran Shield
(1766, 2407, 0.0134, 1, 0, 1, 1), -- 5Pattern: White Leather Jerkin
(1766, 2406, 0.0134, 1, 0, 1, 1), -- 5Pattern: Fine Leather Boots
(1766, 2975, 0.0134, 1, 0, 1, 1), -- 6Hunting Boots
(1766, 2598, 0.0125, 1, 0, 1, 1), -- 5Pattern: Red Linen Robe
(1766, 3609, 0.0125, 1, 0, 1, 1), -- 5Plans: Copper Chain Vest
(1766, 3652, 0.0125, 1, 0, 1, 1), -- 5Hunting Buckler
(1766, 2408, 0.0125, 1, 0, 1, 1), -- 5Pattern: Fine Leather Gloves
(1766, 6271, 0.0116, 1, 0, 1, 1), -- 5Pattern: Red Linen Vest
(1766, 9763, 0.0116, 1, 0, 1, 1), -- 5Cadet Leggings
(1766, 2555, 0.0116, 1, 0, 1, 1), -- 5Recipe: Swiftness Potion
(1766, 3610, 0.0107, 1, 0, 1, 1), -- 5Plans: Gemmed Copper Gauntlets
(1766, 15933, 0.0107, 1, 0, 1, 1), -- 5Simple Branch
(1766, 62328, 0.0089, 1, 0, 1, 1), -- 7Shed Fur
(1766, 7288, 0.0081, 1, 0, 1, 1), -- 5Pattern: Rugged Leather Pants
(1766, 4293, 0.0054, 1, 0, 1, 1), -- 5Pattern: Hillman's Leather Vest
(1766, 4346, 0.0054, 1, 0, 1, 1), -- 5Pattern: Heavy Woolen Cloak
(1766, 3173, 0.0054, 1, 0, 1, 1), -- 6Bear Meat
(1766, 4292, 0.0045, 1, 0, 1, 1), -- 5Pattern: Green Woolen Bag
(1766, 4751, -0.0045, 1, 0, 1, 1), -- 6Windfury Talon
(1766, 828, 0.0045, 1, 0, 1, 1), -- 6Small Blue Pouch
(1766, 3169, 0.0045, 1, 0, 1, 1), -- 7Chipped Bear Tooth
(1766, 2881, 0.0036, 1, 0, 1, 1), -- 5Plans: Runed Copper Breastplate
(1766, 2409, 0.0036, 1, 0, 1, 1), -- 5Pattern: Dark Leather Tunic
(1766, 5204, -0.0036, 1, 0, 1, 1), -- 6Bloodfeather Belt
(1766, 6347, 0.0027, 1, 0, 1, 1), -- 5Formula: Enchant Bracer - Minor Strength
(1766, 6716, 0.0027, 1, 0, 1, 1), -- 5Schematic: EZ-Thro Dynamite
(1766, 2855, -0.0027, 1, 0, 1, 1), -- 6Putrid Claw
(1766, 2859, -0.0027, 1, 0, 1, 1), -- 6Vile Fin Scale
(1766, 2589, 0.0027, 1, 0, 1, 1), -- 6Linen Cloth
(1766, 6344, 0.0018, 1, 0, 1, 1), -- 5Formula: Enchant Bracer - Minor Spirit
(1766, 117, 0.0018, 1, 0, 1, 1), -- 6Tough Jerky
(1766, 6303, 0.0018, 1, 0, 1, 1), -- 6Raw Slitherskin Mackerel
(1766, 1468, 0.0018, 1, 0, 1, 1), -- 6Murloc Fin
(1766, 4757, 0.0018, 1, 0, 1, 1), -- 7Cracked Egg Shells
(1766, 20812, 0.0018, 1, 0, 1, 1), -- 7Tattered Pelt
(1766, 60743, 0.0018, 1, 0, 1, 1), -- 7Diseased Beast Guts
(1766, 6556, 0.0009, 1, 0, 1, 1), -- 5Bard's Bracers
(1766, 6548, 0.0009, 1, 0, 1, 1), -- 5Soldier's Girdle
(1766, 4345, 0.0009, 1, 0, 1, 1), -- 5Pattern: Red Woolen Boots
(1766, 4409, 0.0009, 1, 0, 1, 1), -- 5Schematic: Small Seaforium Charge
(1766, 6348, 0.0009, 1, 0, 1, 1), -- 5Formula: Enchant Weapon - Minor Beastslayer
(1766, 2070, 0.0009, 1, 0, 1, 1), -- 6Darnassian Bleu
(1766, 2831, -0.0009, 1, 0, 1, 1), -- 6Devlin's Remains
(1766, 2834, -0.0009, 1, 0, 1, 1), -- 6Embalming Ichor
(1766, 2858, -0.0009, 1, 0, 1, 1), -- 6Darkhound Blood
(1766, 4604, 0.0009, 1, 0, 1, 1), -- 6Forest Mushroom Cap
(1766, 7097, 0.0009, 1, 0, 1, 1), -- 6Leg Meat
(1766, 20764, -0.0009, 1, 0, 1, 1), -- 6Prospector Anvilward's Head
(1766, 20797, -0.0009, 1, 0, 1, 1), -- 6Lynx Collar
(1766, 21808, -0.0009, 1, 0, 1, 1), -- 6Arcane Core
(1766, 23334, 0.0009, 1, 0, 1, 1), -- 6Cracked Power Core
(1766, 52077, 0.0009, 1, 0, 1, 1), -- 6Urgent Scarlet Memorandum
(1766, 118, 0.0009, 1, 0, 1, 1), -- 6Minor Healing Potion
(1766, 12223, 0.0009, 1, 0, 1, 1), -- 6Meaty Bat Wing
(1766, 2452, 0.0009, 1, 0, 1, 1), -- 6Swiftthistle
(1766, 4865, 0.0009, 1, 0, 1, 1), -- 7Ruined Pelt
(1766, 56151, 0.0009, 1, 0, 1, 1), -- 7Broken Hoof Piece
(1766, 3370, 0.0009, 1, 0, 1, 1), -- 7Patchwork Belt
(1766, 1415, 0.0009, 1, 0, 1, 1), -- 7Carpenter's Mallet
(1766, 1425, 0.0009, 1, 0, 1, 1); -- 7Worn Leather Vest
UPDATE `creature_template` SET `lootid` = 1766 WHERE `entry` = 1766;

DELETE FROM creature_addon WHERE guid in (47250,58678,58726,58728,58741,58750,58752,58800,58826,58833,58864,58869,58878,58941,58959,58979,58982,58984,59028,59050,59052,59054,59071,59081,59110,59114,59115,59147,59155,59159,59242,59243,59303,59326,59331,59339,59340,59344,59353,59388,59394,59399,59477,59478,59481,59482,59503,59515,59555,59558,59573,59576,59586,59632,59637,59641,59677,59679,59681,59691,59707,59723,59747,59751,59772,59799,59804,59806,59872,59879,59928,59942,59944,59956,59968,59970,59971,59983,60014,60018,60023);

UPDATE `quest_template` SET `PrevQuestId` = 27476 WHERE `Id` = 27483;
UPDATE `quest_template` SET `PrevQuestId` = 27476 WHERE `Id` = 27480;
UPDATE `quest_template` SET `PrevQuestId` = 27484 WHERE `Id` = 27510;
UPDATE `quest_template` SET `PrevQuestId` = 27518 WHERE `Id` = 27542;
UPDATE `quest_template` SET `PrevQuestId` = 27542 WHERE `Id` = 27550;
UPDATE `quest_template` SET `PrevQuestId` = 27542 WHERE `Id` = 27548;
UPDATE `quest_template` SET `PrevQuestId` = 27542 WHERE `Id` = 27547;

DELETE FROM `gameobject` WHERE `id`=106319;
DELETE FROM `creature_text` WHERE `entry`=44942;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44942, 0, 0, 'Thank you, friend. Let\'ll end a couple of those ... Spider-age. Y-yes ... it sounds like something out loud is not very ...', 12, 0, 100, 5, 0, 0, '???-??????? ????'),
(44942, 0, 1, 'We will find the commander of the operation and finish!', 12, 0, 100, 5, 0, 0, '???-??????? ????'),
(44942, 0, 2, 'I need a drink!', 12, 0, 100, 5, 0, 0, '???-??????? ????');

-- Webbed Victim
SET @ENTRY := 44941;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,86,83927,0,21,100,0,0,21,100,0,0,0.0,0.0,0.0,0.0,"closest player cast 83927");

UPDATE `creature_template` SET `minlevel` = 11, `maxlevel` = 11, `faction_A` = 5, `faction_H` = 5, `unit_flags` = 32776, `AIName` = '' WHERE `entry` = 44942;

-- Orc Sea Dog
SET @ENTRY := 44942;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,4494200,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Do Action on summon"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Run");


-- Orc Sea Dog
SET @ENTRY := 4494200;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,33,44942,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Give Credit"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,25000,25000,25000,25000,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn on OOC"),
(@ENTRY,@SOURCETYPE,3,0,37,0,100,0,0,0,0,0,29,0,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Follow Owner on Spawn");

UPDATE `creature_template` SET `KillCredit1` = 1781 WHERE `entry` = 1780;

UPDATE `creature_template` SET `VehicleId` = 1063 WHERE `entry` = 44367;

DELETE FROM creature WHERE id=44367;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(44367, 0, 1, 1, 781.967, 1633.18, 29.73663, 0.8739128, 120, 0, 0); -- 44367 (Area: 928) (possible waypoints or random movement)

UPDATE `creature` SET `movementtype`= 1, `spawndist`= 120 WHERE `id`= 44367;

-- Mutant Bush Chicken
SET @ENTRY := 44935;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,37,0,100,1,1000,1000,0,0,29,0,0,0,0,0,0,11,44367,100,0,0.0,0.0,0.0,0.0,"on summon go to Ettin"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,80,4493500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on data set 1 do action"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"set run self");

-- Mutant Bush Chicken
SET @ENTRY := 4493500;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,1000,1000,11,46598,0,0,0,0,0,19,44367,100,0,0.0,0.0,0.0,0.0,"Jump on Ettin"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,0,0,11,83903,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Explode"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,33,44367,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Death Quest Complete");

-- Forest Ettin
SET @ENTRY := 44367;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,7000,17000,22000,11,80146,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Bonk"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,12000,15000,28000,35000,11,88421,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Log Smash"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,1500,1500,1500,45,0,1,0,0,0,0,19,44935,10,0,0.0,0.0,0.0,0.0,"update send data to chicken");

UPDATE `quest_template` SET `SourceSpellId` = 83982 WHERE `Id` = 27097;
UPDATE `creature_template` SET `minlevel` = 15, `maxlevel` = 15, `faction_A` = 5, `faction_H` = 5, `attackpower` = 6520, `unit_flags` = 32776, `type_flags` = 0, `VehicleId` = 1075, `InhabitType` = 4, `HoverHeight` = 2.4 WHERE `entry` = 44951;
DELETE FROM `creature_template_addon` WHERE (`entry`=44951);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (44951, 0, 0, 50397184, 1, 0, '');
UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 44951;

DELETE FROM `creature_text` WHERE entry=44951;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44951, 0, 1, 'The warmth of this place sickens me.', 12, 0, 100, 0, 0, 0, '?????'),
(44951, 0, 0, 'I sense doom in your future, $n.', 12, 0, 100, 0, 0, 0, '?????'),
(44951, 1, 0, 'Rise and destroy our enemies!', 14, 0, 100, 0, 0, 0, '????? to ???????????? ???????'),
(44951, 1, 1, 'Rise, Hillsbrad Refugee! Become Forsaken!', 14, 0, 100, 0, 0, 0, '????? to ???????????? ???????'),
(44951, 0, 2, 'Waste no time, $n. We mustn''t keep the Banshee Queen waiting.', 12, 0, 100, 0, 0, 0, '?????'),
(44951, 1, 2, 'Bow before your new master!', 14, 0, 100, 0, 0, 0, '????? to ???????????? ???????'),
(44951, 2, 0, 'This way, $n. We will take them by surprise.', 12, 0, 100, 457, 0, 0, '?????'),
(44951, 3, 0, 'Run...', 12, 0, 100, 457, 0, 0, '????? to ??????? ????? ????? ?????'),
(44951, 3, 1, 'RUN!', 12, 0, 100, 457, 0, 0, '????? to ??????? ????? ????? ?????');

DELETE FROM `creature_involvedrelation` WHERE id=44951;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES ('44951', '27097');

DELETE FROM `creature_text` WHERE entry=44963;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(44963, 0, 0, 'To the glory of the Dark Lady!', 12, 1, 100, 15, 0, 0, '??????????-???? to ???????????? ???????'),
(44963, 0, 1, 'I am eternal... I am death.', 12, 1, 100, 273, 0, 0, '??????????-???? to ???????????? ???????'),
(44963, 0, 2, 'Wha... What has happened?', 12, 1, 100, 6, 0, 0, '??????????-???? to ???????????? ???????'),
(44963, 0, 3, 'I am Forsaken.', 12, 1, 100, 66, 0, 0, '??????????-???? to ???????????? ???????');
UPDATE `creature_template` SET `faction_A` = 68, `faction_H` = 68, `unit_flags` = 33536 WHERE `entry` = 44963;

DELETE FROM `creature_template_addon` WHERE (`entry`=45270);
DELETE FROM `creature` WHERE `id`=45270;

SET @CGUID := 786772;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+15;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 44954, 0, 1, 1, 1065.004, 739.4683, 45.38259, 2.951549, 120, 0, 0), 
(@CGUID+1, 44954, 0, 1, 1, 1078.26, 716.108, 46.21903, 3.065562, 120, 0, 0), 
(@CGUID+2, 44954, 0, 1, 1, 1078.032, 713.1166, 46.86649, 3.071656, 120, 0, 0), 
(@CGUID+3, 44954, 0, 1, 1, 977.925, 630.656, 53.40493, 2.984513, 120, 0, 0), 
(@CGUID+4, 44954, 0, 1, 1, 950.566, 627.721, 53.61423, 1.48353, 120, 0, 0), 
(@CGUID+5, 44954, 0, 1, 1, 988.238, 605.0987, 55.0663, 5.943095, 120, 0, 0), 
(@CGUID+6, 44954, 0, 1, 1, 948.477, 634.106, 53.43565, 5.646388, 120, 0, 0), 
(@CGUID+7, 44954, 0, 1, 1, 953.5855, 712.905, 59.39228, 4.721546, 120, 0, 0), 
(@CGUID+8, 44954, 0, 1, 1, 985.6078, 743.5355, 60.09973, 1.385859, 120, 0, 0), 
(@CGUID+9, 44954, 0, 1, 1, 944.83, 681.802, 59.34833, 3.228859, 120, 0, 0), 
(@CGUID+10, 44954, 0, 1, 1, 977.24, 636.233, 53.70723, 3.036873, 120, 0, 0), 
(@CGUID+11, 44954, 0, 1, 1, 914.627, 697.276, 54.19193, 1.518436, 120, 0, 0), 
(@CGUID+12, 44954, 0, 1, 1, 913.1692, 712.7667, 55.29779, 2.358877, 120, 0, 0), 
(@CGUID+13, 44954, 0, 1, 1, 912.052, 680.637, 53.63503, 3.193953, 120, 0, 0), 
(@CGUID+14, 44954, 0, 1, 1, 855.2161, 594.6187, 35.90318, 2.884347, 120, 0, 0), 
(@CGUID+15, 44954, 0, 1, 1, 863.6045, 595.5145, 36.40539, 2.884965, 120, 0, 0); 

DELETE FROM `creature` WHERE `id`=44962;
DELETE FROM `creature` WHERE `id`=44963;
DELETE FROM `creature` WHERE `id`=44964;
DELETE FROM `creature` WHERE `id`=44965;

DELETE FROM creature WHERE id=44966;
SET @CGUID := 786788;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+14;
INSERT INTO creature(guid, id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, npcflag, unit_flags, dynamicflags) VALUES 
(@CGUID+0, 44966, 0, 1, 1, 0, 0, 977.655, 614.695, 54.0813, 1.13184, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+1, 44966, 0, 1, 1, 0, 0, 1002.91, 734.892, 59.2673, 2.38464, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+2, 44966, 0, 1, 1, 0, 0, 963.105, 729.727, 59.3923, 2.82878, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+3, 44966, 0, 1, 1, 0, 0, 1022.21, 725.2, 60.2404, 0.10472, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+4, 44966, 0, 1, 1, 0, 0, 946.639, 696.479, 59.3605, 1.58825, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+5, 44966, 0, 1, 1, 0, 0, 1022.32, 728.483, 59.4135, 6.10865, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+6, 44966, 0, 1, 1, 0, 0, 944.477, 694.101, 59.367, 3.26377, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+7, 44966, 0, 1, 1, 0, 0, 944.193, 679.759, 59.3609, 3.28122, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+8, 44966, 0, 1, 1, 0, 0, 1051.47, 693.757, 53.5873, 0.478449, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+9, 44966, 0, 1, 1, 0, 0, 1047.48, 729.684, 51.9015, 0.668456, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+10, 44966, 0, 1, 1, 0, 0, 912.061, 693.785, 53.6937, 3.15905, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+11, 44966, 0, 1, 1, 0, 0, 854.571, 687.913, 53.501, 6.24887, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+12, 44966, 0, 1, 1, 0, 0, 854.613, 696.894, 53.6658, 3.35103, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+13, 44966, 0, 1, 1, 0, 0, 912.061, 693.785, 53.6937, 3.15905, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+14, 44966, 0, 1, 1, 0, 0, 912.052, 680.637, 53.635, 3.19395, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `id`=44961;
DELETE FROM `creature` WHERE `id`=44960;
DELETE FROM `creature` WHERE `id`=44959;
DELETE FROM `creature` WHERE `id`=44958;
DELETE FROM `creature` WHERE `id`=1954;
DELETE FROM `creature` WHERE `id`=1953;
DELETE FROM `creature` WHERE `id`=1944;
DELETE FROM `creature` WHERE `id`=1909;
DELETE FROM creature WHERE id=1908;
SET @CGUID := 786802;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+109;
INSERT INTO creature(guid, id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, npcflag, unit_flags, dynamicflags) VALUES 
(@CGUID+0, 1908, 0, 1, 1, 0, 0, 1185.31, 414.162, 49.5933, 4.84222, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+1, 1908, 0, 1, 1, 0, 0, 1187.02, 395.631, 33.68, 0.2357, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+2, 1908, 0, 1, 1, 0, 0, 1206.91, 392.507, 33.8836, 2.39373, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+3, 1908, 0, 1, 1, 0, 0, 1207.46, 391.894, 33.8453, 1.309, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+4, 1908, 0, 1, 1, 0, 0, 1164.88, 389.356, 42.8029, 5.49843, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+5, 1908, 0, 1, 1, 0, 0, 1205.21, 386.459, 35.1851, 6.05968, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+6, 1908, 0, 1, 1, 0, 0, 1208.71, 384.444, 34.2874, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+7, 1908, 0, 1, 1, 0, 0, 1209.09, 384.243, 34.1787, 3.91543, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+8, 1908, 0, 1, 1, 0, 0, 1205.48, 379.745, 35.3102, 5.32067, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+9, 1908, 0, 1, 1, 0, 0, 1191.52, 377.749, 34.6118, 4.9681, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+10, 1908, 0, 1, 1, 0, 0, 1209.65, 377.613, 34.9533, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+11, 1908, 0, 1, 1, 0, 0, 1209.81, 377.42, 34.9229, 2.87392, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+12, 1908, 0, 1, 1, 0, 0, 1213.38, 375.974, 33.7508, 6.02605, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+13, 1908, 0, 1, 1, 0, 0, 1214.07, 375.45, 33.4909, 0.837758, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+14, 1908, 0, 1, 1, 0, 0, 1205.97, 372.136, 34.5291, 5.71359, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+15, 1908, 0, 1, 1, 0, 0, 1214.88, 368.227, 33.1559, 5.63741, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+16, 1908, 0, 1, 1, 0, 0, 1186.54, 357.611, 33.3138, 0.934485, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+17, 1908, 0, 1, 1, 0, 0, 1201.2, 355.009, 34.2184, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+18, 1908, 0, 1, 1, 0, 0, 1202.37, 348.826, 34.8965, 1.02232, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+19, 1908, 0, 1, 1, 0, 0, 1207.03, 343.741, 35.096, 3.53238, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+20, 1908, 0, 1, 1, 0, 0, 1197.2, 341.508, 34.8138, 5.38283, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+21, 1908, 0, 1, 1, 0, 0, 1197.86, 341.314, 34.8853, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+22, 1908, 0, 1, 1, 0, 0, 1206.43, 330.7, 35.6831, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+23, 1908, 0, 1, 1, 0, 0, 1206.9, 327.5, 35.4892, 6.03252, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+24, 1908, 0, 1, 1, 0, 0, 1184.9, 326.56, 35.8642, 5.85624, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+25, 1908, 0, 1, 1, 0, 0, 1173.31, 304.035, 34.0949, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+26, 1908, 0, 1, 1, 0, 0, 1119.49, 313.508, 33.9023, 0.215139, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+27, 1908, 0, 1, 1, 0, 0, 1092.34, 320.01, 36.1971, 0.191366, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+28, 1908, 0, 1, 1, 0, 0, 1121.07, 295.027, 33.3797, 0.478103, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+29, 1908, 0, 1, 1, 0, 0, 1091.06, 307.8, 37.5178, 1.73181, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+30, 1908, 0, 1, 1, 0, 0, 1080.39, 316.139, 36.0186, 3.95285, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+31, 1908, 0, 1, 1, 0, 0, 1108.75, 275.125, 34.3927, 3.13995, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+32, 1908, 0, 1, 1, 0, 0, 1109.46, 247.474, 34.0745, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+33, 1908, 0, 1, 1, 0, 0, 1085.44, 261.636, 34.9729, 1.79655, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+34, 1908, 0, 1, 1, 0, 0, 1070.9, 270.911, 35.8935, 2.33091, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+35, 1908, 0, 1, 1, 0, 0, 1125.61, 223.517, 34.0261, 1.84197, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+36, 1908, 0, 1, 1, 0, 0, 1110.43, 230.991, 34.0745, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+37, 1908, 0, 1, 1, 0, 0, 1082.79, 251.669, 35.2698, 0.555996, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+38, 1908, 0, 1, 1, 0, 0, 1051.01, 280.637, 36.1067, 0.594788, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+39, 1908, 0, 1, 1, 0, 0, 1041.67, 225, 35.67, 2.93736, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+40, 1908, 0, 1, 1, 0, 0, 1043.96, 247.663, 36.7806, 1.62172, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+41, 1908, 0, 1, 1, 0, 0, 1111.41, 211.209, 36.0015, 2.07539, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+42, 1908, 0, 1, 1, 0, 0, 1095.72, 212.644, 35.2188, 1.50264, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+43, 1908, 0, 1, 1, 0, 0, 1089.88, 241.215, 35.1162, 0.544105, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+44, 1908, 0, 1, 1, 0, 0, 1098.63, 222.955, 36.14, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+45, 1908, 0, 1, 1, 0, 0, 1096.52, 207.795, 35.247, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+46, 1908, 0, 1, 1, 0, 0, 1027.68, 275.652, 34.9801, 2.2359, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+47, 1908, 0, 1, 1, 0, 0, 1034.48, 178.321, 31.1297, 0.153508, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+48, 1908, 0, 1, 1, 0, 0, 1023.49, 153.177, 37.0377, 5.19873, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+49, 1908, 0, 1, 1, 0, 0, 1012.83, 168.328, 40.1206, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+50, 1908, 0, 1, 1, 0, 0, 994.842, 196.868, 34.3679, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+51, 1908, 0, 1, 1, 0, 0, 1008.83, 154.12, 40.7567, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+52, 1908, 0, 1, 1, 0, 0, 995.319, 163.626, 39.0784, 1.76921, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+53, 1908, 0, 1, 1, 0, 0, 981.296, 181.96, 36.7678, 2.72071, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+54, 1908, 0, 1, 1, 0, 0, 979.833, 180.622, 37.1221, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+55, 1908, 0, 1, 1, 0, 0, 979.486, 157.065, 37.472, 1.95009, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+56, 1908, 0, 1, 1, 0, 0, 978.288, 150.145, 37.554, 3.13382, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+57, 1908, 0, 1, 1, 0, 0, 959.114, 208.201, 35.6375, 5.91845, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+58, 1908, 0, 1, 1, 0, 0, 980.2, 137.755, 35.6254, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+59, 1908, 0, 1, 1, 0, 0, 961.119, 167.971, 38.0604, 4.65768, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+60, 1908, 0, 1, 1, 0, 0, 969.842, 147.526, 36.8377, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+61, 1908, 0, 1, 1, 0, 0, 952.331, 188.18, 38.5821, 2.18379, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+62, 1908, 0, 1, 1, 0, 0, 961.591, 140.566, 35.5633, 4.78558, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+63, 1908, 0, 1, 1, 0, 0, 938.368, 206.513, 37.2047, 0.230281, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+64, 1908, 0, 1, 1, 0, 0, 865.994, 170.738, 35.268, 6.13052, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+65, 1908, 0, 1, 1, 0, 0, 924.341, 190.332, 38.7584, 2.08073, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+66, 1908, 0, 1, 1, 0, 0, 894.284, 221.898, 33.486, 5.48674, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+67, 1908, 0, 1, 1, 0, 0, 909.298, 149.083, 37.3836, 4.11309, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+68, 1908, 0, 1, 1, 0, 0, 905.318, 159.471, 37.6319, 5.88782, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+69, 1908, 0, 1, 1, 0, 0, 939.165, 128.749, 33.882, 0.0960076, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+70, 1908, 0, 1, 1, 0, 0, 903.497, 141.882, 35.7757, 0.971526, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+71, 1908, 0, 1, 1, 0, 0, 861.962, 116.549, 33.515, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+72, 1908, 0, 1, 1, 0, 0, 853.469, 127.627, 37.5903, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+73, 1908, 0, 1, 1, 0, 0, 879.9, 86.4353, 34.0746, 2.34897, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+74, 1908, 0, 1, 1, 0, 0, 838.171, 145.387, 37.6239, 3.2433, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+75, 1908, 0, 1, 1, 0, 0, 872.78, 80.9699, 33.9976, 1.48454, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+76, 1908, 0, 1, 1, 0, 0, 872.813, 80.6458, 33.9618, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+77, 1908, 0, 1, 1, 0, 0, 869.172, 78.7587, 34.0472, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+78, 1908, 0, 1, 1, 0, 0, 867.599, 75.3351, 33.7361, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+79, 1908, 0, 1, 1, 0, 0, 858.809, 82.6181, 34.7726, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+80, 1908, 0, 1, 1, 0, 0, 862.194, 79.0052, 34.6184, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+81, 1908, 0, 1, 1, 0, 0, 858.93, 82.3663, 34.6082, 5.81076, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+82, 1908, 0, 1, 1, 0, 0, 858.623, 70.6493, 34.3896, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+83, 1908, 0, 1, 1, 0, 0, 859.623, 69.5067, 34.0515, 0.802738, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+84, 1908, 0, 1, 1, 0, 0, 804.986, 164.122, 34.3587, 5.18034, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+85, 1908, 0, 1, 1, 0, 0, 819.247, 102.375, 37.679, 4.40664, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+86, 1908, 0, 1, 1, 0, 0, 803.295, 194.98, 34.9169, 1.44366, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+87, 1908, 0, 1, 1, 0, 0, 806.287, 122.9, 38.423, 3.93483, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+88, 1908, 0, 1, 1, 0, 0, 798.25, 156.826, 35.5367, 0.965001, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+89, 1908, 0, 1, 1, 0, 0, 826.067, 76.3143, 36.1883, 1.70838, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+90, 1908, 0, 1, 1, 0, 0, 821.309, 79.309, 35.5278, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+91, 1908, 0, 1, 1, 0, 0, 831.438, 63.7344, 36.2486, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+92, 1908, 0, 1, 1, 0, 0, 829.065, 62.3845, 36.008, 3.67354, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+93, 1908, 0, 1, 1, 0, 0, 789.902, 195.952, 37.925, 2.95889, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+94, 1908, 0, 1, 1, 0, 0, 808.007, 60.4895, 34.936, 1.47733, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+95, 1908, 0, 1, 1, 0, 0, 786.403, 96.8742, 35.2005, 4.06828, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+96, 1908, 0, 1, 1, 0, 0, 775.06, 215.804, 42.0516, 5.83742, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+97, 1908, 0, 1, 1, 0, 0, 775.745, 241.594, 37.6443, 2.79971, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+98, 1908, 0, 1, 1, 0, 0, 769.191, 112.995, 35.1718, 3.05854, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+99, 1908, 0, 1, 1, 0, 0, 714.389, 202.537, 34.5639, 0.899462, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+100, 1908, 0, 1, 1, 0, 0, 710.434, 206.7, 34.2309, 1.60301, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+101, 1908, 0, 1, 1, 0, 0, 713.254, 211.199, 35.5809, 2.35584, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+102, 1908, 0, 1, 1, 0, 0, 727.64, 192.201, 33.5958, 3.12837, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+103, 1908, 0, 1, 1, 0, 0, 719.01, 197.271, 34.1878, 5.16304, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+104, 1908, 0, 1, 1, 0, 0, 728.743, 203.755, 35.8935, 5.22318, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+105, 1908, 0, 1, 1, 0, 0, 744.735, 203.953, 37.9123, 2.71028, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+106, 1908, 0, 1, 1, 0, 0, 737.135, 190.452, 33.9445, 1.16531, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+107, 1908, 0, 1, 1, 0, 0, 782.693, 271.252, 36.7301, 5.88035, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+108, 1908, 0, 1, 1, 0, 0, 750.909, 275.238, 38.6943, 3.53114, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+109, 1908, 0, 1, 1, 0, 0, 740.213, 307.378, 33.6491, 2.09507, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=44966;
SET @CGUID := 786912;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+14;
INSERT INTO creature(guid, id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, MovementType, npcflag, unit_flags, dynamicflags) VALUES 
(@CGUID+0, 44966, 0, 1, 1, 0, 0, 912.052, 680.637, 53.635, 3.19395, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+1, 44966, 0, 1, 1, 0, 0, 912.061, 693.785, 53.6937, 3.15905, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+2,44966, 0, 1, 1, 0, 0, 854.613, 696.894, 53.6658, 3.35103, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+3,44966, 0, 1, 1, 0, 0, 854.571, 687.913, 53.501, 6.24887, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+4,44966, 0, 1, 1, 0, 0, 912.061, 693.785, 53.6937, 3.15905, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+5,44966, 0, 1, 1, 0, 0, 1047.48, 729.684, 51.9015, 0.668456, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+6,44966, 0, 1, 1, 0, 0, 1051.47, 693.757, 53.5873, 0.478449, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+7,44966, 0, 1, 1, 0, 0, 944.193, 679.759, 59.3609, 3.28122, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+8,44966, 0, 1, 1, 0, 0, 944.477, 694.101, 59.367, 3.26377, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+9,44966, 0, 1, 1, 0, 0, 1022.32, 728.483, 59.4135, 6.10865, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+10,44966, 0, 1, 1, 0, 0, 946.639, 696.479, 59.3605, 1.58825, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+11,44966, 0, 1, 1, 0, 0, 1022.21, 725.2, 60.2404, 0.10472, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+12,44966, 0, 1, 1, 0, 0, 963.105, 729.727, 59.3923, 2.82878, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+13,44966, 0, 1, 1, 0, 0, 1002.91, 734.892, 59.2673, 2.38464, 120, 0, 0, 1, 0, 0, 0, 0, 0),
(@CGUID+14,44966, 0, 1, 1, 0, 0, 977.655, 614.695, 54.0813, 1.13184, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `id`=1947;
DELETE FROM `creature` WHERE `id`=1948;
DELETE FROM `creature` WHERE `id`=45032;

UPDATE `creature_template` SET `npcflag` = 0 WHERE `entry` = 45195;

-- Bloodfang Stalker
SET @ENTRY := 45195;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,11,0,100,1,0,0,0,0,11,86237,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Stalking on Spawn"),
(@ENTRY,@SOURCETYPE,1,0,7,0,100,1,0,0,0,0,11,86237,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Stalking on Evade"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,30,0,0,11,79864,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shadowstep at 30% HP"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3000,4500,12000,15000,11,60195,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Sinister Strike"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,7,27181,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"on death add quest 27181");

DELETE FROM conditions WHERE SourceTypeOrReferenceId=22 AND ConditionTypeOrReference=8;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=22 AND ConditionTypeOrReference=9;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=22 AND ConditionTypeOrReference=28;
INSERT INTO conditions(SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ErrorTextId, ScriptName, Comment) VALUES 
(22, 5, 45195, 0, 0, 8, 0, 27181, 0, 0, 1, 0, 0, '', null),
(22, 5, 45195, 0, 0, 9, 0, 27181, 0, 0, 1, 0, 0, '', null),
(22, 5, 45195, 0, 0, 28, 0, 27181, 0, 0, 1, 0, 0, '', null);

UPDATE creature_template SET faction_A=16 WHERE entry=49424;
UPDATE creature_template SET faction_H=16 WHERE entry=49424;
UPDATE creature_template set modelid1=16480,modelid2=0, modelid3=0,modelid4=0 WHERE entry=50373;
UPDATE creature_template set flags_extra=128 WHERE entry=50373;


--- STOPPED HERE (TODO: CONTINUE OPTIMIZING)

DELETE FROM gameobject WHERE id IN (2843, 2849, 75293, 106318, 205878, 205879, 205880, 205881);
INSERT INTO gameobject(id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, rotation0, rotation1, rotation2, rotation3, spawntimesecs, animprogress, state) VALUES 
(2843, 0, 1, 1, 2081.69, 1967.03, 101.193, 2.82743, 0, 0, 0.987688, 0.156436, 120, 100, 1),
(2849, 0, 1, 1, -11332, 1731.29, 38.489, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 0, 1, 1, 2549.84, 783.776, 110.478, 3.072, 0, 0, 0.999395, 0.0347893, 120, 100, 1),
(2843, 0, 1, 1, 1788.45, 1344.75, 89.389, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 0, 1, 1, -9973.6, -155.299, 24.4805, 1.23918, 0, 0, 0.580701, 0.814117, 120, 100, 1),
(106318, 0, 1, 1, 2603.06, 1464.46, -10.673, 2.53072, 0, 0, 0.953716, 0.300709, 120, 100, 1),
(106318, 0, 1, 1, -9734, 136.241, 18.712, -3, 0, 0, -0.997495, 0.0707372, 120, 100, 1),
(2849, 0, 1, 1, -5700.12, -3867.4, 331.614, -1.27409, 0, 0, -0.594823, 0.803857, 120, 100, 1),
(2849, 0, 1, 1, -5117.36, -3315.32, 250.467, -1.18682, 0, 0, -0.559191, 0.829039, 120, 100, 1),
(2849, 0, 1, 1, -9251.55, -2707.21, 88.8043, 1.93731, 0, 0, 0.824125, 0.566409, 120, 100, 1),
(2849, 0, 1, 1, -8949.61, -2309.69, 132.443, 2.72271, 0, 0, 0.978147, 0.207914, 120, 100, 1),
(2849, 0, 1, 1, -9779.8, -2270.56, 59.3705, 2.65289, 0, 0, 0.970294, 0.241927, 120, 100, 1),
(2843, 0, 1, 1, -6524.63, 362.427, 388.329, -2.75761, 0, 0, -0.981626, 0.190814, 120, 100, 1),
(2843, 0, 1, 1, -6507.27, 688.761, 387.274, -0.314158, 0, 0, -0.156434, 0.987688, 120, 100, 1),
(106318, 0, 1, 1, -9838.12, 207.45, 14.054, 1.06465, 0, 0, 0.507538, 0.861629, 120, 100, 1),
(106318, 0, 1, 1, 2036.27, -455.528, 35.8657, 2.25147, 0, 0, 0.902584, 0.430513, 120, 100, 1),
(106318, 0, 1, 1, -9303.33, -282.874, 71.1022, -2.23402, 0, 0, -0.898794, 0.438372, 120, 100, 1),
(106318, 0, 1, 1, -9796.16, -929.679, 39.1327, -0.401425, 0, 0, -0.199368, 0.979925, 120, 100, 1),
(106318, 0, 1, 1, -10071.6, 631.747, 39.3654, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 0, 1, 1, -9940.88, -116.771, 24.9764, 2.23402, 0, 0, 0.898794, 0.438372, 120, 100, 1),
(106318, 0, 1, 1, -9739.5, -934.509, 38.9182, 1.51844, 0, 0, 0.688356, 0.725373, 120, 100, 1),
(106318, 0, 1, 1, -9828, 86.875, 0.879, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 0, 1, 1, -9216, -1228, 72.3836, 5.891, 0, 0, 0.194838, -0.980835, 120, 100, 1),
(205879, 0, 1, 1, 1598.97, -5280.33, 75.8868, -0.401424, 0, 0, -0.199367, 0.979925, 120, 100, 1),
(205880, 0, 1, 1, 1579.63, -5315.36, 75.8868, -0.750491, 0, 0, -0.366501, 0.930418, 120, 100, 1),
(205881, 0, 1, 1, 1621.18, -5346.45, 75.8869, 1.65806, 0, 0, 0.737277, 0.675591, 120, 100, 1),
(205878, 0, 1, 1, 1643.2, -5301.81, 75.8869, 2.67035, 0, 0, 0.972369, 0.233448, 120, 100, 1),
(2849, 0, 1, 1, -11151, 729.512, 33.619, 2.356, 0, 0, 0.923842, 0.382773, 120, 100, 1),
(106318, 0, 1, 1, 2909.79, 379.327, 31.667, -3, 0, 0, -0.997495, 0.0707372, 120, 100, 1),
(2843, 0, 1, 1, -9039, -304, 74.354, 2.286, 0, 0, 0.909882, 0.414867, 120, 100, 1),
(106318, 0, 1, 1, -5660, 655.705, 383.569, 2.635, 0, 0, 0.968092, 0.250596, 120, 100, 1),
(2843, 0, 1, 1, 1964.25, 1383.72, 64.0972, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 0, 1, 1, -9749, 84.423, 13.209, 2.653, 0, 0, 0.970308, 0.241874, 120, 100, 1),
(106318, 0, 1, 1, -9804.88, -933.027, 39.8566, 0.995, 0, 0, 0.47723, 0.878778, 120, 100, 1),
(106318, 0, 1, 1, -5589, 669.436, 394.492, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(2843, 0, 1, 1, 2017.35, 1853.37, 102.838, -2, 0, 0, -0.841471, 0.540302, 120, 100, 1),
(106318, 0, 1, 1, -5534.88, -1703.65, 342.914, -2, 0, 0, -0.841471, 0.540302, 120, 100, 1),
(106318, 0, 1, 1, -5406.3, -128.7, 368.288, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 0, 1, 1, 2760.54, 790.103, 114.367, 1.955, 0, 0, 0.829102, 0.559097, 120, 100, 1),
(106318, 0, 1, 1, -9051, -625, 53.454, 1.361, 0, 0, 0.629182, 0.777258, 120, 100, 1),
(106318, 0, 1, 1, -9268, -1179, 70.1113, 0.436, 0, 0, 0.216277, 0.976332, 120, 100, 1),
(2843, 0, 1, 1, 1901.25, 1488.57, 93.95, 1.449, 0, 0, 0.662761, 0.748831, 120, 100, 1),
(106318, 0, 1, 1, -5513, -1746, 336.938, 2.059, 0, 0, 0.857041, 0.515247, 120, 100, 1),
(2849, 0, 1, 1, -4836, -3880, 301.562, 3.089, 0, 0, 0.999654, 0.0262933, 120, 100, 1),
(106318, 0, 1, 1, 1806.8, 726.838, 54.2283, 2.356, 0, 0, 0.923842, 0.382773, 120, 100, 1),
(106318, 0, 1, 1, -5586, -1750, 372.8, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 0, 1, 1, -5671, -2124, 400.933, 2.409, 0, 0, 0.93366, 0.35816, 120, 100, 1),
(2843, 0, 1, 1, -5054.1, -266.36, 441.729, 0.6322, 0, 0, 0.310862, 0.950455, 120, 100, 1),
(2843, 0, 1, 1, -6489, 512.694, 387.292, 0.925, 0, 0, 0.446187, 0.89494, 120, 100, 1),
(106318, 0, 1, 1, -9203, -1219, 70.0934, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 0, 1, 1, -9716, -943, 38.412, 3.089, 0, 0, 0.999654, 0.0262933, 120, 100, 1),
(2849, 0, 1, 1, -9504, -1897, 79.263, 0.175, 0, 0, 0.0873884, 0.996174, 120, 100, 1),
(2843, 0, 1, 1, 1965.91, 1617.19, 88.2, 5.648, 0, 0, 0.312281, -0.94999, 120, 100, 1),
(2849, 0, 1, 1, -9471, -1887, 83.315, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(2849, 0, 1, 1, -11398, 1805.32, 6.738, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 0, 1, 1, -5580, 735.881, 392.456, 2.897, 0, 0, 0.992531, 0.121992, 120, 100, 1),
(106318, 0, 1, 1, -5301.79, -98.5944, 400.765, 1.623, 0, 0, 0.725321, 0.688411, 120, 100, 1),
(2843, 0, 1, 1, -9728, 113.06, 24.463, 6.055, 0, 0, 0.113845, -0.993499, 120, 100, 1),
(106318, 0, 1, 1, -8882, -762, 68.411, 3.054, 0, 0, 0.999041, 0.0437824, 120, 100, 1),
(106318, 0, 1, 1, -9442, 468.709, 53.275, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 0, 1, 1, -9914, -1087, 25.253, 1.082, 0, 0, 0.514993, 0.857194, 120, 100, 1),
(2849, 0, 1, 1, -5710, -3918, 344.945, 0.367, 0, 0, 0.182472, 0.983211, 120, 100, 1),
(2849, 1, 1, 1, 1261.72, -3628, 90.402, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 1, 1, 1, -2389, 449.59, 74.992, 1.152, 0, 0, 0.544674, 0.838648, 120, 100, 1),
(106318, 1, 1, 1, -910, -4489, 29.686, -2, 0, 0, -0.841471, 0.540302, 120, 100, 1),
(2849, 1, 1, 1, 7356.2, -800, 8.262, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 1, 1, 1, 936.459, -4764, 23.514, 1.083, 0, 0, 0.515422, 0.856937, 120, 100, 1),
(106318, 1, 1, 1, -825, -44, -13, -2, 0, 0, -0.841471, 0.540302, 120, 100, 1),
(106318, 1, 1, 1, 876.966, -4741.63, 30.0402, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 1, 1, 1, -666, -786, 43.129, 1.431, 0, 0, 0.655995, 0.754765, 120, 100, 1),
(106318, 1, 1, 1, 960.305, -4781, 21.444, 2.025, 0, 0, 0.848159, 0.529742, 120, 100, 1),
(2849, 1, 1, 1, -1915, -1761, 91.668, 1.92, 0, 0, 0.819192, 0.57352, 120, 100, 1),
(106318, 1, 1, 1, 1442.9, -4723, -17, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 1, 1, 1, -1161, 529.876, 28.384, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 1, 1, 1, -157, -5240, -2, -2, 0, 0, -0.841471, 0.540302, 120, 100, 1),
(106318, 1, 1, 1, 717.344, -4469, 15.668, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 1, 1, 1, -2402, 233.932, 49.28, 2.81, 0, 0, 0.986287, 0.165038, 120, 100, 1),
(2843, 1, 1, 1, 8009.84, -887, 1.243, 1.777, 0, 0, 0.776127, 0.630577, 120, 100, 1),
(2849, 1, 1, 1, 7186.58, -748, 76.089, 0, 0, 0, 0, 1, 120, 100, 1),
(2849, 1, 1, 1, 3459.36, 633.122, 9.543, 2.304, 0, 0, 0.913579, 0.406661, 120, 100, 1),
(2849, 1, 1, 1, -2010, -2135, 91.667, 0.314, 0, 0, 0.156356, 0.987701, 120, 100, 1),
(106318, 1, 1, 1, -89, -4047, 64.565, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(2849, 1, 1, 1, -2058, -1966, 91.667, 0.14, 0, 0, 0.0699428, 0.997551, 120, 100, 1),
(106318, 1, 1, 1, -1734.92, 420.683, 97.2078, 0.279252, 0, 0, 0.139173, 0.990268, 120, 100, 1),
(106318, 1, 1, 1, 1106.89, -4706.9, 17.5527, -0.244346, 0, 0, -0.121869, 0.992546, 120, 100, 1),
(106318, 1, 1, 1, -2750.03, -430.934, -2.93079, 2.94959, 0, 0, 0.995395, 0.0958539, 120, 100, 1),
(106318, 1, 1, 1, 852.074, -4187.02, -10.9082, -0.157079, 0, 0, -0.0784588, 0.996917, 120, 100, 1),
(106318, 1, 1, 1, 440.375, -4213.46, 25.2133, -1.74533, 0, 0, -0.766045, 0.642787, 120, 100, 1),
(106318, 1, 1, 1, 51.3314, -4452.3, 48.4894, 0.331611, 0, 0, 0.165047, 0.986286, 120, 100, 1),
(106318, 1, 1, 1, 856.534, -4209.93, -11.351, -0.977383, 0, 0, -0.469471, 0.882948, 120, 100, 1),
(106318, 1, 1, 1, 915.269, -4714.02, 22.9547, -1.27409, 0, 0, -0.594823, 0.803857, 120, 100, 1),
(106318, 1, 1, 1, 35.211, -4301, 69.052, 1.588, 0, 0, 0.713163, 0.700998, 120, 100, 1),
(2849, 1, 1, 1, 7461.66, -861.202, 1.05914, 2.11185, 0, 0, 0.870356, 0.492423, 120, 100, 1),
(2849, 1, 1, 1, 7562.19, -879.454, 17.5976, 2.84488, 0, 0, 0.989015, 0.147813, 120, 100, 1),
(2849, 1, 1, 1, -1921, -2706, 93.0172, 2.007, 0, 0, 0.843357, 0.537354, 120, 100, 1),
(2849, 1, 1, 1, -2095, -2576, 91.757, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 1, 1, 1, -715, 163.091, 43.758, 1.257, 0, 0, 0.587932, 0.80891, 120, 100, 1),
(2849, 1, 1, 1, 7050.3, 426.994, -5, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 1, 1, 1, 9184.01, 1373.37, 1315.07, -3, 0, 0, -0.997495, 0.0707372, 120, 100, 1),
(106318, 1, 1, 1, 9674, 454.641, 1309.96, 1.641, 0, 0, 0.731487, 0.681856, 120, 100, 1),
(2849, 1, 1, 1, 4544.61, 425.187, 33.743, 0.733, 0, 0, 0.35835, 0.933587, 120, 100, 1),
(106318, 1, 1, 1, -1190, -5575, 9.364, 0.175, 0, 0, 0.0873884, 0.996174, 120, 100, 1),
(106318, 1, 1, 1, -546, 71.777, 52.759, 0.803, 0, 0, 0.390799, 0.920476, 120, 100, 1),
(106318, 1, 1, 1, -1922, -692, 2.54, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 1, 1, 1, -1923, -1051, 44.403, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 1, 1, 1, 10889.5, 1968.89, 1321.76, -1, 0, 0, -0.479426, 0.877583, 120, 100, 1),
(106318, 1, 1, 1, 1484.49, -4739, -4, 0.105, 0, 0, 0.0524759, 0.998622, 120, 100, 1),
(106318, 1, 1, 1, 94.593, -4555, 55.006, -2, 0, 0, -0.841471, 0.540302, 120, 100, 1),
(2843, 1, 1, 1, 10995.5, 964.79, 1334.47, 2.925, 0, 0, 0.994142, 0.108085, 120, 100, 1),
(106318, 1, 1, 1, 1067.85, -4672, 13.7875, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 1, 1, 1, -2782, -708, 6.352, 2.688, 0, 0, 0.974392, 0.224857, 120, 100, 1),
(106318, 1, 1, 1, 10419.2, 1909.93, 1321.25, 2.618, 0, 0, 0.965927, 0.258816, 120, 100, 1),
(106318, 1, 1, 1, 421.608, -4252, 26.858, 2.513, 0, 0, 0.951014, 0.309147, 120, 100, 1),
(2843, 1, 1, 1, 10328.6, 1030.53, 1339.13, 2.798, 0, 0, 0.985279, 0.170952, 120, 100, 1),
(106318, 1, 1, 1, 10619.6, 2089.65, 1336.64, -2, 0, 0, -0.841471, 0.540302, 120, 100, 1),
(106318, 1, 1, 1, -174.871, -5115.7, 22.1271, 0.838, 0, 0, 0.406847, 0.913496, 120, 100, 1),
(106318, 1, 1, 1, 19.877, -4274, 72.578, 1.588, 0, 0, 0.713163, 0.700998, 120, 100, 1),
(106318, 1, 1, 1, 817.75, -4807, 11.162, 0.733, 0, 0, 0.35835, 0.933587, 120, 100, 1),
(106318, 1, 1, 1, 10085.3, 1155.55, 1318.6, 1.466, 0, 0, 0.669102, 0.74317, 120, 100, 1),
(2849, 1, 1, 1, 7389.17, -1117, 41.935, 0.541, 0, 0, 0.267213, 0.963637, 120, 100, 1),
(106318, 1, 1, 1, 10875.1, 2073.58, 1328.34, 0, 0, 0, 0, 1, 120, 100, 1),
(106318, 1, 1, 1, 116.43, -4558, 59.8, -3, 0, 0, -0.997495, 0.0707372, 120, 100, 1),
(2849, 1, 1, 1, 4547.23, 154.427, 59.672, 1.815, 0, 0, 0.787967, 0.615718, 120, 100, 1),
(75293, 36, 1, 1, -312.046, -477.501, 49.5979, -1.55334, 0, 0, 0.700909, -0.71325, 120, 100, 1),
(75293, 36, 1, 1, -77.7409, -788.596, 26.1097, 1.16937, 0, 0, 0.551937, 0.833886, 120, 100, 1),
(75293, 36, 1, 1, -209.206, -602.72, 19.3065, -0.139626, 0, 0, 0.069756, -0.997564, 120, 100, 1),
(75293, 36, 1, 1, -63.0889, -797.013, 39.0067, 1.55334, 0, 0, 0.700909, 0.71325, 120, 100, 1),
(75293, 36, 1, 1, -300.887, -532.542, 49.4236, 0.226893, 0, 0, 0.113203, 0.993572, 120, 100, 1),
(75293, 43, 1, 1, -49.9295, 370.574, -59.6856, 0.575959, 0, 0, 0.284015, 0.95882, 120, 100, 1),
(75293, 43, 1, 1, -79.462, -32.6, -59.1092, -0.296706, 0, 0, 0.147809, -0.989016, 120, 100, 1),
(75293, 43, 1, 1, -95.0718, -311.132, -61.8035, 2.32129, 0, 0, 0.91706, 0.398749, 120, 100, 1),
(75293, 43, 1, 1, -10.4679, -272.442, -66.1606, 0.715585, 0, 0, 0.350207, 0.936672, 120, 100, 1),
(2849, 530, 1, 1, -1318.83, -11245.7, 0.202506, 1.18682, 0, 0, 0.559193, 0.829038, 120, 100, 1),
(75293, 530, 1, 1, 6272.09, -6348.59, 79.1625, 0.401426, 0, 0, 0.199368, 0.979925, 120, 100, 1),
(2843, 530, 1, 1, 8249.34, -6885.52, 87.3604, 5.15803, 0, 0, 0.533368, -0.845884, 120, 100, 1),
(2843, 530, 1, 1, 8086.65, -6748.09, 64.5604, 5.50596, 0, 0, 0.378903, -0.925436, 120, 100, 1),
(2843, 530, 1, 1, 8453.67, -6996.44, 93.1697, 2.0777, 0, 0, 0.861822, 0.507211, 120, 100, 1),
(2843, 530, 1, 1, 8815.11, -6988.26, 33.6424, 3.25815, 0, 0, 0.998302, -0.058248, 120, 100, 1),
(2843, 530, 1, 1, 7823.81, -6640.25, 27.4591, 0.393303, 0, 0, 0.195387, 0.980726, 120, 100, 1),
(2843, 530, 1, 1, 7232.46, -6414.72, 56.1665, 3.2655, 0, 0, 0.998081, -0.0619165, 120, 100, 1),
(2843, 530, 1, 1, 7157.67, -6612.69, 60.6594, 5.86517, 0, 0, 0.207487, -0.978238, 120, 100, 1),
(2843, 530, 1, 1, 6301.62, -6475.85, 83.0104, 1.67507, 0, 0, 0.742996, 0.669296, 120, 100, 1);

DELETE FROM  creature_questrelation WHERE id=31146;
DELETE FROM  creature_questrelation WHERE id=31146;
DELETE FROM creature_addon WHERE guid=24934;
DELETE FROM creature_addon WHERE guid=25004;
DELETE FROM creature_addon WHERE guid=25030;
DELETE FROM creature_addon WHERE guid=25057;
DELETE FROM creature_addon WHERE guid=25063;
DELETE FROM creature_addon WHERE guid=25158;
DELETE FROM creature_addon WHERE guid=25223;
DELETE FROM creature_addon WHERE guid=25384;
DELETE FROM creature_addon WHERE guid=25442;
DELETE FROM creature_addon WHERE guid=25494;
DELETE FROM creature_addon WHERE guid=25597;
DELETE FROM creature_addon WHERE guid=25652;
DELETE FROM creature_addon WHERE guid=25654;
DELETE FROM creature_addon WHERE guid=25680;
DELETE FROM creature_addon WHERE guid=25818;
DELETE FROM creature_addon WHERE guid=25960;
DELETE FROM creature_addon WHERE guid=26089;
DELETE FROM creature_addon WHERE guid=26097;
DELETE FROM creature_addon WHERE guid=63957;
DELETE FROM smart_scripts WHERE event_param1=115757;
DELETE FROM smart_scripts WHERE event_param1=100787;

DELETE FROM creature WHERE guid=65055;

UPDATE `creature_template` SET `npcflag` = '8' WHERE `entry` IN (44821,44894);

UPDATE `creature_template` SET `npcflag` = '2' WHERE `entry` =45195;

UPDATE `creature_template` SET `faction_A` = '190' WHERE `entry` =49424;

UPDATE `creature_template` SET `npcflag` = '0' WHERE `entry` =44894;

DELETE FROM `creature_questrelation` WHERE `quest` = 31146;

UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44608';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44609';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44610';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44615';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44365';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44789';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44790';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44825';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '45491';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44784';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '44778';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '45490';
UPDATE `creature` SET `phaseMask`=1 WHERE  `id` = '45489';

delete from creature where id = '44733';
delete from creature where id = '44732';
delete from creature where id = '44737';
delete from creature where id = '46560';

DELETE FROM `waypoints` WHERE `entry` = '4476400';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(4476400, 1, 1444.46, 676.08, 47.12, 'Hauler Waypoints'), 
(4476400, 2, 1410.31, 742.94, 47.12, 'Hauler Waypoints'),
(4476400, 3, 1368.53, 840.10, 49.81, 'Hauler Waypoints'),
(4476400, 4, 1336.03, 952.38, 54.59, 'Hauler Waypoints'),
(4476400, 5, 1315.77, 1027.68, 54.59, 'Hauler Waypoints'),
(4476400, 6, 1261.31, 1099.18, 51.45, 'Hauler Waypoints'),
(4476400, 7, 1176.29, 1165.50, 48.82, 'Hauler Waypoints'),
(4476400, 8, 996.30, 1301.44, 45.85, 'Hauler Waypoints'),
(4476400, 9, 918.45, 1348.38, 48.00, 'Hauler Waypoints'),
(4476400, 10, 864.30, 1360.91, 54.71, 'Hauler Waypoints'),
(4476400, 11, 774.28, 1362.27, 64.72, 'Hauler Waypoints'),
(4476400, 12, 730.66, 1356.92, 71.95, 'Hauler Waypoints'),
(4476400, 13, 659.56, 1305.40, 83.10, 'Hauler Waypoints'),
(4476400, 14, 609.78, 1280.22, 87.27, 'Hauler Waypoints'),
(4476400, 15, 572.68, 1248.71, 86.55, 'Hauler Waypoints'),
(4476400, 16, 534.36, 1229.41, 88.41, 'Hauler Waypoints'),
(4476400, 17, 476.46, 1228.23, 88.49, 'Hauler Waypoints'),
(4476400, 18, 349.65, 1240.31, 81.28, 'Hauler Waypoints'),
(4476400, 19, 266.10, 1270.77, 76.70, 'Hauler Waypoints'),
(4476400, 20, 179.32, 1256.14, 71.87, 'Hauler Waypoints'),
(4476400, 21, -8.96, 1198.67, 64.55, 'Hauler Waypoints');

DELETE FROM `waypoints` WHERE `entry` = '4476401';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(4476401, 21, 1444.46, 676.08, 47.12, 'Hauler Waypoints'), 
(4476401, 20, 1410.31, 742.94, 47.12, 'Hauler Waypoints'),
(4476401, 19, 1368.53, 840.10, 49.81, 'Hauler Waypoints'),
(4476401, 18, 1336.03, 952.38, 54.59, 'Hauler Waypoints'),
(4476401, 17, 1315.77, 1027.68, 54.59, 'Hauler Waypoints'),
(4476401, 16, 1261.31, 1099.18, 51.45, 'Hauler Waypoints'),
(4476401, 15, 1176.29, 1165.50, 48.82, 'Hauler Waypoints'),
(4476401, 14, 996.30, 1301.44, 45.85, 'Hauler Waypoints'),
(4476401, 13, 918.45, 1348.38, 48.00, 'Hauler Waypoints'),
(4476401, 12, 864.30, 1360.91, 54.71, 'Hauler Waypoints'),
(4476401, 11, 774.28, 1362.27, 64.72, 'Hauler Waypoints'),
(4476401, 10, 730.66, 1356.92, 71.95, 'Hauler Waypoints'),
(4476401, 9, 659.56, 1305.40, 83.10, 'Hauler Waypoints'),
(4476401, 8, 609.78, 1280.22, 87.27, 'Hauler Waypoints'),
(4476401, 7, 572.68, 1248.71, 86.55, 'Hauler Waypoints'),
(4476401, 6, 534.36, 1229.41, 88.41, 'Hauler Waypoints'),
(4476401, 5, 476.46, 1228.23, 88.49, 'Hauler Waypoints'),
(4476401, 4, 349.65, 1240.31, 81.28, 'Hauler Waypoints'),
(4476401, 3, 266.10, 1270.77, 76.70, 'Hauler Waypoints'),
(4476401, 2, 179.32, 1256.14, 71.87, 'Hauler Waypoints'),
(4476401, 1, -8.96, 1198.67, 64.55, 'Hauler Waypoints');

-- Horde Hauler
SET @ENTRY := 44731;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,53,0,4476400,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,21,0,0,0,53,0,4476401,1,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Reverse WP");

-- Horde Coffin Hauler
SET @ENTRY := 44764;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,53,0,4476400,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,21,0,0,0,53,0,4476401,1,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Reverse WP");

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN('44731','44764');
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(44731, 44733, 3, 1, 'Horde Hauler', 6, 30000),
(44731, 44733, 0, 1, 'Horde Hauler', 6, 30000),
(44731, 44733, 4, 1, 'Horde Hauler', 6, 30000),
(44731, 44733, 5, 1, 'Horde Hauler', 6, 30000),
(44764, 46560, 1, 1, 'Horde Coffin Hauler', 6, 30000),
(44764, 44766, 2, 1, 'Horde Coffin Hauler', 6, 30000),
(44731, 44732, 2, 1, 'Horde Hauler', 6, 30000),
(44731, 46560, 1, 1, 'Horde Hauler', 6, 30000);

UPDATE `quest_template` SET `MaxLevel`=0 WHERE  `Id`=26964;
UPDATE creature_template SET `npcflag` = '1' WHERE `entry` = '44894';
UPDATE `creature_template` SET `InhabitType`=3 WHERE  `entry`=44882;
update creature_template set modelid1 = '999' where name = 'invisible trigger one';
update creature_template set modelid2 = '999' where name = 'invisible trigger one';
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE  `entry`=45496;
UPDATE `creature` SET `position_z`=9.4088 WHERE  `guid`=196841;
UPDATE `creature_template` SET `InhabitType`=3 WHERE  `entry`=44951;

-- Hillsbrad Refugee
SET @ENTRY := 44954;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,3000,14000,16000,11,87104,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Might of Lordaeron"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,12,44593,8,60000,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Summon Fallen Human"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn");

-- Hillsbrad Refugee
SET @ENTRY := 44966;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,3000,14000,16000,11,87104,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Might of Lordaeron"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,12,44593,8,60000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Summon Fallen Human"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn");

-- Agatha
SET @ENTRY := 44951;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,75,85451,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Add Death Walk to self"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,2000,2000,0,0,11,83173,0,0,0,0,0,11,44593,10,0,0.0,0.0,0.0,0.0,"Raise Forsaken from Fallen Humans"),
(@ENTRY,@SOURCETYPE,3,0,31,0,100,0,83173,1,0,0,33,44953,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Run"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Passive"),
(@ENTRY,@SOURCETYPE,6,0,0,0,50,0,1500,1500,1500,1500,11,84012,0,0,0,0,0,11,44987,2,0,0.0,0.0,0.0,0.0,"Cast Doomhowl"),
(@ENTRY,@SOURCETYPE,7,0,0,0,25,0,5000,5000,5000,5000,11,84013,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Cast Unholy Darkness"),
(@ENTRY,@SOURCETYPE,8,0,0,0,50,0,1500,1500,1500,1500,11,84014,0,0,0,0,0,11,44987,2,0,0.0,0.0,0.0,0.0,"Cast Unholy Smite"),
(@ENTRY,@SOURCETYPE,9,0,32,0,100,0,1,15,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Aggressive"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,0,10000,10000,40000,40000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 0"),
(@ENTRY,@SOURCETYPE,11,0,31,0,100,0,83173,1,1500,1500,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 1"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,1,0,0,80,4495100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 Call Actionlist"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,1,2,44951,0,0,12,44989,8,120000,0,0,0,8,0,0,0,992.64,692.38,74.89,6.09,"Summon Crowley on Text 2"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,2,0,0,80,4495101,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 2 Call Actionlist");

UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=44640;
UPDATE `quest_template` SET `SourceSpellId`=83982 WHERE  `Id`=27099;
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=45003;
UPDATE `creature_template` SET `VehicleId`=1055, `AIName`='', `MovementType`=212 WHERE  `entry`=45003;
UPDATE `creature_template` SET `unit_flags`=33554440 WHERE  `entry`=45003;

-- Agatha
SET @ENTRY := 4495100;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,86,83788,0,23,0,0,0,11,45003,25,0,0.0,0.0,0.0,0.0,"Set player in camera on Data init"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 2");

-- Agatha
SET @ENTRY := 4495101;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,28,83788,0,0,0,0,0,11,45003,20,0,0.0,0.0,0.0,0.0,"Remove camera"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,0,0,1,3,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Run..."),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,2000,2000,0,0,1,4,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"RUN!"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,500,500,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Grab Owner"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,0,0,0,0,33,44951,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Quest Complete (To all players in range)"),
(@ENTRY,@SOURCETYPE,6,0,27,0,100,0,0,0,0,0,53,1,44951,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start WP"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,0,0,0,0,18,1048576,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Pacified"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Passive"),
(@ENTRY,@SOURCETYPE,9,0,60,0,100,0,115000,115000,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop");

-- Fenris Keep Stalker
SET @ENTRY := 45032;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,1000,1000,45,0,1,0,0,0,0,11,44951,2,0,0.0,0.0,0.0,0.0,"Set data 1 to Agatha");

DELETE FROM `creature_text` WHERE `entry`=44989;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(44989,0,0,'The Forsaken have broken through your defenses, magistrate.',12,0,100,0,0,0,'Comment'),
(44989,1,0,'You are out of time.',12,0,100,0,0,0,'Comment'),
(44989,2,0,'A decision must be made.',12,0,100,0,0,0,'Comment'),
(44989,3,0,'Die in battle and be raised as a servant of the Forsaken or...',12,0,100,0,0,0,'Comment'),
(44989,4,0,'Drink my blood and be reborn as worgen, immune to the depravity of the Forsaken.',12,0,100,0,0,0,'Comment'),
(44989,5,0,'Help us destroy the Forsaken and retake Lordaeron for the Alliance!',12,0,100,0,0,0,'Comment');

-- Lord Darius Crowley
SET @ENTRY := 44989;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start talk on summon"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,44989,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,44989,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,2,44989,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 3"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,3,44989,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 4"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,4,44989,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 5"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,5,44989,0,0,1,0,6000,0,0,0,0,11,44996,25,0,0.0,0.0,0.0,0.0,"Talk 6"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,44996,0,0,1,1,6000,0,0,0,0,11,44996,25,0,0.0,0.0,0.0,0.0,"Talk 7"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,1,44996,0,0,86,84097,0,11,44996,50,0,11,44996,50,0,0.0,0.0,0.0,0.0,"On Talk 7 - Cast Worgen"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,1,44996,0,0,86,84096,0,11,44995,50,0,11,44995,50,0,0.0,0.0,0.0,0.0,"On Talk 7 - Cast Worgen"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,1,44996,0,0,86,84094,0,11,44993,50,0,11,44993,50,0,0.0,0.0,0.0,0.0,"On Talk 7 - Cast Worgen"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,1,44996,0,0,86,84095,0,11,44994,50,0,11,44994,50,0,0.0,0.0,0.0,0.0,"On Talk 7 - Cast Worgen"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,1,44996,0,0,86,84099,0,11,45002,50,0,11,45002,50,0,0.0,0.0,0.0,0.0,"On Talk 7 - Cast Worgen"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,1,44996,0,0,86,84098,0,11,44997,50,0,11,44997,50,0,0.0,0.0,0.0,0.0,"On Talk 7 - Cast Worgen"),
(@ENTRY,@SOURCETYPE,14,0,54,0,100,0,0,0,0,0,41,80000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn");

DELETE FROM `waypoints` WHERE `entry` = '44951';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(44951, 1, 977.73, 706.36, 74.89, 'Agatha Return'),
(44951, 2, 996.52, 707.52, 69.79, 'Agatha Return'),
(44951, 3, 998.33, 683.80, 69.79, 'Agatha Return'),
(44951, 4, 1012.49, 683.44, 64.90, 'Agatha Return'),
(44951, 5, 1012.25, 694.72, 60.97, 'Agatha Return'),
(44951, 6, 997.69, 693.71, 60.97, 'Agatha Return'),
(44951, 7, 995.18, 710.49, 60.97, 'Agatha Return'),
(44951, 8, 983.91, 710.84, 60.97, 'Agatha Return'),
(44951, 9, 983.35, 690.65, 59.47, 'Agatha Return'),
(44951, 10, 938.72, 690.44, 59.28, 'Agatha Return'),
(44951, 11, 954.44, 722.80, 59.28, 'Agatha Return'),
(44951, 12, 978.95, 728.36, 59.35, 'Agatha Return'),
(44951, 13, 1001.50, 724.47, 59.96, 'Agatha Return'),
(44951, 14, 1026.39, 725.62, 59.14, 'Agatha Return'),
(44951, 15, 1046.84, 724.53, 52.82, 'Agatha Return'),
(44951, 16, 1070.61, 738.71, 56.43, 'Agatha Return'),
(44951, 17, 1303.52, 931.34, 79.35, 'Agatha Return'),
(44951, 18, 1381.17, 1046.03, 53.94, 'Agatha Return');

UPDATE `creature_template` SET `mindmg`=45, `maxdmg`=95 WHERE  `entry`=44951;

DELETE FROM `creature` WHERE `id` = '45032';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (45032, 0, 1, 32768, 0, 0, 979.168, 677.551, 74.8994, 1.59512, 120, 0, 0, 42, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '45003';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (45003, 0, 1, 32768, 0, 0, 982.818, 690.533, 80.7845, 1.57, 120, 0, 0, 42, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '44990';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (44990, 0, 1, 32768, 0, 0, 993.221, 686.624, 74.8984, 0.27213, 120, 0, 0, 840, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '45002';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (45002, 0, 1, 32768, 0, 0, 1003.66, 688.896, 76.1921, 3.12909, 120, 0, 0, 85239, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '44994';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (44994, 0, 1, 32768, 0, 1, 1002.34, 687.092, 76.1922, 3.16443, 120, 0, 0, 46, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '44996';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (44996, 0, 1, 32768, 0, 1, 1001.12, 690.02, 76.1922, 3.17909, 120, 0, 0, 840, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '44993';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (44993, 0, 1, 32768, 0, 1, 1003.67, 691.852, 76.1922, 3.16396, 120, 0, 0, 48, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '44995';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (44995, 0, 1, 32768, 0, 1, 1002.9, 685.29, 76.1922, 2.84896, 120, 0, 0, 44, 0, 0, 0, 0, 0);
DELETE FROM `creature` WHERE `id` = '44997';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (44997, 0, 1, 32768, 0, 1, 1003.12, 694.955, 76.1922, 3.41749, 120, 0, 0, 46, 0, 0, 0, 0, 0);

UPDATE `quest_template` SET `SourceSpellId`=84128 WHERE  `Id`=27098;
UPDATE `creature_template` SET `VehicleId`=1077 WHERE  `entry`=45057;
UPDATE `creature_template` SET `VehicleId`=1076 WHERE  `entry`=45041;

DELETE FROM `waypoints` WHERE `entry` = '45041';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(45041, 1, 1341.96, 1011.48, 54.59, 'Sylvanas (Lordaeron Event)'),
(45041, 2, 1315.56, 1020.83, 54.59, 'Sylvanas (Lordaeron Event)'),
(45041, 3, 1268.48, 1086.55, 52.33, 'Sylvanas (Lordaeron Event)'),
(45041, 4, 1226.24, 1124.89, 50.47, 'Sylvanas (Lordaeron Event)'),
(45041, 5, 1142.65, 1183.89, 47.89, 'Sylvanas (Lordaeron Event)'),
(45041, 6, 1105.21, 1205.00, 46.40, 'Sylvanas (Lordaeron Event)'),
(45041, 7, 1040.83, 1269.22, 46.03, 'Sylvanas (Lordaeron Event)'),
(45041, 8, 954.33, 1320.40, 46.54, 'Sylvanas (Lordaeron Event)'),
(45041, 9, 904.19, 1348.97, 48.92, 'Sylvanas (Lordaeron Event)'),
(45041, 10, 865.52, 1358.90, 54.70, 'Sylvanas (Lordaeron Event)'),
(45041, 11, 773.64, 1359.87, 65.12, 'Sylvanas (Lordaeron Event)'),
(45041, 12, 733.14, 1353.96, 71.88, 'Sylvanas (Lordaeron Event)'),
(45041, 13, 670.48, 1306.19, 81.39, 'Sylvanas (Lordaeron Event)'),
(45041, 14, 641.97, 1294.35, 85.60, 'Sylvanas (Lordaeron Event)'),
(45041, 15, 607.69, 1355.34, 87.32, 'Sylvanas (Lordaeron Event)'),
(45041, 16, 579.67, 1416.12, 96.24, 'Sylvanas (Lordaeron Event)'),
(45041, 17, 550.03, 1454.93, 106.07, 'Sylvanas (Lordaeron Event)'),
(45041, 18, 506.98, 1495.19, 124.92, 'Sylvanas (Lordaeron Event)'),
(45041, 19, 497.14, 1531.72, 129.62, 'Sylvanas (Lordaeron Event)'),
(45041, 20, 497.45, 1562.66, 127.63, 'Sylvanas (Lordaeron Event)');

DELETE FROM `waypoints` WHERE `entry` = '45057';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(45057, 1, 1326.03, 1014.21, 54.59, 'Sylvanas (Lordaeron Event)'),
(45057, 2, 1299.57, 1063.55, 54.24, 'Sylvanas (Lordaeron Event)'),
(45057, 3, 1246.14, 1123.01, 50.48, 'Sylvanas (Lordaeron Event)'),
(45057, 4, 1147.52, 1192.92, 47.93, 'Sylvanas (Lordaeron Event)'),
(45057, 5, 1090.83, 1230.29, 46.30, 'Sylvanas (Lordaeron Event)'),
(45057, 6, 1044.43, 1277.15, 46.03, 'Sylvanas (Lordaeron Event)'),
(45057, 7, 918.90, 1353.01, 48.07, 'Sylvanas (Lordaeron Event)'),
(45057, 8, 866.91, 1362.60, 54.37, 'Sylvanas (Lordaeron Event)'),
(45057, 9, 780.10, 1365.81, 63.59, 'Sylvanas (Lordaeron Event)'),
(45057, 10, 737.31, 1363.36, 71.06, 'Sylvanas (Lordaeron Event)'),
(45057, 11, 704.86, 1345.78, 76.35, 'Sylvanas (Lordaeron Event)'),
(45057, 12, 665.92, 1313.16, 81.79, 'Sylvanas (Lordaeron Event)'),
(45057, 13, 644.02, 1303.32, 85.06, 'Sylvanas (Lordaeron Event)'),
(45057, 14, 616.48, 1349.65, 86.25, 'Sylvanas (Lordaeron Event)'),
(45057, 15, 584.40, 1419.63, 96.37, 'Sylvanas (Lordaeron Event)'),
(45057, 16, 536.69, 1475.85, 113.83, 'Sylvanas (Lordaeron Event)'),
(45057, 17, 510.08, 1498.48, 124.62, 'Sylvanas (Lordaeron Event)'),
(45057, 18, 502.31, 1525.38, 128.80, 'Sylvanas (Lordaeron Event)'),
(45057, 19, 500.94, 1549.35, 129.21, 'Sylvanas (Lordaeron Event)'),
(45057, 20, 500.67, 1563.95, 128.31, 'Sylvanas (Lordaeron Event)');

-- Lady Sylvanas Windrunner
SET @ENTRY := 45051;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,45057,5,0,0.0,0.0,0.0,0.0,"Ride Sylvanas Warhorse"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,1500,1500,1500,1500,11,84182,4,0,0,0,0,11,44793,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,1500,1500,1500,11,84182,4,0,0,0,0,11,1778,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike on Bear"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,1500,1500,1500,1500,11,84182,4,0,0,0,0,11,1766,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike on Wolf"),
(@ENTRY,@SOURCETYPE,4,0,60,0,100,0,2000,2000,2000,2000,5,66,0,0,0,0,0,11,44911,12,0,0.0,0.0,0.0,0.0,"Salute Sylvanas"),
(@ENTRY,@SOURCETYPE,5,0,60,0,100,0,1500,1500,1500,1500,11,0,0,0,0,0,0,11,1797,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike on Bear 2");

DELETE FROM `creature_text` WHERE `entry`=45051;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(45051,0,0,'I have not always been the Bansheee Queen.',12,0,100,0,0,20470,'Comment'),
(45051,1,0,'And my people have not always been the Forsaken.',12,0,100,0,0,20471,'Comment'),
(45051,2,0,'Long ago this land comprised the northern kingdoms of Lordaeron, ruled by King Terenas Menethil.',12,0,100,0,0,20472,'Comment'),
(45051,3,0,'Terenas had a son named Arthas.',12,0,100,0,0,20473,'Comment'),
(45051,4,0,'Arthas... even saying his name makes my body quiver in rage.',12,0,100,0,0,20474,'Comment'),
(45051,5,0,'This man-child, Arthas, took for himself a cursed blade known as Frostmourne.',12,0,100,0,0,20475,'Comment'),
(45051,6,0,'Through Frostmourne, Arthas killed his own father and razed this land along with every living creature in it!',12,0,100,0,0,20476,'Comment'),
(45051,7,0,'My own death came at the hands of Arthas when he and his armies sacked my homeland, Quel Thalas, and murdered my people. ',12,0,100,0,0,20477,'Comment'),
(45051,8,0,'In his vast cruelty, Arthas severed my spirit from my body and raised me as a banshee to serve in his Scourge army.',12,0,100,0,0,20478,'Comment'),
(45051,9,0,'A similar fate befell all that would die to the Scourge war machine.',12,0,100,0,0,20479,'Comment'),
(45051,10,0,'In death, they were reborn as mindless undead.',12,0,100,0,0,20480,'Comment'),
(45051,11,0,'But Arthas was not invincible! With each passing day his power wanted - his grip over the will of the damned loosening.',12,0,100,0,0,20481,'Comment'),
(45051,12,0,'It was when Arthas was at his weakest that I struck!',12,0,100,0,0,20482,'Comment'),
(45051,13,0,'And though the hour of his atonement had come, the worm managed to escape his fate, returning to the frozen wastes of Northrend.',12,0,100,0,0,20483,'Comment'),
(45051,14,0,'With Arthas gone, so too was the control he held over the undead masses of Lordaeron. After recovering my body, I freed the remaining Scourge that were left behind.',12,0,100,0,0,20484,'Comment'),
(45051,15,0,'From the cruelty and mercilessness of Arthas, the man who would be the Lich King, the Forsaken were born.',12,0,100,0,0,20485,'Comment'),
(45051,16,0,'Our goal... Our sole purpose was to destroy the Lich King. We threw our lot in with the Horde and began our journey towards redemption.',12,0,100,0,0,20486,'Comment'),
(45051,17,0,'Now the Lich King is dead and we have returned.',12,0,100,0,0,20487,'Comment'),
(45051,18,0,'The people who called this land their home in life, do so in death as well.',12,0,100,0,0,20488,'Comment'),
(45051,19,0,'But the Alliance does not recognize our rights. They claim this land as their own while attempting to invalidate the claims of the founders of this kingdom.',12,0,100,0,0,20489,'Comment'),
(45051,20,0,'I will never allow it... Never!',12,0,100,0,0,20490,'Comment'),
(45051,21,0,'Lordaeron belongs to the Forsaken - always and forever.',12,0,100,0,0,20491,'Comment');

-- Forsaken Warhorse
SET @ENTRY := 45057;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,2000,2000,0,0,53,1,45057,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,18,1048576,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Taxi"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,1,0,8000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45051,0,0,1,1,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,45051,0,0,1,2,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45051,0,0,1,3,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45051,0,0,1,4,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,45051,0,0,1,5,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 5"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,5,45051,0,0,1,6,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 6"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,6,45051,0,0,1,7,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 7"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,7,45051,0,0,1,8,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 8"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,8,45051,0,0,1,9,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 9"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,9,45051,0,0,1,10,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 10"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,10,45051,0,0,1,11,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 11"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,11,45051,0,0,1,12,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 12"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,12,45051,0,0,1,13,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 13"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,13,45051,0,0,1,14,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 14"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,14,45051,0,0,1,15,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 15"),
(@ENTRY,@SOURCETYPE,18,0,52,0,100,0,15,45051,0,0,1,16,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 16"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,16,45051,0,0,1,17,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 17"),
(@ENTRY,@SOURCETYPE,20,0,52,0,100,0,17,45051,0,0,1,18,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 18"),
(@ENTRY,@SOURCETYPE,21,0,52,0,100,0,18,45051,0,0,1,19,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 19"),
(@ENTRY,@SOURCETYPE,22,0,52,0,100,0,19,45051,0,0,1,20,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 20"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,20,0,0,0,41,3000,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Dismount on WP End"),
(@ENTRY,@SOURCETYPE,24,0,58,0,100,0,0,0,0,0,33,45051,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Completed"),
(@ENTRY,@SOURCETYPE,25,0,52,0,100,0,20,45051,0,0,1,21,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk - 21"),
(@ENTRY,@SOURCETYPE,26,0,40,0,100,0,14,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 14 - Set Walk");

-- Forsaken Warhorse
SET @ENTRY := 45041;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Ride Forsaken Warhorse (Player)"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,45041,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,39,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,0,0,0,0,28,46598,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Dismount on WP Completed"),
(@ENTRY,@SOURCETYPE,4,0,27,0,100,0,0,0,0,0,52,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Taxi"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,17,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 17 Set Walk");

UPDATE `creature_template` SET `Health_mod`=100 WHERE  `entry`=45041;
UPDATE `creature_template` SET `flags_extra`=2 WHERE  `entry`=45041;
UPDATE `creature_template` SET `npcflag`=1 WHERE  `entry`=45197;
UPDATE `creature_template` SET `flags_extra`=0 WHERE  `entry`=45195;
UPDATE `creature_template` SET `ScriptName`='npc_veteran_forsaken_trooper' WHERE  `entry`=45197;
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=45197;

SET @CGUID := 786927;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+15;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(@CGUID+0, 1035372, 144954, 0, 1, 2, 0, 0, 711.086, 950.093, 34.7558, 5.37947, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+1, 44916, 0, 1, 1, 0, 1, 491.738, 1527.97, 130.617, 5.83066, 300, 0, 0, 1640, 0, 0, 0, 0, 0),
(@CGUID+2, 44917, 0, 1, 1, 0, 0, 493.135, 1530.63, 130.156, 5.79924, 300, 0, 0, 1500, 0, 0, 0, 0, 0),
(@CGUID+3, 45032, 0, 1, 32768, 0, 0, 979.168, 677.551, 74.8994, 1.59512, 120, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+4, 45003, 0, 1, 32768, 0, 0, 982.818, 690.533, 80.7845, 1.57, 120, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+5, 44990, 0, 1, 32768, 0, 0, 993.221, 686.624, 74.8984, 0.27213, 120, 0, 0, 840, 0, 0, 0, 0, 0),
(@CGUID+6, 45002, 0, 1, 32768, 0, 0, 1003.66, 688.896, 76.1921, 3.12909, 120, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+7, 44994, 0, 1, 32768, 0, 1, 1002.34, 687.092, 76.1922, 3.16443, 120, 0, 0, 46, 0, 0, 0, 0, 0),
(@CGUID+8, 44996, 0, 1, 32768, 0, 1, 1001.12, 690.02, 76.1922, 3.17909, 120, 0, 0, 840, 0, 0, 0, 0, 0),
(@CGUID+9, 44993, 0, 1, 32768, 0, 1, 1003.67, 691.852, 76.1922, 3.16396, 120, 0, 0, 48, 0, 0, 0, 0, 0),
(@CGUID+10, 44995, 0, 1, 32768, 0, 1, 1002.9, 685.29, 76.1922, 2.84896, 120, 0, 0, 44, 0, 0, 0, 0, 0),
(@CGUID+11, 44997, 0, 1, 32768, 0, 1, 1003.12, 694.955, 76.1922, 3.41749, 120, 0, 0, 46, 0, 0, 0, 0, 0),
(@CGUID+12, 44894, 0, 1, 1, 0, 1, 1315.02, 1211.67, 58.5026, 4.60558, 300, 0, 0, 120, 0, 0, 0, 0, 0),
(@CGUID+13, 44893, 0, 1, 1, 34165, 0, 1315.06, 1211.81, 58.5562, 62.2251, 500, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+14, 44731, 0, 1, 1, 0, 0, 1465.98, 649.399, 46.9216, 2.42223, 300, 0, 0, 484, 0, 0, 0, 0, 0),
(@CGUID+15, 44764, 0, 1, 1, 0, 0, 1454.09, 664.532, 46.9778, 2.20623, 300, 0, 0, 484, 0, 0, 0, 0, 0);
