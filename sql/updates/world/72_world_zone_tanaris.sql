DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` IN (28507, 27446, 28509, 27447);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 976, 28507, 1, 74, 0),
(49416, 976, 27446, 1, 74, 0),
(49416, 976, 28509, 1, 74, 0),
(49416, 976, 27447, 1, 74, 0);

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (732675, 733006);

DELETE FROM `creature_text` WHERE `entry`=39696;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39696,0,0,'Yaaaaaaaaaaaaaaaaaaaaaaay!',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '74175';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(74175, 74176, 'Deploy Butcherbot -> Summon Butcherbot to Corpse');

UPDATE `creature_template` SET `ScriptName`='npc_butcherbot' WHERE `entry`=39696;

DELETE FROM `spell_script_names` WHERE `spell_id` = '74175';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74175, 'spell_deploy_butcherbot');

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=39022;
UPDATE `creature_template` SET `unit_flags`=768, `VehicleId`=751, `InhabitType`=4 WHERE `entry`=40791;
UPDATE `creature_template` SET `unit_flags`=768, `VehicleId`=751, `InhabitType`=4 WHERE `entry`=40505;
UPDATE `creature_template` SET `unit_flags`=768, `VehicleId`=752, `spell1`=75560, `spell2`=73257, `spell6`=75991 WHERE `entry`=40511;

DELETE FROM `creature_loot_template` WHERE `item` = '52064';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5647, 52064, -60.687, 1, 0, 1, 1),
(5646, 52064, -59.9938, 1, 0, 1, 1),
(5645, 52064, -60.0431, 1, 0, 1, 1);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '40505';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(40505, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '40511';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(40505, 40511, 0, 1, 'Steamwheedle Balloon -> Throwing Station', 8, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = '40505';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(40505, 0, 0, 50331648, 1, 0, '');

UPDATE `creature_template` SET `IconName`='vehichleCursor', `npcflag`=1, `ScriptName`='npc_steamwheedle_balloon' WHERE `entry`=40604;
UPDATE `creature_template` SET `ScriptName`='npc_steamwheedle_balloon_escort' WHERE `entry`=40505;

DELETE FROM `script_waypoint` WHERE `entry` = '40505';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(40505, 1, -7090.10, -3909.76, 75, 'Steamwheedle Balloon'),
(40505, 2, -7050.32, -4211.33, 75, 'Steamwheedle Balloon'),
(40505, 3, -6875.14, -4618.66, 75, 'Steamwheedle Balloon'),
(40505, 4, -6796.45, -4735.78, 75, 'Steamwheedle Balloon'),
(40505, 5, -6767.71, -4796.64, 75, 'Steamwheedle Balloon'),
(40505, 6, -6767.39, -4889.12, 75, 'Steamwheedle Balloon'),
(40505, 7, -6869.06, -4908.59, 75, 'Steamwheedle Balloon'),
(40505, 8, -6980.09, -4898.15, 75, 'Steamwheedle Balloon'),
(40505, 9, -7089.12, -4832.38, 75, 'Steamwheedle Balloon'),
(40505, 10, -7098.96, -4682.06, 75, 'Steamwheedle Balloon'),
(40505, 11, -7086.16, -4553.28, 75, 'Steamwheedle Balloon'),
(40505, 12, -7141.32, -4441.87, 75, 'Steamwheedle Balloon'),
(40505, 13, -7068.47, -4360.89, 75, 'Steamwheedle Balloon'),
(40505, 14, -6998.87, -4385.42, 75, 'Steamwheedle Balloon'),
(40505, 15, -6929.76, -4617.46, 75, 'Steamwheedle Balloon'),
(40505, 16, -6875.14, -4618.66, 75, 'Steamwheedle Balloon');

UPDATE `creature_template` SET `ScriptName`='npc_balloon_throwing_station' WHERE `entry`=40511;
UPDATE `creature_template` SET `minlevel`=45, `maxlevel`=45, `speed_walk`=3.2, `speed_run`=2 WHERE `entry`=40505;

-- Steamwheedle Survivor
SET @ENTRY := 38571;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,72337,1,0,0,11,75710,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast Jump"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,72337,1,0,0,33,38576,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

DELETE FROM `conditions` WHERE `SourceEntry` = '72337';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 72337, 0, 0, 31, 0, 3, 38571, 0, 0, 0, '', 'Targeting -> Steamwheedle Survivor');

DELETE FROM `spell_script_names` WHERE `spell_id` = '75991';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75991, 'spell_emergency_rocket_pack');

-- Dune Worm
SET @ENTRY := 44573;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,5000,5000,5000,5000,11,29147,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Sandworm Submerge Visual OOC"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,1,5000,5000,5000,5000,11,33928,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Tunnel Bore Passive OOC"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,4,1,100,1,0,0,0,0,28,29147,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Remove Sandworm Submerge Visual on Aggro"),
(@ENTRY,@SOURCETYPE,4,0,4,1,100,1,0,0,0,0,28,33928,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Remove Tunnel Bore Passive on Aggro"),
(@ENTRY,@SOURCETYPE,5,0,4,1,100,1,0,0,0,0,11,31747,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Poison on Aggro"),
(@ENTRY,@SOURCETYPE,6,0,4,1,100,1,0,0,0,0,19,16777215,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Change Flag for attack on Aggro"),
(@ENTRY,@SOURCETYPE,7,0,9,1,100,0,0,50,2100,4500,11,31747,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Poison"),
(@ENTRY,@SOURCETYPE,8,0,9,1,100,0,0,50,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in Poison Range"),
(@ENTRY,@SOURCETYPE,9,0,9,1,100,0,0,50,8000,9100,11,32738,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Bore on Close"),
(@ENTRY,@SOURCETYPE,10,0,7,1,100,1,0,0,0,0,11,33928,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Tunnel Bore Passive on Evade"),
(@ENTRY,@SOURCETYPE,11,0,7,1,100,1,0,0,0,0,11,29147,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Sandworm Submerge Visual on Evade"),
(@ENTRY,@SOURCETYPE,12,0,7,1,100,1,0,0,0,0,18,16777215,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Change Flag on Evade");

UPDATE `creature_template_addon` SET `bytes1`=0, `auras`='' WHERE `entry`=44573;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '25115';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 979, 25115, 25032, 1, 66);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` IN (24910, 25050); 
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 1336, 24910, 0, 1, 74, 0),
(49417, 1336, 25050, 0, 1, 74, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (736586, 736587);
UPDATE `creature` SET `MovementType`=0, `spawndist`=0 WHERE `guid` IN (174973, 174974);

DELETE FROM `conditions` WHERE `SourceEntry` = '72520';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 72520, 0, 0, 31, 0, 3, 38660, 0, 0, 0, '', 'Targeting -> Bunny 01'),
(13, 1, 72520, 0, 1, 31, 0, 3, 38662, 0, 0, 0, '', 'Targeting -> Bunny 02'),
(13, 1, 72520, 0, 2, 31, 0, 3, 38665, 0, 0, 0, '', 'Targeting -> Bunny 03');

