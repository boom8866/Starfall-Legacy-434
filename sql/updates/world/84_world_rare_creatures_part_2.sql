-- Marina DeSirrus
SET @ENTRY := 45811;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,6595,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Exploit Weakness"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,10000,10000,11,6595,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Exploit Weakness"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,7000,7000,12500,12500,11,78509,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Torch Toss");

-- Mahamba
SET @ENTRY := 51662;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,7000,12500,11,78542,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Splash"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,14000,14000,11,79831,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wave Crash");

-- Marus
SET @ENTRY := 45771;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,80576,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shadowstep"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,12000,12000,15000,15000,11,80576,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadowstep"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,8000,8000,12000,12000,11,81173,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frenzy"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,15000,15000,15000,15000,11,79853,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Evasion");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=773723;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=774738;

-- Mogh the Dead
SET @ENTRY := 51658;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,6000,6000,11,12471,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,4000,15000,15000,11,17173,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Drain Life");

UPDATE `creature_template` SET `lootid`=45257 WHERE `entry`=45257;
UPDATE `creature_template` SET `lootid`=43488 WHERE `entry`=43488;

-- Mordak Nightbender
SET @ENTRY := 45257;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,11,79934,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Demon Armor"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79930,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corruption"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3500,3500,6500,8000,11,84533,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Drain Life"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,5000,5000,12500,12500,11,77722,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Void Whip");

