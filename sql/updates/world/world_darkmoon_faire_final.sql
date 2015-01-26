DELETE FROM `creature_text` WHERE `entry`=14841;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(14841,0,0,'Test your skill, win a prize!',12,0,100,0,0,0,'Comment'),
(14841,0,1,'Test your aim! Test your aim!',12,0,100,0,0,0,'Comment'),
(14841,0,2,'Step right up and take your best shot!',12,0,100,0,0,0,'Comment'),
(14841,0,3,'Shoot for loot! Who wants to shoot for some loot?',12,0,100,0,0,0,'Comment'),
(14841,0,4,'If you can shoot, you can score some sweet prizes!',12,0,100,0,0,0,'Comment'),
(14841,0,5,'Guns, guns, guns! C\'mon, pal!',12,0,100,0,0,0,'Comment'),
(14841,0,6,'Folks, I\'m handing out epics over here! Don\'t miss out!',12,0,100,0,0,0,'Comment');

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