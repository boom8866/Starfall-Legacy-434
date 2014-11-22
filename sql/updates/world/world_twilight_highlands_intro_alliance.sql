UPDATE `creature_template` SET `modelid2`=31201 WHERE `entry`=1747;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11874 AND `id`=0;
UPDATE `creature_template` SET `gossip_menu_id`=11874 WHERE `entry`=1747;

DELETE FROM `conditions` WHERE `SourceGroup`=11874 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11874, 0, 0, 0, 9, 0, 26960, 0, 0, 0, 0, 0, '', 'Anduin - Show gossip only if quest 26960 is active');

DELETE FROM `spell_area` WHERE `spell` = '82809' AND `quest_start` = '28716';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(82809, 1519, 28716, 26960, 1, 66, 11);

DELETE FROM `creature_text` WHERE `entry`=1747;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(1747,0,0,'You really have a way with people, $n. They fear and respect you.',12,0,100,0,0,0,'Comment');

-- Anduin Wrynn
SET @ENTRY := 1747;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11874,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11874,0,0,0,85,83451,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11874,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11874,0,0,0,5,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Bow"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invisible");

DELETE FROM `gossip_menu` WHERE `entry`=11874 AND `text_id`=16682;
DELETE FROM `gossip_menu` WHERE `entry`=11874 AND `text_id`=16641;

UPDATE `quest_template` SET `PrevQuestId`='26960' WHERE `Id` IN (26975, 26977);

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `npcflag`=3, `exp`=3, `InhabitType`=7, `ScriptName`='npc_th_anduinn_wrynn' WHERE `entry`=44293;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `InhabitType`=4 WHERE `entry`=44356;
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=26975;

DELETE FROM `spell_area` WHERE `spell` = '82823' AND `quest_start` = '26960';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(82823, 1519, 26960, 27064, 0, 0, 2, 1, 66, 11);

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6214';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6214, 'at_stormwind_graves');

DELETE FROM `creature_text` WHERE `entry`=44293;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44293,0,0,'Are you often sent to gather things for people? I suppose a hero\'s work is never done.',12,0,100,1,0,0,'Comment'),
(44293,1,0,'Does this feel like a wild goose chase to you? These workers don\'t know anything!',12,0,100,1,0,0,'Comment'),
(44293,2,0,'Hmmmm... no valuable information there.',12,0,100,0,0,0,'Comment'),
(44293,3,0,'Can I help you with the Twilight\'s Hammer investigation? We don\'t have to tell my father...',15,0,100,1,0,0,'Comment'),
(44293,4,0,'What IS this place? Ugh, and that smell...',12,0,100,0,0,0,'Comment'),
(44293,5,0,'Some sort of rituals were performed at this altar, it looks like a kind of pagan initiation ritual that Valen once told me about. Bloody. Disgusting.',12,0,100,1,0,0,'Comment'),
(44293,6,0,'Who do you think - wait - $n, look out behind you!',12,0,100,1,0,0,'Comment'),
(44293,7,0,'Look out - I see another!',12,0,100,1,0,0,'Comment'),
(44293,8,0,'Fight them back - I can\'t hold this shield up much longer!',12,0,100,1,0,0,'Comment'),
(44293,9,0,'$n, you did it. It looks like they\'re fleeing.',12,0,100,1,0,0,'Comment'),
(44293,10,0,'Hey $n, we don\'t have to tell my father about that little ambush, If he finds out about an attempt on my life, he\'d never allow me out of that keep...',12,0,100,1,0,0,'Comment'),
(44293,11,0,'Here we go. Nobody here will question it if the Prince wants to glance through some files.',12,0,100,1,0,0,'Comment'),
(44293,12,0,'Hmmmm....',12,0,100,1,0,0,'Comment'),
(44293,13,0,'This is all wrong. There\'s nothing in here about the Twilight\'s Hammer. What is Samuelson playing at?',12,0,100,1,0,0,'Comment');

-- Supply Sergeant Graves
SET @ENTRY := 44749;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27038,0,0,0,1,0,5000,0,0,0,0,11,44293,15,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk Anduin");

