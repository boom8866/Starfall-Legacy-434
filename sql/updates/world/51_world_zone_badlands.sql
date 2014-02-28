DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27762 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=28579 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27762 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=28580 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=16378;
UPDATE `creature_template_addon` SET `auras`='' WHERE `auras`='87871';
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=48708;
UPDATE `creature_template` SET `VehicleId`=1577, `InhabitType`=4, `minlevel`=44, `maxlevel`=44 WHERE `entry`=48766;

DELETE FROM `waypoints` WHERE `entry` = '48766';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(48766, 1, 2260.16, -5285.67, 145.74, 'The Uncrashable WP'),
(48766, 2, 1753.68, -2543.16, 294.77, 'The Uncrashable WP'),
(48766, 3, 1063.61, -2351.49, 199.13, 'The Uncrashable WP'),
(48766, 4, 676.70, -2412.21, 380.55, 'The Uncrashable WP'),
(48766, 5, -3435.23, -3449.01, 390.91, 'The Uncrashable WP'),
(48766, 6, -4083.78, -2648.55, 263.48, 'The Uncrashable WP'),
(48766, 7, -4615.41, -2671.05, 455.23, 'The Uncrashable WP'),
(48766, 8, -6631.60, -3842.47, 487.14, 'The Uncrashable WP'),
(48766, 9, -6461.89, -4487.31, 339.56, 'The Uncrashable WP'),
(48766, 10, -6613.39, -4713.79, 12.29, 'The Uncrashable WP');

UPDATE `creature_template` SET `speed_run`=5 WHERE `entry`=48766;
UPDATE `creature_template` SET `mindmg`=48, `maxdmg`=78, `attackpower`=18, `dmg_multiplier`=1.4 WHERE `entry` IN (46694, 46693, 46695);

-- The Uncrashable
SET @ENTRY := 48766;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,86,46598,0,21,5,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,53,1,48766,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - WP Start"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,10,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger");

-- The Uncrashable
SET @ENTRY := 48708;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,12,48766,8,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Creature");

