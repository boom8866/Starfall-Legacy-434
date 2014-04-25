DELETE FROM `phase_definitions` WHERE `zoneId` = 616 AND `entry` IN (6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18);
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES 
(616, 6, 32, 0, 'Mount Hyjal: Phase before Lyncanthot the Corruptor (Horde)'),
(616, 7, 64, 0, 'Mount Hyjal: Phase after Lyncanthot the Corruptor'),
(616, 8, 32, 4, 'Mount Hyjal: Negate Phase 32 after Lycan'),
(616, 9, 128, 0, 'Mount Hyjal: Phase before Aessinas Miarcale'),
(616, 10, 256, 0, 'Mount Hyjal: Add Phase after Aessinas Miarcale'),
(616, 11, 512, 0, 'Mount Hyjal: Add Phase after Commander Jarod Shadowsong'),
(616, 12, 1024, 0, 'Mount Hyjal: Add Phase at Twilight Riot'),
(616, 13, 512, 4, 'Mount Hyjal: Negate Phase after Twilight Riot'),
(616, 14, 2048, 0, 'Mount Hyjal: Add Phase after Twilight Riot'),
(616, 15, 4096, 0, 'Mount Hyjal: Add Phase after Slash and Burn'),
(616, 16, 1024, 4, 'Mount Hyjal: Negate Phase after Slash and Burn'),
(616, 17, 8192, 0, 'Mount Hyjal: Add Phase after Aessinas Miarcale'),
(616, 18, 16384, 0, 'Mount Hyjal: Add Phase After A Flame Ritual');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = 616 AND `SourceEntry` IN (1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, 616, 6, 0, 0, 16, 0, 2099199, 0, 0, 0, 0, 0, '', ''),
(25, 616, 7, 0, 1, 8, 0, 25272, 0, 0, 0, 0, 0, '', ''),
(25, 616, 7, 0, 2, 8, 0, 25273, 0, 0, 0, 0, 0, '', ''),
(25, 616, 8, 0, 1, 8, 0, 25272, 0, 0, 0, 0, 0, '', ''),
(25, 616, 8, 0, 2, 8, 0, 25273, 0, 0, 0, 0, 0, '', ''),
(25, 616, 1, 0, 1, 9, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 1, 0, 2, 14, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 1, 0, 3, 28, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 9, 0, 1, 9, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 9, 0, 2, 14, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 9, 0, 3, 28, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 10, 0, 0, 8, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 11, 0, 0, 8, 0, 25597, 0, 0, 0, 0, 0, '', ''),
(25, 616, 12, 0, 1, 8, 0, 25531, 0, 0, 0, 0, 0, '', ''),
(25, 616, 12, 0, 2, 9, 0, 25531, 0, 0, 0, 0, 0, '', ''),
(25, 616, 12, 0, 3, 28, 0, 25531, 0, 0, 0, 0, 0, '', ''),
(25, 616, 13, 0, 0, 8, 0, 25531, 0, 0, 0, 0, 0, '', ''),
(25, 616, 14, 0, 0, 8, 0, 25531, 0, 0, 0, 0, 0, '', ''),
(25, 616, 15, 0, 0, 8, 0, 25608, 0, 0, 0, 0, 0, '', ''),
(25, 616, 16, 0, 0, 8, 0, 25608, 0, 0, 0, 0, 0, '', ''),
(25, 616, 17, 0, 0, 8, 0, 25372, 0, 0, 0, 0, 0, '', ''),
(25, 616, 18, 0, 1, 8, 0, 29195, 0, 0, 0, 0, 0, '', ''),
(25, 616, 18, 0, 2, 28, 0, 29195, 0, 0, 0, 0, 0, '', '');

UPDATE `gameobject` SET `phaseMask`=32 WHERE  `guid`=700339;
UPDATE `gameobject` SET `phaseMask`=32 WHERE  `guid`=700340;
UPDATE `gameobject` SET `phaseMask`=32 WHERE  `guid`=700338;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711185;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711181;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711184;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711183;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711182;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711143;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711144;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711149;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711188;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711189;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711187;
UPDATE `creature` SET `phaseMask`=32 WHERE  `guid`=711190;
UPDATE `gameobject` SET `phaseMask`=64 WHERE  `guid`=700601;
UPDATE `gameobject` SET `phaseMask`=64 WHERE  `guid`=700600;
UPDATE `creature` SET `phaseMask` = 32 WHERE `id` = 39445;
UPDATE `gameobject_template` SET `flags`=0 WHERE  `entry`=202697;
UPDATE `gameobject_template` SET `flags`=0 WHERE  `entry`=202706;
UPDATE `gameobject_template` SET `flags`=0 WHERE  `entry`=202712;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=712577;
UPDATE `creature_template_addon` SET `auras`='' WHERE  `entry`=41006;
UPDATE `creature` SET `phaseMask` = 128 WHERE `id` IN (39939, 39974, 40336, 41396, 46910, 46911);
UPDATE `creature` SET `phaseMask` = 128 WHERE `guid` = 711328;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=730879;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=730875;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=712995;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=713067;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=730854;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711660;
UPDATE `creature` SET `phaseMask` = 128 WHERE `id` = 41029;
UPDATE `creature` SET `phaseMask` = 128 WHERE `id` = 41031;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711659;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700473;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700472;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700347;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700348;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700354;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700350;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700352;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711468;
UPDATE `gameobject` SET `phaseMask` = 128 WHERE `id` = 202884;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700429;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700439;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700399;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700376;
UPDATE `gameobject` SET `phaseMask`=128 WHERE  `guid`=700396;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711635;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711641;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711634;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711632;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711630;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711633;
UPDATE `creature` SET `phaseMask`=128 WHERE  `guid`=711631;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=730835;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=730840;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=730839;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=712899;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=712900;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=712901;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=712910;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=712909;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=712921;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=730853;
UPDATE `creature` SET `phaseMask`=256 WHERE  `guid`=730852;
UPDATE `gameobject` SET `phaseMask`=256 WHERE  `guid`=700619;
UPDATE `gameobject` SET `phaseMask` = 128 WHERE `id` = 203208;
UPDATE `creature` SET `phaseMask` = 128 WHERE `id` = 41030;
UPDATE `creature` SET `phaseMask` = 128 WHERE `id` = 40561;

