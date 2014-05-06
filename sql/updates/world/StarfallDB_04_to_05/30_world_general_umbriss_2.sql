
UPDATE `creature_template` SET `scriptname`= 'npc_gb_malignant_trogg' WHERE `entry`= 39984;
UPDATE `creature_template` SET `scriptname`= 'npc_gb_trogg_dweller' WHERE `entry`= 45467;

DELETE FROM conditions WHERE SourceEntry = 90170;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 1, 90170, 1, 0, 31, 0, 3, 39625, 0, 0, 0, '', 'Godmunds Malice - Target General Umbriss'),
(13, 2, 90170, 1, 0, 31, 0, 3, 39625, 0, 0, 0, '', 'Godmunds Malice - Target General Umbriss'),
(13, 4, 90170, 0, 0, 31, 0, 3, 45467, 0, 0, 0, '', 'Godmunds Malice - Target Trogg Dweller');
