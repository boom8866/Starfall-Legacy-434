-- Deletes creature Tidebreaker Sailor (id: 49350, guid: 759018) in zone: 4922, area: 5140
DELETE FROM `creature` WHERE `guid` = 759018; DELETE FROM creature_addon WHERE guid = 759018;

-- Deletes creature Tidebreaker Sailor (id: 49350, guid: 759017) in zone: 4922, area: 5140
DELETE FROM `creature` WHERE `guid` = 759017; DELETE FROM creature_addon WHERE guid = 759017;

UPDATE `creature_template` SET `ScriptName`='npc_th_axebite_infantry' WHERE `entry`=49008;

UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (49342, 49008, 49284, 49009, 49028, 49143);
UPDATE `creature` SET `phaseMask`=2 WHERE `guid` IN (764707, 764980, 764265, 764264, 759032);
UPDATE `creature_template_addon` SET `bytes1`=0, `auras`='' WHERE `entry`=49009;
UPDATE `creature_template_addon` SET `auras`='95843' WHERE  `entry`=49284;
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry`=49008;
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `dynamicflags`=0 WHERE `entry`=49009;
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry`=49028;
UPDATE `creature_template` SET `ScriptName`='npc_th_tidebreaker_sailor' WHERE `entry`=49028;
UPDATE `creature_template` SET `ScriptName`='npc_th_highbank_guardsman' WHERE `entry`=49342;
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry`=49342;
UPDATE `creature_template` SET `ScriptName`='npc_th_bilgewater_gunman' WHERE `entry`=49009;

DELETE FROM `creature` WHERE `guid` = '841873';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(841873, 49022, 0, 1, 2, 0, 1, -4946.65, -6704.95, 14.9801, 5.30686, 300, 0, 0, 70946, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '841873';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `emote`) VALUES
(841873, 1, 333);

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '1';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 1, 2, 0, 'Twilight Highlands [A]: Add Phase 2 On Quest Complete: Twilight Shores [28832]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '1' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28832';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 1, 0, 0, 28, 0, 28832, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '2';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 2, 2, 0, 'Twilight Highlands [A]: Add Phase 2 On Quest Rewarded: Twilight Shores [28832]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '2' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28832';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 2, 0, 0, 8, 0, 28832, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=4 WHERE `id` IN (49008,49009);

DELETE FROM `creature_addon` WHERE `guid` = '764265';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(764265, '49414');

DELETE FROM `creature_addon` WHERE `guid` = '764264';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(764264, '49414 93391');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28832';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 5140, 28832, 28597, 1, 66);

UPDATE `quest_template` SET `PrevQuestId`='28596' WHERE `Id`=28597;

-- Position update for Fargo Flintlocke (id: 49020) in zone: 4922, area: 5140
UPDATE `creature` SET `position_x` = -4857.037, `position_y` = -6589.754, `position_z` = 10.661, `orientation`= 5.422 WHERE `guid` = 759162;

UPDATE `gameobject` SET `phaseMask`=2 WHERE `guid` IN (727493, 727494);
UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=759162;

DELETE FROM `creature_addon` WHERE `guid` = '759162';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(759162, '49415');

#IMPOSTARE QUESTEND
DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '28597';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5140, 28597, 1, 66, 0);

UPDATE `creature_template` SET `ScriptName`='npc_th_fargo_near_cannon' WHERE `entry`=49020;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=49020;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=49143;
UPDATE `creature_template` SET `ScriptName`='npc_th_cannon_powder_barrel' WHERE `entry`=49143;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=49143;
UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=764274;

DELETE FROM `creature_addon` WHERE `guid` = '764274';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(764274, '49415');

UPDATE `creature_addon` SET `bytes2`=1, `emote`=333 WHERE `guid`=759162;
UPDATE `quest_template` SET `Method`=0 WHERE `Id`=28598;

DELETE FROM `creature` WHERE `guid' = '841874';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(841874, 49020, 0, 1, 1, 0, 1, -4849.76, -6597.83, 9.41808, 5.69525, 300, 0, 0, 96744, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '841874';
INSERT INTO `creature_addon` (`guid`) VALUES
(841874);

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '3';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 3, 2, 4, 'Twilight Highlands [A]: Negate Phase 2 On Quest Rewarded: Aiming High [28598]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '3' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28598';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 3, 0, 0, 8, 0, 28598, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '4';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 4, 1, 0, 'Twilight Highlands [A]: Add Phase 1 On Quest Rewarded: Aiming High [28598]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '4' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28598';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 4, 0, 0, 8, 0, 28598, 0, 0, 0, 0, 0, '', '');

