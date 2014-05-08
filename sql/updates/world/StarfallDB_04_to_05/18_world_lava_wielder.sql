
UPDATE `creature_template` SET `scriptname`= 'npc_fl_lava_wielder' WHERE `entry`= 53575;
UPDATE `creature_template` SET `InhabitType`= 4 WHERE `entry`= 53585;
DELETE FROM `creature` WHERE `id`= 53585;
DELETE FROM `creature_addon` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);

DELETE FROM `conditions` WHERE `SourceEntry`= 99503;
INSERT INTO `conditions` (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 99503, 0, 0, 31, 0, 3, 53585, 0, 0, 0, '', 'Raise Lava - Target Lava Dummy');

REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(99503, 'spell_fl_raise_lava');
