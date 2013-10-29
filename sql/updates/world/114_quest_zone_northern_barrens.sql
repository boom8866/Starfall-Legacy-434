DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (1582, 344, 349);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(1582, 2, 0, 'Trick or Treat!', 1, 1, 0, 0, 0, 0, NULL),
(1582, 3, 1, 'I want to browse your goods.', 3, 128, 0, 0, 0, 0, NULL),
(1582, 1, 5, 'Make this inn your home.', 8, 65536, 0, 0, 0, 0, NULL),
(344, 2, 0, 'Trick or Treat!', 1, 1, 0, 0, 0, 0, NULL),
(344, 1, 5, 'Make this inn your home.', 8, 65536, 0, 0, 0, 0, NULL),
(344, 3, 1, 'Let me browse your goods.', 3, 128, 0, 0, 0, 0, NULL),
(349, 1, 5, 'Make this inn your home.', 8, 65536, 0, 0, 0, 0, NULL),
(349, 3, 1, 'I want to browse your goods.', 3, 128, 0, 0, 0, 0, NULL),
(349, 2, 0, 'Trick or Treat!', 1, 1, 0, 0, 0, 0, NULL);

UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=34285;

-- Barrens Burning Barn Fire Bunny
SET @ENTRY := 34280;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,10000,10000,75,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Add Aura Fire");

-- Trapped Wolf
SET @ENTRY := 34285;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,11,0,100,0,0,0,0,0,11,88964,2,0,0,0,0,19,34287,0,0,0.0,0.0,0.0,0.0,"Respawn - Cast Chains"),
(@ENTRY,@SOURCETYPE,1,2,38,0,100,1,0,1,0,0,11,65086,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Get Data 1 - Break the Chains"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,45,0,1,0,0,0,0,19,34287,0,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Creature Chain"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,1,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,1,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,3.12,-3619.21,27.24,0.89,"Link - Move Out of Stable"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,1,0,1,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Get Data 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,1,0,0,0,0,33,34285,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

-- Chain Origin
SET @ENTRY := 34287;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,28,88964,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Chains effect");

-- Wolf Chains
SET @ENTRY := 195004;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34285,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Wolfs");

-- Wolf Chains
SET @ENTRY := 195003;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34285,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Wolfs");

-- Wolf Chains
SET @ENTRY := 195001;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,34285,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Wolfs");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE  `menu_id`=10514 AND `id`=0;
DELETE FROM `conditions` WHERE `SourceGroup` = '10514';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10514, 0, 0, 0, 9, 0, 13949, 0, 0, 0, 0, 0, '', 'Halga Bloodeye - Show gossip only if quest 13949 is active');

DELETE FROM `spell_script_names` WHERE `spell_id` = '101668';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(101668, 'spell_calling_the_caravan');

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '34430';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(34430, 34431, 0, 1, 'Balgor Whipshank on Caravan', 6, 30000),
(34430, 34438, 1, 1, 'Caravan Shotgun Seat', 6, 30000);

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=34430;
UPDATE `creature_template` SET `spell1`=65479 WHERE `entry`=34438;
UPDATE `creature_template` SET `speed_run`=0.992063 WHERE `entry`=34432;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (34430, 34438);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(34438, 65466, 1),
(34430, 46598, 1);

DELETE FROM `waypoints` WHERE `entry` = '34430';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(34430, 1, 321.12, -3597.05, 27.10, 'Caravan 1 WP'),
(34430, 2, 292.13, -3568.22, 27.00, 'Caravan 1 WP'),
(34430, 3, 285.00, -3533.57, 25.49, 'Caravan 1 WP'),
(34430, 4, 259.87, -3498.95, 27.16, 'Caravan 1 WP'),
(34430, 5, 251.66, -3464.32, 27.60, 'Caravan 1 WP'),
(34430, 6, 186.38, -3399.42, 34.06, 'Caravan 1 WP'),
(34430, 7, 177.17, -3288.96, 60.24, 'Caravan 1 WP'),
(34430, 8, 153.56, -3260.74, 67.07, 'Caravan 1 WP'),
(34430, 9, 145.80, -3197.16, 81.79, 'Caravan 1 WP'),
(34430, 10, 124.91, -3156.07, 90.90, 'Caravan 1 WP'),
(34430, 11, 198.37, -3071.69, 91.66, 'Caravan 1 WP'),
(34430, 12, 180.84, -3042.58, 91.84, 'Caravan 1 WP');

DELETE FROM `creature_text` WHERE `entry` IN (34258, 34438, 34431);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34258,0,0,'Mount up, $n! Do not fail me.',12,0,100,0,0,0,'Comment'),
(34438,0,0,'Defend the Caravan Kodo!',41,0,100,0,0,0,'Comment'),
(34431,0,0,'Excellent work! I\'ll unload the goods. You should check in with Kranal Fiss',12,0,100,0,0,0,'Comment');

