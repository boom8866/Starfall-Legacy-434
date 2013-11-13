DROP TABLE IF EXISTS `world_quest_phases`;
CREATE TABLE `world_quest_phases` (
	`QuestId` MEDIUMINT(8) NOT NULL,
	`Phase` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`type` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT '0 on quest fail 1 on quest accept 2 on quest reward 3 on quest complete',
	`MapId` INT(5) UNSIGNED NULL DEFAULT '0' COMMENT 'Add correct MapID for phase switch',
	`ZoneId` INT(5) UNSIGNED NULL DEFAULT '0' COMMENT 'Add correct ZoneID for phase switch',
	`AreaId` INT(5) UNSIGNED NULL DEFAULT '0' COMMENT 'Add correct AreaID for phase switch',
	`Comment` TEXT NULL
)
COMMENT='Simply Phase System'
COLLATE='utf8_general_ci'
ENGINE=InnoDB;