DELETE FROM `creature_loot_template` WHERE `entry` IN (43488, 45257);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(43488, 3185, 0.0399, 1, 0, 1, 1),
(43488, 9395, 0.0399, 1, 0, 1, 1),
(43488, 11164, 0.0399, 1, 0, 1, 1),
(43488, 12029, 0.0399, 1, 0, 1, 1),
(43488, 14200, 0.0399, 1, 0, 1, 1),
(43488, 14211, 0.0399, 1, 0, 1, 1),
(43488, 14218, 0.0399, 1, 0, 1, 1),
(43488, 14414, 0.0399, 1, 0, 1, 1),
(43488, 14589, 0.0399, 1, 0, 1, 1),
(43488, 14590, 0.0399, 1, 0, 1, 1),
(43488, 14595, 0.0399, 1, 0, 1, 1),
(43488, 14761, 0.0399, 1, 0, 1, 1),
(43488, 15130, 0.0399, 1, 0, 1, 1),
(43488, 15140, 0.0399, 1, 0, 1, 1),
(43488, 15154, 0.0399, 1, 0, 1, 1),
(43488, 15286, 0.0399, 1, 0, 1, 1),
(43488, 15352, 0.0399, 1, 0, 1, 1),
(43488, 15550, 0.0399, 1, 0, 1, 1),
(43488, 15573, 0.0399, 1, 0, 1, 1),
(45257, 11225, 0.0443, 1, 0, 1, 1),
(45257, 11736, 0.0443, 1, 0, 1, 1),
(45257, 15218, 0.0443, 1, 0, 1, 1),
(45257, 15237, 0.0443, 1, 0, 1, 1),
(45257, 15254, 0.0443, 1, 0, 1, 1),
(45257, 15264, 0.0443, 1, 0, 1, 1),
(45257, 15271, 0.0443, 1, 0, 1, 1),
(45257, 15742, 0.0443, 1, 0, 1, 1),
(45257, 19260, 0.0443, 1, 0, 1, 1),
(43488, 1990, 0.0797, 1, 0, 1, 1),
(43488, 14203, 0.0797, 1, 0, 1, 1),
(43488, 14764, 0.0797, 1, 0, 1, 1),
(43488, 15551, 0.0797, 1, 0, 1, 1),
(43488, 15562, 0.0797, 1, 0, 1, 1),
(43488, 15566, 0.0797, 1, 0, 1, 1),
(43488, 15590, 0.0797, 1, 0, 1, 1),
(45257, 3997, 0.0887, 1, 0, 1, 1),
(43488, 3385, 0.1, 1, 0, 1, 1),
(43488, 3800, 0.1, 1, 0, 1, 1),
(43488, 3804, 0.1, 1, 0, 1, 1),
(43488, 8746, 0.1, 1, 0, 1, 1),
(45257, 3971, 0.133, 1, 0, 1, 1),
(45257, 15295, 0.133, 1, 0, 1, 1),
(43488, 7456, 0.1595, 1, 0, 1, 1),
(45257, 8081, 0.1595, 1, 0, 1, 1),
(45257, 8085, 0.1595, 1, 0, 1, 1),
(45257, 10213, 0.1774, 1, 0, 1, 1),
(45257, 10237, 0.1774, 1, 0, 1, 1),
(43488, 3794, 0.1859, 1, 0, 1, 1),
(43488, 1725, 0.2, 1, 0, 1, 1),
(45257, 3987, 0.2217, 1, 0, 1, 1),
(45257, 10181, 0.2217, 1, 0, 1, 1),
(45257, 10216, 0.2217, 1, 0, 1, 1),
(45257, 10281, 0.2217, 1, 0, 1, 1),
(43488, 9866, 0.2392, 1, 0, 1, 1),
(45257, 10223, 0.2661, 1, 0, 1, 1),
(45257, 13819, 0.2661, 1, 0, 1, 1),
(43488, 3783, 0.3, 1, 0, 1, 1),
(43488, 3817, 0.3, 1, 0, 1, 1),
(45257, 10182, 0.3104, 1, 0, 1, 1),
(43488, 7445, 0.319, 1, 0, 1, 1),
(45257, 13823, 0.319, 1, 0, 1, 1),
(45257, 10148, 0.3548, 1, 0, 1, 1),
(43488, 3785, 0.3589, 1, 0, 1, 1),
(43488, 7441, 0.3589, 1, 0, 1, 1),
(43488, 7459, 0.3589, 1, 0, 1, 1),
(43488, 9844, 0.3589, 1, 0, 1, 1),
(43488, 9890, 0.3589, 1, 0, 1, 1),
(43488, 7432, 0.3987, 1, 0, 1, 1),
(45257, 10112, 0.3991, 1, 0, 1, 1),
(45257, 10118, 0.3991, 1, 0, 1, 1),
(45257, 10164, 0.3991, 1, 0, 1, 1),
(45257, 10232, 0.3991, 1, 0, 1, 1),
(45257, 10234, 0.3991, 1, 0, 1, 1),
(45257, 10101, 0.4435, 1, 0, 1, 1),
(45257, 10279, 0.4878, 1, 0, 1, 1),
(45257, 5758, 0.5, 1, 0, 1, 1),
(45257, 13443, 0.5, 1, 0, 1, 1),
(45257, 10169, 0.5322, 1, 0, 1, 1),
(45257, 10212, 0.5322, 1, 0, 1, 1),
(43488, 7435, 0.5582, 1, 0, 1, 1),
(43488, 7462, 0.5582, 1, 0, 1, 1),
(43488, 9851, 0.5582, 1, 0, 1, 1),
(43488, 9854, 0.5981, 1, 0, 1, 1),
(45257, 10100, 0.6208, 1, 0, 1, 1),
(45257, 10277, 0.6652, 1, 0, 1, 1),
(43488, 9870, 0.6778, 1, 0, 1, 1),
(43488, 9852, 0.7177, 1, 0, 1, 1),
(43488, 9871, 0.7177, 1, 0, 1, 1),
(43488, 9898, 0.7177, 1, 0, 1, 1),
(45257, 10097, 0.7539, 1, 0, 1, 1),
(45257, 10119, 0.7539, 1, 0, 1, 1),
(45257, 10221, 0.7539, 1, 0, 1, 1),
(43488, 9863, 0.7576, 1, 0, 1, 1),
(43488, 9872, 0.7576, 1, 0, 1, 1),
(43488, 7433, 0.7974, 1, 0, 1, 1),
(43488, 7457, 0.7974, 1, 0, 1, 1),
(43488, 9848, 0.7974, 1, 0, 1, 1),
(45257, 10224, 0.8426, 1, 0, 1, 1),
(43488, 7434, 0.8772, 1, 0, 1, 1),
(43488, 7461, 0.8772, 1, 0, 1, 1),
(45257, 10124, 0.8869, 1, 0, 1, 1),
(45257, 10179, 0.8869, 1, 0, 1, 1),
(45257, 10111, 0.9313, 1, 0, 1, 1),
(43488, 9877, 0.9569, 1, 0, 1, 1),
(43488, 7458, 0.9968, 1, 0, 1, 1),
(43488, 9849, 0.9968, 1, 0, 1, 1),
(45257, 10113, 1.02, 1, 0, 1, 1),
(43488, 9864, 1.0367, 1, 0, 1, 1),
(43488, 7447, 1.0766, 1, 0, 1, 1),
(43488, 9856, 1.0766, 1, 0, 1, 1),
(43488, 9862, 1.0766, 1, 0, 1, 1),
(45257, 10170, 1.153, 1, 0, 1, 1),
(43488, 9850, 1.1563, 1, 0, 1, 1),
(43488, 9859, 1.1962, 1, 0, 1, 1),
(43488, 7443, 1.236, 1, 0, 1, 1),
(45257, 10188, 1.2417, 1, 0, 1, 1),
(45257, 10177, 1.286, 1, 0, 1, 1),
(45257, 10103, 1.3304, 1, 0, 1, 1),
(45257, 10109, 1.3747, 1, 0, 1, 1),
(45257, 10183, 1.3747, 1, 0, 1, 1),
(43488, 7368, 1.4354, 1, 0, 1, 1),
(43488, 7460, 1.4354, 1, 0, 1, 1),
(45257, 10282, 1.4634, 1, 0, 1, 1),
(45257, 10106, 1.5078, 1, 0, 1, 1),
(43488, 7438, 1.5152, 1, 0, 1, 1),
(43488, 7444, 1.5152, 1, 0, 1, 1),
(43488, 7437, 1.555, 1, 0, 1, 1),
(43488, 9819, 1.5949, 1, 0, 1, 1),
(45257, 10107, 1.5965, 1, 0, 1, 1),
(45257, 10166, 1.5965, 1, 0, 1, 1),
(43488, 7423, 1.6348, 1, 0, 1, 1),
(43488, 9826, 1.6746, 1, 0, 1, 1),
(43488, 9857, 1.6746, 1, 0, 1, 1),
(45257, 10121, 1.6851, 1, 0, 1, 1),
(45257, 10171, 1.6851, 1, 0, 1, 1),
(45257, 10231, 1.6851, 1, 0, 1, 1),
(45257, 10276, 1.6851, 1, 0, 1, 1),
(43488, 7417, 1.7145, 1, 0, 1, 1),
(45257, 10199, 1.7295, 1, 0, 1, 1),
(45257, 10233, 1.7295, 1, 0, 1, 1),
(43488, 7446, 1.7544, 1, 0, 1, 1),
(45257, 10168, 1.7738, 1, 0, 1, 1),
(45257, 10125, 1.8182, 1, 0, 1, 1),
(45257, 10095, 1.8625, 1, 0, 1, 1),
(45257, 10126, 1.8625, 1, 0, 1, 1),
(45257, 10175, 1.8625, 1, 0, 1, 1),
(43488, 1708, 1.9, 1, 0, 1, 1),
(43488, 7448, 1.9936, 1, 0, 1, 1),
(43488, 8705, 2, 1, 0, 1, 1),
(45257, 10229, 2.0399, 1, 0, 1, 1),
(45257, 8766, 2.1, 1, 0, 1, 1),
(45257, 10096, 2.1286, 1, 0, 1, 1),
(45257, 10128, 2.1286, 1, 0, 1, 1),
(45257, 10244, 2.1286, 1, 0, 1, 1),
(45257, 10165, 2.2616, 1, 0, 1, 1),
(45257, 10193, 2.2616, 1, 0, 1, 1),
(45257, 10278, 2.2616, 1, 0, 1, 1),
(45257, 10123, 2.3503, 1, 0, 1, 1),
(43488, 9855, 2.4721, 1, 0, 1, 1),
(43488, 9853, 2.512, 1, 0, 1, 1),
(43488, 9860, 2.512, 1, 0, 1, 1),
(45257, 10172, 2.6164, 1, 0, 1, 1),
(43488, 9865, 2.6715, 1, 0, 1, 1),
(45257, 10057, 2.7051, 1, 0, 1, 1),
(45257, 10070, 2.7494, 1, 0, 1, 1),
(43488, 7414, 2.9107, 1, 0, 1, 1),
(45257, 10099, 2.9268, 1, 0, 1, 1),
(45257, 10189, 3.1042, 1, 0, 1, 1),
(43488, 9868, 3.1499, 1, 0, 1, 1),
(43488, 7357, 3.1898, 1, 0, 1, 1),
(43488, 9846, 3.1898, 1, 0, 1, 1),
(45257, 10187, 3.1929, 1, 0, 1, 1),
(43488, 9869, 3.2695, 1, 0, 1, 1),
(45257, 10110, 3.3259, 1, 0, 1, 1),
(45257, 10122, 3.3703, 1, 0, 1, 1),
(43488, 7353, 3.4689, 1, 0, 1, 1),
(45257, 10176, 3.5477, 1, 0, 1, 1),
(43488, 9845, 3.6683, 1, 0, 1, 1),
(43488, 2592, 3.7, 1, 0, 1, 3),
(45257, 10240, 3.8137, 1, 0, 1, 1),
(43488, 7407, 3.8278, 1, 0, 1, 1),
(43488, 7369, 3.9474, 1, 0, 1, 1),
(43488, 7436, 3.9872, 1, 0, 1, 1),
(45257, 10167, 4.1242, 1, 0, 1, 1),
(45257, 8952, 5.0111, 1, 0, 1, 1),
(43488, 3771, 5.3828, 1, 0, 1, 1),
(43488, 9861, 5.4226, 1, 0, 1, 1),
(43488, 7418, 6.1802, 1, 0, 1, 1),
(45257, 14047, 22.2, 1, 0, 1, 2),
(43488, 4306, 26.9, 1, 0, 1, 2);

