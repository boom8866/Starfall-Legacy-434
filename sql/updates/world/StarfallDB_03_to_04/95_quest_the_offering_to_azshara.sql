UPDATE `quest_template` SET `RequiredNpcOrGo1`=34423, `RequiredNpcOrGoCount1`=1 WHERE `Id`=13899;

DELETE FROM `creature_text` WHERE `entry`=34423;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34423,0,0,'You are too late... the relic is being offered to Azshara above us as we speak!',12,0,100,0,0,0,'Comment');

-- Warlord Wrathspine
SET @ENTRY := 34423;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,9000,12000,11,5164,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Knockdown"),
(@ENTRY,@SOURCETYPE,1,3,2,0,100,0,5,20,1000,1000,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hp 5% - Set Faction 35"),
(@ENTRY,@SOURCETYPE,2,5,61,0,100,0,0,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,2,61,0,100,0,0,0,0,0,33,34423,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Objective Complete - To Players"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,15000,15000,15000,15000,2,74,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Evade");