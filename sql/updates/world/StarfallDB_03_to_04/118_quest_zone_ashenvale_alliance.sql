UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=194202;
DELETE FROM `gameobject_loot_template` WHERE `item` = '44967';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(194202, 44967, -100, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '62506';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 62506, 0, 0, 31, 0, 3, 33183, 0, 0, 0, '', 'Bottle of Wildfire - Targeting Bathran Corpse');

-- Bathran's Corpse
SET @ENTRY := 33183;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,62506,0,0,0,11,62511,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast Fire"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,33,33183,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,60000,60000,60000,60000,28,62511,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Fire");

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=33347;

-- Delgren the Purifier
SET @ENTRY := 33347;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,100,60000,60000,75,62817,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Invisible on Spawn"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,56,45043,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Item"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Close Gossip");

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=33407;

-- Feero Ironhand
SET @ENTRY := 33348;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,100,60000,60000,75,62817,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Invisible on Spawn"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,56,45042,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Item"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Close Gossip");

-- Horde Invader
SET @ENTRY := 33334;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,25000,40000,35000,75000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update IC - Evade"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,2,1,1,0,45,0,3000,10000,25000,45000,49,0,0,0,0,0,0,11,33278,400,0,0.0,0.0,0.0,0.0,"Update OOC - Attack Alliance");

-- Ashenvale Wrecker
SET @ENTRY := 33283;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,75,0,5000,18000,5000,18000,11,68591,0,0,0,0,0,11,33278,200,0,0.0,0.0,0.0,0.0,"Update - Cast Fiery Boulder");

DELETE FROM `spell_script_names` WHERE `spell_id` IN (62981, 65514);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62981, 'spell_unbathed_concotion'),
(65514, 'spell_cleanse_elune_tear');

UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=0 WHERE `Id`=13919;

DELETE FROM `creature_involvedrelation` WHERE `quest` = '13919';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(34335, 13919);

DELETE FROM `spell_area` WHERE `quest_end` = '13919';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65315, 4705, 13919, 13919, 0, 0, 2, 1, 74, 74),
(65315, 425, 13919, 13919, 0, 0, 2, 1, 74, 74);

DELETE FROM `creature_questrelation` WHERE `quest` = '13921';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(34335, 13921);

-- Avrus Illwhisper
SET @ENTRY := 34335;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,49,0,100,0,0,0,0,0,7,13921,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Add Next Quest"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `creature_loot_template` WHERE `item` = '5508';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3758, 5508, -47, 1, 0, 1, 1),
(3759, 5508, -47, 1, 0, 1, 1),
(3762, 5508, -40, 1, 0, 1, 1),
(3763, 5508, -38, 1, 0, 1, 1);

DELETE FROM `spell_area` WHERE `quest_end` IN (13976, 13982);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65714, 4716, 13976, 13976, 0, 0, 2, 1, 2, 2),
(65714, 4716, 13982, 13982, 0, 0, 2, 1, 2, 2);

UPDATE `creature_template` SET `minlevel`=26, `maxlevel`=26, `faction_A`=1801, `faction_H`=1801, `mindmg`=33, `maxdmg`=48, `attackpower`=12, `baseattacktime`=2000, `spell1`=81650, `spell2`=81651, `lootid`=34602 WHERE `entry`=34602;

DELETE FROM `creature_loot_template` WHERE `item` = '46774';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(34602, 46774, -100);

-- Kaliva
SET @ENTRY := 34602;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,12000,20000,11,81651,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Vile Beam"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,7000,9000,19000,28000,11,81650,0,0,0,0,0,4,0,0,0,0.0,0.0,0.0,0.0,"Cast Sinful Beam"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Player");

UPDATE `quest_template` SET `RewardSpellCast`=65715 WHERE `Id`=13982;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (734295, 734293, 734294);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '65715';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(65715, -65714, 'In a Bind: See Invisibility switch');

DELETE FROM `creature_template_addon` WHERE `entry` = '34604';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(34604, '65727');