UPDATE `quest_template` SET `PrevQuestId`='27537' WHERE `Id`=27545;
UPDATE `quest_template` SET `PrevQuestId`='27338' WHERE `Id` IN (27341, 27366);
UPDATE `creature_template_addon` SET `emote`=333 WHERE `entry`=45368;
UPDATE `creature_template` SET `ScriptName`='npc_th_highbank_sniper' WHERE `entry`=45368;
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry` IN (45174, 45175);
UPDATE `creature_template` SET `ScriptName`='npc_th_highbank_guardsman' WHERE `entry`=45174;
UPDATE `creature_template` SET `ScriptName`='npc_th_axebite_marine' WHERE `entry`=45175;
UPDATE `quest_template` SET `Flags`=8, `SpecialFlags`=2 WHERE `Id`=27341;

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (6304, 6245);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6304, 'th_control_point'),
(6425, 'th_control_point');

UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `id`=45185;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=771225;

#IMPOSTARE QUESTEND
DELETE FROM `spell_area` WHERE `spell` = '98392' AND `quest_start` = '28599';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(98392, 5425, 28599, 1, 64, 0);

DELETE FROM `creature_text` WHERE `entry`=45168;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45168,0,0,'Can we fire some more cannons? I dunnae think we\'re firin\' nearly enough cannons.',12,0,100,1,0,0,'Comment'),
(45168,0,1,'More artillery... more! I never liked peninsulas.',12,0,100,1,0,0,'Comment'),
(45168,0,2,'So long as we\'re sendin\' troops up the beach, we should double-up the artillery-fire. You know, to help.',12,0,100,1,0,0,'Comment'),
(45168,0,3,'Thas\'it! Pulverize the beach! Leave nuthin\' but ... sand.',12,0,100,1,0,0,'Comment');

-- Fargo Flintlocke
SET @ENTRY := 45168;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,25000,10000,30000,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk Random");

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27514';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5425, 27514, 27516, 1, 66, 11);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (771226, 771227);
UPDATE `quest_template` SET `PrevQuestId`='27516' WHERE `Id`=27538;
UPDATE `quest_template` SET `PrevQuestId`='27545' WHERE `Id`=27621;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (45175, 45174);
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=27200;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=45224;

DELETE FROM `creature_text` WHERE `entry`=45171;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45171,0,0,'Avert yer eyes! Don\'t look at her!',12,0,100,1,0,0,'Comment'),
(45171,1,0,'Don\'t listen to her voice!',12,0,100,5,0,0,'Comment'),
(45171,2,0,'Don\'t look at her... ruby red... soft... sensual lips! Oh...',12,0,100,20,0,0,'Comment'),
(45171,3,0,'Eh - what? Who? What\'s going on?',12,0,100,1,0,0,'Comment'),
(45171,4,0,'Here she comes. Oh, foul temptress of the sea...',12,0,100,1,0,0,'Comment'),
(45171,5,0,'Hold fast. This is for yer own protection.',12,0,100,1,0,0,'Comment'),
(45171,6,0,'There! She reveals herself. Attack!',12,0,100,1,0,0,'Comment');

-- Position update for Stranded Crewman (id: 45210) in zone: 4922, area: 5424
UPDATE `creature` SET `position_x` = -4966.061, `position_y` = -6451.450, `position_z` = 1.987, `orientation`= 3.257 WHERE `guid` = 758985;

-- Position update for Stranded Crewman (id: 45210) in zone: 4922, area: 5424
UPDATE `creature` SET `position_x` = -4964.316, `position_y` = -6448.326, `position_z` = 1.857, `orientation`= 3.326 WHERE `guid` = 758987;

-- Position update for Stranded Crewman (id: 45210) in zone: 4922, area: 5424
UPDATE `creature` SET `position_x` = -4971.788, `position_y` = -6439.136, `position_z` = 0.437, `orientation`= 3.827 WHERE `guid` = 758972;

-- Position update for Stranded Crewman (id: 45210) in zone: 4922, area: 5424
UPDATE `creature` SET `position_x` = -4969.158, `position_y` = -6440.994, `position_z` = 0.824, `orientation`= 3.701 WHERE `guid` = 758971;

-- Position update for Ephram Hardstone (id: 45171) in zone: 4922, area: 5424
UPDATE `creature` SET `position_x` = -4964.463, `position_y` = -6443.625, `position_z` = 1.401, `orientation`= 0.480 WHERE `guid` = 758986;

UPDATE `creature_template` SET `InhabitType`=7, `ScriptName`='npc_th_ophelia' WHERE `entry`=45183;
UPDATE `creature_template` SET `ScriptName`='npc_th_ephram_hardstone' WHERE `entry`=45171;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=45183;

-- Position update for Lashed to the Mast (id: 45224) in zone: 4922, area: 5424
UPDATE `creature` SET `position_x` = -4958.703, `position_y` = -6443.234, `position_z` = 4.683, `orientation`= 3.489 WHERE `guid` = 758970;

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=45171;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=45224;
UPDATE `creature_template` SET `scale`=1 WHERE `entry`=45224;

DELETE FROM `creature_template_addon` WHERE `entry` = '45183';
INSERT INTO `creature_template_addon` (`entry`, `emote`) VALUES
(45183, 474);

UPDATE `creature_template` SET `VehicleId`=1146 WHERE `entry`=45768;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12055 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12055 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12055, 0, 0, 0, 9, 0, 27516, 0, 0, 0, 0, 0, '', 'Thordun - Show gossip only if quest 27516 is active');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45768';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45768, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '45768';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(45768, 45770, 1, 0, 'Thordun on Lightning', 8, 0);

DELETE FROM `script_waypoint` WHERE `entry` = '45768';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(45768, 1, -4483.62, -6050.26, 48.07, 'Lightning WP'),
(45768, 2, -4492.00, -6322.43, 66.02, 'Lightning WP'),
(45768, 3, -4479.42, -6477.87, 66.02, 'Lightning WP'),
(45768, 4, -4539.45, -6508.91, 87.02, 'Lightning WP'),
(45768, 5, -4679.06, -6487.46, 107.66, 'Lightning WP'),
(45768, 6, -4884.82, -6597.59, 82.45, 'Lightning WP'),
(45768, 7, -4899.71, -6629.10, 51.92, 'Lightning WP'),
(45768, 8, -4894.23, -6639.71, 37.41, 'Lightning WP'),
(45768, 9, -4882.01, -6634.58, 24.63, 'Lightning WP'),
(45768, 10, -4884.83, -6629.58, 16.46, 'Lightning WP'),
(45768, 11, -4888.56, -6641.86, 9.86, 'Lightning WP');

DELETE FROM `creature_text` WHERE `entry`=45172;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45172,0,0,'Hop aboard, $n. Let\'s move!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45770;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45770,0,0,'I hope you Alliance are here to give them Dragonmaw Orcs a good thumpin\'.',12,0,100,0,0,0,'Comment'),
(45770,1,0,'Stuff me like a haggis! Kurdran Wildhammer - in the flesh. He lives!',12,0,100,0,0,0,'Comment'),
(45770,2,0,'You\'ve got quite the setup here, friend. Come with me while I find out who\'s in charge.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=768, `ScriptName`='npc_th_lightning_travel' WHERE `entry`=45768;

-- Thordun Hammerblow
SET @ENTRY := 45172;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12055,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12055,0,0,0,28,49416,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Invisibility Detection"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12055,0,0,0,85,85375,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Lightning"),
(@ENTRY,@SOURCETYPE,3,0,19,0,100,0,27516,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

UPDATE `creature_template` SET `minlevel`=84, `maxlevel`=84, `exp`=3, `unit_flags`=768 WHERE `entry`=45770;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=45768;
UPDATE `creature_template` SET `minlevel`=84, `maxlevel`=84, `exp`=3 WHERE `entry`=45768;

DELETE FROM `script_waypoint` WHERE `entry` = '45770';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(45770, 1, -4892.89, -6637.95, 9.82, 'Thordrun WP'),
(45770, 2, -4902.30, -6645.80, 10.04, 'Thordrun WP'),
(45770, 3, -4911.70, -6648.11, 11.30, 'Thordrun WP'),
(45770, 4, -4921.20, -6635.78, 18.96, 'Thordrun WP'),
(45770, 5, -4907.91, -6613.29, 19.09, 'Thordrun WP');

UPDATE `creature_template` SET `ScriptName`='npc_th_thordrun_at_highbank' WHERE `entry`=45770;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=771228;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27516';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5140, 27516, 1, 66, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (759144, 759104);
UPDATE `creature` SET `spawndist`=5, `MovementType`=1 WHERE `id`='44011';

DELETE FROM `creature_loot_template` WHERE `entry` = '44011';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(44011, 33363, 0.05, 1, 0, 1, 1),
(44011, 33366, 0.05, 1, 0, 1, 1),
(44011, 33380, 0.05, 1, 0, 1, 1),
(44011, 33384, 0.05, 1, 0, 1, 1),
(44011, 33390, 0.05, 1, 0, 1, 1),
(44011, 33407, 0.05, 1, 0, 1, 1),
(44011, 33409, 0.05, 1, 0, 1, 1),
(44011, 33412, 0.05, 1, 0, 1, 1),
(44011, 33419, 0.05, 1, 0, 1, 1),
(44011, 33427, 0.05, 1, 0, 1, 1),
(44011, 33429, 0.05, 1, 0, 1, 1),
(44011, 33431, 0.05, 1, 0, 1, 1),
(44011, 52197, 0.0073, 1, 0, 1, 1),
(44011, 52326, 13.0461, 1, 0, 1, 1),
(44011, 52363, 0.05, 1, 0, 1, 1),
(44011, 52364, 0.05, 1, 0, 1, 1),
(44011, 52365, 0.05, 1, 0, 1, 1),
(44011, 52366, 0.05, 1, 0, 1, 1),
(44011, 52367, 0.05, 1, 0, 1, 1),
(44011, 52368, 0.05, 1, 0, 1, 1),
(44011, 52369, 0.05, 1, 0, 1, 1),
(44011, 52370, 0.05, 1, 0, 1, 1),
(44011, 52371, 0.05, 1, 0, 1, 1),
(44011, 52373, 0.05, 1, 0, 1, 1),
(44011, 52374, 0.05, 1, 0, 1, 1),
(44011, 52375, 0.05, 1, 0, 1, 1),
(44011, 52376, 0.05, 1, 0, 1, 1),
(44011, 52377, 0.05, 1, 0, 1, 1),
(44011, 52378, 0.05, 1, 0, 1, 1),
(44011, 52379, 0.05, 1, 0, 1, 1),
(44011, 52382, 0.05, 1, 0, 1, 1),
(44011, 52383, 0.05, 1, 0, 1, 1),
(44011, 52385, 0.05, 1, 0, 1, 1),
(44011, 52386, 0.05, 1, 0, 1, 1),
(44011, 52388, 0.05, 1, 0, 1, 1),
(44011, 52494, 0.05, 1, 0, 1, 1),
(44011, 52495, 0.05, 1, 0, 1, 1),
(44011, 52496, 0.05, 1, 0, 1, 1),
(44011, 52506, -14.949, 1, 0, 1, 1),
(44011, 52719, 0.0002, 1, 0, 1, 1),
(44011, 53062, 0.0001, 1, 0, 1, 1),
(44011, 53071, 0.0001, 1, 0, 1, 1),
(44011, 55285, 0.0069, 1, 0, 1, 1),
(44011, 55286, 0.05, 1, 0, 1, 1),
(44011, 55287, 0.05, 1, 0, 1, 1),
(44011, 55294, 0.0065, 1, 0, 1, 1),
(44011, 55295, 0.05, 1, 0, 1, 1),
(44011, 55296, 0.05, 1, 0, 1, 1),
(44011, 55303, 0.0022, 1, 0, 1, 1),
(44011, 55304, 0.05, 1, 0, 1, 1),
(44011, 55305, 0.05, 1, 0, 1, 1),
(44011, 55312, 0.0098, 1, 0, 1, 1),
(44011, 55313, 0.05, 1, 0, 1, 1),
(44011, 55314, 0.05, 1, 0, 1, 1),
(44011, 55321, 0.001, 1, 0, 1, 1),
(44011, 55322, 0.0041, 1, 0, 1, 1),
(44011, 55323, 0.05, 1, 0, 1, 1),
(44011, 55330, 0.0078, 1, 0, 1, 1),
(44011, 55331, 0.05, 1, 0, 1, 1),
(44011, 55332, 0.05, 1, 0, 1, 1),
(44011, 55339, 0.0041, 1, 0, 1, 1),
(44011, 55340, 0.05, 1, 0, 1, 1),
(44011, 55341, 0.05, 1, 0, 1, 1),
(44011, 55348, 0.008, 1, 0, 1, 1),
(44011, 55349, 0.05, 1, 0, 1, 1),
(44011, 55350, 0.05, 1, 0, 1, 1),
(44011, 55357, 0.0016, 1, 0, 1, 1),
(44011, 55358, 0.05, 1, 0, 1, 1),
(44011, 55359, 0.05, 1, 0, 1, 1),
(44011, 55366, 0.012, 1, 0, 1, 1),
(44011, 55367, 0.05, 1, 0, 1, 1),
(44011, 55368, 0.05, 1, 0, 1, 1),
(44011, 55375, 0.009, 1, 0, 1, 1),
(44011, 55376, 0.05, 1, 0, 1, 1),
(44011, 55377, 0.05, 1, 0, 1, 1),
(44011, 55384, 0.0075, 1, 0, 1, 1),
(44011, 55385, 0.05, 1, 0, 1, 1),
(44011, 55386, 0.05, 1, 0, 1, 1),
(44011, 55393, 0.004, 1, 0, 1, 1),
(44011, 55394, 0.05, 1, 0, 1, 1),
(44011, 55395, 0.05, 1, 0, 1, 1),
(44011, 55402, 0.0163, 1, 0, 1, 1),
(44011, 55403, 0.05, 1, 0, 1, 1),
(44011, 55404, 0.05, 1, 0, 1, 1),
(44011, 55411, 0.0063, 1, 0, 1, 1),
(44011, 55412, 0.05, 1, 0, 1, 1),
(44011, 55413, 0.05, 1, 0, 1, 1),
(44011, 55420, 0.0376, 1, 0, 1, 1),
(44011, 55421, 0.05, 1, 0, 1, 1),
(44011, 55422, 0.05, 1, 0, 1, 1),
(44011, 55429, 0.0084, 1, 0, 1, 1),
(44011, 55430, 0.05, 1, 0, 1, 1),
(44011, 55431, 0.05, 1, 0, 1, 1),
(44011, 55438, 0.0301, 1, 0, 1, 1),
(44011, 55439, 0.05, 1, 0, 1, 1),
(44011, 55440, 0.05, 1, 0, 1, 1),
(44011, 55447, 0.0049, 1, 0, 1, 1),
(44011, 55448, 0.05, 1, 0, 1, 1),
(44011, 55449, 0.05, 1, 0, 1, 1),
(44011, 55456, 0.0081, 1, 0, 1, 1),
(44011, 55457, 0.05, 1, 0, 1, 1),
(44011, 55458, 0.05, 1, 0, 1, 1),
(44011, 55465, 0.0047, 1, 0, 1, 1),
(44011, 55466, 0.05, 1, 0, 1, 1),
(44011, 55467, 0.05, 1, 0, 1, 1),
(44011, 55474, 0.0019, 1, 0, 1, 1),
(44011, 55475, 0.05, 1, 0, 1, 1),
(44011, 55476, 0.05, 1, 0, 1, 1),
(44011, 55483, 0.0153, 1, 0, 1, 1),
(44011, 55484, 0.05, 1, 0, 1, 1),
(44011, 55485, 0.05, 1, 0, 1, 1),
(44011, 55492, 0.0158, 1, 0, 1, 1),
(44011, 55493, 0.05, 1, 0, 1, 1),
(44011, 55494, 0.05, 1, 0, 1, 1),
(44011, 55501, 0.0123, 1, 0, 1, 1),
(44011, 55502, 0.05, 1, 0, 1, 1),
(44011, 55503, 0.05, 1, 0, 1, 1),
(44011, 55510, 0.0114, 1, 0, 1, 1),
(44011, 55511, 0.05, 1, 0, 1, 1),
(44011, 55512, 0.05, 1, 0, 1, 1),
(44011, 55519, 0.0114, 1, 0, 1, 1),
(44011, 55520, 0.05, 1, 0, 1, 1),
(44011, 55521, 0.05, 1, 0, 1, 1),
(44011, 55528, 0.0153, 1, 0, 1, 1),
(44011, 55529, 0.05, 1, 0, 1, 1),
(44011, 55530, 0.05, 1, 0, 1, 1),
(44011, 55537, 0.0121, 1, 0, 1, 1),
(44011, 55538, 0.05, 1, 0, 1, 1),
(44011, 55539, 0.05, 1, 0, 1, 1),
(44011, 55546, 0.0125, 1, 0, 1, 1),
(44011, 55547, 0.05, 1, 0, 1, 1),
(44011, 55548, 0.05, 1, 0, 1, 1),
(44011, 55555, 0.0148, 1, 0, 1, 1),
(44011, 55556, 0.05, 1, 0, 1, 1),
(44011, 55557, 0.05, 1, 0, 1, 1),
(44011, 55564, 0.0115, 1, 0, 1, 1),
(44011, 55565, 0.05, 1, 0, 1, 1),
(44011, 55566, 0.05, 1, 0, 1, 1),
(44011, 55573, 0.0116, 1, 0, 1, 1),
(44011, 55574, 0.05, 1, 0, 1, 1),
(44011, 55575, 0.05, 1, 0, 1, 1),
(44011, 55582, 0.0161, 1, 0, 1, 1),
(44011, 55583, 0.05, 1, 0, 1, 1),
(44011, 55584, 0.05, 1, 0, 1, 1),
(44011, 55591, 0.0121, 1, 0, 1, 1),
(44011, 55592, 0.05, 1, 0, 1, 1),
(44011, 55593, 0.05, 1, 0, 1, 1),
(44011, 55600, 0.0118, 1, 0, 1, 1),
(44011, 55601, 0.05, 1, 0, 1, 1),
(44011, 55602, 0.05, 1, 0, 1, 1),
(44011, 55609, 0.0132, 1, 0, 1, 1),
(44011, 55610, 0.05, 1, 0, 1, 1),
(44011, 55611, 0.05, 1, 0, 1, 1),
(44011, 55618, 0.0148, 1, 0, 1, 1),
(44011, 55619, 0.05, 1, 0, 1, 1),
(44011, 55620, 0.05, 1, 0, 1, 1),
(44011, 55627, 0.0139, 1, 0, 1, 1),
(44011, 55628, 0.05, 1, 0, 1, 1),
(44011, 55629, 0.05, 1, 0, 1, 1),
(44011, 55636, 0.0134, 1, 0, 1, 1),
(44011, 55637, 0.05, 1, 0, 1, 1),
(44011, 55638, 0.05, 1, 0, 1, 1),
(44011, 55645, 0.0121, 1, 0, 1, 1),
(44011, 55646, 0.05, 1, 0, 1, 1),
(44011, 55647, 0.05, 1, 0, 1, 1),
(44011, 55654, 0.0136, 1, 0, 1, 1),
(44011, 55655, 0.05, 1, 0, 1, 1),
(44011, 55656, 0.05, 1, 0, 1, 1),
(44011, 55663, 0.0127, 1, 0, 1, 1),
(44011, 55664, 0.05, 1, 0, 1, 1),
(44011, 55665, 0.05, 1, 0, 1, 1),
(44011, 55672, 0.0142, 1, 0, 1, 1),
(44011, 55673, 0.05, 1, 0, 1, 1),
(44011, 55674, 0.05, 1, 0, 1, 1),
(44011, 55681, 0.0153, 1, 0, 1, 1),
(44011, 55682, 0.05, 1, 0, 1, 1),
(44011, 55683, 0.05, 1, 0, 1, 1),
(44011, 55690, 0.0136, 1, 0, 1, 1),
(44011, 55691, 0.05, 1, 0, 1, 1),
(44011, 55692, 0.05, 1, 0, 1, 1),
(44011, 55699, 0.0147, 1, 0, 1, 1),
(44011, 55700, 0.05, 1, 0, 1, 1),
(44011, 55701, 0.05, 1, 0, 1, 1),
(44011, 55708, 0.0204, 1, 0, 1, 1),
(44011, 55709, 0.05, 1, 0, 1, 1),
(44011, 55710, 0.05, 1, 0, 1, 1),
(44011, 55717, 0.0187, 1, 0, 1, 1),
(44011, 55718, 0.05, 1, 0, 1, 1),
(44011, 55719, 0.05, 1, 0, 1, 1),
(44011, 55726, 0.0173, 1, 0, 1, 1),
(44011, 55727, 0.05, 1, 0, 1, 1),
(44011, 55728, 0.05, 1, 0, 1, 1),
(44011, 55735, 0.019, 1, 0, 1, 1),
(44011, 55736, 0.05, 1, 0, 1, 1),
(44011, 55737, 0.05, 1, 0, 1, 1),
(44011, 55744, 0.0206, 1, 0, 1, 1),
(44011, 55745, 0.05, 1, 0, 1, 1),
(44011, 55746, 0.05, 1, 0, 1, 1),
(44011, 55753, 0.0179, 1, 0, 1, 1),
(44011, 55754, 0.05, 1, 0, 1, 1),
(44011, 55755, 0.05, 1, 0, 1, 1),
(44011, 55762, 0.0187, 1, 0, 1, 1),
(44011, 55763, 0.05, 1, 0, 1, 1),
(44011, 55764, 0.0194, 1, 0, 1, 1),
(44011, 55771, 0.0219, 1, 0, 1, 1),
(44011, 55772, 0.05, 1, 0, 1, 1),
(44011, 55773, 0.05, 1, 0, 1, 1),
(44011, 60333, -27.6892, 1, 0, 1, 1),
(44011, 60337, -0.0177, 1, 0, 1, 1),
(44011, 60485, 80.0456, 1, 0, 1, 1),
(44011, 60486, 19.0824, 1, 0, 1, 1),
(44011, 62065, 0.1, 1, 0, 1, 1),
(44011, 62071, 0.1, 1, 0, 1, 1),
(44011, 62101, 0.05, 1, 0, 1, 1),
(44011, 62111, 0.05, 1, 0, 1, 1),
(44011, 62136, 0.05, 1, 0, 1, 1),
(44011, 65894, 0.0167, 1, 0, 1, 1),
(44011, 65895, 0.0141, 1, 0, 1, 1),
(44011, 65896, 0.0208, 1, 0, 1, 1),
(44011, 65897, 0.0171, 1, 0, 1, 1),
(44011, 66919, 0.0003, 1, 0, 1, 1),
(44011, 66920, 0.0017, 1, 0, 1, 1),
(44011, 66924, 0.0009, 1, 0, 1, 1),
(44011, 66931, 0.0029, 1, 0, 1, 1),
(44011, 66932, 0.05, 1, 0, 1, 1),
(44011, 66941, 0.001, 1, 0, 1, 1),
(44011, 66942, 0.0012, 1, 0, 1, 1),
(44011, 66964, 0.0007, 1, 0, 1, 1),
(44011, 66965, 0.0015, 1, 0, 1, 1),
(44011, 66966, 0.0012, 1, 0, 1, 1),
(44011, 66967, 0.0005, 1, 0, 1, 1),
(44011, 66968, 0.0012, 1, 0, 1, 1),
(44011, 66969, 0.05, 1, 0, 1, 1),
(44011, 66970, 0.05, 1, 0, 1, 1),
(44011, 66972, 0.05, 1, 0, 1, 1),
(44011, 66973, 0.0016, 1, 0, 1, 1),
(44011, 66974, 0.05, 1, 0, 1, 1),
(44011, 66975, 0.05, 1, 0, 1, 1),
(44011, 66976, 0.05, 1, 0, 1, 1),
(44011, 66986, 0.0013, 1, 0, 1, 1),
(44011, 66987, 0.0004, 1, 0, 1, 1),
(44011, 66988, 0.0007, 1, 0, 1, 1),
(44011, 66989, 0.05, 1, 0, 1, 1),
(44011, 66990, 0.0018, 1, 0, 1, 1),
(44011, 66991, 0.05, 1, 0, 1, 1),
(44011, 66992, 0.05, 1, 0, 1, 1),
(44011, 66993, 0.05, 1, 0, 1, 1),
(44011, 67050, 0.0009, 1, 0, 1, 1),
(44011, 67051, 0.0012, 1, 0, 1, 1),
(44011, 67052, 0.0004, 1, 0, 1, 1),
(44011, 67057, 0.05, 1, 0, 1, 1),
(44011, 67059, 0.002, 1, 0, 1, 1),
(44011, 67061, 0.05, 1, 0, 1, 1),
(44011, 67067, 0.05, 1, 0, 1, 1),
(44011, 67069, 0.05, 1, 0, 1, 1),
(44011, 67071, 0.05, 1, 0, 1, 1),
(44011, 67115, 0.0002, 1, 0, 1, 1),
(44011, 67116, 0.0014, 1, 0, 1, 1),
(44011, 67117, 0.0009, 1, 0, 1, 1),
(44011, 67118, 0.0003, 1, 0, 1, 1),
(44011, 67119, 0.05, 1, 0, 1, 1),
(44011, 67120, 0.05, 1, 0, 1, 1),
(44011, 67121, 0.05, 1, 0, 1, 1),
(44011, 67122, 0.05, 1, 0, 1, 1),
(44011, 67123, 0.05, 1, 0, 1, 1),
(44011, 67124, 0.05, 1, 0, 1, 1),
(44011, 67125, 0.001, 1, 0, 1, 1),
(44011, 67126, 0.0006, 1, 0, 1, 1),
(44011, 67132, 0.0002, 1, 0, 1, 1),
(44011, 67133, 0.0002, 1, 0, 1, 1),
(44011, 67135, 0.0008, 1, 0, 1, 1),
(44011, 67137, 0.0008, 1, 0, 1, 1),
(44011, 67139, 0.0006, 1, 0, 1, 1),
(44011, 67140, 0.0004, 1, 0, 1, 1),
(44011, 67141, 0.0002, 1, 0, 1, 1),
(44011, 67144, 0.0002, 1, 0, 1, 1),
(44011, 67145, 0.0002, 1, 0, 1, 1),
(44011, 67539, 0.2144, 1, 0, 1, 1),
(44011, 69820, 0.0003, 1, 0, 1, 1);

-- Muddied Water Elemental
SET @ENTRY := 44011;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,3000,3000,11,32011,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Bolt"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,39207,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Water Spout"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5500,8500,5500,8500,11,32011,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Spout");

-- Highbank Shaman
SET @ENTRY := 45869;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,6000,20000,18500,35500,11,82405,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Chain Lightning");

DELETE FROM `creature_text` WHERE `entry`=45173;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45173,0,0,'By wind and wave, by earth and fire... To Stormwind we go, $n!',12,0,100,0,0,0,'Comment');

-- Talaa
SET @ENTRY := 45173;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27537,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0," On Quest Rewarded - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,27537,0,0,0,66,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0," On Quest Rewarded - Set Orientation"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,27537,0,0,0,5,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0," On Quest Rewarded - Play Emote"),
(@ENTRY,@SOURCETYPE,3,0,20,0,100,0,27537,0,0,0,11,85322,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0," On Quest Rewarded - Summon Portal");

-- Portal to Stormwind
SET @ENTRY := 31640;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,18,33554432,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Unselectable");

DELETE FROM `creature` WHERE `guid` = '841875';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(841875, 31640, 0, 1, 1, 0, 0, -4892.15, -6624.18, 10.8373, 2.30035, 300, 0, 0, 42, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '841875';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(841875, '60921');

DELETE FROM `spell_area` WHERE `spell` = '60922' AND `quest_start` = '27537';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_end_status`) VALUES
(60922, 5140, 27537, 1, 0);

UPDATE `creature` SET `position_z`=10.6373 WHERE `guid`=841875;
UPDATE `creature` SET `id`=45526 WHERE `id`=45527;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45527';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(45527, 46598, 0);

-- Siege Tank Commander
SET @ENTRY := 45524;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,3000,3000,3000,3000,11,46598,0,0,0,0,0,11,45527,15,0,0.0,0.0,0.0,0.0,"OOC - Enter Vehicle");

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '45527';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(45527, 45526, 0, 0, 'Highbank Siege Engine -> On Siege Controller', 8, 0),
(45527, 45524, 1, 0, 'Siege Tank Commander -> On Siege Controller', 8, 0);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12042 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=45524;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45524,0,0,'Aye, protect the tank while the boys make repairs! I\'ll try to get her moving again...',12,0,100,0,0,0,'Comment'),
(45524,1,0,'Defend the Siege Tank!',42,0,100,0,0,0,'Comment'),
(45524,2,0,'Ahh, blast it. C\'mon, c\'mon already!',12,0,100,0,0,0,'Comment'),
(45524,3,0,'There! We got it! Let\'s get \'er outta here.',12,0,100,0,0,0,'Comment'),
(45524,4,0,'Success! The Siege Tank is able to retreat.',42,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceGroup`=12042 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12042, 0, 0, 0, 9, 0, 27468, 0, 0, 0, 0, 0, '', 'Siege Tank Commander - Show gossip only if quest 27468 is active');

UPDATE `creature_template` SET `ScriptName`='npc_th_siege_tank_commander' WHERE `entry`=45524;

-- Axebite Grunt
SET @ENTRY := 45187;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Players"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,63227,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Enrage"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3500,7500,7500,12500,11,79881,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Slam");

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry`=45523;

-- Beleagurered Engineer
SET @ENTRY := 45523;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2000,2000,2000,2000,49,0,0,0,0,0,0,11,45187,10,0,0.0,0.0,0.0,0.0,"OOC - Attack Axebiters");

UPDATE `creature_template` SET `DamageModifier`=1 WHERE `entry` IN (45523, 45187);
UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `id`=48688;

-- Diamond-Blade Shredder
SET @ENTRY := 45185;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,3500,4000,6000,11,32735,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Saw Blade");

-- Dragonmaw Hold
SET @ENTRY := 45388;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,84864,4,0,0,28,84841,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Remove Marker");

UPDATE `creature_template` SET `ScriptName`='npc_th_cannon_beach_triggering' WHERE `entry`=45396;
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=45388;

-- Dragonmaw Hold
SET @ENTRY := 45388;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,84864,4,0,0,28,84841,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Remove Marker"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,84864,4,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Invincible"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,84864,4,0,0,18,33554432,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Unselectable");

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6294';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6294, 'th_areatrigger_teleport_sw');

UPDATE `quest_template` SET `PrevQuestId`='27621' WHERE `Id`=27803;
UPDATE `quest_template` SET `PrevQuestId`='27621' WHERE `Id`=27804;
UPDATE `quest_template` SET `PrevQuestId`='27817' WHERE `Id`=27640;
UPDATE `quest_template` SET `PrevQuestId`='27817' WHERE `Id`=28001;
UPDATE `quest_template` SET `PrevQuestId`='27806' WHERE `Id`=27807;
UPDATE `quest_template` SET `PrevQuestId`='27806' WHERE `Id`=27808;
UPDATE `quest_template` SET `PrevQuestId`='27806' WHERE `Id`=27809;
UPDATE `quest_template` SET `PrevQuestId`='27621' WHERE `Id`=27805;
UPDATE `quest_template` SET `PrevQuestId`='27807' WHERE `Id`=27811;
UPDATE `quest_template` SET `PrevQuestId`='27808' WHERE `Id`=27999;
UPDATE `quest_template` SET `PrevQuestId`='28171' WHERE `Id`=28173;
UPDATE `quest_template` SET `PrevQuestId`='28171' WHERE `Id`=28191;
UPDATE `quest_template` SET `PrevQuestId`='28171' WHERE `Id`=28175;
UPDATE `quest_template` SET `PrevQuestId`='28247' WHERE `Id`=28248;
UPDATE `quest_template` SET `PrevQuestId`='27809' WHERE `Id`=28233;
UPDATE `quest_template` SET `PrevQuestId`='27809' WHERE `Id`=27814;

/* FIREBEARD'S PATROL PHASING */

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '5';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 5, 4, 0, 'Twilight Highlands [A]: Add Phase 4 On Quest Complete: Firebeard Patrol [27621]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '5' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '27621';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 5, 0, 0, 28, 0, 27621, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '6';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 6, 4, 0, 'Twilight Highlands [A]: Add Phase 4 On Quest Rewarded: Firebeard Patrol [27621]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '6' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '27621';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 6, 0, 0, 8, 0, 27621, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=4 WHERE `id` IN (46838, 46831, 46849);
UPDATE `gameobject` SET `phaseMask`=4 WHERE `id` IN (206408, 206411, 206410, 206387);
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (758444, 758443);
UPDATE `gameobject` SET `spawntimesecs`=5 WHERE `id`=206387;

-- Firebeard's Patrol Fire Bunny
SET @ENTRY := 46849;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,87250,1,0,0,33,46849,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,87250,1,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Despawn");

UPDATE `creature_template` SET `unit_flags`=0, `ScriptName`='npc_th_firebeard_militia' WHERE `entry`=46831;
UPDATE `creature_template` SET `unit_flags`=0, `ScriptName`='npc_th_subjugated_firestarter' WHERE `entry`=46838;

UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`=46849;

SET @CGUID := 841876;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+8;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 46807, 0, 1, 4, 0, 1, -4173.08, -5567.18, 28.0896, 6.10795, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+1, 46807, 0, 1, 4, 0, 1, -4142.35, -5584.47, 34.0168, 5.71683, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+2, 46807, 0, 1, 4, 0, 1, -4129.18, -5570.26, 37.1586, 5.41759, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+3, 46807, 0, 1, 4, 0, 1, -4137.52, -5560.68, 36.1364, 0.599956, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+4, 46807, 0, 1, 4, 0, 1, -4160.34, -5587.1, 30.1261, 0.528485, 30, 0, 0, 85239, 0, 0, 0, 0, 0);

SET @CGUID := 841876;
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+8;
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(@CGUID+0, 0, '87270'),
(@CGUID+1, 0, '87270'),
(@CGUID+2, 0, '87270'),
(@CGUID+3, 0, '87270'),
(@CGUID+4, 0, '87270');

UPDATE `creature_template` SET `ScriptName`='npc_th_firebeard_citizen', `speed_run`=1.14714 WHERE `entry`=46807;
UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `id`=48692;

-- Firebeard Gryphon Rider
SET @ENTRY := 47312;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2000,2000,2000,2000,49,0,0,0,0,0,0,11,46851,20,0,0.0,0.0,0.0,0.0,"OOC - Attack Start Dragonmaw");

-- Dragonmaw Straggler
SET @ENTRY := 46851;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,22120,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Charge"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,32064,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battle Shout");

-- Position update for Bahrum Forgehammer (id: 48053) in zone: 4922, area: 5488
UPDATE `creature` SET `position_x` = -3829.733, `position_y` = -5765.567, `position_z` = 24.279, `orientation`= 4.980 WHERE `guid` = 758813;

DELETE FROM `spell_area` WHERE `spell` = '89536' AND `quest_start` = '28233';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(89536, 5488, 28233, 28234, 1, 66, 11);

UPDATE `quest_template` SET `RewardSpellCast`=0 WHERE `Id`=28234;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12247 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=46813;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46813,0,0,'Them\'s DEFINITELY fightin\' words!',12,0,100,0,0,0,'Comment'),
(46813,1,0,'The duel will begin in...',42,0,100,0,0,0,'Comment'),
(46813,2,0,'3...',42,0,100,0,0,0,'Comment'),
(46813,3,0,'2...',42,0,100,0,0,0,'Comment'),
(46813,4,0,'1...',42,0,100,0,0,0,'Comment'),
(46813,5,0,'Fine! Fine. You win this one.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_th_mullan_gryphon_rider' WHERE `entry`=46813;
UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE `id`=46153;

-- Twilight Trapper
SET @ENTRY := 46984;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,7500,4500,9500,11,78578,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Immolation Trap"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,100,100,18000,18000,11,80009,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Serpent Sting"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,6000,6000,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

-- Highland Worg
SET @ENTRY := 46153;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,7000,4000,9000,11,48287,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Powerful Bite");

DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27815 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27813 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27815 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27810 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

UPDATE `quest_template` SET `PrevQuestId`='27814' WHERE `Id`=27815;

DELETE FROM `conditions` WHERE `SourceEntry` = '27812' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27812, 27810, 0),
(20, 8, 27812, 27811, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27812' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27812, 27810, 0),
(19, 8, 27812, 27811, 0);

DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27816 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27815 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

UPDATE `quest_template` SET `NextQuestIdChain`=27810 WHERE `Id`=27807;
UPDATE `quest_template` SET `NextQuestIdChain`=0 WHERE `Id` IN (27810, 27812, 27815);
UPDATE `quest_template` SET `PrevQuestId`='27813' WHERE `Id`=27815;

DELETE FROM `conditions` WHERE `SourceEntry` = '27816' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27816, 27999, 0),
(20, 8, 27816, 27815, 0),
(20, 8, 27816, 27812, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27816' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27816, 27999, 0),
(19, 8, 27816, 27815, 0),
(19, 8, 27816, 27812, 0);

DELETE FROM `creature_text` WHERE `entry`=46969;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46969,0,0,'The gryphon muscles tense and eyes tighten as soon as the bark is extended towards it.',16,0,100,0,0,0,'Comment'),
(46969,1,0,'The gryphon screams with glee as you break it free.',16,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_th_mullan_gryphon_trapped', `InhabitType`=5 WHERE `entry`=46969;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry` IN (46975, 46969);
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12165 AND `id`=0;
UPDATE `creature_template` SET `ScriptName`='npc_th_mullan_gryphon_injuried', `InhabitType`=5 WHERE `entry`=46968;

-- Position update for Dave's Industrial Light and Magic Bunny (Medium)(Sessile)(Large AOI) (id: 45396) in zone: 4922, area: 5425
UPDATE `creature` SET `position_x` = -4502.937, `position_y` = -6528.389, `position_z` = 44.547, `orientation`= 0.261 WHERE `guid` = 759305;

-- Position update for Dave's Industrial Light and Magic Bunny (Medium)(Sessile)(Large AOI) (id: 45396) in zone: 4922, area: 5425
UPDATE `creature` SET `position_x` = -4413.350, `position_y` = -6578.925, `position_z` = 30.503, `orientation`= 2.410 WHERE `guid` = 755219;

-- Position update for Dave's Industrial Light and Magic Bunny (Medium)(Sessile)(Large AOI) (id: 45396) in zone: 4922, area: 5425
UPDATE `creature` SET `position_x` = -4453.734, `position_y` = -6442.361, `position_z` = 61.397, `orientation`= 3.679 WHERE `guid` = 755217;

-- Position update for Dave's Industrial Light and Magic Bunny (Medium)(Sessile)(Large AOI) (id: 45396) in zone: 4922, area: 5425
UPDATE `creature` SET `position_x` = -4432.864, `position_y` = -6467.949, `position_z` = 31.921, `orientation`= 3.410 WHERE `guid` = 755218;

-- Position update for Dave's Industrial Light and Magic Bunny (Medium)(Sessile)(Large AOI) (id: 45396) in zone: 4922, area: 5425
UPDATE `creature` SET `position_x` = -4345.532, `position_y` = -6541.357, `position_z` = 54.951, `orientation`= 3.004 WHERE `guid` = 755215;

-- Position update for Dave's Industrial Light and Magic Bunny (Medium)(Sessile)(Large AOI) (id: 45396) in zone: 4922, area: 5425
UPDATE `creature` SET `position_x` = -4434.693, `position_y` = -6440.230, `position_z` = 28.733, `orientation`= 3.927 WHERE `guid` = 755216;

-- Highbank
SET @ENTRY := 45406;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,84864,4,0,0,28,84841,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Remove Marker"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,84864,4,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Invincible"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,84864,4,0,0,18,33554432,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Unselectable");

UPDATE `creature` SET `spawndist`=50, `MovementType`=1 WHERE `id`=47186;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47186';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47186, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47186';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `description`) VALUES
(47186, 46321, 0, 'Thundermr Gryphon Rider on his Gryphon');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '7';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 7, 8, 0, 'Twilight Highlands [A]: Add Phase 8 On Quest Complete: Personal Request [27816]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '7' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '27816';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 7, 0, 0, 28, 0, 27816, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '8';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 8, 8, 0, 'Twilight Highlands [A]: Add Phase 8 On Quest Rewarded: Personal Request [27816]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '8' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '27816';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 8, 0, 0, 8, 0, 27816, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '9';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 9, 4, 4, 'Twilight Highlands [A]: Negate Phase 4 On Quest Complete: Personal Request [27816]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '9' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '27816';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 9, 0, 0, 28, 0, 27816, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '10';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 10, 4, 4, 'Twilight Highlands [A]: Negate Phase 4 On Quest Rewarded: Personal Request [27816]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '10' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '27816';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 10, 0, 0, 8, 0, 27816, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=8 WHERE `id` IN (47316, 50426, 47241, 47199, 46839);
UPDATE `creature` SET `phaseMask`=8 WHERE `guid` IN (758440, 758427, 772462);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47241';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47241, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47241';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47241, 47229, 1, 'Mullan Gryphon Rider on their Gryphon', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47241';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47241, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47241';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47241, 47229, 1, 'Mullan Gryphon Rider on their Gryphon', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '50426';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(50426, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '50426';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(50426, 50428, 1, 'Moore Gryphon Rider on their Gryphon', 8, 0);

-- Position update for Firebeard Citizen (id: 46807) in zone: 4922, area: 5141
UPDATE `creature` SET `position_x` = -4168.196, `position_y` = -5597.498, `position_z` = 28.028, `orientation`= 2.386 WHERE `guid` = 758673;

UPDATE `creature_template` SET `minlevel`=88, `maxlevel`=88, `exp`=3, `faction`=2339, `speed_run`=1.27286, `VehicleId`=1261, `InhabitType`=4 WHERE `entry`=47315;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47315';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47315, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47315';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47315, 47313, 1, 'Firebeard Gryphon Rider on their Gryphon', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '47316';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(47316, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '47316';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(47316, 47313, 1, 'Firebeard Gryphon Rider on their Gryphon', 8, 0);

UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_th_firebeard_gryphon_mount' WHERE `entry`=47316;
UPDATE `creature_template` SET `ScriptName`='npc_th_firebeard_gryphon_summoned' WHERE `entry`=47315;

DELETE FROM `creature_text` WHERE `entry`=47315;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47315,0,0,'Use your Storm Shield before the Static Charge finishes! |TInterface\\Icons\\spell_nature_lightningshield.blp:32|t',42,0,100,0,0,0,'Comment'),
(47315,1,0,'Good work, $n! Now to attack their leader!',12,0,100,0,0,0,'Comment');

DELETE FROM `script_waypoint` WHERE `entry` = '47315';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(47315, 1, -4176.39, -5577.44, 37.56, 'Firebeard Gryphon Mount WP'),
(47315, 2, -4203.09, -5562.53, 42.20, 'Firebeard Gryphon Mount WP'),
(47315, 3, -4221.88, -5496.36, 67.25, 'Firebeard Gryphon Mount WP'),
(47315, 4, -4087.76, -5475.71, 103.94, 'Firebeard Gryphon Mount WP'),
(47315, 5, -3970.96, -5469.29, 131.56, 'Firebeard Gryphon Mount WP'),
(47315, 6, -3946.59, -5467.98, 129.40, 'Firebeard Gryphon Mount WP'),
(47315, 7, -3909.54, -5434.34, 104.02, 'Firebeard Gryphon Mount WP'),
(47315, 8, -3865.14, -5586.50, 110.28, 'Firebeard Gryphon Mount WP'),
(47315, 9, -3949.85, -5698.53, 104.11, 'Firebeard Gryphon Mount WP'),
(47315, 10, -4050.49, -5673.99, 100.73, 'Firebeard Gryphon Mount WP'),
(47315, 11, -4023.13, -5618.05, 134.94, 'Firebeard Gryphon Mount WP'),
(47315, 12, -4031.84, -5504.07, 138.72, 'Firebeard Gryphon Mount WP'),
(47315, 13, -3937.95, -5475.39, 258.35, 'Firebeard Gryphon Mount WP'),
(47315, 14, -3931.96, -5556.97, 258.35, 'Firebeard Gryphon Mount WP'),
(47315, 15, -3947.68, -5514.53, 258.35, 'Firebeard Gryphon Mount WP'),
(47315, 16, -3981.75, -5497.03, 258.35, 'Firebeard Gryphon Mount WP'),
(47315, 17, -4004.43, -5513.37, 258.35, 'Firebeard Gryphon Mount WP'),
(47315, 18, -3992.17, -5547.33, 258.35, 'Firebeard Gryphon Mount WP'),
(47315, 19, -3959.18, -5563.43, 258.35, 'Firebeard Gryphon Mount WP'),
(47315, 20, -3970.97, -5532.88, 245.35, 'Firebeard Gryphon Mount WP');

UPDATE `creature_template` SET `InhabitType`=7, `movementId`=140 WHERE `entry`=47315;

-- Twilight Stormbender
SET @ENTRY := 47199;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,25,0,100,0,0,0,0,0,11,88113,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset - Cast Twilight Channeling"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,3000,3000,3000,3000,49,0,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Nearest Player"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,500,500,18000,18000,11,88043,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Static Charge"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,3100,3100,3500,3500,11,88106,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Lightning Bolt");

UPDATE `creature_template` SET `ScriptName`='npc_th_twilight_stormbender' WHERE `entry`=47199;
UPDATE `creature` SET `phaseMask`=8 WHERE `guid`=772505;
UPDATE `creature_template` SET `ScriptName`='npc_th_servias_windterror' WHERE `entry`=46839;
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=47298;
UPDATE `creature_template` SET `RegenHealth`=0 WHERE `entry`=46839;
UPDATE `creature` SET `spawntimesecs`=15 WHERE `guid`=772502;

DELETE FROM `spell_area` WHERE `spell` = '98433' AND `quest_start` = '27640';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(98433, 5484, 27640, 27650, 1, 66, 11);

UPDATE `quest_template` SET `PrevQuestId`='27640' WHERE `Id` IN (27643, 27644, 27645, 27641, 27642);
UPDATE `creature` SET `spawndist`=50, `MovementType`=1 WHERE `id`=48683;

-- Twilight Scavenger
SET @ENTRY := 46183;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,100,100,3000,4500,11,6660,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

-- Twilight Pillager
SET @ENTRY := 46144;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,6000,19000,20000,11,84442,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On OCC do emote (radom time)"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2500,3500,3500,11,14873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike");

-- Bloodgorged Ettin
SET @ENTRY := 46145;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,8000,15000,11,88421,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Log Smash");

DELETE FROM `spell_area` WHERE `spell` = '84481' AND `quest_start` = '27644';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(84481, 5483, 27644, 27647, 1, 66, 11);

#IMPOSTARE QUESTEND
DELETE FROM `spell_area` WHERE `spell` = '86875' AND `quest_start` = '27643';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(86875, 5485, 27643, 1, 66, 0);

