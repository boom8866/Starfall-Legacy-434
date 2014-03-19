UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (769753, 770850, 769754, 770849);
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=12022 AND `id`=0;

DELETE FROM `creature_addon` WHERE `guid` IN (769753, 770850, 769754, 770849);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(769753, '49414'),
(770850, '49414'),
(769754, '49414'),
(770849, '49414');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` IN (28577, 28578, 27683, 27684);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 2619, 28577, 27373, 1, 66, 11),
(49416, 2619, 28578, 27373, 1, 66, 11),
(49416, 2619, 27683, 27373, 1, 66, 11),
(49416, 2619, 27684, 27373, 1, 66, 11);

DELETE FROM `spell_area` WHERE `spell` = '84481' AND `quest_start` = '27367';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(84481, 2619, 27367, 27368, 1, 66, 11);

UPDATE `creature_template` SET `InhabitType`=3, `flags_extra`=0 WHERE `entry`=8555;
UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid` IN (192783, 192796, 192790, 192791);

DELETE FROM `creature_addon` WHERE `guid` IN (192783, 192796, 192790, 192791);
INSERT INTO `creature_addon` (`guid`, `bytes1`, `emote`, `auras`) VALUES
(192783, 7, 65, '29266'),
(192796, 7, 65, '29266'),
(192790, 7, 65, '29266'),
(192791, 7, 65, '29266');

UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid` IN (192783, 192796, 192790, 192791);

DELETE FROM `creature_loot_template` WHERE `item` = '60983';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8558, 60983, -76.569, 1, 0, 1, 1),
(8557, 60983, -77.7324, 1, 0, 1, 1),
(8556, 60983, -74.4514, 1, 0, 1, 1),
(8555, 60983, -73.8597, 1, 0, 1, 1);

UPDATE `creature_template_addon` SET `auras`='49415 79976 79977 79972' WHERE `entry`=45429;

DELETE FROM `creature` WHERE `guid` = '400785';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(400785, 45431, 0, 1, 1, 0, 1, 2736.41, -2454.52, 68.6967, 3.36394, 300, 0, 0, 1478, 1534, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '400785';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400785, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27368';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 2619, 27368, 27369, 0, 0, 2, 1, 64, 11);

UPDATE `quest_template` SET `PrevQuestId`='27368' WHERE `Id`=27369;

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27371;
UPDATE `creature_template` SET `mindmg`=49, `maxdmg`=72, `attackpower`=18, `dmg_multiplier`=1.1 WHERE `entry` IN (45443, 45444);

-- Death's Step Putrifier
SET @ENTRY := 45443;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,6000,6000,11,79938,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Incinerate");

-- Death's Step Miscreation
SET @ENTRY := 45444;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,6000,6000,11,83019,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Toxic Waste");

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27370';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5446, 27370, 27372, -84902, 0, 2, 1, 66, 11);

DELETE FROM `spell_area` WHERE `spell` = '84902' AND `quest_start` = '27371';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(84902, 5446, 27371, 27372, 0, 0, 2, 1, 66, 11);

DELETE FROM `creature_equip_template` WHERE `entry` = '45445';
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(45445, 1, 57038, 0, 0);

-- Tarenar Sunstrike
SET @ENTRY := 45445;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might (Self)"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might (Owner)");

UPDATE `creature_template` SET `maxdmg`=59, `dmgschool`=82, `attackpower`=26, `dmg_multiplier`=1.5, `baseattacktime`=2000, `rangeattacktime`=2000, `npcflag`=2 WHERE `entry`=45445;

-- Tarenar Sunstrike
SET @ENTRY := 45445;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might (Self)"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might (Owner)"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invincible");

DELETE FROM `creature_involvedrelation` WHERE `id` = '45445' AND `quest` = '27371';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(45445, 27371);

DELETE FROM `creature_questrelation` WHERE `id` = '45445' AND `quest` = '27372';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(45445, 27372);

-- Tarenar Sunstrike
SET @ENTRY := 45445;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might (Self)"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might (Owner)"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invincible"),
(@ENTRY,@SOURCETYPE,4,0,19,0,100,0,27372,0,0,0,28,84902,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Remove Aura (Summon)"),
(@ENTRY,@SOURCETYPE,5,0,19,0,100,0,27372,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Despawn");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27372;

DELETE FROM `conditions` WHERE `SourceEntry` = '27373' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27373, 27369, 0),
(20, 8, 27373, 27372, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27373' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27373, 27369, 0),
(19, 8, 27373, 27372, 0);

UPDATE `quest_template` SET `PrevQuestId`='27372' WHERE `Id` IN (27555, 27557);
UPDATE `quest_template` SET `PrevQuestId`='27369' WHERE `Id`=27556;

DELETE FROM `creature_loot_template` WHERE `item` = '60986';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8596, 60986, -58.0017, 1, 0, 1, 1),
(8598, 60986, -0.9448, 1, 0, 1, 1);

UPDATE `quest_template` SET `Flags`=8192, `SpecialFlags`=1 WHERE `Id` IN (27555, 27556, 27557, 27558, 27559, 27560, 27561, 27562);

DELETE FROM `spell_group` WHERE `id` = '2619';
INSERT INTO `spell_group` (`id`, `spell_id`) VALUES
(2619, 85612),
(2619, 85613),
(2619, 85614),
(2619, 85615),
(2619, 85616),
(2619, 85617),
(2619, 85618),
(2619, 85619);

DELETE FROM `spell_group_stack_rules` WHERE `group_id` = '2619';
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
(2619, 1);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12035 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12035 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12035, 0, 0, 0, 9, 0, 27373, 0, 0, 0, 0, 0, '', 'Fiona\'s Caravan - Show gossip only if quest 27373 is active');

UPDATE `creature_template` SET `VehicleId`=1107 WHERE `entry`=45436;
UPDATE `creature_template` SET `VehicleId`=1108 WHERE `entry`=45437;
UPDATE `creature_template_addon` SET `auras`='49414' WHERE `entry`=45400;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45436';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45436, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45437';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45437, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (45437, 45436);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(45437, 46191, 1, 1, 'Caravan - Gidwin', 8, 0),
(45437, 46192, 3, 1, 'Caravan - Fiona', 8, 0),
(45437, 46193, 2, 1, 'Caravan - Tarenar', 8, 0),
(45436, 45434, 2, 1, 'Harness - Argyle', 8, 0),
(45436, 45433, 1, 1, 'Harness - Preston', 8, 0),
(45436, 45437, 0, 1, 'Harness - Caravan', 8, 0);

DELETE FROM `waypoints` WHERE `entry` = '45436';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45436, 1, 1933.48, -2854.75, 75.24, 'Fiona\'s Caravan 1 WP'),
(45436, 2, 1921.96, -2914.33, 75.50, 'Fiona\'s Caravan 1 WP'),
(45436, 3, 1892.51, -2957.45, 74.52, 'Fiona\'s Caravan 1 WP'),
(45436, 4, 1840.99, -3004.84, 73.67, 'Fiona\'s Caravan 1 WP'),
(45436, 5, 1785.28, -3089.93, 79.71, 'Fiona\'s Caravan 1 WP'),
(45436, 6, 1736.46, -3206.99, 86.78, 'Fiona\'s Caravan 1 WP'),
(45436, 7, 1716.30, -3320.82, 99.90, 'Fiona\'s Caravan 1 WP'),
(45436, 8, 1725.09, -3476.32, 129.82, 'Fiona\'s Caravan 1 WP'),
(45436, 9, 1746.25, -3602.31, 120.81, 'Fiona\'s Caravan 1 WP'),
(45436, 10, 1798.00, -3634.33, 123.57, 'Fiona\'s Caravan 1 WP'),
(45436, 11, 1845.98, -3649.63, 137.24, 'Fiona\'s Caravan 1 WP'),
(45436, 12, 1865.07, -3668.22, 150.20, 'Fiona\'s Caravan 1 WP'),
(45436, 13, 1867.67, -3692.37, 157.66, 'Fiona\'s Caravan 1 WP');

DELETE FROM `creature_text` WHERE `entry`=46193;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46193,0,0,'Shotgun!',12,0,100,0,0,0,'Comment'),
(46193,1,0,'Because I won our bet. And I called shotgun.',12,0,100,0,0,0,'Comment'),
(46193,2,0,'Fine. I killed five zombies. And they were huge. How many undead did you kill?',12,0,100,0,0,0,'Comment'),
(46193,3,0,'I\'m going to bet that you only killed four.',12,0,100,0,0,0,'Comment'),
(46193,4,0,'I didn\'t. You just told me!',12,0,100,0,0,0,'Comment'),
(46193,5,0,'So seriously, how did your undead hunting go? I want to hear stories.',12,0,100,0,0,0,'Comment'),
(46193,6,0,'Gidwin? Are you ignoring me?',12,0,100,0,0,0,'Comment'),
(46193,7,0,'Giddy... you\'re mad at me, aren\'t you?',12,0,100,0,0,0,'Comment'),
(46193,8,0,'Remember when we were kids, Gidwin? We would spend all day pretending to fight the trolls, or the murlocs, or the girls.',12,0,100,0,0,0,'Comment'),
(46193,9,0,'We had a name we called ourselves... what was it?',12,0,100,0,0,0,'Comment'),
(46193,10,0,'I\'m dead serious. I\'ve completely forgotten.',12,0,100,0,0,0,'Comment'),
(46193,11,0,'Actually, I agree with Fiona.',12,0,100,0,0,0,'Comment'),
(46193,12,0,'The Argent Crusade can wait for us a little while longer. Besides, our guest may want to get off the caravan soon.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=46191;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46191,0,0,'Hey now! Why do you get to sit in front?',12,0,100,0,0,0,'Comment'),
(46191,1,0,'Who says you won the bet? We haven\'t compared tallies yet.',12,0,100,0,0,0,'Comment'),
(46191,2,0,'I\'m pretty sure I killed six.',12,0,100,0,0,0,'Comment'),
(46191,3,0,'H... how did you know that?',12,0,100,0,0,0,'Comment'),
(46191,4,0,'Don\'t do this, Tarenar.',12,0,100,0,0,0,'Comment'),
(46191,5,0,'You remember damn well enough what it was.',12,0,100,0,0,0,'Comment'),
(46191,6,0,'<Sigh>... "The Paladin Pals".',12,0,100,0,0,0,'Comment'),
(46191,7,0,'Maybe now I don\'t want to. Maybe I like it better sitting back here with my new friend. It smells like horses up there.',12,0,100,0,0,0,'Comment'),
(46191,8,0,'We just rested a few minutes ago! Let\'s just go to Light\'s Hope Chapel!',12,0,100,0,0,0,'Comment'),
(46191,9,0,'We won\'t lose a horse. Look at them! They look exactly like they did when we started.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=46192;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46192,0,0,'Fiona laughs',16,0,100,0,0,0,'Comment'),
(46192,1,0,'Gidwin, you can sit in front with me next time.',12,0,100,0,0,0,'Comment'),
(46192,2,0,'There\'s a tower coming up on our left. What do you say we stop and rest a bit?',12,0,100,0,0,0,'Comment'),
(46192,3,0,'The roads here are rough, Gidwin. I don\'t want to risk losing a horse.',12,0,100,0,0,0,'Comment'),
(46192,4,0,'Here we are!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry` IN (45436, 45434, 45433, 45437, 46191, 46192, 46193);

DELETE FROM `creature_template_addon` WHERE `entry` IN (45436, 45437);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(45437, '60191'),
(45436, '60191');

-- Fiona
SET @ENTRY := 46192;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3000,3000,0,0,11,85610,32,0,0,0,0,11,45434,20,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Left Rope on Argyle"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,4000,4000,0,0,11,85611,32,0,0,0,0,11,45433,20,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Right Rope on Preston"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,46192,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,46192,0,0,45,0,8,0,0,0,0,11,46191,25,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 8 to Gidwin"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,46192,0,0,45,0,9,0,0,0,0,11,46191,25,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 9 to Gidwin"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,46192,0,0,45,0,10,0,0,0,0,11,46191,25,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 10 to Gidwin"),
(@ENTRY,@SOURCETYPE,9,10,38,0,100,0,0,4,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,33,45400,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

-- Gidwin Goldbraids
SET @ENTRY := 46191;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46191,0,0,45,0,1,0,0,0,0,11,46193,25,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Tarenar"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,46191,0,0,45,0,2,0,0,0,0,11,46193,25,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Tarenar"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,3,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,46191,0,0,45,0,3,0,0,0,0,11,46193,25,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Tarenar"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,4,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,46191,0,0,45,0,4,0,0,0,0,11,46193,25,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Tarenar"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,5,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,46191,0,0,45,0,5,0,0,0,0,11,46193,25,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 5 to Tarenar"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,6,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 5"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,5,46191,0,0,45,0,6,0,0,0,0,11,46193,25,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 6 to Tarenar"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,7,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Talk 6"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,6,46191,0,0,45,0,1,0,0,0,0,11,46192,25,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 1 to Fiona"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,8,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 8 - Talk 7"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,7,46191,0,0,45,0,2,0,0,0,0,11,46192,25,0,0.0,0.0,0.0,0.0,"After Talk 7 - Set Data 2 to Fiona"),
(@ENTRY,@SOURCETYPE,16,0,38,0,100,0,0,9,0,0,1,8,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 9 - Talk 8"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,8,46191,0,0,45,0,3,0,0,0,0,11,46192,25,0,0.0,0.0,0.0,0.0,"After Talk 8 - Set Data 3 to Fiona"),
(@ENTRY,@SOURCETYPE,18,0,38,0,100,0,0,10,0,0,1,9,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 9"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,9,46191,0,0,45,0,7,0,0,0,0,11,46193,25,0,0.0,0.0,0.0,0.0,"After Talk 9 - Set Data 7 to Tarenar");

-- Tarenar Sunstrike
SET @ENTRY := 46193;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,5000,5000,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46193,0,0,45,0,1,0,0,0,0,11,46191,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Gidwin"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,46193,0,0,45,0,2,0,0,0,0,11,46191,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Gidwin"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,46193,0,0,45,0,3,0,0,0,0,11,46191,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Gidwin"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,46193,0,0,45,0,4,0,0,0,0,11,46191,20,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Gidwin"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,4,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,46193,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,46193,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,6,46193,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,7,46193,0,0,1,8,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,8,46193,0,0,45,0,5,0,0,0,0,11,46191,20,0,0.0,0.0,0.0,0.0,"After Talk 8 - Set Data 5 to Gidwin"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,5,0,0,1,9,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 9"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,9,46193,0,0,45,0,6,0,0,0,0,11,46191,20,0,0.0,0.0,0.0,0.0,"After Talk 9 - Set Data 6 to Gidwin"),
(@ENTRY,@SOURCETYPE,16,0,38,0,100,0,0,6,0,0,1,10,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 10"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,10,46193,0,0,45,0,7,0,0,0,0,11,46191,20,0,0.0,0.0,0.0,0.0,"After Talk 10 - Set Data 7 to Gidwin"),
(@ENTRY,@SOURCETYPE,18,0,38,0,100,0,0,7,0,0,1,11,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Talk 11"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,11,46193,0,0,1,12,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 11 - Talk 12");

-- Fiona's Caravan
SET @ENTRY := 45437;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,2000,2000,0,0,86,46598,0,18,50,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker");

-- Fiona's Caravan Harness
SET @ENTRY := 45436;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,45436,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,12,0,0,0,45,0,4,0,0,0,0,11,46192,25,0,0.0,0.0,0.0,0.0,"On WP Reached 12 - Set Data 4 to Fiona"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,13,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - Remove All Passengers"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,13,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - Force Despawn");

-- Fiona's Caravan
SET @ENTRY := 45400;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12035,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12035,0,0,0,85,84897,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Caravan"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12035,2,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,12035,2,0,0,85,85066,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Caravan"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12035,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12035,1,0,0,85,85393,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Caravan");

-- Fiona
SET @ENTRY := 45417;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27373,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,27487,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Despawn All Summons");

SET @CGUID := 400800;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+6;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45429, 0, 1, 1, 0, 1, 1854.23, -3708.65, 160.585, 1.26377, 300, 0, 0, 1535, 1587, 0, 0, 0, 0),
(@CGUID+1, 45431, 0, 1, 1, 0, 1, 1866.83, -3699.26, 158.445, 2.82537, 300, 0, 0, 1478, 1534, 0, 0, 0, 0),
(@CGUID+2, 45417, 0, 1, 1, 0, 0, 1844.24, -3691.39, 158.33, 4.47477, 300, 0, 0, 1478, 1534, 0, 0, 0, 0),
(@CGUID+3, 45434, 0, 1, 1, 0, 0, 1844.94, -3695.19, 158.707, 0.637212, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+4, 45433, 0, 1, 1, 0, 0, 1845.94, -3696.18, 158.708, 0.739313, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+5, 45416, 0, 1, 1, 0, 0, 1842.46, -3698.09, 158.683, 0.676482, 300, 0, 0, 1848, 0, 0, 16777216, 0, 0),
(@CGUID+6, 45400, 0, 1, 1, 0, 0, 1842.28, -3698.27, 158.68, 0.637205, 300, 0, 0, 1848, 0, 0, 16777219, 0, 0);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27373';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 2263, 27373, 27448, 1, 66, 11);

UPDATE `creature` SET `spawndist`=20, `MovementType`=1 WHERE `guid`=193393;
UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `guid`=400801;

DELETE FROM `creature_addon` WHERE `guid` IN (400800, 400801);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400800, '49414'),
(400801, '49414');

