-- Aviana's Guardian
SET @ENTRY := 40719;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,1000,1000,1000,1000,51,0,0,0,0,0,0,11,40650,5,0,0.0,0.0,0.0,0.0,"OOC - Kill Unit"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,1000,1000,1000,1000,51,0,0,0,0,0,0,11,39833,5,0,0.0,0.0,0.0,0.0,"OOC - Kill Unit"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,0,1000,1000,1000,1000,85,35041,0,0,0,0,0,11,40650,5,0,0.0,0.0,0.0,0.0,"OOC - Swing"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,1000,1000,1000,1000,85,35041,0,0,0,0,0,11,39833,5,0,0.0,0.0,0.0,0.0,"OOC - Swing"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,0,1000,1000,1000,1000,51,0,0,0,0,0,0,11,40762,6,0,0.0,0.0,0.0,0.0,"OOC - Kill Unit"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,0,1000,1000,1000,1000,85,35041,0,0,0,0,0,11,40762,6,0,0.0,0.0,0.0,0.0,"OOC - Swing"),
(@ENTRY,@SOURCETYPE,10,0,8,0,4,0,74183,1,0,0,1,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,11,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive");

UPDATE `creature_template` SET `exp`=3 WHERE `entry`=40719;