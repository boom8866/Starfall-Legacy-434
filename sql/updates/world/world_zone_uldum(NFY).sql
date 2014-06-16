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