-- Lead Caravan Kodo
SET @ENTRY := 34430;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,18,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,4,38,0,100,0,0,2,0,0,53,1,34430,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,45,0,3,0,0,0,0,11,34432,30,0,0.0,0.0,0.0,0.0,"Link - Set Data 3 to Second Caravan"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,3,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,3,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,7,0,40,0,100,0,4,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,8,0,40,0,100,0,4,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,5,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,10,0,40,0,100,0,5,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,11,0,40,0,100,0,8,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,12,0,40,0,100,0,8,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,13,0,40,0,100,0,9,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,9,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,15,0,40,0,100,0,10,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 10 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,16,0,40,0,100,0,10,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 10 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,17,0,40,0,100,0,11,0,0,0,33,53613,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Quest Complete"),
(@ENTRY,@SOURCETYPE,18,0,40,0,100,0,12,0,0,0,45,0,5,0,0,0,0,11,34438,15,0,0.0,0.0,0.0,0.0,"On WP Reached 12 - Set Data 5 to Shotgun"),
(@ENTRY,@SOURCETYPE,19,20,40,0,100,0,12,0,0,0,28,46598,0,0,0,0,0,11,34431,15,0,0.0,0.0,0.0,0.0,"On WP Reached 12 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,20,21,61,0,100,0,0,0,0,0,45,0,6,0,0,0,0,11,34431,20,0,0.0,0.0,0.0,0.0,"Link - Set Data 6 to Balgor"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (5000)");

-- Balgor Whipshank
SET @ENTRY := 34431;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,38,0,100,0,0,6,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,34431,0,0,69,0,0,0,0,0,0,11,34432,30,0,0.0,0.0,0.0,0.0,"After Talk 0 - Move To Caravan"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,60000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (1 min)");

-- Far Watch Caravan Kodo
SET @ENTRY := 34432;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,3,54,0,100,0,0,0,0,0,46,18,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,1,1,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,2,5,38,0,100,0,0,3,0,0,29,15,0,0,0,0,0,11,34430,20,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Move Follow"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,12,34431,8,300000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Balgor Whipshank"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,41,160000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Riding Shotgun
SET @ENTRY := 34438;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,5000,5000,5000,5000,86,65466,0,21,10,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - 5 secs Cast on Closest Player"),
(@ENTRY,@SOURCETYPE,2,3,27,0,100,1,0,0,0,0,45,0,2,0,0,0,0,11,34430,10,0,0.0,0.0,0.0,0.0,"Passenger Boarded - Set Data 2 to Caravan"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,4,5,38,0,100,0,0,5,0,0,28,65466,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,3,27,0,100,1,0,0,0,0,45,0,2,0,0,0,0,11,34577,10,0,0.0,0.0,0.0,0.0,"Passenger Boarded - Set Data 2 to Caravan");

-- Razormane Raider
SET @ENTRY := 34487;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,60,0,100,1,1500,1500,2000,2000,29,1,0,0,0,0,0,11,34432,50,0,0.0,0.0,0.0,0.0,"Update (1.5 secs) Follow Caravan"),
(@ENTRY,@SOURCETYPE,1,0,61,0,50,1,0,0,0,0,11,46598,2,0,0,0,0,11,34432,50,0,0.0,0.0,0.0,0.0,"Link - (75% chance)"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,4,60,0,100,1,1500,1500,2000,2000,29,1,0,0,0,0,0,11,52212,50,0,0.0,0.0,0.0,0.0,"Update (1.5 secs) Follow Caravan"),
(@ENTRY,@SOURCETYPE,4,0,61,0,50,1,0,0,0,0,11,46598,2,0,0,0,0,11,52212,50,0,0.0,0.0,0.0,0.0,"Link - (75% chance)");

-- Halga Bloodeye
SET @ENTRY := 34258;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10514,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,86,101668,0,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cross Cast Invoker"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0");

UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=13961;
UPDATE `creature_template` SET `ScriptName`='npc_togrik' WHERE `entry`=34513;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (65580, 65609);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(65580, 'spell_snared_in_net'),
(65609, 'spell_snared_secondary_effect');

DELETE FROM `creature_text` WHERE `entry`=34503;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34503,0,0,'%s attempts to run away in fear!',16,0,100,0,0,0,'combat Flee'),
(34503,1,0,'Razormane Pillager is ensnared!',16,0,100,0,0,0,'Comment');

-- Razormane Pillager
SET @ENTRY := 34503;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,2,4,8,0,100,0,65581,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Spellhit - Set Phase 1"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,2000,2000,2000,2000,11,65608,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - 2 secs (Cast spell dragging)"),
(@ENTRY,@SOURCETYPE,4,7,61,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,18,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Not attackable"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,0,2000,2000,2000,2000,11,65609,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cleanup self");

UPDATE `creature_template` SET `dynamicflags`=0 WHERE `entry`=34594;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10521;
DELETE FROM `conditions` WHERE `SourceGroup` = '10521';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10521, 0, 0, 0, 9, 0, 13963, 0, 0, 0, 0, 0, '', 'Captured Razormane - Show gossip only if quest 13963 is active');