DELETE FROM `spell_area` WHERE `quest_end` IN (13985, 13987, 13982);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65727, 416, 13985, 13985, 0, 0, 2, 1, 2, 2),
(65727, 416, 13987, 13987, 0, 0, 2, 1, 10, 10),
(65715, 4716, 13982, 13982, 0, 0, 2, 1, 64, 64);

DELETE FROM `creature` WHERE `guid` = '798400';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(798400, 34604, 1, 1, 2, 0, 0, 2640.52, 418.39, 74.2187, 5.46939, 300, 0, 0, 12192, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `Armor_mod`=20 WHERE `entry`=34604;

-- Big Baobob
SET @ENTRY := 34604;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1000,1000,15000,15000,12,34609,1,65000,0,0,0,8,0,0,0,2667.63,390.41,70.73,2.22,"Update - Summon Demonic Invader 1"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,1000,1000,15000,15000,12,34610,1,65000,0,0,0,8,0,0,0,2615.93,417.63,72.77,0.03,"Update - Summon Demonic Invader 2"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1000,1000,15000,15000,12,34609,1,65000,0,0,0,8,0,0,0,2628.87,453.64,73.56,5.0,"Update - Summon Demonic Invader 1"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,1000,1000,15000,15000,12,34610,1,65000,0,0,0,8,0,0,0,2657.2,437.88,72.68,4.06,"Update - Summon Demonic Invader 2"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,2500,2500,15000,15000,11,65735,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rejuvenation"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,2500,2500,15000,15000,11,65735,2,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rejuvenation - To Player");

-- Demonic Invader
SET @ENTRY := 34610;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,10000,10000,49,0,0,0,0,0,0,10,798400,34604,0,0.0,0.0,0.0,0.0,"OOC - Attack Big Baobob"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,60000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Force Despawn "),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,75,65727,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Add Aura"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,33,34609,0,0,0,0,0,3,0,0,0,0.0,0.0,0.0,0.0,"On Death - Killed Monster");

-- Demonic Invader
SET @ENTRY := 34609;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,10000,10000,49,0,0,0,0,0,0,10,798400,34604,0,0.0,0.0,0.0,0.0,"OOC - Attack Big Baobob"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,60000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Force Despawn "),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,75,65727,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Add Aura"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,33,34609,0,0,0,0,0,3,0,0,0,0.0,0.0,0.0,0.0,"On Death - Killed Monster");

UPDATE `creature_template` SET `minlevel`=23, `maxlevel`=25, `faction_A`=1801, `faction_H`=1801, `mindmg`=6, `maxdmg`=18, `attackpower`=6, `dmg_multiplier`=1, `baseattacktime`=2000 WHERE  `entry` IN (34609, 34610);

DELETE FROM `spell_area` WHERE `quest_end` IN (13849, 13853);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(64572, 415, 13849, 13849, 0, 0, 2, 1, 10, 10),
(64572, 415, 13853, 13853, 0, 0, 2, 1, 10, 10);

UPDATE `creature_template` SET `npcflag`=16777216, `InhabitType`=7 WHERE `entry`=34160;
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=34163;
DELETE FROM `creature` WHERE `id`= '34163';

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (34160, 34132);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(34160, 46598, 0, 0),
(34132, 68388, 1, 0);

UPDATE `creature_template` SET `spell1`=64664 WHERE `entry`=34132;

DELETE FROM `conditions` WHERE `SourceEntry` = '64711';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 64711, 0, 0, 31, 0, 3, 34160, 0, 0, 0, '', 'Throw Glaive (DMG) - Targeting Watch Wind Rider');

UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=34160;

-- Watch Wind Rider
SET @ENTRY := 34160;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,64711,1,0,0,33,34176,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die");

