UPDATE `gameobject_template` SET `ScriptName`='go_mount_hyjal_horde_portal' WHERE `entry`=209081;
UPDATE `gameobject_template` SET `ScriptName`='go_mount_hyjal_alliance_portal' WHERE `entry`=209080;

DELETE FROM `creature_questrelation` WHERE `id` = '40289' AND `quest` IN (25985, 25584);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(40289, 25985),
(40289, 25584);

DELETE FROM `creature_text` WHERE `entry`=39446;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39446,0,0,'Log\'loth og shandai, mortal. Only death is eternal. You will be undone.',12,0,100,0,0,0,'Comment');

-- Lycanthoth
SET @ENTRY := 39446;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,8000,8000,18000,21000,11,37776,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Lycanthoth - In combat - Cast Blood Howl"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,11,74475,4,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon Lo'gosh"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

UPDATE `creature_template` SET `VehicleId`=1227 WHERE `entry`=39622;

DELETE FROM `waypoints` WHERE `entry` = '39622';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(39622, 0, 5198.76, -2257.78, 1271.26, 'Lo\'Gosh WP'),
(39622, 1, 5218.97, -2248.13, 1267.76, 'Lo\'Gosh WP'),
(39622, 2, 5238.10, -2226.21, 1264.29, 'Lo\'Gosh WP'),
(39622, 3, 5293.32, -2206.68, 1263.70, 'Lo\'Gosh WP (Pause)'),
(39622, 4, 5334.62, -2173.95, 1271.29, 'Lo\'Gosh WP (Pause low )'),
(39622, 5, 5366.20, -2186.74, 1291.11, 'Lo\'Gosh WP');

-- Spirit of Lo'Gosh
SET @ENTRY := 39622;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,66,3,0,0,0,0,0,8,0,0,0,5143.51,-2300.51,1278.61,0.48,"On Just Summoned - Set Orientation"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,25272,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Ride Invoker"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,53,1,39622,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,5,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Remove Passengers"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `creature_template` SET `speed_run`=1.64286, `unit_flags`=768 WHERE `entry`=39622;

-- Spirit of Lo'Gosh
SET @ENTRY := 39622;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,66,3,0,0,0,0,0,8,0,0,0,5143.51,-2300.51,1278.61,0.48,"On Just Summoned - Set Orientation"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,25272,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Ride Invoker (DISABLED TEMP)"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,53,1,39622,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,5,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Remove Passengers"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,20,0,100,0,25272,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Force Despawn"),
(@ENTRY,@SOURCETYPE,7,0,20,0,100,0,25273,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Force Despawn");

UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=39644;

DELETE FROM `creature_text` WHERE `entry`=39644;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39644,0,0,'What did they do to me? I\'ve got to get back to camp...',12,0,100,0,0,0,'Comment'),
(39644,0,1,'...What am I saying? Nothing makes sense anymore. I\'ve got to get out of this place!',12,0,100,0,0,0,'Comment'),
(39644,0,2,'Wha - what? Where am I? I\'ve got to get out of here!',12,0,100,0,0,0,'Comment'),
(39644,0,3,'What happened to me? I\'m leaving!',12,0,100,0,0,0,'Comment'),
(39644,0,4,'Whoa, you made the voices go away. I\'m outta here!',12,0,100,0,0,0,'Comment'),
(39644,0,5,'My ... brain ... hurts!',12,0,100,0,0,0,'Comment');

-- Twilight Servitor
SET @ENTRY := 39644;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,62,0,100,0,11279,0,0,0,33,39719,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11279,0,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11279,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,11279,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove NPC Flag");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11279';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11279, '<Administer the drought.> ', 1, 1);

UPDATE `npc_text` SET `text0_0`='Thoth\'al amun Ree\'thael vormos! Vormos! Vormos! ', `text1_0`='Mar\'kow tallol ye\'tarin, it knows, it knows.', `text2_0`='Fear broils forth from the heart of the infinite! Don\'t make me look! I\'ve seen more than I can stand! ', `text3_0`='We are nothing. Tulall par\'okoth. Far\'al ka\'kar. The void devours. ', `text4_0`='The shadow sees. Bo\'al lal arwl C\'toth. The end comes, cloaked in silent fire. ', `text5_0`='Al\'tha, Al\'tha bormaz. Ni bormaz ta\'thall? It comes, it walks in flames! ', `text6_0`='<The Twilight Servitor gurgles at you, white spittle foaming and bubbling from his mouth.> ', `text7_0`='H\'thon, the column of darkness stretching beyond sight. H\'thon marwol qualar: the infinite grasp of night. ' WHERE `ID`=15711;

UPDATE `creature_template` SET `ScriptName`='npc_generic_dave_trigger' WHERE `entry`=35845;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=711025;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `id` IN (203095, 203092, 203096, 203094, 203093, 203098);

DELETE FROM `creature_text` WHERE `entry`=40845;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40845,0,0,'Water! Here!?',12,0,100,0,0,0,'Comment'),
(40845,0,1,'Aiiieee!',12,0,100,0,0,0,'Comment'),
(40845,0,2,'I\'ll get you, mortal! And your little wolves too!',12,0,100,0,0,0,'Comment'),
(40845,0,3,'It ... burns!',12,0,100,0,0,0,'Comment'),
(40845,0,4,'This <glub> is not over yet, mortal...',12,0,100,0,0,0,'Comment'),
(40845,1,0,'Forgemaster Pyrendius howls in fury as he is doused by water!',41,0,100,0,0,0,'Comment'),
(40845,2,0,'Impurity! Your fragile flesh defiles my work.',12,0,100,0,0,0,'Comment');

-- Forgemaster Pyrendius
SET @ENTRY := 40845;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,1000,4000,6000,11,18543,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Lash"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 2"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,76406,1,0,0,18,262144,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Stunned"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,40845,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,33,40845,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,11,76406,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Water"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,0,40845,0,0,19,262144,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Remove Stunned"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,1,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1");

-- Dave's Industrial Light and Magic Bunny
SET @ENTRY := 34346;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,76406,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Water"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,45,0,1,0,0,0,0,11,40845,5,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Data 1 to Forgemaster");

-- Portal Rune
SET @ENTRY := 203095;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34346,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger Water");

-- Portal Rune
SET @ENTRY := 203092;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34346,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger Water");

-- Portal Rune
SET @ENTRY := 203096;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34346,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger Water");

-- Portal Rune
SET @ENTRY := 203094;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34346,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger Water");

-- Portal Rune
SET @ENTRY := 203093;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34346,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger Water");

UPDATE `creature` SET `phaseMask`=1 WHERE `id`='34346' AND `phaseMask`='4096';
UPDATE `creature_template` SET `unit_flags`=768 WHERE entry IN (40834, 40837);
UPDATE `creature` SET `position_z`=1439.30 WHERE `guid`=710890;
UPDATE `creature` SET `position_z`=1438.67 WHERE `guid`=710890;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=41084;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11461 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11461 AND `id`=1;
UPDATE `gossip_menu_option` SET `action_menu_id`=11462 WHERE `menu_id`=11461 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11463 WHERE `menu_id`=11462 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11464 WHERE `menu_id`=11463 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11464 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11464 AND `id`=1;

