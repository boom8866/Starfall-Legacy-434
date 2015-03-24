DELETE FROM `conditions` WHERE `SourceEntry` = '80962';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 80962, 0, 0, 31, 0, 3, 43331, 0, 0, 0, '', 'Targeting -> Golden Stonefish');

UPDATE `creature_template` SET `lootid`=43331 WHERE `entry`=43331;

DELETE FROM `creature_loot_template` WHERE `entry` = '43331';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(43331, 58960, -100, 1, 0, 1, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` = '80948';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(80948, 'spell_razgar_fillet_knife');

DELETE FROM `disables` WHERE `sourceType` = '0' AND `entry` = '80962';