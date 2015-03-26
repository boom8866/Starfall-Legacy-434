UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048 WHERE `entry`=44326;

-- Stickbone Berserker
SET @ENTRY := 44329;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,14,82595,204966,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Animus"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,0,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Random Move"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,14,82618,204966,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Animus");