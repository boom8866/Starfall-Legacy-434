-- Therazane
SET @ENTRY := 42465;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,26752,0,0,0,83,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,1,17,19,0,100,0,26752,0,0,0,85,82138,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Torunscar"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,26752,0,0,0,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,42465,0,0,1,1,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,42465,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,42465,0,0,1,3,9000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,42465,0,0,45,0,1,0,0,0,0,11,43901,60,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 1 to Torunscar"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,1,0,0,1,4,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,42465,0,0,45,0,2,0,0,0,0,11,43901,60,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 2 to Torunscar"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,2,0,0,1,5,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 5"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,42465,0,0,1,6,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,6,42465,0,0,1,7,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,7,42465,0,0,1,8,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,8,42465,0,0,45,0,3,0,0,0,0,11,43901,60,0,0.0,0.0,0.0,0.0,"After Talk 8 - Set Data 3 to Torunscar"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,3,0,0,1,9,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 9"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,9,42465,0,0,82,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Reset Flags"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,9,42465,0,0,33,44051,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Quest Credit"),
(@ENTRY,@SOURCETYPE,17,0,61,0,100,0,26752,0,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Despawn");