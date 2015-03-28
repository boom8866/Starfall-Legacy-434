UPDATE `creature_template` SET `DamageModifier`=14 WHERE `entry`=49308;

-- Temple Runecaster
SET @ENTRY := 48140;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,1000,2000,16000,16000,11,89551,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"48140 - Curse of the runecaster"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,2,1000,1200,4000,4200,11,89554,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"48140- Runic cleave"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,4,1000,2000,16000,16000,11,95181,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"48140 - Curse of the runecaster"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,4,1000,1200,4000,4200,11,91806,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"48140- Runic cleave");