DELETE FROM `creature_text` WHERE `entry`=46175;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46175,0,0,'Bah! Dere\'s got to be some here somewhere...',12,0,100,0,0,0,'Comment'),
(46175,1,0,'water?! Are you daft?! I need some ALE!',12,0,100,0,0,0,'Comment');

-- Eoin Dunwald
SET @ENTRY := 46175;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,30000,60000,45000,60000,65,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12139,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,12139,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,30000,30000,30000,30000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset");

-- Adds Waypoint Movement to Eoin Dunwald (guid: 758048, entry: 46175)
SET @GUID  := 758048;
SET @WP_ID := 7580480;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 758048;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(758048, 7580480, 0, 65536, 1, 0, '0 80852');
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -4761.810, -5238.010, 116.467, 2),
(@WP_ID, 2, -4763.860, -5230.340, 116.932, 2),
(@WP_ID, 3, -4765.890, -5217.550, 117.107, 2),
(@WP_ID, 4, -4765.060, -5216.380, 117.129, 2),
(@WP_ID, 5, -4760.450, -5214.780, 117.891, 2),
(@WP_ID, 6, -4765.580, -5216.730, 117.103, 2),
(@WP_ID, 7, -4770.290, -5221.920, 117.101, 2),
(@WP_ID, 8, -4772.420, -5220.960, 117.096, 2),
(@WP_ID, 9, -4773.690, -5225.700, 117.099, 2),
(@WP_ID, 10, -4779.160, -5228.830, 117.099, 2),
(@WP_ID, 11, -4772.060, -5230.760, 117.053, 2),
(@WP_ID, 12, -4766.250, -5228.480, 117.101, 2),
(@WP_ID, 13, -4763.270, -5241.670, 116.446, 2),
(@WP_ID, 14, -4760.400, -5242.650, 116.460, 2);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12139 AND `id`=0;

-- Position update for Cayden Dunwald (id: 46174) in zone: 4922, area: 5487
UPDATE `creature` SET `position_x` = -4677.288, `position_y` = -4850.363, `position_z` = 162.517, `orientation`= 3.821 WHERE `guid` = 757842;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `id`=206203;

DELETE FROM `gameobject_loot_template` WHERE `item` = '62317';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(35326, 62317, -100);

UPDATE `gameobject_template` SET `ScriptName`='go_th_sacred_ale_tap' WHERE `entry`=206203;
UPDATE `quest_template` SET `NextQuestIdChain`=0 WHERE `Id`=27646;
UPDATE `quest_template` SET `NextQuestIdChain`=0 WHERE `Id`=27648;
UPDATE `quest_template` SET `NextQuestIdChain`=27646 WHERE `Id`=27643;

DELETE FROM `conditions` WHERE `SourceEntry` = '27650' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27650, 27646, 0),
(20, 8, 27650, 27648, 0),
(20, 8, 27650, 27647, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27650' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27650, 27646, 0),
(19, 8, 27650, 27648, 0),
(19, 8, 27650, 27647, 0);

DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27648 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27643 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27648 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27645 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27646 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27643 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=19 AND `SourceGroup`=0 AND `SourceEntry`=27646 AND `SourceId`=0 AND `ElseGroup`=1 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=27645 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

UPDATE `quest_template` SET `PrevQuestId`='27643' WHERE `Id`=27646;
UPDATE `quest_template` SET `PrevQuestId`='27645' WHERE `Id`=27648;

DELETE FROM `creature` WHERE `guid` = '842655';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842655, 46585, 0, 1, 9, 0, 1, -4462.9, -4859.79, 123.178, 5.36492, 300, 0, 0, 619920, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '842655';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(842655, '49414');

#IMPOSTARE QUESTEND
DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27647';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_end_status`) VALUES
(49416, 5484, 27647, 1, 0);

DELETE FROM `creature_text` WHERE `entry`=46583;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46583,0,0,'An\' where you think you\'re goin\', sonny?!',14,0,100,0,0,0,'Comment'),
(46583,1,0,'Keep your hands off me ale, ya unclean pint-hatin\' mongels!',14,0,100,0,0,0,'Comment');

-- Eoin Dunwald
SET @ENTRY := 46583;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,46583,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

-- Twilight Ambusher
SET @ENTRY := 46527;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,5000,5000,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Nearest Player"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,5000,8000,11,84836,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Multi-Shot"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,4000,6000,11,80015,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Steady Shot");

-- Twilight Shadeprowler
SET @ENTRY := 46526;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,5000,5000,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Nearest Player"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,11,14873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike");

UPDATE `gameobject` SET `spawntimesecs`=60 WHERE `id`=206199;
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `dynamicflags`=0 WHERE `entry`=46526;
UPDATE `gameobject` SET `spawntimesecs`=30 WHERE `id`=206203;

DELETE FROM `creature_addon` WHERE `guid` = '757842';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(757842, '49415');

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27647';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5487, 27647, 27650, 1, 66, 11);

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (757840, 757812, 757811);

DELETE FROM `script_waypoint` WHERE `entry` = '46174';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(46174, 1, -4677.28, -4850.36, 162.51, 'Cayen WP'),
(46174, 2, -4702.18, -4872.38, 158.20, 'Cayen WP'),
(46174, 3, -4707.90, -4881.18, 156.69, 'Cayen WP'),
(46174, 4, -4717.83, -4901.66, 155.84, 'Cayen WP'),
(46174, 5, -4726.70, -4910.71, 156.05, 'Cayen WP'),
(46174, 6, -4742.00, -4928.64, 156.35, 'Cayen WP'),
(46174, 7, -4753.85, -4936.36, 158.05, 'Cayen WP'),
(46174, 8, -4765.76, -4948.66, 159.08, 'Cayen WP'),
(46174, 9, -4776.37, -4961.04, 160.37, 'Cayen WP');

DELETE FROM `creature_text` WHERE `entry`=46174;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46174,0,0,'That\'s tha spirit!',12,0,100,1,0,0,'Comment'),
(46174,1,0,'That all ya got?!',14,0,100,1,0,0,'Comment'),
(46174,2,0,'Cayden\'s got an axe with your name on it!',14,0,100,1,0,0,'Comment'),
(46174,3,0,'Come\'n get it!',14,0,100,1,0,0,'Comment');

-- Twilight Pillager
SET @ENTRY := 46144;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,6000,19000,20000,11,84442,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On OCC do emote (radom time)"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2500,3500,3500,11,14873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,100,100,5000,5000,49,0,0,0,0,0,0,11,46174,35,0,0.0,0.0,0.0,0.0,"OOC - Attack Cayden");

UPDATE `creature_template` SET `type_flags`=4096, `speed_run`=1.07, `ScriptName`='npc_th_cayden_dunwald_escort' WHERE `entry`=46174;
UPDATE `creature` SET `spawntimesecs`=15 WHERE `guid`=757842;

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (6334, 6335, 6336);
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6334, 'th_south_dunwald_hovel'),
(6335, 'th_north_dunwald_hovel'),
(6336, 'th_east_dunwald_hovel');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=46607;

DELETE FROM `creature_text` WHERE `entry`=46607;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46607,0,0,'You seem to have gained a companion. You should bring him back to Donnelly',42,0,100,0,0,0,'Comment');

-- Beak
SET @ENTRY := 46607;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk to Owner"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn");

DELETE FROM `creature_text` WHERE `entry`=46176;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46176,0,0,'Go home to Keely, She keep you safe til Donnelly come back.',12,0,100,0,0,0,'Comment');

-- Donnelly Dunwald
SET @ENTRY := 46176;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27646,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,27646,0,0,0,45,0,1,0,0,0,0,11,46607,30,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove Beak");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (772506, 776580);

#IMPOSTARE QUESTEND (NON ANCORA)
DELETE FROM `spell_area` WHERE `spell` = '81742' AND `quest_start` = '27650';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(81742, 5484, 27650, 1, 66, 0);
#IMPOSTARE QUESTEND (NON ANCORA)
DELETE FROM `spell_area` WHERE `spell` = '98392' AND `quest_start` = '27650';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(98392, 5484, 27650, 1, 66, 0);

UPDATE `quest_template` SET `PrevQuestId`='28655' WHERE `Id` IN (28863, 28860, 28864, 28861, 28862);
UPDATE `quest_template` SET `PrevQuestId`='28001' WHERE `Id` IN (27754, 28369, 27752);
UPDATE `quest_template` SET `PrevQuestId`='28377' WHERE `Id` IN (28378, 28379);

