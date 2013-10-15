UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=13892;
UPDATE `creature_template` SET `dynamicflags`=2 WHERE `entry`=34413;

DELETE FROM `creature_text` WHERE `entry` IN (34405, 34406, 34326, 34427, 34326);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34405,0,0,'%s attempts to run away in fear!',16,0,100,0,0,0,'combat Flee'),
(34405,1,0,'Why are we digging this thing up anyway, boss?',12,0,100,0,0,0,'Comment'),
(34406,0,0,'Watch your tongue, worm. You will not refer to Soggoth the Slitherer as "that thing" or you\'ll find yourself eating your own heart for dinner.',12,0,100,0,0,0,'Comment'),
(34406,1,0,'Now, back to work! Your superiors are watching from the outlook above and they do not take kindly to idleness!',12,0,100,0,0,0,'Comment'),
(34427,0,0,'Not quite. We shall need a great many offerings of sacrifice before the Herald of the Old Gods roams the land again.',12,0,100,0,0,0,'Comment'),
(34326,0,0,'Our men are almost finished unearthing great Soggoth. Is the ritual ready?',12,0,100,0,0,0,'Comment'),
(34326,1,0,'Do not worry. Like I said, our men are almost done unearthing the Slithering One. They will make for a suitable -- and even voluntary -- sacrifice. Soggoth will rise!',12,0,100,0,0,0,'Comment');

-- Foreman Balsoth
SET @ENTRY := 34406;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,10000,10000,40000,40000,45,0,1,0,0,0,0,10,189348,34405,0,0.0,0.0,0.0,0.0,"OOC LOS - Set Data 1 to Twilight Worker"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,3,52,0,100,0,0,34406,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,33,34410,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

-- Twilight Worker
SET @ENTRY := 34405;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,36645,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw Rock on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,3000,17000,21000,11,75059,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shatter Armor"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,34405,0,0,45,0,1,0,0,0,0,10,189352,34406,0,0.0,0.0,0.0,0.0,"Set Data 1 to Boss");

-- Doomspeaker Trevellion
SET @ENTRY := 34326;
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
(@ENTRY,@SOURCETYPE,10,0,0,1,100,0,2000,4500,34000,35000,11,14868,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Curse of Agony"),
(@ENTRY,@SOURCETYPE,11,0,0,1,100,0,9000,11000,25000,29500,11,32063,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Corruption"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,0,30000,30000,30000,30000,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,0,34326,0,0,45,0,1,0,0,0,0,10,189372,34427,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Thalya"),
(@ENTRY,@SOURCETYPE,14,15,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,15,0,61,0,100,0,0,0,0,0,33,34411,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

-- Thalya the Voidcaller
SET @ENTRY := 34427;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,3000,5000,0,0,11,12746,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Summon Voidwalker on Spawn"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,34427,0,0,45,0,1,0,0,0,0,10,189143,34326,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Doomcaller");