UPDATE `quest_template` SET `PrevQuestId`='27373' WHERE `Id`=27381;
UPDATE `quest_template` SET `PrevQuestId`='27382' WHERE `Id`=27448;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12034 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12034;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12034, 0, 0, 0, 9, 0, 27381, 0, 0, 0, 0, 0, '', 'Argus Highbeacon - Show gossip only if quest 27381 is active');

-- Argus Highbeacon
SET @ENTRY := 45451;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12034,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12034,0,0,0,33,45501,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Complete");

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=193086;

-- The Lone Hunter
SET @ENTRY := 45450;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,5000,22000,25000,11,3604,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Tendon Rip"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,3000,30000,30000,11,3264,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Blood Howl"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,2000,20000,20000,11,32901,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Carnivorous Bite"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,28,81238,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Remove Dead State Cosmetic");

UPDATE `creature_template` SET `mindmg`=52, `maxdmg`=78, `attackpower`=19, `dmg_multiplier`=1.1 WHERE `entry` IN (47064, 45453);
UPDATE `quest_template` SET `PrevQuestId`='27386' WHERE `Id` IN (27387, 27388,  27389);

-- Blighthound
SET @ENTRY := 45453;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,0,0,11,16577,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Disease Cloud"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,5500,9500,11,13445,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rend");

UPDATE `quest_template` SET `PrevQuestId`='27382' WHERE `Id`=27560;
UPDATE `gossip_menu_option` SET `id`=0, `option_text`='Carlin, do you have the extended Annals of Darrowshire?', `option_id`=1, `npc_option_npcflag`=1 WHERE  `menu_id`=3864 AND `id`=2;

DELETE FROM `conditions` WHERE `SourceGroup`=3864;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 3864, 0, 0, 0, 9, 0, 27388, 0, 0, 0, 0, 0, '', 'Carlin Redpath - Show gossip only if quest 27388 is active');

-- Carlin Redpath
SET @ENTRY := 11063;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,3864,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,56,13202,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=11063;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(11063,0,0,'Why yes... does Chromie need this? I suppose she would.',12,0,100,0,0,0,'Comment'),
(11063,0,1,'Yes, you may have it. Feel free to leaf through the pages. Inside you will find the history of Darrowshire, and the details of the events that led to the deaths of so very many men.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=11289;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(11289,0,0,'Fight for your families! Don\'t give up!',12,0,100,0,0,0,'Comment'),
(11289,0,1,'Fight! Fight for Darrowshire!',12,0,100,0,0,0,'Comment'),
(11289,0,2,'If we fall, then Darrowshire is doomed!',12,0,100,0,0,0,'Comment'),
(11289,0,3,'Our captain has fallen!',12,0,100,0,0,0,'Comment'),
(11289,0,4,'We must not give up!',12,0,100,0,0,0,'Comment'),
(11289,0,5,'The Alliance has abandoned us!',12,0,100,0,0,0,'Comment'),
(11289,0,6,'Where is the Silver Hand? We need their help!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=11288;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(11288,0,0,'Your soul is doomed!',12,0,100,0,0,0,'Comment'),
(11288,0,1,'Hail the Lich King!',12,0,100,0,0,0,'Comment'),
(11288,0,2,'Join us, or fall forever!',12,0,100,0,0,0,'Comment'),
(11288,0,3,'Scourge will prevail!',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `orientation`=3.71 WHERE `guid`=193487;
UPDATE `creature` SET `position_x`=2089.45, `position_y`=-3788.52, `position_z`=133.73, `orientation`=4.29 WHERE `guid`=193483;
UPDATE `gameobject` SET `spawntimesecs`=60 WHERE `id` IN (176208, 176591, 176209, 176865);
DELETE FROM `creature_template_addon` WHERE `entry` IN (11289, 11288, 11620, 11621);
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (11289, 11288, 11620, 11621);

-- Spectral Betrayer
SET @ENTRY := 11288;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,5000,7000,10000,11,5337,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Spectral Betrayer - In Combat - Cast Wither Strike"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,2000,4500,2000,4500,5,36,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote (Attack)"),
(@ENTRY,@SOURCETYPE,2,0,1,0,75,0,2000,4500,2000,4500,5,43,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote (Block)"),
(@ENTRY,@SOURCETYPE,3,0,1,0,10,0,2000,4500,2000,4500,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,60,0,100,1,2000,2000,0,0,17,333,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Set Combat Emote State"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Shattered Sword of Marduk
SET @ENTRY := 176209;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,0,50,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 5 to Creatures");

-- Horgus' Skull
SET @ENTRY := 176208;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,0,50,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 5 to Creatures");

-- Spectral Marauder
SET @ENTRY := 11620;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Spectral Corpse
SET @ENTRY := 11621;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Spectral Defender
SET @ENTRY := 11289;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,5000,5000,8000,11,11976,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Spectral Defender - In Combat - Cast Strike"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,7000,7000,10000,11,12169,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Spectral Defender - In Combat - Cast Shield Block"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,2000,4500,2000,4500,5,36,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote (Attack)"),
(@ENTRY,@SOURCETYPE,3,0,1,0,10,0,2000,4500,2000,4500,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,1,0,75,0,2000,4500,2000,4500,5,43,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote (Block)"),
(@ENTRY,@SOURCETYPE,5,0,60,0,100,1,2000,2000,0,0,17,333,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Set Combat Emote State"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn"),
(@ENTRY,@SOURCETYPE,7,0,60,0,100,1,2000,2000,0,0,11,17327,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Cast Spirit Particles");

DELETE FROM `creature_loot_template` WHERE `item` = '61037';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8546, 61037, 51.821, 1, 0, 1, 1),
(8550, 61037, 51.6524, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '84973';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 84973, 0, 0, 31, 0, 3, 45475, 0, 0, 0, '', 'Overcharge');

-- Plague Disseminator
SET @ENTRY := 45475;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,84972,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,1500,1500,1500,1500,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Die");

DELETE FROM `spell_script_names` WHERE `spell_id` = '84973';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84973, 'spell_overcharge_effect');

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=45485;

-- Necropolis Flowers
SET @ENTRY := 45485;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,84961,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Add Flowers");

DELETE FROM `spell_script_names` WHERE `spell_id` = '84964';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84964, 'spell_raynes_seed');

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid` IN (722157, 727155);

DELETE FROM `creature` WHERE `guid`=400817;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(400817, 10948, 0, 1, 1, 0, 1, 1443.76, -3699.77, 77.3144, 0.699189, 300, 0, 0, 3758, 0, 0, 0, 0, 0);

DELETE FROM `creature_text` WHERE `entry`=10948;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(10948,0,0,'Darrowshire, to arms! The Scourge approach!',14,0,100,0,0,0,'Comment'),
(10948,1,0,'Help Joseph Carlin\'s troops defend Darrowshire!',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `faction_A`=1920, `faction_H`=1920 WHERE `entry` IN (10948, 10944, 10937);

DELETE FROM `creature_text` WHERE `entry`=10944;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(10944,0,0,'Do not lose hope, Darrowshire! We will not fail!',14,0,100,0,0,0,'Comment'),
(10944,1,0,'Davil Lightfire joined the battle! Protect him!',41,0,100,0,0,0,'Comment'),
(10944,2,0,'Horgus, your nightmare ends! Now!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=10937;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(10937,0,0,'Captain Redpath has appeared on the battlefield! Protect him!',41,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=10938;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(10938,0,0,'Captain Joseph Redpath has been corrupted! Kill him quickly!',41,0,100,0,0,0,'Comment'),
(10938,1,0,'Speak with Joseph Redpath in the center of Darrowshire.',41,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=10936;

-- Relic Bundle
SET @ENTRY := 177526;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,25000,25000,0,0,12,10944,3,90000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Davil Lightfire"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,5000,5000,0,0,45,0,1,0,0,0,0,10,400817,10948,0,0.0,0.0,0.0,0.0,"Update - Set Data 1 to Defender");

-- Darrowshire Defender
SET @ENTRY := 10948;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,5000,5000,8000,11,11976,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Darrowshire Defender - In Combat - Cast Strike"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,7000,7000,10000,11,12169,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Darrowshire Defender - In Combat - Cast Shield Block"),
(@ENTRY,@SOURCETYPE,2,17,38,0,100,0,0,1,0,0,1,0,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,10948,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,10948,0,0,12,10948,3,300000,0,0,0,8,0,0,0,1489.94,-3685.92,80.44,0.54,"After Talk 0 - Summon Guard"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,10948,0,0,12,10948,3,300000,0,0,0,8,0,0,0,1495.33,-3687.0,80.44,0.54,"After Talk 0 - Summon Guard"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,0,10948,0,0,12,10948,3,300000,0,0,0,8,0,0,0,1483.33,-3681.0,79.46,0.66,"After Talk 0 - Summon Guard"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,10948,0,0,12,10948,3,300000,0,0,0,8,0,0,0,1479.84,-3676.3,79.4,0.73,"After Talk 0 - Summon Guard"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,0,10948,0,0,12,10948,3,300000,0,0,0,8,0,0,0,1469.84,-3673.43,78.8,0.73,"After Talk 0 - Summon Guard"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,0,10948,0,0,12,10948,3,300000,0,0,0,8,0,0,0,1466.35,-3666.42,79.22,6.04,"After Talk 0 - Summon Guard"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,0,10948,0,0,12,10948,8,120000,0,0,0,8,0,0,0,1467.22,-3699.99,79.04,0.47,"After Talk 0 - Summon Guard"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,0,10948,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Run"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,0,10948,0,0,69,0,0,0,0,0,0,8,0,0,0,1483.05,-3677.55,79.64,0.4,"After Talk 0 - Move to Pos"),
(@ENTRY,@SOURCETYPE,13,0,54,0,50,0,0,0,0,0,12,10952,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Spawn Skeletons"),
(@ENTRY,@SOURCETYPE,14,0,60,0,20,0,12500,21500,12500,21500,12,10952,3,30000,0,1,0,8,0,0,0,1488.7,-3661.33,81.76,3.71,"Update (Summon Marauding Skeleton)"),
(@ENTRY,@SOURCETYPE,15,0,60,0,20,0,12500,21500,12500,21500,12,10952,3,30000,0,1,0,8,0,0,0,1504.11,-3683.0,82.13,3.41,"Update (Summon Marauding Skeleton)"),
(@ENTRY,@SOURCETYPE,16,0,60,0,20,0,12500,21500,12500,21500,12,10951,3,30000,0,1,0,8,0,0,0,1494.04,-3673.75,81.04,3.49,"Update (Summon Marauding Corpse)"),
(@ENTRY,@SOURCETYPE,17,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,18,0,60,1,100,1,15000,15000,0,0,0,10944,4,120000,0,0,0,8,0,0,0,1458.49,-3689.26,76.92,0.57,"Update (1.5 minutes) - Summon Davil Lightfire"),
(@ENTRY,@SOURCETYPE,19,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,20,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Davil Lightfire
SET @ENTRY := 10944;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,17232,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Davil Lightfire - On Aggro - Cast Devotion Aura"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,7000,8000,10000,11,17284,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Davil Lightfire - In Combat - Cast Holy Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,8000,11000,15000,20000,11,13005,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Davil Lightfire - In Combat - Cast Hammer of Justice"),
(@ENTRY,@SOURCETYPE,3,0,37,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,1,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,1484.97,-3677.74,79.82,6.13,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,1,0,10944,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,1,1,10944,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,7,0,60,0,85,0,12500,21500,12500,21500,0,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Update - None"),
(@ENTRY,@SOURCETYPE,8,0,60,0,100,1,15000,15000,95000,95000,12,10946,4,30000,0,1,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Horgus the Ravager"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,1,0,1,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,1,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,1,1,10944,0,0,74,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Remove Timed Event");

-- Horgus the Ravager
SET @ENTRY := 10946;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,1000,1000,0,0,11,17467,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Horgus the Ravager - Out Of Combat - Cast Unholy Aura"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,5000,6000,8000,11,3391,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Horgus the Ravager - In Combat - Cast Thrash"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,8000,11000,9000,12000,11,15608,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Horgus the Ravager - In Combat - Cast Ravenous Claw"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,1,0,0,0,0,45,0,1,0,0,0,0,11,10944,40,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 1 to Davil"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,12,10937,3,120000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon Redpath");

-- Marauding Corpse
SET @ENTRY := 10951;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,5000,5000,8000,11,13584,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Marauding Corpse - In Combat - Cast Strike"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,10948,60,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Defenders"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Marauding Skeleton
SET @ENTRY := 10952;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4000,12000,15000,11,9080,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Marauding Skeleton - In Combat - Cast Hamstring"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,7000,15000,18000,11,11972,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Marauding Skeleton - In Combat - Cast Shield Bash"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,10948,60,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Defender"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Captain Redpath
SET @ENTRY := 10937;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,7000,8000,10000,11,15284,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Captain Redpath - In Combat - Cast Cleave"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,10000,14000,18000,11,6253,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Captain Redpath - In Combat - Cast Backhand"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,5000,15000,20000,11,9128,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Captain Redpath - In Combat - Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,1,0,20000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,2000,2000,2000,2000,49,0,0,0,0,0,0,11,10952,50,0,0.0,0.0,0.0,0.0,"OOC - Attack Skeletons"),
(@ENTRY,@SOURCETYPE,5,6,52,0,100,0,0,10937,0,0,12,10938,3,120000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Redpath the Corrupted"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,7,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

-- Redpath the Corrupted
SET @ENTRY := 10938;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,5000,5000,7000,11,15580,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Redpath the Corrupted - In Combat - Cast Strike"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,10000,14000,18000,11,6253,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Redpath the Corrupted - In Combat - Cast Backhand"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,5000,15000,20000,11,16244,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Redpath the Corrupted - In Combat - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,5000,7000,9000,14000,11,12542,1,0,0,0,0,6,0,0,0,0.0,0.0,0.0,0.0,"Redpath the Corrupted - In Combat - Cast Fear"),
(@ENTRY,@SOURCETYPE,4,0,60,0,100,1,45000,45000,600000,600000,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Die"),
(@ENTRY,@SOURCETYPE,5,0,60,0,100,1,45000,45000,60000,60000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,6,7,6,0,100,0,0,0,0,0,1,1,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 1"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"Link - Set Data 5 to All Creatures in Area"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,12,10936,3,90000,0,0,0,8,0,0,0,1444.01,-3699.99,77.32,0.52,"Link - Summon Joseph Redpath");

-- Joseph Redpath
SET @ENTRY := 10936;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,33,10936,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Complete"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,10936,0,0,45,0,1,0,0,0,0,11,10926,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Pamela"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,10936,0,0,45,0,2,0,0,0,0,11,10926,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Pamela"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2");

DELETE FROM `creature_text` WHERE `entry`=10926;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(10926,0,0,'Daddy! You\'re back!',12,0,100,0,0,0,'Comment'),
(10926,1,0,'Let\'s go play! No, tell me a story, Daddy! No... let\'s go pick flowers! And play tea time! I found my dollie, did I tell you? ',12,0,100,0,0,0,'Comment'),
(10926,2,0,'I missed you so much, Daddy!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=10936;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(10936,0,0,'Pamela? Are you there, honey?',12,0,100,0,0,0,'Comment'),
(10936,1,0,'Hahah!',12,0,100,0,0,0,'Comment'),
(10936,2,0,'I missed you too, honey. And I\'m finally home...',12,0,100,0,0,0,'Comment');

-- Pamela Redpath
SET @ENTRY := 10926;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27390,0,0,0,12,10936,3,60000,0,0,0,8,0,0,0,1459.02,-3598.12,86.95,2.22,"On Quest Rewarded - Summon Joseph"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,27390,0,0,0,45,0,1,0,0,0,0,11,10936,30,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Joseph"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,10926,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,10926,0,0,45,0,2,0,0,0,0,11,10936,30,0,0.0,0.0,0.0,0.0,"After Talk 1- Set Data 2 to Joseph"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,10926,0,0,45,0,3,0,0,0,0,11,10936,30,0,0.0,0.0,0.0,0.0,"After Talk 2- Set Data 3 to Joseph");

UPDATE `creature_template` SET `faction_A`=974, `faction_H`=974, `attackpower`=1, `dmg_multiplier`=1, `Health_mod`=1, `mindmg`=45, `maxdmg`=78 WHERE `entry`=10938;
UPDATE `quest_template` SET `PrevQuestId`='27391' WHERE `Id`=27558;
UPDATE `quest_template` SET `PrevQuestId`='27522' WHERE `Id`=27532;
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=12034 AND `id`=2;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12035 AND `id`=2;

DELETE FROM `conditions` WHERE `SourceGroup`=12035 AND `SourceEntry` = '2';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12035, 2, 0, 0, 9, 0, 27448, 0, 0, 0, 0, 0, '', 'Fiona\'s Caravan - Show gossip only if quest 27448 is active');

UPDATE `creature_template` SET `VehicleId`=1107 WHERE `entry`=45542;
UPDATE `creature_template` SET `VehicleId`=1109 WHERE `entry`=45547;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45542';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45542, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45547';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45547, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (45542, 45547);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(45547, 45677, 1, 1, 'Caravan - Gidwin', 8, 0),
(45547, 45959, 3, 1, 'Caravan - Fiona', 8, 0),
(45547, 45678, 4, 1, 'Caravan - Tarenar', 8, 0),
(45547, 45958, 2, 1, 'Caravan - Argus', 8, 0),
(45542, 45434, 2, 1, 'Harness - Argyle', 8, 0),
(45542, 45433, 1, 1, 'Harness - Preston', 8, 0),
(45542, 45547, 0, 1, 'Harness - Caravan', 8, 0);

UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry` IN (45547, 45542, 45433, 45434, 45958, 45678, 45959, 45677);

DELETE FROM `creature_text` WHERE `entry`=45677;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45677,0,0,'This hardly seems fair!',12,0,100,0,0,0,'Comment'),
(45677,1,0,'Why do I have to sit up top with all the stuff?!',12,0,100,0,0,0,'Comment'),
(45677,2,0,'Hey! I oughtta bounce one of the trunks off of your head, Tarenar.',12,0,100,0,0,0,'Comment'),
(45677,3,0,'Oh, shut up you dolt. YOU probably want to kiss her a hundred times.',12,0,100,0,0,0,'Comment'),
(45677,4,0,'If you don\'t mind my askin\', what do you do that requires walking so much?',12,0,100,0,0,0,'Comment'),
(45677,5,0,'So you\'re part of the Argent Crusade, eh?',12,0,100,0,0,0,'Comment'),
(45677,6,0,'Think you can put in the good word for us? We\'re looking to join the order.',12,0,100,0,0,0,'Comment'),
(45677,7,0,'NOOOOOOO! Stopped again!',12,0,100,0,0,0,'Comment'),
(45677,8,0,'Walking, eh...?',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45959;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45959,0,0,'Because you\'re the bravest, dear.',12,0,100,0,0,0,'Comment'),
(45959,1,0,'I know I promised you the front seat, Giddy, but we have an elderly guest. I\'m sorry.',12,0,100,0,0,0,'Comment'),
(45959,2,0,'Do you normally walk these roads alone?',12,0,100,0,0,0,'Comment'),
(45959,3,0,'Of course I\'m not just going to drop you off, Master Hightower. We\'ll be happy to wait for you.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45678;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45678,0,0,'Because you\'re short.',12,0,100,0,0,0,'Comment'),
(45678,1,0,'Fiona, I must warn you: Gidwin only wants to sit in front because he wants to kiss you.',12,0,100,0,0,0,'Comment'),
(45678,2,0,'Do not!',14,0,100,0,0,0,'Comment'),
(45678,3,0,'Noble work.',12,0,100,0,0,0,'Comment'),
(45678,4,0,'Whoah... he lets you call him Max?',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45958;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45958,0,0,'Ahem! I, ah, appreciate the ride, Madam Fiona. It\'s nice to get off my feet for once.',12,0,100,0,0,0,'Comment'),
(45958,1,0,'Yes, I do, thought it was easier when I was younger. These days, I have to be more careful.',12,0,100,0,0,0,'Comment'),
(45958,2,0,'I service the five Argent towers. Mostly repairs and maintenance, and some minor magical work.',12,0,100,0,0,0,'Comment'),
(45958,3,0,'Without proper upkeep, buildings within the plaguelands tend to... waste away.',12,0,100,0,0,0,'Comment'),
(45958,4,0,'I find it satisfying. I enjoy working with my hands.',12,0,100,0,0,0,'Comment'),
(45958,5,0,'By the way, if any of you need anything repaired, let me know. I am at your service.',12,0,100,0,0,0,'Comment'),
(45958,6,0,'Certainly. I don\'t make it out to Light\'s Hope very often anymore, but when you arrive, tell Max Tyrosus that I sent you.',12,0,100,0,0,0,'Comment'),
(45958,7,0,'Ma\'am, would you mind dropping me off at Light\'s Shield Tower, just up ahead? I have to stop here.',12,0,100,0,0,0,'Comment'),
(45958,8,0,'Light\'s Hope isn\'t far, young paladin. Might I suggest walking?',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '45542';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45542, 1, 1866.63, -3672.35, 152.46, 'Fiona\'s Caravan WP 2'),
(45542, 2, 1856.34, -3656.76, 142.84, 'Fiona\'s Caravan WP 2'),
(45542, 3, 1812.53, -3636.48, 125.89, 'Fiona\'s Caravan WP 2'),
(45542, 4, 1771.21, -3639.36, 120.86, 'Fiona\'s Caravan WP 2'),
(45542, 5, 1753.89, -3652.01, 120.03, 'Fiona\'s Caravan WP 2'),
(45542, 6, 1742.06, -3761.41, 127.70, 'Fiona\'s Caravan WP 2'),
(45542, 7, 1752.35, -3846.65, 124.03, 'Fiona\'s Caravan WP 2'),
(45542, 8, 1774.36, -3911.01, 130.18, 'Fiona\'s Caravan WP 2'),
(45542, 9, 1828.54, -4057.76, 106.96, 'Fiona\'s Caravan WP 2'),
(45542, 10, 1873.07, -4168.66, 103.49, 'Fiona\'s Caravan WP 2'),
(45542, 11, 1895.40, -4234.73, 87.02, 'Fiona\'s Caravan WP 2'),
(45542, 12, 2064.89, -4264.59, 80.31, 'Fiona\'s Caravan WP 2'),
(45542, 13, 2206.46, -4322.85, 76.08, 'Fiona\'s Caravan WP 2'),
(45542, 14, 2243.33, -4370.94, 98.21, 'Fiona\'s Caravan WP 2'),
(45542, 15, 2254.47, -4417.20, 111.72, 'Fiona\'s Caravan WP 2');

-- Fiona's Caravan
SET @ENTRY := 45547;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,2000,2000,0,0,86,46598,0,18,50,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker");

-- Fiona's Caravan Harness
SET @ENTRY := 45542;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,45542,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,13,0,0,0,45,0,5,0,0,0,0,11,45677,25,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - Set Data 5 to Gidwin"),
(@ENTRY,@SOURCETYPE,2,3,38,0,100,0,0,1,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Passengers"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,33,45400,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Gidwin Goldbraids
SET @ENTRY := 45677;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,5000,5000,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45677,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,45677,0,0,45,0,1,0,0,0,0,11,45959,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Fiona"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,45677,0,0,45,0,2,0,0,0,0,11,45959,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Fiona"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45677,0,0,45,0,3,0,0,0,0,11,45678,20,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Tarenar"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,3,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,45677,0,0,45,0,3,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 3 to Argus"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,4,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,45677,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,6,45677,0,0,45,0,5,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 5 to Argus"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,5,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 7"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,7,45677,0,0,45,0,7,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 7 - Set Data 7 to Argus"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,6,0,0,1,8,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 8"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,8,45677,0,0,45,0,1,0,0,0,0,11,45542,20,0,0.0,0.0,0.0,0.0,"After Talk 8 - Set Data 1 to Harness");

-- Tarenar Sunstrike
SET @ENTRY := 45678;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45678,0,0,45,0,1,0,0,0,0,11,45677,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Gidwin"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45678,0,0,45,0,2,0,0,0,0,11,45677,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Gidwin"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,3,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45678,0,0,45,0,1,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Argus"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,4,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,45678,0,0,45,0,4,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Argus"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,5,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,45678,0,0,45,0,6,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 6 to Argus");

-- Argus Highbeacon
SET @ENTRY := 45958;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45958,0,0,45,0,3,0,0,0,0,11,45959,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 3 to Fiona"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45958,0,0,45,0,3,0,0,0,0,11,45677,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 3 to Gidwin"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,3,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45958,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45958,0,0,45,0,4,0,0,0,0,11,45678,20,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Tarenar"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,4,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,45958,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,5,45958,0,0,45,0,4,0,0,0,0,11,45677,20,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 4 to Gidwin"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,5,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,6,45958,0,0,45,0,5,0,0,0,0,11,45678,20,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 5 to Tarenar"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,6,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,3,45958,0,0,45,0,4,0,0,0,0,11,45959,20,0,0.0,0.0,0.0,0.0,"After Talk 7 - Set Data 4 to Fiona"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,7,0,0,1,8,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,8,45958,0,0,45,0,6,0,0,0,0,11,45677,20,0,0.0,0.0,0.0,0.0,"After Talk 8 - Set Data 6 to Gidwin");

-- Fiona
SET @ENTRY := 45959;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45959,0,0,45,0,1,0,0,0,0,11,45678,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Tarenar"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45959,0,0,45,0,2,0,0,0,0,11,45678,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Tarenar"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,3,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45959,0,0,45,0,2,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Argus"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,4,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3");

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27448';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5448, 27448, 27455, 1, 66, 11);

