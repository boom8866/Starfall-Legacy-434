DELETE FROM `spell_area` WHERE `spell` = '94566' AND `quest_start` IN (28557,28558,28295,28296,27003);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(94566, 440, 28557, 27003, 1, 72),
(94566, 440, 28558, 27003, 1, 72),
(94566, 440, 28295, 27003, 1, 72),
(94566, 440, 28296, 27003, 1, 72),
(94566, 440, 27003, 27003, 1, 8);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start`=27003;
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 5599, 27003, 27003, 1, 2);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN
(735123,735116,735112,735120,735113,735119,735108,735111,735115,735114,735120,735122,735118,735110);

DELETE FROM `quest_poi_points` WHERE `questId` = '27003';
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES
(27003, 0, 0, -8932, -2219); -- Easy Money

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=46517;
UPDATE `creature_template` SET `ScriptName`='npc_lady_humps_intro_uldum', `speed_walk`=1, `speed_run`=1.41 WHERE `entry`=46517;

UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86751 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86752 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86758 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86757 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86756 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86755 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86754 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=1.39 WHERE `id`=86753 AND `effIndex`=0;

UPDATE `creature_template` SET `ScriptName`='npc_uldum_intro_selfmirror' WHERE `entry`=46554;
UPDATE `creature_template` SET `VehicleId`=1203, `ScriptName`='npc_uldum_intro_camera01' WHERE `entry`=46557;

UPDATE `spell_target_position` SET `target_position_x`=-8917.45, `target_position_y`=-2268.28, `target_position_z`=15.24, `target_orientation`=2.86 WHERE `id`=86792 AND `effIndex`=0;

DELETE FROM `conditions` WHERE `SourceEntry` = '86784';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85784, 0, 0, 31, 0, 3, 46554, 0, 0, 0, '', 'Targeting -> Mirror Image (Uldum)');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46524';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46524, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46543';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46543, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46524';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46524, 46523, 1, 'Mack -> Mack\'s Camel', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46543';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46543, 46523, 1, 'Mack -> Mack\'s Camel', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46519';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46519, 46520, 1, 'Budd -> Budd\'s Camel', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46538';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46538, 46520, 1, 'Budd -> Budd\'s Camel', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46540';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46540, 46522, 1, 'Samir -> Samir\'s Camel', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46521';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46521, 46522, 1, 'Samir -> Samir\'s Camel', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46519';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46519, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46540';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46540, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46516';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46516, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46543';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46543, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46521';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46521, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46538';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46538, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46516';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46516, 46514, 3, 1, 'Kodo -> Uldum Caravan', 8, 0),
(46516, 46525, 0, 1, 'Turgore -> Uldum Caravan', 8, 0),
(46516, 46529, 2, 1, 'Kurzel -> Uldum Caravan', 8, 0),
(46516, 46530, 5, 1, 'Harkor -> Uldum Caravan', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46596';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46596, 46514, 3, 1, 'Kodo -> Uldum Caravan', 8, 0),
(46596, 46525, 0, 1, 'Turgore -> Uldum Caravan', 8, 0),
(46596, 46529, 2, 1, 'Kurzel -> Uldum Caravan', 8, 0),
(46596, 46530, 5, 1, 'Harkor -> Uldum Caravan', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46596';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46596, 46598, 0);

UPDATE `creature_template` SET `VehicleId`=1197 WHERE `entry` IN (46540, 46546, 46538, 46543);
UPDATE `creature_template` SET `ScriptName`='npc_adarrah_uldum_intro' WHERE `entry`=46533;

DELETE FROM `creature_text` WHERE `entry`=46533;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46533,0,0,'No, no, silly $R...',12,0,100,0,1,0,'Comment'),
(46533,1,0,'No one rides the Lady!',12,0,100,1,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '86750';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(86750, 'spell_uldum_intro_preparation');

UPDATE `creature_template` SET `VehicleId`=1199 WHERE `entry`=46596;
UPDATE `creature_template` SET `ScriptName`='npc_uldum_caravan_intro', `speed_walk`=1, `speed_run`=1.41 WHERE `entry`=46596;

DELETE FROM `script_waypoint` WHERE `entry` = '46536';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46536, 1, -8944.66, -2162.54, 8.96, 'Lady Humps WP');
 
DELETE FROM `script_waypoint` WHERE `entry` = '46596';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46596, 1, -8944.66, -2162.54, 8.96, 'Uldum Caravan WP');
 
DELETE FROM `script_waypoint` WHERE `entry` = '46537';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46537, 1, -8938.77, -2169.80, 8.89, 'Pack Mule WP');
 
DELETE FROM `script_waypoint` WHERE `entry` = '46540';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46540, 1, -8938.77, -2169.80, 8.89, 'Samir Camel WP');
 
DELETE FROM `script_waypoint` WHERE `entry` = '46543';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46543, 1, -8938.77, -2169.80, 8.89, 'Mack Camel WP');
 
DELETE FROM `script_waypoint` WHERE `entry` = '46546';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46546, 1, -8948.45, -2165.75, 8.90, 'Adarrah Camel WP');
 
DELETE FROM `script_waypoint` WHERE `entry` = '46538';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46538, 1, -8948.45, -2165.75, 8.90, 'Budd Camel WP');

UPDATE `creature_template` SET `ScriptName`='npc_lady_humps_intro_escort' WHERE `entry`=46536;
UPDATE `creature_template` SET `ScriptName`='npc_adarrah_camel_intro_escort' WHERE `entry`=46546;
UPDATE `creature_template` SET `ScriptName`='npc_pack_mule_intro_escort' WHERE `entry`=46537;
UPDATE `creature_template` SET `ScriptName`='npc_mack_camel_intro_escort' WHERE `entry`=46543;
UPDATE `creature_template` SET `ScriptName`='npc_samir_camel_intro_escort' WHERE `entry`=46540;
UPDATE `creature_template` SET `ScriptName`='npc_budd_camel_intro_escort' WHERE `entry`=46538;

DELETE FROM `creature_text` WHERE `entry`=46520;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46520,0,0,'Ahoy!',12,0,100,1,0,21174,'Comment');

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (735111,735116,735115,735118,735117,735114);
UPDATE `creature_template` SET `VehicleId`=1208 WHERE `entry`=46679;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '46679';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(46679, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '46679';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(46679, 46680, 1, 'Skarf -> Sultan Oogah', 8, 0);

UPDATE `creature_template` SET `ScriptName`='npc_skarf_and_oogah_intro' WHERE `entry`=46679;

DELETE FROM `creature_text` WHERE `entry`=46680;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46680,0,0,'Attack!',14,0,100,0,0,0,'Comment');

SET @CGUID := 837422;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+17;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 46537, 1, 1, 298, 0, 0, -8955.58, -1689.02, 94.4533, 1.57944, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+1, 46533, 1, 1, 298, 0, 0, -8972.84, -1681.79, 94.4533, 2.48029, 300, 0, 0, 34, 0, 0, 0, 0, 0),
(@CGUID+2, 46538, 1, 1, 298, 0, 0, -8962.37, -1712.31, 94.4533, 1.59122, 300, 0, 0, 378, 0, 0, 16777216, 0, 0),
(@CGUID+3, 46546, 1, 1, 298, 0, 0, -8970.82, -1683.12, 94.4533, 1.59122, 300, 0, 0, 378, 0, 0, 16777216, 0, 0),
(@CGUID+4, 46536, 1, 1, 298, 0, 0, -8962.53, -1676.52, 94.4533, 1.59122, 300, 0, 0, 483129, 0, 0, 0, 0, 0),
(@CGUID+5, 46596, 1, 1, 298, 0, 0, -8962.63, -1696.33, 94.4533, 1.603, 300, 0, 0, 42, 0, 0, 16777216, 0, 0),
(@CGUID+6, 46540, 1, 1, 298, 0, 0, -8952.14, -1695.99, 94.4533, 1.603, 300, 0, 0, 378, 0, 0, 16777216, 0, 0),
(@CGUID+7, 46543, 1, 1, 298, 0, 0, -8954.17, -1704.75, 94.4536, 1.59514, 300, 0, 0, 378, 0, 0, 16777216, 0, 0),
(@CGUID+8, 46720, 1, 1, 298, 0, 1, -8986.17, -1701.68, 94.4538, 0.7642, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+9, 46720, 1, 1, 298, 0, 1, -8982.14, -1722.2, 94.4538, 0.638536, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+10, 46720, 1, 1, 298, 0, 1, -8966.53, -1730.01, 94.4538, 1.56923, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+11, 46720, 1, 1, 298, 0, 1, -8951.29, -1723.16, 94.4538, 1.9957, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+12, 46720, 1, 1, 298, 0, 1, -8938.39, -1707.26, 94.4538, 2.49836, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+13, 46720, 1, 1, 298, 0, 1, -8937.79, -1683.96, 94.4533, 3.55864, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+14, 46720, 1, 1, 298, 0, 1, -8946.85, -1673.74, 94.4533, 3.80996, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+15, 46720, 1, 1, 298, 0, 1, -8952.91, -1664.85, 94.4533, 4.13747, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+16, 46720, 1, 1, 298, 0, 1, -8966.53, -1662.82, 94.4533, 4.81134, 300, 0, 0, 42, 0, 0, 0, 0, 0),
(@CGUID+17, 46720, 1, 1, 298, 0, 1, -8974.52, -1669.42, 94.4533, 5.35719, 300, 0, 0, 42, 0, 0, 0, 0, 0);

DELETE FROM `creature_text` WHERE `entry`=46720;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46720,0,0,'How many coconuts can we get for the ugly one?',12,0,100,0,0,0,'Comment'),
(46720,1,0,'THREE? He woulda paid five, easy... Dummy!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `VehicleId`=1267, `InhabitType`=4 WHERE `entry`=47473;

-- Pygmy Ambusher
SET @ENTRY := 46720;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Walk"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,80,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Despawn");

UPDATE `creature` SET `phaseMask`=299 WHERE `guid` IN (736334, 181848, 181847, 181849, 181850, 181846);
UPDATE `creature` SET `phaseMask`=298 WHERE `guid`=736334;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (735605, 735268);
UPDATE `gameobject` SET `phaseMask`=299 WHERE `guid` iN (77543, 77544, 77545);

-- Neferset Jailer
SET @ENTRY := 48029;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,100,100,5000,5000,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Defensive");

UPDATE `gameobject` SET `state`=1 WHERE `guid`=77544;

DELETE FROM `spell_script_names` WHERE `spell_id` = '89328';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89328, 'spell_adarrah_breakout_cage');

DELETE FROM `creature_text` WHERE `entry`=48030;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48030,0,0,'Please don\'t break... please don\'t break...',12,0,100,0,0,0,'Comment'),
(48030,1,0,'Crap! That was my last lock pick!',12,0,100,0,0,0,'Comment'),
(48030,2,0,'Here comes the guard, $n! take him out!',12,0,100,0,0,0,'Comment'),
(48030,3,0,'Well done! I was about to jump in! But it looked like you had it under control.',12,0,100,0,0,0,'Comment'),
(48030,4,0,'That cat-creature chained back there looks like he wants to talk. Maybe he can help us... but be careful.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_adarrah_breakout' WHERE `entry`=48030;
UPDATE `creature_template` SET `ScriptName`='npc_neferset_jailor_breakout' WHERE `entry`=48011;

DELETE FROM `creature_addon` WHERE `guid` IN (181848, 181847, 181849, 181850, 181846);
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(181848, 1, '49415'),
(181847, 1, '49415'),
(181849, 1, '49415'),
(181850, 1, '49415'),
(181846, 1, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27003';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5599, 27003, 1, 74, 0);

UPDATE `quest_template` SET `PrevQuestId`='27922' WHERE `Id` IN (27923, 27924, 28105);

DELETE FROM `conditions` WHERE `SourceEntry` = '28112' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28112, 27923, 0),
(20, 8, 28112, 28105, 0),
(20, 8, 28112, 27924, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28112' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28112, 27923, 0),
(19, 8, 28112, 28105, 0),
(19, 8, 28112, 27924, 0);

DELETE FROM `creature_addon` WHERE `guid` = '181851';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `emote`) VALUES
(181851, 1, 433);

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=727925;

DELETE FROM `spell_target_position` WHERE `id` = '88510';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(88510, 1, -10968.63, -1375.07, 39.94, 5.76);

UPDATE `gameobject_template` SET `ScriptName`='go_plant_trap_traitors' WHERE `entry`=206579;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=727926;

DELETE FROM `creature_text` WHERE `entry`=47451;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47451,0,0,'You\'re the last of your tribe with any sense left. As a reward for giving us Prince Nadun, I grant you the gift that is your birthright and more',12,0,100,0,0,0,'Comment'),
(47451,1,0,'Your makers failed you... your race succumbed to the curse of flesh! Lord Deathwing\'s gift makes you perfect again!',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_target_position` WHERE `id` = '88489';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(88489, 1, -10948.50, -1400.04, 35.57, 1.27);

DELETE FROM `spell_target_position` WHERE `id` IN (88523, 88487, 88488);
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(88523, 1, -10946.2, -1384.51, 35.7071, 4.53),
(88487, 1, -10944.1, -1383.71, 35.707, 4.53),
(88488, 1, -10948.4, -1382.85, 35.5345, 4.53);

UPDATE `creature_template` SET `ScriptName`='npc_siamat_traitors' WHERE `entry`=47451;
UPDATE `creature_template` SET `ScriptName`='npc_ramkahen_traitors' WHERE `entry` IN (47450, 47449, 47478);

DELETE FROM `creature_loot_template` WHERE `entry` = '48267';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48267, 17057, 100, 1, 0, 1, 1),
(48267, 17058, 19.8884, 1, 0, 1, 1),
(48267, 33399, 0.05, 1, 0, 1, 1),
(48267, 33451, 0.0016, 1, 0, 1, 1),
(48267, 36781, 20, 1, 0, 1, 1),
(48267, 52197, 0.05, 1, 0, 1, 1),
(48267, 52340, 11.9742, 1, 0, 1, 1),
(48267, 52364, 0.0074, 1, 0, 1, 1),
(48267, 52368, 0.05, 1, 0, 1, 1),
(48267, 52371, 0.0056, 1, 0, 1, 1),
(48267, 52372, 0.05, 1, 0, 1, 1),
(48267, 52376, 0.0075, 1, 0, 1, 1),
(48267, 52378, 0.0102, 1, 0, 1, 1),
(48267, 52382, 0.05, 1, 0, 1, 1),
(48267, 52383, 0.05, 1, 0, 1, 1),
(48267, 52386, 0.05, 1, 0, 1, 1),
(48267, 52494, 0.05, 1, 0, 1, 1),
(48267, 52496, 0.05, 1, 0, 1, 1),
(48267, 53010, 16.7, 1, 0, 1, 4),
(48267, 55284, 0.0102, 1, 0, 1, 1),
(48267, 55285, 0.0056, 1, 0, 1, 1),
(48267, 55286, 0.05, 1, 0, 1, 1),
(48267, 55293, 0.0037, 1, 0, 1, 1),
(48267, 55294, 0.0065, 1, 0, 1, 1),
(48267, 55295, 0.05, 1, 0, 1, 1),
(48267, 55302, 0.0019, 1, 0, 1, 1),
(48267, 55304, 0.05, 1, 0, 1, 1),
(48267, 55311, 0.012, 1, 0, 1, 1),
(48267, 55312, 0.013, 1, 0, 1, 1),
(48267, 55313, 0.05, 1, 0, 1, 1),
(48267, 55329, 0.0102, 1, 0, 1, 1),
(48267, 55330, 0.0093, 1, 0, 1, 1),
(48267, 55331, 0.05, 1, 0, 1, 1),
(48267, 55338, 0.0111, 1, 0, 1, 1),
(48267, 55339, 0.0111, 1, 0, 1, 1),
(48267, 55340, 0.05, 1, 0, 1, 1),
(48267, 55347, 0.0065, 1, 0, 1, 1),
(48267, 55348, 0.0045, 1, 0, 1, 1),
(48267, 55349, 0.05, 1, 0, 1, 1),
(48267, 55365, 0.0269, 1, 0, 1, 1),
(48267, 55366, 0.0343, 1, 0, 1, 1),
(48267, 55367, 0.05, 1, 0, 1, 1),
(48267, 55374, 0.0102, 1, 0, 1, 1),
(48267, 55375, 0.0148, 1, 0, 1, 1),
(48267, 55376, 0.05, 1, 0, 1, 1),
(48267, 55383, 0.05, 1, 0, 1, 1),
(48267, 55384, 0.0435, 1, 0, 1, 1),
(48267, 55385, 0.05, 1, 0, 1, 1),
(48267, 55392, 0.0093, 1, 0, 1, 1),
(48267, 55393, 0.0028, 1, 0, 1, 1),
(48267, 55394, 0.05, 1, 0, 1, 1),
(48267, 55401, 0.0361, 1, 0, 1, 1),
(48267, 55402, 0.0204, 1, 0, 1, 1),
(48267, 55403, 0.05, 1, 0, 1, 1),
(48267, 55410, 0.0074, 1, 0, 1, 1),
(48267, 55411, 0.0037, 1, 0, 1, 1),
(48267, 55412, 0.05, 1, 0, 1, 1),
(48267, 55419, 0.0667, 1, 0, 1, 1),
(48267, 55420, 0.0398, 1, 0, 1, 1),
(48267, 55421, 0.1, 1, 0, 1, 1),
(48267, 55428, 0.0074, 1, 0, 1, 1),
(48267, 55430, 0.05, 1, 0, 1, 1),
(48267, 55437, 0.0222, 1, 0, 1, 1),
(48267, 55438, 0.0269, 1, 0, 1, 1),
(48267, 55439, 0.05, 1, 0, 1, 1),
(48267, 55446, 0.0037, 1, 0, 1, 1),
(48267, 55447, 0.0028, 1, 0, 1, 1),
(48267, 55455, 0.013, 1, 0, 1, 1),
(48267, 55456, 0.05, 1, 0, 1, 1),
(48267, 55457, 0.05, 1, 0, 1, 1),
(48267, 55464, 0.0028, 1, 0, 1, 1),
(48267, 55465, 0.0037, 1, 0, 1, 1),
(48267, 55473, 0.0037, 1, 0, 1, 1),
(48267, 55482, 0.0232, 1, 0, 1, 1),
(48267, 55483, 0.0204, 1, 0, 1, 1),
(48267, 55484, 0.05, 1, 0, 1, 1),
(48267, 55491, 0.0139, 1, 0, 1, 1),
(48267, 55492, 0.009, 1, 0, 1, 1),
(48267, 55493, 0.05, 1, 0, 1, 1),
(48267, 55500, 0.0195, 1, 0, 1, 1),
(48267, 55501, 0.05, 1, 0, 1, 1),
(48267, 55502, 0.05, 1, 0, 1, 1),
(48267, 55509, 0.0139, 1, 0, 1, 1),
(48267, 55510, 0.012, 1, 0, 1, 1),
(48267, 55511, 0.05, 1, 0, 1, 1),
(48267, 55518, 0.0185, 1, 0, 1, 1),
(48267, 55519, 0.0111, 1, 0, 1, 1),
(48267, 55520, 0.05, 1, 0, 1, 1),
(48267, 55527, 0.0269, 1, 0, 1, 1),
(48267, 55528, 0.0278, 1, 0, 1, 1),
(48267, 55529, 0.05, 1, 0, 1, 1),
(48267, 55536, 0.0102, 1, 0, 1, 1),
(48267, 55537, 0.0232, 1, 0, 1, 1),
(48267, 55538, 0.05, 1, 0, 1, 1),
(48267, 55545, 0.0158, 1, 0, 1, 1),
(48267, 55547, 0.05, 1, 0, 1, 1),
(48267, 55554, 0.012, 1, 0, 1, 1),
(48267, 55555, 0.0185, 1, 0, 1, 1),
(48267, 55556, 0.05, 1, 0, 1, 1),
(48267, 55563, 0.013, 1, 0, 1, 1),
(48267, 55564, 0.05, 1, 0, 1, 1),
(48267, 55565, 0.05, 1, 0, 1, 1),
(48267, 55572, 0.0185, 1, 0, 1, 1),
(48267, 55573, 0.0148, 1, 0, 1, 1),
(48267, 55574, 0.05, 1, 0, 1, 1),
(48267, 55581, 0.013, 1, 0, 1, 1),
(48267, 55582, 0.0158, 1, 0, 1, 1),
(48267, 55583, 0.05, 1, 0, 1, 1),
(48267, 55590, 0.012, 1, 0, 1, 1),
(48267, 55591, 0.0148, 1, 0, 1, 1),
(48267, 55592, 0.05, 1, 0, 1, 1),
(48267, 55599, 0.0075, 1, 0, 1, 1),
(48267, 55600, 0.0111, 1, 0, 1, 1),
(48267, 55601, 0.05, 1, 0, 1, 1),
(48267, 55608, 0.009, 1, 0, 1, 1),
(48267, 55609, 0.0241, 1, 0, 1, 1),
(48267, 55610, 0.05, 1, 0, 1, 1),
(48267, 55617, 0.0167, 1, 0, 1, 1),
(48267, 55618, 0.0176, 1, 0, 1, 1),
(48267, 55619, 0.05, 1, 0, 1, 1),
(48267, 55626, 0.0139, 1, 0, 1, 1),
(48267, 55627, 0.0075, 1, 0, 1, 1),
(48267, 55635, 0.0148, 1, 0, 1, 1),
(48267, 55636, 0.05, 1, 0, 1, 1),
(48267, 55637, 0.05, 1, 0, 1, 1),
(48267, 55645, 0.0148, 1, 0, 1, 1),
(48267, 55646, 0.05, 1, 0, 1, 1),
(48267, 55653, 0.0213, 1, 0, 1, 1),
(48267, 55654, 0.0315, 1, 0, 1, 1),
(48267, 55655, 0.05, 1, 0, 1, 1),
(48267, 55662, 0.0102, 1, 0, 1, 1),
(48267, 55663, 0.0158, 1, 0, 1, 1),
(48267, 55664, 0.05, 1, 0, 1, 1),
(48267, 55671, 0.0185, 1, 0, 1, 1),
(48267, 55672, 0.0195, 1, 0, 1, 1),
(48267, 55673, 0.05, 1, 0, 1, 1),
(48267, 55680, 0.0167, 1, 0, 1, 1),
(48267, 55681, 0.012, 1, 0, 1, 1),
(48267, 55682, 0.05, 1, 0, 1, 1),
(48267, 55689, 0.05, 1, 0, 1, 1),
(48267, 55690, 0.0176, 1, 0, 1, 1),
(48267, 55691, 0.05, 1, 0, 1, 1),
(48267, 55698, 0.0102, 1, 0, 1, 1),
(48267, 55699, 0.012, 1, 0, 1, 1),
(48267, 55700, 0.05, 1, 0, 1, 1),
(48267, 55707, 0.0185, 1, 0, 1, 1),
(48267, 55708, 0.0195, 1, 0, 1, 1),
(48267, 55709, 0.05, 1, 0, 1, 1),
(48267, 55716, 0.05, 1, 0, 1, 1),
(48267, 55717, 0.0213, 1, 0, 1, 1),
(48267, 55718, 0.05, 1, 0, 1, 1),
(48267, 55725, 0.0148, 1, 0, 1, 1),
(48267, 55726, 0.0195, 1, 0, 1, 1),
(48267, 55727, 0.05, 1, 0, 1, 1),
(48267, 55734, 0.0204, 1, 0, 1, 1),
(48267, 55735, 0.0296, 1, 0, 1, 1),
(48267, 55736, 0.05, 1, 0, 1, 1),
(48267, 55743, 0.0195, 1, 0, 1, 1),
(48267, 55744, 0.0194, 1, 0, 1, 1),
(48267, 55745, 0.05, 1, 0, 1, 1),
(48267, 55752, 0.0158, 1, 0, 1, 1),
(48267, 55753, 0.0269, 1, 0, 1, 1),
(48267, 55754, 0.05, 1, 0, 1, 1),
(48267, 55761, 0.025, 1, 0, 1, 1),
(48267, 55762, 0.0195, 1, 0, 1, 1),
(48267, 55763, 0.05, 1, 0, 1, 1),
(48267, 55770, 0.0232, 1, 0, 1, 1),
(48267, 55771, 0.0195, 1, 0, 1, 1),
(48267, 58262, 6.3585, 1, 0, 1, 1),
(48267, 59029, 3.0065, 1, 0, 1, 1),
(48267, 62065, 0.1, 1, 0, 1, 1),
(48267, 62101, 0.05, 1, 0, 1, 1),
(48267, 62111, 0.05, 1, 0, 1, 1),
(48267, 62136, 0.05, 1, 0, 1, 1),
(48267, 62821, -70.9706, 1, 0, 1, 1),
(48267, 63299, 13.6364, 1, 0, 1, 1),
(48267, 63300, 4.8485, 1, 0, 1, 1),
(48267, 63314, 6.9697, 1, 0, 1, 1),
(48267, 63322, 0.303, 1, 0, 1, 1),
(48267, 63337, 34.2424, 1, 0, 1, 1),
(48267, 63343, 33.6364, 1, 0, 1, 1),
(48267, 63349, 21.2121, 1, 0, 1, 1),
(48267, 65651, 0.0454, 1, 0, 1, 1),
(48267, 65894, 0.0241, 1, 0, 1, 1),
(48267, 65895, 0.0167, 1, 0, 1, 1),
(48267, 65896, 0.025, 1, 0, 1, 1),
(48267, 65897, 0.0232, 1, 0, 1, 1),
(48267, 66912, 0.0111, 1, 0, 1, 1),
(48267, 66916, 0.0009, 1, 0, 1, 1),
(48267, 66919, 0.0009, 1, 0, 1, 1),
(48267, 66924, 0.0009, 1, 0, 1, 1),
(48267, 66931, 0.0015, 1, 0, 1, 1),
(48267, 66960, 0.0009, 1, 0, 1, 1),
(48267, 66961, 0.0009, 1, 0, 1, 1),
(48267, 66962, 0.0028, 1, 0, 1, 1),
(48267, 66963, 0.0009, 1, 0, 1, 1),
(48267, 66964, 0.0009, 1, 0, 1, 1),
(48267, 66966, 0.0028, 1, 0, 1, 1),
(48267, 66967, 0.0009, 1, 0, 1, 1),
(48267, 66969, 0.0015, 1, 0, 1, 1),
(48267, 66970, 0.05, 1, 0, 1, 1),
(48267, 66985, 0.0019, 1, 0, 1, 1),
(48267, 66987, 0.0009, 1, 0, 1, 1),
(48267, 66988, 0.0009, 1, 0, 1, 1),
(48267, 67047, 0.0009, 1, 0, 1, 1),
(48267, 67050, 0.0028, 1, 0, 1, 1),
(48267, 67051, 0.0009, 1, 0, 1, 1),
(48267, 67052, 0.0009, 1, 0, 1, 1),
(48267, 67114, 0.0009, 1, 0, 1, 1),
(48267, 67115, 0.0009, 1, 0, 1, 1),
(48267, 67116, 0.0046, 1, 0, 1, 1),
(48267, 67117, 0.0019, 1, 0, 1, 1),
(48267, 67118, 0.0019, 1, 0, 1, 1),
(48267, 67121, 0.05, 1, 0, 1, 1),
(48267, 67122, 0.0015, 1, 0, 1, 1),
(48267, 67539, 0.05, 1, 0, 1, 1),
(48267, 68197, 2.4, 1, 0, 1, 2),
(48267, 68198, 7.3, 1, 0, 1, 2),
(48267, 68787, 0.0011, 1, 0, 1, 1);

UPDATE `creature_template` SET `lootid`=48267 WHERE `entry`=48267;

SET @OGUID := 780907;
DELETE FROM `gameobject` WHERE `guid` BETWEEN @OGUID+0 AND @OGUID+14;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@OGUID+0, 206682, 1, 1, 1, -11041.4, -1375.85, 10.8068, 1.44862, 0, 0, 0.66262, 0.748956, 300, 255, 1),
(@OGUID+1, 206682, 1, 1, 1, -11025.3, -1397.11, 10.8068, 1.44862, 0, 0, 0.66262, 0.748956, 300, 255, 1),
(@OGUID+2, 206682, 1, 1, 1, -11082.7, -1407.14, 10.8068, 1.76278, 0, 0, 0.771625, 0.636078, 300, 255, 1),
(@OGUID+3, 206682, 1, 1, 1, -11080.2, -1314.31, 10.8068, 1.44862, 0, 0, 0.66262, 0.748956, 300, 255, 1),
(@OGUID+4, 206682, 1, 1, 1, -11075.6, -1333.9, 10.8068, 1.01229, 0, 0, 0.484809, 0.87462, 300, 255, 1),
(@OGUID+5, 206682, 1, 1, 1, -11102.6, -1422.79, 10.8068, 2.56563, 0, 0, 0.958819, 0.284016, 300, 255, 1),
(@OGUID+6, 206682, 1, 1, 1, -11104.7, -1312.27, 10.8068, 1.44862, 0, 0, 0.66262, 0.748956, 300, 255, 1),
(@OGUID+7, 206682, 1, 1, 1, -11135.2, -1382.03, 10.8073, 1.44862, 0, 0, 0.66262, 0.748956, 300, 255, 1),
(@OGUID+8, 206682, 1, 1, 1, -11145, -1449.7, 10.8068, 1.44862, 0, 0, 0.66262, 0.748956, 300, 255, 1),
(@OGUID+9, 206588, 1, 1, 1, -11008.8, -1361.59, 12.2339, -0.750491, 0, 0, -0.366501, 0.930418, 300, 255, 1),
(@OGUID+10, 206588, 1, 1, 1, -11116.1, -1390.73, 12.2273, -1.46608, 0, 0, -0.66913, 0.743145, 300, 255, 1),
(@OGUID+11, 206588, 1, 1, 1, -11088.3, -1337.69, 12.3042, 0, 0, 0, 0, 1, 300, 255, 1),
(@OGUID+12, 206588, 1, 1, 1, -11027.7, -1320.94, 12.2415, 0, 0, 0, 0, 1, 300, 255, 1),
(@OGUID+13, 206588, 1, 1, 1, -11100.8, -1273.78, 13.395, 0, 0, 0, 0, 1, 300, 255, 1),
(@OGUID+14, 206588, 1, 1, 1, -11132.5, -1322.1, 12.7107, 0.698131, 0, 0, 0.34202, 0.939693, 300, 255, 1);

DELETE FROM `creature_loot_template` WHERE `entry` = '47306';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(47306, 17057, 100, 1, 0, 1, 1),
(47306, 17058, 20.2649, 1, 0, 1, 1),
(47306, 33362, 0.05, 1, 0, 1, 1),
(47306, 33394, 0.05, 1, 0, 1, 1),
(47306, 33425, 0.05, 1, 0, 1, 1),
(47306, 33433, 0.05, 1, 0, 1, 1),
(47306, 33451, 0.0012, 1, 0, 1, 1),
(47306, 36781, 20, 1, 0, 1, 1),
(47306, 44700, 1, 1, 0, 1, 1),
(47306, 52197, 0.05, 1, 0, 1, 1),
(47306, 52340, 12.2898, 1, 0, 1, 1),
(47306, 52363, 0.0082, 1, 0, 1, 1),
(47306, 52367, 0.05, 1, 0, 1, 1),
(47306, 52368, 0.05, 1, 0, 1, 1),
(47306, 52370, 0.0054, 1, 0, 1, 1),
(47306, 52371, 0.05, 1, 0, 1, 1),
(47306, 52373, 0.0043, 1, 0, 1, 1),
(47306, 52375, 0.0054, 1, 0, 1, 1),
(47306, 52376, 0.0054, 1, 0, 1, 1),
(47306, 52379, 0.05, 1, 0, 1, 1),
(47306, 52382, 0.0086, 1, 0, 1, 1),
(47306, 52388, 0.05, 1, 0, 1, 1),
(47306, 52495, 0.05, 1, 0, 1, 1),
(47306, 52496, 0.0048, 1, 0, 1, 1),
(47306, 53010, 17.2, 1, 0, 1, 4),
(47306, 55284, 0.0068, 1, 0, 1, 1),
(47306, 55285, 0.0048, 1, 0, 1, 1),
(47306, 55286, 0.05, 1, 0, 1, 1),
(47306, 55293, 0.0048, 1, 0, 1, 1),
(47306, 55294, 0.0048, 1, 0, 1, 1),
(47306, 55295, 0.05, 1, 0, 1, 1),
(47306, 55303, 0.0014, 1, 0, 1, 1),
(47306, 55311, 0.0136, 1, 0, 1, 1),
(47306, 55312, 0.0102, 1, 0, 1, 1),
(47306, 55313, 0.05, 1, 0, 1, 1),
(47306, 55321, 0.0048, 1, 0, 1, 1),
(47306, 55322, 0.0032, 1, 0, 1, 1),
(47306, 55329, 0.05, 1, 0, 1, 1),
(47306, 55330, 0.0089, 1, 0, 1, 1),
(47306, 55331, 0.05, 1, 0, 1, 1),
(47306, 55338, 0.0041, 1, 0, 1, 1),
(47306, 55339, 0.0061, 1, 0, 1, 1),
(47306, 55347, 0.0116, 1, 0, 1, 1),
(47306, 55348, 0.0082, 1, 0, 1, 1),
(47306, 55349, 0.05, 1, 0, 1, 1),
(47306, 55357, 0.0014, 1, 0, 1, 1),
(47306, 55358, 0.05, 1, 0, 1, 1),
(47306, 55365, 0.05, 1, 0, 1, 1),
(47306, 55366, 0.0123, 1, 0, 1, 1),
(47306, 55367, 0.05, 1, 0, 1, 1),
(47306, 55374, 0.0116, 1, 0, 1, 1),
(47306, 55375, 0.05, 1, 0, 1, 1),
(47306, 55376, 0.05, 1, 0, 1, 1),
(47306, 55383, 0.0089, 1, 0, 1, 1),
(47306, 55384, 0.0123, 1, 0, 1, 1),
(47306, 55385, 0.05, 1, 0, 1, 1),
(47306, 55392, 0.0048, 1, 0, 1, 1),
(47306, 55393, 0.0034, 1, 0, 1, 1),
(47306, 55394, 0.05, 1, 0, 1, 1),
(47306, 55401, 0.0143, 1, 0, 1, 1),
(47306, 55402, 0.05, 1, 0, 1, 1),
(47306, 55403, 0.05, 1, 0, 1, 1),
(47306, 55410, 0.0068, 1, 0, 1, 1),
(47306, 55411, 0.0041, 1, 0, 1, 1),
(47306, 55412, 0.05, 1, 0, 1, 1),
(47306, 55419, 0.0402, 1, 0, 1, 1),
(47306, 55420, 0.0484, 1, 0, 1, 1),
(47306, 55421, 0.1, 1, 0, 1, 1),
(47306, 55428, 0.0177, 1, 0, 1, 1),
(47306, 55429, 0.013, 1, 0, 1, 1),
(47306, 55430, 0.05, 1, 0, 1, 1),
(47306, 55437, 0.0552, 1, 0, 1, 1),
(47306, 55438, 0.0259, 1, 0, 1, 1),
(47306, 55439, 0.05, 1, 0, 1, 1),
(47306, 55446, 0.0068, 1, 0, 1, 1),
(47306, 55447, 0.0075, 1, 0, 1, 1),
(47306, 55448, 0.05, 1, 0, 1, 1),
(47306, 55455, 0.0068, 1, 0, 1, 1),
(47306, 55456, 0.0054, 1, 0, 1, 1),
(47306, 55457, 0.05, 1, 0, 1, 1),
(47306, 55464, 0.0034, 1, 0, 1, 1),
(47306, 55465, 0.0048, 1, 0, 1, 1),
(47306, 55466, 0.05, 1, 0, 1, 1),
(47306, 55473, 0.013, 1, 0, 1, 1),
(47306, 55474, 0.0007, 1, 0, 1, 1),
(47306, 55475, 0.0043, 1, 0, 1, 1),
(47306, 55482, 0.0218, 1, 0, 1, 1),
(47306, 55483, 0.0273, 1, 0, 1, 1),
(47306, 55484, 0.05, 1, 0, 1, 1),
(47306, 55491, 0.013, 1, 0, 1, 1),
(47306, 55492, 0.0116, 1, 0, 1, 1),
(47306, 55493, 0.05, 1, 0, 1, 1),
(47306, 55500, 0.0116, 1, 0, 1, 1),
(47306, 55501, 0.05, 1, 0, 1, 1),
(47306, 55502, 0.05, 1, 0, 1, 1),
(47306, 55509, 0.0232, 1, 0, 1, 1),
(47306, 55510, 0.0086, 1, 0, 1, 1),
(47306, 55511, 0.05, 1, 0, 1, 1),
(47306, 55518, 0.0109, 1, 0, 1, 1),
(47306, 55519, 0.0164, 1, 0, 1, 1),
(47306, 55520, 0.05, 1, 0, 1, 1),
(47306, 55527, 0.0136, 1, 0, 1, 1),
(47306, 55528, 0.0164, 1, 0, 1, 1),
(47306, 55529, 0.05, 1, 0, 1, 1),
(47306, 55536, 0.0184, 1, 0, 1, 1),
(47306, 55537, 0.0136, 1, 0, 1, 1),
(47306, 55538, 0.05, 1, 0, 1, 1),
(47306, 55545, 0.0123, 1, 0, 1, 1),
(47306, 55546, 0.0136, 1, 0, 1, 1),
(47306, 55547, 0.05, 1, 0, 1, 1),
(47306, 55554, 0.0109, 1, 0, 1, 1),
(47306, 55555, 0.0198, 1, 0, 1, 1),
(47306, 55556, 0.05, 1, 0, 1, 1),
(47306, 55563, 0.0157, 1, 0, 1, 1),
(47306, 55564, 0.0118, 1, 0, 1, 1),
(47306, 55565, 0.05, 1, 0, 1, 1),
(47306, 55572, 0.015, 1, 0, 1, 1),
(47306, 55573, 0.0123, 1, 0, 1, 1),
(47306, 55574, 0.05, 1, 0, 1, 1),
(47306, 55581, 0.05, 1, 0, 1, 1),
(47306, 55582, 0.0157, 1, 0, 1, 1),
(47306, 55583, 0.05, 1, 0, 1, 1),
(47306, 55590, 0.0116, 1, 0, 1, 1),
(47306, 55591, 0.0136, 1, 0, 1, 1),
(47306, 55592, 0.05, 1, 0, 1, 1),
(47306, 55599, 0.0266, 1, 0, 1, 1),
(47306, 55600, 0.0123, 1, 0, 1, 1),
(47306, 55601, 0.05, 1, 0, 1, 1),
(47306, 55608, 0.0123, 1, 0, 1, 1),
(47306, 55609, 0.05, 1, 0, 1, 1),
(47306, 55610, 0.05, 1, 0, 1, 1),
(47306, 55617, 0.0109, 1, 0, 1, 1),
(47306, 55618, 0.017, 1, 0, 1, 1),
(47306, 55619, 0.05, 1, 0, 1, 1),
(47306, 55626, 0.05, 1, 0, 1, 1),
(47306, 55627, 0.05, 1, 0, 1, 1),
(47306, 55628, 0.05, 1, 0, 1, 1),
(47306, 55635, 0.0259, 1, 0, 1, 1),
(47306, 55636, 0.013, 1, 0, 1, 1),
(47306, 55637, 0.05, 1, 0, 1, 1),
(47306, 55644, 0.0116, 1, 0, 1, 1),
(47306, 55645, 0.0279, 1, 0, 1, 1),
(47306, 55646, 0.05, 1, 0, 1, 1),
(47306, 55653, 0.0143, 1, 0, 1, 1),
(47306, 55654, 0.0211, 1, 0, 1, 1),
(47306, 55655, 0.05, 1, 0, 1, 1),
(47306, 55662, 0.0082, 1, 0, 1, 1),
(47306, 55663, 0.0177, 1, 0, 1, 1),
(47306, 55664, 0.05, 1, 0, 1, 1),
(47306, 55671, 0.0089, 1, 0, 1, 1),
(47306, 55672, 0.0123, 1, 0, 1, 1),
(47306, 55673, 0.05, 1, 0, 1, 1),
(47306, 55680, 0.0116, 1, 0, 1, 1),
(47306, 55681, 0.0164, 1, 0, 1, 1),
(47306, 55682, 0.05, 1, 0, 1, 1),
(47306, 55689, 0.0095, 1, 0, 1, 1),
(47306, 55690, 0.05, 1, 0, 1, 1),
(47306, 55691, 0.05, 1, 0, 1, 1),
(47306, 55698, 0.0082, 1, 0, 1, 1),
(47306, 55699, 0.0143, 1, 0, 1, 1),
(47306, 55700, 0.05, 1, 0, 1, 1),
(47306, 55707, 0.0218, 1, 0, 1, 1),
(47306, 55708, 0.0177, 1, 0, 1, 1),
(47306, 55709, 0.05, 1, 0, 1, 1),
(47306, 55716, 0.0239, 1, 0, 1, 1),
(47306, 55717, 0.0161, 1, 0, 1, 1),
(47306, 55718, 0.05, 1, 0, 1, 1),
(47306, 55725, 0.0184, 1, 0, 1, 1),
(47306, 55726, 0.0161, 1, 0, 1, 1),
(47306, 55727, 0.05, 1, 0, 1, 1),
(47306, 55734, 0.0286, 1, 0, 1, 1),
(47306, 55735, 0.0252, 1, 0, 1, 1),
(47306, 55736, 0.05, 1, 0, 1, 1),
(47306, 55743, 0.0218, 1, 0, 1, 1),
(47306, 55744, 0.0204, 1, 0, 1, 1),
(47306, 55745, 0.05, 1, 0, 1, 1),
(47306, 55752, 0.0107, 1, 0, 1, 1),
(47306, 55753, 0.0266, 1, 0, 1, 1),
(47306, 55754, 0.05, 1, 0, 1, 1),
(47306, 55761, 0.0266, 1, 0, 1, 1),
(47306, 55762, 0.017, 1, 0, 1, 1),
(47306, 55763, 0.05, 1, 0, 1, 1),
(47306, 55770, 0.0211, 1, 0, 1, 1),
(47306, 55771, 0.0139, 1, 0, 1, 1),
(47306, 55772, 0.05, 1, 0, 1, 1),
(47306, 58262, 6.0183, 1, 0, 1, 1),
(47306, 59029, 2.8465, 1, 0, 1, 1),
(47306, 62065, 0.1, 1, 0, 1, 1),
(47306, 62101, 0.05, 1, 0, 1, 1),
(47306, 62111, 0.05, 1, 0, 1, 1),
(47306, 62136, 0.05, 1, 0, 1, 1),
(47306, 62821, -70.315, 1, 0, 1, 1),
(47306, 63299, 27.2289, 1, 0, 1, 1),
(47306, 63300, 6.506, 1, 0, 1, 1),
(47306, 63314, 10.1205, 1, 0, 1, 1),
(47306, 63337, 26.2651, 1, 0, 1, 1),
(47306, 63343, 27.2289, 1, 0, 1, 1),
(47306, 63349, 14.9398, 1, 0, 1, 1),
(47306, 65651, 0.0559, 1, 0, 1, 1),
(47306, 65894, 0.0239, 1, 0, 1, 1),
(47306, 65895, 0.05, 1, 0, 1, 1),
(47306, 65896, 0.0259, 1, 0, 1, 1),
(47306, 65897, 0.0266, 1, 0, 1, 1),
(47306, 66912, 0.0014, 1, 0, 1, 1),
(47306, 66919, 0.0014, 1, 0, 1, 1),
(47306, 66920, 0.0014, 1, 0, 1, 1),
(47306, 66924, 0.0014, 1, 0, 1, 1),
(47306, 66932, 0.05, 1, 0, 1, 1),
(47306, 66961, 0.002, 1, 0, 1, 1),
(47306, 66962, 0.002, 1, 0, 1, 1),
(47306, 66963, 0.0007, 1, 0, 1, 1),
(47306, 66964, 0.0007, 1, 0, 1, 1),
(47306, 66965, 0.002, 1, 0, 1, 1),
(47306, 66967, 0.0007, 1, 0, 1, 1),
(47306, 66971, 0.0021, 1, 0, 1, 1),
(47306, 66983, 0.0014, 1, 0, 1, 1),
(47306, 66986, 0.0041, 1, 0, 1, 1),
(47306, 66990, 0.0021, 1, 0, 1, 1),
(47306, 66991, 0.0021, 1, 0, 1, 1),
(47306, 67051, 0.0007, 1, 0, 1, 1),
(47306, 67052, 0.0014, 1, 0, 1, 1),
(47306, 67059, 0.0032, 1, 0, 1, 1),
(47306, 67111, 0.0007, 1, 0, 1, 1),
(47306, 67112, 0.0007, 1, 0, 1, 1),
(47306, 67114, 0.0014, 1, 0, 1, 1),
(47306, 67115, 0.0007, 1, 0, 1, 1),
(47306, 67116, 0.0014, 1, 0, 1, 1),
(47306, 67117, 0.0007, 1, 0, 1, 1),
(47306, 67118, 0.0014, 1, 0, 1, 1),
(47306, 67119, 0.0032, 1, 0, 1, 1),
(47306, 67121, 0.05, 1, 0, 1, 1),
(47306, 67122, 0.0021, 1, 0, 1, 1),
(47306, 67539, 0.05, 1, 0, 1, 1),
(47306, 68197, 2.3, 1, 0, 1, 2),
(47306, 68198, 7.4, 1, 0, 1, 2),
(47306, 68783, 0.0008, 1, 0, 1, 1);

