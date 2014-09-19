UPDATE `creature_template` SET `Health_mod`=20 WHERE `entry`=33944;

DELETE FROM `conditions` WHERE `SourceEntry` = '39429';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 7, 39429, 0, 0, 31, 0, 3, 33912, 0, 0, 0, '', 'Targeting -> Raging Ancient'),
(13, 7, 39429, 0, 1, 31, 0, 3, 33945, 0, 0, 0, '', 'Targeting -> Assaliant'),
(13, 7, 39429, 0, 2, 31, 0, 3, 33945, 0, 0, 0, '', 'Targeting -> Bowman');

-- Felfire Projectile Bunny
SET @ENTRY := 33965;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,39429,16,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Fel Flamestrike");

-- Ashenvale Bowman
SET @ENTRY := 33914;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,33965,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Death - Give Credit"),
(@ENTRY,@SOURCETYPE,1,2,8,0,100,0,39429,4,0,0,33,33965,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Give Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Die");


-- Raging Ancient
SET @ENTRY := 33912;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,33969,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Death - Give Credit"),
(@ENTRY,@SOURCETYPE,1,2,8,0,100,0,39429,4,0,0,33,33969,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Give Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Die");

-- Ashenvale Assailant
SET @ENTRY := 33945;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,33965,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Death - Give Credit"),
(@ENTRY,@SOURCETYPE,1,2,8,0,100,0,39429,4,0,0,33,33965,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Give Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Die");

-- Splintertree Guard
SET @ENTRY := 33944;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,9,0,100,100,0.0,0.0,0.0,0.0,"OOC - Attack");

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=33944;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=33944;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85 WHERE `entry`=33965;
UPDATE `quest_template` SET `SpecialFlags`=0 WHERE `Id`=14046;

DELETE FROM `conditions` WHERE `SourceGroup`=10567 AND `SourceEntry` = '1';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10567, 1, 0, 0, 9, 0, 14046, 0, 0, 0, 0, 0, '', 'Baron - Show gossip only if quest 14046 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=10567 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10567, 0, 0, 0, 9, 0, 14046, 0, 0, 0, 0, 0, '', 'Baron - Show gossip only if quest 14046 is active');

-- Baron Longshore
SET @ENTRY := 3467;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,10000,10000,11,77531,32,0,0,0,0,10,149448,34527,0,0.0,0.0,0.0,0.0,"Add Chains on Update"),
(@ENTRY,@SOURCETYPE,1,4,62,0,100,0,10567,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,3,62,0,100,0,10567,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,5,61,0,100,0,0,0,0,0,11,66176,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Break Manacles"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,0,0,0,0,33,34769,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,0,0,0,0,28,77531,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Chains"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,15,14046,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-66 WHERE `item`=5030;
UPDATE `creature_template` SET `mindmg`=12, `maxdmg`=18, `attackpower`=4, `dmg_multiplier`=1.3, `baseattacktime`=1500, `rangeattacktime`=1500 WHERE `entry`=34635;
UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=33374;

-- Zoram'gar Lighthouse Bunny
SET @ENTRY := 34329;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,65203,1,0,0,33,34329,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Complete"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,75,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Aura");

UPDATE `creature_template` SET `scale`=5, `flags_extra`=128 WHERE `entry`=34329;

SET @CGUID := 798786;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+79;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 3566, 1, 1, 1, 1056, 0, -1276.74, -543.93, -60.1814, 0.660981, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+1, 3566, 1, 1, 1, 1056, 0, -1386.49, -248.538, 2.79417, 1.48279, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+2, 3566, 1, 1, 1, 1056, 0, -1281.42, -692.702, -58.7135, 5.22356, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+3, 3566, 1, 1, 1, 1056, 0, -1341.67, -691.666, -49.1358, 5.48369, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+4, 3566, 1, 1, 1, 1056, 0, -1356.5, -620.909, -59.235, 2.98328, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+5, 3566, 1, 1, 1, 1056, 0, -1118.59, -978.059, 3.24179, 2.248, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+6, 3566, 1, 1, 1, 1056, 0, -1244.34, -923.591, -1.92605, 2.3608, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+7, 3566, 1, 1, 1, 1056, 0, -1139.32, -884.648, -9.78494, 0.238772, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+8, 3566, 1, 1, 1, 1056, 0, -1215.58, -549.846, -56.969, 1.13076, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+9, 3566, 1, 1, 1, 1056, 0, -581.349, -175.54, 15.5478, 1.71186, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+10, 3566, 1, 1, 1, 1056, 0, -628.059, -254.797, 2.12966, 3.54932, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+11, 3566, 1, 1, 1, 1056, 0, -1249.21, -987.188, -1.59793, 4.11099, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+12, 3566, 1, 1, 1, 1056, 0, -914.479, 139.68, -0.00382233, 5.52406, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+13, 3566, 1, 1, 1, 1056, 0, -682.097, -145.717, -13.8458, 0.24261, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+14, 3566, 1, 1, 1, 1056, 0, -758.033, -612.645, -26.3057, 2.37472, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+15, 3566, 1, 1, 1, 1056, 0, -668.477, -270.782, -15.5693, 3.28456, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+16, 3566, 1, 1, 1, 1056, 0, -580.948, -317.661, 22.941, 5.17142, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+17, 3566, 1, 1, 1, 1056, 0, -1184.87, -786.35, -40.2101, 3.96744, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+18, 3566, 1, 1, 1, 1056, 0, -1306.21, -783.603, -26.5207, 5.52142, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+19, 3566, 1, 1, 1, 1056, 0, -1182.25, -644.985, -58.0467, 1.74634, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+20, 3566, 1, 1, 1, 1056, 0, -1127.24, -1113.71, 29.5643, 5.15681, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+21, 3566, 1, 1, 1, 1056, 0, -710.628, -450.326, -20.9022, 0.436441, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+22, 3566, 1, 1, 1, 1056, 0, -649.011, -449.997, -9.04463, 5.88589, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+23, 3566, 1, 1, 1, 1056, 0, -616.392, -481.759, 5.49199, 3.88006, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+24, 3566, 1, 1, 1, 1056, 0, -1048.79, -916.886, 0.820722, 1.10809, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+25, 3566, 1, 1, 1, 1056, 0, -1109.19, -1062.96, 15.4895, 2.7073, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+26, 3566, 1, 1, 1, 1056, 0, -713.764, -376.98, -25.1077, 0.724721, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+27, 3566, 1, 1, 1, 1056, 0, -950.8, -355.987, -18.0665, 4.55366, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+28, 3566, 1, 1, 1, 1056, 0, -1216.13, -280.664, -1.42625, 1.14949, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+29, 3566, 1, 1, 1, 1056, 0, -1083.21, -755.951, -42.2909, 4.69286, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+30, 3566, 1, 1, 1, 1056, 0, -1315.1, -249.343, -5.95113, 3.82334, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+31, 3566, 1, 1, 1, 1056, 0, -1252.09, -318.24, -24.7104, 2.40533, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+32, 3566, 1, 1, 1, 1056, 0, -685.405, -219.026, -18.9409, 1.32257, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+33, 3566, 1, 1, 1, 1056, 0, -752.926, -322.174, -28.8847, 1.54714, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+34, 3566, 1, 1, 1, 1056, 0, -1053.35, -851.917, -9.89027, 5.28663, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+35, 3566, 1, 1, 1, 1056, 0, -1238.92, -586.402, -56.1463, 2.66674, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+36, 3566, 1, 1, 1, 1056, 0, -1224.89, -408.427, -38.0967, 1.92591, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+37, 3566, 1, 1, 1, 1056, 0, -953.165, -424.083, -37.2708, 4.6479, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+38, 3566, 1, 1, 1, 1056, 0, -1045.73, -650.487, -53.6133, 0.500254, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+39, 3566, 1, 1, 1, 1056, 0, -978.582, -719.308, -34.4727, 4.85483, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+40, 3566, 1, 1, 1, 1056, 0, -1222.67, -816.615, -28.6557, 3.36445, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+41, 3566, 1, 1, 1, 1056, 0, -1085.51, -816.311, -24.4134, 2.21078, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+42, 3566, 1, 1, 1, 1056, 0, -886.649, -613.984, -49.0932, 3.63797, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+43, 3566, 1, 1, 1, 1056, 0, -919.67, -653.042, -49.5714, 3.89133, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+44, 3566, 1, 1, 1, 1056, 0, -1036.85, -559.847, -55.8101, 1.14138, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+45, 3566, 1, 1, 1, 1056, 0, -1117, -515.633, -51.2172, 0.534146, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+46, 3566, 1, 1, 1, 1056, 0, -1120.22, -575.484, -55.0745, 1.93169, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+47, 3566, 1, 1, 1, 1056, 0, -920.683, -851.316, 3.99514, 3.12792, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+48, 3566, 1, 1, 1, 1056, 0, -874.961, -491.525, -32.9748, 5.29879, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+49, 3566, 1, 1, 1, 1056, 0, -920.797, 379.187, 16.8308, 1.97415, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+50, 3566, 1, 1, 1, 1056, 0, -890.508, 260.736, 25.9085, 5.37171, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+51, 3566, 1, 1, 1, 1056, 0, -825.393, -224.329, -10.4668, 0.301489, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+52, 3566, 1, 1, 1, 1056, 0, -843.05, -183.67, -11.3679, 6.22817, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+53, 3566, 1, 1, 1, 1056, 0, -718.644, -587.795, -19.1825, 3.16218, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+54, 3566, 1, 1, 1, 1056, 0, -849.725, -709.864, -22.5618, 2.065, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+55, 3566, 1, 1, 1, 1056, 0, -967.312, -561.079, -56.1017, -1.35209, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+56, 3566, 1, 1, 1, 1056, 0, -1081.66, -420.898, -21.5246, 4.54958, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+57, 3566, 1, 1, 1, 1056, 0, -1127.38, -1113.79, 29.4669, 1.91723, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+58, 3566, 1, 1, 1, 1056, 0, -1182.85, -320.235, -0.0876244, 5.18962, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+59, 3566, 1, 1, 1, 1056, 0, -757.46, -616.966, -25.6807, 2.96488, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+60, 3566, 1, 1, 1, 1056, 0, -719.869, -453.819, -22.8884, 3.67866, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+61, 3566, 1, 1, 1, 1056, 0, -1049.94, -583.291, -58.0285, 5.19614, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+62, 3566, 1, 1, 1, 1056, 0, -882.714, -484.051, -35.0268, 5.53235, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+63, 3566, 1, 1, 1, 1056, 0, -1118.61, -589.585, -53.5747, 2.97291, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+64, 3566, 1, 1, 1, 1056, 0, -954.667, -410.33, -32.429, 2.79028, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+65, 3566, 1, 1, 1, 1056, 0, -950.502, -352.533, -17.3891, 5.06663, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+66, 3566, 1, 1, 1, 1056, 0, -964.657, -538.392, -55.9527, 2.94309, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+67, 3566, 1, 1, 1, 1056, 0, -724.153, -447.027, -23.9212, 3.88558, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+68, 3566, 1, 1, 1, 1056, 0, -893.126, -492.347, -35.2248, 5.75212, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+69, 3566, 1, 1, 1, 1056, 0, -763.085, -328.477, -28.2222, 3.65773, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+70, 3566, 1, 1, 1, 1056, 0, -802.794, -681.454, -23.8536, 1.61179, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+71, 3566, 1, 1, 1, 1056, 0, -753.485, -321.683, -28.9636, 2.82507, 300, 0, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+72, 3566, 1, 1, 1, 1056, 0, -873.417, -479.523, -34.9747, 0.54359, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+73, 3566, 1, 1, 1, 1056, 0, -711.938, -449.418, -21.1522, 3.25505, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+74, 3566, 1, 1, 1, 1056, 0, -948.589, -886.139, 5.68907, 0.615813, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+75, 3566, 1, 1, 1, 1056, 0, -1113.53, -1056.84, 13.0334, 2.28652, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+76, 3566, 1, 1, 1, 1056, 0, -949.159, -351.965, -17.6391, 6.05312, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+77, 3566, 1, 1, 1, 1056, 0, -1160.85, -212.877, 38.4744, 5.37035, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+78, 3566, 1, 1, 1, 1056, 0, -1066.7, -170.236, 54.374, 0.940565, 300, 3, 0, 176, 100, 0, 0, 0, 0),
(@CGUID+79, 3566, 1, 1, 1, 1056, 0, -1080.19, -413.442, -17.3996, 4.3131, 300, 3, 0, 176, 100, 0, 0, 0, 0);

UPDATE `creature` SET `MovementType`=1 WHERE `id`= '3566' AND `spawndist` > '0';
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85 WHERE `entry`=34433;