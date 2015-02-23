DELETE FROM `creature_text` WHERE `entry`=14841;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(14841,0,0,'Test your skill, win a prize!',12,0,100,1,0,0,'Comment'),
(14841,0,1,'Test your aim! Test your aim!',12,0,100,1,0,0,'Comment'),
(14841,0,2,'Step right up and take your best shot!',12,0,100,1,0,0,'Comment'),
(14841,0,3,'Shoot for loot! Who wants to shoot for some loot?',12,0,100,1,0,0,'Comment'),
(14841,0,4,'If you can shoot, you can score some sweet prizes!',12,0,100,1,0,0,'Comment'),
(14841,0,5,'Guns, guns, guns! C\'mon, pal!',12,0,100,1,0,0,'Comment'),
(14841,0,6,'Folks, I\'m handing out epics over here! Don\'t miss out!',12,0,100,1,0,0,'Comment');

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=6226 WHERE  `menu_id`=6225 AND `id`=0;
UPDATE `gossip_menu_option` SET `npc_option_npcflag`=1 WHERE `menu_id`=6225 AND `id`=1;

DELETE FROM `gossip_menu` WHERE `entry` = '6226' AND `text_id` = '18370';
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(6226, 18370);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '6226';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(6226, 0, 0, 'I understdood.', 1, 1, 0, 0, 0, 0, NULL);