UPDATE `creature_template` SET `lootid`=47306 WHERE `entry`=47306;

SET @CGUID := 837440;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+34;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 47306, 1, 1, 1, 35541, 0, -10929.7, -1505.99, 6.75974, 0.436332, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+1, 47306, 1, 1, 1, 35542, 0, -10784.5, -1401.48, 15.4361, 1.39626, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+2, 47306, 1, 1, 1, 35542, 0, -11108.8, -1424.42, 10.8901, 2.14675, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+3, 47306, 1, 1, 1, 35542, 0, -10993.9, -1360.32, 10.886, 4.43529, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+4, 47306, 1, 1, 1, 35542, 0, -11121.7, -1433.12, 10.8901, 1.90241, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+5, 47306, 1, 1, 1, 35542, 0, -11166.9, -1373.07, 10.8901, 0.314159, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+6, 47306, 1, 1, 1, 35541, 0, -11159.6, -1397.52, 10.8901, 0.331613, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+7, 47306, 1, 1, 1, 35542, 0, -11151.3, -1412.29, 10.8901, 0.436332, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+8, 47306, 1, 1, 1, 35541, 0, -11144.4, -1429.52, 10.8901, 0.436332, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+9, 47306, 1, 1, 1, 35542, 0, -11084.4, -1323.81, 10.8843, 0.280094, 300, 0, 0, 53681, 0, 2, 0, 0, 0),
(@CGUID+10, 47306, 1, 1, 1, 35541, 0, -11066, -1318.24, 10.8378, 3.43768, 300, 0, 0, 53681, 0, 2, 0, 0, 0),
(@CGUID+11, 47306, 1, 1, 1, 35542, 0, -11077.9, -1316.53, 10.8901, 5.37561, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+12, 47306, 1, 1, 1, 35541, 0, -11068.5, -1319.02, 10.8455, 3.43768, 300, 0, 0, 53681, 0, 2, 0, 0, 0),
(@CGUID+13, 47306, 1, 1, 1, 35541, 0, -11034, -1381.99, 10.816, 3.4372, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+14, 48267, 1, 1, 1, 34742, 0, -10869.2, -1364.23, 15.4777, 4.95371, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+15, 48267, 1, 1, 1, 34742, 0, -10811.6, -1292.07, 15.4184, 3.94631, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+16, 48267, 1, 1, 1, 34742, 0, -10892.4, -1376.44, 15.4777, 2.57217, 300, 0, 0, 53681, 0, 2, 0, 0, 0),
(@CGUID+17, 48267, 1, 1, 1, 34738, 0, -10894.4, -1328.96, 15.3854, 3.54145, 300, 0, 0, 53681, 0, 2, 0, 0, 0),
(@CGUID+18, 48267, 1, 1, 1, 34738, 0, -11036.2, -1495.41, 6.79455, 0.282876, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+19, 48267, 1, 1, 1, 34742, 0, -11096.5, -1512.88, 6.80077, 4.48267, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+20, 48267, 1, 1, 1, 34742, 0, -10934.3, -1275.96, 10.8854, -3.0698, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+21, 48267, 1, 1, 1, 34738, 0, -11124.7, -1408.3, 10.8854, 4.86002, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+22, 48267, 1, 1, 1, 34738, 0, -11005.6, -1369.34, 10.8854, 4.08375, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+23, 48267, 1, 1, 1, 34742, 0, -11026.7, -1390.83, 10.8854, 1.90223, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+24, 48267, 1, 1, 1, 34742, 0, -11068.8, -1487.42, 6.7604, 2.04779, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+25, 48267, 1, 1, 1, 34742, 0, -10979.6, -1472.43, 6.76603, 3.90588, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+26, 48267, 1, 1, 1, 34738, 0, -11057.8, -1328.92, 10.8196, 0.571543, 300, 0, 0, 53681, 0, 2, 0, 0, 0),
(@CGUID+27, 48267, 1, 1, 1, 34738, 0, -10938.5, -1273.39, 10.8854, 2.20639, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+28, 48267, 1, 1, 1, 34738, 0, -11038.8, -1497.04, 6.79455, 3.33408, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+29, 48267, 1, 1, 1, 34738, 0, -11057.6, -1329.24, 10.8196, 0.34372, 300, 0, 0, 53681, 0, 2, 0, 0, 0),
(@CGUID+30, 48267, 1, 1, 1, 34738, 0, -11007.5, -1367.65, 10.8971, 4.64403, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+31, 48267, 1, 1, 1, 34742, 0, -10981.8, -1471.74, 6.76603, 3.91411, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+32, 48267, 1, 1, 1, 34742, 0, -10892.5, -1379.97, 15.4777, 4.78122, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+33, 48267, 1, 1, 1, 34738, 0, -11119.8, -1372.78, 10.9298, 1.81553, 300, 3, 0, 53681, 0, 1, 0, 0, 0),
(@CGUID+34, 48267, 1, 1, 1, 34738, 0, -11029.8, -1392.16, 10.8854, 2.94403, 300, 3, 0, 53681, 0, 1, 0, 0, 0);

UPDATE `creature` SET `MovementType`=0 WHERE `id` IN (48267, 47306) AND `MovementType`=2;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (837469,183312,837451,837449,837463,837462);
UPDATE `creature` SET `position_x`=-11063.01, `position_y`=-1380.05, `position_z`=10.80, `orientation`=5.38, `spawndist`=0, `MovementType`=0 WHERE `guid`=837453;

DELETE FROM `creature_formations` WHERE `leaderGUID` = '837452';
INSERT INTO `creature_formations` (`leaderGUID`, `memberGUID`, `dist`, `angle`, `groupAI`) VALUES
(837452, 837452, 10, 0, 0),
(837452, 183308, 10, 4.5, 0),
(837452, 837450, 10, 1.5, 0);

DELETE FROM `waypoint_data` WHERE `id` = '8374520';
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_flag`, `action`, `action_chance`, `wpguid`) VALUES
(8374520, 1, -11078.3, -1322, 10.8076, 0, 0, 0, 0, 100, 0),
(8374520, 2, -11115.6, -1343.48, 10.8055, 0, 0, 0, 0, 100, 0),
(8374520, 3, -11108.6, -1374.54, 10.8061, 0, 0, 0, 0, 100, 0),
(8374520, 4, -11087.3, -1395.17, 10.8078, 0, 0, 0, 0, 100, 0),
(8374520, 5, -11036.2, -1383.73, 10.8077, 0, 0, 0, 0, 100, 0),
(8374520, 6, -10999.3, -1372.76, 10.8068, 0, 0, 0, 0, 100, 0),
(8374520, 7, -10987.7, -1334.81, 10.8089, 0, 0, 0, 0, 100, 0),
(8374520, 8, -10996.6, -1310.29, 10.8046, 0, 0, 0, 0, 100, 0),
(8374520, 9, -11019, -1307.89, 10.8082, 0, 0, 0, 0, 100, 0),
(8374520, 10, -11058.8, -1315.91, 10.807, 0, 0, 0, 0, 100, 0);

UPDATE `creature` SET `MovementType`=2 WHERE `guid`=837452;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=100 WHERE `entry`=47567 AND `item`=62817;
UPDATE `gameobject` SET `id`=206684 WHERE `id`=206682;
UPDATE `gameobject_template` SET `displayId`=8701, `data10`=88646, `data5`=1 WHERE `entry`=206684;
UPDATE `gameobject` SET `spawntimesecs`=120 WHERE `id`=206684;

DELETE FROM `creature_text` WHERE `entry`=47306;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47306,0,0,'A prisoner has escaped! Slay $g!',12,0,100,0,0,0,'Comment'),
(47306,0,1,'I will show you the weakness of flesh!',12,0,100,0,0,0,'Comment'),
(47306,0,2,'I will spill your blood in Deathwing\'s name!',12,0,100,0,0,0,'Comment'),
(47306,0,3,'If slavery does not suit you, maybe death will!',12,0,100,0,0,0,'Comment'),
(47306,0,4,'You won\'t make it far!',12,0,100,0,0,0,'Comment'),
(47306,0,5,'You\'re going to wish you\'d never set foot in Uldum!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=48267;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48267,0,0,'A prisoner has escaped! Slay $g!',12,0,100,0,0,0,'Comment'),
(48267,0,1,'I will show you the weakness of flesh!',12,0,100,0,0,0,'Comment'),
(48267,0,2,'I will spill your blood in Deathwing\'s name!',12,0,100,0,0,0,'Comment'),
(48267,0,3,'If slavery does not suit you, maybe death will!',12,0,100,0,0,0,'Comment'),
(48267,0,4,'You won\'t make it far!',12,0,100,0,0,0,'Comment'),
(48267,0,5,'You\'re going to wish you\'d never set foot in Uldum!',12,0,100,0,0,0,'Comment');

-- Neferset Sentinel
SET @ENTRY := 47306;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

-- Neferset Denizen
SET @ENTRY := 48267;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

UPDATE `creature_template` SET `VehicleId`=1288, `InhabitType`=4 WHERE `entry`=47873;
UPDATE `creature_template` SET `ScriptName`='npc_prince_nadun_escape' WHERE `entry`=46872;

DELETE FROM `spell_target_position` WHERE `id` = '89074';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89074, 1, -11004.11, -1254.43, 15.00, 6.27);

DELETE FROM `spell_target_position` WHERE `id` = '89101';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89101, 1, -10984.14, -1251.70, 13.24, 3.15);

DELETE FROM `spell_target_position` WHERE `id` = '89077';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89077, 1, -11002.90, -1248.02, 13.32, 4.66);

DELETE FROM `creature_text` WHERE `entry`=47896;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47896,0,0,'Free... at last. Your reward will be substantial, friends.',12,0,100,1,0,0,'Comment'),
(47896,1,0,'Your approach is... unorthodox. Though, I suppose with the smoke from the fires all they\'ll see is your silhouettes.',12,0,100,1,0,0,'Comment'),
(47896,2,0,'Let\'s go!',12,0,100,1,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=47912;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47912,0,0,'This is the most moronic... half-assed... ridiculous plan you\'ve ever come up with, Budd!',12,0,100,0,0,0,'Comment'),
(47912,1,0,'But I suppose it\'s the only plan we\'ve got.',12,0,100,1,0,0,'Comment'),
(47912,2,0,'What am I grabbing again?',12,0,100,1,0,0,'Comment'),
(47912,3,0,'Shut your stupid face, Budd. SHUT IT!!',12,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_prince_nadun_mantaur' WHERE `entry`=47896;
UPDATE `creature_template` SET `ScriptName`='npc_adarrah_mantaur' WHERE `entry`=47912;
UPDATE `creature_template` SET `ScriptName`='npc_mantaur_camera_event' WHERE `entry`=47873;

UPDATE `creature_template` SET `VehicleId`=1203 WHERE `entry`=47873;
UPDATE `creature_template` SET `VehicleId`=1241 WHERE `entry`=47098;
UPDATE `creature_template` SET `VehicleId`=1245 WHERE `entry`=47112;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47112';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47112, 46875, 0, 1, 'Budd -> On Mantaur', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47112';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47112, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47098';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47098, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47098';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47098, 46878, 0, 1, 'Mack -> On Mantaur', 8, 0),
(47098, 46879, 1, 1, 'Harkor -> On Mantaur', 8, 0);

DELETE FROM `spell_target_position` WHERE `id` = '89075';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89075, 1, -11009.47, -1264.56, 13.24, 4.44);

DELETE FROM `spell_target_position` WHERE `id` = '89076';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89076, 1, -11005.73, -1264.57, 13.24, 4.38);

DELETE FROM `creature_text` WHERE `entry`=46875;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46875,0,0,'LOOK AT ME!!!! I\'M A MANTAUR!!!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (47873, 47112, 47098, 46879, 46878, 46875, 47896);

-- Mantaur 1
SET @ENTRY := 47098;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Invisibility ");

-- Harkor
SET @ENTRY := 46879;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Invisibility ");

-- Mack
SET @ENTRY := 46878;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Invisibility ");

-- Budd
SET @ENTRY := 46875;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Invisibility ");

UPDATE `quest_template` SET `PrevQuestId`='28533' WHERE `Id`=28561;
UPDATE `quest_template` SET `PrevQuestId`='28135' WHERE `Id` IN (27519, 27595);
UPDATE `quest_template` SET `PrevQuestId`='27706' WHERE `Id`=27628;
UPDATE `quest_template` SET `PrevQuestId`='27669' WHERE `Id`=27899;
UPDATE `quest_template` SET `PrevQuestId`='27519' WHERE `Id`=28845;
UPDATE `quest_template` SET `PrevQuestId`='28135' WHERE `Id`=27519;

UPDATE `gossip_menu_option` SET `option_id`=8, `npc_option_npcflag`=65536 WHERE `menu_id`=9868 AND `id`=0;

DELETE FROM `spell_script_names` WHERE `spell_id` = '88882';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(88882, 'spell_draining_venom');

-- Orsis Survivor
SET @ENTRY := 45715;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,79,0,0,0,0,0,0,19,45716,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Enter Vehicle"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,33,45715,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=45715;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45715,0,0,'I owe you my life. My people have paid a high price for defying Deathwing.',12,0,100,0,0,0,'Comment'),
(45715,0,1,'I\'d only heard about your kind in stories, $R. I never thought I\'d owe my life to one of you.',12,0,100,0,0,0,'Comment'),
(45715,0,2,'I... *cough* I thank you, stranger.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=45716;
UPDATE `creature_template` SET `ScriptName`='npc_orsis_survivor_event' WHERE `entry`=45715;
UPDATE `creature_template` SET `IconName`='openhand' WHERE `entry`=45715;

UPDATE `creature` SET `position_z`=87.25 WHERE `guid`=182424;
UPDATE `creature` SET `position_z`=95.75 WHERE `guid`=182406;

UPDATE `creature_template` SET `IconName`='openhandglow', `npcflag`=1 WHERE `entry` IN (46042, 46041);

-- Colossus of the Moon
SET @ENTRY := 46042;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,8,15000,17000,11,85840,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Thunderclap on Close"),
(@ENTRY,@SOURCETYPE,1,0,7,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Friendly"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Enemy"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,10000,10000,10000,10000,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Friendly"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,11,85840,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Thunderclap");

-- Colossus of the Sun
SET @ENTRY := 46041;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,8,15000,17000,11,85840,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Thunderclap on Close"),
(@ENTRY,@SOURCETYPE,1,0,7,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set Friendly"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Enemy"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,10000,10000,10000,10000,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Friendly"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,11,85840,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Thunderclap");

UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=28960;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (735250, 735257, 735261, 735251, 184095, 735252);
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid` IN
(727948,727937,727957,727951,727930,727931,727955,727935,727947,727934,
727943,727940,727952,727939,727945,727953,727932,727938,727956,727958,
727944);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27993';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5455, 27993, 27141, 1, 66, 11);

-- Harrison Jones
SET @ENTRY := 44860;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

-- Totally Generic Bunny (JSB)
SET @ENTRY := 28960;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2000,2000,2000,2000,33,47318,0,0,0,0,0,18,45,0,0,0.0,0.0,0.0,0.0,"OOC - Quest Complete");

UPDATE `creature_template` SET `VehicleId`=1203, `ScriptName`='npc_post_orsis_camera_event' WHERE `entry`=48991;

DELETE FROM `spell_target_position` WHERE `id` = '87119';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(87119, 1, -9406.19, -959.26, 113.96, 6.28);

DELETE FROM `spell_target_position` WHERE `id` = '91377';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91377, 1, -9393.13, -948.90, 116.76, 5.35);

DELETE FROM `creature_text` WHERE `entry`=47684;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47684,0,0,'Perhaps we ought to give the enemy what they\'re after... and spare our people the coming bloodshed.',12,0,100,1,0,0,'Comment'),
(47684,1,0,'I must act to protect my people first. Our enemies buried Orsis in the desert. How do you fight against that sort of power?',12,0,100,1,0,0,'Comment'),
(47684,2,0,'Your words ring true, brother... but even a king cannot make this decision alone. I will put the issue to a High Council vote.',12,0,100,1,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=46774;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46774,0,0,'I urge you to reconsider, Phaoris. Deathwing would use the scepters\' power to unravel the secrets of Uldum and unleash great destruction.',12,0,100,1,0,0,'Comment'),
(46774,1,0,'We fight to the death, Phaoris! Our race was created to guard this land. We must not betray that legacy.',12,0,100,1,0,0,'Comment'),
(46774,2,0,'I defer to your wisdom, brother. Let us pray we are quick to come to a decision. The enemy will not wait.',12,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_nadun_post_orsis_event' WHERE `entry`=46774;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735294;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27628';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5466, 27628, 1, 74, 0);

UPDATE `quest_template` SET `PrevQuestId`='27631' WHERE `Id` IN (28200, 28201, 28198);
UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (735267, 735266, 735265, 735221, 735222, 735220);
UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=45321;

DELETE FROM `creature_text` WHERE `entry`=46333;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46333,0,0,'If the rumors about you are true, stranger, I will gladly join you in the fight against the Neferset!',12,0,100,0,0,0,'Comment'),
(46333,0,1,'The $R that rescued Prince Nadun is the only $R that I\'ll ever take orders from.',12,0,100,0,0,0,'Comment'),
(46333,0,2,'I heard of what you did in Orsis. I will be honored to fight along your side.',12,0,100,0,0,0,'Comment'),
(46333,0,3,'I will defend Ramkahen with my bare hands if I have to!',12,0,100,0,0,0,'Comment'),
(46333,0,4,'It\'s about time we started doing something.',12,0,100,0,0,0,'Comment'),
(46333,0,5,'We will defend our lands!',12,0,100,0,0,0,'Comment');

-- Ramkahen Laborer
SET @ENTRY := 46333;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Flags"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,72,1,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,85,89278,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Recruit Laborer"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,41,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,64,0,100,0,0,0,0,0,33,46333,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit");

UPDATE `quest_template` SET `PrevQuestId`='27630' WHERE `Id`=27837;
UPDATE `creature_template` SET `ScriptName`='npc_ramkahen_prisoner_chain', `flags_extra`=128 WHERE `entry`=46462;
UPDATE `gossip_menu_option` SET `option_id`=0, `npc_option_npcflag`=0 WHERE `menu_id`=12121 AND `id`=0;
UPDATE `creature_template` SET `unit_flags`=4 WHERE `entry`=46425;

DELETE FROM `creature_text` WHERE `entry`=46425;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46425,0,0,'Wait! Here come the Neferset guards! Fight near me so I can beat their skulls in!',14,0,100,0,0,0,'Comment'),
(46425,1,0,'Ramkahen Prisoner picks up a key from Neferset Enforcer.',16,0,100,0,0,0,'Comment'),
(46425,2,0,'Freedom at last. I thank you, stranger. Tahet is no longer here. A cruel Neferset warlord called Caimas took him.',12,0,100,0,0,0,'Comment'),
(46425,3,0,'I must warn you. Caimas does horrible things to prisoners... he forces them to fight his pet beasts. Prepare for the worst, friend.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature` WHERE `guid` IN (735295, 735296, 735297, 735299);
UPDATE `creature_template` SET `ScriptName`='npc_ramkahen_prisoner_event' WHERE `entry`=46425;
UPDATE `creature_template` SET `ScriptName`='npc_neferset_overlord_event' WHERE `entry`=46441;
UPDATE `creature` SET `phaseMask`=1 WHERE `id`=46311;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=46441;
UPDATE `creature_template` SET `npcflag`=3 WHERE `entry`=46425;
UPDATE `creature` SET `spawntimesecs`=120 WHERE `guid`=735220;

-- Neferset Enforcer
SET @ENTRY := 46432;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,1,0,0,0,0,0,8,0,0,0,-11074.4,-1970.25,9.7,5.46,"On Just Summoned - Move To Pos");

DELETE FROM `creature_involvedrelation` WHERE `id` = '46425' AND `quest` = '27707';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(46425, 27707);

DELETE FROM `creature_questrelation` WHERE `id` = '46425' AND `quest` = '27738';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(46425, 27738);

DELETE FROM `creature_text` WHERE `entry`=49148;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49148,0,0,'Serpents of the depths! Come and aid your master!',14,0,100,0,0,0,'Comment');

-- Dark Ritualist Zakahn
SET @ENTRY := 49148;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `ScriptName`='npc_dark_ritualist_zakahn' WHERE `entry`=49148;
UPDATE `creature_template_addon` SET `auras`='91600, 68797' WHERE `entry`=49148;

DELETE FROM `event_scripts` WHERE `id` = '26734' AND `datalong` = '46887';
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `x`, `y`, `z`, `o`) VALUES
(26734, 5, 10, 46887, 45000, -10411.216, -1308.53, 44.31, 3.15),
(26734, 5, 10, 46887, 45000, -10413.182, -1304.86, 43.99, 3.15),
(26734, 5, 10, 46887, 45000, -10411.832, -1299.42, 43.50, 3.42),
(26734, 5, 10, 46887, 45000, -10402.772, -1302.47, 43.87, 3.29),
(26734, 5, 10, 46887, 45000, -10415.839, -1305.49, 44.04, 3.07);

UPDATE `creature_template` SET `minlevel`=83, `maxlevel`=83, `exp`=3, `faction_A`=2333, `faction_H`=2333, `mindmg`=967.1, `maxdmg`=1260.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=46887;

-- Ramkahen Laborer
SET @ENTRY := 46887;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,1,0,0,0,0,0,8,0,0,0,-10450.7,-1307.51,44.34,3.38,"On Just Summoned - Move To Pos");

DELETE FROM `creature_equip_template` WHERE `entry` = '46887';
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(46887, 1, 30697, 0, 5258);

DELETE FROM `spell_area` WHERE `spell` = '89298' AND `quest_start` = '28210';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(89298, 5665, 28210, 28276, 1, 66);

UPDATE `creature_template` SET `mindmg`=967, `maxdmg`=1021, `baseattacktime`=2000, `rangeattacktime`=2000, `minrangedmg`=2000, `maxrangedmg`=2500 WHERE `entry`=48022;

-- Salhet
SET @ENTRY := 48022;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,2000,2000,2000,2000,49,0,0,0,0,0,0,11,45353,50,0,0.0,0.0,0.0,0.0,"OOC - Check for Hyenas"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,89710,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shoot"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1500,1500,1500,2000,11,89710,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,4,0,19,0,100,0,28276,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Despawn"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Despawn");

-- Salhet
SET @ENTRY := 48237;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,28276,0,0,0,45,0,1,0,0,0,0,11,0,60,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Salhet (Summon)");

UPDATE `creature_template` SET `ScriptName`='npc_tahet_pit_of_scales' WHERE `entry`=46496;

DELETE FROM `creature_text` WHERE `entry`=46496;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46496,0,0,'I... *cough* I owe you my life, stranger. Thank you.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_caimas_the_pit_master' WHERE `entry`=46276;

DELETE FROM `creature_text` WHERE `entry`=46276;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46276,0,0,'I\'m afraid your friend won\'t be waking up any time soon. I always sedate my croc\'s food. I hate to see them struggle with their meal.',14,0,100,1,0,0,'Comment'),
(46276,1,0,'But perhaps I will make an exception for you. Let the crocs out! IT\'S FEEDING TIME!',14,0,100,1,0,0,'Comment'),
(46276,2,0,'Bah! Mere luck! My pets will make mincemeat out of you yet!',14,0,100,1,0,0,'Comment'),
(46276,3,0,'Enough! I grow tired of you!',14,0,100,1,0,0,'Comment'),
(46276,4,0,'Lure Caimas over the Croc Eggs without stepping on them yourself!',41,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_entry_gorebite' WHERE `entry`=46278;
UPDATE `creature_template` SET `ScriptName`='npc_entry_thartep' WHERE `entry`=46280;
UPDATE `creature_template` SET `ScriptName`='npc_entry_kamen' WHERE `entry`=46281;
UPDATE `creature_template` SET `ScriptName`='npc_young_crocolisk' WHERE `entry`=46279;

UPDATE `gameobject_template` SET `data3`=86593 WHERE `entry`=206112;

DELETE FROM `spell_script_names` WHERE `spell_id` = '86593';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(86593, 'spell_tiny_teeth');

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=46276;
UPDATE `creature_template` SET `VehicleId`=1203, `InhabitType`=4, `ScriptName`='npc_high_council_event_camera' WHERE `entry`=49167;
UPDATE `creature_template` SET `ScriptName`='npc_king_phaoris' WHERE `entry`=47684;

DELETE FROM `creature_text` WHERE `entry`=49170;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49170,0,0,'On the matter of war against the rebel tribe of Ramkahen... has each member of the High Council reached a decision?',12,0,100,0,0,0,'Comment'),
(49170,1,0,'Nadun...',12,0,100,0,0,0,'Comment'),
(49170,2,0,'Commander. Move all forward regiments westward.',12,0,100,0,0,0,'Comment'),
(49170,3,0,'We attack Neferset city at first light.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=49383;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49383,0,0,'Yes, your majesty. The Sword of Ramkahen casts its vote in favor of war. Your armies are standing at the ready.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=49175;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49175,0,0,'The Voice of Ramkahen casts its vote in favor of war as well.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=49172;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49172,0,0,'The Faith of Ramkahen... abstains.',12,0,100,0,0,0,'Comment'),
(49172,1,0,'In my visions, negotiations with the enemy brought our people fleeting peace... followed by terrible betrayal and destruction.',12,0,100,0,0,0,'Comment'),
(49172,2,0,'But war, waged by a leader reluctantly following protocol, brought an even swifter demise to our nation.',12,0,100,0,0,0,'Comment'),
(49172,3,0,'Only one vision offered a faint glimmer of hope. And in that vision... the High Council did not make this decision for you, Phaoris.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=49202;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49202,0,0,'My liege, a skirmish along the Neferset border just occurred. A patrol led by your brother was involved...',12,0,100,0,0,0,'Comment'),
(49202,1,0,'He\'s been... mortally wounded, sir.',12,0,100,0,0,0,'Comment');

UPDATE `quest_template` SET `RewardSpellCast`=0 WHERE `Id`=28533;

DELETE FROM `spell_target_position` WHERE `id` = '91628';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91628, 1, -9378.49, -966.60, 117.20, 1.99);

DELETE FROM `spell_target_position` WHERE `id` = '91630';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91630, 1, -9380.082, -958.96, 113.84, 3.22);

DELETE FROM `spell_target_position` WHERE `id` = '91634';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91634, 1, -9391.368, -965.7743, 113.7635, 0.0);

DELETE FROM `spell_target_position` WHERE `id` = '91974';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91974, 1, -9388.904, -953.00, 113.7647, 6.03);

DELETE FROM `spell_target_position` WHERE `id` = '91643';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91643, 1, -9389.716, -959.8177, 113.7635, 0.0);

DELETE FROM `spell_target_position` WHERE `id` = '91708';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91708, 1, -9409.90, -959.21, 114.187, 0.01);

UPDATE `creature_template` SET `ScriptName`='npc_envoy_council_event' WHERE `entry`=49202;
UPDATE `creature_template` SET `ScriptName`='npc_king_phaoris_council_event' WHERE `entry`=49170;

DELETE FROM `creature_template_addon` WHERE `entry` IN (49383, 49175, 49172);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(49383, 1, '60191'),
(49175, 1, '60191'),
(49172, 1, '60191');

UPDATE `quest_template` SET `PrevQuestId`='28561' WHERE `Id` IN (28498, 28499);
UPDATE `quest_template` SET `PrevQuestId`='28500' WHERE `Id`=28501;
UPDATE `quest_template` SET `PrevQuestId`='28501' WHERE `Id`=27755;
UPDATE `quest_template` SET `PrevQuestId`='28623' WHERE `Id`=28483;
UPDATE `quest_template` SET `PrevQuestId`='28623' WHERE `Id`=28480;
UPDATE `quest_template` SET `PrevQuestId`='28486' WHERE `Id`=28520;
UPDATE `quest_template` SET `PrevQuestId`='27760' WHERE `Id` IN (27761, 27777);

DELETE FROM `conditions` WHERE `SourceEntry` = '28500' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28500, 28498, 0),
(20, 8, 28500, 28499, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28500' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28500, 28498, 0),
(19, 8, 28500, 28499, 0);

DELETE FROM `creature_text` WHERE `entry`=48761;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48761,0,0,'It... it worked! We will defend Nahom with the power stored in this temple!',12,0,100,0,0,0,'Comment');

-- Salhet
SET @ENTRY := 48761;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,28500,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 0");

UPDATE `creature_template` SET `ScriptName`='npc_sun_radiance', `InhabitType`=4 WHERE `entry`=51147;

DELETE FROM `spell_target_position` WHERE `id` = '94261';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(94261, 1, -9804.22, -1721.57, 29.26, 5.52);

UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_ramkahen_sergeant' WHERE `entry`=49228;
UPDATE `creature_template` SET `VehicleId`=1127 WHERE `entry`=45670;

DELETE FROM `creature_text` WHERE `entry`=45670;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45670,0,0,'The enemy approaches. Use the Move ability to move the Ramkahen Champions to the southern ramp.$B$B|TInterface\\Icons\\misc_arrowleft.blp:64|t',42,0,100,0,0,0,'Comment'),
(45670,1,0,'Use your archers to support your infantry. A few volleys of flaming arrows will take down most groups.$B$B|TInterface\\Icons\\ability_searingarrow.blp:64|t',42,0,100,0,0,0,'Comment'),
(45670,2,0,'Use the Sun\'s Radiance ability if you get overwhelmed! It will heal your units and deal terrible damage to the opponent.$B$B|TInterface\\Icons\\spell_holy_divineprovidence.blp:64|t',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_champions_controller' WHERE `entry`=45660;
UPDATE `creature_template` SET `ScriptName`='npc_archers_controller' WHERE `entry`=45680;
UPDATE `creature_template` SET `ScriptName`='npc_light_controller' WHERE `entry`=48466;
UPDATE `creature_template` SET `ScriptName`='npc_waves_controller' WHERE `entry`=48486;

DELETE FROM `spell_script_names` WHERE `spell_id` = '85212';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85212, 'spell_move_champions');

DELETE FROM `spell_script_names` WHERE `spell_id` = '89803';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89803, 'spell_flame_arrows');

DELETE FROM `spell_script_names` WHERE `spell_id` = '92728';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(92728, 'spell_sun_radiance');

