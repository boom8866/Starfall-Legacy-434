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
(@CGUID+4, 46807, 0, 1, 4, 0, 1, -4160.34, -5587.1, 30.1261, 0.528485, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+5, 46807, 0, 1, 4, 0, 1, -4178, -5582.61, 28.6213, 2.21788, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+6, 46807, 0, 1, 4, 0, 1, -4168.7, -5600.26, 27.8857, 0.0328991, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+7, 46807, 0, 1, 4, 0, 1, -4183.61, -5604.76, 25.6744, 3.74705, 30, 0, 0, 85239, 0, 0, 0, 0, 0),
(@CGUID+8, 46807, 0, 1, 4, 0, 1, -4186.6, -5603.57, 25.3942, 4.67617, 30, 0, 0, 85239, 0, 0, 0, 0, 0);

SET @CGUID := 841876;
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+8;
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(@CGUID+0, 1, '87270'),
(@CGUID+1, 1, '87270'),
(@CGUID+2, 1, '87270'),
(@CGUID+3, 1, '87270'),
(@CGUID+4, 1, '87270'),
(@CGUID+5, 1, '87270'),
(@CGUID+6, 1, '87270'),
(@CGUID+7, 1, '87270'),
(@CGUID+8, 1, '87270');

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