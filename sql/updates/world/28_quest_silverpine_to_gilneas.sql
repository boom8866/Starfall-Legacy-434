UPDATE `creature_template` SET `InhabitType`=4, `HoverHeight`=2.4 WHERE  `entry`=46032;
UPDATE `quest_template` SET `SourceSpellId`=85869 WHERE  `Id`=27290;
UPDATE `creature_template` SET `VehicleId`=1075 WHERE  `entry`=46032;
UPDATE `creature_template` SET `speed_walk`=3, `speed_run`=3 WHERE  `entry`=46032;

DELETE FROM `waypoints` WHERE `entry` = '46032';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(46032, 1, 480.35, 1541.18, 158.89, 'Arthura to Gilneas'),
(46032, 2, 255.29, 1453.40, 164.76, 'Arthura to Gilneas'),
(46032, 3, -248.32, 1493.53, 194.38, 'Arthura to Gilneas'),
(46032, 4, -683.24, 1535.08, 79.41, 'Arthura to Gilneas'),
(46032, 5, -836.23, 1552.09, 49.79, 'Arthura to Gilneas'),
(46032, 6, -935.18, 1634.08, 73.90, 'Arthura to Gilneas');

DELETE FROM `creature_text` WHERE `entry`=46032;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES (46032,0,0,'Do not be afraid. I will not let you fall.',12,0,100,0,0,0,'Comment');

-- Arthura
SET @ENTRY := 46032;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Grab Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,46032,0,27290,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 1 Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,6,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Last WP Reached - Leave Vehicle");

INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `MapId`, `ZoneId`, `AreaId`, `Comment`) VALUES 
(27342, 32768, 4, 0, 4706, 5434, 'Quest ID: 27342 - In Time, All Will Be Revealed (ON AURA UPDATE)'),
(27342, 27333, 4, 0, 4706, 5440, 'Quest ID: 27194 - In Time, All Will Be Revealed (ON AURA UPDATE)'),
(27290, 32768, 4, 0, 4706, 5434, 'Quest ID: 27290 - To Forsaken Forward Command (ON AURA UPDATE)'),
(27333, 32768, 4, 0, 4706, 5434, 'Quest ID: 27333 - Losing Ground (ON AURA UPDATE)'),
(27333, 32768, 4, 0, 4706, 5440, 'Quest ID: 27333 - Losing Ground (ON AURA UPDATE)');

INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES (45315, 27345);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES (45315, 27345);