-- Captured Razormane
SET @ENTRY := 34523;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,10000,10000,10000,10000,11,88964,0,0,0,0,0,10,147831,34527,0,0.0,0.0,0.0,0.0,"Update - Cast Chains"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,10521,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,10521,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,10521,2,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,10521,3,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,10521,4,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,6,7,62,0,100,0,10521,3,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select 3 - Talk 1"),
(@ENTRY,@SOURCETYPE,7,10,61,0,100,0,0,0,0,0,33,34529,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,0,10521,0,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select 0 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,62,0,100,0,10521,2,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select 2 - Talk 4"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 3"),
(@ENTRY,@SOURCETYPE,11,0,62,0,100,0,10521,1,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select 1 - Talk 4"),
(@ENTRY,@SOURCETYPE,12,7,62,0,20,0,10521,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,13,14,62,0,20,0,10521,4,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select 4 - Talk 2"),
(@ENTRY,@SOURCETYPE,14,0,61,0,25,0,0,0,0,0,11,65629,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Nasty to Invoker");

UPDATE `quest_template` SET `RequiredNpcOrGo1`=53573, `RequiredNpcOrGoCount1`=1 WHERE `Id`=13975;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE  `menu_id`=10528 AND `id`=0;
DELETE FROM `conditions` WHERE `SourceGroup` = '10528';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10528, 0, 0, 0, 9, 0, 13975, 0, 0, 0, 0, 0, '', 'Rocco Whipshank - Show gossip only if quest 13975 is active');

UPDATE `creature_template` SET `dynamicflags`=0, `unit_flags2`=2048 WHERE `entry`=34576;
UPDATE `creature_template` SET `VehicleId`=415 WHERE `entry` IN (34576, 34577);
DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (34577, 34593);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(34577, 34431, 0, 1, 'Balgor Whipshank on Caravan Crossroads', 6, 30000),
(34577, 34438, 1, 1, 'Caravan Shotgun Seat', 6, 30000);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (34577, 34576);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(34577, 65466, 1),
(34576, 46598, 1),
(34593, 46598, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=34593;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=34593;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=34594;

DELETE FROM `waypoints` WHERE `entry` = '34577';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(34577, 1, 122.53, -2709.44, 91.67, 'Caravan 2 WP'),
(34577, 2, 52.74, -2713.52, 91.66, 'Caravan 2 WP'),
(34577, 3, -30.03, -2714.87, 93.47, 'Caravan 2 WP'),
(34577, 4, -65.04, -2688.19, 95.83, 'Caravan 2 WP'),
(34577, 5, -428.27, -2675.12, 95.70, 'Caravan 2 WP');

DELETE FROM `creature_text` WHERE `entry`=34578;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34578,0,0,'There she is. Mount up!',12,0,100,0,0,0,'Comment'),
(34578,1,0,'Ride hard and show no mercy!',12,0,100,0,0,0,'Comment');

-- Rocco Whipshank
SET @ENTRY := 34578;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10528,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,11,101668,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Call the Caravan"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,34578,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Text 0 - Text 1");

-- Burning Blade Mount
SET @ENTRY := 34593;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,63,0,100,0,0,0,0,0,12,34594,5,25000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Created - Summon Rider"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,3000,3000,3000,3000,86,46598,0,11,34594,1,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cross Cast - Mount Rider"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,2000,2000,2000,2000,49,0,0,0,0,0,0,11,34576,20,0,0.0,0.0,0.0,0.0,"Every 2 seconds check and attack Caravan");