DELETE FROM `spell_script_names` WHERE `spell_id` = '82823';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(82823, 'spell_summon_generic_controller');

UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=27044;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=29152;

DELETE FROM `creature_addon` WHERE `guid` IN (31395, 31402, 31401);
INSERT INTO `creature_addon` (`guid`, `bytes1`, `bytes2`, `emote`) VALUES
(31395, 8, 257, 173),
(31402, 8, 257, 173),
(31401, 8, 257, 173);

UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE `id` = '29152' AND `guid` NOT IN (31395, 31402, 31401);
UPDATE `creature_template` SET `speed_run`=3.10 WHERE `entry`=44356;

DELETE FROM `creature_text` WHERE `entry`=29152;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(29152,0,0,'I don\'t know anything about a cult! Please let me get back to work...',12,0,100,0,0,0,'Comment'),
(29152,0,1,'I haven\'t heard a thing. I swear!',12,0,100,0,0,0,'Comment'),
(29152,0,2,'I swear that guy was dead when I found him! What - oh - Twilight\'s Hammer? No, I don\'t know anything about that.',12,0,100,0,0,0,'Comment'),
(29152,0,3,'I\'m innocent. Innocent I tell you! The Cataclysm isn\'t my fault!',12,0,100,0,0,0,'Comment'),
(29152,0,4,'Tw- Tw- Twilight\'s Ha- Hammer? Keep them away from me!',12,0,100,0,0,0,'Comment'),
(29152,0,5,'Twilight\'s Hammer? I don\'t know anything! Why are you asking me?',12,0,100,0,0,0,'Comment'),
(29152,0,6,'What are you asking me for? I just schlepp boxes!',12,0,100,0,0,0,'Comment'),
(29152,0,7,'What, that crazy end-of-the-world cult? If I hear anything, you\'ll be the first to know!',12,0,100,0,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceEntry` = '83577';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 83577, 0, 0, 31, 0, 3, 29152, 0, 0, 0, '', 'Targeting -> Stormwind Dock Worker');

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=44806;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6218';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6218, 'areatrigger_th_wollerton_stead');

DELETE FROM `conditions` WHERE `SourceEntry` = '27060' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27060, 26997, 0),
(20, 8, 27060, 27044, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27060' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27060, 26997, 0),
(19, 8, 27060, 27044, 0);

UPDATE `gameobject` SET `phaseMask`=4096 WHERE `id`=205162;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6219';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6219, 'areatrigger_th_crime_scene');

DELETE FROM `phase_definitions` WHERE `zoneId` = '1519' AND `entry` = '7';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(1519, 7, 4097, 0, 'Stormwind: Add Phase 4097 On Quest Accepted: Unholy Cow [27060]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '1519' AND `SourceEntry` = '7' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '27060';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 1519, 7, 0, 0, 9, 0, 27060, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '1519' AND `entry` = '8';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(1519, 8, 4096, 4, 'Stormwind: Negate Phase 4096 On Quest Rewarded: Unholy Cow [27060]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '1519' AND `SourceEntry` = '8' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '27060';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 1519, 8, 0, 0, 8, 0, 27060, 0, 0, 0, 0, 0, '', '');

UPDATE `creature_template` SET `scale`=4, `flags_extra`=128 WHERE `entry`=50253;
UPDATE `gameobject` SET `phaseMask`=4096 WHERE `guid` IN (30698, 46175);
UPDATE `creature_template` SET `dmg_multiplier`=1.5, `baseattacktime`=2000, `rangeattacktime`=2000, `ScriptName`='npc_th_twilight_striker' WHERE `entry`=44808;
UPDATE `creature_template` SET `unit_flags`=0, `unit_class`=8 WHERE `entry`=44293;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6224';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6224, 'areatrigger_th_si7');

UPDATE `creature` SET `phaseMask`=8192, `spawndist`=5, `MovementType`=1, `spawntimesecs`=120 WHERE `id`=44814;
UPDATE `creature` SET `phaseMask`=8192 WHERE `id` IN (50049, 50135, 44815, 44816, 44957);
UPDATE `gameobject` SET `phaseMask`=8192 WHERE `guid` IN (728518, 728538);

DELETE FROM `phase_definitions` WHERE `zoneId` = '1519' AND `entry` = '9';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(1519, 9, 8193, 0, 'Stormwind: Add Phase 8193 On Quest Accept: The Old Barracks [27072]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '1519' AND `SourceEntry` = '9' AND `ConditionTypeOrReference` = '9' AND `ConditionValue1` = '27072';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 1519, 9, 0, 0, 9, 0, 27072, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '1519' AND `entry` = '10';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(1519, 10, 8193, 0, 'Stormwind: Add Phase 8193 On Quest Complete: The Old Barracks [27072]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '1519' AND `SourceEntry` = '10' AND `ConditionTypeOrReference` = '28' AND `ConditionValue1` = '27072';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 1519, 10, 0, 0, 28, 0, 27072, 0, 0, 0, 0, 0, '', '');

DELETE FROM `phase_definitions` WHERE `zoneId` = '1519' AND `entry` = '11';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(1519, 11, 8192, 0, 'Stormwind: Add Phase 8192 On Quest Rewarded: The Old Barracks [27072]');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = '25' AND `SourceGroup` = '1519' AND `SourceEntry` = '11' AND `ConditionTypeOrReference` = '8' AND `ConditionValue1` = '27072';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 1519, 11, 0, 0, 8, 0, 27072, 0, 0, 0, 0, 0, '', '');

-- Crazed Cultist
SET @ENTRY := 44814;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,15,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,0,0,15,0,5000,5000,9000,9000,75,84535,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Zealotry");

DELETE FROM `creature_text` WHERE `entry`=44814;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44814,0,0,'All will fall to the master\'s call....',12,0,100,0,0,0,'Comment'),
(44814,0,1,'Biting... clawing... clutching... tearing...',12,0,100,0,0,0,'Comment'),
(44814,0,2,'Do you not feel the master\'s gaze?! It watches us all!',12,0,100,0,0,0,'Comment'),
(44814,0,3,'Embrace the coming of the end!',12,0,100,0,0,0,'Comment'),
(44814,0,4,'I will prove myself to the master!',12,0,100,0,0,0,'Comment'),
(44814,0,5,'The master will end everything!',12,0,100,0,0,0,'Comment'),
(44814,0,6,'This is the end... for you, and for the world.',12,0,100,0,0,0,'Comment'),
(44814,0,7,'Whispers... whispers... I can hear the whispers....',12,0,100,0,0,0,'Comment');

-- Position update for Crazed Cultist (id: 44814) in zone: 1519, area: 5409
UPDATE `creature` SET `position_x` = -8679.798, `position_y` = 957.497, `position_z` = 101.203, `orientation`= 2.062 WHERE `guid` = 770967;

-- Adds Waypoint Movement to Babbling Cultist (guid: 770942, entry: 50135)
SET @GUID  := 770942;
SET @WP_ID := 7709420;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
UPDATE `creature_addon` SET `path_id` = 7709420 WHERE `guid` = 770942;
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -8465.680, 820.635, 81.612, 0),
(@WP_ID, 2, -8461.030, 814.828, 81.612, 0),
(@WP_ID, 3, -8463.040, 810.500, 81.612, 0),
(@WP_ID, 4, -8472.650, 804.263, 81.610, 0),
(@WP_ID, 5, -8484.060, 794.113, 81.608, 0);

-- Adds Waypoint Movement to Warped Cultist (guid: 770993, entry: 44815)
SET @GUID  := 770993;
SET @WP_ID := 7709930;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 770993;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(770993, 7709930, 0, 0, 1, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -8511.120, 800.321, 81.613, 0),
(@WP_ID, 2, -8522.520, 791.424, 81.614, 0),
(@WP_ID, 3, -8517.290, 784.274, 81.614, 0),
(@WP_ID, 4, -8522.830, 790.966, 81.616, 0),
(@WP_ID, 5, -8510.850, 800.516, 81.615, 0),
(@WP_ID, 6, -8502.970, 806.136, 81.613, 0);

DELETE FROM `creature_text` WHERE `entry`=50135;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(50135,0,0,'Gillari, geth\'shar. Gillari, teko\'shar. It sees. It knows.',12,0,100,0,0,0,'Comment'),
(50135,0,1,'My eyes are opened, yet they see only black.',12,0,100,0,0,0,'Comment'),
(50135,0,2,'Nothing, nothing, we are nothing. The grasper touches our hearts and clenches his fist.',12,0,100,0,0,0,'Comment'),
(50135,0,3,'Shethnoth, ol\'goth, grell. Such is the mantra of those who come.',12,0,100,0,0,0,'Comment'),
(50135,0,4,'The harbinger has come. The world heaves.',12,0,100,0,0,0,'Comment'),
(50135,0,5,'The shadow sees. Bal\'qwari Og Shadar. The end comes!',12,0,100,0,0,0,'Comment'),
(50135,0,6,'The sun eclipses. Darkness crawls through earth and ash. The seas are as blood...',12,0,100,0,0,0,'Comment');

-- Babbling Cultist
SET @ENTRY := 50135;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,10,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=44815;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44815,0,0,'All will fall to the master\'s call....',12,0,100,0,0,0,'Comment'),
(44815,0,1,'Biting... clawing... clutching... tearing...',12,0,100,0,0,0,'Comment'),
(44815,0,2,'Do you not feel the master\'s gaze?! It watches us all!',12,0,100,0,0,0,'Comment'),
(44815,0,3,'Embrace the coming of the end!',12,0,100,0,0,0,'Comment'),
(44815,0,4,'I will prove myself to the master!',12,0,100,0,0,0,'Comment'),
(44815,0,5,'The master will end everything!',12,0,100,0,0,0,'Comment'),
(44815,0,6,'This is the end... for you, and for the world.',12,0,100,0,0,0,'Comment'),
(44815,0,7,'Whispers... whispers... I can hear the whispers....',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=44816;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44816,0,0,'Bishop threatens pawn...',12,0,100,0,0,0,'Comment'),
(44816,1,0,'Check!',12,0,100,0,0,0,'Comment'),
(44816,2,0,'Pawn ... takes ... bishop ...',12,0,100,0,0,0,'Comment'),
(44816,3,0,'The Bishop moves diagonally!',12,0,100,0,0,0,'Comment'),
(44816,4,0,'The game is afoot! But you are a mere pawn, whereas I am ... THE BLACK BISHOP!',12,0,100,0,0,0,'Comment'),
(44816,5,0,'The game isn\'t over yet...',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry`=44957;
UPDATE `creature_template` SET `dmg_multiplier`=1.9, `ScriptName`='npc_th_the_black_bishop' WHERE `entry`=44816;
UPDATE `creature` SET `spawntimesecs`=120 WHERE `guid`=770969;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11909 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=11909 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11909, 0, 0, 0, 9, 0, 27106, 0, 0, 0, 0, 0, '', 'Major Samuelson - Show gossip only if quest 27106 is active');

