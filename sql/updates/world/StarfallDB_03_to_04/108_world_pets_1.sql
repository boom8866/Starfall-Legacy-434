
-- arglglglglg :D
REPLACE INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 67400, 0, 0, 31, 0, 3, 34694, 0, 0, 0, '', 'Zergling Attack - Target Grunty');

UPDATE `creature_template` SET `scriptname`= 'npc_pet_grunty' WHERE `entry`= 34694;
UPDATE `creature_template` SET `scriptname`= 'npc_pet_sunflower' WHERE `entry`= 51090;