UPDATE `creature_template` SET `spell2`=89803 WHERE `entry`=45670;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=35.724 WHERE `entry`=46590 AND `item`=62483;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=10.363 WHERE `entry`=47014 AND `item`=62483;
UPDATE `creature_template` SET `minlevel`=82, `maxlevel`=82, `exp`=3, `faction_A`=2333, `faction_H`=2333, `speed_walk`=0.666, `speed_run`=1.142, `mindmg`=927.2, `maxdmg`=1240.1, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_flags`=4 WHERE `entry`=45679;
UPDATE `creature_template` SET `minlevel`=82, `maxlevel`=82, `exp`=3, `faction_A`=2333, `faction_H`=2333, `speed_walk`=0.666, `speed_run`=1.142, `mindmg`=927.2, `maxdmg`=1240.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45643;
UPDATE `creature_template` SET `minlevel`=82, `maxlevel`=82, `unit_flags`=0 WHERE `entry` IN (45670, 45680, 45660, 48466);
UPDATE `creature_template` SET `minlevel`=82, `maxlevel`=82, `unit_flags`=0 WHERE `entry`=51147;

DELETE FROM conditions WHERE SourceEntry = '89805' AND ConditionValue2 IN (45543, 48462, 48463, 45586, 48490); 
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 89805, 0, 0, 31, 0, 3, 45543, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89805, 0, 1, 31, 0, 3, 48462, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89805, 0, 2, 31, 0, 3, 48463, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89805, 0, 3, 31, 0, 3, 45586, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89805, 0, 4, 31, 0, 3, 48490, 0, 0, 0, '', 'Explosive Arrows - Only Infantry');

DELETE FROM conditions WHERE SourceEntry = '89816' AND ConditionValue2 IN (45543, 48462, 48463, 45586, 48490); 
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 89816, 0, 0, 31, 0, 3, 45543, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89816, 0, 1, 31, 0, 3, 48462, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89816, 0, 2, 31, 0, 3, 48463, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89816, 0, 3, 31, 0, 3, 45586, 0, 0, 0, '', 'Explosive Arrows - Only Infantry'),
(13, 7, 89816, 0, 4, 31, 0, 3, 48490, 0, 0, 0, '', 'Explosive Arrows - Only Infantry');

DELETE FROM conditions WHERE SourceEntry = '90118' AND ConditionValue2 IN (45543, 48462, 48463, 45679, 45643, 45586, 48490); 
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 90118, 0, 0, 31, 0, 3, 45543, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 1, 90118, 0, 1, 31, 0, 3, 48462, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 1, 90118, 0, 2, 31, 0, 3, 48463, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 1, 90118, 0, 3, 31, 0, 3, 45586, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 1, 90118, 0, 4, 31, 0, 3, 48490, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 2, 90118, 0, 0, 31, 0, 3, 45543, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 2, 90118, 0, 1, 31, 0, 3, 48462, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 2, 90118, 0, 2, 31, 0, 3, 48463, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 2, 90118, 0, 3, 31, 0, 3, 45586, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 2, 90118, 0, 4, 31, 0, 3, 48490, 0, 0, 0, '', 'Sun Radiance - Only Infantry'),
(13, 4, 90118, 0, 0, 31, 0, 3, 45679, 0, 0, 0, '', 'Sun Radiance - Friendly Heal'),
(13, 4, 90118, 0, 1, 31, 0, 3, 45643, 0, 0, 0, '', 'Sun Radiance - Friendly Heal');

UPDATE `creature_template` SET `ScriptName`='npc_neferset_wave_attacker' WHERE `entry` IN (45543, 45586, 48490);
UPDATE `creature_template` SET `minlevel`=82, `maxlevel`=83, `exp`=3, `faction_A`=2334, `faction_H`=2334, `speed_walk`=0.66, `mindmg`=550, `maxdmg`=950, `attackpower`=7, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45543;
UPDATE `creature_template` SET `minlevel`=84, `maxlevel`=84, `exp`=3, `faction_A`=2334, `faction_H`=2334, `mindmg`=484, `maxdmg`=726, `attackpower`=181, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (45586, 48490);
UPDATE `creature_template` SET `ScriptName`='npc_ramkahen_champion' WHERE `entry`=45643;
UPDATE `creature_template` SET `ScriptName`='npc_nahom_battle_camera' WHERE `entry`=45670;
UPDATE `creature_template` SET `ScriptName`='npc_infantry_and_archer_counter' WHERE `entry` IN (45679, 45643);
UPDATE `creature_template` SET `type_flags`=0 WHERE `entry`=45643;

DELETE FROM `creature_template_addon` WHERE `entry` IN
(45543,48462,48463,45679,45643,45586,48490,45660,45680,48466,48486,51147,45670);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(45543, 1, '60191'),
(48462, 1, '60191'),
(48463, 1, '60191'),
(45679, 1, '60191'),
(45643, 1, '60191'),
(45586, 1, '60191'),
(48490, 1, '60191'),
(45660, 1, '60191'),
(45680, 1, '60191'),
(48466, 1, '60191'),
(48486, 1, '60191'),
(51147, 1, '60191'),
(45670, 1, '60191');

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=45670;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=51147;
UPDATE `quest_template` SET `PrevQuestId`='27778' WHERE `Id`=27779;
UPDATE `creature` SET `MovementType`=0 WHERE `id`=48512;

SET @CGUID := 837475;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+51;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 48512, 1, 1, 1, 0, 1, -10719.2, -748.402, 87.9873, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+1, 48512, 1, 1, 1, 0, 1, -10720, -752.197, 88.1805, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+2, 48512, 1, 1, 1, 0, 1, -10721.1, -755.989, 88.1697, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+3, 48512, 1, 1, 1, 0, 1, -10721.8, -759.44, 88.0545, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+4, 48512, 1, 1, 1, 0, 1, -10723.5, -762.935, 87.8261, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+5, 48512, 1, 1, 1, 0, 1, -10725, -766.493, 87.6052, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+6, 48512, 1, 1, 1, 0, 1, -10726.5, -770.095, 87.3941, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+7, 48512, 1, 1, 1, 0, 1, -10728.2, -774.489, 87.2442, 2.99548, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+8, 48512, 1, 1, 1, 0, 1, -10738.2, -818.25, 90.5461, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+9, 48512, 1, 1, 1, 0, 1, -10737.1, -814.292, 90.2732, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+10, 48512, 1, 1, 1, 0, 1, -10736.1, -810.752, 89.9468, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+11, 48512, 1, 1, 1, 0, 1, -10734.8, -806.254, 89.3858, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+12, 48512, 1, 1, 1, 0, 1, -10734.7, -802.569, 88.8168, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+13, 48512, 1, 1, 1, 0, 1, -10734.1, -798.57, 88.1965, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+14, 48512, 1, 1, 1, 0, 1, -10732.9, -794.329, 88.095, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+15, 48512, 1, 1, 1, 0, 1, -10731.6, -789.669, 87.8392, 2.86982, 300, 0, 0, 64496, 4363, 0, 0, 0, 0),
(@CGUID+16, 48514, 1, 1, 1, 0, 1, -10718.1, -779.497, 86.0313, 2.87846, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+17, 48514, 1, 1, 1, 0, 1, -10716.9, -774.91, 86.0992, 2.87846, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+18, 48514, 1, 1, 1, 0, 1, -10715.9, -771.179, 86.3853, 2.87846, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+19, 48514, 1, 1, 1, 0, 1, -10714.6, -767.905, 86.7266, 2.83998, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+20, 48514, 1, 1, 1, 0, 1, -10713.4, -764.082, 87.2144, 2.83998, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+21, 48514, 1, 1, 1, 0, 1, -10712.3, -760.633, 87.6528, 2.83998, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+22, 48514, 1, 1, 1, 0, 1, -10710.9, -756.698, 88.0778, 2.83998, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+23, 48514, 1, 1, 1, 0, 1, -10709.8, -753.188, 88.3383, 2.83998, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+24, 48514, 1, 1, 1, 0, 1, -10708.7, -749.866, 88.4568, 2.83998, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+25, 48514, 1, 1, 1, 0, 1, -10713.9, -748.216, 88.3335, 2.82035, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+26, 48514, 1, 1, 1, 0, 1, -10715, -751.55, 88.4134, 2.82035, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+27, 48514, 1, 1, 1, 0, 1, -10716.2, -755.124, 88.3303, 2.82035, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+28, 48514, 1, 1, 1, 0, 1, -10717.5, -758.836, 88.0871, 2.82035, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+29, 48514, 1, 1, 1, 0, 1, -10718.6, -762.317, 87.7435, 2.82035, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+30, 48514, 1, 1, 1, 0, 1, -10719.9, -766.03, 87.3594, 2.82035, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+31, 48514, 1, 1, 1, 0, 1, -10721, -769.45, 87.0223, 2.82035, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+32, 48514, 1, 1, 1, 0, 1, -10722.7, -773.414, 86.7663, 2.88632, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+33, 48514, 1, 1, 1, 0, 1, -10723.8, -777.674, 86.6054, 2.88632, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+34, 48514, 1, 1, 1, 0, 1, -10721.3, -790.497, 86.5481, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+35, 48514, 1, 1, 1, 0, 1, -10722.1, -794.993, 86.9485, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+36, 48514, 1, 1, 1, 0, 1, -10722.8, -799.295, 87.3593, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+37, 48514, 1, 1, 1, 0, 1, -10723.5, -803.302, 87.6874, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+38, 48514, 1, 1, 1, 0, 1, -10724.1, -806.777, 87.9351, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+39, 48514, 1, 1, 1, 0, 1, -10724.9, -811.025, 88.3597, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+40, 48514, 1, 1, 1, 0, 1, -10725.6, -815.218, 88.977, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+41, 48514, 1, 1, 1, 0, 1, -10726.2, -818.693, 89.4469, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+42, 48514, 1, 1, 1, 0, 1, -10726.9, -822.782, 89.9667, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+43, 48514, 1, 1, 1, 0, 1, -10732.7, -821.769, 90.5014, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+44, 48514, 1, 1, 1, 0, 1, -10732, -817.576, 90.1289, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+45, 48514, 1, 1, 1, 0, 1, -10731.4, -814.052, 89.7973, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+46, 48514, 1, 1, 1, 0, 1, -10730.6, -809.798, 89.3066, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+47, 48514, 1, 1, 1, 0, 1, -10729.9, -805.75, 88.6609, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+48, 48514, 1, 1, 1, 0, 1, -10729.3, -801.999, 88.1857, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+49, 48514, 1, 1, 1, 0, 1, -10728.6, -797.944, 87.9618, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+50, 48514, 1, 1, 1, 0, 1, -10727.8, -793.427, 87.5648, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0),
(@CGUID+51, 48514, 1, 1, 1, 0, 1, -10727, -788.841, 87.1223, 2.96879, 300, 0, 0, 64496, 0, 0, 0, 0, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735269;

DELETE FROM `creature_addon` WHERE `guid` = '735269';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(735269, 1, '49414');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28623';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 5679, 28623, 28520, 1, 66);

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=49244;
UPDATE `creature_template` SET `ScriptName`='npc_ramkahen_ranger_captain' WHERE `entry`=49244;
UPDATE `creature_template` SET `ScriptName`='npc_ramkahen_ranger' WHERE `entry`=49242;

DELETE FROM `script_waypoint` WHERE `entry` = '49244';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(49244, 1, -10981.44, -889.76, 112.06, 'Ramkahen Ranger Captain WP'),
(49244, 2, -10984.99, -878.06, 117.53, 'Ramkahen Ranger Captain WP'),
(49244, 3, -10994.95, -868.29, 127.92, 'Ramkahen Ranger Captain WP'),
(49244, 4, -10996.47, -856.25, 134.65, 'Ramkahen Ranger Captain WP'),
(49244, 5, -11000.27, -851.15, 138.74, 'Ramkahen Ranger Captain WP'),
(49244, 6, -11000.56, -835.87, 146.76, 'Ramkahen Ranger Captain WP'),
(49244, 7, -11007.73, -827.88, 155.03, 'Ramkahen Ranger Captain WP'),
(49244, 8, -11019.33, -815.76, 166.12, 'Ramkahen Ranger Captain WP'),
(49244, 9, -11032.04, -816.79, 175.14, 'Ramkahen Ranger Captain WP'),
(49244, 10, -11033.03, -823.48, 176.34, 'Ramkahen Ranger Captain WP'),
(49244, 11, -11033.27, -842.96, 184.65, 'Ramkahen Ranger Captain WP'),
(49244, 12, -11031.78, -862.15, 185.28, 'Ramkahen Ranger Captain WP'),
(49244, 13, -11050.85, -887.57, 191.95, 'Ramkahen Ranger Captain WP'),
(49244, 14, -11073.69, -888.37, 204.22, 'Ramkahen Ranger Captain WP'),
(49244, 15, -11086.10, -901.41, 213.64, 'Ramkahen Ranger Captain WP'),
(49244, 16, -11075.01, -915.63, 217.96, 'Ramkahen Ranger Captain WP'),
(49244, 17, -11074.96, -935.25, 235.90, 'Ramkahen Ranger Captain WP'),
(49244, 18, -11080.87, -935.92, 238.04, 'Ramkahen Ranger Captain WP'),
(49244, 19, -11087.74, -928.62, 239.17, 'Ramkahen Ranger Captain WP'),
(49244, 20, -11089.18, -921.89, 240.08, 'Ramkahen Ranger Captain WP'),
(49244, 21, -11099.71, -911.64, 243.71, 'Ramkahen Ranger Captain WP'),
(49244, 22, -11103.67, -911.43, 245.00, 'Ramkahen Ranger Captain WP'),
(49244, 23, -11116.71, -898.40, 254.25, 'Ramkahen Ranger Captain WP'),
(49244, 24, -11143.23, -882.99, 262.40, 'Ramkahen Ranger Captain WP');

UPDATE `creature` SET `phaseMask`=39278 WHERE `id`=49281;

DELETE FROM `spell_script_names` WHERE `spell_id` = '87368';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87368, 'spell_mech_control_scrambler');

DELETE FROM `conditions` WHERE `SourceEntry` = '28486' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28486, 28483, 0),
(20, 8, 28486, 28480, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28486' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28486, 28483, 0),
(19, 8, 28486, 28480, 0);

DELETE FROM conditions WHERE SourceEntry = '87368' AND ConditionValue2 = '46587';
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 87368, 0, 0, 31, 0, 3, 46587, 0, 0, 0, '', 'Scrambler - Only on Twizzlefux');

DELETE FROM `spell_script_names` WHERE `spell_id` = '87020';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87020, 'spell_holographic_projector');

-- Ramkahen Marksman
SET @ENTRY := 48514;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,85232,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,85232,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
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
(@ENTRY,@SOURCETYPE,21,0,1,0,100,0,3800,4000,3800,4000,11,90329,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,22,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Phasing");

UPDATE `creature_template` SET `ScriptName`='npc_holographic_image' WHERE `entry`=45176;
UPDATE `creature_template` SET `ScriptName`='npc_cursed_engineer' WHERE `entry`=46617;

-- Unstable Bomb Bot
SET @ENTRY := 46888;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,33,46888,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,37,46888,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Die");

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=46888;
UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=46692;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12408 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12408 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12408, 0, 0, 0, 9, 0, 28277, 0, 0, 0, 0, 0, '', 'Salhet - Show gossip only if quest 28277 is active');

UPDATE `creature` SET `position_z`=147.842 WHERE `guid`=185030;
UPDATE `creature_template` SET `scale`=0.19, `InhabitType`=4, `modelid1`=35418 WHERE `entry` IN (46372, 46750);
UPDATE `creature_template` SET `ScriptName`='npc_wibson_mainframe', `npcflag`=1, `IconName`='Interact' WHERE `entry`=46715;
UPDATE `creature_template` SET `minlevel`=82, `maxlevel`=82, `VehicleId`=1308 WHERE `entry`=48171;

DELETE FROM `spell_script_names` WHERE `spell_id` = '89533';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89533, 'spell_salhet_summon_camera');

-- Salhet
SET @ENTRY := 48237;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,28276,0,0,0,45,0,1,0,0,0,0,11,0,60,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Salhet (Summon)"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12408,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12408,0,0,0,85,89533,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Camera");

UPDATE `creature_template` SET `ScriptName`='npc_lions_controller', `unit_flags`=768 WHERE `entry`=48198;

DELETE FROM `spell_script_names` WHERE `spell_id` = '89570';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89570, 'spell_lions_move');

UPDATE `creature_template` SET `ScriptName`='npc_lions_camera' WHERE `entry`=48171;

DELETE FROM `creature_text` WHERE `entry`=48171;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48171,0,0,'You can command the lions to move with the Move ability.$B$B|TInterface\\Icons\\misc_arrowleft.blp:48|t',42,0,100,0,0,0,'Comment'),
(48171,1,0,'Hyenas approach from your left flank. Engage them!',42,0,100,0,0,0,'Comment'),
(48171,2,0,'They approach from the right now! Use your Fierce Roar ability if your lions become overwhelmed!$B$B|TInterface\\Icons\\ability_druid_skinteeth.blp:48|t',42,0,100,0,0,0,'Comment'),
(48171,3,0,'They approach from both sides in great number now!',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_lions_counter' WHERE `entry`=48168;
UPDATE `creature_template` SET `ScriptName`='npc_bloodsnarl_scavenger' WHERE `entry`=48209;
UPDATE `creature_template` SET `dmg_multiplier`=35 WHERE `entry`=48168;
UPDATE `creature_template` SET `Health_mod`=100, `unit_flags`=768 WHERE `entry`=48171;

DELETE FROM conditions WHERE SourceEntry = '89599' AND ConditionValue2 = '48209'; 
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 89599, 0, 0, 31, 0, 3, 48209, 0, 0, 0, '', 'Fierce Roar - On Hyenas');

DELETE FROM conditions WHERE SourceEntry = '92796' AND ConditionValue2 = '48168'; 
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 92796, 0, 0, 31, 0, 3, 48168, 0, 0, 0, '', 'Claw Flurry - On Lions');

UPDATE `creature_template` SET `VehicleId`=1180, `InhabitType`=3 WHERE `entry`=46372;
UPDATE `creature_template` SET `ScriptName`='npc_fusion_core_summoned' WHERE `entry`=46372;

DELETE FROM `spell_script_names` WHERE `spell_id` = '86418';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(86418, 'spell_summon_fusion_core');

UPDATE `creature_template` SET `speed_run`=2.56286 WHERE `entry`=46372;

SET @CGUID := 837410;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+2117 AND @CGUID+3362;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+2117, 46384, 1, 1, 1, -10559.27, -2419.438, 91.19573, 0.3879321, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2118, 46384, 1, 1, 1, -10542.08, -2417.555, 89.68987, 3.03792, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2119, 46384, 1, 1, 1, -10546.19, -2409.131, 88.64568, 3.669949, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2120, 46384, 1, 1, 1, -10547.17, -2410.916, 88.96697, 3.822188, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2121, 46384, 1, 1, 1, -10549.29, -2414.122, 89.50555, 6.170253, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2122, 46384, 1, 1, 1, -10552.3, -2414.157, 89.94744, 4.966391, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2123, 46384, 1, 1, 1, -10558.12, -2418.293, 90.89568, 0.5977584, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2124, 46384, 1, 1, 1, -10541.19, -2416.467, 89.34783, 2.747815, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2125, 46384, 1, 1, 1, -10522.09, -2406.162, 86.12902, 2.793981, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2126, 46384, 1, 1, 1, -10521.98, -2407.056, 86.35705, 3.27272, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2127, 46384, 1, 1, 1, -10526.38, -2415.982, 88.80236, 5.557833, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2128, 46384, 1, 1, 1, -10525.38, -2418.682, 89.23864, 4.527641, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2129, 46384, 1, 1, 1, -10539.23, -2393.927, 88.34076, 1.900818, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2130, 46384, 1, 1, 1, -10544.2, -2386.62, 86.20604, 0, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver)
(@CGUID+2131, 46384, 1, 1, 1, -10544.2, -2386.62, 86.20604, 0, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver)
(@CGUID+2132, 46384, 1, 1, 1, -10539.91, -2395.765, 88.18316, 2.35067, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2133, 46384, 1, 1, 1, -10529.4, -2319.65, 75.88493, 0, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2134, 46384, 1, 1, 1, -10529.4, -2319.65, 75.88493, 0, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2135, 46384, 1, 1, 1, -10524.53, -2390.814, 86.9494, 0.6560251, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2136, 46384, 1, 1, 1, -10530.13, -2393.079, 87.24638, 3.858659, 120, 0, 0), -- Crazed Gnome (Area: M.A.C. Diver) (possible waypoints or random movement)
(@CGUID+2137, 46384, 1, 1, 1, -10470.16, -2309.477, 64.20893, 2.738812, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2138, 46384, 1, 1, 1, -10482.65, -2321.287, 64.42963, 1.618698, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2139, 46384, 1, 1, 1, -10482.1, -2317.13, 61.20323, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2140, 46384, 1, 1, 1, -10493, -2342.96, 67.14384, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2141, 46384, 1, 1, 1, -10464.89, -2322.952, 61.54832, 1.307207, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2142, 46384, 1, 1, 1, -10479.63, -2354.101, 63.06055, 4.654658, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2143, 46384, 1, 1, 1, -10495.3, -2344.68, 64.84174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2144, 46384, 1, 1, 1, -10491.9, -2282.95, 62.26403, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2145, 46384, 1, 1, 1, -10477.61, -2287.414, 63.59306, 0.5739191, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2146, 46384, 1, 1, 1, -10491.9, -2282.95, 62.26403, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2147, 46384, 1, 1, 1, -10482.1, -2317.13, 61.20323, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2148, 46384, 1, 1, 1, -10481.9, -2349.971, 64.21094, 2.498873, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2149, 46384, 1, 1, 1, -10464.35, -2326.357, 60.9221, 3.108421, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2150, 46384, 1, 1, 1, -10495.3, -2344.68, 64.84174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2151, 46384, 1, 1, 1, -10481.92, -2323.213, 64.37202, 4.344935, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2152, 46384, 1, 1, 1, -10479.21, -2291.953, 64.08171, 4.547107, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2153, 46384, 1, 1, 1, -10510.25, -2325.714, 71.59864, 5.840634, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2154, 46384, 1, 1, 1, -10512.4, -2326.799, 72.94337, 3.950259, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2155, 46384, 1, 1, 1, -10470.67, -2312.312, 64.33247, 4.59208, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2156, 46384, 1, 1, 1, -10469.68, -2343.483, 61.35938, 3.553631, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2157, 46384, 1, 1, 1, -10470.21, -2343.479, 61.71094, 3.444827, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2158, 46384, 1, 1, 1, -10493, -2342.96, 67.14384, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2159, 46384, 1, 1, 1, -10484.1, -2335.78, 62.06223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2160, 46384, 1, 1, 1, -10498, -2316.7, 67.87354, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2161, 46384, 1, 1, 1, -10484.1, -2335.78, 62.06223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2162, 46384, 1, 1, 1, -10508.8, -2335.86, 67.22533, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2163, 46384, 1, 1, 1, -10508.8, -2335.86, 67.22533, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2164, 46384, 1, 1, 1, -10498, -2316.7, 67.87354, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2165, 46384, 1, 1, 1, -10461.4, -2330.72, 56.36363, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2166, 46384, 1, 1, 1, -10461.4, -2330.72, 56.36363, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2167, 46384, 1, 1, 1, -10456.06, -2322.844, 59.88572, 4.504816, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2168, 46384, 1, 1, 1, -10455.24, -2319.932, 59.88229, 1.303716, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2169, 46384, 1, 1, 1, -10464.1, -2287.97, 51.96013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2170, 46384, 1, 1, 1, -10464.1, -2287.97, 51.96013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2171, 46384, 1, 1, 1, -10450.16, -2293.098, 54.9262, 2.461168, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2172, 46384, 1, 1, 1, -10449.21, -2291.135, 54.47918, 4.349039, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2173, 46384, 1, 1, 1, -10448.8, -2290.534, 54.40422, 1.535853, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2174, 46384, 1, 1, 1, -10448.5, -2288.467, 54.41594, 1.996812, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2175, 46384, 1, 1, 1, -10444.29, -2338.699, 56.59986, 5.694069, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2176, 46384, 1, 1, 1, -10443.57, -2338.171, 56.42799, 1.966949, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2177, 46384, 1, 1, 1, -10430.23, -2298.008, 51.17551, 0.4215064, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2178, 46384, 1, 1, 1, -10430.06, -2297.812, 51.13685, 3.885204, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2179, 46384, 1, 1, 1, -10450.5, -2382.99, 52.29866, 1.859585, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2180, 46384, 1, 1, 1, -10448.63, -2381.301, 51.72663, 0.9573525, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2181, 46384, 1, 1, 1, -10404.64, -2393.595, 37.63679, 2.53132, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2182, 46384, 1, 1, 1, -10402.84, -2395.095, 37.73685, 3.910156, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2183, 46384, 1, 1, 1, -10423.33, -2389.439, 49.53498, 2.687189, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2184, 46384, 1, 1, 1, -10424.44, -2390.45, 50.32185, 3.87866, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2185, 46384, 1, 1, 1, -10472.62, -2412.929, 54.94342, 4.672649, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2186, 46384, 1, 1, 1, -10479.62, -2423.311, 59.76966, 2.230042, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2187, 46384, 1, 1, 1, -10454.95, -2418.691, 46.56312, 5.344199, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2188, 46384, 1, 1, 1, -10454.18, -2419.719, 46.53212, 5.675934, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2189, 46384, 1, 1, 1, -10441.17, -2416.552, 49.23231, 2.107277, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2190, 46384, 1, 1, 1, -10441.92, -2418.061, 49.29506, 3.279844, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2191, 46384, 1, 1, 1, -10427.26, -2410.712, 50.20318, 0.7218696, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2192, 46384, 1, 1, 1, -10426.63, -2411.681, 50.13859, 0.3198976, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2193, 46384, 1, 1, 1, -10467.77, -2436.815, 51.84369, 0.8822217, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2194, 46384, 1, 1, 1, -10469.2, -2438.123, 53.49359, 5.92848, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2195, 46384, 1, 1, 1, -10457.9, -2434.85, 40.34023, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2196, 46384, 1, 1, 1, -10457.9, -2434.85, 40.34023, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2197, 46384, 1, 1, 1, -10448.4, -2436.8, 41.38013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2198, 46384, 1, 1, 1, -10448.4, -2436.8, 41.38013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2199, 46384, 1, 1, 1, -10461.8, -2441.67, 40.33393, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2200, 46384, 1, 1, 1, -10461.8, -2441.67, 40.33393, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2201, 46384, 1, 1, 1, -10522.17, -2420.524, 89.48742, 1.890015, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2202, 46384, 1, 1, 1, -10442.2, -2438.247, 46.73401, 4.885099, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2203, 46384, 1, 1, 1, -10471.1, -2445.69, 47.73513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2204, 46384, 1, 1, 1, -10471.1, -2445.69, 47.73513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2205, 46384, 1, 1, 1, -10443.99, -2439.309, 46.29993, 2.193186, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2206, 46384, 1, 1, 1, -10455.33, -2442.681, 43.3468, 2.112579, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2207, 46384, 1, 1, 1, -10520.68, -2423.808, 89.70251, 0.2111547, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2208, 46384, 1, 1, 1, -10443.29, -2439.246, 46.42104, 4.431401, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2209, 46384, 1, 1, 1, -10455.31, -2443.038, 43.23572, 2.170489, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2210, 46384, 1, 1, 1, -10440.19, -2440.093, 46.28699, 0.7718408, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2211, 46384, 1, 1, 1, -10440.9, -2440.63, 42.32703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2212, 46384, 1, 1, 1, -10440.9, -2440.63, 42.32703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2213, 46384, 1, 1, 1, -10460.1, -2447.32, 39.02213, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2214, 46384, 1, 1, 1, -10460.1, -2447.32, 39.02213, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2215, 46384, 1, 1, 1, -10421.04, -2430.42, 46.82316, 5.734636, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2216, 46384, 1, 1, 1, -10448.3, -2445.49, 39.65223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2217, 46384, 1, 1, 1, -10448.3, -2445.49, 39.65223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2218, 46384, 1, 1, 1, -10445.19, -2446.058, 44.724, 1.313053, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2219, 46384, 1, 1, 1, -10419.8, -2431.44, 46.65251, 5.300392, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2220, 46384, 1, 1, 1, -10432.9, -2441.137, 44.95227, 3.201954, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2221, 46384, 1, 1, 1, -10444.01, -2446.719, 44.75658, 0.824053, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2222, 46384, 1, 1, 1, -10431.09, -2441.503, 44.89736, 2.484919, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2223, 46384, 1, 1, 1, -10462.6, -2453.96, 39.78143, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2224, 46384, 1, 1, 1, -10462.6, -2453.96, 39.78143, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2225, 46384, 1, 1, 1, -10457.63, -2454.337, 41.97009, 3.726596, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2226, 46384, 1, 1, 1, -10455.93, -2454.235, 41.56091, 4.300964, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2227, 46384, 1, 1, 1, -10445.28, -2453.209, 42.87585, 2.298239, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2228, 46384, 1, 1, 1, -10423.04, -2443.538, 45.43933, 0.9377357, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2229, 46384, 1, 1, 1, -10445.17, -2454.894, 42.49695, 3.594349, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2230, 46384, 1, 1, 1, -10424.43, -2446.412, 44.81262, 4.275014, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2231, 46384, 1, 1, 1, -10450.1, -2457.22, 37.06963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2232, 46384, 1, 1, 1, -10450.1, -2457.22, 37.06963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2233, 46384, 1, 1, 1, -10437.6, -2455.92, 39.66883, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2234, 46384, 1, 1, 1, -10437.6, -2455.92, 39.66883, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2235, 46384, 1, 1, 1, -10431.96, -2455.528, 42.3385, 4.892632, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2236, 46384, 1, 1, 1, -10431.24, -2455.233, 42.3739, 5.158096, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2237, 46384, 1, 1, 1, -10443.89, -2461.401, 41.5612, 6.166722, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2238, 46384, 1, 1, 1, -10445.85, -2462.008, 41.00671, 5.500358, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2239, 46568, 1, 1, 1, -10439.45, -2476.003, 40.14598, 4.465617, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2240, 46384, 1, 1, 1, -10436.25, -2463.952, 41.8136, 2.95461, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2241, 46384, 1, 1, 1, -10422.27, -2460.904, 42.80334, 1.790589, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2242, 46384, 1, 1, 1, -10435.92, -2463.153, 41.87048, 2.518022, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2243, 46384, 1, 1, 1, -10422.37, -2461.401, 42.69983, 1.910184, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2244, 46384, 1, 1, 1, -10417.2, -2496.98, 34.66383, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2245, 46384, 1, 1, 1, -10417.2, -2496.98, 34.66383, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2246, 46384, 1, 1, 1, -10402.3, -2500.43, 32.34723, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2247, 46384, 1, 1, 1, -10402.3, -2500.43, 32.34723, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2248, 46384, 1, 1, 1, -10417.52, -2510.892, 36.05405, 2.345728, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2249, 46384, 1, 1, 1, -10415.57, -2511.9, 35.99497, 6.1342, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2250, 46384, 1, 1, 1, -10408.7, -2507.7, 32.69053, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2251, 46384, 1, 1, 1, -10408.7, -2507.7, 32.69053, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2252, 46384, 1, 1, 1, -10403.96, -2505.235, 35.06308, 3.551342, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2253, 46384, 1, 1, 1, -10404.13, -2505.485, 35.07505, 3.601926, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2254, 46384, 1, 1, 1, -10417.77, -2516.773, 35.72861, 0.665844, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2255, 46384, 1, 1, 1, -10419.53, -2518.159, 35.5626, 0.6564786, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2256, 46384, 1, 1, 1, -10391.4, -2503.57, 31.79873, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2257, 46384, 1, 1, 1, -10404.92, -2514.726, 34.02964, 3.268815, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2258, 46384, 1, 1, 1, -10402.48, -2514.516, 33.59531, 3.435583, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2259, 46384, 1, 1, 1, -10519.28, -2479.626, 84.79704, 2.096878, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2260, 46384, 1, 1, 1, -10518.78, -2481.042, 85.02702, 4.281562, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2261, 46384, 1, 1, 1, -10394.31, -2511.915, 32.61132, 5.712955, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2262, 46384, 1, 1, 1, -10402.67, -2518.22, 33.07163, 2.810127, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2263, 46384, 1, 1, 1, -10402.54, -2518.345, 33.02402, 2.853314, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2264, 46384, 1, 1, 1, -10388.32, -2507.21, 32.30419, 5.504189, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2265, 46384, 1, 1, 1, -10393.53, -2511.963, 32.55159, 5.841185, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2266, 46384, 1, 1, 1, -10386.5, -2507.53, 32.24773, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2267, 46384, 1, 1, 1, -10410.2, -2524.27, 31.62623, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2268, 46384, 1, 1, 1, -10410.2, -2524.27, 31.62623, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2269, 46384, 1, 1, 1, -10406.87, -2524.324, 33.42905, 2.669212, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2270, 46384, 1, 1, 1, -10529.53, -2473.306, 85.16227, 5.768938, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2271, 46384, 1, 1, 1, -10391.56, -2514.552, 32.09838, 0.1839804, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2272, 46384, 1, 1, 1, -10390.22, -2513.541, 32.07537, 0.4398313, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2273, 46384, 1, 1, 1, -10531.32, -2472.245, 85.39306, 3.011545, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2274, 46384, 1, 1, 1, -10384.8, -2510.026, 32.10693, 5.310966, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2275, 46384, 1, 1, 1, -10404.92, -2525.207, 32.89731, 2.550695, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2276, 46384, 1, 1, 1, -10384, -2511.31, 32.10693, 1.50411, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2277, 46384, 1, 1, 1, -10385.76, -2516.641, 32.00365, 4.131835, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2278, 46384, 1, 1, 1, -10392.67, -2522.382, 31.25351, 1.137516, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2279, 46384, 1, 1, 1, -10536.33, -2473.609, 86.40651, 4.509679, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2280, 46384, 1, 1, 1, -10537.62, -2474.531, 86.87379, 4.289787, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2281, 46384, 1, 1, 1, -10542.73, -2469.611, 88.10017, 2.468632, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2282, 46384, 1, 1, 1, -10543.17, -2469.895, 88.19386, 1.917361, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2283, 46384, 1, 1, 1, -10393.9, -2525.05, 31.10923, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2284, 46384, 1, 1, 1, -10385.83, -2518.499, 31.87035, 1.47768, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2285, 46384, 1, 1, 1, -10393.3, -2529.878, 30.70897, 0.931767, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2286, 46384, 1, 1, 1, -10385.9, -2521.118, 31.73656, 1.011719, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2287, 46384, 1, 1, 1, -10393.4, -2530.496, 30.63476, 0.7108473, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2288, 46384, 1, 1, 1, -10382.83, -2517.339, 32.10693, 2.953501, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2289, 46384, 1, 1, 1, -10378.44, -2513.416, 32.23193, 4.635789, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2290, 46384, 1, 1, 1, -10380.4, -2517.8, 32.23543, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2291, 46568, 1, 1, 1, -10384.76, -2525.647, 31.74828, 1.320133, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2292, 46384, 1, 1, 1, -10375.82, -2510.781, 31.83813, 1.296649, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2293, 46384, 1, 1, 1, -10379.11, -2529.627, 32.36425, 1.953103, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2294, 46384, 1, 1, 1, -10378.97, -2530.391, 32.27245, 2.049245, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2295, 46384, 1, 1, 1, -10371.95, -2519.488, 31.82934, 2.078288, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2296, 46384, 1, 1, 1, -10372.23, -2520.089, 31.83715, 2.871473, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2297, 46384, 1, 1, 1, -10461.61, -2563.924, 13.61313, 2.037193, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2298, 46384, 1, 1, 1, -10460.3, -2566.52, 12.88743, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2299, 46384, 1, 1, 1, -10444.65, -2571.085, 14.25315, 1.633589, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2300, 46384, 1, 1, 1, -10445.31, -2572.617, 12.67844, 2.253169, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2301, 46384, 1, 1, 1, -10481.7, -2562, 12.58563, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2302, 46384, 1, 1, 1, -10481.7, -2562, 12.58563, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2303, 46384, 1, 1, 1, -10468.12, -2568.882, 12.47, 3.048077, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2304, 46384, 1, 1, 1, -10468.72, -2569.028, 12.55479, 3.117032, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2305, 46384, 1, 1, 1, -10457.88, -2578.667, 10.27723, 0.6023594, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2306, 46384, 1, 1, 1, -10476, -2573.17, 10.82413, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2307, 46384, 1, 1, 1, -10476, -2573.17, 10.82413, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2308, 46384, 1, 1, 1, -10457.3, -2580.508, 9.729467, 6.2013, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2309, 46384, 1, 1, 1, -10373.2, -2579.43, 20.81073, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2310, 46384, 1, 1, 1, -10373.2, -2579.43, 20.81073, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2311, 46384, 1, 1, 1, -10374.55, -2582.966, 21.12569, 1.99529, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2312, 46384, 1, 1, 1, -10377.84, -2584.504, 20.03926, 4.390082, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2313, 46384, 1, 1, 1, -10377.42, -2585.082, 20.19307, 4.508304, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2314, 46384, 1, 1, 1, -10374.09, -2586.519, 20.48214, 0.9003276, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2315, 46384, 1, 1, 1, -10361.76, -2587.865, 20.99628, 0.9313204, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2316, 46384, 1, 1, 1, -10359.15, -2587.455, 20.75214, 3.12609, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2317, 46384, 1, 1, 1, -10362.48, -2589.741, 21.0832, 3.5891, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2318, 46384, 1, 1, 1, -10355.83, -2589.586, 20.24604, 4.260546, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2319, 46384, 1, 1, 1, -10360.46, -2593.362, 20.98164, 2.386423, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2320, 46384, 1, 1, 1, -10354.2, -2591.16, 6.126244, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2321, 46384, 1, 1, 1, -10354.2, -2591.16, 6.126244, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2322, 46384, 1, 1, 1, -10357.29, -2596.875, 19.71064, 5.606243, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2323, 46384, 1, 1, 1, -10317.5, -2555.71, 18.66513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2324, 46384, 1, 1, 1, -10317.5, -2555.71, 18.66513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2325, 46384, 1, 1, 1, -10347.7, -2590.82, 6.472963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2326, 46384, 1, 1, 1, -10347.7, -2590.82, 6.472963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2327, 46384, 1, 1, 1, -10313.41, -2561.257, 20.00584, 0.2791923, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2328, 46384, 1, 1, 1, -10316.1, -2567.82, 17.93863, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2329, 46384, 1, 1, 1, -10316.1, -2567.82, 17.93863, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2330, 46384, 1, 1, 1, -10310.5, -2557.135, 19.92283, 1.34507, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2331, 46384, 1, 1, 1, -10357.8, -2601.88, 5.314283, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2332, 46384, 1, 1, 1, -10357.8, -2601.88, 5.314283, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2333, 46384, 1, 1, 1, -10309.3, -2554.766, 19.34373, 0.7571847, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2334, 46384, 1, 1, 1, -10312.12, -2562.135, 18.90672, 0.1161416, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2335, 46384, 1, 1, 1, -10306.86, -2548.155, 19.01585, 5.606017, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2336, 46384, 1, 1, 1, -10306.65, -2547.483, 19.21482, 4.578936, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2337, 46384, 1, 1, 1, -10349.8, -2599.4, 5.316254, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2338, 46384, 1, 1, 1, -10349.8, -2599.4, 5.316254, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2339, 46384, 1, 1, 1, -10338.68, -2595.715, 6.707467, 1.68256, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2340, 46384, 1, 1, 1, -10307.86, -2559.803, 18.71311, 2.383234, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2341, 46384, 1, 1, 1, -10307.52, -2559.721, 18.71311, 2.188294, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2342, 46384, 1, 1, 1, -10337.82, -2596.389, 6.490914, 1.270172, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2343, 46384, 1, 1, 1, -10304.75, -2559.136, 18.71311, 5.534507, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2344, 46384, 1, 1, 1, -10411.47, -2610.879, 5.910961, 0.9138222, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2345, 46384, 1, 1, 1, -10411.19, -2611.201, 5.929924, 0.7699877, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2346, 46384, 1, 1, 1, -10410.78, -2611.559, 5.886413, 0.5915747, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2347, 46384, 1, 1, 1, -10303.43, -2558.098, 18.71311, 5.722022, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2348, 46384, 1, 1, 1, -10411.38, -2611.804, 5.886413, 0.6452071, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2349, 46384, 1, 1, 1, -10351, -2607.379, 5.747708, 0.7127798, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2350, 46384, 1, 1, 1, -10409.87, -2612.412, 5.886413, 1.132744, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2351, 46384, 1, 1, 1, -10350.98, -2607.414, 5.747708, 0.6938537, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2352, 46384, 1, 1, 1, -10412.37, -2611.912, 5.886413, 0.9641711, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2353, 46384, 1, 1, 1, -10412.33, -2612.006, 5.886413, 0.9116579, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2354, 46384, 1, 1, 1, -10426.94, -2606.764, 7.056335, 6.007033, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2355, 46384, 1, 1, 1, -10330.56, -2595.615, 7.155754, 1.076373, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2356, 46384, 1, 1, 1, -10426.44, -2607.333, 6.996276, 5.865188, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2357, 46384, 1, 1, 1, -10427.52, -2606.94, 7.126892, 5.818671, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2358, 46384, 1, 1, 1, -10331.02, -2596.393, 6.789299, 1.098491, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2359, 46384, 1, 1, 1, -10412.76, -2612.776, 6.011413, 0.7204918, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2360, 46384, 1, 1, 1, -10428.38, -2606.724, 7.104431, 5.61126, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2361, 46384, 1, 1, 1, -10426.58, -2607.678, 7.013122, 5.739013, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2362, 46384, 1, 1, 1, -10429.1, -2606.15, 5.983324, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2363, 46384, 1, 1, 1, -10347.07, -2606.932, 5.45439, 2.436123, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2364, 46568, 1, 1, 1, -10301.07, -2556.716, 18.66087, 3.634986, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2365, 46384, 1, 1, 1, -10413.3, -2613.25, 5.983324, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2366, 46384, 1, 1, 1, -10410.75, -2614.048, 5.886413, 1.261456, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2367, 46384, 1, 1, 1, -10426.98, -2608.142, 7.06195, 4.295045, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2368, 46384, 1, 1, 1, -10426.5, -2608.367, 7.003845, 5.15105, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2369, 46384, 1, 1, 1, -10426.22, -2608.525, 6.969909, 5.594071, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2370, 46384, 1, 1, 1, -10302.41, -2562.33, 18.58811, 2.598736, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2371, 46384, 1, 1, 1, -10302.25, -2562.318, 18.58811, 2.6546, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2372, 46384, 1, 1, 1, -10427.64, -2608.725, 7.141052, 5.227752, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2373, 46384, 1, 1, 1, -10425.94, -2609.581, 7.09906, 1.658831, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2374, 46384, 1, 1, 1, -10454.18, -2588.869, 7.459452, 1.3196, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2375, 46384, 1, 1, 1, -10425.44, -2610.995, 6.8703, 0.3881587, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2376, 46384, 1, 1, 1, -10335.77, -2604.773, 5.362454, 2.369036, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2377, 46384, 1, 1, 1, -10346.34, -2611.042, 5.245999, 4.095559, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2378, 46384, 1, 1, 1, -10454.9, -2591.69, 7.144303, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2379, 46384, 1, 1, 1, -10342.29, -2609.277, 5.247708, 3.792688, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2380, 46384, 1, 1, 1, -10428, -2612.07, 7.052329, 0.5779541, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2381, 46384, 1, 1, 1, -10432.33, -2609.936, 7.194763, 0.4542533, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2382, 46384, 1, 1, 1, -10429.92, -2611.425, 7.261413, 0.2528682, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2383, 46384, 1, 1, 1, -10426.81, -2612.947, 6.922118, 1.264673, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2384, 46384, 1, 1, 1, -10343.63, -2610.791, 5.182278, 3.950945, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2385, 46384, 1, 1, 1, -10432.7, -2610.12, 5.814613, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2386, 46384, 1, 1, 1, -10426.55, -2613.733, 6.886413, 1.057713, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2387, 46384, 1, 1, 1, -10431, -2611.646, 7.176208, 0.279201, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2388, 46384, 1, 1, 1, -10411.84, -2619.025, 5.886413, 3.545377, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2389, 46384, 1, 1, 1, -10334.54, -2605.893, 5.353177, 2.301718, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2390, 46384, 1, 1, 1, -10429.6, -2613.027, 7.011413, 0.6395152, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2391, 46384, 1, 1, 1, -10411.5, -2619.825, 5.886413, 1.440631, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2392, 46384, 1, 1, 1, -10398.61, -2622.223, 5.519114, 0.88221, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2393, 46384, 1, 1, 1, -10410.53, -2620.115, 5.785095, 4.437773, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2394, 46384, 1, 1, 1, -10414.89, -2619.268, 5.886413, 5.299303, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2395, 46384, 1, 1, 1, -10301.53, -2575.029, 17.58715, 2.731127, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2396, 46384, 1, 1, 1, -10414.93, -2619.921, 5.886413, 5.16525, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2397, 46384, 1, 1, 1, -10419.14, -2619.038, 6.024353, 3.822302, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2398, 46384, 1, 1, 1, -10402.4, -2623.241, 5.535095, 2.615709, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2399, 46384, 1, 1, 1, -10300.57, -2574.944, 17.52758, 5.831057, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2400, 46384, 1, 1, 1, -10418.45, -2619.718, 6.011413, 4.156631, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2401, 46384, 1, 1, 1, -10413.63, -2621.315, 5.761413, 5.834455, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2402, 46384, 1, 1, 1, -10414.16, -2621.244, 5.761413, 5.594626, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2403, 46384, 1, 1, 1, -10299.36, -2573.444, 17.66996, 3.940237, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2404, 46384, 1, 1, 1, -10411.66, -2622.115, 5.636413, 1.263399, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2405, 46384, 1, 1, 1, -10293.8, -2561.333, 18.45901, 3.914062, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2406, 46384, 1, 1, 1, -10418.56, -2620.298, 6.011413, 3.765606, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2407, 46384, 1, 1, 1, -10297.12, -2570.801, 17.86209, 3.797642, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2408, 46384, 1, 1, 1, -10419.73, -2620.823, 6.131212, 3.67736, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2409, 46384, 1, 1, 1, -10336.19, -2612.809, 5.472317, 1.39965, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2410, 46384, 1, 1, 1, -10336.57, -2615.016, 5.622708, 1.395164, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2411, 46384, 1, 1, 1, -10289.21, -2571.774, 17.19461, 3.900569, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2412, 46384, 1, 1, 1, -10290.89, -2559.551, 18.31326, 0.3767822, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2413, 46384, 1, 1, 1, -10287.51, -2554.85, 18.31326, 6.239173, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2414, 46384, 1, 1, 1, -10286.43, -2563.058, 18.18386, 5.298347, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2415, 46384, 1, 1, 1, -10290.04, -2554.705, 18.31326, 3.868203, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2416, 46384, 1, 1, 1, -10286.77, -2562.128, 18.18826, 1.620612, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2417, 46384, 1, 1, 1, -10287.48, -2571.818, 16.88358, 5.374737, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2418, 46384, 1, 1, 1, -10240.68, -2581.878, 16.68775, 2.873377, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2419, 46384, 1, 1, 1, -10238.82, -2580.004, 16.86811, 1.937682, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2420, 46384, 1, 1, 1, -10328.67, -2614.002, 5.532526, 1.452796, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2421, 46384, 1, 1, 1, -10328.47, -2614.351, 5.574274, 1.309294, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2422, 46384, 1, 1, 1, -10241.01, -2596.903, 16.66724, 2.188084, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2423, 46384, 1, 1, 1, -10240.78, -2596.659, 16.69005, 1.683577, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2424, 46384, 1, 1, 1, -10314.53, -2634.769, 6.941556, 4.360876, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2425, 46384, 1, 1, 1, -10314.99, -2635.29, 6.88638, 4.17094, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2426, 46384, 1, 1, 1, -10230.07, -2596.719, 16.45441, 1.186976, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2427, 46384, 1, 1, 1, -10230.5, -2597.642, 16.45441, 1.209996, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2428, 46384, 1, 1, 1, -10259.53, -2627.078, 5.151202, 0.8004215, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2429, 46384, 1, 1, 1, -10262.46, -2629.108, 5.12009, 3.025321, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2430, 46384, 1, 1, 1, -10296.65, -2641.581, 10.06638, 6.101031, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2431, 46384, 1, 1, 1, -10310.94, -2640.259, 7.400441, 4.421472, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2432, 46384, 1, 1, 1, -10311.38, -2640.182, 7.391751, 4.27451, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2433, 46384, 1, 1, 1, -10297.17, -2641.887, 9.863257, 5.828866, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2434, 46384, 1, 1, 1, -10233.25, -2609.618, 16.69613, 1.110997, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2435, 46384, 1, 1, 1, -10308.69, -2641.269, 7.912259, 4.077086, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2436, 46568, 1, 1, 1, -10283.41, -2641.082, 10.23264, 4.396811, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2437, 46384, 1, 1, 1, -10221.71, -2588.342, 16.45441, 1.869767, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2438, 46384, 1, 1, 1, -10232.89, -2610.409, 16.6606, 6.172604, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2439, 46384, 1, 1, 1, -10309.48, -2641.548, 7.721829, 3.914096, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2440, 46384, 1, 1, 1, -10221.26, -2588.135, 16.45441, 1.147539, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2441, 46384, 1, 1, 1, -10221.31, -2588.709, 16.45441, 1.436475, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2442, 46384, 1, 1, 1, -10293.91, -2643.093, 10.27439, 5.903774, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2443, 46384, 1, 1, 1, -10220.95, -2588.516, 16.45441, 0.8713834, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2444, 46384, 1, 1, 1, -10293.7, -2643.498, 10.34885, 5.681161, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2445, 46384, 1, 1, 1, -10291.46, -2645.313, 10.58518, 6.021014, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2446, 46384, 1, 1, 1, -10259.79, -2635.78, 5.245117, 5.192024, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2447, 46384, 1, 1, 1, -10292.17, -2646.43, 10.7363, 5.560994, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2448, 46384, 1, 1, 1, -10259.88, -2637.235, 5.39917, 4.853513, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2449, 46384, 1, 1, 1, -10290.66, -2647.308, 10.68088, 5.642691, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2450, 46384, 1, 1, 1, -10223.15, -2604.053, 16.37012, 0.2172209, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2451, 46384, 1, 1, 1, -10295.99, -2647.674, 10.24778, 0.01930106, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2452, 46384, 1, 1, 1, -10294.87, -2647.88, 10.49754, 6.225003, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2453, 46384, 1, 1, 1, -10223.03, -2604.851, 16.37012, 6.067206, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2454, 46384, 1, 1, 1, -10222.02, -2603.095, 16.37012, 0.8033292, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2455, 46384, 1, 1, 1, -10289.09, -2648.154, 10.74778, 5.731582, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2456, 46384, 1, 1, 1, -10277.89, -2647.103, 10.53196, 1.18511, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2457, 46384, 1, 1, 1, -10257.79, -2639.956, 5.474365, 3.217039, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2458, 46384, 1, 1, 1, -10220.54, -2605.439, 16.37012, 5.975055, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2459, 46384, 1, 1, 1, -10254.8, -2639.73, 5.245117, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2460, 46384, 1, 1, 1, -10244.11, -2634.004, 7.835102, 0.9378376, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2461, 46384, 1, 1, 1, -10221.2, -2611.445, 16.37012, 4.885777, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2462, 46384, 1, 1, 1, -10245.8, -2636.31, 6.871614, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2463, 46384, 1, 1, 1, -10220.76, -2611.955, 16.37012, 3.684089, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2464, 46384, 1, 1, 1, -10277.85, -2651.663, 9.973853, 5.276854, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2465, 46384, 1, 1, 1, -10218.92, -2610.745, 16.37012, 0.0478119, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2466, 46384, 1, 1, 1, -10280.98, -2653.179, 9.791236, 1.011068, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2467, 46384, 1, 1, 1, -10218.01, -2610.232, 16.37012, 3.621985, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2468, 46384, 1, 1, 1, -10284.84, -2655.533, 8.949683, 3.390673, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2469, 46384, 1, 1, 1, -10220.27, -2619.112, 16.37012, 3.739563, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2470, 46384, 1, 1, 1, -10219.22, -2618.07, 16.37012, 3.564105, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2471, 46384, 1, 1, 1, -10213, -2608.527, 16.37012, 5.587072, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2472, 46384, 1, 1, 1, -10212.9, -2608.327, 16.37012, 5.662643, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2473, 46384, 1, 1, 1, -10209.58, -2522.928, 16.45441, 2.715805, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2474, 46384, 1, 1, 1, -10205.69, -2596, 16.45441, 1.768192, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2475, 46384, 1, 1, 1, -10205.6, -2596.46, 16.41273, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2476, 46384, 1, 1, 1, -10245.11, -2644.913, 6.327911, 4.46785, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2477, 46384, 1, 1, 1, -10209.25, -2520.367, 16.45441, 2.477735, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2478, 46384, 1, 1, 1, -10244.64, -2645.019, 6.549147, 4.631977, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2479, 46384, 1, 1, 1, -10206.92, -2524.677, 16.45441, 5.502593, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2480, 46384, 1, 1, 1, -10239.58, -2727.084, 5.011385, 2.601063, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2481, 46384, 1, 1, 1, -10226.97, -2726.689, 5.120117, 5.950631, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2482, 46384, 1, 1, 1, -10239.77, -2727.596, 5.011385, 2.781084, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2483, 46384, 1, 1, 1, -10230.38, -2724.938, 5.120117, 2.392432, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2484, 46384, 1, 1, 1, -10161.55, -2671.293, 5.028946, 2.541372, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2485, 46384, 1, 1, 1, -10162.69, -2670.917, 5.028946, 2.64763, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2486, 46384, 1, 1, 1, -10167.96, -2689.237, 5.022966, 3.745242, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2487, 46384, 1, 1, 1, -10167.19, -2685.938, 5.01993, 2.381708, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2488, 46384, 1, 1, 1, -10347.07, -2658.138, 5.122708, 2.166038, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2489, 46384, 1, 1, 1, -10346.27, -2658.146, 5.122708, 1.911778, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2490, 46384, 1, 1, 1, -10341.58, -2659.79, 5.122708, 1.907661, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2491, 46384, 1, 1, 1, -10337.83, -2658.183, 5.122708, 2.468839, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2492, 46384, 1, 1, 1, -10336.47, -2659.329, 5.122708, 2.518551, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2493, 46384, 1, 1, 1, -10340.61, -2662.202, 5.122708, 2.715487, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2494, 46384, 1, 1, 1, -10342.34, -2657.644, 5.122708, 1.910808, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2495, 46384, 1, 1, 1, -10341.11, -2662.015, 5.122708, 2.741267, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2496, 46568, 1, 1, 1, -10183.46, -2609.627, 16.37012, 0.07827285, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2497, 46384, 1, 1, 1, -10208.74, -2610.072, 16.37012, 2.2029, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2498, 46384, 1, 1, 1, -10202.46, -2618.566, 16.37012, 6.076146, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2499, 46384, 1, 1, 1, -10207.6, -2611.63, 16.41273, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2500, 46384, 1, 1, 1, -10202.48, -2618.291, 16.37012, 6.16677, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2501, 46384, 1, 1, 1, -10201.86, -2617.68, 16.37012, 4.174726, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2502, 46384, 1, 1, 1, -10236.83, -2648.81, 7.912352, 5.541131, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2503, 46384, 1, 1, 1, -10202.17, -2619.757, 16.37012, 4.44796, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2504, 46384, 1, 1, 1, -10240, -2647.873, 7.337646, 3.952791, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2505, 46384, 1, 1, 1, -10351.75, -2652.419, 5.122708, 2.169972, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2506, 46384, 1, 1, 1, -10355.09, -2651.17, 5.122708, 0.8578526, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2507, 46384, 1, 1, 1, -10355.99, -2651.826, 5.122708, 0.9831882, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2508, 46384, 1, 1, 1, -10353.24, -2653.655, 5.122708, 0.6550316, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2509, 46384, 1, 1, 1, -10353.35, -2654.224, 5.122708, 3.805421, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2510, 46384, 1, 1, 1, -10352.71, -2654.669, 5.122708, 0.2708858, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2511, 46384, 1, 1, 1, -10358.91, -2651.885, 5.122708, 0.6166633, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2512, 46384, 1, 1, 1, -10359.35, -2651.761, 5.122708, 0.7575786, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2513, 46384, 1, 1, 1, -10392.51, -2641.778, 4.804257, 1.747531, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2514, 46384, 1, 1, 1, -10394.06, -2643.557, 4.804257, 2.880486, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2515, 46384, 1, 1, 1, -10402.93, -2646.238, 4.673882, 2.040592, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2516, 46384, 1, 1, 1, -10405.15, -2643.743, 4.673882, 3.160707, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2517, 46384, 1, 1, 1, -10408.16, -2638.547, 4.673882, 4.545623, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2518, 46384, 1, 1, 1, -10404.92, -2646.961, 4.673882, 2.829613, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2519, 46384, 1, 1, 1, -10406.94, -2643.643, 4.673882, 3.11523, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2520, 46384, 1, 1, 1, -10408.96, -2639.711, 4.673882, 4.342594, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2521, 46384, 1, 1, 1, -10410.16, -2640.157, 4.673882, 0.7940147, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2522, 46384, 1, 1, 1, -10410.58, -2642.75, 4.673882, 5.814195, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2523, 46384, 1, 1, 1, -10416.9, -2638.26, 4.692043, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2524, 46384, 1, 1, 1, -10412.85, -2648.566, 4.834527, 0.7259938, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2525, 46384, 1, 1, 1, -10413.16, -2648.039, 4.733941, 1.218936, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2526, 46384, 1, 1, 1, -10417.54, -2638.907, 4.673882, 3.936514, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2527, 46384, 1, 1, 1, -10379.84, -2687.932, 5.058864, 0.07965104, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2528, 46384, 1, 1, 1, -10419.9, -2636.62, 4.633914, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2529, 46384, 1, 1, 1, -10419.11, -2640.298, 4.673882, 2.770779, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2530, 46384, 1, 1, 1, -10384.5, -2687.299, 5.058864, 2.853632, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2531, 46384, 1, 1, 1, -10420.64, -2641.862, 4.673882, 3.520962, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2532, 46384, 1, 1, 1, -10422.34, -2638.225, 4.673882, 3.724159, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2533, 46384, 1, 1, 1, -10420.99, -2642.754, 4.673882, 2.652832, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2534, 46384, 1, 1, 1, -10421.56, -2643.809, 4.673882, 3.085102, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2535, 46384, 1, 1, 1, -10399.2, -2680.95, 5.081044, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2536, 46384, 1, 1, 1, -10399.2, -2680.95, 5.081044, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2537, 46384, 1, 1, 1, -10390.4, -2692.57, 5.058864, 0.2993016, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2538, 46384, 1, 1, 1, -10386.23, -2694.803, 5.058864, 0.8983085, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2539, 46384, 1, 1, 1, -10402.07, -2687.029, 4.934314, 1.4726, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2540, 46384, 1, 1, 1, -10391.52, -2694.205, 5.058864, 2.939955, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2541, 46384, 1, 1, 1, -10388.54, -2696.243, 5.058864, 4.572657, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2542, 46384, 1, 1, 1, -10402.4, -2688.475, 3.839207, 4.44884, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2543, 46384, 1, 1, 1, -10405.95, -2685.97, 4.481206, 5.595149, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2544, 46384, 1, 1, 1, -10426.54, -2641.461, 4.673882, 0.229813, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2545, 46384, 1, 1, 1, -10405.05, -2690.366, 2.377851, 4.980333, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2546, 46384, 1, 1, 1, -10426.73, -2637.117, 4.798882, 5.168149, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2547, 46384, 1, 1, 1, -10427, -2637.774, 4.751187, 4.98633, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2548, 46384, 1, 1, 1, -10428.22, -2642.31, 4.673882, 6.132802, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2549, 46384, 1, 1, 1, -10396.87, -2700, 5.011385, 2.108672, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2550, 46384, 1, 1, 1, -10387.27, -2704.204, 5.011385, 1.598409, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2551, 46384, 1, 1, 1, -10396.81, -2700.13, 5.046664, 1.540622, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2552, 46384, 1, 1, 1, -10431.49, -2629.907, 5.360046, 0.801025, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2553, 46384, 1, 1, 1, -10431.71, -2630.387, 5.302429, 0.6621325, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2554, 46384, 1, 1, 1, -10380.87, -2709.774, 5.011385, 1.48241, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2555, 46384, 1, 1, 1, -10388.9, -2708.48, 5.011385, 2.193218, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2556, 46384, 1, 1, 1, -10434.5, -2636.87, 4.387683, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2557, 46384, 1, 1, 1, -10435.21, -2637.536, 4.067972, 3.897353, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2558, 46384, 1, 1, 1, -10381, -2711.792, 5.011385, 3.608042, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2559, 46384, 1, 1, 1, -10404.5, -2702.998, 0, 4.982734, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2560, 46384, 1, 1, 1, -10405.19, -2703.59, -0.5215632, 4.591267, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2561, 46384, 1, 1, 1, -10399.8, -2724.49, 5.081034, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2562, 46384, 1, 1, 1, -10399.8, -2724.49, 5.081034, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2563, 46384, 1, 1, 1, -10384.2, -2729.276, 5.011385, 0.6610825, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2564, 46384, 1, 1, 1, -10384.08, -2731.545, 5.011385, 6.09929, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2565, 46384, 1, 1, 1, -10479, -2592.659, 7.858898, 0.4461821, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2566, 46384, 1, 1, 1, -10470.8, -2584.59, 7.463314, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2567, 46384, 1, 1, 1, -10463.54, -2601.041, 6.944919, 6.265021, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2568, 46384, 1, 1, 1, -10479.81, -2593.624, 7.562039, 0.153296, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2569, 46384, 1, 1, 1, -10470.8, -2584.59, 7.463314, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2570, 46384, 1, 1, 1, -10466.04, -2601.781, 7.494479, 4.416351, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2571, 46384, 1, 1, 1, -10420.1, -2518.6, 34.59113, 0.805785, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2572, 46384, 1, 1, 1, -10410.2, -2524.27, 31.62623, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2573, 46384, 1, 1, 1, -10404.2, -2525.69, 32.58883, 2.440684, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2574, 46384, 1, 1, 1, -10410.2, -2524.27, 31.62623, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2575, 46384, 1, 1, 1, -10401.9, -2514.34, 31.78193, 3.023221, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2576, 46384, 1, 1, 1, -10392.9, -2514.8, 32.09173, 0.5429642, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2577, 46384, 1, 1, 1, -10394.4, -2531.36, 30.62023, 1.012854, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2578, 46384, 1, 1, 1, -10404.2, -2525.69, 32.58883, 2.440684, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2579, 46384, 1, 1, 1, -10420.1, -2518.6, 34.59113, 0.7668373, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2580, 46384, 1, 1, 1, -10408.7, -2507.7, 32.69053, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2581, 46384, 1, 1, 1, -10408.7, -2507.7, 32.69053, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2582, 46384, 1, 1, 1, -10401.9, -2514.34, 31.78193, 3.381336, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2583, 46384, 1, 1, 1, -10394.4, -2531.36, 30.62023, 1.206338, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2584, 46384, 1, 1, 1, -10393.9, -2525.05, 31.10923, 0.1137221, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2585, 46384, 1, 1, 1, -10387.92, -2520.771, 31.74389, 2.789485, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2586, 46384, 1, 1, 1, -10371.34, -2521.376, 31.85473, 3.143817, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2587, 46384, 1, 1, 1, -10378.92, -2531.144, 32.18237, 2.255045, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2588, 46384, 1, 1, 1, -10378.31, -2531.472, 32.14281, 1.877364, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2589, 46384, 1, 1, 1, -10376.31, -2513.525, 32.05116, 4.467964, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2590, 46384, 1, 1, 1, -10370.02, -2521.281, 31.69677, 3.087364, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2591, 46384, 1, 1, 1, -10385.39, -2509.428, 32.10693, 5.242324, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2592, 46384, 1, 1, 1, -10383.21, -2514.251, 32.23193, 0.01831478, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2593, 46384, 1, 1, 1, -10378.58, -2510.568, 32.09911, 3.107268, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2594, 46384, 1, 1, 1, -10385.26, -2520.451, 31.84032, 0.866417, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2595, 46384, 1, 1, 1, -10390.75, -2506.635, 32.57543, 4.922742, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2596, 46384, 1, 1, 1, -10394.36, -2512.898, 32.50683, 5.41063, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2597, 46384, 1, 1, 1, -10385.63, -2508.675, 32.10693, 5.36362, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2598, 46384, 1, 1, 1, -10385.16, -2514.282, 32.10693, 3.154871, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2599, 46384, 1, 1, 1, -10382.87, -2516.046, 32.23193, 2.523761, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2600, 46384, 1, 1, 1, -10390.09, -2504.426, 32.76196, 5.703719, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2601, 46384, 1, 1, 1, -10402.3, -2500.43, 32.34723, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2602, 46384, 1, 1, 1, -10403.51, -2505.343, 34.94199, 3.660965, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2603, 46384, 1, 1, 1, -10380.19, -2518.087, 32.23193, 5.345434, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2604, 46384, 1, 1, 1, -10393.9, -2525.05, 31.10923, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2605, 46384, 1, 1, 1, -10390.05, -2516.171, 31.85692, 5.83481, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2606, 46384, 1, 1, 1, -10395.46, -2511.435, 32.83276, 5.500598, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2607, 46568, 1, 1, 1, -10385.34, -2525.546, 31.67895, 1.516241, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2608, 46384, 1, 1, 1, -10410.06, -2498.737, 44.08614, 2.634624, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2609, 46384, 1, 1, 1, -10403.41, -2517.032, 33.29355, 2.520294, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2610, 46384, 1, 1, 1, -10402.41, -2518.034, 33.05454, 2.657121, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2611, 46384, 1, 1, 1, -10402.3, -2500.43, 32.34723, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2612, 46384, 1, 1, 1, -10416.66, -2510.622, 36.1539, 1.53776, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2613, 46384, 1, 1, 1, -10403.17, -2505.868, 34.79721, 3.905218, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2614, 46568, 1, 1, 1, -10437.15, -2469.153, 41.28466, 1.445472, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2615, 46384, 1, 1, 1, -10419.48, -2463.866, 41.98792, 5.933621, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2616, 46384, 1, 1, 1, -10421.01, -2462.401, 42.297, 0.6651478, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2617, 46384, 1, 1, 1, -10437.05, -2463.275, 41.9906, 2.778002, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2618, 46384, 1, 1, 1, -10436.63, -2462.428, 42.13806, 2.459844, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2619, 46384, 1, 1, 1, -10445.21, -2462.76, 40.94324, 5.463103, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2620, 46384, 1, 1, 1, -10431.48, -2455.329, 42.36218, 5.070251, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2621, 46384, 1, 1, 1, -10444.32, -2460.351, 41.64099, 0.2793027, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2622, 46384, 1, 1, 1, -10437.6, -2455.92, 39.66883, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2623, 46384, 1, 1, 1, -10437.6, -2455.92, 39.66883, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2624, 46384, 1, 1, 1, -10431.97, -2453.249, 42.56433, 5.392708, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2625, 46384, 1, 1, 1, -10450.1, -2457.22, 37.06963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2626, 46384, 1, 1, 1, -10450.1, -2457.22, 37.06963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2627, 46384, 1, 1, 1, -10444.2, -2454.42, 42.81453, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2628, 46384, 1, 1, 1, -10444.92, -2453.39, 42.9198, 2.176735, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2629, 46384, 1, 1, 1, -10424.87, -2445.486, 44.89734, 1.510829, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2630, 46384, 1, 1, 1, -10424.07, -2444.97, 45.14636, 1.246574, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2631, 46384, 1, 1, 1, -10455.74, -2454.531, 41.51599, 4.463981, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2632, 46384, 1, 1, 1, -10429.29, -2443.504, 44.49841, 0.1228186, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2633, 46384, 1, 1, 1, -10445.73, -2448.222, 43.96472, 1.263006, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2634, 46384, 1, 1, 1, -10455.67, -2453.21, 41.62488, 3.982864, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2635, 46384, 1, 1, 1, -10445.03, -2447.484, 44.31042, 0.9696631, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2636, 46384, 1, 1, 1, -10429.9, -2442.513, 44.80344, 0.4897341, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2637, 46384, 1, 1, 1, -10448.3, -2445.49, 39.65223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2638, 46384, 1, 1, 1, -10448.3, -2445.49, 39.65223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2639, 46384, 1, 1, 1, -10442.1, -2441.95, 46.12003, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2640, 46384, 1, 1, 1, -10440.9, -2440.63, 42.32703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2641, 46384, 1, 1, 1, -10440.9, -2440.63, 42.32703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2642, 46384, 1, 1, 1, -10453.37, -2444.792, 42.98352, 1.067234, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2643, 46384, 1, 1, 1, -10460.1, -2447.32, 39.02213, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2644, 46384, 1, 1, 1, -10460.1, -2447.32, 39.02213, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2645, 46384, 1, 1, 1, -10441.34, -2438.098, 47.04187, 5.33871, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2646, 46384, 1, 1, 1, -10443.91, -2438.868, 46.37341, 2.101301, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2647, 46384, 1, 1, 1, -10444.03, -2438.892, 46.34045, 4.142813, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2648, 46384, 1, 1, 1, -10455.17, -2442.924, 43.30378, 2.108027, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2649, 46384, 1, 1, 1, -10448.4, -2436.8, 41.38013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2650, 46384, 1, 1, 1, -10448.4, -2436.8, 41.38013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2651, 46384, 1, 1, 1, -10421.68, -2429.252, 47.18679, 2.281541, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2652, 46384, 1, 1, 1, -10421.21, -2429.126, 47.16032, 2.117679, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2653, 46384, 1, 1, 1, -10461.8, -2441.67, 40.33393, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2654, 46384, 1, 1, 1, -10461.8, -2441.67, 40.33393, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2655, 46384, 1, 1, 1, -10471.1, -2445.69, 47.73513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2656, 46384, 1, 1, 1, -10471.1, -2445.69, 47.73513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2657, 46384, 1, 1, 1, -10457.9, -2434.85, 40.34023, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2658, 46384, 1, 1, 1, -10457.9, -2434.85, 40.34023, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2659, 46384, 1, 1, 1, -10467.91, -2437.265, 51.9411, 3.910519, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2660, 46384, 1, 1, 1, -10468.53, -2437.766, 52.77069, 3.872218, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2661, 46384, 1, 1, 1, -10309.9, -2554.65, 18.60313, 5.52505, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2662, 46384, 1, 1, 1, -10286.7, -2564.72, 18.09953, 1.271916, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2663, 46384, 1, 1, 1, -10294.1, -2561.75, 18.42483, 1.088248, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2664, 46384, 1, 1, 1, -10289.9, -2568.95, 17.75673, 5.974966, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2665, 46384, 1, 1, 1, -10301.6, -2562.81, 18.54173, 2.657204, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2666, 46384, 1, 1, 1, -10289.9, -2568.95, 17.75673, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2667, 46384, 1, 1, 1, -10305.7, -2561.85, 17.84523, 1.856163, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2668, 46384, 1, 1, 1, -10306.2, -2548.94, 18.59053, 1.803872, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2669, 46384, 1, 1, 1, -10314.6, -2563.3, 18.08053, 0.4931358, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2670, 46384, 1, 1, 1, -10314.6, -2563.3, 18.08053, 0.6477894, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2671, 46568, 1, 1, 1, -10312.16, -2453.639, 18.83166, 3.664884, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2672, 46384, 1, 1, 1, -10429.12, -2411.92, 49.69304, 1.178202, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2673, 46384, 1, 1, 1, -10443.06, -2416.686, 49.46009, 2.728869, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2674, 46384, 1, 1, 1, -10428.82, -2412.247, 49.80778, 0.5435543, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2675, 46384, 1, 1, 1, -10454.51, -2416.789, 46.84388, 0.3220994, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2676, 46384, 1, 1, 1, -10441.91, -2416.116, 49.36976, 2.285996, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2677, 46384, 1, 1, 1, -10456.12, -2415.757, 46.60316, 1.402127, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2678, 46384, 1, 1, 1, -10480.3, -2423.02, 60.30726, 5.300015, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2679, 46384, 1, 1, 1, -10473.39, -2411.572, 55.32113, 1.883395, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2680, 46384, 1, 1, 1, -10423.69, -2390.507, 49.99031, 4.130612, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2681, 46384, 1, 1, 1, -10423.39, -2388.844, 49.50154, 3.31287, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2682, 46384, 1, 1, 1, -10450.36, -2386.775, 52.49177, 4.693836, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2683, 46384, 1, 1, 1, -10405.37, -2393.172, 37.68757, 4.516686, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2684, 46384, 1, 1, 1, -10404.58, -2393.067, 37.70027, 5.416074, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2685, 46384, 1, 1, 1, -10451.61, -2381.003, 52.62615, 2.02819, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2686, 46384, 1, 1, 1, -10481.05, -2350.504, 63.95508, 2.458426, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2687, 46384, 1, 1, 1, -10479.51, -2349.957, 63.34131, 1.577801, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2688, 46384, 1, 1, 1, -10548.6, -2464.28, 85.49174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2689, 46384, 1, 1, 1, -10548.6, -2464.28, 85.49174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2690, 46384, 1, 1, 1, -10492.12, -2345.409, 66.93945, 5.058181, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2691, 46384, 1, 1, 1, -10470.6, -2344.076, 62.05565, 3.620979, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2692, 46384, 1, 1, 1, -10469.63, -2343.93, 61.38477, 3.809537, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2693, 46384, 1, 1, 1, -10490.63, -2344.384, 66.22656, 5.739717, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2694, 46384, 1, 1, 1, -10495.3, -2344.68, 64.84174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2695, 46384, 1, 1, 1, -10495.3, -2344.68, 64.84174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2696, 46384, 1, 1, 1, -10558.1, -2460.59, 87.75674, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2697, 46384, 1, 1, 1, -10558.1, -2460.59, 87.75674, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2698, 46568, 1, 1, 1, -10550.89, -2474.532, 90.5464, 4.88525, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2699, 46384, 1, 1, 1, -10547.09, -2482.129, 89.22194, 0.9208933, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2700, 46384, 1, 1, 1, -10546.02, -2484.299, 89.00905, 5.899181, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2701, 46384, 1, 1, 1, -10541.85, -2489.662, 88.49562, 2.597202, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2702, 46384, 1, 1, 1, -10542.86, -2489.054, 88.68715, 2.597488, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2703, 46384, 1, 1, 1, -10484.1, -2335.78, 62.06223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2704, 46384, 1, 1, 1, -10484.1, -2335.78, 62.06223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2705, 46384, 1, 1, 1, -10554.73, -2480.861, 90.95851, 1.024825, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2706, 46384, 1, 1, 1, -10554.11, -2485.085, 90.57448, 5.639257, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2707, 46384, 1, 1, 1, -10563.9, -2476.36, 88.54954, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2708, 46384, 1, 1, 1, -10563.9, -2476.36, 88.54954, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+2709, 46384, 1, 1, 1, -10461.4, -2330.72, 56.36363, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2710, 46384, 1, 1, 1, -10461.4, -2330.72, 56.36363, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2711, 46384, 1, 1, 1, -10456.09, -2321.831, 60.00462, 4.410827, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2712, 46384, 1, 1, 1, -10479.82, -2322.188, 63.56049, 0.5950447, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2713, 46384, 1, 1, 1, -10464.1, -2287.97, 51.96013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2714, 46384, 1, 1, 1, -10447.63, -2292.211, 53.91326, 1.342388, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2715, 46384, 1, 1, 1, -10498, -2316.7, 67.87354, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2716, 46384, 1, 1, 1, -10508.8, -2335.86, 67.22533, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2717, 46384, 1, 1, 1, -10510.98, -2326.236, 72.25757, 0.1905044, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2718, 46384, 1, 1, 1, -10478.75, -2288.941, 63.97087, 2.744397, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2719, 46384, 1, 1, 1, -10498, -2316.7, 67.87354, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2720, 46384, 1, 1, 1, -10447.25, -2290.537, 53.84417, 1.880728, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2721, 46384, 1, 1, 1, -10484.26, -2321.921, 65.28977, 2.401822, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2722, 46384, 1, 1, 1, -10464.1, -2287.97, 51.96013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2723, 46384, 1, 1, 1, -10472.75, -2311.802, 64.37226, 3.096536, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2724, 46384, 1, 1, 1, -10478.31, -2289.423, 63.81266, 2.864301, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2725, 46384, 1, 1, 1, -10447.84, -2292.932, 54.07439, 1.361068, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2726, 46384, 1, 1, 1, -10429.14, -2296.416, 50.85374, 0.8928739, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
-- (@CGUID+2727, 46384, 0, 1, 1, -1, 2, -1.6, 4.712389, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) - !!! on transport (NYI) !!! (possible waypoints or random movement)
(@CGUID+2727, 46384, 1, 1, 1, -10482.1, -2317.13, 61.20323, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2728, 46384, 1, 1, 1, -10470.74, -2311.131, 64.34956, 1.237177, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2729, 46384, 1, 1, 1, -10429.25, -2296.384, 50.86253, 0.9268068, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2730, 46384, 1, 1, 1, -10508.8, -2335.86, 67.22533, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2731, 46384, 1, 1, 1, -10482.1, -2317.13, 61.20323, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2732, 46384, 1, 1, 1, -10468.37, -2323.324, 64.85078, 0.7156237, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2733, 46384, 1, 1, 1, -10465.82, -2324.095, 61.2739, 0.3445002, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2734, 46384, 1, 1, 1, -10447.09, -2290.804, 53.75579, 1.800284, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2735, 46384, 1, 1, 1, -10512.09, -2325.736, 72.66846, 0.5879278, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2736, 46384, 1, 1, 1, -10529.4, -2319.65, 75.88493, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2737, 46384, 1, 1, 1, -10529.4, -2319.65, 75.88493, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2738, 46384, 1, 1, 1, -10426.06, -2444.99, 44.84851, 1.940433, 120, 0, 0), -- Crazed Gnome (Area: 0) (possible waypoints or random movement)
(@CGUID+2739, 46384, 1, 1, 1, -10443.36, -2417.916, 49.31239, 3.164044, 120, 0, 0), -- Crazed Gnome (Area: 0) (possible waypoints or random movement)
(@CGUID+2740, 46384, 1, 1, 1, -10429.56, -2444.332, 44.38056, 6.137441, 120, 0, 0), -- Crazed Gnome (Area: 0) (possible waypoints or random movement)
(@CGUID+2741, 46384, 1, 1, 1, -10421.62, -2429.1, 47.21281, 2.231497, 120, 0, 0), -- Crazed Gnome (Area: 0) (possible waypoints or random movement)
(@CGUID+2742, 46384, 1, 1, 1, -10429.28, -2443.17, 44.57849, 0.2226909, 120, 0, 0), -- Crazed Gnome (Area: 0) (possible waypoints or random movement)
(@CGUID+2743, 46384, 1, 1, 1, -10423.8, -2446.281, 44.94812, 0.8807983, 120, 0, 0), -- Crazed Gnome (Area: 0) (possible waypoints or random movement)
(@CGUID+2744, 46384, 1, 1, 1, -10405.2, -2392.34, 37.66523, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2745, 46384, 1, 1, 1, -10207.15, -2408.324, 28.56307, 1.212446, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2746, 46384, 1, 1, 1, -10209.5, -2405.1, 28.76733, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2747, 46384, 1, 1, 1, -10208.15, -2410.064, 28.30916, 1.636177, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2748, 46384, 1, 1, 1, -10206.9, -2406.563, 28.65349, 5.771155, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+2749, 46384, 1, 1, 1, -10173.61, -2380.64, 27.54462, 3.507228, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2750, 46384, 1, 1, 1, -10162.87, -2392.04, 27.91962, 0.4251631, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2751, 46384, 1, 1, 1, -10154.82, -2373.739, 27.54462, 3.951833, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2752, 46384, 1, 1, 1, -10156.17, -2389.17, 27.66962, 4.326336, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2753, 46384, 1, 1, 1, -10147.79, -2394.994, 27.54462, 5.222525, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2754, 46384, 1, 1, 1, -10146.42, -2394.657, 27.54462, 5.70979, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2755, 46384, 1, 1, 1, -10188.39, -2373.458, 27.54462, 2.043757, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2756, 46384, 1, 1, 1, -10162.47, -2380.852, 27.54462, 1.155158, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2757, 46384, 1, 1, 1, -10173.53, -2380.679, 27.54462, 3.584824, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2758, 46384, 1, 1, 1, -10174.5, -2380.015, 27.54462, 3.015584, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2759, 46384, 1, 1, 1, -10161.49, -2380.117, 27.54462, 0.9479446, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2760, 46384, 1, 1, 1, -10182.3, -2385.607, 27.54462, 2.485868, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2761, 46384, 1, 1, 1, -10171.96, -2386.698, 27.54462, 3.122643, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2762, 46384, 1, 1, 1, -10172, -2385.879, 27.54462, 2.83948, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2763, 46384, 1, 1, 1, -10180.24, -2376.265, 27.54462, 3.788773, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2764, 46384, 1, 1, 1, -10172.36, -2380.45, 27.54462, 3.170078, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2765, 46384, 1, 1, 1, -10179.58, -2378.242, 27.54462, 4.546586, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2766, 46384, 1, 1, 1, -10153.3, -2393.84, 27.66143, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2767, 46384, 1, 1, 1, -10171.52, -2362.988, 27.54462, 2.11668, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2768, 46384, 1, 1, 1, -10171.3, -2363.079, 27.54462, 2.316788, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2769, 46384, 1, 1, 1, -10163.22, -2391.68, 27.91962, 0.5848753, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2770, 46384, 1, 1, 1, -10188.53, -2375.28, 27.54462, 4.744298, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2771, 46384, 1, 1, 1, -10164.28, -2387.268, 27.66962, 5.192276, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2772, 46384, 1, 1, 1, -10164.75, -2386.087, 27.66962, 5.450016, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2773, 46384, 1, 1, 1, -10171.7, -2363.226, 27.54462, 2.440419, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2774, 46384, 1, 1, 1, -10172.31, -2363.941, 27.54462, 2.521784, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2775, 46384, 1, 1, 1, -10178.58, -2386.865, 27.54462, 6.066146, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2776, 46384, 1, 1, 1, -10153.86, -2393.564, 27.58491, 2.686982, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2777, 46384, 1, 1, 1, -10158.52, -2389.832, 27.79462, 3.79521, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2778, 46384, 1, 1, 1, -10155.88, -2374.167, 27.54462, 3.793832, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2779, 46384, 1, 1, 1, -10171.76, -2479.57, 16.45443, 3.138151, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2780, 46384, 1, 1, 1, -10168.48, -2479.364, 16.45443, 3.751609, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2781, 46384, 1, 1, 1, -10169.99, -2480.013, 16.45443, 3.490611, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2782, 46384, 1, 1, 1, -10170.55, -2480.967, 16.45443, 3.793971, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2783, 46384, 1, 1, 1, -10187.83, -2484.198, 16.45443, 1.683212, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2784, 46384, 1, 1, 1, -10186.08, -2484.55, 16.45443, 1.071527, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2785, 46568, 1, 1, 1, -10195.23, -2543.597, 16.45443, 5.165162, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2786, 46384, 1, 1, 1, -10154.06, -2487.83, 16.4256, 3.895486, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2787, 46384, 1, 1, 1, -10165.75, -2509.379, 16.35269, 3.534553, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2788, 46384, 1, 1, 1, -10161.76, -2495.464, 16.4256, 1.233883, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2789, 46384, 1, 1, 1, -10146.56, -2505.611, 16.85228, 0.5934806, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2790, 46384, 1, 1, 1, -10154.73, -2501.824, 16.47281, 4.004182, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2791, 46384, 1, 1, 1, -10147.69, -2503.926, 16.819, 1.391081, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2792, 46384, 1, 1, 1, -10169.24, -2502.025, 16.45443, 0.05601103, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2793, 46384, 1, 1, 1, -10168.77, -2501.163, 16.45443, 3.715274, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2794, 46384, 1, 1, 1, -10171.7, -2494.25, 16.41273, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2795, 46384, 1, 1, 1, -10175.27, -2506.568, 20.73999, 0.05347378, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2796, 46384, 1, 1, 1, -10163.39, -2497.492, 16.4256, 1.293043, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate)
(@CGUID+2797, 46384, 1, 1, 1, -10165.44, -2492.688, 20.94095, 2.836704, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2798, 46384, 1, 1, 1, -10161.14, -2495.75, 16.4256, 0.6112057, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2799, 46384, 1, 1, 1, -10155.14, -2502.671, 16.423, 4.170484, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2800, 46384, 1, 1, 1, -10154.37, -2488.681, 16.4256, 4.028675, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2801, 46384, 1, 1, 1, -10164, -2499.62, 16.41273, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2802, 46384, 1, 1, 1, -10155.04, -2506.738, 16.3566, 2.795714, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2803, 46384, 1, 1, 1, -10155.04, -2506.911, 16.398, 2.851443, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2804, 46384, 1, 1, 1, -10165.99, -2492.553, 20.94095, 2.706517, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2805, 46384, 1, 1, 1, -10172.49, -2492.494, 16.45443, 2.461939, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2806, 46384, 1, 1, 1, -10163.18, -2508.397, 16.35269, 5.534537, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2807, 46384, 1, 1, 1, -10168.39, -2502.973, 26.69591, 3.020627, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2808, 46384, 1, 1, 1, -10206.32, -2521.377, 16.45441, 5.435834, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2809, 46384, 1, 1, 1, -10176.4, -2517.286, 27.14686, 2.323805, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2810, 46384, 1, 1, 1, -10175.45, -2508.898, 20.73999, 5.905248, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2811, 46384, 1, 1, 1, -10286.93, -2563.198, 18.06326, 1.718455, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2812, 46384, 1, 1, 1, -10288.9, -2555.207, 18.31326, 0.5372601, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2813, 46384, 1, 1, 1, -10289.07, -2553.337, 18.31326, 1.144794, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2814, 46384, 1, 1, 1, -10292.18, -2560.194, 18.40188, 0.6814726, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2815, 46568, 1, 1, 1, -10295.19, -2553.223, 18.56326, 0.5405762, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2816, 46384, 1, 1, 1, -10295.7, -2569.951, 17.83915, 0.1441046, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2817, 46384, 1, 1, 1, -10298.08, -2570.728, 17.87064, 5.853423, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2818, 46384, 1, 1, 1, -10297.85, -2576.551, 17.88464, 5.696136, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2819, 46384, 1, 1, 1, -10298.13, -2576.915, 17.82596, 5.538671, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2820, 46384, 1, 1, 1, -10303.01, -2561.401, 18.5901, 2.355534, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2821, 46384, 1, 1, 1, -10304.56, -2557.762, 18.71311, 3.210959, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2822, 46384, 1, 1, 1, -10262.16, -2629.53, 5.391575, 3.663558, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2823, 46384, 1, 1, 1, -10305.21, -2556.424, 18.71311, 2.725988, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2824, 46384, 1, 1, 1, -10245.87, -2637.567, 6.901367, 4.653406, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2825, 46384, 1, 1, 1, -10261.94, -2630.48, 5.365696, 4.44978, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2826, 46384, 1, 1, 1, -10305.8, -2546.858, 19.07688, 1.378934, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2827, 46384, 1, 1, 1, -10246.58, -2638.619, 6.393799, 4.383982, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2828, 46384, 1, 1, 1, -10308.55, -2557.133, 18.94358, 5.209799, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2829, 46384, 1, 1, 1, -10308.57, -2561.235, 19.01537, 2.930749, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2830, 46384, 1, 1, 1, -10260.2, -2634.98, 6.676894, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2831, 46384, 1, 1, 1, -10258.81, -2637.636, 5.365479, 5.193689, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2832, 46384, 1, 1, 1, -10244.72, -2643.641, 6.458252, 4.510606, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2833, 46384, 1, 1, 1, -10244.28, -2643.904, 6.616455, 4.777616, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2834, 46384, 1, 1, 1, -10255.14, -2640.636, 5.245117, 4.35052, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2835, 46384, 1, 1, 1, -10237, -2646.773, 8.370117, 0.02343321, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2836, 46384, 1, 1, 1, -10257.64, -2640.185, 5.484619, 3.300024, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2837, 46384, 1, 1, 1, -10236.73, -2648.676, 7.950694, 5.597796, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2838, 46384, 1, 1, 1, -10316.1, -2567.82, 17.93863, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate)
(@CGUID+2839, 46384, 1, 1, 1, -10316.1, -2567.82, 17.93863, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate)
(@CGUID+2840, 46384, 1, 1, 1, -10317.5, -2555.71, 18.66513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate)
(@CGUID+2841, 46384, 1, 1, 1, -10317.5, -2555.71, 18.66513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate)
-(@CGUID+2842, 46568, 1, 1, 1, -10284.08, -2640.701, 10.14133, 4.129798, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2843, 46384, 1, 1, 1, -10281.39, -2648.027, 10.62278, 2.492891, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2844, 46384, 1, 1, 1, -10279.92, -2651.514, 10.16282, 4.208701, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2845, 46384, 1, 1, 1, -10282, -2652.028, 10.13547, 1.571167, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2846, 46384, 1, 1, 1, -10282, -2654.81, 9.241893, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2847, 46384, 1, 1, 1, -10288.99, -2647.943, 10.74778, 5.811113, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2848, 46384, 1, 1, 1, -10290.15, -2645.983, 10.57297, 0.4071809, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2849, 46384, 1, 1, 1, -10291.34, -2644.469, 10.50254, 0.02771914, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2850, 46384, 1, 1, 1, -10292.52, -2645.784, 10.58274, 5.676455, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2851, 46384, 1, 1, 1, -10293.5, -2644.197, 10.46506, 5.439697, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2852, 46384, 1, 1, 1, -10293.97, -2643.916, 10.36619, 5.326661, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2853, 46384, 1, 1, 1, -10296.22, -2642.665, 10.07127, 5.725625, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2854, 46384, 1, 1, 1, -10296.25, -2643.103, 10.12034, 5.591847, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2855, 46384, 1, 1, 1, -10294.88, -2648.026, 10.49724, 6.175102, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2856, 46384, 1, 1, 1, -10296.88, -2648.039, 10.24778, 5.936987, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2857, 46384, 1, 1, 1, -10148.05, -2654.304, 6.209041, 2.179037, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2858, 46384, 1, 1, 1, -10147.01, -2656.802, 5.517228, 3.338758, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2859, 46384, 1, 1, 1, -10153.71, -2671.258, 5.028946, 4.505173, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2860, 46384, 1, 1, 1, -10153.54, -2671.288, 5.028946, 4.565891, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2861, 46384, 1, 1, 1, -10308.35, -2639.774, 7.993802, 3.403683, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2862, 46384, 1, 1, 1, -10311.52, -2633.041, 7.317194, 0.3762917, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2863, 46384, 1, 1, 1, -10309.23, -2641.839, 7.699368, 4.044202, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2864, 46384, 1, 1, 1, -10310.52, -2638.007, 7.598294, 4.070081, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2865, 46384, 1, 1, 1, -10310.72, -2639.696, 7.548977, 4.441913, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2866, 46384, 1, 1, 1, -10314.81, -2635.935, 6.907864, 4.434593, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2867, 46384, 1, 1, 1, -10158.61, -2688.396, 5.028946, 3.923699, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2868, 46384, 1, 1, 1, -10156.86, -2687.07, 5.028946, 4.338563, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2869, 46384, 1, 1, 1, -10145.56, -2678.67, 5.028946, 5.327052, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2870, 46384, 1, 1, 1, -10142.54, -2678.021, 5.028946, 0.7937499, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2871, 46384, 1, 1, 1, -10137.46, -2672.442, 5.028946, 1.625834, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2872, 46384, 1, 1, 1, -10136.74, -2676.159, 5.057267, 5.36403, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2873, 46384, 1, 1, 1, -10129.72, -2662.371, 5.128339, 1.012743, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2874, 46384, 1, 1, 1, -10129.34, -2662.338, 5.128339, 0.8523743, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2875, 46384, 1, 1, 1, -10147.6, -2693.822, 5.028946, 0.3710144, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2876, 46384, 1, 1, 1, -10146.82, -2693.798, 5.028946, 0.284981, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2877, 46384, 1, 1, 1, -10142.28, -2692.71, 5.028946, 2.651524, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2878, 46384, 1, 1, 1, -10141.87, -2695.544, 5.028946, 4.228079, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2879, 46384, 1, 1, 1, -10112.33, -2659.548, 6.710859, 0.5580362, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2880, 46384, 1, 1, 1, -10111.25, -2659.125, 6.903601, 3.573462, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2881, 46568, 1, 1, 1, -10142.89, -2712.963, 5.120117, 5.048585, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2882, 46384, 1, 1, 1, -10104.75, -2653.516, 6.980634, 3.757293, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2883, 46384, 1, 1, 1, -10104.55, -2653.333, 6.981855, 3.661186, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2884, 46384, 1, 1, 1, -10214.24, -2729.428, 5.120117, 0.7962064, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2885, 46384, 1, 1, 1, -10214.21, -2729.458, 5.120117, 0.7825729, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2886, 46384, 1, 1, 1, -10212.52, -2731.472, 5.120117, 0.9848559, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2887, 46384, 1, 1, 1, -10212.93, -2732.001, 5.120117, 1.030188, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2888, 46384, 1, 1, 1, -10219.56, -2733.807, 5.120117, 1.268443, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2889, 46384, 1, 1, 1, -10201.79, -2739.112, 5.120117, 3.49862, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2890, 46384, 1, 1, 1, -10203.37, -2739.341, 5.120117, 3.384282, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2891, 46384, 1, 1, 1, -10213.83, -2738.251, 5.120117, 6.224347, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2892, 46384, 1, 1, 1, -10212.97, -2738.524, 5.120117, 6.12596, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2893, 46384, 1, 1, 1, -10102.71, -2688.865, 10.46747, 3.855878, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2894, 46384, 1, 1, 1, -10220.3, -2736.19, 5.078454, 0, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2895, 46384, 1, 1, 1, -10101.02, -2687.39, 10.85956, 3.841356, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2896, 46384, 1, 1, 1, -10197.12, -2743.552, 5.120117, 0.6461021, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2897, 46384, 1, 1, 1, -10096.74, -2621.723, 5.368697, 0.6188419, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2898, 46384, 1, 1, 1, -10125.23, -2721.75, 8.116401, 0.8344782, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2899, 46384, 1, 1, 1, -10197.79, -2744.097, 5.120117, 0.6281381, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2900, 46384, 1, 1, 1, -10125.65, -2723.256, 7.932311, 3.250633, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2901, 46384, 1, 1, 1, -10094.07, -2621.25, 5.699019, 0.2368409, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2902, 46568, 1, 1, 1, -10106.22, -2708.01, 13.26299, 1.330083, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2903, 46384, 1, 1, 1, -10097.41, -2693.484, 10.96218, 5.786067, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2904, 46384, 1, 1, 1, -10095.84, -2691.676, 10.74514, 0.8268234, 120, 0, 0), -- Crazed Gnome (Area: The Steps of Fate) (possible waypoints or random movement)
(@CGUID+2905, 46384, 1, 1, 1, -10128.4, -2734.52, 6.117824, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2906, 46384, 1, 1, 1, -10120.94, -2737.257, 7.943923, 5.184521, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2907, 46384, 1, 1, 1, -10111.84, -2728.617, 12.46795, 1.804141, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2908, 46384, 1, 1, 1, -10116.1, -2723.332, 11.83758, 0.131048, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2909, 46384, 1, 1, 1, -10117.66, -2731.108, 10.21698, 4.47112, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2910, 46384, 1, 1, 1, -10111.79, -2727.828, 12.54999, 1.776351, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2911, 46384, 1, 1, 1, -10118.35, -2730.465, 10.17084, 5.791499, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2912, 46384, 1, 1, 1, -10126.58, -2736.809, 6.26123, 5.383741, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2913, 46384, 1, 1, 1, -10116.84, -2721.807, 11.55682, 1.30619, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2914, 46384, 1, 1, 1, -10122.34, -2736.094, 7.72876, 1.912145, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2915, 46384, 1, 1, 1, -10115.98, -2735.892, 9.545898, 4.751652, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2916, 46384, 1, 1, 1, -10095.47, -2705.085, 13.49048, 5.324235, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2917, 46384, 1, 1, 1, -10115.37, -2739.014, 8.693359, 4.890382, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2918, 46384, 1, 1, 1, -10093.41, -2705.255, 13.40581, 0.466413, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2919, 46384, 1, 1, 1, -10090.67, -2684.528, 11.50197, 6.148616, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2920, 46384, 1, 1, 1, -10102.2, -2730.326, 13.45306, 2.77944, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2921, 46384, 1, 1, 1, -10090.28, -2683.131, 11.76809, 0.3447537, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2922, 46384, 1, 1, 1, -10101.5, -2730.59, 13.47308, 0.3771034, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2923, 46384, 1, 1, 1, -10112.81, -2742.054, 8.193359, 4.266621, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2924, 46384, 1, 1, 1, -10113.29, -2744.87, 7.122803, 4.50341, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2925, 46384, 1, 1, 1, -10106.16, -2739.441, 9.813477, 3.431069, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2926, 46384, 1, 1, 1, -10107.01, -2742.106, 8.774414, 3.82262, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2927, 46384, 1, 1, 1, -10108.74, -2743.529, 8.141525, 3.828833, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2928, 46384, 1, 1, 1, -10105.91, -2741.46, 9.110107, 3.988964, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2929, 46568, 1, 1, 1, -10141.78, -2757.793, 5.120117, 2.213228, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2930, 46384, 1, 1, 1, -10082.97, -2703.648, 11.2669, 4.558462, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2931, 46384, 1, 1, 1, -10082.6, -2701.67, 10.75003, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2932, 46384, 1, 1, 1, -10103.14, -2742.601, 8.827978, 3.20313, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2933, 46384, 1, 1, 1, -10082.91, -2711.056, 12.91021, 2.476191, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2934, 46384, 1, 1, 1, -10101.82, -2743.668, 8.336914, 3.798082, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2935, 46384, 1, 1, 1, -10081.22, -2711.789, 12.59233, 1.613983, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2936, 46384, 1, 1, 1, -10086.36, -2658.157, 12.64577, 0.7940192, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2937, 46384, 1, 1, 1, -10086.24, -2658.237, 12.68557, 0.7457014, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2938, 46384, 1, 1, 1, -10074.79, -2693.375, 9.957049, 2.16882, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2939, 46384, 1, 1, 1, -10073.1, -2695.85, 9.807763, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2940, 46384, 1, 1, 1, -10075.07, -2714.879, 11.54131, 3.333617, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2941, 46384, 1, 1, 1, -10082.5, -2734.77, 6.143703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2942, 46384, 1, 1, 1, -10082.5, -2734.77, 6.143703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2943, 46384, 1, 1, 1, -10086.43, -2646.209, 10.66289, 6.102633, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2944, 46384, 1, 1, 1, -10085.59, -2645.854, 10.82806, 6.282657, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2945, 46384, 1, 1, 1, -10070.26, -2714.538, 10.99785, 0.2967373, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2946, 46384, 1, 1, 1, -10079.6, -2737.8, 5.948574, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2947, 46384, 1, 1, 1, -10079.6, -2737.8, 5.948574, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2948, 46384, 1, 1, 1, -10075.17, -2651.573, 15.12089, 2.653474, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2949, 46384, 1, 1, 1, -10073.77, -2653.046, 15.51103, 3.232384, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2950, 46384, 1, 1, 1, -10185.1, -2771.78, 5.078454, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2951, 46384, 1, 1, 1, -10208.08, -2754.552, 5.120117, 4.870687, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2952, 46568, 1, 1, 1, -10183.75, -2773.32, 5.120117, 4.127042, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2953, 46384, 1, 1, 1, -10169.67, -2778.994, 5.120117, 3.440697, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2954, 46384, 1, 1, 1, -10209.62, -2755.817, 5.120117, 4.249059, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2955, 46384, 1, 1, 1, -10184.41, -2774.658, 5.120117, 4.946056, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2956, 46384, 1, 1, 1, -10171.96, -2780.17, 5.120117, 3.592227, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2957, 46384, 1, 1, 1, -10069.49, -2742.198, 6.546387, 3.259174, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2958, 46384, 1, 1, 1, -10068.2, -2743.09, 6.179594, 3.8235, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2959, 46384, 1, 1, 1, -10221.8, -2745.409, 5.120117, 0.2801362, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2960, 46384, 1, 1, 1, -10054.84, -2709.736, 10.62703, 5.330698, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2961, 46384, 1, 1, 1, -10222.66, -2745.747, 5.120117, 0.2204771, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2962, 46384, 1, 1, 1, -10081.24, -2628.433, 8.664839, 4.739697, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2963, 46384, 1, 1, 1, -10054.32, -2711.7, 10.57057, 5.086641, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2964, 46384, 1, 1, 1, -10081.97, -2627.369, 8.313032, 1.992873, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2965, 46384, 1, 1, 1, -10175.47, -2784.185, 5.120117, 2.322929, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2966, 46384, 1, 1, 1, -10053.51, -2720.041, 9.281572, 1.108132, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2967, 46384, 1, 1, 1, -10063.44, -2744.637, 5.944336, 0.6360073, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2968, 46384, 1, 1, 1, -10177.78, -2785.485, 5.120117, 3.378302, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2969, 46384, 1, 1, 1, -10052.92, -2720.089, 9.298418, 0.8428581, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2970, 46384, 1, 1, 1, -10159.87, -2790.434, 5.659668, 2.110279, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2971, 46384, 1, 1, 1, -10158.98, -2791.453, 5.781982, 1.515113, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2972, 46384, 1, 1, 1, -10061.11, -2743.68, 6.099854, 0.4255342, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2973, 46384, 1, 1, 1, -10223, -2754.554, 5.120117, 3.937969, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2974, 46384, 1, 1, 1, -10049.39, -2715.81, 9.569221, 3.995366, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2975, 46384, 1, 1, 1, -10223.34, -2755.498, 5.120117, 4.044211, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2976, 46384, 1, 1, 1, -10049.7, -2717.97, 6.943923, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2977, 46384, 1, 1, 1, -10049.7, -2717.97, 6.943923, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2978, 46384, 1, 1, 1, -10048.61, -2713.978, 9.743486, 1.485721, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2979, 46384, 1, 1, 1, -10180.94, -2787.747, 5.120117, 1.020119, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2980, 46384, 1, 1, 1, -10178.11, -2789.336, 5.120117, 1.53313, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2981, 46384, 1, 1, 1, -10018.31, -2718.376, 17.26397, 4.573542, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2982, 46384, 1, 1, 1, -10041.48, -2715.158, 9.095293, 2.698504, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2983, 46384, 1, 1, 1, -10026.87, -2717.042, 10.47224, 5.605816, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2984, 46384, 1, 1, 1, -10106.45, -2787.686, 5.120117, 1.05665, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2985, 46384, 1, 1, 1, -10082.4, -2789.107, 5.120117, 5.735342, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2986, 46384, 1, 1, 1, -10031.68, -2721.977, 7.7635, 0.1158785, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2987, 46384, 1, 1, 1, -10029, -2775.41, 5.078454, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2988, 46384, 1, 1, 1, -10091.43, -2779.919, 5.120117, 1.485566, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2989, 46384, 1, 1, 1, -10019.92, -2718.81, 16.84289, 4.027474, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2990, 46384, 1, 1, 1, -10030.26, -2721.023, 8.276928, 0.392838, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2991, 46384, 1, 1, 1, -10094.96, -2789.812, 5.120117, 5.919204, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2992, 46384, 1, 1, 1, -10036.73, -2724.426, 6.996172, 2.924893, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2993, 46384, 1, 1, 1, -10028.59, -2776.371, 5.120117, 5.11504, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2994, 46384, 1, 1, 1, -10091.81, -2781.123, 5.120117, 1.848386, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2995, 46384, 1, 1, 1, -10041.94, -2717.848, 8.699785, 3.797297, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2996, 46384, 1, 1, 1, -10072.84, -2789.166, 5.120117, 6.210045, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2997, 46384, 1, 1, 1, -10081.45, -2789.302, 5.120117, 5.902179, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2998, 46384, 1, 1, 1, -10026.78, -2715.71, 10.95784, 6.061231, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+2999, 46384, 1, 1, 1, -10036.53, -2723.835, 7.027825, 2.71638, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3000, 46568, 1, 1, 1, -10021.96, -2623.613, 16.38068, 1.895727, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3001, 46568, 1, 1, 1, -10182.5, -2606.81, 16.41273, 3.243829, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3002, 46384, 1, 1, 1, -10027.46, -2782.476, 5.120117, 6.036502, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3003, 46384, 1, 1, 1, -10025.67, -2782.024, 5.120117, 0.1347608, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3004, 46384, 1, 1, 1, -10021.56, -2782.037, 5.120117, 5.32983, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3005, 46384, 1, 1, 1, -10020.05, -2781.081, 5.120117, 5.967461, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3006, 46384, 1, 1, 1, -10014.35, -2779.895, 5.120117, 1.98555, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3007, 46384, 1, 1, 1, -10016.38, -2781.854, 5.120117, 2.101792, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3008, 46384, 1, 1, 1, -10014.3, -2780.105, 5.120117, 2.689516, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3009, 46384, 1, 1, 1, -10073.88, -2791.606, 5.120117, 5.337723, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3010, 46384, 1, 1, 1, -10013.81, -2780.744, 5.120117, 3.308419, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3011, 46384, 1, 1, 1, -10068.96, -2795.234, 5.120117, 2.88013, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3012, 46384, 1, 1, 1, -10014.47, -2783.557, 5.120117, 3.830901, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3013, 46384, 1, 1, 1, -10070.29, -2795.162, 5.120117, 2.974482, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3014, 46384, 1, 1, 1, -10015.02, -2784.967, 5.120117, 4.220971, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3015, 46384, 1, 1, 1, -10080.25, -2794.862, 5.120117, 0.5470546, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3016, 46384, 1, 1, 1, -10079.38, -2795.34, 5.120117, 0.206507, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3017, 46384, 1, 1, 1, -10009.52, -2785.63, 5.120117, 2.56973, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3018, 46384, 1, 1, 1, -10011.25, -2787.333, 5.120117, 1.187017, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3019, 46384, 1, 1, 1, -10087.68, -2792.973, 5.120117, 2.406326, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3020, 46384, 1, 1, 1, -10012.1, -2789.44, 5.078454, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3021, 46384, 1, 1, 1, -10087.34, -2794.395, 5.120117, 2.849723, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3022, 46384, 1, 1, 1, -10069.7, -2802.05, 5.078124, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3023, 46384, 1, 1, 1, -10007.68, -2786.65, 5.120117, 2.416675, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3024, 46384, 1, 1, 1, -10095.81, -2790.829, 5.120117, 5.455243, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3025, 46384, 1, 1, 1, -10070.94, -2803.634, 5.120117, 4.047122, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3026, 46384, 1, 1, 1, -10091.12, -2794.98, 5.120117, 1.201381, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3027, 46384, 1, 1, 1, -10092.97, -2794.675, 5.120117, 2.003617, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3028, 46384, 1, 1, 1, -10094.33, -2795.895, 5.120117, 1.000107, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3029, 46384, 1, 1, 1, -10094.54, -2796.011, 5.120117, 1.171054, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3030, 46384, 1, 1, 1, -10079.55, -2804.597, 5.120117, 4.071702, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3031, 46384, 1, 1, 1, -10078.5, -2806.694, 5.120117, 4.844537, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3032, 46384, 1, 1, 1, -10106.55, -2788.732, 5.120117, 0.7925559, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3033, 46384, 1, 1, 1, -9996.962, -2787.587, 5.120117, 0.3595589, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3034, 46384, 1, 1, 1, -9995.729, -2786.771, 5.295166, 0.5334976, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3035, 46384, 1, 1, 1, -9996.984, -2790.105, 5.294678, 0.6582034, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3036, 46384, 1, 1, 1, -9994.942, -2790.505, 5.539307, 0.003613862, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3037, 46568, 1, 1, 1, -10101.8, -2700.72, 12.02193, 2.203637, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3038, 46568, 1, 1, 1, -10143.65, -2710.783, 5.078548, 0.4098781, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3039, 46384, 1, 1, 1, -10160.75, -2796.525, 6.484701, 0.97235, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3040, 46384, 1, 1, 1, -10173.7, -2791.897, 5.120117, 2.308454, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3041, 46384, 1, 1, 1, -10157.19, -2802.119, 7.929688, 4.301712, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3042, 46384, 1, 1, 1, -10169.25, -2795.953, 5.273926, 2.311374, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3043, 46384, 1, 1, 1, -10156.32, -2802.218, 7.848877, 4.818379, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3044, 46384, 1, 1, 1, -10173.56, -2792.683, 5.120117, 2.602792, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3045, 46384, 1, 1, 1, -10161.81, -2797.304, 6.481445, 1.22766, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3046, 46384, 1, 1, 1, -10169.72, -2796.964, 5.568115, 2.685113, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3047, 46384, 1, 1, 1, -10152.87, -2808.425, 8.831055, 3.541833, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3048, 46384, 1, 1, 1, -10155.48, -2807.818, 8.87085, 2.991034, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3049, 46384, 1, 1, 1, -10179.29, -2790.615, 5.120117, 2.292407, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3050, 46384, 1, 1, 1, -10159.29, -2806.751, 8.69043, 3.636804, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3051, 46384, 1, 1, 1, -10159.38, -2806.947, 8.703369, 3.845198, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3052, 46384, 1, 1, 1, -10181.34, -2788.651, 5.120117, 0.9747624, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3053, 46384, 1, 1, 1, -10169.33, -2802.114, 6.106934, 3.885003, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3054, 46384, 1, 1, 1, -10175.04, -2798.695, 5.58374, 2.000163, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3055, 46384, 1, 1, 1, -10170.95, -2802.352, 5.82373, 3.560935, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3056, 46384, 1, 1, 1, -10174.7, -2799.44, 5.468506, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3057, 46384, 1, 1, 1, -10235.9, -2746.52, 5.053917, 5.297965, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3058, 46384, 1, 1, 1, -10236.64, -2748.317, 5.053917, 4.732198, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3059, 46384, 1, 1, 1, -10156.6, -2686.4, 5.078474, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3060, 46384, 1, 1, 1, -10140.8, -2693.5, 5.078474, 1.71438, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3061, 46384, 1, 1, 1, -10218.4, -2618.533, 16.37012, 4.210472, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3062, 46384, 1, 1, 1, -10233.22, -2609.382, 16.69356, 1.189846, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3063, 46384, 1, 1, 1, -10219.95, -2612.652, 16.37012, 5.356086, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3064, 46384, 1, 1, 1, -10219.28, -2611.895, 16.37012, 3.92793, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3065, 46384, 1, 1, 1, -10219.91, -2610.862, 16.37012, 3.511645, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3066, 46384, 1, 1, 1, -10205.62, -2618.744, 16.37012, 4.439369, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3067, 46384, 1, 1, 1, -10240.86, -2600.312, 16.69829, 4.66118, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3068, 46384, 1, 1, 1, -10223.22, -2604.609, 16.37012, 6.182797, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3069, 46384, 1, 1, 1, -10202.29, -2617.956, 16.37012, 4.00623, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3070, 46384, 1, 1, 1, -10225.92, -2602.997, 16.37012, 2.594399, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3071, 46384, 1, 1, 1, -10222.12, -2603.728, 16.37012, 0.5578471, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3072, 46384, 1, 1, 1, -10213.3, -2606.088, 16.37012, 0.2554162, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3073, 46384, 1, 1, 1, -10201.83, -2613.96, 16.37012, 1.716007, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3074, 46384, 1, 1, 1, -10240.92, -2595.785, 16.67484, 1.737651, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3075, 46384, 1, 1, 1, -10206.7, -2608.77, 16.37012, 1.266389, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3076, 46384, 1, 1, 1, -10230.21, -2596.875, 16.45441, 1.209996, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3077, 46384, 1, 1, 1, -10335.7, -2659.88, 5.081044, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3078, 46384, 1, 1, 1, -10338.33, -2658.554, 5.122708, 2.675131, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3079, 46384, 1, 1, 1, -10221.4, -2589.36, 16.41273, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3080, 46384, 1, 1, 1, -10341.18, -2661.708, 5.122708, 2.582293, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3081, 46384, 1, 1, 1, -10219.91, -2588.762, 16.45441, 0.4483343, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3082, 46384, 1, 1, 1, -10341.35, -2659.963, 5.122708, 2.107669, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3083, 46384, 1, 1, 1, -10238.49, -2583.383, 16.90251, 3.941412, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3084, 46384, 1, 1, 1, -10220.8, -2587.078, 16.45441, 1.150121, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3085, 46384, 1, 1, 1, -10206.31, -2593.983, 16.45441, 1.850007, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3086, 46384, 1, 1, 1, -10221.84, -2586.267, 16.45441, 1.71287, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3087, 46384, 1, 1, 1, -10342.68, -2658.353, 5.122708, 2.124762, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3088, 46384, 1, 1, 1, -10343.57, -2658.714, 5.122708, 2.451174, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3089, 46384, 1, 1, 1, -10345.08, -2657.566, 5.122708, 1.464358, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3090, 46384, 1, 1, 1, -10345.59, -2659.551, 5.122708, 1.744271, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3091, 46384, 1, 1, 1, -10326.72, -2613.803, 5.53985, 0.7835996, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3092, 46384, 1, 1, 1, -10328.55, -2613.911, 5.521784, 1.403553, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3093, 46384, 1, 1, 1, -10154.8, -2670.949, 5.028946, 4.135526, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3094, 46384, 1, 1, 1, -10153.97, -2668.991, 5.028946, 3.789553, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3095, 46384, 1, 1, 1, -10205.6, -2596.46, 16.41273, 1.363833, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3096, 46384, 1, 1, 1, -10231.2, -2599.51, 16.41273, 2.086139, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3097, 46384, 1, 1, 1, -10215.3, -2606.61, 16.41273, 5.380496, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3098, 46384, 1, 1, 1, -10207.6, -2611.63, 16.41273, 2.356608, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3099, 46384, 1, 1, 1, -10221.3, -2610.86, 16.41273, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3100, 46384, 1, 1, 1, -10205.4, -2617.95, 16.41273, 4.005117, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3101, 46384, 1, 1, 1, -10217.8, -2617.43, 16.41273, 4.258225, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3102, 46384, 1, 1, 1, -10233.6, -2610.33, 16.35603, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3103, 46384, 1, 1, 1, -10224.9, -2604.44, 16.41273, 5.973411, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3104, 46384, 1, 1, 1, -10237.8, -2582.67, 16.41273, 1.868595, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3105, 46384, 1, 1, 1, -10359.25, -2651.323, 5.122708, 0.8410892, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3106, 46384, 1, 1, 1, -10347.7, -2590.82, 6.472963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3107, 46384, 1, 1, 1, -10349.8, -2599.4, 5.316254, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3108, 46384, 1, 1, 1, -10353.5, -2653.402, 5.122708, 0.7791477, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3109, 46384, 1, 1, 1, -10345.18, -2593.706, 9.420167, 2.358892, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3110, 46384, 1, 1, 1, -10342.32, -2607.107, 14.48442, 2.038453, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3111, 46384, 1, 1, 1, -10351.58, -2652.434, 5.122708, 1.801257, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3112, 46384, 1, 1, 1, -10350.87, -2607.104, 5.747708, 0.7675945, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3113, 46384, 1, 1, 1, -10349.8, -2599.4, 5.316254, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3114, 46384, 1, 1, 1, -10350.74, -2652.561, 5.122708, 0.2817091, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3115, 46384, 1, 1, 1, -10329.88, -2595.899, 7.126448, 0.8114378, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3116, 46384, 1, 1, 1, -10338.4, -2598.26, 6.141963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3117, 46384, 1, 1, 1, -10347.7, -2590.82, 6.472963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
-- (@CGUID+3118, 46384, 0, 1, 1, 1, 2, 1.4, 4.712389, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) - !!! on transport (NYI) !!!
(@CGUID+3118, 46384, 1, 1, 1, -10354.23, -2654.136, 5.122708, 6.061576, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3119, 46384, 1, 1, 1, -10357.8, -2601.88, 5.314283, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3120, 46384, 1, 1, 1, -10346.68, -2594.469, 10.30827, 2.612086, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3121, 46384, 1, 1, 1, -10348.01, -2604.414, 5.86957, 4.829512, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3122, 46384, 1, 1, 1, -10346.59, -2604.059, 5.730742, 3.955291, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3123, 46384, 1, 1, 1, -10359.96, -2652.964, 5.122708, 0.4129037, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3124, 46384, 1, 1, 1, -10389.25, -2644.78, 5.013082, 6.042146, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3125, 46384, 1, 1, 1, -10353.53, -2653.833, 5.122708, 0.6683352, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3126, 46384, 1, 1, 1, -10336.44, -2596.101, 6.583688, 0.8333523, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3127, 46384, 1, 1, 1, -10350.83, -2606.986, 5.747708, 0.7915624, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3128, 46384, 1, 1, 1, -10329.73, -2596.038, 7.106597, 0.7390356, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3129, 46384, 1, 1, 1, -10357.8, -2601.88, 5.314283, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3130, 46384, 1, 1, 1, -10356.83, -2653.273, 5.122708, 0.6814916, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3131, 46384, 1, 1, 1, -10345.52, -2603.277, 5.900576, 3.958773, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3132, 46384, 1, 1, 1, -10347.85, -2602.153, 6.482613, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3133, 46384, 1, 1, 1, -10393.13, -2645.644, 4.981259, 4.130682, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3134, 46384, 1, 1, 1, -10401.04, -2625.86, 5.345642, 4.298331, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3135, 46384, 1, 1, 1, -10401.19, -2623.463, 5.511413, 2.269694, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3136, 46384, 1, 1, 1, -10403.46, -2645.988, 4.673882, 2.195072, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3137, 46384, 1, 1, 1, -10404.14, -2645.742, 4.673882, 2.336074, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3138, 46384, 1, 1, 1, -10405.9, -2644.116, 4.673882, 3.346804, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3139, 46384, 1, 1, 1, -10406.6, -2642.359, 4.673882, 2.658972, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3140, 46384, 1, 1, 1, -10407.35, -2638.609, 4.673882, 5.036296, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3141, 46384, 1, 1, 1, -10407.16, -2619.884, 5.761413, 5.758091, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3142, 46384, 1, 1, 1, -10408.7, -2638.4, 4.673882, 4.200457, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3143, 46384, 1, 1, 1, -10408.64, -2613.077, 5.886413, 0.6387249, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3144, 46384, 1, 1, 1, -10411.09, -2641.377, 4.673882, 0.6225572, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3145, 46384, 1, 1, 1, -10409.75, -2613.28, 5.886413, 0.8906602, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3146, 46384, 1, 1, 1, -10411.71, -2641.729, 4.673882, 0.8086498, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3147, 46384, 1, 1, 1, -10411.48, -2619.925, 5.808044, 3.992043, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3148, 46384, 1, 1, 1, -10411.78, -2621.328, 5.773882, 6.104426, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3149, 46384, 1, 1, 1, -10412.13, -2622.032, 5.636413, 1.83944, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3150, 46384, 1, 1, 1, -10411.22, -2647.989, 4.708306, 0.4818178, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3151, 46384, 1, 1, 1, -10412.02, -2619.596, 5.886413, 0.4224188, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3152, 46384, 1, 1, 1, -10410.78, -2612.676, 5.886413, 0.223828, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3153, 46384, 1, 1, 1, -10412.53, -2619.991, 5.886413, 1.787237, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3154, 46384, 1, 1, 1, -10410.84, -2611.661, 5.913616, 0.5737055, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3155, 46384, 1, 1, 1, -10411.2, -2612.537, 5.886413, 0.3276049, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3156, 46384, 1, 1, 1, -10412.96, -2646.333, 4.713587, 1.352444, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3157, 46384, 1, 1, 1, -10411.33, -2610.782, 5.886413, 0.8987148, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3158, 46384, 1, 1, 1, -10411.93, -2610.615, 5.918947, 1.09232, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3159, 46384, 1, 1, 1, -10412.02, -2610.594, 5.930944, 1.121093, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3160, 46384, 1, 1, 1, -10412.88, -2612.756, 6.011413, 0.8673219, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3161, 46384, 1, 1, 1, -10412.4, -2610.458, 5.913187, 1.258891, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3162, 46384, 1, 1, 1, -10415.66, -2617.859, 6.055847, 5.48426, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3163, 46384, 1, 1, 1, -10416.9, -2638.26, 4.692043, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3164, 46384, 1, 1, 1, -10416.2, -2617.3, 5.429994, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3165, 46384, 1, 1, 1, -10417.78, -2638.556, 4.673882, 3.466417, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3166, 46384, 1, 1, 1, -10417.2, -2619.32, 5.996624, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3167, 46384, 1, 1, 1, -10417.64, -2618.555, 6.011413, 4.207141, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3168, 46384, 1, 1, 1, -10419.09, -2643.926, 4.673882, 3.026284, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3169, 46384, 1, 1, 1, -10419.24, -2619.005, 6.052292, 3.794005, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3170, 46384, 1, 1, 1, -10420.16, -2640.511, 4.673882, 3.02788, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3171, 46384, 1, 1, 1, -10420.81, -2637.931, 4.673882, 4.10581, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3172, 46384, 1, 1, 1, -10420.86, -2638.159, 4.673882, 4.153234, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3173, 46384, 1, 1, 1, -10420.27, -2620.436, 6.011413, 3.4897, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3174, 46384, 1, 1, 1, -10420.7, -2641.766, 4.673882, 3.48374, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3175, 46384, 1, 1, 1, -10420.89, -2642.018, 4.673882, 2.412258, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3176, 46384, 1, 1, 1, -10426.21, -2637.422, 4.798882, 5.279303, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3177, 46384, 1, 1, 1, -10426.29, -2641.297, 4.673882, 0.2616612, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3178, 46384, 1, 1, 1, -10426.87, -2637.744, 4.73264, 5.030651, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3179, 46384, 1, 1, 1, -10426.57, -2641.357, 4.673882, 0.2663989, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3180, 46384, 1, 1, 1, -10425.59, -2610.505, 6.946716, 5.12298, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3181, 46384, 1, 1, 1, -10425.7, -2610.681, 6.938171, 1.349318, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3182, 46384, 1, 1, 1, -10424.87, -2605.863, 6.652526, 0.7687513, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3183, 46384, 1, 1, 1, -10426.89, -2613.01, 6.886413, 1.285732, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3184, 46384, 1, 1, 1, -10426.12, -2609.604, 7.118347, 1.776883, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3185, 46384, 1, 1, 1, -10427.5, -2612.852, 6.92347, 1.502547, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3186, 46384, 1, 1, 1, -10426.17, -2606.117, 6.96405, 0.01143697, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3187, 46384, 1, 1, 1, -10426.35, -2606.45, 6.986022, 6.174469, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3188, 46384, 1, 1, 1, -10426.88, -2606.851, 7.049011, 5.978252, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3189, 46384, 1, 1, 1, -10428.33, -2611.648, 7.136413, 0.7564721, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3190, 46384, 1, 1, 1, -10427.76, -2608.484, 7.155212, 5.233651, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3191, 46384, 1, 1, 1, -10428.99, -2611.917, 7.136413, 0.867337, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3192, 46384, 1, 1, 1, -10431.78, -2630.566, 5.280944, 0.5718988, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3193, 46384, 1, 1, 1, -10428.07, -2606.406, 7.067077, 6.039989, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3194, 46384, 1, 1, 1, -10428.46, -2606.534, 7.113952, 5.744671, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3195, 46384, 1, 1, 1, -10432.19, -2630.728, 5.261413, 0.3280222, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3196, 46384, 1, 1, 1, -10429.51, -2609.482, 7.261413, 0.1969396, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3197, 46384, 1, 1, 1, -10429.1, -2606.15, 5.983324, 5.319882, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3198, 46384, 1, 1, 1, -10429.1, -2606.15, 5.983324, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3199, 46384, 1, 1, 1, -10430.54, -2610.634, 7.261413, 0.5719044, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3200, 46384, 1, 1, 1, -10430.42, -2609.747, 7.261413, 3.421999, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3201, 46384, 1, 1, 1, -10433, -2612.22, 5.814504, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3202, 46384, 1, 1, 1, -10436.07, -2638.605, 4.013041, 3.975709, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3203, 46384, 1, 1, 1, -10436.54, -2638.358, 3.787699, 3.773322, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3204, 46384, 1, 1, 1, -10465.58, -2603.083, 7.378512, 4.818851, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3205, 46384, 1, 1, 1, -10455.52, -2592.673, 7.002905, 4.15203, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3206, 46384, 1, 1, 1, -10463.4, -2601.115, 6.840671, 6.235153, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3207, 46384, 1, 1, 1, -10458.27, -2580.715, 9.771704, 6.056684, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3208, 46384, 1, 1, 1, -10461.41, -2579.969, 9.439184, 2.897944, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3209, 46384, 1, 1, 1, -10456.47, -2592.932, 7.085913, 3.811949, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3210, 46384, 1, 1, 1, -10476, -2573.17, 10.82413, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3211, 46384, 1, 1, 1, -10463.36, -2569.681, 11.73801, 6.049171, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3212, 46384, 1, 1, 1, -10476, -2573.17, 10.82413, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3213, 46384, 1, 1, 1, -10470.8, -2584.59, 7.463314, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3214, 46384, 1, 1, 1, -10470.8, -2584.59, 7.463314, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3215, 46384, 1, 1, 1, -10464.38, -2569.708, 11.76975, 5.878086, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3216, 46384, 1, 1, 1, -10479.24, -2593.077, 7.765652, 0.335808, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3217, 46384, 1, 1, 1, -10479.62, -2592.669, 7.722439, 0.5574877, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3218, 46384, 1, 1, 1, -10461.62, -2563.79, 13.60122, 2.021661, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3219, 46384, 1, 1, 1, -10457.68, -2565.268, 13.52701, 0.4459348, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3220, 46384, 1, 1, 1, -10410.2, -2524.27, 31.62623, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3221, 46384, 1, 1, 1, -10410.2, -2524.27, 31.62623, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3222, 46384, 1, 1, 1, -10418.92, -2520.197, 35.34604, 5.348416, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3223, 46384, 1, 1, 1, -10418.3, -2519.345, 35.42099, 5.891013, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3224, 46384, 1, 1, 1, -10406.81, -2524.207, 33.42905, 2.624627, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3225, 46384, 1, 1, 1, -10405.84, -2524.662, 33.16247, 2.581752, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3226, 46384, 1, 1, 1, -10393.86, -2530.076, 30.68529, 1.173738, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3227, 46384, 1, 1, 1, -10392.53, -2529.087, 30.81065, 0.8826212, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3228, 46384, 1, 1, 1, -10403.7, -2519.465, 33.16904, 3.36429, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3229, 46384, 1, 1, 1, -10403.77, -2519.038, 33.23838, 3.213874, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3230, 46384, 1, 1, 1, -10416.5, -2512.859, 36.11582, 4.889048, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3231, 46384, 1, 1, 1, -10417.8, -2512.069, 35.91831, 3.441432, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3232, 46384, 1, 1, 1, -10393.55, -2524.417, 31.06859, 1.065368, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3233, 46384, 1, 1, 1, -10391.27, -2523.64, 31.20751, 0.4929291, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3234, 46384, 1, 1, 1, -10404.76, -2513.9, 34.12904, 2.988943, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3235, 46384, 1, 1, 1, -10402.38, -2514.466, 33.57773, 3.397001, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3236, 46568, 1, 1, 1, -10385.21, -2525.556, 31.69359, 1.47568, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3237, 46384, 1, 1, 1, -10378.06, -2531.676, 32.1184, 1.49485, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3238, 46384, 1, 1, 1, -10408.7, -2507.7, 32.69053, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3239, 46384, 1, 1, 1, -10408.7, -2507.7, 32.69053, 0, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing)
(@CGUID+3240, 46384, 1, 1, 1, -10378.08, -2530.167, 32.23193, 1.561172, 120, 0, 0), -- Crazed Gnome (Area: The Cursed Landing) (possible waypoints or random movement)
(@CGUID+3241, 46384, 1, 1, 1, -10417.2, -2496.98, 34.66383, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3242, 46384, 1, 1, 1, -10396.2, -2510.7, 32.00083, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3243, 46384, 1, 1, 1, -10417.2, -2496.98, 34.66383, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3244, 46384, 1, 1, 1, -10402.3, -2500.43, 32.34723, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3245, 46384, 1, 1, 1, -10402.3, -2500.43, 32.34723, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3246, 46568, 1, 1, 1, -10437.54, -2469.13, 41.26732, 1.580562, 120, 0, 0), -- Crazed Spiderbot Pilot (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3247, 46384, 1, 1, 1, -10403.67, -2505.826, 34.9227, 3.776605, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3248, 46384, 1, 1, 1, -10404.23, -2505.068, 35.02353, 3.466838, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3249, 46384, 1, 1, 1, -10393.33, -2511.342, 32.49364, 6.0634, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3250, 46384, 1, 1, 1, -10445.17, -2463.228, 40.99744, 5.357204, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3251, 46384, 1, 1, 1, -10390.52, -2515.715, 31.85692, 5.917165, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3252, 46384, 1, 1, 1, -10390.07, -2515.554, 31.92372, 6.023154, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3253, 46384, 1, 1, 1, -10390.86, -2504.971, 32.7893, 5.077846, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3254, 46384, 1, 1, 1, -10435.55, -2463.147, 41.82678, 2.389763, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3255, 46384, 1, 1, 1, -10435.73, -2462.83, 41.88635, 2.336743, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3256, 46384, 1, 1, 1, -10389.54, -2505.921, 32.51611, 5.381839, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3257, 46384, 1, 1, 1, -10445.59, -2459.647, 41.50574, 0.8637365, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3258, 46384, 1, 1, 1, -10386.8, -2509.643, 32.10693, 4.569247, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3259, 46384, 1, 1, 1, -10420.06, -2463.512, 42.09998, 6.007426, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3260, 46384, 1, 1, 1, -10421.18, -2462.776, 42.32263, 0.3731656, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3261, 46384, 1, 1, 1, -10450.1, -2457.22, 37.06963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3262, 46384, 1, 1, 1, -10450.1, -2457.22, 37.06963, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3263, 46384, 1, 1, 1, -10384.83, -2510.216, 32.10693, 5.267444, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3264, 46384, 1, 1, 1, -10384.49, -2520.275, 31.90371, 0.6265652, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3265, 46384, 1, 1, 1, -10384.01, -2514.895, 32.10693, 5.006385, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3266, 46384, 1, 1, 1, -10437.6, -2455.92, 39.66883, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3267, 46384, 1, 1, 1, -10437.6, -2455.92, 39.66883, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3268, 46384, 1, 1, 1, -10383.17, -2521.712, 31.96655, 6.190362, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3269, 46384, 1, 1, 1, -10446.31, -2454.943, 42.21277, 3.385153, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3270, 46384, 1, 1, 1, -10382.09, -2515.786, 32.23193, 5.661081, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3271, 46384, 1, 1, 1, -10381.86, -2515.25, 32.23193, 2.090502, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3272, 46384, 1, 1, 1, -10446.37, -2453.397, 42.44421, 2.70028, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3273, 46384, 1, 1, 1, -10379.94, -2519.03, 32.23193, 5.067586, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3274, 46384, 1, 1, 1, -10455.89, -2453.254, 41.67664, 3.806685, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3275, 46384, 1, 1, 1, -10456.72, -2453.356, 41.87683, 3.51923, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3276, 46384, 1, 1, 1, -10462.6, -2453.96, 39.78143, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3277, 46384, 1, 1, 1, -10462.6, -2453.96, 39.78143, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3278, 46384, 1, 1, 1, -10432.5, -2452.59, 42.60493, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3279, 46384, 1, 1, 1, -10432.5, -2452.59, 42.60493, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3280, 46384, 1, 1, 1, -10376.96, -2513.257, 32.09433, 4.22733, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3281, 46384, 1, 1, 1, -10375.93, -2511.746, 31.87816, 4.414847, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3282, 46384, 1, 1, 1, -10444.74, -2447.301, 44.46161, 0.9003276, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3283, 46384, 1, 1, 1, -10460.1, -2447.32, 39.02213, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3284, 46384, 1, 1, 1, -10460.1, -2447.32, 39.02213, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3285, 46384, 1, 1, 1, -10444.37, -2446.26, 44.77332, 1.022339, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3286, 46384, 1, 1, 1, -10448.3, -2445.49, 39.65223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3287, 46384, 1, 1, 1, -10448.3, -2445.49, 39.65223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3288, 46384, 1, 1, 1, -10455.21, -2444.791, 43.01306, 2.762653, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3289, 46384, 1, 1, 1, -10455.21, -2444.791, 43.01306, 2.762653, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3290, 46384, 1, 1, 1, -10444.09, -2444.125, 45.31995, 3.971388, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3291, 46384, 1, 1, 1, -10370.79, -2519.646, 31.67945, 2.516239, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3292, 46384, 1, 1, 1, -10370.64, -2519.472, 31.64672, 2.439791, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3293, 46384, 1, 1, 1, -10440.17, -2441.72, 46.00793, 0.1184305, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3294, 46384, 1, 1, 1, -10440.9, -2440.63, 42.32703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3295, 46384, 1, 1, 1, -10440.9, -2440.63, 42.32703, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3296, 46384, 1, 1, 1, -10461.8, -2441.67, 40.33393, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3297, 46384, 1, 1, 1, -10461.8, -2441.67, 40.33393, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3298, 46384, 1, 1, 1, -10471.1, -2445.69, 47.73513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3299, 46384, 1, 1, 1, -10471.1, -2445.69, 47.73513, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3300, 46384, 1, 1, 1, -10441.54, -2438.936, 46.88757, 5.088464, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3301, 46384, 1, 1, 1, -10442.84, -2438.391, 46.68591, 4.532536, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3302, 46384, 1, 1, 1, -10448.4, -2436.8, 41.38013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3303, 46384, 1, 1, 1, -10448.4, -2436.8, 41.38013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3304, 46384, 1, 1, 1, -10457.9, -2434.85, 40.34023, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3305, 46384, 1, 1, 1, -10457.9, -2434.85, 40.34023, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3306, 46384, 1, 1, 1, -10468.48, -2438.569, 53.09869, 4.140112, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3307, 46384, 1, 1, 1, -10469.07, -2437.391, 53.47787, 3.550625, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3308, 46384, 1, 1, 1, -10420.72, -2430.398, 46.99797, 2.294287, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3309, 46384, 1, 1, 1, -10442.06, -2419.08, 49.17274, 3.778766, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3310, 46384, 1, 1, 1, -10455.35, -2418.223, 46.57045, 5.629025, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3311, 46384, 1, 1, 1, -10455.11, -2417.723, 46.6598, 6.052675, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3312, 46384, 1, 1, 1, -10428.38, -2410.218, 50.19084, 1.164656, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3313, 46384, 1, 1, 1, -10424.64, -2389.933, 50.60461, 3.667278, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3314, 46384, 1, 1, 1, -10470.59, -2344.051, 62.04717, 3.615314, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3315, 46384, 1, 1, 1, -10482.22, -2352.255, 64.41927, 3.318302, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3316, 46384, 1, 1, 1, -10480.46, -2348.928, 63.96094, 1.895019, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3317, 46384, 1, 1, 1, -10422.89, -2389.217, 49.2447, 4.075816, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3318, 46384, 1, 1, 1, -10429.4, -2412.6, 49.61463, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3319, 46384, 1, 1, 1, -10472.5, -2414.32, 54.88873, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3320, 46384, 1, 1, 1, -10469.76, -2343.365, 61.39404, 3.462086, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3321, 46384, 1, 1, 1, -10450.11, -2384.399, 52.14802, 4.961538, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3322, 46384, 1, 1, 1, -10448.24, -2381.497, 51.69678, 0.8127353, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3323, 46384, 1, 1, 1, -10480.08, -2422.81, 60.09925, 6.072092, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3324, 46384, 1, 1, 1, -10443.34, -2339.649, 56.3733, 5.602953, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3325, 46384, 1, 1, 1, -10444.83, -2338.439, 56.73024, 5.607095, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3326, 46384, 1, 1, 1, -10403.68, -2394.965, 37.6761, 5.236569, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3327, 46384, 1, 1, 1, -10491.75, -2344.293, 66.62964, 5.46465, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3328, 46384, 1, 1, 1, -10461.4, -2330.72, 56.36363, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3329, 46384, 1, 1, 1, -10461.4, -2330.72, 56.36363, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3330, 46384, 1, 1, 1, -10495.3, -2344.68, 64.84174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3331, 46384, 1, 1, 1, -10495.3, -2344.68, 64.84174, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3332, 46384, 1, 1, 1, -10493, -2342.96, 67.14384, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3333, 46384, 1, 1, 1, -10484.1, -2335.78, 62.06223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3334, 46384, 1, 1, 1, -10484.1, -2335.78, 62.06223, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3335, 46384, 1, 1, 1, -10465.4, -2325.998, 60.83884, 5.136798, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3336, 46384, 1, 1, 1, -10464.49, -2323.169, 61.41257, 0.5557178, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3337, 46384, 1, 1, 1, -10457.39, -2319.951, 60.37302, 3.559828, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3338, 46384, 1, 1, 1, -10457.29, -2319.791, 60.36961, 3.511582, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3339, 46384, 1, 1, 1, -10482.88, -2322.501, 64.6601, 2.05371, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3340, 46384, 1, 1, 1, -10480.61, -2321.38, 63.76875, 0.9898359, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3341, 46384, 1, 1, 1, -10508.8, -2335.86, 67.22533, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3342, 46384, 1, 1, 1, -10508.8, -2335.86, 67.22533, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3343, 46384, 1, 1, 1, -10482.1, -2317.13, 61.20323, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3344, 46384, 1, 1, 1, -10482.1, -2317.13, 61.20323, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3345, 46384, 1, 1, 1, -10470.91, -2312.607, 64.2707, 4.835976, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3346, 46384, 1, 1, 1, -10471.75, -2311.797, 64.49335, 3.029677, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3347, 46384, 1, 1, 1, -10498, -2316.7, 67.87354, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3348, 46384, 1, 1, 1, -10498, -2316.7, 67.87354, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3349, 46384, 1, 1, 1, -10512.16, -2327.114, 72.865, 6.029617, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3350, 46384, 1, 1, 1, -10512.61, -2325.445, 72.75562, 0.9171807, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3351, 46384, 1, 1, 1, -10430.05, -2297.726, 51.12083, 0.8109368, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3352, 46384, 1, 1, 1, -10448.95, -2293.875, 54.5844, 2.066416, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3353, 46384, 1, 1, 1, -10449.38, -2293.141, 54.65178, 2.08002, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3354, 46384, 1, 1, 1, -10428.4, -2296.808, 50.81223, 0.6346611, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3355, 46384, 1, 1, 1, -10446.9, -2291.268, 53.63274, 1.579141, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3356, 46384, 1, 1, 1, -10476.44, -2286.999, 63.22519, 1.682463, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3357, 46384, 1, 1, 1, -10478.06, -2287.862, 63.76187, 2.301929, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3358, 46384, 1, 1, 1, -10491.9, -2282.95, 62.26403, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3359, 46384, 1, 1, 1, -10491.9, -2282.95, 62.26403, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3360, 46384, 1, 1, 1, -10464.1, -2287.97, 51.96013, 0, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation)
(@CGUID+3361, 46384, 1, 1, 1, -10446.52, -2288.646, 53.75595, 1.441976, 120, 0, 0), -- Crazed Gnome (Area: The Trail of Devastation) (possible waypoints or random movement)
(@CGUID+3362, 46384, 1, 1, 1, -10464.1, -2287.97, 51.96013, 0, 120, 0, 0); -- Crazed Gnome (Area: The Trail of Devastation)

UPDATE `creature` SET `phaseMask`=182 WHERE `id`=46384;

UPDATE `creature_template` SET `modelid1`=37557, `scale`=1, `HoverHeight`=2 WHERE `entry`=46372;
UPDATE `creature_template` SET `VehicleId`=1179 WHERE `entry`=46360;
UPDATE `creature_template` SET `ScriptName`='npc_crazed_gnome' WHERE `entry`=46384;
UPDATE `creature_template` SET `ScriptName`='npc_fusion_core_pivot' WHERE `entry`=46360;

DELETE FROM `creature_text` WHERE `entry`=47753;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47753,0,0,'You will pay for this intrusion!',12,0,100,0,0,0,'Comment');

-- Dark Pharaoh Tekahn
SET @ENTRY := 47753;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `ScriptName`='npc_dark_pharaoh_tekahn' WHERE `entry`=47753;
UPDATE `creature` SET `phaseMask`=32768, `position_x`=-11408.28, `position_y`=-766.33, `position_z`=136.56, `orientation`=4.72, `spawndist`=10, `MovementType`=1 WHERE `guid`=739415;
UPDATE `creature` SET `phaseMask`=32768, `position_x`=-11437.43, `position_y`=-766.69, `position_z`=136.56, `orientation`=4.72, `spawndist`=10, `MovementType`=1 WHERE `guid`=739419;
UPDATE `creature_template` SET `ScriptName`='npc_pyramid_watcher' WHERE `entry`=47810;
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=47852;
UPDATE `creature_template` SET `ScriptName`='npc_ramkahen_champion_tekahn' WHERE `entry`=47868;

DELETE FROM conditions WHERE SourceEntry = '89013' AND ConditionValue2 = '47852';
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 89013, 0, 0, 31, 0, 3, 47852, 0, 0, 0, '', 'Burning Gaze - Only on Burning Gaze Trigger');

-- Burning Gaze
SET @ENTRY := 47852;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,89,15,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Random Move");

UPDATE `creature_template` SET `modelid2`=11686 WHERE `entry`=47852;
UPDATE `creature_template` SET `ScriptName`='npc_king_phaoris_tekahn' WHERE `entry`=47867;
UPDATE `creature_template` SET `VehicleId`=1393, `InhabitType`=4, `ScriptName`='npc_fall_of_neferset_camera' WHERE `entry`=49376;

DELETE FROM `spell_target_position` WHERE `id` = '91956';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(91956, 1, -10679.29, -760.41, 91.59, 3.14);

DELETE FROM `creature_text` WHERE `entry`=49183;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49183,0,0,'The Dark Pharaoh has fallen! His immortal colossi tumble like toys!',14,0,100,0,0,0,'Comment'),
(49183,1,0,'Neferset City will fall! ATTACK!!!',14,0,100,0,0,0,'Comment');

-- Immortal Colossus
SET @ENTRY := 48548;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,12000,13000,11,90422,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Colossal Cleave"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Phasing");

-- Ramkahen Legionnaire
SET @ENTRY := 48512;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Phasing");

-- High Commander Kamses
SET @ENTRY := 49183;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Phasing");

UPDATE `creature_template` SET `VehicleId`=1082 WHERE `entry`=45146;

DELETE FROM `spell_script_names` WHERE `spell_id` = '84294'; 
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84294, 'spell_summon_camera_explosionation');

UPDATE `gameobject` SET `phaseMask`=5 WHERE `guid` IN
(727957, 727930, 727934, 727955, 727943, 727940, 727937, 727951,
727952, 727939, 727931, 727945, 727953, 727935, 727938,
727956, 727958, 727932, 727944, 77685, 727946);

UPDATE `creature_template` SET `ScriptName`='npc_camera_explosionation' WHERE `entry`=45146;

DELETE FROM `conditions` WHERE `SourceEntry` = '84286';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 84286, 0, 0, 31, 0, 3, 45144, 0, 0, 0, '', 'Targeting -> Mirror Image (Explosionation)');

UPDATE `creature_template` SET `ScriptName`='npc_explosionation_clone' WHERE `entry`=45144;
UPDATE `gameobject_template` SET `data0`=84294 WHERE `entry`=205394;

DELETE FROM `creature_text` WHERE `entry`=44860;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44860,0,0,'Whoa... easy, now.',12,0,100,1,0,0,'Comment'),
(44860,1,0,'Quick, $n! Into the chests!',14,0,100,1,0,0,'Comment'),
(44860,2,0,'You\'d be surprised how often that works.',12,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_summoned_pygmy' WHERE `entry`=50702;
UPDATE `creature_template` SET `ScriptName`='npc_harrison_mule' WHERE `entry`=45140;

DELETE FROM `conditions` WHERE `SourceEntry` = '94651';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 94651, 0, 0, 31, 0, 3, 45140, 0, 0, 0, '', 'Targeting -> Harrison Mule');

UPDATE `creature_template` SET `VehicleId`=1081 WHERE `entry`=45135;
UPDATE `spell_target_position` SET `target_position_x`=-8948.59, `target_position_y`=-1546.67, `target_position_z`=97.55, `target_orientation`=0.01 WHERE `id`=84294 AND `effIndex`=0;
UPDATE `creature_template` SET `ScriptName`='npc_harrison_jones_explosionation' WHERE `entry`=44860;

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27141';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5423, 27141, 27196, 1, 66, 11);

DELETE FROM `creature` WHERE `guid` IN (712256, 164121);
DELETE FROM `creature_addon` WHERE `guid` IN (712256, 164121);

UPDATE `creature_template_addon` SET `auras`='49415 29266' WHERE `entry`=45186;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27993';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5455, 27993, 27141, 1, 66, 11);

UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=2 WHERE `Id`=27141;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735256;
UPDATE `creature_template_addon` SET `auras`='49415' WHERE `entry`=45180;
UPDATE `creature_template` SET `ScriptName`='npc_explosionation_expl_dummy' WHERE `entry`=28960;
UPDATE `quest_template` SET `PrevQuestId`='27141' WHERE `Id`=27176;

DELETE FROM `creature_questrelation` WHERE `quest` = '27179' AND `id` = '45186';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(45186, 27179);

UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=45186;
UPDATE `quest_template` SET `PrevQuestId`='27141' WHERE `Id`=27179;

-- Mangy Hyena
SET @ENTRY := 45202;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,8000,12000,12000,11,85415,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Mangle"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,7,27187,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Add Quest ");

DELETE FROM `creature_involvedrelation` WHERE `quest` = '27187' AND `id` IN (45180, 45296, 47684);
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(45180, 27187),
(45296, 27187),
(47684, 27187);

DELETE FROM `creature_text` WHERE `entry`=45180;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45180,0,0,'Let\'s go, $n. Stay close.',12,0,100,0,0,0,'Comment'),
(45180,1,0,'Stay alert, $n. There\'s no telling what we might run into down here...',12,0,100,0,0,0,'Comment'),
(45180,2,0,'Watch your step!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_harrison_jones_ots' WHERE `entry`=45180;

DELETE FROM `script_waypoint` WHERE `entry` = '45180';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(45180, 0, -9152.71, -1531.88, 71.22, 'Harrison Jones 00 WP');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735255;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27196';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5431, 27196, 27669, 1, 66, 11);

UPDATE `quest_template` SET `PrevQuestId`='27511' WHERE `Id`=28602;

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (6288, 6286, 6284);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6288, 'at_quest_tod'),
(6286, 'at_quest_tod'),
(6284, 'at_quest_tod');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27511;

DELETE FROM `creature_template_addon` WHERE `entry` IN (45136, 45138, 45121, 45135, 45159);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(45136, 1, '60191'),
(45138, 1, '60191'),
(45121, 1, '60191'),
(45135, 1, '60191'),
(45159, 1, '60191');

UPDATE `creature_template` SET `unit_flags`=0, `dynamicflags`=0 WHERE `entry`=45765;
UPDATE `quest_template` SET `PrevQuestId`='27196' WHERE `Id` IN (27517, 27541);
DELETE FROM `creature_questrelation` WHERE `id`=45296 AND `quest`=28602;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12058 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12058 AND `id`=1;

DELETE FROM `conditions` WHERE `SourceGroup`=12058 AND `SourceEntry` IN (0, 1);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12058, 0, 0, 0, 9, 0, 27541, 0, 0, 0, 0, 0, '', 'Schnottz Scout - Show gossip only if quest 27541 is active'),
(15, 12058, 1, 0, 0, 9, 0, 27541, 0, 0, 0, 0, 0, '', 'Schnottz Scout - Show gossip only if quest 27541 is active');

-- Schnottz Scout
SET @ENTRY := 45874;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,12058,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Schnottz Scout - On gossip option select - Close gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,56,61930,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Schnottz Scout - Scout journal"),
(@ENTRY,@SOURCETYPE,2,3,62,0,100,0,12058,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Schnottz Scout - On gossip option select - Close gossip"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,56,61929,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Schnottz Scout - Scout spectacles");

UPDATE `quest_template` SET `PrevQuestId`='27549' WHERE `Id`=27431;

SET @CGUID := 840773;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+20;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45949, 1, 1, 1, 0, 1, -9231.03, -1508.72, -169.261, 6.26988, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+1, 45949, 1, 1, 1, 0, 1, -9279.4, -1512.3, -169.261, 6.09631, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+2, 45949, 1, 1, 1, 0, 1, -9313.24, -1579, -169.26, 0.903255, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+3, 45949, 1, 1, 1, 0, 1, -9285.06, -1600.74, -170.91, 2.251, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+4, 45949, 1, 1, 1, 0, 1, -9257.4, -1593.93, -169.245, 2.71438, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+5, 45949, 1, 1, 1, 0, 1, -9201.86, -1604.91, -170.91, 5.14912, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+6, 45949, 1, 1, 1, 0, 1, -9211.46, -1554.22, -169.252, 4.03071, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+7, 45949, 1, 1, 1, 0, 1, -9196.46, -1524.53, -170.91, 2.40101, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+8, 45949, 1, 1, 1, 0, 1, -9375.82, -1559.61, -170.91, 4.47524, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+9, 45949, 1, 1, 1, 0, 1, -9340.26, -1499.18, -172.559, 5.61564, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+10, 45949, 1, 1, 1, 0, 1, -9233.21, -1691.99, -170.91, 3.28773, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+11, 45949, 1, 1, 1, 0, 1, -9218.51, -1380.03, -169.215, 0.544332, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+12, 45949, 1, 1, 1, 0, 1, -9286.08, -1389.79, -169.26, 0.642506, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+13, 45949, 1, 1, 1, 0, 1, -9308.99, -1718.54, -169.26, 5.09729, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+14, 45949, 1, 1, 1, 0, 1, -9284.75, -1663.59, -170.488, 4.65825, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+15, 45949, 1, 1, 1, 0, 1, -9181.86, -1627.2, -172.559, 2.1599, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+16, 45949, 1, 1, 1, 0, 1, -9126.47, -1622.95, -170.91, 5.5214, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+17, 45949, 1, 1, 1, 0, 1, -9144.43, -1541.19, -170.91, 5.7421, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+18, 45949, 1, 1, 1, 0, 1, -9186.52, -1477.59, -172.559, 0.275726, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+19, 45949, 1, 1, 1, 0, 1, -9243.14, -1481.85, -172.559, 5.93216, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+20, 45949, 1, 1, 1, 0, 1, -9280.09, -1474.02, -172.559, 4.29696, 120, 0, 0, 26841, 0, 0, 0, 0, 0);

UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE `id`=45949;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `id`=205582;

-- Suspended Starlight
SET @ENTRY := 205582;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,45949,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Protector");

DELETE FROM `gameobject_loot_template` WHERE `entry` = '34726';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(34726, 61376, -100, 1, 0, 1, 1);

-- Indentured Protector
SET @ENTRY := 45949;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,91856,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,91856,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw"),
(@ENTRY,@SOURCETYPE,5,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model"),
(@ENTRY,@SOURCETYPE,6,7,9,1,100,0,30,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Throw Range"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Throw Range"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,0,0,10,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Throw Range"),
(@ENTRY,@SOURCETYPE,9,10,61,1,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model when not in Throw Range"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Throw Range"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,0,11,25,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 25 Yards"),
(@ENTRY,@SOURCETYPE,12,13,61,1,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack at 25 Yards"),
(@ENTRY,@SOURCETYPE,13,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model at 25 Yards"),
(@ENTRY,@SOURCETYPE,14,15,7,1,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,15,0,61,1,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,16,0,0,1,100,0,5000,5000,13500,14200,11,86085,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Mutilate"),
(@ENTRY,@SOURCETYPE,17,0,38,0,100,0,0,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Faction Enemy"),
(@ENTRY,@SOURCETYPE,18,0,38,0,100,0,0,1,0,0,49,0,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Attack Players"),
(@ENTRY,@SOURCETYPE,19,0,7,0,100,0,0,0,0,0,2,190,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Faction"),
(@ENTRY,@SOURCETYPE,20,0,25,0,100,0,0,0,0,0,2,190,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset - Reset Faction"),
(@ENTRY,@SOURCETYPE,21,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

UPDATE `gameobject` SET `phaseMask`=2 WHERE `id` IN (205581, 205582);
UPDATE `creature` SET `phaseMask`=2 WHERE `id`=45949;
UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=735255;
UPDATE `creature` SET `phaseMask`=3 WHERE `id`=44842;

DELETE FROM `spell_script_names` WHERE `spell_id` = '85697';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(85697, 'spell_sapphire_sight');

UPDATE `creature_template` SET `VehicleId`=1096 WHERE `entry`=45281;

DELETE FROM `gameobject_loot_template` WHERE `entry` = '39345';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(39345, 66964, 5),
(39345, 66920, 3),
(39345, 67052, 3),
(39345, 66987, 2),
(39345, 67050, 2),
(39345, 66967, 2),
(39345, 67117, 2),
(39345, 67051, 1.4),
(39345, 66965, 1.4),
(39345, 67118, 1.4),
(39345, 66924, 1.4),
(39345, 66986, 1.4),
(39345, 66966, 0.7),
(39345, 66919, 0.7);

-- Harrison Jones
SET @ENTRY := 45296;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `VehicleId`=1225, `InhabitType`=4, `flags_extra`=128 WHERE `entry`=45723;
UPDATE `creature_template` SET `VehicleId`=1226, `InhabitType`=4, `flags_extra`=128 WHERE `entry`=45724;
UPDATE `creature_template` SET `VehicleId`=1139, `InhabitType`=4, `flags_extra`=128 WHERE `entry`=45722;
UPDATE `creature_template` SET `VehicleId`=1140, `InhabitType`=4, `flags_extra`=128 WHERE `entry`=45725;
UPDATE `creature_template` SET `VehicleId`=1144, `InhabitType`=4, `flags_extra`=128 WHERE `entry`=45726;
UPDATE `creature_template` SET `VehicleId`=1141, `InhabitType`=4, `flags_extra`=128 WHERE `entry`=45727;
UPDATE `creature_template` SET `VehicleId`=1143, `InhabitType`=4, `flags_extra`=128 WHERE `entry`=45737;
UPDATE `creature_template` SET `VehicleId`=1167, `flags_extra`=128 WHERE `entry`=46099;
UPDATE `creature_template` SET `VehicleId`=1121, `flags_extra`=128 WHERE `entry`=45590;
UPDATE `creature_template` SET `VehicleId`=1169, `flags_extra`=128 WHERE `entry`=46111;
UPDATE `creature_template` SET `VehicleId`=1169, `flags_extra`=128 WHERE `entry`=46116;

UPDATE `creature_template` SET `ScriptName`='npc_harrison_jones_cots' WHERE `entry`=45296;
UPDATE `creature_template` SET `ScriptName`='npc_harrison_jones_camera_cots' WHERE `entry`=45737;

DELETE FROM `creature_text` WHERE `entry`=45505;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45505,0,0,'Just stand back, $n. We wouldn\'t want you getting hurt. ',12,0,100,1,0,0,'Comment');

DELETE FROM `spell_target_position` WHERE `id` = '85018';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(85018, 1, -9185.50, -1553.50, -172.47, 3.12);

UPDATE `creature_template` SET `ScriptName`='npc_harrison_jones_cots_summon' WHERE `entry`=45505;

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (44842, 45316);
UPDATE `spell_target_position` SET `target_position_x`=-9159.50, `target_position_y`=-1457.26, `target_position_z`=-107.80, `target_orientation`=4.88 WHERE `id`=85312 AND `effIndex`=0;

DELETE FROM `conditions` WHERE `SourceEntry` = '85051';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85051, 0, 0, 31, 0, 3, 28960, 0, 0, 0, '', 'Targeting -> Rope Bunny');

DELETE FROM `conditions` WHERE `SourceEntry` = '85323';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85323, 0, 0, 31, 0, 3, 28960, 0, 0, 0, '', 'Targeting -> Harrison');

DELETE FROM `conditions` WHERE `SourceEntry` = '85333';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85333, 0, 0, 31, 0, 3, 45727, 0, 0, 0, '', 'Targeting -> Statue Head');

DELETE FROM `conditions` WHERE `SourceEntry` = '85912';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 85912, 0, 0, 31, 0, 3, 46120, 0, 0, 0, '', 'Targeting -> Mirror');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=184192;
UPDATE `creature` SET `phaseMask`=3 WHERE `id` = '45316';
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (712254, 712255, 712258, 712259);
UPDATE `spell_target_position` SET `target_orientation`=3.83 WHERE `id`=85019 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=2.40 WHERE `id`=85885 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=0.69 WHERE `id`=85895 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_orientation`=5.55 WHERE `id`=85907 AND `effIndex`=0;

