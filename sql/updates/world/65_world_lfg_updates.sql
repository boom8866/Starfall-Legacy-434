UPDATE `quest_template` SET `RewardCurrencyCount1`= 150, `SpecialFlags`= 8 WHERE `id` IN (28905, 28906, 28907, 28908, 29185, 29183);
UPDATE `quest_template` SET `RewardCurrencyCount1`= 250, `SpecialFlags`= 8 WHERE `id` IN (30110, 30111);

DELETE FROM `lfg_gear_score` WHERE `dungeonId` IN (416, 417);
INSERT INTO `lfg_gear_score` (`dungeonId`,`gearScore`,`Comment`) VALUES
-- 372 gearScore
(416, 372, 'Siege of the Wyrmrest Temple'),
(417, 372, 'Fall of Deathwing');