-- Lost Rigger Building 01 Bunny
SET @ENTRY := 38660;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,72520,1,0,0,75,42346,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Flames"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,72520,1,0,0,33,38660,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

-- Lost Rigger Building 02 Bunny
SET @ENTRY := 38662;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,72520,1,0,0,75,42346,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Flames"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,72520,1,0,0,33,38662,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

-- Lost Rigger Building 03 Bunny
SET @ENTRY := 38665;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,72520,1,0,0,75,42346,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Flames"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,72520,1,0,0,33,38665,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

UPDATE `creature_template` SET `scale`=3, `flags_extra`=128 WHERE `entry` IN (38660, 38662, 38665);
UPDATE `gossip_menu_option` SET `option_id`=8, `npc_option_npcflag`=65536 WHERE `menu_id`=11402 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=11402 AND `id`=1;

DELETE FROM `creature_loot_template` WHERE `item` = '51778';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5427, 51778, -41.7815, 1, 0, 1, 1);

-- Hazzali Swarmer
SET @ENTRY := 5451;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,0,0,1000,1000,11,6589,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hazzali Swarmer - Out Of Combat - Cast Silithid Swarm"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,1,0,0,0,0,11,11023,3,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Hazzali Swarmer - On Death - Cast Summon Hazzali Parasites"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,72659,1,0,0,85,72677,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Summon Wrangled Swarmer"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,72659,1,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Despawn");

UPDATE `creature_template` SET `ScriptName`='npc_wrangled_silithid' WHERE `entry`=38739;

DELETE FROM `creature_text` WHERE `entry`=38706;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38706,0,0,'Holy cats! It worked! Soothfancy, come look at this!',12,0,100,1,0,0,'Comment'),
(38706,1,0,'What\'s it thinking?',12,0,100,1,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '72659';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72659, 'spell_throw_hyena_chunk');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '6646';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(6646, 0, 'I\'m ready to pilot our silithid.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=6646 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 6646, 0, 0, 0, 9, 0, 24953, 0, 0, 0, 0, 0, '', 'Narain Soothfancy - Show gossip only if quest 24953 is active');

UPDATE `creature_template` SET `minlevel`=47, `maxlevel`=47, `VehicleId`=654, `spell1`=73207, `spell2`=73211 WHERE `entry`=38748;

-- Narain Soothfancy
SET @ENTRY := 11811;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,6646,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,6646,0,0,0,85,72976,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Mind-Controlled Silithid");

DELETE FROM `creature_text` WHERE `entry`=38748;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38748,0,0,'Sniff for pheromones to find your way into the hive!',42,0,100,0,0,8174,'Comment');

-- Mind-Controlled Swarmer
SET @ENTRY := 38748;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0");

DELETE FROM `creature_template_addon` WHERE `entry` = '38748';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(38748, '73199');

DELETE FROM `conditions` WHERE `SourceEntry` = '73207';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 73207, 0, 0, 31, 0, 3, 38992, 0, 0, 0, '', 'Targeting -> Bunny 01'),
(13, 1, 73207, 0, 1, 31, 0, 3, 38993, 0, 0, 0, '', 'Targeting -> Bunny 02'),
(13, 1, 73207, 0, 2, 31, 0, 3, 38994, 0, 0, 0, '', 'Targeting -> Bunny 03');

-- Pheromone Bunny A
SET @ENTRY := 38992;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73207,1,0,0,11,72766,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast Trail");

-- Pheromone Bunny B
SET @ENTRY := 38993;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73207,1,0,0,11,72766,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast Trail");

-- Pheromone Bunny C
SET @ENTRY := 38994;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73207,1,0,0,11,72766,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast Trail");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry` IN (38992, 38993, 38994);

DELETE FROM `spell_script_names` WHERE `spell_id` = '73211';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73211, 'spell_detonate_silithid');

