DELETE FROM `disables` WHERE `entry` IN (86839, 87355, 71388);
INSERT INTO `disables` (`sourceType`, `entry`, `flags`, `comment`) VALUES
(0, 86839, 1, 'Heavy Manacles (Disable till script)'),
(0, 87355, 1, 'Heavy Manacles (Disable till script)'),
(0, 71388, 1, 'Rapier of the Gilnean Patriots (Disable till script)'),
(0, 101883, 1, 'Darkmoon Bandage (Disable till script)');

DELETE FROM `spell_script_names` WHERE `spell_id` = '36107';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(36107, 'spell_totem_of_spirits');

DELETE FROM `spell_script_names` WHERE `spell_id` = '75554';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(75554, 'spell_flame_ascendancy');

DELETE FROM `conditions` WHERE `SourceEntry` = '101883';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 101883, 0, 0, 31, 0, 3, 54518, 0, 0, 0, '', 'Targeting -> Injuried Carnie');