DELETE FROM `creature_template_addon` WHERE `entry` IN (46115, 46110, 46097, 45507);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(46115, 1, '83702'),
(46110, 1, '83702'),
(46097, 1, '83702'),
(45507, 1, '83702');

UPDATE `creature` SET `phaseMask`=4 WHERE `guid`=184208;
UPDATE `creature_template` SET `ScriptName`='npc_player_clone_cots' WHERE `entry`=46120;
UPDATE `gameobject` SET `phaseMask`=8, `spawntimesecs`=120 WHERE `id` IN (205883, 205887);
UPDATE `creature` SET `phaseMask`=11 WHERE `guid`=735255;
UPDATE `gameobject` SET `phaseMask`=11 WHERE `id`=205888;
UPDATE `gameobject` SET `phaseMask`=8 WHERE `guid` IN (77766, 727977, 728034);

UPDATE `creature_template` SET `scale`=3 WHERE `entry` IN (46129, 46127, 46129, 46126, 46128);

DELETE FROM `creature_template_addon` WHERE `entry` IN (46128, 46127, 46129, 46126, 46128);

SET @CGUID := 840809;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+60;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+1, 46126, 1, 1, 8, 0, 0, -9410.55, -1483.27, -170.189, 1.32473, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+2, 46126, 1, 1, 8, 0, 0, -9389.08, -1464.49, -170.91, 3.69035, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+3, 46126, 1, 1, 8, 0, 0, -9363.75, -1461.79, -170.91, 2.82563, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+4, 46126, 1, 1, 8, 0, 0, -9340.85, -1476.36, -172.559, 2.52639, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+5, 46126, 1, 1, 8, 0, 0, -9120.33, -1438.72, -170.533, 4.49774, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+6, 46126, 1, 1, 8, 0, 0, -9317.1, -1409.9, -170.91, 1.06398, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+7, 46126, 1, 1, 8, 0, 0, -9333.41, -1423.57, -170.72, 6.20913, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+8, 46126, 1, 1, 8, 0, 0, -9362.94, -1421.38, -170.909, 6.20913, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+10, 46126, 1, 1, 8, 0, 0, -9382.17, -1425.45, -170.909, 1.4072, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+11, 46126, 1, 1, 8, 0, 0, -9385.04, -1440.78, -170.909, 0.373619, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+12, 46126, 1, 1, 8, 0, 0, -9400.45, -1442.48, -170.909, 4.81897, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+13, 46126, 1, 1, 8, 0, 0, -9402.81, -1426.38, -170.909, 5.77716, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+14, 46126, 1, 1, 8, 0, 0, -9415.37, -1419.42, -169.23, 4.36972, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+15, 46126, 1, 1, 8, 0, 0, -9406.26, -1393.9, -169.239, 4.36972, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+16, 46126, 1, 1, 8, 0, 0, -9400.95, -1379.15, -169.177, 3.20184, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+17, 46126, 1, 1, 8, 0, 0, -9376.22, -1389.93, -169.221, 2.03316, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+18, 46126, 1, 1, 8, 0, 0, -9361.21, -1413.88, -170.91, 2.4667, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+19, 46126, 1, 1, 8, 0, 0, -9332.46, -1419.26, -170.862, 3.27959, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+20, 46129, 1, 1, 8, 0, 0, -9120.44, -1410.92, -170.91, 4.31003, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+21, 46129, 1, 1, 8, 0, 0, -9111.74, -1389.79, -169.11, 6.00257, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+22, 46129, 1, 1, 8, 0, 0, -9133.25, -1396.02, -169.142, 0.866064, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+23, 46129, 1, 1, 8, 0, 0, -9152.53, -1414.45, -170.91, 0.159205, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+24, 46129, 1, 1, 8, 0, 0, -9163.13, -1417.66, -170.91, 0.857424, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+25, 46129, 1, 1, 8, 0, 0, -9169.32, -1438.11, -170.796, 1.56036, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+26, 46129, 1, 1, 8, 0, 0, -9169.52, -1457.04, -170.73, 2.44314, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+27, 46129, 1, 1, 8, 0, 0, -9155.25, -1468.9, -170.91, 2.77537, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+28, 46129, 1, 1, 8, 0, 0, -9142.16, -1473.84, -170.91, 3.47359, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+29, 46129, 1, 1, 8, 0, 0, -9121.26, -1464.67, -170.91, 4.05557, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+30, 46129, 1, 1, 8, 0, 0, -9103.44, -1441.55, -169.22, 4.05557, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+31, 46129, 1, 1, 8, 0, 0, -9098.04, -1409.04, -169.111, 4.96035, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+32, 46129, 1, 1, 8, 0, 0, -9103.04, -1398.55, -169.165, 0.436454, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+33, 46129, 1, 1, 8, 0, 0, -9118.8, -1406.85, -170.909, 1.15352, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+34, 46129, 1, 1, 8, 0, 0, -9123.07, -1417.79, -170.909, 2.90653, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+35, 46127, 1, 1, 8, 0, 0, -9121.34, -1701.91, -170.646, 0.335137, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+36, 46127, 1, 1, 8, 0, 0, -9139.56, -1707.57, -169.257, 5.55411, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+37, 46127, 1, 1, 8, 0, 0, -9156.4, -1694.76, -170.91, 6.22091, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+38, 46127, 1, 1, 8, 0, 0, -9173.16, -1693.64, -170.91, 5.3177, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+39, 46127, 1, 1, 8, 0, 0, -9180.31, -1682.37, -170.883, 3.11937, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+40, 46127, 1, 1, 8, 0, 0, -9166.7, -1680.81, -170.909, 3.88357, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+41, 46127, 1, 1, 8, 0, 0, -9157.58, -1664.39, -170.909, 4.64933, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+42, 46127, 1, 1, 8, 0, 0, -9156.98, -1654.82, -170.909, 3.2199, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+43, 46127, 1, 1, 8, 0, 0, -9139.16, -1659.09, -170.909, 2.46749, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+44, 46127, 1, 1, 8, 0, 0, -9125.03, -1671.06, -170.909, 2.07479, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+45, 46127, 1, 1, 8, 0, 0, -9117.88, -1684.3, -170.909, 0.871562, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+46, 46127, 1, 1, 8, 0, 0, -9124, -1691.58, -170.909, 3.13665, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+47, 46128, 1, 1, 8, 0, 0, -9378.73, -1658.04, -170.909, 0.10502, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+48, 46128, 1, 1, 8, 0, 0, -9372.56, -1647.12, -170.91, 4.06579, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+49, 46128, 1, 1, 8, 0, 0, -9366.77, -1637.11, -170.91, 4.39095, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+50, 46128, 1, 1, 8, 0, 0, -9365.5, -1624.81, -170.91, 6.00809, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+51, 46128, 1, 1, 8, 0, 0, -9381.23, -1624.7, -170.91, 0.441186, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+52, 46128, 1, 1, 8, 0, 0, -9385.57, -1634.6, -170.91, 1.66405, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+53, 46128, 1, 1, 8, 0, 0, -9389.01, -1645.36, -170.91, 1.02081, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+54, 46128, 1, 1, 8, 0, 0, -9394.79, -1655.27, -170.91, 1.88789, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+55, 46128, 1, 1, 8, 0, 0, -9387.75, -1666.05, -170.91, 2.52878, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+56, 46128, 1, 1, 8, 0, 0, -9376.18, -1673.55, -170.91, 2.50521, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+57, 46128, 1, 1, 8, 0, 0, -9367.48, -1673.77, -170.91, 3.50895, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+58, 46128, 1, 1, 8, 0, 0, -9354.61, -1667.44, -170.819, 4.14198, 120, 0, 0, 26841, 0, 0, 0, 0, 0),
(@CGUID+59, 46128, 1, 1, 8, 0, 0, -9357.22, -1655.37, -170.808, 3.82312, 120, 0, 0, 26841, 0, 0, 0, 0, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27669' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27669, 27627, 0),
(20, 8, 27669, 27624, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27669' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27669, 27627, 0),
(19, 8, 27669, 27624, 0);

DELETE FROM `creature_questrelation` WHERE `id` = '45296' AND `quest` = '27627';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(45296, 27627);

DELETE FROM `creature_involvedrelation` WHERE `id` = '45296' AND `quest` = '27627';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(45296, 27627);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27627;

DELETE FROM `creature_text` WHERE `entry`=45949;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45949,0,0,'Your theft is forbitten, trespasser!',12,0,100,0,0,0,'Comment'),
(45949,0,1,'I welcome you into an eternity of service, thief.',12,0,100,0,0,0,'Comment'),
(45949,0,2,'We have sworn to serve, intruder. And so shall you.',12,0,100,0,0,0,'Comment'),
(45949,0,3,'Once a thief, I am now a servant of the Stars.',12,0,100,0,0,0,'Comment'),
(45949,0,4,'You tread on sacred ground! You must be purified!',12,0,100,0,0,0,'Comment'),
(45949,0,5,'Those who behold the starlight must forever protect it!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45275;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45275,0,0,'Alright, $n, Time to see what this staff of yours has to show us.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_harrison_jones_btlos' WHERE `entry`=45275;
UPDATE `creature_template` SET `VehicleId`=1099, `ScriptName`='npc_camera_bunny_btlos' WHERE `entry`=45309;
UPDATE `creature_template` SET `ScriptName`='npc_staff_bunny_btlos' WHERE `entry`=45281;

DELETE FROM `spell_target_position` WHERE `id` = '84600';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(84600, 1, -9185.50, -1553.50, -172.47, 3.12);

UPDATE `creature` SET `phaseMask`=4 WHERE `id`=45319;
UPDATE `creature` SET `phaseMask`=4 WHERE `guid` IN (735638,735625,735661,735621,735660);
UPDATE `creature_addon` SET `auras`='76651 94657 84702' WHERE `guid` IN (735638,735625,735661,735621);

DELETE FROM `conditions` WHERE `SourceEntry` = '84703';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 84703, 0, 0, 31, 0, 3, 45281, 0, 0, 0, '', 'Targeting -> Staff');

DELETE FROM `conditions` WHERE `SourceEntry` = '84681';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 84681, 0, 0, 31, 0, 3, 45281, 0, 0, 0, '', 'Targeting -> Staff');

