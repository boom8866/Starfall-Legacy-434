UPDATE `creature` SET `phaseMask`=1 WHERE `guid` = '734566';
UPDATE `creature` SET `phaseMask`=2 WHERE `guid` = '736507';
UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (34399, 34398);
UPDATE `creature_template` SET `InhabitType`=4, `VehicleId`=1173, `speed_walk`=3, `speed_run`=3 WHERE `entry`=34400;

DELETE FROM `waypoints` WHERE `entry` = '34400';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(34400, 1, 5776.86, -164.85, 18.19, 'Thessera WP'),
(34400, 2, 5795.20, -157.64, 13.61, 'Thessera WP'),
(34400, 3, 5811.05, -157.90, 5.90, 'Thessera WP'),
(34400, 4, 5829.02, -180.91, 1.56, 'Thessera WP'),
(34400, 5, 5839.31, -193.92, -3.03, 'Thessera WP'),
(34400, 6, 5835.49, -237.04, 3.84, 'Thessera WP'),
(34400, 7, 5813.28, -211.93, 10.01, 'Thessera WP'),
(34400, 8, 5816.83, -190.55, 14.14, 'Thessera WP'),
(34400, 9, 5842.88, -158.33, 19.85, 'Thessera WP'),
(34400, 10, 5832.18, -136.60, 15.91, 'Thessera WP'),
(34400, 11, 5817.22, -53.25, 27.14, 'Thessera WP'),
(34400, 12, 5805.87, -31.57, 22.91, 'Thessera WP'),
(34400, 13, 5781.33, -53.25, 27.14, 'Thessera WP'),
(34400, 14, 5786.48, 1.97, 21.45, 'Thessera WP'),
(34400, 15, 5790.06, 104.60, 74.51, 'Thessera WP'),
(34400, 16, 5898.45, 190.25, 71.21, 'Thessera WP');

-- Thessera
SET @ENTRY := 33166;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,13940,0,0,0,11,65424,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Accept Quest - Cast Thessera Ride");

-- Thessera
SET @ENTRY := 34400;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,54,0,100,1,0,0,0,0,86,46598,0,21,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Grab closest player"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,53,1,34400,0,13940,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,16,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger");