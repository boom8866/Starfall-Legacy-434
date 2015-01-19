UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (43720, 44759, 44761, 45801, 44227);

-- Ankha
SET @ENTRY := 54318;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,54318,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Charge"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,4500,5000,11,101631,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Spirit Claw");

-- Anthriss
SET @ENTRY := 54338;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,11,101413,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Searing Webs");

-- Armagedillo
SET @ENTRY := 50065;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,1000,5000,15000,11,93598,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Armagedillo - Spiked Charge"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,12000,9000,15000,11,93592,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Armagedillo - Dillogeddon"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,8000,6000,10000,11,93590,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Armagedillo - Flame Breath");

-- Ban'thalos
SET @ENTRY := 54320;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,53148,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Charge"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,8000,18000,18000,11,101632,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Harsh Moonlight");

UPDATE `creature` SET `phaseMask`=2049, `spawndist`=22, `MovementType`=1 WHERE `guid`=731440;

-- Ashtail
SET @ENTRY := 45380;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,80576,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shadowstep"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,20000,20000,11,78826,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Evasion"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,5000,5000,5000,11,0,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Vanish");

UPDATE `creature` SET `phaseMask`=1, `spawndist`=22, `MovementType`=1 WHERE `guid`=762631;
UPDATE `creature` SET `phaseMask`=2049, `spawndist`=22, `MovementType`=1 WHERE `guid`=730911;

UPDATE `creature_template` SET `lootid`=50057 WHERE `entry`=50057;
DELETE FROM `creature_loot_template` WHERE `entry` = '50057';
INSERT INTO `creature_loot_template` (`entry`, `item`) VALUES
(50057, 67236);

-- Blazewing
SET @ENTRY := 50057;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,93515,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Charge on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4400,5500,22400,31500,11,93514,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Melt Armor"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,7700,9100,12300,13100,11,93513,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Flame Buffet");

UPDATE `creature` SET `phaseMask`=1, `spawndist`=22, `MovementType`=1 WHERE `guid`=750014;

-- Burgy Blackheart
SET @ENTRY := 50052;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,20000,20000,11,79414,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Brittle Touch"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,5000,5000,11,75361,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Slice");

-- Carved One
SET @ENTRY := 45785;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,10000,10000,11,78472,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Breath"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,85253,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Rotten Stench"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,5000,5000,5000,11,85253,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Rotten Stench");

UPDATE `creature` SET `phaseMask`=1, `spawndist`=22, `MovementType`=1 WHERE `guid`=772589;

DELETE FROM `creature` WHERE `guid` = '842899';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842899, 45258, 0, 1, 1, 0, 1, -12416.2, -3417.23, 22.2117, 2.43511, 28800, 0, 0, 3015, 5461, 0, 0, 0, 0);

UPDATE `creature_template` SET `lootid`=45258 WHERE `entry`=45258;

DELETE FROM `creature_loot_template` WHERE `entry` = '45258';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(45258, 647, 0.0371, 1, 0, 1, 1),
(45258, 3944, 0.1856, 1, 0, 1, 1),
(45258, 3948, 0.5939, 1, 0, 1, 1),
(45258, 3970, 0.1233, 1, 0, 1, 1),
(45258, 3972, 0.1114, 1, 0, 1, 1),
(45258, 3976, 0.1114, 1, 0, 1, 1),
(45258, 3992, 1.233, 1, 0, 1, 1),
(45258, 3996, 0.1233, 1, 0, 1, 1),
(45258, 3997, 0.1233, 1, 0, 1, 1),
(45258, 3998, 0.0742, 1, 0, 1, 1),
(45258, 4500, 0.2, 1, 0, 1, 1),
(45258, 5759, 0.2227, 1, 0, 1, 1),
(45258, 7973, 50, 1, 0, 1, 1),
(45258, 8082, 0.1114, 1, 0, 1, 1),
(45258, 8084, 0.0742, 1, 0, 1, 1),
(45258, 8086, 0.2227, 1, 0, 1, 1),
(45258, 8298, 0.0742, 1, 0, 1, 1),
(45258, 8305, 0.0742, 1, 0, 1, 1),
(45258, 8766, 0.6, 1, 0, 1, 1),
(45258, 8959, 4.2316, 1, 0, 1, 1),
(45258, 10097, 1.8931, 1, 0, 1, 1),
(45258, 10100, 1.7446, 1, 0, 1, 1),
(45258, 10101, 3.9718, 1, 0, 1, 1),
(45258, 10104, 1.0022, 1, 0, 1, 1),
(45258, 10105, 0.8537, 1, 0, 1, 1),
(45258, 10111, 2.487, 1, 0, 1, 1),
(45258, 10112, 2.7097, 1, 0, 1, 1),
(45258, 10113, 2.1529, 1, 0, 1, 1),
(45258, 10118, 3.4892, 1, 0, 1, 1),
(45258, 10119, 1.8931, 1, 0, 1, 1),
(45258, 10123, 2.0416, 1, 0, 1, 1),
(45258, 10124, 3.415, 1, 0, 1, 1),
(45258, 10136, 0.7424, 1, 0, 1, 1),
(45258, 10137, 0.1856, 1, 0, 1, 1),
(45258, 10138, 0.928, 1, 0, 1, 1),
(45258, 10140, 0.4083, 1, 0, 1, 1),
(45258, 10144, 0.5939, 1, 0, 1, 1),
(45258, 10145, 1.7075, 1, 0, 1, 1),
(45258, 10146, 0.3712, 1, 0, 1, 1),
(45258, 10147, 1.0765, 1, 0, 1, 1),
(45258, 10148, 2.4128, 1, 0, 1, 1),
(45258, 10149, 0.2227, 1, 0, 1, 1),
(45258, 10154, 0.3712, 1, 0, 1, 1),
(45258, 10155, 0.5197, 1, 0, 1, 1),
(45258, 10156, 0.5939, 1, 0, 1, 1),
(45258, 10159, 1.0765, 1, 0, 1, 1),
(45258, 10161, 0.3341, 1, 0, 1, 1),
(45258, 10164, 2.5984, 1, 0, 1, 1),
(45258, 10169, 1.7817, 1, 0, 1, 1),
(45258, 10178, 0.0371, 1, 0, 1, 1),
(45258, 10181, 2.0787, 1, 0, 1, 1),
(45258, 10182, 3.3779, 1, 0, 1, 1),
(45258, 10210, 0.5568, 1, 0, 1, 1),
(45258, 10211, 0.8909, 1, 0, 1, 1),
(45258, 10212, 0.8909, 1, 0, 1, 1),
(45258, 10213, 2.3756, 1, 0, 1, 1),
(45258, 10214, 1.3363, 1, 0, 1, 1),
(45258, 10216, 2.0787, 1, 0, 1, 1),
(45258, 10217, 0.4826, 1, 0, 1, 1),
(45258, 10219, 0.3712, 1, 0, 1, 1),
(45258, 10221, 3.9347, 1, 0, 1, 1),
(45258, 10222, 0.8166, 1, 0, 1, 1),
(45258, 10223, 2.2272, 1, 0, 1, 1),
(45258, 10224, 2.4499, 1, 0, 1, 1),
(45258, 10225, 1.8931, 1, 0, 1, 1),
(45258, 10226, 0.4083, 1, 0, 1, 1),
(45258, 10228, 0.6682, 1, 0, 1, 1),
(45258, 10230, 1.2249, 1, 0, 1, 1),
(45258, 10232, 2.0787, 1, 0, 1, 1),
(45258, 10233, 1.4105, 1, 0, 1, 1),
(45258, 10234, 3.2665, 1, 0, 1, 1),
(45258, 10235, 0.8537, 1, 0, 1, 1),
(45258, 10236, 1.3734, 1, 0, 1, 1),
(45258, 10237, 2.0787, 1, 0, 1, 1),
(45258, 10249, 0.5939, 1, 0, 1, 1),
(45258, 10256, 0.4826, 1, 0, 1, 1),
(45258, 10258, 0.631, 1, 0, 1, 1),
(45258, 10267, 0.2227, 1, 0, 1, 1),
(45258, 10275, 0.631, 1, 0, 1, 1),
(45258, 10277, 1.3734, 1, 0, 1, 1),
(45258, 10279, 2.3756, 1, 0, 1, 1),
(45258, 10280, 1.8189, 1, 0, 1, 1),
(45258, 10281, 1.9302, 1, 0, 1, 1),
(45258, 10373, 0.4826, 1, 0, 1, 1),
(45258, 10376, 0.4083, 1, 0, 1, 1),
(45258, 10377, 1.1136, 1, 0, 1, 1),
(45258, 10379, 0.3341, 1, 0, 1, 1),
(45258, 10380, 1.2249, 1, 0, 1, 1),
(45258, 10381, 1.9673, 1, 0, 1, 1),
(45258, 10383, 0.7424, 1, 0, 1, 1),
(45258, 10387, 0.5939, 1, 0, 1, 1),
(45258, 10391, 0.7424, 1, 0, 1, 1),
(45258, 12694, 0.0371, 1, 0, 1, 1),
(45258, 12697, 0.0371, 1, 0, 1, 1),
(45258, 13047, 0.0371, 1, 0, 1, 1),
(45258, 13072, 0.0371, 1, 0, 1, 1),
(45258, 13135, 0.0371, 1, 0, 1, 1),
(45258, 13444, 0.6, 1, 0, 1, 1),
(45258, 13446, 1.4, 1, 0, 1, 1),
(45258, 13816, 0.2, 1, 0, 1, 1),
(45258, 13820, 0.2, 1, 0, 1, 1),
(45258, 14047, 34.9, 1, 0, 1, 3),
(45258, 15239, 0.0371, 1, 0, 1, 1),
(45258, 15255, 0.0371, 1, 0, 1, 1),
(45258, 15256, 0.0371, 1, 0, 1, 1),
(45258, 15265, 0.1114, 1, 0, 1, 1),
(45258, 15266, 0.0371, 1, 0, 1, 1),
(45258, 15281, 0.0371, 1, 0, 1, 1),
(45258, 15755, 0.0371, 1, 0, 1, 1),
(45258, 16251, 0.0371, 1, 0, 1, 1),
(45258, 19232, 0.0371, 1, 0, 1, 1),
(45258, 19260, 0.0371, 1, 0, 1, 1),
(45258, 19261, 0.0371, 1, 0, 1, 1),
(45258, 19270, 0.1485, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=740461;
UPDATE `creature_template` SET `lootid`=50064 WHERE `entry`=50064;

DELETE FROM `creature_loot_template` WHERE `entry` = '50064';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50064, 67242, 100, 1, 0, 1, 1);

UPDATE `creature_template` SET `DamageModifier`=17 WHERE `entry`=54322;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=734941;

-- Golgarok
SET @ENTRY := 50059;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,86699,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shockwave"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,12500,12500,11,80117,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Earth Spike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,8000,8000,16500,18500,11,86861,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Earthquake");

UPDATE `creature_template` SET `lootid`=50059 WHERE `entry`=50059;

DELETE FROM `creature_loot_template` WHERE `entry` = '50059';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50059, 67237, 100, 1, 0, 1, 1);

UPDATE `creature` SET `spawntimesecs`=28800 WHERE `guid`=742586;

-- Jadefang
SET @ENTRY := 49822;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,16000,16000,11,86571,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shale Flurry");

-- Karoma
SET @ENTRY := 50138;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,3149,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Furious Howl"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,12500,12500,11,75002,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Leaping Rush");

-- Kirix
SET @ENTRY := 54323;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,101319,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Bouncing Charge"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,8000,20000,20000,11,101340,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Suffocating PRey"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,10000,10000,30000,30000,11,101302,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Magmatoxin");

UPDATE `creature_template` SET `lootid`=54323 WHERE `entry`=54323;

DELETE FROM `creature_loot_template` WHERE `entry` = '54323';
INSERT INTO `creature_loot_template` (`entry`, `item`) VALUES
(54323, 68055);

-- Lady La-La
SET @ENTRY := 49913;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,7000,7000,20000,20000,11,92888,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Siren's Song"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,12500,12500,11,92895,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Briny's Romance");

DELETE FROM `creature_loot_template` WHERE `entry` = '49913';
INSERT INTO `creature_loot_template` (`entry`, `item`) VALUES
(49913, 67152);