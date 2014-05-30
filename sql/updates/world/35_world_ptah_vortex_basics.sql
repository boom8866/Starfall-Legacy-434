UPDATE `creature_template` SET `VehicleId`= 741, `scriptname`= 'npc_earthrager_ptah_vortex', `unit_flags`= 33554496, `unit_flags2`= 34848, `faction_A`= 14, `faction_H`=14, `minlevel`= 85, `maxlevel`= 85 WHERE `entry`= 40406;
UPDATE `creature_template` SET `unit_flags`= 33554496 WHERE `entry`= 40503;

DELETE FROM `conditions` WHERE `SourceEntry` IN (75378, 75365, 89396);
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 2, 75378 , 0, 0, 31, 0, 3, 40458, 0, 0, 0, '', 'Consume Knockback - Target Jeweled Scarab'),
(13, 2, 75378 , 1, 0, 31, 0, 3, 40450, 0, 0, 0, '', 'Consume Knockback - Target Dustbone Horror'),
(13, 1, 75365 , 1, 0, 31, 0, 3, 40406, 0, 0, 0, '', 'Consume Vehicle Aura - Target Tomultous Earthstorm'),
(13, 2, 75378 , 1, 0, 31, 0, 3, 39443, 0, 0, 0, '', 'Sinking Sand - Target Camel');
