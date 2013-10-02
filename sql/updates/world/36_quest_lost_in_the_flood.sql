UPDATE `creature_template` SET `VehicleId`=686 WHERE  `entry`=39320;
UPDATE `creature_template` SET `VehicleId`=686 WHERE  `entry`=39345;
UPDATE `creature_template` SET `VehicleId`=686 WHERE  `entry`=39346;
UPDATE `creature_template` SET `VehicleId`=686 WHERE  `entry`=39347;
UPDATE `creature_template` SET `speed_walk`=5, `speed_run`=5 WHERE  `entry`=39320;
UPDATE `creature_template` SET `speed_walk`=5, `speed_run`=5 WHERE  `entry`=39345;
UPDATE `creature_template` SET `speed_walk`=5, `speed_run`=5 WHERE  `entry`=39346;
UPDATE `creature_template` SET `speed_walk`=5, `speed_run`=5 WHERE  `entry`=39347;
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=39320;
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=39345;
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=39346;
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=39347;

DELETE FROM `spell_script_names` WHERE `spell_id` = '73817';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (73817, 'spell_thonk_spyglass');

DELETE FROM `waypoints` WHERE `entry` = '39320';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(39320, 1, 253.31, -4438.12, 64.48, 'Camera Raggaran'),
(39320, 2, 105.31, -4277.61, 51.28, 'Camera Raggaran'),
(39320, 3, 64.44, -4234.71, 38.79, 'Camera Raggaran');

DELETE FROM `waypoints` WHERE `entry` = '39345';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(39345, 1, 436.80, -4452.51, 67.38, 'Camera Tekla'),
(39345, 2, 497.26, -4303.24, 50.31, 'Camera Tekla'),
(39345, 3, 541.47, -4177.34, 31.79, 'Camera Tekla');

DELETE FROM `waypoints` WHERE `entry` = '39346';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(39346, 1, 523.43, -4454.42, 63.01, 'Camera Misha'),
(39346, 2, 614.62, -4361.05, 42.80, 'Camera Misha'),
(39346, 3, 708.10, -4272.72, 24.67, 'Camera Misha');

DELETE FROM `waypoints` WHERE `entry` = '39347';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(39347, 1, 323.93, -4275.83, 61.68, 'Camera Zentaji'),
(39347, 2, 343.30, -4016.13, 45.55, 'Camera Zentaji'),
(39347, 3, 349.78, -3879.92, 24.83, 'Camera Zentaji');

-- Durotar Watershed Telescope 01 (Raggaran)
SET @ENTRY := 39320;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,39320,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Fly"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI - Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,3,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,0,6000,6000,6000,6000,28,83788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Phase 1 - Update (6 secs) Remove Camera"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,0,10000,10000,10000,10000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn");

-- Durotar Watershed Telescope 02 (Tekla)
SET @ENTRY := 39345;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,39345,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Fly"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI - Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,3,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,0,6000,6000,6000,6000,28,83788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Phase 1 - Update (6 secs) Remove Camera"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,0,10000,10000,10000,10000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn");

-- Durotar Watershed Telescope 03 (Misha)
SET @ENTRY := 39346;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,39346,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Fly"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI - Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,3,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,0,6000,6000,6000,6000,28,83788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Phase 1 - Update (6 secs) Remove Camera"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,0,10000,10000,10000,10000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn");

-- Durotar Watershed Telescope 04 (Zen'Taji)
SET @ENTRY := 39347;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,39347,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Fly"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI - Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,3,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,0,6000,6000,6000,6000,28,83788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Phase 1 - Update (6 secs) Remove Camera"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,0,10000,10000,10000,10000,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn");