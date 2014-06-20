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
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5455, 27993, 1, 74, 0);

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