UPDATE `creature_template` SET `ScriptName`='npc_chogall_wave_event' WHERE `entry`=46965;

DELETE FROM `creature_text` WHERE `entry`=46965;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46965,0,0,'Halfus! Hear me! (The Master calls, the Master wants) Protect our secrets, Halfus. Destroy the intruders. (Murder for His glory. Murder for His hunger.)',14,0,100,0,0,22055,'Cho\'Gall - Halfus Intro'),
(46965,1,0,'Flesh and sinew, weak but proud. Dare they part the Master\'s shroud? They stumble fumble groping blind, Finding fate and chaos intertwined.',14,0,100,0,0,22056,'Cho\'Gall - Halfus Death'),
(46965,2,0,'Brothers in chaos, the Twilights has come! (Shadows lengthen, endless night.) Deathwing has sundered this world. (Doors once opened never close.) So that its true Lords may return. (The Master comes. He comes He comes.)',14,0,100,0,0,22057,'Cho\'Gall Wave Event');

-- Position update for Azureborne Destroyer (id: 47087) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -620.429, `position_y` = -735.130, `position_z` = 834.631, `orientation`= 2.688 WHERE `guid` = 779248;

-- Position update for Azureborne Destroyer (id: 47087) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -619.771, `position_y` = -729.284, `position_z` = 834.631, `orientation`= 3.190 WHERE `guid` = 779247;

-- Position update for Crimsonborne Firestarter (id: 47086) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -596.818, `position_y` = -644.433, `position_z` = 834.631, `orientation`= 0.068 WHERE `guid` = 779246;

-- Position update for Twilight Brute (id: 47161) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -581.961, `position_y` = -641.358, `position_z` = 834.631, `orientation`= 3.363 WHERE `guid` = 779245;

-- Position update for Twilight Brute (id: 47161) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -632.843, `position_y` = -725.031, `position_z` = 834.631, `orientation`= 5.728 WHERE `guid` = 779257;

-- Position update for Chosen Seer (id: 46952) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -614.647, `position_y` = -681.053, `position_z` = 834.631, `orientation`= 6.249 WHERE `guid` = 779361;

-- Position update for Chosen Warrior (id: 46951) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -610.129, `position_y` = -684.984, `position_z` = 834.631, `orientation`= 0.009 WHERE `guid` = 779368;

-- Position update for Chosen Seer (id: 46952) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -620.008, `position_y` = -687.728, `position_z` = 834.631, `orientation`= 0.148 WHERE `guid` = 779359;

-- Position update for Chosen Warrior (id: 46951) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -618.842, `position_y` = -683.425, `position_z` = 834.631, `orientation`= 6.028 WHERE `guid` = 779362;

-- Position update for Chosen Warrior (id: 46951) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -618.968, `position_y` = -678.436, `position_z` = 834.631, `orientation`= 6.125 WHERE `guid` = 779355;

-- Position update for Chosen Warrior (id: 46951) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -619.250, `position_y` = -691.663, `position_z` = 834.631, `orientation`= 0.064 WHERE `guid` = 779363;

-- Position update for Twilight Elementalist (id: 47152) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -624.942, `position_y` = -687.804, `position_z` = 834.631, `orientation`= 0.017 WHERE `guid` = 779250;

-- Position update for Twilight Elementalist (id: 47152) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -623.648, `position_y` = -676.718, `position_z` = 834.631, `orientation`= 6.254 WHERE `guid` = 779249;

-- Position update for Chosen Seer (id: 46952) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -609.281, `position_y` = -680.515, `position_z` = 834.631, `orientation`= 6.262 WHERE `guid` = 779365;

-- Position update for Chosen Warrior (id: 46951) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -610.181, `position_y` = -689.671, `position_z` = 834.631, `orientation`= 6.241 WHERE `guid` = 779364;

-- Position update for Twilight Elementalist (id: 47152) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -628.511, `position_y` = -652.498, `position_z` = 834.631, `orientation`= 1.075 WHERE `guid` = 779249;

-- Position update for Twilight Elementalist (id: 47152) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -617.962, `position_y` = -646.003, `position_z` = 834.631, `orientation`= 3.305 WHERE `guid` = 779250;

-- Position update for Elemental Firelord (id: 47081) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -615.818, `position_y` = -656.186, `position_z` = 834.631, `orientation`= 2.034 WHERE `guid` = 779311;

-- Position update for Earth Ravager (id: 47150) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -612.144, `position_y` = -643.629, `position_z` = 834.631, `orientation`= 2.790 WHERE `guid` = 779310;

-- Position update for Wind Breaker (id: 47151) in zone: 5334, area: 5334
UPDATE `creature` SET `position_x` = -634.195, `position_y` = -637.387, `position_z` = 834.632, `orientation`= 5.941 WHERE `guid` = 779309;

