-- Stormpike Trainee
SET @ENTRY := 48912;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,500,1500,500,1500,5,37,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,13730,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,79871,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Recklessness"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,33,49037,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Death - Killed Monster Credit"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,69,0,0,0,0,0,0,11,49036,15,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Move to Invoker"),
(@ENTRY,@SOURCETYPE,5,0,34,0,100,0,8,0,0,0,45,0,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Data 2 to Self"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,2,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Die"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,2,0,0,5,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Play Emote "),
(@ENTRY,@SOURCETYPE,8,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Defensive");