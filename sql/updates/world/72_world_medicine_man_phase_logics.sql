DELETE FROM `conditions` WHERE `SourceEntry` = '26608' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 26608, 26549, 0),
(20, 8, 26608, 26538, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '26608' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 26608, 26549, 0),
(19, 8, 26608, 26538, 0);