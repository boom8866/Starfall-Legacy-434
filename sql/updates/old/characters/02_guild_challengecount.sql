ALTER TABLE `guild`
	CHANGE COLUMN `ChallengeCount` `ChallengeCount` INT(32) UNSIGNED NOT NULL DEFAULT '0' AFTER `todayExperience`;