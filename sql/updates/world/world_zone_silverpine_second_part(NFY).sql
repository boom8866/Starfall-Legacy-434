DELETE FROM `creature_questrelation` WHERE `id`=45315 AND `quest`=27364;

-- Forsaken Warhorse
SET @ENTRY := 45041;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Forsaken Warhorse (Player)"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,45041,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,39,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Start - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,20,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 20 - Dismount"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,15,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 15 Set Walk");

-- Forsaken Warhorse
SET @ENTRY := 45057;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,2000,2000,0,0,53,1,45057,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,18,1048576,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Taxi"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,1,0,8000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45051,0,0,1,1,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,45051,0,0,1,2,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45051,0,0,1,3,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45051,0,0,1,4,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,45051,0,0,1,5,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 5"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,5,45051,0,0,1,6,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 6"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,6,45051,0,0,1,7,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 7"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,7,45051,0,0,1,8,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 8"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,8,45051,0,0,1,9,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 9"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,9,45051,0,0,1,10,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 10"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,10,45051,0,0,1,11,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 11"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,11,45051,0,0,1,12,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 12"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,12,45051,0,0,1,13,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 13"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,13,45051,0,0,1,14,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 14"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,14,45051,0,0,1,15,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 15"),
(@ENTRY,@SOURCETYPE,18,0,52,0,100,0,15,45051,0,0,1,16,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 16"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,16,45051,0,0,1,17,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 17"),
(@ENTRY,@SOURCETYPE,20,0,52,0,100,0,17,45051,0,0,1,18,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 18"),
(@ENTRY,@SOURCETYPE,21,0,52,0,100,0,18,45051,0,0,1,19,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 19"),
(@ENTRY,@SOURCETYPE,22,0,52,0,100,0,19,45051,0,0,1,20,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 20"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,20,0,0,0,41,3000,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Dismount on WP End"),
(@ENTRY,@SOURCETYPE,24,0,58,0,100,0,0,0,0,0,33,45051,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Completed"),
(@ENTRY,@SOURCETYPE,25,0,52,0,100,0,20,45051,0,0,1,21,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk - 21"),
(@ENTRY,@SOURCETYPE,26,0,40,0,100,0,15,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 15 - Set Walk");

DELETE FROM `waypoints` WHERE `entry` = '45057';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(45057, 1, 1344.96, 1011.48, 54.59, 'Sylvanas (Lordaeron Event)'),
(45057, 2, 1318.56, 1020.83, 54.59, 'Sylvanas (Lordaeron Event)'),
(45057, 3, 1271.48, 1086.55, 52.33, 'Sylvanas (Lordaeron Event)'),
(45057, 4, 1229.24, 1124.89, 50.47, 'Sylvanas (Lordaeron Event)'),
(45057, 5, 1145.65, 1183.89, 47.89, 'Sylvanas (Lordaeron Event)'),
(45057, 6, 1108.21, 1205.00, 46.40, 'Sylvanas (Lordaeron Event)'),
(45057, 7, 1043.83, 1269.22, 46.03, 'Sylvanas (Lordaeron Event)'),
(45057, 8, 957.33, 1320.40, 46.54, 'Sylvanas (Lordaeron Event)'),
(45057, 9, 907.19, 1348.97, 48.92, 'Sylvanas (Lordaeron Event)'),
(45057, 10, 868.52, 1358.90, 54.70, 'Sylvanas (Lordaeron Event)'),
(45057, 11, 776.64, 1359.87, 65.12, 'Sylvanas (Lordaeron Event)'),
(45057, 12, 736.14, 1353.96, 71.88, 'Sylvanas (Lordaeron Event)'),
(45057, 13, 673.48, 1306.19, 81.39, 'Sylvanas (Lordaeron Event)'),
(45057, 14, 644.97, 1294.35, 85.60, 'Sylvanas (Lordaeron Event)'),
(45057, 15, 610.69, 1355.34, 87.32, 'Sylvanas (Lordaeron Event)'),
(45057, 16, 582.67, 1416.12, 96.24, 'Sylvanas (Lordaeron Event)'),
(45057, 17, 553.03, 1454.93, 106.07, 'Sylvanas (Lordaeron Event)'),
(45057, 18, 509.98, 1495.19, 124.92, 'Sylvanas (Lordaeron Event)'),
(45057, 19, 500.14, 1531.72, 129.62, 'Sylvanas (Lordaeron Event)'),
(45057, 20, 500.45, 1562.66, 127.63, 'Sylvanas (Lordaeron Event)');

UPDATE `creature_template` SET `unit_flags`=2 WHERE `entry`=45041;

-- Agatha
SET @ENTRY := 44951;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,75,85451,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Add Death Walk to self"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,5000,10000,10000,11,83173,0,0,0,0,0,11,44593,10,0,0.0,0.0,0.0,0.0,"Raise Forsaken from Fallen Humans"),
(@ENTRY,@SOURCETYPE,3,0,31,0,100,0,83173,1,0,0,33,44953,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Run"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Passive"),
(@ENTRY,@SOURCETYPE,6,0,0,0,50,0,1500,1500,1500,1500,11,84012,0,0,0,0,0,11,44987,3,0,0.0,0.0,0.0,0.0,"Cast Doomhowl"),
(@ENTRY,@SOURCETYPE,7,0,0,0,25,0,5000,5000,5000,5000,11,84013,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Cast Unholy Darkness"),
(@ENTRY,@SOURCETYPE,8,0,0,0,50,0,1500,1500,1500,1500,11,84014,0,0,0,0,0,11,44987,3,0,0.0,0.0,0.0,0.0,"Cast Unholy Smite"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,0,10000,10000,40000,40000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 0"),
(@ENTRY,@SOURCETYPE,10,0,31,0,100,0,83173,1,1500,1500,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 1"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,1,0,0,80,4495100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 Call Actionlist"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,1,2,44951,0,0,12,44989,8,120000,0,0,0,8,0,0,0,992.64,692.38,74.89,6.09,"Summon Crowley on Text 2"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,2,0,0,80,4495101,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 2 Call Actionlist"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,18,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 18 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,44987,5,0,0.0,0.0,0.0,0.0,"OOC - Attack Worgens"),
(@ENTRY,@SOURCETYPE,16,0,4,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Set Defensive"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,0,5000,5000,5000,5000,8,0,0,0,0,0,0,1,44987,5,0,0.0,0.0,0.0,0.0,"OOC - Set Passive");

-- Fenris Keep Stalker
SET @ENTRY := 45032;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,1000,1000,45,0,1,0,0,0,0,11,44951,1,0,0.0,0.0,0.0,0.0,"Set data 1 to Agatha");