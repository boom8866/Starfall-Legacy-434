UPDATE `quest_template` SET `QuestStartType`= 1 WHERE `id` IN (28737);
SET @CORLATRIGGER := 6593;

DELETE FROM `areatrigger_queststart` WHERE `trigger_id`= @CORLATRIGGER;
INSERT INTO `areatrigger_queststart` (`trigger_id`, `quest_id`) VALUES
(@CORLATRIGGER, 28737);
