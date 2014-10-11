-- Earthen Catapult
SET @ENTRY := 43509;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,8000,8000,8000,8000,11,81770,0,0,0,0,0,11,43652,20,0,0.0,0.0,0.0,0.0,"IC - Cast Thunder Stone"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,8000,8000,8000,8000,11,81770,0,0,0,0,0,11,43847,20,0,0.0,0.0,0.0,0.0,"IC - Cast Thunder Stone"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invincible"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,53,0,43509,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Start WP"),
(@ENTRY,@SOURCETYPE,5,6,40,0,100,1,2,0,0,0,11,66854,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Summon First Wave"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,7,8,40,0,100,1,6,0,0,0,11,82027,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 6 - Summon Second Wave"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,9,10,40,0,100,1,7,0,0,0,11,66854,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 7 - Summon Third Wave"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,1,2,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 2"),
(@ENTRY,@SOURCETYPE,11,0,40,0,100,1,9,0,0,0,33,43649,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - Quest Complete"),
(@ENTRY,@SOURCETYPE,12,0,40,0,100,1,9,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - Force Despawn"),
(@ENTRY,@SOURCETYPE,13,0,40,0,100,1,2,0,0,0,54,12000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - (Pause 12 secs)"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,1,6,0,0,0,54,12000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 6 - (Pause 12 secs)"),
(@ENTRY,@SOURCETYPE,15,0,40,0,100,1,7,0,0,0,54,12000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 7 - (Pause 12 secs)"),
(@ENTRY,@SOURCETYPE,16,0,54,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Walk"),
(@ENTRY,@SOURCETYPE,17,0,40,0,100,1,2,0,0,0,11,66854,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Summon First Wave"),
(@ENTRY,@SOURCETYPE,18,0,40,0,100,1,6,0,0,0,11,82027,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 6 - Summon Second Wave"),
(@ENTRY,@SOURCETYPE,19,0,40,0,100,1,7,0,0,0,11,66854,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 7 - Summon Third Wave"),
(@ENTRY,@SOURCETYPE,20,0,40,0,100,1,7,0,0,0,11,66854,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 7 - Summon Third Wave");

-- Peak Grindstone
SET @ENTRY := 45043;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11916,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11916,0,0,0,85,81622,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Catapult"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,26632,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11916,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,30000,30000,30000,30000,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Restore NPC Flag");

-- Catapult Driver
SET @ENTRY := 45064;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45064,0,0,45,0,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Owner"),
(@ENTRY,@SOURCETYPE,2,0,38,0,90,0,0,10,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 1");

DELETE FROM `waypoints` WHERE `entry` = '43509';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(43509, 1, 743.57, 1992.31, 326.74, 'Earthen Catapult'),
(43509, 2, 777.92, 1993, 324.84, 'Earthen Catapult'),
(43509, 3, 805.71, 2017.48, 325.07, 'Earthen Catapult'),
(43509, 4, 859.33, 2019.01, 324.53, 'Earthen Catapult'),
(43509, 5, 891.95, 2031.75, 321.35, 'Earthen Catapult'),
(43509, 6, 939.54, 2031.44, 317.28, 'Earthen Catapult'),
(43509, 7, 991.13, 2006.21, 311.46, 'Earthen Catapult'),
(43509, 8, 1018.52, 1973.44, 307.47, 'Earthen Catapult'),
(43509, 9, 1018.65, 1947.62, 306.51, 'Earthen Catapult');