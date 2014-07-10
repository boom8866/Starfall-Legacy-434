DROP TABLE IF EXISTS `guild_challenges`;
CREATE TABLE IF NOT EXISTS `guild_challenges` (
  `challengeId` int(5) unsigned NOT NULL DEFAULT '0',
  `challengeRewardId` int(5) unsigned DEFAULT NULL,
  `challengeType` tinyint(1) unsigned DEFAULT NULL,
  `challengeEntry` int(5) unsigned DEFAULT NULL,
  PRIMARY KEY (`challengeId`),
  KEY `challengeRewardId` (`challengeRewardId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `guild_challenges` (`challengeId`, `challengeRewardId`, `challengeType`, `challengeEntry`) VALUES
(1, 1, 1, 568),
(2, 1, 1, 643),
(3, 1, 1, 644),
(4, 1, 1, 645),
(5, 1, 1, 657),
(6, 1, 1, 670),
(7, 1, 1, 725),
(8, 1, 1, 755),
(9, 1, 1, 859),
(10, 1, 1, 938),
(12, 1, 1, 940),
(14, 1, 1, 939),
(15, 2, 2, 669),
(16, 2, 2, 671),
(17, 2, 2, 720),
(18, 2, 2, 754),
(19, 2, 2, 757),
(20, 2, 2, 967),
(21, 3, 3, 100),
(22, 3, 3, 101),
(23, 3, 3, 102);

DROP TABLE IF EXISTS `guild_challenges_rewards`;
CREATE TABLE IF NOT EXISTS `guild_challenges_rewards` (
  `rewardId` int(5) unsigned NOT NULL DEFAULT '0',
  `xpReward` int(5) unsigned DEFAULT NULL,
  `goldReward` int(5) unsigned DEFAULT NULL,
  `goldExtraReward` int(5) unsigned DEFAULT NULL,
  PRIMARY KEY (`rewardId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO `guild_challenges_rewards` (`rewardId`, `xpReward`, `goldReward`, `goldExtraReward`) VALUES
(1, 300000, 125, 0),
(2, 300000, 500, 0),
(3, 1500000, 250, 0);
