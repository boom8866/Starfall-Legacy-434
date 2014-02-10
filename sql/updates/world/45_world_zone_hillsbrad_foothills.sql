DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47204';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47204, 87978, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47204';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47204, 47203, 0, 1, 'Creeper Eggs', 6, 300000),
(47204, 47203, 1, 1, 'Creeper Eggs', 6, 300000),
(47204, 47203, 2, 1, 'Creeper Eggs', 6, 300000),
(47204, 47203, 3, 1, 'Creeper Eggs', 6, 300000),
(47204, 47203, 4, 1, 'Creeper Eggs', 6, 300000),
(47204, 47203, 5, 1, 'Creeper Eggs', 6, 300000);

DELETE FROM `creature` WHERE `id`=47203;
UPDATE `creature_template` SET `IconName`='LootAll', `faction_A`=35, `faction_H`=35, `npcflag`=1 WHERE `entry`=47203;
UPDATE `creature_template` SET `maxdmg`=24, `dmgschool`=36, `attackpower`=9 WHERE `entry`=47204;

-- Creeper Egg
SET @ENTRY := 47203;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,11,88695,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Cast to Invoker"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,47204,5,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Bear");

-- Infested Bear
SET @ENTRY := 47204;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,49,0,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Attack Nearest Player");

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=2374;
UPDATE `quest_template` SET `SourceSpellId`=88762 WHERE `Id`=28146;

-- Hungry Mine Creeper
SET @ENTRY := 47662;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,7500,10000,7500,10000,11,88760,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shot Web"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,12500,5000,12500,11,3396,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Corrosive Poison"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,11,88894,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Quest Credit");

-- Torn Fin Muckdweller
SET @ENTRY := 2374;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,5,8000,12000,11,3427,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Muckdweller - At 0 - 5 Range - Cast Infected Wound"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Muckdweller - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,47662,15,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Creeper");

-- Torn Fin Coastrunner
SET @ENTRY := 2375;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,1,0,100,0,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - Out Of Combat - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - Out Of Combat - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,2,3,4,0,100,0,0,0,0,0,11,10277,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - On Aggro - Cast Throw"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - On Aggro - Increment Phase"),
(@ENTRY,@SOURCETYPE,4,5,9,0,100,0,5,30,2300,3900,11,10277,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 5 - 30 Range - Cast Throw"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 5 - 30 Range - Display ranged weapon"),
(@ENTRY,@SOURCETYPE,6,7,9,0,100,0,25,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 25 - 80 Range - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 25 - 80 Range - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,8,0,9,0,100,0,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 0 - 5 Range - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,9,10,9,0,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 0 - 5 Range - Display melee weapon"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 0 - 5 Range - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,11,12,9,0,100,0,5,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 5 - 15 Range - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,12,0,61,0,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 5 - 15 Range - Start Auto Attack"),
(@ENTRY,@SOURCETYPE,13,0,2,0,100,1,0,15,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 15% HP - Increment Phase"),
(@ENTRY,@SOURCETYPE,14,15,2,0,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 15% HP - Allow Combat Movement"),
(@ENTRY,@SOURCETYPE,15,0,61,0,100,0,0,0,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,16,0,61,0,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Torn Fin Coastrunner - On Evade - Display melee weapon"),
(@ENTRY,@SOURCETYPE,17,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,47662,15,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Creeper");

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=2375;
UPDATE `creature_template` SET `VehicleId`=1270 WHERE `entry`=47488;
UPDATE `spell_target_position` SET `target_orientation`=2.51 WHERE `id`=88542 AND `effIndex`=0;
UPDATE `creature_template` SET `IconName`='vehichleCursor', `npcflag`=16777216 WHERE `entry`=47445;
UPDATE `creature_template_addon` SET `auras`='69196' WHERE `entry`=47433;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47445';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47445, 88542, 3);

DELETE FROM `page_text` WHERE `entry` IN (3718, 3719, 3720);
INSERT INTO `page_text` (`entry`, `text`, `next_page`, `WDBVerified`) VALUES
(3718, 'Daily Report - Hillsbrad Foothills\r\n\r\nSouthshore Under Attack - Worgen Activity Increasing\r\n\r\nReports of worgen activity from the south, specifically around Southshore, are increasing in frequency. Our scouts indicate that the terrorist known as Ivar Bloodfang and his renegades are responsible for these recent attacks against our citizens.\r\n\r\nRecommendation: Send capable heroes to investigate.', 3719, 15595),
(3719, 'Trouble at the Sludge Fields\r\n\r\nThe area formerly known as Hillsbrad Fields - now known as the Sludge Fields, located in southwestern Hillsbrad - has seen a sharp rise in "accidents." Reports from Warden Stillwater indicate possible contagion outbreak.\r\n\r\nRecommendation: Send capable heroes to investigate.', 3720, 15595),
(3720, 'Azurelode Spider Farm Productivity Issues\r\n\r\nOur spider domestication operations in the area near Azurelode Mine, located in the southwest region of Hillsbrad, are seeing extremely low production numbers. Spider-Handler Sarus and Captain Keyton have requested assistance.\r\n\r\nRecommendation: Send capable heroes to investigate.', 0, 15595);

UPDATE `creature` SET `phaseMask`=3 WHERE `guid` IN (199109,199113,199118,199121,199123,199111,199107,199119,199115,199114,
199106,199105,199116,199117,199110,199108);

-- Skeletal Steed
SET @ENTRY := 47488;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,85,88476,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Quest Giver on Invoker"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,85,88477,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Remove Quest Giver from Invoker");

UPDATE `creature_template` SET `minlevel`=19, `maxlevel`=19 WHERE `entry`=47444;

DELETE FROM `creature_text` WHERE `entry`=47444;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47444,0,0,'HI! HI! HELP!',12,0,100,0,0,0,'Comment'),
(47444,1,0,'HI! HI! HELP!',12,0,100,0,0,0,'Comment'),
(47444,2,0,'NORTH! GOT IT! THANKS! BYE! THANKS!',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '47444';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47444, 1, -587.72, 458.65, 82.04, 'Dumass WP'),
(47444, 2, -588.36, 429.93, 79.69, 'Dumass WP'),
(47444, 3, -578.15, 424.70, 79.84, 'Dumass WP');

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (12272, 12273);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(12273, 0, 0, 'Maybe you should go take a nap or something. I don\'t know if I have any work for you.', 1, 1, 12272, 0, 0, 0, ''),
(12272, 0, 0, 'Wait a minute. It looks like something just came up. Yes, right here on this sheet of paper. You need to head southeast to the Azurelode Mine and report to Captain Keyton. Southeast is that way *you point southeast*.', 1, 1, 0, 0, 0, 0, '');

UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80 WHERE `entry`=47443;

DELETE FROM `waypoints` WHERE `entry` = '47443';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47443, 1, -583.33, 426.89, 78.60, 'Orkus WP'),
(47443, 2, -578.81, 424.74, 79.82, 'Orkus WP');

DELETE FROM `creature_text` WHERE `entry`=47443;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47443,0,0,'CAN YOU SMELL WHAT THE LOK\'TAR IS COOKIN\'?!',14,0,100,0,0,0,'Comment'),
(47443,1,0,'HAH! Looks like you\'re running out of idiots to put atop this horse, Darthalia. This is the puniest one yet.',12,0,100,0,0,0,'Comment'),
(47443,2,0,'What have you got for me today, weakling?! Point me to where the Alliance hide and I shall DOMINATE THEM!',12,0,100,0,0,0,'Comment'),
(47443,3,0,'Yes, cowardly quest giver, sit atop your pale horse while Orkus brings glory to the Horde! I shall return with a thousand skulls!',12,0,100,0,0,0,'Comment');

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (12274, 12275, 12276);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(12276, 0, 0, 'Um... Apparently there is some trouble at Southshore. Something about worgen insurgents. Maybe you could help with them?', 1, 1, 12275, 0, 0, 0, ''),
(12275, 0, 0, 'None.', 1, 1, 12274, 0, 0, 0, ''),
(12274, 0, 0, 'Right, thanks. Just go ahead and head southeast. More south than east. Probably off the coast.', 1, 1, 0, 0, 0, 0, '');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (47443, 28531);
UPDATE `creature_template` SET `minlevel`=20, `maxlevel`=20, `speed_walk`=2 WHERE `entry`=47442;

DELETE FROM `creature_text` WHERE `entry`=47499;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47499,0,0,'Stand tall and proud, $n. Don\'t let any of these scrubs give you any trouble. Show them who\'s boss! ',12,0,100,0,0,0,'Comment'),
(47499,1,0,'I see one coming now! Looks like a real winner. Keep it cool, $n. Keep it cool.',12,0,100,0,0,0,'Comment'),
(47499,2,0,'These new Forsaken tend to be a little... um... stupid. It usually takes awhile for them to acclimate.',12,0,100,0,0,0,'Comment'),
(47499,3,0,'Oh great... not this one again. I know this orc. He\'s got no business being here, but since he\'s a bottom-feeding pansy he likes to hang around here and prey on the helpless. Don\'t let him bully you.',12,0,100,0,0,0,'Comment'),
(47499,4,0,'Here\'s to hoping he never returns. Maybe he\'ll drown?',12,0,100,0,0,0,'Comment'),
(47499,5,0,'Ah, crap. You\'re on your own with this one, $n.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=47442;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47442,0,0,'Johnny Awesome has arrived, philistine. Present me with your menial tasks so that I may complete them with only mild enthusiasm and most likely a complete disregard for any directions that you provide that are more complicated than what my map is able to display.',12,0,100,0,0,0,'Comment'),
(47442,1,0,'I will do this ONE thing that you ask of me, quest giver. Pray I find more menial tasks to accomplish or you will be hearing from me again and I assure you that my commentary on forums of public opinion will be most unkind.',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '47442';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47442, 1, -580.54, 426.86, 79.79, 'Johnny Awesome WP'),
(47442, 2, -578.41, 425.13, 79.83, 'Johnny Awesome WP');

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (12277, 12278, 12279);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(12279, 0, 0, 'Well, we are having some problems at the Sludge Fields, located northeast of here. Warden Stillwater could use your help.', 1, 1, 12278, 0, 0, 0, ''),
(12278, 0, 0, 'That\'s all.', 1, 1, 12277, 0, 0, 0, ''),
(12277, 0, 0, 'THAT\'S ALL, JOHNNY AWESOME. TAKE IT OR LEAVE IT!', 1, 1, 0, 0, 0, 0, '');

UPDATE `creature` SET `spawndist`=25, `MovementType`=1 WHERE `guid`=199121;

DELETE FROM `spell_script_names` WHERE `spell_id` = '88476';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88476, 'spell_quest_giver');

-- High Executor Darthalia
SET @ENTRY := 47499;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,1,0,47499,0,0,1,1,3000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,1,0,47499,0,0,85,88559,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Summon Dumass"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,0,1,0,0,1,2,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,1,2,47499,0,0,1,3,3000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,1,2,47499,0,0,85,88560,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Summon Orkus"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,1,0,2,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,1,4,47499,0,0,1,5,3500,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,1,4,47499,0,0,85,88562,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Summon Johnny Awesome");