DELETE FROM `creature_text` WHERE `entry`=41114;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41114,0,1,'Gotcha Chickenlips! You\'d best get talky, or I\'ll get stabby.',12,0,100,0,0,0,'Comment'),
(41114,1,0,'We don\'t need to tell Omnuron about this.',12,0,100,0,0,0,'Comment'),
(41114,1,1,'Easy. We still need the info.',12,0,100,0,0,0,'Comment'),
(41114,1,2,'Hey, you don\'t waste any time.',12,0,100,0,0,0,'Comment'),
(41114,1,3,'There\'s more where that came from, Marion!',12,0,100,0,0,0,'Comment'),
(41114,1,4,'Brutal!',12,0,100,0,0,0,'Comment'),
(41114,1,5,'Wait, was I supposed to be the good cop?',12,0,100,0,0,0,'Comment'),
(41114,1,6,'I\'m not sure that\'s strictly necessary.',12,0,100,0,0,0,'Comment'),
(41114,2,0,'We\'re finished with this filth.',12,0,100,0,0,0,'Comment'),
(41114,3,0,'You\'re a better person than I. But I suppose the harpies are just pawns here.',12,0,100,0,0,0,'Comment'),
(41114,4,0,'Meet me back at Aviana\'s Shrine,',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41112;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41112,0,0,'Step away from there!',12,0,100,0,0,0,'Comment');

-- Harpy Signal Fire
SET @ENTRY := 203187;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,85,77041,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Marion Wormwing");

UPDATE `gameobject_template` SET `AIName`='', `ScriptName`='go_harpy_signal_fire' WHERE  `entry`=203187;
UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=41114;
UPDATE `creature_template_addon` SET `bytes1`=0, `auras`='76863' WHERE `entry`=41114;
UPDATE `creature_template` SET `speed_run`=2.682063 WHERE `entry`=41114;