DELETE FROM `creature_template_addon` WHERE `entry` IN (45433, 45434);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(45433, '49414'),
(45434, '49414');

SET @CGUID := 400820;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+6;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45433, 0, 1, 1, 0, 0, 2272.88, -4423.55, 111.731, 2.00028, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+1, 45434, 0, 1, 1, 0, 0, 2271.66, -4424.11, 111.731, 2.00028, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+2, 45417, 0, 1, 1, 0, 0, 2277.75, -4424.08, 111.732, 2.44795, 300, 0, 0, 1478, 1534, 0, 0, 0, 0),
(@CGUID+3, 45400, 0, 1, 1, 0, 0, 2273.85, -4427.27, 111.732, 2.00766, 300, 0, 0, 1848, 0, 0, 16777219, 0, 0),
(@CGUID+4, 45416, 0, 1, 1, 0, 0, 2273.85, -4427.27, 111.732, 2.00766, 300, 0, 0, 1848, 0, 0, 16777216, 0, 0),
(@CGUID+5, 45429, 0, 1, 1, 0, 1, 2269.83, -5278.92, 81.4738, 1.58892, 300, 0, 0, 1535, 1587, 0, 0, 0, 0),
(@CGUID+6, 45431, 0, 1, 1, 0, 1, 2270.68, -5286.65, 82.1973, 1.58732, 300, 0, 0, 1478, 1534, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (400825, 400826);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400825, '49414'),
(400826, '49414');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27455';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 2268, 27455, 27465, 1, 66, 11);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (27451, 27452);
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry` IN (45650, 45655, 45657);

-- Plague Puffer
SET @ENTRY := 45650;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,56,61292,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Infectis Incher
SET @ENTRY := 45655;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,56,61293,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Infectis Scuttler
SET @ENTRY := 45657;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,56,61294,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `creature_loot_template` WHERE `item` = '61280';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8548, 61280, -28.1484, 1, 0, 1, 1),
(8551, 61280, -28.6079, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `item` = '61281';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8551, 61281, -28.2831, 1, 0, 1, 1),
(8548, 61281, -28.6097, 1, 0, 1, 1);

UPDATE `creature_template` SET `mindmg`=58, `maxdmg`=86, `attackpower`=22 WHERE `entry`=45664;

DELETE FROM `spell_script_names` WHERE `spell_id` = '85144';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85144, 'spell_gather_liquid_sample');

UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=2 WHERE `Id`=27454;
UPDATE `creature_template` SET `mindmg`=45, `maxdmg`=68, `attackpower`=17 WHERE `entry`=1843;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12043';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(12043, 0, 0, 'Put in a drop of liquid, as Betina requested.', 1, 1, 0, 0, 0, 0, NULL),
(12043, 1, 0, 'Throw in an entire flask.', 1, 1, 0, 0, 0, 0, NULL),
(12043, 2, 0, 'Throw in all 12 flasks.', 1, 1, 0, 0, 0, 0, NULL);

-- Mereldar Plague Cauldron
SET @ENTRY := 205485;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,12043,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select (Option 1) - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,15,27454,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,2,1,62,0,100,0,12043,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip (Option 2)"),
(@ENTRY,@SOURCETYPE,3,1,62,0,100,0,12043,2,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip (Option 3)"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12043,1,0,0,85,85172,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select (Option 2) - Cast Explosion Light"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12043,2,0,0,85,85173,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select (Option 3) - Cast Explosion Huge");

DELETE FROM `conditions` WHERE `SourceGroup`=12043;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12043, 0, 0, 0, 9, 0, 27454, 0, 0, 0, 0, 0, '', 'Mereldar Plague Cauldron - Show gossip only if quest 27454 is active'),
(15, 12043, 1, 0, 0, 9, 0, 27454, 0, 0, 0, 0, 0, '', 'Mereldar Plague Cauldron - Show gossip only if quest 27454 is active'),
(15, 12043, 2, 0, 0, 9, 0, 27454, 0, 0, 0, 0, 0, '', 'Mereldar Plague Cauldron - Show gossip only if quest 27454 is active');

UPDATE `creature_template` SET `dmg_multiplier`=1 WHERE `entry`=9447;
UPDATE `quest_template` SET `PrevQuestId`='27460' WHERE `Id` IN (27461, 27462);
UPDATE `quest_template` SET `PrevQuestId`='27462' WHERE `Id` IN (27614, 27615, 27616, 27619);
UPDATE `quest_template` SET `PrevQuestId`='27461' WHERE `Id` IN (27613, 27612);
UPDATE `quest_template` SET `PrevQuestId`='27464' WHERE `Id`=27467;

DELETE FROM `spell_area` WHERE `spell` = '84481' AND `quest_start` = '27463';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(84481, 2268, 27463, 1, 66, 0);

UPDATE `creature_template` SET `mindmg`=58, `maxdmg`=89, `attackpower`=22 WHERE `entry`=46167;

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '27460';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65141, 2266, 27460, 27620, 1, 64, 11);

UPDATE `creature` SET `phaseMask`=3 WHERE `id` IN (9449, 9452, 6547, 9540, 9451, 9448);
UPDATE `gameobject` SET `phaseMask`=3 WHERE `id` IN (205880, 205878, 205881, 205879);
UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=205878;

-- Argent Portal
SET @ENTRY := 205876;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,33,46102,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,85,52096,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Portal Effect");

-- Argent Portal
SET @ENTRY := 205877;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,33,46103,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,85,52096,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Portal Effect");

DELETE FROM `gameobject_loot_template` WHERE `item` IN (61959, 61960, 61961, 61962);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(2265, 61959, -20.8384, 1, 0, 1, 1),
(2265, 61960, -20.8928, 1, 0, 1, 1),
(2265, 61961, -20.8942, 1, 0, 1, 1),
(2265, 61962, -20.9274, 1, 0, 1, 1),
(34748, 61959, -100, 1, 0, 1, 1),
(34749, 61960, -100, 1, 0, 1, 1),
(34750, 61961, -100, 1, 0, 1, 1),
(34751, 61962, -100, 1, 0, 1, 1);

UPDATE `creature_template` SET `minlevel`=42, `maxlevel`=42, `faction_A`=14, `faction_H`=14, `mindmg`=58, `maxdmg`=62, `attackpower`=22, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (46092, 46094, 46093, 46095, 46096);
UPDATE `creature_template` SET `lootid`=46093 WHERE `entry`=46093;
UPDATE `creature_template` SET `lootid`=46094 WHERE `entry`=46094;
UPDATE `creature_template` SET `lootid`=46092 WHERE `entry`=46092;
UPDATE `creature_template` SET `lootid`=46095 WHERE `entry`=46095;
UPDATE `creature_template` SET `lootid`=46096 WHERE `entry`=46096;

-- Scarlet Commander Marjhan
SET @ENTRY := 46092;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79976,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Retribution Aura"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6000,6000,11,79970,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Divine Storm"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,7500,7500,15000,15000,11,79971,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hammer of Wrath");

-- Huntsman Leopold
SET @ENTRY := 46094;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,80004,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Snake Trap"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,8500,8500,11,80003,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Black Arrow"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,5000,5000,11,79721,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosive Shot"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3000,3000,4000,4000,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

-- Mataus the Wrathcaster
SET @ENTRY := 46093;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,18266,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Curse of Agony"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,20000,20000,20000,20000,11,18266,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Curse of Agony"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,7500,7500,11,9613,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3000,3000,12500,12500,11,17173,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Drain Life"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,11500,11500,11500,11500,11,85800,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadowflame");

-- Rohan the Assassin
SET @ENTRY := 46095;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,11,34189,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Stealth"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,90783,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Deadly Throw"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,4000,4000,11,37685,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Backstab"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,2000,2000,5500,5500,11,30478,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hemorrhage");

-- Crusader Lord Valdelmar
SET @ENTRY := 46096;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,17232,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Devotion Aura"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,14517,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Crusader Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,5000,15500,15500,11,13005,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hammer of Justice");

DELETE FROM `creature_loot_template` WHERE `entry` IN (46092, 46093, 46094, 46095, 46096);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(46092, 866, 0.0819, 1, 0, 1, 1),
(46092, 1625, 0.0682, 1, 0, 1, 1),
(46092, 1640, 0.0819, 1, 0, 1, 1),
(46092, 1645, 5.5, 1, 0, 1, 1),
(46092, 1685, 0.0136, 1, 0, 1, 1),
(46092, 3187, 0.0269, 1, 0, 1, 1),
(46092, 3395, 0.0273, 1, 0, 1, 1),
(46092, 3419, 12.5, 1, 0, 1, 1),
(46092, 3430, 0.0273, 1, 0, 1, 1),
(46092, 3869, 0.0136, 1, 0, 1, 1),
(46092, 3914, 0.2, 1, 0, 1, 1),
(46092, 3928, 3.5344, 1, 0, 1, 1),
(46092, 3936, 0.05, 1, 0, 1, 1),
(46092, 3937, 0.2456, 1, 0, 1, 1),
(46092, 3938, 0.1, 1, 0, 1, 1),
(46092, 3939, 0.1, 1, 0, 1, 1),
(46092, 3940, 0.1883, 1, 0, 1, 1),
(46092, 3941, 0.1614, 1, 0, 1, 1),
(46092, 3942, 0.1501, 1, 0, 1, 1),
(46092, 3943, 0.1365, 1, 0, 1, 1),
(46092, 3962, 0.1774, 1, 0, 1, 1),
(46092, 3963, 0.1365, 1, 0, 1, 1),
(46092, 3964, 0.1, 1, 0, 1, 1),
(46092, 3965, 0.2729, 1, 0, 1, 1),
(46092, 3966, 0.3139, 1, 0, 1, 1),
(46092, 3968, 0.1638, 1, 0, 1, 1),
(46092, 3986, 0.1, 1, 0, 1, 1),
(46092, 3989, 0.1638, 1, 0, 1, 1),
(46092, 4000, 0.05, 1, 0, 1, 1),
(46092, 4001, 0.1, 1, 0, 1, 1),
(46092, 4002, 0.05, 1, 0, 1, 1),
(46092, 4003, 0.1501, 1, 0, 1, 1),
(46092, 4004, 0.1, 1, 0, 1, 1),
(46092, 4005, 0.1076, 1, 0, 1, 1),
(46092, 4006, 0.1228, 1, 0, 1, 1),
(46092, 4007, 0.0807, 1, 0, 1, 1),
(46092, 4017, 0.1, 1, 0, 1, 1),
(46092, 4018, 0.05, 1, 0, 1, 1),
(46092, 4019, 0.3684, 1, 0, 1, 1),
(46092, 4020, 0.2, 1, 0, 1, 1),
(46092, 4021, 0.2456, 1, 0, 1, 1),
(46092, 4022, 0.1, 1, 0, 1, 1),
(46092, 4023, 0.1, 1, 0, 1, 1),
(46092, 4024, 0.2456, 1, 0, 1, 1),
(46092, 4025, 0.3002, 1, 0, 1, 1),
(46092, 4026, 0.1, 1, 0, 1, 1),
(46092, 4046, 0.0136, 1, 0, 1, 1),
(46092, 4047, 0.0273, 1, 0, 1, 1),
(46092, 4058, 0.0273, 1, 0, 1, 1),
(46092, 4061, 0.0409, 1, 0, 1, 1),
(46092, 4063, 0.0136, 1, 0, 1, 1),
(46092, 4068, 0.0136, 1, 0, 1, 1),
(46092, 4083, 0.0136, 1, 0, 1, 1),
(46092, 4087, 0.0819, 1, 0, 1, 1),
(46092, 4306, 23, 1, 0, 1, 2),
(46092, 4338, 53.4389, 1, 0, 1, 1),
(46092, 4608, 10.0437, 1, 0, 1, 1),
(46092, 4637, 0.1365, 1, 0, 1, 1),
(46092, 4734, 0.0136, 1, 0, 1, 1),
(46092, 4735, 0.0136, 1, 0, 1, 1),
(46092, 4736, 0.1228, 1, 0, 1, 1),
(46092, 4738, 0.0136, 1, 0, 1, 1),
(46092, 5215, 0.1638, 1, 0, 1, 1),
(46092, 6149, 1.6376, 1, 0, 1, 1),
(46092, 6415, 0.0136, 1, 0, 1, 1),
(46092, 6424, 0.0409, 1, 0, 1, 1),
(46092, 6425, 0.0546, 1, 0, 1, 1),
(46092, 6426, 0.0136, 1, 0, 1, 1),
(46092, 6432, 0.0409, 1, 0, 1, 1),
(46092, 6433, 0.0136, 1, 0, 1, 1),
(46092, 7112, 0.0136, 1, 0, 1, 1),
(46092, 7468, 0.0136, 1, 0, 1, 1),
(46092, 7470, 0.0136, 1, 0, 1, 1),
(46092, 7471, 0.0409, 1, 0, 1, 1),
(46092, 7472, 0.0136, 1, 0, 1, 1),
(46092, 7473, 0.0273, 1, 0, 1, 1),
(46092, 7478, 0.1638, 1, 0, 1, 1),
(46092, 7479, 0.0409, 1, 0, 1, 1),
(46092, 7480, 0.0409, 1, 0, 1, 1),
(46092, 7481, 0.0273, 1, 0, 1, 1),
(46092, 7482, 0.0273, 1, 0, 1, 1),
(46092, 7484, 0.0273, 1, 0, 1, 1),
(46092, 7485, 0.0136, 1, 0, 1, 1),
(46092, 7486, 0.0136, 1, 0, 1, 1),
(46092, 7487, 0.0409, 1, 0, 1, 1),
(46092, 7488, 0.0136, 1, 0, 1, 1),
(46092, 7490, 0.0273, 1, 0, 1, 1),
(46092, 7491, 0.0136, 1, 0, 1, 1),
(46092, 7495, 0.0682, 1, 0, 1, 1),
(46092, 7496, 0.0273, 1, 0, 1, 1),
(46092, 7524, 0.0136, 1, 0, 1, 1),
(46092, 7533, 0.0136, 1, 0, 1, 1),
(46092, 7545, 0.0136, 1, 0, 1, 1),
(46092, 7552, 0.0273, 1, 0, 1, 1),
(46092, 7610, 0.0136, 1, 0, 1, 1),
(46092, 7990, 0.0136, 1, 0, 1, 1),
(46092, 7993, 0.0136, 1, 0, 1, 1),
(46092, 8029, 0.0273, 1, 0, 1, 1),
(46092, 8140, 0.0136, 1, 0, 1, 1),
(46092, 8157, 0.0273, 1, 0, 1, 1),
(46092, 8194, 0.0136, 1, 0, 1, 1),
(46092, 8196, 0.0136, 1, 0, 1, 1),
(46092, 8749, 0.05, 1, 0, 1, 1),
(46092, 8750, 0.1, 1, 0, 1, 1),
(46092, 8751, 0.05, 1, 0, 1, 1),
(46092, 9287, 0.0273, 1, 0, 1, 1),
(46092, 9290, 0.0273, 1, 0, 1, 1),
(46092, 9292, 0.0409, 1, 0, 1, 1),
(46092, 9293, 0.0136, 1, 0, 1, 1),
(46092, 9874, 0.0273, 1, 0, 1, 1),
(46092, 9878, 0.0136, 1, 0, 1, 1),
(46092, 9881, 0.0136, 1, 0, 1, 1),
(46092, 9883, 0.0682, 1, 0, 1, 1),
(46092, 9893, 0.0136, 1, 0, 1, 1),
(46092, 9894, 0.0273, 1, 0, 1, 1),
(46092, 9897, 0.0136, 1, 0, 1, 1),
(46092, 9899, 0.0136, 1, 0, 1, 1),
(46092, 9903, 0.0273, 1, 0, 1, 1),
(46092, 9906, 0.1228, 1, 0, 1, 1),
(46092, 9907, 0.0136, 1, 0, 1, 1),
(46092, 9908, 0.0136, 1, 0, 1, 1),
(46092, 9915, 0.0273, 1, 0, 1, 1),
(46092, 9917, 0.0136, 1, 0, 1, 1),
(46092, 9918, 0.0136, 1, 0, 1, 1),
(46092, 9919, 0.0546, 1, 0, 1, 1),
(46092, 9921, 0.0136, 1, 0, 1, 1),
(46092, 9927, 0.0409, 1, 0, 1, 1),
(46092, 9929, 0.0273, 1, 0, 1, 1),
(46092, 9931, 0.0409, 1, 0, 1, 1),
(46092, 9932, 0.0273, 1, 0, 1, 1),
(46092, 9934, 0.0136, 1, 0, 1, 1),
(46092, 9959, 0.0136, 1, 0, 1, 1),
(46092, 9966, 0.0136, 1, 0, 1, 1),
(46092, 9968, 0.0273, 1, 0, 1, 1),
(46092, 9972, 0.0273, 1, 0, 1, 1),
(46092, 10302, 0.0136, 1, 0, 1, 1),
(46092, 10312, 0.0273, 1, 0, 1, 1),
(46092, 10606, 0.0136, 1, 0, 1, 1),
(46092, 11202, 0.0136, 1, 0, 1, 1),
(46092, 11973, 0.0819, 1, 0, 1, 1),
(46092, 11998, 0.1092, 1, 0, 1, 1),
(46092, 12011, 0.0136, 1, 0, 1, 1),
(46092, 12022, 0.0136, 1, 0, 1, 1),
(46092, 12042, 0.0819, 1, 0, 1, 1),
(46092, 12808, 1.5557, 1, 0, 1, 1),
(46092, 13064, 0.0273, 1, 0, 1, 1),
(46092, 15244, 0.0819, 1, 0, 1, 1),
(46092, 15251, 0.0546, 1, 0, 1, 1),
(46092, 21940, 0.0273, 1, 0, 1, 1),
(46092, 21944, 0.0682, 1, 0, 1, 1),
(46092, 61387, 9.0748, 1, 0, 1, 1),
(46093, 866, 0.116, 1, 0, 1, 1),
(46093, 1613, 0.3046, 1, 0, 1, 1),
(46093, 1625, 0.0435, 1, 0, 1, 1),
(46093, 1640, 0.087, 1, 0, 1, 1),
(46093, 1645, 5.5547, 1, 0, 1, 1),
(46093, 1982, 0.0145, 1, 0, 1, 1),
(46093, 3419, 22.2222, 1, 0, 1, 1),
(46093, 3914, 0.2, 1, 0, 1, 1),
(46093, 3928, 22.2222, 1, 0, 1, 1),
(46093, 3936, 0.139, 1, 0, 1, 1),
(46093, 3937, 0.174, 1, 0, 1, 1),
(46093, 3938, 0.2321, 1, 0, 1, 1),
(46093, 3939, 0.05, 1, 0, 1, 1),
(46093, 3940, 0.05, 1, 0, 1, 1),
(46093, 3941, 0.139, 1, 0, 1, 1),
(46093, 3942, 0.174, 1, 0, 1, 1),
(46093, 3943, 0.139, 1, 0, 1, 1),
(46093, 3961, 0.174, 1, 0, 1, 1),
(46093, 3963, 0.05, 1, 0, 1, 1),
(46093, 3964, 0.1595, 1, 0, 1, 1),
(46093, 3965, 0.1305, 1, 0, 1, 1),
(46093, 3966, 0.05, 1, 0, 1, 1),
(46093, 3967, 0.145, 1, 0, 1, 1),
(46093, 3968, 0.1, 1, 0, 1, 1),
(46093, 3986, 0.174, 1, 0, 1, 1),
(46093, 3989, 0.05, 1, 0, 1, 1),
(46093, 4001, 0.116, 1, 0, 1, 1),
(46093, 4002, 0.116, 1, 0, 1, 1),
(46093, 4003, 0.1305, 1, 0, 1, 1),
(46093, 4005, 0.116, 1, 0, 1, 1),
(46093, 4006, 0.05, 1, 0, 1, 1),
(46093, 4007, 0.0834, 1, 0, 1, 1),
(46093, 4017, 0.3046, 1, 0, 1, 1),
(46093, 4018, 0.2, 1, 0, 1, 1),
(46093, 4019, 0.1, 1, 0, 1, 1),
(46093, 4020, 0.4351, 1, 0, 1, 1),
(46093, 4021, 0.3771, 1, 0, 1, 1),
(46093, 4022, 0.2321, 1, 0, 1, 1),
(46093, 4023, 0.2, 1, 0, 1, 1),
(46093, 4024, 0.2224, 1, 0, 1, 1),
(46093, 4025, 0.1, 1, 0, 1, 1),
(46093, 4045, 0.029, 1, 0, 1, 1),
(46093, 4046, 0.0145, 1, 0, 1, 1),
(46093, 4047, 0.0145, 1, 0, 1, 1),
(46093, 4058, 0.0145, 1, 0, 1, 1),
(46093, 4061, 0.058, 1, 0, 1, 1),
(46093, 4062, 0.0435, 1, 0, 1, 1),
(46093, 4068, 0.0145, 1, 0, 1, 1),
(46093, 4083, 0.0145, 1, 0, 1, 1),
(46093, 4087, 0.087, 1, 0, 1, 1),
(46093, 4306, 22.4, 1, 0, 1, 2),
(46093, 4338, 52.7194, 1, 0, 1, 1),
(46093, 4608, 10.0508, 1, 0, 1, 1),
(46093, 4637, 0.203, 1, 0, 1, 1),
(46093, 4735, 0.0435, 1, 0, 1, 1),
(46093, 4736, 0.029, 1, 0, 1, 1),
(46093, 4737, 0.0145, 1, 0, 1, 1),
(46093, 4738, 0.0145, 1, 0, 1, 1),
(46093, 5215, 0.0725, 1, 0, 1, 1),
(46093, 5216, 0.0278, 1, 0, 1, 1),
(46093, 5974, 0.0145, 1, 0, 1, 1),
(46093, 6149, 1.6, 1, 0, 1, 1),
(46093, 6424, 0.0145, 1, 0, 1, 1),
(46093, 6428, 0.0145, 1, 0, 1, 1),
(46093, 6429, 0.0145, 1, 0, 1, 1),
(46093, 6431, 0.029, 1, 0, 1, 1),
(46093, 6432, 0.0145, 1, 0, 1, 1),
(46093, 7332, 0.058, 1, 0, 1, 1),
(46093, 7469, 0.0145, 1, 0, 1, 1),
(46093, 7470, 0.116, 1, 0, 1, 1),
(46093, 7471, 0.029, 1, 0, 1, 1),
(46093, 7473, 0.029, 1, 0, 1, 1),
(46093, 7475, 0.058, 1, 0, 1, 1),
(46093, 7479, 0.029, 1, 0, 1, 1),
(46093, 7480, 0.0145, 1, 0, 1, 1),
(46093, 7481, 0.0435, 1, 0, 1, 1),
(46093, 7482, 0.058, 1, 0, 1, 1),
(46093, 7485, 0.0145, 1, 0, 1, 1),
(46093, 7486, 0.1015, 1, 0, 1, 1),
(46093, 7487, 0.2321, 1, 0, 1, 1),
(46093, 7488, 0.0145, 1, 0, 1, 1),
(46093, 7491, 0.0145, 1, 0, 1, 1),
(46093, 7494, 0.0145, 1, 0, 1, 1),
(46093, 7495, 0.029, 1, 0, 1, 1),
(46093, 7496, 0.029, 1, 0, 1, 1),
(46093, 7524, 0.0145, 1, 0, 1, 1),
(46093, 7525, 0.0435, 1, 0, 1, 1),
(46093, 7533, 0.0145, 1, 0, 1, 1),
(46093, 7545, 0.0145, 1, 0, 1, 1),
(46093, 7552, 0.0145, 1, 0, 1, 1),
(46093, 7555, 0.029, 1, 0, 1, 1),
(46093, 7909, 0.3, 1, 0, 1, 1),
(46093, 7910, 0.2, 1, 0, 1, 1),
(46093, 7976, 0.0145, 1, 0, 1, 1),
(46093, 8120, 0.0145, 1, 0, 1, 1),
(46093, 8139, 0.0145, 1, 0, 1, 1),
(46093, 8140, 0.029, 1, 0, 1, 1),
(46093, 8142, 0.0145, 1, 0, 1, 1),
(46093, 8157, 0.0145, 1, 0, 1, 1),
(46093, 8162, 0.029, 1, 0, 1, 1),
(46093, 8194, 0.0435, 1, 0, 1, 1),
(46093, 8196, 0.029, 1, 0, 1, 1),
(46093, 8749, 0.3771, 1, 0, 1, 1),
(46093, 8750, 0.1, 1, 0, 1, 1),
(46093, 8751, 0.1, 1, 0, 1, 1),
(46093, 9285, 0.0145, 1, 0, 1, 1),
(46093, 9287, 0.0145, 1, 0, 1, 1),
(46093, 9288, 0.0435, 1, 0, 1, 1),
(46093, 9290, 0.029, 1, 0, 1, 1),
(46093, 9291, 0.029, 1, 0, 1, 1),
(46093, 9292, 0.029, 1, 0, 1, 1),
(46093, 9293, 0.029, 1, 0, 1, 1),
(46093, 9881, 0.0145, 1, 0, 1, 1),
(46093, 9883, 0.1015, 1, 0, 1, 1),
(46093, 9884, 0.0145, 1, 0, 1, 1),
(46093, 9893, 0.0435, 1, 0, 1, 1),
(46093, 9897, 0.0435, 1, 0, 1, 1),
(46093, 9899, 0.029, 1, 0, 1, 1),
(46093, 9902, 0.029, 1, 0, 1, 1),
(46093, 9903, 0.0725, 1, 0, 1, 1),
(46093, 9904, 0.0145, 1, 0, 1, 1),
(46093, 9907, 0.029, 1, 0, 1, 1),
(46093, 9910, 0.0145, 1, 0, 1, 1),
(46093, 9917, 0.029, 1, 0, 1, 1),
(46093, 9919, 0.029, 1, 0, 1, 1),
(46093, 9921, 0.0145, 1, 0, 1, 1),
(46093, 9926, 0.0145, 1, 0, 1, 1),
(46093, 9927, 0.058, 1, 0, 1, 1),
(46093, 9935, 0.0145, 1, 0, 1, 1),
(46093, 9959, 0.0145, 1, 0, 1, 1),
(46093, 9967, 0.0145, 1, 0, 1, 1),
(46093, 9968, 0.029, 1, 0, 1, 1),
(46093, 9969, 0.0435, 1, 0, 1, 1),
(46093, 9970, 0.029, 1, 0, 1, 1),
(46093, 9971, 0.058, 1, 0, 1, 1),
(46093, 9972, 0.029, 1, 0, 1, 1),
(46093, 9973, 0.029, 1, 0, 1, 1),
(46093, 10301, 0.0145, 1, 0, 1, 1),
(46093, 11168, 0.0145, 1, 0, 1, 1),
(46093, 11973, 0.0435, 1, 0, 1, 1),
(46093, 11987, 0.029, 1, 0, 1, 1),
(46093, 11998, 0.029, 1, 0, 1, 1),
(46093, 12011, 0.029, 1, 0, 1, 1),
(46093, 12022, 0.029, 1, 0, 1, 1),
(46093, 12031, 0.0145, 1, 0, 1, 1),
(46093, 12042, 0.0145, 1, 0, 1, 1),
(46093, 12808, 1.6244, 1, 0, 1, 1),
(46093, 13199, 0.0145, 1, 0, 1, 1),
(46093, 15215, 0.0435, 1, 0, 1, 1),
(46093, 15244, 0.0435, 1, 0, 1, 1),
(46093, 15251, 0.087, 1, 0, 1, 1),
(46093, 24231, 0.0145, 1, 0, 1, 1),
(46093, 61387, 9.4126, 1, 0, 1, 1),
(46094, 866, 0.0597, 1, 0, 1, 1),
(46094, 1625, 0.0298, 1, 0, 1, 1),
(46094, 1640, 0.0149, 1, 0, 1, 1),
(46094, 1645, 5.5365, 1, 0, 1, 1),
(46094, 1685, 0.0149, 1, 0, 1, 1),
(46094, 1722, 0.0149, 1, 0, 1, 1),
(46094, 3187, 0.1194, 1, 0, 1, 1),
(46094, 3419, 35, 1, 0, 1, 1),
(46094, 3914, 0.2, 1, 0, 1, 1),
(46094, 3928, 15, 1, 0, 1, 1),
(46094, 3936, 0.1343, 1, 0, 1, 1),
(46094, 3937, 0.1, 1, 0, 1, 1),
(46094, 3938, 0.1, 1, 0, 1, 1),
(46094, 3939, 0.1, 1, 0, 1, 1),
(46094, 3940, 0.1, 1, 0, 1, 1),
(46094, 3941, 0.1791, 1, 0, 1, 1),
(46094, 3942, 0.2238, 1, 0, 1, 1),
(46094, 3961, 0.1, 1, 0, 1, 1),
(46094, 3962, 0.1791, 1, 0, 1, 1),
(46094, 3963, 0.05, 1, 0, 1, 1),
(46094, 3964, 0.2238, 1, 0, 1, 1),
(46094, 3965, 0.1343, 1, 0, 1, 1),
(46094, 3966, 0.2, 1, 0, 1, 1),
(46094, 3967, 0.1, 1, 0, 1, 1),
(46094, 3968, 0.1741, 1, 0, 1, 1),
(46094, 3986, 0.2089, 1, 0, 1, 1),
(46094, 3989, 0.2238, 1, 0, 1, 1),
(46094, 4000, 0.1343, 1, 0, 1, 1),
(46094, 4001, 0.05, 1, 0, 1, 1),
(46094, 4002, 0.1791, 1, 0, 1, 1),
(46094, 4003, 0.1791, 1, 0, 1, 1),
(46094, 4004, 0.1, 1, 0, 1, 1),
(46094, 4005, 0.1343, 1, 0, 1, 1),
(46094, 4006, 0.1343, 1, 0, 1, 1),
(46094, 4007, 0.1642, 1, 0, 1, 1),
(46094, 4017, 0.2985, 1, 0, 1, 1),
(46094, 4018, 0.3134, 1, 0, 1, 1),
(46094, 4019, 0.1, 1, 0, 1, 1),
(46094, 4020, 0.2985, 1, 0, 1, 1),
(46094, 4021, 0.1, 1, 0, 1, 1),
(46094, 4022, 0.1, 1, 0, 1, 1),
(46094, 4023, 0.1, 1, 0, 1, 1),
(46094, 4024, 0.2611, 1, 0, 1, 1),
(46094, 4025, 0.2686, 1, 0, 1, 1),
(46094, 4026, 0.2835, 1, 0, 1, 1),
(46094, 4045, 0.0746, 1, 0, 1, 1),
(46094, 4046, 0.0149, 1, 0, 1, 1),
(46094, 4058, 0.0448, 1, 0, 1, 1),
(46094, 4061, 0.0298, 1, 0, 1, 1),
(46094, 4063, 0.0149, 1, 0, 1, 1),
(46094, 4068, 0.0149, 1, 0, 1, 1),
(46094, 4080, 0.0149, 1, 0, 1, 1),
(46094, 4083, 0.0149, 1, 0, 1, 1),
(46094, 4087, 0.0746, 1, 0, 1, 1),
(46094, 4306, 20.7, 1, 0, 1, 2),
(46094, 4338, 52.6638, 1, 0, 1, 1),
(46094, 4416, 0.0149, 1, 0, 1, 1),
(46094, 4608, 9.8045, 1, 0, 1, 1),
(46094, 4637, 0.2089, 1, 0, 1, 1),
(46094, 4734, 0.0597, 1, 0, 1, 1),
(46094, 4736, 0.0597, 1, 0, 1, 1),
(46094, 4737, 0.0149, 1, 0, 1, 1),
(46094, 4738, 0.0298, 1, 0, 1, 1),
(46094, 5215, 0.0895, 1, 0, 1, 1),
(46094, 5216, 0.0149, 1, 0, 1, 1),
(46094, 6411, 0.0298, 1, 0, 1, 1),
(46094, 6415, 0.0149, 1, 0, 1, 1),
(46094, 6424, 0.1492, 1, 0, 1, 1),
(46094, 6426, 0.1194, 1, 0, 1, 1),
(46094, 6433, 0.0149, 1, 0, 1, 1),
(46094, 7086, 0.0149, 1, 0, 1, 1),
(46094, 7469, 0.0298, 1, 0, 1, 1),
(46094, 7470, 0.0597, 1, 0, 1, 1),
(46094, 7471, 0.0746, 1, 0, 1, 1),
(46094, 7472, 0.0298, 1, 0, 1, 1),
(46094, 7473, 0.1791, 1, 0, 1, 1),
(46094, 7478, 0.0298, 1, 0, 1, 1),
(46094, 7479, 0.0149, 1, 0, 1, 1),
(46094, 7481, 0.0298, 1, 0, 1, 1),
(46094, 7482, 0.0448, 1, 0, 1, 1),
(46094, 7485, 0.0448, 1, 0, 1, 1),
(46094, 7486, 0.0149, 1, 0, 1, 1),
(46094, 7487, 0.0149, 1, 0, 1, 1),
(46094, 7488, 0.0298, 1, 0, 1, 1),
(46094, 7490, 0.0448, 1, 0, 1, 1),
(46094, 7491, 0.0448, 1, 0, 1, 1),
(46094, 7495, 0.0149, 1, 0, 1, 1),
(46094, 7534, 0.0149, 1, 0, 1, 1),
(46094, 7610, 0.0298, 1, 0, 1, 1),
(46094, 7909, 0.1, 1, 0, 1, 1),
(46094, 7910, 0.05, 1, 0, 1, 1),
(46094, 7976, 0.0149, 1, 0, 1, 1),
(46094, 7990, 0.0149, 1, 0, 1, 1),
(46094, 8137, 0.0298, 1, 0, 1, 1),
(46094, 8157, 0.0597, 1, 0, 1, 1),
(46094, 8162, 0.1194, 1, 0, 1, 1),
(46094, 8163, 0.0149, 1, 0, 1, 1),
(46094, 8194, 0.0298, 1, 0, 1, 1),
(46094, 8196, 0.0298, 1, 0, 1, 1),
(46094, 8749, 0.2, 1, 0, 1, 1),
(46094, 8750, 0.1, 1, 0, 1, 1),
(46094, 8751, 0.116, 1, 0, 1, 1),
(46094, 9285, 0.0895, 1, 0, 1, 1),
(46094, 9286, 0.0149, 1, 0, 1, 1),
(46094, 9287, 0.0597, 1, 0, 1, 1),
(46094, 9288, 0.0448, 1, 0, 1, 1),
(46094, 9289, 0.2537, 1, 0, 1, 1),
(46094, 9292, 0.0149, 1, 0, 1, 1),
(46094, 9293, 0.0149, 1, 0, 1, 1),
(46094, 9434, 0.0149, 1, 0, 1, 1),
(46094, 9874, 0.0298, 1, 0, 1, 1),
(46094, 9878, 0.0298, 1, 0, 1, 1),
(46094, 9882, 0.0149, 1, 0, 1, 1),
(46094, 9883, 0.0448, 1, 0, 1, 1),
(46094, 9887, 0.0298, 1, 0, 1, 1),
(46094, 9893, 0.1343, 1, 0, 1, 1),
(46094, 9894, 0.0149, 1, 0, 1, 1),
(46094, 9897, 0.0597, 1, 0, 1, 1),
(46094, 9902, 0.0149, 1, 0, 1, 1),
(46094, 9903, 0.0149, 1, 0, 1, 1),
(46094, 9904, 0.0149, 1, 0, 1, 1),
(46094, 9908, 0.0298, 1, 0, 1, 1),
(46094, 9912, 0.0746, 1, 0, 1, 1),
(46094, 9916, 0.0298, 1, 0, 1, 1),
(46094, 9917, 0.0448, 1, 0, 1, 1),
(46094, 9919, 0.0298, 1, 0, 1, 1),
(46094, 9926, 0.0149, 1, 0, 1, 1),
(46094, 9927, 0.0448, 1, 0, 1, 1),
(46094, 9928, 0.0149, 1, 0, 1, 1),
(46094, 9929, 0.0448, 1, 0, 1, 1),
(46094, 9930, 0.0298, 1, 0, 1, 1),
(46094, 9967, 0.0149, 1, 0, 1, 1),
(46094, 9968, 0.0298, 1, 0, 1, 1),
(46094, 9969, 0.0149, 1, 0, 1, 1),
(46094, 9971, 0.0149, 1, 0, 1, 1),
(46094, 9972, 0.0298, 1, 0, 1, 1),
(46094, 9973, 0.0149, 1, 0, 1, 1),
(46094, 10089, 0.0298, 1, 0, 1, 1),
(46094, 10094, 0.0149, 1, 0, 1, 1),
(46094, 10300, 0.0149, 1, 0, 1, 1),
(46094, 10302, 0.0149, 1, 0, 1, 1),
(46094, 11202, 0.0149, 1, 0, 1, 1),
(46094, 11998, 0.0597, 1, 0, 1, 1),
(46094, 12022, 0.0298, 1, 0, 1, 1),
(46094, 12031, 0.0149, 1, 0, 1, 1),
(46094, 12042, 0.0149, 1, 0, 1, 1),
(46094, 12808, 1.4326, 1, 0, 1, 1),
(46094, 13068, 0.0298, 1, 0, 1, 1),
(46094, 13095, 0.0149, 1, 0, 1, 1),
(46094, 13138, 0.0149, 1, 0, 1, 1),
(46094, 13199, 0.0149, 1, 0, 1, 1),
(46094, 15215, 0.0298, 1, 0, 1, 1),
(46094, 15244, 0.0597, 1, 0, 1, 1),
(46094, 15251, 0.0298, 1, 0, 1, 1),
(46094, 61387, 9.327, 1, 0, 1, 1),
(46095, 866, 0.1044, 1, 0, 1, 1),
(46095, 1613, 0.0746, 1, 0, 1, 1),
(46095, 1625, 0.1492, 1, 0, 1, 1),
(46095, 1640, 0.0746, 1, 0, 1, 1),
(46095, 1645, 5.6849, 1, 0, 1, 1),
(46095, 1685, 0.0149, 1, 0, 1, 1),
(46095, 1982, 0.0149, 1, 0, 1, 1),
(46095, 2825, 0.0149, 1, 0, 1, 1),
(46095, 3419, 4.5455, 1, 0, 1, 1),
(46095, 3928, 13.6364, 1, 0, 1, 1),
(46095, 3936, 0.1343, 1, 0, 1, 1),
(46095, 3937, 0.1, 1, 0, 1, 1),
(46095, 3938, 0.5073, 1, 0, 1, 1),
(46095, 3939, 1.5047, 1, 0, 1, 1),
(46095, 3940, 0.1641, 1, 0, 1, 1),
(46095, 3941, 0.05, 1, 0, 1, 1),
(46095, 3942, 0.1641, 1, 0, 1, 1),
(46095, 3962, 0.1641, 1, 0, 1, 1),
(46095, 3963, 0.1, 1, 0, 1, 1),
(46095, 3964, 0.2537, 1, 0, 1, 1),
(46095, 3965, 0.194, 1, 0, 1, 1),
(46095, 3966, 0.2, 1, 0, 1, 1),
(46095, 3967, 0.1492, 1, 0, 1, 1),
(46095, 3968, 0.2984, 1, 0, 1, 1),
(46095, 3986, 0.1806, 1, 0, 1, 1),
(46095, 3989, 0.3283, 1, 0, 1, 1),
(46095, 4000, 0.05, 1, 0, 1, 1),
(46095, 4001, 0.1492, 1, 0, 1, 1),
(46095, 4002, 0.1492, 1, 0, 1, 1),
(46095, 4003, 0.1791, 1, 0, 1, 1),
(46095, 4005, 0.1, 1, 0, 1, 1),
(46095, 4006, 0.1343, 1, 0, 1, 1),
(46095, 4007, 0.05, 1, 0, 1, 1),
(46095, 4017, 0.2, 1, 0, 1, 1),
(46095, 4018, 0.05, 1, 0, 1, 1),
(46095, 4019, 0.2984, 1, 0, 1, 1),
(46095, 4020, 0.2835, 1, 0, 1, 1),
(46095, 4021, 3.0093, 1, 0, 1, 1),
(46095, 4022, 0.2686, 1, 0, 1, 1),
(46095, 4023, 3.3103, 1, 0, 1, 1),
(46095, 4024, 0.2537, 1, 0, 1, 1),
(46095, 4025, 0.3133, 1, 0, 1, 1),
(46095, 4026, 0.05, 1, 0, 1, 1),
(46095, 4045, 0.0298, 1, 0, 1, 1),
(46095, 4047, 0.0149, 1, 0, 1, 1),
(46095, 4058, 0.0149, 1, 0, 1, 1),
(46095, 4063, 0.0298, 1, 0, 1, 1),
(46095, 4080, 0.0149, 1, 0, 1, 1),
(46095, 4087, 0.0597, 1, 0, 1, 1),
(46095, 4306, 21, 1, 0, 1, 2),
(46095, 4338, 53.0737, 1, 0, 1, 1),
(46095, 4608, 9.624, 1, 0, 1, 1),
(46095, 4637, 0.3133, 1, 0, 1, 1),
(46095, 4734, 0.0149, 1, 0, 1, 1),
(46095, 4735, 0.1194, 1, 0, 1, 1),
(46095, 4736, 0.0298, 1, 0, 1, 1),
(46095, 4737, 0.0149, 1, 0, 1, 1),
(46095, 5215, 0.0597, 1, 0, 1, 1),
(46095, 5216, 0.0448, 1, 0, 1, 1),
(46095, 6149, 1.6264, 1, 0, 1, 1),
(46095, 6415, 0.0149, 1, 0, 1, 1),
(46095, 6426, 0.0746, 1, 0, 1, 1),
(46095, 6429, 0.0149, 1, 0, 1, 1),
(46095, 6431, 0.0448, 1, 0, 1, 1),
(46095, 6432, 0.0448, 1, 0, 1, 1),
(46095, 6433, 0.0149, 1, 0, 1, 1),
(46095, 7469, 0.0746, 1, 0, 1, 1),
(46095, 7470, 0.0448, 1, 0, 1, 1),
(46095, 7471, 0.0149, 1, 0, 1, 1),
(46095, 7473, 0.0298, 1, 0, 1, 1),
(46095, 7475, 0.0448, 1, 0, 1, 1),
(46095, 7478, 0.0149, 1, 0, 1, 1),
(46095, 7479, 0.0149, 1, 0, 1, 1),
(46095, 7480, 0.0149, 1, 0, 1, 1),
(46095, 7481, 0.0895, 1, 0, 1, 1),
(46095, 7482, 0.0298, 1, 0, 1, 1),
(46095, 7484, 0.0149, 1, 0, 1, 1),
(46095, 7485, 0.0149, 1, 0, 1, 1),
(46095, 7486, 0.0149, 1, 0, 1, 1),
(46095, 7487, 0.0149, 1, 0, 1, 1),
(46095, 7488, 0.0298, 1, 0, 1, 1),
(46095, 7489, 0.0298, 1, 0, 1, 1),
(46095, 7490, 0.0895, 1, 0, 1, 1),
(46095, 7491, 0.1044, 1, 0, 1, 1),
(46095, 7522, 0.0149, 1, 0, 1, 1),
(46095, 7525, 0.0149, 1, 0, 1, 1),
(46095, 7533, 0.0149, 1, 0, 1, 1),
(46095, 7534, 0.0597, 1, 0, 1, 1),
(46095, 7544, 0.0448, 1, 0, 1, 1),
(46095, 7545, 0.0149, 1, 0, 1, 1),
(46095, 7552, 0.0149, 1, 0, 1, 1),
(46095, 7556, 0.0149, 1, 0, 1, 1),
(46095, 7610, 0.1044, 1, 0, 1, 1),
(46095, 7909, 0.1, 1, 0, 1, 1),
(46095, 7910, 0.05, 1, 0, 1, 1),
(46095, 7989, 0.0149, 1, 0, 1, 1),
(46095, 8141, 0.0746, 1, 0, 1, 1),
(46095, 8157, 0.0149, 1, 0, 1, 1),
(46095, 8162, 0.0149, 1, 0, 1, 1),
(46095, 8163, 0.0149, 1, 0, 1, 1),
(46095, 8196, 0.0597, 1, 0, 1, 1),
(46095, 8749, 0.05, 1, 0, 1, 1),
(46095, 8750, 0.2089, 1, 0, 1, 1),
(46095, 8751, 0.0895, 1, 0, 1, 1),
(46095, 9286, 0.0149, 1, 0, 1, 1),
(46095, 9288, 0.0149, 1, 0, 1, 1),
(46095, 9292, 0.0448, 1, 0, 1, 1),
(46095, 9293, 0.0149, 1, 0, 1, 1),
(46095, 9298, 0.0149, 1, 0, 1, 1),
(46095, 9874, 0.0149, 1, 0, 1, 1),
(46095, 9878, 0.0597, 1, 0, 1, 1),
(46095, 9881, 0.0149, 1, 0, 1, 1),
(46095, 9887, 0.0298, 1, 0, 1, 1),
(46095, 9893, 0.0298, 1, 0, 1, 1),
(46095, 9894, 0.0597, 1, 0, 1, 1),
(46095, 9897, 0.0448, 1, 0, 1, 1),
(46095, 9899, 0.0597, 1, 0, 1, 1),
(46095, 9903, 0.0149, 1, 0, 1, 1),
(46095, 9904, 0.0746, 1, 0, 1, 1),
(46095, 9906, 0.0149, 1, 0, 1, 1),
(46095, 9908, 0.0149, 1, 0, 1, 1),
(46095, 9910, 0.0149, 1, 0, 1, 1),
(46095, 9912, 0.0149, 1, 0, 1, 1),
(46095, 9915, 0.0149, 1, 0, 1, 1),
(46095, 9916, 0.0746, 1, 0, 1, 1),
(46095, 9917, 0.0149, 1, 0, 1, 1),
(46095, 9920, 0.0448, 1, 0, 1, 1),
(46095, 9925, 0.0149, 1, 0, 1, 1),
(46095, 9927, 0.0149, 1, 0, 1, 1),
(46095, 9928, 0.0448, 1, 0, 1, 1),
(46095, 9931, 0.0298, 1, 0, 1, 1),
(46095, 9967, 0.0149, 1, 0, 1, 1),
(46095, 9968, 0.0448, 1, 0, 1, 1),
(46095, 9971, 0.0149, 1, 0, 1, 1),
(46095, 9972, 0.0149, 1, 0, 1, 1),
(46095, 10302, 0.0149, 1, 0, 1, 1),
(46095, 10603, 0.0149, 1, 0, 1, 1),
(46095, 10604, 0.0149, 1, 0, 1, 1),
(46095, 11202, 0.0149, 1, 0, 1, 1),
(46095, 11208, 0.0149, 1, 0, 1, 1),
(46095, 11973, 0.0149, 1, 0, 1, 1),
(46095, 11987, 0.0149, 1, 0, 1, 1),
(46095, 11998, 0.0895, 1, 0, 1, 1),
(46095, 12011, 0.0298, 1, 0, 1, 1),
(46095, 12022, 0.0149, 1, 0, 1, 1),
(46095, 12023, 0.0149, 1, 0, 1, 1),
(46095, 12031, 0.0298, 1, 0, 1, 1),
(46095, 12808, 1.5667, 1, 0, 1, 1),
(46095, 13132, 0.0298, 1, 0, 1, 1),
(46095, 15244, 0.0448, 1, 0, 1, 1),
(46095, 15251, 0.0597, 1, 0, 1, 1),
(46095, 21940, 0.0149, 1, 0, 1, 1),
(46095, 21945, 0.0149, 1, 0, 1, 1),
(46095, 21947, 0.0298, 1, 0, 1, 1),
(46095, 61387, 9.6389, 1, 0, 1, 1),
(46096, 866, 0.0759, 1, 0, 1, 1),
(46096, 868, 0.0152, 1, 0, 1, 1),
(46096, 1613, 0.0607, 1, 0, 1, 1),
(46096, 1640, 0.0607, 1, 0, 1, 1),
(46096, 1645, 6.4653, 1, 0, 1, 1),
(46096, 1718, 0.0152, 1, 0, 1, 1),
(46096, 1994, 0.0152, 1, 0, 1, 1),
(46096, 2802, 0.0152, 1, 0, 1, 1),
(46096, 3419, 14.2857, 1, 0, 1, 1),
(46096, 3430, 0.0304, 1, 0, 1, 1),
(46096, 3868, 0.0304, 1, 0, 1, 1),
(46096, 3874, 0.0152, 1, 0, 1, 1),
(46096, 3914, 0.2, 1, 0, 1, 1),
(46096, 3928, 50, 1, 0, 1, 1),
(46096, 3936, 0.05, 1, 0, 1, 1),
(46096, 3938, 0.1518, 1, 0, 1, 1),
(46096, 3939, 0.1, 1, 0, 1, 1),
(46096, 3940, 0.2277, 1, 0, 1, 1),
(46096, 3941, 0.05, 1, 0, 1, 1),
(46096, 3942, 0.2277, 1, 0, 1, 1),
(46096, 3943, 0.1, 1, 0, 1, 1),
(46096, 3961, 0.05, 1, 0, 1, 1),
(46096, 3962, 0.1518, 1, 0, 1, 1),
(46096, 3963, 0.1, 1, 0, 1, 1),
(46096, 3965, 0.1752, 1, 0, 1, 1),
(46096, 3966, 0.1366, 1, 0, 1, 1),
(46096, 3967, 0.05, 1, 0, 1, 1),
(46096, 3968, 0.2125, 1, 0, 1, 1),
(46096, 3986, 0.1752, 1, 0, 1, 1),
(46096, 3989, 0.1669, 1, 0, 1, 1),
(46096, 4000, 0.1062, 1, 0, 1, 1),
(46096, 4002, 0.2277, 1, 0, 1, 1),
(46096, 4003, 0.1366, 1, 0, 1, 1),
(46096, 4005, 0.1214, 1, 0, 1, 1),
(46096, 4007, 0.1, 1, 0, 1, 1),
(46096, 4017, 0.3339, 1, 0, 1, 1),
(46096, 4018, 0.2, 1, 0, 1, 1),
(46096, 4019, 0.3491, 1, 0, 1, 1),
(46096, 4020, 0.258, 1, 0, 1, 1),
(46096, 4021, 0.1, 1, 0, 1, 1),
(46096, 4022, 0.1, 1, 0, 1, 1),
(46096, 4023, 0.2732, 1, 0, 1, 1),
(46096, 4024, 0.4401, 1, 0, 1, 1),
(46096, 4025, 0.3946, 1, 0, 1, 1),
(46096, 4026, 0.3642, 1, 0, 1, 1),
(46096, 4045, 0.1062, 1, 0, 1, 1),
(46096, 4047, 0.0759, 1, 0, 1, 1),
(46096, 4063, 0.0759, 1, 0, 1, 1),
(46096, 4068, 0.0607, 1, 0, 1, 1),
(46096, 4080, 0.0304, 1, 0, 1, 1),
(46096, 4306, 20.1, 1, 0, 1, 2),
(46096, 4338, 52.2689, 1, 0, 1, 1),
(46096, 4608, 10.5175, 1, 0, 1, 1),
(46096, 4637, 0.1669, 1, 0, 1, 1),
(46096, 4734, 0.0304, 1, 0, 1, 1),
(46096, 4737, 0.0152, 1, 0, 1, 1),
(46096, 4738, 0.0152, 1, 0, 1, 1),
(46096, 6424, 0.0455, 1, 0, 1, 1),
(46096, 6425, 0.0152, 1, 0, 1, 1),
(46096, 6426, 0.0304, 1, 0, 1, 1),
(46096, 6428, 0.0304, 1, 0, 1, 1),
(46096, 6429, 0.0152, 1, 0, 1, 1),
(46096, 6430, 0.0152, 1, 0, 1, 1),
(46096, 7085, 0.0152, 1, 0, 1, 1),
(46096, 7332, 0.0304, 1, 0, 1, 1),
(46096, 7470, 0.0607, 1, 0, 1, 1),
(46096, 7471, 0.0152, 1, 0, 1, 1),
(46096, 7478, 0.0455, 1, 0, 1, 1),
(46096, 7479, 0.0152, 1, 0, 1, 1),
(46096, 7481, 0.0152, 1, 0, 1, 1),
(46096, 7482, 0.0152, 1, 0, 1, 1),
(46096, 7486, 0.0304, 1, 0, 1, 1),
(46096, 7487, 0.0607, 1, 0, 1, 1),
(46096, 7491, 0.0304, 1, 0, 1, 1),
(46096, 7496, 0.0304, 1, 0, 1, 1),
(46096, 7524, 0.0304, 1, 0, 1, 1),
(46096, 7531, 0.0304, 1, 0, 1, 1),
(46096, 7534, 0.0152, 1, 0, 1, 1),
(46096, 7541, 0.0152, 1, 0, 1, 1),
(46096, 7552, 0.0304, 1, 0, 1, 1),
(46096, 7909, 0.05, 1, 0, 1, 1),
(46096, 7975, 0.0152, 1, 0, 1, 1),
(46096, 7992, 0.0152, 1, 0, 1, 1),
(46096, 8109, 0.0152, 1, 0, 1, 1),
(46096, 8120, 0.0455, 1, 0, 1, 1),
(46096, 8139, 0.0152, 1, 0, 1, 1),
(46096, 8140, 0.0152, 1, 0, 1, 1),
(46096, 8141, 0.0304, 1, 0, 1, 1),
(46096, 8142, 0.0607, 1, 0, 1, 1),
(46096, 8157, 0.0152, 1, 0, 1, 1),
(46096, 8194, 0.0911, 1, 0, 1, 1),
(46096, 8196, 0.0911, 1, 0, 1, 1),
(46096, 8273, 0.0152, 1, 0, 1, 1),
(46096, 8386, 0.0455, 1, 0, 1, 1),
(46096, 8749, 0.1518, 1, 0, 1, 1),
(46096, 8750, 0.1, 1, 0, 1, 1),
(46096, 8751, 0.1518, 1, 0, 1, 1),
(46096, 9291, 0.0304, 1, 0, 1, 1),
(46096, 9433, 0.0152, 1, 0, 1, 1),
(46096, 9882, 0.0152, 1, 0, 1, 1),
(46096, 9883, 0.0152, 1, 0, 1, 1),
(46096, 9884, 0.0304, 1, 0, 1, 1),
(46096, 9887, 0.0455, 1, 0, 1, 1),
(46096, 9899, 0.0152, 1, 0, 1, 1),
(46096, 9903, 0.0152, 1, 0, 1, 1),
(46096, 9908, 0.0455, 1, 0, 1, 1),
(46096, 9909, 0.1366, 1, 0, 1, 1),
(46096, 9912, 0.0152, 1, 0, 1, 1),
(46096, 9915, 0.0455, 1, 0, 1, 1),
(46096, 9916, 0.0152, 1, 0, 1, 1),
(46096, 9919, 0.1366, 1, 0, 1, 1),
(46096, 9922, 0.0152, 1, 0, 1, 1),
(46096, 9923, 0.0152, 1, 0, 1, 1),
(46096, 9927, 0.0152, 1, 0, 1, 1),
(46096, 9928, 0.0304, 1, 0, 1, 1),
(46096, 9930, 0.0304, 1, 0, 1, 1),
(46096, 9931, 0.0304, 1, 0, 1, 1),
(46096, 9933, 0.0152, 1, 0, 1, 1),
(46096, 9934, 0.0304, 1, 0, 1, 1),
(46096, 9935, 0.0455, 1, 0, 1, 1),
(46096, 9967, 0.0304, 1, 0, 1, 1),
(46096, 9968, 0.0152, 1, 0, 1, 1),
(46096, 9969, 0.0152, 1, 0, 1, 1),
(46096, 9972, 0.0152, 1, 0, 1, 1),
(46096, 9973, 0.0152, 1, 0, 1, 1),
(46096, 10094, 0.0152, 1, 0, 1, 1),
(46096, 11204, 0.0152, 1, 0, 1, 1),
(46096, 11973, 0.0304, 1, 0, 1, 1),
(46096, 11998, 0.0152, 1, 0, 1, 1),
(46096, 12023, 0.0152, 1, 0, 1, 1),
(46096, 12808, 1.4873, 1, 0, 1, 1),
(46096, 13029, 0.0152, 1, 0, 1, 1),
(46096, 13199, 0.0152, 1, 0, 1, 1),
(46096, 15244, 0.0607, 1, 0, 1, 1),
(46096, 15251, 0.1518, 1, 0, 1, 1),
(46096, 15270, 0.0152, 1, 0, 1, 1),
(46096, 61387, 9.5917, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '27617' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27617, 27612, 0),
(20, 8, 27617, 27613, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27617' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27617, 27612, 0),
(19, 8, 27617, 27613, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27620' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27620, 27617, 0),
(20, 8, 27620, 27618, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27620' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27620, 27617, 0),
(19, 8, 27620, 27618, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27618' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(19, 0, 27618, 0, 3, 8, 0, 27619, 0, 0, 0, 0, 0, '', NULL),
(19, 0, 27618, 0, 2, 8, 0, 27616, 0, 0, 0, 0, 0, '', NULL),
(19, 0, 27618, 0, 1, 8, 0, 27615, 0, 0, 0, 0, 0, '', NULL),
(19, 0, 27618, 0, 0, 8, 0, 27614, 0, 0, 0, 0, 0, '', NULL);

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=6547;
UPDATE `creature_template` SET `unit_class`=8 WHERE `entry`=46093;
UPDATE `creature_template` SET `unit_class`=3 WHERE `entry`=46094;
UPDATE `creature_template` SET `unit_class`=2 WHERE `entry` IN (46092, 46096);

UPDATE `creature_template_addon` SET `path_id`=1949700, `mount`=22471 WHERE `entry`=16378;

SET @CGUID := 400830;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+9;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 46096, 0, 1, 2, 0, 1, 1569.45, -5606.52, 114.191, 1.06887, 120, 0, 0, 3963, 1381, 0, 0, 0, 0),
(@CGUID+1, 16116, 0, 1, 2, 0, 0, 1681.22, -5355.06, 73.6133, 4.00529, 120, 0, 0, 158730, 73020, 0, 0, 0, 0),
(@CGUID+2, 46094, 0, 1, 2, 0, 1, 1621.03, -5291.92, 99.9684, 1.14866, 120, 0, 0, 84, 0, 0, 0, 0, 0),
(@CGUID+3, 46092, 0, 1, 2, 0, 1, 1600.38, -5305.93, 91.1058, 5.82586, 120, 0, 0, 84, 0, 0, 0, 0, 0),
(@CGUID+4, 46093, 0, 1, 2, 0, 1, 1594.64, -5306.35, 68.7322, 5.77582, 120, 0, 0, 84, 0, 0, 0, 0, 0),
(@CGUID+5, 46095, 0, 1, 2, 0, 1, 1749.18, -5416.44, 113.524, 1.34514, 120, 0, 0, 84, 0, 0, 0, 0, 0),
(@CGUID+6, 16112, 0, 1, 2, 0, 1, 1657.62, -5327.31, 74.2528, 5.53576, 120, 0, 0, 610400, 0, 0, 0, 0, 0),
(@CGUID+7, 16115, 0, 1, 2, 0, 0, 1737.96, -5378.16, 80.8628, 2.94837, 120, 0, 0, 244200, 12170, 0, 0, 0, 0),
(@CGUID+8, 45729, 0, 1, 1, 0, 1, 2295.55, -5341.9, 90.7519, 0.0666899, 300, 0, 0, 1535, 1587, 0, 0, 0, 0),
(@CGUID+9, 46173, 0, 1, 1, 0, 1, 2299.43, -5342.06, 90.7519, 2.97659, 300, 0, 0, 42, 0, 0, 0, 0, 0);

SET @OGUID := 400100;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+1;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+0, 205877, 0, 1, 2, 1802.3, -5423.32, 82.3116, 4.51409, 0, 0, 0.773629, -0.633639, 300, 0, 1),
(@OGUID+1, 205876, 0, 1, 2, 1745.24, -5455.39, 83.3631, 2.385, 0, 0, 0.929295, 0.369339, 300, 0, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (85218, 85217);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85218, 'spell_summon_generic_controller'),
(85217, 'spell_summon_generic_controller');

DELETE FROM `spell_area` WHERE `spell` IN (85218, 85217) AND `quest_start` = '27463';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(85218, 2268, 27463, 27465, 0, 0, 2, 1, 66, 11),
(85217, 2268, 27463, 27465, 0, 0, 2, 1, 66, 11);

-- Gidwin Goldbraids
SET @ENTRY := 46173;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,8258,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Devotion Aura"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,60000,60000,11,79968,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blessing of Kings"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,60000,60000,11,79968,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blessing of Kings (Owner)"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,2000,2000,8000,8000,11,79966,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Consecration"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,10000,10000,10000,10000,11,79960,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Holy Light (Owner)"),
(@ENTRY,@SOURCETYPE,6,0,54,0,100,0,0,0,0,0,7,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,7,0,0,0,15,0,6000,6000,6000,6000,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Talk 0");

-- Tarenar Sunstrike
SET @ENTRY := 45957;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,60000,60000,11,79977,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blessing of Might (Owner)"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,79976,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Retribution Aura"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,2000,2000,6000,6000,11,79970,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Divine Storm"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,6500,6500,8500,8500,11,79971,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hammer of Wrath"),
(@ENTRY,@SOURCETYPE,5,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,6,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

DELETE FROM `creature_equip_template` WHERE `entry` = '46173';
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(46173, 1, 13312, 58938, 0);

DELETE FROM `creature_equip_template` WHERE `entry` = '45957';
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(45957, 1, 57038, 0, 0);

DELETE FROM `creature_text` WHERE `entry`=46173;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46173,0,0,'Ka-boom!',12,0,100,0,0,0,'Comment'),
(46173,0,1,'Did you see that, Tarenar?',12,0,100,0,0,0,'Comment'),
(46173,0,2,'I can\'t believe we\'re actually fighting for the Crusade!',12,0,100,0,0,0,'Comment'),
(46173,0,3,'Can we slow down just a bit?',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `mindmg`=105, `maxdmg`=154, `attackpower`=112 WHERE `entry` IN (46173, 45157, 45698, 45957, 45692);
UPDATE `creature_template` SET `mindmg`=54, `maxdmg`=80, `attackpower`=20, `dmg_multiplier`=3.6, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45707;

DELETE FROM `creature_text` WHERE `entry`=16378;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(16378,0,0,'Good Luck.',12,0,100,0,0,0,'Comment'),
(16378,1,0,'You can feel a strange sensation...',42,0,100,0,0,0,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6282';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6282, 'at_light_hope_crypt');

DELETE FROM `creature_text` WHERE `entry`=45707;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45707,0,0,'Let the trial begin. Rise, champions! Rise, and meet these three in combat!',12,0,100,0,0,0,'Comment'),
(45707,1,0,'Your warm-up is complete. Now, the real trial begins!',12,0,100,0,0,0,'Comment'),
(45707,2,0,'Well-done, heroes. You have passed my test of combat.',12,0,100,0,0,0,'Comment');

-- Lord Raymond George
SET @ENTRY := 45707;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45707,0,0,12,45698,3,60000,0,0,0,8,0,0,0,2311.55,-5393.06,75.65,5.55,"After Talk 0 - Summon Argent Warden"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,45707,0,0,12,45698,3,60000,0,0,0,8,0,0,0,2334.92,-5392.53,75.65,3.64,"After Talk 0 - Summon Argent Warden"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45707,0,0,12,45698,3,60000,0,0,0,8,0,0,0,2334.9,-5404.7,75.65,2.65,"After Talk 0 - Summon Argent Warden"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,45707,0,0,12,45698,3,60000,0,0,0,8,0,0,0,2311.55,-5404.58,75.65,0.72,"After Talk 0 - Summon Argent Warden"),
(@ENTRY,@SOURCETYPE,5,0,60,0,100,1,60000,60000,60000,60000,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 1"),
(@ENTRY,@SOURCETYPE,6,11,52,0,100,0,1,45707,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Attackable"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 2"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Force Despawn"),
(@ENTRY,@SOURCETYPE,9,0,6,0,100,0,0,0,0,0,33,45707,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,0,45707,0,0,11,45849,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Cast Shake"),
(@ENTRY,@SOURCETYPE,11,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,46173,15,0,0.0,0.0,0.0,0.0,"Link - Attack Gidwin");

-- Argent Warden
SET @ENTRY := 45698;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Players");

DELETE FROM `spell_script_names` WHERE `spell_id` = '85308';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85308, 'spell_trial_of_the_crypt');

DELETE FROM `spell_area` WHERE `spell` IN (85218, 85217) AND `quest_start` = '27465';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(85218, 2270, 27465, 27465, 1, 64, 11),
(85217, 2270, 27465, 27465, 1, 64, 11);

DELETE FROM `spell_script_names` WHERE `spell_id` = '85252';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85252, 'spell_bury_blade');

-- Noxious Assassin
SET @ENTRY := 45692;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4500,4500,11,7159,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Backstab"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,8500,12500,11,34802,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Kick");

DELETE FROM `conditions` WHERE `SourceEntry` = '27684' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference` = '14';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 14, 27684, 27683, 0),
(20, 14, 27684, 28577, 0),
(20, 14, 27684, 28578, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27684' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference` = '14';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 14, 27684, 27683, 0),
(19, 14, 27684, 28577, 0),
(19, 14, 27684, 28578, 0);

DELETE FROM `creature_addon` WHERE `guid` = '400839';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400839, '82358');