DELETE FROM `spell_area` WHERE `spell` = '84481' AND `quest_start` = '27764';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`, `aura_spell`) VALUES
(84481, 5519, 27764, 1, 74, 0, -49417);

-- Dustbelcher Initiate
SET @ENTRY := 46694;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3500,3500,11,9053,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fireball");

-- Dustbelcher Trainee
SET @ENTRY := 46695;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3500,3500,11,9053,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fireball");

-- Dustbelcher Instructor
SET @ENTRY := 46693;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,6742,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Bloodlust"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,3500,3500,11,20822,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt");

DELETE FROM `creature_loot_template` WHERE `item` = '62390';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(2725, 62390, -61.4753, 1, 0, 1, 1);

UPDATE `creature_template_addon` SET `auras`='87169', `bytes1`=3 WHERE `entry`=46658;

DELETE FROM `spell_area` WHERE `spell` = '90418' AND `quest_start` = '27770';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(90418, 5519, 27770, 27771, 1, 74);

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '27770';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 5519, 27770, 27771, 1, 74);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '90418';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(90418, 91202, 'Vulcanic Skyeffect -> Cast Blackout');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-90418';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-90418, 91202, 'Vulcanic Skyeffect -> Cast Blackout');

UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=773852;
UPDATE `creature_template` SET `npcflag`=0, `unit_flags`=768 WHERE  `entry`=46658;

DELETE FROM `creature_text` WHERE `entry`=46654;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46654,0,0,'I will now remove the fog from your eyes. Behold, our captive.',42,0,100,0,0,0,'Comment'),
(46654,1,0,'Deathwing\'s madness overcomes him, and we, the red dragonflight, must take this opportunity to steal his black dragons from beneath him. We will remake the black dragons as they are intended to be: the warders of the earth.',12,0,100,0,0,0,'Comment');

-- Nyxondra
SET @ENTRY := 46658;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,10000,15000,10000,15000,33,46658,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"Update - Quest complete");

UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=190074;
UPDATE `gameobject` SET `phaseMask`=2 WHERE `id`=206321;

DELETE FROM `gameobject_loot_template` WHERE `item` = '62393';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(35343, 62393, -100, 1, 0, 1, 1);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27769';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5519, 27769, 1, 66, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=773851;

-- Billy Goat
SET @ENTRY := 46393;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,86425,1,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Force Despawn ");

DELETE FROM `spell_script_names` WHERE `spell_id` = '86425';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(86425, 'spell_billy_goat_blast');

UPDATE `creature_template_addon` SET `auras`='49415' WHERE `entry`=46655;

DELETE FROM `creature_loot_template` WHERE `item` = '62650';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(2743, 62650, -56.1702, 1, 0, 1, 1),
(2742, 62650, -45.1826, 1, 0, 1, 1),
(2740, 62650, -25.7104, 1, 0, 1, 1),
(2739, 62650, -26.2125, 1, 0, 1, 1);

UPDATE `creature_template` SET `spell1`=87030, `spell2`=87034 WHERE `entry`=46707;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46707';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46707, 46598, 1);

-- Blam Turret
SET @ENTRY := 46707;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46707,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,1,1,2500,3500,11,87029,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Wave 1"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,1,1,4000,4500,11,87031,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Summon Wave 2"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,0,30000,30000,300000,300000,11,87073,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Credit Wave 1"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,0,60000,60000,300000,300000,11,87074,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Credit Wave 2"),
(@ENTRY,@SOURCETYPE,6,0,60,1,100,0,90000,90000,300000,300000,11,87075,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Credit Wave 3"),
(@ENTRY,@SOURCETYPE,7,0,60,1,100,0,120000,120000,300000,300000,11,87076,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Credit Wave 4"),
(@ENTRY,@SOURCETYPE,8,0,61,1,100,0,0,0,0,0,33,46739,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit 3"),
(@ENTRY,@SOURCETYPE,9,0,61,1,100,0,0,0,0,0,33,46740,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit 4"),
(@ENTRY,@SOURCETYPE,10,0,28,1,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Set Phase 0");

-- Stonevault Ruffian
SET @ENTRY := 46711;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Invoker"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

-- Stonevault Goon
SET @ENTRY := 46712;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Invoker"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

UPDATE `creature_template` SET `VehicleId`=1214 WHERE `entry`=46707;
UPDATE `creature_template` SET `speed_run`=2.14,`mindmg`=69, `maxdmg`=103, `attackpower`=26, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (46712, 46711);

DELETE FROM `creature_text` WHERE `entry`=46707;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46707,0,0,'Survive to four waves!',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1 WHERE `entry`=46707;
DELETE FROM `creature` WHERE `id` IN (46711, 46712);

DELETE FROM `creature` WHERE `guid` IN (793980, 793981, 793982);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(793980, 46654, 0, 1, 1, 0, 0, -6721.43, -2457.11, 272.837, 1.46918, 300, 0, 0, 77490, 0, 0, 0, 0, 0),
(793981, 46654, 0, 1, 1, 0, 0, -6522.32, -2391.9, 295.714, 4.29202, 300, 0, 0, 77490, 0, 0, 0, 0, 0),
(793982, 46654, 0, 1, 1, 0, 0, -7052.6, -2585.03, 255.79, 0.798133, 300, 0, 0, 77490, 0, 0, 0, 0, 0);

DELETE FROM `spell_area` WHERE `spell` IN (60922, 90161) AND `quest_start` IN (27889, 27897, 27898, 27826, 27832, 27858);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60922, 5565, 27889, 0, 1, 74, 0),
(60922, 5564, 27826, 0, 1, 74, 0),
(90161, 5592, 27897, 27897, 1, 2, 11),
(90161, 5592, 27898, 27898, 1, 75, 11),
(90161, 5592, 27832, 27832, 1, 2, 11),
(90161, 5592, 27858, 27858, 1, 75, 11);

UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (47011, 47018, 47013);
UPDATE `creature_template_addon` SET `auras`='49415' WHERE `entry` IN (47011, 47018, 47013);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27890';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5565, 27890, 1, 74, 0);

DELETE FROM `creature_text` WHERE `entry`=46664;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46664,0,0,'I suppose we\'ll just have to throw these away... WAIT! I think I\'m having an idea. ',12,0,100,0,0,0,'Comment'),
(46664,1,0,'Yes, definately an idea. ',12,0,100,0,0,0,'Comment');

-- Dr. Hieronymus Blam
SET @ENTRY := 46664;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27789,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46664,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

UPDATE `quest_template` SET `PrevQuestId`='27888' WHERE `Id`=27889;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=46344;
UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id` IN (27885, 27693);
UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id` IN (27709, 27886);

-- Stone Slab
SET @ENTRY := 206335;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27885,0,0,0,12,46339,8,0,0,0,0,8,0,0,0,-6964.62,-3444.98,200.89,6.22,"On Quest Accept - Summon Warden's Game Controller"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27693,0,0,0,12,46339,8,0,0,0,0,8,0,0,0,-6964.62,-3444.98,200.89,6.22,"On Quest Accept - Summon Warden's Game Controller");

-- Warden's Game Controller
SET @ENTRY := 46339;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6966.41,-3443.17,200.89,3.05,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6966.58,-3445.14,200.89,3.07,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6966.59,-3447.12,200.89,3.09,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,3,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6964.61,-3447.2,200.89,4.67,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6962.16,-3447.29,200.89,4.67,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6962.03,-3445.19,200.89,6.22,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,6,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6961.82,-3442.76,200.89,6.23,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,7,0,37,0,100,0,0,0,0,0,12,46344,4,30000,0,0,0,8,0,0,0,-6964.6,-3442.55,200.89,1.49,"On Just Summoned - Summon Pawn"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,1,0,0,45,0,1,0,0,0,0,11,46344,2,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Data 1 to Pawn");

DELETE FROM `gameobject_involvedrelation` WHERE `id` = '206335' AND `quest` IN (27885, 27693);
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(206335, 27885),
(206335, 27693);

DELETE FROM `gameobject_involvedrelation` WHERE `id` = '206336' AND `quest` IN (27709, 27886);
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(206336, 27709),
(206336, 27886);

DELETE FROM `creature_involvedrelation` WHERE `id` = '46757' AND `quest` IN (27887, 27793);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(46757, 27887),
(46757, 27793);

UPDATE `gameobject_template` SET `ScriptName`='go_marble_slab' WHERE `entry`=206336;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=46395;
UPDATE `creature_template` SET `ScriptName`='npc_sentinel_pawn' WHERE `entry`=46395;
UPDATE `creature_template` SET `ScriptName`='npc_sentinel_start' WHERE `entry`=46397;

-- Sentinel's Pawn
SET @ENTRY := 46395;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,86555,1,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Force Despawn"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,5,64,0,5,0,0,0,0,0,66,15,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Orientation"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,92,0,86432,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Interrupt Spell"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,11,86432,0,0,0,0,0,19,46395,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Cast Beam"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,33,46398,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,85,86555,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Despawn");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12147 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12146 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12146;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12146, 0, 0, 0, 9, 0, 27887, 0, 0, 0, 0, 0, '', 'The Warden - Show gossip only if quest 27887 is active'),
(15, 12146, 0, 0, 1, 9, 0, 27793, 0, 0, 0, 0, 0, '', 'The Warden - Show gossip only if quest 27793 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=12147;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12147, 0, 0, 0, 9, 0, 27887, 0, 0, 0, 0, 0, '', 'The Sentinel - Show gossip only if quest 27887 is active'),
(15, 12147, 0, 0, 1, 9, 0, 27793, 0, 0, 0, 0, 0, '', 'The Sentinel - Show gossip only if quest 27793 is active');

-- The Sentinel
SET @ENTRY := 46769;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12147,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,4,62,0,100,0,12147,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Turn Hostile"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,6000,6000,6000,6000,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Return Friendly"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1000,1000,10000,10000,11,83368,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heave"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,28,87134,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Freeze");

-- The Warden
SET @ENTRY := 46768;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12146,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,4,62,0,100,0,12146,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Turn Hostile"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,6000,6000,6000,6000,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Return Friendly"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1000,1000,10000,10000,11,83370,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shockwave"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,28,87134,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Freeze");

UPDATE `creature_template` SET `mindmg`=69, `maxdmg`=103, `attackpower`=26 WHERE `entry` IN (46769, 46768);
UPDATE `creature` SET `position_z`=242.08 WHERE `guid`=190266;
UPDATE `creature_template_addon` SET `bytes1`=0 WHERE `entry`=46757;

DELETE FROM `creature_questrelation` WHERE `id` = '46757' AND `quest` = '27913';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(46757, 27913);

UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id` IN (27912, 27913);
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=729028;

-- Trove of the Watchers
SET @ENTRY := 206374;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip");

UPDATE `gameobject` SET `phaseMask`=2, `spawntimesecs`=60 WHERE `id`=206108;
UPDATE `creature_template` SET `minlevel`=47, `maxlevel`=47, `VehicleId`=1187 WHERE `entry`=46466;

