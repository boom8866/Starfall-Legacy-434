DELETE FROM `creature_template_addon` WHERE `entry` = '36440';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(36440, '68730');

-- Drowning Watchman
SET @ENTRY := 36440;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,8,64,0,100,0,0,0,0,0,11,46598,32,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Ride Player"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,28,46598,0,0,0,0,0,18,2,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove From Player"),
(@ENTRY,@SOURCETYPE,2,9,38,0,100,0,0,1,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Vehicle"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,0,3000,0,0,0,0,18,5,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,36440,0,0,69,0,0,0,0,0,0,8,0,0,0,-1875.87,2514.3,1.39,6.1,"After Talk 0 - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,33,36450,0,0,0,0,0,18,2,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,7,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,28,68730,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Drowning");

UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`=36440;