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