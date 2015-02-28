-- Gnomeregan Trainee
SET @ENTRY := 42329;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1200,1700,1800,2000,5,36,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Play ONESHOT_ATTACK1H emote"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,0,4000,2000,10000,5,440,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chance to Dodge"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,0,4000,2000,10000,5,54,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chance for Special");