DELETE FROM `spell_area` WHERE `spell` = 73426 AND `area` = 5013;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES (73426, 5013, 25404, 0, 0, 0, 2, 1, 74, 11);
DELETE FROM `spell_area` WHERE `spell` = 74096 AND `area` = 5013;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES (74096, 5013, 25404, 0, 0, 0, 2, 1, 74, 11);
DELETE FROM `spell_area` WHERE `spell` = 77402 AND `area` = 4990;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES (77402, 4990, 25795, 25807, 0, 0, 2, 1, 74, 9);
DELETE FROM `spell_area` WHERE `spell` = 77403 AND `area` = 4990;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES (77403, 4990, 25807, 0, 0, 0, 2, 1, 66, 11);
DELETE FROM `spell_area` WHERE `spell` = 94997 AND `area` = 4861;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`) VALUES (94997, 4861, 25372, 1);
DELETE FROM `spell_area` WHERE `spell` = 77520 AND `area` = 4989;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_status`, `autocast`) VALUES (77520, 4989, 25372, 74, 1);
DELETE FROM `spell_area` WHERE `spell` = 60922 AND `area` = 4996;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_status`) VALUES (60922, 4996, 25315, 74);

DELETE FROM `creature_addon` WHERE `guid` = 710890;
INSERT INTO `creature_addon` (`guid`, `bytes1`, `bytes2`, `auras`) VALUES (710890, 65536, 1, '76701 49414');

SET @CGUID := 785907;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+1 AND @CGUID+34;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+1, 35845, 1, 1, 64, 5346.37, -2136.42, 1280.603, 4.904375, 120, 0, 0),
(@CGUID+2, 35845, 1, 1, 64, 5346.52, -2125.56, 1280.603, 1.570796, 120, 0, 0),
(@CGUID+3, 39637, 1, 1, 64, 5344.132, -2148.733, 1280.531, 4.39823, 120, 0, 0),
(@CGUID+4, 39432, 1, 1, 64, 5349.751, -2137.142, 1280.603, 1.658063, 120, 0, 0),
(@CGUID+5, 43548, 1, 1, 64, 5355.78, -2133.64, 1280.603, 2.984513, 120, 0, 0),
(@CGUID+6, 39435, 1, 1, 64, 5347.046, -2130.59, 1280.52, 0, 120, 0, 0),
(@CGUID+7, 39433, 1, 1, 64, 5353.563, -2127.177, 1280.603, 3.333579, 120, 0, 0),
(@CGUID+8, 39434, 1, 1, 64, 5349.915, -2125.339, 1280.603, 4.886922, 120, 0, 0),
(@CGUID+9, 39644, 1, 1, 64, 5350.282, -2120.955, 1280.603, 0.9250245, 120, 0, 0),
(@CGUID+10, 39644, 1, 1, 64, 5352.26, -2118.189, 1280.603, 3.543018, 120, 0, 0),
(@CGUID+11, 39644, 1, 1, 64, 5349.622, -2117.373, 1280.603, 4.625123, 120, 0, 0),
(@CGUID+12, 39637, 1, 1, 64, 5338.963, -2116.507, 1280.634, 3.124139, 120, 0, 0),
(@CGUID+13, 43547, 1, 1, 64, 5351.92, -2108.88, 1280.603, 3.054326, 120, 0, 0),
(@CGUID+14, 39637, 1, 1, 64, 5339.74, -2103.36, 1280.613, 1.797689, 120, 0, 0),
(@CGUID+15, 39637, 1, 1, 64, 5350.694, -2098.399, 1280.664, 1.902409, 120, 0, 0),
(@CGUID+16, 39637, 1, 1, 64, 5350.095, -2172.814, 1279.973, 3.159046, 120, 0, 0),
(@CGUID+17, 39622, 1, 1, 64, 5367.265625, -2188.148682, 1291.633423, 2.993843, 0, 0, 0),
(@CGUID+18, 39637, 1, 1, 64, 5346.54, -2184.69, 1278.61, 2.71928, 0, 0, 0),
(@CGUID+19, 39637, 1, 1, 64, 5306.763, -2206.842, 1263.784, 3.141593, 120, 0, 0),
(@CGUID+20, 39637, 1, 1, 64, 5313.143, -2200.722, 1263.784, 2.007129, 120, 0, 0),
(@CGUID+21, 41006, 1, 1, 128, 4192.761, -2321.214, 1148.047, 3.647738, 120, 0, 0),
(@CGUID+22, 41029, 1, 1, 128, 4125.576, -2282.418, 1132.367, 1.381328, 120, 0, 0),
(@CGUID+23, 41029, 1, 1, 128, 4093.429, -2277.401, 1132.595, 2.109991, 120, 0, 0),
(@CGUID+24, 41029, 1, 1, 128, 3639.382, -2345.113, 1089.472, 5.305801, 120, 0, 0),
(@CGUID+25, 41029, 1, 1, 128, 3489.619, -2424.637, 973.4338, 5.026548, 120, 0, 0),
(@CGUID+26, 41029, 1, 1, 128, 3493.761, -2405.56, 973.2911, 1.55279, 120, 0, 0), 
(@CGUID+27, 41029, 1, 1, 128, 3464.324, -2390.803, 969.3176, 3.349308, 120, 0, 0),
(@CGUID+28, 41029, 1, 1, 128, 3480.477, -2392.293, 972.1199, 1.291544, 120, 0, 0),
(@CGUID+29, 41029, 1, 1, 128, 3485.961, -2478.87, 980.0939, 3.438299, 120, 0, 0), 
(@CGUID+30, 41029, 1, 1, 128, 3504.517, -2310.012, 972.6765, 3.700098, 120, 0, 0),
(@CGUID+31, 41029, 1, 1, 128, 3435.96, -2371.951, 969.6036, 3.926991, 120, 0, 0),
(@CGUID+32, 41029, 1, 1, 128, 3442.095, -2317.215, 970.7748, 2.460914, 120, 0, 0),
(@CGUID+33, 41029, 1, 1, 128, 3399.44, -2337.113, 969.0239, 2.96706, 120, 0, 0),
(@CGUID+34, 40772, 1, 1, 1024, 4084.59, -3996.44, 971.424, 0.0174533, 300, 0, 0);

SET @OGUID := 778463;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+1 AND @OGUID+4;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+1, 203208, 1, 1, 128, 3628.652, -2355.031, 1089.054, 2.164206, 0, 0, 0, 1, 120, 255, 1),
(@OGUID+2, 203208, 1, 1, 128, 3527.037, -2355.998, 976.6681, 2.164206, 0, 0, 0, 1, 120, 255, 1),
(@OGUID+3, 203208, 1, 1, 128, 3436.575, -2330.085, 968.6746, 2.164206, 0, 0, 0, 1, 120, 255, 1),
(@OGUID+4, 203208, 1, 1, 128, 3907.212, -2211.981, 1121.838, 2.164206, 0, 0, 0, 1, 120, 255, 1);


UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=39730;
UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=39737;
UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=39736;
UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=39738;

DELETE FROM `gameobject_loot_template` WHERE `entry` = 29580;
INSERT INTO `gameobject_loot_template` (`entry`, `item`) VALUES (29580, 55809);

-- Aviana's Egg
SET @ENTRY := 41300;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,77394,0,0,0,33,41310,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Kill Credit"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,75,77403,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Link - Cast ");

SET @SPELL        := 77394;
SET @ENTRY        := 41300;
DELETE FROM `conditions`  WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = @SPELL;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`) VALUES
(13, 2, @SPELL, 31, 3, @ENTRY);

