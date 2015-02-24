-- Defias Henchman
SET @ENTRY := 594;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,5,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - On Aggro - Say random text"),
(@ENTRY,@SOURCETYPE,1,0,13,0,100,1,3200,13800,0,0,11,8242,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - Combat - Cast Shield Slam"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,1,3600,18800,0,0,11,3248,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - Combat - Cast Improved Blocking"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - HP@15% - Flee");
