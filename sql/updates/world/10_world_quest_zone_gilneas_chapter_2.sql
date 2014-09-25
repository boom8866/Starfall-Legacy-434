DELETE FROM `creature_text` WHERE `entry`=34571;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34571,0,0,'Welcome back, $n. You were fortunate. Krennan\'s treatment doesn\'t always work this well on people who\'ve had the Curse as long as you.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=36132;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36132,0,0,'Do exercise caution. Don\'t expect anyone to invite you to their homes just yet. But at least they won\'t shoot you outright.',12,0,100,0,0,0,'Comment');

-- Krennan Aranas
SET @ENTRY := 36132;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,14313,0,0,0,1,0,8000,0,0,0,0,10,798902,34571,0,0.0,0.0,0.0,0.0,"On Quest Reward - Talk 0 Gwen"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,34571,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 0");

UPDATE `creature_template` SET `flags_extra`=0, `ScriptName`='npc_forsaken_invader' WHERE `entry`=34511;
UPDATE `creature_template` SET `ScriptName`='npc_duskhaven_watchman' WHERE `entry`=36211;

-- Prince Liam Greymane
SET @ENTRY := 36140;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,1032,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Immune"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,6000,4000,6500,11,68552,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Throw Bottle");

UPDATE `creature_template` SET `ScriptName`='npc_dh_forsaken_catapult' WHERE `entry`=36283;
UPDATE `creature` SET `spawntimesecs`=120 WHERE `id`='36283';

DELETE FROM `conditions` WHERE `SourceEntry` = '68591' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 68591, 0, 0, 31, 0, 3, 36286, 0, 0, 0, '', 'Targeting -> Catapult Triggers');

DELETE FROM `spell_script_names` WHERE `spell_id` = '68591';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(68591, 'spell_catapult_boulder');

UPDATE `creature_template` SET `npcflag`=0 WHERE `entry`=36283;
UPDATE `npc_spellclick_spells` SET `spell_id`=46598 WHERE `npc_entry`=36283 AND `spell_id`=69434;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '56007';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(56007, 'Your mother\'s in the basement next door. Get to her now!', 1, 1);

UPDATE `creature_template` SET `gossip_menu_id`=56007 WHERE `entry`=36289;
UPDATE `creature` SET `spawndist`=8, `MovementType`=1, `spawntimesecs`=60 WHERE `guid`=799075;

DELETE FROM `conditions` WHERE `SourceGroup`=56007 AND `SourceEntry` = '0';

DELETE FROM `creature_text` WHERE `entry`=36289;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36289,0,0,'Don\'t hurt me! I was just looking for my sister! I think Ashley\'s inside that house!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_dh_james' WHERE `entry`=36289;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_dh_ashley' WHERE `entry`=36288;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_dh_cynthia' WHERE `entry`=36287;

DELETE FROM `conditions` WHERE `SourceEntry` = '68659' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 68659, 0, 0, 31, 0, 3, 36286, 0, 0, 0, '', 'Targeting -> Catapult Triggers');

DELETE FROM `creature_text` WHERE `entry`=36288;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36288,0,0,'Are you one of the good worgen, mister? Did you see Cynthia hinding in the sheds outside?',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=36287;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36287,0,0,'You are scary! I just want my mommy!',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `spawntimesecs`=120 WHERE `map`='654' AND `spawntimesecs` >= '120';
UPDATE `creature` SET `phaseMask`=4096 WHERE `id`=36211;
UPDATE `creature_template` SET `ScriptName`='npc_forsaken_footsoldier' WHERE `entry`=36236;
UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE `id`='36236';
UPDATE `creature` SET `spawndist`=5, `MovementType`=1 WHERE `id`='36211';
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=36211;

DELETE FROM `conditions` WHERE `SourceEntry` = '68659' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 68659, 0, 0, 31, 0, 3, 36286, 0, 0, 0, '', 'Targeting -> Catapult Triggers');

DELETE FROM `spell_script_names` WHERE `spell_id` = '68659';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(68659, 'spell_load_catapult_boulder');