DELETE FROM `spell_area` WHERE `spell` = '94567' AND `quest_start` = '27465';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(94567, 2268, 27465, 27466, 0, 0, 2, 1, 64, 11);

-- Lord Maxwell Tyrosus
SET @ENTRY := 11034;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27465,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Despawn All Summons");

UPDATE `quest_template` SET `PrevQuestId`='27487' WHERE `Id`=27488;
UPDATE `quest_template` SET `PrevQuestId`='27457' WHERE `Id`=27561;
UPDATE `quest_template` SET `PrevQuestId`='27466' WHERE `Id`=27487;

SET @CGUID := 400840;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+7;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45417, 0, 1, 1, 0, 0, 2555.06, -4759.17, 105.423, 2.64178, 300, 0, 0, 1478, 1534, 0, 0, 0, 0),
(@CGUID+1, 45433, 0, 1, 1, 0, 0, 2553.73, -4761.46, 105.577, 2.13106, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+2, 45434, 0, 1, 1, 0, 0, 2552.46, -4762.14, 105.587, 2.13106, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+3, 45400, 0, 1, 1, 0, 0, 2554.95, -4764.79, 105.886, 2.1232, 300, 0, 0, 1848, 0, 0, 16777219, 0, 0),
(@CGUID+4, 45416, 0, 1, 1, 0, 0, 2554.95, -4764.79, 105.886, 2.1232, 300, 0, 0, 1848, 0, 0, 16777216, 0, 0),
(@CGUID+5, 45729, 0, 1, 1, 0, 1, 2542.66, -4769.78, 105.285, 6.25095, 300, 0, 0, 1535, 1587, 0, 0, 0, 0),
(@CGUID+6, 45574, 0, 1, 1, 0, 0, 2317.6, -4405.96, 96.307, 3.51934, 300, 0, 0, 1716, 0, 0, 0, 0, 0),
(@CGUID+7, 45574, 0, 1, 1, 0, 0, 2522.84, -4787.89, 106.379, 1.17873, 300, 0, 0, 1716, 0, 0, 0, 0, 0);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` IN (27457, 27466);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 2271, 27457, 27489, 1, 66),
(49416, 2271, 27466, 27489, 1, 66);

DELETE FROM `creature_addon` WHERE `guid` = '400845';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400845, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27466';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 2271, 27466, 27489, -85405, 0, 2, 1, 66, 11);

DELETE FROM `spell_script_names` WHERE `spell_id` = '85405';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85405, 'spell_summon_generic_controller');

DELETE FROM `spell_area` WHERE `spell` = '85405' AND `quest_start` = '27487';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(85405, 2271, 27487, 27487, 1, 10);

-- Tarenar Sunstrike
SET @ENTRY := 45794;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might "),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,79977,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Blessing of Might (Owner)"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,7500,8500,11,79970,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Divine Storm"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,4000,4000,9500,9500,11,79971,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hammer of Wrath"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invincible");

UPDATE `creature_template` SET `unit_class`=2, `minlevel`=46, `maxlevel`=46, `mindmg`=78, `maxdmg`=114, `attackpower`=112, `dmg_multiplier`=1.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45794;
UPDATE `creature_template` SET `mindmg`=60, `maxdmg`=91, `attackpower`=26 WHERE `entry` IN (45743, 45744);


-- Nerubian Sycophant
SET @ENTRY := 45743;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,17169,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Summon Carrion Scarab");

-- Ix'lar the Underlord
SET @ENTRY := 45744;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,17169,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Summon Carrion Scarab"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,5500,5500,11,90908,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mandible Crush");

UPDATE `creature_template_addon` SET `auras`='80852' WHERE `entry`=46022;

DELETE FROM `creature_loot_template` WHERE `item` = '61313';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8562, 61313, -70.9781, 1, 0, 1, 3),
(8560, 61313, -70.7269, 1, 0, 1, 3),
(8561, 61313, -68.8504, 1, 0, 1, 3),
(12261, 61313, -36.3242, 1, 0, 1, 3),
(10822, 61313, -32.4795, 1, 0, 1, 3);

UPDATE `quest_template` SET `PrevQuestId`='27449' WHERE `Id`=27559;
UPDATE `quest_template` SET `PrevQuestId`='0', `Flags`=0 WHERE `Id`=27481;
UPDATE `quest_template` SET `PrevQuestId`='27432' WHERE `Id`=27449;

DELETE FROM `conditions` WHERE `SourceEntry` = '27481' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27481, 27449, 0),
(20, 8, 27481, 27466, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27481' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27481, 27449, 0),
(19, 8, 27481, 27466, 0);

DELETE FROM `creature_equip_template` WHERE `entry` = '45579';
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(45579, 5282, 12298, 0);

DELETE FROM `creature_equip_template` WHERE `entry` = '46199';
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(46199, 1, 57038, 0, 0);

UPDATE `creature_template` SET `unit_class`=4, `mindmg`=58, `maxdmg`=86, `attackpower`=22, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45579;

-- Mossflayer Rogue
SET @ENTRY := 45579;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,3000,4500,6500,11,14873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,11,1784,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Stealth"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,5000,5000,5000,11,1784,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Stealth"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,25,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Summoner"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Aggressive");

DELETE FROM `creature_text` WHERE `entry`=45574;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45574,0,0,'Defeat Mossflayer Rogues to prove your strenght!',42,0,100,0,0,0,'Comment');

-- Vex'tul
SET @ENTRY := 45574;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27449,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45574,0,0,85,85094,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Mossflayer Rogue (SW)"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,45574,0,0,85,85095,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Mossflayer Rogue (SE)"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45574,0,0,85,85095,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Mossflayer Rogue (SE)"),
(@ENTRY,@SOURCETYPE,4,0,20,0,100,0,27482,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Despawn All Summons");

UPDATE `creature_template` SET `mindmg`=45, `maxdmg`=67, `attackpower`=17 WHERE `entry`=8537;
UPDATE `creature_template` SET `mindmg`=84, `maxdmg`=115, `attackpower`=85 WHERE `entry`=45741;

-- Interloper
SET @ENTRY := 8537;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,4500,4500,11,11975,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Arcane Explosion");

DELETE FROM `creature_addon` WHERE `guid` = '400847';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400847, '60921');

DELETE FROM `spell_area` WHERE `spell` = '60922' AND `quest_start` = '27449';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `aura_spell`, `autocast`, `quest_end_status`) VALUES
(60922, 2271, 27449, -85334, 1, 0);

DELETE FROM `spell_area` WHERE `spell` = '85334' AND `quest_start` = '27481';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(85334, 2273, 27481, 27481, 1, 8);

-- Vex'tul
SET @ENTRY := 45741;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,63227,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Enrage"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4500,4500,11,79881,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Slam"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,42,1,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invincible"),
(@ENTRY,@SOURCETYPE,4,0,20,0,100,0,27482,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Force Despawn");

DELETE FROM `spell_script_names` WHERE `spell_id` = '85334';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85334, 'spell_summon_generic_controller');

DELETE FROM `creature_involvedrelation` WHERE `id` = '45741' AND `quest` = '27481';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(45741, 27481);

DELETE FROM `creature_questrelation` WHERE `id` = '45741' AND `quest` = '27482';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(45741, 27482);

DELETE FROM `creature_involvedrelation` WHERE `quest` = '27482';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(45741, 27482),
(45574, 27482);

DELETE FROM `creature_loot_template` WHERE `item` = '61315';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(10822, 61315, -89.565, 1, 0, 1, 1);

UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=45741;

DELETE FROM `spell_script_names` WHERE `spell_id` = '85327';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85327, 'spell_destroy_threshjin_body');

DELETE FROM `conditions` WHERE `SourceEntry` = '85327';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85327, 0, 0, 31, 0, 3, 41200, 0, 0, 0, '', 'Targeting -> Bonfire');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27482;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12035' AND `id` = '1';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12035, 1, 'Ride Fiona\'s Caravan to its final destination.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=12035 AND `SourceEntry` = '1';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12035, 1, 0, 0, 9, 0, 27489, 0, 0, 0, 0, 0, '', 'Fiona\'s Caravan - Show gossip only if quest 27489 is active');

UPDATE `creature_template` SET `VehicleId`=1107 WHERE `entry`=45782;
UPDATE `creature_template` SET `VehicleId`=1108 WHERE `entry`=45783;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45783';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45783, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45782';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45782, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (45783, 45782);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(45783, 46194, 2, 1, 'Caravan - Argus', 8, 0),
(45783, 45941, 3, 1, 'Caravan - Fiona', 8, 0),
(45783, 46178, 1, 1, 'Caravan - Tarenar', 8, 0),
(45782, 45434, 2, 1, 'Harness - Argyle', 8, 0),
(45782, 45433, 1, 1, 'Harness - Preston', 8, 0),
(45782, 45783, 0, 1, 'Harness - Caravan', 8, 0);

DELETE FROM `creature_text` WHERE `entry`=46178;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46178,0,0,'I can\'t believe I let Gidwin run off like that!',14,0,100,0,0,0,'Comment'),
(46178,1,0,'No, he\'d never just leave his prayer book behind! He was always nose-deep in that book, studying.',14,0,100,0,0,0,'Comment'),
(46178,2,0,'He was always studying, always trying to get better.',12,0,100,0,0,0,'Comment'),
(46178,3,0,'I\'m not sure I\'m ready to go in there alone.',12,0,100,0,0,0,'Comment'),
(46178,4,0,'Me, skilled? No, no, Gidwin was the good paladin. He\'s the one who stayed up for hours every night practising...',12,0,100,0,0,0,'Comment'),
(46178,5,0,'What do you mean?',12,0,100,0,0,0,'Comment'),
(46178,6,0,'This is all my fault. I\'ve got to go find him, to set things right.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45941;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45941,0,0,'It\'s not your fault, Tarenar. He ran off on his own will. None of us could stop him.',12,0,100,0,0,0,'Comment'),
(45941,1,0,'Really? That\'s great news!',14,0,100,0,0,0,'Comment'),
(45941,2,0,'Well, actually, that\'s pretty bad news, but considering the alternatives...',12,0,100,0,0,0,'Comment'),
(45941,3,0,'You\'re not alone, Tarenar. You\'ve made allies along the way. And besides, you\'re a skilled paladin in your own right.',12,0,100,0,0,0,'Comment'),
(45941,4,0,'...yet it was you that continually kept up with him. Without practise.',12,0,100,0,0,0,'Comment'),
(45941,5,0,'I\'ve watched both of you fight, Tarenar. You\'ve got natural talent - more than Gidwin ever will.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=46194;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46194,0,0,'We can\'t be certain that he was killed. Maybe he just ran off somewhere.',12,0,100,0,0,0,'Comment'),
(46194,1,0,'Even more reason to believe that he\'s still alive.',12,0,100,0,0,0,'Comment'),
(46194,2,0,'A paladin like Gidwin makes a fine death knight. Any member of the Scourge powerful enough to defeat him would know that.',12,0,100,0,0,0,'Comment'),
(46194,3,0,'If we\'re to find him, we\'re headed in the right direction. It\'s likely that he was taken to Stratholme, or potentially to the Plaguewood.',12,0,100,0,0,0,'Comment'),
(46194,4,0,'Both are places of great evil. This is the leg of my journey that I shun the most.',12,0,100,0,0,0,'Comment'),
(46194,5,0,'Perhaps that\'s why he left without you.',12,0,100,0,0,0,'Comment'),
(46194,6,0,'Perhaps he felt he needed to prove that he was as talented as you.',12,0,100,0,0,0,'Comment'),
(46194,7,0,'I wouldn\'t say that it\'s your fault, Tarenar. But don\'t let that stop you from saving Gidwin.',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '45782';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45782, 1, 2492.71, -4715.12, 87.33, 'Fiona\'s Caravan Final'),
(45782, 2, 2494.19, -4660.58, 75.22, 'Fiona\'s Caravan Final'),
(45782, 3, 2561.51, -4647.44, 78.92, 'Fiona\'s Caravan Final'),
(45782, 4, 2742.02, -4541.36, 88.64, 'Fiona\'s Caravan Final'),
(45782, 5, 2820.26, -4461.22, 89.94, 'Fiona\'s Caravan Final'),
(45782, 6, 2874.95, -4372.69, 90.00, 'Fiona\'s Caravan Final'),
(45782, 7, 2892.48, -4305.42, 90.66, 'Fiona\'s Caravan Final'),
(45782, 8, 2898.66, -4269.09, 91.31, 'Fiona\'s Caravan Final'),
(45782, 9, 3001.92, -4230.04, 95.45, 'Fiona\'s Caravan Final'),
(45782, 10, 3045.05, -4260.33, 97.46, 'Fiona\'s Caravan Final'),
(45782, 11, 3086.12, -4254.30, 97.8, 'Fiona\'s Caravan Final'),
(45782, 12, 3129.47, -4298.66, 119.04, 'Fiona\'s Caravan Final'),
(45782, 13, 3163.65, -4325.21, 132.55, 'Fiona\'s Caravan Final');

-- Fiona's Caravan Harness
SET @ENTRY := 45782;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,45782,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,13,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - Remove Passengers"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,13,0,0,0,33,45400,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - Quest Complete"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,13,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - Forced Despawn");

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (45783, 45782, 46194, 45941, 46178, 45434, 45433, 45921, 45965);

-- Tarenar Sunstrike
SET @ENTRY := 46178;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,5000,5000,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46178,0,0,45,0,1,0,0,0,0,11,45941,15,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Fiona"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,46178,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,46178,0,0,45,0,2,0,0,0,0,11,46194,15,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Argus"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,46178,0,0,45,0,3,0,0,0,0,11,45941,15,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Fiona"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,3,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,46178,0,0,45,0,4,0,0,0,0,11,45941,15,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 4 to Fiona"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,4,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,46178,0,0,45,0,5,0,0,0,0,11,46194,15,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 5 to Argus"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,5,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,6,46178,0,0,45,0,6,0,0,0,0,11,46194,15,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 6 to Argus");

-- Argus Highbeacon
SET @ENTRY := 46194;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46194,0,0,45,0,1,0,0,0,0,11,46178,15,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Tarenar"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,46194,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,46194,0,0,45,0,2,0,0,0,0,11,45941,15,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Fiona"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,46194,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,46194,0,0,45,0,2,0,0,0,0,11,46178,15,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 2 to Tarenar"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,4,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,5,46194,0,0,45,0,4,0,0,0,0,11,46178,15,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 4 to Tarenar"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,5,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,6,46194,0,0,45,0,5,0,0,0,0,11,46178,15,0,0.0,0.0,0.0,0.0,"After Talk 6 - Set Data 5 to Tarenar"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,6,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 7");

-- Fiona
SET @ENTRY := 45941;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45941,0,0,45,0,1,0,0,0,0,11,46194,15,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Argus"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45941,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,45941,0,0,45,0,3,0,0,0,0,11,46194,15,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Argus"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45941,0,0,45,0,3,0,0,0,0,11,46178,15,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Tarenar"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,4,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,45941,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,5,45941,0,0,45,0,4,0,0,0,0,11,46194,15,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 4 to Argus");

-- Fiona's Caravan
SET @ENTRY := 45783;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,2000,2000,0,0,86,46598,0,18,50,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker");

UPDATE `creature_template` SET `minlevel`=46, `maxlevel`=46 WHERE `entry`=45960;

SET @CGUID := 400880;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+8;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45451, 0, 1, 1, 0, 1, 3163.88, -4320.89, 131.711, 0.0381412, 300, 0, 0, 4244, 0, 0, 0, 0, 0),
(@CGUID+1, 45417, 0, 1, 1, 0, 0, 3165.24, -4324.39, 132.561, 1.98064, 300, 0, 0, 1478, 1534, 0, 0, 0, 0),
(@CGUID+2, 45960, 0, 1, 1, 0, 0, 3168.98, -4322.54, 132.737, 2.96358, 300, 0, 0, 2100, 0, 0, 0, 0, 0),
(@CGUID+3, 45434, 0, 1, 1, 0, 0, 3166.96, -4327.59, 133.024, 3.51528, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+4, 45433, 0, 1, 1, 0, 0, 3166.45, -4326.28, 132.877, 3.51528, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+5, 45400, 0, 1, 1, 0, 0, 3170.11, -4325.78, 133.3, 3.49565, 300, 0, 0, 1848, 0, 0, 16777219, 0, 0),
(@CGUID+6, 45416, 0, 1, 1, 0, 0, 3170.11, -4325.78, 133.3, 3.49565, 300, 0, 0, 1848, 0, 0, 16777216, 0, 0),
(@CGUID+7, 45729, 0, 1, 1, 0, 1, 3167.97, -4319.3, 131.68, 3.88023, 300, 0, 0, 1535, 1587, 0, 0, 0, 0),
(@CGUID+8, 45729, 0, 1, 1, 0, 1, 3130.98, -3390.02, 140.05, 5.17635, 300, 0, 0, 1535, 1587, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (400882, 400880, 400887);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400882, '49414'),
(400880, '49414'),
(400887, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27489';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 2275, 27489, 27527, 0, 0, 2, 1, 66, 11);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27489';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 2275, 27489, 27522, 1, 66, 11);

UPDATE `creature_template` SET `type_flags`=0, `InhabitType`=4 WHERE `entry`=11897;
UPDATE `creature` SET `position_z`=125.849 WHERE `guid`=193777;

DELETE FROM `creature_text` WHERE `entry`=17878;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(17878,0,0,'I will tell you nothing!',12,0,100,0,0,0,'Comment'),
(17878,0,1,'I do not fear death at your hands!',12,0,100,0,0,0,'Comment'),
(17878,0,2,'The dwarf belongs to our kind now, not yours!',12,0,100,0,0,0,'Comment'),
(17878,0,3,'She will never return the dwarf to you!',12,0,100,0,0,0,'Comment'),
(17878,1,0,'The Plaguewood is too big! Your friend is gone! You will never find him!',12,0,100,0,0,0,'Comment'),
(17878,2,0,'Foolish! You seek the dwarf? Baroness Anastari has hidden him well!',12,0,100,0,0,0,'Comment');

-- Scourge Siege Engineer
SET @ENTRY := 17878;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,9000,9000,11,86088,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Throw Dynamite"),
(@ENTRY,@SOURCETYPE,1,0,0,0,33,0,1000,3500,5000,10000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Talk 0"),
(@ENTRY,@SOURCETYPE,2,4,0,0,10,0,1000,3500,5000,10000,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Talk 1"),
(@ENTRY,@SOURCETYPE,3,5,0,0,10,0,1000,3500,5000,10000,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,33,45845,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit "),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,33,45846,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit ");

DELETE FROM `creature_loot_template` WHERE `item` = '61372';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(8523, 61372, -86.3126, 1, 0, 1, 1),
(8524, 61372, -86.1156, 1, 0, 1, 1);

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=16117;

DELETE FROM `conditions` WHERE `SourceEntry` = '85555';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85555, 0, 0, 31, 0, 3, 45851, 0, 0, 0, '', 'Targeting -> Overstuffed Golems');

DELETE FROM `spell_script_names` WHERE `spell_id` = '85555';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85555, 'spell_burn_corpse');

DELETE FROM `creature_addon` WHERE `guid` = '400888';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400888, '49414');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27522';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 2277, 27522, 27526, 1, 66);

UPDATE `creature_template` SET `mindmg`=63, `maxdmg`=95, `attackpower`=24 WHERE `entry` IN (45851, 45868, 45867, 45897);

-- Overstuffed Golem
SET @ENTRY := 45851;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,6000,6000,11,14099,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mighty Blow");

-- Karthis Darkrune
SET @ENTRY := 45868;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79899,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Chains of Ice"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,500,500,5000,5000,11,79895,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frost Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,12500,12500,11,79896,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Howling Blast"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3500,3500,6500,6500,11,79897,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Icy Touch");

-- Omasum Blighthoof
SET @ENTRY := 45867;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79891,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Horn of Winter"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,500,500,60000,60000,11,79894,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Deathgrip"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,10000,10000,11,79887,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Death and Decay"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,7000,7000,7000,7000,11,79885,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heart Strike");

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=44.127 WHERE `entry`=45867 AND `item`=61378;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=57.177 WHERE `entry`=45868 AND `item`=61378;
UPDATE `creature_template` SET `InhabitType`=4, `VehicleId`=1028, `modelid2`=11686 WHERE `entry`=45965;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6300';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6300, 'at_gfr_event');

DELETE FROM `creature_text` WHERE `entry`=45956;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45956,0,0,'Oh really? What exactly will you do, dwarf? There\'s nobody to save you here.',12,0,100,0,0,0,'Comment'),
(45956,1,0,'Just the two of you? You\'ll never stand a chance.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45955;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45955,0,0,'You\'ll never get away with this, you nappy-headed horror!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=46199;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46199,0,0,'You\'re wrong, banshee. We\'ve come to take Gidwin back.',12,0,100,0,0,0,'Comment'),
(46199,1,0,'Charge!',14,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceEntry` = '85682';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85682, 0, 0, 31, 0, 3, 45978, 0, 0, 0, '', 'Targeting -> Your Doppelganger');

