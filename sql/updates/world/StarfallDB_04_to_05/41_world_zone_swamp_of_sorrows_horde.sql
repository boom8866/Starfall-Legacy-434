UPDATE `quest_template` SET `PrevQuestId`='27852 27853' WHERE `Id` IN (27854, 27855, 27856);
UPDATE `quest_template` SET `PrevQuestId`='27854 27855 27856' WHERE `Id`=27857;
UPDATE `creature_template` SET `mindmg`=83, `maxdmg`=125, `attackpower`=31 WHERE `entry` IN (46487, 46414, 46869, 46870, 47053);
UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (46882, 46775);

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` IN (27854, 27855, 27856);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 5460, 27854, 27854, 1, 10),
(65141, 5460, 27855, 27855, 1, 10),
(65141, 5460, 27856, 27856, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '87292' AND `quest_start` IN (27854, 27855, 27856);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(87292, 5460, 27854, 27854, 1, 10),
(87292, 5460, 27855, 27855, 1, 10),
(87292, 5460, 27856, 27856, 1, 10);

DELETE FROM `spell_script_names` WHERE `spell_id` = '87296';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87296, 'spell_marked_for_retrieval');

SET @CGUID := 400455;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+39;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 46414, 0, 1, 2, 0, 1, -10164.1, -3684.72, 20.9865, 2.14838, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+1, 46414, 0, 1, 2, 0, 1, -10163.7, -3679.02, 21.9022, 2.14838, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+2, 46414, 0, 1, 2, 0, 1, -10169.5, -3682.82, 22.398, 2.14838, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+3, 46414, 0, 1, 2, 0, 1, -10166.8, -3681.05, 22.1177, 2.14838, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+4, 46414, 0, 1, 2, 0, 1, -10168.8, -3678.02, 22.998, 2.14838, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+5, 46414, 0, 1, 2, 0, 1, -10232.7, -3465.99, 24.2205, 1.71225, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+6, 46414, 0, 1, 2, 0, 1, -10229.8, -3460.35, 24.0461, 1.71225, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+7, 46414, 0, 1, 2, 0, 1, -10237.3, -3461.41, 24.008, 1.71225, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+8, 46414, 0, 1, 2, 0, 1, -10233.4, -3460.86, 24.2236, 1.71225, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+9, 46414, 0, 1, 2, 0, 1, -10234.1, -3456.11, 23.3833, 1.71225, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+10, 46414, 0, 1, 2, 0, 1, -10275.3, -3395.54, 20.7519, 3.98275, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+11, 46414, 0, 1, 2, 0, 1, -10282.6, -3397.54, 22.3133, 3.98275, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+12, 46414, 0, 1, 2, 0, 1, -10276.4, -3403.06, 20.976, 3.98275, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+13, 46414, 0, 1, 2, 0, 1, -10279.4, -3400.41, 21.785, 3.98275, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+14, 46414, 0, 1, 2, 0, 1, -10281.9, -3403.26, 22.0395, 3.98275, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+15, 46414, 0, 1, 2, 0, 1, -10288.8, -3454.96, 18.5464, 2.56174, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+16, 46414, 0, 1, 2, 0, 1, -10292.1, -3449.43, 18.7274, 2.56174, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+17, 46414, 0, 1, 2, 0, 1, -10295.6, -3454.8, 20.8832, 2.56174, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+18, 46414, 0, 1, 2, 0, 1, -10293.8, -3452.07, 19.912, 2.56174, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+19, 46414, 0, 1, 2, 0, 1, -10297.2, -3449.9, 20.5783, 2.56174, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+20, 46414, 0, 1, 2, 0, 1, -10269.8, -3505.98, 18.7644, 2.7895, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+21, 46414, 0, 1, 2, 0, 1, -10273.4, -3501.83, 19.2424, 2.7895, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+22, 46414, 0, 1, 2, 0, 1, -10274.4, -3509.75, 21.5179, 2.7895, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+23, 46414, 0, 1, 2, 0, 1, -10273.4, -3506.99, 20.467, 2.7895, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+24, 46414, 0, 1, 2, 0, 1, -10277.2, -3505.59, 21.4047, 2.7895, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+25, 46414, 0, 1, 2, 0, 1, -10208.6, -3577.38, 22.8649, 2.85626, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+26, 46414, 0, 1, 2, 0, 1, -10209.1, -3580.29, 23.0472, 2.86993, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+27, 46414, 0, 1, 2, 0, 1, -10210.4, -3585.15, 23.7335, 2.86993, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+28, 46414, 0, 1, 2, 0, 1, -10208.5, -3582.81, 23.1293, 2.86993, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+29, 46414, 0, 1, 2, 0, 1, -10212.4, -3581.72, 23.7103, 2.86993, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+30, 46414, 0, 1, 2, 0, 1, -10209.8, -3623.9, 23.1485, 2.30837, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+31, 46414, 0, 1, 2, 0, 1, -10211.5, -3617.42, 23.669, 2.30837, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+32, 46414, 0, 1, 2, 0, 1, -10216.6, -3622.11, 23.8989, 2.30837, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+33, 46414, 0, 1, 2, 0, 1, -10213.9, -3619.65, 23.7906, 2.30837, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+34, 46414, 0, 1, 2, 0, 1, -10217.1, -3616.15, 24.4554, 2.30837, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+35, 46414, 0, 1, 2, 0, 1, -10233, -3675.18, 24.6087, 2.24084, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+36, 46414, 0, 1, 2, 0, 1, -10233.5, -3667.93, 24.7946, 2.35334, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+37, 46414, 0, 1, 2, 0, 1, -10239, -3673.45, 24.8239, 2.35334, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+38, 46414, 0, 1, 2, 0, 1, -10236.4, -3670.87, 24.8814, 2.35334, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0),
(@CGUID+39, 46414, 0, 1, 2, 0, 1, -10239.3, -3668.04, 25.3321, 2.35334, 60, 0, 0, 2453, 0, 0, 0, 134217728, 0);

DELETE FROM `creature_formations` WHERE `leaderGUID` IN (400455, 400460, 400465, 400470, 400475, 400480, 400485, 400490);
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`, `point_1`, `point_2`) VALUES
(400455, 400455, 5, 0, 0, 0, 0),
(400455, 400456, 5, 15, 0, 0, 0),
(400455, 400457, 5, 30, 0, 0, 0),
(400455, 400458, 5, 60, 0, 0, 0),
(400455, 400459, 5, 90, 0, 0, 0),
(400460, 400460, 5, 0, 0, 0, 0),
(400460, 400461, 5, 15, 0, 0, 0),
(400460, 400462, 5, 30, 0, 0, 0),
(400460, 400463, 5, 60, 0, 0, 0),
(400460, 400464, 5, 90, 0, 0, 0),
(400465, 400465, 5, 0, 0, 0, 0),
(400465, 400466, 5, 15, 0, 0, 0),
(400465, 400467, 5, 30, 0, 0, 0),
(400465, 400468, 5, 60, 0, 0, 0),
(400465, 400469, 5, 90, 0, 0, 0),
(400470, 400470, 5, 0, 0, 0, 0),
(400470, 400471, 5, 15, 0, 0, 0),
(400470, 400472, 5, 30, 0, 0, 0),
(400470, 400473, 5, 60, 0, 0, 0),
(400470, 400474, 5, 90, 0, 0, 0),
(400475, 400475, 5, 0, 0, 0, 0),
(400475, 400476, 5, 15, 0, 0, 0),
(400475, 400477, 5, 30, 0, 0, 0),
(400475, 400478, 5, 60, 0, 0, 0),
(400475, 400479, 5, 90, 0, 0, 0),
(400480, 400480, 5, 0, 0, 0, 0),
(400480, 400481, 5, 15, 0, 0, 0),
(400480, 400482, 5, 30, 0, 0, 0),
(400480, 400483, 5, 60, 0, 0, 0),
(400480, 400484, 5, 90, 0, 0, 0),
(400485, 400485, 5, 0, 0, 0, 0),
(400485, 400486, 5, 15, 0, 0, 0),
(400485, 400487, 5, 30, 0, 0, 0),
(400485, 400488, 5, 60, 0, 0, 0),
(400485, 400489, 5, 90, 0, 0, 0),
(400490, 400490, 5, 0, 0, 0, 0),
(400490, 400491, 5, 15, 0, 0, 0),
(400490, 400492, 5, 30, 0, 0, 0),
(400490, 400493, 5, 60, 0, 0, 0),
(400490, 400494, 5, 90, 0, 0, 0);