-- Romo's Standard Bunny
SET @ENTRY := 37522;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,11,46262,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Darkness"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,11,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Banish State"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,0,0,0,0,22,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On SpellHit - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,5,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Evade"),
(@ENTRY,@SOURCETYPE,5,0,7,0,100,0,0,0,0,0,28,46262,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Auras"),
(@ENTRY,@SOURCETYPE,6,0,7,0,100,0,0,0,0,0,28,32567,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Auras"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,28,46265,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Auras"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,0,10000,10000,10000,10000,28,72942,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Auras");

DELETE FROM `creature` WHERE `guid` = '840942';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(840942, 39059, 1, 1, 1, 0, 0, -9757.74, -3666.69, 10.8998, 1.03354, 300, 0, 0, 126, 0, 0, 0, 0, 0);

DELETE FROM `creature_loot_template` WHERE `item` = '52282';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5431, 52282, -17.6612, 1, 0, 1, 1);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-100 WHERE `entry`=39061 AND `item`=52281;
UPDATE `gameobject_template` SET `ScriptName`='go_antediluvean_chest' WHERE `entry`=202474;
UPDATE `quest_template` SET `PrevQuestId`='25095' WHERE `Id`=25513;
UPDATE `quest_template` SET `PrevQuestId`='25094' WHERE `Id`=25095;
UPDATE `quest_template` SET `PrevQuestId`='25067' WHERE `Id`=25094;
UPDATE `quest_template` SET `PrevQuestId`='25095' WHERE `Id`=25591;

DELETE FROM `creature_text` WHERE `entry`=39034;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39034,0,0,'%n has done it again! Zumonga dies once more!',14,0,100,0,0,0,'ZUMONGA DIED'),
(39034,1,0,'All that\'s left of the challenger is a red stain on the floor!',14,0,100,0,0,0,'PLAYER DIED'),
(39034,1,2,'And that\'s that, folks! This conflict\'s been settled the proper way, with VIOLENCE! Let\'s hear it for our contestants!',14,0,100,0,0,0,'RANDOM?'),
(39034,3,0,'Any Ladies and Gentlemen present should LEAVE NOW...for only REAL MEN AND WOMEN will be able to handle the gory spectacle about to unfold! Introducing the first fighter, the warrior of the Wastewander, the Ayatollah of Kaja-Cola...THE GINORMUS!',14,0,100,0,0,0,'GINORMUS ENTER'),
(39034,1,3,'Avert your eyes, ladies and gentlemen! It\'s a bloodbath!',14,0,100,0,0,0,'PLAYER DIED'),
(39034,5,0,'Call in the clowns! It\'s turned into a circus in there!',14,0,100,0,0,0,'RANDOM?'),
(39034,6,0,'OOOF! That one\'s gonna require the "scraper."',14,0,100,0,0,0,'RANDOM?'),
(39034,7,0,'Our next fighter was found in the deepest tombs of Zul\'Farrak! Gorged on cursed blood, raised from death countless times, he now knows only fury and violence! Dare you face the mindless wrath of...ZUMONGA!',14,0,100,0,0,0,'ZUMONGA ENTER'),
(39034,0,1,'OUTTA NOWHERE -- WHAMO! DEAD!',14,0,100,0,0,0,'ZUMONGA DIED?'),
(39034,1,1,'The challenger has been defeated!',14,0,100,0,0,0,'PLAYER DIED'),
(39034,10,0,'The faint of heart may wish to shield their eyes! Being brought into the ring now is a horror, captured from the dark tunnels of the Centipaar Hive! I give you the skittering death: SARINEXX!',14,0,100,0,0,0,'SARINEXX ENTER'),
(39034,11,0,'The Ginormus has fallen! %n looks like $g\'s ready for more!',14,0,100,0,0,0,'GINORMUS DIED'),
(39034,12,0,'The Ginormus has fallen! Water Elemental looks like she\'s ready for more!',14,0,100,0,0,0,'GINORMUS DIED'),
(39034,13,0,'There is no stopping $n! Sarinexx has been massacred!',14,0,100,0,0,0,'SARINEXX DIED'),
(39034,14,0,'They went down like a sack of orc skulls!',14,0,100,0,0,0,'Comment'),
(39034,15,0,'Into the Thunderdrome, $n! There\'s no getting out until someone\'s hit the sand. Let\'s start the show!',12,0,100,0,0,0,'INTRO SAY');