DELETE FROM `conditions` WHERE `SourceEntry` = '14386' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 14386, 14382, 0),
(20, 8, 14386, 14369, 0),
(20, 8, 14386, 14368, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '14386' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 14386, 14382, 0),
(19, 8, 14386, 14369, 0),
(19, 8, 14386, 14368, 0);

DELETE FROM `creature_template_addon` WHERE `entry` = '36312';
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes2`) VALUES
(36312, 10718, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` = '68682';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(68682, 'spell_call_attack_mastiffs');

DELETE FROM `event_scripts` WHERE `id` = '22388';
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `x`, `y`, `z`, `o`) VALUES
(22388, 2, 10, 36409, 60, -1957.08, 2680.12, 0.60, 1.35),
(22388, 2, 10, 36409, 60, -1944.69, 2665.62, 0.96, 1.61),
(22388, 2, 10, 36409, 60, -1948.55, 2667.41, 0.88, 1.70),
(22388, 4, 10, 36409, 60, -1952.68, 2674.89, 0.69, 1.54),
(22388, 4, 10, 36409, 60, -1973.49, 2694.47, 0.95, 0.22),
(22388, 4, 10, 36409, 60, -1976.15, 2702.74, 0.59, 6.10),
(22388, 7, 10, 36409, 60, -1957.08, 2680.12, 0.60, 1.35),
(22388, 7, 10, 36409, 60, -1944.69, 2665.62, 0.96, 1.61),
(22388, 7, 10, 36409, 60, -1948.55, 2667.41, 0.88, 1.70);

-- Attack Mastiff
SET @ENTRY := 36409;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,100,100,5000,5000,49,0,0,0,0,0,0,11,36312,100,0,0.0,0.0,0.0,0.0,"OOC - Attack Dark Ranger"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,15000,15000,11,68687,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Leap"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4000,4000,5000,5000,11,26281,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Taunt"),
(@ENTRY,@SOURCETYPE,3,0,0,0,75,0,3500,15500,3500,1500,11,15971,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Demoralizing Roar");

-- Dark Ranger Thyala
SET @ENTRY := 36312;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,100,100,2000,2000,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

UPDATE `creature_template` SET `mindmg`=6, `maxdmg`=9, `attackpower`=2, `dmg_multiplier`=7 WHERE `entry`=36312;
UPDATE `creature_template` SET `mindmg`=2, `maxdmg`=4, `attackpower`=1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=36409;

-- Dark Ranger Thyala
SET @ENTRY := 36312;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,100,100,2000,2000,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,43,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Dismount"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,33,0,0,0,0,0,0,18,60,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit AoE");

-- Lord Godfrey
SET @ENTRY := 36290;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,14386,0,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,36290,0,0,1,0,3500,0,0,0,0,10,799039,36291,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 0 (Melinda)");

DELETE FROM `creature_text` WHERE `entry`=36291;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36291,0,0,'What\'s happening?!',12,0,100,430,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=36290;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36290,0,0,'Hold your positions, men!',14,0,100,5,0,0,'Comment'),
(36290,1,0,'Impossible!',14,0,100,5,0,0,'Comment'),
(36290,2,0,'Crowley! You and your elven allies are hereby ordered to serve along the king\'s army. Cursed or not, you are still bound by Gilnean law!',12,0,100,0,0,0,'Comment'),
(36290,3,0,'No... I\'d sooner die than have one of your kind for a king!',12,0,100,0,0,0,'Comment');

-- Prince Liam Greymane
SET @ENTRY := 36451;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14395,0,0,0,85,68735,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Add Quest Buff"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,5000,5000,5000,45,0,1,0,0,0,0,11,36440,10,0,0.0,0.0,0.0,0.0,"OOC - Set Data 1 to Drowning Watchmans"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,14395,0,0,0,28,68735,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove Quest Buff");

-- Drowning Watchman
SET @ENTRY := 36440;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,8,64,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Ride Player"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,28,46598,0,0,0,0,0,18,2,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove From Player"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Vehicle"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,0,3000,0,0,0,0,18,5,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,36440,0,0,69,0,0,0,0,0,0,8,0,0,0,-1875.87,2514.3,1.39,6.1,"After Talk 0 - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,33,36450,0,0,0,0,0,18,2,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,7,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run");