UPDATE `creature_template` SET `npcflag`=16777216 WHERE `entry` IN (39071, 39070);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (39071, 39070);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(39071, 46598, 0),
(39070, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (39071);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`) VALUES
(39071, 40829, 7, 1, 'Dead Gnome'),
(39071, 40829, 6, 1, 'Dead Gnome'),
(39071, 40829, 5, 1, 'Dead Gnome'),
(39071, 40829, 4, 1, 'Dead Gnome'),
(39071, 40829, 3, 1, 'Dead Gnome'),
(39071, 39096, 0, 1, 'Thundrak'),
(39071, 40800, 1, 1, 'Minx'),
(39071, 40799, 2, 1, 'Boog');

DELETE FROM `creature` WHERE `id` IN (40829, 39096, 40820, 40799, 40800, 39070, 39071);

DELETE FROM `waypoints` WHERE `entry` = '40820';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(40820, 1, 2198.87, -941.11, 92.22, 'War Kodo WP'),
(40820, 2, 2172.26, -949.76, 93.93, 'War Kodo WP'),
(40820, 3, 2143.99, -1022.14, 99.35, 'War Kodo WP'),
(40820, 4, 2148.25, -1124.75, 99.71, 'War Kodo WP');

-- Painmaster Thundrak
SET @ENTRY := 39096;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,6000,19000,22000,11,81419,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast The Painhammer"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,1,0,30,0,0,11,33958,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Enrage at 30% HP"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,30,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 30% HP"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,5000,5000,5000,5000,15,13913,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Aggro - Quest Complete"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,1,1,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=39096;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39096,0,0,'%s becomes enraged!',16,0,100,0,0,0,'combat Enrage'),
(39096,1,0,'PAIN is all that you will find here. Ashenvale Assassin!',14,0,100,0,0,0,'Comment');

-- Horde Infantry
SET @ENTRY := 41681;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,0,0,5,16,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update Every 10 seconds (Bow)");

DELETE FROM `spell_area` WHERE `quest_end` IN (13877, 13886);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65098, 4690, 13877, 13877, 0, 0, 2, 1, 74, 74),
(65098, 4690, 13886, 13886, 0, 0, 2, 1, 74, 74);

DELETE FROM `creature_loot_template` WHERE `item` = '46128';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3924, 46128, 7, 1, 0, 1, 1),
(3925, 46128, 8, 1, 0, 1, 1),
(3926, 46128, 4, 1, 0, 1, 1),
(3922, 46128, 0.3, 1, 0, 1, 1),
(3921, 46128, 0.3, 1, 0, 1, 1);

UPDATE `creature_template` SET `modelid1`=2723, `modelid2`=2723, `lootid`=34426, `questItem1`=46543, `npcflag`=1 WHERE `entry`=34426;

DELETE FROM `creature_loot_template` WHERE `item` = '46543';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(34426, 46543, -100);

UPDATE `creature_template` SET `mindmg`=1, `maxdmg`=1, `attackpower`=1 WHERE `entry`=4054;
UPDATE `creature_template` SET `mindmg`=43, `maxdmg`=55, `attackpower`=40, `dmg_multiplier`=1 WHERE `entry`=34366;
UPDATE `creature_template` SET `IconName`='LootAll' WHERE `entry`=34426;

-- Laughing Sister
SET @ENTRY := 34426;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,56,46543,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Laughing Sister
SET @ENTRY := 4054;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Laughing Sister - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,1,2,6,0,100,0,0,0,0,0,12,34426,4,25000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon Corpse"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `conditions` WHERE `SourceEntry` = '65535';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 65535, 0, 0, 31, 0, 3, 34499, 0, 0, 0, '', 'Playing Possum - Target Orso Bramblescar');

DELETE FROM `spell_script_names` WHERE `spell_id` = '65535';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(65535, 'spell_playing_possum');

UPDATE `creature_template` SET `mindmg`=38, `maxdmg`=41, `attackpower`=10, `dmg_multiplier`=5.5 WHERE `entry`=34499;

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (65535, -65535);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(65535, 57626, 2, 'Playing Possum -> Feign Death'),
(-65535, -57626, 2, 'Playing Possum -> Remove Feign Death');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10506 AND `id`=0;
UPDATE `creature_template` SET `gossip_menu_id`=10506 WHERE `entry`=34377;

DELETE FROM `conditions` WHERE `SourceGroup` = '10506';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10506, 0, 0, 0, 9, 0, 13935, 0, 0, 0, 0, 0, '', 'Halannia - Show gossip only if quest 13935 is active');

UPDATE `creature_template` SET `spell1`=65402, `spell2`=65406, `spell3`=65407, `VehicleId`=690, `minlevel`=22, `maxlevel`=25, `mindmg`=44, `maxdmg`=80, `unit_class`=4 WHERE `entry`=3831;

-- Halannia
SET @ENTRY := 34377;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10506,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,86,61872,0,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Shade of Shadumbra"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,86,66772,0,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cross Cast Earthquake");

UPDATE `creature_template` SET `minlevel`=22, `maxlevel`=23, `faction_A`=1801, `faction_H`=1801, `mindmg`=28, `maxdmg`=43, `attackpower`=11, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (32856, 32850, 34390);
UPDATE `creature_template` SET `unit_flags`=4 WHERE `entry`=32850;

-- Warsong Demolisher
SET @ENTRY := 32850;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,9,0,100,0,0,50,10000,14000,11,61865,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Flaming Ball on Close"),
(@ENTRY,@SOURCETYPE,3,0,9,0,100,0,0,20,14000,19000,11,65388,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Flamethrower on Close"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,1,0,0,0,0,11,65417,3,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Warsong Demolisher Explodes on Death"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,0,5000,5000,5000,5000,11,61864,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Another Flaming Ball"),
(@ENTRY,@SOURCETYPE,6,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Passive");

-- Shade of Shadumbra
SET @ENTRY := 3831;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,54,0,100,0,0,0,0,0,86,65396,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Grab Summoner"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,60000,60000,60000,60000,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=178115;
UPDATE `creature` SET `equipment_id`=1 WHERE `id` IN (32856, 34390);
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=26482;
UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=175680;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10537 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup` = '10537';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10537, 0, 0, 0, 9, 0, 26482, 0, 0, 0, 0, 0, '', 'Ota Wen - Show gossip only if quest 26482 is active');

