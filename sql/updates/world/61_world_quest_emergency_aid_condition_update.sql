DELETE FROM `conditions` WHERE `SourceEntry` = '26619' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 26619, 26608, 0),
(20, 8, 26619, 26540, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '26619' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 26619, 26608, 0),
(19, 8, 26619, 26540, 0);