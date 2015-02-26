DELETE FROM `conditions` WHERE `SourceEntry` = '28593' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 28593, 28593, 0),
(20, 8, 28593, 28594, 0),
(20, 8, 28593, 28592, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '28593' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 28593, 28593, 0),
(19, 8, 28593, 28594, 0),
(19, 8, 28593, 28592, 0);