-- UPDATE `creature_questrelation` SET `id`=40833 WHERE  `id`=41005 AND `quest`=25985;
UPDATE `gameobject_template` SET `flags`=0 WHERE  `entry`=202701;

UPDATE `creature` SET `phaseMask` = 512 WHERE `guid` IN (713452,
713456,
713453,
713451,
713457,
713449,
713454,
713460,
713455,
713448,
713461,
713458,
713462,
713450,
713463,
713459,
713514,
713572,
713561,
713579,
713536,
713682,
713706,
713707,
713710,
713711,
713712,
713469,
713470);

UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 46991;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 39342;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 39344;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 39453;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 39391;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 40536;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 39828;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 39752;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 40185;
UPDATE `creature` SET `phaseMask` = 512 WHERE `id` = 39749;
UPDATE `gameobject` SET `phaseMask`=512 WHERE  `guid`=700737;

UPDATE `creature` SET `phaseMask`=1024 WHERE  `guid`=731304;
UPDATE `creature` SET `phaseMask`=1024 WHERE  `guid`=731295;
UPDATE `creature` SET `phaseMask`=1024 WHERE  `guid`=731296;
UPDATE `creature` SET `phaseMask`=1024 WHERE  `guid`=731294;
UPDATE `creature` SET `phaseMask`=1024 WHERE  `guid`=712268;

