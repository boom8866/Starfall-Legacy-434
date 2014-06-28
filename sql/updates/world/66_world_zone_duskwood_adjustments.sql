-- Stalvan Mistmantle
SET @ENTRY := 315;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,20,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stalvan Mistmantle - On Aggro - Say Line 0"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,7800,9000,8000,16000,11,3105,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Stalvan Mistmantle - In Combat - Cast Curse of Stalvan"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Stalvan Mistmantle - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,3,4,54,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,69,2,0,0,0,0,0,8,0,0,0,-10369.6,-1254.16,35.9,5.99,"Link - Move to Pos"),
(@ENTRY,@SOURCETYPE,5,18,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,1,0,0,1,2,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,315,0,0,45,0,1,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Tobias"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,2,315,0,0,45,0,2,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Tobias"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,2,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,3,315,0,0,45,0,3,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Tobias"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,3,0,0,1,4,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,4,315,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,5,315,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,4,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 7"),
(@ENTRY,@SOURCETYPE,15,19,52,0,100,0,6,315,0,0,45,0,4,0,0,0,0,11,43904,50,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 4 to Tobias"),
(@ENTRY,@SOURCETYPE,16,0,6,0,100,0,0,0,0,0,1,7,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 7"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,7,315,0,0,45,0,5,0,0,0,0,11,43904,200,0,0.0,0.0,0.0,0.0,"After Talk 7 - Set Data 5 to Tobias"),
(@ENTRY,@SOURCETYPE,18,0,61,0,100,0,0,0,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Unattackable"),
(@ENTRY,@SOURCETYPE,19,0,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Aggressive"),
(@ENTRY,@SOURCETYPE,20,21,38,0,100,0,0,10,0,0,19,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Make attackable"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,43904,100,0,0.0,0.0,0.0,0.0,"Link - Set Data 10 to Tobias");

-- Tobias Mistmantle
SET @ENTRY := 43904;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward 5 yd"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,43904,0,0,45,0,1,0,0,0,0,11,315,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Tobias"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,2,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,43904,0,0,45,0,2,0,0,0,0,11,315,50,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Tobias"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,1,2,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,43904,0,0,45,0,3,0,0,0,0,11,315,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Tobias"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,4,0,0,1,3,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,43904,0,0,11,81908,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Cast Transform Worgen"),
(@ENTRY,@SOURCETYPE,9,10,8,0,100,0,81908,1,0,0,3,0,33508,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Morph into Worgen"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,2,2173,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction 1770"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,10,0,0,11,76678,2,0,0,0,0,11,315,100,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Attack"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,5,0,0,1,4,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 4"),
(@ENTRY,@SOURCETYPE,13,14,52,0,100,0,4,43904,0,0,69,0,0,0,0,0,0,8,0,0,0,-10355.5,-1256.69,35.3,0.05,"After Talk 4 - Move Out"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,3,43904,0,0,45,0,10,0,0,0,0,11,315,100,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 10 to Stalvan");

DELETE FROM `creature` WHERE `guid` = '775039';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(775039, 43862, 0, 1, 2, 0, 0, -10553.2, -1169.15, 27.8817, 1.76278, 60, 0, 0, 1, 0, 0, 0, 0, 0);

UPDATE `spell_area` SET `quest_end_status`=11 WHERE `spell`=82071 AND `area`=42 AND `quest_start`=26727 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;
DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '26727';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 42, 26727, 26727, 1, 10);