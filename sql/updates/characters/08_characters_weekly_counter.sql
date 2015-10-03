DROP TABLE IF EXISTS `character_weekly_boss_kills`;
CREATE TABLE `character_weekly_boss_kills` (
  `guid` INT(10) UNSIGNED DEFAULT 0  NOT NULL,
  `entry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Boss Entry',
  `looted` TINYINT(3) DEFAULT '0'   NOT NULL,
  PRIMARY KEY (`guid`,`entry`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='Loot-based Lockout System';

DROP TABLE IF EXISTS `character_weekly_lfg_reward`;
CREATE TABLE `character_weekly_lfg_reward` (
  `guid` INT(10) UNSIGNED DEFAULT 0  NOT NULL,
  `questId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Boss Entry',
  `count` TINYINT(3) DEFAULT '0'   NOT NULL,
  PRIMARY KEY (`guid`,`questId`)
) ENGINE=INNODB DEFAULT CHARSET=utf8 COMMENT='Weekly Random LFG Completion Counter';