DELETE FROM `creature_text` WHERE `entry`=36440;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36440,0,0,'Thank you... *gasp* I owe you my life.',12,0,100,0,0,0,'Comment'),
(36440,0,1,'The land gave way from under our feet... I thought I was dead. I owe you one.',12,0,100,0,0,0,'Comment'),
(36440,0,2,'I... I thought I was a goner. Thanks.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=36540;
UPDATE `creature_template` SET `ScriptName`='npc_mountain_horse' WHERE `entry`=36540;
UPDATE `creature_template` SET `ScriptName`='npc_mountain_horse_summoned' WHERE `entry`=36555;
UPDATE `creature_template` SET `speed_walk`=1, `speed_run`=1.71429 WHERE `entry`=36555;
UPDATE `creature` SET `phaseMask`=2048 WHERE `guid`=799315;

-- Adds Waypoint Movement to Koroth the Hillbreaker (guid: 799315, entry: 36528)
SET @GUID  := 799315;
SET @WP_ID := 7993150;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 799315;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(799315, 7993150, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -2189.870, 2194.490, 16.296, 0),
(@WP_ID, 2, -2165.700, 2189.120, 19.854, 0),
(@WP_ID, 3, -2141.210, 2177.520, 22.675, 0),
(@WP_ID, 4, -2128.210, 2173.930, 27.181, 0),
(@WP_ID, 5, -2102.510, 2170.630, 27.701, 0),
(@WP_ID, 6, -2088.690, 2162.790, 33.686, 0),
(@WP_ID, 7, -2077.280, 2184.070, 27.670, 0),
(@WP_ID, 8, -2085.340, 2201.400, 22.591, 0),
(@WP_ID, 9, -2100.600, 2193.230, 22.176, 0),
(@WP_ID, 10, -2114.170, 2189.790, 20.897, 0),
(@WP_ID, 11, -2138.800, 2183.540, 21.563, 0),
(@WP_ID, 12, -2159.350, 2188.480, 20.033, 0),
(@WP_ID, 13, -2186.580, 2195.010, 16.406, 0),
(@WP_ID, 14, -2201.760, 2182.050, 15.807, 0),
(@WP_ID, 15, -2191.350, 2192.030, 16.134, 0);

UPDATE `creature_template` SET `mindmg`=13, `maxdmg`=19, `attackpower`=5, `dmg_multiplier`=7 WHERE `entry`=36528;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=36459;

-- Deletes creature Lucius the Cruel (id: 36461, guid: 799333) in zone: 4714, area: 4714
DELETE FROM `creature` WHERE `guid` = 799333; DELETE FROM creature_addon WHERE guid = 799333;

DELETE FROM `creature_text` WHERE `entry`=36461;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36461,0,0,'I\'ll be taking this cat. It seems to work as the perfect bait. Prepare to die now, fool!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=7, `maxlevel`=7, `faction_A`=2173, `faction_H`=2173, `mindmg`=4, `maxdmg`=6, `attackpower`=1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=36462;

-- Lucius the Cruel
SET @ENTRY := 36461;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-2105.61,2331.66,7.31,0.46,"On Just Summoned - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,5000,5000,5000,5,16,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,1,7000,7000,0,0,19,33024,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Flags"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,1,2000,2000,0,0,12,36462,4,20000,0,0,0,8,0,0,0,-2107.97,2352.31,6.04,4.76,"IC - Summon Grandma Wahl"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,36462,100,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Grandma Wahl");

DELETE FROM `creature_text` WHERE `entry`=36462;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36462,0,0,'You do not mess with my kitty you son of a mongrel!',14,0,100,0,0,0,'Comment');

-- Grandma Wahl
SET @ENTRY := 36462;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,100,100,0,0,3,0,30288,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Human Form"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,1,500,500,0,0,49,0,0,0,0,0,0,11,36461,100,0,0.0,0.0,0.0,0.0,"OOC - Attack Lucius"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,1,2000,2000,0,0,3,0,36852,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Worgen Form"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,0,1,0,0,69,0,0,0,0,0,0,8,0,0,0,-2112.02,2376.39,7.38,2.11,"On Get Data 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,1,0,1,0,0,41,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,1,0,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Run"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,1,2000,2000,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0");

