-- Warlord Bloodhilt
SET @ENTRY := 37837;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,37837,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,4,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,28,49415,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Invisibility Auras"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,37837,0,0,45,0,1,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,37837,0,0,45,0,2,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,2,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,2,37837,0,0,45,0,3,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,3,37837,0,0,45,0,4,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,4,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,13,20,52,0,100,0,4,37837,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,5,37837,0,0,45,0,5,0,0,0,0,11,37811,40,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 5 to Gar'Dul"),
(@ENTRY,@SOURCETYPE,15,17,27,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-3212.99,-1669.75,131.22,5.48,"On Passenger Boarded - Move To Window"),
(@ENTRY,@SOURCETYPE,16,0,34,0,100,0,8,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Remove Passenger"),
(@ENTRY,@SOURCETYPE,17,0,61,0,100,0,0,0,0,0,41,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,18,0,54,0,100,0,0,0,0,0,28,49416,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Invisibility Aura"),
(@ENTRY,@SOURCETYPE,19,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invisibility (Player)"),
(@ENTRY,@SOURCETYPE,20,0,61,0,100,0,0,0,0,0,28,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Invisibility");

-- Warlord Gar'dul
SET @ENTRY := 37811;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,37811,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,1,4,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,37811,0,0,45,0,1,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,2,37811,0,0,45,0,2,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,3,37811,0,0,45,0,3,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,10,11,38,0,100,0,0,4,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Set Aggressive"),
(@ENTRY,@SOURCETYPE,11,12,61,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Hostile"),
(@ENTRY,@SOURCETYPE,12,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,40,0,0,0.0,0.0,0.0,0.0,"Link - Attack Player"),
(@ENTRY,@SOURCETYPE,13,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,14,15,2,0,100,1,0,25,120000,120000,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health - Still Hostile"),
(@ENTRY,@SOURCETYPE,15,18,61,0,100,0,0,0,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 4"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,4,37811,0,0,45,0,4,0,0,0,0,11,37837,25,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 4 to Bloodhilt"),
(@ENTRY,@SOURCETYPE,17,0,38,0,100,0,0,5,0,0,11,46598,0,0,0,0,0,11,37837,40,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Ride Bloodhilt"),
(@ENTRY,@SOURCETYPE,18,0,61,0,100,0,0,0,0,0,33,37811,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,19,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invisibility (Player)");

DELETE FROM `creature_involvedrelation` WHERE `id` = '37837' AND `quest` = '24591';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(37837, 24591);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=24577;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '24577';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 4853, 24577, 24591, 1, 66);

-- Warlord Bloodhilt
SET @ENTRY := 37679;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24577,0,0,0,33,37816,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Quest Complete");