UPDATE `creature_template` SET `ScriptName`='npc_dr_dealwell' WHERE `entry`=39034;
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id` IN (25067, 25513, 25591, 25095, 25094);
UPDATE `creature_template` SET `mindmg`=90, `maxdmg`=112, `attackpower`=202, `dmg_multiplier`=3.5, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN
(40542, 40876, 39149, 39075, 39148);

-- Megs Dreadshredder
SET @ENTRY := 40542;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,76746,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Summon Dreadshredder"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,5000,7500,11,76735,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Wave"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,15,25513,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Call Quest Complete");

-- Kelsey Steelspark
SET @ENTRY := 40876;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,76749,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Summon the Steelspark"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,5000,7000,11,76749,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Chained Sparks"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,15,25591,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Call Quest Complete");

-- The Ginormus
SET @ENTRY := 39075;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,15,25067,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Call Quest Complete");

-- Zumonga
SET @ENTRY := 39148;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,73859,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Headbutt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,10000,6500,12500,11,73858,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Taste of Blood"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,15,25094,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Call Quest Complete");

-- Sarinexx
SET @ENTRY := 39149;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,83730,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Sand Trap"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,4000,3000,4000,11,73863,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wide Slash"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,15,25095,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Call Quest Complete");

UPDATE `creature_template` SET `unit_class`=8 WHERE `entry` IN (40542, 40876, 39149, 39075, 39148);
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=40542;

-- Mazoga
SET @ENTRY := 38968;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-7453.02,-2879.7,6.58,5.55,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,7000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,38968,0,0,1,1,7000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,38968,0,0,1,2,7000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,38968,0,0,1,3,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,6,52,0,100,0,3,38968,0,0,19,320,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Attackable"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Despawn"),
(@ENTRY,@SOURCETYPE,8,0,4,0,100,0,0,0,0,0,11,11658,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Sul'Thraze"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,2000,3000,12000,12000,11,41056,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Whirlwind"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,4000,4000,5000,5000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,11,0,6,0,100,0,0,0,0,0,15,25032,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete");

UPDATE `gameobject_template` SET `ScriptName`='go_jang_thraze_the_protector' WHERE `entry`=202441;
UPDATE `quest_template` SET `Flags`=10, `SpecialFlags`=0 WHERE `Id`=25032;

DELETE FROM `creature` WHERE `guid` = '840943';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(840943, 40712, 209, 1, 1, 0, 0, 1216.13, 836.708, 8.87785, 6.134, 300, 0, 0, 1294, 3801, 0, 0, 0, 0);

UPDATE `creature_template` SET `mindmg`=90, `maxdmg`=95, `attackpower`=115, `dmg_multiplier`=1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN
(40717 ,40656,40657,39022,40581,38909,40648,44569,44573,44568,40632,38749,40636,40593,40635,47387,39020,44714,39061,38914,38997,38916,39186, 38880);

DELETE FROM `creature_loot_template` WHERE `item` = '52041';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(5455, 52041, -89.5178, 1, 0, 1, 2),
(5458, 52041, -83.4869, 1, 0, 1, 2),
(5460, 52041, -80.3412, 1, 0, 1, 2),
(5459, 52041, -43.4437, 1, 0, 1, 2);

DELETE FROM `creature_text` WHERE `entry`=5471;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(5471,0,0,'I'll crush you!',12,0,50,0,0,0,'on Aggro Text'),
(5471,0,1,'Me smash! You die!',12,0,50,0,0,0,'on Aggro Text'),
(5471,0,2,'Raaar!!! Me smash $r!',12,0,50,0,0,0,'on Aggro Text'),
(5471,1,0,'Thank you, funny ogre!',12,0,100,0,0,0,'Comment'),
(5471,1,1,'We get tabard?',12,0,100,0,0,0,'Comment'),
(5471,1,2,'Yay!',12,0,100,0,0,0,'Comment'),
(5471,1,3,'...me forget what you said.',12,0,100,0,0,0,'Comment'),
(5471,1,4,'Me still hungry',12,0,100,0,0,0,'Comment'),
(5471,1,5,'Okay. Me sign.',12,0,100,0,0,0,'Comment'),
(5471,1,6,'Me not understand.',12,0,100,0,0,0,'Comment'),
(5471,1,7,'Read make head hurt.',12,0,100,0,0,0,'Comment');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11093 AND `id`=0;
UPDATE `creature_template` SET `gossip_menu_id`=11093 WHERE `entry`=5471;

DELETE FROM `conditions` WHERE `SourceGroup`=11093 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11093, 0, 0, 0, 9, 0, 24955, 0, 0, 0, 0, 0, '', 'Dunemaul Ogre - Show gossip only if quest 24955 is active');

-- Dunemaul Ogre
SET @ENTRY := 5471;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,1000,1000,0,0,11,7165,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dunemaul Ogre - Out Of Combat - Cast Battle Stance"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,6000,6000,9000,11,25710,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Dunemaul Ogre - In Combat - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,2,8,62,0,100,0,11093,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11093,0,0,0,33,38848,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,11093,0,0,0,1,1,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,11093,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Gossip"),
(@ENTRY,@SOURCETYPE,6,0,25,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset - Set Gossip"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Gossip"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Despawn"),
(@ENTRY,@SOURCETYPE,9,0,8,0,100,0,73068,1,0,0,33,39073,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,10,0,8,0,100,0,73068,1,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Friendly"),
(@ENTRY,@SOURCETYPE,11,8,8,0,100,0,73068,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 1"),
(@ENTRY,@SOURCETYPE,12,0,25,0,100,0,0,0,0,0,2,45,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset - Reset Faction"),
(@ENTRY,@SOURCETYPE,13,0,7,0,100,0,0,0,0,0,2,45,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Faction");

UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE `entry`=5474;

SET @CGUID := 840944;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+11;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 5471, 1, 1, 1, 0, 1, -8427.62, -3088.25, 8.62604, 3.31743, 120, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+1, 5471, 1, 1, 1, 0, 1, -8387.89, -3094.43, 8.62499, 2.49748, 120, 0, 0, 1919, 0, 0, 0, 0, 0),
(@CGUID+2, 5471, 1, 1, 1, 0, 1, -8363.08, -3101.66, 8.64454, 3.24204, 120, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+3, 5471, 1, 1, 1, 0, 1, -8327.86, -3104.45, 8.63607, 2.60586, 120, 0, 0, 1919, 0, 0, 0, 0, 0),
(@CGUID+4, 5471, 1, 1, 1, 0, 1, -8289.16, -3119.33, 8.86648, 3.31743, 120, 0, 0, 1919, 0, 0, 0, 0, 0),
(@CGUID+5, 5471, 1, 1, 1, 0, 1, -8273.54, -3108.4, 8.81324, 4.94792, 120, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+6, 5471, 1, 1, 1, 0, 1, -8290.9, -3088.45, 8.62677, 5.9116, 120, 0, 0, 1919, 0, 0, 0, 0, 0),
(@CGUID+7, 5471, 1, 1, 1, 0, 1, -8318.27, -3064.44, 8.62538, 4.74293, 120, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+8, 5471, 1, 1, 1, 0, 1, -8310.47, -3042.54, 8.62574, 3.85936, 120, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+9, 5471, 1, 1, 1, 0, 1, -8301.12, -3017.89, 9.00249, 4.94792, 120, 0, 0, 1919, 0, 0, 0, 0, 0),
(@CGUID+10, 5471, 1, 1, 1, 0, 1, -8291.85, -2989.57, 8.63096, 3.83108, 120, 0, 0, 1919, 0, 0, 0, 0, 0),
(@CGUID+11, 5471, 1, 1, 1, 0, 1, -8275.93, -2975.32, 8.66363, 4.26698, 120, 0, 0, 1919, 0, 0, 0, 0, 0);

UPDATE `creature` SET `spawndist`=25, `MovementType`=1 WHERE `id`=5471;