-- Dumass
SET @ENTRY := 47444;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,53,1,47444,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,1,1,0,0,0,0,0,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - (DO NOTHING)"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,1,1,0,0,0,54,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - WP Pause (5 secs)"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,1,2,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,1,2,0,0,0,54,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause (5 secs)"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,1,3,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,1,1,47444,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Active Gossip"),
(@ENTRY,@SOURCETYPE,7,0,62,0,100,1,12272,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,1,12272,0,0,0,33,47444,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,9,0,62,0,100,1,12272,0,0,0,1,2,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 2"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,1,2,47444,0,0,45,0,1,0,0,0,0,11,47499,80,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Darthalia"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,1,2,47444,0,0,69,0,0,0,0,0,0,8,0,0,0,-599.72,324.19,71.03,4.48,"After Talk 2 - Move Away"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,1,2,47444,0,0,41,12000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Force Despawn"),
(@ENTRY,@SOURCETYPE,13,0,62,0,100,1,12272,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Disable Gossip");

-- Kingslayer Orkus
SET @ENTRY := 47443;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,1,0,47443,0,0,53,1,47443,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - WP Start"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,1,2,0,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,1,1,47443,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,1,2,47443,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Active Gossip"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,1,0,0,0,0,43,28531,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Mount Frost Wyrm"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,1,12274,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,7,0,62,0,100,1,12274,0,0,0,33,47443,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,1,12274,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Disable Gossip"),
(@ENTRY,@SOURCETYPE,9,0,62,0,100,1,12274,0,0,0,1,3,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 3"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,1,3,47443,0,0,45,0,2,0,0,0,0,11,47499,80,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 2 to Darthalia"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,1,3,47443,0,0,69,0,0,0,0,0,0,8,0,0,0,-607.81,305.34,68.92,4.5,"After Talk 3 - Move Away"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,1,3,47443,0,0,41,12500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Force Despawn");

-- Johnny Awesome
SET @ENTRY := 47442;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,43,40625,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Mount Steed"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,1,0,0,0,0,53,0,47442,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start Wp"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,1,2,0,0,0,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,1,12277,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,1,0,47442,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Active Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,1,12277,0,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,1,12277,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Disable Gossip"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,1,1,47442,0,0,69,0,0,0,0,0,0,8,0,0,0,-604.57,318.28,70.28,4.59,"After Talk 1 - Move Away"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,1,12277,0,0,0,33,47442,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Skeletal Steed
SET @ENTRY := 47488;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,85,88476,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Quest Giver on Invoker"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,85,88477,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Remove Quest Giver from Invoker"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,85,88563,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Summon Darthalia");

DELETE FROM `spell_script_names` WHERE `spell_id` = '88477';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (88477, 'spell_quest_giver');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28189;

---
DELETE FROM `conditions` WHERE `SourceGroup`=47445 AND `SourceTypeOrReferenceId`=18;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(18, 47445, 0, 88542, 0, 9, 0, 28096, 0, 0, 0, 0, 0, '', 'Skeletal Steed - Welcome to the Machine quest');
--

DELETE FROM `conditions` WHERE `SourceEntry` = '89089';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 89089, 1, 0, 31, 0, 3, 47872, 0, 0, 0, '', 'Shovel -> Target Human Seedling');

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=47872;
UPDATE `creature_template_addon` SET `auras`='89097 89098 52970' WHERE `entry`=47872;

DELETE FROM `creature_text` WHERE `entry`=47872;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47872,0,0,'I won\'t soon forget this kindness.',12,0,100,0,0,0,'Comment'),
(47872,0,1,'Thank you for saving my life. I owe you a debt of gratitude.',12,0,100,0,0,0,'Comment'),
(47872,0,2,'It... they planted us in the dirt like crops. Stillwater is insane! Get out of here while you still can!',12,0,100,0,0,0,'Comment'),
(47872,0,3,'He killed everyone! EVERYONE!',12,0,100,0,0,0,'Comment'),
(47872,0,4,'M... maybe you\'re not all bad after all...',12,0,100,0,0,0,'Comment'),
(47872,0,5,'Should you ever be buried neck deep in a field of feces and urine, I will be sure to lend you a hand.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_template_addon` WHERE `entry` IN (47859, 47861);
DELETE FROM `creature` WHERE `id` IN (47859, 47861);

SET @CGUID := 798529;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+9;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 47859, 0, 1, 1, 0, 1, -571.178, -27.8558, 45.9983, 2.10814, 120, 15, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+1, 47859, 0, 1, 1, 0, 1, -583.312, -21.9005, 46.3085, 3.23539, 120, 15, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+2, 47859, 0, 1, 1, 0, 1, -562.693, -39.9602, 45.9163, 1.82801, 120, 15, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+3, 47859, 0, 1, 1, 0, 1, -563.427, -60.0632, 45.6772, 0.312636, 120, 15, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+4, 47859, 0, 1, 1, 0, 1, -573.19, -68.1187, 45.796, 0.822261, 120, 15, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+5, 47859, 0, 1, 1, 0, 1, -592.491, -54.3841, 45.9484, 2.97794, 120, 15, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+6, 47859, 0, 1, 1, 0, 1, -599.467, -71.1654, 46.0188, 4.5472, 120, 15, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+7, 47859, 0, 1, 1, 0, 1, -586.338, -81.3296, 46.091, 5.90957, 120, 15, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+8, 47859, 0, 1, 1, 0, 1, -586.994, -40.9761, 45.7054, 5.99726, 120, 15, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+9, 47859, 0, 1, 1, 0, 1, -604.527, -33.3329, 45.9063, 0.297951, 120, 15, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+10, 47859, 0, 1, 1, 0, 1, -599.441, -16.9375, 45.7164, 3.10601, 120, 15, 0, 458, 0, 1, 0, 0, 0);

SET @CGUID := 798539;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+13;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 47861, 0, 1, 1, 0, 1, -605.698, 8.79009, 46.3757, 5.74641, 120, 10, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+1, 47861, 0, 1, 1, 0, 1, -573.387, -109.845, 47.4545, 5.19291, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+2, 47861, 0, 1, 1, 0, 1, -557.317, -97.3762, 46.4568, 3.33328, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+3, 47861, 0, 1, 1, 0, 1, -542.42, -94.1161, 45.609, 3.67078, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+4, 47861, 0, 1, 1, 0, 1, -524.463, -81.7107, 47.4636, 4.17703, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+5, 47861, 0, 1, 1, 0, 1, -522.346, -59.8126, 49.8727, 5.97928, 120, 10, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+6, 47861, 0, 1, 1, 0, 1, -540.445, -40.0088, 45.9972, 4.80141, 120, 10, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+7, 47861, 0, 1, 1, 0, 1, -551.686, -13.5784, 46.3677, 5.13216, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+8, 47861, 0, 1, 1, 0, 1, -553.967, 25.1, 48.0303, 5.01741, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+9, 47861, 0, 1, 1, 0, 1, -552.497, 45.9448, 48.2367, 6.14128, 120, 10, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+10, 47861, 0, 1, 1, 0, 1, -565.69, 41.6958, 48.0922, 1.03935, 120, 10, 0, 494, 0, 1, 0, 0, 0),
(@CGUID+11, 47861, 0, 1, 1, 0, 1, -574.544, 25.8442, 47.6375, 0.701849, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+12, 47861, 0, 1, 1, 0, 1, -588.645, 11.4464, 47.1495, 1.03935, 120, 10, 0, 458, 0, 1, 0, 0, 0),
(@CGUID+13, 47861, 0, 1, 1, 0, 1, -623.857, 8.50143, 45.5275, 0.306974, 120, 10, 0, 494, 0, 1, 0, 0, 0);

DELETE FROM `gameobject_involvedrelation` WHERE `quest` = '28189';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(206944, 28189);

DELETE FROM `creature_text` WHERE `entry`=2270;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2270,0,0,'Hillsbrad Sentry weakens! Capture them with your shackles!',41,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '88797';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88797, 'spell_shackle');

-- Hillsbrad Sentry
SET @ENTRY := 2270;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,0,30,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Health 30% - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,88797,1,0,0,85,88801,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Summon Captured"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,88797,1,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Force Despawn "),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,88797,1,0,0,33,47697,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Killed Monster "),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Defensive"),
(@ENTRY,@SOURCETYPE,5,0,11,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Respawn - Set Defensive"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,5000,5000,5000,5000,11,87969,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Add Poison");

-- Captured Hillsbrad Human
SET @ENTRY := 47694;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,8,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Summoner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,1,4000,4000,4000,4000,85,88964,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Chains to Summoner"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive");

UPDATE `creature_template` SET `VehicleId`=1292, `InhabitType`=7, `speed_run`=2.14286, `unit_flags`=2, `flags_extra`=2 WHERE `entry`=47928;
UPDATE `spell_target_position` SET `target_position_x`=-501.79, `target_position_y`=118.25, `target_position_z`=113.06, `target_orientation`=4.76 WHERE `id`=89144 AND `effIndex`=0;

DELETE FROM `waypoints` WHERE `entry` = '47928';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47928, 1, -506.32, 69.11, 100.34, 'Sludge Camera WP'),
(47928, 2, -523.86, 68.42, 91.81, 'Sludge Camera WP'),
(47928, 3, -562.37, 77.10, 78.99, 'Sludge Camera WP'),
(47928, 4, -645.17, 60.35, 71.41, 'Sludge Camera WP'),
(47928, 5, -640.11, -65.74, 61.76, 'Sludge Camera WP'),
(47928, 6, -502.05, -64.90, 69.20, 'Sludge Camera WP'),
(47928, 7, -393.69, -22.95, 54.34, 'Sludge Camera WP'),
(47928, 8, -378.18, -44.99, 69.62, 'Sludge Camera WP'),
(47928, 9, -448.85, 18.79, 66.24, 'Sludge Camera WP'),
(47928, 10, -504.81, 27.50, 57.03, 'Sludge Camera WP'),
(47928, 11, -501.05, 87.52, 58.17, 'Sludge Camera WP');

DELETE FROM `creature_text` WHERE `entry`=47928;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47928,0,0,'|cffffffffThere\'s trouble at the Sludge Fields...',41,0,100,0,0,0,'Comment');

-- Sludge Fields Camera
SET @ENTRY := 47928;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,8000,8000,8000,8000,1,0,1000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,85,91202,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Blackout"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,47928,0,0,53,1,47928,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Start WP"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,11,0,0,0,11,89154,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Quest Complete"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,11,0,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,11,0,0,0,28,89149,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 11 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,6,0,28,0,100,0,0,0,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

-- Warden Stillwater
SET @ENTRY := 47781;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,28192,0,0,0,85,89144,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Camera");

UPDATE `creature_template` SET `mindmg`=24, `maxdmg`=36, `attackpower`=9 WHERE `entry`=47791;

-- Citizen Wilkes
SET @ENTRY := 47791;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,11,86345,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"OOC - Jump to Target");

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=197787;

DELETE FROM `conditions` WHERE `SourceEntry` = '89821';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 89821, 1, 0, 31, 0, 3, 48269, 0, 0, 0, '', 'Helcular\'s Rod -> Target Dark Ranger');

DELETE FROM `spell_script_names` WHERE `spell_id` = '89821';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89821, 'spell_helcular_rod');

-- Dark Ranger
SET @ENTRY := 48269;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,89824,1,0,0,33,48269,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

DELETE FROM `spell_area` WHERE `quest_start` IN (28206, 28209, 28230, 28231, 28235, 28237, 28251);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(89275, 286, 28206, 0, 1, 11, 11),
(89275, 286, 28209, 0, 1, 11, 11),
(89275, 286, 28230, 0, 1, 11, 11),
(89275, 286, 28231, 0, 1, 11, 11),
(89275, 286, 28235, 0, 1, 11, 11),
(89275, 286, 28237, 0, 1, 11, 11),
(89275, 286, 28251, 0, 1, 11, 11);

DELETE FROM `creature_text` WHERE `entry`=47900;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47900,0,0,'YOU THERE! Yes, you! I have been captured against my will and imprisoned illegaly by Warden Stillwater. Get me out of this cage and I will explain everything.',12,0,100,0,0,0,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6476';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6476, 'at_sludge_fields_cage');

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=82.648 WHERE `entry`=47789 AND `item`=63250;
UPDATE `creature_template` SET `lootid`=48017 WHERE `entry`=48017;