-- Marion Wormwing
SET @ENTRY := 41112;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11461,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11461,0,0,0,45,0,1,0,0,0,0,19,41114,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Data 1 to Thisalee"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11464,1,0,0,33,41170,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,11464,0,0,0,33,41170,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,11464,1,0,0,72,41112,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,0,11464,0,0,0,72,41112,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,7,0,54,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Hostile"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,0,11464,0,0,0,45,0,2,0,0,0,0,19,41114,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Data 2 to Thisalee"),
(@ENTRY,@SOURCETYPE,9,0,62,0,100,0,11464,1,0,0,45,0,3,0,0,0,0,19,41114,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Data 3 to Thisalee"),
(@ENTRY,@SOURCETYPE,10,0,54,0,100,0,0,0,0,0,49,14,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Invoker"),
(@ENTRY,@SOURCETYPE,11,0,4,0,100,0,0,0,0,0,42,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,12,0,2,0,100,1,0,25,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 25% - Set Friendly"),
(@ENTRY,@SOURCETYPE,13,0,2,0,100,1,0,25,0,0,11,76835,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 25% - Summon Thisalee"),
(@ENTRY,@SOURCETYPE,14,15,38,0,100,0,0,1,0,0,11,46598,0,0,0,0,0,19,41114,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Ride Thisalee"),
(@ENTRY,@SOURCETYPE,15,16,61,0,100,0,0,0,0,0,33,41169,0,0,0,0,0,18,1,0,0,0.0,0.0,0.0,0.0,"Link - First Quest Credit"),
(@ENTRY,@SOURCETYPE,16,0,61,0,100,0,0,0,0,0,24,39942,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Evade"),
(@ENTRY,@SOURCETYPE,17,0,38,0,100,0,0,2,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Die"),
(@ENTRY,@SOURCETYPE,18,0,0,0,100,0,500,500,3500,3500,11,77160,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Nimbus Bolt");

-- Thisalee Crow
SET @ENTRY := 41114;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,76863,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Transform"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0"),
(@ENTRY,@SOURCETYPE,3,8,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,9,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,41114,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 4"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,41114,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,7,0,54,0,100,0,0,0,0,0,45,0,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 1 to Marion"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,45,0,2,0,0,0,0,19,41112,0,0,0.0,0.0,0.0,0.0,"Link - Set Data 2 to Marion"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Passenger"),
(@ENTRY,@SOURCETYPE,10,0,54,0,100,0,0,0,0,0,33,41169,0,0,0,0,0,18,30,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Quest Credit"),
(@ENTRY,@SOURCETYPE,11,12,52,0,100,0,4,41114,0,0,28,76863,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Remove Transformation"),
(@ENTRY,@SOURCETYPE,12,13,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,4932.82,-2699.59,1441.86,4.17,"Link - Move To Pos"),
(@ENTRY,@SOURCETYPE,13,14,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,14,15,61,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Fly"),
(@ENTRY,@SOURCETYPE,15,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `creature_template` SET `unit_class`=2 WHERE `entry`=41112;

DELETE FROM `creature_text` WHERE `entry`=41005;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41005,0,0,'Mother of all winged creatures, hear my prayer and reveal yourself... a vision! What could this mean? I will report this to Omnuron.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41084;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41084,0,0,'Blaithe appears above your head with an ear-splitting caw!',42,0,100,0,0,0,'Comment');

-- Choluna
SET @ENTRY := 41005;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,25664,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,41005,0,0,11,76787,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Egg");

DELETE FROM `creature_text` WHERE `entry`=41089;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41089,0,0,'This is the one. The ancient will be ours.',12,0,100,0,0,0,'Comment'),
(41089,1,0,'Take the others to the Firelands Hatchery! Soon we will possess the skies.',12,0,100,0,0,0,'Comment');

-- Vision of Aviana's Egg
SET @ENTRY := 41092;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,76791,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Effect");

-- Vision of Sethria
SET @ENTRY := 41089;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,91218,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Ghost Visual"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,4883.7,-2810.22,1437.67,5.35,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,8,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,41089,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,41089,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Force Despawn");

UPDATE `quest_template` SET `RewardSpellCast`=0 WHERE `Id`=25664;

-- Injured Fawn
SET @ENTRY := 40000;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,3,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,2,3,38,0,100,0,0,1,0,0,33,40031,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Mylune
SET @ENTRY := 39930;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2000,2000,2000,2000,45,0,1,0,0,0,0,11,40000,15,0,0.0,0.0,0.0,0.0,"OOC - Set Data 1 to Fawn");

DELETE FROM `spell_script_names` WHERE `spell_id` = '77231';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77231, 'spell_pry_armor');

UPDATE `gameobject_template` SET `ScriptName`='go_shadow_cloak_generator' WHERE `entry`=203208;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=41224;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=41234;

DELETE FROM `creature_text` WHERE `entry`=41226;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41226,0,0,'Disabling the shadow cloak reveals one of Sethria\'s Hatchlings!',16,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41224;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41224,0,0,'Disabling the shadow cloak reveals Aviana\'s Egg!',16,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41234;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41234,0,0,'This is it! You\'ve found Aviana\'s Egg! Keep it safe while I go get help.',12,0,100,0,0,0,'Comment'),
(41234,1,0,'Defend the Egg!',42,0,100,0,0,0,'Comment');

-- Thisalee Crow
SET @ENTRY := 41234;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,41234,0,0,69,0,0,0,0,0,0,8,0,0,0,3861.39,-2244.36,1165.82,4.2,"After Talk 0 - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,0,8,0,0,0,11,77319,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Summon Druids"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,41234,0,0,1,1,41234,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

-- Aviana's Egg
SET @ENTRY := 41224;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,1,0,0,69,0,0,0,0,0,0,8,0,0,0,3969.22,-2242.45,1201.74,5.64,"On Passenger Boarded - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,8000,8000,35000,35000,12,41029,4,60000,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"OOC - Summon Dragonkin"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,1,0,0,33,41218,0,0,0,0,0,18,30,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,0,8,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0");

-- Druid of the Talon
SET @ENTRY := 41243;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,11,41224,500,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move To Egg"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,11,46598,0,0,0,0,0,19,41224,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Ride Egg"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

UPDATE `creature_template` SET `speed_run`=2.85206 WHERE `entry`=41243;

UPDATE `creature_template` SET `speed_run`=1.852063, `InhabitType`=4 WHERE `entry` IN (41243, 41234);

-- Sethria's Hatchling
SET @ENTRY := 41226;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,6000,12000,15000,11,78143,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Twilight Breath"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0");

UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=120 WHERE `guid`=735200;

DELETE FROM `creature_text` WHERE `entry`=41255;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41255,0,0,'You are little more than insects! When I am done with you, I will burn your shrine to the ground!',12,0,100,0,0,0,'Comment'),
(41255,1,0,'You buy time... but not your lives... my hatchery remains...',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `speed_run`=1.6820, `InhabitType`=4 WHERE `entry`=41287;
UPDATE `creature` SET `phaseMask`=1 WHERE `id`=41287;

DELETE FROM `creature_text` WHERE `entry`=41287;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41287,0,0,'We\'re coming! keep her occupied while we loop around for an attack.',12,0,100,0,0,0,'Comment');

-- Sethria
SET @ENTRY := 41255;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,0,1,100,0,500,500,3000,3000,11,78129,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Bolt"),
(@ENTRY,@SOURCETYPE,2,0,2,1,100,1,0,66,0,0,3,41261,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 66% - Morph into Dragon"),
(@ENTRY,@SOURCETYPE,3,0,2,1,100,1,0,66,0,0,11,63723,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 66% - Cast Shadow Nova"),
(@ENTRY,@SOURCETYPE,4,0,2,1,100,1,0,66,0,0,11,78160,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 66% - Cast Twilight Fissure"),
(@ENTRY,@SOURCETYPE,5,0,2,1,100,1,0,66,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 66% - Set Phase 2"),
(@ENTRY,@SOURCETYPE,6,0,0,2,100,0,3000,3000,8500,8500,11,78143,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Breath"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 1"),
(@ENTRY,@SOURCETYPE,8,0,7,0,100,0,0,0,0,0,3,41255,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Demorph"),
(@ENTRY,@SOURCETYPE,9,0,7,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Phase 0");

DELETE FROM `spell_script_names` WHERE `spell_id` = '77346';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77346, 'spell_signal_rocket');

UPDATE `creature_template` SET `unit_flags`=256 WHERE `entry`=41287;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=25807;
UPDATE `quest_template` SET `ExclusiveGroup`=0 WHERE `Id`=25807;

DELETE FROM `creature_text` WHERE `entry`=47002;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47002,0,0,'The guardian of the skies has taken flight again! This is encouraging news. But much remains undone, and we must turn our attention elsewhere...',12,0,100,0,0,0,'Comment');

-- Aviana
SET @ENTRY := 41308;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,20,0,100,0,25807,0,0,0,12,47002,3,60000,0,0,0,8,0,0,0,4893.86,-2787.87,1437.61,4.39,"On Quest Rewarded - Summon Ysera"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=41308;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41308,0,0,'A vision of Ysera materializes before you.',16,0,100,0,0,0,'Comment');

DELETE FROM `creature_template_addon` WHERE `entry` = '47002';
INSERT INTO `creature_template_addon` (`entry`, `bytes1`, `auras`) VALUES
(47002, '50397184', '76743');

UPDATE `creature_template` SET `InhabitType`=3, `HoverHeight`=1.2 WHERE `entry`=47002;

DELETE FROM `conditions` WHERE `SourceEntry` = '25830' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25830, 25807, 0),
(20, 8, 25830, 25520, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25830' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25830, 25807, 0),
(19, 8, 25830, 25520, 0);

UPDATE `creature_template` SET `ScriptName`='npc_generic_dave_trigger' WHERE `entry`=38821;
UPDATE `quest_template` SET `PrevQuestId`='25560' WHERE `Id`=29177;
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `speed_run`=2.12286, `VehicleId`=701, `spell1`=74183 WHERE  `entry`=40719;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_aviana_guardian' WHERE `entry`=40723;

-- Aviana's Guardian
SET @ENTRY := 40719;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

DELETE FROM `creature_text` WHERE `entry`=40578;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40578,0,0,'Grab a Lance from the Racks',42,0,100,0,0,0,'Comment');

-- Farden Talonshrike
SET @ENTRY := 40578;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,25523,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

-- Guardian Flag
SET @ENTRY := 202973;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,2000,2000,2000,2000,33,47459,0,0,0,0,0,18,7,0,0,0.0,0.0,0.0,0.0,"Update - Quest Credit");

-- Thol'embaar Summon Bunny
SET @ENTRY := 40121;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,12,40107,4,120000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon TholEmbaar");

UPDATE `creature_template_addon` SET `auras`='74788' WHERE `entry`=40107;

DELETE FROM `creature_text` WHERE `entry`=40107;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40107,0,0,'Fool of a mortal. Flesh burns.',12,0,100,0,0,0,'Comment'),
(40107,1,0,'Others will come... the age of mortals... has passed.',12,0,100,0,0,0,'Comment');

-- Thol'embaar
SET @ENTRY := 40107;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,8,15800,18300,11,80600,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Flame Stomp on Close"),
(@ENTRY,@SOURCETYPE,1,0,9,0,100,0,0,8,10000,30000,11,74788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Ring of Fire on Close"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,40107,0,0,19,559872,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Remove Flags"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=39933;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39933,1,0,'Madness. Chaos. Much as I thrill to see the titans\' work undone, I do wish to remain alive when the master returns. I will help you.',12,0,100,0,0,0,''),
(39933,2,0,'The dark ashes swirl around Tyrus Blackhorn, who utters an incantation:',16,0,100,0,0,0,'Comment'),
(39933,3,0,'Ashes from the plane below, scattered by the hand of foe...',12,0,100,0,0,0,'Comment'),
(39933,4,0,'Gods of terror, quake and thunder, tear these mortal lands asunder!',12,0,100,0,0,0,'Comment'),
(39933,5,0,'Tyrus Blackhorn barks a cruel laugh.',16,0,100,0,0,0,'Comment'),
(39933,6,0,'Thank you! Your heroism in the Inferno has made my escape possible.',12,0,100,0,0,0,'Comment'),
(39933,7,0,'As a reward, I will allow you to live.',12,0,100,0,0,0,'Comment'),
(39933,8,0,'But your time will coon soon enough. Yes. Soon enough...',0,0,100,0,0,0,'Comment');

-- Tyrus Blackhorn
SET @ENTRY := 39933;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,98,11316,15772,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Update Gossip"),
(@ENTRY,@SOURCETYPE,1,2,62,0,100,0,11325,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Gossip Close"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11325,0,0,0,33,40056,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select  - Kill Credit"),
(@ENTRY,@SOURCETYPE,4,0,20,0,100,0,25428,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,39933,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,39933,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,39933,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,39933,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,5,39933,0,0,1,6,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,6,39933,0,0,1,7,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7");

UPDATE `creature_template` SET `npcflag`=1, `InhabitType`=3, `modelid1`=31729, `ScriptName` = 'npc_climbing_tree_start' WHERE `entry` IN (40190, 52676);

-- Keeper Taldros
SET @ENTRY := 39932;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,25462,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=39932;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39932,0,0,'Find a Tree to Climb',42,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (74922, 74974);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74922, 'spell_climb_up_tree'),
(74974, 'spell_climb_down_tree');

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=40250;
UPDATE `creature_template` SET `modelid1`=32815 WHERE `entry`=40250;

DELETE FROM `creature` WHERE `id` = '40250';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(730757, 40250, 1, 1, 1, 0, 0, 5252.06, -1436.05, 1396.06, 6.04507, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730758, 40250, 1, 1, 1, 0, 0, 5288.8, -1533.62, 1400.48, 0.523599, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730759, 40250, 1, 1, 1, 0, 0, 5253.11, -1433.89, 1395.7, 4.7673, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730760, 40250, 1, 1, 1, 0, 0, 5229.45, -1521.92, 1390.35, 0.491736, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730761, 40250, 1, 1, 1, 0, 0, 5249.17, -1433.97, 1396.25, 0.126973, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730762, 40250, 1, 1, 1, 0, 0, 5291.18, -1445.32, 1400.31, 2.02958, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730763, 40250, 1, 1, 1, 0, 0, 5303.11, -1486.93, 1400.37, 0.523599, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730764, 40250, 1, 1, 1, 0, 0, 5288.92, -1538.05, 1400.39, 2.39878, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730771, 40250, 1, 1, 1, 0, 0, 5303.46, -1484.15, 1400.27, 1.30599, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730772, 40250, 1, 1, 1, 0, 0, 5227.1, -1520.46, 1389.37, 4.48358, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730773, 40250, 1, 1, 1, 0, 0, 5225.55, -1470.9, 1390.94, 0.523599, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730775, 40250, 1, 1, 1, 0, 0, 5224.28, -1467.03, 1396.27, 0.523599, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730783, 40250, 1, 1, 1, 0, 0, 5255.12, -1535.94, 1390.42, 1.65457, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730784, 40250, 1, 1, 1, 0, 0, 5227.74, -1518.09, 1389.29, 0.442086, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730793, 40250, 1, 1, 1, 0, 0, 5292.29, -1448.41, 1399.21, 0.523599, 300, 0, 0, 1, 0, 0, 0, 0, 0),
(730796, 40250, 1, 1, 1, 0, 0, 5259.5, -1536.13, 1394.29, 0.523599, 300, 0, 0, 1, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=40240;

-- Hyjal Bear Cub
SET @ENTRY := 40240;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,56,54439,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Item"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn");

UPDATE `creature_template` SET `spell2`=74974 WHERE `entry`=40250;

DELETE FROM `spell_script_names` WHERE `spell_id` = '75139';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75139, 'spell_chuck_a_bear');

UPDATE `creature_template` SET `modelid1`=31379, `modelid2`=31379 WHERE `entry`=40242;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=40240;
UPDATE `creature_template` SET `lootid`=46911 WHERE `entry`=46911;

DELETE FROM `creature_loot_template` WHERE `entry` = '46911';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(46911, 39512, 80.9802, 1, 0, 1, 1),
(46911, 39513, 18.8557, 1, 0, 1, 1),
(46911, 52325, 0.0005, 1, 0, 1, 1),
(46911, 52327, 9.2824, 1, 0, 1, 1),
(46911, 52328, 0.0013, 1, 0, 1, 1),
(46911, 52363, 0.05, 1, 0, 1, 1),
(46911, 52364, 0.05, 1, 0, 1, 1),
(46911, 52365, 0.05, 1, 0, 1, 1),
(46911, 52366, 0.05, 1, 0, 1, 1),
(46911, 52367, 0.05, 1, 0, 1, 1),
(46911, 52368, 0.05, 1, 0, 1, 1),
(46911, 52373, 0.05, 1, 0, 1, 1),
(46911, 52374, 0.05, 1, 0, 1, 1),
(46911, 52375, 0.05, 1, 0, 1, 1),
(46911, 52376, 0.05, 1, 0, 1, 1),
(46911, 52377, 0.05, 1, 0, 1, 1),
(46911, 52378, 0.05, 1, 0, 1, 1),
(46911, 52379, 0.05, 1, 0, 1, 1),
(46911, 52382, 0.05, 1, 0, 1, 1),
(46911, 52383, 0.05, 1, 0, 1, 1),
(46911, 52385, 0.05, 1, 0, 1, 1),
(46911, 52386, 0.05, 1, 0, 1, 1),
(46911, 52388, 0.05, 1, 0, 1, 1),
(46911, 52496, 0.05, 1, 0, 1, 1),
(46911, 52506, -1.3923, 1, 0, 1, 1),
(46911, 54574, -0.0552, 1, 0, 1, 1),
(46911, 55281, 0.0074, 1, 0, 1, 1),
(46911, 55282, 0.0055, 1, 0, 1, 1),
(46911, 55283, 0.0073, 1, 0, 1, 1),
(46911, 55290, 0.0089, 1, 0, 1, 1),
(46911, 55291, 0.0078, 1, 0, 1, 1),
(46911, 55292, 0.0089, 1, 0, 1, 1),
(46911, 55299, 0.0004, 1, 0, 1, 1),
(46911, 55300, 0.0016, 1, 0, 1, 1),
(46911, 55301, 0.0022, 1, 0, 1, 1),
(46911, 55308, 0.0062, 1, 0, 1, 1),
(46911, 55309, 0.0127, 1, 0, 1, 1),
(46911, 55310, 0.0105, 1, 0, 1, 1),
(46911, 55317, 0.0009, 1, 0, 1, 1),
(46911, 55318, 0.002, 1, 0, 1, 1),
(46911, 55319, 0.0009, 1, 0, 1, 1),
(46911, 55326, 0.0065, 1, 0, 1, 1),
(46911, 55327, 0.0098, 1, 0, 1, 1),
(46911, 55328, 0.0067, 1, 0, 1, 1),
(46911, 55335, 0.0027, 1, 0, 1, 1),
(46911, 55336, 0.0029, 1, 0, 1, 1),
(46911, 55337, 0.0065, 1, 0, 1, 1),
(46911, 55344, 0.0064, 1, 0, 1, 1),
(46911, 55345, 0.006, 1, 0, 1, 1),
(46911, 55346, 0.0074, 1, 0, 1, 1),
(46911, 55353, 0.0058, 1, 0, 1, 1),
(46911, 55354, 0.0035, 1, 0, 1, 1),
(46911, 55355, 0.0022, 1, 0, 1, 1),
(46911, 55362, 0.0125, 1, 0, 1, 1),
(46911, 55363, 0.0098, 1, 0, 1, 1),
(46911, 55364, 0.0147, 1, 0, 1, 1),
(46911, 55371, 0.0065, 1, 0, 1, 1),
(46911, 55372, 0.0078, 1, 0, 1, 1),
(46911, 55373, 0.0091, 1, 0, 1, 1),
(46911, 55380, 0.0055, 1, 0, 1, 1),
(46911, 55381, 0.01, 1, 0, 1, 1),
(46911, 55382, 0.0065, 1, 0, 1, 1),
(46911, 55389, 0.006, 1, 0, 1, 1),
(46911, 55390, 0.0033, 1, 0, 1, 1),
(46911, 55391, 0.0055, 1, 0, 1, 1),
(46911, 55398, 0.016, 1, 0, 1, 1),
(46911, 55399, 0.0151, 1, 0, 1, 1),
(46911, 55400, 0.0191, 1, 0, 1, 1),
(46911, 55407, 0.0035, 1, 0, 1, 1),
(46911, 55408, 0.0058, 1, 0, 1, 1),
(46911, 55409, 0.004, 1, 0, 1, 1),
(46911, 55416, 0.0354, 1, 0, 1, 1),
(46911, 55417, 0.0451, 1, 0, 1, 1),
(46911, 55418, 0.036, 1, 0, 1, 1),
(46911, 55425, 0.0073, 1, 0, 1, 1),
(46911, 55426, 0.0064, 1, 0, 1, 1),
(46911, 55427, 0.0062, 1, 0, 1, 1),
(46911, 55434, 0.0294, 1, 0, 1, 1),
(46911, 55435, 0.0263, 1, 0, 1, 1),
(46911, 55436, 0.0283, 1, 0, 1, 1),
(46911, 55443, 0.0053, 1, 0, 1, 1),
(46911, 55444, 0.0044, 1, 0, 1, 1),
(46911, 55445, 0.0036, 1, 0, 1, 1),
(46911, 55452, 0.0044, 1, 0, 1, 1),
(46911, 55453, 0.0073, 1, 0, 1, 1),
(46911, 55454, 0.008, 1, 0, 1, 1),
(46911, 55461, 0.0055, 1, 0, 1, 1),
(46911, 55462, 0.0044, 1, 0, 1, 1),
(46911, 55463, 0.0069, 1, 0, 1, 1),
(46911, 55470, 0.0005, 1, 0, 1, 1),
(46911, 55471, 0.0011, 1, 0, 1, 1),
(46911, 55472, 0.0011, 1, 0, 1, 1),
(46911, 55479, 0.018, 1, 0, 1, 1),
(46911, 55480, 0.0167, 1, 0, 1, 1),
(46911, 55481, 0.0196, 1, 0, 1, 1),
(46911, 55488, 0.0167, 1, 0, 1, 1),
(46911, 55489, 0.0149, 1, 0, 1, 1),
(46911, 55490, 0.0162, 1, 0, 1, 1),
(46911, 55497, 0.0125, 1, 0, 1, 1),
(46911, 55498, 0.01, 1, 0, 1, 1),
(46911, 55499, 0.0134, 1, 0, 1, 1),
(46911, 55506, 0.0071, 1, 0, 1, 1),
(46911, 55507, 0.0125, 1, 0, 1, 1),
(46911, 55508, 0.0105, 1, 0, 1, 1),
(46911, 55515, 0.0114, 1, 0, 1, 1),
(46911, 55516, 0.0104, 1, 0, 1, 1),
(46911, 55517, 0.0174, 1, 0, 1, 1),
(46911, 55524, 0.0125, 1, 0, 1, 1),
(46911, 55525, 0.0102, 1, 0, 1, 1),
(46911, 55526, 0.0162, 1, 0, 1, 1),
(46911, 55533, 0.0125, 1, 0, 1, 1),
(46911, 55534, 0.0193, 1, 0, 1, 1),
(46911, 55535, 0.0116, 1, 0, 1, 1),
(46911, 55542, 0.0109, 1, 0, 1, 1),
(46911, 55543, 0.0138, 1, 0, 1, 1),
(46911, 55544, 0.012, 1, 0, 1, 1),
(46911, 55551, 0.0096, 1, 0, 1, 1),
(46911, 55552, 0.0111, 1, 0, 1, 1),
(46911, 55553, 0.0122, 1, 0, 1, 1),
(46911, 55560, 0.0087, 1, 0, 1, 1),
(46911, 55561, 0.0136, 1, 0, 1, 1),
(46911, 55562, 0.0145, 1, 0, 1, 1),
(46911, 55569, 0.0102, 1, 0, 1, 1),
(46911, 55570, 0.0145, 1, 0, 1, 1),
(46911, 55571, 0.0117, 1, 0, 1, 1),
(46911, 55578, 0.0109, 1, 0, 1, 1),
(46911, 55579, 0.0094, 1, 0, 1, 1),
(46911, 55580, 0.0129, 1, 0, 1, 1),
(46911, 55587, 0.0124, 1, 0, 1, 1),
(46911, 55588, 0.0158, 1, 0, 1, 1),
(46911, 55589, 0.013, 1, 0, 1, 1),
(46911, 55596, 0.0162, 1, 0, 1, 1),
(46911, 55597, 0.0134, 1, 0, 1, 1),
(46911, 55598, 0.05, 1, 0, 1, 1),
(46911, 55605, 0.0136, 1, 0, 1, 1),
(46911, 55606, 0.0147, 1, 0, 1, 1),
(46911, 55607, 0.0111, 1, 0, 1, 1),
(46911, 55614, 0.01, 1, 0, 1, 1),
(46911, 55615, 0.0116, 1, 0, 1, 1),
(46911, 55616, 0.018, 1, 0, 1, 1),
(46911, 55623, 0.0085, 1, 0, 1, 1),
(46911, 55624, 0.016, 1, 0, 1, 1),
(46911, 55625, 0.01, 1, 0, 1, 1),
(46911, 55632, 0.0105, 1, 0, 1, 1),
(46911, 55633, 0.0136, 1, 0, 1, 1),
(46911, 55634, 0.0156, 1, 0, 1, 1),
(46911, 55641, 0.0105, 1, 0, 1, 1),
(46911, 55642, 0.0174, 1, 0, 1, 1),
(46911, 55643, 0.0184, 1, 0, 1, 1),
(46911, 55650, 0.0127, 1, 0, 1, 1),
(46911, 55651, 0.0104, 1, 0, 1, 1),
(46911, 55652, 0.0116, 1, 0, 1, 1),
(46911, 55659, 0.0165, 1, 0, 1, 1),
(46911, 55660, 0.012, 1, 0, 1, 1),
(46911, 55661, 0.0156, 1, 0, 1, 1),
(46911, 55668, 0.012, 1, 0, 1, 1),
(46911, 55669, 0.0133, 1, 0, 1, 1),
(46911, 55670, 0.05, 1, 0, 1, 1),
(46911, 55677, 0.0118, 1, 0, 1, 1),
(46911, 55678, 0.0131, 1, 0, 1, 1),
(46911, 55679, 0.0134, 1, 0, 1, 1),
(46911, 55686, 0.0138, 1, 0, 1, 1),
(46911, 55687, 0.0145, 1, 0, 1, 1),
(46911, 55688, 0.0113, 1, 0, 1, 1),
(46911, 55695, 0.0109, 1, 0, 1, 1),
(46911, 55696, 0.01, 1, 0, 1, 1),
(46911, 55697, 0.0153, 1, 0, 1, 1),
(46911, 55704, 0.0236, 1, 0, 1, 1),
(46911, 55705, 0.016, 1, 0, 1, 1),
(46911, 55706, 0.0161, 1, 0, 1, 1),
(46911, 55713, 0.0238, 1, 0, 1, 1),
(46911, 55714, 0.0176, 1, 0, 1, 1),
(46911, 55715, 0.0178, 1, 0, 1, 1),
(46911, 55722, 0.0142, 1, 0, 1, 1),
(46911, 55723, 0.0169, 1, 0, 1, 1),
(46911, 55724, 0.0258, 1, 0, 1, 1),
(46911, 55731, 0.0185, 1, 0, 1, 1),
(46911, 55732, 0.0184, 1, 0, 1, 1),
(46911, 55733, 0.022, 1, 0, 1, 1),
(46911, 55740, 0.0207, 1, 0, 1, 1),
(46911, 55741, 0.016, 1, 0, 1, 1),
(46911, 55742, 0.0205, 1, 0, 1, 1),
(46911, 55749, 0.0193, 1, 0, 1, 1),
(46911, 55750, 0.0156, 1, 0, 1, 1),
(46911, 55751, 0.0193, 1, 0, 1, 1),
(46911, 55758, 0.0214, 1, 0, 1, 1),
(46911, 55759, 0.0169, 1, 0, 1, 1),
(46911, 55760, 0.0191, 1, 0, 1, 1),
(46911, 55767, 0.016, 1, 0, 1, 1),
(46911, 55768, 0.0174, 1, 0, 1, 1),
(46911, 55769, 0.0198, 1, 0, 1, 1),
(46911, 60486, 0.0271, 1, 0, 1, 1),
(46911, 62065, 0.1, 1, 0, 1, 1),
(46911, 62101, 0.1, 1, 0, 1, 1),
(46911, 63024, 0.0002, 1, 0, 1, 1),
(46911, 63025, 0.0002, 1, 0, 1, 1),
(46911, 63122, 0.0029, 1, 0, 1, 1),
(46911, 66641, 0.0027, 1, 0, 1, 1),
(46911, 66879, 0.0013, 1, 0, 1, 1),
(46911, 66880, 0.0011, 1, 0, 1, 1),
(46911, 66882, 0.0007, 1, 0, 1, 1),
(46911, 66883, 0.0016, 1, 0, 1, 1),
(46911, 66895, 0.0013, 1, 0, 1, 1),
(46911, 66952, 0.0016, 1, 0, 1, 1),
(46911, 66953, 0.0004, 1, 0, 1, 1),
(46911, 66954, 0.0013, 1, 0, 1, 1),
(46911, 66955, 0.0015, 1, 0, 1, 1),
(46911, 66956, 0.0016, 1, 0, 1, 1),
(46911, 66957, 0.0013, 1, 0, 1, 1),
(46911, 66958, 0.0013, 1, 0, 1, 1),
(46911, 66977, 0.0011, 1, 0, 1, 1),
(46911, 66978, 0.0056, 1, 0, 1, 1),
(46911, 66979, 0.0016, 1, 0, 1, 1),
(46911, 66980, 0.0018, 1, 0, 1, 1),
(46911, 66981, 0.0016, 1, 0, 1, 1),
(46911, 66982, 0.0009, 1, 0, 1, 1),
(46911, 67024, 0.0013, 1, 0, 1, 1),
(46911, 67027, 0.0016, 1, 0, 1, 1),
(46911, 67029, 0.0007, 1, 0, 1, 1),
(46911, 67032, 0.0022, 1, 0, 1, 1),
(46911, 67037, 0.0011, 1, 0, 1, 1),
(46911, 67040, 0.0013, 1, 0, 1, 1),
(46911, 67088, 0.0013, 1, 0, 1, 1),
(46911, 67098, 0.0011, 1, 0, 1, 1),
(46911, 67099, 0.0005, 1, 0, 1, 1),
(46911, 67101, 0.0016, 1, 0, 1, 1),
(46911, 67102, 0.0016, 1, 0, 1, 1),
(46911, 67103, 0.0005, 1, 0, 1, 1),
(46911, 67104, 0.0007, 1, 0, 1, 1),
(46911, 67105, 0.0005, 1, 0, 1, 1),
(46911, 67106, 0.0013, 1, 0, 1, 1),
(46911, 67109, 0.0018, 1, 0, 1, 1),
(46911, 67539, 0.1, 1, 0, 1, 1),
(46911, 68783, 0.0008, 1, 0, 1, 1),
(46911, 69820, 0.0002, 1, 0, 1, 1);

UPDATE `creature_template` SET `InhabitType`=1 WHERE `entry`=46911;
UPDATE `gameobject_template` SET `ScriptName`='go_hyjal_flameward' WHERE `entry`=202927;

DELETE FROM `spell_script_names` WHERE `spell_id` = '75470';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75470, 'spell_flameward_activated');

DELETE FROM `creature_text` WHERE `entry`=40461;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40461,0,0,'Victory! The flameward has been defended.',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `modelid1`=21072, `scale`=1 WHERE `entry`=40461;

-- Flameward Activated
SET @ENTRY := 40461;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,75454,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Apply Shield"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,1,60000,60000,0,0,1,0,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,8000,8000,8000,8000,12,46925,4,60000,0,0,0,8,0,0,0,4388.35,-2569.14,1119.96,1.52,"OOC - Summon Ashbearer");

DELETE FROM `creature_template_addon` WHERE `entry` = '46998';
INSERT INTO `creature_template_addon` (`entry`, `bytes1`, `auras`) VALUES
(46998, '50397184', '76743');

UPDATE `creature_template` SET `InhabitType`=3, `HoverHeight`=1.2 WHERE `entry`=46998;

DELETE FROM `creature_text` WHERE `entry`=46998;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46998,0,0,'A vision of Ysera materializes before you.',16,0,100,0,0,0,'Comment'),
(46998,1,0,'So Tortolla has risen to fight at our side. You are wise, it is difficult to earn that ancient\'s trust. He will be a stalwart companion.',12,0,100,0,0,0,'Comment');

-- Vision of Ysera
SET @ENTRY := 46998;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46998,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

UPDATE `quest_template` SET `SourceSpellId`=77725 WHERE `Id`=25915;
UPDATE `quest_template` SET `SourceSpellId`=77725 WHERE `Id`=25923;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11528 AND `id`=0;

-- Garunda Mountainpeak
SET @ENTRY := 41498;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11528,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11528,0,0,0,85,77725,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Child of Tortolla"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,0,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove Child of Tortolla");