DELETE FROM `conditions` WHERE `SourceEntry` = '84602';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 84602, 0, 0, 29, 200, 3, 45319, 0, 0, 0, '', 'Targeting -> Staff');

UPDATE `creature` SET `phaseMask`=5 WHERE `guid` IN (164124, 164123, 164120, 164119);
UPDATE `creature_template_addon` SET `auras`='76651 84758' WHERE `entry`=45319;
UPDATE `creature_template_addon` SET `auras`='83702 60191' WHERE `entry` IN (45507, 46097, 46110, 46115);
UPDATE `creature_template` SET `ScriptName`='npc_uldum_watcher' WHERE `entry`=45316;
UPDATE `gameobject` SET `position_z`=-178.75 WHERE `guid`=77745;
UPDATE `creature_template` SET `VehicleId`=1099, `ScriptName`='npc_orb_of_the_stars_camera' WHERE `entry`=46289;

DELETE FROM `spell_script_names` WHERE `spell_id` = '89314';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89314, 'spell_orb_of_the_stars');

UPDATE `gameobject` SET `phaseMask`=16 WHERE `guid` IN (77718, 77745);
UPDATE `creature` SET `phaseMask`=16 WHERE `guid`=735637;
UPDATE `gameobject` SET `phaseMask`=16 WHERE `id`=206419;
UPDATE `creature` SET `phaseMask`=16 WHERE `id` IN (46195, 46196, 46197, 46198);
UPDATE `creature` SET `phaseMask`=16 WHERE `guid`=184257;
UPDATE `spell_target_position` SET `target_position_x`=-9195.29, `target_position_y`=-1553.90, `target_position_z`=-121.02, `target_orientation`=3.11 WHERE `id`=86268 AND `effIndex`=0;
UPDATE `gameobject` SET `phaseMask`=17 WHERE `guid`=77717;

