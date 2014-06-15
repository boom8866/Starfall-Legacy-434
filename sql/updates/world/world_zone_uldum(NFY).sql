DELETE FROM `spell_area` WHERE `spell` = '94566' AND `quest_start` IN (28557,28558,28295,28296,27003);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(94566, 440, 28557, 27003, 1, 10),
(94566, 440, 28558, 27003, 1, 10),
(94566, 440, 28295, 27003, 1, 10),
(94566, 440, 28296, 27003, 1, 10),
(94566, 440, 27003, 27003, 1, 10);

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
(46536, 1, -8944.66, -2162.54, 8.96, 'Lady Humps WP'),
(46536, 2, -8963.40, -1681.32, 94.44, 'Lady Humps WP');

DELETE FROM `script_waypoint` WHERE `entry` = '46596';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46596, 1, -8944.66, -2162.54, 8.96, 'Uldum Caravan WP'),
(46596, 2, -8963.29, -1696.34, 94.44, 'Uldum Caravan WP');

DELETE FROM `script_waypoint` WHERE `entry` = '46537';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46537, 1, -8938.77, -2169.80, 8.89, 'Pack Mule WP'),
(46537, 2, -8955.54, -1690.98, 94.45, 'Pack Mule WP');

DELETE FROM `script_waypoint` WHERE `entry` = '46540';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46540, 1, -8938.77, -2169.80, 8.89, 'Samir Camel WP'),
(46540, 2, -8950.76, -1695.39, 94.45, 'Samir Camel WP');

DELETE FROM `script_waypoint` WHERE `entry` = '46543';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46543, 1, -8938.77, -2169.80, 8.89, 'Mack Camel WP'),
(46543, 2, -8954.05, -1704.67, 94.45, 'Mack Camel WP');

DELETE FROM `script_waypoint` WHERE `entry` = '46546';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46546, 1, -8948.45, -2165.75, 8.90, 'Adarrah Camel WP'),
(46546, 2, -8972.29, -1693.71, 94.45, 'Adarrah Camel WP');

DELETE FROM `script_waypoint` WHERE `entry` = '46538';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46538, 1, -8948.45, -2165.75, 8.90, 'Budd Camel WP'),
(46538, 2, -8962.96, -1715.27, 94.44, 'Budd Camel WP');

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