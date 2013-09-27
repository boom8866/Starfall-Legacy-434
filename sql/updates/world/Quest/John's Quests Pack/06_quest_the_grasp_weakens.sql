DELETE FROM `gossip_menu` WHERE  `entry`=11157 AND `text_id`=15529;
UPDATE `creature_template` SET `gossip_menu_id`=11157 WHERE  `entry`=39117;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE  `entry`=39117;
UPDATE `creature_template` SET `Health_mod`=444 WHERE  `entry`=38981;
UPDATE `creature_template` SET `maxlevel`=9 WHERE  `entry`=38981;
UPDATE `creature_template` SET `spell1`=89032 WHERE  `entry`=38981;
UPDATE `creature` SET `spawntimesecs`=60 WHERE  `guid`=205555;
UPDATE `creature_template` SET `ScriptName`='npc_shadow_of_agamand' WHERE  `entry`=38981;
UPDATE `creature_template` SET `minlevel` = 11, `maxlevel` = 11, `faction_A` = 974, `faction_H` = 974, `unit_flags` = 526848, `AIName` = '', `InhabitType` = 4 WHERE `entry` = 38981;

DELETE FROM `waypoints` WHERE `entry` = '39117';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(39117, 1, 2242.28, 230.37, 34.50, 'Shadow Priestess Malia'),
(39117, 2, 2234.06, 230.18, 38.22, 'Shadow Priestess Malia'),
(39117, 3, 2236.00, 225.79, 38.21, 'Shadow Priestess Malia'),
(39117, 4, 2244.50, 228.44, 41.81, 'Shadow Priestess Malia');

DELETE FROM `creature_text` WHERE `entry`=39117;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(39117,0,0,'Very well. Follow me.',12,0,100,1,0,0,'Shadow Priestess Malia - Start'),
(39117,1,0,'Now it is time for us to begin.',12,0,100,1,0,0,'Shadow Priestess Malia - WP End'),
(39117,2,0,'Devlin Agamand! Listen to my voice!.',14,0,100,5,0,0,'Shadow Priestess Malia - Mid Event'),
(39117,3,0,'Your mortal remains are been gathered here in this place where you spent your childhood!.',14,0,100,5,0,0,'Shadow Priestess Malia - Mid Event'),
(39117,4,0,'Resist the Lich King\'s will Devlin! Come to us!.',14,0,100,5,0,0,'Shadow Priestess Malia - Mid Event'),
(39117,5,0,'I had better return to my post. You can find me downstairs if you need something.',12,0,100,1,0,0,'Shadow Priestess Malia - End Event');

DELETE FROM `creature_text` WHERE `entry` = '38980';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(38980, 0, 0, 'What\'s going on here?.', 12, 0, 100, 0, 0, 0, 'Devlin - Talk'),
(38980, 1, 0, 'Wait, am I... home?', 12, 0, 100, 0, 0, 0, 'Devlin - Talk'),
(38980, 2, 0, 'You people... What are you doing here? Why are you in my house?', 12, 0, 100, 0, 0, 0, 'Devlin - Talk'),
(38980, 3, 0, 'Mother... father... Thurman... where are you? Come help me!', 12, 0, 100, 0, 0, 0, 'Devlin - Talk'),
(38980, 4, 0, 'No... I remember. My family is dead. And so am I.', 12, 0, 100, 0, 0, 0, 'Devlin - Talk'),
(38980, 5, 0, 'And my soul... my soul belongs to the Scourge!', 12, 0, 100, 0, 0, 0, 'Devlin - Talk (Green Aura)'),
(38980, 6, 0, 'DIE...YOU WRETCHES!', 14, 0, 100, 0, 0, 0, 'Devlin - Yell Final (Spawn Spirit Attack)');

-- Shadow Priestess Malia
SET @ENTRY := 39117;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11157,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11157,0,0,0,1,0,3000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,39117,0,0,53,0,39117,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Start WP"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,4,0,0,0,1,1,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"WP End"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,39117,0,0,1,2,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Mid Event"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,39117,0,0,1,3,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Mid Event"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,39117,0,0,1,4,4000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Mid Event"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,39117,0,0,12,38980,3,40000,0,0,0,8,0,0,0,2246.8,228.36,42.65,1.96,"Summon Devlin"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,0,11157,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Block Gossip"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,39117,0,0,41,1000,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Despawn Finally");

-- Spirit of Devlin Agamand
SET @ENTRY := 38980;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Start event on Spawn"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,1,0,38980,0,0,1,1,5000,0,0,0,0,0,38980,0,0,0.0,0.0,0.0,0.0,"Agamand"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,1,1,38980,0,0,1,2,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Agamand"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,2,38980,0,0,1,3,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Agamand"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,1,3,38980,0,0,1,4,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Agamand"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,1,4,38980,0,0,1,5,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Agamand"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,5,38980,0,0,1,6,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Agamand"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,1,5,38980,0,0,3,0,8475,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Agamand - Morph in Spirit Form"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,1,6,38980,0,0,12,38981,5,0,0,0,0,8,0,0,0,2246.62,229.44,42.68,1.96,"Agamand - Spawn Shadow of Agamand"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,38980,0,0,11,39839,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Green Aura"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,38980,0,0,28,39839,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Remove Green Aura");