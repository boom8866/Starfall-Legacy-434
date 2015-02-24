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

UPDATE `creature_template` SET `lootid`=50050 WHERE `entry`=50050;

-- Shok'sharak
SET @ENTRY := 50050;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1,1,8000,8000,11,75903,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Crash"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,9000,9000,9000,9000,11,75073,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Nova");

DELETE FROM `creature_loot_template` WHERE `entry` = '50050';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50050, 67233, 100, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=777099;
UPDATE `creature_template` SET `lootid`=50086 WHERE `entry`=50086;

DELETE FROM `creature_loot_template` WHERE `entry` = '50086';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50086, 67245, 100, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `entry` = '50060';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50060, 67238, 100, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=746686;
UPDATE `creature_template` SET `lootid`=50060 WHERE `entry`=50060;

-- Terborus
SET @ENTRY := 50060;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79927,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Earth Shield"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1500,1500,46000,46000,11,32738,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bore");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=731478;

-- Adds Waypoint Movement to Terrorpene (guid: 731478, entry: 50058)
SET @GUID  := 731478;
SET @WP_ID := 7314780;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 731478;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(731478, 7314780, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, 4062.310, -3288.660, 954.756, 0),
(@WP_ID, 2, 4082.960, -3295.330, 955.893, 0),
(@WP_ID, 3, 4082.450, -3290.900, 957.518, 0),
(@WP_ID, 4, 4064.780, -3289.400, 955.010, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=731261;
UPDATE `creature_template` SET `lootid`=50053 WHERE `entry`=50053;

DELETE FROM `creature_loot_template` WHERE `entry` = '50053';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50053, 67234, 100, 1, 0, 1, 1);

-- Thartuk the Exile
SET @ENTRY := 50053;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,0,30,0,0,11,8599,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Enrage at 30% HP"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 30% HP"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,6000,12500,12500,11,81173,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frenzy");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (51661, 44722);

-- Twisted Reflection of Narain
SET @ENTRY := 44722;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1,1,4500,4500,11,77721,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Weave"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5500,5500,15650,25450,11,75073,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Nova"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,77471,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shadow Shield");

-- Tsul'Kalu
SET @ENTRY := 51661;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79927,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Earth Shield"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,4500,12500,14000,11,81140,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Thunderclap");

UPDATE `creature` SET `spawndist`=25, `MovementType`=1 WHERE `id`=49780;

-- Position update for Xariona (id: 50061) in zone: 5042, area: 5042
UPDATE `creature` SET `position_x` = 621.049, `position_y` = 736.982, `position_z` = 462.755, `orientation`= 1.244 WHERE `guid` = 746683;

-- Adds Waypoint Movement to Xariona (guid: 746683, entry: 50061)
SET @GUID  := 746683;
SET @WP_ID := 7466830;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 746683;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(746683, 7466830, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, 597.888, 681.293, 453.786, 0),
(@WP_ID, 2, 558.915, 524.295, 443.384, 0),
(@WP_ID, 3, 609.457, 350.011, 455.276, 0),
(@WP_ID, 4, 718.475, 181.551, 477.429, 0),
(@WP_ID, 5, 863.465, 92.291, 481.441, 0),
(@WP_ID, 6, 1021.230, 73.513, 464.633, 0),
(@WP_ID, 7, 1250.900, 112.619, 460.947, 0),
(@WP_ID, 8, 1431.800, 280.946, 455.675, 0),
(@WP_ID, 9, 1487.210, 477.085, 453.804, 0),
(@WP_ID, 10, 1476.230, 656.958, 444.296, 0),
(@WP_ID, 11, 1381.580, 826.212, 460.069, 0),
(@WP_ID, 12, 1217.520, 948.648, 463.607, 0),
(@WP_ID, 13, 1026.070, 983.015, 446.925, 0),
(@WP_ID, 14, 877.249, 963.587, 443.241, 0),
(@WP_ID, 15, 699.809, 841.261, 451.909, 0),
(@WP_ID, 16, 599.555, 681.812, 452.580, 0);

UPDATE `creature_template` SET `HoverHeight`=10 WHERE `entry`=50061;

-- Xariona
SET @ENTRY := 50061;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,93553,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Twilight Zone"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,14650,14650,14650,14650,11,93544,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Breath"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,20000,20000,20000,20000,11,93556,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Unleashed Magic"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,22500,22500,22500,22500,11,93546,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Fissure"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,25500,25500,25500,25500,11,93553,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Zone");