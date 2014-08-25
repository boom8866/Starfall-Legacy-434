-- Deep Murloc Hunter
SET @ENTRY := 40579;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1500,1500,1500,1500,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset - Set Run");

DELETE FROM `creature_formations` WHERE `leaderGUID` = '781212';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(781212, 781212, 0, 0, 2),
(781212, 781209, 4, 25, 2),
(781212, 781208, 4, 50, 2),
(781212, 781211, 4, 60, 2),
(781212, 781202, 4, 345, 2),
(781212, 781203, 4, 325, 2),
(781212, 781204, 4, 305, 2),
(781212, 781201, 4, 290, 2);

-- Adds Waypoint Movement to Deep Murloc Hunter (guid: 781212, entry: 40579)
SET @GUID  := 781212;
SET @WP_ID := 7812120;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 781212;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(781212, 7812120, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, 38.156, 778.163, 806.317, 0),
(@WP_ID, 2, 38.385, 802.250, 805.731, 0),
(@WP_ID, 3, 37.646, 825.236, 806.317, 0),
(@WP_ID, 4, 52.727, 854.158, 806.020, 0),
(@WP_ID, 5, 65.544, 820.367, 806.317, 0),
(@WP_ID, 6, 60.684, 781.492, 806.317, 0),
(@WP_ID, 7, 52.332, 752.783, 806.107, 0);