UPDATE `creature_onkill_reward` SET `CurrencyCount1`=70 WHERE `creature_id` IN (44600, 45992, 45993, 43735);

DELETE FROM `creature_onkill_reward` WHERE `creature_id` = '44324';
INSERT INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `MaxStanding1`, `RewOnKillRepValue1`, `CurrencyId1`, `CurrencyCount1`) VALUES
(44324, 1168, 7, 195, 396, 70);