DELETE FROM `creature_text` WHERE `entry`=46466;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46466,0,0,'I remember it well. It was a bright, shiny day...',42,0,100,0,0,0,'Comment'),
(46466,1,0,'I was just mindin\' my own business, when all of a sudden, Deathwing appeared! ',42,0,100,0,0,0,'Comment'),
(46466,2,0,'I said to myself, "I\'m gonna punch that dragon in the face!"',42,0,100,0,0,0,'Comment'),
(46466,3,0,'I\'m gonna punch that dragon in the face! ',14,0,100,0,0,0,'Comment'),
(46466,4,0,'Unfortunately, the cataclysm had knocked loose a bunch of angry elementals. ',42,0,100,0,0,0,'Comment'),
(46466,5,0,'You dang-blasted rock elementals!',14,0,100,0,0,0,'Comment'),
(46466,6,0,'I\'ll punch you too!',14,0,100,0,0,0,'Comment'),
(46466,7,0,'P-p-punch!',12,0,100,0,0,0,'Comment'),
(46466,7,1,'Face punch!',12,0,100,0,0,0,'Comment'),
(46466,7,2,'Take that, dangerous enemy!',12,0,100,0,0,0,'Comment'),
(46466,7,3,'Theldurin the Lost!',12,0,100,0,0,0,'Comment'),
(46466,7,4,'Get punched!',12,0,100,0,0,0,'Comment'),
(46466,7,5,'I\'m going to punch that dragon right in the face!',12,0,100,0,0,0,'Comment'),
(46466,7,6,'I\'m coming for you, Deathwing!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `InhabitType`=4, `speed_walk`=4.14, `speed_run`=4.14286, `movementId`=113 WHERE `entry`=46484;

DELETE FROM `waypoints` WHERE `entry` = '46484';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(46484, 1, -6732.66, -3177.63, 324.40, 'TDDC Deathwing WP');

DELETE FROM `creature_template_addon` WHERE `entry` = '46484';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(46484, 512, '50195');

UPDATE `creature_template` SET `spell1`=86561 WHERE `entry`=46466;
UPDATE `creature` SET `phaseMask`=2, `spawntimesecs`=60, `spawndist`=15, `MovementType`=1 WHERE `id`=46467;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=46467;
UPDATE `creature` SET `phaseMask`=2, `spawntimesecs`=60 WHERE `id`=46471;
UPDATE `quest_template` SET `PrevQuestId`='27713' WHERE `Id`=27714;
UPDATE `quest_template` SET `PrevQuestId`='27714' WHERE `Id`=27715;

DELETE FROM `creature_text` WHERE `entry`=2920;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2920,0,0,'No, no, no, Theldurin. You\'re telling the story wrong!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=47, `maxlevel`=47, `VehicleId`=1239, `spell1`=87743, `spell2`=87777 WHERE `entry`=47080;

DELETE FROM `creature_text` WHERE `entry`=47080;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47080,1,0,'First of all, it wasn\'t sunny out. It was cloudy when Deathwing appeared.',42,0,100,0,0,0,'Comment'),
(47080,2,0,'The cowardly dragon must have seen me, because he turned away and flew into the clouds.',42,0,100,0,0,0,'Comment'),
(47080,3,0,'"I\'ll find you in those clouds, you worm!" I yelled. "And then I\'ll throw you to Kalimdor!" ',42,0,100,0,0,0,'Comment'),
(47080,4,0,'I\'ll find you in those clouds, you worm!',14,0,100,0,0,0,'Comment'),
(47080,5,0,'And then I\'ll throw you to Kalimdor!',14,0,100,0,0,0,'Comment'),
(47080,6,0,'Luckily, I had been tinkering with my world-shrinking device.',42,0,100,0,0,0,'Comment'),
(47080,7,0,'I decided to keep shrinking the world until I could reach the clouds.',42,0,100,0,0,0,'Comment'),
(47080,8,0,'Once the world was small enough, I started to hunt for Deathwing in the clouds.',42,0,100,0,0,0,'Comment'),
(47080,9,0,'When I find that dragon, I\'m gonna throw him to Kalimdor.',12,0,100,0,0,0,'Comment'),
(47080,9,1,'Surprise, dragon! Aw, shucks.',12,0,100,0,0,0,'Comment'),
(47080,9,2,'Where you at?',12,0,100,0,0,0,'Comment'),
(47080,9,3,'Where are you, dragon?',12,0,100,0,0,0,'Comment'),
(47080,9,4,'He can\'t have gotten far...',12,0,100,0,0,0,'Comment'),
(47080,10,0,'I had searched every cloud, but I couldn\'t find Deathwing.',42,0,100,0,0,0,'Comment'),
(47080,11,0,'It was then that I realized: he was hiding in the sun. I looked up.',42,0,100,0,0,0,'Comment'),
(47080,12,0,'The sun burned me bad, but I got my hands around his slimy neck.',42,0,100,0,0,0,'Comment'),
(47080,13,0,'I summoned all my strength, faced west, and threw him to Kalimdor.',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=47097;
UPDATE `creature` SET `phaseMask`=4, `spawndist`=0, `MovementType`=0 WHERE `id`=47097;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `InhabitType`=4, `speed_walk`=4.14, `speed_run`=4.14286 WHERE `entry`=46502;

DELETE FROM `creature_template_addon` WHERE `entry` = '46502';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(46502, 512, '50195');

DELETE FROM `waypoints` WHERE `entry` = '46502';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(46502, 1, -7056.57, -2776.76, 296.26, 'TDDC 2 Deathwing WP'),
(46502, 2, -6927.26, -2721.52, 334.38, 'TDDC 2 Deathwing WP');

UPDATE `creature_template` SET `faction_A`=31, `faction_H`=31 WHERE `entry`=47097;

UPDATE `creature` SET `spawntimesecs`=30 WHERE `guid`=47097;
UPDATE `creature_template` SET `scale`=1, `unit_flags`=512 WHERE `entry`=47103;

DELETE FROM `creature_text` WHERE `entry`=2785;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2785,0,0,'Wow, Lucien. You need to stop drinking RIGHT NOW.',12,0,100,0,0,0,'Comment'),
(2785,1,0,'Sorry about the interruption, Martek. You\'ve gotta admit though... I made your story about fifty times better. Next drink\'s on me.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=47, `maxlevel`=47, `VehicleId`=1191 WHERE `entry`=46501;

DELETE FROM `creature_text` WHERE `entry`=46501;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46501,0,0,'The day that Deathwing came, blood rained from the skies.',42,0,100,0,0,0,'Comment'),
(46501,1,0,'I believe I was showing my motorcycle to some hot babes at the time.',42,0,100,0,0,0,'Comment'),
(46501,2,0,'After Deathwing appeared, they became quite frightened, but I only had room to rescue one of them.',42,0,100,0,0,0,'Comment'),
(46501,3,0,'Obviously, I picked the <race>.',42,0,100,0,0,0,'Comment'),
(46501,4,0,'We rode off down the canyon, careful to avoid falling rocks.',42,0,100,0,0,0,'Comment'),
(46501,5,0,'When I reached the end of the canyon, I remembered that my motorcycle could fly.',42,0,100,0,0,0,'Comment'),
(46501,6,0,'That would have been helpful to know earlier.',42,0,100,0,0,0,'Comment'),
(46501,7,0,'I flew up to the pillar located just north of the canyon.',42,0,100,0,0,0,'Comment'),
(46501,8,0,'During the flight, I shared a tender moment with the <strapping/grateful young> <race>.',0,0,100,0,0,0,'Comment'),
(46501,9,0,'Atop the pillar, I saw him: Deathwing. The time for the ultimate confrontation had arrived.',42,0,100,0,0,0,'Comment'),
(46501,10,0,'I\'m gonna punch that dragon in the face!',14,0,100,0,0,0,'Comment'),
(46501,11,0,'Hey, stop it Theldurin! This is my story!',14,0,100,0,0,0,'Comment'),
(46501,12,0,'Cut it out guys! Quit interrupting!',42,0,100,0,0,0,'Comment'),
(46501,13,0,'Fine. You don\'t get to hear about how I beat Deathwing in a knife fight. Your loss.',42,0,100,0,0,0,'Comment');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12205 AND `id`=0;
UPDATE `creature_template` SET `npcflag`=1, `gossip_menu_id`=12205 WHERE `entry` IN (47123, 47124, 47125, 47126);