UPDATE `creature` SET `phaseMask`=4096 WHERE  `guid`=731303;
UPDATE `creature` SET `phaseMask`=4096 WHERE  `guid`=731298;
UPDATE `creature` SET `phaseMask`=4096 WHERE  `guid`=730754;
UPDATE `creature` SET `phaseMask`=4096 WHERE  `guid`=731305;
UPDATE `creature` SET `phaseMask`=4096 WHERE  `guid`=731302;
UPDATE `creature` SET `phaseMask`=4096 WHERE  `guid`=731299;

UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730889;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730896;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730893;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730891;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730892;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730885;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730886;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 52853;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 52846 AND `phaseMask` = 32768;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 52219;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 52816;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 52795;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 52791;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=712926;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=712929;
UPDATE `creature` SET `phaseMask` = 49152 WHERE `id` = 52794;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 54251;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730837;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730844;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730874;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730836;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730843;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730871;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730872;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730850;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730849;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=731468;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730841;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730847;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730848;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730842;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=712919;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730846;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730870;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730826;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=731470;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=731471;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730845;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730869;
UPDATE `creature` SET `phaseMask` = 262144 WHERE  `guid`=730827;
UPDATE `creature` SET `position_z`= 1140.42 WHERE  `guid`=730826;
UPDATE `gameobject` SET `phaseMask` = 262144 WHERE  `guid`=700647;
UPDATE `gameobject` SET `phaseMask`=262144 WHERE  `guid`=717709;
UPDATE `gameobject` SET `phaseMask`=262144 WHERE  `guid`=700648;
UPDATE `gameobject` SET `phaseMask`=262144 WHERE  `guid`=700607;
UPDATE `gameobject` SET `phaseMask`=262144 WHERE  `guid`=700608;
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730888; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730883; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730895; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730890; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730894; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730881; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730877; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730829; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730882; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730833; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730859; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730864; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730832; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730876; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730830; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730878; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730868; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730865; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730897; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730887; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730884; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730834; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730828; 
UPDATE `creature` SET `phaseMask`=8192 WHERE  `guid`=730880; 
UPDATE `creature` SET `phaseMask`=16384 WHERE  `guid`=730838;
UPDATE `creature` SET `phaseMask`=16384 WHERE  `guid`=730826;
UPDATE `creature` SET `phaseMask`=16384 WHERE  `guid`=730827;
UPDATE `creature` SET `phaseMask` = 262144 WHERE `id` = 52557;

DELETE FROM `quest_poi_points` WHERE `questId` = 25904 AND `id` = 2;
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES 
(25904, 2, 1, 4666, -3665),
(25904, 2, 2, 4611, -3421),
(25904, 2, 3, 4693, -3265),
(25904, 2, 4, 4709, -3075),
(25904, 2, 5, 4674, -2993),
(25904, 2, 6, 4600, -2939),
(25904, 2, 7, 4483, -2943),
(25904, 2, 8, 4437, -3021),
(25904, 2, 9, 4355, -3510),
(25904, 2, 10, 4355, -3525),
(25904, 2, 11, 4526, -3739),
(25904, 2, 12, 4565, -3766);

DELETE FROM `quest_poi_points` WHERE `questId` = 25899 AND `id` = 0;
DELETE FROM `quest_poi_points` WHERE `questId` = 25899 AND `id` = 1;
DELETE FROM `quest_poi_points` WHERE `questId` = 25899 AND `id` = 2;
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES 
(25899, 0, 1, 4512, -3542),
(25899, 0, 2, 4712, -3376),
(25899, 0, 3, 4765, -3082),
(25899, 0, 4, 4664, -2946),
(25899, 0, 5, 4502, -2900),
(25899, 0, 6, 4455, -3490),
(25899, 0, 7, 4458, -3536),
(25899, 1, 1, 4684, -3741),
(25899, 1, 2, 4699, -3703),
(25899, 1, 3, 4697, -3652),
(25899, 1, 4, 4675, -3618),
(25899, 2, 0, 4612, -3354);

DELETE FROM `quest_poi_points` WHERE `questId` = 25881 AND `id` = 1;
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES 
(25881, 1, 1, 4472, -3513),
(25881, 1, 2, 4526, -3506),
(25881, 1, 3, 4604, -3467),
(25881, 1, 4, 4662, -3405),
(25881, 1, 5, 4720, -3300),
(25881, 1, 6, 4767, -3172),
(25881, 1, 7, 4767, -3094),
(25881, 1, 8, 4740, -2986),
(25881, 1, 9, 4639, -2912),
(25881, 1, 10, 4542, -2900),
(25881, 1, 11, 4460, -2974),
(25881, 1, 12, 4406, -3432);