-- Chance
SET @ENTRY := 36459;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,12,36461,4,15000,0,0,0,8,0,0,0,-2112.21,2329.38,7.34,0.37,"On Gossip Hello - Summon Lucius"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,11,0,100,0,0,0,0,0,82,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set NPC Flag");

UPDATE `creature` SET `phaseMask`=2048 WHERE `id`=36488;

-- Deletes creature Grandma Wahl (id: 36458, guid: 799334) in zone: 4714, area: 4714
DELETE FROM `creature` WHERE `guid` = 799334; DELETE FROM creature_addon WHERE guid = 799334;

-- Forsaken Castaway
SET @ENTRY := 36488;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,15,0,0.0,0.0,0.0,0.0,"OOC - Attack Creatures");

UPDATE `quest_template` SET `PrevQuestId`='14403' WHERE `Id`=14412;

DELETE FROM `creature_template_addon` WHERE `entry` = '36452';
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes2`) VALUES
(36452, 238, 1);

DELETE FROM `waypoints` WHERE `entry` = '38765';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(38765, 1, -1870.36, 2282.73, 42.32, 'To Greymane Manor WP'),
(38765, 2, -1852.05, 2302.51, 41.83, 'To Greymane Manor WP'),
(38765, 3, -1829.29, 2323.74, 37.55, 'To Greymane Manor WP'),
(38765, 4, -1818.32, 2332.80, 36.37, 'To Greymane Manor WP'),
(38765, 5, -1801.58, 2344.71, 35.77, 'To Greymane Manor WP'),
(38765, 6, -1792.48, 2352.44, 36.52, 'To Greymane Manor WP'),
(38765, 7, -1787.74, 2359.60, 38.00, 'To Greymane Manor WP'),
(38765, 8, -1781.81, 2383.18, 43.27, 'To Greymane Manor WP'),
(38765, 9, -1777.55, 2423.56, 55.68, 'To Greymane Manor WP'),
(38765, 10, -1770.01, 2447.47, 62.25, 'To Greymane Manor WP'),
(38765, 11, -1754.47, 2464.13, 69.36, 'To Greymane Manor WP'),
(38765, 12, -1710.82, 2466.15, 82.81, 'To Greymane Manor WP'),
(38765, 13, -1691.46, 2493.66, 95.20, 'To Greymane Manor WP'),
(38765, 14, -1682.62, 2507.22, 97.79, 'To Greymane Manor WP'),
(38765, 15, -1669.61, 2519.56, 97.89, 'To Greymane Manor WP');

UPDATE `gameobject` SET `phaseMask`=2048 WHERE `guid`=781121;

-- Stout Mountain Horse
SET @ENTRY := 38765;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,38765,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,15,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 15 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,3,0,0,0,54,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - WP Pause (Open Gate)"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,3,0,0,0,9,0,0,0,0,0,0,14,781120,196863,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Open Gate"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,13,0,0,0,54,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - WP Pause (Open Gate)"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,13,0,0,0,9,0,0,0,0,0,0,14,781121,196864,0,0.0,0.0,0.0,0.0,"On WP Reached 13 - Open Gate");

-- Gwen Armstead
SET @ENTRY := 36452;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14465,0,0,0,85,72772,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Horse");

UPDATE `gameobject` SET `phaseMask`=32768 WHERE `guid`=781008;
UPDATE `quest_template` SET `Flags`=8 WHERE `Id`=14465;

-- Queen Mia Greymane
SET @ENTRY := 36606;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,14465,0,0,0,85,68709,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Cataclysm");

DELETE FROM `spell_script_names` WHERE `spell_id` = '69257';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(69257, 'spell_gilneas_test_telescope');

DELETE FROM `spell_script_names` WHERE `spell_id` = '42292';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(42292, 'spell_generic_pvp_trinket');

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '43336';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(43336, 43338, 0, 1, 'Stagecoach Harness - > Horse', 8, 0),
(43336, 43338, 1, 1, 'Stagecoach Harness - > Horse', 8, 0),
(43336, 44928, 2, 1, 'Stagecoach Harness - > Caravan', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '44928';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(44928, 38853, 0, 1, 'Stagecoach Carriage', 8, 0),
(44928, 44460, 2, 1, 'Stagecoach Carriage', 8, 0),
(44928, 36138, 3, 1, 'Stagecoach Carriage', 8, 0),
(44928, 43907, 4, 1, 'Stagecoach Carriage', 8, 0),
(44928, 43907, 5, 1, 'Stagecoach Carriage', 8, 0),
(44928, 51409, 6, 1, 'Stagecoach Carriage', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '44928';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(44928, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '43336';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(43336, 46598, 0);

-- Position update for Stagecoach Carriage (id: 44928) in zone: 4714, area: 4817
UPDATE `creature` SET `position_x` = -1669.974, `position_y` = 2532.950, `position_z` = 97.848, `orientation`= 4.367 WHERE `guid` = 799380;

-- Position update for Stagecoach Harness (id: 38755) in zone: 4714, area: 4817
UPDATE `creature` SET `position_x` = -1670.250, `position_y` = 2531.543, `position_z` = 97.848, `orientation`= 4.352 WHERE `guid` = 799377;

-- Position update for Stagecoach Harness (id: 38755) in zone: 4714, area: 4817
UPDATE `creature` SET `position_x` = -1670.155, `position_y` = 2532.311, `position_z` = 97.848, `orientation`= 4.387 WHERE `guid` = 799377;

-- Position update for Stagecoach Horse (id: 43338) in zone: 4714, area: 4817
UPDATE `creature` SET `position_x` = -1671.675, `position_y` = 2530.066, `position_z` = 97.848, `orientation`= 4.391 WHERE `guid` = 799378;

-- Position update for Stagecoach Horse (id: 43338) in zone: 4714, area: 4817
UPDATE `creature` SET `position_x` = -1670.333, `position_y` = 2529.619, `position_z` = 97.848, `orientation`= 4.391 WHERE `guid` = 799379;

-- Deletes creature Duskhaven Watchman (id: 37946, guid: 799385) in zone: 4714, area: 4817
DELETE FROM `creature` WHERE `guid` = 799385; DELETE FROM creature_addon WHERE guid = 799385;

-- Deletes creature Duskhaven Watchman (id: 43907, guid: 799384) in zone: 4714, area: 4817
DELETE FROM `creature` WHERE `guid` = 799384; DELETE FROM creature_addon WHERE guid = 799384;

-- Deletes creature Gwen Armstead (id: 44460, guid: 799382) in zone: 4714, area: 4817
DELETE FROM `creature` WHERE `guid` = 799382; DELETE FROM creature_addon WHERE guid = 799382;

-- Deletes creature Krennan Aranas (id: 36138, guid: 799383) in zone: 4714, area: 4817
DELETE FROM `creature` WHERE `guid` = 799383; DELETE FROM creature_addon WHERE guid = 799383;

-- Deletes creature Marie Allen (id: 38853, guid: 799381) in zone: 4714, area: 4817
DELETE FROM `creature` WHERE `guid` = 799381; DELETE FROM creature_addon WHERE guid = 799381;

-- Deletes creature Lorna Crowley (id: 51409, guid: 799386) in zone: 4714, area: 4817
DELETE FROM `creature` WHERE `guid` = 799386; DELETE FROM creature_addon WHERE guid = 799386;

UPDATE `creature_equip_template` SET `itemEntry1`=15460 WHERE `entry`=51409 AND `id`=1;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_stagecoach_carriage_exodus' WHERE `entry`=44928;

UPDATE `gameobject` SET `phaseMask`=16384 WHERE `guid`=781008;
UPDATE `creature_template` SET `ScriptName`='npc_stagecoach_harness' WHERE `entry`=43336;

DELETE FROM `script_waypoint` WHERE `entry` = '43336';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(43336, 1, -1681.45, 2508.27, 97.84, 'Carriage Harness'),
(43336, 2, -1695.46, 2486.82, 92.64, 'Carriage Harness'),
(43336, 3, -1704.99, 2468.26, 84.84, 'Carriage Harness'),
(43336, 4, -1698.38, 2447.65, 80.77, 'Carriage Harness'),
(43336, 5, -1698.42, 2432.73, 76.52, 'Carriage Harness'),
(43336, 6, -1725.88, 2390.50, 60.80, 'Carriage Harness'),
(43336, 7, -1735.64, 2362.27, 63.15, 'Carriage Harness'),
(43336, 8, -1745.18, 2343.69, 67.34, 'Carriage Harness'),
(43336, 9, -1746.53, 2329.92, 69.60, 'Carriage Harness'),
(43336, 10, -1757.21, 2300.38, 75.77, 'Carriage Harness'),
(43336, 11, -1776.38, 2271.80, 82.11, 'Carriage Harness'),
(43336, 12, -1799.38, 2251.48, 87.64, 'Carriage Harness'),
(43336, 13, -1826.19, 2238.05, 89.31, 'Carriage Harness'),
(43336, 14, -1868.50, 2174.60, 89.31, 'Carriage Harness'),
(43336, 15, -1872.45, 2135.71, 89.31, 'Carriage Harness'),
(43336, 16, -1872.96, 2075.18, 89.31, 'Carriage Harness'),
(43336, 17, -1881.14, 2046.58, 89.31, 'Carriage Harness'),
(43336, 18, -1885.72, 2019.56, 89.31, 'Carriage Harness'),
(43336, 19, -1876.85, 1970.16, 89.17, 'Carriage Harness'),
(43336, 20, -1878.35, 1921.33, 89.13, 'Carriage Harness'),
(43336, 21, -1890.52, 1904.26, 89.15, 'Carriage Harness'),
(43336, 22, -1990.23, 1901.42, 89.28, 'Carriage Harness'),
(43336, 23, -2036.81, 1914.56, 83.23, 'Carriage Harness'),
(43336, 24, -2061.07, 1905.41, 73.95, 'Carriage Harness'),
(43336, 25, -2093.23, 1881.99, 53.77, 'Carriage Harness'),
(43336, 26, -2103.06, 1870.42, 46.52, 'Carriage Harness'),
(43336, 27, -2122.61, 1831.95, 29.18, 'Carriage Harness'),
(43336, 28, -2146.32, 1814.97, 19.03, 'Carriage Harness'),
(43336, 29, -2186.33, 1808.11, 12.11, 'Carriage Harness'),
(43336, 30, -2217.77, 1809.60, 11.78, 'Carriage Harness'),
(43336, 31, -2239.38, 1805.10, 11.94, 'Carriage Harness'),
(43336, 32, -2310.30, 1774.33, 11.05, 'Carriage Harness'),
(43336, 33, -2376.50, 1704.52, 11.15, 'Carriage Harness');

DELETE FROM `creature_text` WHERE `entry`=51409;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(51409,0,0,'Look out! We\'re under attack!',14,0,100,0,0,0,'Comment');

-- Ogre Ambusher
SET @ENTRY := 38762;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,3500,4500,3500,3500,11,72768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Throw Boulder");

DELETE FROM `conditions` WHERE `SourceEntry` = '72768' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 72768, 0, 0, 31, 0, 3, 35374, 0, 0, 0, '', 'Targeting -> Boulder Triggers');

DELETE FROM `creature_text` WHERE `entry`=37065;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37065,0,0,'You will come no further, Forsaken scum! By the war banner of the ancient Greymane clan, I expel you from our ancestral lands!',14,0,100,1,0,0,'Comment'),
(37065,1,0,'Just in time, $n. Here come the Forsaken',12,0,100,1,0,0,'Comment');

SET @CGUID := 801935;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+6;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 36882, 654, 1, 16384, 0, 0, -2078.16, 1734.25, 5.62082, 2.3902, 120, 0, 0, 156, 0, 0, 0, 0, 0),
(@CGUID+1, 36882, 654, 1, 16384, 0, 0, -2047.03, 1778.71, 6.10111, 1.71475, 120, 0, 0, 156, 0, 0, 0, 0, 0),
(@CGUID+2, 36882, 654, 1, 16384, 0, 0, -2081.04, 1800.2, 5.67714, 1.21916, 120, 0, 0, 156, 0, 0, 0, 0, 0),
(@CGUID+3, 36882, 654, 1, 16384, 0, 0, -2093.24, 1771.31, 5.4132, 0.218565, 120, 0, 0, 156, 0, 0, 0, 0, 0),
(@CGUID+4, 36882, 654, 1, 16384, 0, 0, -1975.81, 1752.73, 5.75775, 1.6959, 120, 0, 0, 156, 0, 0, 0, 0, 0),
(@CGUID+5, 36882, 654, 1, 16384, 0, 0, -1969.98, 1795.78, 6.63861, 3.31304, 120, 0, 0, 156, 0, 0, 0, 0, 0),
(@CGUID+6, 36882, 654, 1, 16384, 0, 0, -1992.91, 1819.56, 5.90587, 3.18345, 120, 0, 0, 156, 0, 0, 0, 0, 0);

-- Crash Survivor
SET @ENTRY := 37067;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,114,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

UPDATE `gameobject` SET `phaseMask`=18432 WHERE `guid`=781163;

DELETE FROM `creature_text` WHERE `entry`=36294;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36294,0,0,'Corpse-men take Koroth\'s banner! Corpse-men get smashed to bitses!!!',14,0,100,0,0,0,'Comment'),
(36294,0,1,'Who dares to touch Koroth\'s banner!?',14,0,100,0,0,0,'Comment'),
(36294,0,2,'You puny thief! Koroth find you! Koroth smash your face in!',14,0,100,0,0,0,'Comment');

-- Koroth the Hillbreaker
SET @ENTRY := 36294;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,49,0,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Attack Start Player"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,80,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0");

-- Koroth's Banner
SET @ENTRY := 201594;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,799481,36294,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Talk 0");

UPDATE `creature_template` SET `mindmg`=13, `maxdmg`=19, `attackpower`=5, `dmg_multiplier`=7 WHERE `entry`=36294;

-- Prince Liam Greymane
SET @ENTRY := 37065;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,10,0,100,0,1,3,60000,60000,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"OOC LoS - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,20000,45000,20000,45000,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0");

-- Adds Waypoint Movement to Prince Liam Greymane (guid: 799423, entry: 37065)
SET @GUID  := 799423;
SET @WP_ID := 7994230;
UPDATE `creature` SET `MovementType` = 2, `spawndist` = 0 WHERE `guid` = @GUID;
DELETE FROM `creature_addon` WHERE `guid` = 799423;
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(799423, 7994230, 0, 0, 0, 0, NULL);
DELETE FROM `waypoint_data` WHERE `id` = @WP_ID;
INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `delay`) VALUES
(@WP_ID, 1, -2205.920, 1808.540, 12.124, 5),
(@WP_ID, 2, -2221.190, 1809.500, 11.797, 5);

UPDATE `creature_template` SET `mindmg`=6, `maxdmg`=12, `attackpower`=2 WHERE `entry` IN
(34511,36231,36236,36292,36312,36396,36397,36399,36460,36528,36671,36488,36454,36461,36293,36882);
UPDATE `creature_template` SET `mindmg`=6, `maxdmg`=7, `attackpower`=5, `dmg_multiplier`=3 WHERE `entry` IN
(36455, 36491, 36456, 36492);
UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid` IN (799133, 799044);
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `guid` IN (780969, 781036, 781005);
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (799074, 799072, 799049);

-- Horrid Abomination
SET @ENTRY := 36231;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,15000,15000,15000,25000,11,68864,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Restitching");

-- Forsaken Sailor
SET @ENTRY := 36396;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,3000,3000,11,75361,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Swashbuckling Slice");

-- Captain Anson
SET @ENTRY := 36397;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,8000,16500,8000,16500,11,75363,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rusty Rapier");

-- Forsaken Scout
SET @ENTRY := 36671;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,3000,3000,11,75388,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rusty Cut");

-- Forsaken Castaway
SET @ENTRY := 36488;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,15,0,0.0,0.0,0.0,0.0,"OOC - Attack Creatures"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,12500,25000,12500,30000,11,75395,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Planked");

-- Ogre Minion
SET @ENTRY := 36293;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,3000,3000,11,75436,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Clubbed");

-- Swamp Crocolisk
SET @ENTRY := 36882;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,37078,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,80,0,0.0,0.0,0.0,0.0,"OOC - Attack"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,6000,20000,6000,20000,11,3604,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Tendon Rip");
