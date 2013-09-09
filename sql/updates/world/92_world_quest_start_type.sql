
ALTER TABLE `quest_template` DROP COLUMN `QuestStartType`;
ALTER TABLE `quest_template` ADD COLUMN `QuestStartType` mediumint(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `OfferRewardEmoteDelay4`;