-- Marshtide Knight
SET @ENTRY := 46414;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Attack Invoker"),
(@ENTRY,@SOURCETYPE,3,0,11,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set Passive"),
(@ENTRY,@SOURCETYPE,4,0,11,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set Run"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,46765,30,0,0.0,0.0,0.0,0.0,"OOC - Attack Ogre");

UPDATE `creature` SET `spawndist`=60, `MovementType`=1 WHERE `guid` IN (400455, 400460, 400465, 400470, 400475, 400480, 400485, 400490);

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start`=27857;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 75, 27857, 27857, 1, 10);

UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=150853;
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=27911;

-- Neeka Bloodscar
SET @ENTRY := 47041;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27911,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Remove Quest Flag"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27911,0,0,0,45,0,1,0,0,0,0,10,150997,1442,0,0.0,0.0,0.0,0.0,"On Quest Accept - Set Data 1 to Helgrum"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,1,3500,3500,3500,3500,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3.5 secs) - Reset NPC Flag"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,1,3500,3500,3500,3500,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3.5 secs) - Reset NPC Flag"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,0,0,47041,0,0,70,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Respawn Self"),
(@ENTRY,@SOURCETYPE,6,0,19,0,100,0,27911,0,0,0,70,0,0,0,0,0,0,10,150997,1442,0,0.0,0.0,0.0,0.0,"On Quest Accept - Respawn Helgrum");

-- Helgrum the Swift
SET @ENTRY := 1442;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,1442,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Die"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,1,1,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,15,27911,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,150995,47041,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Neeka");

-- Duskfang
SET @ENTRY := 47053;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,75002,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Leaping Rush"),
(@ENTRY,@SOURCETYPE,1,0,0,0,85,0,5000,5000,5000,5000,11,31289,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Claw"),
(@ENTRY,@SOURCETYPE,2,0,0,0,85,0,3500,3500,3500,3500,11,75930,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mangle");

DELETE FROM `creature_text` WHERE `entry` IN (47041, 1442);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47041,0,0,'Neeka Bloodscar cries.',16,0,100,18,0,0,'Comment'),
(1442,0,0,'Be strong, Neeka. I will watch over you...',12,0,100,0,0,0,'Comment'),
(1442,1,0,'Helgrum the Swift dies.',16,0,100,0,0,0,'Comment');

UPDATE `quest_template` SET `RequiredRaces`=0 WHERE `Id`=27773;