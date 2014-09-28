-- Prince Liam Greymane
SET @ENTRY := 37065;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,0,1,3,60000,60000,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"OOC LoS - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,20000,45000,20000,45000,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,24472,0,0,0,85,72857,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Reward Quest - *TEMP* Learn Two Forms");