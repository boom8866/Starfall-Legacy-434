DELETE FROM `creature` WHERE `id` = '38910';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (38910, 0, 1, 1, 0, 0, 1857.74, 1556.2, 94.7914, 3.18656, 10, 0, 0, 98, 115, 0, 0, 0, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = '38910';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(38910, 0, 0, 0, 1, 431, '');

DELETE FROM `waypoints` WHERE `entry` = 38910;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(38910, 1, 1860.6, 1556.85, 94.789, 'Lilian Voss'),
(38910, 2, 1863.89, 1568.14, 94.3127, 'Lilian Voss'),
(38910, 3, 1875.33, 1573.06, 94.3127, 'Lilian Voss'),
(38910, 4, 1874.63, 1575.2, 94.3127, 'Lilian Voss'),
(38910, 5, 1863.54, 1575.25, 99.0438, 'Lilian Voss'),
(38910, 6, 1859.32, 1563.07, 99.0771, 'Lilian Voss'),
(38910, 7, 1855.27, 1555.96, 99.0779, 'Lilian Voss');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11132';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES (11132, 0, 0, 'You\'re not hideous, Lilian... you\'re one of us.  Here, look in this mirror, see for yourself.', 1, 1, 0, 0, 0, 0, '');

-- Lilian Voss
SET @ENTRY := 38910;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,11132,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,33,38910,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Complete Quest"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11132,0,0,0,1,0,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11132,0,0,0,53,1,38910,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Follow WP"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,7,0,0,0,41,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Stop WP");
