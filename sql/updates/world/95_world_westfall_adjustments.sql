-- Hope Saldean
SET @ENTRY := 42575;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,2,0,0,53,0,42575,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,1,1,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,42575,0,0,45,0,1,0,0,0,0,10,172646,234,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Gryan"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,3,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,42575,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,42575,0,0,11,79709,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Transform in Vanessa"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,79709,1,0,0,1,3,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,42575,0,0,45,0,5,0,0,0,0,11,42771,80,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 5 to Triggers"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,1,0,6,0,0,1,4,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,42575,0,0,45,0,7,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 7 to Nearest Creatures (Tie up)"),
(@ENTRY,@SOURCETYPE,10,0,40,0,100,0,1,0,0,0,54,35000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - WP Pause (35 secs)"),
(@ENTRY,@SOURCETYPE,11,0,40,0,100,0,2,0,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Talk 5"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,5,42575,0,0,45,0,1,0,0,0,0,10,172484,42635,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 1 to Ripsnarl"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,11,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 11 - Talk 6"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,2,0,0,0,54,18000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause (18 secs)"),
(@ENTRY,@SOURCETYPE,15,0,40,0,100,0,3,0,0,0,54,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - WP Pause (2 secs)"),
(@ENTRY,@SOURCETYPE,16,0,38,0,100,0,0,20,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 20 - Talk 7"),
(@ENTRY,@SOURCETYPE,17,0,40,0,100,0,4,0,0,0,54,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - WP Pause (20 secs)"),
(@ENTRY,@SOURCETYPE,18,0,52,0,100,0,7,42575,0,0,1,8,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,19,21,52,0,100,0,8,42575,0,0,1,9,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 8 - Talk 9"),
(@ENTRY,@SOURCETYPE,20,0,40,0,100,0,3,0,0,0,45,0,15,0,0,0,0,11,42744,80,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Set Data 15 to Laine"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,15,26322,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,22,0,40,0,100,0,5,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Wp Reached 5 - Force Despawn (1 sec)"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,5,0,0,0,45,0,25,0,0,0,0,10,172646,234,0,0.0,0.0,0.0,0.0,"On Wp Reached 5 - Set Data 25 to Gryan"),
(@ENTRY,@SOURCETYPE,24,0,40,0,100,0,5,0,0,0,45,0,25,0,0,0,0,11,42769,100,0,0.0,0.0,0.0,0.0,"On Wp Reached 5 - Set Data 25 to Blackguards");

-- Sentinel Hill Fire Trigger
SET @ENTRY := 42793;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,30,0,0,11,84788,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 30 - Cast Flames"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,1,0,35,0,0,70,0,0,0,0,0,0,11,0,35,0,0.0,0.0,0.0,0.0,"On Get Data 35 - Respawn Creatures (Reset Events)");

-- Defias Henchman
SET @ENTRY := 594;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - On Aggro - Say random text"),
(@ENTRY,@SOURCETYPE,1,0,13,0,100,1,3200,13800,0,0,11,8242,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - Combat - Cast Shield Slam"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,1,3600,18800,0,0,11,3248,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - Combat - Cast Improved Blocking"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Defias Henchman - HP@15% - Flee");

-- Deletes creature Defias Pillager (id: 589, guid: 772520) in zone: 40, area: 108
DELETE FROM `creature` WHERE `guid` = 772520; DELETE FROM creature_addon WHERE guid = 772520;