DELETE FROM `spell_area` WHERE `spell` = '98433' AND `quest_start` = '27669';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(98433, 5423, 27669, 27669, 1, 2);

DELETE FROM `creature_text` WHERE `entry`=48045;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48045,0,0,'I\'m going to need to research what we\'ve learned here, $n.',12,0,100,1,0,0,'Comment'),
(48045,1,0,'There\'s no telling how we might use the power these mechanisms create.',12,0,100,1,0,0,'Comment'),
(48045,2,0,'Meet me in Ramkahen and I\'ll tell you what our next step should be.',12,0,100,1,0,0,'Comment'),
(48045,3,0,'See ya around, kid.',12,0,100,1,0,0,'Comment');

-- Harrison Jones
SET @ENTRY := 48045;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,48045,0,0,1,1,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,48045,0,0,1,2,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,2,48045,0,0,1,3,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,3,48045,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Run"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,3,48045,0,0,69,1,0,0,0,0,0,8,0,0,0,-9480.65,-1461.71,72.77,2.33,"After Talk 3 - Move To Pos"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,48045,0,0,41,7000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Despawn");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735663;

DELETE FROM `spell_target_position` WHERE `id` = '89360';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(89360, 1, -9426.71, -1516.31, 67.72, 2.67);

UPDATE `quest_template` SET `PrevQuestId`='27899' WHERE `Id`=27901;
UPDATE `quest_template` SET `PrevQuestId`='27903' WHERE `Id`=27905;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27899';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5597, 27899, 27905, 1, 66, 11);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=14.879 WHERE `entry`=46993 AND `item`=62768;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735666;
UPDATE `creature` SET `position_x`=-10388.23, `position_y`=-283.26, `position_z`=336.59, `orientation`=0.51, `spawntimesecs`=120 WHERE `guid`=12;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=11;
UPDATE `quest_template` SET `PrevQuestId`='27969' WHERE `Id`=28002;

