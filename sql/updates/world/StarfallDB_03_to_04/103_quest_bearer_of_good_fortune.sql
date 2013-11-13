UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=31, `groupid`=1 WHERE `entry`=33022 AND `item`=44927;
UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `id`=33024;

-- Secure Bear Cage
SET @ENTRY := 194124;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,33024,5,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Bear");

-- Uncorrupted Thistle Bear
SET @ENTRY := 33024;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,1,3,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (5 secs)"),
(@ENTRY,@SOURCETYPE,2,0,60,2,100,1,4000,4000,0,0,33,33024,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"Phase 2 - Update (4 secs) Quest Complete"),
(@ENTRY,@SOURCETYPE,3,0,60,2,100,1,2000,2000,0,0,46,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (4 secs) - Move Forward (2 yd)");