DELETE FROM `quest_poi_points` WHERE `questId` = 25886 AND `id` = 1;
DELETE FROM `quest_poi_points` WHERE `questId` = 25886 AND `id` = 2;
DELETE FROM `quest_poi_points` WHERE `questId` = 25886 AND `id` = 3;
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES 
(25886, 1, 0, 4612, -3354),
(25886, 2, 0, 4643, -3781),
(25886, 2, 1, 4674, -3746),
(25886, 2, 2, 4677, -3719),
(25886, 2, 3, 4646, -3626),
(25886, 2, 4, 4608, -3579),
(25886, 2, 5, 4569, -3579),
(25886, 2, 6, 4522, -3583),
(25886, 2, 7, 4487, -3618),
(25886, 2, 8, 4518, -3704),
(25886, 2, 9, 4530, -3735),
(25886, 2, 10, 4545, -3766),
(25886, 2, 11, 4580, -3789),
(25886, 3, 0, 4460, -3595),
(25886, 3, 1, 4577, -3467),
(25886, 3, 2, 4615, -3409),
(25886, 3, 3, 4701, -3164),
(25886, 3, 4, 4701, -3090),
(25886, 3, 5, 4677, -3009),
(25886, 3, 6, 4646, -2958),
(25886, 3, 7, 4608, -2920),
(25886, 3, 8, 4534, -2912),
(25886, 3, 9, 4472, -2955),
(25886, 3, 10, 4344, -3502),
(25886, 3, 11, 4367, -3607);

DELETE FROM `quest_poi_points` WHERE `questId` = 25901 AND `id` = 0;
DELETE FROM `quest_poi_points` WHERE `questId` = 25901 AND `id` = 1;
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES 
(25901, 0, 0, 4602, -3441),
(25901, 0, 1, 4644, -3430),
(25901, 0, 2, 4663, -3422),
(25901, 0, 3, 4694, -3384),
(25901, 0, 4, 4720, -3330),
(25901, 0, 5, 4720, -3283),
(25901, 0, 6, 4659, -3271),
(25901, 0, 7, 4573, -3264),
(25901, 0, 8, 4543, -3304),
(25901, 0, 9, 4518, -3375),
(25901, 0, 10, 4526, -3419),
(25901, 1, 0, 4610, -3343);

UPDATE `gameobject` SET `phaseMask` = 1 WHERE `id` = 202619;
DELETE FROM `gameobject_loot_template` WHERE `entry` = 28423 AND `item` = 52537;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES (28423, 52537, -100);
DELETE FROM `creature_loot_template` WHERE `entry` = 48724 AND `item` = 52708;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (48724, 52708, -80.862, 1, 0, 1, 1);
UPDATE `gameobject` SET `phaseMask` = 512 WHERE `id`=202952;

-- Spawn of Smolderos
SET @ENTRY := 39659;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,74142,0,0,0,33,39673,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Kill Credit");

DELETE FROM `gameobject_loot_template` WHERE `entry` = 28705 AND `item` = 52724;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES (28705, 52724, -100, 1, 0, 1, 1);
DELETE FROM `gameobject_loot_template` WHERE `entry` = 28706 AND `item` = 52725;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES (28706, 52725, -100);
UPDATE `gameobject` SET `phaseMask`=1 WHERE  `guid`=700742;

SET @SPELL        := 74142;
SET @ENTRY        := 39659;
DELETE FROM `conditions`  WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = @SPELL;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`) VALUES
(13, 1, @SPELL, 31, 3, @ENTRY);

DELETE FROM `spell_area` WHERE `spell` = 49416 AND `area` = 4996;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`) VALUES (49416, 4996, 25315, 1, 74);
UPDATE `creature` SET `phaseMask`=512 WHERE  `guid`=735553;

UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=730808;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (39730, 39737, 39736, 39738);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES 
(39730, 74287, 3, 0),
(39737, 74288 , 3, 0),
(39736, 74290  , 3, 0),
(39738, 74292   , 3, 0);

UPDATE `creature_template` SET `IconName`='Interact' WHERE  `entry`=39730;
UPDATE `creature_template` SET `IconName`='Interact' WHERE  `entry`=39737;
UPDATE `creature_template` SET `IconName`='Interact' WHERE  `entry`=39736;
UPDATE `creature_template` SET `IconName`='Interact' WHERE  `entry`=39738;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 17 AND `SourceEntry` IN (74288, 74290, 74292);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(17, 0, 74288, 0, 0, 1, 0, 74287, 0, 0, 0, 0, 0, '', ''),
(17, 0, 74290, 0, 0, 1, 0, 74288, 0, 0, 0, 0, 0, '', ''),
(17, 0, 74292, 0, 0, 1, 0, 74290, 0, 0, 0, 0, 0, '', '');

-- Crucible's
SET @ENTRY := 39737;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,73,0,100,0,0,0,0,0,28,74287,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellclick - Remove Aura"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,28,74288,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,28,74290,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura");

SET @ENTRY := 39736;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,73,0,100,0,0,0,0,0,28,74287,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellclick - Remove Aura"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,28,74288,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,28,74290,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura");

SET @ENTRY := 39738;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,73,0,100,0,0,0,0,0,28,74287,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellclick - Remove Aura"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,28,74288,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,28,74290,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` IN (39737, 39736);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `NegativeCondition`) VALUES 
(22, 1, 39737, 0, 1, 74287, 1),
(22, 1, 39736, 0, 1, 74288, 1);

-- Takrik Ragehowl
SET @ENTRY := 39432;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,25612,0,0,0,11,87486,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On Quest reward - Cast");