UPDATE `creature_template` SET `faction`=90, `DamageModifier`=7.8 WHERE `entry`=45257;

DELETE FROM `creature` WHERE `guid` = '842900';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842900, 45257, 0, 1, 1, 0, 1, -11304.9, -3408.13, 7.46824, 2.07226, 28800, 0, 0, 2745, 10026, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `guid` = '842901';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842901, 54319, 1, 1, 1, 0, 0, 4731.11, -2072.63, 1223.67, 4.79323, 28800, 0, 0, 232470, 0, 2, 0, 0, 0);

-- Adds Waypoint Movement to Magria (guid: 842901, entry: 54319)
SET @GUID  := 842901;
SET @WP_ID := 8429010;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 842901;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(842901, 8429010, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, 4731.920, -2098.060, 1217.410, 0),
(@WP_ID, 2, 4723.360, -2152.860, 1203.360, 0),
(@WP_ID, 3, 4724.520, -2179.510, 1196.410, 0),
(@WP_ID, 4, 4731.660, -2191.370, 1197.750, 0),
(@WP_ID, 5, 4732.700, -2211.780, 1194.930, 0),
(@WP_ID, 6, 4731.960, -2230.190, 1190.080, 0),
(@WP_ID, 7, 4730.930, -2245.540, 1187.080, 0),
(@WP_ID, 8, 4730.070, -2261.780, 1185.840, 0),
(@WP_ID, 9, 4727.720, -2279.120, 1184.020, 0),
(@WP_ID, 10, 4733.680, -2295.820, 1186.690, 0),
(@WP_ID, 11, 4735.350, -2307.680, 1187.350, 0),
(@WP_ID, 12, 4727.900, -2321.160, 1184.520, 0),
(@WP_ID, 13, 4718.300, -2332.110, 1179.160, 0),
(@WP_ID, 14, 4703.250, -2346.760, 1172.790, 0),
(@WP_ID, 15, 4705.710, -2364.540, 1170.210, 0);