DELETE FROM `creature_text` WHERE `entry`=34618;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34618,0,0,'YES WE WILL RISE UP! RISE UP AND DESTROY OUR JAILORS!',14,0,100,0,0,0,'Comment');

-- Ota Wen
SET @ENTRY := 34618;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10537,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,15,26482,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

SET @CGUID := 798401;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+52;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 32856, 1, 1, 2, 0, 1, 2739.18, -1873.38, 193.498, 1.68426, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+1, 32856, 1, 1, 2, 0, 1, 2741.94, -1893.32, 188.068, 3.43411, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+2, 32856, 1, 1, 2, 0, 1, 2747.61, -1878, 190.764, 5.02711, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+3, 32856, 1, 1, 2, 0, 1, 2747.13, -1864.83, 193.362, 4.39936, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+4, 32856, 1, 1, 2, 0, 1, 2750.97, -1847, 195.932, 4.25424, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+5, 32856, 1, 1, 2, 0, 1, 2747.32, -1836.84, 199.119, 0.475305, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+6, 32856, 1, 1, 2, 0, 1, 2735.97, -1839.85, 196.909, 6.18137, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+7, 32856, 1, 1, 2, 0, 1, 2725.48, -1833.68, 197.039, 5.12161, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+8, 32856, 1, 1, 2, 0, 1, 2716.42, -1828.01, 195.822, 6.08349, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+9, 32856, 1, 1, 2, 0, 1, 2705.28, -1823.73, 194.404, 5.65149, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+10, 32856, 1, 1, 2, 0, 1, 2694.8, -1808.89, 194.776, 3.60275, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+11, 32856, 1, 1, 2, 0, 1, 2683.64, -1803.37, 195.19, 4.85488, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+12, 32856, 1, 1, 2, 0, 1, 2598.02, -1848.26, 164.421, 0.589986, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+13, 32856, 1, 1, 2, 0, 1, 2590.38, -1858.43, 158.768, 0.380532, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+14, 32856, 1, 1, 2, 0, 1, 2584.49, -1864.63, 155.381, 0.537612, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+15, 32856, 1, 1, 2, 0, 1, 2580.86, -1830.45, 156.334, 5.85817, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+16, 32856, 1, 1, 2, 0, 1, 2568.53, -1842.33, 157.968, 0.00698917, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+17, 32856, 1, 1, 2, 0, 1, 2584.84, -1851.91, 159.279, 6.18022, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+18, 32856, 1, 1, 2, 0, 1, 2607.29, -1837.13, 170.725, 6.1838, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+19, 32856, 1, 1, 2, 0, 1, 2613.5, -1845.82, 171.051, 0.224614, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+20, 32856, 1, 1, 2, 0, 1, 2616.3, -1855.88, 180.771, 0.224614, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+21, 32856, 1, 1, 2, 0, 1, 2631.14, -1870.47, 181.031, 0.405543, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+22, 32856, 1, 1, 2, 0, 1, 2684, -1822.92, 191.954, 3.88335, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+23, 32856, 1, 1, 2, 0, 1, 2680.19, -1814.24, 193.974, 4.70016, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+24, 32850, 1, 1, 2, 0, 0, 2654, -1809.4, 187.748, 5.13553, 60, 0, 0, 74, 0, 0, 0, 0, 0),
(@CGUID+25, 32850, 1, 1, 2, 0, 0, 2628.33, -1856.62, 182.25, 0.250349, 60, 0, 0, 74, 0, 0, 0, 0, 0),
(@CGUID+26, 32856, 1, 1, 2, 0, 1, 2628.63, -1845.24, 181.151, 6.02303, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+27, 32856, 1, 1, 2, 0, 1, 2633.9, -1825.43, 182.202, 6.02303, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+28, 32856, 1, 1, 2, 0, 1, 2626.54, -1832.24, 179.372, 6.02303, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+29, 32856, 1, 1, 2, 0, 1, 2623.34, -1824.19, 180.242, 6.02303, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+30, 32856, 1, 1, 2, 0, 1, 2627.76, -1816.72, 184.396, 5.73278, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+31, 32856, 1, 1, 2, 0, 1, 2636.84, -1809.73, 186.429, 5.34803, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+32, 34390, 1, 1, 2, 0, 1, 2647.27, -1856.71, 187.577, 5.66182, 60, 0, 0, 126, 0, 0, 0, 0, 0),
(@CGUID+33, 34390, 1, 1, 2, 0, 1, 2659.3, -1838.84, 185.961, 5.54794, 60, 0, 0, 126, 0, 0, 0, 0, 0),
(@CGUID+34, 32856, 1, 1, 2, 0, 1, 2658.97, -1845.94, 186.118, 0.373992, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+35, 32856, 1, 1, 2, 0, 1, 2644.46, -1848.22, 186.234, 0.421116, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+36, 32850, 1, 1, 2, 0, 0, 2644.99, -1835.58, 183.672, 5.60474, 60, 0, 0, 74, 0, 0, 0, 0, 0),
(@CGUID+37, 32856, 1, 1, 2, 0, 1, 2676.8, -1833.37, 190.26, 4.68218, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+38, 32856, 1, 1, 2, 0, 1, 2643.48, -1859.41, 186.97, 6.2778, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+39, 32856, 1, 1, 2, 0, 1, 2652.58, -1855.25, 187.964, 6.0304, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+40, 32856, 1, 1, 2, 0, 1, 2648.09, -1851.25, 187.084, 5.9854, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+41, 32856, 1, 1, 2, 0, 1, 2641.83, -1853.69, 186.445, 5.9854, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+42, 32856, 1, 1, 2, 0, 1, 2638.82, -1848.77, 185.072, 5.9854, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+43, 32856, 1, 1, 2, 0, 1, 2640.14, -1839.65, 183.935, 5.9854, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+44, 32856, 1, 1, 2, 0, 1, 2637.61, -1842.59, 183.968, 5.7289, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+45, 32856, 1, 1, 2, 0, 1, 2666.95, -1831.63, 187.938, 5.39857, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+46, 32856, 1, 1, 2, 0, 1, 2656.74, -1830.47, 185.917, 5.39857, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+47, 32856, 1, 1, 2, 0, 1, 2661.03, -1825.86, 187.369, 5.39857, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+48, 32856, 1, 1, 2, 0, 1, 2647.46, -1831.69, 183.92, 5.7372, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+49, 32856, 1, 1, 2, 0, 1, 2648.91, -1829.3, 184.426, 5.7372, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+50, 32856, 1, 1, 2, 0, 1, 2652.39, -1826.39, 185.596, 5.30182, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+51, 32856, 1, 1, 2, 0, 1, 2655.53, -1823.61, 186.424, 5.30182, 60, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+52, 39071, 1, 1, 1, 0, 0, 2140.99, -1077.36, 99.3514, 0.906095, 300, 0, 0, 699, 0, 0, 0, 0, 0);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '5502';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(5502, 'Raene, I lost my rod, can I have another one?', 1, 1);

