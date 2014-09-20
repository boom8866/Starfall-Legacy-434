-- Defias Knuckleduster
SET @ENTRY := 449;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
UPDATE `creature_template` SET `speed_walk`=0.0001, `speed_run`=0.0001 WHERE `entry`=42617;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Knuckleduster - On Aggro - Say random text"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1400,2700,7300,15000,11,12555,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Defias Knuckleduster - Combat - Cast Pummel"),
(@ENTRY,@SOURCETYPE,2,0,0,0,40,0,2100,4300,3900,4300,11,3391,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Knuckleduster - Combat - Cast Thrash"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Knuckleduster - HP@15% - Flee");

-- Thoralius the Wise
SET @ENTRY := 42651;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

