SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `character_ratedbg_stats`
-- ----------------------------
DROP TABLE IF EXISTS `character_ratedbg_stats`;
CREATE TABLE `character_ratedbg_stats` (
  `guid` int(10) unsigned NOT NULL,
  `10vs10WeeklyPlayed` int(10) unsigned NOT NULL DEFAULT '0',
  `10vs10WeeklyWins` int(10) unsigned NOT NULL DEFAULT '0',
  `PersonalRating` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;
