DELETE FROM `creature` WHERE `id` In (36727, 37156, 37155);
SET @CGUID := 786684;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+2;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0,37156,1,1,1,-3406.3501,-265.036011,62.7770996,0,300,3,1),
(@CGUID+1,36727,1,1,1,-3358.20996,-232.444,63.0433006,0,300,3,1),
(@CGUID+2,37155,1,1,1,-3391.43994,-210.651001,62.8213997,0,300,3,1);

UPDATE `creature_template` SET `ScriptName`= 'npc_trough' WHERE `entry`= 36727;
UPDATE `creature_template` SET `ScriptName`= 'npc_trough' WHERE `entry`= 37155;
UPDATE `creature_template` SET `ScriptName`= 'npc_trough' WHERE `entry`= 37156;

DELETE FROM `conditions` WHERE `SourceEntry`= 69228;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 0, 69228, 0, 0, 31, 0, 3, 37156, 0, 0, 0, '', 'Throw Torch for NPC: 37156'),
(13, 0, 69228, 0, 0, 31, 0, 3, 37155, 0, 0, 0, '', 'Throw Torch for NPC: 37155'),
(13, 0, 69228, 0, 0, 31, 0, 3, 36727, 0, 0, 0, '', 'Throw Torch for NPC: 36727');