DELETE FROM `creature_text` WHERE `entry`=3691;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(3691,0,0,'$n, be careful about your items next time!',12,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceGroup` = '5502';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 5502, 0, 0, 0, 8, 0, 26480, 0, 0, 0, 0, 0, '', 'Raene Wolfrunner - Show gossip only if quest 26480 is active');

-- Raene Wolfrunner
SET @ENTRY := 3691;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,16100,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,16100,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
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
(@ENTRY,@SOURCETYPE,16,0,9,1,100,0,0,20,8000,9000,11,6533,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Net on Close"),
(@ENTRY,@SOURCETYPE,17,5,9,1,100,0,5,30,12000,19000,11,15495,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Explosive Shot"),
(@ENTRY,@SOURCETYPE,18,5,9,1,100,0,5,30,22000,27000,11,22908,2,0,0,0,0,4,0,0,0,0.0,0.0,0.0,0.0,"Cast Volley"),
(@ENTRY,@SOURCETYPE,19,20,62,0,100,0,5502,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,20,21,61,0,100,0,0,0,0,0,56,46781,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Quest Item"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0");

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '33706';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(33706, 63517, 1);

UPDATE `creature_template` SET `spell1`=63520 WHERE `entry`=33706;
UPDATE `quest_template` SET `RequiredSpellCast1`=63520 WHERE `Id`=13698;

-- Warsong Shredder
SET @ENTRY := 33706;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,28,0,100,0,0,0,0,0,33,33709,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Evade"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Passive");

UPDATE `quest_template` SET `PrevQuestId`=13869 WHERE `Id`=26446;
UPDATE `quest_template` SET `PrevQuestId`=26454 WHERE `Id`=13869;
UPDATE `quest_template` SET `RequiredSpellCast1`=63578 WHERE `Id`=13766;
UPDATE `quest_template` SET `PrevQuestId`=13922 WHERE `Id`=13924;
UPDATE `quest_template` SET `NextQuestIdChain`=13924 WHERE `Id`=13922;

DELETE FROM `creature_loot_template` WHERE `item` = '45571';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(3799, 45571, 27.171, 1, 0, 1, 1),
(3803, 45571, 26.5525, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE `item` = '45573';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(26899, 45573, -100, 1, 0, 1, 1);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=3 WHERE `item`=23777;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=3 WHERE `item`=23797;
UPDATE `creature_questrelation` SET `id`=34335 WHERE `id`=34358 AND `quest`=13924;

DELETE FROM `creature_loot_template` WHERE `item` IN (45476, 45477);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(6072, 45476, -100, 1, 0, 1, 1),
(17300, 45477, -100, 1, 0, 1, 1);