DELETE FROM `creature_addon` WHERE `guid` = '12';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(12, 1, '87541 49414');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735664;

DELETE FROM `spell_script_names` WHERE `spell_id` = '87623';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87623, 'spell_activate_guardian');

-- Titanic Guardian
SET @ENTRY := 47032;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `ScriptName`='npc_titanic_guardian' WHERE `entry`=47032;

DELETE FROM `creature_text` WHERE `entry`=47058;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47058,0,0,'Use the meteor to launch a critical attack on the Titanic Guardian!',41,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_titanic_guardian_meteor', `InhabitType`=4 WHERE `entry`=47058;

DELETE FROM `spell_target_position` WHERE `id` = '87694';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(87694, 1, -10455.94, -470.50, 277.50, 1.45);

UPDATE `creature_template_addon` SET `auras`='87645' WHERE `entry`=47065;

DELETE FROM `conditions` WHERE `SourceEntry` = '87665';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 87665, 0, 0, 31, 0, 3, 47047, 0, 0, 0, '', 'Targeting -> Burning Gaze Summon');

UPDATE `creature_template` SET `modelid1`=37565, `InhabitType`=4, `unit_flags`=0, `unit_flags2`=2048, `flags_extra`=128 WHERE `entry`=50401;
UPDATE `creature_template` SET `VehicleId`=1423, `ScriptName`='npc_ignition_camera_event' WHERE `entry`=50392;
UPDATE `creature_template` SET `scale`=1.5, `flags_extra`=0 WHERE `entry`=50401;

-- Titan Mechanism
SET @ENTRY := 50401;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,0,0,0,0,11,87822,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Cast Fiery Explosion"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,0,0,0,0,85,93941,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Summon Camera"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,0,0,0,0,11,87817,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Lens Effect");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=47037;
UPDATE `gossip_menu_option` SET `menu_id`=12212, `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12211 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12214 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12217 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12220 AND `id`=0;

-- Ambassador Laurent
SET @ENTRY := 47176;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12212,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12212,0,0,0,33,47176,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Budding Artist
SET @ENTRY := 47187;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12217,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12217,0,0,0,33,47187,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip");

-- Refined Gentleman
SET @ENTRY := 47185;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12214,0,0,0,33,47185,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12214,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip");

-- Aspiring Starlet
SET @ENTRY := 47189;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12220,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12220,0,0,0,33,47189,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735270;
UPDATE `quest_template` SET `PrevQuestId`='28002' WHERE `Id`=27990;
UPDATE `quest_template` SET `PrevQuestId`='27950' WHERE `Id`=27969;
UPDATE `quest_template` SET `PrevQuestId`='27926' WHERE `Id`=27939;

UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=25 WHERE `guid`=181364;

-- Desert Fox
SET @ENTRY := 47201;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,31,0,100,0,87963,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Despawn"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,4000,4000,4000,4000,89,50,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Random Move"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,2000,2000,2000,2000,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Run");

UPDATE `creature_template` SET `speed_walk`=3 WHERE `entry`=47201;

DELETE FROM `spell_script_names` WHERE `spell_id` = '87996';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87996, 'spell_fire_lpac');

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry` IN (47216, 47213, 47207, 47219);

-- Dead Trooper
SET @ENTRY := 47216;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,56,62789,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,28,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Aura"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,75,87983,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Uniform"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,5,0,11,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,6,0,11,0,100,0,0,0,0,0,75,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Add Kit"),
(@ENTRY,@SOURCETYPE,7,0,64,0,100,0,0,0,0,0,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Despawn");

-- Dead Trooper
SET @ENTRY := 47207;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,56,62789,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,28,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Aura"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,75,87983,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Uniform"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,5,0,11,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,6,0,11,0,100,0,0,0,0,0,75,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Add Kit"),
(@ENTRY,@SOURCETYPE,7,0,64,0,100,0,0,0,0,0,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Despawn");

-- Dead Trooper
SET @ENTRY := 47213;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,56,62789,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,28,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Aura"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,75,87983,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Uniform"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,5,0,11,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,6,0,11,0,100,0,0,0,0,0,75,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Add Kit"),
(@ENTRY,@SOURCETYPE,7,0,64,0,100,0,0,0,0,0,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Despawn");

-- Dead Trooper
SET @ENTRY := 47219;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,56,62789,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,28,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Aura"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,75,87983,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove Uniform"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,5,0,11,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,6,0,11,0,100,0,0,0,0,0,75,85500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Add Kit"),
(@ENTRY,@SOURCETYPE,7,0,64,0,100,0,0,0,0,0,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Despawn");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27950;

DELETE FROM `creature_involvedrelation` WHERE `id` = '47159' AND `quest` = '27950';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(47159, 27950);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12213';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12213, 'The perimeter is secure, commander.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=12213 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12213, 0, 0, 0, 9, 0, 27950, 0, 0, 0, 0, 0, '', 'Commander Schnottz - Show gossip only if quest 27950 is active');

UPDATE `gameobject` SET `phaseMask`=16 WHERE `id`=206571;

DELETE FROM `creature_text` WHERE `entry`=47957;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47957,0,0,'Very vell, zhen. Let me just check my notes vone lasht time...',12,0,100,1,0,0,'Comment'),
(47957,1,0,'Mmm-hmm, yes, yes... simple enough...',12,0,100,1,0,0,'Comment'),
(47957,2,0,'Oh, Gobbles! Ve\'re ready to begin! Come, come!',14,0,100,1,0,0,'Comment'),
(47957,3,0,'Hold on, Gobbles! Shtand back everyvone!',12,0,100,1,0,0,'Comment'),
(47957,4,0,'VHAT!?',14,0,100,1,0,0,'Comment'),
(47957,5,0,'My poor Gobbles...',12,0,100,1,0,0,'Comment'),
(47957,6,0,'Vhat could haf possibly gone wrong? I followed every last detail...',14,0,100,1,0,0,'Comment'),
(47957,7,0,'Vait a shekkont! Vhat\'s zhis!?',12,0,100,1,0,0,'Comment'),
(47957,8,0,'You only brought me eight idols!',14,0,100,1,0,0,'Comment'),
(47957,9,0,'Zhe ritual specifically calls for NINE!!',14,0,100,1,0,0,'Comment'),
(47957,10,0,'NINE! NINE! NINE! NINE! NINE!!!',14,0,100,1,0,0,'Comment'),
(47957,11,0,'Out of my sight, vizh you! Auch...',14,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_commander_schnottz' WHERE `entry`=47957;
UPDATE `spell_target_position` SET `target_position_x`=-10682.79, `target_position_y`=926.52, `target_position_z`=26.23, `target_orientation`=3.31 WHERE `id`=89178 AND `effIndex`=0;

-- Gobbles
SET @ENTRY := 47255;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-10690.8,924.79,26.56,3.3,"On Just Summoned - Move to Pos"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,88119,1,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Turkey!");

-- Commander Schnottz
SET @ENTRY := 47159;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12213,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12213,0,0,0,85,89178,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Commander Schnottz");

UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=27950;
UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=120 WHERE `id`=47292;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12238 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12238 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12238, 0, 0, 0, 9, 0, 27969, 0, 0, 0, 0, 0, '', 'Slacking Laborer - Show gossip only if quest 27969 is active');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '88236';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(88236, 88210, 'Trooper Uniform -> Force Reaction');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '88210';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(88210, 88235, 'Trooper Uniform -> Force Reaction');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-88210';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-88210, -88235, 'Trooper Uniform -> Force Reaction');

DELETE FROM `creature_text` WHERE `entry`=47292;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47292,0,0,'I\'m not working for that maniac anymore!',12,0,100,1,0,0,'Comment'),
(47292,0,1,'I have a message for you to deliver to that tyrant!',12,0,100,1,0,0,'Comment'),
(47292,0,2,'I can\'t believe I fell for Schnottz\'s lies! I\'m out of here!',12,0,100,1,0,0,'Comment'),
(47292,0,3,'I haven\'t been paid since I got here! I\'m through with this place!',12,0,100,1,0,0,'Comment'),
(47292,0,4,'I\'m done working in this heat!',12,0,100,1,0,0,'Comment'),
(47292,1,0,'Yeah, yeah. When aren\'t we behind schedule?',12,0,100,1,0,0,'Comment'),
(47292,1,1,'I should never have left Tanaris.',12,0,100,1,0,0,'Comment'),
(47292,1,2,'I didn\'t sign up for this...',12,0,100,1,0,0,'Comment');

-- Slacking Laborer
SET @ENTRY := 47292;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,11,14890,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Dismounting Blow on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12238,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12238,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Emote"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,12238,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,47292,0,0,33,47127,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,47292,0,0,46,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Move Forward"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,0,47292,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Despawn"),
(@ENTRY,@SOURCETYPE,7,0,62,0,100,0,12238,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Gossip"),
(@ENTRY,@SOURCETYPE,8,0,11,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Reset Flag"),
(@ENTRY,@SOURCETYPE,9,0,62,0,100,0,12238,0,0,0,28,32951,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Sleep");

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=181201;
UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (47704, 47705, 47706);

UPDATE `creature` SET `phaseMask`=2 WHERE `guid` IN
(735703, 735694, 735707, 181250, 181253, 181251, 
735821, 735833, 735842, 735811, 735817);

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '28002';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 5602, 28002, 28002, 1, 10);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12267';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12267, 'Who could have done such a thing?', 1, 1);

-- Prolific Writer
SET @ENTRY := 47461;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12267,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12267,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12267,0,0,0,33,47516,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,47461,0,0,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12269';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12269, 'Just calm down. Are you alright?', 1, 1);

DELETE FROM `creature_text` WHERE `entry`=47472;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47472,0,0,'No! Of course I\'m not alright! ',12,0,100,1,0,0,'Comment'),
(47472,1,0,'I-I\'ve never seen an actual corpse before... ',12,0,100,1,0,0,'Comment');

-- Privileged Socialite
SET @ENTRY := 47472;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12269,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12269,0,0,0,33,47519,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12269,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,47472,0,0,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=47461;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47461,0,0,'Who knows?',12,0,100,1,0,0,'Comment'),
(47461,1,0,'He was becoming quite critical of this operation, but that\'s not proof of anything.',12,0,100,1,0,0,'Comment');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12314 AND `id`=0;

-- Pretentious Businessman
SET @ENTRY := 47520;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12314,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12314,0,0,0,33,47520,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12314,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,47520,0,0,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=47520;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47520,0,0,'I\'m curious, of course, but what\'s done is done. ',12,0,100,1,0,0,'Comment'),
(47520,1,0,'We wouldn\'t want to stir up any unnecessary panic. That simply wouldn\'t be prudent! ',12,0,100,1,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=10;
UPDATE `gossip_menu_option` SET `menu_id`=12319, `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12317 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=47707;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47707,0,0,'No, but I don\'t need to have seen it to know that we\'re all going to DIE! ',12,0,100,1,0,0,'Comment'),
(47707,1,0,'Do you hear me? ',12,0,100,1,0,0,'Comment');

-- Budding Artist
SET @ENTRY := 47707;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12319,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12319,0,0,0,33,47707,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12319,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,47707,0,0,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

UPDATE `creature` SET `phaseMask`=3 WHERE `guid` IN (181272, 735270);

DELETE FROM `conditions` WHERE `SourceGroup`=12319 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12319, 0, 0, 0, 9, 0, 28002, 0, 0, 0, 0, 0, '', 'Show gossip only if quest 28002 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=12314 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12314, 0, 0, 0, 9, 0, 28002, 0, 0, 0, 0, 0, '', 'Show gossip only if quest 28002 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=12269 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12269, 0, 0, 0, 9, 0, 28002, 0, 0, 0, 0, 0, '', 'Show gossip only if quest 28002 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=12267 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12267, 0, 0, 0, 9, 0, 28002, 0, 0, 0, 0, 0, '', 'Show gossip only if quest 28002 is active');

UPDATE `creature` SET `position_z`=37.7739 WHERE `guid`=181210;
UPDATE `creature` SET `phaseMask`=1, `position_z`=23.8833 WHERE `guid`=181201;

UPDATE `creature` SET `position_z`=44.9277 WHERE `guid`=181200;
UPDATE `creature` SET `position_z`=26.0768 WHERE `guid`=181226;
UPDATE `creature` SET `position_z`=110.20 WHERE `guid`=181204;
UPDATE `creature` SET `position_z`=63.20 WHERE `guid`=181207;
UPDATE `creature` SET `position_z`=53.21 WHERE `guid`=181274;
UPDATE `creature` SET `position_z`=20 WHERE `guid`=181199;

UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`=47546;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735816;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=47734;

DELETE FROM `creature_addon` WHERE `guid` = '181209';
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(181209, 0, 0, 0, 1, 0, '49415');

DELETE FROM `creature_addon` WHERE `guid` = '735816';
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(735816, 0, 0, 0, 1, 0, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27990';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49417, 5602, 27990, 27990, 1, 10);

UPDATE `creature_template` SET `ScriptName`='npc_schnottz_siege_tank', `npcflag`=1 WHERE `entry`=47732;
UPDATE `creature_template` SET `VehicleId`=1281 WHERE `entry`=47743;
UPDATE `creature_template` SET `VehicleId`=1282 WHERE `entry`=47744;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47743';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47743, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47743';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47743, 47744, 1, 'Schnottz Siege Tank -> Turret ', 8, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=47385;
UPDATE `creature_template` SET `ScriptName`='npc_schnottz_siege_tank_summoned' WHERE `entry`=47743;
UPDATE `creature_template` SET `ScriptName`='npc_schnottz_siege_turret' WHERE `entry`=47744;
UPDATE `creature` SET `position_z`=55.21 WHERE `guid`=181274;

DELETE FROM `creature_text` WHERE `entry`=47746;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47746,0,0,'$n! Ovah he\'ah!',12,0,100,1,0,0,'Comment'),
(47746,1,0,'Ve haf engineered a shield zhat should vitzhshtand zheir eye beams.',12,0,100,1,0,0,'Comment'),
(47746,2,0,'Don\'t forget to use it!',12,0,100,1,0,0,'Comment');

-- Siege Tank Driver
SET @ENTRY := 47746;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI  " WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,3000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,47746,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,47746,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,2,47746,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Despawn");

DELETE FROM `creature_text` WHERE `entry`=47743;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47743,0,0,'Zhat's it!',42,0,100,0,0,0,'Comment'),
(47743,1,0,'Zhe scrubs vill clean up zhe rest.',42,0,100,0,0,0,'Comment'),
(47743,2,0,'Back to zhe base we go!',42,0,100,0,0,0,'Comment');

DELETE FROM `script_waypoint` WHERE `entry` = '47743';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(47743, 1, -10654.81, 1135.84, 23.95, 'Schnottz Siege Tank WP'),
(47743, 2, -10625.31, 1155.91, 23.49, 'Schnottz Siege Tank WP'),
(47743, 3, -10620.66, 1131.01, 27.46, 'Schnottz Siege Tank WP'),
(47743, 4, -10591.73, 1098.14, 30.03, 'Schnottz Siege Tank WP'),
(47743, 5, -10599.07, 1057.52, 31.56, 'Schnottz Siege Tank WP'),
(47743, 6, -10585.00, 1013.00, 34.02, 'Schnottz Siege Tank WP'),
(47743, 7, -10512.05, 1060.89, 43.49, 'Schnottz Siege Tank WP'),
(47743, 8, -10440.73, 1101.53, 48.26, 'Schnottz Siege Tank WP'),
(47743, 9, -10400.00, 1053.69, 61.40, 'Schnottz Siege Tank WP'),
(47743, 10, -10345.05, 1014.03, 68.34, 'Schnottz Siege Tank WP'),
(47743, 11, -10344.36, 936.28, 62.31, 'Schnottz Siege Tank WP'),
(47743, 12, -10297.67, 860.17, 66.15, 'Schnottz Siege Tank WP'),
(47743, 13, -10375.47, 864.59, 52.65, 'Schnottz Siege Tank WP'),
(47743, 14, -10452.21, 926.22, 42.59, 'Schnottz Siege Tank WP'),
(47743, 15, -10475.97, 915.19, 43.29, 'Schnottz Siege Tank WP'),
(47743, 16, -10511.99, 911.36, 43.12, 'Schnottz Siege Tank WP'),
(47743, 17, -10547.35, 868.46, 40.73, 'Schnottz Siege Tank WP'),
(47743, 18, -10618.84, 889.48, 33.94, 'Schnottz Siege Tank WP'),
(47743, 19, -10638.50, 891.60, 29.26, 'Schnottz Siege Tank WP'),
(47743, 20, -10593.45, 1055.39, 32.47, 'Schnottz Siege Tank WP');

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=47974;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (47743, 47744);
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85 WHERE `entry`=47744;

DELETE FROM `conditions` WHERE `SourceEntry` = '88891';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 7, 88891, 0, 0, 31, 0, 3, 47385, 0, 0, 0, '', 'Targeting -> Decrepits');

SET @CGUID := 840869;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+13;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 47385, 1, 1, 1, 0, 0, -10533.2, 1027.58, 41.431, 3.80999, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+1, 47385, 1, 1, 1, 0, 0, -10484.5, 1085.33, 42.8193, 4.18306, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+2, 47385, 1, 1, 1, 0, 0, -10426.4, 1141.46, 56.6294, 4.63937, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+3, 47385, 1, 1, 1, 0, 0, -10429, 1215.64, 69.3177, 5.62583, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+4, 47385, 1, 1, 1, 0, 0, -10520.9, 1246.64, 46.1403, 5.58027, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+5, 47385, 1, 1, 1, 0, 0, -10553.7, 1284.88, 42.2843, 0.49011, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+6, 47385, 1, 1, 1, 0, 0, -10615.8, 1267.86, 30.3978, 0.699811, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+7, 47385, 1, 1, 1, 0, 0, -10639.5, 1230.8, 21.6615, 1.63758, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+8, 47385, 1, 1, 1, 0, 0, -10634.8, 1160.67, 22.4242, 1.63758, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+9, 47385, 1, 1, 1, 0, 0, -10601.8, 1104.36, 28.42, 2.55414, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+10, 47385, 1, 1, 1, 0, 0, -10536.5, 1093.68, 40.8293, 3.49269, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+11, 47385, 1, 1, 1, 0, 0, -10451.7, 1081.81, 48.0055, 2.40648, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+12, 47385, 1, 1, 1, 0, 0, -10396.8, 1042.92, 61.1484, 3.01359, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+13, 47385, 1, 1, 1, 0, 0, -10338.4, 993.984, 71.0918, 2.4324, 30, 0, 0, 154980, 0, 0, 0, 2048, 0);