DELETE FROM `creature_text` WHERE `entry`=46200;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46200,0,0,'I beg to differ.',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '45965';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45965, 1, 3018.27, -3424.50, 154.55, 'GFR Event Camera'),
(45965, 2, 3016.27, -3426.44, 153.79, 'GFR Event Camera'),
(45965, 3, 3002.09, -3450.14, 151.88, 'GFR Event Camera'),
(45965, 4, 3003.78, -3443.88, 152.64, 'GFR Event Camera');

UPDATE `creature_template` SET `speed_walk`=3, `speed_run`=3.14286 WHERE `entry`=45965;

UPDATE `creature_template` SET `VehicleId`=1028 WHERE `entry`=45940;

SET @CGUID := 400890;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+9;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45417, 0, 1, 1, 0, 0, 2999.54, -3437.75, 149.709, 0.145, 300, 0, 0, 1478, 1534, 0, 0, 0, 0),
(@CGUID+1, 45794, 0, 1, 1, 0, 1, 3007.8, -3440.41, 149.709, 1.38464, 300, 0, 0, 1535, 1587, 0, 0, 0, 0),
(@CGUID+2, 45730, 0, 1, 1, 0, 1, 3008.87, -3433.97, 151.158, 4.47325, 300, 0, 0, 1478, 1534, 0, 0, 0, 0),
(@CGUID+3, 16134, 0, 1, 1, 0, 0, 3004.75, -3424.62, 149.709, 4.63168, 300, 0, 0, 95950, 0, 0, 0, 0, 0),
(@CGUID+4, 45451, 0, 1, 1, 0, 1, 3010.38, -3425.64, 149.708, 4.45842, 300, 0, 0, 4244, 0, 0, 0, 0, 0),
(@CGUID+5, 45434, 0, 1, 1, 0, 0, 2311.06, -5252.28, 81.6421, 6.25868, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+6, 45433, 0, 1, 1, 0, 0, 2311.03, -5253.68, 81.6836, 6.25868, 300, 0, 0, 1848, 0, 0, 0, 0, 0),
(@CGUID+7, 45400, 0, 1, 1, 0, 0, 2307.87, -5252.9, 81.7659, 6.23511, 300, 0, 0, 1848, 0, 0, 16777219, 0, 0),
(@CGUID+8, 45416, 0, 1, 1, 0, 0, 2307.87, -5252.9, 81.7659, 6.23511, 300, 0, 0, 1848, 0, 0, 16777216, 0, 0),
(@CGUID+9, 45417, 0, 1, 1, 0, 0, 2304.65, -5256.93, 81.9403, 4.76609, 300, 0, 0, 1478, 1534, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (400890, 400891, 400892, 400893, 400894, 400895, 400896, 400897, 400898, 400899);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400890, '82343'),
(400891, '82343'),
(400892, '82343'),
(400893, '82343'),
(400894, '82343'),
(400895, '85096'),
(400896, '85096'),
(400897, '85096'),
(400898, '85096'),
(400899, '85096');

