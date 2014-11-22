DELETE FROM `creature_onkill_reward` WHERE `creature_id` IN (42696, 49667);
INSERT INTO `creature_onkill_reward` (`creature_id`, `RewOnKillRepFaction1`, `RewOnKillRepFaction2`, `MaxStanding1`, `RewOnKillRepValue1`, `MaxStanding2`, `RewOnKillRepValue2`, `TeamDependent`) VALUES 
(42696, 1168, 1168, 7, 8, 7, 8, 1),
(49667, 1168, 1168, 7, 15, 7, 15, 1);