UPDATE `creature_template` SET `faction`=14 WHERE `entry`=56081;

DELETE FROM `creature` WHERE `guid` = '842952';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842952, 56081, 560, 3, 1, 0, 0, 2116.83, 708.681, 30.2834, 4.18662, 7200, 15, 0, 651, 0, 1, 0, 0, 0);

UPDATE `creature` SET `phaseMask`=1, `spawndist`=15, `MovementType`=1 WHERE `guid`=739051;

-- Caliph Scorpidsting
SET @ENTRY := 44750;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79443,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Sand Step"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,21000,21000,11,79443,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sand Step"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,20000,20000,11,744,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Poison");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=770386;

-- Two-Toes
SET @ENTRY := 44224;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,34827,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Water Shield"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,12500,14500,11,78542,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Splash");

UPDATE `creature_template` SET `minlevel`=87, `maxlevel`=87, `exp`=3, `faction`=14, `BaseAttackTime`=2000, `RangeAttackTime`=2000, `lootid`=54533 WHERE `entry`=54533;

-- Prince Lakma
SET @ENTRY := 54533;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,3500,4500,11,20543,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Breath"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,20545,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Lightning Shield");

DELETE FROM `creature` WHERE `guid` = '133801';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(133801, 54533, 1, 1, 1, 0, 0, -6054.63, 2109.39, 98.5575, 2.91374, 300, 15, 0, 2100, 0, 1, 0, 0, 0);

DELETE FROM `creature_loot_template` WHERE `entry` = '54533';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(54533, 21024, 52, 1, 0, 15, 20),
(54533, 62270, 8.8235, 1, 0, 1, 1),
(54533, 62271, 42.6471, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=774737;

-- Rufus Darkshot
SET @ENTRY := 44225;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1,1,6000,6000,11,79721,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosive Shot"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,4000,12500,12500,11,80004,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Snake Trap");

DELETE FROM `creature` WHERE `guid` = '201612';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(201612, 45384, 0, 1, 1, 0, 1, -5279.51, -2696.94, 344.469, 4.54227, 300, 0, 0, 345, 374, 0, 0, 0, 0);

-- Sagepaw
SET @ENTRY := 45384;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1,1,5000,5000,11,9739,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wrath"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,12500,12500,20000,20000,11,79924,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Healing Wave"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,8852,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Moss Hide");

-- Skitterflame
SET @ENTRY := 54324;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,101395,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Pyroclastic Charge"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,101357,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Cooling Down");