DELETE FROM `conditions` WHERE `SourceEntry` = '28216' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28216, 27752, 0),
(20, 8, 28216, 27754, 0),
(20, 8, 28216, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28216' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28216, 27752, 0),
(19, 8, 28216, 27754, 0),
(19, 8, 28216, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28211' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28211, 27752, 0),
(20, 8, 28211, 27754, 0),
(20, 8, 28211, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28211' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28211, 27752, 0),
(19, 8, 28211, 27754, 0),
(19, 8, 28211, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28212' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28212, 27752, 0),
(20, 8, 28212, 27754, 0),
(20, 8, 28212, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28212' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28212, 27752, 0),
(19, 8, 28212, 27754, 0),
(19, 8, 28212, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28215' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28215, 27752, 0),
(20, 8, 28215, 27754, 0),
(20, 8, 28215, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28215' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28215, 27752, 0),
(19, 8, 28215, 27754, 0),
(19, 8, 28215, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28241' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28241, 27752, 0),
(20, 8, 28241, 27754, 0),
(20, 8, 28241, 27753, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28241' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28241, 27752, 0),
(19, 8, 28241, 27754, 0),
(19, 8, 28241, 27753, 0);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '28369';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5142, 28369, 28244, 1, 66, 11);

-- Dragonmaw Marauder
SET @ENTRY := 46310;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,32064,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battle Shout");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=770466;
UPDATE `gameobject_template` SET `data0`=86855, `data1`=1 WHERE `entry`=206195;
UPDATE `gameobject` SET `spawntimesecs`=60 WHERE `id`=206195;

-- Obsidian Stoneslave
SET @ENTRY := 47226;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,6000,9000,11,89932,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rupture Line");

UPDATE `gameobject` SET `phaseMask`=16 WHERE `guid`=727693;

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '11';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 11, 16, 0, 'Twilight Highlands [A]: Add Phase 16 On Quest Complete: A Vision of Twilight [28241]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '11' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28241';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 11, 0, 0, 28, 0, 28241, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '12';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 12, 16, 0, 'Twilight Highlands [A]: Add Phase 16 On Quest Rewarded: A Vision of Twilight [28241]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '12' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28241';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 12, 0, 0, 8, 0, 28241, 0, 0, 0, 0, 0, '', '');

-- Unbound Emberfiend
SET @ENTRY := 48016;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3500,7000,11,35377,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scorch"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,9000,9000,9000,9000,11,11970,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire Nova");

UPDATE `creature_template` SET `lootid`=48016 WHERE `entry`=48016;

DELETE FROM `creature_loot_template` WHERE `entry` = '48016';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48016, 33363, 0.05, 1, 0, 1, 1),
(48016, 33366, 0.05, 1, 0, 1, 1),
(48016, 33383, 0.05, 1, 0, 1, 1),
(48016, 33399, 0.05, 1, 0, 1, 1),
(48016, 33417, 0.05, 1, 0, 1, 1),
(48016, 33419, 0.05, 1, 0, 1, 1),
(48016, 33425, 0.05, 1, 0, 1, 1),
(48016, 33426, 0.05, 1, 0, 1, 1),
(48016, 33429, 0.05, 1, 0, 1, 1),
(48016, 52197, 0.05, 1, 0, 1, 1),
(48016, 52325, 12.9225, 1, 0, 1, 1),
(48016, 52363, 0.05, 1, 0, 1, 1),
(48016, 52364, 0.05, 1, 0, 1, 1),
(48016, 52365, 0.05, 1, 0, 1, 1),
(48016, 52366, 0.05, 1, 0, 1, 1),
(48016, 52367, 0.05, 1, 0, 1, 1),
(48016, 52368, 0.05, 1, 0, 1, 1),
(48016, 52369, 0.05, 1, 0, 1, 1),
(48016, 52370, 0.05, 1, 0, 1, 1),
(48016, 52372, 0.05, 1, 0, 1, 1),
(48016, 52373, 0.05, 1, 0, 1, 1),
(48016, 52375, 0.0082, 1, 0, 1, 1),
(48016, 52376, 0.05, 1, 0, 1, 1),
(48016, 52377, 0.05, 1, 0, 1, 1),
(48016, 52378, 0.05, 1, 0, 1, 1),
(48016, 52382, 0.05, 1, 0, 1, 1),
(48016, 52383, 0.05, 1, 0, 1, 1),
(48016, 52385, 0.05, 1, 0, 1, 1),
(48016, 52386, 0.05, 1, 0, 1, 1),
(48016, 52388, 0.05, 1, 0, 1, 1),
(48016, 52494, 0.05, 1, 0, 1, 1),
(48016, 52495, 0.05, 1, 0, 1, 1),
(48016, 52496, 0.05, 1, 0, 1, 1),
(48016, 52506, -2.3563, 1, 0, 1, 1),
(48016, 52843, -0.0013, 1, 0, 1, 1),
(48016, 55285, 0.0057, 1, 0, 1, 1),
(48016, 55286, 0.05, 1, 0, 1, 1),
(48016, 55287, 0.05, 1, 0, 1, 1),
(48016, 55294, 0.0076, 1, 0, 1, 1),
(48016, 55295, 0.05, 1, 0, 1, 1),
(48016, 55296, 0.05, 1, 0, 1, 1),
(48016, 55303, 0.0015, 1, 0, 1, 1),
(48016, 55305, 0.0023, 1, 0, 1, 1),
(48016, 55312, 0.0117, 1, 0, 1, 1),
(48016, 55313, 0.05, 1, 0, 1, 1),
(48016, 55314, 0.05, 1, 0, 1, 1),
(48016, 55321, 0.0006, 1, 0, 1, 1),
(48016, 55322, 0.05, 1, 0, 1, 1),
(48016, 55323, 0.05, 1, 0, 1, 1),
(48016, 55330, 0.0088, 1, 0, 1, 1),
(48016, 55331, 0.05, 1, 0, 1, 1),
(48016, 55332, 0.05, 1, 0, 1, 1),
(48016, 55339, 0.0057, 1, 0, 1, 1),
(48016, 55340, 0.05, 1, 0, 1, 1),
(48016, 55341, 0.05, 1, 0, 1, 1),
(48016, 55348, 0.0033, 1, 0, 1, 1),
(48016, 55349, 0.05, 1, 0, 1, 1),
(48016, 55350, 0.05, 1, 0, 1, 1),
(48016, 55357, 0.0014, 1, 0, 1, 1),
(48016, 55358, 0.0056, 1, 0, 1, 1),
(48016, 55359, 0.003, 1, 0, 1, 1),
(48016, 55366, 0.0173, 1, 0, 1, 1),
(48016, 55367, 0.05, 1, 0, 1, 1),
(48016, 55368, 0.05, 1, 0, 1, 1),
(48016, 55375, 0.009, 1, 0, 1, 1),
(48016, 55376, 0.05, 1, 0, 1, 1),
(48016, 55377, 0.05, 1, 0, 1, 1),
(48016, 55384, 0.006, 1, 0, 1, 1),
(48016, 55385, 0.05, 1, 0, 1, 1),
(48016, 55386, 0.05, 1, 0, 1, 1),
(48016, 55393, 0.009, 1, 0, 1, 1),
(48016, 55394, 0.05, 1, 0, 1, 1),
(48016, 55395, 0.05, 1, 0, 1, 1),
(48016, 55402, 0.0213, 1, 0, 1, 1),
(48016, 55403, 0.05, 1, 0, 1, 1),
(48016, 55404, 0.05, 1, 0, 1, 1),
(48016, 55411, 0.0046, 1, 0, 1, 1),
(48016, 55412, 0.05, 1, 0, 1, 1),
(48016, 55413, 0.05, 1, 0, 1, 1),
(48016, 55420, 0.0369, 1, 0, 1, 1),
(48016, 55421, 0.05, 1, 0, 1, 1),
(48016, 55422, 0.05, 1, 0, 1, 1),
(48016, 55429, 0.0073, 1, 0, 1, 1),
(48016, 55430, 0.05, 1, 0, 1, 1),
(48016, 55431, 0.05, 1, 0, 1, 1),
(48016, 55438, 0.0202, 1, 0, 1, 1),
(48016, 55439, 0.05, 1, 0, 1, 1),
(48016, 55440, 0.05, 1, 0, 1, 1),
(48016, 55447, 0.0043, 1, 0, 1, 1),
(48016, 55448, 0.05, 1, 0, 1, 1),
(48016, 55449, 0.05, 1, 0, 1, 1),
(48016, 55456, 0.0076, 1, 0, 1, 1),
(48016, 55457, 0.05, 1, 0, 1, 1),
(48016, 55458, 0.05, 1, 0, 1, 1),
(48016, 55465, 0.0043, 1, 0, 1, 1),
(48016, 55466, 0.05, 1, 0, 1, 1),
(48016, 55467, 0.05, 1, 0, 1, 1),
(48016, 55474, 0.0026, 1, 0, 1, 1),
(48016, 55475, 0.0023, 1, 0, 1, 1),
(48016, 55476, 0.05, 1, 0, 1, 1),
(48016, 55483, 0.0185, 1, 0, 1, 1),
(48016, 55484, 0.05, 1, 0, 1, 1),
(48016, 55485, 0.05, 1, 0, 1, 1),
(48016, 55492, 0.0105, 1, 0, 1, 1),
(48016, 55493, 0.05, 1, 0, 1, 1),
(48016, 55494, 0.05, 1, 0, 1, 1),
(48016, 55501, 0.0153, 1, 0, 1, 1),
(48016, 55502, 0.05, 1, 0, 1, 1),
(48016, 55503, 0.05, 1, 0, 1, 1),
(48016, 55510, 0.0133, 1, 0, 1, 1),
(48016, 55511, 0.05, 1, 0, 1, 1),
(48016, 55512, 0.05, 1, 0, 1, 1),
(48016, 55519, 0.0128, 1, 0, 1, 1),
(48016, 55520, 0.05, 1, 0, 1, 1),
(48016, 55521, 0.05, 1, 0, 1, 1),
(48016, 55528, 0.05, 1, 0, 1, 1),
(48016, 55529, 0.05, 1, 0, 1, 1),
(48016, 55530, 0.05, 1, 0, 1, 1),
(48016, 55537, 0.0145, 1, 0, 1, 1),
(48016, 55538, 0.05, 1, 0, 1, 1),
(48016, 55539, 0.05, 1, 0, 1, 1),
(48016, 55546, 0.0148, 1, 0, 1, 1),
(48016, 55547, 0.05, 1, 0, 1, 1),
(48016, 55548, 0.05, 1, 0, 1, 1),
(48016, 55555, 0.0093, 1, 0, 1, 1),
(48016, 55556, 0.05, 1, 0, 1, 1),
(48016, 55557, 0.05, 1, 0, 1, 1),
(48016, 55564, 0.0148, 1, 0, 1, 1),
(48016, 55565, 0.05, 1, 0, 1, 1),
(48016, 55566, 0.05, 1, 0, 1, 1),
(48016, 55573, 0.0116, 1, 0, 1, 1),
(48016, 55574, 0.05, 1, 0, 1, 1),
(48016, 55575, 0.05, 1, 0, 1, 1),
(48016, 55582, 0.0252, 1, 0, 1, 1),
(48016, 55583, 0.05, 1, 0, 1, 1),
(48016, 55584, 0.05, 1, 0, 1, 1),
(48016, 55591, 0.0122, 1, 0, 1, 1),
(48016, 55592, 0.05, 1, 0, 1, 1),
(48016, 55593, 0.05, 1, 0, 1, 1),
(48016, 55600, 0.0202, 1, 0, 1, 1),
(48016, 55601, 0.05, 1, 0, 1, 1),
(48016, 55602, 0.05, 1, 0, 1, 1),
(48016, 55609, 0.011, 1, 0, 1, 1),
(48016, 55610, 0.05, 1, 0, 1, 1),
(48016, 55611, 0.05, 1, 0, 1, 1),
(48016, 55618, 0.0219, 1, 0, 1, 1),
(48016, 55619, 0.05, 1, 0, 1, 1),
(48016, 55620, 0.05, 1, 0, 1, 1),
(48016, 55627, 0.0136, 1, 0, 1, 1),
(48016, 55628, 0.05, 1, 0, 1, 1),
(48016, 55629, 0.05, 1, 0, 1, 1),
(48016, 55636, 0.0112, 1, 0, 1, 1),
(48016, 55637, 0.05, 1, 0, 1, 1),
(48016, 55638, 0.05, 1, 0, 1, 1),
(48016, 55645, 0.0131, 1, 0, 1, 1),
(48016, 55646, 0.05, 1, 0, 1, 1),
(48016, 55647, 0.05, 1, 0, 1, 1),
(48016, 55654, 0.013, 1, 0, 1, 1),
(48016, 55655, 0.05, 1, 0, 1, 1),
(48016, 55656, 0.05, 1, 0, 1, 1),
(48016, 55663, 0.0119, 1, 0, 1, 1),
(48016, 55664, 0.05, 1, 0, 1, 1),
(48016, 55665, 0.05, 1, 0, 1, 1),
(48016, 55672, 0.013, 1, 0, 1, 1),
(48016, 55673, 0.05, 1, 0, 1, 1),
(48016, 55674, 0.05, 1, 0, 1, 1),
(48016, 55681, 0.0131, 1, 0, 1, 1),
(48016, 55682, 0.05, 1, 0, 1, 1),
(48016, 55683, 0.05, 1, 0, 1, 1),
(48016, 55690, 0.0134, 1, 0, 1, 1),
(48016, 55691, 0.05, 1, 0, 1, 1),
(48016, 55692, 0.05, 1, 0, 1, 1),
(48016, 55699, 0.0142, 1, 0, 1, 1),
(48016, 55700, 0.05, 1, 0, 1, 1),
(48016, 55701, 0.05, 1, 0, 1, 1),
(48016, 55708, 0.0159, 1, 0, 1, 1),
(48016, 55709, 0.05, 1, 0, 1, 1),
(48016, 55710, 0.05, 1, 0, 1, 1),
(48016, 55717, 0.0198, 1, 0, 1, 1),
(48016, 55718, 0.05, 1, 0, 1, 1),
(48016, 55719, 0.05, 1, 0, 1, 1),
(48016, 55726, 0.0169, 1, 0, 1, 1),
(48016, 55727, 0.05, 1, 0, 1, 1),
(48016, 55728, 0.05, 1, 0, 1, 1),
(48016, 55735, 0.0171, 1, 0, 1, 1),
(48016, 55736, 0.05, 1, 0, 1, 1),
(48016, 55737, 0.05, 1, 0, 1, 1),
(48016, 55744, 0.0222, 1, 0, 1, 1),
(48016, 55745, 0.05, 1, 0, 1, 1),
(48016, 55746, 0.05, 1, 0, 1, 1),
(48016, 55753, 0.0213, 1, 0, 1, 1),
(48016, 55754, 0.05, 1, 0, 1, 1),
(48016, 55755, 0.05, 1, 0, 1, 1),
(48016, 55762, 0.0167, 1, 0, 1, 1),
(48016, 55763, 0.05, 1, 0, 1, 1),
(48016, 55771, 0.0181, 1, 0, 1, 1),
(48016, 55772, 0.05, 1, 0, 1, 1),
(48016, 55773, 0.05, 1, 0, 1, 1),
(48016, 60485, 80.3556, 1, 0, 1, 1),
(48016, 60486, 19.1412, 1, 0, 1, 1),
(48016, 62065, 0.1, 1, 0, 1, 1),
(48016, 62071, 0.1, 1, 0, 1, 1),
(48016, 62101, 0.05, 1, 0, 1, 1),
(48016, 62111, 0.05, 1, 0, 1, 1),
(48016, 62136, 0.05, 1, 0, 1, 1),
(48016, 63122, 0.0005, 1, 0, 1, 1),
(48016, 63283, -60.006, 1, 0, 1, 1),
(48016, 65894, 0.05, 1, 0, 1, 1),
(48016, 65895, 0.0116, 1, 0, 1, 1),
(48016, 65896, 0.05, 1, 0, 1, 1),
(48016, 65897, 0.05, 1, 0, 1, 1),
(48016, 66919, 0.0005, 1, 0, 1, 1),
(48016, 66920, 0.0011, 1, 0, 1, 1),
(48016, 66924, 0.0005, 1, 0, 1, 1),
(48016, 66931, 0.05, 1, 0, 1, 1),
(48016, 66932, 0.05, 1, 0, 1, 1),
(48016, 66940, 0.05, 1, 0, 1, 1),
(48016, 66941, 0.05, 1, 0, 1, 1),
(48016, 66964, 0.0014, 1, 0, 1, 1),
(48016, 66965, 0.0009, 1, 0, 1, 1),
(48016, 66966, 0.0002, 1, 0, 1, 1),
(48016, 66967, 0.0009, 1, 0, 1, 1),
(48016, 66969, 0.05, 1, 0, 1, 1),
(48016, 66971, 0.05, 1, 0, 1, 1),
(48016, 66972, 0.05, 1, 0, 1, 1),
(48016, 66974, 0.0017, 1, 0, 1, 1),
(48016, 66975, 0.05, 1, 0, 1, 1),
(48016, 66976, 0.05, 1, 0, 1, 1),
(48016, 66986, 0.0014, 1, 0, 1, 1),
(48016, 66987, 0.0009, 1, 0, 1, 1),
(48016, 66988, 0.0005, 1, 0, 1, 1),
(48016, 66989, 0.05, 1, 0, 1, 1),
(48016, 66991, 0.0127, 1, 0, 1, 1),
(48016, 66993, 0.05, 1, 0, 1, 1),
(48016, 66994, 0.0017, 1, 0, 1, 1),
(48016, 67050, 0.0009, 1, 0, 1, 1),
(48016, 67052, 0.0009, 1, 0, 1, 1),
(48016, 67057, 0.05, 1, 0, 1, 1),
(48016, 67059, 0.05, 1, 0, 1, 1),
(48016, 67061, 0.05, 1, 0, 1, 1),
(48016, 67069, 0.05, 1, 0, 1, 1),
(48016, 67071, 0.05, 1, 0, 1, 1),
(48016, 67116, 0.0011, 1, 0, 1, 1),
(48016, 67117, 0.0011, 1, 0, 1, 1),
(48016, 67118, 0.0006, 1, 0, 1, 1),
(48016, 67119, 0.05, 1, 0, 1, 1),
(48016, 67120, 0.05, 1, 0, 1, 1),
(48016, 67121, 0.05, 1, 0, 1, 1),
(48016, 67122, 0.05, 1, 0, 1, 1),
(48016, 67123, 0.05, 1, 0, 1, 1),
(48016, 67127, 0.05, 1, 0, 1, 1),
(48016, 67130, 0.0013, 1, 0, 1, 1),
(48016, 67135, 0.0003, 1, 0, 1, 1),
(48016, 67136, 0.0009, 1, 0, 1, 1),
(48016, 67137, 0.0003, 1, 0, 1, 1),
(48016, 67141, 0.0003, 1, 0, 1, 1),
(48016, 67145, 0.0007, 1, 0, 1, 1),
(48016, 67149, 0.0003, 1, 0, 1, 1),
(48016, 67539, 0.0883, 1, 0, 1, 1),
(48016, 68782, 0.004, 1, 0, 1, 1),
(48016, 68789, 0.0008, 1, 0, 1, 1);

-- Shaman of the Black
SET @ENTRY := 46322;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,78129,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Bolt"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corruption"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=46322;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46322,0,0,'Behold the powers of the master!',12,0,100,0,0,0,'Comment'),
(46322,0,1,'But a pebble against the avalanche...',12,0,100,0,0,0,'Comment'),
(46322,0,2,'Excellent, another stone to grind!',12,0,100,0,0,0,'Comment'),
(46322,0,3,'I bask in the twilight.',12,0,100,0,0,0,'Comment'),
(46322,0,4,'I will crush your bones to dust.',12,0,100,0,0,0,'Comment'),
(46322,0,5,'Stones of the earth, obey the call of the Twilight\'s Hammer!',12,0,100,0,0,0,'Comment'),
(46322,0,6,'The end of all things is upon us!',12,0,100,0,0,0,'Comment'),
(46322,0,7,'Your life is meaningless.',12,0,100,0,0,0,'Comment');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '13';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 13, 16, 4, 'Twilight Highlands [A]: Negate Phase 16 On Quest Complete: The Eyes Have It [28243]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '13' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28243';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 13, 0, 0, 28, 0, 28243, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '14';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 14, 16, 4, 'Twilight Highlands [A]: Negate Phase 16 On Quest Rewarded: The Eyes Have It [28243]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '14' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28243';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 14, 0, 0, 8, 0, 28243, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=8 WHERE `guid`=770465;

#IMPOSTARE QUESTEND
DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28243';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 5142, 28243, 1, 64, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=48116 AND `spell_id`=88237;

DELETE FROM `spell_area` WHERE `spell` = '88237' AND `quest_start` = '28243';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(88237, 4922, 28243, 28243, 1, 2);

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-64.362 WHERE `entry`=47226 AND `item`=63285;

-- Magmalord Falthazar
SET @ENTRY := 48015;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,87487,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Flame Blast"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,8000,8000,11,11962,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Immolate"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4500,4500,12500,12500,11,83018,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Magma Wave"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,14000,14000,14000,14000,11,87481,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hellfire");

UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `id`='48016';

DELETE FROM `creature_loot_template` WHERE `entry` = '48015';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(48015, 52197, 0.0053, 1, 0, 1, 1),
(48015, 52325, 12.7886, 1, 0, 1, 1),
(48015, 52366, 0.0053, 1, 0, 1, 1),
(48015, 52367, 0.0053, 1, 0, 1, 1),
(48015, 52369, 0.0053, 1, 0, 1, 1),
(48015, 52371, 0.0053, 1, 0, 1, 1),
(48015, 52375, 0.0053, 1, 0, 1, 1),
(48015, 52377, 0.0053, 1, 0, 1, 1),
(48015, 52382, 0.0053, 1, 0, 1, 1),
(48015, 52496, 0.0077, 1, 0, 1, 1),
(48015, 52506, -0.9931, 1, 0, 1, 1),
(48015, 55285, 0.0077, 1, 0, 1, 1),
(48015, 55286, 0.05, 1, 0, 1, 1),
(48015, 55287, 0.0159, 1, 0, 1, 1),
(48015, 55294, 0.0232, 1, 0, 1, 1),
(48015, 55296, 0.05, 1, 0, 1, 1),
(48015, 55304, 0.0053, 1, 0, 1, 1),
(48015, 55312, 0.0077, 1, 0, 1, 1),
(48015, 55314, 0.05, 1, 0, 1, 1),
(48015, 55323, 0.0053, 1, 0, 1, 1),
(48015, 55330, 0.0155, 1, 0, 1, 1),
(48015, 55331, 0.05, 1, 0, 1, 1),
(48015, 55332, 0.05, 1, 0, 1, 1),
(48015, 55340, 0.05, 1, 0, 1, 1),
(48015, 55348, 0.0106, 1, 0, 1, 1),
(48015, 55357, 0.0052, 1, 0, 1, 1),
(48015, 55359, 0.0053, 1, 0, 1, 1),
(48015, 55367, 0.05, 1, 0, 1, 1),
(48015, 55368, 0.05, 1, 0, 1, 1),
(48015, 55376, 0.05, 1, 0, 1, 1),
(48015, 55384, 0.0077, 1, 0, 1, 1),
(48015, 55385, 0.0264, 1, 0, 1, 1),
(48015, 55402, 0.0258, 1, 0, 1, 1),
(48015, 55403, 0.05, 1, 0, 1, 1),
(48015, 55404, 0.05, 1, 0, 1, 1),
(48015, 55411, 0.0053, 1, 0, 1, 1),
(48015, 55412, 0.05, 1, 0, 1, 1),
(48015, 55413, 0.05, 1, 0, 1, 1),
(48015, 55422, 0.05, 1, 0, 1, 1),
(48015, 55429, 0.0077, 1, 0, 1, 1),
(48015, 55431, 0.05, 1, 0, 1, 1),
(48015, 55438, 0.0387, 1, 0, 1, 1),
(48015, 55439, 0.0952, 1, 0, 1, 1),
(48015, 55440, 0.1, 1, 0, 1, 1),
(48015, 55447, 0.0026, 1, 0, 1, 1),
(48015, 55456, 0.0155, 1, 0, 1, 1),
(48015, 55457, 0.05, 1, 0, 1, 1),
(48015, 55466, 0.0317, 1, 0, 1, 1),
(48015, 55474, 0.0026, 1, 0, 1, 1),
(48015, 55483, 0.0335, 1, 0, 1, 1),
(48015, 55485, 0.05, 1, 0, 1, 1),
(48015, 55492, 0.0159, 1, 0, 1, 1),
(48015, 55494, 0.05, 1, 0, 1, 1),
(48015, 55501, 0.0155, 1, 0, 1, 1),
(48015, 55502, 0.05, 1, 0, 1, 1),
(48015, 55510, 0.0181, 1, 0, 1, 1),
(48015, 55519, 0.0155, 1, 0, 1, 1),
(48015, 55520, 0.05, 1, 0, 1, 1),
(48015, 55521, 0.05, 1, 0, 1, 1),
(48015, 55528, 0.05, 1, 0, 1, 1),
(48015, 55529, 0.0423, 1, 0, 1, 1),
(48015, 55530, 0.05, 1, 0, 1, 1),
(48015, 55537, 0.0206, 1, 0, 1, 1),
(48015, 55538, 0.0423, 1, 0, 1, 1),
(48015, 55539, 0.05, 1, 0, 1, 1),
(48015, 55546, 0.0129, 1, 0, 1, 1),
(48015, 55555, 0.0284, 1, 0, 1, 1),
(48015, 55556, 0.05, 1, 0, 1, 1),
(48015, 55557, 0.05, 1, 0, 1, 1),
(48015, 55564, 0.0106, 1, 0, 1, 1),
(48015, 55565, 0.05, 1, 0, 1, 1),
(48015, 55566, 0.05, 1, 0, 1, 1),
(48015, 55573, 0.0106, 1, 0, 1, 1),
(48015, 55574, 0.05, 1, 0, 1, 1),
(48015, 55575, 0.05, 1, 0, 1, 1),
(48015, 55593, 0.05, 1, 0, 1, 1),
(48015, 55602, 0.05, 1, 0, 1, 1),
(48015, 55609, 0.0206, 1, 0, 1, 1),
(48015, 55610, 0.05, 1, 0, 1, 1),
(48015, 55620, 0.05, 1, 0, 1, 1),
(48015, 55628, 0.05, 1, 0, 1, 1),
(48015, 55636, 0.0129, 1, 0, 1, 1),
(48015, 55637, 0.05, 1, 0, 1, 1),
(48015, 55645, 0.0258, 1, 0, 1, 1),
(48015, 55647, 0.05, 1, 0, 1, 1),
(48015, 55654, 0.0155, 1, 0, 1, 1),
(48015, 55655, 0.05, 1, 0, 1, 1),
(48015, 55663, 0.0335, 1, 0, 1, 1),
(48015, 55664, 0.05, 1, 0, 1, 1),
(48015, 55672, 0.0159, 1, 0, 1, 1),
(48015, 55673, 0.05, 1, 0, 1, 1),
(48015, 55681, 0.0258, 1, 0, 1, 1),
(48015, 55690, 0.0206, 1, 0, 1, 1),
(48015, 55691, 0.05, 1, 0, 1, 1),
(48015, 55692, 0.05, 1, 0, 1, 1),
(48015, 55699, 0.05, 1, 0, 1, 1),
(48015, 55700, 0.05, 1, 0, 1, 1),
(48015, 55709, 0.05, 1, 0, 1, 1),
(48015, 55710, 0.05, 1, 0, 1, 1),
(48015, 55717, 0.05, 1, 0, 1, 1),
(48015, 55718, 0.05, 1, 0, 1, 1),
(48015, 55719, 0.05, 1, 0, 1, 1),
(48015, 55726, 0.0159, 1, 0, 1, 1),
(48015, 55728, 0.05, 1, 0, 1, 1),
(48015, 55736, 0.05, 1, 0, 1, 1),
(48015, 55737, 0.05, 1, 0, 1, 1),
(48015, 55744, 0.0159, 1, 0, 1, 1),
(48015, 55745, 0.05, 1, 0, 1, 1),
(48015, 55746, 0.05, 1, 0, 1, 1),
(48015, 55753, 0.0206, 1, 0, 1, 1),
(48015, 55754, 0.05, 1, 0, 1, 1),
(48015, 55755, 0.05, 1, 0, 1, 1),
(48015, 55762, 0.05, 1, 0, 1, 1),
(48015, 55763, 0.05, 1, 0, 1, 1),
(48015, 55771, 0.0181, 1, 0, 1, 1),
(48015, 55772, 0.05, 1, 0, 1, 1),
(48015, 55773, 0.05, 1, 0, 1, 1),
(48015, 60485, 78.7665, 1, 0, 1, 1),
(48015, 60486, 18.9946, 1, 0, 1, 1),
(48015, 62065, 0.1, 1, 0, 1, 1),
(48015, 62101, 0.05, 1, 0, 1, 1),
(48015, 62111, 0.05, 1, 0, 1, 1),
(48015, 62132, 0.1419, 1, 0, 1, 1),
(48015, 63286, -100, 1, 0, 1, 1),
(48015, 66931, 0.0181, 1, 0, 1, 1),
(48015, 66974, 0.0053, 1, 0, 1, 1),
(48015, 67059, 0.0053, 1, 0, 1, 1),
(48015, 67115, 0.0026, 1, 0, 1, 1),
(48015, 67121, 0.0129, 1, 0, 1, 1),
(48015, 67123, 0.0053, 1, 0, 1, 1),
(48015, 67539, 0.05, 1, 0, 1, 1),
(48015, 69820, 0.0026, 1, 0, 1, 1);

UPDATE `quest_template` SET `PrevQuestId`='28346' WHERE `Id`=28377;
UPDATE `quest_template` SET `PrevQuestId`='28407' WHERE `Id` IN (28408, 28409, 28410, 28411, 28413);
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `exp`=3, `VehicleId`=1528 WHERE `entry`=48117;
UPDATE `creature_template` SET `minlevel`=80, `maxlevel`=80, `exp`=3, `VehicleId`=1257, `ScriptName`='npc_th_eye_of_twilight_veh', `InhabitType`=4 WHERE `entry`=47273;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_th_eye_of_twilight_spy', `IconName`='openhandglow' WHERE `entry`=48116;

DELETE FROM `creature_text` WHERE `entry`=48142;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48142,0,0,'This changes nothing. (Nothing nothing changes. Crush them, crush.)',12,0,100,1,0,22102,'Comment'),
(48142,1,0,'What of our agents in Stormwind? (Stormwind! The eye, the eye sees into the city heart.) Bring me the eye.',12,0,100,1,0,22103,'Comment'),
(48142,2,0,'(Blaspheme! Blaspheme disgust hate hate...) No matter. Where one eye closes, another opens. (The Master sees all! The Master knows all!) We will know our enemy\'s hearts, for they are weak. The eye. Now.',12,0,100,1,0,22105,'Comment'),
(48142,3,0,'The shadow of the Master covers this world... (Darkness, all darkness.) Our enemies fight one another, across the Highland. Fools. (Blood, blood.) WAIT! There is another!',12,0,100,1,0,22106,'Comment'),
(48142,4,0,'A mortal dares peer into the eye! (Brave little plaything.) I see you, little one! You want to see what the Eye sees, do you? (Show it! Show it all!)',12,0,100,1,0,22107,'Comment'),
(48142,5,0,'Behold the chaos to come. (Madness, madness, bliss!) Do you like what you see mortal?',12,0,100,1,0,22108,'Comment');

DELETE FROM `creature_text` WHERE `entry`=48145;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48145,0,0,'The Alliance has made landfall master, and in great numbers upon the shore.',12,0,100,0,0,21073,'Comment'),
(48145,1,0,'Our agents have been outed and killed, master.',12,0,100,0,0,21075,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_th_eye_spy_twilight_servant' WHERE `entry`=48145;
UPDATE `creature_template` SET `modelid1`=27823 WHERE `entry`=47273;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=770463;

-- Position update for Cinematic Camera Target 01 (id: 51039) in zone: 4922, area: 5503
UPDATE `creature` SET `position_x` = -5113.526, `position_y` = -4585.395, `position_z` = 369.698, `orientation`= 4.698 WHERE `guid` = 770463;

DELETE FROM `creature_template_addon` WHERE `entry` = '48142';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(48142, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '47273';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(47273, '60191');

DELETE FROM `creature_text` WHERE `entry`=48010;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48010,0,0,'Quit lookin\' at me, ya big purple eye-face! Ah, blast it all, $n.',12,0,100,0,0,0,'Comment');

-- Low Shaman Blundy
SET @ENTRY := 48010;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,28244,0,0,0,11,35426,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Arcane Explosion"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,28244,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=47380;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(47380,0,0,'(The master sees you! He sees! He sees! He wants! Wants wants...)',15,0,100,0,0,22109,'Comment');

-- Deletes creature Voice of Cho'gall (id: 47380, guid: 755573) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 755573; DELETE FROM creature_addon WHERE guid = 755573;

DELETE FROM `creature_addon` WHERE `guid` IN (755572, 755569);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(755572, '60921'),
(755569, '60921');

DELETE FROM `spell_area` WHERE `spell` = '60922' AND `quest_start` = '28001';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`) VALUES
(60922, 5142, 28001, 28244, 1);

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '15';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 15, 32, 0, 'Twilight Highlands [A]: Add Phase 32 On Quest Rewarded: Eye Spy [28244]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '15' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28244';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 15, 0, 0, 8, 0, 28244, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=32 WHERE `id` IN (48194, 52035, 48173, 48174, 48197, 47623);
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (48173, 48174);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '48197';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(48197, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '48197';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(48197, 48194, 1, 'Dragonmaw Skyclaw on Drakes', 8, 0);

UPDATE `creature_template` SET `ScriptName`='npc_th_dragonmaw_skyclaw' WHERE `entry`=48194;
UPDATE `creature_template` SET `ScriptName`='npc_th_thundermar_defender' WHERE `entry`=52035;
UPDATE `creature` SET `spawndist`=65, `MovementType`=1 WHERE `id`=48197;

-- Dragonmaw Black Drake
SET @ENTRY := 48197;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,75,89643,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Add Flame Aura");

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771161) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771161; DELETE FROM creature_addon WHERE guid = 771161;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771198) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771198; DELETE FROM creature_addon WHERE guid = 771198;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771165) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771165; DELETE FROM creature_addon WHERE guid = 771165;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771166) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771166; DELETE FROM creature_addon WHERE guid = 771166;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771167) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771167; DELETE FROM creature_addon WHERE guid = 771167;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771122) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771122; DELETE FROM creature_addon WHERE guid = 771122;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771178) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771178; DELETE FROM creature_addon WHERE guid = 771178;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771121) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771121; DELETE FROM creature_addon WHERE guid = 771121;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771160) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771160; DELETE FROM creature_addon WHERE guid = 771160;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771164) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771164; DELETE FROM creature_addon WHERE guid = 771164;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771197) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771197; DELETE FROM creature_addon WHERE guid = 771197;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771163) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771163; DELETE FROM creature_addon WHERE guid = 771163;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771185) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771185; DELETE FROM creature_addon WHERE guid = 771185;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771117) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771117; DELETE FROM creature_addon WHERE guid = 771117;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771130) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771130; DELETE FROM creature_addon WHERE guid = 771130;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771181) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771181; DELETE FROM creature_addon WHERE guid = 771181;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771173) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771173; DELETE FROM creature_addon WHERE guid = 771173;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771171) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771171; DELETE FROM creature_addon WHERE guid = 771171;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771136) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771136; DELETE FROM creature_addon WHERE guid = 771136;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771154) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771154; DELETE FROM creature_addon WHERE guid = 771154;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771132) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771132; DELETE FROM creature_addon WHERE guid = 771132;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771156) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771156; DELETE FROM creature_addon WHERE guid = 771156;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771184) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771184; DELETE FROM creature_addon WHERE guid = 771184;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771190) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771190; DELETE FROM creature_addon WHERE guid = 771190;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771134) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771134; DELETE FROM creature_addon WHERE guid = 771134;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771115) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771115; DELETE FROM creature_addon WHERE guid = 771115;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771137) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771137; DELETE FROM creature_addon WHERE guid = 771137;

-- Deletes creature Dragonmaw Skyclaw (id: 48194, guid: 771120) in zone: 4922, area: 5142
DELETE FROM `creature` WHERE `guid` = 771120; DELETE FROM creature_addon WHERE guid = 771120;

UPDATE `quest_template` SET `PrevQuestId`='28280' WHERE `Id`=28281;
UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=48197;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=48197;

DELETE FROM `spell_script_names` WHERE `spell_id` = '89557';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(89557, 'spell_th_drake_dropper');

DELETE FROM `creature_text` WHERE `entry`=48173;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48173,0,0,'Here he comes, $n! Flying in from the west. Get your weapons ready!',12,0,100,0,0,0,'Comment'),
(48173,1,0,'Oh, that\'s just like a Firebeard, can\'t see anything past yer own fat nose. We were up to arses and elbows in Dragonmaw. But did you send a single bird to help? NO!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=52025;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '52025';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(52025, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '52025';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `description`, `summontype`, `summontimer`) VALUES
(52025, 48257, 'Narkral on his Drake', 8, 0);

UPDATE `creature_template` SET `ScriptName`='npc_th_colin_thundermar' WHERE `entry`=48173;
UPDATE `creature_template` SET `ScriptName`='npc_th_narkral_drake' WHERE `entry`=52025;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=48257;

-- Narkrall Rakeclaw
SET @ENTRY := 48257;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,13730,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1500,1500,3500,7000,11,9080,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hamstring"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,4500,5500,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,6000,6000,6000,6000,11,32736,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mortal Strike"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,10000,10000,25000,25000,11,79871,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Recklessness"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,0,1000,1000,1000,1000,49,0,0,0,0,0,0,10,771111,48173,0,0.0,0.0,0.0,0.0,"OOC - Attack Colin"),
(@ENTRY,@SOURCETYPE,6,0,6,0,100,0,0,0,0,0,33,48257,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit AoE"),
(@ENTRY,@SOURCETYPE,7,0,4,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Remove Flags");

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '16';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 16, 32, 4, 'Twilight Highlands [A]: Negate Phase 32 On Quest Rewarded: The Kirthaven Summit [28294]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '16' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28294';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 16, 0, 0, 8, 0, 28294, 0, 0, 0, 0, 0, '', '');

#IMPOSTARE QUESTEND
DELETE FROM `spell_area` WHERE `spell` = '60922' AND `quest_start` = '28294';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(60922, 5143, 28294, 1, 66, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=770467;

DELETE FROM `conditions` WHERE `SourceEntry` = '28655' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28655, 28411, 0),
(20, 8, 28655, 28410, 0),
(20, 8, 28655, 28409, 0),
(20, 8, 28655, 28408, 0),
(20, 8, 28655, 28413, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28655' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28655, 28411, 0),
(19, 8, 28655, 28410, 0),
(19, 8, 28655, 28409, 0),
(19, 8, 28655, 28408, 0),
(19, 8, 28655, 28413, 0);

DELETE FROM `creature_text` WHERE `entry`=48364;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48364,0,0,'Here, what\'s this?',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=48410;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48410,0,0,'Haaaaaalp!',14,0,100,0,0,0,'Comment'),
(48410,1,0,'The Glopgut ogres stormed Thundermar while Colin was here at the summit. They kidnapped Fanny and ran for the hills!',12,0,100,0,0,0,'Comment'),
(48410,2,0,'Colin is massing the Thundermar for a full-on assault of Glopgut\'s Hollow.',12,0,100,0,0,0,'Comment');

-- Keegan Firebeard
SET @ENTRY := 48364;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,28346,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,28346,0,0,0,12,48410,3,60000,0,0,0,8,0,0,0,-2758.3,-5319.09,173.71,0.88,"On Quest Rewarded - Summon Creature");

-- Cliff Thundermar
SET @ENTRY := 48410;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,100,100,60000,60000,69,0,0,0,0,0,0,8,0,0,0,-2746.59,-5303.7,174.07,0.87,"OOC - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,50,50,60000,60000,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,50,50,60000,60000,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,48410,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,48410,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,48410,0,0,41,30000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Force Despawn ");

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '17';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 17, 64, 0, 'Twilight Highlands [A]: Add Phase 64 On Quest Complete: Rescue at Glopgut\'s Hollow [28377]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '17' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '28377';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 17, 0, 0, 28, 0, 28377, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '4922' AND `entry` = '18';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4922, 18, 64, 0, 'Twilight Highlands [A]: Add Phase 64 On Quest Rewarded: Rescue at Glopgut\'s Hollow [28377]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '4922' AND `SourceEntry` = '18' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '28377';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 4922, 18, 0, 0, 8, 0, 28377, 0, 0, 0, 0, 0, '', '');

UPDATE `creature` SET `phaseMask`=64 WHERE `id` IN (48472, 48473, 48476, 48474, 48479, 48498, 48480);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '48476';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(48476, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '48476';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(48476, 48477, 1, 'Firebeard Gryphon Rider on Gryphon', 8, 0);

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=48476;
UPDATE `creature` SET `spawndist`=65, `MovementType`=1 WHERE `id`=48476;
UPDATE `creature` SET `spawndist`=6, `MovementType`=1 WHERE `id` IN (48474, 48479, 47768, 48498);

-- Position update for Glopgut Warhound (id: 48479) in zone: 4922, area: 5639
UPDATE `creature` SET `position_x` = -3344.542, `position_y` = -4423.891, `position_z` = 173.200, `orientation`= 3.657 WHERE `guid` = 771215;

-- Position update for Glopgut Pounder (id: 48474) in zone: 4922, area: 5639
UPDATE `creature` SET `position_x` = -3385.469, `position_y` = -4477.419, `position_z` = 171.233, `orientation`= 2.276 WHERE `guid` = 771108;

-- Position update for Thundermar Defender (id: 48473) in zone: 4922, area: 5639
UPDATE `creature` SET `position_x` = -3363.154, `position_y` = -4445.811, `position_z` = 171.606, `orientation`= 5.527 WHERE `guid` = 771045;

-- Position update for Thundermar Defender (id: 48473) in zone: 4922, area: 5639
UPDATE `creature` SET `position_x` = -3356.785, `position_y` = -4436.316, `position_z` = 174.702, `orientation`= 5.979 WHERE `guid` = 771057;

-- Position update for Thundermar Defender (id: 48473) in zone: 4922, area: 5639
UPDATE `creature` SET `position_x` = -3364.867, `position_y` = -4453.516, `position_z` = 170.202, `orientation`= 5.720 WHERE `guid` = 771053;

UPDATE `gameobject` SET `phaseMask`=64 WHERE `guid` IN (728556, 728555);

DELETE FROM `conditions` WHERE `SourceEntry` = '28407' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28407, 28378, 0),
(20, 8, 28407, 28379, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28407' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28407, 28378, 0),
(19, 8, 28407, 28379, 0);

-- Brogg Glopgut
SET @ENTRY := 48480;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,4500,7500,11,8374,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Arcing Smash"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8500,8500,20000,20000,11,75967,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Whirlwind");