DELETE FROM `conditions` WHERE `SourceGroup`=11528 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11528, 0, 0, 0, 9, 0, 25915, 0, 0, 0, 0, 0, '', 'Garunda Mountainpeak - Show gossip only if quest 25915 is active'),
(15, 11528, 0, 0, 1, 9, 0, 25923, 0, 0, 0, 0, 0, '', 'Garunda Mountainpeak - Show gossip only if quest 25915 is active');

DELETE FROM `creature_text` WHERE `entry`=41581;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41581,0,0,'Child of Tortolla approaches the Nemesis crystal and cautiously examines it.',16,0,100,0,0,0,'Comment');

-- Child of Tortolla
SET @ENTRY := 41581;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,1,0,1,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,52,0,100,0,0,41581,0,0,11,0,0,0,0,0,0,10,712034,38821,0,0.0,0.0,0.0,0.0,"After Talk 0 - Cast Examine on Trigger"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,41602,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

UPDATE `creature` SET `modelid`=21072 WHERE `guid`=712034;

DELETE FROM `creature_addon` WHERE `guid` = '712034';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(712034, '77742');

-- Child of Tortolla
SET @ENTRY := 41581;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,1,0,1,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,52,0,100,0,0,41581,0,0,11,77753,0,0,0,0,0,10,712034,38821,0,0.0,0.0,0.0,0.0,"After Talk 0 - Cast Examine on Trigger"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,41602,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,29,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Run"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,6,0,4,0,100,0,0,0,0,0,11,77731,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Water Gout"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,1000,1000,15500,15500,11,16727,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast War Stomp"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,3500,3500,7500,7500,11,77731,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Gout"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,25000,25000,25000,25000,0,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"IC - None"),
(@ENTRY,@SOURCETYPE,10,0,54,0,100,0,0,0,0,0,85,77736,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Aura Turtle Power"),
(@ENTRY,@SOURCETYPE,11,0,6,0,100,0,0,0,0,0,28,77736,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Death - Remove Turtle Power from Owner"),
(@ENTRY,@SOURCETYPE,12,0,35,0,100,0,41581,0,0,0,28,77736,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Summon Despawned - Remove Turtle Power from Owner"),
(@ENTRY,@SOURCETYPE,13,0,36,0,100,0,0,0,0,0,28,77736,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Corpse Removed - Remove Turtle Power from Owner");

DELETE FROM `creature_text` WHERE `entry`=41614;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41614,0,0,'Nemesis is about to erupt! Get under Tooga\'s shell!',42,0,100,0,0,0,'Comment');

-- Nemesis
SET @ENTRY := 41614;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,6000,21000,21000,11,77777,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Molten Fury"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,6000,6000,21000,21000,1,0,5000,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Talk 0");

DELETE FROM `spell_script_names` WHERE `spell_id` = '77770';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77770, 'spell_tortolla_shell');

DELETE FROM `creature_text` WHERE `entry`=39619;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39619,1,0,'Fine. I\'ll come with you. This had better be important.',12,0,0,0,0,0,''),
(39619,1,2,'You have something to show me?',12,0,0,0,0,0,''),
(39619,1,3,'You want something?',12,0,0,0,0,0,''),
(39619,2,0,'Lead the Twilight Recruit away from the Group and use the Blackjack to knock him out.',41,0,100,0,0,0,'');

