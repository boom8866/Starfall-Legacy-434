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
(47443,1,0,'HAH! Looks like you're running out of idiots to put atop this horse, Darthalia. This is the puniest one yet.',12,0,100,0,0,0,'Comment'),
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
(47499,0,0,'Stand tall and proud, $n. Don\'t let any of these scrubs give you any trouble. Show them who\'s boss! ',12,0,100,0,0,0,'Comment');
(47499,1,0,'I see one coming now! Looks like a real winner. Keep it cool, $n. Keep it cool. ',12,0,100,0,0,0,'Comment');
(47499,2,0,'These new Forsaken tend to be a little... um... stupid. It usually takes awhile for them to acclimate. ',12,0,100,0,0,0,'Comment');
(47499,3,0,'Oh great... not this one again. I know this orc. He\'s got no business being here, but since he\'s a bottom-feeding pansy he likes to hang around here and prey on the helpless. Don\'t let him bully you. ',12,0,100,0,0,0,'Comment');
(47499,4,0,'Here's to hoping he never returns. Maybe he'll drown?',12,0,100,0,0,0,'Comment');
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
(47872,0,0,'I won't soon forget this kindness.',12,0,100,0,0,0,'Comment'),
(47872,0,1,'Thank you for saving my life. I owe you a debt of gratitude.',12,0,100,0,0,0,'Comment'),
(47872,0,2,'It... they planted us in the dirt like crops. Stillwater is insane! Get out of here while you still can!',12,0,100,0,0,0,'Comment'),
(47872,0,3,'He killed everyone! EVERYONE!',12,0,100,0,0,0,'Comment'),
(47872,0,4,'M... maybe you're not all bad after all...',12,0,100,0,0,0,'Comment'),
(47872,0,5,'Should you ever be buried neck deep in a field of feces and urine, I will be sure to lend you a hand. ',12,0,100,0,0,0,'Comment');

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
(47928,0,0,'|cffffffffThere's trouble at the Sludge Fields...',41,0,100,0,0,0,'Comment');

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