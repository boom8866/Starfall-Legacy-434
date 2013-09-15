DELETE FROM `creature` WHERE  `id`=36727;
DELETE FROM `creature` WHERE  `id`=37156;
DELETE FROM `creature` WHERE  `id`=37155;
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(36727, 1, 1, 1, 0, 0, -3358,21, -232,444, 63,0433, 0, 300, 0, 0, 274, 0, 0, 0, 0, 0),
(37156, 1, 1, 1, 0, 0, -3406,35, -265,036, 62,7771, 0, 300, 0, 0, 274, 0, 0, 0, 0, 0),
(37155, 1, 1, 1, 0, 0, -3391,44, -210,651, 62,8214, 0, 300, 0, 0, 274, 0, 0, 0, 0, 0);

UPDATE `creature_template` SET `ScriptName`='npc_trough' WHERE  `entry`=36727;
UPDATE `creature_template` SET `ScriptName`='npc_trough' WHERE  `entry`=37155;
UPDATE `creature_template` SET `ScriptName`='npc_trough' WHERE  `entry`=37156;

DELETE FROM `conditions` WHERE `SourceEntry` = '69228';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 0, 69228, 0, 0, 31, 0, 3, 37156, 0, 0, 0, 0, '', 'Throw Torch for NPC: 37156'),
(13, 0, 69228, 0, 0, 31, 0, 3, 37155, 0, 0, 0, 0, '', 'Throw Torch for NPC: 37155'),
(13, 0, 69228, 0, 0, 31, 0, 3, 36727, 0, 0, 0, 0, '', 'Throw Torch for NPC: 36727');