DELETE FROM `creature_text` WHERE `entry`=39453;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39453,0,0,'Thank you!',12,0,100,0,0,0,'Comment'),
(39453,0,1,'Thanks!',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '74359';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74359, 'spell_hyjal_extinguish_flames');

DELETE FROM `creature_text` WHERE `entry`=39601;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39601,0,0,'Do rocks float on water?',12,0,100,0,0,0,'Comment'),
(39601,1,0,'Do murderers kill?',12,0,100,0,0,0,'Comment'),
(39601,2,0,'Are the oceans filled with water?',12,0,100,0,0,0,'Comment'),
(39601,3,0,'Do rivers flow upstream?',12,0,100,0,0,0,'Comment'),
(39601,4,0,'Is blood red?',12,0,100,0,0,0,'Comment'),
(39601,5,0,'Is ice hot?',12,0,100,0,0,0,'Comment'),
(39601,6,0,'Are slaves free?',12,0,100,0,0,0,'Comment'),
(39601,7,0,'Is fire hot?',12,0,100,0,0,0,'Comment'),
(39601,8,0,'Do maggots feast on corpses?',12,0,100,0,0,0,'Comment'),
(39601,9,0,'Does fire consume stone?',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_orb_of_ascension' WHERE `entry`=39601;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (73982, 73983, 76643);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73982, 'spell_answer_yes'),
(73983, 'spell_answer_no'),
(76643, 'spell_dismiss_orb_of_ascension');

-- Instructor Devoran
SET @ENTRY := 39406;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,25294,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove Dog");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '616' AND `SourceEntry` = '19' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '25372';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 616, 19, 0, 0, 8, 0, 25372, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '616' AND `entry` = '19' AND `phasemask` = '128';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `phaseId`, `terrainswapmap`, `flags`, `comment`) VALUES
(616, 19, 128, 0, 0, 4, 'Mount Hyjal: Negate Phase after Aessinas Miracle');

DELETE FROM `spell_area` WHERE `spell` = '60922' AND `quest_start` = '25597';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`) VALUES
(60922, 616, 25597, 25315, 1);

UPDATE `gameobject` SET `phaseMask`=512 WHERE `guid`=700744;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (74934, 74935, 74937);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74934, 'spell_podium_inspire'),
(74935, 'spell_podium_incite'),
(74937, 'spell_podium_pander');

UPDATE `creature` SET `position_z`=976.218 WHERE `guid`=731304;
UPDATE `creature` SET `position_z`=975.893 WHERE `guid`=731295;

DELETE FROM `creature_text` WHERE `entry`=40185;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40185,0,0,'%s attempts to run away in fear!',16,0,100,0,0,0,'combat Flee'),
(40185,1,0,'Meh.',12,0,100,0,0,0,'Comment'),
(40185,1,1,'Yea... I don\'t know about this.',12,0,100,0,0,0,'Comment'),
(40185,1,2,'I\'m not quite convinced',12,0,100,0,0,0,'Comment'),
(40185,1,3,'*yawn*',12,0,100,0,0,0,'Comment'),
(40185,2,0,'Raaahhh!!!!',12,0,100,0,0,0,'Comment'),
(40185,2,1,'Blood!',12,0,100,0,0,0,'Comment'),
(40185,2,2,'Kill!!',12,0,100,0,0,0,'Comment'),
(40185,2,3,'Kill them all!',12,0,100,0,0,0,'Comment'),
(40185,2,4,'Crush!',12,0,100,0,0,0,'Comment'),
(40185,2,5,'Death!',12,0,100,0,0,0,'Comment'),
(40185,3,0,'It\'s like... it\'s like the void just touched my mind. ',12,0,100,0,0,0,'Comment'),
(40185,3,1,'The end is nigh! The end is a new beginning! ',12,0,100,0,0,0,'Comment'),
(40185,3,2,'Immalanath, yasoth nalarub!!! ',12,0,100,0,0,0,'Comment'),
(40185,3,3,'I hear the voices!',12,0,100,0,0,0,'Comment'),
(40185,4,0,'It\'s like I\'m hearing the Old Gods themselves! ',12,0,100,0,0,13904,'Comment'),
(40185,4,1,'That\'s how it\'s done! Yeah!',12,0,100,0,0,13904,'Comment'),
(40185,4,2,'History in the making!',12,0,100,0,0,13904,'Comment'),
(40185,4,3,'Truer words were never spoken!',12,0,100,0,0,13904,'Comment'),
(40185,5,0,'Huh?',12,0,100,0,0,19772,'Comment'),
(40185,5,1,'You lie!',12,0,100,0,0,19772,'Comment'),
(40185,5,2,'Sit down!',12,0,100,0,0,19771,'Comment'),
(40185,5,3,'What are you talking about?',12,0,100,0,0,19771,'Comment');

UPDATE `creature_template_addon` SET `bytes1`=1 WHERE `entry`=40185;

DELETE FROM `spell_script_names` WHERE `spell_id` = '76421';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(76421, 'spell_horn_of_cenarius');

DELETE FROM `creature` WHERE `id`='40956';

DELETE FROM `creature_text` WHERE `entry`=40814;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40814,0,0,'Feel the fury of Ragnaros!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=40955;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40955,0,0,'You know nothing of fury, worm!',14,0,100,0,0,19638,'Comment'),
(40955,1,0,'Let this be a lesson to those who would defile Hyjal.',12,0,100,0,0,19639,'Comment');

-- Azralon the Gatekeeper
SET @ENTRY := 40814;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4800,7900,12300,14900,11,80606,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Evil Cleave"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,50,0,0,12,40955,4,120000,0,0,0,8,0,0,0,4259.22,-3327.75,1019.49,4.85,"On Health 50% - Summon Goldrinn"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Creatures");

UPDATE `creature_template` SET `unit_flags`=559104, `minlevel`=81, `maxlevel`=81, `mindmg`=927, `maxdmg`=1240, `attackpower`=21, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=40955;

-- Goldrinn
SET @ENTRY := 40955;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,49,0,0,0,0,0,0,10,712391,40814,0,0.0,0.0,0.0,0.0,"AI Init - Attack Azralon"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,1,1000,1000,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,40955,0,0,69,0,0,0,0,0,0,8,0,0,0,4271.43,-3329.0,1019.51,1.32,"After Talk 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,1,40955,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Run"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,40955,0,0,41,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Force Despawn");

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=40974;

DELETE FROM `creature_text` WHERE `entry`=40816;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40816,0,0,'Show yourself, beast! We will destroy you and your corrupt spawn no matter where you hide!',14,0,100,0,0,20947,'Comment'),
(40816,1,0,'Slay her now, before Aviana\'s magic wears off!',14,0,100,0,0,20948,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_aronus_desperiona_event' WHERE `entry`=40816;
UPDATE `creature_template` SET `ScriptName`='npc_desperiona_event', `speed_run`=2.14143 WHERE `entry`=40974;

DELETE FROM `spell_script_names` WHERE `spell_id` = '76559';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(76559, 'spell_place_drake_skull');

DELETE FROM `creature_text` WHERE `entry`=40974;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40974,0,0,'What coward dares attack my young while I\'m away? I will feed your entrails to my brood!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template_addon` SET `auras`='76743' WHERE `entry`=40982;

DELETE FROM `creature_text` WHERE `entry`=40982;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40982,0,0,'You will not defile the winds of Hyjal for much longer, monster!',14,0,100,0,0,20740,'Comment'),
(40982,1,0,'Hurry, she is breaking free!',14,0,100,0,0,20741,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_aviana_event' WHERE `entry`=40982;

DELETE FROM `spell_script_names` WHERE `spell_id` = '76607';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(76607, 'spell_drums_of_the_turtle_god');

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=40999;

-- Tortolla
SET @ENTRY := 40999;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,5000,5000,11,80604,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Crushing Bite"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,12000,12000,12000,12000,11,80605,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Headbutt"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,10,712444,40998,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack King Moltron");

DELETE FROM `creature_addon` WHERE `guid`=731432;
DELETE FROM `creature` WHERE `guid`=731432;

DELETE FROM `spell_script_names` WHERE `spell_id` = '74475';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74475, 'spell_summon_spirit_of_logosh');

-- Spirit of Goldrinn
SET @ENTRY := 39627;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,66,3,0,0,0,0,0,8,0,0,0,5143.51,-2300.51,1278.61,0.48,"On Just Summoned - Set Orientation"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,25272,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Ride Invoker (DISABLED TEMP)"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,53,1,39622,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Remove NPC Flags"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,5,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Remove Passengers"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,20,0,100,0,25272,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Force Despawn"),
(@ENTRY,@SOURCETYPE,7,0,20,0,100,0,25273,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Force Despawn");

UPDATE `creature_template` SET `speed_walk`=3.0, `speed_run`=3.0 WHERE `entry`=41243;
UPDATE `creature_template` SET `npcflag`=16777216 WHERE  `entry`=40340;

DELETE FROM `creature` WHERE `guid` = '785906';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(785906, 39627, 1, 1, 64, 0, 0, 5367.27, -2188.15, 1291.63, 2.99384, 0, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '785906';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(785906, '49414');

DELETE FROM `creature_addon` WHERE `guid` = '785924';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(785924, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '25272';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 4979, 25272, 1, 66, 0);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '25273';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 4979, 25273, 1, 66, 0);