DELETE FROM `conditions` WHERE `SourceEntry` = '82545';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 82545, 0, 0, 31, 0, 3, 2439, 0, 0, 0, '', 'Targeting -> Major Samuelson');

DELETE FROM `creature_text` WHERE `entry`=2439;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2439,0,0,'Gods of shadow, lords of twilight ... give me strength!',14,0,100,0,0,0,'Comment'),
(2439,1,0,'Al\'golath mal shal\'nel... darkness consumes...',12,0,100,0,0,0,'Comment'),
(2439,2,0,'But I am not yet finished. Death to the king!',12,0,100,0,0,0,'Comment'),
(2439,3,0,'Yes... It\'s all true. I am not ashamed. The powers I submit to make mortal kings look like insects.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_th_major_samuelson' WHERE `entry`=2439;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (230,231,232,257,258,259,260);
UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=2439;

-- Stormwind Royal Guard
SET @ENTRY := 1756;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Invisibility");

-- King Varian Wrynn
SET @ENTRY := 29611;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invisible");

-- Genn Greymane
SET @ENTRY := 45253;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,75,60191,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invisible");

UPDATE `quest_template` SET `PrevQuestId`='27060' WHERE `Id`=27064;

DELETE FROM `creature` WHERE `guid` = '840956';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(840956, 44806, 0, 1, 1, 0, 0, -8542.48, 1269.14, 4.54385, 4.75035, 300, 0, 0, 96744, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '840956';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(840956, '93308');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=770927;

DELETE FROM `spell_area` WHERE `spell` = '93310' AND `quest_start` = '28238';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(93310, 4411, 28238, 28832, 1, 66);

UPDATE `creature_template` SET `VehicleId`=1415, `InhabitType`=4 WHERE `entry`=50266;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '50266';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(50266, 44806, 1, 1, 'Fargo on Seaplane', 8, 0);

DELETE FROM `creature_text` WHERE `entry`=44806;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44806,0,0,'Yep! Off we go.',12,0,100,0,0,0,'Comment'),
(44806,1,0,'Easy ... does it...',12,0,100,0,0,0,'Comment'),
(44806,2,0,'Oh, like you coulda done any better.',12,0,100,0,0,0,'Comment'),
(44806,3,0,'Right then. I hate long plane rides. So I\'mma gonna kick in the after-market burners and ignite our entire fuel supply in one go.',12,0,100,0,0,0,'Comment'),
(44806,4,0,'Whatever yeh do... Don\'t. Black. Out!',12,0,100,0,0,0,'Comment');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '50266';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(50266, 63313, 0);

DELETE FROM `script_waypoint` WHERE `entry` = '50266';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(50266, 1, -8554.75, 1390.75, 13.25, 'Fargo Seaplane WP'),
(50266, 2, -8470.32, 1399.85, 39.95, 'Fargo Seaplane WP'),
(50266, 3, -8463.27, 1274.09, 48.67, 'Fargo Seaplane WP'),
(50266, 4, -8476.89, 1122.44, 114.58, 'Fargo Seaplane WP - FALL'),
(50266, 5, -8484.94, 1091.76, 65.22, 'Fargo Seaplane WP'),
(50266, 6, -8513.28, 1050.51, 108.47, 'Fargo Seaplane WP'),
(50266, 7, -8649.27, 929.07, 107.40, 'Fargo Seaplane WP'),
(50266, 8, -8895.87, 693.79, 168.18, 'Fargo Seaplane WP'),
(50266, 9, -8772.58, 639.40, 168.26, 'Fargo Seaplane WP - BOOST'),
(50266, 10, -8482.24, 518.20, 192.54, 'Fargo Seaplane WP');

-- Fargo Flintlocke
SET @ENTRY := 44806;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,28832,0,0,0,85,93320,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Seaplane");

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `unit_flags`=768, `ScriptName`='npc_th_flintlocke_seaplane' WHERE `entry`=50266;

-- Deletes creature Tidebreaker Sailor (id: 49028, guid: 764979) in zone: 4922, area: 5140
DELETE FROM `creature` WHERE `guid` = 764979; DELETE FROM creature_addon WHERE guid = 764979;

-- Deletes creature Tidebreaker Sailor (id: 49028, guid: 764726) in zone: 4922, area: 5140
DELETE FROM `creature` WHERE `guid` = 764726; DELETE FROM creature_addon WHERE guid = 764726;

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (764980, 764707, 764265, 764264);
UPDATE `creature_template` SET `modelid2`=26556 WHERE `entry`=50300;

DELETE FROM `creature_addon` WHERE `guid` = '764264';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(764264, '83305');

UPDATE `creature_template` SET `modelid1`=26556, `modelid2`=26556, `InhabitType`=4 WHERE `entry`=50300;
UPDATE `creature_addon` SET `bytes1`=1, `auras`='83305 93391' WHERE `guid`=764264;

DELETE FROM `creature_text` WHERE `entry`=49252;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(49252,0,0,'Oh, like you coulda done any better.',12,0,100,5,0,0,'Comment');