-- Deathwing
SET @ENTRY := 46502;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,46502,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,2,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Force Despawn");

-- Theldurin the Lost
SET @ENTRY := 46466;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,1000,1000,1000,1000,1,0,10000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update (2 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,1,100,0,0,46466,0,0,1,1,10000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,1,100,0,0,46466,0,0,85,86628,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Deathwing"),
(@ENTRY,@SOURCETYPE,4,0,52,1,100,0,1,46466,0,0,1,2,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,0,2,46466,0,0,85,82316,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Switch Position"),
(@ENTRY,@SOURCETYPE,6,0,52,1,100,0,2,46466,0,0,75,86621,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Transform Theldurin"),
(@ENTRY,@SOURCETYPE,7,0,52,1,100,0,2,46466,0,0,1,3,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,1,100,0,3,46466,0,0,1,4,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,38,0,80,0,0,1,0,0,1,7,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 7"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,1,0,2,0,0,11,86561,0,0,0,0,0,11,46471,50,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Punch Deathwing!"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,2,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,3,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Kill Vehicle"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,1,0,1,0,0,45,0,1,0,0,0,0,11,46471,50,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Data 1 to Deathwing"),
(@ENTRY,@SOURCETYPE,14,0,52,1,100,0,4,46466,0,0,85,87782,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Switch Seat");

-- Dang-Blasted Rock Elemental
SET @ENTRY := 46467;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Theldurin");

-- Deathwing
SET @ENTRY := 46484;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,46484,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,60,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Fly"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,1,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Force Despawn");

-- Night Elf Admirer
SET @ENTRY := 47123;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12205,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12205,0,0,0,11,84336,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Seat for Admirer"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,4500,2500,6500,10,11,21,24,3,17,4,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Random Emote"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,12205,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Gossip Flag"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12205,0,0,0,33,47123,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12205,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0");

-- Human Admirer
SET @ENTRY := 47124;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12205,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12205,0,0,0,11,84336,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Seat for Admirer"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,4500,2500,6500,10,11,21,24,3,17,4,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Random Emote"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,12205,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Gossip Flag"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12205,0,0,0,33,47123,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12205,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0");

-- Orc Admirer
SET @ENTRY := 47125;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12205,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12205,0,0,0,11,84336,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Seat for Admirer"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,4500,2500,6500,10,11,21,24,3,17,4,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Random Emote"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,12205,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Gossip Flag"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12205,0,0,0,33,47123,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12205,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0");

-- Blood Elf Admirer
SET @ENTRY := 47126;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12205,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12205,0,0,0,11,84336,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Seat for Admirer"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,4500,2500,6500,10,11,21,24,3,17,4,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Random Emote"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,12205,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Gossip Flag"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12205,0,0,0,33,47123,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12205,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0");

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46501';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46501, 84319, 0);

DELETE FROM `creature_text` WHERE `entry`=47126;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47126,0,0,'Obviously, I picked the Blood Elf.',42,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=47125;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47125,0,0,'Obviously, I picked the Orc.',42,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=47124;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47124,0,0,'Obviously, I picked the Human.',42,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=47123;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47123,0,0,'Obviously, I picked the Night Elf.',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `spell1`=87851 WHERE `entry`=46501;
UPDATE `creature` SET `phaseMask`=8 WHERE `id`=47128;

UPDATE `creature` SET `phaseMask`=8 WHERE `guid`=762537;

-- Deathwing
SET @ENTRY := 46471;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1500,1500,1500,1500,45,0,2,0,0,0,0,11,46466,8,0,0.0,0.0,0.0,0.0,"Update (1.5 secs) - Set Data 2 to Theldurin"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,8000,8000,8000,8000,45,0,3,0,0,0,0,11,46466,8,0,0.0,0.0,0.0,0.0,"Update (8.0 secs) - Set Data 3 to Theldurin"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,1500,1500,1500,45,0,2,0,0,0,0,11,46501,80,0,0.0,0.0,0.0,0.0,"Update (1.5 secs) - Set Data 2 to Martek's Hog"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,11,87912,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Punch on Self");

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=46471;

DELETE FROM `creature_text` WHERE `entry`=47157;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47157,0,0,'I\'m gonna punch that dragon in the face!',14,0,100,0,0,0,'Comment');

-- Theldurin the Lost
SET @ENTRY := 47157;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-6651.56,-3108.21,340.69,6.23,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,1,0,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,47157,0,0,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,47157,0,0,45,0,5,0,0,0,0,11,46501,80,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 5 to Martek");