DELETE FROM `creature_loot_template` WHERE `entry` = '48017';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48017, 789, 0.05, 1, 0, 1, 1),
(48017, 790, 0.2517, 1, 0, 1, 1),
(48017, 804, 0.1888, 1, 0, 1, 1),
(48017, 856, 0.05, 1, 0, 1, 1),
(48017, 857, 0.05, 1, 0, 1, 1),
(48017, 858, 1.4, 1, 0, 1, 1),
(48017, 929, 10.8108, 1, 0, 1, 1),
(48017, 935, 0.003, 1, 0, 1, 1),
(48017, 1179, 1.8, 1, 0, 1, 1),
(48017, 1205, 2.6, 1, 0, 1, 1),
(48017, 1206, 0.1929, 1, 0, 1, 1),
(48017, 1738, 0.1, 1, 0, 1, 1),
(48017, 1739, 0.2, 1, 0, 1, 1),
(48017, 1740, 0.1, 1, 0, 1, 1),
(48017, 1742, 0.1, 1, 0, 1, 1),
(48017, 1743, 0.1809, 1, 0, 1, 1),
(48017, 1744, 0.1, 1, 0, 1, 1),
(48017, 1745, 0.1, 1, 0, 1, 1),
(48017, 1746, 0.1, 1, 0, 1, 1),
(48017, 1747, 0.1, 1, 0, 1, 1),
(48017, 1748, 0.1636, 1, 0, 1, 1),
(48017, 1749, 0.1888, 1, 0, 1, 1),
(48017, 1750, 0.1, 1, 0, 1, 1),
(48017, 1751, 0.1, 1, 0, 1, 1),
(48017, 1752, 0.1, 1, 0, 1, 1),
(48017, 1753, 0.1, 1, 0, 1, 1),
(48017, 1764, 0.1, 1, 0, 1, 1),
(48017, 1766, 0.2, 1, 0, 1, 1),
(48017, 1767, 0.2, 1, 0, 1, 1),
(48017, 1768, 0.1, 1, 0, 1, 1),
(48017, 1769, 0.2, 1, 0, 1, 1),
(48017, 1770, 0.2, 1, 0, 1, 1),
(48017, 1772, 0.1, 1, 0, 1, 1),
(48017, 1774, 0.1, 1, 0, 1, 1),
(48017, 1775, 0.2, 1, 0, 1, 1),
(48017, 1776, 0.1, 1, 0, 1, 1),
(48017, 1777, 0.1, 1, 0, 1, 1),
(48017, 1778, 2.2654, 1, 0, 1, 1),
(48017, 1787, 0.1, 1, 0, 1, 1),
(48017, 1788, 0.2, 1, 0, 1, 1),
(48017, 1789, 0.2, 1, 0, 1, 1),
(48017, 1791, 0.1, 1, 0, 1, 1),
(48017, 1792, 0.2, 1, 0, 1, 1),
(48017, 1793, 0.1, 1, 0, 1, 1),
(48017, 1794, 0.2, 1, 0, 1, 1),
(48017, 1795, 0.1, 1, 0, 1, 1),
(48017, 1796, 0.1, 1, 0, 1, 1),
(48017, 1797, 0.1, 1, 0, 1, 1),
(48017, 1798, 0.1, 1, 0, 1, 1),
(48017, 1799, 0.1, 1, 0, 1, 1),
(48017, 1800, 0.1, 1, 0, 1, 1),
(48017, 1801, 0.1, 1, 0, 1, 1),
(48017, 1802, 0.1, 1, 0, 1, 1),
(48017, 1811, 0.2, 1, 0, 1, 1),
(48017, 1812, 0.2, 1, 0, 1, 1),
(48017, 1813, 0.2, 1, 0, 1, 1),
(48017, 1814, 0.1, 1, 0, 1, 1),
(48017, 1815, 0.2, 1, 0, 1, 1),
(48017, 1817, 0.2, 1, 0, 1, 1),
(48017, 1818, 0.2, 1, 0, 1, 1),
(48017, 1819, 0.2, 1, 0, 1, 1),
(48017, 1820, 0.1, 1, 0, 1, 1),
(48017, 1821, 0.2, 1, 0, 1, 1),
(48017, 1822, 0.1, 1, 0, 1, 1),
(48017, 1823, 0.1, 1, 0, 1, 1),
(48017, 1824, 0.2, 1, 0, 1, 1),
(48017, 2216, 0.1, 1, 0, 1, 1),
(48017, 2217, 0.1, 1, 0, 1, 1),
(48017, 2219, 0.1, 1, 0, 1, 1),
(48017, 2220, 0.05, 1, 0, 1, 1),
(48017, 2256, 0.003, 1, 0, 1, 1),
(48017, 2409, 0.0663, 1, 0, 1, 1),
(48017, 2455, 0.8, 1, 0, 1, 1),
(48017, 2553, 0.05, 1, 0, 1, 1),
(48017, 2589, 30.2, 1, 0, 1, 3),
(48017, 2592, 36.4, 1, 0, 1, 2),
(48017, 2601, 0.009, 1, 0, 1, 1),
(48017, 2764, 0.3, 1, 0, 1, 1),
(48017, 2765, 0.1, 1, 0, 1, 1),
(48017, 2780, 0.1, 1, 0, 1, 1),
(48017, 2781, 0.3021, 1, 0, 1, 1),
(48017, 2782, 0.1, 1, 0, 1, 1),
(48017, 2783, 0.1, 1, 0, 1, 1),
(48017, 2879, 0.006, 1, 0, 1, 1),
(48017, 2882, 0.0121, 1, 0, 1, 1),
(48017, 2883, 0.006, 1, 0, 1, 1),
(48017, 2981, 0.0332, 1, 0, 1, 1),
(48017, 2982, 0.0995, 1, 0, 1, 1),
(48017, 2985, 0.0271, 1, 0, 1, 1),
(48017, 2986, 0.1025, 1, 0, 1, 1),
(48017, 2988, 0.0301, 1, 0, 1, 1),
(48017, 2989, 0.0422, 1, 0, 1, 1),
(48017, 2990, 0.0332, 1, 0, 1, 1),
(48017, 2991, 0.0633, 1, 0, 1, 1),
(48017, 2992, 0.0663, 1, 0, 1, 1),
(48017, 3039, 0.0378, 1, 0, 1, 1),
(48017, 3040, 0.0844, 1, 0, 1, 1),
(48017, 3057, 0.0121, 1, 0, 1, 1),
(48017, 3065, 0.0362, 1, 0, 1, 1),
(48017, 3184, 0.1296, 1, 0, 1, 1),
(48017, 3193, 0.0995, 1, 0, 1, 1),
(48017, 3198, 0.0378, 1, 0, 1, 1),
(48017, 3199, 0.0693, 1, 0, 1, 1),
(48017, 3202, 0.0121, 1, 0, 1, 1),
(48017, 3211, 0.006, 1, 0, 1, 1),
(48017, 3376, 0.1, 1, 0, 1, 1),
(48017, 3377, 0.1, 1, 0, 1, 1),
(48017, 3378, 2.5801, 1, 0, 1, 1),
(48017, 3379, 0.1, 1, 0, 1, 1),
(48017, 3385, 0.6, 1, 0, 1, 1),
(48017, 3393, 0.006, 1, 0, 1, 1),
(48017, 3610, 0.2517, 1, 0, 1, 1),
(48017, 3647, 0.0362, 1, 0, 1, 1),
(48017, 3655, 0.0121, 1, 0, 1, 1),
(48017, 4292, 0.1888, 1, 0, 1, 1),
(48017, 4293, 0.05, 1, 0, 1, 1),
(48017, 4306, 4.1, 1, 0, 1, 1),
(48017, 4346, 0.05, 1, 0, 1, 1),
(48017, 4349, 0.0126, 1, 0, 1, 1),
(48017, 4408, 0.1888, 1, 0, 1, 1),
(48017, 4409, 0.2517, 1, 0, 1, 1),
(48017, 4568, 0.1326, 1, 0, 1, 1),
(48017, 4575, 0.6293, 1, 0, 1, 1),
(48017, 4576, 0.0874, 1, 0, 1, 1),
(48017, 4605, 4.1692, 1, 0, 1, 1),
(48017, 4606, 4.2656, 1, 0, 1, 1),
(48017, 4694, 0.0211, 1, 0, 1, 1),
(48017, 4697, 0.0512, 1, 0, 1, 1),
(48017, 4698, 0.2171, 1, 0, 1, 1),
(48017, 4700, 0.0724, 1, 0, 1, 1),
(48017, 4706, 0.003, 1, 0, 1, 1),
(48017, 4708, 0.009, 1, 0, 1, 1),
(48017, 4710, 0.0211, 1, 0, 1, 1),
(48017, 5207, 0.1537, 1, 0, 1, 1),
(48017, 5376, 24.3243, 1, 0, 1, 1),
(48017, 5573, 0.0392, 1, 0, 1, 1),
(48017, 5574, 0.05, 1, 0, 1, 1),
(48017, 5575, 0.1259, 1, 0, 1, 1),
(48017, 6342, 0.05, 1, 0, 1, 1),
(48017, 6347, 0.0181, 1, 0, 1, 1),
(48017, 6348, 0.0181, 1, 0, 1, 1),
(48017, 6375, 0.009, 1, 0, 1, 1),
(48017, 6381, 0.006, 1, 0, 1, 1),
(48017, 6382, 0.0241, 1, 0, 1, 1),
(48017, 6383, 0.009, 1, 0, 1, 1),
(48017, 6390, 0.0063, 1, 0, 1, 1),
(48017, 6536, 0.0121, 1, 0, 1, 1),
(48017, 6538, 0.0241, 1, 0, 1, 1),
(48017, 6552, 0.0151, 1, 0, 1, 1),
(48017, 6561, 0.0271, 1, 0, 1, 1),
(48017, 6562, 0.0995, 1, 0, 1, 1),
(48017, 6563, 0.0995, 1, 0, 1, 1),
(48017, 6564, 0.0422, 1, 0, 1, 1),
(48017, 6565, 0.0121, 1, 0, 1, 1),
(48017, 6566, 0.0629, 1, 0, 1, 1),
(48017, 6568, 0.0629, 1, 0, 1, 1),
(48017, 6570, 0.0271, 1, 0, 1, 1),
(48017, 6571, 0.009, 1, 0, 1, 1),
(48017, 6572, 0.0392, 1, 0, 1, 1),
(48017, 6573, 0.0211, 1, 0, 1, 1),
(48017, 6574, 0.0452, 1, 0, 1, 1),
(48017, 6575, 0.0663, 1, 0, 1, 1),
(48017, 6576, 0.0063, 1, 0, 1, 1),
(48017, 6577, 0.0121, 1, 0, 1, 1),
(48017, 6578, 0.006, 1, 0, 1, 1),
(48017, 6580, 0.0271, 1, 0, 1, 1),
(48017, 6581, 0.0573, 1, 0, 1, 1),
(48017, 6582, 0.009, 1, 0, 1, 1),
(48017, 6583, 0.0693, 1, 0, 1, 1),
(48017, 6585, 0.0935, 1, 0, 1, 1),
(48017, 6586, 0.0392, 1, 0, 1, 1),
(48017, 6588, 0.0271, 1, 0, 1, 1),
(48017, 6716, 0.05, 1, 0, 1, 1),
(48017, 7092, 0.0063, 1, 0, 1, 1),
(48017, 7554, 0.0543, 1, 0, 1, 1),
(48017, 7608, 0.0241, 1, 0, 1, 1),
(48017, 8491, 0.0151, 1, 0, 1, 1),
(48017, 9775, 0.0211, 1, 0, 1, 1),
(48017, 9776, 0.0452, 1, 0, 1, 1),
(48017, 9777, 0.0211, 1, 0, 1, 1),
(48017, 9778, 0.0211, 1, 0, 1, 1),
(48017, 9780, 0.0633, 1, 0, 1, 1),
(48017, 9781, 0.0211, 1, 0, 1, 1),
(48017, 9782, 0.0151, 1, 0, 1, 1),
(48017, 9783, 0.0693, 1, 0, 1, 1),
(48017, 9784, 0.0241, 1, 0, 1, 1),
(48017, 9787, 0.0482, 1, 0, 1, 1),
(48017, 9789, 0.0181, 1, 0, 1, 1),
(48017, 9790, 0.0211, 1, 0, 1, 1),
(48017, 9811, 0.0063, 1, 0, 1, 1),
(48017, 9812, 0.0241, 1, 0, 1, 1),
(48017, 10405, 0.0422, 1, 0, 1, 1),
(48017, 10407, 0.0603, 1, 0, 1, 1),
(48017, 11038, 0.0151, 1, 0, 1, 1),
(48017, 11039, 0.0181, 1, 0, 1, 1),
(48017, 11081, 0.006, 1, 0, 1, 1),
(48017, 11965, 0.0422, 1, 0, 1, 1),
(48017, 11981, 0.0241, 1, 0, 1, 1),
(48017, 11982, 0.0063, 1, 0, 1, 1),
(48017, 11993, 0.1598, 1, 0, 1, 1),
(48017, 12052, 0.0452, 1, 0, 1, 1),
(48017, 12053, 0.0362, 1, 0, 1, 1),
(48017, 12054, 0.009, 1, 0, 1, 1),
(48017, 12975, 0.006, 1, 0, 1, 1),
(48017, 12976, 0.003, 1, 0, 1, 1),
(48017, 12977, 0.003, 1, 0, 1, 1),
(48017, 12978, 0.009, 1, 0, 1, 1),
(48017, 12979, 0.009, 1, 0, 1, 1),
(48017, 12982, 0.003, 1, 0, 1, 1),
(48017, 12983, 0.0362, 1, 0, 1, 1),
(48017, 12984, 0.009, 1, 0, 1, 1),
(48017, 12985, 0.006, 1, 0, 1, 1),
(48017, 12987, 0.006, 1, 0, 1, 1),
(48017, 12989, 0.003, 1, 0, 1, 1),
(48017, 12990, 0.003, 1, 0, 1, 1),
(48017, 12994, 0.003, 1, 0, 1, 1),
(48017, 12996, 0.006, 1, 0, 1, 1),
(48017, 13136, 0.0271, 1, 0, 1, 1),
(48017, 14166, 0.0241, 1, 0, 1, 1),
(48017, 14167, 0.0241, 1, 0, 1, 1),
(48017, 14168, 0.0784, 1, 0, 1, 1),
(48017, 14170, 0.0392, 1, 0, 1, 1),
(48017, 14171, 0.0241, 1, 0, 1, 1),
(48017, 14172, 0.0121, 1, 0, 1, 1),
(48017, 14173, 0.1236, 1, 0, 1, 1),
(48017, 14174, 0.0362, 1, 0, 1, 1),
(48017, 14175, 0.0181, 1, 0, 1, 1),
(48017, 15211, 0.0378, 1, 0, 1, 1),
(48017, 15222, 0.1, 1, 0, 1, 1),
(48017, 15223, 0.05, 1, 0, 1, 1),
(48017, 15248, 0.1176, 1, 0, 1, 1),
(48017, 15912, 0.009, 1, 0, 1, 1),
(48017, 16882, 59.4595, 1, 0, 1, 1),
(48017, 63281, -23.4204, 1, 0, 1, 1);

UPDATE `quest_template` SET `PrevQuestId`=28209 WHERE `Id` IN (28231, 28230);
UPDATE `creature_template` SET `mindmg`=24, `maxdmg`=39, `attackpower`=9, `dmg_multiplier`=1.1 WHERE `entry` IN (48017, 47861, 47791, 47789);
UPDATE `creature_template` SET `mindmg`=18, `maxdmg`=27, `attackpower`=7, `dmg_multiplier`=1.3 WHERE `entry` IN (47792, 47793);
UPDATE `creature_template` SET `spell1`=89272, `spell2`=6016 WHERE `entry`=47861;
UPDATE `creature_template` SET `spell1`=42745 WHERE `entry`=47789;
UPDATE `creature_template` SET `spell1`=83021, `spell2`=83019 WHERE `entry`=47792;