-- Decrepit Watcher
SET @ENTRY := 47385;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `ScriptName`='npc_decrepit_watcher' WHERE `entry`=47385;
UPDATE `creature_template` SET `RegenHealth`=0 WHERE `entry`=47385;
UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`=47385;
UPDATE `creature` SET `phaseMask`=1 WHERE `id`=47935;
UPDATE `creature_template_addon` SET `auras`='89150 86877' WHERE `entry`=47935;

DELETE FROM `spell_area` WHERE `spell` = '81742' AND `quest_start` = '27990';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(81742, 5602, 27990, 1, 66, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735835;

DELETE FROM `creature_addon` WHERE `guid` = '735270';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(735270, 1, '82343');

DELETE FROM `creature_template_addon` WHERE `entry` = '47193';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(47193, 1, '82343');

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=47947;
UPDATE `creature_template_addon` SET `auras`='29266 86877' WHERE `entry`=47947;

DELETE FROM `spell_area` WHERE `spell` = '90161' AND `quest_start` = '27926';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(90161, 5602, 27926, 27990, 1, 66);

UPDATE `creature` SET `phaseMask`=8 WHERE `id`=47385;

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '1';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 1, 3, 'Uldum: Add Phase 3 On Quest: Make Yourself Useful (27969)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '1' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '27969';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 1, 0, 0, 9, 0, 27969, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '2';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 2, 9, 'Uldum: Add Phase 8 On Quest: Battlezone (27990)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '2' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '27990';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 2, 0, 0, 9, 0, 27990, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '3';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 3, 17, 'Uldum: Add Phase 16 After Quest: Battlezone (27990)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '3' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '27990';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 3, 0, 0, 8, 0, 27990, 0, 0, 0, 0, 0, '', '');

DELETE FROM `spell_script_names` WHERE `spell_id` = '84474';

-- Deletes creature Decrepit Watcher (id: 47385, guid: 840879) in zone: 5034, area: 5602
DELETE FROM `creature` WHERE `guid` = 840879; DELETE FROM creature_addon WHERE guid = 840879;

-- Deletes creature Decrepit Watcher (id: 47385, guid: 735782) in zone: 5034, area: 5602
DELETE FROM `creature` WHERE `guid` = 735782; DELETE FROM creature_addon WHERE guid = 735782;

-- Deletes creature Decrepit Watcher (id: 47385, guid: 840877) in zone: 5034, area: 5602
DELETE FROM `creature` WHERE `guid` = 840877; DELETE FROM creature_addon WHERE guid = 840877;

-- Deletes creature Decrepit Watcher (id: 47385, guid: 735781) in zone: 5034, area: 5602
DELETE FROM `creature` WHERE `guid` = 735781; DELETE FROM creature_addon WHERE guid = 735781;

-- Deletes creature Decrepit Watcher (id: 47385, guid: 840880) in zone: 5034, area: 5602
DELETE FROM `creature` WHERE `guid` = 840880; DELETE FROM creature_addon WHERE guid = 840880;

-- Deletes creature Decrepit Watcher (id: 47385, guid: 840878) in zone: 5034, area: 5602
DELETE FROM `creature` WHERE `guid` = 840878; DELETE FROM creature_addon WHERE guid = 840878;

-- Deletes creature Decrepit Watcher (id: 47385, guid: 840882) in zone: 5034, area: 5602
DELETE FROM `creature` WHERE `guid` = 840882; DELETE FROM creature_addon WHERE guid = 840882;

UPDATE `creature` SET `phaseMask`=9 WHERE `guid`=735680;
UPDATE `creature` SET `phaseMask`=9 WHERE `guid`=735681;
UPDATE `creature` SET `phaseMask`=16 WHERE `id`=47546;
UPDATE `creature_template_addon` SET `auras`='88644 29266' WHERE `entry`=47546;
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=47911;

UPDATE `creature` SET `phaseMask`=2 WHERE `id`=47292;

SET @CGUID := 840882;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+3;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 47385, 1, 1, 8, 0, 0, -10475.4, 955.212, 41.7716, 3.91551, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+1, 47385, 1, 1, 8, 0, 0, -10396.3, 821.704, 56.8165, 3.06257, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+2, 47385, 1, 1, 8, 0, 0, -10310, 937.731, 65.4978, 1.28443, 30, 0, 0, 154980, 0, 0, 0, 2048, 0),
(@CGUID+3, 47385, 1, 1, 8, 0, 0, -10288.4, 1044.29, 90.6871, 3.74273, 30, 0, 0, 154980, 0, 0, 0, 2048, 0);

UPDATE `spell_area` SET `aura_spell`=-81742 WHERE `spell`=90161 AND `area`=5602 AND `quest_start`=27926 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;

SET @CGUID := 840886;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+6;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 47193, 1, 1, 32, 0, 0, -10622.9, 1034.7, 25.7107, 0.158627, 300, 0, 0, 77490, 4454, 0, 0, 0, 0),
(@CGUID+1, 47193, 1, 1, 32, 0, 0, -10625.2, 1042.61, 25.2438, 0.413882, 300, 0, 0, 77490, 4454, 0, 0, 0, 0),
(@CGUID+2, 47193, 1, 1, 32, 0, 0, -10644.2, 1040.06, 25.751, 0.27251, 300, 0, 0, 77490, 4454, 0, 0, 0, 0),
(@CGUID+3, 47193, 1, 1, 32, 0, 0, -10647.3, 1049.36, 26.1253, 0.187705, 300, 0, 0, 77490, 4454, 0, 0, 0, 0),
(@CGUID+4, 47193, 1, 1, 32, 0, 0, -10651, 1060.18, 26.2, 0.270973, 300, 0, 0, 77490, 4454, 0, 0, 0, 0),
(@CGUID+5, 47193, 1, 1, 32, 0, 0, -10653, 1053.5, 24.6655, 3.32303, 300, 0, 0, 77490, 4454, 0, 0, 0, 0),
(@CGUID+6, 47193, 1, 1, 32, 0, 0, -10654.9, 1059.73, 24.6575, 3.42123, 300, 0, 0, 77490, 4454, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (840886, 840887, 840888, 840889, 840890, 840891, 840892);
INSERT INTO `creature_addon` (`guid`, `bytes2`) VALUES
(840886, 1),
(840887, 1),
(840888, 1),
(840889, 1),
(840890, 1),
(840891, 1),
(840892, 1);

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '4';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 4, 32, 'Uldum: Add Phase 32 After Quest: Missed Me By Zhat Much (28187)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '4' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '28187';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 4, 0, 0, 9, 0, 28187, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '5';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 5, 1, 4, 'Uldum: Negate Phase 1 After Quest: Missed Me By Zhat Much (28187)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '5' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '28187';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 5, 0, 0, 9, 0, 28187, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=33 WHERE `id`=47935;
UPDATE `creature` SET `phaseMask`=33 WHERE `guid` IN (735840, 735828, 735835);
UPDATE `creature` SET `phaseMask`=32 WHERE `guid` IN (735819, 735820, 735838);

DELETE FROM `spell_area` WHERE `spell` = '98392' AND `quest_start` = '28187';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(98392, 5602, 28187, 1, 66, 0);

DELETE FROM `spell_area` WHERE `spell` = '94570' AND `quest_start` = '28187';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(94570, 5602, 28187, 1, 66, 0);

-- Commander Schnottz
SET @ENTRY := 47940;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `script_waypoint` WHERE `entry` = '47940';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(47940, 1, -10678.33, 949.10, 25.19, 'Commander Schnottz WP'),
(47940, 2, -10653.38, 998.59, 27.33, 'Commander Schnottz WP'),
(47940, 3, -10652.46, 1022.37, 24.26, 'Commander Schnottz WP'),
(47940, 4, -10657.82, 1054.87, 24.26, 'Commander Schnottz WP'),
(47940, 5, -10646.26, 1059.21, 26.19, 'Commander Schnottz WP'),
(47940, 6, -10637.89, 1046.02, 25.88, 'Commander Schnottz WP');

DELETE FROM `creature_text` WHERE `entry`=47940;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47940,0,0,'Auch! Zhis is an outrage!',12,0,100,0,0,0,'Comment'),
(47940,1,0,'You take a group of miserable bandits, make them part of somethink historical, and zhis is vhat you get?',12,0,100,0,0,0,'Comment'),
(47940,2,0,'I am goink to find out who is behind zhis treachery, and you are goink to help me!',12,0,100,0,0,0,'Comment'),
(47940,3,0,'Zhis vork is bigger than you or me... Bigger zhan anyvone knows!',12,0,100,0,0,0,'Comment'),
(47940,4,0,'Zhese vould-be assassins don\'t know who zhey are meddling vizh!',12,0,100,0,0,0,'Comment'),
(47940,5,0,'Soon, zhey shall learn.. and vhen zhey do, zhey will tremble!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_commander_schnottz_awake' WHERE `entry`=47940;

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '6';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 6, 32, 'Uldum: Add Phase 32 After Quest Complete: Missed Me By Zhat Much (28187)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '6' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28187';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 6, 0, 0, 28, 0, 28187, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '7';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 7, 32, 'Uldum: Add Phase 32 After Quest Rewarded: Missed Me By Zhat Much (28187)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '7' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28187';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 7, 0, 0, 8, 0, 28187, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=2 WHERE `guid` IN
(181261, 181258, 181257, 181255, 181256, 181255, 735842, 
735811, 735836, 181259, 181254, 735817, 735825, 735807,
735821, 735833, 735841, 735805, 735823);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (735271, 735667);
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=47562;
UPDATE `creature_template` SET `ScriptName`='npc_harrison_jones_tailgunner' WHERE `entry`=46978;
UPDATE `creature_template` SET `VehicleId`=1234 WHERE `entry`=47055;

UPDATE `creature_template_addon` SET `auras`='49414' WHERE `entry`=47092;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47054';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47054, 46598, 0);

DELETE FROM `creature_template_addon` WHERE `entry` IN (47051, 49414, 47052, 47092, 47050);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(47051, 1, '60191 87541'),
(49414, 1, '60191 87541'),
(47050, 1, '60191 87541'),
(47052, 1, '60191 85500 70628'),
(47092, 1, '60191');

UPDATE `spell_target_position` SET `target_position_z`=336.983, `target_orientation`=2.25 WHERE `id`=87682 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_position_y`=-283.26, `target_orientation`=0.51 WHERE `id`=87675 AND `effIndex`=0;
UPDATE `spell_target_position` SET `target_position_z`=336.67, `target_orientation`=2.25 WHERE `id`=87681 AND `effIndex`=0;

UPDATE `creature` SET `phaseMask`=32 WHERE `guid` IN (735832, 735812, 735809, 735834, 735691);
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=47967;

DELETE FROM `creature_loot_template` WHERE `item` = '63248';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(47982, 63248, -67.553, 1, 0, 1, 1);

UPDATE `creature_template` SET `lootid`=47982 WHERE `entry`=47982;

DELETE FROM `creature_addon` WHERE `guid` = '735664';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(735664, 1, '49414');

UPDATE `spell_target_position` SET `target_orientation`=3.76 WHERE `id`=87673 AND `effIndex`=0;
UPDATE `creature_template` SET `ScriptName`='npc_tailgunner_camera' WHERE `entry`=47055;

DELETE FROM `conditions` WHERE `SourceEntry` = '87671';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 87671, 0, 0, 31, 0, 3, 47049, 0, 0, 0, '', 'Targeting -> Mirror');

UPDATE `creature_template` SET `ScriptName`='npc_tailgunner_clone' WHERE `entry`=47049;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=47049;

DELETE FROM `creature_text` WHERE `entry`=47050;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47050,0,0,'Quick! Into the plane!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_tailgunner_bomber' WHERE `entry`=47054;

DELETE FROM `script_waypoint` WHERE `entry` = '47054';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(47054, 1, -10385.62, -296.12, 336.70, 'Tailgunner Bomber WP'),
(47054, 2, -10407.93, -266.86, 336.70, 'Tailgunner Bomber WP'),
(47054, 3, -10433.02, -249.45, 336.70, 'Tailgunner Bomber WP'),
(47054, 4, -10483.19, -302.72, 336.70, 'Tailgunner Bomber WP'),
(47054, 5, -10534.61, -357.31, 361.67, 'Tailgunner Bomber WP'),
(47054, 6, -10766.89, -672.72, 374.36, 'Tailgunner Bomber WP'),
(47054, 7, -10512.62, -912.02, 319.49, 'Tailgunner Bomber WP'),
(47054, 8, -10335.03, -932.04, 285.39, 'Tailgunner Bomber WP'),
(47054, 9, -9934.68, -823.80, 165.18, 'Tailgunner Bomber WP'),
(47054, 10, -9805.76, -897.81, 107.00, 'Tailgunner Bomber WP'),
(47054, 11, -9765.09, -944.31, 106.93, 'Tailgunner Bomber WP');

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `VehicleId`=1235, `InhabitType`=4 WHERE `entry`=47054;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47054';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47054, 47102, 2, 1, 'Bomber -> Tailgun', 8, 0),
(47054, 47050, 0, 1, 'Bomber -> Harrison', 8, 0);

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `VehicleId`=1243 WHERE `entry`=47102;
UPDATE `creature_template` SET `unit_class`=4 WHERE `entry`=47102;

DELETE FROM `conditions` WHERE `SourceEntry` = '88650';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 88650, 0, 0, 31, 0, 3, 47562, 0, 0, 0, '', 'Targeting -> Schnottz Fighter');

UPDATE `creature_template` SET `ScriptName`='npc_tailgunner_fighter' WHERE `entry`=47562;

DELETE FROM `spell_area` WHERE `spell` = '94568' AND `quest_start` = '27905';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(94568, 5666, 27905, 27905, 1, 2);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735678;

-- Harrison Jones
SET @ENTRY := 47050;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,4000,4000,4000,4000,11,87489,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Knockdown"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

-- Burly Sea Trooper
SET @ENTRY := 47051;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,3900,3900,3900,3900,5,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Play Emote Attack");

UPDATE `creature_template` SET `VehicleId`=1425 WHERE `entry`=50408;

DELETE FROM `creature_text` WHERE `entry`=49467;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49467,0,0,'Did you really zhink you vould get avay vizh it, $n? Hmm?',12,0,100,0,0,0,'Comment'),
(49467,1,0,'First, you come traipsing into Uldum as if you owned zhe place...',12,0,100,0,0,0,'Comment'),
(49467,2,0,'Clumsily interferink vizh my operation...',12,0,100,0,0,0,'Comment'),
(49467,3,0,'Zhen you mercilessly kill my loyal vorkers...',12,0,100,0,0,0,'Comment'),
(49467,4,0,'NO BUT! Silence! Keep Movink!',14,0,100,0,0,0,'Comment'),
(49467,5,0,'Zhen, on top of everyzhink, you nearly take my life... ME!',12,0,100,0,0,0,'Comment'),
(49467,6,0,'You vill pay, $n. Deazh by firink sqvad!',12,0,100,0,0,0,'Comment'),
(49467,7,0,'Zhat\'s far enough!',14,0,100,0,0,0,'Comment'),
(49467,8,0,'You are fortunate zhat I am too busy to make you suffer as you deserve.',12,0,100,0,0,0,'Comment'),
(49467,9,0,'I can take it from here, my friends. Report to your master zhat zhe problem has been dealt vizh.',12,0,100,0,0,0,'Comment'),
(49467,10,0,'Tell him zhat zhere vill be no furzher interruptions.',12,0,100,0,0,0,'Comment'),
(49467,11,0,'Now, zhen, vhere vere ve?',12,0,100,0,0,0,'Comment'),
(49467,12,0,'Ahh, yes. Any last vords? Hmm?',12,0,100,0,0,0,'Comment'),
(49467,13,0,'You haven\'t seen zhe last of me, $n!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=50630;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(50630,0,0,'But...',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=50642;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(50642,0,0,'Be certain there aren\'t, Schnottz. Deathwing\'s patience wears thin.',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=50652;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(50652,0,0,'Beat it, Schnottz!',14,0,100,25,0,0,'Comment');

-- Commander Schnottz
SET @ENTRY := 47972;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `ScriptName`='npc_commander_firing_squad' WHERE `entry`=47972;
UPDATE `creature_template` SET `ScriptName`='npc_firing_squad_clone' WHERE `entry`=50630;
UPDATE `creature_template` SET `ScriptName`='npc_firing_squad_camera' WHERE `entry`=50408;

DELETE FROM `conditions` WHERE `SourceEntry` = '93976';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 93976, 0, 0, 31, 0, 3, 50630, 0, 0, 0, '', 'Targeting -> Mirror Image');

DELETE FROM `script_waypoint` WHERE `entry` = '49467';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(49467, 1, -10598.22, 1013.98, 31.55, 'Firing Squad WP (Schnottz)'),
(49467, 2, -10569.42, 1023.88, 36.08, 'Firing Squad WP (Schnottz)'),
(49467, 3, -10555.88, 1040.55, 37.05, 'Firing Squad WP (Schnottz)'),
(49467, 4, -10534.13, 1036.87, 40.44, 'Firing Squad WP (Schnottz)'),
(49467, 5, -10527.96, 1020.27, 42.45, 'Firing Squad WP (Schnottz)'),
(49467, 6, -10535.06, 983.28, 43.94, 'Firing Squad WP (Schnottz)');

DELETE FROM `script_waypoint` WHERE `entry` = '50630';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(50630, 1, -10598.22, 1013.98, 31.55, 'Firing Squad WP (Clone)'),
(50630, 2, -10569.42, 1023.88, 36.08, 'Firing Squad WP (Clone)'),
(50630, 3, -10555.88, 1040.55, 37.05, 'Firing Squad WP (Clone)'),
(50630, 4, -10534.13, 1036.87, 40.44, 'Firing Squad WP (Clone)'),
(50630, 5, -10527.96, 1020.27, 42.45, 'Firing Squad WP (Clone)'),
(50630, 6, -10552.83, 986.95, 40.00, 'Firing Squad WP (Clone)'),
(50630, 7, -10541.37, 969.79, 39.75, 'Firing Squad WP (Clone)');

DELETE FROM `script_waypoint` WHERE `entry` = '50639';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(50639, 1, -10590.18, 1010.25, 33.46, 'Firing Squad WP (Emissary 02)'),
(50639, 2, -10565.28, 1021.50, 37.55, 'Firing Squad WP (Emissary 02)'),
(50639, 3, -10553.46, 1035.31, 38.15, 'Firing Squad WP (Emissary 02)'),
(50639, 4, -10540.54, 1033.42, 40.39, 'Firing Squad WP (Emissary 02)'),
(50639, 5, -10564.62, 988.04, 38.88, 'Firing Squad WP (Emissary 02)'),
(50639, 6, -10555.80, 968.03, 44.13, 'Firing Squad WP (Emissary 02)');

DELETE FROM `script_waypoint` WHERE `entry` = '50642';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(50642, 1, -10591.48, 1022.75, 32.40, 'Firing Squad WP (Emissary 01)'),
(50642, 2, -10552.99, 1044.24, 37.69, 'Firing Squad WP (Emissary 01)'),
(50642, 3, -10531.93, 1040.66, 40.49, 'Firing Squad WP (Emissary 01)'),
(50642, 4, -10527.61, 1026.83, 41.86, 'Firing Squad WP (Emissary 01)'),
(50642, 5, -10550.87, 986.39, 40.19, 'Firing Squad WP (Emissary 01)'),
(50642, 6, -10548.20, 956.25, 43.80, 'Firing Squad WP (Emissary 01)');

UPDATE `creature_template` SET `ScriptName`='npc_firing_squad_commander_summon' WHERE `entry`=49467;
UPDATE `creature_template` SET `ScriptName`='npc_firing_squad_emissary_01' WHERE `entry`=50642;
UPDATE `creature_template` SET `ScriptName`='npc_firing_squad_emissary_02' WHERE `entry`=50639;

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (50642, 50639);
UPDATE `creature_template` SET `VehicleId`=1429 WHERE `entry`=51097;
UPDATE `creature_template` SET `VehicleId`=1430 WHERE `entry`=51100;
UPDATE `creature_template` SET `ScriptName`='npc_firing_squad_harrison' WHERE `entry`=50652;
UPDATE `gameobject` SET `phaseMask`=192 WHERE `guid` IN (728061, 728053);

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '8';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 8, 128, 'Uldum: Add Phase 128 After Quest Complete: Firing Squad (28267)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '8' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28267';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 8, 0, 0, 28, 0, 28267, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '9';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 9, 128, 'Uldum: Add Phase 128 After Quest Rewarded: Firing Squad (28267)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '9' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28267';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 9, 0, 0, 8, 0, 28267, 0, 0, 0, 0, 0, '', '');

DELETE FROM `spell_area` WHERE `spell` = '94566' AND `quest_start` = '28267';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(94566, 5602, 28267, 28269, 1, 64, 11);

UPDATE `gameobject` SET `phaseMask`=192 WHERE `id` IN (206978, 206979);
UPDATE `creature` SET `phaseMask`=128 WHERE `guid`=735815;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=181497;

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '10';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 10, 32, 4, 'Uldum: Negate Phase 32 After Quest: Firing Squad (28267)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '10' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28267';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 10, 0, 0, 28, 0, 28267, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '11';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 11, 32, 4, 'Uldum: Negate Phase 32 After Quest: Firing Squad (28267)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '11' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28267';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 11, 0, 0, 8, 0, 28267, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=181265;

-- Harrison Jones
SET @ENTRY := 48162;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,28269,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,48162,0,0,28,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Remove Detection to Invoker");

DELETE FROM `creature_text` WHERE `entry`=48162;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48162,0,0,'See ya around, kid.',12,0,100,66,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=735855;

DELETE FROM `spell_area` WHERE `spell` = '94566' AND `quest_start` = '28269';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(94566, 5670, 28269, 1, 74, 0);

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=728599;

DELETE FROM `spell_area` WHERE `spell` = '94567' AND `quest_start` = '28269';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(94567, 5670, 28269, 1, 74, 0);

UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=12499 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=8, `npc_option_npcflag`=65536 WHERE `menu_id`=12499 AND `id`=1;
UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=51675;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '50476';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(50476, 50939, 3, 1, 'Caravan -> Domesticated Kodo', 8, 0),
(50476, 48203, 0, 1, 'Caravan -> Sullah', 8, 0);

UPDATE `creature_template` SET `unit_flags`=768, `VehicleId`=1421, `ScriptName`='npc_two_tents_caravan' WHERE `entry`=50476;

DELETE FROM `script_waypoint` WHERE `entry` = '50476';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(50476, 1, -8412.86, 848.55, 152.05, 'Sullah Caravan WP'),
(50476, 2, -8462.72, 830.99, 152.32, 'Sullah Caravan WP'),
(50476, 3, -8490.72, 820.82, 154.89, 'Sullah Caravan WP'),
(50476, 4, -8519.41, 793.65, 153.10, 'Sullah Caravan WP'),
(50476, 5, -8564.61, 746.61, 152.56, 'Sullah Caravan WP'),
(50476, 6, -8592.72, 719.89, 154.55, 'Sullah Caravan WP'),
(50476, 7, -8577.92, 668.54, 149.71, 'Sullah Caravan WP'),
(50476, 8, -8592.97, 660.69, 149.96, 'Sullah Caravan WP'),
(50476, 9, -8634.12, 672.73, 150.51, 'Sullah Caravan WP'),
(50476, 10, -8720.15, 686.88, 153.85, 'Sullah Caravan WP'),
(50476, 11, -8732.79, 674.79, 153.30, 'Sullah Caravan WP'),
(50476, 12, -8762.70, 656.54, 151.12, 'Sullah Caravan WP'),
(50476, 13, -8779.58, 631.75, 150.97, 'Sullah Caravan WP'),
(50476, 14, -8810.73, 612.92, 151.09, 'Sullah Caravan WP'),
(50476, 15, -8844.97, 623.38, 151.38, 'Sullah Caravan WP'),
(50476, 16, -8898.76, 647.03, 156.49, 'Sullah Caravan WP'),
(50476, 17, -8925.11, 627.81, 153.39, 'Sullah Caravan WP'),
(50476, 18, -8944.14, 621.26, 153.48, 'Sullah Caravan WP');

DELETE FROM `creature_text` WHERE `entry`=48203;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48203,0,0,'What a beautiful land this is, wouldn\'t you say?',12,0,100,1,0,0,'Comment'),
(48203,1,0,'The sights, the sounds, the smells...',12,0,100,1,0,0,'Comment'),
(48203,2,0,'Uldum is full of treasures, my friend.',12,0,100,1,0,0,'Comment'),
(48203,3,0,'Some are easy for even simple men to discern, while others require wisdom to see.',12,0,100,1,0,0,'Comment'),
(48203,4,0,'I can see that Uldum will one day transform from a dangerous wilderness to a tourist magnet!',12,0,100,1,0,0,'Comment'),
(48203,5,0,'People will come from all over Azeroth to marvel at her wonders.',12,0,100,1,0,0,'Comment'),
(48203,6,0,'I plan on creating a wonder of my own for them to behold...',12,0,100,1,0,0,'Comment'),
(48203,7,0,'And I invite you to take part in its creation.',12,0,100,1,0,0,'Comment'),
(48203,8,0,'Believe me when I tell you, $n, you\'re in on the ground floor of something big!',12,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=768, `ScriptName`='npc_two_tents_sullah' WHERE `entry`=48203;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=50939;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '50476';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(50476, 46598, 0);

UPDATE `gameobject` SET `phaseMask`=256 WHERE `id` IN
(205437, 205438, 205464, 205530, 205465, 205456, 205441, 205463,
205529, 205528, 205443, 205440, 205447, 205466, 205461, 205462,
205436, 205435, 205448, 205533, 205532, 205531, 205467, 205454,
205453, 205455, 205468, 205469, 205460, 205458, 205459, 205439,
205442);

UPDATE `creature` SET `phaseMask`=256 WHERE `guid` IN
(735861,735858,735857,735860,735859,735846,735849,735852,735851,735853,
735848,735863,735850,735854,735847, 735862);

DELETE FROM `spell_area` WHERE `spell` = '89981' AND `quest_start` = '28274';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(89981, 5673, 28274, 1, 66, 0);

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '12';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 12, 256, 'Uldum: Add Phase 256 After Quest Complete: Two Tents (28274)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '12' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28274';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 12, 0, 0, 28, 0, 28274, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '13';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 13, 256, 'Uldum: Add Phase 256 After Quest Accept: Two Tents (28274)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '13' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '28274';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 13, 0, 0, 9, 0, 28274, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '14';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 14, 256, 'Uldum: Add Phase 256 After Quest Rewarded: Two Tents (28274)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '14' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28274';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 14, 0, 0, 8, 0, 28274, 0, 0, 0, 0, 0, '', '');

UPDATE `quest_template` SET `PrevQuestId`='28274' WHERE `Id` IN (28352, 28351);

DELETE FROM `conditions` WHERE `SourceEntry` = '28353' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28353, 28350, 0),
(20, 8, 28353, 28351, 0),
(20, 8, 28353, 28352, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28353' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28353, 28350, 0),
(19, 8, 28353, 28351, 0),
(19, 8, 28353, 28352, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '94428';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 94428, 0, 0, 31, 0, 3, 51193, 0, 0, 0, '', 'Targeting -> Wild Camel');

DELETE FROM `spell_script_names` WHERE `spell_id` = '94428';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(94428, 'spell_sullah_camel_harness');

-- Wild Camel
SET @ENTRY := 51193;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,94428,0,0,0,33,51199,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Killcredit"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,11,94436,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Captured"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `creature_template` SET `minlevel`=84, `maxlevel`=84, `exp`=3, `unit_flags`=768 WHERE `entry`=51197;

DELETE FROM `spell_area` WHERE `spell` = '98920' AND `quest_start` = '28352';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_end_status`) VALUES
(98920, 5673, 28352, 1, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` = '94685';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(94685, 'spell_camel_tow_completion');

UPDATE `creature_template` SET `ScriptName`='npc_captured_wild_camel' WHERE `entry`=51197;

SET @CGUID := 840893;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+34;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+1, 45190, 1, 1, 1, 0, 1, -9015.65, 643.743, 171.175, 3.77789, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+2, 45190, 1, 1, 1, 0, 1, -8987.13, 679.945, 177.88, 4.23342, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+3, 45190, 1, 1, 1, 0, 1, -9052.67, 687.784, 182.569, 6.25973, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+4, 45190, 1, 1, 1, 0, 1, -9076.4, 656.935, 164.247, 2.20315, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+5, 45190, 1, 1, 1, 0, 1, -9087.09, 620.986, 152.868, 0.500407, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+6, 45190, 1, 1, 1, 0, 1, -9139.92, 608.014, 156.065, 6.04846, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+7, 45190, 1, 1, 1, 0, 1, -9190.68, 620.555, 165.825, 6.04846, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+8, 45190, 1, 1, 1, 0, 1, -9237.33, 654.626, 187.194, 5.81755, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+9, 45190, 1, 1, 1, 0, 1, -9274.31, 658.925, 185.252, 0.724248, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+10, 45190, 1, 1, 1, 0, 1, -9300, 635.589, 178.521, 1.72406, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+11, 45190, 1, 1, 1, 0, 1, -9318.67, 598.149, 171.282, 0.802788, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+12, 45190, 1, 1, 1, 0, 1, -9363.89, 595.767, 166.119, 5.29841, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+13, 45190, 1, 1, 1, 0, 1, -9399.43, 623.904, 170.691, 0.44229, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+14, 45190, 1, 1, 1, 0, 1, -9459.37, 603.097, 157.932, 5.94479, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+15, 45190, 1, 1, 1, 0, 1, -9498.79, 613.087, 148.454, 0.373961, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+16, 45190, 1, 1, 1, 0, 1, -9525.23, 582.818, 139.055, 1.25832, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+17, 45190, 1, 1, 1, 0, 1, -9550.53, 504.394, 139.868, 1.25832, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+18, 45190, 1, 1, 1, 0, 1, -9578.12, 469.598, 139.503, 5.78221, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+19, 45190, 1, 1, 1, 0, 1, -9613.07, 487.276, 131.189, 0.468994, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+20, 45190, 1, 1, 1, 0, 1, -9665.43, 455.505, 113.446, 5.45627, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+21, 45190, 1, 1, 1, 0, 1, -9677.18, 503.587, 109.536, 4.56092, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+22, 45190, 1, 1, 1, 0, 1, -9647.22, 535.8, 107.688, 4.718, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+23, 45190, 1, 1, 1, 0, 1, -9650.57, 573.092, 98.9637, 5.38323, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+24, 45190, 1, 1, 1, 0, 1, -9730.03, 519.214, 82.4025, 4.879, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+25, 45190, 1, 1, 1, 0, 1, -9722.96, 564.41, 80.5264, 4.98268, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+26, 45190, 1, 1, 1, 0, 1, -9730.37, 632.486, 81.483, 5.06514, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+27, 45190, 1, 1, 1, 0, 1, -9777.19, 624.272, 68.3588, 1.44603, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+28, 45190, 1, 1, 1, 0, 1, -9787.99, 576.834, 61.3945, 0.815354, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+29, 45190, 1, 1, 1, 0, 1, -9846.51, 536.767, 49.7571, 4.26168, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+30, 45190, 1, 1, 1, 0, 1, -9845.87, 591.979, 54.0439, 5.3581, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+31, 45190, 1, 1, 1, 0, 1, -9876.77, 632.994, 51.7843, 5.3581, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+32, 45190, 1, 1, 1, 0, 1, -9904.83, 670.228, 58.3286, 0.0990703, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+33, 45190, 1, 1, 1, 0, 1, -9959.94, 653.685, 46.9472, 0.839701, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0),
(@CGUID+34, 45190, 1, 1, 1, 0, 1, -9953.59, 596.777, 37.3765, 1.70521, 120, 0, 0, 53681, 0, 0, 16777216, 0, 0);

-- Sand Pygmy
SET @ENTRY := 45190;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,8,12000,12500,11,86695,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Whirlwind on Close"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,14500,16900,11,86699,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shockwave"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,93753,1,0,0,33,51188,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,93753,1,0,0,75,94365,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Cage"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,93753,1,0,0,18,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Root");

DELETE FROM `spell_script_names` WHERE `spell_id` = '93753';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(93753, 'spell_sullah_pigmy_pen');

-- Sand Pygmy
SET @ENTRY := 45190;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,9,0,100,0,0,8,12000,12500,11,86695,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Whirlwind on Close"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,14500,16900,11,86699,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shockwave"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,93753,1,0,0,33,51188,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,93753,1,0,0,75,94365,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Cage"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,93753,1,0,0,75,40885,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Root"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,93753,1,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Force Despawn");

DELETE FROM `spell_area` WHERE `spell` = '98546' AND `quest_start` = '28351';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(98546, 5673, 28351, 1, 66, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (90090, 90089);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(90090, 'spell_completion_checks'),
(90089, 'spell_completion_checks');

UPDATE `creature_template` SET `VehicleId`=1432 WHERE `entry`=50407;

DELETE FROM `spell_area` WHERE `spell` = '90089' AND `quest_start` = '28271';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(90089, 5668, 28271, 28271, 1, 2);

DELETE FROM `spell_area` WHERE `spell` = '90090' AND `quest_start` = '28272';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(90090, 5668, 28272, 28272, 1, 2);

UPDATE `creature_template` SET `ScriptName`='npc_otm_clone_event' WHERE `entry`=50629;
UPDATE `creature_template` SET `ScriptName`='npc_otm_camera_event' WHERE `entry`=50407;

DELETE FROM `conditions` WHERE `SourceEntry` = '93996';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 93996, 0, 0, 31, 0, 3, 50629, 0, 0, 0, '', 'Targeting -> Mirror Image');

DELETE FROM `creature_text` WHERE `entry`=50661;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(50661,0,0,'Warning! Warning! Intruder alert! Intruder Alert!',14,0,100,5,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_otm_elite_event' WHERE `entry`=50673;
UPDATE `creature_template` SET `InhabitType`=4, `ScriptName`='npc_otm_myzerian_event' WHERE `entry`=50663;

DELETE FROM `creature_template_addon` WHERE `entry` = '50663';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50663, 1, '60191');

DELETE FROM `creature` WHERE `guid`=735679;
DELETE FROM `creature_addon` WHERE `guid`=735679;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=48214;
UPDATE `creature` SET `position_x`=-8935.98, `position_y`=36.28, `position_z`=225.79, `orientation`=4.90, `spawntimesecs`=120 WHERE `guid`=736042;

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '15';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 15, 512, 'Uldum: Add Phase 512 After Quest Accepted: Reduced Productivity (28271)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '15' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '28271';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 15, 0, 0, 9, 0, 28271, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '16';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 16, 512, 'Uldum: Add Phase 512 After Quest Complete: Reduced Productivity (28271)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '16' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28271';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 16, 0, 0, 28, 0, 28271, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '17';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 17, 1024, 'Uldum: Add Phase 1024 After Quest Rewarded: Reduced Productivity (28271)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '17' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28271';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 17, 0, 0, 8, 0, 28271, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=1024 WHERE `guid`=736042;
UPDATE `creature` SET `phaseMask`=1024 WHERE `id` IN (48443, 50658);
UPDATE `creature` SET `phaseMask`=512 WHERE `id` IN (48204, 48205, 48374);
UPDATE `creature` SET `phaseMask`=386 WHERE `guid` IN (735887, 735881, 735889, 735880, 735926);

DELETE FROM `script_waypoint` WHERE `entry` = '48428';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(48428, 0, -8993.56, -88.51, 222.77, 'Myzerian WP'),
(48428, 1, -9097.71, -42.20, 222.77, 'Myzerian WP'),
(48428, 2, -9029.20, 59.49, 222.77, 'Myzerian WP'),
(48428, 3, -8961.79, 64.66, 229.40, 'Myzerian WP'),
(48428, 4, -8945.19, 50.26, 223.63, 'Myzerian WP'),
(48428, 5, -8935.98, 36.28, 225.79, 'Myzerian WP');

UPDATE `gameobject` SET `phaseMask`=1024 WHERE `id`=207127;

-- Myzerian
SET @ENTRY := 48428;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature_template` SET `ScriptName`='npc_myzerian_sentinel' WHERE `entry`=48428;
UPDATE `creature_addon` SET `auras`='90055 90136 89942' WHERE `guid`=736042;

DELETE FROM `spell_script_names` WHERE `spell_id` = '90139';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(90139, 'spell_shroud_of_the_makers');

UPDATE `creature` SET `phaseMask`=2048 WHERE `guid`=735911;
UPDATE `creature` SET `phaseMask`=2048 WHERE `id`=48488 AND `phaseMask`=32768;

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '18';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `comment`) VALUES
(5034, 18, 2048, 'Uldum: Add Phase 2048 After Quest Rewarded: Shroud of the Makers (28367)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '18' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28367';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 18, 0, 0, 8, 0, 28367, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '19';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 19, 1024, 4, 'Uldum: Negate Phase 1024 After Quest Rewarded: Shroud of the Markers (28367)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '19' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28367';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 19, 0, 0, 8, 0, 28367, 0, 0, 0, 0, 0, '', '');

DELETE FROM `spell_script_names` WHERE `spell_id` = '91826';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(91826, 'spell_completion_check_sec');

UPDATE `creature_template` SET `InhabitType`=4, `ScriptName`='npc_myzerian_death' WHERE `entry`=50664;

DELETE FROM `spell_area` WHERE `spell` = '91826' AND `quest_start` = '28367';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(91826, 5668, 28367, 28367, 1, 2);

UPDATE `creature_template` SET `VehicleId`=1432, `ScriptName`='npc_md_camera_event' WHERE `entry`=50406;
UPDATE `creature_template` SET `ScriptName`='npc_md_explosion_bunny' WHERE `entry`=51134;
UPDATE `creature_template` SET `scale`=10 WHERE `entry`=51134;
UPDATE `spell_target_position` SET `target_position_x`=-8952.03, `target_position_y`=-113.73, `target_position_z`=191.82, `target_orientation`=1.30 WHERE `id`=94153 AND `effIndex`=0;

DELETE FROM `spell_area` WHERE `spell` = '94188' AND `quest_start` = '28402';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(94188, 5672, 28402, 28402, 1, 2);

UPDATE `creature` SET `position_x`=-8904.04, `position_y`=54.86, `position_z`=141.04, `orientation`=3.15 WHERE `guid`=735911;
UPDATE `creature_addon` SET `auras`='29266' WHERE `guid`=735911;

UPDATE `spell_target_position` SET `target_position_x`=-8776.35, `target_position_y`=346.36, `target_position_z`=2.73, `target_orientation`=4.16 WHERE `id`=94192 AND `effIndex`=0;

DELETE FROM `spell_script_names` WHERE `spell_id` = '94188';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(94188, 'spell_schnottz_so_fast_complete');

UPDATE `creature_template` SET `ScriptName`='npc_com_camera_event', `VehicleId`=1441 WHERE `entry`=50405;
UPDATE `creature` SET `phaseMask`=4097 WHERE `guid`=183536;

DELETE FROM `spell_area` WHERE `spell` = '94566' AND `quest_start` = '28402';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(94566, 5672, 28402, 1, 74, 0);

UPDATE `creature` SET `phaseMask`=4096 WHERE `guid`=735891;
UPDATE `creature` SET `phaseMask`=4096 WHERE `id`=48534 AND `phaseMask`=1;
UPDATE `creature` SET `phaseMask`=2048 WHERE `id` IN (48668, 48518);

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '20';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 20, 4096, 0, 'Uldum: Add Phase 4096 After Quest Rewarded: Schnottz So Fast (28402)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '20' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28402';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 20, 0, 0, 8, 0, 28402, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '21';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 21, 4096, 0, 'Uldum: Add Phase 4096 After Quest Complete: Schnottz So Fast (28402)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '21' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28402';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 21, 0, 0, 28, 0, 28402, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '22';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 22, 2048, 4, 'Uldum: Negate Phase 2048 After Quest Complete: Schnottz So Fast (28402)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '22' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28402';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 22, 0, 0, 28, 0, 28402, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '5034' AND `entry` = '23';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(5034, 23, 2048, 4, 'Uldum: Negate Phase 2048 After Quest Rewarded: Schnottz So Fast (28402)');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '5034' AND `SourceEntry` = '23' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28402';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 5034, 23, 0, 0, 8, 0, 28402, 0, 0, 0, 0, 0, '', '');

DELETE FROM `creature_template_addon` WHERE `entry` = '50664';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50664, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '49462';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(49462, 1, '60191');