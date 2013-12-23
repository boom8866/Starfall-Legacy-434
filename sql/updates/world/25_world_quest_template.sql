ALTER TABLE `quest_template`
ALTER `PrevQuestId` DROP DEFAULT,
ALTER `NextQuestId` DROP DEFAULT;

ALTER TABLE `quest_template`
CHANGE COLUMN `PrevQuestId` `PrevQuestId` TEXT NULL AFTER `RequiredMaxRepValue`,
CHANGE COLUMN `NextQuestId` `NextQuestId` TEXT NULL AFTER `PrevQuestId`;
