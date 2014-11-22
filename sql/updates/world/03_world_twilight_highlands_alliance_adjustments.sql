fDELETE FROM `conditions` WHERE `SourceEntry` = '27044' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27044, 26977, 0),
(20, 8, 27044, 26997, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27044' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27044, 26977, 0),
(19, 8, 27044, 26997, 0);

UPDATE `quest_template` SET `PrevQuestId`='27064' WHERE `Id`=28807;