UPDATE `creature_addon` SET `emote`=400 WHERE `guid`=400892;
UPDATE `creature_addon` SET `auras`='85096 79976' WHERE `guid`=776728;
UPDATE `creature_addon` SET `auras`='85096' WHERE `guid`=776729;

DELETE FROM `spell_area` WHERE `spell` = '90161' AND `quest_start` = '27526';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(90161, 2277, 27526, 27527, 1, 66, 9);

DELETE FROM `spell_area` WHERE `spell` = '60191' AND `quest_start` = '27526';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60191, 2277, 27526, 27527, 1, 66, 9);

DELETE FROM `spell_target_position` WHERE `id` = '85609';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(85609, 2302.30, -5340.62, 90.75, 5.51);

DELETE FROM `spell_area` WHERE `spell` = '94568' AND `quest_start` = '27527';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(94568, 2268, 27527, 0, 0, 0, 2, 1, 74, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (776728, 776729);

-- Plaguewood Reanimator
SET @ENTRY := 45897;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,6500,6500,11,16583,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Shock"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,1000,1000,10000,10000,11,85550,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Reanimate Corpsebeast");

DELETE FROM `conditions` WHERE `SourceEntry` = '85601';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85601, 0, 0, 31, 0, 3, 45895, 0, 0, 0, '', 'Targeting -> Corpsebeast');

