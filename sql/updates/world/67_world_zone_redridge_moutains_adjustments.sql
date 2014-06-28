UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (89612, 89611, 89585, 759922);
UPDATE `creature_template` SET `VehicleId`=686, `modelid1`=11686, `flags_extra`=128 WHERE `entry`=43618;
UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `guid`=90021;

DELETE FROM `spell_target_position` WHERE `id` = '81607';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(81607, -9555.71, -3045.73, 111.72, 3.77);

-- Render's Valley Camera
SET @ENTRY := 43618;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,0,500,500,500,500,86,81619,0,7,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Ride Owner"),
(@ENTRY,@SOURCETYPE,2,0,27,1,100,0,0,0,0,0,74,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Remove Timed Event"),
(@ENTRY,@SOURCETYPE,3,0,27,1,100,0,0,0,0,0,53,1,43618,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - WP Start"),
(@ENTRY,@SOURCETYPE,4,0,40,1,100,0,1,0,0,0,45,0,1,0,0,0,0,10,90228,43590,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Set Data 1 to Blackrock Tower"),
(@ENTRY,@SOURCETYPE,5,0,40,1,100,0,1,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,6,0,60,2,100,0,12500,12500,12500,12500,28,81619,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - (8 seconds) - Remove Passenger"),
(@ENTRY,@SOURCETYPE,7,0,28,2,100,0,0,0,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,0,40,1,100,0,1,0,0,0,45,0,1,0,0,0,0,10,90192,43589,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Set Data 1 to Munitions Dump");

-- Munitions Dump
SET @ENTRY := 43589;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,81639,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Explosion"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,11,81639,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Explosion");

-- Darkblaze
SET @ENTRY := 43496;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,69,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,1,8,0,0,0,11,82067,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Morph into Human Form"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,8,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Phase 1"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,1,1500,1500,1500,1500,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,1,100,1,0,43496,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,1,1,43496,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,1,100,1,2,43496,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Faction 14"),
(@ENTRY,@SOURCETYPE,7,0,52,1,100,1,2,43496,0,0,28,82067,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Return to Original Form"),
(@ENTRY,@SOURCETYPE,8,0,52,1,100,1,2,43496,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,9,0,60,2,100,1,2000,2000,2000,2000,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 3"),
(@ENTRY,@SOURCETYPE,10,0,2,2,100,1,1,10,0,0,1,4,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On HP 10% - Talk 4"),
(@ENTRY,@SOURCETYPE,11,12,52,2,100,1,4,43496,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,12,15,61,2,100,1,0,0,0,0,11,82069,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Darkblaze"),
(@ENTRY,@SOURCETYPE,13,0,54,0,100,1,0,0,0,0,42,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invincible on 10% HP"),
(@ENTRY,@SOURCETYPE,14,0,7,2,100,1,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Force Despawn"),
(@ENTRY,@SOURCETYPE,15,0,61,2,100,1,0,0,0,0,45,0,25,0,0,0,0,11,0,80,0,0.0,0.0,0.0,0.0,"Link - Set Data 25 to Creatures"),
(@ENTRY,@SOURCETYPE,16,0,27,2,100,1,0,0,0,0,53,1,43496,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,17,0,40,2,100,1,2,0,0,0,33,43496,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Quest Complete"),
(@ENTRY,@SOURCETYPE,18,0,40,2,100,1,2,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Die"),
(@ENTRY,@SOURCETYPE,19,0,2,2,100,1,5,10,0,0,42,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On HP 10% - Set Invicibility"),
(@ENTRY,@SOURCETYPE,20,0,52,1,100,1,2,43496,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Aggressive"),
(@ENTRY,@SOURCETYPE,21,0,52,1,100,1,2,43496,0,0,49,2,0,0,0,0,0,11,0,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Attack Start");

-- Gath'Ilzogg
SET @ENTRY := 334;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1300,6500,194300,194300,11,7164,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Gath'Ilzogg - In Combat - Cast Defensive Stance"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,12900,32100,39400,11,3427,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Gath'Ilzogg - In Combat - Cast Infected Wound"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,5200,12100,11,11792,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Gath'Ilzogg - In Combat - Cast Opening Cage"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,12,43863,4,120000,0,0,0,8,0,0,0,-9469.75,-2969.32,126.55,2.09,"On Death - Spawn Horn of Summoning");