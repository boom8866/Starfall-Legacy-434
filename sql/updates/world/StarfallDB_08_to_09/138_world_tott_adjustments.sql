UPDATE `creature_template` SET `DamageModifier`=15 WHERE `entry` IN (40586, 40765, 40825, 40788, 44566);
UPDATE `creature_template` SET `DamageModifier`=7 WHERE `entry`=41139;
UPDATE `creature_template` SET `DamageModifier`=14 WHERE `entry`=49091;
UPDATE `creature_template` SET `DamageModifier`=7 WHERE `entry`=50276;
UPDATE `creature_template` SET `DamageModifier`=14 WHERE `entry`=50277;
UPDATE `creature_template` SET `DamageModifier`=4 WHERE `entry`=44841;
UPDATE `creature_template` SET `DamageModifier`=8 WHERE `entry`=49061;

-- Faceless Watcher
SET @ENTRY := 40936;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,30,10000,10000,40000,40000,11,76590,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Ground Puond"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,30,1000,1000,30000,30000,11,76604,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Void rip");