DELETE FROM `spell_target_position` WHERE `id` = 87486;
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES (87486, 1, 5353.386230, -2130.681152, 1280.519897, 3.133435);


-- Tyrus Blackhorn QUEST: If you're not against us
SET @ENTRY := 39933;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,98,11316,15772,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Update Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11325,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Gossip Close"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11325,0,0,0,33,40056,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select  - Kill Credit");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11322 WHERE  `menu_id`=11316 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11324 WHERE  `menu_id`=11322 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11325 WHERE  `menu_id`=11322 AND `id`=1;
DELETE FROM `gossip_menu` WHERE `entry` = 11326  AND `text_id` = 15782;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (11326, 15782);
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11326 WHERE  `menu_id`=11322 AND `id`=2;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11325 WHERE  `menu_id`=11324 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11326 WHERE  `menu_id`=11324 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11325 WHERE  `menu_id`=11326 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE  `menu_id`=11325 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry` = 39933 AND `groupid` = 1;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES (39933, 1, 0, 'Madness. Chaos. Much as I thrill to see the titans\' work undone, I do wish to remain alive when the master returns. I will help you.', 12, 0, 100, 0, 0, 0, '');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceGroup` = 1 AND `SourceEntry` = 39933; 
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (22, 1, 39933, 0, 1, 9, 0, 25404, 0, 0, 0, 0, 0, '', NULL);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (22, 1, 39933, 0, 1, 28, 0, 25404, 0, 0, 1, 0, 0, '', NULL);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 15 AND `SourceGroup` = 11316 AND `SourceEntry` = 0; 
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (15, 11316, 0, 0, 1, 9, 0, 25404, 0, 0, 0, 0, 0, '', NULL);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES (15, 11316, 0, 0, 1, 28, 0, 25404, 0, 0, 1, 0, 0, '', NULL);