-- Magria
SET @ENTRY := 54319;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,53148,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Charge"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,8000,6000,10000,11,101631,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Spirit Claw");

UPDATE `creature_template` SET `lootid`=54319 WHERE `entry`=54319;
DELETE FROM `creature_loot_template` WHERE `entry` = '54319';
INSERT INTO `creature_loot_template` (`entry`, `item`) VALUES
(54319, 68055);

-- Morick Darkbrew
SET @ENTRY := 45369;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,6000,16000,16000,11,37591,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Drunken Haze"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,80576,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shadowstep"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4500,6500,4500,6500,11,13340,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire Blast"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,18000,18000,18000,18000,11,80576,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadowstep");

-- Nix
SET @ENTRY := 45402;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,9000,9000,11,11918,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Poison"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,15000,15000,11,84872,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fatal Sting");

-- Narixxus the Doombringer
SET @ENTRY := 45262;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,6000,6000,12000,11,36255,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Chaos Nova");

DELETE FROM `creature` WHERE `guid` = '842902';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842902, 45262, 0, 1, 1, 0, 0, -11666, -2371.89, 0.550016, 3.68703, 28800, 0, 0, 6104, 0, 0, 0, 0, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=736588;

-- Occulus the Corrupted
SET @ENTRY := 44767;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,31458,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Hasten"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,7000,5500,9500,11,31464,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mortal Wound"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,6000,12500,14500,11,32914,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wing Buffet");

UPDATE `creature_template` SET `lootid`=50085 WHERE `entry`=50085;

DELETE FROM `creature_loot_template` WHERE `entry` = '50085';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(50085, 67244, 100, 1, 0, 1, 1);

UPDATE `creature` SET `spawntimesecs`=28800 WHERE `guid`=216887;

-- Pogeyan
SET @ENTRY := 51663;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4000,7000,14000,11,75002,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Leaping Rush");

-- Scorpitar
SET @ENTRY := 39183;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79840,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Harden"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,10000,10000,20000,20000,11,79443,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sand Step"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,5000,6000,6000,11,79607,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Venom Splash");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=736470;

-- Whitefin
SET @ENTRY := 45401;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4500,4500,6500,9500,11,32011,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Bolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,10000,10000,10000,10000,11,79831,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wave Crash"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,14000,14000,14000,14000,11,78542,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Splash");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=763311;