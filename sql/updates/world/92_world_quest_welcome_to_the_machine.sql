UPDATE `creature_template` SET `minlevel`=20, `maxlevel`=20, `faction_A`=68, `faction_H`=68 WHERE  `entry`=47488;

-- Skeletal Steed
SET @ENTRY := 47488;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,85,88476,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Quest Giver on Invoker"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,85,88477,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Remove Quest Giver from Invoker"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,85,88563,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Summon Darthalia"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,2000,2000,0,0,86,88543,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Ride");