-- Martek's Hog
SET @ENTRY := 46501;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,2500,2500,2500,2500,1,0,8000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update (1.5 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,1,100,0,0,46501,0,0,1,1,12000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,1,0,0,0,0,85,86628,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Summon Deathwing"),
(@ENTRY,@SOURCETYPE,4,0,52,1,100,0,0,46501,0,0,85,87823,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Admirer"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,0,0,46501,0,0,85,87824,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Admirer"),
(@ENTRY,@SOURCETYPE,6,0,52,1,100,0,0,46501,0,0,85,87825,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Admirer"),
(@ENTRY,@SOURCETYPE,7,0,52,1,100,0,0,46501,0,0,85,87826,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Admirer"),
(@ENTRY,@SOURCETYPE,8,0,52,1,100,0,0,46501,0,0,75,86680,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Display"),
(@ENTRY,@SOURCETYPE,9,0,52,1,100,0,0,46501,0,0,85,82316,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Switch Seat"),
(@ENTRY,@SOURCETYPE,10,0,52,1,100,0,1,46501,0,0,1,2,8000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,11,0,52,1,100,0,0,46501,0,0,12,4618,6,300000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Martek"),
(@ENTRY,@SOURCETYPE,12,0,38,1,100,1,0,2,0,0,1,9,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 9"),
(@ENTRY,@SOURCETYPE,13,0,52,1,100,0,9,46501,0,0,33,47179,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Quest Credit "),
(@ENTRY,@SOURCETYPE,14,0,52,1,100,0,9,46501,0,0,85,87857,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Summon Theldurin"),
(@ENTRY,@SOURCETYPE,15,0,52,1,100,0,2,46501,0,0,85,87782,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Switch Seat"),
(@ENTRY,@SOURCETYPE,16,0,38,1,100,1,0,5,0,0,1,11,8000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 11"),
(@ENTRY,@SOURCETYPE,17,0,52,1,100,0,11,46501,0,0,1,12,8000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 11 - Talk 12"),
(@ENTRY,@SOURCETYPE,18,0,52,1,100,0,12,46501,0,0,1,13,8000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 12 - Talk 13"),
(@ENTRY,@SOURCETYPE,19,0,52,1,100,0,12,46501,0,0,33,46471,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"After Talk 12 - Quest Credit"),
(@ENTRY,@SOURCETYPE,20,0,52,1,100,0,13,46501,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 13 - Die"),
(@ENTRY,@SOURCETYPE,21,0,52,1,100,0,9,46501,0,0,85,87858,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Summon Lucien"),
(@ENTRY,@SOURCETYPE,22,0,52,1,100,0,1,46501,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Invisibility");

-- Lucien Tosselwrench
SET @ENTRY := 47163;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,1,0,0,0,0,0,8,0,0,0,-6553.79,-3103.25,267.24,3.05,"On Just Summoned - Move to Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

DELETE FROM `creature_template_addon` WHERE `entry`=47128;

-- Cave In Trigger
SET @ENTRY := 47128;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,15000,17500,12500,11,87843,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Cast Cave In");

DELETE FROM `spell_area` WHERE `spell` = '60191' AND `quest_start` IN (27713, 27714, 27715);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(60191, 1878, 27713, 27713, 1, 8),
(60191, 5322, 27713, 27713, 1, 8),
(60191, 1878, 27714, 27714, 1, 8),
(60191, 5322, 27714, 27714, 1, 8);

UPDATE `creature_template` SET `InhabitType`=3, `flags_extra`=0 WHERE `entry`=2734;

-- Theldurin the Lost
SET @ENTRY := 2785;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27713,0,0,0,75,60191,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Set Player Invisibility"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27713,0,0,0,85,86557,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Theldurin"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,27713,0,0,0,45,0,1,0,0,0,0,10,190877,2920,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Lucien Tosselwrench"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,10,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 1");

-- Cowardly Deathwing
SET @ENTRY := 47103;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,11,64138,0,0,0,0,0,11,47080,50,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Lucien"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,47080,80,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 10 to Lucien");

-- Lucien Tosselwrench
SET @ENTRY := 47080;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,1000,1000,1000,1000,1,1,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update (1 sec) - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,1,100,0,1,47080,0,0,1,2,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,1,100,100,100,100,85,86681,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (100 ms) - Summon Deathwing"),
(@ENTRY,@SOURCETYPE,4,0,52,1,100,0,2,47080,0,0,1,3,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,0,2,47080,0,0,85,82316,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Change Seat"),
(@ENTRY,@SOURCETYPE,6,0,52,1,100,0,3,47080,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,7,0,52,1,100,0,3,47080,0,0,75,87748,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Transform Lucien"),
(@ENTRY,@SOURCETYPE,8,0,52,1,100,0,4,47080,0,0,1,5,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,52,1,100,0,5,47080,0,0,1,6,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,10,0,52,1,100,0,6,47080,0,0,1,7,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,11,0,38,1,100,0,0,10,0,0,1,12,10000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 12"),
(@ENTRY,@SOURCETYPE,12,0,52,1,100,0,6,47080,0,0,75,87808,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Add Helm"),
(@ENTRY,@SOURCETYPE,13,0,52,1,100,0,7,47080,0,0,85,87782,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Switch Seat"),
(@ENTRY,@SOURCETYPE,14,0,52,1,100,0,7,47080,0,0,1,8,2000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,15,0,52,1,100,0,2,47080,0,0,75,87748,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Transform Lucien"),
(@ENTRY,@SOURCETYPE,16,0,52,1,100,0,12,47080,0,0,28,64138,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 12 - Remove Deathwing"),
(@ENTRY,@SOURCETYPE,17,0,52,1,100,0,12,47080,0,0,1,13,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 12 - Talk 13"),
(@ENTRY,@SOURCETYPE,18,0,52,1,100,0,13,47080,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 13 - Die"),
(@ENTRY,@SOURCETYPE,19,0,52,1,100,1,8,47080,0,0,1,8,2000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 8 - Talk 8");

-- Lucien Tosselwrench
SET @ENTRY := 2920;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27714,0,0,0,75,60191,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Set Player Invisibility"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,27714,0,0,0,85,87737,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Lucien"),
(@ENTRY,@SOURCETYPE,3,0,20,0,100,0,27714,0,0,0,45,0,1,0,0,0,0,10,190876,2785,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Theldurin");

-- Martek the Exiled
SET @ENTRY := 4618;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27715,0,0,0,85,86675,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Martek's Hog"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,11,84319,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Flags"),
(@ENTRY,@SOURCETYPE,3,0,20,0,100,0,27715,0,0,0,45,0,10,0,0,0,0,10,190876,2785,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 10 to Theldurin"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invisibility");

DELETE FROM `creature_template_addon` WHERE `entry` IN (47080, 46466, 47157, 47163, 47123, 47124, 47125, 47126);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(47080, '60191'),
(46466, '60191'),
(47157, '60191'),
(47163, '60191'),
(47123, '60191'),
(47124, '60191'),
(47125, '60191'),
(47126, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '47103';
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(47103, 0, 0, 50331648, 1, 0, '87818');

SET @OGUID := 400050;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+68;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(400050, 205578, 0, 1, 8, -6652.38, -3099.19, 341.232, 4.89449, 0, 0, 0.639884, -0.768472, 300, 0, 1),
(400051, 205578, 0, 1, 8, -6649.97, -3116.74, 341.231, 1.35856, 0, 0, 0.628231, 0.778027, 300, 0, 1),
(400052, 205578, 0, 1, 8, -6641.96, -3106.84, 340.847, 3.49485, 0, 0, 0.984442, -0.175709, 300, 0, 1),
(400053, 205578, 0, 1, 8, -6642.74, -3114.89, 340.874, 2.68485, 0, 0, 0.974036, 0.226394, 300, 0, 1),
(400054, 205578, 0, 1, 8, -6650.4, -3095.88, 341.229, 4.39169, 0, 0, 0.810936, -0.585135, 300, 0, 1),
(400055, 205578, 0, 1, 8, -6643.55, -3118.28, 341.089, 2.71274, 0, 0, 0.977098, 0.212788, 300, 0, 1),
(400056, 205578, 0, 1, 8, -6640.05, -3110.64, 340.354, 3.08624, 0, 0, 0.999617, 0.0276743, 300, 0, 1),
(400057, 205578, 0, 1, 8, -6639.59, -3102.25, 341.23, 3.08624, 0, 0, 0.999617, 0.0276743, 300, 0, 1),
(400058, 205578, 0, 1, 8, -6645.07, -3097.86, 341.226, 3.75383, 0, 0, 0.953511, -0.301358, 300, 0, 1),
(400059, 205578, 0, 1, 2, -6740.09, -3189.82, 224.518, 3.03088, 0, 0, 0.998468, 0.0553282, 300, 0, 1),
(400060, 205578, 0, 1, 2, -6738.04, -3178.32, 223.246, 3.54924, 0, 0, 0.9793, -0.202415, 300, 0, 1),
(400061, 205578, 0, 1, 2, -6735.76, -3182.27, 223.719, 3.54924, 0, 0, 0.9793, -0.202415, 300, 0, 1),
(400062, 205578, 0, 1, 2, -6734.73, -3187.08, 224.6, 3.05312, 0, 0, 0.999022, 0.0442242, 300, 0, 1),
(400063, 205578, 0, 1, 2, -6757.88, -3189.74, 223.713, 0.343473, 0, 0, 0.170894, 0.98529, 300, 0, 1),
(400064, 205578, 0, 1, 2, -6754.58, -3194.42, 223.532, 0.839598, 0, 0, 0.407577, 0.913171, 300, 0, 1),
(400065, 205578, 0, 1, 2, -6748.97, -3197.56, 223.538, 2.21885, 0, 0, 0.895442, 0.445177, 300, 0, 1),
(400066, 205578, 0, 1, 2, -6734.09, -3191.59, 225.125, 2.20422, 0, 0, 0.892163, 0.451713, 300, 0, 1),
(400067, 205578, 0, 1, 2, -6738.86, -3195.24, 224.627, 1.89035, 0, 0, 0.810599, 0.585602, 300, 0, 1),
(400068, 205578, 0, 1, 2, -6744.34, -3197.05, 223.939, 1.89035, 0, 0, 0.810599, 0.585602, 300, 0, 1);

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=46501;

UPDATE `creature_template` SET `VehicleId`=1187, `spell1`=87608, `spell2`=87609, `mindmg`=109, `maxdmg`=215, `attackpower`=25, `dmg_multiplier`=2.1 WHERE `entry`=47021;
UPDATE `creature_template` SET `VehicleId`=1187, `spell1`=87606, `spell2`=87607, `mindmg`=109, `maxdmg`=215, `attackpower`=25, `dmg_multiplier`=2.1 WHERE `entry`=47022;
UPDATE `creature_template` SET `VehicleId`=1187, `spell1`=38382, `spell2`=87596, `mindmg`=109, `maxdmg`=215, `attackpower`=25, `dmg_multiplier`=2.1 WHERE `entry`=47024;

-- Darkflight Flameblade
SET @ENTRY := 46917;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,8599,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Enrage"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,40000,40000,11,38793,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flameblade");

-- Darkflight Shadowspeaker
SET @ENTRY := 46918;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,18266,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Curse of Agony"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1500,1500,4500,4500,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadowbolt");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (87589, 87590, 87591);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(87589, -49417, 'KEF Effects remove Invis Detection Auras'),
(87590, -49417, 'KEF Effects remove Invis Detection Auras'),
(87591, -49417, 'KEF Effects remove Invis Detection Auras');

UPDATE `creature_template` SET `mindmg`=67, `maxdmg`=99, `attackpower`=25, `dmg_multiplier`=1.1 WHERE `entry` IN
(47073, 46917, 46918, 46915, 46859, 46938, 46860, 46916, 46981, 51352);

-- Amakkar
SET @ENTRY := 47011;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27891,0,0,0,85,87589,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Amakkar"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27894,0,0,0,85,87589,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Amakkar");

-- Gargal
SET @ENTRY := 47013;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27893,0,0,0,85,87590,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Gargal"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27894,0,0,0,85,87590,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Gargal");

-- Jurrix Whitemane
SET @ENTRY := 47018;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27892,0,0,0,85,87591,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Jurrix"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27894,0,0,0,85,87591,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Jurrix");

UPDATE `quest_template` SET `PrevQuestId`='27930' WHERE `Id`=27859;
UPDATE `creature_involvedrelation` SET `id`=47011 WHERE `quest`=27891;
UPDATE `creature_involvedrelation` SET `id`=47018 WHERE `quest`=27892;
UPDATE `creature_involvedrelation` SET `id`=47013 WHERE `quest`=27893;

DELETE FROM `creature_questrelation` WHERE `id` IN (47011, 47018, 47013) AND `quest` = '27894'; 
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(47011, 27894),
(47018, 27894),
(47013, 27894);

DELETE FROM `creature_questrelation` WHERE `id` IN (46852, 46853, 46854) AND `quest` = '27829'; 
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(46852, 27829),
(46853, 27829),
(46854, 27829);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (27894, 27829);

DELETE FROM `conditions` WHERE `SourceEntry` = '27894' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27894, 27891, 0),
(20, 8, 27894, 27892, 1),
(20, 8, 27894, 27893, 2);

DELETE FROM `conditions` WHERE `SourceEntry` = '27829' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27829, 27828, 0),
(20, 8, 27829, 27834, 0),
(20, 8, 27829, 27835, 0);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '19' AND `SourceEntry` = '27894';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES
(19, 27894, 8, 27891),
(19, 27894, 8, 27892),
(19, 27894, 8, 27893);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '19' AND `SourceEntry` = '27829';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES
(19, 27829, 8, 27828),
(19, 27829, 8, 27834),
(19, 27829, 8, 27835);

UPDATE `quest_template` SET `NextQuestIdChain`=0 WHERE `NextQuestIdChain`=27894;
UPDATE `quest_template` SET `PrevQuestId`='27891 27892 27893' WHERE `Id`=27894;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (27891, 27892, 27893);

UPDATE `creature_template` SET `ScriptName`='npc_amakkar' WHERE `entry`=47021;
UPDATE `creature_template` SET `ScriptName`='npc_gargal' WHERE `entry`=47022;
UPDATE `creature_template` SET `ScriptName`='npc_jurrix' WHERE `entry`=47024;

DELETE FROM `spell_area` WHERE `spell` IN (87589, 87590, 87591);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(87589, 3, 27894, 27896, 1, 74, 11),
(87590, 3, 27894, 27896, 1, 74, 11),
(87591, 3, 27894, 27896, 1, 74, 11);

DELETE FROM `spell_area` WHERE `spell` IN (87262, 87263, 87264);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(87262, 3, 27829, 27831, 1, 74, 11),
(87263, 3, 27829, 27831, 1, 74, 11),
(87264, 3, 27829, 27831, 1, 74, 11);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (87589, 87590, 87591, 87262, 87263, 87264);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87589, 'spell_summon_generic_controller'),
(87590, 'spell_summon_generic_controller'),
(87591, 'spell_summon_generic_controller'),
(87262, 'spell_summon_generic_controller'),
(87263, 'spell_summon_generic_controller'),
(87264, 'spell_summon_generic_controller');

-- Darkflight Soldier
SET @ENTRY := 46915;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,22120,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Charge"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,15000,15000,11,49807,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Whirlwind");

-- Kalaran the Annihilator
SET @ENTRY := 46859;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,51219,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Flame Breath"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,6000,12000,6000,12000,11,51219,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Breath");

DELETE FROM `creature_addon` WHERE `guid` IN (793980, 793981, 793982);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(793980, '60921'),
(793981, '82343'),
(793982, '60921');

-- Moldarr
SET @ENTRY := 46938;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,90557,0,0,0,0,0,21,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Conflagration"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,8000,8000,8000,11,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Conflagration");

-- General Jirakka
SET @ENTRY := 46860;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,5000,5000,11,10452,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Buffet"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,6000,8000,6000,8000,11,90255,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire Nova");

-- Nyxondra's Broodling
SET @ENTRY := 46916;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,11985,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Fireball"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,3500,3500,3500,11,11985,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fireball");

-- Nyxondra
SET @ENTRY := 46861;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,51219,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Flame Breath"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,6000,4000,6000,11,10452,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Buffet"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,8500,8500,8500,8500,11,51219,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Breath");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (27895, 27896, 27898, 27830, 27831, 27832);
UPDATE `creature_template` SET `VehicleId`=1230, `speed_run`=2.14286, `speed_walk`=0.8, `modelid2`=0, `flags_extra`=128 WHERE `entry`=46958;

DELETE FROM `waypoints` WHERE `entry` = '46958';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(46958, 2, -6472.11, -2468.12, 306.86, 'RG Event Camera WP'),
(46958, 3, -6462.49, -2488.01, 307.36, 'RG Event Camera WP'),
(46958, 4, -6462.49, -2488.01, 307.36, 'RG Event Camera WP'),
(46958, 5, -6485.21, -2441.41, 311.44, 'RG Event Camera WP'),
(46958, 6, -6570.81, -2403.88, 327.27, 'RG Event Camera WP');

DELETE FROM `waypoints` WHERE `entry` = '46955';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(46955, 1, -6465.81, -2482.23, 305.75, 'RG Rhea WP'),
(46955, 2, -6472.65, -2478.87, 306.36, 'RG Rhea WP'),
(46955, 3, -6462.37, -2489.00, 307.65, 'RG Rhea WP'),
(46955, 4, -6466.07, -2480.95, 305.68, 'RG Rhea WP');

DELETE FROM `creature_text` WHERE `entry`=46955;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46955,0,0,'I\'ll just leave this right here.',12,0,100,0,0,0,'Comment'),
(46955,1,0,'How\'s my little baby doing?',12,0,100,0,0,0,'Comment'),
(46955,2,0,'No... it\'s... it\'s you! NO! ',12,0,100,0,0,0,'Comment'),
(46955,3,0,'Yes. Just... just show mercy to the egg.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=46957;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46957,0,0,'You impetuous little whelp... I know exactly what you and the mortal are up to.',12,0,100,0,0,0,'Comment'),
(46957,1,0,'Are you ready to die, dragon?',12,0,100,0,0,0,'Comment'),
(46957,2,0,'Mercy?!',14,0,100,0,0,0,'Comment'),
(46957,3,0,'THERE IS NO MERCY! YOU WILL BURN FOR THIS, DRAGON!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `InhabitType`=4, `speed_run`=2.14286, `speed_walk`=2.14 WHERE `entry`=46957;
UPDATE `spell_target_position` SET `target_position_x`=-6484.97, `target_position_y`=-2438.47, `target_position_z`=301.91, `target_orientation`=5.15 WHERE `id`=87442 AND `effIndex`=0;
UPDATE `gameobject` SET `phaseMask`=3 WHERE `guid`=729029;

DELETE FROM `gameobject_involvedrelation` WHERE `quest` = '27898';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(206504, 27898);

-- Rhea
SET @ENTRY := 46955;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,53,0,46955,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,2,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,3,0,0,0,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,4,0,0,0,1,2,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,2,0,0,0,54,5000,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,3,0,0,0,54,5000,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - WP Pause"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,2,0,0,0,85,87456,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Summon Note"),
(@ENTRY,@SOURCETYPE,7,0,40,0,100,0,4,0,0,0,5,431,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Set Cower"),
(@ENTRY,@SOURCETYPE,8,0,40,0,100,0,3,0,0,0,85,87442,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Summon Deathwing"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,3,0,0,0,11,87457,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Hold Egg"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,1,0,0,1,3,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 3"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,3,46955,0,0,45,0,1,0,0,0,0,11,46957,80,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 1 to Deathwing"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,2,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Die"),
(@ENTRY,@SOURCETYPE,13,0,6,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,46957,80,0,0.0,0.0,0.0,0.0,"On Death - Set Data 2 to Deathwing"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,3,0,0,0,33,46654,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Quest Credit");

-- Deathwing
SET @ENTRY := 46957;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,12000,12000,12000,12000,1,0,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update (8 seconds) - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,1,100,0,0,46957,0,0,1,1,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,38,1,100,0,0,1,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,1,100,0,2,46957,0,0,1,3,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,0,2,46957,0,0,11,87455,0,0,0,0,0,11,46955,100,0,0.0,0.0,0.0,0.0,"After Talk 2 - Cast Flame Breath"),
(@ENTRY,@SOURCETYPE,6,0,52,1,100,0,1,46957,0,0,45,0,1,0,0,0,0,11,46955,100,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Rhea"),
(@ENTRY,@SOURCETYPE,7,0,52,1,100,0,2,46957,0,0,45,0,2,0,0,0,0,11,46955,80,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Rhea"),
(@ENTRY,@SOURCETYPE,8,0,38,1,100,0,0,2,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,9,0,34,2,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,10,0,60,2,100,1,5000,5000,5000,5000,69,0,0,0,0,0,0,8,0,0,0,-6614.17,-2394.54,333.02,2.89,"Update (5 seconds) - Move Away"),
(@ENTRY,@SOURCETYPE,11,0,60,2,100,1,1000,1000,1000,1000,60,1,0,0,0,0,0,1,0,0,0,-6614.17,-2394.54,333.02,2.89,"Update (1 seconds) - Set Fly");

-- RG Event Camera
SET @ENTRY := 46958;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-6486.05,-2443.19,308.9,5.22,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,8,0,0,0,85,87433,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Summon Rhea"),
(@ENTRY,@SOURCETYPE,3,0,34,0,100,1,8,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Walk"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,1,8,0,0,0,53,0,46958,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - WP Start"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,2,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Run"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,2,0,0,0,54,24000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause"),
(@ENTRY,@SOURCETYPE,7,0,40,0,100,0,4,0,0,0,54,41000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - WP Pause"),
(@ENTRY,@SOURCETYPE,8,0,40,0,100,0,4,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Set Walk"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,5,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Die"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,1,0,0,11,87444,0,0,0,0,0,11,46957,200,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Channel Deathwing");

-- Rhea
SET @ENTRY := 46654;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27770,0,0,0,1,0,10000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27769,0,0,0,1,1,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,46654,0,0,33,46654,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Complete Quest"),
(@ENTRY,@SOURCETYPE,3,0,19,0,100,0,27769,0,0,0,11,99709,7000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Cast Magic"),
(@ENTRY,@SOURCETYPE,4,0,20,0,100,0,27896,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Despawn All Summons"),
(@ENTRY,@SOURCETYPE,5,0,19,0,100,0,27898,0,0,0,75,60191,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Player Invisibility"),
(@ENTRY,@SOURCETYPE,6,0,19,0,100,0,27897,0,0,0,85,91202,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Blackout"),
(@ENTRY,@SOURCETYPE,7,0,19,0,100,0,27898,0,0,0,85,87436,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Start RG Event"),
(@ENTRY,@SOURCETYPE,8,0,20,0,100,0,27831,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Despawn All Summons"),
(@ENTRY,@SOURCETYPE,9,0,19,0,100,0,27832,0,0,0,85,91202,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Blackout"),
(@ENTRY,@SOURCETYPE,10,0,19,0,100,0,27858,0,0,0,75,60191,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Player Invisibility"),
(@ENTRY,@SOURCETYPE,11,0,19,0,100,0,27858,0,0,0,85,87436,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Start RG Event");

DELETE FROM `gameobject_questrelation` WHERE `quest` = '27930';
INSERT INTO `gameobject_questrelation` (`id`, `quest`) VALUES
(206504, 27930);

DELETE FROM `spell_area` WHERE `spell` = '60191' AND `quest_start` IN (27898, 27858);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(60191, 5592, 27898, 27898, 1, 8),
(60191, 5592, 27858, 27858, 1, 8);

-- Rhea's Final Note
SET @ENTRY := 206504;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27930,0,0,0,12,46664,4,120000,0,0,0,8,0,0,0,-6479.58,-2452.59,306.81,5.19,"On Quest Rewarded - Summon Dr");

-- Rhea's Child
SET @ENTRY := 51352;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,1000,1000,11,9053,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fireball");

DELETE FROM `conditions` WHERE `SourceEntry` = '27887' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27887, 27885, 0),
(20, 8, 27887, 27886, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27793' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27793, 27693, 0),
(20, 8, 27793, 27709, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27887' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27887, 27885, 0),
(19, 8, 27887, 27886, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27793' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27793, 27693, 0),
(19, 8, 27793, 27709, 0);

DELETE FROM `gameobject_involvedrelation` WHERE `quest` = '27793';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(206374, 27793);

DELETE FROM `gameobject_questrelation` WHERE `quest` = '27912';
INSERT INTO `gameobject_questrelation` (`id`, `quest`) VALUES
(206374, 27912);

UPDATE `creature_template` SET `mindmg`=69, `maxdmg`=103, `attackpower`=26 WHERE `entry`=46772;

-- Reliquary Excavator
SET @ENTRY := 46772;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,5000,5000,11,7978,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Throw Dynamite");

UPDATE `quest_template` SET `PrevQuestId`='27794' WHERE `Id`=27826;

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27827';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5564, 27827, 1, 74, 0);

UPDATE `creature_template` SET `ScriptName`='npc_eric' WHERE `entry`=46855;
UPDATE `creature_template` SET `ScriptName`='npc_baelog' WHERE `entry`=46856;
UPDATE `creature_template` SET `ScriptName`='npc_olaf' WHERE `entry`=46857;

UPDATE `creature_template` SET `VehicleId`=1187, `spell1`=87278, `spell2`=87279, `mindmg`=109, `maxdmg`=215, `attackpower`=25, `dmg_multiplier`=2.1 WHERE `entry`=46855;
UPDATE `creature_template` SET `VehicleId`=1187, `spell1`=87276, `spell2`=87277, `mindmg`=109, `maxdmg`=215, `attackpower`=25, `dmg_multiplier`=2.1 WHERE `entry`=46856;
UPDATE `creature_template` SET `VehicleId`=1187, `spell1`=87274, `spell2`=87275, `mindmg`=109, `maxdmg`=215, `attackpower`=25, `dmg_multiplier`=2.1 WHERE `entry`=46857;

-- Eric
SET @ENTRY := 46852;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27828,0,0,0,85,87262,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Eric"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27829,0,0,0,85,87262,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Eric");

-- Baelog
SET @ENTRY := 46853;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27834,0,0,0,85,87263,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Baelog"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27829,0,0,0,85,87263,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Baelog");

-- Olaf
SET @ENTRY := 46854;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27835,0,0,0,85,87264,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Olaf"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27829,0,0,0,85,87264,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Olaf");

DELETE FROM `creature_involvedrelation` WHERE `id` = '46854' AND `quest` = '27835';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(46854, 27835);

DELETE FROM `creature_involvedrelation` WHERE `id` = '46853' AND `quest` = '27834';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(46853, 27834);

DELETE FROM `creature_involvedrelation` WHERE `id` = '46852' AND `quest` = '27828';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(46852, 27828);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (87262, 87263, 87264);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(87262, -49417, 'Viking Effects remove Invis Detection Auras'),
(87263, -49417, 'Viking Effects remove Invis Detection Auras'),
(87264, -49417, 'Viking Effects remove Invis Detection Auras');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27858;

DELETE FROM `gameobject_involvedrelation` WHERE `quest` = '27858';
INSERT INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES
(206504, 27858);