DELETE FROM `conditions` WHERE `SourceEntry` = '82545';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 82545, 0, 0, 31, 0, 3, 45895, 0, 0, 0, '', 'Targeting -> Corpsebeast');

UPDATE `creature_template` SET `speed_walk`=0.001, `speed_run`=0.001 WHERE `entry`=45921;

DELETE FROM `spell_script_names` WHERE `spell_id` = '85590';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85590, 'spell_summon_argent_lightwell');

UPDATE `creature_template` SET `faction_A`=35, `faction_H`=35 WHERE `entry`=45956;
UPDATE `creature_template` SET `faction_A`=35, `faction_H`=35 WHERE `entry` IN (46199, 46201, 46200, 45960);
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (45783, 45782, 46194, 45941, 46178, 45434, 45433, 45921, 45965, 45956);

DELETE FROM `waypoints` WHERE `entry` IN (46199, 46200, 45960);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(46199, 1, 3006.19, -3432.55, 149.7, 'Tarenar Attack WP'),
(46200, 1, 3004.83, -3429.55, 149.7, 'Argus Attack WP'),
(45960, 1, 3009.11, -3430.67, 149.7, 'Rimblat Attack WP');

-- GFR Event Camera
SET @ENTRY := 45965;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,85649,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon Gidwin"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,85,85650,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon Anastari"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,85,85651,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Summon Tarenar"),
(@ENTRY,@SOURCETYPE,3,4,38,0,100,0,0,1,0,0,85,85680,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Summon Hero"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,85,85682,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Mirror Image"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,85,85652,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Summon Fiona"),
(@ENTRY,@SOURCETYPE,6,7,38,0,100,0,0,2,0,0,85,85655,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Summon Argus"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,8,9,61,0,100,0,0,0,0,0,53,1,45965,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - WP Start"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,85,85653,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Rimblat"),
(@ENTRY,@SOURCETYPE,10,0,40,0,100,0,2,0,0,0,54,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause"),
(@ENTRY,@SOURCETYPE,11,12,38,0,100,0,0,10,0,0,33,45940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Quest Complete"),
(@ENTRY,@SOURCETYPE,12,0,61,0,100,0,0,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove From Vehicle");

-- Baroness Anastari
SET @ENTRY := 45956;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45956,0,0,45,0,1,0,0,0,0,11,45965,100,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Camera"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45956,0,0,45,0,2,0,0,0,0,11,45965,100,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Camera"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,5,0,0,17,438,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Set Emote Attack"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,4,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Die"),
(@ENTRY,@SOURCETYPE,6,0,6,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,0,80,0,0.0,0.0,0.0,0.0,"On Death - Set Data 10 to Creatures");

-- Rimblat Earthshatter
SET @ENTRY := 45960;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,3009.24,-3442.43,149.7,1.72,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,5,0,0,53,1,45960,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - WP Start"),
(@ENTRY,@SOURCETYPE,2,0,39,0,100,0,0,0,0,0,17,438,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Emote Attack"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,10,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Force Despawn");

-- Your Doppelganger
SET @ENTRY := 45978;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,0,97650,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - None"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,85682,0,0,0,0,0,8,0,0,0,3003.0,-3438.34,149.7,1.39,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,5,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn");

-- Fiona
SET @ENTRY := 45959;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45959,0,0,45,0,1,0,0,0,0,11,45678,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Tarenar"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45959,0,0,45,0,2,0,0,0,0,11,45678,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Tarenar"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,3,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45959,0,0,45,0,2,0,0,0,0,11,45958,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Argus"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,4,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3");

-- Argus Highbeacon
SET @ENTRY := 46200;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,3001.91,-3440.76,149.7,1.35,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,1,8,0,0,0,1,0,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,46200,0,0,45,0,1,0,0,0,0,11,46199,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Tarenar"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,5,0,0,53,1,46200,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - WP Start"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,1,0,0,0,17,438,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Emote Attack"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,10,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Force Despawn");

-- Tarenar Sunstrike
SET @ENTRY := 46199;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,3006.64,-3439.41,149.7,1.33,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,3,34,0,100,1,8,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,46199,0,0,45,0,2,0,0,0,0,11,45956,25,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 2 to Anastari"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,5,25,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Emote Point"),
(@ENTRY,@SOURCETYPE,4,5,38,0,100,0,0,1,0,0,1,1,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,7,61,0,100,0,0,0,0,0,53,1,46199,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - WP Start"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,1,0,0,0,17,438,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Emote Attack"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,0,80,0,0.0,0.0,0.0,0.0,"Link - Set Data 5 to Creatures"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,10,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Force Despawn"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,1,46199,0,0,45,0,4,0,0,0,0,11,45956,80,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 4 to Anastari");

-- Gidwin Goldbraids
SET @ENTRY := 45955;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45955,0,0,45,0,1,0,0,0,0,11,45956,15,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Anastari"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,75,75511,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Sleep"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,10,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Force Despawn");

DELETE FROM `creature_template_addon` WHERE `entry` IN (45955, 46199, 46200, 45959, 45978, 45960, 45956, 45965);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(45955, '60191'),
(46199, '60191'),
(46200, '60191'),
(45959, '60191'),
(45978, '60191'),
(45960, '60191'),
(45956, '60191'),
(45965, '60191');

UPDATE `creature` SET `id`=45895 WHERE `id` IN (45893, 45886);