-- Head Caravan Kodo
SET @ENTRY := 34577;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,209.42,-2936.0,92.28,2.1,"On Just Summoned - Move to Pos"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,4,38,0,100,0,0,2,0,0,53,1,34577,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,45,0,3,0,0,0,0,11,34576,30,0,0.0,0.0,0.0,0.0,"Link - Set Data 3 to Second Caravan"),
(@ENTRY,@SOURCETYPE,18,0,40,0,100,0,5,0,0,0,45,0,5,0,0,0,0,11,34438,15,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Set Data 5 to Shotgun"),
(@ENTRY,@SOURCETYPE,19,20,40,0,100,0,5,0,0,0,28,46598,0,0,0,0,0,11,34431,15,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,20,21,61,0,100,0,0,0,0,0,45,0,6,0,0,0,0,11,34431,20,0,0.0,0.0,0.0,0.0,"Link - Set Data 6 to Balgor"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (5000)");

-- Crossroads Caravan Kodo
SET @ENTRY := 34576;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,3,54,0,100,0,0,0,0,0,29,15,0,0,0,0,0,11,34577,60,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Follow Head Caravan"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (2 mins)"),
(@ENTRY,@SOURCETYPE,3,2,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Passive");

DELETE FROM `creature_loot_template` WHERE `item` = '5096';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3415, 5096, -64.619, 1, 0, 1, 1),
(3425, 5096, -64.619, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `entry` = '3254';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3254, 727, 0.18, 1, 0, -727, 1),
(3254, 818, 0.4609, 1, 0, 1, 1),
(3254, 2073, 0.42, 1, 0, -2073, 1),
(3254, 2075, 0.59, 1, 0, -2075, 1),
(3254, 2140, 0.76, 1, 0, -2140, 1),
(3254, 2406, 0.1649, 1, 0, -2406, 1),
(3254, 2409, 0.1649, 1, 0, -2409, 1),
(3254, 2632, 0.35, 1, 0, -2632, 1),
(3254, 2970, 0.18, 1, 0, -2970, 1),
(3254, 3279, 0.7, 1, 0, -3279, 1),
(3254, 3281, 0.4, 1, 0, -3281, 1),
(3254, 3283, 0.82, 1, 0, -3283, 1),
(3254, 3285, 1, 1, 0, -3285, 1),
(3254, 3304, 0.6, 1, 0, -3304, 1),
(3254, 3311, 0.028, 1, 0, 1, 1),
(3254, 3312, 0.6, 1, 0, -3312, 1),
(3254, 4663, 0.7, 1, 0, -4663, 1),
(3254, 4878, 5.4123, 1, 0, 1, 1),
(3254, 5062, -100, 1, 0, 1, 1),
(3254, 5123, 18.8808, 1, 0, 1, 1),
(3254, 5165, -80, 1, 0, 1, 1),
(3254, 5574, 0.3, 1, 0, -5574, 1),
(3254, 5635, 1.1647, 1, 0, 1, 1),
(3254, 54833, 88.512, 1, 0, 1, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` = '5316';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(5316, 'spell_placing_raptor_feather');

-- Raptor Feather
SET @ENTRY := 195317;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn (10 secs)");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (738366, 734958, 738367);

-- Verog the Dervish
SET @ENTRY := 3395;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,6268,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Rushing Charge on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,1000,1000,60000,60000,47,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Invisible in OOC"),
(@ENTRY,@SOURCETYPE,2,3,38,0,100,0,0,1,0,0,69,0,0,0,0,0,0,8,0,0,0,-1208.35,-2746.0,102.27,1.65,"On Get Data 1 - Move To Wyneth"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,47,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Visible"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run");

-- Wyneth
SET @ENTRY := 34846;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,9532,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,9532,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
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
(@ENTRY,@SOURCETYPE,14,0,0,1,100,0,5000,7000,18000,26000,11,6535,1,0,0,0,0,4,0,0,0,0.0,0.0,0.0,0.0,"Cast Lightning Cloud"),
(@ENTRY,@SOURCETYPE,15,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,738367,3395,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Verog");

UPDATE `gameobject` SET `phaseMask`=1, `position_x`=-18.59, `position_y`=-2379.44, `position_z`=91.66, `orientation`=1.35 WHERE `guid`=721842;
UPDATE `quest_template` SET `PrevQuestId`=881 WHERE `Id`=905;
UPDATE `quest_template` SET `Flags`=132, `SpecialFlags`=2 WHERE `Id`=14066;

-- Echeyakee
SET @ENTRY := 3475;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,24450,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Echeyakee On summon, cast Prowl"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,93435,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Echeyakee - Combat - Buff self with Roar of Courage (every 30 seconds)"),
(@ENTRY,@SOURCETYPE,2,0,12,0,100,0,1,20,1,20,11,83381,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Echeyakee - Combat - If player hp less than 20%, cast Kill Command"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1500,1500,5000,5000,11,2649,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Echeyakee - Combat - every 5 seconds, cast Growl"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1200,1200,5000,5000,11,16827,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Echeyakee - Combat - every 5 seconds, cast Claw"),
(@ENTRY,@SOURCETYPE,5,0,9,0,100,0,10,40,10,40,11,66060,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Echeyakee - On player out past 10 meters, cast sprint on self (For player chase)"),
(@ENTRY,@SOURCETYPE,6,0,54,0,100,0,0,0,0,0,46,8,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward");

DELETE FROM `spell_script_names` WHERE `spell_id` = '12189';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(12189, 'spell_summon_echeyakee');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5482';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5482, 'at_caravan_scene');

DELETE FROM `creature_loot_template` WHERE `item` = '68820';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3282, 68820, -13.9636, 1, 0, 1, 1),
(3285, 68820, -4.5768, 1, 0, 1, 1),
(3284, 68820, -15.4439, 1, 0, 1, 1),
(52356, 68820, -32.9848, 1, 0, 1, 1),
(52357, 68820, -36.2343, 1, 0, 1, 1);

UPDATE `quest_template` SET `Flags`=132, `SpecialFlags`=2 WHERE `Id`=869;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=734970;

-- Sunscale Ravager
SET @ENTRY := 44164;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,7000,18000,24000,11,82608,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Howling Screech"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,3000,3000,3000,3000,15,869,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Update - Quest Complete to Players in Range"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,66284,1,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Spellhit - Force Despawn");

-- Waptor Twap
SET @ENTRY := 34831;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,2000,2000,8000,8000,11,66282,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Scweech"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,3000,3000,3000,3000,11,66284,2,0,0,0,0,11,3256,5,0,0.0,0.0,0.0,0.0,"Update - 3 seconds (Cast Shrink on Raptors)"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,3000,3000,3000,3000,11,66284,2,0,0,0,0,11,44164,5,0,0.0,0.0,0.0,0.0,"Update - 3 seconds (Cast Shrink on Raptors)");

DELETE FROM `spell_script_names` WHERE `spell_id` IN (66282, 66284);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(66282, 'spell_waptor_twap_scweech'),
(66284, 'spell_waptor_shrink');

-- Sunscale Scytheclaw
SET @ENTRY := 3256;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,60,0,15000,15000,20000,20000,11,3391,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Sunscale Scytheclaw - In Combat - Cast Thrash"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,66284,1,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Spellhit - Force Despawn");

DELETE FROM `gameobject_loot_template` WHERE `item` = '46851';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(27298, 46851, -100);

UPDATE `quest_template` SET `Flags`=128 WHERE `Id`=14046;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10567;
DELETE FROM `conditions` WHERE `SourceGroup` = '10567';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10567, 0, 0, 0, 9, 0, 14046, 0, 0, 0, 0, 0, '', 'Baron Longshore - Show gossip only if quest 14046 is active');

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
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,28,77531,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Chains");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738370;
UPDATE `creature_template` SET `InhabitType`=4, `HoverHeight`=4 WHERE `entry`=34615;

DELETE FROM `creature_text` WHERE `entry`=3467;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(3467,0,0,'Suit yerself, mate. Me an' the treasure can both be buried. ',12,0,100,0,0,0,'Comment'),
(3467,1,0,'Har! Pleasure doin' business with ye, $n. ',12,0,100,0,0,0,'Comment');

-- Tonga's Spirit
SET @ENTRY := 34623;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3000,3000,3000,3000,45,0,1,0,0,0,0,11,34615,50,0,0.0,0.0,0.0,0.0,"Every 3 seconds Set Data 1 to Tonga's Bird");

DELETE FROM `waypoints` WHERE `entry` = '34615';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(34615, 1, -1480.99, -3301.88, 212.76, 'Tonga WP'),
(34615, 2, -1484.16, -3294.12, 212.76, 'Tonga WP'),
(34615, 3, -1479.79, -3289.34, 212.76, 'Tonga WP'),
(34615, 4, -1475.39, -3295.40, 212.76, 'Tonga WP');

-- Tonga's Eyes
SET @ENTRY := 34615;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,54,0,100,0,0,0,0,0,11,65753,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast to Summoner Eyes"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Passive"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,3,6,38,0,100,1,0,1,0,0,53,0,34615,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Start WP"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,4,0,0,0,33,34631,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Complete Quest"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,28,65753,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Aura to Owner");

DELETE FROM `spell_script_names` WHERE `spell_id` = '66204';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(66204, 'spell_pirate_signal_horn');


-- Southsea Mutineer
SET @ENTRY := 34790;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
(@ENTRY,@SOURCETYPE,5,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model"),
(@ENTRY,@SOURCETYPE,6,7,9,1,100,0,30,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,0,0,10,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,9,10,61,1,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,0,11,25,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 25 Yards"),
(@ENTRY,@SOURCETYPE,12,13,61,1,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack at 25 Yards"),
(@ENTRY,@SOURCETYPE,13,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model at 25 Yards"),
(@ENTRY,@SOURCETYPE,14,15,7,1,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,15,0,61,1,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,16,0,2,1,100,1,0,15,0,0,22,2,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"At 15% HP - Set Phase 2"),
(@ENTRY,@SOURCETYPE,17,0,2,2,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,18,19,7,2,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,19,0,61,2,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,20,0,2,2,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,21,0,0,1,100,0,8000,9000,120000,120000,11,32064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,22,23,54,0,100,0,0,0,0,0,29,3,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Invoker"),
(@ENTRY,@SOURCETYPE,23,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run");

-- Tony Two-Tusk
SET @ENTRY := 34749;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
(@ENTRY,@SOURCETYPE,5,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model"),
(@ENTRY,@SOURCETYPE,6,7,9,1,100,0,30,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,0,0,10,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,9,10,61,1,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,0,11,25,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 25 Yards"),
(@ENTRY,@SOURCETYPE,12,13,61,1,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack at 25 Yards"),
(@ENTRY,@SOURCETYPE,13,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model at 25 Yards"),
(@ENTRY,@SOURCETYPE,14,15,7,1,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,15,0,61,1,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,16,0,2,1,100,1,0,15,0,0,22,2,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"At 15% HP - Set Phase 2"),
(@ENTRY,@SOURCETYPE,17,0,2,2,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,18,19,7,2,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,19,0,61,2,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,20,0,2,2,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,21,0,0,1,100,0,8000,9000,120000,120000,11,32064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,22,23,54,0,100,0,0,0,0,0,29,3,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Invoker"),
(@ENTRY,@SOURCETYPE,23,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run");

UPDATE `creature_template` SET `faction_A`=230, `faction_H`=230 WHERE `entry`=34782;
UPDATE `creature` SET `phaseMask`=1 WHERE `id`=34782;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=34749;

DELETE FROM `creature_text` WHERE `entry`=34782;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34782,0,0,'Do not trifle with me, $n.',12,0,100,0,0,0,'on Aggro Text');

-- Remove some Gameobjects that shouldn't be anymore spawned due to cataclysm map change (No addons)
DELETE FROM `gameobject` WHERE `guid` IN (69694, 69695, 69696, 69697, 69698, 69699, 69700, 69701, 69702);

-- Remove duplicate spawns (No addons)
DELETE FROM `creature` WHERE `guid` IN (149394, 149395);

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=727854;
DELETE FROM `gameobject_loot_template` WHERE `item` = '46833';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(27289, 46833, -100);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10556 AND `id`=0;
DELETE FROM `conditions` WHERE `SourceGroup` = '10556';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10556, 0, 0, 0, 9, 0, 14034, 0, 0, 0, 0, 0, '', 'Show gossip only if quest 14034 is active');

DELETE FROM `creature_text` WHERE `entry`=34651;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34651,0,0,'Hahaha, very nice!',12,0,100,0,0,0,'Comment');

-- Chief Engineer Foote
SET @ENTRY := 34754;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10556,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,149388,34651,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Sashya");

-- Sashya
SET @ENTRY := 34651;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,34707,50,0,0.0,0.0,0.0,0.0,"Link - Set Data 2 to Creatures"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,56,46827,1,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete to Player");

-- Theramore Deck Hand
SET @ENTRY := 34707;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,66076,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,4500,12000,16000,11,75361,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Swashbuckling Slice"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Defensive"),
(@ENTRY,@SOURCETYPE,3,4,38,0,100,0,0,2,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Aggressive"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Attack start on Player");

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '52203';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(52203, 96526, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738360;
UPDATE `quest_template` SET `RewardSpellCast`=96823 WHERE `Id`=14006;

DELETE FROM `spell_area` WHERE `quest_end` = '14006';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(96823, 5117, 14006, 14006, 0, 0, 2, 1, 64, 64);

UPDATE `creature_template` SET `VehicleId`=1577, `InhabitType`=7, `speed_run`=3.2 WHERE `entry`=52201;

DELETE FROM `waypoints` WHERE `entry` = '52201';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(52201, 1, 1136.37, -3356.15, 95.23, 'Silver Bullet WP'),
(52201, 2, 1133.08, -3348.96, 102.87, 'Silver Bullet WP'),
(52201, 3, 1122.49, -3320.30, 114.72, 'Silver Bullet WP'),
(52201, 4, 1050.49, -3300.30, 114.72, 'Silver Bullet WP'),
(52201, 5, 950.49, -3300.30, 114.72, 'Silver Bullet WP'),
(52201, 6, 900.49, -3280.30, 114.72, 'Silver Bullet WP'),
(52201, 7, 850.49, -3260.30, 114.72, 'Silver Bullet WP'),
(52201, 8, 800.49, -3240.30, 114.72, 'Silver Bullet WP'),
(52201, 9, 565.80, -2459.42, 164.24, 'Silver Bullet WP'),
(52201, 10, 195.61, -2577.74, 127.50, 'Silver Bullet WP'),
(52201, 11, 72.39, -2517.49, 120.02, 'Silver Bullet WP'),
(52201, 12, -136.10, -2078.13, 116.85, 'Silver Bullet WP'),
(52201, 13, -80.98, -1994.13, 114.93, 'Silver Bullet WP'),
(52201, 14, 70.71, -1911.44, 108.39, 'Silver Bullet WP'),
(52201, 15, 223.25, -1715.18, 115.16, 'Silver Bullet WP'),
(52201, 16, 145.97, -1602.70, 110.22, 'Silver Bullet WP'),
(52201, 17, 62.338, -1571.85, 94.39, 'Silver Bullet WP');

-- Silver Bullet X-831
SET @ENTRY := 52201;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,54,0,100,0,0,0,0,0,53,1,52201,0,29094,500000,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,11,97203,4,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Spell"),
(@ENTRY,@SOURCETYPE,2,4,40,0,100,0,12,0,0,0,11,95500,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Explode"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,12,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Despawn"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,0,0,0,0,33,52360,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

UPDATE `creature_template` SET `npcflag`=16777216 WHERE `entry`=44057;
UPDATE `creature_template` SET `InhabitType`=7, `VehicleId`=1021, `unit_flags`=768, `HoverHeight`=4, `speed_walk`=2.14286, `speed_run`=2.14286 WHERE `entry`=44055;

DELETE FROM `waypoints` WHERE `entry` = '44055';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(44055, 1, -645.07, -3965.66, 17.80, 'Riverboat WP'),
(44055, 2, -608.84, -3963.70, 17.80, 'Riverboat WP'),
(44055, 3, -585.30, -3954.13, 17.80, 'Riverboat WP'),
(44055, 4, -560.79, -3939.24, 17.80, 'Riverboat WP'),
(44055, 5, -501.78, -3925.88, 17.80, 'Riverboat WP'),
(44055, 6, -373.44, -3897.70, 17.80, 'Riverboat WP'),
(44055, 7, -141.09, -3790.42, 17.80, 'Riverboat WP'),
(44055, 8, 287.70, -3760.04, 17.80, 'Riverboat WP'),
(44055, 9, 410.37, -3777.89, 17.80, 'Riverboat WP'),
(44055, 10, 805.24, -3777.60, 17.80, 'Riverboat WP'),
(44055, 11, 1002.13, -3813.37, 17.80, 'Riverboat WP');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '44057';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(44057, 82457, 1);

UPDATE `quest_template` SET `Flags`=8 WHERE `Id`=875;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738361;
UPDATE `creature_template` SET `npcflag`=0, `VehicleId`=1021 WHERE `entry`=52212;
UPDATE `creature_template` SET `VehicleId`=1048 WHERE `entry`=52316;

DELETE FROM `spell_area` WHERE `quest_end` = '29095';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(96718, 380, 29095, 29095, 0, 0, 2, 1, 64, 64);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12744';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12744, 'I\'m ready to escort the caravan, Rocco.', 1, 1);

UPDATE `creature_template` SET `VehicleId`=1021 WHERE `entry` IN (52212, 52316);
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '52316';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(52316, 46598, 1, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '52316';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(52316, 144951, 5, 1, 'Caravan Kodo (Mor\'shan)', 6, 30000),
(52316, 144951, 4, 1, 'Caravan Kodo (Mor\'shan)', 6, 30000),
(52316, 144951, 0, 1, 'Caravan Kodo (Mor\'shan)', 6, 30000),
(52316, 52212, 1, 1, 'Caravan Kodo (Mor\'shan)', 6, 30000);

UPDATE `creature_template_addon` SET `auras`='80852' WHERE `entry` IN (52316, 52212);
DELETE FROM creature WHERE guid = '738844';
DELETE FROM creature_addon WHERE guid = '738844';

DELETE FROM `creature_text` WHERE `entry`=52220;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(52220,0,0,'Very well $n, mount up now!',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '52212';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(52212, 1, -76.24, -2685.24, 95.83, 'Mor\'shan WP'),
(52212, 2, -16.80, -2718.16, 92.20, 'Mor\'shan WP'),
(52212, 3, 270.02, -2685.54, 91.66, 'Mor\'shan WP'),
(52212, 4, 335.27, -2645.74, 91.81, 'Mor\'shan WP'),
(52212, 5, 290.12, -2547.62, 91.74, 'Mor\'shan WP');

-- Rocco Whipshank
SET @ENTRY := 52220;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,12744,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,11,101668,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Call the Caravan"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,33,52445,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Killed Monster"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0");

-- Mor'shan Caravan Cart
SET @ENTRY := 52316;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1500,1500,1500,1500,29,4,0,0,0,0,0,19,52212,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Follow Kodo"),
(@ENTRY,@SOURCETYPE,2,3,27,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,52212,10,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Data 1 to Kodo"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,4,5,38,0,100,0,0,2,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Vehicle");

-- Mor'shan Caravan Kodo
SET @ENTRY := 52212;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,53,1,52212,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Start WP"),
(@ENTRY,@SOURCETYPE,1,2,40,0,100,0,5,0,0,0,33,52303,0,0,0,0,0,18,25,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Quest Complete"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,52316,25,0,0.0,0.0,0.0,0.0,"Link - Set Data 2 to Cart"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,5,38,0,100,0,0,4,0,0,29,15,0,0,0,0,0,11,52314,60,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Follow Master Caravan"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,10,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Force Despawn");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (738362, 738363, 738364);
DELETE FROM `spell_area` WHERE `quest_end` = '29110';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(96737, 384, 29110, 29110, 0, 0, 2, 1, 74, 74);

UPDATE `quest_template` SET `PrevQuestId`=14006 WHERE `Id`=28877;
UPDATE `quest_template` SET `PrevQuestId`=28877 WHERE `Id`=29094;
UPDATE `quest_template` SET `PrevQuestId`=29094 WHERE `Id`=867;
UPDATE `quest_template` SET `PrevQuestId`=867 WHERE `Id`=875;
UPDATE `quest_template` SET `PrevQuestId`=875 WHERE `Id`=876;
UPDATE `quest_template` SET `PrevQuestId`=876 WHERE `Id`=29095;
UPDATE `quest_template` SET `PrevQuestId`=29095 WHERE `Id`=29109;
UPDATE `quest_template` SET `PrevQuestId`=29109 WHERE `Id`=29110;
UPDATE `quest_template` SET `PrevQuestId`=29110 WHERE `Id`=29112;
UPDATE `quest_template` SET `PrevQuestId`=29112 WHERE `Id`=29111;
UPDATE `gameobject_template` SET `faction`=35 WHERE `entry`=3524;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12754';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(12754, 0, 0, 'I\'m ready to protect again your shipment!', 1, 1, 0, 0, 0, 0, NULL);

DELETE FROM `creature_text` WHERE `entry`=52207;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(52207,0,0,'Alright $n, mount up and good luck!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `VehicleId`=415 WHERE `entry`=52314;
UPDATE `creature_template` SET `VehicleId`=419 WHERE `entry`=52212;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=734271;

DELETE FROM `spell_area` WHERE `quest_end` = '29111';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65053, 1703, 29111, 29111, 0, 0, 2, 1, 74, 74);

DELETE FROM `conditions` WHERE `SourceGroup` = '12754';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12754, 0, 0, 0, 9, 0, 29111, 0, 0, 0, 0, 0, '', 'Nagala Whipshank - Show gossip only if quest 29111 is active');

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '52314';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(52314, 34431, 0, 1, 'Balgor Whipshank on Caravan', 6, 30000),
(52314, 34438, 1, 1, 'Caravan Shotgun Seat', 6, 30000);

DELETE FROM `waypoints` WHERE `entry` = '52314';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(52314, 1, 251.50, -2559.08, 91.66, 'Mor\'shan WP'),
(52314, 2, 283.45, -2678.88, 91.66, 'Mor\'shan WP'),
(52314, 3, 453.49, -2622.98, 91.66, 'Mor\'shan WP'),
(52314, 4, 535.47, -2581.27, 95.52, 'Mor\'shan WP'),
(52314, 5, 573.17, -2568.22, 95.78, 'Mor\'shan WP'),
(52314, 6, 723.80, -2302.04, 91.66, 'Mor\'shan WP'),
(52314, 7, 766.81, -2280.84, 91.66, 'Mor\'shan WP'),
(52314, 8, 1116.22, -2317.90, 91.67, 'Mor\'shan WP'),
(52314, 9, 1116.22, -2317.90, 91.67, 'Mor\'shan WP'),
(52314, 10, 1200.93, -2308.98, 91.70, 'Mor\'shan WP'),
(52314, 11, 1226.94, -2243.13, 91.81, 'Mor\'shan WP');

-- Master Caravan Kodo
SET @ENTRY := 52314;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,18,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,3,4,38,0,100,0,0,2,0,0,53,1,52314,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,45,0,3,0,0,0,0,11,52212,40,0,0.0,0.0,0.0,0.0,"Link - Set Data 3 to Second Caravan"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,3,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,3,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,7,0,40,0,100,0,4,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,8,0,40,0,100,0,4,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,5,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,10,0,40,0,100,0,5,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,11,0,40,0,100,0,8,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,12,0,40,0,100,0,8,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,13,0,40,0,100,0,9,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,9,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 9 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,15,0,40,0,100,0,10,0,0,0,12,34487,4,30000,0,0,0,11,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 10 - Summon Razormane"),
(@ENTRY,@SOURCETYPE,16,0,40,0,100,0,10,0,0,0,12,34487,4,30000,0,0,0,1,34432,60,0,0.0,0.0,0.0,0.0,"On WP Reached 10 - Summon Razormane 2"),
(@ENTRY,@SOURCETYPE,17,23,40,0,100,0,11,0,0,0,33,52326,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Quest Complete"),
(@ENTRY,@SOURCETYPE,18,0,40,0,100,0,11,0,0,0,45,0,5,0,0,0,0,11,34438,15,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Set Data 5 to Shotgun"),
(@ENTRY,@SOURCETYPE,19,20,40,0,100,0,11,0,0,0,28,46598,0,0,0,0,0,11,34431,15,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,20,21,61,0,100,0,0,0,0,0,45,0,6,0,0,0,0,11,34431,20,0,0.0,0.0,0.0,0.0,"Link - Set Data 6 to Balgor"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (5000)"),
(@ENTRY,@SOURCETYPE,22,0,60,0,100,1,2500,2500,2500,2500,45,0,4,0,0,0,0,11,52212,60,0,0.0,0.0,0.0,0.0,"Update - Set Data 4 to Mor'shan Caravan"),
(@ENTRY,@SOURCETYPE,23,0,61,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,52212,70,0,0.0,0.0,0.0,0.0,"Link - Set Data 10 to Mor'shan Caravan");

-- Nagala Whipshank
SET @ENTRY := 52207;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,12754,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,33,52505,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,11,101668,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Call the Caravan");

UPDATE `quest_template` SET `PrevQuestId`=29024 WHERE `Id`=14003;
UPDATE `quest_template` SET `PrevQuestId`=14003 WHERE `Id`=29026;
UPDATE `quest_template` SET `PrevQuestId`=29027 WHERE `Id`=14004;

-- Prevent some errors with SAI editor exporter!
UPDATE gameobject_template SET scriptname = 'SmartGameObjectAI' where scriptname = 'SmartObjectAI';