-- Blacksmith Verringtan
SET @ENTRY := 47792;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,50,0,5000,5000,5000,5000,11,83021,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC -  Cast Blight Bomb"),
(@ENTRY,@SOURCETYPE,1,0,0,0,50,0,5000,5000,5000,5000,11,83019,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC -  Cast Toxic Waste");

-- Magistrate Burnside
SET @ENTRY := 47790;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,33,0,5000,5000,5000,5000,11,11969,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC -  Cast Fire Nova"),
(@ENTRY,@SOURCETYPE,1,0,0,0,50,0,5000,5000,5000,5000,11,20811,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC -  Cast Fireball"),
(@ENTRY,@SOURCETYPE,2,0,0,0,33,0,5000,5000,5000,5000,11,7739,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC -  Cast Inferno Shell"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,2500,2500,2500,2500,49,0,0,0,0,0,0,18,8,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Players"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,47790,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,4,0,100,0,0,0,0,0,18,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,18,33536,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Unit Flag");

-- The Ray-Getz-Kalaba Monstrosity
SET @ENTRY := 47793;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,65,0,5000,5000,5000,5000,11,95002,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Belch");

-- Risen Hillsbrad Peasant
SET @ENTRY := 47861;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,50,0,5000,5000,5000,5000,11,89272,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Eat Face"),
(@ENTRY,@SOURCETYPE,1,0,0,0,50,0,5000,5000,5000,5000,11,6016,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Pierce Armor");

-- Clerk Horrace Whitesteed
SET @ENTRY := 47789;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,75,0,5000,5000,5000,5000,11,42745,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Enrage");

-- Master Apothecary Lydon
SET @ENTRY := 48020;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,12,0,5000,5000,5000,5000,11,54633,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Drink Potion"),
(@ENTRY,@SOURCETYPE,1,0,0,0,12,0,5000,5000,5000,5000,11,17137,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Flash Heal"),
(@ENTRY,@SOURCETYPE,2,0,0,0,12,0,5000,5000,5000,5000,11,17137,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Flash Heal (Friendly)"),
(@ENTRY,@SOURCETYPE,3,0,0,0,12,0,5000,5000,5000,5000,11,11974,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Power Word: Shield (Self)"),
(@ENTRY,@SOURCETYPE,4,0,0,0,12,0,5000,5000,5000,5000,11,11974,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Power Word: Shield (Friendly)"),
(@ENTRY,@SOURCETYPE,5,0,0,0,12,0,5000,5000,5000,5000,11,11640,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Renew (Friendly)"),
(@ENTRY,@SOURCETYPE,6,0,0,0,12,0,5000,5000,5000,5000,11,11640,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Renew (Self)"),
(@ENTRY,@SOURCETYPE,7,0,0,0,12,0,5000,5000,5000,5000,11,84713,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Toxic Potion"),
(@ENTRY,@SOURCETYPE,8,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

-- Johnny Awesome
SET @ENTRY := 48021;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,17,0,5000,5000,5000,5000,11,80003,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Black Arrow"),
(@ENTRY,@SOURCETYPE,1,0,0,0,17,0,5000,5000,5000,5000,11,79721,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosive Shot"),
(@ENTRY,@SOURCETYPE,2,0,0,0,50,0,5000,5000,5000,5000,11,6660,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Shoot"),
(@ENTRY,@SOURCETYPE,3,0,0,0,17,0,5000,5000,5000,5000,11,80004,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Snake Trap"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,28,89275,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Aura To Owner"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

UPDATE `quest_template` SET `SourceSpellId`=89293 WHERE `Id` IN (28230, 28235, 28237, 28251); 
UPDATE `creature_template` SET `minlevel`=19, `maxlevel`=19, `mindmg`=40, `maxdmg`=65, `attackpower`=1, `dmg_multiplier`=1.3, `baseattacktime`=1500, `rangeattacktime`=1500 WHERE `entry` IN (48020, 48021);

DELETE FROM `creature_text` WHERE `entry`=47790;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47790,0,0,'See now the product of your meddling!',14,0,100,0,0,0,'Comment'),
(47790,1,0,'BURN IN MY HATRED!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_questrelation` WHERE `id` = '48020' AND `quest` IN (28230, 28235, 28237, 28251);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(48020, 28230),
(48020, 28235),
(48020, 28237),
(48020, 28251);

DELETE FROM `creature_involvedrelation` WHERE `id` = '48020' AND `quest` IN (28230, 28235, 28237, 28251);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(48020, 28230),
(48020, 28235),
(48020, 28237),
(48020, 28251);

DELETE FROM `creature_questrelation` WHERE `id` = '47900' AND `quest` IN (28230, 28235, 28237, 28251);
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(47900, 28230),
(47900, 28235),
(47900, 28237),
(47900, 28251);

DELETE FROM `creature_involvedrelation` WHERE `id` = '47900' AND `quest` IN (28230, 28235, 28237, 28251);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(47900, 28230),
(47900, 28235),
(47900, 28237),
(47900, 28251);

UPDATE `quest_template` SET `PrevQuestId`=28235 WHERE `Id`=28237;

DELETE FROM `creature_text` WHERE `entry`=48080;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48080,0,0,'Lydon!? Alive?',12,0,100,0,1,0,'Comment'),
(48080,1,0,'Now I know where your allegiances lie...!',12,0,100,0,1,0,'Comment'),
(48080,2,0,'And you, Jenny? I thought we had a connection. You\'ve broken my heart for the last time. ',12,0,100,0,1,0,'Comment'),
(48080,3,0,'I AM A THREAT? I AM DERANGED?!',12,0,100,0,11,0,'Comment'),
(48080,4,0,'What I\'ve created here is an evolution! THIS is how the Forsaken will thrive, not through some magical winged fairy sprinkling happy dust on corpses!',12,0,100,0,1,0,'Comment'),
(48080,5,0,'Kill them all! They will serve as subjects for our next study!',12,0,100,0,1,0,'Comment'),
(48080,6,0,'You think that you\'ve won? THINK AGAIN! Stand before my new form and tremble! ',14,0,100,0,1,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=48020;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48020,0,0,'Warden Stillwater, you are deranged and a threat to our way of life. By authority of the Dark Lady herself, I hereby impose upon you the harshest penalty under Forsaken law - true death. ',12,0,100,0,1,0,'Comment'),
(48020,1,0,'That goes for all of you traitorous scum who supported this fool!',12,0,100,0,1,0,'Comment'),
(48020,2,0,'KNEEL!',12,0,100,0,1,0,'Comment');

DELETE FROM `creature` WHERE `guid`=773285;
UPDATE `creature` SET `phaseMask`=32769 WHERE `guid`=706483;

SET @CGUID := 798700;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+1;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 48021, 0, 1, 32768, 0, 1, -499.481, 73.0664, 54.8062, 1.50801, 300, 0, 0, 1347, 0, 0, 0, 0, 0),
(@CGUID+1, 48020, 0, 1, 32768, 0, 1, -501.919, 73.2197, 54.8167, 1.50801, 300, 0, 0, 2694, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=48080;
UPDATE `creature_template` SET `faction_A`=71, `faction_H`=71 WHERE `entry` IN (48020, 48021);
UPDATE `creature_template` SET `faction_A`=14, `faction_H`=14, `mindmg`=24, `maxdmg`=42, `attackpower`=5, `dmg_multiplier`=1.3, `unit_flags`=0, `unit_flags2`=2048, `dynamicflags`=0 WHERE `entry`=47834;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=47834;

DELETE FROM `creature` WHERE `guid`=776575;

-- Sludge Guard
SET @ENTRY := 48083;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Faction Hostile"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,2,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Die");

-- Warden Stillwater
SET @ENTRY := 48080;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,50000,50000,50000,50000,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - 50 secs (Set Faction Hostile)"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,50000,50000,50000,50000,49,14,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Update - 50 secs (Attack Player Nearest)"),
(@ENTRY,@SOURCETYPE,3,0,0,0,50,0,5000,5000,5000,5000,11,89463,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Plague Barrel"),
(@ENTRY,@SOURCETYPE,4,0,0,0,50,0,5000,5000,5000,5000,11,89461,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Plague Slime"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,1,50000,50000,50000,50000,45,0,1,0,0,0,0,11,48083,50,0,0.0,0.0,0.0,0.0,"Update - 50 secs (Set Data 1 to Guards)"),
(@ENTRY,@SOURCETYPE,6,0,6,0,100,0,0,0,0,0,12,47834,4,120000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon Monster"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 6"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Force Despawn"),
(@ENTRY,@SOURCETYPE,9,0,11,0,100,0,0,0,0,0,70,0,0,0,0,0,0,11,48083,200,0,0.0,0.0,0.0,0.0,"On Respawn - Respawn Guards"),
(@ENTRY,@SOURCETYPE,10,0,11,0,100,0,0,0,0,0,70,0,0,0,0,0,0,11,48081,200,0,0.0,0.0,0.0,0.0,"On Respawn - Respawn Arnauld"),
(@ENTRY,@SOURCETYPE,11,0,60,1,100,1,50000,50000,50000,50000,45,0,1,0,0,0,0,11,48081,50,0,0.0,0.0,0.0,0.0,"Update - 50 secs (Set Data 1 to Arnauld)");

-- Warden Stillwater
SET @ENTRY := 47834;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,89461,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Plague"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,11,89450,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Smash"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,5000,5000,5000,11,89461,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Plague"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,48083,50,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 2 to Guards"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,49,0,2,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Nearest Player"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,48081,50,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 2 to Arnauld");

-- Sludge Guard
SET @ENTRY := 48083;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Faction Hostile"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,2,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Die");

-- Flesh-Shaper Arnauld
SET @ENTRY := 48081;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Hostile"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Die");

UPDATE `creature_template` SET `questItem1`=63330, `lootid`=47834 WHERE `entry`=47834;

DELETE FROM `creature_loot_template` WHERE `entry` = '47834';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(47834, 63330, -100);

UPDATE `creature_template` SET `flags_extra`=130 WHERE `entry`=4;
DELETE FROM `creature_involvedrelation` WHERE `id`=47900 AND `quest`=28251;
DELETE FROM `creature_involvedrelation` WHERE `id`=48020 AND `quest`=28251;

DELETE FROM `world_quest_phases` WHERE `QuestId` = '28251';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `Comment`) VALUES
(28251, 1, 1, 'Quest ID: 28251 - Trouble at Soutshore (ON QUEST_ ACCEPT)');

UPDATE `quest_template` SET `RewardSpellCast`=88763 WHERE `Id`=28251;
UPDATE `quest_template` SET `NextQuestIdChain`=0 WHERE `Id`=28196;
UPDATE `creature_template` SET `ScriptName`='npc_blight_slime' WHERE `entry`=48136;
UPDATE `quest_template` SET `SourceSpellId`=88375 WHERE `Id`=28324;

DELETE FROM `spell_script_names` WHERE `spell_id` = '89752';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89752, 'spell_collect_specimen');

UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `id`=48136;
UPDATE `quest_template` SET `RewardSpellCast`=88763 WHERE `Id`=28324;
UPDATE `creature_template` SET `mindmg`=27, `maxdmg`=40, `attackpower`=10, `lootid`=48319, `pickpocketloot`=48319 WHERE `entry`=48319;

-- Angry Blight Slime
SET @ENTRY := 48319;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,9459,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Cast Corrosive Ooze"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,7,28329,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Quest"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,15000,15000,15000,15000,11,9459,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Corrosive Ooze");

DELETE FROM `creature_loot_template` WHERE `entry` = '48319';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48319, 789, 0.4677, 1, 0, 1, 1),
(48319, 790, 0.05, 1, 0, 1, 1),
(48319, 804, 0.05, 1, 0, 1, 1),
(48319, 857, 0.05, 1, 0, 1, 1),
(48319, 890, 0.0026, 1, 0, 1, 1),
(48319, 935, 0.0026, 1, 0, 1, 1),
(48319, 1121, 0.0051, 1, 0, 1, 1),
(48319, 1206, 0.234, 1, 0, 1, 1),
(48319, 1746, 0.1, 1, 0, 1, 1),
(48319, 1747, 0.1, 1, 0, 1, 1),
(48319, 1748, 0.1, 1, 0, 1, 1),
(48319, 1749, 0.1, 1, 0, 1, 1),
(48319, 1750, 0.1337, 1, 0, 1, 1),
(48319, 1751, 0.1, 1, 0, 1, 1),
(48319, 1752, 0.1, 1, 0, 1, 1),
(48319, 1753, 0.1, 1, 0, 1, 1),
(48319, 1772, 0.1, 1, 0, 1, 1),
(48319, 1774, 0.1, 1, 0, 1, 1),
(48319, 1775, 0.2, 1, 0, 1, 1),
(48319, 1776, 0.1, 1, 0, 1, 1),
(48319, 1777, 0.2108, 1, 0, 1, 1),
(48319, 1778, 0.2, 1, 0, 1, 1),
(48319, 1795, 0.1, 1, 0, 1, 1),
(48319, 1796, 0.1, 1, 0, 1, 1),
(48319, 1797, 0.1, 1, 0, 1, 1),
(48319, 1798, 1.7304, 1, 0, 1, 1),
(48319, 1799, 0.1826, 1, 0, 1, 1),
(48319, 1800, 0.1, 1, 0, 1, 1),
(48319, 1801, 1.5434, 1, 0, 1, 1),
(48319, 1802, 0.1774, 1, 0, 1, 1),
(48319, 1818, 0.1, 1, 0, 1, 1),
(48319, 1819, 0.3, 1, 0, 1, 1),
(48319, 1820, 0.324, 1, 0, 1, 1),
(48319, 1821, 0.2, 1, 0, 1, 1),
(48319, 1822, 0.2, 1, 0, 1, 1),
(48319, 1823, 0.3, 1, 0, 1, 1),
(48319, 1824, 0.2, 1, 0, 1, 1),
(48319, 2194, 0.0026, 1, 0, 1, 1),
(48319, 2219, 0.1, 1, 0, 1, 1),
(48319, 2220, 0.1, 1, 0, 1, 1),
(48319, 2236, 0.0103, 1, 0, 1, 1),
(48319, 2601, 0.0094, 1, 0, 1, 1),
(48319, 2765, 0.1, 1, 0, 1, 1),
(48319, 2782, 0.2, 1, 0, 1, 1),
(48319, 2783, 0.2, 1, 0, 1, 1),
(48319, 2881, 0.2338, 1, 0, 1, 1),
(48319, 2882, 0.0047, 1, 0, 1, 1),
(48319, 2981, 0.0154, 1, 0, 1, 1),
(48319, 2982, 0.0077, 1, 0, 1, 1),
(48319, 2985, 0.0386, 1, 0, 1, 1),
(48319, 2986, 0.0231, 1, 0, 1, 1),
(48319, 2989, 0.0206, 1, 0, 1, 1),
(48319, 2990, 0.0283, 1, 0, 1, 1),
(48319, 2991, 0.0206, 1, 0, 1, 1),
(48319, 2992, 0.018, 1, 0, 1, 1),
(48319, 3039, 0.05, 1, 0, 1, 1),
(48319, 3057, 0.0129, 1, 0, 1, 1),
(48319, 3058, 0.018, 1, 0, 1, 1),
(48319, 3065, 0.036, 1, 0, 1, 1),
(48319, 3066, 0.0103, 1, 0, 1, 1),
(48319, 3184, 0.05, 1, 0, 1, 1),
(48319, 3193, 0.0489, 1, 0, 1, 1),
(48319, 3198, 0.05, 1, 0, 1, 1),
(48319, 3199, 0.05, 1, 0, 1, 1),
(48319, 3202, 0.0051, 1, 0, 1, 1),
(48319, 3378, 0.2, 1, 0, 1, 1),
(48319, 3379, 0.1, 1, 0, 1, 1),
(48319, 3396, 0.0154, 1, 0, 1, 1),
(48319, 3608, 0.0047, 1, 0, 1, 1),
(48319, 3647, 0.018, 1, 0, 1, 1),
(48319, 3655, 0.0051, 1, 0, 1, 1),
(48319, 3673, 72.9912, 1, 0, 1, 1),
(48319, 3674, 26.9754, 1, 0, 1, 1),
(48319, 3740, 0.05, 1, 0, 1, 1),
(48319, 4292, 0.05, 1, 0, 1, 1),
(48319, 4345, 0.05, 1, 0, 1, 1),
(48319, 4348, 0.0468, 1, 0, 1, 1),
(48319, 4349, 0.0047, 1, 0, 1, 1),
(48319, 4409, 0.05, 1, 0, 1, 1),
(48319, 4568, 0.054, 1, 0, 1, 1),
(48319, 4576, 0.0514, 1, 0, 1, 1),
(48319, 4694, 0.0437, 1, 0, 1, 1),
(48319, 4697, 0.0077, 1, 0, 1, 1),
(48319, 4698, 0.0411, 1, 0, 1, 1),
(48319, 4700, 0.036, 1, 0, 1, 1),
(48319, 4706, 0.0129, 1, 0, 1, 1),
(48319, 4708, 0.0077, 1, 0, 1, 1),
(48319, 4709, 0.0103, 1, 0, 1, 1),
(48319, 4710, 0.018, 1, 0, 1, 1),
(48319, 5207, 0.05, 1, 0, 1, 1),
(48319, 5575, 0.05, 1, 0, 1, 1),
(48319, 5576, 0.0231, 1, 0, 1, 1),
(48319, 5972, 0.0077, 1, 0, 1, 1),
(48319, 6381, 0.0077, 1, 0, 1, 1),
(48319, 6383, 0.0129, 1, 0, 1, 1),
(48319, 6390, 0.0206, 1, 0, 1, 1),
(48319, 6391, 0.0077, 1, 0, 1, 1),
(48319, 6454, 0.0051, 1, 0, 1, 1),
(48319, 6561, 0.0129, 1, 0, 1, 1),
(48319, 6562, 0.054, 1, 0, 1, 1),
(48319, 6563, 0.0103, 1, 0, 1, 1),
(48319, 6564, 0.0437, 1, 0, 1, 1),
(48319, 6565, 0.0386, 1, 0, 1, 1),
(48319, 6566, 0.0468, 1, 0, 1, 1),
(48319, 6568, 0.0935, 1, 0, 1, 1),
(48319, 6570, 0.0309, 1, 0, 1, 1),
(48319, 6572, 0.0129, 1, 0, 1, 1),
(48319, 6573, 0.018, 1, 0, 1, 1),
(48319, 6574, 0.0257, 1, 0, 1, 1),
(48319, 6576, 0.0206, 1, 0, 1, 1),
(48319, 6577, 0.0051, 1, 0, 1, 1),
(48319, 6578, 0.0051, 1, 0, 1, 1),
(48319, 6579, 0.0077, 1, 0, 1, 1),
(48319, 6580, 0.0103, 1, 0, 1, 1),
(48319, 6581, 0.0334, 1, 0, 1, 1),
(48319, 6582, 0.036, 1, 0, 1, 1),
(48319, 6583, 0.0231, 1, 0, 1, 1),
(48319, 6584, 0.0047, 1, 0, 1, 1),
(48319, 6585, 0.0103, 1, 0, 1, 1),
(48319, 6586, 0.0129, 1, 0, 1, 1),
(48319, 6587, 0.0935, 1, 0, 1, 1),
(48319, 6588, 0.0206, 1, 0, 1, 1),
(48319, 7554, 0.0154, 1, 0, 1, 1),
(48319, 7608, 0.0051, 1, 0, 1, 1),
(48319, 8491, 0.0103, 1, 0, 1, 1),
(48319, 9776, 0.0206, 1, 0, 1, 1),
(48319, 9778, 0.0103, 1, 0, 1, 1),
(48319, 9780, 0.0206, 1, 0, 1, 1),
(48319, 9781, 0.0514, 1, 0, 1, 1),
(48319, 9782, 0.0026, 1, 0, 1, 1),
(48319, 9783, 0.0468, 1, 0, 1, 1),
(48319, 9790, 0.0077, 1, 0, 1, 1),
(48319, 9792, 0.0468, 1, 0, 1, 1),
(48319, 9794, 0.0094, 1, 0, 1, 1),
(48319, 9801, 0.2338, 1, 0, 1, 1),
(48319, 9805, 0.0334, 1, 0, 1, 1),
(48319, 9810, 0.0468, 1, 0, 1, 1),
(48319, 9811, 0.0257, 1, 0, 1, 1),
(48319, 9812, 0.0154, 1, 0, 1, 1),
(48319, 9815, 0.0468, 1, 0, 1, 1),
(48319, 10405, 0.0129, 1, 0, 1, 1),
(48319, 10407, 0.0386, 1, 0, 1, 1),
(48319, 11038, 0.0468, 1, 0, 1, 1),
(48319, 11081, 0.0047, 1, 0, 1, 1),
(48319, 11098, 0.0047, 1, 0, 1, 1),
(48319, 11965, 0.0051, 1, 0, 1, 1),
(48319, 11967, 0.0103, 1, 0, 1, 1),
(48319, 11981, 0.0026, 1, 0, 1, 1),
(48319, 11982, 0.0094, 1, 0, 1, 1),
(48319, 11993, 0.0129, 1, 0, 1, 1),
(48319, 11994, 0.0047, 1, 0, 1, 1),
(48319, 12006, 0.0154, 1, 0, 1, 1),
(48319, 12052, 0.0283, 1, 0, 1, 1),
(48319, 12053, 0.0077, 1, 0, 1, 1),
(48319, 12977, 0.0026, 1, 0, 1, 1),
(48319, 12979, 0.0129, 1, 0, 1, 1),
(48319, 12982, 0.0077, 1, 0, 1, 1),
(48319, 12983, 0.0051, 1, 0, 1, 1),
(48319, 12984, 0.0026, 1, 0, 1, 1),
(48319, 12987, 0.0051, 1, 0, 1, 1),
(48319, 12988, 0.0103, 1, 0, 1, 1),
(48319, 12990, 0.0026, 1, 0, 1, 1),
(48319, 12998, 0.0026, 1, 0, 1, 1),
(48319, 14168, 0.018, 1, 0, 1, 1),
(48319, 14170, 0.0334, 1, 0, 1, 1),
(48319, 14171, 0.0257, 1, 0, 1, 1),
(48319, 14172, 0.0103, 1, 0, 1, 1),
(48319, 14173, 0.0129, 1, 0, 1, 1),
(48319, 14175, 0.0026, 1, 0, 1, 1),
(48319, 15211, 0.0694, 1, 0, 1, 1),
(48319, 15223, 0.05, 1, 0, 1, 1),
(48319, 15230, 0.05, 1, 0, 1, 1),
(48319, 15248, 0.1, 1, 0, 1, 1),
(48319, 15269, 0.3741, 1, 0, 1, 1),
(48319, 15912, 0.0051, 1, 0, 1, 1),
(48319, 20768, 0.0874, 1, 0, 1, 1);

DELETE FROM `pickpocketing_loot_template` WHERE `entry` = '48319';
INSERT INTO `pickpocketing_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48319, 3673, 31.9149, 1, 0, 1, 1),
(48319, 3674, 17.0213, 1, 0, 1, 1),
(48319, 62772, 48.9362, 1, 0, 1, 1),
(48319, 68771, 2.1277, 1, 0, 1, 1);

UPDATE `quest_template` SET `Flags`=1638400 WHERE `Id`=28329;
UPDATE `creature_template` SET `mindmg`=27, `maxdmg`=40, `attackpower`=10, `dmg_multiplier`=3.5 WHERE `entry`=48322;

-- Chet the Slime-Breeder
SET @ENTRY := 48322;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,5000,5000,11,31281,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bloodbolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,15000,15000,11,9459,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Corrosive Ooze"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,9459,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corrosive Ooze");

DELETE FROM `creature_loot_template` WHERE `entry` = '48322'; 
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48322, 789, 0.2056, 1, 0, 1, 1),
(48322, 790, 0.0685, 1, 0, 1, 1),
(48322, 804, 0.0571, 1, 0, 1, 1),
(48322, 857, 0.0228, 1, 0, 1, 1),
(48322, 1206, 0.7207, 1, 0, 1, 1),
(48322, 1705, 0.6206, 1, 0, 1, 1),
(48322, 1746, 0.2627, 1, 0, 1, 1),
(48322, 1747, 0.297, 1, 0, 1, 1),
(48322, 1748, 0.3198, 1, 0, 1, 1),
(48322, 1749, 0.4569, 1, 0, 1, 1),
(48322, 1750, 0.2056, 1, 0, 1, 1),
(48322, 1751, 0.2284, 1, 0, 1, 1),
(48322, 1752, 0.2284, 1, 0, 1, 1),
(48322, 1753, 0.3084, 1, 0, 1, 1),
(48322, 1772, 0.4226, 1, 0, 1, 1),
(48322, 1774, 0.8681, 1, 0, 1, 1),
(48322, 1775, 0.5368, 1, 0, 1, 1),
(48322, 1776, 0.5597, 1, 0, 1, 1),
(48322, 1777, 0.434, 1, 0, 1, 1),
(48322, 1778, 0.4911, 1, 0, 1, 1),
(48322, 1795, 0.4455, 1, 0, 1, 1),
(48322, 1796, 0.434, 1, 0, 1, 1),
(48322, 1797, 0.4455, 1, 0, 1, 1),
(48322, 1798, 0.3084, 1, 0, 1, 1),
(48322, 1799, 0.3312, 1, 0, 1, 1),
(48322, 1800, 0.731, 1, 0, 1, 1),
(48322, 1801, 0.434, 1, 0, 1, 1),
(48322, 1802, 0.2284, 1, 0, 1, 1),
(48322, 1818, 0.6282, 1, 0, 1, 1),
(48322, 1819, 0.7539, 1, 0, 1, 1),
(48322, 1820, 0.5825, 1, 0, 1, 1),
(48322, 1821, 0.8338, 1, 0, 1, 1),
(48322, 1822, 0.6054, 1, 0, 1, 1),
(48322, 1823, 0.3998, 1, 0, 1, 1),
(48322, 1824, 0.7881, 1, 0, 1, 1),
(48322, 2059, 0.0228, 1, 0, 1, 1),
(48322, 2194, 0.0114, 1, 0, 1, 1),
(48322, 2219, 0.4797, 1, 0, 1, 1),
(48322, 2220, 0.434, 1, 0, 1, 1),
(48322, 2236, 0.0228, 1, 0, 1, 1),
(48322, 2765, 0.811, 1, 0, 1, 1),
(48322, 2782, 0.6511, 1, 0, 1, 1),
(48322, 2783, 0.6054, 1, 0, 1, 1),
(48322, 2881, 0.2002, 1, 0, 1, 1),
(48322, 2882, 0.0343, 1, 0, 1, 1),
(48322, 2981, 0.0343, 1, 0, 1, 1),
(48322, 2985, 0.0343, 1, 0, 1, 1),
(48322, 2989, 0.1142, 1, 0, 1, 1),
(48322, 2990, 0.0457, 1, 0, 1, 1),
(48322, 2991, 0.0343, 1, 0, 1, 1),
(48322, 3039, 0.0343, 1, 0, 1, 1),
(48322, 3057, 0.0114, 1, 0, 1, 1),
(48322, 3058, 0.0114, 1, 0, 1, 1),
(48322, 3065, 0.1028, 1, 0, 1, 1),
(48322, 3066, 0.0457, 1, 0, 1, 1),
(48322, 3193, 0.1142, 1, 0, 1, 1),
(48322, 3198, 0.0914, 1, 0, 1, 1),
(48322, 3199, 0.1485, 1, 0, 1, 1),
(48322, 3202, 0.0228, 1, 0, 1, 1),
(48322, 3378, 0.3541, 1, 0, 1, 1),
(48322, 3379, 0.4797, 1, 0, 1, 1),
(48322, 3393, 0.0228, 1, 0, 1, 1),
(48322, 3394, 0.0457, 1, 0, 1, 1),
(48322, 3608, 0.0114, 1, 0, 1, 1),
(48322, 3611, 0.0114, 1, 0, 1, 1),
(48322, 3612, 0.0114, 1, 0, 1, 1),
(48322, 3647, 0.0114, 1, 0, 1, 1),
(48322, 3655, 0.0114, 1, 0, 1, 1),
(48322, 3673, 71.3307, 1, 0, 1, 1),
(48322, 3674, 28.3609, 1, 0, 1, 1),
(48322, 4293, 0.0228, 1, 0, 1, 1),
(48322, 4348, 0.0228, 1, 0, 1, 1),
(48322, 4350, 0.0114, 1, 0, 1, 1),
(48322, 4410, 0.0114, 1, 0, 1, 1),
(48322, 4568, 0.1942, 1, 0, 1, 1),
(48322, 4576, 0.0914, 1, 0, 1, 1),
(48322, 4694, 0.1942, 1, 0, 1, 1),
(48322, 4698, 0.0685, 1, 0, 1, 1),
(48322, 4700, 0.0343, 1, 0, 1, 1),
(48322, 4708, 0.0228, 1, 0, 1, 1),
(48322, 4710, 0.1256, 1, 0, 1, 1),
(48322, 5543, 0.0114, 1, 0, 1, 1),
(48322, 5578, 0.0228, 1, 0, 1, 1),
(48322, 5972, 0.0343, 1, 0, 1, 1),
(48322, 6375, 0.0228, 1, 0, 1, 1),
(48322, 6381, 0.08, 1, 0, 1, 1),
(48322, 6382, 0.0114, 1, 0, 1, 1),
(48322, 6383, 0.0228, 1, 0, 1, 1),
(48322, 6391, 0.0343, 1, 0, 1, 1),
(48322, 6454, 0.0228, 1, 0, 1, 1),
(48322, 6561, 0.0228, 1, 0, 1, 1),
(48322, 6562, 0.0571, 1, 0, 1, 1),
(48322, 6564, 0.1828, 1, 0, 1, 1),
(48322, 6565, 0.1028, 1, 0, 1, 1),
(48322, 6566, 0.0343, 1, 0, 1, 1),
(48322, 6567, 0.0228, 1, 0, 1, 1),
(48322, 6568, 0.0343, 1, 0, 1, 1),
(48322, 6569, 0.0114, 1, 0, 1, 1),
(48322, 6570, 0.2284, 1, 0, 1, 1),
(48322, 6572, 0.0343, 1, 0, 1, 1),
(48322, 6573, 0.0571, 1, 0, 1, 1),
(48322, 6574, 0.1713, 1, 0, 1, 1),
(48322, 6576, 0.1142, 1, 0, 1, 1),
(48322, 6577, 0.1256, 1, 0, 1, 1),
(48322, 6578, 0.0685, 1, 0, 1, 1),
(48322, 6579, 0.0228, 1, 0, 1, 1),
(48322, 6580, 0.1142, 1, 0, 1, 1),
(48322, 6581, 0.0343, 1, 0, 1, 1),
(48322, 6582, 0.1828, 1, 0, 1, 1),
(48322, 6583, 0.0457, 1, 0, 1, 1),
(48322, 6584, 0.0228, 1, 0, 1, 1),
(48322, 6586, 0.0457, 1, 0, 1, 1),
(48322, 6587, 0.0114, 1, 0, 1, 1),
(48322, 6588, 0.0343, 1, 0, 1, 1),
(48322, 9778, 0.0114, 1, 0, 1, 1),
(48322, 9781, 0.1371, 1, 0, 1, 1),
(48322, 9782, 0.0228, 1, 0, 1, 1),
(48322, 9790, 0.0228, 1, 0, 1, 1),
(48322, 9792, 0.0343, 1, 0, 1, 1),
(48322, 9793, 0.0228, 1, 0, 1, 1),
(48322, 9794, 0.08, 1, 0, 1, 1),
(48322, 9804, 0.0114, 1, 0, 1, 1),
(48322, 9805, 0.0343, 1, 0, 1, 1),
(48322, 9810, 0.0228, 1, 0, 1, 1),
(48322, 9811, 0.0457, 1, 0, 1, 1),
(48322, 9812, 0.0914, 1, 0, 1, 1),
(48322, 9813, 0.0685, 1, 0, 1, 1),
(48322, 9814, 0.0457, 1, 0, 1, 1),
(48322, 9818, 0.0343, 1, 0, 1, 1),
(48322, 10316, 0.0228, 1, 0, 1, 1),
(48322, 10405, 0.1599, 1, 0, 1, 1),
(48322, 10407, 0.1142, 1, 0, 1, 1),
(48322, 11081, 0.0228, 1, 0, 1, 1),
(48322, 11982, 0.0114, 1, 0, 1, 1),
(48322, 11994, 0.0228, 1, 0, 1, 1),
(48322, 12006, 0.0343, 1, 0, 1, 1),
(48322, 12052, 0.0571, 1, 0, 1, 1),
(48322, 12053, 0.0457, 1, 0, 1, 1),
(48322, 12054, 0.0228, 1, 0, 1, 1),
(48322, 12977, 0.0228, 1, 0, 1, 1),
(48322, 12983, 0.0228, 1, 0, 1, 1),
(48322, 12988, 0.0685, 1, 0, 1, 1),
(48322, 12989, 0.0114, 1, 0, 1, 1),
(48322, 14170, 0.1828, 1, 0, 1, 1),
(48322, 14171, 0.1371, 1, 0, 1, 1),
(48322, 14172, 0.0114, 1, 0, 1, 1),
(48322, 14175, 0.0114, 1, 0, 1, 1),
(48322, 15211, 0.1485, 1, 0, 1, 1),
(48322, 15230, 0.1028, 1, 0, 1, 1),
(48322, 15269, 0.0343, 1, 0, 1, 1),
(48322, 15912, 0.0457, 1, 0, 1, 1),
(48322, 15927, 0.0114, 1, 0, 1, 1),
(48322, 20768, 0.0571, 1, 0, 1, 1);

DELETE FROM `spell_area` WHERE `spell` = '89277';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(89277, 271, 28344, 28344, 1, 10, 10);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (773711, 773712, 773283, 773284);
UPDATE `quest_template` SET `SpecialFlags`=2, `Flags`=0 WHERE `Id`=28345;
UPDATE `creature_template` SET `InhabitType`=4, `speed_walk`=2.666668, `speed_run`=2.38571 WHERE `entry`=48217;

DELETE FROM `spell_linked_spell` WHERE `spell_effect` = '-89277';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(89957, -89277, 'Detect Auras 3 -> Remove 2');

DELETE FROM `spell_area` WHERE `quest_start` IN (28345, 28344);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(89957, 271, 28345, 28345, 0, 0, 2, 1, 66, 66),
(89277, 271, 28345, 28345, -89957, 0, 2, 1, 11, 11),
(89277, 271, 28344, 28344, -89957, 0, 2, 1, 75, 75);

DELETE FROM `creature_addon` WHERE `guid`=773712;

DELETE FROM `conditions` WHERE `SourceGroup`=12430;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12430, 0, 0, 0, 9, 0, 28345, 0, 0, 0, 0, 0, '', 'Orkus- Show gossip only if quest 28345 is active');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12430';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12430, 'Your feet are touching the ground, Orkus. This is shallow water. Just stand up and walk to shore.', 1, 1);

UPDATE `quest_template` SET `PrevQuestId`=28354 WHERE  `Id`=28375;

DELETE FROM `spell_target_position` WHERE `id` IN (89985, 89986, 89984, 89983);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89985, -932.11, -584.06, 2.50, 0.80),
(89983, -928.59, -582.60, 1.55, 3.36);

-- Kingslayer Orkus
SET @ENTRY := 48218;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,28345,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12430,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12430,0,0,0,28,89662,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Drowning Aura"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,12430,0,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,48218,0,0,69,0,0,0,0,0,0,8,0,0,0,-928.59,-582.6,1.55,3.36,"After Talk 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,34,0,100,0,8,0,0,0,1,2,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,48218,0,0,45,0,1,0,0,0,0,10,773712,48217,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Kasha"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,1,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,48218,0,0,15,28345,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Quest Complete"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,3,48218,0,0,70,0,0,0,0,0,0,10,773712,48217,0,0.0,0.0,0.0,0.0,"After Talk 3 - Respawn Kasha"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,3,48218,0,0,70,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Respawn Self");

-- Kasha
SET @ENTRY := 48217;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,69,0,0,0,0,0,0,8,0,0,0,-932.11,-584.06,2.5,0.8,"On Get Data 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Die"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,773711,48218,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Orkus");

DELETE FROM `creature_text` WHERE `entry` IN (48397, 48395);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48397,0,0,'Ugh, the lok\'tar must have been cooking up a turd - which would explain the smell.',12,0,100,0,0,0,'Comment'),
(48397,1,0,'By Hellscream\'s axe!',12,0,100,0,0,0,'Comment'),
(48397,2,0,'You face Kingslayer Orkus now, dwarf!',12,0,100,0,0,0,'Comment'),
(48397,3,0,'KASHA! Your master needs you! ',14,0,100,0,0,0,'Comment'),
(48395,0,0,'|cffffffffI had just finished making use of the facilities on the docks when...',41,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `speed_walk`=1.80286, `speed_run`=1.80286, `VehicleId`=686, `InhabitType`=7 WHERE `entry`=48395;

DELETE FROM `spell_target_position` WHERE `id` IN (89971, 89983, 89984, 89986, 89985);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89971, -881.83, -562.42, 15.85, 5.22),
(89983, -875.20, -573.62, 11.47, 2.09),
(89986, -899.90, -557.96, 6.87, 2.09),
(89984, -902.64, -558.36, 6.87, 1.52),
(89985, -885.74, -604.18, 10.47, 1.96);

DELETE FROM `waypoints` WHERE `entry` = '48395';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(48395, 1, -882, -566.19, 14.97, 'Orkus Camera WP'),
(48395, 2, -884.14, -569.30, 13.55, 'Orkus Camera WP'),
(48395, 3, -901.48, -538.19, 9.77, 'Orkus Camera WP'),
(48395, 4, -906.39, -534.96, 8.69, 'Orkus Camera WP'),
(48395, 5, -906.09, -540.90, 9.04, 'Orkus Camera WP');

DELETE FROM `creature_text` WHERE `entry` IN (48407, 48403);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48407,0,0,'They are massing at Purgation Isle, just west of us here, off the coast. We are to meet them there, general.',12,0,100,0,0,0,'Comment'),
(48407,1,0,'As for the smell... *Balinda sniffs the air* I think it\'s coming from over there...',12,0,100,0,0,0,'Comment'),
(48407,2,0,'Aye, general!',12,0,100,0,0,0,'Comment'),
(48403,0,0,'Oy, \'Linda, where are we meetin\' up this Ivar Bloodfang fella? An\' what in Bronzebeard\'s name is that terrible smell?',12,0,100,0,0,0,'Comment'),
(48403,1,0,'Look there, \'Linda! What in the...',12,0,100,0,0,0,'Comment'),
(48403,2,0,'ENOUGH TOYIN\' AROUND!!!',14,0,100,0,0,0,'Comment'),
(48403,3,0,'Let\'s get outta here, \'Linda. We dun wanna draw any unwanted attention!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `exp`=2, `faction_A`=85, `faction_H`=85 WHERE `entry` IN (48397, 48396);
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `exp`=2, `faction_A`=11, `faction_H`=11 WHERE `entry` IN (48407, 48403);

UPDATE `creature_template` SET `speed_walk`=2.40286, `speed_run`=2.40286, `InhabitType`=7 WHERE `entry`=48396;

-- Orkus Camera
SET @ENTRY := 48395;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,5000,5000,0,0,1,0,3000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Update (5 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,1,3500,3500,0,0,85,89983,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update (3.5 secs) - Summon Orkus"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,1,20000,20000,0,0,53,0,48395,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (20 secs) - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,2,0,0,0,85,89986,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Summon Balinda"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,2,0,0,0,85,89984,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Summon Vanndar"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,2,0,0,0,54,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause"),
(@ENTRY,@SOURCETYPE,7,0,60,0,100,1,65000,65000,0,0,85,89985,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update (65 secs) - Summon Kasha"),
(@ENTRY,@SOURCETYPE,8,0,60,0,100,1,96000,96000,0,0,28,89970,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (96 secs) - Remove Passenger");

-- Kasha
SET @ENTRY := 48396;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-897.34,-570.41,6.87,1.78,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,49,0,0,0,0,0,0,11,48407,50,0,0.0,0.0,0.0,0.0,"On Movement Inform - Attack Balinda"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive");

-- Kingslayer Orkus
SET @ENTRY := 48397;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,6000,6000,6000,6000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (6 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,1,0,48397,0,0,1,1,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,1,1,48397,0,0,69,0,0,0,0,0,0,8,0,0,0,-890.03,-572.52,7.52,2.15,"After Talk 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,4,0,60,0,100,1,55000,55000,55000,55000,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (55 secs) - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,1,2,48397,0,0,49,0,0,0,0,0,0,11,48403,100,0,0.0,0.0,0.0,0.0,"After Talk 2 - Attack Vanndar"),
(@ENTRY,@SOURCETYPE,6,0,4,0,100,1,0,0,0,0,11,90272,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Heroic Leap"),
(@ENTRY,@SOURCETYPE,7,0,54,0,100,1,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,8,0,60,0,100,1,63000,63000,0,0,1,3,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (63 secs) - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,60,0,100,1,90000,90000,0,0,97,0,0,0,0,0,0,8,0,0,0,-931.75,-560.49,-1.52,0.17,"Update (90 secs) - Jump in Water"),
(@ENTRY,@SOURCETYPE,10,0,60,0,100,1,90000,90000,0,0,11,105528,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (90 secs) - Jump in Water"),
(@ENTRY,@SOURCETYPE,11,0,60,0,100,1,90000,90000,0,0,45,0,2,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"Update (90 secs) - Set Data 2 to Creatures"),
(@ENTRY,@SOURCETYPE,12,0,60,0,100,1,90000,90000,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (90 secs) - Force Despawn");

-- Captain Balinda Stonehearth
SET @ENTRY := 48407;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,21000,21000,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (21 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,1,0,48407,0,0,1,1,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,1,1,48407,0,0,69,0,0,0,0,0,0,8,0,0,0,-900.1,-559.4,6.87,5.36,"After Talk 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3500,3500,3500,30000,11,46987,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,15000,15000,15000,15000,11,90053,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Arcane Explosion"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,2,0,0,1,2,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,2,48407,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Force Despawn");

-- Vanndar Stormpike
SET @ENTRY := 48403;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,15000,15000,0,0,1,0,16000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (15 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,1,0,48403,0,0,1,1,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,1,1,48403,0,0,69,0,0,0,0,0,0,8,0,0,0,-901.92,-560.26,6.87,5.36,"After Talk 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,49,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Attack Start"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,2,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,48403,0,0,1,3,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,48403,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Force Despawn");

-- Mudsnout Gnoll
SET @ENTRY := 2372;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,5,30000,30000,11,3650,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Mudsnout Gnoll - At 0 - 5 Range - Cast Sling Mud"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,7,28355,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Quest");

DELETE FROM `creature_involvedrelation` WHERE `quest` = '28355';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(48218, 28355);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28355;
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `speed_walk`=3, `speed_run`=3, `VehicleId`=1329, `InhabitType`=7 WHERE `entry`=48467;
UPDATE `quest_template` SET `SourceSpellId`=90123 WHERE `Id`=28375;

DELETE FROM `waypoints` WHERE `entry` = '48467';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(48467, 1, -1029.71, -470.79, 62.90, 'Kasha WP'),
(48467, 2, -1245.80, 102.32, 38.52, 'Kasha WP'),
(48467, 3, -1235.88, 376.30, 16.62, 'Kasha WP'),
(48467, 4, -1235.61, 424.27, 2.50, 'Kasha WP');

DELETE FROM `creature_text` WHERE `entry` IN (48467, 48468);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48467,0,0,'|cffffffffYou, Orkus and Kasha flew off to Purgation Isle',41,0,100,0,0,0,'Comment'),
(48468,0,0,'TO PURGATION ISLE! KASHA! RIDE LIKE THUNDER!',14,0,100,0,0,0,'Comment');

-- Kingslayer Orkus
SET @ENTRY := 48468;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Kasha"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,48503,0,0,45,0,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Kasha");

-- Kasha
SET @ENTRY := 48467;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,1000,1000,1000,1000,12,48468,8,0,0,0,0,8,0,0,0,-923.48,-579.02,1.08,3.38,"Update (1 sec) - Summon Orkus"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,5000,5000,5000,5000,53,1,48467,0,28375,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (5.0 secs) - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,1,3500,3500,3500,3500,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3.5 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,4,0,0,0,28,90122,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Remove Passenger");

-- Kingslayer Orkus
SET @ENTRY := 48470;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,82061,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Commanding Shout"),
(@ENTRY,@SOURCETYPE,2,0,0,0,33,0,5500,9500,5500,9500,11,9080,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hamstring"),
(@ENTRY,@SOURCETYPE,3,0,0,0,33,0,5500,9500,5500,9500,11,57846,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,4,0,0,0,33,0,5500,9500,5500,9500,11,32736,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mortal Strike");

DELETE FROM `spell_area` WHERE `spell` = '90132';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(90132, 896, 28375, 28400, 1, 66, 64);

UPDATE `creature_template` SET `mindmg`=24, `maxdmg`=35, `dmg_multiplier`=1.2 WHERE `entry` IN (48484, 48482, 48483, 48470);

-- Bloodfang Sentry
SET @ENTRY := 48484;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,11,86237,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Stalking"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,2000,2000,11,79881,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Slam"),
(@ENTRY,@SOURCETYPE,2,0,0,0,20,0,12500,12500,12500,12500,11,79881,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Enrage");

-- Stormpike Mountaineer
SET @ENTRY := 48482;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,2000,2000,11,15547,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,1,0,0,0,35,0,2000,2000,2000,2000,11,15495,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosive Shot");

-- Stormpike Ram Rider
SET @ENTRY := 48483;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,50,0,3500,3500,3500,3500,11,15284,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,1,0,0,0,50,0,3500,3500,3500,3500,11,15284,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mortal Strike");

UPDATE `creature_template` SET `mindmg`=24, `maxdmg`=35, `dmg_multiplier`=1.2, `baseattacktime`=2000, `minlevel`=80, `maxlevel`=80, `lootid`=48515, `questItem1`=64307 WHERE `entry`=48503;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '90205';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(90205, -90132, 'Summon Orkus -> Remove Old Orkus Aura');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6512';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6512, 'at_purgation_isle');

UPDATE `creature_template` SET `unit_flags`=256, `IconName`='Pickup', `type_flags`=128, `minlevel`=23, `maxlevel`=23, `faction_A`=1216, `faction_H`=1216, `mindmg`=24, `maxdmg`=49, `baseattacktime`=2000 WHERE `entry`=48515;
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `unit_flags`=256, `faction_A`=1216, `faction_H`=1216 WHERE `entry` IN (48507, 48485, 48508);

DELETE FROM `spell_target_position` WHERE `id` IN (90209, 90210, 90211, 90206, 90278, 90407);
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(90209, -1342.64, 574.29, 103.52, 3.74),
(90210, -1346.55, 574.69, 103.52, 5.35),
(90211, -1346.56, 571.15, 103.52, 1.40),
(90206, -1317.71, 528.60, 99.51, 6.27),
(90278, -1288.77, 591.94, 117.73, 3.98),
(90407, -36.19, -937.79, 54.27, 4.31);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '56002';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56002, 'I\'m ready, Orkus. let\'s do this!', 1, 1);

DELETE FROM `gossip_menu` WHERE `entry` = '56002';
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(56002, 48503);

DELETE FROM `npc_text` WHERE `ID` = '48503';
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES
(48503, 'Are you ready? You will have to act quickly, $N. I do not know how long I can hold them all off for! Get the plans and get out!');

DELETE FROM `creature_loot_template` WHERE `entry` = '48515';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(48515, 64307, -100);

UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `speed_walk`=2.40, `speed_run`=2.40286, `VehicleId`=463, `InhabitType`=4 WHERE `entry`=48504;

DELETE FROM `creature_template_addon` WHERE `entry` = '48504';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(48504, '83412');

DELETE FROM `waypoints` WHERE `entry` IN (48504, 48503);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(48504, 1, -1353.00, 534.51, 117.58, 'Kasha (Final WP)'),
(48504, 2, -1351.72, 510.04, 114.94, 'Kasha (Final WP)'),
(48504, 3, -1317.43, 531.37, 113.39, 'Kasha (Final WP)'),
(48504, 4, -1328.83, 552.90, 107.85, 'Kasha (Final WP)'),
(48504, 5, -239.20, -920.18, 141.87, 'Kasha (Final WP)'),
(48504, 6, -39.20, -941.59, 54.27, 'Kasha (Final WP)'),
(48503, 1, -1341.66, 568.98, 103.52, 'Orkus (Final WP)');

DELETE FROM `creature_template_addon` WHERE `entry` IN (48503, 48515, 48504, 48557);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(48503, '90205'),
(48515, '90205'),
(48504, '90205'),
(48557, '90205');

DELETE FROM `spell_script_names` WHERE `spell_id` = '90205';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(90205, 'spell_summon_orkus');

UPDATE `creature_template` SET `VehicleId`=1170 WHERE `entry`=48557;

DELETE FROM `creature_text` WHERE `entry` IN (48557, 48503, 48508);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48557,0,0,'What happened? What have you got in your hands there?',12,0,100,0,0,0,'Comment'),
(48557,1,0,'High Warlord Cromush reads the Alliance battle plan.',42,0,100,0,0,0,'Comment'),
(48557,2,0,'He... He died to get this here?',12,0,100,0,0,0,'Comment'),
(48557,3,0,'High Warlord Cromush lifts Orkus\' lifeless body up.',42,0,100,0,0,0,'Comment'),
(48557,4,0,'Do not mourn Orkus. He died with honor... with pride. He died a hero of the Horde.',12,0,100,0,0,0,'Comment'),
(48557,5,0,'From Lordaeron to Kalimdor, they will know his name and they will sing songs of glory, praising the fallen champion of the Horde.',12,0,100,0,0,0,'Comment'),
(48557,6,0,'Know that what you did will save hundreds, maybe thousands of lives. You are also a true hero of the Horde.',12,0,100,0,0,0,'Comment'),
(48503,0,0,'STOP! GET DOWN $n!',12,0,100,0,0,0,'Comment'),
(48503,1,0,'Look there, near the map table! The Stormpike Battle Master holds the Alliance battle plans!',12,0,100,0,0,0,'Comment'),
(48503,2,0,'I... I have a plan of my own.',12,0,100,0,0,0,'Comment'),
(48503,3,0,'I will kill the guard at the table and then I will draw the attention of the trio.',12,0,100,0,0,0,'Comment'),
(48503,4,0,'While I have them distracted you get the plans from the guard\'s corpse. I will call Kasha to pick you up as soon as I see you get the plans.',12,0,100,0,0,0,'Comment'),
(48503,5,0,'Do not worry about Orkus, $n. I... I will be fine.',12,0,100,0,0,0,'Comment'),
(48503,6,0,'Tell me when you are ready and we will go! |TInterface\Icons\ChatBubble-Backdrop.blp:20|t',12,0,100,0,0,0,'Comment'),
(48503,7,0,'GET THE PLANS AND GO!',14,0,100,0,0,0,'Comment'),
(48503,8,0,'CAN YOU SMELL WHAT THE LOK\'TAR IS COOKIN\'?!',14,0,100,0,0,0,'Comment'),
(48503,9,0,'KASHA, GET $n OUT OF HERE!',14,0,100,0,0,0,'Comment'),
(48503,10,0,'FORGET ABOUT ME, KASHA! GO!',14,0,100,0,0,0,'Comment'),
(48503,11,0,'K... Kasha... you... came back for me...',12,0,100,0,0,0,'Comment'),
(48503,12,0,'You are the best friend that Orkus has ever had, $n. *Orkus coughs*',12,0,100,0,0,0,'Comment'),
(48503,13,0,'I... I never knew anyone like you. You saved me, $n. More than once. I... I know it\'s selfish, but I have something to ask of you.',12,0,100,0,0,0,'Comment'),
(48503,14,0,'Please take care of Kasha. Make sure she finds a cold place to live.',12,0,100,0,0,0,'Comment'),
(48503,15,0,'Somewhere safe...',12,0,100,0,0,0,'Comment'),
(48508,0,0,'There\'s no gettin\' away this time, orc! You\'ve sung your last lok\'tar!',14,0,100,0,0,0,'Comment');

-- High Warlord Cromush
SET @ENTRY := 48557;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,48557,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,48557,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,2,48557,0,0,1,3,6000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,48557,0,0,45,0,10,0,0,0,0,11,48504,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 10 to Kasha"),
(@ENTRY,@SOURCETYPE,5,0,27,0,100,0,0,0,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 4"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,4,48557,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,5,48557,0,0,1,6,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,6,48557,0,0,15,28400,0,0,0,0,0,18,250,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Quest Complete");

-- Kingslayer Orkus
SET @ENTRY := 48503;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,29,3,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,1,41000,41000,41000,41000,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (41 secs) - Enable Gossip"),
(@ENTRY,@SOURCETYPE,6,0,62,0,100,0,56002,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,7,0,62,0,100,0,56002,0,0,0,81,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Gossip Flag"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,0,56002,0,0,0,69,0,0,0,0,0,0,11,48515,500,0,0.0,0.0,0.0,0.0,"On Gossip Select - Move To Stormpike Battle Master"),
(@ENTRY,@SOURCETYPE,9,0,4,0,100,0,0,0,0,0,11,90272,4,0,0,0,0,11,48515,500,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Heroic Leap"),
(@ENTRY,@SOURCETYPE,10,0,4,0,100,1,0,0,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 7"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,1,0,2,0,0,53,1,48503,0,28400,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Start WP (Trio)"),
(@ENTRY,@SOURCETYPE,12,13,40,0,100,0,1,0,0,0,1,8,5000,0,0,0,0,1,0,100,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 8"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,1,0,0,0,0,45,0,1,0,0,0,0,11,0,30,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to Creatures"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,1,0,3,0,0,1,9,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 9"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,1,9,48503,0,0,1,10,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Talk 10"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,1,9,48503,0,0,11,90278,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Summon Kasha"),
(@ENTRY,@SOURCETYPE,17,0,38,0,100,1,0,4,0,0,1,10,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 10"),
(@ENTRY,@SOURCETYPE,18,0,52,0,100,0,10,48503,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"After Talk 10 - DO NOTHING"),
(@ENTRY,@SOURCETYPE,19,0,38,0,100,0,0,5,0,0,11,56687,0,0,0,0,0,11,48504,100,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Ride Kasha"),
(@ENTRY,@SOURCETYPE,20,0,62,0,100,0,56002,0,0,0,49,0,0,0,0,0,0,11,48515,500,0,0.0,0.0,0.0,0.0,"On Gossip Select - Attack Stormpike Battle Master"),
(@ENTRY,@SOURCETYPE,21,0,38,0,100,0,0,5,0,0,1,11,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 11"),
(@ENTRY,@SOURCETYPE,22,0,38,0,100,0,0,6,0,0,1,12,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 12"),
(@ENTRY,@SOURCETYPE,23,0,38,0,100,0,0,7,0,0,1,13,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Talk 13"),
(@ENTRY,@SOURCETYPE,24,0,38,0,100,0,0,8,0,0,1,14,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 8 - Talk 14"),
(@ENTRY,@SOURCETYPE,25,0,38,0,100,0,0,9,0,0,1,15,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 9 - Talk 15"),
(@ENTRY,@SOURCETYPE,26,0,38,0,100,0,0,9,0,0,11,90359,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 9 - Die"),
(@ENTRY,@SOURCETYPE,27,0,38,0,100,0,0,10,0,0,11,46598,0,0,0,0,0,11,48557,50,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Ride Cromush");

-- Kasha
SET @ENTRY := 48504;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-1323.96,545.8,105.5,3.43,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Ride Owner"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,1,0,0,0,0,45,0,4,0,0,0,0,11,48503,100,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Data 4 to Orkus"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,1,0,0,0,0,53,1,48504,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,4,0,0,0,45,0,5,0,0,0,0,11,48503,100,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Set Data 5 to Orkus"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,4,0,0,0,54,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - WP Pause"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 6 - Do Nothing"),
(@ENTRY,@SOURCETYPE,7,0,40,0,100,0,4,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,8,0,1,1,100,1,6000,6000,6000,6000,45,0,6,0,0,0,0,11,48503,50,0,0.0,0.0,0.0,0.0,"Update - Set Data 6 to Orkus"),
(@ENTRY,@SOURCETYPE,9,0,1,1,100,1,16000,16000,16000,16000,45,0,7,0,0,0,0,11,48503,50,0,0.0,0.0,0.0,0.0,"Update - Set Data 7 to Orkus"),
(@ENTRY,@SOURCETYPE,10,0,1,1,100,1,36000,36000,36000,36000,45,0,8,0,0,0,0,11,48503,50,0,0.0,0.0,0.0,0.0,"Update - Set Data 8 to Orkus"),
(@ENTRY,@SOURCETYPE,11,0,1,1,100,1,46000,46000,46000,46000,45,0,9,0,0,0,0,11,48503,50,0,0.0,0.0,0.0,0.0,"Update - Set Data 9 to Orkus"),
(@ENTRY,@SOURCETYPE,12,0,40,0,100,0,6,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 6 - Remove Owner"),
(@ENTRY,@SOURCETYPE,13,14,38,0,100,0,0,10,0,0,28,56687,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Remove Orkus"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,48503,50,0,0.0,0.0,0.0,0.0,"Link - Set Data 10 to Orkus"),
(@ENTRY,@SOURCETYPE,15,0,40,0,100,0,6,0,0,0,85,90407,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 6 - Summon Cromush");

-- Vanndar Stormpike
SET @ENTRY := 48508;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,3500,3500,3500,3500,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3.5 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,48508,0,0,49,0,0,0,0,0,0,11,48503,25,0,0.0,0.0,0.0,0.0,"After Talk 0 - Attack Orkus"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,48508,0,0,45,0,3,0,0,0,0,11,48503,25,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 3 to Orkus");

DELETE FROM `creature_text` WHERE `entry`=48969;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48969,0,0,'So you have come seeking our aid?',12,0,100,0,0,0,'Comment'),
(48969,1,0,'Drek\'Thar coughs.',16,0,100,0,0,0,'Comment'),
(48969,2,0,'I... *cough* I have been alive for a very long time. In that time I have seen and done terrible things.',12,0,100,0,0,0,'Comment'),
(48969,3,0,'Things that still keep me awake at nights.',12,0,100,0,0,0,'Comment'),
(48969,4,0,'But these terrible things that I have done and the people that I have harmed - I know them... I face them... and I feel remorse for them.',12,0,100,0,0,0,'Comment'),
(48969,5,0,'But the Forsaken. *cough* What do they feel?',12,0,100,0,0,0,'Comment'),
(48969,6,0,'They ravage the land and destroy everything that they touch. How many lives have been lost to their vile poisons?',12,0,100,0,0,0,'Comment'),
(48969,7,0,'How many innocents have fallen before the Forsaken war machine?',12,0,100,0,0,0,'Comment'),
(48969,8,0,'Countless... countless lives... *cough*',12,0,100,0,0,0,'Comment'),
(48969,9,0,'Yes... I have done terrible things, but nothing could ever be as terrible as lending aid to the Forsaken.',12,0,100,0,0,0,'Comment'),
(48969,10,0,'You go back to that spineless orc who would not come see me and you tell him that the Frostwolf clan will not aid the Forsaken. Not now, not ever!',12,0,100,0,0,0,'Comment'),
(48969,11,0,'BEGONE!',12,0,100,0,0,0,'Comment');

-- Captain Galvangar
SET @ENTRY := 48980;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward");

-- Drek'Thar
SET @ENTRY := 48969;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,46,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward 20 yd"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,48969,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,48969,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,48969,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,3,48969,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,4,48969,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,5,48969,0,0,1,6,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,6,48969,0,0,1,7,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,7,48969,0,0,1,8,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,8,48969,0,0,1,9,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 8 - Talk 9"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,9,48969,0,0,1,10,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Talk 10"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,10,48969,0,0,1,11,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 10 - Talk 11"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,10,48969,0,0,15,28600,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"After Talk 10 - Quest Complete"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,11,48969,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 11 - Force Despawn "),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,11,48969,0,0,45,0,1,0,0,0,0,11,48980,30,0,0.0,0.0,0.0,0.0,"After Talk 11 - Set Data 1 to Captain"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,11,48969,0,0,81,2,0,0,0,0,0,11,13817,150,0,0.0,0.0,0.0,0.0,"After Talk 11 - Set Quest Flag to Voggah");

-- Voggah Deathgrip
SET @ENTRY := 13817;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,28600,0,0,0,12,48980,4,120000,0,0,0,8,0,0,0,407.2,-1009.42,111.41,2.6,"On Quest Accept - Summon Galvangar"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,28600,0,0,0,12,48969,4,120000,0,0,0,8,0,0,0,405.27,-1012.61,111.36,2.59,"On Quest Accept - Summon Drek'thar"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,28600,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Remove Quest Flag");

UPDATE `creature_template` SET `VehicleId`=686, `InhabitType`=4, `speed_walk`=500, `speed_run`=500.14286 WHERE `entry`=49152;
UPDATE `quest_template` SET `SourceSpellId`=91608 WHERE `Id`=28616;
UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (49111, 49116);

DELETE FROM `waypoints` WHERE `entry` = '49152';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(49152, 1, -25.50, -832.58, 167.15, 'Stormpike Apocalypse WP'),
(49152, 2, -11.27, -333.00, 211.21, 'Stormpike Apocalypse WP'),
(49152, 3, -57.40, -145.93, 163.73, 'Stormpike Apocalypse WP');

-- Stormpike Apocalypse Camera
SET @ENTRY := 49152;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,1,49152,0,28616,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,85,91202,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Blackout to Owner"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,3,0,0,0,12,49166,4,120000,0,0,0,8,0,0,0,-78.13,-107.21,134.77,1.55,"On WP Reached - Summon Lagrave"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,3,0,0,0,12,49165,4,120000,0,0,0,8,0,0,0,-78.34,-103.31,134.93,4.76,"On WP Reached - Summon Magruder");

DELETE FROM `creature_text` WHERE `entry` IN (49165, 49166);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49165,0,0,'Holy... What in the hell is this?',12,0,100,0,0,0,'Comment'),
(49165,1,0,'Are you kidding me? Look at all this crap! There\'s like a million wires. I\'m a three wire kind of guy...',12,0,100,0,0,0,'Comment'),
(49165,2,0,'RUN!!!!!!',12,0,100,0,0,0,'Comment'),
(49166,0,0,'Ye can defuse it, right Magruder?!',12,0,100,0,0,0,'Comment');

-- Goblin Pocket-Nuke
SET @ENTRY := 49153;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,49169,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Explode");

-- Goblin Pocket-Nuke
SET @ENTRY := 49179;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,49169,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Explode");

-- Goblin Pocket-Nuke
SET @ENTRY := 49169;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,49169,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Explode");

-- Goblin Pocket-Nuke
SET @ENTRY := 49168;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,49169,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Explode");

DELETE FROM `creature_template_addon` WHERE `entry` IN (49165, 49166);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(49165, '91609'),
(49166, '91609');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28538;
UPDATE `creature_template` SET `VehicleId`=1170, `unit_flags`=512, `InhabitType`=4, `speed_walk`=2, `speed_run`=2.14286 WHERE `entry`=48752;

-- Banshee
SET @ENTRY := 48752;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,34804,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Materialize"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,1,0,0,0,0,29,1,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,1500,1500,1500,1500,86,46598,0,11,48741,10,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Ride Creature"),
(@ENTRY,@SOURCETYPE,4,0,27,0,100,0,0,0,0,0,74,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Remove Event"),
(@ENTRY,@SOURCETYPE,5,0,27,0,100,0,0,0,0,0,46,100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Move Away"),
(@ENTRY,@SOURCETYPE,6,0,27,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Run"),
(@ENTRY,@SOURCETYPE,7,0,27,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Fly"),
(@ENTRY,@SOURCETYPE,8,0,27,0,100,0,0,0,0,0,33,48752,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Quest Credit"),
(@ENTRY,@SOURCETYPE,9,0,27,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,10,0,60,0,100,0,1500,1500,1500,1500,86,46598,0,11,48742,10,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Ride Creature"),
(@ENTRY,@SOURCETYPE,11,0,27,0,100,0,0,0,0,0,74,10,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Remove Event"),
(@ENTRY,@SOURCETYPE,12,0,60,1,100,0,10000,10000,10000,10000,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Passenger"),
(@ENTRY,@SOURCETYPE,13,0,28,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

DELETE FROM `conditions` WHERE `SourceEntry` = '90679';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 90679, 1, 0, 31, 0, 3, 48187, 0, 0, 0, '', 'Duskingdawn\'s Blessing - Hill Fawn');

DELETE FROM `spell_script_names` WHERE `spell_id` = '90679';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(90679, 'spell_duskingdawn_blessing');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28603;
DELETE FROM `creature_template_addon` WHERE `entry` IN (48912, 48922);
DELETE FROM `creature_addon` WHERE `emote`=37;

UPDATE `creature_template` SET `mindmg`=30, `maxdmg`=44, `attackpower`=11 WHERE `entry` IN (48924, 48922, 48923);
UPDATE `creature_template` SET `mindmg`=15, `maxdmg`=20, `attackpower`=5 WHERE `entry`=48912;
-- Drill Sergeant Magnus
SET @ENTRY := 48923;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79977,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79972,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Seal of Truth"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,79976,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Retribution Aura"),
(@ENTRY,@SOURCETYPE,3,0,0,0,75,0,3500,7500,3500,7500,11,79970,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Divine Storm"),
(@ENTRY,@SOURCETYPE,4,0,0,0,25,0,3500,7500,3500,7500,11,31803,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Censure"),
(@ENTRY,@SOURCETYPE,5,0,0,0,15,0,3500,7500,3500,7500,11,79971,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hammer of Wrath");

-- Instructor Rufus
SET @ENTRY := 48922;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,39591,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Searing Totem"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79892,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Water Shield"),
(@ENTRY,@SOURCETYPE,2,0,0,0,50,0,3500,7500,3500,7500,11,79886,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lava Burst"),
(@ENTRY,@SOURCETYPE,3,0,0,0,50,0,3500,7500,3500,7500,11,79884,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Bolt"),
(@ENTRY,@SOURCETYPE,4,0,0,0,25,0,3500,7500,3500,7500,11,79884,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Shock");

-- Captain Crudbeard
SET @ENTRY := 48924;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79905,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Raise Dead"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79907,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Anti-Magic Zone"),
(@ENTRY,@SOURCETYPE,2,0,0,0,75,0,3500,7500,3500,7500,11,79901,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blood Plague"),
(@ENTRY,@SOURCETYPE,3,0,0,0,50,0,3500,7500,3500,7500,11,79903,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Death Coil"),
(@ENTRY,@SOURCETYPE,4,0,0,0,75,0,3500,7500,3500,7500,11,79902,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Plague Strike"),
(@ENTRY,@SOURCETYPE,5,0,0,0,75,0,3500,7500,3500,7500,11,79909,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scourge Strike");

-- Stormpike Trainee
SET @ENTRY := 48912;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,500,1500,500,1500,5,37,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,13730,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,79871,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Recklessness");

UPDATE `creature_template` SET `lootid`=48184 WHERE `entry`=48184;

DELETE FROM `creature_loot_template` WHERE `item` = '64410';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48184, 64410, -89.1668, 1, 0, 1, 1);

UPDATE `creature_template` SET `mindmg`=31, `maxdmg`=47, `attackpower`=12, `dmg_multiplier`=3.5 WHERE `entry`=47484;
DELETE FROM `creature_loot_template` WHERE `item` = '64386';

-- Yetimus the Yeti Lord
SET @ENTRY := 47484;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,88533,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Jump");
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(47484, 64386, -57.6312, 1, 0, 1, 1);

UPDATE `creature_template` SET `mindmg`=31, `maxdmg`=47, `attackpower`=12, `dmg_multiplier`=3.5 WHERE `entry` IN (49263, 49264, 49265, 49266, 49268);

-- Zephyrus
SET @ENTRY := 49263;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,75,0,3500,7500,3500,7500,11,80066,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Tornado"),
(@ENTRY,@SOURCETYPE,1,0,0,0,75,0,3500,7500,3500,7500,11,95038,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wind Shear");

-- Bloodvenom
SET @ENTRY := 49264;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,7500,3500,7500,11,39207,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Sprout");

-- Teracula
SET @ENTRY := 49265;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,7500,3500,7500,11,89932,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rupture Line");

-- Infernus
SET @ENTRY := 49266;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,75025,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Rush of Flame"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,7500,3500,7500,11,90257,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Conflagration");

-- D-1000
SET @ENTRY := 49268;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,61369,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Enrage"),
(@ENTRY,@SOURCETYPE,1,0,0,0,75,0,3500,7500,3500,7500,11,95970,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frost Breath"),
(@ENTRY,@SOURCETYPE,2,0,0,0,75,0,3500,7500,3500,7500,11,16564,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Gargoyle Strike"),
(@ENTRY,@SOURCETYPE,3,0,0,0,25,0,3500,7500,3500,7500,11,16564,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Swipe");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=28643;
UPDATE `quest_template` SET `PrevQuestId`='28506' WHERE `Id`=28556;
UPDATE `quest_template` SET `Method`=2, `Flags`=0, `SpecialFlags`=2 WHERE `Id`=28506;

DELETE FROM `spell_script_names` WHERE `spell_id` = '91085';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(91085, 'spell_place_goblin_pocket_nuke');

-- High Warlord Cromush
SET @ENTRY := 48545;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,28506,0,0,0,15,28506,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Complete Quest on Accept");

UPDATE `quest_template` SET `SourceSpellId`=0 WHERE `Id`=28603;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (91393, -91391);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(91393, 91391, 'Lilith Summon Controller'),
(91393, 91392, 'Lilith Despawn'),
(-91391, 91393, 'Lilith Despawn');

DELETE FROM `spell_script_names` WHERE `spell_id` = '91393';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(91393, 'spell_summon_lilith');

-- Lilith
SET @ENTRY := 49035;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,91671,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spawn Cast Demonstration"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,29,5,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Summoner"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,75,91391,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Aura");

-- Water Barrel
SET @ENTRY := 49036;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,3500,3500,60000,60000,45,0,1,0,0,0,0,11,0,35,0,0.0,0.0,0.0,0.0,"Update - Set Data 1 to Trainee");

-- Stormpike Trainee
SET @ENTRY := 48912;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,500,1500,500,1500,5,37,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,13730,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,79871,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Recklessness"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,33,49037,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Death - Killed Monster Credit"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,69,0,0,0,0,0,0,11,49036,15,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Move to Invoker"),
(@ENTRY,@SOURCETYPE,5,0,34,0,100,0,8,0,0,0,45,0,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Data 2 to Self"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,2,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Die"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,2,0,0,5,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Play Emote ");