-- Rinling
SET @ENTRY := 14841;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,30000,60000,60000,120000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,6226,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,3,62,0,100,0,6225,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,57,71083,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Token"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,75,101871,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Shoot");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 14841;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 3, 14841, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play'),
(22, 4, 14841, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play'),
(22, 5, 14841, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play');

DELETE FROM `gameobject` WHERE `guid` = '781664';
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(781664, 300129, 974, 1, 1, -4074.09, 6351.28, 14.0099, 0.811717, 0, 0, 0.394807, 0.918764, 300, 0, 1);

DELETE FROM `creature` WHERE `guid` = '842918';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(842918, 24220, 974, 1, 1, 0, 0, -4074.13, 6351.32, 15.0087, 0.852061, 300, 0, 0, 57, 0, 0, 0, 33554432, 0);

UPDATE `creature_template` SET `ScriptName`='npc_df_shoot_target_controller' WHERE `entry`=24220;

DELETE FROM `conditions` WHERE `SourceEntry` = '101872';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 101872, 0, 0, 31, 0, 3, 24171, 0, 0, 0, '', 'Targeting -> Darkmoon Faire Target Bunny');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '43313';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(43313, 101010, 'Darkmoon Target -> Quick Shot');

DELETE FROM `creature_text` WHERE `entry`=24171;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(24171,0,0,'Quick Shot!',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_df_darkmoon_target_bunny' WHERE `entry`=24171;

DELETE FROM `npc_vendor` WHERE `entry` = '14844' AND `item` = '74822';
INSERT INTO `npc_vendor` (`entry`, `item`) VALUES
(14844, 74822);

-- Kolin
SET @ENTRY := 56035;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,22,0,100,0,34,5,5,0,5,94,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Receive Emote - Dance");

UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `guid`=8981;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=13012 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=13013 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=13013 WHERE  `menu_id`=13012 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=54485;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(54485,0,0,'Hey, hey $C! Think you can land a ring on a slow moving turtle?',12,0,100,1,0,0,'Comment'),
(54485,1,0,'Simple game, for simple folk. Think you can manage it?',12,0,100,1,0,0,'Comment'),
(54485,1,1,'Toss a ring, win a prize!',12,0,100,1,0,0,'Comment'),
(54485,1,2,'You look like you\'ve got quite the arm there. Care to give this game a try?',12,0,100,1,0,0,'Comment');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 54485;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 4, 54485, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play');

DELETE FROM `conditions` WHERE `SourceEntry` = '101695';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 101695, 0, 0, 31, 0, 3, 54490, 0, 0, 0, '', 'Targeting -> Dubenko');

DELETE FROM `spell_script_names` WHERE `spell_id` = '101695';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(101695, 'spell_df_ring_toss');

DELETE FROM `spell_script_names` WHERE `spell_id` = '102058';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(102058, 'spell_df_ring_powerbar');

UPDATE `creature_template` SET `ScriptName`='npc_df_dubenko' WHERE `entry`=54490;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '7338';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(7338, 'at_target_turtle');

-- Jessica Rogers
SET @ENTRY := 54485;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,30000,60000,35000,45000,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 1"),
(@ENTRY,@SOURCETYPE,1,0,10,0,100,0,1,5,120000,180000,1,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"OOC LoS - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,13013,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,4,62,0,100,0,13012,1,0,0,57,71083,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Token"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,75,102058,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Toss Aura"),
(@ENTRY,@SOURCETYPE,6,0,20,0,100,0,29455,0,0,0,28,102058,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove Rings");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=13019 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=13066 WHERE `menu_id`=13019 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=13066 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=54605;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(54605,0,0,'We\'re under attack! Step up and do your part, $C!',12,0,100,1,0,0,'Comment'),
(54605,1,0,'Tonks! We got tonks here!',12,0,100,1,0,0,'Comment'),
(54605,1,1,'Step right up and try a tonk!',12,0,100,1,0,0,'Comment'),
(54605,1,2,'Hey, hey! Command a tonk in glorious battle!',12,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `VehicleId`=1734 WHERE `entry`=54588;
UPDATE `creature` SET `spawntimesecs`=30, `spawndist`=4, `MovementType`=1 WHERE `id` IN (54642, 54643);

-- Finlay Coolshot
SET @ENTRY := 54605;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,35000,60000,45000,60000,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 1"),
(@ENTRY,@SOURCETYPE,1,0,10,0,100,0,1,5,60000,180000,1,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"OOC LoS - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,13066,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,4,62,0,100,0,13019,1,0,0,57,71083,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Item"),
(@ENTRY,@SOURCETYPE,4,5,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,85,100752,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Tonk");

UPDATE `gossip_menu_option` SET `option_id`=1 WHERE `menu_id`=6225 AND `id`=1;

-- Enemy MiniZep
SET @ENTRY := 54643;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,5000,10000,15000,11,102209,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Bombs Away");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '100752';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(100752, 102178, 2, 'Tonk Timer!');

DELETE FROM `spell_target_position` WHERE `id` = '100752';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(100752, 974, -4133.14, 6321.41, 13.11, 3.96);

UPDATE `creature_template` SET `speed_walk`=0.8, `speed_run`=0.857143 WHERE `entry`=54588;

-- Tonk Target
SET @ENTRY := 33081;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,30000,60000,30000,60000,0,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Despawn"),
(@ENTRY,@SOURCETYPE,1,2,6,0,100,0,0,0,0,0,85,62265,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Cast Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Despawn");

DELETE FROM `areatrigger_scripts` WHERE `entry` = '7340';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(7340, 'at_tonks_zone');

DELETE FROM `conditions` WHERE `SourceEntry` = '102292';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 102292, 0, 0, 31, 0, 3, 33081, 0, 0, 0, '', 'Targeting -> Tonk Target');

DELETE FROM `spell_script_names` WHERE `spell_id` = '62265';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(62265, 'spell_df_tonks_credit');

-- Enemy Tonk
SET @ENTRY := 54642;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,12500,24000,11,102341,0,0,0,0,0,11,54588,6,0,0.0,0.0,0.0,0.0,"OOC - Cast Marked");

DELETE FROM `spell_script_names` WHERE `spell_id` = '102341';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(102341, 'spell_dk_tonk_marked');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 22 AND `SourceEntry` = 54605;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 4, 54605, 0, 0, 2, 0, 71083, 1, 0, 0, 0, 0, '', 'Need Token to play');