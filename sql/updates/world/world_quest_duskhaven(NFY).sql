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