-- Twilight Inferno Lord
SET @ENTRY := 39974;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,32707,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,32707,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,2,2,100,1,0,15,0,0,22,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 3 at 15% HP"),
(@ENTRY,@SOURCETYPE,11,0,2,3,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,12,0,7,3,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,13,0,2,3,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,14,0,0,1,100,0,4000,7000,17000,17000,11,11962,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Cast Immolate"),
(@ENTRY,@SOURCETYPE,15,0,0,1,100,0,9000,9000,11000,13000,11,13339,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Fire Blast"),
(@ENTRY,@SOURCETYPE,16,0,1,0,100,0,1000,1000,30000,30000,11,74587,2,0,0,0,0,9,35845,0,6,0.0,0.0,0.0,0.0,"Cast Fire Channeling on Bunny"),
(@ENTRY,@SOURCETYPE,17,18,8,0,100,0,74763,0,0,0,11,74760,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast"),
(@ENTRY,@SOURCETYPE,18,19,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Corpse"),
(@ENTRY,@SOURCETYPE,19,0,61,0,100,0,0,0,0,0,33,40099,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Kill Credit");

SET @SPELL        := 74763;
SET @ENTRY        := 39974;
DELETE FROM `conditions`  WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = @SPELL;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `NegativeCondition`) VALUES
(13, 1, @SPELL, 0, 31, 3, @ENTRY, 0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 17 AND `SourceEntry` = 74763 AND `ConditionTypeOrReference` = 36;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionTarget`, `NegativeCondition`) VALUES (17, 74763, 36, 1, 1);

UPDATE `creature_template` SET `IconName` = 'LootAll' WHERE `entry` = 39998;
UPDATE `creature_template` SET `npcflag` = 16777216 WHERE `entry` = 39998;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`= 39998;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`= 39998;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 18 AND `SourceGroup` = 39998 AND `SourceEntry` = 74618; 
DELETE FROM `smart_scripts` WHERE `entryorguid` = 39998 AND `source_type` = 0 AND `id` = 0;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (39998, 74618, 3, 0);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(18, 39998, 74618, 0, 0, 9, 0, 25385, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39998, 0, 0, 0, 73, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spellclick - Despawn');

UPDATE `creature_template` SET `IconName` = 'LootAll' WHERE `entry` = 39997;
UPDATE `creature_template` SET `npcflag` = 16777216 WHERE `entry` = 39997;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`= 39997;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`= 39997;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 18 AND `SourceGroup` = 39997 AND `SourceEntry` = 74618; 
DELETE FROM `smart_scripts` WHERE `entryorguid` = 39997 AND `source_type` = 0 AND `id` = 0;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (39997, 74618, 3, 0);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(18, 39997, 74618, 0, 0, 9, 0, 25385, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39997, 0, 0, 0, 73, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spellclick - Despawn');
UPDATE `creature_template` SET `flags_extra`=0 WHERE  `entry`=39997;

DELETE FROM `spell_area` WHERE `spell` = 49416 AND `area` = 5019;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES (49416, 5019, 25490, 25372, 0, 0, 2, 1, 74, 1);

-- Oh, Deer!
UPDATE `creature_template` SET `IconName` = 'Pickup' WHERE `entry` = 39999;
UPDATE `creature_template` SET `npcflag` = 16777216 WHERE `entry` = 39999;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`= 39999;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`= 39999;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 18 AND `SourceGroup` = 39999 AND `SourceEntry` = 74654;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 39999 AND `source_type` = 0 AND `id` = 0;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (39999, 74654, 3, 0);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(18, 39999, 74654, 0, 0, 9, 0, 25392, 0, 0, 0, 0, 0, 0, '');
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(39999, 0, 0, 0, 73, 0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spellclick - Despawn');

-- Nemesis
SET @ENTRY := 40340;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,73,0,100,0,0,0,0,0,85,75570,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellclick - Invoker Cast"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,1,1,50000,50000,45,2,2,0,0,0,0,11,40500,15,0,0.0,0.0,0.0,0.0,"On Data Set - Set Data"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,1,1,50000,50000,2,2028,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set - Set Faction"),
(@ENTRY,@SOURCETYPE,4,0,73,0,100,0,0,0,0,0,80,4034000,0,2,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellclick - Call Timed Actionlist");

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 40340;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES (40340, 75576, 2);

-- Heap of Core Hound Innards
SET @ENTRY := 40500;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,0,1,10,0,0,45,1,1,0,0,0,0,11,40340,10,0,0.0,0.0,0.0,0.0,"OOC_LOS - Set Data to Nemesis"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,2,2,0,0,80,4050000,0,2,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set - Call Timed Actionlist"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,44,128,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Summon - Set Phase 128"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,41,45000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Despawn 45sec");

-- Timed Actionlists
SET @ENTRY := 4050000;
SET @SOURCETYPE := 9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,40000,55000,1,1,2,2147,0,0,0,0,0,10,711660,40340,0,0.0,0.0,0.0,0.0,"On Timed Event 2 min - Set Faction to Original");

DELETE FROM `creature_text` WHERE `entry` = 40340;
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`, `probability`) VALUES (40340, 1, 'Nemesis is angry - run for it!', 41, 100);

SET @ENTRY := 4034000;
SET @SOURCETYPE := 9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,8000,8000,1,1,1,1,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Timed Event - Talk"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,0,0,2,2147,0,0,0,0,0,10,711660,40340,0,0.0,0.0,0.0,0.0,"On Timed Event - Set Faction");


-- Rod of Subjugation
SET @ENTRY := 202955;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,70,0,100,0,2,0,0,0,85,75625,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On State Change - Invoker Cast"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,33,40545,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Kill Credit");

-- Rod of Subjugation
SET @ENTRY := 202954;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,70,0,100,0,2,0,0,0,85,75625,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On State Change - Invoker Cast"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,33,40544,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Kill Credit");

UPDATE `creature_template` SET `unit_flags`=33280 WHERE  `entry`=40341;

DELETE FROM `creature_text` WHERE `entry` = 40551;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`) VALUES 
(40551, 1, 0, 'The master will not suffer this insult!', 12),
(40551, 1, 1, 'No - No! This one is ours...', 12),
(40551, 1, 2, 'Mortal! You overreach.', 12);

-- Twilight Dominator
SET @ENTRY := 40551;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On Summon - Talk");

-- Arch Druid Hamuul Runetotem
SET @ENTRY := 39858;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,25520,0,0,0,85,87516,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Invoker Cast");

DELETE FROM `spell_area` WHERE `spell` = 77063 AND `area` = 4990;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`) VALUES (77063, 4990, 25740, 1, 1);

-- Twilight Juggernaut
SET @ENTRY := 41031;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,500,1000,60000,60000,11,77224,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Armor Plating on Spawn");

UPDATE `creature_involvedrelation` SET `id`=52838 WHERE  `id`=39858 AND `quest`=25372;

-- Twilight Scorchlord
SET @ENTRY := 41500;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,9053,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,9053,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,2,2,100,1,0,15,0,0,22,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 3 at 15% HP"),
(@ENTRY,@SOURCETYPE,11,0,2,3,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,12,0,7,3,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,13,0,2,3,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,0,5000,5000,55000,55000,11,77627,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Summon Fiery Minion");

DELETE FROM `creature_text` WHERE `entry` = 39619;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(39619, 1, 0, 'Fine. I "'"ll come with you. This had better be important.', 12, 0, 0, 0, 0, 0, ''),
(39619, 1, 1, 'Now you"'"re just wasting my time!', 12, 0, 0, 0, 0, 0, ''),
(39619, 1, 2, 'You have something to show me?', 12, 0, 0, 0, 0, 0, ''),
(39619, 1, 3, 'You want something?', 12, 0, 0, 0, 0, 0, ''),
(39619, 2, 0, 'Lead the Twilight Recruit away from the Group and use the Blackjack to knock him out.', 41, 0, 100, 0, 0, 0, '');

-- Twilight Recruit
SET @ENTRY := 39619;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Flag"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,29,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Gossip Hello - Follow");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceGroup` = 1 AND `SourceEntry` = 39619;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES (22, 1, 39619, 9, 25274);
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceGroup` = 5 AND `SourceEntry` = 39619;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES (22, 5, 39619, 9, 25274);

UPDATE `gameobject_template` SET `data5`=1 WHERE  `entry`= 202952;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE  `menu_id`=11420 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry` = 40489;
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`) VALUES (40489, 1, 'What? I\'ll show that pipsqueak!', 12);
UPDATE `creature_template` SET `npcflag`=1 WHERE  `entry`=39619;

-- High Cultist Azennios
SET @ENTRY := 40491;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,1,1,0,0,2,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set - Set faction"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk");

-- Karr'gonn
SET @ENTRY := 40489;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,11420,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11420,0,0,0,45,1,1,0,0,0,0,10,713711,40491,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Data");

DELETE FROM `creature_text` WHERE `entry` = 40491;
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`) VALUES (40491, 1, 'I\'ve got a bad feeling about this.', 12);

-- Instructor Mylva
SET @ENTRY := 39413;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,25499,0,0,0,85,75397,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Invoker Cast 75397");

-- Blazing Trainer
SET @ENTRY := 40434;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,4043400,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Call Timed Actionlist"),
(@ENTRY,@SOURCETYPE,1,2,33,0,100,0,1,99999,0,0,28,75397,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Target Damage - Remove Aura"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Despawn"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,6,25499,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Fail"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Die");

-- Blazing Trainer
SET @ENTRY := 4043400;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On timed Event - SAttack Invoker");

DELETE FROM `creature_text` WHERE `entry` = 40434;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES (40434, 1, 0, 'Run away from the Blazing Trainer!', 41, 0, 0, 0, 0, 0, '');
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE  `menu_id`=11382 AND `id`=0;

-- Gromm'ko
SET @ENTRY := 40409;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11382,0,0,0,45,1,1,0,0,0,0,10,731293,40427,0,0.0,0.0,0.0,0.0,"Gossip Select - Set Data"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11382,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,1,1,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set - Talk"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,1,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set - Change Faction");

-- Spawn of Smolderos
SET @ENTRY := 40427;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,8000,16000,18000,11,74143,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Little Big Flame Breath"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,1,1,0,0,28,94224,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Data Set - Remove Aura"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,1,1,0,0,49,0,0,0,0,0,0,19,40412,0,0,0.0,0.0,0.0,0.0,"Data Set - Attack"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,2,2,0,0,75,94224,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Data Set - Add Aura"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,1,1,0,0,19,131584,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Data Set - Remove Unit flag"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,2,2,0,0,18,131584,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set - Set Unit flag");

-- Butcher
SET @ENTRY := 40412;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,1,1,0,0,0,0,11,40409,15,0,0.0,0.0,0.0,0.0,"On Death - Set Data"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,45,2,2,0,0,0,0,10,731293,40427,0,0.0,0.0,0.0,0.0,"On Death - Set Data");

DELETE FROM `creature_text` WHERE `entry` = 40409;
INSERT INTO `creature_text` (`entry`, `groupid`, `text`, `type`) VALUES (40409, 1, 'You! Your mutt killed my Butcher! I will crush you!', 14);
UPDATE `creature_template` SET `unit_flags`=0 WHERE  `entry`=40427;
UPDATE `creature_template` SET `faction_A`=1959, `faction_H`=1959 WHERE  `entry`=40412;
UPDATE `creature` SET `phaseMask`=512 WHERE  `guid`=731293;
UPDATE `creature_addon` SET `auras`='94224' WHERE  `guid`=731293;
UPDATE `creature_template` SET `unit_flags`=131584 WHERE  `entry`=40427;

UPDATE `creature_template` SET `VehicleId`=166 WHERE  `entry`=40025;
UPDATE `creature_template` SET `InhabitType`=5 WHERE  `entry`=40025;
UPDATE `creature_template` SET `InhabitType`=5 WHERE  `entry`=40934;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = 40934;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (40934, 75638, 3, 0);
UPDATE `creature_template` SET `spell1`=75637, `spell2`=75668, `spell4`=76460 WHERE  `entry`=40025;
DELETE FROM `creature_template_addon` WHERE `entry` = 40025;
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES (40025, '75639');
UPDATE `creature_template` SET `unit_flags`=32768 WHERE  `entry`=40025;
UPDATE `creature_template` SET `exp`=3 WHERE  `entry`=40025;
UPDATE `creature_template` SET `unit_class`=2 WHERE  `entry`=40025;
UPDATE `creature_template` SET `Mana_mod`=2 WHERE  `entry`=40025;
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80 WHERE  `entry`=40025;
UPDATE `gameobject_template` SET `flags`=0 WHERE  `entry`=207359;
UPDATE `creature` SET `phasemask` = 49152 WHERE `id` = 52791;
UPDATE `creature` SET `phasemask` = 49152 WHERE `id` = 52219;
UPDATE `creature` SET `phasemask` = 49152 WHERE `id` = 52795;
UPDATE `creature` SET `phasemask` = 49152 WHERE `id` = 52816;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-100 WHERE  `entry`=40687 AND `item`=54973;
DELETE FROM `creature_addon` WHERE `guid` = 730838;
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES (730838, '98613');